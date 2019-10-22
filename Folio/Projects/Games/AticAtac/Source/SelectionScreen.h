#pragma once

// "Home-made" includes.
#include    <Applet.h>
#include    <Game.h>
#include    "PlayerSprite.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Selection screen item identifier enumeration.
enum SELECTION_SCREEN_ITEM_ID
{
    SELECTION_SCREEN_ITEM_UNDEFINED = Folio::Core::Game::AItem::ITEM_ID_UNDEFINED,
    SELECTION_SCREEN_ITEM_TITLE_TEXT,
    SELECTION_SCREEN_ITEM_KEYBOARD_LEFT_PANE,
    SELECTION_SCREEN_ITEM_KEYBOARD_RIGHT_PANE,
    SELECTION_SCREEN_ITEM_KEYBOARD_TEXT,
    SELECTION_SCREEN_ITEM_JOYSTICK_LEFT_PANE,
    SELECTION_SCREEN_ITEM_JOYSTICK_RIGHT_PANE,
    SELECTION_SCREEN_ITEM_KEMPSTON_JOYSTICK_TEXT,
    SELECTION_SCREEN_ITEM_CURSOR_DIRECTIONS_LEFT_PANE,
    SELECTION_SCREEN_ITEM_CURSOR_DIRECTIONS_RIGHT_PANE,
    SELECTION_SCREEN_ITEM_CURSOR_JOYSTICK_TEXT,
    SELECTION_SCREEN_ITEM_KNIGHT,
    SELECTION_SCREEN_ITEM_KNIGHT_TEXT,
    SELECTION_SCREEN_ITEM_WIZARD,
    SELECTION_SCREEN_ITEM_WIZARD_TEXT,
    SELECTION_SCREEN_ITEM_SERF,
    SELECTION_SCREEN_ITEM_SERF_TEXT,
    SELECTION_SCREEN_ITEM_START_GAME_TEXT,
    SELECTION_SCREEN_ITEM_COPYRIGHT_TEXT,
}; // Endenum.


// Selection screen.
class SelectionScreen : public Folio::Core::Applet::AScreen
{
public:
    SelectionScreen ();
    ~SelectionScreen ();

    // Game control enumeration.
    enum GAME_CONTROL
    {
        GAME_CONTROL_KEYBOARD = 0,
        GAME_CONTROL_DEFAULT = GAME_CONTROL_KEYBOARD,
        GAME_CONTROL_KEMPSTON_JOYSTICK,
        GAME_CONTROL_CURSOR_JOYSTICK,
    }; // Endenum.

    FolioStatus     SetGameControl (GAME_CONTROL gameControl);
    GAME_CONTROL    GetGameControl () const;
    bool    IsKeyboardGameControl () const;
    bool    IsKempstonJoystickGameControl () const;
    bool    IsCursorJoystickGameControl () const;

    // Main player enumeration.
    enum MAIN_PLAYER
    {
        MAIN_PLAYER_KNIGHT  = PLAYER_SPRITE_KNIGHT,
        MAIN_PLAYER_DEFAULT = MAIN_PLAYER_KNIGHT,
        MAIN_PLAYER_WIZARD  = PLAYER_SPRITE_WIZARD,
        MAIN_PLAYER_SERF    = PLAYER_SPRITE_SERF,
    }; // Endenum.

    FolioStatus SetMainPlayer (MAIN_PLAYER mainPlayer);
    MAIN_PLAYER GetMainPlayer () const;
    bool    IsKnightMainPlayer () const;
    bool    IsWizardMainPlayer () const;
    bool    IsSerfMainPlayer () const;

    UInt16  GetMainPlayerResourceId () const;
    
    bool    IsPauseGameKeyDown () const;
    bool    IsMainPlayerFireWeaponKeyDown () const;
    bool    IsMainPlayerCollectItemsKeyDown () const;
    bool    IsMainPlayerDirectionKeyDown (Folio::Core::Game::APlayerSprite::Direction &direction) const;

private:
    GAME_CONTROL    m_gameControl;  // The game control.
    MAIN_PLAYER     m_mainPlayer;   // The main player.

    // AScreen method(s).
    virtual FolioStatus BuildScreenItems (FolioHandle dcHandle, 
                                          FolioHandle instanceHandle);
    virtual FolioStatus StartDisplayingScreen ();
    virtual FolioStatus ProcessScreenInput ();    
    virtual FolioStatus ProcessScreenFrame (UInt32 *frameRateIncrement);
    virtual FolioStatus UpdateScreen ();

    FolioStatus ResetScreen ();
    FolioStatus UpdateTextItem (Folio::Core::Game::TextItemPtr::element_type    &item,
                                bool                                            invertColours,
                                Gdiplus::Graphics                               &graphics, 
                                bool                                            &redrawCanvas);

    void    SetItemText (Folio::Core::Game::TextItemPtr::element_type &item);

    FolioStatus StartGame ();

    FolioStatus ProcessGamepad ();

    // Private copy constructor to prevent copying.
    SelectionScreen (const SelectionScreen& rhs);

    // Private assignment operator to prevent copying.
    SelectionScreen& operator= (const SelectionScreen& rhs);
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
