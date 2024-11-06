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
    
    // load IR Button
    juce::TextButton loadFileButton;
    // load IR Label
    juce::Label loadFileLabel;
    // IR name Display
    juce::Label irNameDisplay;
    //juce::FileChooser fChooser{"Select a plugin..."};
    std::unique_ptr<juce::FileChooser> fileChooser;
    // Nonlinear Control
    juce::Slider nonlinearControl;
    juce::Label nonsliderLabel;
    // Volume Control
    juce::Slider volumeControl;
    juce::Label volumeLabel;
    // Volume Control
    juce::Slider panControl;
    juce::Label panLabel;
    // EQ Control
    juce::Slider eqControl;
    juce::Label eqLabel;
    
    juce::Rectangle<int> borderRect; // 用於包圍滑桿的邊框矩形


    

    
   

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NonlinearIRLoaderAudioProcessorEditor)
};
