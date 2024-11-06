#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NonlinearIRLoaderAudioProcessorEditor::NonlinearIRLoaderAudioProcessorEditor (NonlinearIRLoaderAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (600, 400);
    
    //loadFileButton
    addAndMakeVisible(loadFileButton);
    loadFileButton.addListener(this);
    
    // set loadFile Control Label
    loadFileLabel.setText("Load IR File...", juce::dontSendNotification);
    loadFileLabel.attachToComponent(&loadFileButton, false); // 標籤置於旋鈕上方
    addAndMakeVisible(loadFileLabel);
    
    
    
    // Nonlinear Control
    addAndMakeVisible(nonlinearControl);
    nonlinearControl.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    nonlinearControl.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 15); // 顯示數字框，寬 50 高 20
    // set Nonlinear Control Label
    nonsliderLabel.setText("Nonlinear", juce::dontSendNotification);
    nonsliderLabel.setJustificationType(juce::Justification::centred); // 將文字置中
    nonsliderLabel.attachToComponent(&nonlinearControl, false); // 標籤置於旋鈕上方
    addAndMakeVisible(nonsliderLabel);
    
    // Nonlinear Control
    addAndMakeVisible(volumeControl);
    volumeControl.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    volumeControl.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 15); // 顯示數字框，寬 50 高 20
    // set Nonlinear Control Label
    volumeLabel.setText("Vol", juce::dontSendNotification);
    volumeLabel.setJustificationType(juce::Justification::centred); // 將文字置中
    volumeLabel.attachToComponent(&volumeControl, false);
    addAndMakeVisible(volumeLabel);
    
    // Pan Control
    addAndMakeVisible(panControl);
    panControl.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    panControl.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 15); // 顯示數字框，寬 50 高 20
    // set Pan Control Label
    panLabel.setText("Pan", juce::dontSendNotification);
    panLabel.setJustificationType(juce::Justification::centred); // 將文字置中
    panLabel.attachToComponent(&panControl, false);
    addAndMakeVisible(panLabel);
    
    // eq Control
    addAndMakeVisible(eqControl);
    eqControl.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    eqControl.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 15); // 顯示數字框，寬 50 高 20
    // set eq Control Label
    eqLabel.setText("EQ", juce::dontSendNotification);
    eqLabel.setJustificationType(juce::Justification::centred); // 將文字置中
    eqLabel.attachToComponent(&eqControl, false);
    addAndMakeVisible(eqLabel);
    
    
    
    
    

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
    g.drawRect(borderRect, 1);

    //g.drawFittedText ("Load IR File", getLocalBounds(), juce::Justification::centred, 1);
}

void NonlinearIRLoaderAudioProcessorEditor::resized()
{
    
    // loadFileButton
    int buttonWidth = 350;
    int buttonHeight = 25;
    int x = (getWidth() - buttonWidth) / 2;  // 水平置中
    int y = (getHeight() - buttonHeight) /1.4; // 垂直置中
    loadFileButton.setBounds(x, y, buttonWidth, buttonHeight);
    
    // slider
    int sliderWidth = 75;
    int sliderHeight = 75;
    int numSliders = 4;
    int spacing = 20;

    int totalWidth = (sliderWidth * numSliders) + (spacing * (numSliders - 1));
    int startX = (getWidth() - totalWidth) / 2;
    int startY = 125;

    nonlinearControl.setBounds(startX, startY + 20, sliderWidth, sliderHeight);
    volumeControl.setBounds(startX + (sliderWidth + spacing), startY + 20, sliderWidth, sliderHeight);
    panControl.setBounds(startX + 2 * (sliderWidth + spacing), startY + 20, sliderWidth, sliderHeight);
    eqControl.setBounds(startX + 3 * (sliderWidth + spacing), startY + 20, sliderWidth, sliderHeight);

    // 增加邊框的上邊距，避免遮擋標籤
    borderRect.setBounds(startX - 10, startY - 10, totalWidth + 20, sliderHeight + 40); // 增加高度以適應標籤

    
    
    
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

                // 更新 loadFileButton 按鈕上的文字為檔案名稱
                //loadFileButton.setButtonText(selectedFile.getFileName());
                loadFileButton.setButtonText(selectedFile.getFileNameWithoutExtension());

            }
            else
            {
                DBG("Invalid file selected. Please select a .wav file.");
                loadFileButton.setButtonText("Invalid File. Please select a .wav file.");
            }
        });
    }
}



