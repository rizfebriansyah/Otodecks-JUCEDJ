/*
  ==============================================================================

    songName.cpp

  ==============================================================================
*/

#include "songName.h"
#include <filesystem>

songName::songName(juce::File _file) : file(_file),
                                 title(_file.getFileNameWithoutExtension()),
                                 URL(juce::URL{ _file })
{
    std::cout << "Created new track with title: " << title << std::endl;
}

bool songName::operator == (const juce::String& other) const
{
    return title == other;
}
