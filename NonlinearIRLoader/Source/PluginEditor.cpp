#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NonlinearIRLoaderAudioProcessorEditor::NonlinearIRLoaderAudioProcessorEditor (NonlinearIRLoaderAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // 設定視窗大小
    setSize(600, 400);

    // Load File Button
    addAndMakeVisible(loadFileButton);
    loadFileButton.addListener(this);

    // Load File Label
    loadFileLabel.setText("Load IR File...", juce::dontSendNotification);
    loadFileLabel.attachToComponent(&loadFileButton, false); // 標籤置於旋鈕上方
    addAndMakeVisible(loadFileLabel);

    // Nonlinear Control
    addAndMakeVisible(nonlinearControl);
    nonlinearControl.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    nonlinearControl.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 15); // 顯示數字框，寬 50 高 15

    // Nonlinear Control Label
    nonsliderLabel.setText("Nonlinear", juce::dontSendNotification);
    nonsliderLabel.setJustificationType(juce::Justification::centred); // 將文字置中
    nonsliderLabel.attachToComponent(&nonlinearControl, false);
    addAndMakeVisible(nonsliderLabel);

    // Volume Control
    addAndMakeVisible(volumeControl);
    volumeControl.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    volumeControl.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 15);

    // Volume Control Label
    volumeLabel.setText("Vol", juce::dontSendNotification);
    volumeLabel.setJustificationType(juce::Justification::centred);
    volumeLabel.attachToComponent(&volumeControl, false);
    addAndMakeVisible(volumeLabel);

    // NonOnOff Button
    addAndMakeVisible(nonOnOffButton);
    nonOnOffButton.setButtonText("On/Off");
    nonOnOffButton.addListener(this);
    nonOnOffButton.setClickingTogglesState(true);

    // 設置顏色：普通狀態和按下狀態
    nonOnOffButton.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);        // 普通狀態顏色
    nonOnOffButton.setColour(juce::TextButton::buttonOnColourId, juce::Colours::green);      // 按下狀態顏色

    // Pan Control
    addAndMakeVisible(panControl);
    panControl.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    panControl.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 15);

    // Pan Control Label
    panLabel.setText("Pan", juce::dontSendNotification);
    panLabel.setJustificationType(juce::Justification::centred);
    panLabel.attachToComponent(&panControl, false);
    addAndMakeVisible(panLabel);

    // EQ Control
    addAndMakeVisible(eqControl);
    eqControl.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    eqControl.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 15);

    // EQ Control Label
    eqLabel.setText("EQ", juce::dontSendNotification);
    eqLabel.setJustificationType(juce::Justification::centred);
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
    
    int buttonWidth = 350;
    int buttonHeight = 25;
    int x = (getWidth() - buttonWidth) / 2;
    int y = (getHeight() - buttonHeight) / 1.3;
    loadFileButton.setBounds(x, y, buttonWidth, buttonHeight);
    
    int sliderWidth = 75;
    int sliderHeight = 75;
    int spacing = 20;

    int totalWidth = (sliderWidth * 4) + (spacing * 3);
    int startX = (getWidth() - totalWidth) / 2;
    int startY = 160;

    // NonOnOff 按鈕放置於 Nonlinear 旋鈕的上方
    nonOnOffButton.setBounds(startX + (sliderWidth / 2) - 40, startY - 50, 80, 25); // 調整按鈕大小與位置

    // 佈局旋鈕
    nonlinearControl.setBounds(startX, startY, sliderWidth, sliderHeight);
    volumeControl.setBounds(startX + (sliderWidth + spacing), startY, sliderWidth, sliderHeight);
    panControl.setBounds(startX + 2 * (sliderWidth + spacing), startY, sliderWidth, sliderHeight);
    eqControl.setBounds(startX + 3 * (sliderWidth + spacing), startY, sliderWidth, sliderHeight);

    // 調整外框邊界以包住所有旋鈕和按鈕
    borderRect.setBounds(startX - 10, startY - 60, totalWidth + 20, sliderHeight + 90);
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



