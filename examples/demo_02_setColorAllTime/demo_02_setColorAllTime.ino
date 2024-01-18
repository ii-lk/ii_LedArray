#include <ii_LedArray.h>  // Include the ii_LedArray library

// Initialize an LED array on pin 6 with 4 LEDs
ii_LedArray ledarray = ii_LedArray(4, 6);

long ltime;        // Variable to store the last time the LED colors were updated
bool colorselect;  // Boolean flag to toggle between red and blue colors

void setup() {
  ledarray.begin();            // Initialize the LED strip
  ledarray.setBlurMode(true);  // Enable blur mode for smoother color transitions
}

void loop() {
  // Check if 1000 milliseconds (1 second) have passed since the last update
  if (millis() - ltime > 1000) {
    ltime = millis();  // Update the last time variable to the current time

    // Toggle the entire LED array between red and blue every second
    if (colorselect) {
        ledarray.setColorTrans(255, 0, 0, millis(), 1000); // Set all LEDs to red
    } else {
        ledarray.setColorTrans(0, 0, 255, millis(), 1000); // Set all LEDs to blue
    }

    colorselect = !colorselect;  // Toggle the colorselect flag
  }

  ledarray.update();  // Update the LED array with the new color data
}