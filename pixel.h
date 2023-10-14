#ifndef PIXEL_H
#define PIXEL_H

#include <Arduino.h>  // Include necessary header for Arduino platform

class Pixel {
public:
     Pixel();
    
    // Getter functions
    byte getRed() const;
    byte getGreen() const;
    byte getBlue() const;

    byte getCRed() const;
    byte getCGreen() const;
    byte getCBlue() const;

    long getStart() const;
    long getDuration() const;
    uint8_t getColor(int n);
    uint8_t getCColor(int n);
    uint8_t* getColorArray() const;
    bool isFilled() const;

    // Setter functions
    void setColor(uint8_t r, uint8_t g, uint8_t b);
    void setColor(uint8_t r, uint8_t g, uint8_t b,long start,long duration);
    void setRed(byte r);
    void setGreen(byte g);
    void setBlue(byte b);
    void setStart(long start);
    void setDuration(long duration);
    void setFilled(bool filled);

private:
    byte r_;
    byte g_;
    byte b_;

    byte cr_;
    byte cg_;
    byte cb_;

    long start_;
    long duration_;
    bool filled_;
};

#endif
