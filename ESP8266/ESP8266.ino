#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

MDNSResponder mdns;

const char* ssid = "";
const char* password = "";

ESP8266WebServer server(80);

String webPage = "";

int gpio0 = 0;
int gpio2 = 2;

void setup() {
	webPage += "<p><span style=\"font-size: 25px; text-decoration: bold;\">LED 1: <span><a href=\"socket1On\"><button>ON</button></a>&nbsp;<a href=\"socket1Off\"><button>OFF</button></a></p>";
	webPage += "<p><span style=\"font-size: 25px; text-decoration: bold;\">LED 2: <span><a href=\"socket2On\"><button>ON</button></a>&nbsp;<a href=\"socket2Off\"><button>OFF</button></a></p>";

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

	if (mdns.begin("esp8266")) {
		Serial.println("MDNS responder started");
	}

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