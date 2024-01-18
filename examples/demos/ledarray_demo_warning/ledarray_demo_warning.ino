#include <ii_LedArray.h>

Colors colors;                                       // Initialize a Colors object for color definitions
ii_LedArray ledarray = ii_LedArray(4, 6);  // Initialize the LED array on pin 6 with 4 LEDs

void setup() {
  Serial.begin(115200);  // Start the serial communication
  ledarray.begin();      // Initialize the LED strip
}

void loop() {
  for (int n = 0; n < 3; n++) {
    ledarray.setColor(colors.get(c_red));
    ledarray.update();
    delay(40);
    ledarray.setColor(colors.get(c_black));
    ledarray.update();
    delay(100);
  }
  delay(700);
}
