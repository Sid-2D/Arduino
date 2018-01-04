const int lcdE = 11;
const int lcdRS = 12;

const int D[] = {9, 8, 7, 6, 5, 4, 3, 2};

void sendOut(unsigned int data) {
	unsigned int mask = 1;
	for (int i = 0; i < 8; i++) {
		if (mask & data) {
			digitalWrite(D[i], HIGH);
			Serial.print('1');
		} else {
			digitalWrite(D[i], LOW);
			Serial.print('0');
		}
		mask = (mask << 1);
	}
	Serial.println('x');
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

void setup() {
	Serial.begin(9600);
	pinMode(lcdE, OUTPUT);
	pinMode(lcdRS, OUTPUT);

	for (int i = 0; i < 8; i++) {
		pinMode(D[i], OUTPUT);
	}

	// Init LCD
	delay(20);			// LCD Power ON delay always > 15ms 
	lcd_cmd(0x38);		// Initialization of 16X2 LCD in 8bit mode,  
	lcd_cmd(0x0C);		// Display ON Cursor OFF 
	lcd_cmd(0x06);		// Auto Increment cursor 
	lcd_cmd(0x01);		// clear display 
	delay(2);			// Clear display command delay > 1.63 ms 
	lcd_cmd(0x80);
	
	// Send data
	lcd_cmd(0x40);	// Start storing data at this location
	lcd_data(0x04);	
	lcd_data(0x0e);
	lcd_data(0x0e);
	lcd_data(0x0e);
	lcd_data(0x1f);
	lcd_data(0x00);
	lcd_data(0x04);
	lcd_data(0x00);

	lcd_cmd(0xc0);	// Get to second line
	lcd_data(0x00);	// Display data from this location
}

void loop() {

}