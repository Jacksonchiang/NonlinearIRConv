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
                                               public juce::Button::Listener
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
    //juce::FileChooser fChooser{"Select a plugin..."};
    std::unique_ptr<juce::FileChooser> fileChooser;

    
   

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NonlinearIRLoaderAudioProcessorEditor)
};
