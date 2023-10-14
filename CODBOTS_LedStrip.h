#ifndef CODBOTS_LEDSTRIP_H
#define CODBOTS_LEDSTRIP_H

#include <Adafruit_NeoPixel.h>
#include <colors.h>
#include <pixel.h>

class CODBOTS_LedStrip
{
private:
    Adafruit_NeoPixel strip;
    Colors colors;
    int brightness;
    void changed();
    int patternstart;
    bool patterndir;
    int selectedpattern;

    bool blurmode;
    Pixel* pixels = nullptr;
    void allocatePixelsArray(int size);

public:
    CODBOTS_LedStrip();
    CODBOTS_LedStrip(int pin,int ledcount);
    void begin();
    void setBlurMode(bool bmode);
    void test();
    void testAll();
    void clear();
    void show();
    bool update();
    void setBrightness(int bright);//0-100
    int getBrightness();
    uint32_t getColor(int index);
    void setColor(uint8_t index, uint8_t red, uint8_t green, uint8_t blue);
    void setColor(uint8_t index, uint32_t color);
    void setColor(uint8_t red, uint8_t green, uint8_t blue);

    void _patternAllColors(bool changedir);
    void move(bool direction);
    int getLEDCount();

    void setColorB(uint8_t index, uint8_t red, uint8_t green, uint8_t blue, long start, long duration);
    void setColorB(uint8_t red, uint8_t green, uint8_t blue, long start, long duration);
    void setColorB(uint8_t index, uint32_t color, long start, long duration);
};
 
#endif