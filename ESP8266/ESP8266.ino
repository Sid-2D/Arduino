#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "index.h"

MDNSResponder mdns;

const char* ssid = "";
const char* password = "";

ESP8266WebServer server(80);

String webPage = "";

int gpio0 = 0;
int gpio2 = 2;

void setup() {
	webPage = MAIN_page;

	// GPIO
	pinMode(gpio0, OUTPUT);
	digitalWrite(gpio0, LOW);
	pinMode(gpio2, OUTPUT);
	digitalWrite(gpio2, LOW);

	delay(1000);
	Serial.begin(115200);
	WiFi.begin(ssid, password);
	Serial.println("");

	// Wait for connection
	Serial.println("Trying to connect");
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println("");
	Serial.print("Connected to: ");
	Serial.println(ssid);
	Serial.print("IP Address: ");
	Serial.println(WiFi.localIP());

	server.on("/", [](){
		server.send(200, "text/html", webPage);
	});

	server.on("/socket1On", [](){
		server.send(200, "text/html", webPage);
		digitalWrite(gpio0, HIGH);
		delay(1000);
	});

	server.on("/socket1Off", [](){
		server.send(200, "text/html", webPage);
		digitalWrite(gpio0, LOW);
		delay(1000);
	});

	server.begin();
	Serial.println("HTTP server started");
}

void loop() {
	server.handleClient();
}