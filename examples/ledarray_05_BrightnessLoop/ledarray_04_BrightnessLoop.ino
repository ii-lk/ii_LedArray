#include <ii_LedArray.h>

ii_LedArray ledarray = ii_LedArray(4, 6);  // Initialize the LED array on pin 6 with 4 LEDs

void setup() {
  ledarray.begin();  // Initialize the LED strip
  ledarray.update();
}

void loop() {
  for (int b = 0; b < 100; b++) {
    ledarray.setBrightness(b);
    ledarray.setColor(255, 255, 255);
    ledarray.update();
    delay(20);
  }
  for (int b = 100; b > 0; b--) {
    ledarray.setBrightness(b);
    ledarray.setColor(255, 255, 255);
    ledarray.update();
    delay(20);
  }
}
