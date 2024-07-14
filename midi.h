#pragma once
#include <MIDI.h>
#include <SoftwareSerial.h>

void setupMidi();
void loopMidi();
void sendMidiProgramChange(int program, int channel);
void sendMidiControlChange(int control, int value, int channel);