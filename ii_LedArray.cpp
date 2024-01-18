#include <Arduino.h>
#include "ii_LedArray.h"

ii_LedArray::ii_LedArray()
{
}

ii_LedArray::ii_LedArray(int pin, int ledcount)
{
    LED_COUNT = ledcount;
    GPIO_NUM = pin;
}

void ii_LedArray::begin()
{

    // Try to setup RMT on available channels
    for (size_t i = 0; i < sizeof(availableChannels) / sizeof(availableChannels[0]); ++i)
    {
        if (setupRMT(availableChannels[i]))
        {
            selectedChannel = availableChannels[i];
            break;
        }
    }

    rmt_config_t config = RMT_DEFAULT_CONFIG_TX((gpio_num_t)GPIO_NUM, selectedChannel);
    config.clk_div = 2; // Adjust clock divider for accurate timing

    rmt_config(&config);
    rmt_driver_install(config.channel, 0, 0);

    allocatePixelsArray(LED_COUNT);
}

void ii_LedArray::allocatePixelsArray(int size)
{
    if (pixels != nullptr)
    {
        delete[] pixels; // Free previously allocated memory, if any
    }
    if (size > 0)
    {
        pixels = new Pixel[size];
        clear();
    }
}

void ii_LedArray::test()
{
    for (int c = 3; c > -1; c--)
    {
        for (int n = 0; n < LED_COUNT; n++)
        {
            setColor(n, colors.get(c));
            send();
            delay(100);
        }
        delay(1000);
    }
}

void ii_LedArray::testAll()
{
    for (int c = colors.getColorsCount() - 1; c > -1; c--)
    {
        Serial.println(colors.getName(c));
        for (int n = 0; n < LED_COUNT; n++)
        {
            setColor(n, colors.get(c));
            send();
            delay(100);
        }
        delay(3000);
    }
}

void ii_LedArray::clear()
{
    for (int i = 0; i < getLength(); i++)
    {
        send_ws2812_color(0, 0, 0);
    }
    send_reset();
}

void ii_LedArray::send()
{
    if (_changedb)
    {

        for (int i = 0; i < getLength(); i++)
        {
            send_ws2812_color(pixels[i].getRed(), pixels[i].getGreen(), pixels[i].getBlue());
        }
        send_reset();
        _changedb = false;
    }
}

void ii_LedArray::changed()
{
    _changedb = true;
}

void ii_LedArray::setBrightness(int bright)
{
    brightness = bright;
    brightness_p = (float)brightness / 100.0;
    changed();
}

int ii_LedArray::getLength()
{
    return LED_COUNT;
}

int ii_LedArray::getBrightness()
{
    return brightness;
}

bool ii_LedArray::isFilled() const
{
    return filled_;
}

void ii_LedArray::setFilled(bool filled)
{
    filled_ = filled;
}

/////////////////////////////////////////////////////////////////////////
void ii_LedArray::setColor(uint8_t index, uint32_t color)
{
    uint8_t r, g, b;
    colors.ColorToRGB(color, r, g, b);
    setColor(index, r, g, b);
}

void ii_LedArray::setColor(uint8_t index, uint8_t red, uint8_t green, uint8_t blue)
{
    if (!checkRange(index))
    {
        return;
    }
    pixels[index].setColor(red, green, blue);
    changed();
}

//////////////////////////////////////////////////////////////////////////////
void ii_LedArray::setColor(uint32_t color)
{
    for (int n = 0; n < LED_COUNT; n++)
    {
        setColor(n, (color >> 16) & 0xff, (color >> 8) & 0xff, color & 0xff);
    }
}

void ii_LedArray::setColor(uint8_t red, uint8_t green, uint8_t blue)
{
    for (int n = 0; n < LED_COUNT; n++)
    {
        setColor(n, red, green, blue);
    }
}

void ii_LedArray::setColorTrans(uint8_t index, uint8_t red, uint8_t green, uint8_t blue, long start, long duration)
{
    if (!checkRange(index))
    {
        return;
    }
    pixels[index].setTargetColor(red, green, blue, start, duration);
    MODE_UPDATE = true;
}

void ii_LedArray::setColorTrans(uint8_t index, uint32_t color, long start, long duration)
{
    if (!checkRange(index))
    {
        return;
    }
    pixels[index].setTargetColor((color >> 16) & 0xff, (color >> 8) & 0xff, color & 0xff, start, duration);
    MODE_UPDATE = true;
}

void ii_LedArray::setColorTrans(uint32_t color, long start, long duration)
{
    for (int n = 0; n < getLength(); n++)
    {
        pixels[n].setTargetColor((color >> 16) & 0xff, (color >> 8) & 0xff, color & 0xff, start, duration);
    }
    MODE_UPDATE = true;
}

void ii_LedArray::setColorTrans(uint8_t red, uint8_t green, uint8_t blue, long start, long duration)
{
    for (int n = 0; n < getLength(); n++)
    {
        pixels[n].setTargetColor(red, green, blue, start, duration);
    }
    MODE_UPDATE = true;
}

uint32_t ii_LedArray::getColor(int index)
{
    return pixels[index].getColor();
}

bool ii_LedArray::checkRange(int n)
{
    if (n < 0 || n >= getLength())
    {
        Serial.println("ERROR:invalid index value (" + String(n) + ") PIN:" + String(3) + "\nLENGTH:" + getLength());
        return false;
    }
    else
    {
        return true;
    }
}
////////////////////////////////////////////////////////////////////////////////

