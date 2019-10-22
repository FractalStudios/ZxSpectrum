#pragma once

// STL includes.
#include    <memory>

// "Home-made" includes.
#include    "BorderScreen.h"
#include    "DrawingElement.h"
#include    "HighScoreTable.h"
#include    "InformationPanel.h"
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
    ENTER_HIGH_SCORE_SCREEN_ITEM_INFORMATION_PANEL = DRAWING_ELEMENT_ENTER_HIGH_SCORE_SCREEN_ITEM * MAX_NUM_DRAWING_ELEMENTS_PER_ITEM,
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
    EnterHighScoreScreen (const InformationPanelPtr &informationPanel,
                          const SelectionScreenPtr  &electionScreen,
                          HighScoreTable            &highScoreTable);
    ~EnterHighScoreScreen ();

private:
    const InformationPanelPtr   &m_informationPanel;    // The information panel.
    const SelectionScreenPtr    &m_selectionScreen;     // The selection screen.
    HighScoreTable              &m_highScoreTable;      // The high score table.

    HighScoreTable::HighScore   m_highScore;    // The high score.

    FolioNarrowString::value_type   m_currentInitial;   // Current initial.

    // AScreen method(s).
    virtual FolioStatus BuildScreenItems (FolioHandle dcHandle, 
                                          FolioHandle instanceHandle);
    virtual FolioStatus ProcessScreenInput ();    
    virtual FolioStatus UpdateScreen ();

    void    SetItemText (Folio::Core::Game::TextItemPtr::element_type &item);

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
