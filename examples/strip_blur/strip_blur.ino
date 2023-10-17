#include <CODBOTS_LedStrip.h>
#include <esp_timer.h>
 

#define LEDSTRIP_PIN 4

Colors colors;
CODBOTS_LedStrip strip1 = CODBOTS_LedStrip(LEDSTRIP_PIN, 10);

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
  strip1.begin();
  strip1.setBlurMode(true); 

    esp_timer_create_args_t periodic_timer_args;
  periodic_timer_args.callback = &timerCallback;
  periodic_timer_args.arg = NULL;
  periodic_timer_args.dispatch_method = ESP_TIMER_TASK;
  esp_timer_create(&periodic_timer_args, &periodic_timer);

  // Start the timer with the specified interval
  esp_timer_start_periodic(periodic_timer, interval);
  
}

void loop() {
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
}
