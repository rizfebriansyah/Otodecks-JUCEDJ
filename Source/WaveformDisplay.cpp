/*
  ==============================================================================

    WaveformDisplay.cpp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(int _id,
                                 juce::AudioFormatManager & formatManagerToUse,
                                 juce::AudioThumbnailCache &  cacheToUse) :
                                 audioThumb(1000, formatManagerToUse, cacheToUse),
                                 fileLoaded(false),
                                 position(0), id(_id)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    audioThumb.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
    
    g.setFont(20.0f);
    g.setColour (juce::Colours::darkorange); //deck label colour
    g.drawText(" Deck: " + std::to_string(id), getLocalBounds(),
              juce::Justification::centredTop, true);

    g.setColour (juce::Colours::lightgrey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::seagreen); // wavelength colour
    
    if(fileLoaded)
    {
        audioThumb.drawChannel(g,
                               getLocalBounds(),
                               0,
                               audioThumb.getTotalLength(),
                               0,
                               1.0f
                               );
        g.setColour(juce::Colours::white); //file title colour
        g.setFont (20.0f);
        g.drawText(fileTitle, getLocalBounds(),
                juce::Justification::bottomRight, true);
        
        g.setColour(juce::Colours::darkviolet); // playhead wavelength box colour
        g.drawRect(position * getWidth(), 0, getWidth() / 20, getHeight());
    }
    else
    {
        g.setFont (25.0f);
        g.setColour (juce::Colours::steelblue); // filenotloaded text colour
        g.drawText ("File not loaded...", getLocalBounds(),
                    juce::Justification::centred, true);   // draw some placeholder text
    }

}

void WaveformDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void WaveformDisplay::loadURL(juce::URL audioURL)
{
    
    audioThumb.clear();
    fileLoaded = audioThumb.setSource(new juce::URLInputSource(audioURL));
    if (fileLoaded)
    {
        std::cout << "WaveformDisplay:: loaded! " << std::endl;
        fileTitle = audioURL.getFileName();
        repaint();
    }
    else {
        std::cout << "WaveformDisplay:: not loaded! " << std::endl;
    }
}

void WaveformDisplay::changeListenerCallback(juce::ChangeBroadcaster *source)
{
    std::cout << "WaveformDisplay:: change received! " << std::endl;
    repaint();

}

void WaveformDisplay::setPositionRelative(double pos)
{
    if (pos != position)
    {
        position = pos;
        repaint();
    }
    
}
