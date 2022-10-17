/*
  ==============================================================================

    songName.h

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class songName
{
    public:
        songName(juce::File _file);
        juce::URL URL;
        juce::File file;
        juce::String title;
        juce::String length;
        
    bool operator == (const juce::String& other) const;

};
