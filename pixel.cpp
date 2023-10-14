#include "pixel.h"

// Constructor
Pixel::Pixel(){

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

// Getter functions
byte Pixel::getCRed() const {
    return cr_;
}

byte Pixel::getCGreen() const {
    return cg_;
}

byte Pixel::getCBlue() const {
    return cb_;
}

uint8_t Pixel::getColor(int n){
    switch (n) {
        case 0:
            return getRed();
        case 1:
            return getGreen();
        default:
            return getBlue();
    }
}

uint8_t Pixel::getCColor(int n){
    switch (n) {
        case 0:
            return getCRed();
        case 1:
            return getCGreen();
        default:
            return getCBlue();
    }
}

long Pixel::getStart() const {
    return start_;
}

long Pixel::getDuration() const {
    return duration_;
}

bool Pixel::isFilled() const{
    return filled_;
}

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

void Pixel::setFilled(bool filled){
    filled_ = filled;
}

void Pixel::setColor(uint8_t r, uint8_t g, uint8_t b,long start,long duration) {
  
    cr_ = getRed();
    cg_ = getGreen();
    cb_ = getBlue();
    setColor(r,g,b);
    setStart(start);
    setDuration(duration);
}

void Pixel::setColor(uint8_t r, uint8_t g, uint8_t b) {
    r_ = r;
    g_ = g;
    b_ = b;
    setFilled(false);
}

uint8_t* Pixel::getColorArray() const {
    static uint8_t colorArray[3];
    colorArray[0] = r_;
    colorArray[1] = g_;
    colorArray[2] = b_;
    return colorArray;
}