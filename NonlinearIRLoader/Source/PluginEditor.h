/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class NonlinearIRLoaderAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                               public juce::Button::Listener//,public juce::Slider::Listener
{
public:
    NonlinearIRLoaderAudioProcessorEditor (NonlinearIRLoaderAudioProcessor&);
    ~NonlinearIRLoaderAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void buttonClicked(juce::Button* button) override;


private:
    
    NonlinearIRLoaderAudioProcessor& audioProcessor;
    
 
    // Load IR Button and Label
    juce::TextButton loadFileButton;
    juce::Label loadFileLabel;

    // IR Name Display
    juce::Label irNameDisplay;

    // File Chooser
    std::unique_ptr<juce::FileChooser> fileChooser;

    // Nonlinear Control
    juce::Slider nonlinearControl;
    juce::Label nonsliderLabel;
    juce::TextButton nonOnOffButton; // NonOnOff 按鈕

    // Volume Control
    juce::Slider volumeControl;
    juce::Label volumeLabel;

    // Pan Control
    juce::Slider panControl;
    juce::Label panLabel;

    // EQ Control
    juce::Slider eqControl;
    juce::Label eqLabel;

    // Border Rectangle
    juce::Rectangle<int> borderRect;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NonlinearIRLoaderAudioProcessorEditor)
};
