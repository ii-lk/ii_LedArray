#include <Arduino.h>
#include "CODBOTS_LedArray.h"

CODBOTS_LedArray::CODBOTS_LedArray()
{
}

CODBOTS_LedArray::CODBOTS_LedArray(int pin, int ledcount)
{
    strip = Adafruit_NeoPixel(ledcount, pin, NEO_GRB + NEO_KHZ800);
}

void CODBOTS_LedArray::setBlurMode(bool bmode)
{
    blurmode = bmode;
    if (blurmode)
    {
        allocatePixelsArray(strip.numPixels());
    }
    else
    {
        allocatePixelsArray(0);
    }
}

void CODBOTS_LedArray::begin()
{
    strip.begin();
    for (int n = 0; n < strip.numPixels(); n++)
    {
        strip.setPixelColor(n, 0, 0, 0);
    }
    setBrightness(20);
    strip.show();
}

void CODBOTS_LedArray::allocatePixelsArray(int size)
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

void CODBOTS_LedArray::test()
{
    for (int c = 3; c > -1; c--)
    {
        for (int n = 0; n < strip.numPixels(); n++)
        {
            setColor(n, colors.get(c));
            show();
            delay(100);
        }
        delay(1000);
    }
}

void CODBOTS_LedArray::testAll()
{
    for (int c = colors.getColorsCount() - 1; c > -1; c--)
    {
        Serial.println(colors.getName(c));
        for (int n = 0; n < strip.numPixels(); n++)
        {
            setColor(n, colors.get(c));
            show();
            delay(100);
        }
        delay(3000);
    }
}

void CODBOTS_LedArray::clear()
{
    strip.clear();
}

void CODBOTS_LedArray::show()
{
    if (_changedb)
    {
        for (int i = 0; i < getLength(); i++)
        {
            // Serial.println(String(pixels[i].getRed()) + "," + String(pixels[i].getGreen()) + "," + String(pixels[i].getBlue()) + ",");
            strip.setPixelColor(i, pixels[i].getRed(), pixels[i].getGreen(), pixels[i].getBlue());
        }
        strip.show();
        _changedb = false;
    }
}

void CODBOTS_LedArray::changed()
{
    _changedb = true;
}

void CODBOTS_LedArray::setBrightness(int bright)
{
    strip.setBrightness(map(bright, 0, 100, 0, 255));
    changed();
}

int CODBOTS_LedArray::getLength()
{
    return strip.numPixels();
}

int CODBOTS_LedArray::getBrightness()
{
    return brightness;
}

bool CODBOTS_LedArray::isFilled() const
{
    return filled_;
}

void CODBOTS_LedArray::setFilled(bool filled)
{
    filled_ = filled;
}

void CODBOTS_LedArray::setColor(uint8_t index, uint32_t color)
{
    uint8_t r, g, b;
    colors.ColorToRGB(color, r, g, b);
    setColor(index, r, g, b);
}

void CODBOTS_LedArray::setColor(uint8_t index, uint8_t red, uint8_t green, uint8_t blue)
{
    if (!checkRange(index))
    {
        return;
    }
    pixels[index].setColor(red, green, blue);
    changed();
}

void CODBOTS_LedArray::setColorTime(uint8_t index, uint8_t red, uint8_t green, uint8_t blue, long start, long duration)
{
    if (!checkRange(index))
    {
        return;
    }
    pixels[index].setTargetColor(red, green, blue, start, duration);
}

void CODBOTS_LedArray::setColorTime(uint8_t index, uint32_t color, long start, long duration)
{
    if (!checkRange(index))
    {
        return;
    }
    pixels[index].setTargetColor((color >> 16) & 0xff, (color >> 8) & 0xff, color & 0xff, start, duration);
}

uint32_t CODBOTS_LedArray::getColor(int index)
{
    return pixels[index].getColor();
}

void CODBOTS_LedArray::setColorAll(uint8_t red, uint8_t green, uint8_t blue)
{
    for (int n = 0; n < strip.numPixels(); n++)
    {
        setColor(n, red, green, blue);
    }
}

void CODBOTS_LedArray::setColorAll(uint8_t red, uint8_t green, uint8_t blue, long start, long duration)
{
    for (int n = 0; n < getLength(); n++)
    {
        pixels[n].setTargetColor(red, green, blue, start, duration);
    }
}

bool CODBOTS_LedArray::checkRange(int n)
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

void CODBOTS_LedArray::_patternAllColors(bool changedir)
{
    if (!patterndir)
    {
        patternstart++;
        if (patternstart == strip.numPixels())
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
                patternstart = strip.numPixels() - 1;
            }
        }
    }

    int cn = 0;
    for (int n = patternstart; n < strip.numPixels() && cn < colors.getColorsCount(); n++)
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

void CODBOTS_LedArray::move(bool direction)
{
    if (direction)
    {
        uint32_t lastcolor = getColor(0);
        for (int i = 0; i < strip.numPixels() - 1; i++)
        {
            uint32_t color = getColor(i + 1);
            setColor(i + 1, lastcolor);
            lastcolor = color;
        }
        setColor(0, lastcolor);
    }
    else
    {
        uint32_t lastcolor = getColor(strip.numPixels() - 1);
        for (int i = strip.numPixels() - 1; i > 0; i--)
        {
            uint32_t color = getColor(i - 1);
            setColor(i - 1, lastcolor);
            lastcolor = color;
        }
        setColor(strip.numPixels() - 1, lastcolor);
    }
    // changed();
}

bool CODBOTS_LedArray::update()
{
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
        show();
        setFilled(false);
        return true;
    }
    else
    {
        setFilled(true);
        return false;
    }
}
