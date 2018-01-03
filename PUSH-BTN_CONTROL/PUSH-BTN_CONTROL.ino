const int LED[] = {3, 9, 5};
const int LEFT = 7;
const int RIGHT = 6;
int ledState = 0;
int leftBtnState = 0;
int rightBtnState = 0;

void setup() {
	pinMode(LED[0], OUTPUT);
	pinMode(LED[1], OUTPUT);
	pinMode(LED[2], OUTPUT);

	pinMode(LEFT, INPUT);
	pinMode(RIGHT, INPUT);

	digitalWrite(LED[ledState], HIGH);
	Serial.begin(9600);
}

void updateLedState(int change) {
	ledState += change;
	if (ledState > 2) {
		ledState = 0;
	} else if (ledState < 0) {
		ledState = 2;
	}
}

void performTransition() {
	for (int i = 0; i < 3; i++) {
		digitalWrite(LED[i], LOW);
	}
	digitalWrite(LED[ledState], HIGH);
}

void fadeAll() {
	for (int i = 0; i < 256; i++) {
		analogWrite(LED[0], i);
		analogWrite(LED[1], i);
		analogWrite(LED[2], i);
		delay(10);
	}
	for (int i = 255; i >= 0; i--) {
		analogWrite(LED[0], i);
		analogWrite(LED[1], i);
		analogWrite(LED[2], i);
		delay(10);
	}
}

void loop() {
	leftBtnState = digitalRead(LEFT);
	rightBtnState = digitalRead(RIGHT);
	if (leftBtnState == HIGH && rightBtnState == HIGH) {
		fadeAll();
	} else if (leftBtnState == HIGH) {
		Serial.print("LEFT");
		updateLedState(-1);
		performTransition();		
		delay(300);
	} else if (rightBtnState == HIGH) {
		Serial.print("RIGHT");
		updateLedState(1);
		performTransition();		
		delay(300);
	}
}