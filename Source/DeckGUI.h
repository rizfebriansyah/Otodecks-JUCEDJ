/*
  ==============================================================================

    DeckGUI.h

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "DJAudioPlayer.h"

#include "WaveformDisplay.h"

//==============================================================================
/*
*/
class DeckGUI  : public juce::Component, public juce::Button::Listener, public juce::Slider::Listener, public juce::FileDragAndDropTarget,
                 public juce::Timer
{
public:
    DeckGUI(int _id,
            DJAudioPlayer* player,
            juce::AudioFormatManager & formatManagerToUse,
            juce::AudioThumbnailCache &  cacheToUse);
    ~DeckGUI() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    // implement Button::Listener
    void buttonClicked (juce::Button *) override;
    
    // implement Slider::Listener
    void sliderValueChanged (juce::Slider *slider) override;
    
    // examine if song file has been dragged
    bool isInterestedInFileDrag(const juce::StringArray &files) override;
    
    // examine if song file has been dropped
    void filesDropped(const juce::StringArray &files, int x, int y) override;
    
    // examine for changes on waveform
    void timerCallback() override;
    
private:
    
    juce::TextButton playButton{"PLAY"};
    juce::TextButton stopButton{"STOP"};
    juce::TextButton loadButton{"LOAD"};
    
    juce::Label volName;
    juce::Slider volSlider;
    juce::Label speedName;
    juce::Slider speedSlider;
    juce::Label posName;
    juce::Slider posSlider;
    
    friend class PlaylistComponent;

    DJAudioPlayer* player;
    
    WaveformDisplay waveformDisplay;
    
    void loadFiles(juce::URL audioFileURL);
    
    int id;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
