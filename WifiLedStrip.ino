#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>
#include "Constants.h"
#include <FS.h>

// wifi variables
ESP8266WebServer server(80);
IPAddress apIP(42, 42, 42, 42);
IPAddress subnetMaskIP(255, 255, 255, 0);
const char* ssid = SSID;
const char* password = PASSWORD;

// LED strip variables
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
const uint32_t off = strip.Color(0, 0, 0);
const uint32_t red = strip.Color(255, 0, 0);
const uint32_t orange = strip.Color(255, 63, 0);
const uint32_t yellow = strip.Color(255, 127, 0);
const uint32_t green = strip.Color(0, 255, 0);
const uint32_t blue = strip.Color(0, 0, 255);
const uint32_t purple = strip.Color(255, 0, 255);
const uint32_t white = strip.Color(255, 255, 255);

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
	const uint32_t* rgb;
	switch (color) {
		case 1:
			rgb = &red;
			break;
		case 2:
			rgb = &green;
			break;
		case 3:
			rgb = &blue;
			break;
		default:
			rgb = &off;
			break;
	}
	for (byte i = 0; i < NUM_LEDS; i++)
		strip.setPixelColor(i, *rgb);
	strip.show();
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
	strip.begin();
	strip.setBrightness(BRIGHTNESS);
	strip.show();

	// initialize SPIFFS
	SPIFFS.begin();
}

void loop() {
	server.handleClient();
}
