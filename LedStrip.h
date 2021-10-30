#ifndef LedStrip_h
#define LedStrip_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "Constants.h"

class LedStrip {
	public:
		static void initialize(uint8_t numLeds, uint8_t pin, uint8_t brightness);
		static void fill(uint8_t r, uint8_t g, uint8_t b);
	private:
		static Adafruit_NeoPixel strip;
};

#endif
