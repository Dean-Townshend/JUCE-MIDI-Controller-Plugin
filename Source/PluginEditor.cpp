#pragma once 

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MidiiiiiAudioProcessorEditor::MidiiiiiAudioProcessorEditor (MidiiiiiAudioProcessor& p) :AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 400);

	//Delay time slider
	delayTimeSlider.addListener(this);
	delayTimeSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	delayTimeSlider.setColour(Slider::thumbColourId, Colours::darkslategrey);
	delayTimeSlider.setColour(Slider::textBoxTextColourId, Colours::darkslategrey);
	delayTimeSlider.setRange(0, 127, 1);
	delayTimeSlider.setTextValueSuffix(" S");
	delayTimeSlider.setValue(0);

	//Delay time label
	delayTimeSliderLabel.setText("Delay Time", dontSendNotification);
	delayTimeSliderLabel.setColour(Label::textColourId, Colours::darkslategrey);

	//vari pitch slider
	variPitchSlider.addListener(this);
	variPitchSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	variPitchSlider.setColour(Slider::thumbColourId, Colours::darkslategrey);
	variPitchSlider.setColour(Slider::textBoxTextColourId, Colours::darkslategrey);
	variPitchSlider.setRange(0, 127, 1);
	//tuningSlider.setTextValueSuffix(" ");
	variPitchSlider.setValue(0);

	//vari pitch slider label
	variPitchSliderLabel.setText("Varipitch", dontSendNotification);
	variPitchSliderLabel.setColour(Label::textColourId, Colours::darkslategrey);

	//Tuning slider
	tuningSlider.addListener(this);
	tuningSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	tuningSlider.setColour(Slider::thumbColourId, Colours::darkslategrey);
	tuningSlider.setColour(Slider::textBoxTextColourId, Colours::darkslategrey);
	tuningSlider.setRange(0, 127, 1);
	//tuningSlider.setTextValueSuffix(" ");
	tuningSlider.setValue(0);

	//Tuning slider label
	tuningSliderLabel.setText("Tune", dontSendNotification);
	tuningSliderLabel.setColour(Label::textColourId, Colours::darkslategrey);

	//Note selector combo box
	addAndMakeVisible(noteSelector);
	noteSelector.addItem("C4", 1);
	noteSelector.addItem("C#", 2);
	noteSelector.addItem("D", 3);
	noteSelector.addItem("D#", 4);
	noteSelector.addItem("E", 5);
	noteSelector.addItem("F", 6);
	noteSelector.addItem("F#", 7);
	noteSelector.addItem("G", 8);
	noteSelector.addItem("G#", 9);
	noteSelector.addItem("A", 10);
	noteSelector.addItem("A#", 11);
	noteSelector.addItem("B", 12);
	noteSelector.addItem("C5", 13);

	//noteSelector.onChange = [this] { noteSelectorChanged(); };
	noteSelector.setSelectedId(1);

	// this function adds the slider to the editor
	addAndMakeVisible(&delayTimeSlider);
	addAndMakeVisible(&delayTimeSliderLabel);
	addAndMakeVisible(&variPitchSlider);
	addAndMakeVisible(&variPitchSliderLabel);
	addAndMakeVisible(&tuningSlider);
	addAndMakeVisible(&tuningSliderLabel);
	
}

MidiiiiiAudioProcessorEditor::~MidiiiiiAudioProcessorEditor()
{
}

//==============================================================================
void MidiiiiiAudioProcessorEditor::paint (Graphics& g)
{
	g.fillAll(Colours::white);

}

void MidiiiiiAudioProcessorEditor::resized()
{
	Rectangle<int> area = getLocalBounds();
	Rectangle<int> guiArea = area;

	Rectangle<int> sliderArea = guiArea.removeFromTop(guiArea.getWidth()*0.8);
	Rectangle<int> buttonArea = guiArea;

	int sliderAreaWidthPerElem = sliderArea.getWidth() / 3;

	Rectangle<int> delayTimeArea = sliderArea.removeFromLeft(sliderAreaWidthPerElem);
	Rectangle<int> delayTimeSliderArea = delayTimeArea.removeFromBottom(delayTimeArea.getHeight() * 0.9);
	Rectangle<int> delayTimerSliderVal = delayTimeSliderArea.removeFromBottom(delayTimeSliderArea.getHeight()/10);
	Rectangle<int> delayLabel = delayTimeArea;

	Rectangle<int> variPitchArea = sliderArea.removeFromLeft(sliderAreaWidthPerElem);
	Rectangle<int> variPitchSliderArea = variPitchArea.removeFromBottom(variPitchArea.getHeight() * 0.9);
	Rectangle<int> variPitchSliderVal = variPitchSliderArea.removeFromBottom(variPitchSliderArea.getHeight() / 10);
	Rectangle<int> variPitchLabel = variPitchArea;

	Rectangle<int> tuningArea = sliderArea.removeFromLeft(sliderAreaWidthPerElem);
	Rectangle<int> tuningSliderArea = tuningArea.removeFromBottom(tuningArea.getHeight() * 0.9);
	Rectangle<int> tuningSliderVal = tuningSliderArea.removeFromBottom(tuningSliderArea.getHeight() / 10);
	Rectangle<int> tuningLabel = tuningArea.removeFromLeft(tuningArea.getWidth()/2);
	Rectangle<int> tuningComboBox = tuningArea;

	delayTimeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, delayTimerSliderVal.getWidth(), delayTimerSliderVal.getHeight());
	variPitchSlider.setTextBoxStyle(Slider::TextBoxBelow, false, variPitchSliderVal.getWidth(), variPitchSliderVal.getHeight());
	tuningSlider.setTextBoxStyle(Slider::TextBoxBelow, false, tuningSliderVal.getWidth(), tuningSliderVal.getHeight());

	//Set bounds from areas
	delayTimeSlider.setBounds(delayTimeSliderArea);
	delayTimeSliderLabel.setBounds(delayTimeArea);
	variPitchSlider.setBounds(variPitchSliderArea);

	variPitchSliderLabel.setBounds(variPitchArea);
	tuningSlider.setBounds(tuningSliderArea);
	tuningSliderLabel.setBounds(tuningLabel);
	noteSelector.setBounds(tuningComboBox);

	delayTimeSliderLabel.setJustificationType(Justification::centred);
	variPitchSliderLabel.setJustificationType(Justification::centred);
	tuningSliderLabel.setJustificationType(Justification::centred);
}

void MidiiiiiAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
	processor.noteOnVel = delayTimeSlider.getValue();
	processor.myVal = delayTimeSlider.getValue();
}
