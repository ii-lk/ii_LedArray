#include <ii_LedArray.h>
#include <ii_Timer.h>

#define LEDUPDATE 0
#define REFRESH 1

ii_Timer timer;
Colors colors;                                       // Initialize a Colors object for color definitions
ii_LedArray ledarray = ii_LedArray(4, 6);  // Initialize the LED array on pin 6 with 4 LEDs

void setup() {
  Serial.begin(115200);  // Start the serial communication

  timer.addTimer(LEDUPDATE, 20);
  timer.addTimer(REFRESH, 1000);

  ledarray.setBlurMode(true);
  ledarray.begin();  // Initialize the LED strip
 
  //ledarray.setColorTrans(colors.get(c_orange),millis(),1000);  // Green
}
bool active=true;
void loop() {
  if (timer.isTime(REFRESH, true)) {
     if(active){
        for(int n=0;n<6;n++){
          ledarray.setColorTrans(5-n,colors.get(c_white),millis()+(n*50),100);
        }
     }else{
      for(int n=0;n<random(2)+4;n++){
          ledarray.setColorTrans(n,colors.get(c_blue),millis()+(n*100),40);
        }
     }
     active=!active;
  }

  if (timer.isTime(LEDUPDATE, true)) {
    ledarray.update();
  }
}
