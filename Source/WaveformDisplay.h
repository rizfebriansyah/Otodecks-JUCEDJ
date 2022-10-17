/*
  ==============================================================================

    WaveformDisplay.h

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDisplay  : public juce::Component,
                         public juce::ChangeListener
{
public:
    WaveformDisplay(int _id,
                    juce::AudioFormatManager & formatManagerToUse,
                    juce::AudioThumbnailCache &  cacheToUse);
    
    ~WaveformDisplay();

    void paint (juce::Graphics&) override;
    void resized() override;
    
    void changeListenerCallback(juce::ChangeBroadcaster *source) override;
    
    void loadURL(juce::URL audioURL);
    
    // set the relative position of playhead
    void setPositionRelative(double pos);
    

private:
    juce::AudioThumbnail audioThumb;
    juce::String fileTitle;
    bool fileLoaded;
    int id;
    double position;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
