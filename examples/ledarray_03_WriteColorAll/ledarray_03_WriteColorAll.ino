#include <ii_LedArray.h>

Colors colors;                             // Initialize a Colors object for color definitions
ii_LedArray ledarray = ii_LedArray(4, 6);  // Initialize the LED array on pin 6 with 4 LEDs

void setup() {
  ledarray.begin();  // Initialize the LED strip
  ledarray.show();
}

void loop() {
  for (int cindex = 0; cindex < COLORS_COUNT; cindex++) {
      ledarray.setColorAll(colors.get(cindex));
      ledarray.show();
      delay(1000);
  }
}
