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
void sendResponse(char* filetype, char* filename) {
	// string to store HTML code
	String content = "";
	// open specified file from SPIFFS
	File file = SPIFFS.open(filename, "r");
	// avoid SRAM fragmentation (because of large string)
	content.reserve(file.available());
	// build string byte-by-byte
	while (file.available())
		content += (char)file.read();
	file.close();
	// send response
	server.send(200, filetype, content);
}

void handleNotFound() {
	server.send(404, "text/html", "<h1>404: not found</h1>");
}

void handleRoot() {
	sendResponse("text/html", "/index.html");
}

void handleSubmit() {
	// get RGB values
	uint8_t r = server.arg("red").toInt();
	uint8_t g = server.arg("green").toInt();
	uint8_t b = server.arg("blue").toInt();
	// update LEDs
	LedStrip::fill(r, g, b);

	server.send(200);
}

void handleCss() {
	sendResponse("text/css", "/style.css");
}

void handleInputValues() {
	sendResponse("text/javascript", "/inputValues.js");
}

void handleSubmitForm() {
	sendResponse("text/javascript", "/submitForm.js");
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
	server.on("/submit", handleSubmit);
	server.on("/style.css", handleCss);
	server.on("/inputValues.js", handleInputValues);
	server.on("/submitForm.js", handleSubmitForm);

	// initialize LED strip
	LedStrip::initialize(NUM_LEDS, PIN, BRIGHTNESS);

	// initialize SPIFFS
	SPIFFS.begin();
}

void loop() {
	server.handleClient();
}

