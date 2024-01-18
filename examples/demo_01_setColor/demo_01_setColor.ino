#include <ii_LedArray.h>

ii_LedArray ledarray = ii_LedArray(4, 6);  // Initialize the LED array on pin 6 with 4 LEDs

void setup() {
  ledarray.begin();  // Initialize the LED strip
}

void loop() {
  ledarray.setColor(0, 255, 0, 0);  // Set color of LED at index 0 to red
  ledarray.setColor(1, 0, 0, 255);  // Set color of LED at index 1 to blue
  ledarray.update();                  // Update the strip to apply the color change
  delay(100);

  ledarray.setColor(0, 0, 0, 255);  // Set color of LED at index 1 to blue
  ledarray.setColor(1, 255, 0, 0);  // Set color of LED at index 2 to red
  ledarray.update();                  // Update the strip to apply the color change
  delay(100);
}