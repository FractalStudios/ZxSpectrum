// "Home-made" includes.
#include    "StdAfx.h"
#include    "Globals.h"
#include    "SelectionScreen.h"

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Selection screen item attributesFolio::Core::Game::ItemAttributes<SELECTION_SCREEN_ITEM_ID>.
static  const   Folio::Core::Game::ItemAttributesList<SELECTION_SCREEN_ITEM_ID> g_selectionScreenAttributes  =
{
//      m_itemId                                        m_screenXLeft           m_screenYTop        m_colour
    {   SELECTION_SCREEN_ITEM_INFORMATION_PANEL,        0,                       0,                 Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       },
    {   SELECTION_SCREEN_ITEM_BORDER,                   0,                      16,                 Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       },
    {   SELECTION_SCREEN_ITEM_1_PLAYER_TEXT,            COLUMN_TO_PIXEL( 6),    ROW_TO_PIXEL( 6),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW),  },
    {   SELECTION_SCREEN_ITEM_2_PLAYER_TEXT,            COLUMN_TO_PIXEL( 6),    ROW_TO_PIXEL( 8),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW),  },
    {   SELECTION_SCREEN_ITEM_KEYBOARD_TEXT,            COLUMN_TO_PIXEL( 6),    ROW_TO_PIXEL(10),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    },
    {   SELECTION_SCREEN_ITEM_KEMPSTON_JOYSTICK_TEXT,   COLUMN_TO_PIXEL( 6),    ROW_TO_PIXEL(12),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    },
    {   SELECTION_SCREEN_ITEM_CURSOR_JOYSTICK_TEXT,     COLUMN_TO_PIXEL( 6),    ROW_TO_PIXEL(14),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    },
    {   SELECTION_SCREEN_ITEM_INTERFACE_II_TEXT,        COLUMN_TO_PIXEL( 6),    ROW_TO_PIXEL(16),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    },
    {   SELECTION_SCREEN_ITEM_START_GAME_TEXT,          COLUMN_TO_PIXEL( 6),    ROW_TO_PIXEL(19),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   },
    {   SELECTION_SCREEN_ITEM_COPYRIGHT_TEXT,           COLUMN_TO_PIXEL( 9),    ROW_TO_PIXEL(22),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   },
};


SelectionScreen::SelectionScreen ()
:   m_finishedPlayingMainGameMusic(false),
    m_finishedPlayingStartingGameMusic(false),
    m_isStartingGame(false),
    m_isStartGame(false),
    m_invertCurrentSelectionText(false),
    m_numPlayers(1),
    m_gameControl(GAME_CONTROL_DEFAULT)
{
} // Endproc.


SelectionScreen::~SelectionScreen ()
{
} // Endproc.


bool    SelectionScreen::IsStartGame () const
{
    return (m_isStartGame);
} // Endproc.


FolioStatus SelectionScreen::SetNumPlayers (UInt32 numPlayers)
{
    FolioStatus status = ERR_SUCCESS;

    // Stop the main game music.

    StopMainGameMusic ();

    if (numPlayers != m_numPlayers)
    {
        // Set the number of players.

        m_numPlayers = numPlayers;

        // Update the selection screen.

        status = UpdateScreen (UPDATE_PLAYER_SELECTION);
    } // Endif.

    return (status);
} // Endproc.


UInt32  SelectionScreen::GetNumPlayers () const
{
    return (m_numPlayers);
} // Endproc.


