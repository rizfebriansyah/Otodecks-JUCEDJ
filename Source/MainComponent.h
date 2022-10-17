#pragma once

#include <JuceHeader.h>

#include "DJAudioPlayer.h"

#include "DeckGUI.h"

#include "PlaylistComponent.h"
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/

class OtherLookAndFeel : public juce::LookAndFeel_V4
{
public:
    OtherLookAndFeel()
    {
        setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::blanchedalmond);
        setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::sandybrown);
        setColour(juce::Slider::thumbColourId, juce::Colours::red);

    }
};

class MainComponent  : public juce::AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;
    
private:
    //==============================================================================
    // Your private member variables go here...
    
    juce::AudioFormatManager formatManager;
    juce::AudioThumbnailCache thumbCache{100};
    
    DJAudioPlayer player1{formatManager};
    DeckGUI deckGUI1{1, &player1, formatManager, thumbCache};
    
    DJAudioPlayer player2{formatManager};
    DeckGUI deckGUI2{2, &player2, formatManager, thumbCache};

    juce::MixerAudioSource mixerSource;
    
    PlaylistComponent playlistComponent{ &deckGUI1, &deckGUI2 };

    OtherLookAndFeel otherLookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
