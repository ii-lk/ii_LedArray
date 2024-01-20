#include <ii_LedArray.h>

Colors colors;
// Initialize a Colors object for color definitions
ii_LedArray ledarray = ii_LedArray(4, 6);  // Initialize the LED array on pin 6 with 4 LEDs

void setup() {
  ledarray.begin();  // Initialize the LED strip
  ledarray.setColor(colors.get(c_white));
}

void loop() {
  for (int b = 0; b < 100; b++) {
    ledarray.setBrightness(b);
    ledarray.update();
    delay(20);
  }

  for (int b = 100; b > 0; b--) {
    ledarray.setBrightness(b);
    ledarray.update();
    delay(20);
  }
}
