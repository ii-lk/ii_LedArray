#include <ii_LedArray.h>  // Include the ii_LedArray library

// Initialize an LED array on pin 6 with 4 LEDs
ii_LedArray ledarray = ii_LedArray(4, 6);

long ltime;        // Variable to store the last time the LED color was updated
bool colorselect;  // Boolean flag to toggle between colors

void setup() {
  ledarray.begin();            // Initialize the LED strip
  ledarray.setBlurMode(true);  // Enable blur mode for smoother color transitions
}

void loop() {
  // Check if 1000 milliseconds (1 second) have passed since the last update
  if (millis() - ltime > 1000) {
    ltime = millis();  // Update the last time variable to the current time

    // Toggle between two colors every second
    if (colorselect) {
      // Set the first LED to red (RGB: 255, 0, 0) and transition over 1000ms
      for(int n=0;n<6;n++){
        ledarray.setColorTime(n,255, 0, 0, millis()+(n*100), 400);
      }
    } else {
      // Set the first LED to blue (RGB: 0, 0, 255) and transition over 1000ms
      for(int n=0;n<6;n++){
        ledarray.setColorTime(n,0, 0, 255, millis()+(n*100), 400);
      }
    }

    colorselect = !colorselect;  // Toggle the colorselect flag
  }

  ledarray.update();  // Update the LED array with the new color data
}
