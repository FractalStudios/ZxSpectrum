#pragma once

// "Home-made" includes.
#include    <Applet.h>
#include    <Game.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Game over screen item identifier enumeration.
enum GAME_OVER_SCREEN_ITEM_ID
{
    GAME_OVER_SCREEN_ITEM_UNDEFINED = Folio::Core::Game::AItem::ITEM_ID_UNDEFINED,
    GAME_OVER_SCREEN_ITEM_ROOM,
    GAME_OVER_SCREEN_ITEM_CONGRATULATIONS_TEXT,
    GAME_OVER_SCREEN_ITEM_YOU_HAVE_ESCAPED_TEXT,
    GAME_OVER_SCREEN_ITEM_GAME_OVER_TEXT,
    GAME_OVER_SCREEN_ITEM_TIME_TEXT,
    GAME_OVER_SCREEN_ITEM_TIME_VALUE,
    GAME_OVER_SCREEN_ITEM_SCORE_TEXT,
    GAME_OVER_SCREEN_ITEM_SCORE_VALUE,
    GAME_OVER_SCREEN_ITEM_PERCENTAGE_COMPLETED_TEXT,
    GAME_OVER_SCREEN_ITEM_PERCENTAGE_COMPLETED_VALUE,
}; // Endenum.


// Game over screen.
class GameOverScreen : public Folio::Core::Applet::AScreen
{
public:
    GameOverScreen (bool    mainPlayerCompletedGame,
                    UInt32  timeInSeconds,
                    UInt32  score,
                    UInt32  percentageCompleted);
    ~GameOverScreen ();

private:
    bool    m_mainPlayerCompletedGame;  // Indicates if the main player has completed the game.
    UInt32  m_timeInSeconds;            // The game's time (in seconds). 
    UInt32  m_score;                    // The game's score. 
    UInt32  m_percentageCompleted;      // The percentage of the game completed.

    // AScreen method(s).
    virtual FolioStatus BuildScreenItems (FolioHandle dcHandle, 
                                          FolioHandle instanceHandle);
    virtual FolioStatus ProcessScreenKeyboardMsg (UInt32    wParam,
                                                  UInt32    lParam,
                                                  bool      keyDown); 

    void    SetItemText (Folio::Core::Game::TextItemPtr::element_type &item);

    // Private copy constructor to prevent copying.
    GameOverScreen (const GameOverScreen& rhs);

    // Private assignment operator to prevent copying.
    GameOverScreen& operator= (const GameOverScreen& rhs);
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
