#include <CODBOTS_LedStrip.h>
#include <CODBOTS_Timer.h>

#define LEDSTRIP_PIN 4

#define TIMER_LED_UPDATE 0
#define TIMER_HEADCHANGE 1
#define TIMER_TAILCHANGE 2
#define TIMER_TAILMOVE 3
#define TIMER_ULTRASONIC 4




Colors colors;
CODBOTS_LedStrip tail = CODBOTS_LedStrip(2, 6);
CODBOTS_LedStrip ring = CODBOTS_LedStrip(4, 10);
CODBOTS_LedStrip head = CODBOTS_LedStrip(5, 4);

CODBOTS_Timer timer;

void setup() {
  Serial.begin(115200);

  tail.begin();
  tail.setBlurMode(true);
  ring.begin();
  ring.setBlurMode(true);
  head.begin();
  head.setBlurMode(true);


  timer.addTimer(20);    //0-TIMER_LED_UPDATE-50ms
  timer.addTimer(500);  //1 - TIMER_HEADCHANGE
  timer.addTimer(3000);  //2 - TIMER_TAILCHANGE
  timer.addTimer(100);   //3 - TIMER_TAILMOVE
  timer.addTimer(100);   //4 - TIMER_ULTRASONIC

  ring.setBrightness(100);
  tail.setBrightness(100);
  head.setBrightness(100);

  initUltrasonic();

   
 
}

int pattern_color = 0;
int headside = 0;
int cc = 0;

int colorset = 0;

void loop() {

  if (timer.isTime(TIMER_HEADCHANGE, true)) {

    //uint32_t color = colors.get(pattern_color);
    for (int n = 0; n < head.getLength(); n++) {
      head.setColorTime(n, colors.get(pattern_color, 0), colors.get(pattern_color, 1), colors.get(pattern_color, 2), millis(), 300);
    }
    pattern_color++;
    if (pattern_color == colors.getColorsCount()) {
      pattern_color = 1;
    }
  }

  if (timer.isTime(TIMER_TAILCHANGE, true)) {
    if (colorset == 0) {
      tail.setColor(0, 255, 50, 0);
      tail.setColor(1, 200, 100, 0);
      tail.setColor(2, 150, 150, 0);
      tail.setColor(3, 100, 200, 0);
      tail.setColor(4, 50, 255, 0);
      tail.setColor(5, 0, 255, 0);
    } else if (colorset == 1) {
      tail.setColor(0, 255, 0, 0);
      tail.setColor(1, 0, 0, 255);
      tail.setColor(2, 0, 0, 255);
      tail.setColor(3, 255, 0, 0);
      tail.setColor(4, 0, 0, 255);
      tail.setColor(5, 0, 0, 255);
    } else if (colorset == 2) {
      tail.setColor(0, 255, 255, 255);
      tail.setColor(1, 150, 150, 150);
      tail.setColor(2, 200, 100, 100);
      tail.setColor(3, 255, 0, 0);
      tail.setColor(4, 255, 255, 255);
      tail.setColor(5, 255, 255, 255);
    }
    colorset++;
    if (colorset == 3) {
      colorset = 0;
    }
  }


  if (timer.isTime(TIMER_ULTRASONIC, true)) {
    float distance = getDistance();
    //Serial.println(distance);
    uint32_t white = colors.get(c_white);
    uint32_t blue = colors.get(c_blue);
    int count = map(distance, 10, 50, 255 * 8, 0);


    for (int n = 1; n < 9; n++) {
      int color = 0;
      if (count > 255) {
        color = 255;
        count -= color;
      } else {
        color = count;
        count -= color;
      }
      color = colors.filter(color);
      //Serial.println(color);
      ring.setColorTime(n, 255 - color, 255 - color, 255, millis(), 100);
    }

    ring.setColorTime(0, white, millis(), 50);
    ring.setColorTime(9, white, millis(), 50);
  }

  if (timer.isTime(TIMER_TAILMOVE, true)) {
    tail.move(true);
  }

  if (timer.isTime(TIMER_LED_UPDATE, true)) {
    head.update();
    ring.update();
    tail.show();
  }
}
