const int lcdE = 11;
const int lcdRS = 12;

const int D[] = {9, 8, 7, 6, 5, 4, 3, 2};

void sendOut(unsigned int data) {
	unsigned int mask = 1;
	for (int i = 0; i < 8; i++) {
		if (mask & data) {
			digitalWrite(D[i], HIGH);
		} else {
			digitalWrite(D[i], LOW);
		}
		mask = (mask << 1);
	}
	delay(5);
  	digitalWrite(lcdE, HIGH);
  	delay(5);
  	digitalWrite(lcdE, LOW);
	delay(5);
}

void lcd_cmd(unsigned int cmd) {
	// Turn on cmd mode
	digitalWrite(lcdRS, LOW);
	// Send cmd to data pins
	sendOut(cmd);
}

void lcd_data(unsigned int data) {
	// Turn on data mode
	digitalWrite(lcdRS, HIGH);
	// Send data to data pins
	sendOut(data);
}

void initLCD() {
	// Init LCD
	delay(20);			// LCD Power ON delay always > 15ms 
	lcd_cmd(0x38);		// Initialization of 16X2 LCD in 8bit mode,  
	lcd_cmd(0x0C);		// Display ON Cursor OFF 
	lcd_cmd(0x06);		// Auto Increment cursor 
	lcd_cmd(0x01);		// Clear display 
	delay(2);			// Clear display command delay > 1.63 ms 
	lcd_cmd(0x80);		// Cursor at home position
}

void customChar(int location, char charMatrix[]) {
	lcd_cmd(0x40 + (location * 8));	// Start storing data at this location
	for (int i = 0; i < 8; i++) {
		lcd_data(charMatrix[i]);	
	}
}

void setup() {
	Serial.begin(9600);
	pinMode(lcdE, OUTPUT);
	pinMode(lcdRS, OUTPUT);

	for (int i = 0; i < 8; i++) {
		pinMode(D[i], OUTPUT);
	}

	initLCD();
	
	char charMatrix[][8] = { { 0x00, 0x0A, 0x15, 0x11, 0x0A, 0x04, 0x00, 0x00 },                                
							 { 0x04, 0x1F, 0x11, 0x11, 0x1F, 0x1F, 0x1F, 0x1F },  
							 { 0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x04, 0x00 },
							 // { 0x01, 0x03, 0x07, 0x1F, 0x1F, 0x07, 0x03, 0x01 },
							 // { 0x01, 0x03, 0x05, 0x09, 0x09, 0x0B, 0x1B, 0x1 },
							 { 0x0A, 0x0A, 0x1F, 0x11, 0x11, 0x0E, 0x04, 0x04 },
							 { 0x00, 0x00, 0x0A, 0x00, 0x04, 0x11, 0x0E, 0x00 },
							 { 0x00, 0x0A, 0x1F, 0x1F, 0x0E, 0x04, 0x00, 0x00 } };

	char car0[8] = {
		0b00000,
		0b00111,
		0b00100,
		0b01100,
		0b11111,
		0b10011,
		0b01101,
		0b01100
	};

	char car1[8] = {
		0b00000,
		0b11000,
		0b01000,
		0b01000,
		0b11111,
		0b11001,
		0b10110,
		0b00110
	};

	for (int i = 0; i < 6; i++) {
		customChar(i, charMatrix[i]);
	}

	customChar(6, car0);
	customChar(7, car1);

	// Send data
	lcd_cmd(0x80);	// Get to first line
	for (int i = 0; i < 6; i++) {
		lcd_data(i);	// Display data from this location
		lcd_data(' ');
	}

	lcd_data(6);
	lcd_data(7);
}

void loop() {
	
}