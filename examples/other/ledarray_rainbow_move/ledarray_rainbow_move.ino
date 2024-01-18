#include <ii_LedArray.h>

Colors colors;                            // Initialize a Colors object for color definitions
ii_LedArray ledarray = ii_LedArray(4, 6); // Initialize the LED array on pin 6 with 4 LEDs

void setup()
{
  ledarray.begin();                  // Initialize the LED strip
  ledarray.setColor(0, 255, 0, 0);   // Red
  ledarray.setColor(1, 255, 127, 0); // Orange
  ledarray.setColor(2, 255, 255, 0); // Yellow
  ledarray.setColor(3, 0, 255, 0);   // Green
  ledarray.setColor(4, 0, 0, 255);   // Blue
  ledarray.setColor(5, 75, 0, 130);  // Indigo
}

void loop()
{
  ledarray.move(true);
  ledarray.update();
  delay(100);
}
