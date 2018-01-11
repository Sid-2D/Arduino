// Turns an led on if /ON is visited on the access point's IP address, OFF otherwise

#include<SoftwareSerial.h>

#define DEBUG true

#define LED 7

bool ledStatus = false;

SoftwareSerial esp8266(3, 2);

void ledSwitch(bool ON) {
	if (ON) {
		digitalWrite(LED, HIGH);
		ledStatus = true;
	} else {
		digitalWrite(LED, LOW);
		ledStatus = false;
	}
}

void setup() {
	Serial.println("Starting...");
	pinMode(LED, OUTPUT);
	Serial.begin(9600);    // For Serial monitor 
	esp8266.begin(115200); // ESP Baud rate
	sendData("AT\r\n", 2000, DEBUG); // Check OK
	sendData("AT+RST\r\n", 2000, DEBUG); // Reset module
	sendData("AT+CWMODE=2\r\n", 1000, DEBUG); // Configure as access point
	sendData("AT+CIFSR\r\n", 1000, DEBUG); // Get IP address
	sendData("AT+CIPMUX=1\r\n", 1000, DEBUG); // Configure for multiple connections
	sendData("AT+CIPSERVER=1,80\r\n", 1000, DEBUG); // Turn on server on port 80
}
 
int connectionId;
void loop() {
	if (esp8266.available()) {
		// Recieving from web browser to toggle led
		if (esp8266.find("+IPD,")) {
			delay(600);
			connectionId = esp8266.read() - 48;
			char url[36];
			esp8266.readBytes(url, 30);
			String mode(url);
			if (mode.indexOf("ON") != -1) {
				ledSwitch(true);
			} else if (mode.indexOf("OFF") != -1) {
				ledSwitch(false);
			}

			// Sending data to browser
			String webpage;
			if (ledStatus) {
				webpage = "<h1>LED is: ON</h1>";
			} else {
				webpage = "<h1>LED is: OFF</h1>";
			}
			espFormat(webpage);

			String closeCommand = "AT+CIPCLOSE=";  // Close the socket connection 
			closeCommand += connectionId; // Append connection id
			closeCommand += "\r\n";
			sendData(closeCommand, 3000, DEBUG);
		}
	}
}
 
// Sends data from ESP to webpage
void espFormat(String d) {
    String cipSend = " AT+CIPSEND=";
    cipSend += connectionId; 
    cipSend += ",";
    cipSend += d.length();
    cipSend += "\r\n";
    sendData(cipSend, 1000, DEBUG);
    sendData(d, 1000, DEBUG); 
}

// Gets the data from esp and displays in serial monitor         
String sendData(String command, const int timeout, boolean debug) {
    String response = "";
    esp8266.print(command);
    long int time = millis();
    while ((time + timeout) > millis()) {
		while (esp8266.available()) {
				char c = esp8266.read(); // read the next character
				response += c;
			}
    }
    if (debug) {
    	// Serial.print("Response:");
    	Serial.print(response); // Displays the esp response messages in arduino Serial monitor
    }
    return response;
}