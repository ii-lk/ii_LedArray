#include <ii_LedArray.h>
#include <ii_Timer.h>

ii_Timer timer;

#define LEDUPDATE 0
#define COLORCHANGE 1

Colors colors;                                       // Initialize a Colors object for color definitions
ii_LedArray ledarray1 = ii_LedArray(4, 6);   // Initialize the LED array on pin 6 with 4 LEDs
ii_LedArray ledarray2 = ii_LedArray(5, 10);  // Initialize the LED array on pin 6 with 4 LEDs
ii_LedArray ledarray3 = ii_LedArray(18, 4);  // Initialize the LED array on pin 6 with 4 LEDs

void setup() {
   Serial.begin(115200);  // Start the serial communication

  timer.addTimer(LEDUPDATE, 20);
  timer.addTimer(COLORCHANGE, 1000);

  ledarray1.setBlurMode(true);
  ledarray1.begin();  // Initialize the LED strip
   ledarray2.setBlurMode(true);
  ledarray2.begin();  // Initialize the LED strip
   ledarray3.setBlurMode(true);
  ledarray3.begin();  // Initialize the LED strip
 
}

int color_index=0;
void loop() {
  if (timer.isTime(COLORCHANGE, true)) {
    ledarray1.setColorTrans(colors.get(colors.rainbow[color_index]),millis(),500);
    ledarray2.setColorTrans(colors.get(colors.rainbow[color_index]),millis(),500);
    ledarray3.setColorTrans(colors.get(colors.rainbow[color_index]),millis(),500);
    color_index++;
    if(color_index==6){
      color_index=0; 
    }
  }
  if (timer.isTime(LEDUPDATE, true)) {
    ledarray1.update();
    ledarray2.update();
    ledarray3.update();
  }
}
