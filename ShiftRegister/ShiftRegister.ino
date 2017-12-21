const int DataPin = 2;
const int ClockPin = 4;
const int LatchPin = 3;

void setup() {
	pinMode(DataPin, OUTPUT);
	pinMode(ClockPin, OUTPUT);
	pinMode(LatchPin, OUTPUT);
}

unsigned int MASK = 0b10;
bool left = false;

void loop() {
	digitalWrite(LatchPin, LOW);
	shiftOut(DataPin, ClockPin, MSBFIRST, MASK);
	digitalWrite(LatchPin, HIGH);
	delay(100);
	if (left) {
		MASK = (MASK << 1);
	} else {
		MASK = (MASK >> 1);
	}
	if (MASK == 0b0100000) {
		left = false;
	} else if (MASK == 0b00000001) {
		left = true;
	}
}