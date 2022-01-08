#include "LedStrip.h"

Adafruit_NeoPixel LedStrip::strip;
uint32_t LedStrip::timestamp;
uint32_t LedStrip::timeDelay;
uint8_t LedStrip::mode;
uint8_t LedStrip::step;
bool LedStrip::done;
uint32_t LedStrip::color;

// public functions

void LedStrip::initialize(uint8_t numLeds, uint8_t pin, uint8_t brightness) {
	strip = Adafruit_NeoPixel(numLeds, pin, NEO_GRB + NEO_KHZ800);
	strip.begin();
	strip.setBrightness(brightness);
	timestamp = 0;
	setMode(MODE_OFF);
	setColor(0, 0, 0);
	update();
}

void LedStrip::update() {
	if (!done) {
		switch (mode) {
			case MODE_OFF:
				fill(strip.Color(0, 0, 0));
				done = true;
				break;
			case MODE_SOLID_ON:
				fill(color);
				done = true;
				break;
			case MODE_FLASH:
				flash();
				break;
			default:
				break;
		}
		strip.show();
	}
}

void LedStrip::setMode(uint8_t m) {
	mode = m;
	done = false;
}

void LedStrip::setTimeDelay(uint32_t ms) {
	timeDelay = ms;
}

void LedStrip::setColor(uint8_t r, uint8_t g, uint8_t b) {
	color = strip.Color(r, g, b);
}

// private functions

void LedStrip::fill(uint32_t c) {
	for (uint8_t i = 0; i < NUM_LEDS; i++)
		strip.setPixelColor(i, c);
}

void LedStrip::flash() {
	if (millis() - timestamp >= timeDelay) {
		timestamp = millis();
		// two steps (on & off)
		fill(step ? strip.Color(0, 0, 0) : color);
		step = !step;
	}
}

