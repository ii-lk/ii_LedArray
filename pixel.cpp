#include "pixel.h"

// Constructor
Pixel::Pixel() {
    // Initialize member variables in the constructor if needed
    setStart(0);
    setDuration(0);
}

// Getter functions
byte Pixel::getRed() const {
    return r_;
}

byte Pixel::getGreen() const {
    return g_;
}

byte Pixel::getBlue() const {
    return b_;
}

// Getter functions for cached (C) RGB values
byte Pixel::getTRed() const {
    return tr_;
}

byte Pixel::getTGreen() const {
    return tg_;
}

byte Pixel::getTBlue() const {
    return tb_;
}

// Getter functions for cached (C) RGB values
byte Pixel::getLRed() const {
    return lr_;
}

byte Pixel::getLGreen() const {
    return lg_;
}

byte Pixel::getLBlue() const {
    return lb_;
}

uint32_t Pixel::getColor() {
    return ((uint32_t)getRed() << 16) | ((uint32_t)getGreen() << 8) | getBlue();
}
// Get a specific color channel (0 for Red, 1 for Green, 2 for Blue)
uint8_t Pixel::getColor(int n) {
    switch (n) {
        case 0:
            return getRed();
        case 1:
            return getGreen();
        default:
            return getBlue();
    }
}

uint8_t Pixel::getLastColor(int n) {
    switch (n) {
        case 0:
            return getLRed();
        case 1:
            return getLGreen();
        default:
            return getLBlue();
    }
}

uint8_t Pixel::getTargetColor(int n) {
    switch (n) {
        case 0:
            return getTRed();
        case 1:
            return getTGreen();
        default:
            return getTBlue();
    }
}

long Pixel::getStart() const {
    return start_;
}

long Pixel::getDuration() const {
    return duration_;
}

bool Pixel::isFilled() const {
    return filled_;
}

// Setter functions for RGB values
void Pixel::setRed(byte r) {
    r_ = r;
}

void Pixel::setGreen(byte g) {
    g_ = g;
}

void Pixel::setBlue(byte b) {
    b_ = b;
}

void Pixel::setStart(long start) {
    start_ = start;
}

void Pixel::setDuration(long duration) {
    duration_ = duration;
}

void Pixel::setFilled(bool filled) {
    filled_ = filled;
}

void Pixel::setColor(int index,uint8_t v){
    v = filter(v);
    switch (index)
    {
    case 0:
            setRed(v);
        case 1:
            setGreen(v);
        default:
            setBlue(v);
    }
}

// Set the RGB values and cached values along with start and duration
void Pixel::setTargetColor(uint8_t r, uint8_t g, uint8_t b, long start, long duration) {

    tr_ = r;
    tg_ = g;
    tb_ = b;

    lr_ = r_;
    lg_ = g_;
    lb_ = b_;

    setStart(start);
    setDuration(duration);
}

// Set only the RGB values
void Pixel::setColor(uint8_t r, uint8_t g, uint8_t b) {
    r_ = filter(r);
    g_ = filter(g);
    b_ = filter(b);
    setFilled(false);
}

// Get the RGB values as an array
uint8_t* Pixel::getColorArray() const {
    static uint8_t colorArray[3];
    colorArray[0] = r_;
    colorArray[1] = g_;
    colorArray[2] = b_;
    return colorArray;
}

uint8_t Pixel::filter(int color) {
  return (color > 254) ? 254 : (color < 0) ? 0 : color;
}
