#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>
#include "Constants.h"

// wifi variables
ESP8266WebServer server(80);
IPAddress apIP(42, 42, 42, 42);
IPAddress subnetMaskIP(255, 255, 255, 0);
const char* ssid = SSID;
const char* password = PASSWORD;

// LED strip variables
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
const uint32_t off = strip.Color(0, 0, 0);
const uint32_t red = strip.Color(0, 255, 0);
const uint32_t orange = strip.Color(0, 255, 63);
const uint32_t yellow = strip.Color(0, 255, 127);
const uint32_t green = strip.Color(0, 0, 255);
const uint32_t blue = strip.Color(255, 0, 0);
const uint32_t purple = strip.Color(255, 255, 0);
const uint32_t white = strip.Color(255, 255, 255);

void handleNotFound() {
	server.send(404, "text/html", "<h1>404: not found</h1>");
}

void handleRoot() {
	// TODO: manage GET requests here
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
}

void loop() {
	server.handleClient();
}
