const int spoofPin1 = 6;
const int spoofPin2 = 5;

void setup() {
  pinMode(spoofPin1, OUTPUT);
  pinMode(spoofPin2, OUTPUT);
}

void loop() {
  // Spoof increasing light
  for (int i = 0; i < 255; i += 5) {
    analogWrite(spoofPin1, i);  // Simulated light increasing
    delay(200);
  }

  // Spoof decreasing light
  for (int i = 255; i > 0; i -= 5) {
    analogWrite(spoofPin1, i);  // Simulated light decreasing
    delay(200);
  }
  for (int i = 0; i < 255; i += 5) {
    analogWrite(spoofPin2, i);  // Simulated light increasing
    delay(200);
  }

  // Spoof decreasing light
  for (int i = 255; i > 0; i -= 5) {
    analogWrite(spoofPin2, i);  // Simulated light decreasing
    delay(200);
  }
}
