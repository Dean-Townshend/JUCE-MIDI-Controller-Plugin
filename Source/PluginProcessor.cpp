#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MidiiiiiAudioProcessor::MidiiiiiAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

MidiiiiiAudioProcessor::~MidiiiiiAudioProcessor()
{
}

//==============================================================================
const String MidiiiiiAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MidiiiiiAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MidiiiiiAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MidiiiiiAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MidiiiiiAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MidiiiiiAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MidiiiiiAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MidiiiiiAudioProcessor::setCurrentProgram (int index)
{
}

const String MidiiiiiAudioProcessor::getProgramName (int index)
{
    return {};
}

void MidiiiiiAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MidiiiiiAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void MidiiiiiAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MidiiiiiAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MidiiiiiAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
		buffer.clear();
		midiMessages.clear();
		MidiBuffer generatedMidi;
		MidiMessage m0;
		MidiMessage m1;
		MidiMessage m2;
		MidiMessage m3;
		MidiMessage m4;

		if (ccVal0 != ccTempVal0)
		{
			m1 = MidiMessage::controllerEvent(1, 1, ccVal0);
			generatedMidi.addEvent(m1, midiMessages.getLastEventTime());
		}
		else if (ccVal1 != ccTempVal1)
		{
			m2 = MidiMessage::controllerEvent(1, 2, ccVal1-127);
			generatedMidi.addEvent(m2, midiMessages.getLastEventTime());
		}
		else if (ccVal2 != ccTempVal2)
		{
			m3 = MidiMessage::controllerEvent(1, 3, ccVal2);
			generatedMidi.addEvent(m3, midiMessages.getLastEventTime());
		}
		else if (ccVal3 != ccTempVal3)
		{
			m4 = MidiMessage::controllerEvent(1, 4, ccVal3);
			generatedMidi.addEvent(m4, midiMessages.getLastEventTime());
		}
		else generatedMidi.clear();

		ccTempVal0 = ccVal0;
		ccTempVal1 = ccVal1;
		ccTempVal2 = ccVal2;
		ccTempVal3 = ccVal3;
		
		midiMessages.swapWith(generatedMidi);
}

//==============================================================================
bool MidiiiiiAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MidiiiiiAudioProcessor::createEditor()
{
    return new MidiiiiiAudioProcessorEditor (*this);
}

//==============================================================================
void MidiiiiiAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MidiiiiiAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MidiiiiiAudioProcessor();
}
