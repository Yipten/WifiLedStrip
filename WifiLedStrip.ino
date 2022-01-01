#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>
#include <FS.h>

#include "Constants.h"
#include "LedStrip.h"

// wifi variables
ESP8266WebServer server(80);
IPAddress apIP(42, 42, 42, 42);
IPAddress subnetMaskIP(255, 255, 255, 0);
const char* ssid = SSID;
const char* password = PASSWORD;

// sends an HTTP response containing the contents of the specified file
void sendHtml(char* filename) {
	// string to store HTML code
	String html = "";
	// open specified file from SPIFFS
	File file = SPIFFS.open(filename, "r");
	// avoid SRAM fragmentation (because of large string)
	html.reserve(file.available());
	// build string byte-by-byte
	while (file.available())
		html += (char)file.read();
	file.close();
	// send response
	server.send(200, "text/html", html);
}

void handleNotFound() {
	server.send(404, "text/html", "<h1>404: not found</h1>");
}

void handleRoot() {
	// get whether all LEDs should be on or off
	uint8_t color = server.arg("color").toInt();
	// update LEDs
	switch (color) {
		case 1:
			LedStrip::fill(255, 0, 0);
			break;
		case 2:
			LedStrip::fill(0, 255, 0);
			break;
		case 3:
			LedStrip::fill(0, 0, 255);
			break;
		default:
			LedStrip::fill(0, 0, 0);
			break;
	}
	// send HTTP response
	sendHtml("/index.html");
}

void setup() {
	delay(1000);

	// initialize wifi access point
	WiFi.mode(WIFI_AP);
	WiFi.softAPConfig(apIP, apIP, subnetMaskIP);
	WiFi.softAP(ssid, password);

	// initialize web server
	server.begin();
	server.onNotFound(handleNotFound);
	server.on("/", handleRoot);

	// initialize LED strip
	LedStrip::initialize(NUM_LEDS, PIN, BRIGHTNESS);

	// initialize SPIFFS
	SPIFFS.begin();
}

void loop() {
	server.handleClient();
}
