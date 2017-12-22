const int TRANSISTOR = 2;

void setup() {
	pinMode(TRANSISTOR, OUTPUT);
}

void loop() {
	digitalWrite(TRANSISTOR, HIGH);
	delay(1000);
	digitalWrite(TRANSISTOR, LOW);
	delay(1000);
}