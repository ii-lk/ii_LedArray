#include <ii_LedArray.h>
#include <ii_Timer.h>

#define LEDUPDATE 0
#define REFRESH 1

ii_Timer timer;

Colors colors;                                         // Initialize a Colors object for color definitions
ii_LedArray ledarray = ii_LedArray(4, 6);    // Initialize the LED array on pin 6 with 4 LEDs
ii_LedArray ledarray2 = ii_LedArray(5, 10);  // Initialize the LED array on pin 6 with 4 LEDs
ii_LedArray ledarray3 = ii_LedArray(18, 4);  // Initialize the LED array on pin 6 with 4 LEDs

void setup() {
  Serial.begin(115200);  // Start the serial communication

  timer.addTimer(LEDUPDATE, 20);
  timer.addTimer(REFRESH, 1000);

  ledarray.setBlurMode(true);
  ledarray.begin();  // Initialize the LED strip

  ledarray2.setBlurMode(true);
  ledarray2.begin();  // Initialize the LED strip

  ledarray3.setBlurMode(true);
  ledarray3.begin();  // Initialize the LED strip

  //ledarray.setColorAllTime(colors.get(c_orange),millis(),1000);  // Green
}
bool active = true;
void loop() {
  if (timer.isTime(REFRESH, true)) {
    if (active) {
      ledarray.setColorAllTime(colors.get(random(14) + 1), millis(), 1000);
    } else {
      ledarray.setColorAllTime(colors.get(c_black), millis(), 1000);
    }
    active = !active;
  }

  if (timer.isTime(LEDUPDATE, true)) {
    ledarray.update();
  }
}
