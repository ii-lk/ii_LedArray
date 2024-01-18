#include "ii_UltraSonic.h"
#include <ii_LedArray.h>
#include <ii_Timer.h>

#define LEDUPDATE 0
#define USONICREAD 1

ii_Timer timer;

Colors colors;                                       // Initialize a Colors object for color definitions
ii_LedArray ledarray = ii_LedArray(4, 6);  // Initialize the LED array on pin 6 with 4 LEDs

//ultrasonic
#define ULTRA_TRIG 23
#define ULTRA_ECHO 22

ii_UltraSonic usensor(ULTRA_TRIG, ULTRA_ECHO);

void setup() {
  Serial.begin(115200);  // Start the serial communication

  timer.addTimer(LEDUPDATE, 20);
  timer.addTimer(USONICREAD, 100);

  ledarray.setBlurMode(true);
  ledarray.begin();  // Initialize the LED strip

   usensor.begin(3);

}

void loop() {
  if (timer.isTime(USONICREAD, true)) {
    float distance = usensor.readSensor();

    int mapleds = map((int)distance, 0, 40, 0, 6);
    if (mapleds < 0) {
      mapleds = 0;
    }
    if (mapleds > 6) {
      mapleds = 6;
    }

    Serial.print(distance);
    Serial.print('\t');
    Serial.println(mapleds);

    for (int n = 0; n < mapleds; n++) {
      ledarray.setColorTrans(n, colors.get(c_green), millis(), 100);
    }
    for (int n = mapleds; n < 6; n++) {
      ledarray.setColorTrans(n, 150, 0, 0, millis(), 200);
    }
  }
  if (timer.isTime(LEDUPDATE, true)) {
    ledarray.update();
  }
}
