#include <ii_LedArray.h>

ii_LedArray ledarray = ii_LedArray(4, 6);  // Initialize the LED array on pin 6 with 4 LEDs

void setup() {
  ledarray.begin();      // Initialize the LED strip
}

void loop() {
  // Set the color of each LED to red, one by one
  for (int n = 0; n < ledarray.getLength(); n++) {
    ledarray.setColor(n, 255, 0, 0);  // Set color of LED at index n to red (RGB: 255, 0, 0)
    ledarray.update();                  // Update the strip to apply the color change
    delay(100);                       // Small delay between updates
  }
  delay(1000);  // Delay after completing the loop
}
