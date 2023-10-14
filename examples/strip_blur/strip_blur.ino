#include <CODBOTS_LedStrip.h>

CODBOTS_LedStrip strip1 = CODBOTS_LedStrip(2, 6);
Colors colors;

void setup() {
  Serial.begin(115200);
  strip1.begin();
  delay(500);
  strip1.setBlurMode(true);
  Serial.println("INIT DONE!");
  delay(1000);
  for (int n = 0; n < 6; n++) {
    // Serial.println("SET COLOR BK:"+String(n));
    strip1.setColorB(n, 0, 0, 0, millis(), 1);
  }
}

void loop() {

  uint32_t color = colors.get(random(colors.getColorsCount()-1)+1);
  for (int n = 0; n < 6; n++) {
    strip1.setColorB(n, 255, 0, 0, millis(), (n + 1) * 100);
  }
  while (strip1.update()) {}

  color = colors.get(random(colors.getColorsCount()-1)+1);
  for (int n = 0; n < 6; n++) {
    strip1.setColorB(n, 255, 255, 0, millis(), (n + 1) * 100);
  }
  while (strip1.update()) {}

  color = colors.get(random(colors.getColorsCount()-1)+1);
  for (int n = 0; n < 6; n++) {
    strip1.setColorB(n, 255, 255, 255, millis(), (n + 1) * 100);
  }
  while (strip1.update()) {}
}
