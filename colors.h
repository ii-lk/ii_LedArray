// COLORS.H file
// This file defines a Colors class that provides methods for working with colors.

#ifndef COLORS_H
#define COLORS_H

#include <Arduino.h>

#define COLORS_COUNT 14

// Color index constants
#define c_black 0
#define c_red 1
#define c_green 2
#define c_blue 3
#define c_yellow 4
#define c_magenta 5
#define c_cyan 6
#define c_white 7
#define c_orange 8
#define c_aqua 9
#define c_purple 10
#define c_pink 11
#define c_lime 12
#define c_teal 13
#define c_lavender 14
#define c_brown 15
#define c_grey 16

class Colors {
  private:
    static const byte color_list[COLORS_COUNT][3];
    static const String color_names[COLORS_COUNT];

  public:
    // Get the RGB value of a color at the given index
    uint32_t get(int index);

    uint8_t get(int index,int color);

    // Get the name of a color at the given index
    String getName(int index);

    // Get the total number of colors
    int getColorsCount();

    // Convert RGB values to a 32-bit color value
    uint32_t RGBToColor(uint8_t red, uint8_t green, uint8_t blue);

    // Convert a 32-bit color value to RGB values
    void ColorToRGB(uint32_t color, uint8_t &r, uint8_t &g, uint8_t &b);

    // Convert a hex color string to a 32-bit color value
    uint32_t HexToColor(uint8_t index, String hexcolor);

    // Convert RGB values to a hex color string
    String ColorToHex(uint8_t r, uint8_t g, uint8_t b);

    uint8_t filter(int color);
};

#endif
