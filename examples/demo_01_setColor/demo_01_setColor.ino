#include <ii_LedArray.h>

ii_LedArray ledarray = ii_LedArray(4, 6);  // Initialize the LED array on pin 6 with 4 LEDs

void setup() {
  ledarray.begin();      // Initialize the LED strip
}

void loop() {
   ledarray.show();                  // Update the strip to apply the color change
    delay(100); 
}