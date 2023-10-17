#include "esp_timer.h"
#include <CODBOTS_LedStrip.h>

 
CODBOTS_LedStrip strip1 = CODBOTS_LedStrip(4, 10); 

esp_timer_handle_t timer1;

void setup() {
  Serial.begin(115200); 
  strip1.begin();
  //loops.begin();
  //loops.createLoop(loop1,100);

    esp_timer_create_args_t timer1_args = {
    .callback = &loop1,
    .name = "timer1"
  };
  esp_timer_create(&timer1_args, &timer1);
  esp_timer_start_periodic(timer1, 50 * 1000);

}

void loop1(void* arg) {
  strip1.show();
}

void loop() {
  strip1.setColor(0, 255, 50, 0);
  strip1.setColor(1, 200, 100, 0);
  strip1.setColor(2, 150, 150, 0);
  strip1.setColor(3, 100, 200, 0);
  strip1.setColor(4, 50, 255, 0);
  strip1.setColor(5, 0, 255, 0);
  for (int n = 0; n < strip1.getLEDCount() * 10; n++) {
    strip1.move(false);
    delay(100);
  }

  strip1.setColor(0, 255, 0, 0);
  strip1.setColor(1, 0, 0, 255);
  strip1.setColor(2, 0, 0, 255);
  strip1.setColor(3, 255, 0, 0);
  strip1.setColor(4, 0, 0, 255);
  strip1.setColor(5, 0, 0, 255);
  for (int n = 0; n < strip1.getLEDCount() * 10; n++) {
    strip1.move(true);
    delay(100);
  }

  strip1.setColor(0, 255, 255, 255);
  strip1.setColor(1, 150, 150, 150);
  strip1.setColor(2, 200, 100, 100);
  strip1.setColor(3, 255, 0, 0);
  strip1.setColor(4, 255, 255, 255);
  strip1.setColor(5, 255, 255, 255);
  for (int n = 0; n < strip1.getLEDCount() * 10; n++) {
    strip1.move(false);
    delay(100);
  }
}
