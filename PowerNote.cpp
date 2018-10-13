#include "Arduino.h"
#include "PowerNote.h"
#include <String.h>
#include <Wire.h>

PowerNote::PowerNote(String _name, uint8_t _pin, uint8_t _LEDpin, int _threshold, int _note, int _velocity, int _channel) {
	this->name = _name;
	this->pin = _pin;
	this->LEDpin = _LEDpin;
	this->threshold = _threshold;
	this->note = _note;
	this->velocity = _velocity;
	this->channel = _channel;
}

bool lastOn = false;
int n;
int aread = 0;

void PowerNote::notePlayer() {
	if (noteOn()) {
		if (!lastOn) {
			usbMIDI.sendNoteOn(note, velocity, channel);
			digitalWrite(LEDpin, HIGH);
			lastOn = true;
		}
	} else {
		if (lastOn) {
			usbMIDI.sendNoteOff(note, velocity, channel);
			digitalWrite(LEDpin, HIGH);
			lastOn = false;
		}
	}
	Serial.print(name); Serial.print(" ");
	if (lastOn) Serial.print("On ");
	else Serial.print("Off ");
}

bool PowerNote::noteOn() {
	aread = analogRead(pin);
	Serial.print(aread); Serial.print(" ");

	if (aread > threshold) {
		if (n < 10) n++;
	} else {
		if (n > 0) n--;
	}
	return n > 5;
}