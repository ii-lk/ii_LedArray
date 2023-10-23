#include "esp_timer.h"
#include <CODBOTS_LedStrip.h>

 
CODBOTS_LedStrip strip1 = CODBOTS_LedStrip(2, 6); 

esp_timer_handle_t timer1;

void setup() {
  Serial.begin(115200); 
  strip1.begin();
  strip1.setBlurMode(true);
  strip1.setColor(0, 255, 50, 0);
  strip1.setColor(1, 200, 100, 0);
  strip1.setColor(2, 150, 150, 0);
  strip1.setColor(3, 100, 200, 0);
  strip1.setColor(4, 50, 255, 0);
  strip1.setColor(5, 0, 255, 0);
  

}


void loop() {
  strip1.move(true);
  strip1.show();
  delay(100);
}
