const int PHOTO_DIODE = A0;
int inputVal = 0;

void setup() {
	Serial.begin(9600);
}

void loop() {
	inputVal = analogRead(PHOTO_DIODE);
	delay(10);
	if (inputVal) {
		Serial.print("IR detected: ");
		Serial.println(inputVal);
	}
}