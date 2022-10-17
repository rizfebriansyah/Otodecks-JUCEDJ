/*
  ==============================================================================

    PlaylistComponent.cpp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent(DeckGUI* _deckGUI1, DeckGUI* _deckGUI2) : deckGUI1(_deckGUI1) ,deckGUI2(_deckGUI2)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
//    trackTitles.push_back("Track 1:");
//    trackTitles.push_back("Track 2:");
//    trackTitles.push_back("Track 3:");
//    trackTitles.push_back("Track 4:");
//    trackTitles.push_back("Track 5:");
//    trackTitles.push_back("Track 6:");
//
//
//    tableComponent.getHeader().addColumn("Track Title:", 0, 400);
//    tableComponent.getHeader().addColumn("", 1, 200);
//
//    
//    tableComponent.setModel(this);
    
    addAndMakeVisible(songsLibrary);
    
    addAndMakeVisible(searchBox);
    addAndMakeVisible(importButton);
    addAndMakeVisible(addToDeck1Button);
    addAndMakeVisible(addToDeck2Button);
    
    searchBox.addListener(this);
    importButton.addListener(this);
    addToDeck1Button.addListener(this);
    addToDeck2Button.addListener(this);
    
    // setting up the search Box
    searchBox.setTextToShowWhenEmpty("Search for Desired Song - Press Enter",
                                        juce::Colours::yellow);
    searchBox.onReturnKey = [this] { searchSongsLibrary (searchBox.getText()); };
     
    // setting up the songs Library with 3 columns
    songsLibrary.getHeader().addColumn("Songs", 1, 1);
    songsLibrary.getHeader().addColumn("Discard?", 2, 1);
    songsLibrary.getHeader().addColumn("Length", 3, 1);
    songsLibrary.setModel(this);
    loadSongsFromLibrary();

}

PlaylistComponent::~PlaylistComponent()
{
    //when you close the app
    saveSongsToLibrary();
}

void PlaylistComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    
    g.setColour (juce::Colours::salmon);
    g.setFont (15.0f);
    g.drawText ("PlaylistComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    
    importButton.setBounds(0, 0, getWidth(), 2 * getHeight() / 18);
    searchBox.setBounds(0, 2 * getHeight() / 18, getWidth(), getHeight()/18);
    songsLibrary.setBounds(0, 3 * getHeight() / 18, getWidth(), 15 * getHeight() / 18);
    addToDeck1Button.setBounds(0, 17 * getHeight() / 18, getWidth() / 2, getHeight() / 18);
    addToDeck2Button.setBounds(getWidth() / 2, 17 * getHeight() / 18, getWidth() / 2, getHeight() / 18);

    //construct columns
    songsLibrary.getHeader().setColumnWidth(1, 10 * getWidth() / 20);
    songsLibrary.getHeader().setColumnWidth(2, 4 * getWidth() / 18);
    songsLibrary.getHeader().setColumnWidth(3, 5 * getWidth() / 18);

}

int PlaylistComponent::getNumRows()
{
    return songs.size();
}

void PlaylistComponent::paintRowBackground(juce::Graphics & g,
                        int rowNumber,
                        int width,
                        int height,
                        bool rowIsSelected)
{
    if (rowIsSelected)
    {
        g.fillAll(juce::Colours::cyan);
    }
    else
    {
        g.fillAll(juce::Colours::slategrey);
    }
}

void PlaylistComponent::paintCell (juce::Graphics & g,
                        int rowNumber,
                        int columnId,
                        int width,
                        int height,
                        bool rowIsSelected)
{
    if (rowNumber < getNumRows())
    {
        if (columnId == 1)
            g.drawText(songs[rowNumber].title,
                       2, 0,
                       width -4,
                       height, juce::Justification::centredLeft, true);
    }
        if (columnId == 3)
        {
        g.drawText (songs[rowNumber].length,
                    2, 0,
                    width -4,
                    height, juce::Justification::centredRight, true);
        }
    
}

juce::Component* PlaylistComponent::refreshComponentForCell (int rowNumber,
                                   int ColumnId,
                                   bool isRowSelected,
                                   Component *existingComponentToUpdate)
{
    if(ColumnId == 2)
    {
        if (existingComponentToUpdate == nullptr)
        {
            juce::TextButton* btn = new juce::TextButton{"Yes"};
            juce::String id{std::to_string(rowNumber)};
            btn->setComponentID(id);
            
            btn->addListener(this);
            existingComponentToUpdate = btn;
        }
    }
    return existingComponentToUpdate;
   
}

void PlaylistComponent::buttonClicked(juce::Button* button)
{
    if (button == &importButton)
    {
        std::cout<<"PlaylistComponent::Import Button Clicked " << std::endl;
        importToSongsLibrary();
        songsLibrary.updateContent();
    }
    else if (button == &addToDeck1Button)
    {
        std::cout<<"PlaylistComponent::Add To Deck1 Button Clicked " << std::endl;
        loadInPlayer(deckGUI1);
    }
    else if (button == &addToDeck2Button)
    {
        std::cout<<"PlaylistComponent::Add To Deck2 Button Clicked " << std::endl;
        loadInPlayer(deckGUI2);
    }
    else
    {
    int id = std::stoi(button->getComponentID().toStdString());
    std::cout<< songs[id].title << " - PlaylistComponent:: Removed from Library " << std::endl;
    removeSongsFromLibrary(id);
    songsLibrary.updateContent();
    
//    std::cout<<"PlaylistComponent::buttonClicked " << songs[id] << std::endl;
    
    }
}

void PlaylistComponent::loadInPlayer(DeckGUI* deckGUI)
{
    int selectedRow{songsLibrary.getSelectedRow() };
    if (selectedRow != -1)
    {
        std::cout<< songs[selectedRow].title << " - PlaylistComponent:: Added to Library " << std::endl;
        deckGUI->loadFiles(songs[selectedRow].URL);
    }
    else
    {
        juce::AlertWindow::showMessageBox(juce::AlertWindow::AlertIconType::QuestionIcon,
            "MORE INFORMATION:",
            "Please pick a song above to add to deck!",
            "OK",
            nullptr
        );
    }
}

void PlaylistComponent::importToSongsLibrary()
{
    std::cout<< "PlaylistComponent::importToLibrary called" << std::endl;

    //start to initiate song chooser
    juce::FileChooser chooser{ "Select songs" };
    if (chooser.browseForMultipleFilesToOpen())
    {
        for (const juce::File& file : chooser.getResults())
        {
            juce::String songNameWithoutExtension{ file.getFileNameWithoutExtension() };
            if (!isInSongs(songNameWithoutExtension)) // if song has not been loaded
            {
                songName newSong{ file };
                juce::URL audioFileURL{ file };
                songs.push_back(newSong);
                std::cout<< "Loaded file: " << newSong.title << std::endl;
            }
            else
                // error message will pop out
            {
                juce::AlertWindow::showMessageBox(juce::AlertWindow::AlertIconType::WarningIcon,
                    "ERROR:",
                    songNameWithoutExtension + " has already been loaded!",
                    "CLOSE",
                    nullptr
                );
            }
        }
    }
}


void PlaylistComponent::searchSongsLibrary(juce::String searchForText)
{
    std::cout<< "PlaylistComponent:: Searching Songs Library for " << searchForText << std::endl;

    if (searchForText != "")
    {
        int rowNumber = whereInSongs(searchForText);
        songsLibrary.selectRow(rowNumber);
    }
    else
    {
        songsLibrary.deselectAllRows();
    }
}

int PlaylistComponent::whereInSongs(juce::String searchForText)
{
    // searches the index where song has the searchBox
    auto it = find_if(songs.begin(), songs.end(),
        [&searchForText](const songName& obj) {return obj.title.contains(searchForText); });
    int i = -1;

    if (it != songs.end())
    {
        i = std::distance(songs.begin(), it);
    }

    return i;
}


void PlaylistComponent::saveSongsToLibrary()
{
    // generate a .csv file to store Songs library
    std::ofstream myLibrary("mysongslibrary.csv");

    // save Songs library to .csv file
    for (songName& s : songs)
    {
        myLibrary << s.file.getFullPathName() << "," << s.length << "\n";
    }
}


void PlaylistComponent::loadSongsFromLibrary()
{
    // create input stream from saved Songs library
    std::ifstream myLibrary("mysongslibrary.csv");
    std::string filePath;
    std::string length;

    // to analyse the data
    if (myLibrary.is_open())
    {
        while (getline(myLibrary, filePath, ',')) {
            juce::File file{ filePath };
            songName newSong{ file };

            getline(myLibrary, length);
            newSong.length = length;
            songs.push_back(newSong);
        }
    }
    myLibrary.close();
}

bool PlaylistComponent::isInSongs(juce::String songNameWithoutExtension)
{
    return (std::find(songs.begin(),
                      songs.end(),
                      songNameWithoutExtension) != songs.end());
}


void PlaylistComponent::removeSongsFromLibrary(int id)
{
    songs.erase(songs.begin()
                + id);
}

