#pragma once

// STL includes.
#include    <memory>

// "Home-made" includes.
#include    "BorderScreen.h"
#include    "HighScoreTable.h"
#include    "SelectionScreen.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Enter high score screen item identifier enumeration.
enum ENTER_HIGH_SCORE_SCREEN_ITEM_ID
{
    ENTER_HIGH_SCORE_SCREEN_ITEM_UNDEFINED = Folio::Core::Game::AItem::ITEM_ID_UNDEFINED,
    ENTER_HIGH_SCORE_SCREEN_ITEM_INFORMATION_PANEL,
    ENTER_HIGH_SCORE_SCREEN_ITEM_BORDER,
    ENTER_HIGH_SCORE_SCREEN_ITEM_CONGRATULATIONS_TEXT,
    ENTER_HIGH_SCORE_SCREEN_ITEM_PLAYER_TEXT,
    ENTER_HIGH_SCORE_SCREEN_ITEM_YOU_HAVE_ACHIEVED_TEXT,
    ENTER_HIGH_SCORE_SCREEN_ITEM_TODAYS_TEXT,
    ENTER_HIGH_SCORE_SCREEN_ITEM_POSITION,
    ENTER_HIGH_SCORE_SCREEN_ITEM_HIGHEST_TEXT,
    ENTER_HIGH_SCORE_SCREEN_ITEM_SCORE_TEXT,
    ENTER_HIGH_SCORE_SCREEN_ITEM_REGISTER_TEXT,
    ENTER_HIGH_SCORE_SCREEN_ITEM_YOUR_INITIALS_TEXT,
    ENTER_HIGH_SCORE_SCREEN_ITEM_INITIAL_INPUT_1,
    ENTER_HIGH_SCORE_SCREEN_ITEM_INITIAL_INPUT_2,
    ENTER_HIGH_SCORE_SCREEN_ITEM_INITIAL_INPUT_3,
}; // Endenum.


// Enter high score screen.
class EnterHighScoreScreen : public BorderScreen
{
public:
    EnterHighScoreScreen (const SelectionScreenPtr& selectionScreen);
    ~EnterHighScoreScreen ();

private:
    const SelectionScreenPtr    &m_selectionScreen;     // The selection screen.

    HighScoreTable::HighScore   m_highScore;    // The high score.

    FolioNarrowString::value_type   m_currentInitial;   // Current initial.

    static  Folio::Core::Util::Sound::SoundSample   m_selectingInitialSoundSample;  // The selecting initial sound sample.
    static  Folio::Core::Util::Sound::SoundSample   m_enteredInitialSoundSample;    // The entered initial sound sample.

    // AScreen method(s).
    virtual FolioStatus BuildScreenItems (FolioHandle dcHandle, 
                                          FolioHandle instanceHandle);
    virtual FolioStatus ProcessScreenInput ();    
    
    // The update enumeration.
    enum UPDATE
    {
        UPDATE_INITIAL = 0,
    }; // Endenum.

    FolioStatus UpdateScreen (UPDATE update);
    FolioStatus UpdateInitial (Gdiplus::Graphics&   graphics,
                               bool&                redrawCanvas);
    
    static  void    SetItemText (Folio::Core::Game::TextItemPtr::element_type& item);

    // Private copy constructor to prevent copying.
    EnterHighScoreScreen (const EnterHighScoreScreen& rhs);

    // Private assignment operator to prevent copying.
    EnterHighScoreScreen& operator= (const EnterHighScoreScreen& rhs);
}; // Endclass.

// Enter high score screen pointer.
typedef std::shared_ptr<EnterHighScoreScreen>   EnterHighScoreScreenPtr;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
