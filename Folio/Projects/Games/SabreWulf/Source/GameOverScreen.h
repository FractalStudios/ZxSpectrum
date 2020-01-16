#pragma once

// STL includes.
#include    <memory>

// "Home-made" includes.
#include    <Applet.h>
#include    "DrawingElement.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Game over screen item identifier enumeration.
enum GAME_OVER_SCREEN_ITEM_ID
{
    GAME_OVER_SCREEN_ITEM_INFORMATION_PANEL = DRAWING_ELEMENT_GAME_OVER_SCREEN_ITEM * MAX_NUM_DRAWING_ELEMENTS_PER_ITEM,
    GAME_OVER_SCREEN_ITEM_GAME_OVER_TEXT,
    GAME_OVER_SCREEN_ITEM_PLAYER_TEXT,
    GAME_OVER_SCREEN_ITEM_ADVENTURE_COMPLETED_TEXT,
    GAME_OVER_SCREEN_ITEM_PERCENTAGE_COMPLETE,
}; // Endenum.


// Game over screen.
class GameOverScreen : public Folio::Core::Applet::AScreen
{
public:
    GameOverScreen ();
    ~GameOverScreen ();

private:
    bool    m_finishedPlayingGameOverMusic; // Indicates if we've finished playing the game over music.

    // AScreen method(s).
    virtual FolioStatus BuildScreenItems (FolioHandle dcHandle, 
                                          FolioHandle instanceHandle);
    virtual FolioStatus ProcessScreenInput ();    
    virtual FolioStatus ProcessScreenFrame (UInt32 *frameRateIncrement);

    FolioStatus PlayGameOverMusic ();

    static  void    SetItemText (Folio::Core::Game::TextItemPtr::element_type &item);

    // Private copy constructor to prevent copying.
    GameOverScreen (const GameOverScreen& rhs);

    // Private assignment operator to prevent copying.
    GameOverScreen& operator= (const GameOverScreen& rhs);
}; // Endclass.

// Game over screen pointer.
typedef std::shared_ptr<GameOverScreen> GameOverScreenPtr;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
