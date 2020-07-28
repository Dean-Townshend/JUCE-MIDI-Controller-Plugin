#pragma once
#include "JuceHeader.h"


class MidiProcessor
{
public:

	bool msgSent;
	int noteVelo = 0;

	void process(MidiBuffer& midiMessages)
	{
		//processedBuffer.clear();

		MidiMessage currentMessage;
		MidiBuffer::Iterator it(midiMessages);
		int samplePos;

		auto message = MidiMessage::controllerEvent(1, 7, (uint8)noteVelo);
		//auto noteMes = MidiMessage::noteOn(1, 50, (uint8)noteVelo);
		
		if (msgSent == true)
		processedBuffer.addEvent(message, samplePos);
		msgSent = false;

		midiMessages.swapWith(processedBuffer);
	}

	MidiBuffer processedBuffer;
};