#pragma once

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================

class MidiiiiiAudioProcessorEditor  : public AudioProcessorEditor, private Slider::Listener
{
public:
    MidiiiiiAudioProcessorEditor (MidiiiiiAudioProcessor&);
    ~MidiiiiiAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MidiiiiiAudioProcessor& processor;

	void sliderValueChanged(Slider* slider) override; // [3

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

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiiiiiAudioProcessorEditor)
};
