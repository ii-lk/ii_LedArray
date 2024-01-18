#include <ii_LedArray.h>
#include <ii_Timer.h>

#define LEDUPDATE 0
#define LEDCHANGE 1

ii_Timer timer;

Colors colors;                             // Initialize a Colors object for color definitions
ii_LedArray ledarray = ii_LedArray(4, 6);  // Initialize the LED array on pin 6 with 4 LEDs

void setup() {
  timer.addTimer(LEDUPDATE, 20);
  timer.addTimer(LEDCHANGE, 1000);

  ledarray.setBlurMode(true);
  ledarray.begin();  // Initialize the LED strip
}

void loop() {

  if (timer.isTime(LEDCHANGE, true)) {
    int random_color_index = random(COLORS_COUNT);
    ledarray.setColorAllTime(colors.get(random_color_index), millis(), 800);
  }

  if (timer.isTime(LEDUPDATE,false)) {
    ledarray.update();
  }
}
