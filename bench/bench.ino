// distance-led.ino: reads the HC-SR04, prints cm, lights an LED when something is close.

const int TRIG = 9;          // sensor TRIG to D9
const int ECHO = 10;         // sensor ECHO to D10
const int LED = 5;           // LED long leg to D5, short leg through a 220 ohm resistor to GND
const int HAND_CLOSE_CM = 30; // turn the LED on at this distance or closer
const int GAP = 5;             // turn it off beyond the threshold plus this gap

bool handClose = false;       // remembers the last answer to prevent flicker

void setup() {
  Serial.begin(115200);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);                    // a 10 microsecond ping
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  unsigned long us = pulseIn(ECHO, HIGH, 30000);
  float cm = us ? us / 58.0 : 400.0;           // no echo back: call it far away

  if (cm <= HAND_CLOSE_CM) handClose = true;
  if (cm > HAND_CLOSE_CM + GAP) handClose = false;
  digitalWrite(LED, handClose ? HIGH : LOW);

  Serial.print("cm ");                         // same format bench.html reads
  Serial.println(cm, 1);

  delay(50);
}
