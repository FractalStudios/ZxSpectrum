#pragma once

// STL includes.
#include    <memory>

// "Home-made" includes.
#include    "BorderScreen.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// High score screen item identifier enumeration.
enum HIGH_SCORE_SCREEN_ITEM_ID
{
    HIGH_SCORE_SCREEN_ITEM_UNDEFINED = Folio::Core::Game::AItem::ITEM_ID_UNDEFINED,
    HIGH_SCORE_SCREEN_ITEM_INFORMATION_PANEL,
    HIGH_SCORE_SCREEN_ITEM_BORDER,
    HIGH_SCORE_SCREEN_ITEM_TITLE,
    HIGH_SCORE_SCREEN_ITEM_1_POSITION_TEXT,
    HIGH_SCORE_SCREEN_ITEM_1_SCORE,
    HIGH_SCORE_SCREEN_ITEM_1_INITIALS,
    HIGH_SCORE_SCREEN_ITEM_2_POSITION_TEXT,
    HIGH_SCORE_SCREEN_ITEM_2_SCORE,
    HIGH_SCORE_SCREEN_ITEM_2_INITIALS,
    HIGH_SCORE_SCREEN_ITEM_3_POSITION_TEXT,
    HIGH_SCORE_SCREEN_ITEM_3_SCORE,
    HIGH_SCORE_SCREEN_ITEM_3_INITIALS,
    HIGH_SCORE_SCREEN_ITEM_4_POSITION_TEXT,
    HIGH_SCORE_SCREEN_ITEM_4_SCORE,
    HIGH_SCORE_SCREEN_ITEM_4_INITIALS,
    HIGH_SCORE_SCREEN_ITEM_5_POSITION_TEXT,
    HIGH_SCORE_SCREEN_ITEM_5_SCORE,
    HIGH_SCORE_SCREEN_ITEM_5_INITIALS,
    HIGH_SCORE_SCREEN_ITEM_6_POSITION_TEXT,
    HIGH_SCORE_SCREEN_ITEM_6_SCORE,
    HIGH_SCORE_SCREEN_ITEM_6_INITIALS,
    HIGH_SCORE_SCREEN_ITEM_COPYRIGHT_TEXT,
}; // Endenum.


// High score screen.
class HighScoreScreen : public BorderScreen
{
public:
    HighScoreScreen ();
    ~HighScoreScreen ();

private:
    static  const   UInt32  MAX_DISPLAY_SCREEN_TIME = 30 * 1000;    // 30 seconds.

    // AScreen method(s).
    virtual FolioStatus BuildScreenItems (FolioHandle dcHandle, 
                                          FolioHandle instanceHandle);
    virtual FolioStatus ProcessScreenInput ();    
    virtual FolioStatus ProcessScreenFrame ();

    static  void    SetItemText (Folio::Core::Game::TextItemPtr::element_type& item);

    // Private copy constructor to prevent copying.
    HighScoreScreen (const HighScoreScreen& rhs);

    // Private assignment operator to prevent copying.
    HighScoreScreen& operator= (const HighScoreScreen& rhs);
}; // Endclass.

// High score screen pointer.
typedef std::shared_ptr<HighScoreScreen>    HighScoreScreenPtr;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
