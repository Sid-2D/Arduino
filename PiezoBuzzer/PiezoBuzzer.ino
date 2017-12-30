const int BUZZER = 3;

void setup() {
	pinMode(BUZZER, OUTPUT);
}

void loop() {
	digitalWrite(BUZZER, HIGH);
	delay(200);
	digitalWrite(BUZZER, LOW);
	delay(2000);
}