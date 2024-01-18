#include <ii_LedArray.h>

Colors colors;                             // Initialize a Colors object for color definitions
ii_LedArray ledarray = ii_LedArray(4, 6);  // Initialize the LED array on pin 6 with 4 LEDs

void setup() {
  ledarray.begin();  // Initialize the LED strip
  ledarray.update();
}

void loop() {
  for (int cindex = 0; cindex < COLORS_COUNT; cindex++) {
      ledarray.setColor(colors.get(cindex));
      ledarray.update();
      delay(1000);
  }
}
