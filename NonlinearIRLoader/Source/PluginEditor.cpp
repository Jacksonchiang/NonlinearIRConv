#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NonlinearIRLoaderAudioProcessorEditor::NonlinearIRLoaderAudioProcessorEditor (NonlinearIRLoaderAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (400, 200);
    addAndMakeVisible(loadFileButton);
    loadFileButton.addListener(this);
}

NonlinearIRLoaderAudioProcessorEditor::~NonlinearIRLoaderAudioProcessorEditor()
{
    loadFileButton.removeListener(this);
}

void NonlinearIRLoaderAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
    g.setColour (juce::Colours::white);
    g.setFont (20.0f);
    g.drawFittedText ("Load IR File", getLocalBounds(), juce::Justification::centred, 1);
}

void NonlinearIRLoaderAudioProcessorEditor::resized()
{
    loadFileButton.setBounds (getLocalBounds().reduced(50));
}

void NonlinearIRLoaderAudioProcessorEditor::buttonClicked(juce::Button* button)
{
    if (button == &loadFileButton)
    {
        // 使用 std::make_unique 建立 FileChooser 實例，並設置過濾器僅允許 .wav 檔案
        fileChooser = std::make_unique<juce::FileChooser>(
            "Choose IR File",            // 文件選擇器標題
            juce::File(),                // 起始目錄（默認為空）
            "*.wav"                      // 只允許 .wav 檔案
        );

        auto fileChooserFlags = juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles;

        // 啟動文件選擇器（非同步）
        fileChooser->launchAsync(fileChooserFlags, [this](const juce::FileChooser& chooser)
        {
            auto selectedFile = chooser.getResult();
            
            // 檢查選擇的檔案是否存在且為 .wav 檔案
            if (selectedFile.existsAsFile())
            {
                audioProcessor.loadFile(selectedFile);
                DBG("File loaded: " + selectedFile.getFullPathName());
            }
            else
            {
                DBG("Invalid file selected. Please select a .wav file.");
            }
        });
    }
}


