
#pragma once

#include <JuceHeader.h>
#include "MidiProcessor.h"

//==============================================================================
/**
*/
class MIDIControllerAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    MIDIControllerAudioProcessor();
    ~MIDIControllerAudioProcessor();

	int8 ccTempVal0 = 0;
	int8 ccVal0 = 0;
	int8 ccTempVal1 = 0;
	int8 ccVal1 = 0;
	int8 ccTempVal2 = 0;
	int8 ccVal2 = 0;
	int8 ccTempVal3 = 0;
	int8 ccVal3 = 0;

	//Tuner note selected
	int noteSelected = 1;

    //==============================================================================
	void setMidiProcNoteVel(int noteVel)
	{
		midiProcessor.noteVelo = noteVel;
	}

	void setMidiProcSent(bool sent)
	{
		midiProcessor.msgSent = sent;
	}

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
	MidiProcessor midiProcessor;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MIDIControllerAudioProcessor)
};
