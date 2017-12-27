const int analogInput = A0;
const int LED = 11;
int inputVal = 0;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  inputVal = analogRead(analogInput);
  Serial.println(inputVal);
  analogWrite(LED, inputVal / 4);
  delay(100);
}
