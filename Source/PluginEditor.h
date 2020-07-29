#pragma once

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomLookFeel.h"

//==============================================================================

class MIDICAudioProcessorEditor  : public AudioProcessorEditor, private Slider::Listener, private Button::Listener
{
public:
    MIDICAudioProcessorEditor (MIDIControllerAudioProcessor&);
    ~MIDICAudioProcessorEditor();

	
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

	void noteSelectorChanged();
	void modeSelectorChanged();

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MIDIControllerAudioProcessor& processor;

	void sliderValueChanged(Slider* slider) override;
	void buttonClicked(Button* button) override;

	TextButton noteTestButton;
	TextButton noteResetButton;

	//Sliders
	Slider delayTimeSlider;
	Slider tuningSlider;
	Slider variPitchSlider;

	//Labels for sliders
	Label delayTimeSliderLabel;
	Label tuningSliderLabel;
	Label variPitchSliderLabel;

	//Combo box
	ComboBox noteSelector;
	ComboBox modeSelector;

	//custom look and feel for sliders
	CustLookFeel custLookFeel;

	MidiKeyboardState keyboardState;
	MidiKeyboardComponent keyboard;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MIDICAudioProcessorEditor)
};
