#pragma once 

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MIDICAudioProcessorEditor::MIDICAudioProcessorEditor(MIDIControllerAudioProcessor& p) :AudioProcessorEditor(&p), processor(p), keyboard(keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{
	setSize(600, 400);

	//Delay time slider
	delayTimeSlider.addListener(this);
	delayTimeSlider.setLookAndFeel(&custLookFeel);
	delayTimeSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	delayTimeSlider.setColour(Slider::textBoxTextColourId, Colours::black);
	delayTimeSlider.setColour(Slider::textBoxBackgroundColourId, Colours::slategrey);
	delayTimeSlider.setColour(Slider::textBoxOutlineColourId, Colours::darkslategrey);
	delayTimeSlider.setRange(0, 254, 1);
	delayTimeSlider.setValue(0);
	//Delay time label
	delayTimeSliderLabel.setText("Delay Time", dontSendNotification);
	delayTimeSliderLabel.setColour(Label::textColourId, Colours::darkslategrey);

	//vari pitch slider
	variPitchSlider.addListener(this);
	variPitchSlider.setLookAndFeel(&custLookFeel);
	variPitchSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	variPitchSlider.setColour(Slider::textBoxTextColourId, Colours::black);
	variPitchSlider.setColour(Slider::textBoxBackgroundColourId, Colours::slategrey);
	variPitchSlider.setColour(Slider::textBoxOutlineColourId, Colours::darkslategrey);
	variPitchSlider.setRange(0, 127, 1);
	variPitchSlider.setValue(0);
	//vari pitch slider label
	variPitchSliderLabel.setText("Varipitch", dontSendNotification);
	variPitchSliderLabel.setColour(Label::textColourId, Colours::darkslategrey);

	//Tuning slider
	tuningSlider.addListener(this);
	tuningSlider.setLookAndFeel(&custLookFeel);
	tuningSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
	tuningSlider.setColour(Slider::textBoxTextColourId, Colours::black);
	tuningSlider.setColour(Slider::textBoxBackgroundColourId, Colours::slategrey);
	tuningSlider.setColour(Slider::textBoxOutlineColourId, Colours::darkslategrey);
	tuningSlider.setRange(0, 254, 1);
	tuningSlider.setValue(processor.noteVals[processor.noteSelected]);
	//Tuning slider label
	tuningSliderLabel.setText("Tune", dontSendNotification);
	tuningSliderLabel.setColour(Label::textColourId, Colours::darkslategrey);

	//Note selector combo box
	noteSelector.setColour(ComboBox::backgroundColourId, Colours::slategrey);
	noteSelector.setColour(ComboBox::buttonColourId, Colours::slategrey);

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

	noteSelector.onChange = [this] { noteSelectorChanged(); };
	noteSelector.setSelectedId(1);

	//Mode selector combo box
	addAndMakeVisible(&modeSelector);
	modeSelector.setColour(ComboBox::backgroundColourId, Colours::slategrey);
	modeSelector.setColour(ComboBox::buttonColourId, Colours::slategrey);
	modeSelector.setColour(PopupMenu::backgroundColourId, Colours::slategrey);
	modeSelector.setColour(PopupMenu::highlightedBackgroundColourId, Colours::slategrey);
	
	modeSelector.addItem("Delay", 1);
	modeSelector.addItem("Tuning", 2);
	modeSelector.addItem("Synth", 3);

	modeSelector.onChange = [this] { modeSelectorChanged(); };
	modeSelector.setSelectedId(processor.currentMode);

	//Note test button
	noteTestButton.addListener(this);
	noteTestButton.setColour(TextButton::buttonColourId, Colours::slategrey);
	noteTestButton.setColour(TextButton::textColourOffId, Colours::black);
	noteTestButton.setButtonText("Play Note");

	//Note reset button
	noteResetButton.addListener(this);
	noteResetButton.setColour(TextButton::buttonColourId, Colours::slategrey);
	noteResetButton.setColour(TextButton::textColourOffId, Colours::black);
	noteResetButton.setButtonText("Defualt Pitch");
}

MIDICAudioProcessorEditor::~MIDICAudioProcessorEditor()
{
}

//==============================================================================
void MIDICAudioProcessorEditor::paint(Graphics& g)
{
	g.fillAll(Colours::lightgrey);

}

void MIDICAudioProcessorEditor::resized()
{
	Rectangle<int> area = getLocalBounds();
	Rectangle<int> guiArea = area;

	Rectangle<int> modeSelectorArea = guiArea.removeFromTop(guiArea.getHeight() * 0.1);
	modeSelector.setBounds(modeSelectorArea);

	Rectangle<int> sliderArea = guiArea;

	if (processor.currentMode == 1)
	{
		removeChildComponent(&keyboard);
		removeChildComponent(&tuningSlider);
		removeChildComponent(&tuningSliderLabel);
		removeChildComponent(&noteSelector);
		removeChildComponent(&noteTestButton);
		removeChildComponent(&noteResetButton);
		addAndMakeVisible(delayTimeSlider);
		addAndMakeVisible(delayTimeSliderLabel);
		addAndMakeVisible(variPitchSlider);
		addAndMakeVisible(variPitchSliderLabel);

		int sliderAreaWidthPerElem = sliderArea.getWidth() / 2;

		Rectangle<int> delayTimeArea = sliderArea.removeFromLeft(sliderAreaWidthPerElem);
		Rectangle<int> delayTimeSliderArea = delayTimeArea.removeFromBottom(delayTimeArea.getHeight() * 0.9);
		Rectangle<int> delayTimerSliderVal = delayTimeSliderArea.removeFromBottom(delayTimeSliderArea.getHeight() / 10);
		Rectangle<int> delayLabel = delayTimeArea;

		Rectangle<int> variPitchArea = sliderArea.removeFromLeft(sliderAreaWidthPerElem);
		Rectangle<int> variPitchSliderArea = variPitchArea.removeFromBottom(variPitchArea.getHeight() * 0.9);
		Rectangle<int> variPitchSliderVal = variPitchSliderArea.removeFromBottom(variPitchSliderArea.getHeight() / 10);
		Rectangle<int> variPitchLabel = variPitchArea;

		delayTimeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, delayTimerSliderVal.getWidth(), delayTimerSliderVal.getHeight());
		variPitchSlider.setTextBoxStyle(Slider::TextBoxBelow, false, variPitchSliderVal.getWidth(), variPitchSliderVal.getHeight());

		//Set bounds from areas
		delayTimeSlider.setBounds(delayTimeSliderArea);
		delayTimeSliderLabel.setBounds(delayTimeArea);
		variPitchSlider.setBounds(variPitchSliderArea);
		variPitchSliderLabel.setBounds(variPitchArea);

		delayTimeSliderLabel.setJustificationType(Justification::centred);
		variPitchSliderLabel.setJustificationType(Justification::centred);
	}
	else if (processor.currentMode == 2)
	{
		removeChildComponent(&delayTimeSlider);
		removeChildComponent(&delayTimeSliderLabel);
		removeChildComponent(&variPitchSlider);
		removeChildComponent(&variPitchSliderLabel);
		removeChildComponent(&keyboard);

		addAndMakeVisible(tuningSlider);
		addAndMakeVisible(tuningSliderLabel);
		addAndMakeVisible(noteSelector);

		addAndMakeVisible(noteTestButton);
		addAndMakeVisible(noteResetButton);

		Rectangle<int> tuningArea = sliderArea;

		Rectangle<int> labels = tuningArea.removeFromTop(tuningArea.getHeight() * 0.1);

		Rectangle<int> tuningLabel = labels.removeFromLeft(tuningArea.getWidth() / 2);
		tuningSliderLabel.setBounds(tuningLabel);

		Rectangle<int> tuningComboBox = labels;
		noteSelector.setBounds(tuningComboBox);

		Rectangle<int> tuningSliderArea = tuningArea.removeFromTop(tuningArea.getHeight() * 0.9);
		Rectangle<int> tuningSliderVal = tuningSliderArea.removeFromTop(tuningSliderArea.getHeight() * 0.1);

		tuningSlider.setBounds(tuningSliderArea);

		Rectangle<int> noteTestButtonArea = tuningArea.removeFromLeft(tuningArea.getWidth() / 2);
		noteTestButton.setBounds(noteTestButtonArea);
		noteResetButton.setBounds(tuningArea);

		tuningSlider.setTextBoxStyle(Slider::TextBoxBelow, false, tuningSliderVal.getWidth(), tuningSliderVal.getHeight());

		//noteSelector.setBounds(tuningComboBox);
		tuningSliderLabel.setJustificationType(Justification::centred);
	}
	else if (processor.currentMode == 3)
	{
		removeChildComponent(&tuningSlider);
		removeChildComponent(&tuningSliderLabel);
		removeChildComponent(&noteSelector);
		removeChildComponent(&delayTimeSlider);
		removeChildComponent(&delayTimeSliderLabel);
		removeChildComponent(&variPitchSlider);
		removeChildComponent(&variPitchSliderLabel);
		removeChildComponent(&noteTestButton);
		removeChildComponent(&noteResetButton);

		addAndMakeVisible(keyboard);

		Rectangle<int> keyboardArea = sliderArea.removeFromTop(sliderArea.getHeight() / 2);

		keyboard.setBounds(keyboardArea);
	}

}

void MIDICAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
	if (slider == &delayTimeSlider)
	{
		if (delayTimeSlider.getValue() >= 0 && delayTimeSlider.getValue() <= 127)
			processor.ccVal0 = delayTimeSlider.getValue();

		else if (delayTimeSlider.getValue() >= 128 && delayTimeSlider.getValue() <= 255)
			processor.ccVal1 = delayTimeSlider.getValue();
	}
	else if (slider == &variPitchSlider)
	{
		processor.ccVal2 = variPitchSlider.getValue();
	}

	else if (slider == &tuningSlider)
	{
		//processor.ccVal3 = tuningSlider.getValue();
		processor.noteVals[processor.noteSelected-1] = tuningSlider.getValue();

		if (tuningSlider.getValue() >= 0 && tuningSlider.getValue() <= 127)
			processor.ccVal3 = tuningSlider.getValue();

		else if (tuningSlider.getValue() >= 128 && tuningSlider.getValue() <= 255)
			processor.ccVal4 = tuningSlider.getValue();

	}
}

void MIDICAudioProcessorEditor::noteSelectorChanged()
{
	DBG("Tuning Note: ");
	DBG(noteSelector.getSelectedId() + 59);

	switch (noteSelector.getSelectedId())
	{
	case 1: processor.noteSelected = 1; 
		tuningSlider.setValue(processor.noteVals[0]);
		break;
	case 2: processor.noteSelected = 2; 
		tuningSlider.setValue(processor.noteVals[1]);
		break;
	case 3: processor.noteSelected = 3; 
		tuningSlider.setValue(processor.noteVals[2]);
		break;
	case 4: processor.noteSelected = 4; 
		tuningSlider.setValue(processor.noteVals[3]);
		break;
	case 5: processor.noteSelected = 5; 
		tuningSlider.setValue(processor.noteVals[4]);
		break;
	case 6: processor.noteSelected = 6; 
		tuningSlider.setValue(processor.noteVals[5]);
		break;
	case 7: processor.noteSelected = 7; 
		tuningSlider.setValue(processor.noteVals[6]);
		break;
	case 8: processor.noteSelected = 8; 
		tuningSlider.setValue(processor.noteVals[7]);
		break;
	case 9: processor.noteSelected = 9; 
		tuningSlider.setValue(processor.noteVals[8]);
		break;
	case 10: processor.noteSelected = 10; 
		tuningSlider.setValue(processor.noteVals[9]);
		break;
	case 11: processor.noteSelected = 11; 
		tuningSlider.setValue(processor.noteVals[10]);
		break;
	case 12: processor.noteSelected = 12; 
		tuningSlider.setValue(processor.noteVals[11]);
		break;
	case 13: processor.noteSelected = 13; 
		tuningSlider.setValue(processor.noteVals[12]);
		break;
	default: break;
	}
}

void MIDICAudioProcessorEditor::modeSelectorChanged()
{

	if (modeSelector.getSelectedId() == 1)
	{
		processor.currentMode = 1;
		resized();
		DBG("Changed To Delay Mode");
	}
	else if (modeSelector.getSelectedId() == 2)
	{
		processor.currentMode = 2;
		resized();
		DBG("Changed To Tuning Mode");
	}
	else if (modeSelector.getSelectedId() == 3)
	{
		processor.currentMode = 3;
		resized();
		DBG("Changed To Synth Mode");
	}
}

void MIDICAudioProcessorEditor::buttonClicked(Button* button)
{
	if (button = &noteTestButton)
	{
		processor.notePlay = true;
		DBG("Playing Current Note");
	}
	if (button = &noteResetButton)
	{
		processor.noteReset = true;
		DBG("Current Note Tuning Reset");
	}
}