FolioStatus SelectionScreen::SetGameControl (GAME_CONTROL gameControl)
{
    FolioStatus status = ERR_SUCCESS;

    // Stop the main game music.

    StopMainGameMusic ();

    if (gameControl != m_gameControl)
    {
        // Set the game control.

        m_gameControl = gameControl;

        // Update the selection screen.

        status = UpdateScreen (UPDATE_GAME_CONTROL_SELECTION);
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


bool    SelectionScreen::IsInterfaceIIGameControl () const
{
    return (m_gameControl == GAME_CONTROL_INTERFACE_II);
} // Endproc.


bool    SelectionScreen::IsPauseGameKeyDown () const
{
    return (((m_gameControl == GAME_CONTROL_KEMPSTON_JOYSTICK)  && (m_canvas->GetCanvasGamepad ()->IsBackButtonDown (m_controllerId)))  ||
            ((m_gameControl == GAME_CONTROL_CURSOR_JOYSTICK)    && (Folio::Core::Util::KeyInput::IsKeyDown (VK_SPACE)))                 ||
            ((m_gameControl == GAME_CONTROL_KEYBOARD)           && (Folio::Core::Util::KeyInput::IsKeyDown (VK_SPACE)))                 ||
            ((m_gameControl == GAME_CONTROL_INTERFACE_II)       && (Folio::Core::Util::KeyInput::IsKeyDown (VK_SPACE))));
} // Endproc.


bool    SelectionScreen::IsPlayerFireKeyDown () const
{
    return (((m_gameControl == GAME_CONTROL_KEMPSTON_JOYSTICK)  && (m_canvas->GetCanvasGamepad ()->IsXButtonDown (m_controllerId))) ||
            ((m_gameControl == GAME_CONTROL_CURSOR_JOYSTICK)    && (Folio::Core::Util::KeyInput::IsKeyDown ('0')))                  ||
            ((m_gameControl == GAME_CONTROL_KEYBOARD)           && (Folio::Core::Util::KeyInput::IsKeyDown ('T')))                  ||
            ((m_gameControl == GAME_CONTROL_INTERFACE_II)       && (Folio::Core::Util::KeyInput::IsKeyDown ('T'))));
} // Endproc.


bool    SelectionScreen::IsPlayerDirectionKeyDown (Folio::Core::Game::Direction& direction) const
{
    direction = Folio::Core::Game::NO_DIRECTION;    // Initialise!

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
    case GAME_CONTROL_INTERFACE_II:
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

    default:
        break;
    } // Endswitch.

    return (direction != Folio::Core::Game::NO_DIRECTION);
} // Endproc.


FolioStatus SelectionScreen::BuildScreenItems (FolioHandle  dcHandle, 
                                               FolioHandle  instanceHandle)
{                               
    FolioStatus status = ERR_SUCCESS;

    // Build the selection screen items. 

    for (Folio::Core::Game::ItemAttributesList<SELECTION_SCREEN_ITEM_ID>::const_iterator itr = g_selectionScreenAttributes.begin (); 
         (status == ERR_SUCCESS) && (itr != g_selectionScreenAttributes.end ());
         ++itr)
    {              
        // Build the selection screen item.

        switch (itr->m_itemId)
        {
        case SELECTION_SCREEN_ITEM_INFORMATION_PANEL:
            // No players.

            g_informationPanel->SetNumPlayers (0);

            // Query the information panel's items.

            status = g_informationPanel->QueryItems (m_itemsList);
            break;

        case SELECTION_SCREEN_ITEM_BORDER:
            // Add the border screen's items.
            
            status = AddBorderScreenItems (dcHandle, instanceHandle);
            break;

        case SELECTION_SCREEN_ITEM_1_PLAYER_TEXT:
        case SELECTION_SCREEN_ITEM_2_PLAYER_TEXT:
        case SELECTION_SCREEN_ITEM_KEYBOARD_TEXT:
        case SELECTION_SCREEN_ITEM_KEMPSTON_JOYSTICK_TEXT:
        case SELECTION_SCREEN_ITEM_CURSOR_JOYSTICK_TEXT:
        case SELECTION_SCREEN_ITEM_INTERFACE_II_TEXT:
        case SELECTION_SCREEN_ITEM_START_GAME_TEXT:
        case SELECTION_SCREEN_ITEM_COPYRIGHT_TEXT:
            // Add selection screen text item.

            status = AddTextItem (dcHandle, 
                                  Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_SELECTION_SCREEN_ITEM,
                                  *Folio::Core::Game::ZxSpectrum::GetFont (),
                                  *itr,
                                  SetItemText,
                                  ((itr->m_itemId != SELECTION_SCREEN_ITEM_START_GAME_TEXT) &&
                                   (itr->m_itemId != SELECTION_SCREEN_ITEM_COPYRIGHT_TEXT)));

            // For performance, create the current selection screen's text items.

            if ((status == ERR_SUCCESS) &&
                ((itr->m_itemId == SELECTION_SCREEN_ITEM_1_PLAYER_TEXT) ||
                 (itr->m_itemId == SELECTION_SCREEN_ITEM_KEYBOARD_TEXT)))
            {
                // Get the selection screen's text item.
    
                Folio::Core::Game::TextItemPtr  item(std::dynamic_pointer_cast<Folio::Core::Game::TextItem> (m_itemsList.back ()));

                // Create the GDI bitmap cache for the selection screen's text 
                // item.

                status = item->GetGdiRasterText ()->CreateGdiBitmapCache ();
                
                if (status == ERR_SUCCESS)
                {
                    // Create the inverted GDI bitmap cache for the selection 
                    // screen's text item.

                    status = item->GetGdiRasterText ()->CreateInvertedGdiBitmapCache ();
                } // Endif.

            } // Endif.
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
    m_isStartingGame    = false;    // Initialise!
    m_isStartGame       = false;

    // Reset the selection screen.

    return (ResetScreen ());
} // Endproc.


FolioStatus SelectionScreen::ProcessScreenInput ()
{
    FolioStatus status = ERR_SUCCESS;

    if (Folio::Core::Util::KeyInput::IsKeyDown ('0'))
    {
        // Start game selected.

        status = StartingGame ();
    } // Endif.

    else
    if (Folio::Core::Util::KeyInput::IsKeyDown ('1'))
    {
        // 1 player selected.

        status = SetNumPlayers (1);
    } // Endelseif.

    else
    if (Folio::Core::Util::KeyInput::IsKeyDown ('2'))
    {
        // 2 players selected.

        status = SetNumPlayers (2);
    } // Endelseif.

    else
    if (Folio::Core::Util::KeyInput::IsKeyDown ('3'))
    {
        // Keyboard selected.

        status = SetGameControl (GAME_CONTROL_KEYBOARD);
    } // Endelseif.

    else
    if (Folio::Core::Util::KeyInput::IsKeyDown ('4'))
    {
        // Kempston joystick selected.
        
        status = SetGameControl (GAME_CONTROL_KEMPSTON_JOYSTICK);
    } // Endelseif.

    else
    if (Folio::Core::Util::KeyInput::IsKeyDown ('5'))
    {
        // Cursor joystick selected.

        status = SetGameControl (GAME_CONTROL_CURSOR_JOYSTICK);
    } // Endelseif.

    else
    if (Folio::Core::Util::KeyInput::IsKeyDown ('6'))
    {
        // Interface II selected.

        status = SetGameControl (GAME_CONTROL_INTERFACE_II);
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

    // Are we starting the game?

    if (m_isStartingGame)
    {
        // Yes. Process the frame when starting the game.

        status = ProcessScreenFrameStartingGame (currentTickCount);
    } // Endif.

    else
    {
        // No. Process the frame when waiting for selection.

        status = ProcessScreenFrameWaitingForSelection (currentTickCount);
    } // Endelse.
    
    if (status == ERR_SUCCESS)
    {
        // Should we update any current selection text on the selection screen, 
        // i.e. has the current tick count exceeded the flash rate since the 
        // last update?

        // Get the current tick count.
        
        currentTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount ();

        if (currentTickCount >= (m_previousFrameTickCount + Folio::Core::Game::ZxSpectrum::FLASH_MILLISECONDS))
        {
            // Yes. Note the previous frame tick count.

            m_previousFrameTickCount = currentTickCount;

            // Update the selection screen.

            status = UpdateScreen (UPDATE_FLASH_CURRENT_SELECTIONS);
        } // Endif.
    
    } // Endif.

    return (status);
} // Endproc.


FolioStatus SelectionScreen::UpdateScreen (UPDATE update)
{
    FolioStatus status = ERR_SUCCESS;

    // Get the canvas graphics.

    Gdiplus::Graphics   *graphics = m_canvas->GetCanvasGraphics ();

    // Update the selection screen items (depending on the type of update required).

    bool    redrawCanvas = false;   // Initialise!

    switch (update)
    {
    case UPDATE_PLAYER_SELECTION:
        status = UpdatePlayerSelection (*graphics, redrawCanvas);
        break;

    case UPDATE_GAME_CONTROL_SELECTION:
        status = UpdateGameControlSelection (*graphics, redrawCanvas);
        break;

    case UPDATE_FLASH_CURRENT_SELECTIONS:
        status = UpdateFlashCurrentSelections (*graphics, redrawCanvas);
        break;

    default:
        status = ERR_INVALID;
        break;
    } // Endswitch.

    // Should the canvas be redrawn?

    if (redrawCanvas && (status == ERR_SUCCESS))
    {
        // Yes. The canvas should be redrawn on the next draw.

        m_canvas->SetRedrawRqd ();
    } // Endif.
    
    return (status);
} // Endproc.


FolioStatus SelectionScreen::UpdatePlayerSelection (Gdiplus::Graphics&  graphics,
                                                    bool&               redrawCanvas)
{
    redrawCanvas = false;   // Initialise!

    FolioStatus status = ERR_SUCCESS;

    bool    finished = false;   // Initialise!

    // Reverse order for performance.

    for (Folio::Core::Game::ItemsList::reverse_iterator ritr = m_itemsList.rbegin ();
         !finished && (status == ERR_SUCCESS) && (ritr != m_itemsList.rend ());
         ++ritr)
    {
        // Get the selection screen item's identifier.

        SELECTION_SCREEN_ITEM_ID    itemId = static_cast<SELECTION_SCREEN_ITEM_ID> (ritr->get ()->GetItemId ());
         
        switch (itemId)
        {
        case SELECTION_SCREEN_ITEM_1_PLAYER_TEXT:
        case SELECTION_SCREEN_ITEM_2_PLAYER_TEXT:
            {
                // Invert the selection screen's current player text item's text.

                bool    invertText = false;  // Initialise!
    
                switch (m_numPlayers)
                {
                case 1:
                    invertText = m_invertCurrentSelectionText && (itemId == SELECTION_SCREEN_ITEM_1_PLAYER_TEXT);
                    break;
                    
                case 2:
                    invertText = m_invertCurrentSelectionText && (itemId == SELECTION_SCREEN_ITEM_2_PLAYER_TEXT);
                    break;
                    
                default:
                    break;
                } // Endswitch.
    
                // Get the selection screen text item.
    
                Folio::Core::Game::TextItemPtr  item(std::dynamic_pointer_cast<Folio::Core::Game::TextItem> (*ritr));
    
                // Invert the selection screen text item.

                status = item->SetInvert (invertText, graphics, redrawCanvas);

                // Finished?
            
                finished = (itemId == SELECTION_SCREEN_ITEM_1_PLAYER_TEXT);
            } // Endscope.
            break;

        default:
            break;
        } // Endswitch.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus SelectionScreen::UpdateGameControlSelection (Gdiplus::Graphics& graphics,
                                                         bool&              redrawCanvas)
{
    redrawCanvas = false;   // Initialise!

    FolioStatus status = ERR_SUCCESS;

    bool    finished = false;   // Initialise!

    // Reverse order for performance.

    for (Folio::Core::Game::ItemsList::reverse_iterator ritr = m_itemsList.rbegin ();
         !finished && (status == ERR_SUCCESS) && (ritr != m_itemsList.rend ());
         ++ritr)
    {
        // Get the selection screen item's identifier.

        SELECTION_SCREEN_ITEM_ID    itemId = static_cast<SELECTION_SCREEN_ITEM_ID> (ritr->get ()->GetItemId ());
         
        switch (itemId)
        {
        case SELECTION_SCREEN_ITEM_KEYBOARD_TEXT:
        case SELECTION_SCREEN_ITEM_KEMPSTON_JOYSTICK_TEXT:
        case SELECTION_SCREEN_ITEM_CURSOR_JOYSTICK_TEXT:
        case SELECTION_SCREEN_ITEM_INTERFACE_II_TEXT:
            {
                // Invert the selection screen's current game control text item's text.

                bool    invertText = false;  // Initialise!
    
                switch (m_gameControl)
                {
                case GAME_CONTROL_KEYBOARD:
                    invertText = m_invertCurrentSelectionText && (itemId == SELECTION_SCREEN_ITEM_KEYBOARD_TEXT);
                    break;
                
                case GAME_CONTROL_KEMPSTON_JOYSTICK:
                    invertText = m_invertCurrentSelectionText && (itemId == SELECTION_SCREEN_ITEM_KEMPSTON_JOYSTICK_TEXT);
                    break;
                
                case GAME_CONTROL_CURSOR_JOYSTICK:
                    invertText = m_invertCurrentSelectionText && (itemId == SELECTION_SCREEN_ITEM_CURSOR_JOYSTICK_TEXT);
                    break;
                
                case GAME_CONTROL_INTERFACE_II:
                    invertText = m_invertCurrentSelectionText && (itemId == SELECTION_SCREEN_ITEM_INTERFACE_II_TEXT);
                    break;
                
                default:
                    break;
                } // Endswitch.

                // Get the selection screen text item.
    
                Folio::Core::Game::TextItemPtr  item(std::dynamic_pointer_cast<Folio::Core::Game::TextItem> (*ritr));
    
                // Invert the selection screen text item.

                status = item->SetInvert (invertText, graphics, redrawCanvas);

                // Finished?
            
                finished = (itemId == SELECTION_SCREEN_ITEM_KEYBOARD_TEXT);
            } // Endscope.
            break;

        default:
            break;
        } // Endswitch.

    } // Endfor.
    
    return (status);
} // Endproc.


FolioStatus SelectionScreen::UpdateFlashCurrentSelections (Gdiplus::Graphics&   graphics,
                                                           bool&                redrawCanvas)
{
    redrawCanvas = false;   // Initialise!

    FolioStatus status = ERR_SUCCESS;

    // Invert the selection screen's current selection text.

    m_invertCurrentSelectionText = !m_invertCurrentSelectionText;

    // The current number of players.

    Folio::Core::Game::ItemsList::iterator  itr(Folio::Core::Game::FindItem ((m_numPlayers == 1) ? SELECTION_SCREEN_ITEM_1_PLAYER_TEXT : SELECTION_SCREEN_ITEM_2_PLAYER_TEXT, 
                                                                             m_itemsList));

    if (itr != m_itemsList.end ())
    {
        // Get the selection screen's number of players text item.
    
        Folio::Core::Game::TextItemPtr  item(std::dynamic_pointer_cast<Folio::Core::Game::TextItem> (*itr));

        // Invert the selection screen's number of players text item.

        status = item->SetInvert (m_invertCurrentSelectionText, graphics, redrawCanvas);
    } // Endif.

    if (status == ERR_SUCCESS)
    {
        // The current game control.

        switch (m_gameControl)
        {
        case GAME_CONTROL_KEYBOARD:
            itr = Folio::Core::Game::FindItem (SELECTION_SCREEN_ITEM_KEYBOARD_TEXT, m_itemsList);
            break;
                
        case GAME_CONTROL_KEMPSTON_JOYSTICK:
            itr = Folio::Core::Game::FindItem (SELECTION_SCREEN_ITEM_KEMPSTON_JOYSTICK_TEXT, m_itemsList);
            break;
                
        case GAME_CONTROL_CURSOR_JOYSTICK:
            itr = Folio::Core::Game::FindItem (SELECTION_SCREEN_ITEM_CURSOR_JOYSTICK_TEXT, m_itemsList);
            break;
                
        case GAME_CONTROL_INTERFACE_II:
            itr = Folio::Core::Game::FindItem (SELECTION_SCREEN_ITEM_INTERFACE_II_TEXT, m_itemsList);
            break;
                
        default:
            break;
        } // Endswitch.

        if (itr != m_itemsList.end ())
        {
            // Get the selection screen's game control text item.
    
            Folio::Core::Game::TextItemPtr  item(std::dynamic_pointer_cast<Folio::Core::Game::TextItem> (*itr));

            // Invert the selection screen's game control text item.

            status = item->SetInvert (m_invertCurrentSelectionText, graphics, redrawCanvas);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus SelectionScreen::ProcessScreenFrameWaitingForSelection (UInt32 currentTickCount)
{
    // Play the main game music.

    FolioStatus status = PlayMainGameMusic ();
    
    // Have we finished playing the main game music?
    
    if (m_finishedPlayingMainGameMusic &&
        (status == ERR_SUCCESS))
    {
        // Yes. Have we set the initial frame tick count?

        if (!m_initialFrameTickCount)
        {
            // No. Note the initial frame tick count.

            m_initialFrameTickCount = currentTickCount;
        } // Endif.

        // Have we displayed the selection screen for long enough?

        else
        if (currentTickCount >= (m_initialFrameTickCount + MAX_DISPLAY_SCREEN_TIME))
        {
            // Yes. 
            
            m_initialFrameTickCount = 0;    // Reset.
            
            // Stop displaying the selection screen.

            StopDisplaying ();
        } // Endelseif.
            
    } // Endif.
    
    else
    if (m_initialFrameTickCount)
    {
        m_initialFrameTickCount = 0;    // Reset.
    } // Endelseif.

    return (status);
} // Endproc.


FolioStatus SelectionScreen::ProcessScreenFrameStartingGame (UInt32 currentTickCount)
{
    // Play the starting game music.

    FolioStatus status = PlayStartingGameMusic ();

    // Have we finished playing the starting game music?

    if (m_finishedPlayingStartingGameMusic && 
        (status == ERR_SUCCESS))
    {
        // Yes. Start the game.

        status = StartGame ();
    } // Endif.

    return (status);
} // Endproc.


FolioStatus SelectionScreen::ResetScreen ()
{                   
    FolioStatus status = ERR_SUCCESS;

    // Get the canvas graphics.

    Gdiplus::Graphics   *graphics = m_canvas->GetCanvasGraphics ();

    // Reset the selection screen items (reverse order for performance).

    bool    finished        = false;   // Initialise!
    bool    redrawCanvas    = false;

    for (Folio::Core::Game::ItemsList::reverse_iterator ritr = m_itemsList.rbegin ();
         !finished && (status == ERR_SUCCESS) && (ritr != m_itemsList.rend ());
         ++ritr)
    {
        // Get the selection screen item's identifier.

        SELECTION_SCREEN_ITEM_ID   itemId = static_cast<SELECTION_SCREEN_ITEM_ID> (ritr->get ()->GetItemId ());
         
        switch (itemId)
        {
        case SELECTION_SCREEN_ITEM_1_PLAYER_TEXT:
        case SELECTION_SCREEN_ITEM_2_PLAYER_TEXT:
        case SELECTION_SCREEN_ITEM_KEYBOARD_TEXT:
        case SELECTION_SCREEN_ITEM_KEMPSTON_JOYSTICK_TEXT:
        case SELECTION_SCREEN_ITEM_CURSOR_JOYSTICK_TEXT:
        case SELECTION_SCREEN_ITEM_INTERFACE_II_TEXT:
            {
                m_invertCurrentSelectionText = false;   // Reset.

                // Get the selection screen text item.

                Folio::Core::Game::TextItemPtr  item(std::dynamic_pointer_cast<Folio::Core::Game::TextItem> (*ritr));

                // Don't invert the selection screen text item's text.

                status = item->SetInvert (m_invertCurrentSelectionText, *graphics, redrawCanvas);

                // Finished?
            
                finished = (itemId == SELECTION_SCREEN_ITEM_1_PLAYER_TEXT);
            } // Endscope.
            break;

        default:
            break;
        } // Endswitch.

    } // Endfor.

    // Should the canvas be redrawn?

    if (redrawCanvas && (status == ERR_SUCCESS))
    {
        // Yes. The canvas should be redrawn on the next draw.

        m_canvas->SetRedrawRqd ();
    } // Endif.

    return (status);
} // Endproc.


FolioStatus SelectionScreen::StartingGame ()
{
    // Stop the main game music.

    StopMainGameMusic ();

    // The game is starting.

    m_isStartingGame    = true;
    m_isStartGame       = false;

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus SelectionScreen::StartGame ()
{
    // Stop the starting game music.

    StopStartingGameMusic ();

    // Let the information panel know the number of players.

    g_informationPanel->SetNumPlayers (m_numPlayers);

    // The game should start.

    m_isStartingGame    = false;
    m_isStartGame       = true;

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
        // Starting the game.

        status = StartingGame ();
    } // Endif.

    else
    if (gamepad.IsDPadUpButtonDown (m_controllerId))
    {
        // Decrement the game control.

        Int32   gameControl = static_cast<Int32> (m_gameControl);

        if (--gameControl < GAME_CONTROL_KEYBOARD)
        {
            gameControl = GAME_CONTROL_INTERFACE_II;
        } // Endif.

        // Set the game control.

        status = SetGameControl (static_cast<GAME_CONTROL> (gameControl));
    } // Endelseif.

    else
    if (gamepad.IsDPadDownButtonDown (m_controllerId))
    {
        // Increment the game control.
        
        Int32   gameControl = static_cast<Int32> (m_gameControl);

        if (++gameControl > GAME_CONTROL_INTERFACE_II)
        {
            gameControl = GAME_CONTROL_KEYBOARD;
        } // Endif.

        // Set the game control.
        
        status = SetGameControl (static_cast<GAME_CONTROL> (gameControl));
    } // Endelseif.

    else
    if (gamepad.IsDPadLeftButtonDown (m_controllerId))
    {
        // Decrement the number of players.

        UInt32  numPlayers = m_numPlayers;

        if (--numPlayers < 1)
        {
            numPlayers = 2;
        } // Endif.

        // Set the number of players.
        
        status = SetNumPlayers (numPlayers);
    } // Endelseif.

    else
    if (gamepad.IsDPadRightButtonDown (m_controllerId))
    {
        // Increment the number of players.
        
        UInt32  numPlayers = m_numPlayers;

        if (++numPlayers > 2)
        {
            numPlayers = 1;
        } // Endif.

        // Set the number of players.
        
        status = SetNumPlayers (numPlayers);
    } // Endelseif.

    return (status);
} // Endproc.


FolioStatus SelectionScreen::PlayMainGameMusic ()
{
    FolioStatus status = ERR_SUCCESS;

    // Have we finished playing the main game music?

    if (!m_finishedPlayingMainGameMusic)
    {
        // No. Play the main game music.

        status = g_musicJukebox.PlayMainGameMusic (m_finishedPlayingMainGameMusic);
    } // Endif.

    return (status);
} // Endproc.


void    SelectionScreen::StopMainGameMusic ()
{
    // Stop playing the main game music.

    g_musicJukebox.StopPlayingMusic ();

    m_finishedPlayingMainGameMusic = true;
} // Endproc.


FolioStatus SelectionScreen::PlayStartingGameMusic ()
{
    FolioStatus status = ERR_SUCCESS;

    // Have we finished playing the starting game music?

    if (!m_finishedPlayingStartingGameMusic)
    {
        // No. Play the starting game music.

        status = g_musicJukebox.PlayStartingGameMusic (m_finishedPlayingStartingGameMusic);
    } // Endif.

    return (status);
} // Endproc.


void    SelectionScreen::StopStartingGameMusic ()
{
    m_finishedPlayingStartingGameMusic = true;
} // Endproc.


void    SelectionScreen::SetItemText (Folio::Core::Game::TextItemPtr::element_type& item)
{
    switch (item.GetItemId ())
    {
    case SELECTION_SCREEN_ITEM_1_PLAYER_TEXT:
        item.GetGdiRasterText ()->SetTextString ("1  1 PLAYER GAME");
        break;

    case SELECTION_SCREEN_ITEM_2_PLAYER_TEXT:
        item.GetGdiRasterText ()->SetTextString ("2  2 PLAYER GAME");
        break;

    case SELECTION_SCREEN_ITEM_KEYBOARD_TEXT:
        item.GetGdiRasterText ()->SetTextString ("3  KEYBOARD");
        break;

    case SELECTION_SCREEN_ITEM_KEMPSTON_JOYSTICK_TEXT:
        item.GetGdiRasterText ()->SetTextString ("4  KEMPSTON JOYSTICK");
        break;

    case SELECTION_SCREEN_ITEM_CURSOR_JOYSTICK_TEXT:
        item.GetGdiRasterText ()->SetTextString ("5  CURSOR   JOYSTICK");
        break;

    case SELECTION_SCREEN_ITEM_INTERFACE_II_TEXT:
        item.GetGdiRasterText ()->SetTextString ("6  INTERFACE II");
        break;

    case SELECTION_SCREEN_ITEM_START_GAME_TEXT:
        item.GetGdiRasterText ()->SetTextString ("0  START GAME");
        break;

    case SELECTION_SCREEN_ITEM_COPYRIGHT_TEXT:
        item.GetGdiRasterText ()->SetTextString ("\x7f 1984  A.C.G.");
        break;

    default:
        break;
    } // Endswitch.

} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
