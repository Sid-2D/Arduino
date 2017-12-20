#include <LiquidCrystal.h>

LiquidCrystal myLCD(12, 11, 5, 4, 3, 2);

void setup() {
	myLCD.begin(16, 2);
	myLCD.home();
	myLCD.print("Hello World!");
}

int posX = 0;

void loop() {
	delay(700);
	myLCD.clear();
	myLCD.setCursor(posX, 0);
	myLCD.print("Hello World!");
	if (posX < 16) {
		posX++;
	} else {
		posX = 0;
	}
}