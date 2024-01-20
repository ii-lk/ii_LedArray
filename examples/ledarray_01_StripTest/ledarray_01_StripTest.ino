#include <ii_LedArray.h> 

// Initialize the LED array with the pin number and the number of LEDs
ii_LedArray strip1 = ii_LedArray(4, 6); 

void setup() {
  // Initialize the LED strip
  strip1.begin();

  // Run a test on all LEDs
  strip1.testColors();

  // Clear the strip after the test
  strip1.clear();
}

void loop() {
  // Your main code goes here
}
