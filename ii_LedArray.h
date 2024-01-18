#ifndef ii_LedArray_H
#define ii_LedArray_H

#include <driver/rmt.h>
#include <driver/gpio.h>
#include "colors.h"
#include "pixel.h"

class ii_LedArray
{
private:
    int LED_COUNT;
    int GPIO_NUM;

    bool MODE_UPDATE;

    // You can define a list of channels and iterate through them
    const rmt_channel_t availableChannels[8] = {RMT_CHANNEL_0, RMT_CHANNEL_1, RMT_CHANNEL_2, RMT_CHANNEL_3, RMT_CHANNEL_4, RMT_CHANNEL_5, RMT_CHANNEL_6, RMT_CHANNEL_7};
    rmt_channel_t selectedChannel = RMT_CHANNEL_0;

// WS2812 Timing (in ticks, assuming 80MHz clock for RMT)
#define WS2812_T0H 14   // 350ns
#define WS2812_T0L 28   // 700ns
#define WS2812_T1H 28   // 700ns
#define WS2812_T1L 14   // 350ns
#define WS2812_RESET 50 // >50us

    int brightness;
    float brightness_p;
    void changed();
    int patternstart;
    bool patterndir;
    int selectedpattern;
    Pixel *pixels = nullptr;
    bool filled_;
    bool _changedb;

    // Function to allocate memory for the pixel array
    void allocatePixelsArray(int size);

    bool setupRMT(rmt_channel_t channel);

    void send_ws2812_bit(bool bitVal);
    void send_ws2812_color(uint8_t red, uint8_t green, uint8_t blue);
    void send_reset();

public:
    // Show the current LED colors
    void send();

    Colors colors;
    // Constructor
    ii_LedArray();
    ii_LedArray(int pin, int ledcount);

    // Initialize the LED strip
    void begin();

    // Test the LED strip with color transitions
    void test();

    // Test the LED strip with all available colors
    void testAll();

    // Clear all colors on the LED strip
    void clear();

    // Update the LED strip with any pixel animations
    bool update();

    // Set the brightness of the LED strip
    void setBrightness(int bright); // Brightness range: 0-100

    // Get the brightness of the LED strip
    int getBrightness();

    // Get the color of a specific LED
    uint32_t getColor(int index);

    // Create a pattern with all available colors
    void _patternAllColors(bool changedir);

    // Move colors in the LED strip in a specified direction
    void move(bool direction);

    bool isFilled() const;

    void setFilled(bool filled);

    // Get the number of LEDs in the strip
    int getLength();

    // Set the color of a specific LED using a 32-bit color value
    void setColor(uint8_t index, uint32_t color);

    // Set the color of a specific LED using RGB values
    void setColor(uint8_t index, uint8_t red, uint8_t green, uint8_t blue);

    //
    void setColor(uint32_t color);

    // Set the same color for all LEDs
    void setColor(uint8_t red, uint8_t green, uint8_t blue);

    //////////////////////////////////////////////////////////////////////

    // Set the color of a specific LED with a start time and duration using a 32-bit color value
    void setColorTrans(uint8_t index, uint32_t color, long start, long duration);

    // Set the color of a specific LED with a start time and duration
    void setColorTrans(uint8_t index, uint8_t red, uint8_t green, uint8_t blue, long start, long duration);

    //
    void setColorTrans(uint32_t color, long start, long duration);

    // Set the same color for all LEDs with a start time and duration
    void setColorTrans(uint8_t red, uint8_t green, uint8_t blue, long start, long duration);

    // validations
    bool checkRange(int n);
};

#endif
