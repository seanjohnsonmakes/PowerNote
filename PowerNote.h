#ifndef PowerNote_h
#define PowerNote_h
#include <String.h>
#include <Wire.h>

#include "Arduino.h"

class PowerNote
{
	public:
		PowerNote(String _name, uint8_t _pin, uint8_t _LEDpin, int _threshold, int _note, int _velocity, int _channel);
		uint8_t pin;
		uint8_t LEDpin;
		int threshold;
		int note;
		int velocity;
		int channel;
		bool lastOn;
		String name;
		int aread;
		int n;

		void notePlayer();
		bool noteOn();
};

#endif