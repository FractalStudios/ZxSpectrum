// "Home-made" includes.
#include    "StdAfx.h"
#include    "DrawingElement.h"
#include    "Font.h"
#include    "SelectionScreen.h"
#include    "ZxSpectrum.h"

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Selection screen item attributes.
struct SelectionScreenItemAttributes
{
    SELECTION_SCREEN_ITEM_ID    m_itemId;           // The identifier of the selection screen item.
    UInt16                      m_bitmapResourceId; // The selection screen item's bitmap resource identifier (if it's a graphic item).
    Int32                       m_screenXLeft;      // The screen X left of the selection screen item.
    Int32                       m_screenYTop;       // The screen Y top of the selection screen item.
    ZxSpectrum::COLOUR          m_colour;           // The colour of the selection screen item.
 }; // Endstruct.

// Selection screen item attributes table.
static  const   SelectionScreenItemAttributes   g_selectionScreenAttributesTable [] =
{
//      m_itemId                                            m_bitmapResourceId                          m_screenXLeft   m_screenYTop    m_colour
    {   SELECTION_SCREEN_ITEM_TITLE_TEXT,                   0,                                          32,               0,            ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     },
    {   SELECTION_SCREEN_ITEM_KEYBOARD_LEFT_PANE,           IDB_BITMAP_KEYBOARD_LEFT_PANE,              32,              13,            ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   },
    {   SELECTION_SCREEN_ITEM_KEYBOARD_RIGHT_PANE,          IDB_BITMAP_KEYBOARD_RIGHT_PANE,             48,              13,            ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   },
    {   SELECTION_SCREEN_ITEM_KEYBOARD_TEXT,                0,                                          88,              16,            ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {   SELECTION_SCREEN_ITEM_JOYSTICK_LEFT_PANE,           IDB_BITMAP_JOYSTICK_LEFT_PANE,              32,              33,            ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     },
    {   SELECTION_SCREEN_ITEM_JOYSTICK_RIGHT_PANE,          IDB_BITMAP_JOYSTICK_RIGHT_PANE,             48,              33,            ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     },
    {   SELECTION_SCREEN_ITEM_KEMPSTON_JOYSTICK_TEXT,       0,                                          88,              40,            ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {   SELECTION_SCREEN_ITEM_CURSOR_DIRECTIONS_LEFT_PANE,  IDB_BITMAP_CURSOR_DIRECTIONS_LEFT_PANE,     32,              60,            ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {   SELECTION_SCREEN_ITEM_CURSOR_DIRECTIONS_RIGHT_PANE, IDB_BITMAP_CURSOR_DIRECTIONS_RIGHT_PANE,    48,              60,            ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {   SELECTION_SCREEN_ITEM_CURSOR_JOYSTICK_TEXT,         0,                                          88,              64,            ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {   SELECTION_SCREEN_ITEM_KNIGHT,                       IDB_BITMAP_KNIGHT_WALKING_LEFT_1,           40,              86,            ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     },
    {   SELECTION_SCREEN_ITEM_KNIGHT_TEXT,                  0,                                          88,              88,            ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {   SELECTION_SCREEN_ITEM_WIZARD,                       IDB_BITMAP_WIZARD_WALKING_LEFT_1,           40,             108,            ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     },
    {   SELECTION_SCREEN_ITEM_WIZARD_TEXT,                  0,                                          88,             112,            ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {   SELECTION_SCREEN_ITEM_SERF,                         IDB_BITMAP_SERF_WALKING_LEFT_1,             40,             134,            ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     },
    {   SELECTION_SCREEN_ITEM_SERF_TEXT,                    0,                                          88,             136,            ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {   SELECTION_SCREEN_ITEM_START_GAME_TEXT,              0,                                          88,             160,            ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     },
    {   SELECTION_SCREEN_ITEM_COPYRIGHT_TEXT,               0,                                           0,             184,            ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     },
};


// The main player controls map.
static  const   Folio::Core::Game::APlayerSprite::SpriteControlsMap g_mainPlayerControlsMap =
{
//      virtualKey          control                                             direction
    {   'A',            {   SelectionScreen::GAME_CONTROL_KEMPSTON_JOYSTICK,    Folio::Core::Game::APlayerSprite::N,    },  },
    {   'Z',            {   SelectionScreen::GAME_CONTROL_KEMPSTON_JOYSTICK,    Folio::Core::Game::APlayerSprite::S,    },  },
    {   'P',            {   SelectionScreen::GAME_CONTROL_KEMPSTON_JOYSTICK,    Folio::Core::Game::APlayerSprite::E,    },  },
    {   'O',            {   SelectionScreen::GAME_CONTROL_KEMPSTON_JOYSTICK,    Folio::Core::Game::APlayerSprite::W,    },  },
    {   VK_UP,          {   SelectionScreen::GAME_CONTROL_CURSOR_JOYSTICK,      Folio::Core::Game::APlayerSprite::N,    },  },
    {   VK_DOWN,        {   SelectionScreen::GAME_CONTROL_CURSOR_JOYSTICK,      Folio::Core::Game::APlayerSprite::S,    },  },
    {   VK_RIGHT,       {   SelectionScreen::GAME_CONTROL_CURSOR_JOYSTICK,      Folio::Core::Game::APlayerSprite::E,    },  },
    {   VK_LEFT,        {   SelectionScreen::GAME_CONTROL_CURSOR_JOYSTICK,      Folio::Core::Game::APlayerSprite::W,    },  },
    {   'R',            {   SelectionScreen::GAME_CONTROL_KEYBOARD,             Folio::Core::Game::APlayerSprite::N,    },  },
    {   'E',            {   SelectionScreen::GAME_CONTROL_KEYBOARD,             Folio::Core::Game::APlayerSprite::S,    },  },
    {   'W',            {   SelectionScreen::GAME_CONTROL_KEYBOARD,             Folio::Core::Game::APlayerSprite::E,    },  },
    {   'Q',            {   SelectionScreen::GAME_CONTROL_KEYBOARD,             Folio::Core::Game::APlayerSprite::W,    },  },
};


SelectionScreen::SelectionScreen ()
:   m_gameControl(GAME_CONTROL_DEFAULT),
    m_mainPlayer(MAIN_PLAYER_DEFAULT)
{
} // Endproc.


SelectionScreen::~SelectionScreen ()
{
} // Endproc.


FolioStatus SelectionScreen::SetGameControl (GAME_CONTROL gameControl)
{
    FolioStatus status = ERR_SUCCESS;

    if (gameControl != m_gameControl)
    {
        // Set the game control.

        m_gameControl = gameControl;

        // Reset the selection screen.

        status = ResetScreen ();

        if (status == ERR_SUCCESS)
        {
            // Update the selection screen.

            status = UpdateScreen ();
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


SelectionScreen::GAME_CONTROL   SelectionScreen::GetGameControl () const
{
    return (m_gameControl);
} // Endproc.


bool    SelectionScreen::IsKeyboardGameControl () const
{
    return (m_gameControl == GAME_CONTROL_KEYBOARD);
} // Endproc.


bool    SelectionScreen::IsKempstonJoystickGameControl () const
{
    return (m_gameControl == GAME_CONTROL_KEMPSTON_JOYSTICK);
} // Endproc.


bool    SelectionScreen::IsCursorJoystickGameControl () const
{
    return (m_gameControl == GAME_CONTROL_CURSOR_JOYSTICK);
} // Endproc.


FolioStatus SelectionScreen::SetMainPlayer (MAIN_PLAYER mainPlayer)
{
    FolioStatus status = ERR_SUCCESS;

    if (mainPlayer != m_mainPlayer)
    {
        // Set the main player.

        m_mainPlayer = mainPlayer;

        // Reset the selection screen.

        status = ResetScreen ();

        if (status == ERR_SUCCESS)
        {
            // Update the selection screen.

            status = UpdateScreen ();
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


SelectionScreen::MAIN_PLAYER    SelectionScreen::GetMainPlayer () const
{
    return (m_mainPlayer);
} // Endproc.


bool    SelectionScreen::IsKnightMainPlayer () const
{
    return (m_mainPlayer == MAIN_PLAYER_KNIGHT);
} // Endproc.


bool    SelectionScreen::IsWizardMainPlayer () const
{
    return (m_mainPlayer == MAIN_PLAYER_WIZARD);
} // Endproc.


bool    SelectionScreen::IsSerfMainPlayer () const
{
    return (m_mainPlayer == MAIN_PLAYER_SERF);
} // Endproc.


UInt16  SelectionScreen::GetMainPlayerResourceId () const
{
    switch (m_mainPlayer)
    {
    case MAIN_PLAYER_WIZARD:
        return (IDB_BITMAP_WIZARD_WALKING_LEFT_1);

    case MAIN_PLAYER_SERF:
        return (IDB_BITMAP_SERF_WALKING_LEFT_1);

    case MAIN_PLAYER_KNIGHT:
    default:
        return (IDB_BITMAP_KNIGHT_WALKING_LEFT_1);
    } // Endswitch.

} // Endproc.


bool    SelectionScreen::IsPauseGameKey (UInt32 virtualKey, 
                                         bool   keyDown) const
{
    return (!keyDown &&
            (((m_gameControl == GAME_CONTROL_KEMPSTON_JOYSTICK) && (virtualKey == VK_SPACE))    ||
             ((m_gameControl == GAME_CONTROL_CURSOR_JOYSTICK)   && (virtualKey == VK_SPACE))    ||
             ((m_gameControl == GAME_CONTROL_KEYBOARD)          && (virtualKey == VK_SPACE))));
} // Endproc.


bool    SelectionScreen::IsFireWeaponKey (UInt32    virtualKey, 
                                          bool      keyDown) const
{
    return (keyDown &&
            (((m_gameControl == GAME_CONTROL_KEMPSTON_JOYSTICK) && (virtualKey == 'M')) ||
             ((m_gameControl == GAME_CONTROL_CURSOR_JOYSTICK)   && (virtualKey == '0')) ||
             ((m_gameControl == GAME_CONTROL_KEYBOARD)          && (virtualKey == 'T'))));
} // Endproc.


bool    SelectionScreen::IsCollectItemsKey (UInt32  virtualKey, 
                                            bool    keyDown) const
{
    return (!keyDown &&
            (((m_gameControl == GAME_CONTROL_KEMPSTON_JOYSTICK) && (virtualKey == 'X')) ||
             ((m_gameControl == GAME_CONTROL_CURSOR_JOYSTICK)   && (virtualKey == 'Z')) ||
             ((m_gameControl == GAME_CONTROL_KEYBOARD)          && (virtualKey == 'Z'))));
} // Endproc.


bool    SelectionScreen::IsOtherKeyDown (Folio::Core::Game::APlayerSprite::Direction    mainPlayerDirection,
                                         Folio::Core::Game::APlayerSprite::Direction    direction,
                                         bool                                           keyDown) const
{
    bool    isOtherKeyDown = false; // Initialise!

    switch (mainPlayerDirection)
    {
    case PlayerSprite::NE:
    case PlayerSprite::NW:
    case PlayerSprite::SE:
    case PlayerSprite::SW:
        {
            // Get the other direction.

            Folio::Core::Game::APlayerSprite::Direction otherDirection = mainPlayerDirection & ~direction;

            // Find the other direction in the main player controls map.

            Folio::Core::Game::APlayerSprite::SpriteControlsMap::const_iterator itr =
                std::find_if (g_mainPlayerControlsMap.begin (), g_mainPlayerControlsMap.end (), 
                              [this, otherDirection](const std::pair<UInt32, Folio::Core::Game::APlayerSprite::SpriteControl> &arg)
                              {return ((arg.second.m_direction    == otherDirection) &&
                                       (arg.second.m_controlType  == m_gameControl));});

            if (itr != g_mainPlayerControlsMap.end ())
            {
                // Is the other key down?

                isOtherKeyDown = Folio::Core::Util::KeyInput::IsKeyDown (itr->first);
            } // Endif.

        } // Endscope.
        break;

    case PlayerSprite::N:
    case PlayerSprite::S:
    case PlayerSprite::E:
    case PlayerSprite::W:
    default:
        isOtherKeyDown = false;
        break;
    } // Endswitch.
    
    return (isOtherKeyDown);
} // Endproc.


Folio::Core::Game::APlayerSprite::Direction SelectionScreen::GetMainPlayerDirection (UInt32 virtualKey) const
{
    Folio::Core::Game::APlayerSprite::Direction direction = Folio::Core::Game::APlayerSprite::NO_DIRECTION; // Initialise!

    // Find the virtual key in the main player controls map.

    Folio::Core::Game::APlayerSprite::SpriteControlsMap::const_iterator itr = g_mainPlayerControlsMap.find (virtualKey);

    // Is the virtual key valid?

    if ((itr != g_mainPlayerControlsMap.end ()) &&
        (itr->second.m_controlType == m_gameControl))
    {
        // Yes. Get the direction.

        direction = itr->second.m_direction;
    } // Endif.

    return (direction);
} // Endproc.


FolioStatus SelectionScreen::BuildScreenItems (FolioHandle  dcHandle, 
                                               FolioHandle  instanceHandle)
{                               
    FolioStatus status = ERR_SUCCESS;

    // Build the selection screen items. 

    for (UInt32 index = 0; 
         (status == ERR_SUCCESS) && (index < (sizeof (g_selectionScreenAttributesTable) / sizeof (SelectionScreenItemAttributes)));
         ++index)
    {              
        // Build the selection screen item.

        switch (g_selectionScreenAttributesTable [index].m_itemId)
        {
        case SELECTION_SCREEN_ITEM_TITLE_TEXT:
        case SELECTION_SCREEN_ITEM_KEYBOARD_TEXT:
        case SELECTION_SCREEN_ITEM_KEMPSTON_JOYSTICK_TEXT:
        case SELECTION_SCREEN_ITEM_CURSOR_JOYSTICK_TEXT:
        case SELECTION_SCREEN_ITEM_KNIGHT_TEXT:
        case SELECTION_SCREEN_ITEM_WIZARD_TEXT:
        case SELECTION_SCREEN_ITEM_SERF_TEXT:
        case SELECTION_SCREEN_ITEM_START_GAME_TEXT:
        case SELECTION_SCREEN_ITEM_COPYRIGHT_TEXT:
            { 
                // Create a selection screen text item.

                Folio::Core::Game::TextItemPtr  item(new Folio::Core::Game::TextItemPtr::element_type);
                
                status = item->Create (dcHandle,
                                       DRAWING_ELEMENT_SELECTION_SCREEN_ITEM,
                                       *GetFont (),
                                       g_selectionScreenAttributesTable [index].m_itemId,
                                       g_selectionScreenAttributesTable [index].m_screenXLeft, 
                                       g_selectionScreenAttributesTable [index].m_screenYTop,
                                       ZxSpectrum::DEFAULT_SCREEN_SCALE, 
                                       ZxSpectrum::MapInkColour (g_selectionScreenAttributesTable [index].m_colour));

                if (status == ERR_SUCCESS)
                {
                    // Set the selection screen item's text.

                    SetItemText (*item.get ());
            
                    // Store the selection screen item in the selection screen items list.

                    m_itemsList.push_back (item);
                } // Endif.
            
            } // Endscope.
            break;

        case SELECTION_SCREEN_ITEM_KEYBOARD_LEFT_PANE:
        case SELECTION_SCREEN_ITEM_KEYBOARD_RIGHT_PANE:
        case SELECTION_SCREEN_ITEM_JOYSTICK_LEFT_PANE:
        case SELECTION_SCREEN_ITEM_JOYSTICK_RIGHT_PANE:
        case SELECTION_SCREEN_ITEM_CURSOR_DIRECTIONS_LEFT_PANE:
        case SELECTION_SCREEN_ITEM_CURSOR_DIRECTIONS_RIGHT_PANE:
        case SELECTION_SCREEN_ITEM_KNIGHT:
        case SELECTION_SCREEN_ITEM_WIZARD:
        case SELECTION_SCREEN_ITEM_SERF:
            {
                // Create a selection screen graphic item.
            
                Folio::Core::Game::GraphicItemPtr   item(new Folio::Core::Game::GraphicItemPtr::element_type);
            
                status = item->Create (dcHandle,
                                       instanceHandle,
                                       DRAWING_ELEMENT_SELECTION_SCREEN_ITEM,
                                       g_selectionScreenAttributesTable [index].m_bitmapResourceId,
                                       g_selectionScreenAttributesTable [index].m_itemId,
                                       g_selectionScreenAttributesTable [index].m_screenXLeft, 
                                       g_selectionScreenAttributesTable [index].m_screenYTop,
                                       ZxSpectrum::DEFAULT_SCREEN_SCALE, 
                                       ZxSpectrum::GetBitmapChangeColour (),
                                       ZxSpectrum::MapInkColour (g_selectionScreenAttributesTable [index].m_colour));

                if (status == ERR_SUCCESS)
                {
                    // Store the selection screen item in the selection screen items list.

                    m_itemsList.push_back (item);
                } // Endif.
            
            } // Endscope.
            break;

        default:
            status = ERR_INVALID;
            break;
        } // Endswitch.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus SelectionScreen::SetupGamepad (Folio::Core::Game::Gamepad& gamepad)
{
    // Clear the gamepad controller's key mappings.

    gamepad.ClearKeyMappings (m_controllerId);

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus SelectionScreen::StartDisplayingScreen ()
{
    // Reset the selection screen.

    return (ResetScreen ());
} // Endproc.


FolioStatus SelectionScreen::ProcessScreenFrame (UInt32 *frameRateIncrement)
{
    // Process the gamepad.

    FolioStatus status = ProcessGamepad ();

    if (status == ERR_SUCCESS)
    {
        // Get the current tick count.

        UInt32  currentTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount ();

        if (currentTickCount >= (m_previousFrameTickCount + ZxSpectrum::FLASH_MS))
        {
            // Update the selection screen.

            status = UpdateScreen ();

            if (status == ERR_SUCCESS)
            {
                // Note the previous tick count.

                m_previousFrameTickCount = currentTickCount;
            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus SelectionScreen::ProcessScreenKeyboardMsg (UInt32   wParam,
                                                       UInt32   lParam,
                                                       bool     keyDown)
{
    FolioStatus status = ERR_SUCCESS;

    // Process the keyboard message.

    switch (wParam) 
    { 
    case '0':
        status = StartGame ();
        break;

    case '1':
        status = SetGameControl (GAME_CONTROL_KEYBOARD);
        break; 

    case '2':
        status = SetGameControl (GAME_CONTROL_KEMPSTON_JOYSTICK);
        break; 

    case '3':
        status = SetGameControl (GAME_CONTROL_CURSOR_JOYSTICK);
        break; 

    case '4':
        status = SetMainPlayer (MAIN_PLAYER_KNIGHT);
        break; 

    case '5':
        status = SetMainPlayer (MAIN_PLAYER_WIZARD);
        break; 

    case '6':
        status = SetMainPlayer (MAIN_PLAYER_SERF);
        break; 

    default:
        break;
    } // Endswitch.

    return (status);
} // Endproc.


FolioStatus SelectionScreen::UpdateScreen ()
{
    FolioStatus status = ERR_SUCCESS;

    // Get the canvas bag graphics.

    Gdiplus::Graphics   *graphics = m_canvasBag->GetCanvasGraphics ();

    // Update the selection screen items.

    bool    finished        = false;   // Initialise!
    bool    redrawCanvasBag = false;

    for (ItemsList::iterator itr = m_itemsList.begin ();
         !finished && (status == ERR_SUCCESS) && (itr != m_itemsList.end ());
         ++itr)
    {
        // Get the selection screen item's identifier.

        SELECTION_SCREEN_ITEM_ID    itemId = static_cast<SELECTION_SCREEN_ITEM_ID> (itr->get ()->GetItemId ());
         
        switch (itemId)
        {
        case SELECTION_SCREEN_ITEM_KEYBOARD_TEXT:
        case SELECTION_SCREEN_ITEM_KEMPSTON_JOYSTICK_TEXT:
        case SELECTION_SCREEN_ITEM_CURSOR_JOYSTICK_TEXT:
            {
                bool    invertColours = false;  // Initialise!

                switch (m_gameControl)
                {
                case GAME_CONTROL_KEMPSTON_JOYSTICK:
                    invertColours = (itemId == SELECTION_SCREEN_ITEM_KEMPSTON_JOYSTICK_TEXT);
                    break;
                case GAME_CONTROL_CURSOR_JOYSTICK:
                    invertColours = (itemId == SELECTION_SCREEN_ITEM_CURSOR_JOYSTICK_TEXT);
                    break;
                case GAME_CONTROL_KEYBOARD:
                default:
                    invertColours = (itemId == SELECTION_SCREEN_ITEM_KEYBOARD_TEXT);
                    break;
                } // Endswitch.

                // Get the selection screen text item.

                Folio::Core::Game::TextItemPtr  item(std::dynamic_pointer_cast<Folio::Core::Game::TextItem> (*itr));

                // Update the selection screen text item.

                status = UpdateTextItem (*item,
                                         invertColours,
                                         *graphics,
                                         redrawCanvasBag);
            } // Endscope.
            break;

        case SELECTION_SCREEN_ITEM_KNIGHT_TEXT:
        case SELECTION_SCREEN_ITEM_WIZARD_TEXT:
        case SELECTION_SCREEN_ITEM_SERF_TEXT:
            {
                bool    invertColours = false;  // Initialise!

                switch (m_mainPlayer)
                {
                case MAIN_PLAYER_SERF:
                    invertColours = (itemId == SELECTION_SCREEN_ITEM_SERF_TEXT);
                    break;
                case MAIN_PLAYER_WIZARD:
                    invertColours = (itemId == SELECTION_SCREEN_ITEM_WIZARD_TEXT);
                    break;
                case MAIN_PLAYER_KNIGHT:
                default:
                    invertColours = (itemId == SELECTION_SCREEN_ITEM_KNIGHT_TEXT);
                    break;
                } // Endswitch.

                // Get the selection screen text item.

                Folio::Core::Game::TextItemPtr  item(std::dynamic_pointer_cast<Folio::Core::Game::TextItem> (*itr));

                // Update the selection screen text item.

                status = UpdateTextItem (*item,
                                         invertColours,
                                         *graphics,
                                         redrawCanvasBag);

                // Finished?

                finished = (itemId == SELECTION_SCREEN_ITEM_SERF_TEXT);
            } // Endscope.
            break;

        default:
            break;
        } // Endswitch.

    } // Endfor.

    if (redrawCanvasBag && (status == ERR_SUCCESS))
    {
        // The canvas bag should be redrawn on the next draw.

        m_canvasBag->SetRedrawRqd ();
    } // Endif.
    
    return (status);
} // Endproc.


FolioStatus SelectionScreen::ResetScreen ()
{                   
    FolioStatus status = ERR_SUCCESS;

    // Get the canvas bag graphics.

    Gdiplus::Graphics   *graphics = m_canvasBag->GetCanvasGraphics ();

    // Reset the selection screen items.

    bool    finished        = false;   // Initialise!
    bool    redrawCanvasBag = false;

    for (ItemsList::iterator itr = m_itemsList.begin ();
         !finished && (status == ERR_SUCCESS) && (itr != m_itemsList.end ());
         ++itr)
    {
        // Get the selection screen item's identifier.

        SELECTION_SCREEN_ITEM_ID   itemId = static_cast<SELECTION_SCREEN_ITEM_ID> (itr->get ()->GetItemId ());
         
        switch (itemId)
        {
        case SELECTION_SCREEN_ITEM_KEYBOARD_TEXT:
        case SELECTION_SCREEN_ITEM_KEMPSTON_JOYSTICK_TEXT:
        case SELECTION_SCREEN_ITEM_CURSOR_JOYSTICK_TEXT:
        case SELECTION_SCREEN_ITEM_KNIGHT_TEXT:
        case SELECTION_SCREEN_ITEM_WIZARD_TEXT:
        case SELECTION_SCREEN_ITEM_SERF_TEXT:
            {
                // Get the selection screen text item.

                Folio::Core::Game::TextItemPtr  item(std::dynamic_pointer_cast<Folio::Core::Game::TextItem> (*itr));

                // Update the selection screen text item.
            
                status = UpdateTextItem (*item,
                                         false, // Don't invert colours.
                                         *graphics,
                                         redrawCanvasBag);

                // Finished?
            
                finished = (itemId == SELECTION_SCREEN_ITEM_SERF_TEXT);
            } // Endscope.
            break;

        default:
            break;
        } // Endswitch.

    } // Endfor.

    if (redrawCanvasBag && (status == ERR_SUCCESS))
    {
        // The canvas bag should be redrawn on the next draw.

        m_canvasBag->SetRedrawRqd ();
    } // Endif.

    return (status);
} // Endproc.


FolioStatus SelectionScreen::UpdateTextItem (Folio::Core::Game::TextItemPtr::element_type   &item,
                                             bool                                           invertColours,
                                             Gdiplus::Graphics                              &graphics, 
                                             bool                                           &redrawCanvasBag)
{                   
    FolioStatus status = ERR_SUCCESS;

    // Get the text item's GDI raster text.

    Folio::Core::Graphic::GdiRasterTextPtr  gdiRasterText(item.GetGdiRasterText ());

    // Invert the text item's colours?

    if (invertColours)
    {
        // Yes. Invert the text item's colours

        gdiRasterText->InvertColours ();

        // Draw it.

        status = gdiRasterText->Draw (graphics);

        if (status == ERR_SUCCESS)
        {
            redrawCanvasBag = true;
        } // Endif.

    } // Endif.

    else
    if (!invertColours && gdiRasterText->IsInvertedColours ())
    {
        // No. Reset the text item's colours

        gdiRasterText->ResetColours ();

        // Draw it.

        status = gdiRasterText->Draw (graphics);

        if (status == ERR_SUCCESS)
        {
            redrawCanvasBag = true;
        } // Endif.

    } // Endelseif.

    return (status);
} // Endproc.


void    SelectionScreen::SetItemText (Folio::Core::Game::TextItemPtr::element_type &item)
{
    switch (item.GetItemId ())
    {
    case SELECTION_SCREEN_ITEM_TITLE_TEXT:
        item.GetGdiRasterText ()->SetTextString ("ATICATAC GAME SELECTION");
        break;

    case SELECTION_SCREEN_ITEM_KEYBOARD_TEXT:
        item.GetGdiRasterText ()->SetTextString ("1  KEYBOARD");
        break;

    case SELECTION_SCREEN_ITEM_KEMPSTON_JOYSTICK_TEXT:
        item.GetGdiRasterText ()->SetTextString ("2  KEMPSTON JOYSTICK");
        break;

    case SELECTION_SCREEN_ITEM_CURSOR_JOYSTICK_TEXT:
        item.GetGdiRasterText ()->SetTextString ("3  CURSOR   JOYSTICK");
        break;

    case SELECTION_SCREEN_ITEM_KNIGHT_TEXT:
        item.GetGdiRasterText ()->SetTextString ("4  KNIGHT");
        break;

    case SELECTION_SCREEN_ITEM_WIZARD_TEXT:
        item.GetGdiRasterText ()->SetTextString ("5  WIZARD");
        break;

    case SELECTION_SCREEN_ITEM_SERF_TEXT:
        item.GetGdiRasterText ()->SetTextString ("6  SERF");
        break;

    case SELECTION_SCREEN_ITEM_START_GAME_TEXT:
        item.GetGdiRasterText ()->SetTextString ("0  START GAME");
        break;

    case SELECTION_SCREEN_ITEM_COPYRIGHT_TEXT:
        item.GetGdiRasterText ()->SetTextString ("c1983 A.C.G. ALL RIGHTS RESERVED");
        break;

    default:
        break;
    } // Endswitch.

} // Endproc.


FolioStatus SelectionScreen::StartGame ()
{
    // Configure the gamepad.

    ConfigureGamepad ();

    // Stop displaying the selection screen.

    StopDisplaying ();

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus SelectionScreen::ProcessGamepad ()
{  
    FolioStatus status = ERR_SUCCESS;

    // Get the gamepad.

    Folio::Core::Game::Gamepad  &gamepad(*m_canvasBag->GetCanvasGamepad ());

    if (gamepad.IsStartButtonDown (m_controllerId))
    {
        // Start the game.

        status = StartGame ();
    } // Endif.

    else
    if (gamepad.IsDPadUpButtonDown (m_controllerId))
    {
        // Decrement the game control.

        Int32   gameControl = static_cast<Int32> (m_gameControl);

        if (--gameControl < GAME_CONTROL_KEYBOARD)
        {
            gameControl = GAME_CONTROL_CURSOR_JOYSTICK;
        } // Endif.

        // Set the game control.

        status = SetGameControl (static_cast<GAME_CONTROL> (gameControl));
    } // Endelseif.

    else
    if (gamepad.IsDPadDownButtonDown (m_controllerId))
    {
        // Increment the game control.
        
        Int32   gameControl = static_cast<Int32> (m_gameControl);

        if (++gameControl > GAME_CONTROL_CURSOR_JOYSTICK)
        {
            gameControl = GAME_CONTROL_KEYBOARD;
        } // Endif.

        // Set the game control.
        
        status = SetGameControl (static_cast<GAME_CONTROL> (gameControl));
    } // Endelseif.

    else
    if (gamepad.IsDPadLeftButtonDown (m_controllerId))
    {
        // Decrement the main player.

        Int32   mainPlayer = static_cast<Int32> (m_mainPlayer);

        if (--mainPlayer < MAIN_PLAYER_KNIGHT)
        {
            mainPlayer = MAIN_PLAYER_SERF;
        } // Endif.

        // Set the main player.
        
        status = SetMainPlayer (static_cast<MAIN_PLAYER> (mainPlayer));
    } // Endelseif.

    else
    if (gamepad.IsDPadRightButtonDown (m_controllerId))
    {
        // Increment the main player.
        
        Int32   mainPlayer = static_cast<Int32> (m_mainPlayer);

        if (++mainPlayer > MAIN_PLAYER_SERF)
        {
            mainPlayer = MAIN_PLAYER_KNIGHT;
        } // Endif.

        // Set the main player.

        status = SetMainPlayer (static_cast<MAIN_PLAYER> (mainPlayer));
    } // Endelseif.

    return (status);
} // Endproc.


void    SelectionScreen::ConfigureGamepad ()
{
    if (m_gameControl == GAME_CONTROL_KEMPSTON_JOYSTICK)
    {
        // Get the gamepad.

        Folio::Core::Game::Gamepad  &gamepad(*m_canvasBag->GetCanvasGamepad ());
    
        // Clear the gamepad controller's key mappings.

        gamepad.ClearKeyMappings (m_controllerId);

        // Set the gamepad controller's new key mappings.

        gamepad.AddKeyMapping (m_controllerId, Folio::Core::Game::Gamepad::BUTTON_BACK,         VK_SPACE);  // Pause.
        gamepad.AddKeyMapping (m_controllerId, Folio::Core::Game::Gamepad::BUTTON_DPAD_UP,      'A');
        gamepad.AddKeyMapping (m_controllerId, Folio::Core::Game::Gamepad::BUTTON_DPAD_DOWN,    'Z');
        gamepad.AddKeyMapping (m_controllerId, Folio::Core::Game::Gamepad::BUTTON_DPAD_LEFT,    'O');
        gamepad.AddKeyMapping (m_controllerId, Folio::Core::Game::Gamepad::BUTTON_DPAD_RIGHT,   'P');
        gamepad.AddKeyMapping (m_controllerId, Folio::Core::Game::Gamepad::BUTTON_X,            'M');       // Fire.
        gamepad.AddKeyMapping (m_controllerId, Folio::Core::Game::Gamepad::BUTTON_B,            'X');       // Collect.
    } // Endif.

} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
