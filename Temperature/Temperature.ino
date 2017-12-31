const int TEMP_SENSOR = A0;
int input = 0;
float temperature = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  input = analogRead(TEMP_SENSOR);
  temperature = (5.0 * input * 100.0) / 1024;
  Serial.print("Temperature: ");
  Serial.println(temperature);
  delay(1000);
}