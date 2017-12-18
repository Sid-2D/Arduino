const int LED = 6;

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  for (int i = 0; i < 256; i += 3) {
    analogWrite(LED, i);
    delay(10);
  }
  delay(100);
  for (int j = 255; j >= 0; j -= 3) {
    analogWrite(LED, j);
    delay(10);
  }
  delay(100);
}