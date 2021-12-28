#pragma once

// STL includes.
#include    <memory>

// "Home-made" includes.
#include    <Applet.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Game completed screen item identifier enumeration.
enum GAME_COMPLETED_SCREEN_ITEM_ID
{
    GAME_COMPLETED_SCREEN_ITEM_UNDEFINED = Folio::Core::Game::AItem::ITEM_ID_UNDEFINED,
    GAME_COMPLETED_SCREEN_ITEM_INFORMATION_PANEL,
    GAME_COMPLETED_SCREEN_ITEM_GAME_COMPLETED_1_TEXT,
    GAME_COMPLETED_SCREEN_ITEM_GAME_COMPLETED_2_TEXT,
    GAME_COMPLETED_SCREEN_ITEM_GAME_COMPLETED_3_TEXT,
    GAME_COMPLETED_SCREEN_ITEM_UNDERWURLDE_GRAPHIC,
    GAME_COMPLETED_SCREEN_ITEM_UNDERWURLDE_TEXT,
    GAME_COMPLETED_SCREEN_ITEM_COPYRIGHT_TEXT,
    GAME_COMPLETED_SCREEN_ITEM_RIGHTS_TEXT,
}; // Endenum.


// Game completed screen.
class GameCompletedScreen : public Folio::Core::Applet::AScreen
{
public:
    GameCompletedScreen ();
    ~GameCompletedScreen ();

private:
    bool    m_finishedPlayingMainGameMusic; // Indicates if we've finished playing the main game music.
    
    // AScreen method(s).
    virtual FolioStatus BuildScreenItems (FolioHandle dcHandle, 
                                          FolioHandle instanceHandle);
    virtual FolioStatus ProcessScreenInput ();    
    virtual FolioStatus ProcessScreenFrame ();

    FolioStatus PlayMainGameMusic ();

    static  void    SetItemText (Folio::Core::Game::TextItemPtr::element_type& item);

    // Private copy constructor to prevent copying.
    GameCompletedScreen (const GameCompletedScreen& rhs);

    // Private assignment operator to prevent copying.
    GameCompletedScreen& operator= (const GameCompletedScreen& rhs);
}; // Endclass.

// Game completed screen pointer.
typedef std::shared_ptr<GameCompletedScreen>    GameCompletedScreenPtr;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
