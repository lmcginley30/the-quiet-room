// Arduino Nano + HC-SR04 ultrasonic sensor
// HC-SR04: VCC -> 5V, GND -> GND, TRIG -> D9, ECHO -> D10
// Use the Nano's built-in LED on D13, or connect an external LED
// (with a series resistor) to D13 and GND.

const byte TRIG_PIN = 9;
const byte ECHO_PIN = 10;
const byte LED_PIN = 13;
const float DETECT_DISTANCE_CM = 20.0;
const unsigned long ECHO_TIMEOUT_US = 30000UL;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);  // Ensure the LED starts off.

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);
}

void loop() {
  // Send a 10 us trigger pulse to the HC-SR04.
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  const unsigned long echoTime = pulseIn(ECHO_PIN, HIGH, ECHO_TIMEOUT_US);

  // pulseIn returns 0 if no echo was received before the timeout.
  const float distanceCm = echoTime == 0 ? -1.0 : echoTime * 0.0343 / 2.0;
  const bool detected = distanceCm > 0 && distanceCm <= DETECT_DISTANCE_CM;

  digitalWrite(LED_PIN, detected ? HIGH : LOW);
  delay(50);
}
