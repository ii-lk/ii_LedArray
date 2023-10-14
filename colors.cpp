// colors.cpp
#include "colors.h"



const byte Colors::color_list[COLORS_COUNT][3] = {
  {0, 0, 0},       // Black
  {255, 0, 0},     // Red
  {0, 255, 0},     // Green
  {0, 0, 255},     // Blue
  {255, 255, 0},   // Yellow
  {255, 0, 255},   // Magenta
  {0, 255, 255},   // Cyan
  {255, 255, 255}, // White
  {255, 50, 0},   // Orange
  {0, 255, 127},   // Aqua
  {127, 0, 255},   // Purple
  {255, 0, 255}, // Pink
  {100, 255, 0},     // Lime
  {0, 128, 128},   // Teal
};

const String Colors::color_names[COLORS_COUNT] = {
    "BLACK",
    "RED",
    "GREEN",
    "BLUE",
    "YELLOW",
    "MAGENTA",
    "CYAN",
    "WHITE",
    "ORANGE",
    "AQUA",
    "PURPLE",
    "PINK",
    "LIME",
    "TEAL",
};


uint32_t Colors::get(int index) {
  if (index >= 0 && index < getColorsCount() / sizeof(color_list[0])) {
    // Assuming you have a NeoPixel strip object named "strip"
    return RGBToColor(color_list[index][0], color_list[index][1], color_list[index][2]);
  } else {
    // Return black for invalid index or out-of-range index
    return RGBToColor(0, 0, 0);
  }
}

String Colors::getName(int index) {
  return color_names[index];
}

int Colors::getColorsCount(){
    return sizeof(color_list);
}

uint32_t Colors::RGBToColor(uint8_t red, uint8_t green, uint8_t blue) {
    return ((uint32_t)red << 16) | ((uint32_t)green << 8) | blue;
}

void Colors::ColorToRGB(uint32_t color, uint8_t &r, uint8_t &g, uint8_t &b) {
    r = (color >> 16) & 0xFF;
    g = (color >> 8) & 0xFF;
    b = color & 0xFF;
}

uint32_t Colors::HexToColor(uint8_t index, String hexcolor){
    return  (uint32_t)strtol(hexcolor.c_str(), NULL, 16);
}
 
 String Colors::ColorToHex(uint8_t r, uint8_t g, uint8_t b) {
    char hexColor[7];
    snprintf(hexColor, sizeof(hexColor), "#%02X%02X%02X", r, g, b);
    return String(hexColor);
}