#include <Arduino.h>
#include <CODBOTS_LedStrip.h> 
bool _changedb;
CODBOTS_LedStrip::CODBOTS_LedStrip(){

}
CODBOTS_LedStrip::CODBOTS_LedStrip(int pin,int ledcount){
    strip=Adafruit_NeoPixel(ledcount, pin, NEO_GRB + NEO_KHZ800);
    strip.begin();
    strip.clear();
}
void CODBOTS_LedStrip::test(){
    for (int c = 3; c > -1;c--){
        for (int n = 0; n < strip.numPixels(); n++){
         setColor(n, colors.get(c));
         show();
         delay(100);
    }
     delay(1000);
    }
}
void CODBOTS_LedStrip::testAll(){
    for (int c = COLORS_COUNT-1; c > -1;c--){
        Serial.println(colors.getName(c));
        for (int n = 0; n < strip.numPixels(); n++){
         setColor(n, colors.get(c));
         show();
         delay(100);
    }
    
    delay(3000);
    }
}

void CODBOTS_LedStrip::clear(){
    strip.clear();
}

void CODBOTS_LedStrip::show(){
    if(_changedb){
        strip.show();
        _changedb = false;
    }
}

void CODBOTS_LedStrip::changed(){
    _changedb = true;
}

void CODBOTS_LedStrip::setBrightness(int bright){
    strip.setBrightness(map(bright, 0, 100, 0, 255));
    changed();
}

int CODBOTS_LedStrip::getLEDCount(){
    return strip.numPixels();
}

int CODBOTS_LedStrip::getBrightness(){
    return brightness;
}
void CODBOTS_LedStrip::setColorHex(uint8_t index, String hexcolor){
    // Parse the color value as a hexadecimal number with 24 bits (e.g., 0xFF00FF)
    uint32_t color = (uint32_t)strtol(hexcolor.c_str(), NULL, 16);
    strip.setPixelColor(index, color);
    changed();
}
void CODBOTS_LedStrip::setColor(uint8_t index, uint8_t red, uint8_t green, uint8_t blue){
    strip.setPixelColor(index, red,green,blue);
    changed();
}
void CODBOTS_LedStrip::setColor(uint8_t index, uint32_t color){
    strip.setPixelColor(index, color);
    changed();
}
void CODBOTS_LedStrip::setColor(uint8_t red, uint8_t green, uint8_t blue){
     for (int n = 0; n < strip.numPixels(); n++){
        strip.setPixelColor(n, red,green,blue);
     }
     changed();
}
uint32_t CODBOTS_LedStrip::getColor(int index){
     return strip.getPixelColor(index);
}


void CODBOTS_LedStrip::_patternAllColors(bool changedir){
    if(!patterndir){
    patternstart++;
        if(patternstart==strip.numPixels()){
            if(changedir){
                patterndir = true;
            }else{
                patternstart = 0;
            }
        }
    }else{
        patternstart--;
        if(patternstart==0){
            if(changedir){
                patterndir = false;
            }else{
                patternstart = strip.numPixels()-1;
            }
        }
    }

    int cn = 0;
    for (int n = patternstart; n < strip.numPixels() && cn<COLORS_COUNT; n++){
        setColor(n, colors.get(cn));
        cn++;
    }

    for (int n = 0; n < patternstart && cn<COLORS_COUNT; n++){
        setColor(n, colors.get(cn));
        cn++;
    }
}

void CODBOTS_LedStrip::move(bool direction){
    if(direction){
        uint32_t lastcolor=getColor(0);
        for (int i = 0; i < strip.numPixels()-1; i++)
        {
            uint32_t color= getColor(i+1);
            setColor(i + 1, lastcolor);
            lastcolor = color;
        }
        setColor(0, lastcolor);
    }else{
        uint32_t lastcolor=getColor(strip.numPixels()-1);
        for (int i = strip.numPixels()-1; i >0; i--)
        {
            uint32_t color= getColor(i-1);
            setColor(i - 1, lastcolor);
            lastcolor = color;
        }
        setColor(strip.numPixels()-1, lastcolor);
    }
}