/*
  ==============================================================================

    PlaylistComponent.h

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "DeckGUI.h"

#include "DJAudioPlayer.h"

#include <vector>

#include <string>

#include "songName.h"

#include <fstream>

//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component,
public juce::TableListBoxModel,
public juce::Button::Listener,
public juce::TextEditor::Listener
{
public:
    PlaylistComponent(DeckGUI* _deckGUI1, DeckGUI* _deckGUI2
                      );
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
    int getNumRows() override;
    
    void paintRowBackground(juce::Graphics &,
                            int rowNumber,
                            int width,
                            int height,
                            bool rowIsSelected) override;
    
    void paintCell (juce::Graphics &,
                            int rowNumber,
                            int columnId,
                            int width,
                            int height,
                            bool rowIsSelected) override;
    
    Component* refreshComponentForCell (int rowNumber,
                                       int ColumnId,
                                       bool isRowSelected,
                                        Component *existingComponentToUpdate) override;
    
    void buttonClicked(juce::Button* button) override;

private:
    
    juce::TableListBox songsLibrary;
    
    std::vector<songName> songs;
    
    
    juce::TextButton addToDeck1Button{ "Add to Deck: 1" };
    juce::TextButton addToDeck2Button{ "Add to Deck: 2" };
    juce::TextButton importButton{ "Import New Songs" };
    juce::TextEditor searchBox;
    
    DeckGUI* deckGUI1;
    DeckGUI* deckGUI2;
    
    void importToSongsLibrary();
    void searchSongsLibrary(juce::String searchForText);
    void saveSongsToLibrary();
    void loadSongsFromLibrary();
    void removeSongsFromLibrary(int id);
    bool isInSongs(juce::String songNameWithoutExtension);
    int whereInSongs(juce::String searchForText);
    void loadInPlayer(DeckGUI* deckGUI);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
