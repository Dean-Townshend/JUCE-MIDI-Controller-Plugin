#pragma once 

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MidiiiiiAudioProcessorEditor::MidiiiiiAudioProcessorEditor (MidiiiiiAudioProcessor& p) :AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

	//Delay time slider
	delayTimeSlider.addListener(this);
	delayTimeSlider.setSliderStyle(Slider::LinearBarVertical);
	delayTimeSlider.setRange(0, 127, 1);
	delayTimeSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	delayTimeSlider.setPopupDisplayEnabled(true, false, this);
	delayTimeSlider.setTextValueSuffix(" S");
	delayTimeSlider.setValue(0);

	//Delay time label
	delayTimeSliderLabel.setText("Delay Time", dontSendNotification);
	delayTimeSliderLabel.setColour(Label::textColourId, Colours::darkslategrey);

	//vari pitch slider
	variPitchSlider.addListener(this);
	variPitchSlider.setSliderStyle(Slider::LinearBarVertical);
	variPitchSlider.setRange(0, 127, 1);
	variPitchSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	variPitchSlider.setPopupDisplayEnabled(true, false, this);
	//tuningSlider.setTextValueSuffix(" ");
	variPitchSlider.setValue(0);

	//vari pitch slider label
	variPitchSliderLabel.setText("Varipitch", dontSendNotification);
	variPitchSliderLabel.setColour(Label::textColourId, Colours::darkslategrey);

	//Tuning slider
	tuningSlider.addListener(this);
	tuningSlider.setSliderStyle(Slider::LinearBarVertical);
	tuningSlider.setRange(0, 127, 1);
	tuningSlider.setTextBoxStyle(Slider::NoTextBox, false, 90, 0);
	tuningSlider.setPopupDisplayEnabled(true, false, this);
	//tuningSlider.setTextValueSuffix(" ");
	tuningSlider.setValue(0);

	//Tuning slider label
	tuningSliderLabel.setText("Tune", dontSendNotification);
	tuningSliderLabel.setColour(Label::textColourId, Colours::darkslategrey);

	// this function adds the slider to the editor
	addAndMakeVisible(&delayTimeSlider);
	addAndMakeVisible(delayTimeSliderLabel);
	addAndMakeVisible(&variPitchSlider);
	addAndMakeVisible(variPitchSliderLabel);
	addAndMakeVisible(&tuningSlider);
	addAndMakeVisible(tuningSliderLabel);
	
}

MidiiiiiAudioProcessorEditor::~MidiiiiiAudioProcessorEditor()
{
}

//==============================================================================
void MidiiiiiAudioProcessorEditor::paint (Graphics& g)
{
	// fill the whole window white
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
	Rectangle<int> delayTimerSliderArea = delayTimeArea.removeFromTop(sliderArea.getHeight() * 0.8);
	Rectangle<int> delayLabel = delayTimeArea;

	Rectangle<int> variPitchArea = sliderArea.removeFromLeft(sliderAreaWidthPerElem);
	Rectangle<int> variPitchSliderArea = variPitchArea.removeFromTop(variPitchArea.getHeight() * 0.8);
	Rectangle<int> variPitchLabel = variPitchArea;

	Rectangle<int> tuningArea = sliderArea.removeFromLeft(sliderAreaWidthPerElem);
	Rectangle<int> tuningSliderArea = tuningArea.removeFromTop(tuningArea.getHeight() * 0.8);
	Rectangle<int> tuningLabel = tuningArea;

	//Set bounds from areas
	delayTimeSlider.setBounds(delayTimerSliderArea);
	delayTimeSliderLabel.setBounds(delayTimeArea);
	variPitchSlider.setBounds(variPitchSliderArea);
	variPitchSliderLabel.setBounds(variPitchArea);
	tuningSlider.setBounds(tuningSliderArea);
	tuningSliderLabel.setBounds(tuningArea);
}

void MidiiiiiAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
	processor.noteOnVel = delayTimeSlider.getValue();
	processor.myVal = delayTimeSlider.getValue();
}
