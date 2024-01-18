#include <ii_LedArray.h>
#include <ii_Timer.h>

#define LEDUPDATE 0
#define LEDMOVE 1
#define LEDHEAD 2
#define LEDTAIL 3

ii_Timer timer;

Colors colors;                                         // Initialize a Colors object for color definitions
ii_LedArray ledarray1 = ii_LedArray(4, 6);   // Initialize the LED array on pin 6 with 4 LEDs
ii_LedArray ledarray2 = ii_LedArray(5, 10);  // Initialize the LED array on pin 6 with 4 LEDs
ii_LedArray ledarray3 = ii_LedArray(18, 4);  // Initialize the LED array on pin 6 with 4 LEDs


void setup() {
  Serial.begin(115200);  // Start the serial communication

  timer.addTimer(LEDUPDATE, 20);
  timer.addTimer(LEDMOVE, 100);
  timer.addTimer(LEDHEAD, 600);
  timer.addTimer(LEDTAIL, 500);

  ledarray1.setBlurMode(true);
  ledarray1.begin();  // Initialize the LED strip

  ledarray2.setBlurMode(true);
  ledarray2.begin();  // Initialize the LED strip

  ledarray3.setBlurMode(true);
  ledarray3.begin();  // Initialize the LED strip

  ledarray2.setColor(0, colors.get(1));
  ledarray2.setColor(1, colors.get(2));
  ledarray2.setColor(2, colors.get(3));
  ledarray2.setColor(3, colors.get(4));
  ledarray2.setColor(4, colors.get(5));
  ledarray2.setColor(5, colors.get(6));
  ledarray2.setColor(6, colors.get(7));
  ledarray2.setColor(7, colors.get(8));
  ledarray2.setColor(8, colors.get(9));
  ledarray2.setColor(9, colors.get(10));
}
bool head = false;
 int tailn=0;
void loop() {
  if (timer.isTime(LEDMOVE, false)) {
    ledarray2.move(true);
    ledarray2.show();
  }

  if (timer.isTime(LEDHEAD, false)) {
    if (head) {
      ledarray3.setColorTime(0, colors.get(c_red), millis(), 500);
      ledarray3.setColorTime(1, colors.get(c_red), millis(), 500);
      ledarray3.setColorTime(2, colors.get(c_white), millis(), 500);
      ledarray3.setColorTime(3, colors.get(c_white), millis(), 500);
    } else {
      ledarray3.setColorTime(0, colors.get(c_white), millis(), 500);
      ledarray3.setColorTime(1, colors.get(c_white), millis(), 500);
      ledarray3.setColorTime(2, colors.get(c_red), millis(), 500);
      ledarray3.setColorTime(3, colors.get(c_red), millis(), 500);
    }
    head = !head;
  }

  if (timer.isTime(LEDTAIL, false)) {
    if(tailn<5){
      tailn+=random(3);
    }else{
      tailn = random(6);
    }
    
    ledarray1.setColorAllTime(colors.get(c_white), millis(),100);
    for (int i = 0; i < tailn ; i++) {
      ledarray1.setColorTime(i, colors.get(c_blue), millis()+(i*50), 150);
    }
  }

  if (timer.isTime(LEDUPDATE, true)) {
    ledarray1.update();
    ledarray3.update();
  }
}
