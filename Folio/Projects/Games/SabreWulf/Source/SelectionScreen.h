#pragma once

// STL includes.
#include    <memory>

// "Home-made" includes.
#include    "BorderScreen.h"
#include    "DrawingElement.h"
#include    "InformationPanel.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Selection screen item identifier enumeration.
enum SELECTION_SCREEN_ITEM_ID
{
    SELECTION_SCREEN_ITEM_INFORMATION_PANEL = DRAWING_ELEMENT_SELECTION_SCREEN_ITEM * MAX_NUM_DRAWING_ELEMENTS_PER_ITEM,
    SELECTION_SCREEN_ITEM_BORDER,
    SELECTION_SCREEN_ITEM_1_PLAYER_TEXT,
    SELECTION_SCREEN_ITEM_2_PLAYER_TEXT,
    SELECTION_SCREEN_ITEM_KEYBOARD_TEXT,
    SELECTION_SCREEN_ITEM_KEMPSTON_JOYSTICK_TEXT,
    SELECTION_SCREEN_ITEM_CURSOR_JOYSTICK_TEXT,
    SELECTION_SCREEN_ITEM_INTERFACE_II_TEXT,
    SELECTION_SCREEN_ITEM_START_GAME_TEXT,
    SELECTION_SCREEN_ITEM_COPYRIGHT_TEXT,
}; // Endenum.


// Selection screen.
class SelectionScreen : public BorderScreen
{
public:
    SelectionScreen (const InformationPanelPtr &informationPanel);
    ~SelectionScreen ();

    bool    IsStartGame () const;

    FolioStatus SetNumPlayers (UInt32 numPlayers);
    UInt32      GetNumPlayers () const;

    // Game control enumeration.
    enum GAME_CONTROL
    {
        GAME_CONTROL_KEYBOARD = 0,
        GAME_CONTROL_DEFAULT = GAME_CONTROL_KEYBOARD,
        GAME_CONTROL_KEMPSTON_JOYSTICK,
        GAME_CONTROL_CURSOR_JOYSTICK,
        GAME_CONTROL_INTERFACE_II,
    }; // Endenum.

    FolioStatus     SetGameControl (GAME_CONTROL gameControl);
    GAME_CONTROL    GetGameControl () const;
    bool    IsKeyboardGameControl () const;
    bool    IsKempstonJoystickGameControl () const;
    bool    IsCursorJoystickGameControl () const;
    bool    IsInterfaceIIGameControl () const;

    bool    IsPauseGameKeyDown () const;
    bool    IsPlayerFireKeyDown () const;
    bool    IsPlayerDirectionKeyDown (Folio::Core::Game::Direction &direction) const;

private:
    static  const   UInt32  MAX_DISPLAY_SCREEN_TIME = 30 * 1000;    // 30 seconds.

    const InformationPanelPtr  &m_informationPanel; // The information panel.

    bool            m_isStartGame;  // Indicates if the game should be started.
    UInt32          m_numPlayers;   // The number of players.
    GAME_CONTROL    m_gameControl;  // The game control.

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

// Selection screen pointer.
typedef std::shared_ptr<SelectionScreen>    SelectionScreenPtr;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
