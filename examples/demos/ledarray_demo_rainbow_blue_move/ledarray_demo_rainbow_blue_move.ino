#include <ii_LedArray.h>

Colors colors;                                       // Initialize a Colors object for color definitions
ii_LedArray ledarray = ii_LedArray(4, 6);  // Initialize the LED array on pin 6 with 4 LEDs

void setup() {
  Serial.begin(115200);  // Start the serial communication

  ledarray.setBlurMode(true);
  ledarray.begin();  // Initialize the LED strip

  ledarray.setColor(0, 255, 255, 255);    // Red
  ledarray.setColor(1, 255, 255, 255);  // Orange
  ledarray.setColor(2, 0, 0, 255);   // Indigo
  ledarray.setColor(3, 255, 255, 255);    // Green
  ledarray.setColor(4, 255, 255, 255);    // Blue
  ledarray.setColor(5, 0, 0, 255);   // Indigo
}

void loop() { 
    ledarray.move(true);
    ledarray.show(); 
    delay(100);
}
