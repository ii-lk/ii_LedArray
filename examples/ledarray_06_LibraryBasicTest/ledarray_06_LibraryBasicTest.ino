/*
This Arduino sketch controls an LED strip using the ii_LedArray library. 
It demonstrates setting individual LED colors, applying a uniform color across 
the strip, and dynamically adjusting the brightness. The code cycles through 
different colors for each LED, sets all LEDs to specific colors, and gradually 
modifies the brightness from low to high, showcasing various ways to manipulate 
LED strip lighting. 
*/
#include <ii_LedArray.h>

Colors colors;                             // Initialize a Colors object for color definitions
ii_LedArray ledarray = ii_LedArray(4, 6);  // Initialize the LED array on pin 6 with 4 LEDs

void setup() {
  Serial.begin(115200);  // Start the serial communication
  ledarray.begin();      // Initialize the LED strip
}

void loop() {
  // Set the color of each LED to white, one by one
  for (int n = 0; n < ledarray.getLength(); n++) {
    ledarray.setColor(n, 255, 255, 255);  // Set color of LED at index n to white (RGB: 255, 255, 255)
    ledarray.show();                      // Update the strip to apply the color change
    delay(100);                           // Small delay between updates
  }
  delay(1000);  // Delay after completing the loop

  // Set the color of each LED to blue, one by one, using predefined colors
  for (int n = 0; n < ledarray.getLength(); n++) {
    ledarray.setColor(n, colors.get(c_blue));  // Set color of LED at index n to blue
    ledarray.show();                           // Update the strip to apply the color change
    delay(100);                                // Small delay between updates
  }
  delay(1000);  // Delay after completing the loop

  // Set all LEDs to green
  ledarray.setColorAll(colors.get(c_green));  // Set all LEDs to green
  ledarray.show();                            // Update the strip to apply the color change
  delay(1000);                                // Delay after setting all LEDs to green

  // Set all LEDs to red using RGB components extracted from a predefined color
  ledarray.setColorAll(colors.get(c_red, 0), colors.get(c_red, 1), colors.get(c_red, 2));  // Set all LEDs to red
  ledarray.show();                                                                         // Update the strip to apply the color change
  delay(1000);                                                                             // Delay after setting all LEDs to red

  // Gradually decrease brightness from current level to 5
  for (int b = ledarray.getBrightness(); b > 5; b--) {
    ledarray.setBrightness(b);  // Set the brightness to the current value of 'b'
    ledarray.show();            // Update the strip to apply the brightness change
    delay(10);                  // Small delay for a smooth transition
  }

  // Gradually increase brightness from 5 to 100
  for (int b = 5; b < 100; b++) {
    ledarray.setBrightness(b);  // Increase the brightness
    ledarray.show();            // Update the strip to apply the brightness change
    delay(10);                  // Small delay for smooth transition
  }
}
