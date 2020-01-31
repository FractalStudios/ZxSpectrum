// "Home-made" includes.
#include    "StdAfx.h"
#include    "DrawingElement.h"
#include    "Font.h"
#include    "SelectionScreen.h"

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Selection screen item attributes.
typedef Folio::Core::Game::ItemAttributes<SELECTION_SCREEN_ITEM_ID> SelectionScreenItemAttributes;

// Selection screen item attributes table.
static  const   SelectionScreenItemAttributes   g_selectionScreenAttributesTable [] =
{
//      m_itemId                                            m_bitmapResourceId                          m_screenXLeft   m_screenYTop    m_colour
    {   SELECTION_SCREEN_ITEM_TITLE_TEXT,                   0,                                          32,               0,            Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   },
    {   SELECTION_SCREEN_ITEM_KEYBOARD_LEFT_PANE,           IDB_BITMAP_KEYBOARD_LEFT_PANE,              32,              13,            Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {   SELECTION_SCREEN_ITEM_KEYBOARD_RIGHT_PANE,          IDB_BITMAP_KEYBOARD_RIGHT_PANE,             48,              13,            Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {   SELECTION_SCREEN_ITEM_KEYBOARD_TEXT,                0,                                          88,              16,            Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {   SELECTION_SCREEN_ITEM_JOYSTICK_LEFT_PANE,           IDB_BITMAP_JOYSTICK_LEFT_PANE,              32,              33,            Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   },
    {   SELECTION_SCREEN_ITEM_JOYSTICK_RIGHT_PANE,          IDB_BITMAP_JOYSTICK_RIGHT_PANE,             48,              33,            Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   },
    {   SELECTION_SCREEN_ITEM_KEMPSTON_JOYSTICK_TEXT,       0,                                          88,              40,            Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {   SELECTION_SCREEN_ITEM_CURSOR_DIRECTIONS_LEFT_PANE,  IDB_BITMAP_CURSOR_DIRECTIONS_LEFT_PANE,     32,              60,            Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {   SELECTION_SCREEN_ITEM_CURSOR_DIRECTIONS_RIGHT_PANE, IDB_BITMAP_CURSOR_DIRECTIONS_RIGHT_PANE,    48,              60,            Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {   SELECTION_SCREEN_ITEM_CURSOR_JOYSTICK_TEXT,         0,                                          88,              64,            Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {   SELECTION_SCREEN_ITEM_KNIGHT,                       IDB_BITMAP_KNIGHT_WALKING_LEFT_1,           40,              86,            Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   },
    {   SELECTION_SCREEN_ITEM_KNIGHT_TEXT,                  0,                                          88,              88,            Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {   SELECTION_SCREEN_ITEM_WIZARD,                       IDB_BITMAP_WIZARD_WALKING_LEFT_1,           40,             108,            Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   },
    {   SELECTION_SCREEN_ITEM_WIZARD_TEXT,                  0,                                          88,             112,            Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {   SELECTION_SCREEN_ITEM_SERF,                         IDB_BITMAP_SERF_WALKING_LEFT_1,             40,             134,            Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   },
    {   SELECTION_SCREEN_ITEM_SERF_TEXT,                    0,                                          88,             136,            Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {   SELECTION_SCREEN_ITEM_START_GAME_TEXT,              0,                                          88,             160,            Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   },
    {   SELECTION_SCREEN_ITEM_COPYRIGHT_TEXT,               0,                                           0,             184,            Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   },
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


bool    SelectionScreen::IsPauseGameKeyDown () const
{
    return (((m_gameControl == GAME_CONTROL_KEMPSTON_JOYSTICK)  && (m_canvas->GetCanvasGamepad ()->IsBackButtonDown (m_controllerId)))  ||
            ((m_gameControl == GAME_CONTROL_CURSOR_JOYSTICK)    && (Folio::Core::Util::KeyInput::IsKeyDown (VK_SPACE)))                 ||
            ((m_gameControl == GAME_CONTROL_KEYBOARD)           && (Folio::Core::Util::KeyInput::IsKeyDown (VK_SPACE))));
} // Endproc.


bool    SelectionScreen::IsMainPlayerFireWeaponKeyDown () const
{
    return (((m_gameControl == GAME_CONTROL_KEMPSTON_JOYSTICK)  && (m_canvas->GetCanvasGamepad ()->IsXButtonDown (m_controllerId))) ||
            ((m_gameControl == GAME_CONTROL_CURSOR_JOYSTICK)    && (Folio::Core::Util::KeyInput::IsKeyDown ('0')))                  ||
            ((m_gameControl == GAME_CONTROL_KEYBOARD)           && (Folio::Core::Util::KeyInput::IsKeyDown ('T'))));
} // Endproc.


bool    SelectionScreen::IsMainPlayerCollectItemsKeyDown() const
{
    return (((m_gameControl == GAME_CONTROL_KEMPSTON_JOYSTICK)  && (m_canvas->GetCanvasGamepad ()->IsAButtonDown (m_controllerId))) ||
            ((m_gameControl == GAME_CONTROL_CURSOR_JOYSTICK)    && (Folio::Core::Util::KeyInput::IsKeyDown ('Z')))                  ||
            ((m_gameControl == GAME_CONTROL_KEYBOARD)           && (Folio::Core::Util::KeyInput::IsKeyDown ('Z'))));
} // Endproc.


bool    SelectionScreen::IsMainPlayerDirectionKeyDown (Folio::Core::Game::Direction &direction) const
{
    direction = Folio::Core::Game::NO_DIRECTION; // Initialise!

    switch (m_gameControl)
    {
    case GAME_CONTROL_KEMPSTON_JOYSTICK:
        {
            // Get the gamepad.

            Folio::Core::Game::Gamepad  &gamepad(*m_canvas->GetCanvasGamepad ());
    
            if (gamepad.IsDPadUpButtonDown (m_controllerId))
            {
                direction = Folio::Core::Game::N;
            } // Endif.

            else
            if (gamepad.IsDPadDownButtonDown (m_controllerId))
            {
                direction = Folio::Core::Game::S;
            } // Endelseif.

            if (gamepad.IsDPadRightButtonDown (m_controllerId))
            {
                direction |= Folio::Core::Game::E;
            } // Endif.

            else
            if (gamepad.IsDPadLeftButtonDown (m_controllerId))
            {
                direction |= Folio::Core::Game::W;
            } // Endelseif.
    
        } // Endscope.
        break;

    case GAME_CONTROL_CURSOR_JOYSTICK:
        if (Folio::Core::Util::KeyInput::IsKeyDown (VK_UP))
        {
            direction = Folio::Core::Game::N;
        } // Endif.

        else
        if (Folio::Core::Util::KeyInput::IsKeyDown (VK_DOWN))
        {
            direction = Folio::Core::Game::S;
        } // Endelseif.

        if (Folio::Core::Util::KeyInput::IsKeyDown (VK_RIGHT))
        {
            direction |= Folio::Core::Game::E;
        } // Endif.

        else
        if (Folio::Core::Util::KeyInput::IsKeyDown (VK_LEFT))
        {
            direction |= Folio::Core::Game::W;
        } // Endelseif.
        break;

    case GAME_CONTROL_KEYBOARD:
    default:
        if (Folio::Core::Util::KeyInput::IsKeyDown ('R'))
        {
            direction = Folio::Core::Game::N;
        } // Endif.

        else
        if (Folio::Core::Util::KeyInput::IsKeyDown ('E'))
        {
            direction = Folio::Core::Game::S;
        } // Endelseif.

        if (Folio::Core::Util::KeyInput::IsKeyDown ('W'))
        {
            direction |= Folio::Core::Game::E;
        } // Endif.

        else
        if (Folio::Core::Util::KeyInput::IsKeyDown ('Q'))
        {
            direction |= Folio::Core::Game::W;
        } // Endelseif.
        break;
    } // Endswitch.

    return (direction != Folio::Core::Game::NO_DIRECTION);
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
                                       Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE, 
                                       Folio::Core::Game::ZxSpectrum::MapInkColour (g_selectionScreenAttributesTable [index].m_colour));

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
                                       Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE, 
                                       Folio::Core::Game::ZxSpectrum::GetBitmapChangeColour (),
                                       Folio::Core::Game::ZxSpectrum::MapInkColour (g_selectionScreenAttributesTable [index].m_colour));

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


FolioStatus SelectionScreen::StartDisplayingScreen ()
{
    // Reset the selection screen.

    return (ResetScreen ());
} // Endproc.


FolioStatus SelectionScreen::ProcessScreenInput ()
{
    FolioStatus status = ERR_SUCCESS;

    if (Folio::Core::Util::KeyInput::IsKeyDown ('0'))
    {
        status = StartGame ();
    } // Endif.

    else
    if (Folio::Core::Util::KeyInput::IsKeyDown ('1'))
    {
        status = SetGameControl (GAME_CONTROL_KEYBOARD);
    } // Endelseif.

    else
    if (Folio::Core::Util::KeyInput::IsKeyDown ('2'))
    {
        status = SetGameControl (GAME_CONTROL_KEMPSTON_JOYSTICK);
    } // Endelseif.

    else
    if (Folio::Core::Util::KeyInput::IsKeyDown ('3'))
    {
        status = SetGameControl (GAME_CONTROL_CURSOR_JOYSTICK);
    } // Endelseif.

    else
    if (Folio::Core::Util::KeyInput::IsKeyDown ('4'))
    {
        status = SetMainPlayer (MAIN_PLAYER_KNIGHT);
    } // Endelseif.

    else
    if (Folio::Core::Util::KeyInput::IsKeyDown ('5'))
    {
        status = SetMainPlayer (MAIN_PLAYER_WIZARD);
    } // Endelseif.

    else
    if (Folio::Core::Util::KeyInput::IsKeyDown ('6'))
    {
        status = SetMainPlayer (MAIN_PLAYER_SERF);
    } // Endelseif.

    else
    {
        // Process the gamepad.

        status = ProcessGamepad ();
    } // Endelse.

    return (status);
} // Endproc.


FolioStatus SelectionScreen::ProcessScreenFrame ()
{
    FolioStatus status = ERR_SUCCESS;

    // Get the current tick count.

    UInt32  currentTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount ();

    if (currentTickCount >= (m_previousFrameTickCount + Folio::Core::Game::ZxSpectrum::FLASH_MILLISECONDS))
    {
        // Update the selection screen.

        status = UpdateScreen ();

        if (status == ERR_SUCCESS)
        {
            // Note the previous frame tick count.

            m_previousFrameTickCount = currentTickCount;
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus SelectionScreen::UpdateScreen ()
{
    FolioStatus status = ERR_SUCCESS;

    // Get the canvas graphics.

    Gdiplus::Graphics   *graphics = m_canvas->GetCanvasGraphics ();

    // Update the selection screen items.

    bool    finished        = false;   // Initialise!
    bool    redrawCanvas    = false;

    for (Folio::Core::Game::ItemsList::iterator itr = m_itemsList.begin ();
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
                                         redrawCanvas);
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
                                         redrawCanvas);

                // Finished?

                finished = (itemId == SELECTION_SCREEN_ITEM_SERF_TEXT);
            } // Endscope.
            break;

        default:
            break;
        } // Endswitch.

    } // Endfor.

    if (redrawCanvas && (status == ERR_SUCCESS))
    {
        // The canvas should be redrawn on the next draw.

        m_canvas->SetRedrawRqd ();
    } // Endif.
    
    return (status);
} // Endproc.


FolioStatus SelectionScreen::ResetScreen ()
{                   
    FolioStatus status = ERR_SUCCESS;

    // Get the canvas graphics.

    Gdiplus::Graphics   *graphics = m_canvas->GetCanvasGraphics ();

    // Reset the selection screen items.

    bool    finished        = false;   // Initialise!
    bool    redrawCanvas    = false;

    for (Folio::Core::Game::ItemsList::iterator itr = m_itemsList.begin ();
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
                                         redrawCanvas);

                // Finished?
            
                finished = (itemId == SELECTION_SCREEN_ITEM_SERF_TEXT);
            } // Endscope.
            break;

        default:
            break;
        } // Endswitch.

    } // Endfor.

    if (redrawCanvas && (status == ERR_SUCCESS))
    {
        // The canvas should be redrawn on the next draw.

        m_canvas->SetRedrawRqd ();
    } // Endif.

    return (status);
} // Endproc.


FolioStatus SelectionScreen::UpdateTextItem (Folio::Core::Game::TextItemPtr::element_type   &item,
                                             bool                                           invertColours,
                                             Gdiplus::Graphics                              &graphics, 
                                             bool                                           &redrawCanvas)
{                   
    FolioStatus status = ERR_SUCCESS;

    // Get the text item's GDI raster text.

    Folio::Core::Graphic::GdiRasterTextPtr  gdiRasterText(item.GetGdiRasterText ());

    // Invert the text item's colours?

    if (invertColours)
    {
        // Yes. Toggle text item's inverted state.

        gdiRasterText->ToggleInverted ();

        // Draw it.

        status = gdiRasterText->Draw (item.GetScreenXLeft (), 
                                      item.GetScreenYTop (), 
                                      graphics);

        if (status == ERR_SUCCESS)
        {
            redrawCanvas = true;
        } // Endif.

    } // Endif.

    // No. Is the text item inverted?

    else
    if (gdiRasterText->IsInverted ())
    {
        // Yes.

        gdiRasterText->SetNonInverted ();

        // Draw it.

        status = gdiRasterText->Draw (item.GetScreenXLeft (), 
                                      item.GetScreenYTop (), 
                                      graphics);

        if (status == ERR_SUCCESS)
        {
            redrawCanvas = true;
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
    // Stop displaying the selection screen.

    StopDisplaying ();

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus SelectionScreen::ProcessGamepad ()
{  
    FolioStatus status = ERR_SUCCESS;

    // Get the gamepad.

    Folio::Core::Game::Gamepad  &gamepad(*m_canvas->GetCanvasGamepad ());

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

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
