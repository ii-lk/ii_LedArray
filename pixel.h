#ifndef PIXEL_H
#define PIXEL_H

#include <Arduino.h>

class Pixel {
public:
    // Constructor
    Pixel();

    // Getter functions for the RGB values
    byte getRed() const;
    byte getGreen() const;
    byte getBlue() const;

    // Getter functions for the cached (C) RGB values
    byte getCRed() const;
    byte getCGreen() const;
    byte getCBlue() const;

    // Get a specific color channel (0 for Red, 1 for Green, 2 for Blue)
    uint8_t getColor(int n);
    uint8_t getCColor(int n);

    long getStart() const;
    long getDuration() const;
    bool isFilled() const;

    // Setter functions for RGB values
    void setColor(uint8_t r, uint8_t g, uint8_t b);
    void setColor(uint8_t r, uint8_t g, uint8_t b, long start, long duration);
    void setRed(byte r);
    void setGreen(byte g);
    void setBlue(byte b);
    void setStart(long start);
    void setDuration(long duration);
    void setFilled(bool filled);

    // Get the RGB values as an array
    uint8_t* getColorArray() const;

private:
    byte r_;
    byte g_;
    byte b_;

    byte cr_; // Cached Red
    byte cg_; // Cached Green
    byte cb_; // Cached Blue

    long start_;
    long duration_;
    bool filled_;
};

#endif
