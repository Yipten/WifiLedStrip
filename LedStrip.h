#ifndef LedStrip_h
#define LedStrip_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "Constants.h"

class LedStrip {
	public:
		// one-time setup for use at program start
		static void initialize(uint8_t numLeds, uint8_t pin, uint8_t brightness);
		// updates output of LEDs based on mode and other variables
		static void update();
		static void setMode(uint8_t m);
		static void setTimeDelay(uint32_t ms);
		static void setColor(uint8_t r, uint8_t g, uint8_t b);
	private:
		// object for controlling LED strip
		static Adafruit_NeoPixel strip;
		// for timing of animations
		static uint32_t timestamp;
		// time delay (ms) for animations
		static uint32_t timeDelay;
		// current display mode
		static uint8_t mode;
		// current step of animation
		static uint8_t step;
		// true if static pattern has been shown
		static bool done;
		// color to be displayed
		static uint32_t color;

		// makes all LEDs the same color
		static void fill(uint32_t c);

		// flashes all LEDs on and off
		static void flash();
};

#endif

