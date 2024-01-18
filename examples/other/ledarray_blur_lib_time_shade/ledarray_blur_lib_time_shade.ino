#include <ii_LedArray.h>
#include <ii_Timer.h>

#define LEDUPDATE 0
#define LEDCHANGE 1

ii_Timer timer;

Colors colors;                                       // Initialize a Colors object for color definitions
ii_LedArray ledarray1 = ii_LedArray(4, 6);  // Initialize the LED array on pin 6 with 4 LEDs

void setup() {
  timer.addTimer(LEDUPDATE, 20);
  timer.addTimer(LEDCHANGE, 1500);

  ledarray1.setBlurMode(true);
  ledarray1.begin();  // Initialize the LED strip
}
 
void loop() {

  if (timer.isTime(LEDCHANGE, true)) { 
    int random_color_index = random(COLORS_COUNT);
    for(int i=0;i<ledarray1.getLength();i++){
      ledarray1.setColorTime(i,colors.get(random_color_index), millis()+(i*60),300);
    }
  }

  if (timer.isTime(LEDUPDATE,false)) {
    ledarray1.update();
  }
}
