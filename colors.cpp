#include "colors.h"

// Define the RGB values for various colors
<<<<<<< HEAD
const uint8_t Colors::color_list[COLORS_COUNT][3] = {
=======
const byte Colors::color_list[COLORS_COUNT][3] = {
>>>>>>> a2e43d3e81d2ba5f62772b74aec1a75c25aef2dc
  {0, 0, 0},       // Black
  {255, 0, 0},     // Red
  {0, 255, 0},     // Green
  {0, 0, 255},     // Blue
  {255, 255, 0},   // Yellow
  {255, 0, 255},   // Magenta
  {0, 255, 255},   // Cyan
  {255, 255, 255}, // White
  {255, 50, 0},    // Orange
  {0, 255, 127},   // Aqua
  {127, 0, 255},   // Purple
  {255, 0, 255},   // Pink
  {100, 255, 0},   // Lime
  {0, 128, 128},   // Teal
};

// Define the names of the colors
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

// Get the RGB value of a color at the given index
uint32_t Colors::get(int index) {
  if (index >= 0 && index < getColorsCount()) {
    return RGBToColor(color_list[index][0], color_list[index][1], color_list[index][2]);
  } else {
    // Return black for invalid index or out-of-range index
    return RGBToColor(0, 0, 0);
  }
}

<<<<<<< HEAD
uint8_t Colors::get(int index,int color){
  return color_list[index][color];
}

=======
>>>>>>> a2e43d3e81d2ba5f62772b74aec1a75c25aef2dc
// Get the name of a color at the given index
String Colors::getName(int index) {
  return color_names[index];
}

// Get the total number of colors
int Colors::getColorsCount(){
    return sizeof(color_list) / sizeof(color_list[0]);
}

// Convert RGB values to a 32-bit color value
uint32_t Colors::RGBToColor(uint8_t red, uint8_t green, uint8_t blue) {
    return ((uint32_t)red << 16) | ((uint32_t)green << 8) | blue;
}

// Convert a 32-bit color value to RGB values
void Colors::ColorToRGB(uint32_t color, uint8_t &r, uint8_t &g, uint8_t &b) {
    r = (color >> 16) & 0xFF;
    g = (color >> 8) & 0xFF;
    b = color & 0xFF;
}

// Convert a hex color string to a 32-bit color value
uint32_t Colors::HexToColor(uint8_t index, String hexcolor){
    return  (uint32_t)strtol(hexcolor.c_str(), NULL, 16);
}

// Convert RGB values to a hex color string
String Colors::ColorToHex(uint8_t r, uint8_t g, uint8_t b) {
    char hexColor[7];
    snprintf(hexColor, sizeof(hexColor), "#%02X%02X%02X", r, g, b);
    return String(hexColor);
}
<<<<<<< HEAD

uint8_t Colors::filter(int color) {
  return (color > 255) ? 255 : (color < 0) ? 0 : color;
}
=======
>>>>>>> a2e43d3e81d2ba5f62772b74aec1a75c25aef2dc
