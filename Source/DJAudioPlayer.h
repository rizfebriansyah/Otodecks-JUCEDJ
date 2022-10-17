/*
  ==============================================================================

    DJAudioPlayer.h

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class DJAudioPlayer : public juce::AudioSource {
public:
    
    DJAudioPlayer(juce::AudioFormatManager& _formatManager);
    ~DJAudioPlayer();
  
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    
    //loads audio file
    void loadURL(juce::URL audioURL);
    
    //adjusts the volume of audio file
    void setGain(double gain);
    
    //adjusts the speed of audio file
    void setSpeed(double ratio);
    
    //obtains relative position of audio file
    void setPositionRelative(double pos);
    
    //starts playing the selected audio file
    void start();
    
    //stops playing the selected audio file
    void stop();
    
    //obtains the relative position of playhead
    double getPositionRelative();
    
    //obtains the length of transportsource in seconds
    double getLengthInSeconds();
    
    //adjusts the poisiton of audio file
    void setPosition(double posInSecs);
    
private:
    
    juce::AudioFormatManager& formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    
    juce::AudioTransportSource transportSource;
    
    juce::ResamplingAudioSource resampleSource{&transportSource, false, 2};
    
    
};
