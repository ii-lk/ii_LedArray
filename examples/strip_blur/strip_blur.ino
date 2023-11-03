#include <CODBOTS_LedStrip.h>
<<<<<<< HEAD
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
=======
#include <esp_timer.h>
 

#define LEDSTRIP_PIN 4

Colors colors;
CODBOTS_LedStrip strip1 = CODBOTS_LedStrip(LEDSTRIP_PIN, 10);
>>>>>>> a2e43d3e81d2ba5f62772b74aec1a75c25aef2dc

esp_timer_handle_t periodic_timer;
const int interval = 1000000; // Interval in microseconds (1 second)
const char* TAG = "ESP32_Timer";

// Function to be called by the timer
void timerCallback(void* arg) {
  Serial.println("Timer callback triggered");
  // Your code here
}
 
void setup() {
  Serial.begin(115200);
<<<<<<< HEAD

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

   

  initUltrasonic();

   
 
=======
  strip1.begin();
  strip1.setBlurMode(true); 

    esp_timer_create_args_t periodic_timer_args;
  periodic_timer_args.callback = &timerCallback;
  periodic_timer_args.arg = NULL;
  periodic_timer_args.dispatch_method = ESP_TIMER_TASK;
  esp_timer_create(&periodic_timer_args, &periodic_timer);

  // Start the timer with the specified interval
  esp_timer_start_periodic(periodic_timer, interval);
  
>>>>>>> a2e43d3e81d2ba5f62772b74aec1a75c25aef2dc
}

int pattern_color = 0;
int headside = 0;
int cc = 0;

int colorset = 0;

void loop() {
<<<<<<< HEAD

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
    tail.show();
  }

  if (timer.isTime(TIMER_LED_UPDATE, true)) {
    head.update();
    ring.update();
  }
=======
  int delay1 = 100;
  int delay2 = 50;
  for (int c = 0; c < COLORS_COUNT; c+=2) {
    uint32_t color = colors.get(c);
    for (int n = 0; n < strip1.getLEDCount(); n++) {
      strip1.setColor(n, color, millis() + (n * delay2), (n + 1) * delay1);
    }
    while (strip1.update()) {}
    delay(1000);
    color = colors.get(c+1);
    for (int n = 0; n < strip1.getLEDCount(); n++) {
      strip1.setColor((strip1.getLEDCount()-n)-1, color, millis() + (n * delay2), (n + 1) * delay1);
    }
   while (strip1.update()) {}
    delay(1000);
  }
}

void loop2(){
//  strip1.update();
>>>>>>> a2e43d3e81d2ba5f62772b74aec1a75c25aef2dc
}
