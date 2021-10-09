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
uint32_t off = strip.Color(0, 0, 0);
uint32_t red = strip.Color(255, 0, 0);
uint32_t orange = strip.Color(255, 63, 0);
uint32_t yellow = strip.Color(255, 127, 0);
uint32_t green = strip.Color(0, 255, 0);
uint32_t blue = strip.Color(0, 0, 255);
uint32_t purple = strip.Color(255, 0, 255);
uint32_t white = strip.Color(255, 255, 255);

void handleNotFound() {
	server.send(404, "text/html", "<h1>404: not found</h1>");
}

void handleRoot() {
	// get whether all LEDs should be on or off
	uint8_t color = server.arg("color").toInt();
	// update LEDs
	uint32_t* rgb;
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
	server.send(200, "text/html", "<h1>	<form action=\".\" method=\"get\">	<button type=\"submit\" value=\"0\" name=\"color\" style=\"font-size: 96px\">off</button><br>	<button type=\"submit\" value=\"1\" name=\"color\" style=\"font-size: 96px\">red</button><br>	<button type=\"submit\" value=\"2\" name=\"color\" style=\"font-size: 96px\">green</button><br>	<button type=\"submit\" value=\"3\" name=\"color\" style=\"font-size: 96px\">blue</button>	</form>	</h1>");
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
