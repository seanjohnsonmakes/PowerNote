#include "Arduino.h"
#include "PowerNote.h"
#include <String.h>
#include <Wire.h>

// This library takes care of note detection and activation
PowerNote::PowerNote(String _name, uint8_t _pin, uint8_t _LEDpin, int _threshold, int _note, int _velocity, int _channel) {
	this->name = _name;
	this->pin = _pin;
	this->LEDpin = _LEDpin;
	this->threshold = _threshold;
	this->note = _note;
	this->velocity = _velocity;
	this->channel = _channel;
}

// Tracks if note was "on" each cycle
bool lastOn = false;
// Counter for debouncing input
int n;
// Analog input
int aread = 0;

// Plays note if finger bends pass a certain threshold which is determined in noteOn()
// Keeps track of the state each cycle so that the midi signals are only sent when needed
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
			digitalWrite(LEDpin, LOW);
			lastOn = false;
		}
	}
	// Serial output for debugging
	Serial.print(name); Serial.print(" ");
	if (lastOn) Serial.print("On ");
	else Serial.print("Off ");
}

// Returns true if the finger is bent past a certain threshold
bool PowerNote::noteOn() {
	aread = analogRead(pin);
	Serial.print(aread); Serial.print(" ");

	// Debounces input
	if (aread > threshold) {
		if (n < 10) n++;
	} else {
		if (n > 0) n--;
	}
	return n > 5;
}