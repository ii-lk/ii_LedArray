#ifndef COLORS_H
#define COLORS_H

#include <Arduino.h>

#define COLORS_COUNT 14

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
    uint32_t get(int index);
    String getName(int index);
    int getColorsCount();

    uint32_t RGBToColor(uint8_t red, uint8_t green, uint8_t blue);
    void ColorToRGB(uint32_t color, uint8_t &r, uint8_t &g, uint8_t &b);
    uint32_t HexToColor(uint8_t index, String color);
    String ColorToHex(uint8_t r, uint8_t g, uint8_t b);
};

#endif