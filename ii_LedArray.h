#ifndef ii_LedArray_H
#define ii_LedArray_H

#include <driver/rmt.h>
#include <driver/gpio.h>
#include "colors.h"
#include "pixel.h"

/**
 * ii_LedArray Class for controlling WS2812 LED strips.
 * This class provides functionality to control LED strips, including setting colors,
 * managing transitions, brightness control, and moving patterns. It utilizes the RMT peripheral
 * of the ESP32 for precise timing required by WS2812 LEDs.
 */
class ii_LedArray
{
private:
    int LED_COUNT; // Number of LEDs in the strip
    int GPIO_NUM;  // GPIO pin number connected to the LED strip

    bool MODE_UPDATE; // Flag to track if an update is needed

    // Array of available RMT channels on ESP32
    const rmt_channel_t availableChannels[8] = {RMT_CHANNEL_0, RMT_CHANNEL_1, RMT_CHANNEL_2, RMT_CHANNEL_3, RMT_CHANNEL_4, RMT_CHANNEL_5, RMT_CHANNEL_6, RMT_CHANNEL_7};
    rmt_channel_t selectedChannel = RMT_CHANNEL_0; // Selected RMT channel

    // WS2812 Timing constants (in ticks)
#define WS2812_T0H 14   // 350ns
#define WS2812_T0L 28   // 700ns
#define WS2812_T1H 28   // 700ns
#define WS2812_T1L 14   // 350ns
#define WS2812_RESET 50 // >50us

    int brightness;            // Brightness level (0-100)
    float brightness_p = 1.0f; // Brightness percentage
    int bright(int color);     // Function to calculate brightness-adjusted color
    void changed();            // Function to indicate a change in LED state
    int patternstart;          // Start index for patterns
    bool patterndir;           // Direction for pattern movement
    int selectedpattern;       // Index of the selected pattern
    Pixel *pixels = nullptr;   // Dynamic array to store pixel data
    bool filled_;
    bool _changedb; // Flag to indicate if brightness has changed

    void setFilled(bool filled); // Function to set the filled state

    // Function to allocate memory for the pixel array
    void allocatePixelsArray(int size);

    // Function to setup RMT channel for LED control
    bool setupRMT(rmt_channel_t channel);

    // Functions to send data to WS2812 LEDs
    void send_ws2812_bit(bool bitVal);
    void send_ws2812_color(uint8_t red, uint8_t green, uint8_t blue);
    void send_reset();
    void send(); // Function to update the LED strip with current pixel values

public:
    Colors colors; // Colors class instance for predefined colors

    // Constructors
    ii_LedArray();
    ii_LedArray(int pin, int ledcount);

    // Initialize the LED strip
    void begin();

    //***Strip Test Functions***
    void test();               // Test the LED strip with RED, GREEN, BLUE
    void testColors();         // Test the LED strip with all available colors
    void testColors(bool dir); // Create a pattern with all available colors and shift it

    // Brightness control functions
    void setBrightness(int bright); // Set brightness (0-100)
    int getBrightness();            // Get current brightness

    // Functions to set colors with and without transitions
    void setColor(uint8_t index, uint32_t color);                           // Set a specific LED to a 32-bit color
    void setColor(uint8_t index, uint8_t red, uint8_t green, uint8_t blue); // Set a specific LED to an RGB color
    void setColor(uint32_t color);                                          // Set all LEDs to a 32-bit color
    void setColor(uint8_t red, uint8_t green, uint8_t blue);                // Set all LEDs to an RGB color

    // Functions to set colors with transition effects
    void setColorTrans(uint8_t index, uint32_t color, long start, long duration);                           // Set a specific LED to a 32-bit color with transition
    void setColorTrans(uint8_t index, uint8_t red, uint8_t green, uint8_t blue, long start, long duration); // Set a specific LED to an RGB color with transition
    void setColorTrans(uint32_t color, long start, long duration);                                          // Set all LEDs to a 32-bit color with transition
    void setColorTrans(uint8_t red, uint8_t green, uint8_t blue, long start, long duration);                // Set all LEDs to an RGB color with transition

    void clear(); // Clear all colors on the LED strip

    // Function to update the LED strip. This should be called frequently to ensure smooth transitions.
    bool update();

    bool isUpdated() const; // Check if the transition is completed

    int getLength(); // Get the number of LEDs in the strip

    uint32_t getColor(int index); // Get the color of a specific LED

    bool checkRange(int n); // Check if an LED index is within the valid range

    void move(bool direction); // Move colors in a specified direction
};

#endif