void ii_LedArray::_patternAllColors(bool changedir)
{
    if (!patterndir)
    {
        patternstart++;
        if (patternstart == LED_COUNT)
        {
            if (changedir)
            {
                patterndir = true;
            }
            else
            {
                patternstart = 0;
            }
        }
    }
    else
    {
        patternstart--;
        if (patternstart == 0)
        {
            if (changedir)
            {
                patterndir = false;
            }
            else
            {
                patternstart = LED_COUNT - 1;
            }
        }
    }

    int cn = 0;
    for (int n = patternstart; n < LED_COUNT && cn < colors.getColorsCount(); n++)
    {
        setColor(n, colors.get(cn));
        cn++;
    }

    for (int n = 0; n < patternstart && cn < colors.getColorsCount(); n++)
    {
        setColor(n, colors.get(cn));
        cn++;
    }
}

void ii_LedArray::move(bool direction)
{
    if (direction)
    {
        uint32_t lastcolor = getColor(0);
        for (int i = 0; i < LED_COUNT - 1; i++)
        {
            uint32_t color = getColor(i + 1);
            setColor(i + 1, lastcolor);
            lastcolor = color;
        }
        setColor(0, lastcolor);
    }
    else
    {
        uint32_t lastcolor = getColor(LED_COUNT - 1);
        for (int i = LED_COUNT - 1; i > 0; i--)
        {
            uint32_t color = getColor(i - 1);
            setColor(i - 1, lastcolor);
            lastcolor = color;
        }
        setColor(LED_COUNT - 1, lastcolor);
    }
}

bool ii_LedArray::update()
{

    if (!MODE_UPDATE)
    {
        send();
        return true;
    }
    boolean array_changed = false;
    for (int i = 0; i < getLength(); i++)
    {

        boolean pixel_changed = false;
        for (int c = 0; c < 3; c++)
        {
            if (pixels[i].getColor(c) != pixels[i].getTargetColor(c))
            {
                pixel_changed = true;
            }
        }

        pixels[i].setFilled(!pixel_changed && !(millis() < pixels[i].getStart()));
        // Serial.println(pixels[i].getStart());
        if (millis() < pixels[i].getStart())
        {
            array_changed = true;
        }
        else if (pixel_changed)
        {
            if (pixels[i].getDuration() == 0)
            {
                for (int c = 0; c < 3; c++)
                {
                    if (pixels[i].getColor(c) != pixels[i].getTargetColor(c))
                    {
                        pixels[i].setColor(c, pixels[i].getTargetColor(c));
                    }
                }
            }
            else
            {
                float proportion = ((float)(millis() - pixels[i].getStart())) / (float)pixels[i].getDuration();
                if (proportion < 0.01)
                {
                    proportion = 0.01;
                }
                if (proportion > 1.0)
                {
                    proportion = 1.0;
                }
                for (int c = 0; c < 3; c++)
                {
                    if (pixels[i].getColor(c) != pixels[i].getTargetColor(c))
                    {
                        if (proportion >= 1.0)
                        {
                            pixels[i].setColor(c, pixels[i].getTargetColor(c));
                        }
                        else
                        {
                            byte value = pixels[i].getLastColor(c) + (((float)pixels[i].getTargetColor(c) - (float)pixels[i].getLastColor(c)) * proportion);
                            pixels[i].setColor(c, value);
                        }
                    }
                }
            }
            // Serial.println(String(proportion)+":\t"+String(pixels[i].getRed())+"\t"+String(pixels[i].getGreen())+"\t"+String(pixels[i].getBlue()));
            setColor(i, pixels[i].getRed(), pixels[i].getGreen(), pixels[i].getBlue());
            array_changed = true;
        }
    }
    if (array_changed)
    {
        changed();
        send();
        setFilled(false);
        return true;
    }
    else
    {
        MODE_UPDATE = false;
        setFilled(true);
        return false;
    }
}

bool ii_LedArray::setupRMT(rmt_channel_t channel)
{
    rmt_config_t config = RMT_DEFAULT_CONFIG_TX((gpio_num_t)GPIO_NUM, channel);
    config.clk_div = 2;

    esp_err_t configStatus = rmt_config(&config);
    if (configStatus != ESP_OK)
    {
        return false; // Configuration failed
    }

    esp_err_t installStatus = rmt_driver_install(config.channel, 0, 0);
    if (installStatus != ESP_OK)
    {
        return false; // Driver installation failed
    }

    return true; // Success
}

void ii_LedArray::send_ws2812_bit(bool bitVal)
{
    rmt_item32_t item;
    item.level0 = 1;
    item.duration0 = bitVal ? WS2812_T1H : WS2812_T0H;
    item.level1 = 0;
    item.duration1 = bitVal ? WS2812_T1L : WS2812_T0L;

    rmt_write_items(selectedChannel, &item, 1, true);
}

void ii_LedArray::send_ws2812_color(uint8_t red, uint8_t green, uint8_t blue)
{
    // Send green, red, and blue components
    for (int i = 7; i >= 0; i--)
    {
        send_ws2812_bit(green & (1 << i));
    }
    for (int i = 7; i >= 0; i--)
    {
        send_ws2812_bit(red & (1 << i));
    }
    for (int i = 7; i >= 0; i--)
    {
        send_ws2812_bit(blue & (1 << i));
    }
}

void ii_LedArray::send_reset()
{
    rmt_item32_t item;
    item.level0 = 0;
    item.duration0 = WS2812_RESET;
    item.level1 = 0;
    item.duration1 = 0;
    rmt_write_items(selectedChannel, &item, 1, true);
}