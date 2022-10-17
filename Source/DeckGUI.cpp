/*
  ==============================================================================

    DeckGUI.cpp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(int _id,
                 DJAudioPlayer* _player,
                 juce::AudioFormatManager & formatManagerToUse,
                 juce::AudioThumbnailCache &  cacheToUse
                 ) : player (_player), id(_id),
                     waveformDisplay(_id, formatManagerToUse, cacheToUse)
{
    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(loadButton);
    
    // construct volume slider and volume name
    volSlider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    
    double defaultVolumeValue = 0.5;
    volSlider.setRange(0.0, 1.0);
    volSlider.setNumDecimalPlacesToDisplay(2);
    volSlider.setTextBoxStyle(juce::Slider::TextBoxBelow,
                                  false,
                                  200,
                                  volSlider.getTextBoxHeight()
                                 );
    volSlider.setSkewFactorFromMidPoint(defaultVolumeValue);
    volSlider.setValue(defaultVolumeValue);
    volName.setText("Volume: ", juce::dontSendNotification);
    volName.attachToComponent(&volSlider, false);
    
    
    // construct position slider and position name
    posSlider.setRange(0.0, 1.0);
    posSlider.setNumDecimalPlacesToDisplay(2);
    posSlider.setTextBoxStyle(juce::Slider::TextBoxLeft,
                                false,
                                50,
                                posSlider.getTextBoxHeight()
                                );
    posName.setText("Position: ", juce::dontSendNotification);
    posName.attachToComponent(&posSlider, true);
    
    //construct speed slider and speed name
    double defaultSpeedValue = 1.0;
    speedSlider.setRange(0.10, 5.0);
    speedSlider.setNumDecimalPlacesToDisplay(2);
    speedSlider.setTextBoxStyle(juce::Slider::TextBoxLeft,
                              false,
                              50,
                              speedSlider.getTextBoxHeight()
                             );
    speedSlider.setValue(defaultSpeedValue);
    speedSlider.setSkewFactorFromMidPoint(defaultSpeedValue);
    speedName.setText("Speed: ", juce::dontSendNotification);
    speedName.attachToComponent(&speedSlider, true);
    
    
    addAndMakeVisible(volName);
    addAndMakeVisible(volSlider);
    addAndMakeVisible(posName);
    addAndMakeVisible(posSlider);
    addAndMakeVisible(speedName);
    addAndMakeVisible(speedSlider);

    addAndMakeVisible(waveformDisplay);
    
    playButton.addListener(this);
    stopButton.addListener(this);
    loadButton.addListener(this);
    
    volSlider.addListener(this);
    posSlider.addListener(this);
    speedSlider.addListener(this);


    startTimer(500);

}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::whitesmoke);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    

//    g.setColour (juce::Colours::darkgreen);
//    g.setFont (14.0f);
//    g.drawText ("DeckGUI", getLocalBounds(),
//                juce::Justification::centred, true);   // draw some placeholder text
}

void DeckGUI::resized()
{
    
    double rowH = getHeight() / 8;
    double rowL = getWidth() / 2;

    playButton.setBounds(0, 0, rowL, rowH);

    stopButton.setBounds(rowL, 0, rowL, rowH);

    volSlider.setBounds(0, rowH * 2, rowL, rowH * 2.5);
    
    posSlider.setBounds(rowL, rowH * 2, rowL, rowH);

    speedSlider.setBounds(rowL, rowH * 3, rowL, rowH);
    
    waveformDisplay.setBounds(0, rowH * 5, getWidth(), rowH * 2);

    loadButton.setBounds(0, rowH * 7, getWidth(), rowH);

}

void DeckGUI::buttonClicked(juce::Button * button)
{
    if (button == &playButton)
    {
        std::cout << "DeckGUI::Play button was clicked" << std::endl;
        player->start();
    }
    if (button == &stopButton)
    {
        std::cout << "DeckGUI::Stop button was clicked" << std::endl;
        player->stop();
    }
    if (button == &loadButton)
    {
        std::cout << "DeckGUI::Load button was clicked" << std::endl;
        juce::FileChooser chooser{"Select a file..."};
        if (chooser.browseForFileToOpen())
        {
            loadFiles(juce::URL{chooser.getResult() });
            waveformDisplay.loadURL(juce::URL{chooser.getResult()});
        }
    }
}

void DeckGUI::sliderValueChanged (juce::Slider *slider)
{
    if (slider == &volSlider)
    {
        std::cout << "DeckGUI::Volume Slider Adjusted" << std::endl;
        player->setGain(slider->getValue());
    }

    if(slider == &speedSlider)
    {
        std::cout << "DeckGUI::Speed Slider Adjusted" << std::endl;
        player->setSpeed(slider->getValue());
    }

    if(slider == &posSlider)
    {
        std::cout << "DeckGUI::Position Slider Adjusted" << std::endl;
        player->setPositionRelative(slider->getValue());
    }
}

bool DeckGUI::isInterestedInFileDrag(const juce::StringArray &files)
{
    std::cout << "DeckGUI::isInterestedInFileDrag called. File has been dragged. " << std::endl;
    return true;
}

void DeckGUI::filesDropped (const juce::StringArray &files, int x, int y)
{
    std::cout << "DeckGUI::filesDropped" << std::endl;
    
    if(files.size() == 1)
    {
        loadFiles(juce::URL{ juce::File{files[0]} });
    }
}

void DeckGUI::timerCallback()
{
//    std::cout << "DeckGUI::timerCallback" << std::endl;
    if ( player -> getPositionRelative() > 0 )
    {
        waveformDisplay.setPositionRelative(
                                        player->getPositionRelative());
    }
}

void DeckGUI::loadFiles(juce::URL audioFileURL)
{
    std::cout << "DeckGUI::loadFiles called." << std::endl;
    player -> loadURL(audioFileURL);
    waveformDisplay.loadURL(audioFileURL);
}
