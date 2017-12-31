const int LDR = A5;
float inputVal = 0;
float prevVal = 0;

void setup() {
	Serial.begin(9600);
}

void loop() {
	inputVal = analogRead(LDR);
	if  (abs(inputVal - prevVal) >= 10) {
		Serial.print("LDR value is: ");
		Serial.println(inputVal);
		prevVal = inputVal;
	}
	delay(100);
}