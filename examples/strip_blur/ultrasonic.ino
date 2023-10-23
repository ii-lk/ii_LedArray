//ultrasonic
#define ULTRA_TRIG 23
#define ULTRA_ECHO 22

#define BAUD_RATE 115200
void initUltrasonic() {
  pinMode(ULTRA_TRIG, OUTPUT);  // Sets the trigPin as an Output
  pinMode(ULTRA_ECHO, INPUT);   // Sets the echoPin as an Input
}
long duration;
 #define ultrasonic_array_size 3
int ultrasonic_array[ultrasonic_array_size];
int ultrasonic_index;
float lastdistance=0;
float getDistance() {
  long stime = millis();
  digitalWrite(ULTRA_TRIG, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(ULTRA_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRA_TRIG, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(ULTRA_ECHO, HIGH, 9000);
  if (duration == 0) {
    duration = 6200;
  }
  /* Serial.print('\t');
  Serial.println(duration);
  Serial.print('\t');
  Serial.print('\t');
  Serial.println(millis() - stime);
   */
  // Calculating the distance
  float distance=(duration * 0.034 / 2);
  //Serial.println(distance);
  if(distance<2){
    return lastdistance;
  }
  lastdistance=distance;
  return distance;

/*

  ultrasonic_array[ultrasonic_index] = duration * 0.034 / 2;
  ultrasonic_index++;
  if (ultrasonic_index == ultrasonic_array_size) {
    ultrasonic_index = 0;
  }
  int total = 0;
  for (int i = 0; i < ultrasonic_array_size; i++) {
    total += ultrasonic_array[ultrasonic_index];
  }
  return total/ultrasonic_array_size;
 */
}