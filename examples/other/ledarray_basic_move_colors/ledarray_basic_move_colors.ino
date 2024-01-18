#include <ii_LedArray.h>


Colors colors;                                       // Initialize a Colors object for color definitions
ii_LedArray ledarray = ii_LedArray(5, 6);  // Initialize the LED array on pin 6 with 4 LEDs

void setup() {
  Serial.begin(115200);  // Start the serial communication
  ledarray.setBlurMode(true);
  ledarray.begin();      // Initialize the LED strip

/*
  ledarray.setColor(0, 255, 0, 0);
  ledarray.setColor(1, 255, 40, 40);
  ledarray.setColor(2, 255, 80, 80);
  ledarray.setColor(3, 255, 110, 110);
  ledarray.setColor(4, 255, 150, 150);
  ledarray.setColor(5, 255, 255, 255);
*/

  ledarray.setColor(0, colors.get(1));
  ledarray.setColor(1, colors.get(2));
  ledarray.setColor(2, colors.get(3));
  ledarray.setColor(3, colors.get(4));
  ledarray.setColor(4, colors.get(5));
  ledarray.setColor(5, colors.get(6));
  ledarray.setColor(6, colors.get(7));
  ledarray.setColor(7, colors.get(8));
  ledarray.setColor(8, colors.get(9));
  ledarray.setColor(9, colors.get(10));
  
/*
  ledarray.setColor(0, colors.get(c_red));
  ledarray.setColor(1, colors.get(c_white));
  ledarray.setColor(2, colors.get(c_blue));
  ledarray.setColor(3, colors.get(c_red));
  ledarray.setColor(4, colors.get(c_white));
  ledarray.setColor(5, colors.get(c_blue));
  */
}

void loop() {
  ledarray.move(false);
  ledarray.show();
  delay(100);
}
