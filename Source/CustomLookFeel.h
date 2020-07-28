/*
  ==============================================================================

    CustomLookFeel.h
    Created: 28 Jul 2020 5:52:25pm
    Author:  Dean Townshend

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class CustLookFeel : public juce::LookAndFeel_V4
{
public:
    CustLookFeel()
    {
        setColour (juce::Slider::thumbColourId, juce::Colours::red);
    }

    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override
    {
        auto radius = (float) juce::jmin (width / 2, height / 2) - 4.0f;
        auto centreX = (float) x + (float) width  * 0.5f;
        auto centreY = (float) y + (float) height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

        //Inner fill
        g.setColour (juce::Colours::lightslategrey);
        g.fillEllipse (rx, ry, rw, rw);

        //Outline
        g.setColour (juce::Colours::darkslategrey);
        g.drawEllipse (rx, ry, rw, rw, 1.5f);

        juce::Path p;
        auto pointerLength = radius * 0.33f;
        auto pointerThickness = 2.5f;
        p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.applyTransform (juce::AffineTransform::rotation (angle).translated (centreX, centreY));

        // pointer
        g.setColour (juce::Colours::black);
        g.fillPath (p);
    }
};