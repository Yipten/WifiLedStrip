#include "LedStrip.h"

Adafruit_NeoPixel LedStrip::strip;

void LedStrip::initialize(uint8_t numLeds, uint8_t pin, uint8_t brightness) {
	strip = Adafruit_NeoPixel(numLeds, pin, NEO_GRB + NEO_KHZ800);
	strip.begin();
	strip.setBrightness(brightness);
	strip.show();
	fill(0, 0, 0);
}

void LedStrip::fill(uint8_t r, uint8_t g, uint8_t b) {
	uint32_t color = strip.Color(r, g, b);
	for (uint8_t i = 0; i < NUM_LEDS; i++)
		strip.setPixelColor(i, color);
	strip.show();
}
