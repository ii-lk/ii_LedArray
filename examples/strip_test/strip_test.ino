#include <CODBOTS_LedArray.h> 
CODBOTS_LedArray strip1 = CODBOTS_LedArray(2, 6);

void setup() {
  Serial.begin(115200);
  strip1.testAll();
  strip1.clear();



}

void loop() {
  // put your main code here, to run repeatedly:

}
