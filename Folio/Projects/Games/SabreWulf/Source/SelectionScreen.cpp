// "Home-made" includes.
#include    "StdAfx.h"
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


SelectionScreen::SelectionScreen (const InformationPanelPtr &informationPanel)
:   m_informationPanel(informationPanel),
    m_isStartGame(false),
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

    if (numPlayers != m_numPlayers)
    {
        // Set the number of players.

        m_numPlayers = numPlayers;

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


UInt32  SelectionScreen::GetNumPlayers () const
{
    return (m_numPlayers);
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


bool    SelectionScreen::IsPlayerDirectionKeyDown (Folio::Core::Game::APlayerSprite::Direction &direction) const
{
    direction = Folio::Core::Game::APlayerSprite::NO_DIRECTION; // Initialise!

    switch (m_gameControl)
    {
    case GAME_CONTROL_KEMPSTON_JOYSTICK:
        {
            // Get the gamepad.

            Folio::Core::Game::Gamepad  &gamepad(*m_canvas->GetCanvasGamepad ());
    
            if (gamepad.IsDPadUpButtonDown (m_controllerId))
            {
                direction = Folio::Core::Game::APlayerSprite::N;
            } // Endif.

            else
            if (gamepad.IsDPadDownButtonDown (m_controllerId))
            {
                direction = Folio::Core::Game::APlayerSprite::S;
            } // Endelseif.

            if (gamepad.IsDPadRightButtonDown (m_controllerId))
            {
                direction |= Folio::Core::Game::APlayerSprite::E;
            } // Endif.

            else
            if (gamepad.IsDPadLeftButtonDown (m_controllerId))
            {
                direction |= Folio::Core::Game::APlayerSprite::W;
            } // Endelseif.
    
        } // Endscope.
        break;

    case GAME_CONTROL_CURSOR_JOYSTICK:
        if (Folio::Core::Util::KeyInput::IsKeyDown (VK_UP))
        {
            direction = Folio::Core::Game::APlayerSprite::N;
        } // Endif.

        else
        if (Folio::Core::Util::KeyInput::IsKeyDown (VK_DOWN))
        {
            direction = Folio::Core::Game::APlayerSprite::S;
        } // Endelseif.

        if (Folio::Core::Util::KeyInput::IsKeyDown (VK_RIGHT))
        {
            direction |= Folio::Core::Game::APlayerSprite::E;
        } // Endif.

        else
        if (Folio::Core::Util::KeyInput::IsKeyDown (VK_LEFT))
        {
            direction |= Folio::Core::Game::APlayerSprite::W;
        } // Endelseif.
        break;

    case GAME_CONTROL_KEYBOARD:
    case GAME_CONTROL_INTERFACE_II:
    default:
        if (Folio::Core::Util::KeyInput::IsKeyDown ('R'))
        {
            direction = Folio::Core::Game::APlayerSprite::N;
        } // Endif.

        else
        if (Folio::Core::Util::KeyInput::IsKeyDown ('E'))
        {
            direction = Folio::Core::Game::APlayerSprite::S;
        } // Endelseif.

        if (Folio::Core::Util::KeyInput::IsKeyDown ('W'))
        {
            direction |= Folio::Core::Game::APlayerSprite::E;
        } // Endif.

        else
        if (Folio::Core::Util::KeyInput::IsKeyDown ('Q'))
        {
            direction |= Folio::Core::Game::APlayerSprite::W;
        } // Endelseif.
        break;
    } // Endswitch.

    return (direction != Folio::Core::Game::APlayerSprite::NO_DIRECTION);
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

            m_informationPanel->SetNumPlayers (0);

            // Query the information panel's items.

            status = m_informationPanel->QueryItems (m_itemsList);
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
            { 
                // Create a selection screen text item.

                Folio::Core::Game::TextItemPtr  item(new Folio::Core::Game::TextItemPtr::element_type);
                
                status = item->Create (dcHandle,
                                       DRAWING_ELEMENT_SELECTION_SCREEN_ITEM,
                                       *Folio::Core::Game::ZxSpectrum::GetFont (),
                                       itr->m_itemId,
                                       itr->m_screenXLeft, 
                                       itr->m_screenYTop,
                                       Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE, 
                                       Folio::Core::Game::ZxSpectrum::MapInkColour (itr->m_colour));

                if (status == ERR_SUCCESS)
                {
                    // Set the selection screen item's text.

                    SetItemText (*item.get ());
            
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
        status = SetNumPlayers (1);
    } // Endelseif.

    else
    if (Folio::Core::Util::KeyInput::IsKeyDown ('2'))
    {
        status = SetNumPlayers (2);
    } // Endelseif.

    else
    if (Folio::Core::Util::KeyInput::IsKeyDown ('3'))
    {
        status = SetGameControl (GAME_CONTROL_KEYBOARD);
    } // Endelseif.

    else
    if (Folio::Core::Util::KeyInput::IsKeyDown ('4'))
    {
        status = SetGameControl (GAME_CONTROL_KEMPSTON_JOYSTICK);
    } // Endelseif.

    else
    if (Folio::Core::Util::KeyInput::IsKeyDown ('5'))
    {
        status = SetGameControl (GAME_CONTROL_CURSOR_JOYSTICK);
    } // Endelseif.

    else
    if (Folio::Core::Util::KeyInput::IsKeyDown ('6'))
    {
        status = SetGameControl (GAME_CONTROL_INTERFACE_II);
    } // Endelseif.

    else
    {
        // Process the gamepad.

        status = ProcessGamepad ();
    } // Endelse.

    return (status);
} // Endproc.


FolioStatus SelectionScreen::ProcessScreenFrame (UInt32 *frameRateIncrement)
{
    FolioStatus status = ERR_SUCCESS;

    // Get the current tick count.

    UInt32  currentTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount ();

    if (currentTickCount >= (m_initialFrameTickCount + MAX_DISPLAY_SCREEN_TIME))
    {
        m_isStartGame = false;   // Timeout.

        // Stop displaying the selection screen.

        StopDisplaying ();
    } // Endif.

    else
    if (currentTickCount >= (m_previousFrameTickCount + Folio::Core::Game::ZxSpectrum::FLASH_MILLISECONDS))
    {
        // Update the selection screen.

        status = UpdateScreen ();

        if (status == ERR_SUCCESS)
        {
            // Note the previous frame tick count.

            m_previousFrameTickCount = currentTickCount;
        } // Endif.

    } // Endelseif.

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
        case SELECTION_SCREEN_ITEM_1_PLAYER_TEXT:
        case SELECTION_SCREEN_ITEM_2_PLAYER_TEXT:
            {
                bool    invertColours = false;  // Initialise!

                switch (m_numPlayers)
                {
                case 2:
                    invertColours = (itemId == SELECTION_SCREEN_ITEM_2_PLAYER_TEXT);
                    break;
                case 1:
                default:
                    invertColours = (itemId == SELECTION_SCREEN_ITEM_1_PLAYER_TEXT);
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

        case SELECTION_SCREEN_ITEM_KEYBOARD_TEXT:
        case SELECTION_SCREEN_ITEM_KEMPSTON_JOYSTICK_TEXT:
        case SELECTION_SCREEN_ITEM_CURSOR_JOYSTICK_TEXT:
        case SELECTION_SCREEN_ITEM_INTERFACE_II_TEXT:
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
                case GAME_CONTROL_INTERFACE_II:
                    invertColours = (itemId == SELECTION_SCREEN_ITEM_INTERFACE_II_TEXT);
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
        case SELECTION_SCREEN_ITEM_1_PLAYER_TEXT:
        case SELECTION_SCREEN_ITEM_2_PLAYER_TEXT:
        case SELECTION_SCREEN_ITEM_KEYBOARD_TEXT:
        case SELECTION_SCREEN_ITEM_KEMPSTON_JOYSTICK_TEXT:
        case SELECTION_SCREEN_ITEM_CURSOR_JOYSTICK_TEXT:
        case SELECTION_SCREEN_ITEM_INTERFACE_II_TEXT:
            {
                // Get the selection screen text item.

                Folio::Core::Game::TextItemPtr  item(std::dynamic_pointer_cast<Folio::Core::Game::TextItem> (*itr));

                // Update the selection screen text item.
            
                status = UpdateTextItem (*item,
                                         false, // Don't invert colours.
                                         *graphics,
                                         redrawCanvas);

                // Finished?
            
                finished = (itemId == SELECTION_SCREEN_ITEM_INTERFACE_II_TEXT);
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
        // Yes. Invert the text item's colours

        gdiRasterText->InvertColours ();

        // Draw it.

        status = gdiRasterText->Draw (item.GetScreenXLeft (), 
                                      item.GetScreenYTop (), 
                                      graphics);

        if (status == ERR_SUCCESS)
        {
            redrawCanvas = true;
        } // Endif.

    } // Endif.

    else
    if (!invertColours && gdiRasterText->IsInvertedColours ())
    {
        // No. Reset the text item's colours

        gdiRasterText->ResetColours ();

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


FolioStatus SelectionScreen::StartGame ()
{
    // Let the information panel know the number of players.

    m_informationPanel->SetNumPlayers (m_numPlayers);

    m_isStartGame = true;   // Good to go.

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
        // Increment the number of player.
        
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

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
