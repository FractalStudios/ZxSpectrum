// "Home-made" includes.
#include    "StdAfx.h"
#include    "Globals.h"
#include    "InformationPanel.h"
#include    "ScreenMap.h"
#include    "Ultimate.h"

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Player lives character map.
static  const   Folio::Core::Graphic::GdiRasterFont::CharacterMap   g_playerLivesCharacterMap =
{
//      char        FolioByteBuffer
    {   ' ',	    {   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, },  },
    {   'p',	    {   0x18, 0x24, 0x3c, 0x7e, 0x5a, 0x3c, 0x3c, 0x66, },  },
};

// Player lives character font.
static  Folio::Core::Graphic::GdiRasterFont g_playerLivesCharacterFont(1, 8, g_playerLivesCharacterMap);


// Information panel item attributes.
static  const   Folio::Core::Game::ItemAttributesList<INFORMATION_PANEL_ITEM_ID>    g_informationPanelAttributes =
{
//      m_itemId                                            m_screenXLeft           m_screenYTop        m_colour
    {   INFORMATION_PANEL_ITEM_PLAYER_1_UP,                 COLUMN_TO_PIXEL( 2),    ROW_TO_PIXEL( 0),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),                                                            },
    {   INFORMATION_PANEL_ITEM_PLAYER_1_SCORE,              COLUMN_TO_PIXEL( 1),    ROW_TO_PIXEL( 1),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW),                                                          },
    {   INFORMATION_PANEL_ITEM_PLAYER_1_LIVES,              COLUMN_TO_PIXEL( 7),    ROW_TO_PIXEL( 0),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),                                                           },
    {   INFORMATION_PANEL_ITEM_PLAYER_1_GRAPHIC_CHARACTER,  COLUMN_TO_PIXEL( 9),    ROW_TO_PIXEL( 0),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),                                                           },
    {   INFORMATION_PANEL_ITEM_HI_TEXT,                     COLUMN_TO_PIXEL(15),    ROW_TO_PIXEL( 0),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE) | SET_PAPER_COLOUR(Folio::Core::Game::ZxSpectrum::RED),    },
    {   INFORMATION_PANEL_ITEM_HI_SCORE,                    COLUMN_TO_PIXEL(13),    ROW_TO_PIXEL( 1),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW),                                                          },
    {   INFORMATION_PANEL_ITEM_PLAYER_2_LIVES,              COLUMN_TO_PIXEL(21),    ROW_TO_PIXEL( 0),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),                                                           },
    {   INFORMATION_PANEL_ITEM_PLAYER_2_GRAPHIC_CHARACTER,  COLUMN_TO_PIXEL(23),    ROW_TO_PIXEL( 0),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),                                                           },
    {   INFORMATION_PANEL_ITEM_PLAYER_2_UP,                 COLUMN_TO_PIXEL(27),    ROW_TO_PIXEL( 0),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),                                                            },
    {   INFORMATION_PANEL_ITEM_PLAYER_2_SCORE,              COLUMN_TO_PIXEL(25),    ROW_TO_PIXEL( 1),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW),                                                          },
};


// Information panel static members.
Folio::Core::Util::Sound::SoundSample   InformationPanel::m_startingSoundSample(Ultimate::CreateSoundSample (0x80, 0x10));  // The starting sound sample.

InformationPanel::InformationPanel (Folio::Core::Applet::Canvas& canvas)
:   m_canvas(canvas),
    m_informationPanelScreenRect(SCREEN_X_ORIGIN, SCREEN_Y_ORIGIN, SCREEN_WIDTH, SCREEN_HEIGHT),
    m_totalNumScreens(0),
    m_numPlayers(0),
    m_currentPlayer(PLAYER_1),
    m_invertPlayerText(false)
{
} // Endproc.


InformationPanel::~InformationPanel ()
{
} // Endproc.


FolioStatus InformationPanel::Create (UInt32 totalNumScreens)
{
    // Build the information panel items.

    FolioStatus status = BuildItems (m_canvas.GetCanvasDcHandle (), 
                                     m_canvas.GetAppletInstanceHandle ());

    if (status == ERR_SUCCESS)
    {
        // Note the information panel attributes.

        m_totalNumScreens = totalNumScreens;
    } // Endif.

    return (status);
} // Endproc.


FolioStatus InformationPanel::Start ()
{
    m_currentPlayer = PLAYER_1;

    // Reset the players' statistics.

    m_playerStatistics [PLAYER_1].Reset ();
    m_playerStatistics [PLAYER_2].Reset ();

    // Reset the players' starting attributes.

    m_playerStartingAtttributes [PLAYER_1].Reset ();
    m_playerStartingAtttributes [PLAYER_2].Reset ();

    // Clear the drawing list.

    m_drawingElementsList.clear ();

    // Build the information panel items.

    return (BuildItems (m_canvas.GetCanvasDcHandle (), 
                        m_canvas.GetAppletInstanceHandle ()));
} // Endproc.


FolioStatus InformationPanel::Draw ()
{
    // Clear the canvas rectangle occupied by the information panel.

    FolioStatus status = m_canvas.ClearCanvasRectangle (m_informationPanelScreenRect);

    if (status == ERR_SUCCESS)
    {
        // Have the information panel's drawing elements been built?

        if (m_drawingElementsList.empty ())
        {
            // No. Build the information panel drawing elements.

            status = BuildDrawingElements (m_canvas.GetCanvasDcHandle ());
        } // Endif.

        // Draw the information panel's drawing elements in the canvas.

        status = m_canvas.DrawDrawingElements (m_drawingElementsList);
    } // Endif.

    return (status);
} // Endproc.


FolioStatus InformationPanel::QueryItems (Folio::Core::Game::ItemsList& itemsList) const
{
    // Query the information panel items.

    for (Folio::Core::Game::ItemsList::const_iterator itr = m_itemsList.begin ();
         (itr != m_itemsList.end ());
         ++itr)
    {
        // Get the information panel item's identifier.

        INFORMATION_PANEL_ITEM_ID   itemId = static_cast<INFORMATION_PANEL_ITEM_ID> (itr->get ()->GetItemId ());
         
        switch (itemId)
        {
        case INFORMATION_PANEL_ITEM_PLAYER_1_UP:
        case INFORMATION_PANEL_ITEM_PLAYER_1_SCORE:
        case INFORMATION_PANEL_ITEM_HI_TEXT:
        case INFORMATION_PANEL_ITEM_HI_SCORE:
        case INFORMATION_PANEL_ITEM_PLAYER_2_UP:
        case INFORMATION_PANEL_ITEM_PLAYER_2_SCORE:
            itemsList.push_back (*itr);
            break;
        
        case INFORMATION_PANEL_ITEM_PLAYER_1_LIVES:
        case INFORMATION_PANEL_ITEM_PLAYER_1_GRAPHIC_CHARACTER:
            if (m_numPlayers >= 1)
            {
                itemsList.push_back (*itr);
            } // Endif.
            break;

        case INFORMATION_PANEL_ITEM_PLAYER_2_LIVES:
        case INFORMATION_PANEL_ITEM_PLAYER_2_GRAPHIC_CHARACTER:
            if (m_numPlayers == 2)
            {
                itemsList.push_back (*itr);
            } // Endif.
            break;

        default:
            break;
        } // Endswitch.

    } // Endfor.

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus InformationPanel::HandleProcessFrame (bool& isStarting) 
{
    FolioStatus status = ERR_SUCCESS;

    // Are we starting?

    if (isStarting)
    {
        // Yes. Check player up.

        status = CheckPlayerUp (Folio::Core::Util::DateTime::GetCurrentTickCount (), 
                                isStarting);

        // Have we started?

        if (!isStarting && (status == ERR_SUCCESS))
        {
            // Yes. The current player is now alive.

            g_playerSprite->SetAlive ();
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


void    InformationPanel::SetNumPlayers (UInt32 numPlayers)
{
    m_numPlayers = numPlayers;
} // Endproc.


void    InformationPanel::SetCurrentPlayer (PLAYER player)
{
    m_currentPlayer = player;
} // Endproc.


InformationPanel::PLAYER    InformationPanel::GetCurrentPlayer () const
{
    return (m_currentPlayer);
} // Endproc.


FolioStatus InformationPanel::AddPlayerScore (UInt32 score)
{
    // Add the current player's score.

    m_playerStatistics [m_currentPlayer].AddScore (score);

    // Update the score.

    return (Update (UPDATE_SCORE));
} // Endproc.
    

UInt32  InformationPanel::GetPlayerScore () const
{
    // Get the current player's score.

    return (m_playerStatistics [m_currentPlayer].GetScore ());
} // Endproc.


FolioStatus InformationPanel::IncrementPlayerLife (PlayerSpritePtr *playerSprite)
{
    // Increment the current player's lives.

    m_playerStatistics [m_currentPlayer].IncrementLives ();

    // Update the current player's lives.

    return (Update (UPDATE_LIVES));
} // Endproc.
    

FolioStatus InformationPanel::DecrementPlayerLife (PlayerSpritePtr *playerSprite)
{
    FolioStatus status = ERR_SUCCESS;

    // Decrement the current player's lives.

    m_playerStatistics [m_currentPlayer].DecrementLives ();

    if (playerSprite)
    {
        // Is the current player alive?

        if (m_playerStatistics [m_currentPlayer].IsAlive ())
        {
            // Yes. The current player is static.

            (*playerSprite)->SetState (PlayerSprite::STATE_STATIC);
        } // Endif.

        else
        {
            // No. The current player's game is over.

            (*playerSprite)->SetGameOver ();
        } // Endelse.

    } // Endif.

    // Update the current player's lives.

    return (Update (UPDATE_LIVES));
} // Endproc.
    

void    InformationPanel::IncrementPlayerNumScreensVisited ()
{
    // Increment the current player's number of screens visited.
  
    m_playerStatistics [m_currentPlayer].IncrementNumScreensVisited ();
} // Endproc.


UInt32  InformationPanel::GetPlayerPercentageGameCompleted () const
{
    // Calculate the percentage of the game the current player has completed.

    return (m_totalNumScreens ? 100 * m_playerStatistics [m_currentPlayer].GetNumScreensVisited () / m_totalNumScreens : 0);
} // Endproc.


void    InformationPanel::SetFoundAmuletPiece (OBJECT_SPRITE_ID objectSpriteId)
{
    switch (objectSpriteId)
    {
    case OBJECT_SPRITE_AMULET_PIECE_TOP_LEFT:
        // The current player has found the top-left amulet piece.

        m_playerStatistics [m_currentPlayer].SetFoundAmuletPieceTopLeft ();
        
        // Add to the player's score.

        AddPlayerScore (SCORE_AMULET_PIECE_FOUND);
        break;

    case OBJECT_SPRITE_AMULET_PIECE_TOP_RIGHT:    
        // The current player has found the top-right amulet piece.

        m_playerStatistics [m_currentPlayer].SetFoundAmuletPieceTopRight ();
        
        // Add to the player's score.

        AddPlayerScore (SCORE_AMULET_PIECE_FOUND);
        break;

    case OBJECT_SPRITE_AMULET_PIECE_BOTTOM_LEFT:  
        // The current player has found the bottom-left amulet piece.

        m_playerStatistics [m_currentPlayer].SetFoundAmuletPieceBottomLeft ();
        
        // Add to the player's score.

        AddPlayerScore (SCORE_AMULET_PIECE_FOUND);
        break;

    case OBJECT_SPRITE_AMULET_PIECE_BOTTOM_RIGHT: 
        // The current player has found the bottom-right amulet piece.

        m_playerStatistics [m_currentPlayer].SetFoundAmuletPieceBottomRight ();
        
        // Add to the player's score.

        AddPlayerScore (SCORE_AMULET_PIECE_FOUND);
        break;

    default:
        break;
    } // Endswitch.

} // Endproc.


bool    InformationPanel::IsFoundAmuletPieceTopLeft () const
{
    // Has the current player found the top-left amulet piece?

    return (m_playerStatistics [m_currentPlayer].IsFoundAmuletPieceTopLeft ());
} // Endproc.


bool    InformationPanel::IsFoundAmuletPieceTopRight () const
{
    // Has the current player found the top-right amulet piece?

    return (m_playerStatistics [m_currentPlayer].IsFoundAmuletPieceTopRight ());
} // Endproc.


bool    InformationPanel::IsFoundAmuletPieceBottomLeft () const
{
    // Has the current player found the bottom-left amulet piece?

    return (m_playerStatistics [m_currentPlayer].IsFoundAmuletPieceBottomLeft ());
} // Endproc.


bool    InformationPanel::IsFoundAmuletPieceBottomRight () const
{
    // Has the current player found the bottom-right amulet piece?

    return (m_playerStatistics [m_currentPlayer].IsFoundAmuletPieceBottomRight ());
} // Endproc.


UInt32  InformationPanel::GetNumFoundAmuletPieces () const
{
    // Get the number of amulet pieces the current player has found.

    return (m_playerStatistics [m_currentPlayer].GetNumFoundAmuletPieces ());
} // Endproc.


FolioNarrowString   InformationPanel::DescribeLives (Int32 lives)
{
    FolioNarrowOStringStream    str;

    if (lives > 0)
    {
        if (lives > 99)
        {
            str << std::setw(2) << std::setfill(' ') << 99;
        } // Endif.
        
        else
        {
            str << std::setw(2) << std::setfill(' ') << lives;
        } // Endelse.

    } // Endif.

    else
    {
        str << "  ";
    } // Endelse.

    return (str.str ());
} // Endproc.


FolioNarrowString   InformationPanel::DescribeLivesCharacter (Int32 lives)
{
    FolioNarrowOStringStream    str;

    if (lives > 0)
    {
        str << 'p';
    } // Endif.

    else
    {
        str << ' ';
    } // Endelse.

    return (str.str ());
} // Endproc.


FolioNarrowString   InformationPanel::DescribeScore (UInt32 score)
{
    FolioNarrowOStringStream    str;

    if (score > 999999)
    {
        str << std::setw(6) << std::setfill('0') << 999999;
    } // Endif.

    else
    {
        str << std::setw(6) << std::setfill('0') << score;
    } // Endelse.

    return (str.str ());
} // Endproc.


FolioNarrowString   InformationPanel::DescribePercentage (UInt32 percentage)
{
    FolioNarrowOStringStream    str;

    if (percentage < 10)
    {
        str << ' ' << std::setw(2) << std::setfill('0');
    } // Endif.

    else
    if (percentage < 100)
    {
        str << ' ';
    } // Endelseif.

    if (percentage > 100)
    {
        str << 100 << '%';
    } // Endif.

    else
    {
        str << percentage << '%';
    } // Endelse.

    return (str.str ());
} // Endproc.


FolioNarrowString   InformationPanel::DescribePlayer (PLAYER player)
{
    switch (player)
    {
    case PLAYER_2:
        return ("PLAYER 2");

    case PLAYER_1:
    default:
        return ("PLAYER 1");
    } // Endswitch.

} // Endproc.


FolioStatus InformationPanel::BuildItems (FolioHandle   dcHandle, 
                                          FolioHandle   instanceHandle)
{
    FolioStatus status = ERR_SUCCESS;

    m_itemsList.clear ();   // Initialise!

    // Build the information panel items. 

    for (Folio::Core::Game::ItemAttributesList<INFORMATION_PANEL_ITEM_ID>::const_iterator itr = g_informationPanelAttributes.begin (); 
         (status == ERR_SUCCESS) && (itr != g_informationPanelAttributes.end ());
         ++itr)
    {              
        // Build the information panel item.

        switch (itr->m_itemId)
        {
        case INFORMATION_PANEL_ITEM_PLAYER_1_UP:
        case INFORMATION_PANEL_ITEM_PLAYER_1_SCORE:
        case INFORMATION_PANEL_ITEM_PLAYER_1_LIVES:
        case INFORMATION_PANEL_ITEM_PLAYER_1_GRAPHIC_CHARACTER:
        case INFORMATION_PANEL_ITEM_HI_TEXT:
        case INFORMATION_PANEL_ITEM_HI_SCORE:
        case INFORMATION_PANEL_ITEM_PLAYER_2_LIVES:
        case INFORMATION_PANEL_ITEM_PLAYER_2_GRAPHIC_CHARACTER:
        case INFORMATION_PANEL_ITEM_PLAYER_2_UP:
        case INFORMATION_PANEL_ITEM_PLAYER_2_SCORE:
            { 
                // Create an information panel text item.

                Folio::Core::Game::TextItemPtr  item(new Folio::Core::Game::TextItemPtr::element_type);
                
                status = item->Create (dcHandle,
                                       Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_INFORMATION_PANEL_ITEM,
                                       ((itr->m_itemId == INFORMATION_PANEL_ITEM_PLAYER_1_GRAPHIC_CHARACTER) || 
                                        (itr->m_itemId == INFORMATION_PANEL_ITEM_PLAYER_2_GRAPHIC_CHARACTER)) 
                                       ? g_playerLivesCharacterFont : *Folio::Core::Game::ZxSpectrum::GetFont (),
                                       itr->m_itemId,
                                       itr->m_screenXLeft, 
                                       itr->m_screenYTop,
                                       Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE, 
                                       Folio::Core::Game::ZxSpectrum::MapInkColour (itr->m_colour),
                                       Folio::Core::Game::ZxSpectrum::MapPaperColour (itr->m_colour),
                                       ((itr->m_itemId == INFORMATION_PANEL_ITEM_PLAYER_1_UP) ||
                                        (itr->m_itemId == INFORMATION_PANEL_ITEM_PLAYER_2_UP)));

                if (status == ERR_SUCCESS)
                {
                    // Set the information panel item's text.

                    SetItemText (*item.get ());
            
                    // Store the information panel item in the information panel 
                    // items list.

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


FolioStatus InformationPanel::BuildDrawingElements (FolioHandle dcHandle)
{
    FolioStatus status = ERR_SUCCESS;

    m_drawingElementsList.clear (); // Initialise!

    // Query the drawing elements of the information panel items.

    for (Folio::Core::Game::ItemsList::const_iterator itr = m_itemsList.begin ();
         (status == ERR_SUCCESS) && (itr != m_itemsList.end ());
         ++itr)
    {
        // Query the information panel item's drawing elements.

        Folio::Core::Game::DrawingElementsList  itemDrawingElementsList;

        // Get the information panel item's identifier.

        INFORMATION_PANEL_ITEM_ID   itemId = static_cast<INFORMATION_PANEL_ITEM_ID> (itr->get ()->GetItemId ());
         
        switch (itemId)
        {
        case INFORMATION_PANEL_ITEM_PLAYER_1_UP:
        case INFORMATION_PANEL_ITEM_PLAYER_1_SCORE:
        case INFORMATION_PANEL_ITEM_HI_TEXT:
        case INFORMATION_PANEL_ITEM_HI_SCORE:
        case INFORMATION_PANEL_ITEM_PLAYER_2_UP:
        case INFORMATION_PANEL_ITEM_PLAYER_2_SCORE:
            {
                // Get the information panel text item.

                Folio::Core::Game::TextItemPtr  item(std::dynamic_pointer_cast<Folio::Core::Game::TextItem> (*itr));

                // Get the information panel item's drawing elements.
                
                itemDrawingElementsList = item->GetDrawingElementsList ();
            } // Endscope.
            break;
        
        case INFORMATION_PANEL_ITEM_PLAYER_1_LIVES:
        case INFORMATION_PANEL_ITEM_PLAYER_1_GRAPHIC_CHARACTER:
            if (m_numPlayers >= 1)
            {
                // Get the information panel text item.

                Folio::Core::Game::TextItemPtr  item(std::dynamic_pointer_cast<Folio::Core::Game::TextItem> (*itr));

                // Get the information panel item's drawing elements.
                
                itemDrawingElementsList = item->GetDrawingElementsList ();
            } // Endif.
            break;

        case INFORMATION_PANEL_ITEM_PLAYER_2_LIVES:
        case INFORMATION_PANEL_ITEM_PLAYER_2_GRAPHIC_CHARACTER:
            if (m_numPlayers == 2)
            {
                // Get the information panel text item.

                Folio::Core::Game::TextItemPtr  item(std::dynamic_pointer_cast<Folio::Core::Game::TextItem> (*itr));

                // Get the information panel item's drawing elements.
                
                itemDrawingElementsList = item->GetDrawingElementsList ();
            } // Endif.
            break;

        default:
            status = ERR_INVALID;
            break;
        } // Endswitch.

        if (status == ERR_SUCCESS)
        {
            // Add the information panel item's drawing elements to the drawing elements list.

            m_drawingElementsList.insert (m_drawingElementsList.end (), 
                                          itemDrawingElementsList.begin (),
                                          itemDrawingElementsList.end ()); 
        } // Endif.

    } // Endfor.

    if (status != ERR_SUCCESS)
    {
        m_drawingElementsList.clear ();
    } // Endif.

    return (status);
} // Endproc.


FolioStatus InformationPanel::CheckPlayerUp (UInt32 currentTickCount, 
                                             bool&  isStarting)
{                     
    static  const   UINT32  MAX_STARTING_COUNT = 7;

    FolioStatus status = ERR_SUCCESS;

    // Is this the first in the starting game sequence?

    if (m_playerStartingAtttributes [m_currentPlayer].m_startingCounter == 0)
    {
        // Yes. The current player is starting a game. 

        ++m_playerStartingAtttributes [m_currentPlayer].m_startingCounter;
        
        // Set the current player's starting previous frame tick count.

        m_playerStartingAtttributes [m_currentPlayer].m_startingPreviousFrameTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount ();
    } // Endif.

    // Should we update the information panel, i.e. has the current tick count 
    // exceeded the flash rate since the last update?

    else
    if (currentTickCount >= (m_playerStartingAtttributes [m_currentPlayer].m_startingPreviousFrameTickCount + Folio::Core::Game::ZxSpectrum::FLASH_MILLISECONDS))
    {
        // Yes. Set the current player's starting previous frame tick count.

        m_playerStartingAtttributes [m_currentPlayer].m_startingPreviousFrameTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount ();

        // Update the information panel.

        status = Update (UPDATE_FLASH_PLAYER_UP);

        if (status == ERR_SUCCESS)
        {
            // Play the starting sound.

            status = Folio::Core::Util::Sound::PlaySoundSample (m_startingSoundSample,
                                                                false); // Play synchronously.

            if (status == ERR_SUCCESS)
            {
                // Have we started?
                                                                                
                if (++m_playerStartingAtttributes [m_currentPlayer].m_startingCounter > MAX_STARTING_COUNT)
                {
                    // Yes. We are no longer starting.

                    isStarting = false;

                    // Reset starting counter.

                    m_playerStartingAtttributes [m_currentPlayer].m_startingCounter = 0;

                    // Reset the information panel.

                    status = Reset ();
                } // Endif.
        
            } // Endif.
        
        } // Endif.

    } // Endelseif.

    return (status);
} // Endproc.


FolioStatus InformationPanel::Update (UPDATE update)
{
    FolioStatus status = ERR_SUCCESS;

    // Get the canvas graphics.

    Gdiplus::Graphics   *graphics = m_canvas.GetCanvasGraphics ();

    // Update the information panel items (depending on the type of update required).

    bool    redrawCanvas = false;   // Initialise!

    switch (update)
    {
    case UPDATE_LIVES:
        status = UpdateLives (*graphics, redrawCanvas);
        break;
    
    case UPDATE_SCORE:
        status = UpdateScore (*graphics, redrawCanvas);
        break;
    
    case UPDATE_FLASH_PLAYER_UP:
        status = UpdateFlashPlayerUp (*graphics, redrawCanvas);
        break;

    default:
        status = ERR_INVALID;
        break;
    } // Endswitch.

    // Should the canvas be redrawn?

    if (redrawCanvas && (status == ERR_SUCCESS))
    {
        // Yes. The canvas should be redrawn on the next draw.

        m_canvas.SetRedrawRqd ();
    } // Endif.

    return (status);
} // Endproc.


FolioStatus InformationPanel::UpdateLives (Gdiplus::Graphics&   graphics,
                                           bool&                redrawCanvas)
{
    redrawCanvas = false;   // Initialise!

    FolioStatus status = ERR_SUCCESS;

    bool    finished = false;   // Initialise!

    for (Folio::Core::Game::ItemsList::iterator itr = m_itemsList.begin ();
         !finished && (status == ERR_SUCCESS) && (itr != m_itemsList.end ());
         ++itr)
    {
        // Get the information panel item's identifier.

        INFORMATION_PANEL_ITEM_ID   itemId = static_cast<INFORMATION_PANEL_ITEM_ID> (itr->get ()->GetItemId ());
         
        if ((((itemId == INFORMATION_PANEL_ITEM_PLAYER_1_LIVES) || (itemId == INFORMATION_PANEL_ITEM_PLAYER_1_GRAPHIC_CHARACTER)) &&
               (m_currentPlayer == PLAYER_1)) ||
            (((itemId == INFORMATION_PANEL_ITEM_PLAYER_2_LIVES) || (itemId == INFORMATION_PANEL_ITEM_PLAYER_2_GRAPHIC_CHARACTER)) &&
               (m_currentPlayer == PLAYER_2)))
        {
            // Get the information panel text item.

            Folio::Core::Game::TextItemPtr  item(std::dynamic_pointer_cast<Folio::Core::Game::TextItem> (*itr));

            // Set the information panel text item's text.

            SetItemText (*item);

            // Draw the information panel text item.

            status = item->Draw (graphics);

            redrawCanvas = true;

            // Finished?

            finished = (((itemId == INFORMATION_PANEL_ITEM_PLAYER_1_GRAPHIC_CHARACTER) && (m_currentPlayer == PLAYER_1)) ||
                        ((itemId == INFORMATION_PANEL_ITEM_PLAYER_2_GRAPHIC_CHARACTER) && (m_currentPlayer == PLAYER_2)));
        } // Endif.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus InformationPanel::UpdateScore (Gdiplus::Graphics&   graphics,
                                           bool&                redrawCanvas)
{
    redrawCanvas = false;   // Initialise!

    FolioStatus status = ERR_SUCCESS;

    bool    finished = false;   // Initialise!

    for (Folio::Core::Game::ItemsList::iterator itr = m_itemsList.begin ();
         !finished && (status == ERR_SUCCESS) && (itr != m_itemsList.end ());
         ++itr)
    {
        // Get the information panel item's identifier.

        INFORMATION_PANEL_ITEM_ID   itemId = static_cast<INFORMATION_PANEL_ITEM_ID> (itr->get ()->GetItemId ());
         
        if (((itemId == INFORMATION_PANEL_ITEM_PLAYER_1_SCORE) && (m_currentPlayer == PLAYER_1)) ||
            ((itemId == INFORMATION_PANEL_ITEM_PLAYER_2_SCORE) && (m_currentPlayer == PLAYER_2)))
        {
            // Get the information panel text item.

            Folio::Core::Game::TextItemPtr  item(std::dynamic_pointer_cast<Folio::Core::Game::TextItem> (*itr));

            // Set the information panel text item's text.

            SetItemText (*item);

            // Draw the information panel text item.

            status = item->Draw (graphics);

            redrawCanvas = true;

            // Finished.
            
            finished = true;
        } // Endif.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus InformationPanel::UpdateFlashPlayerUp (Gdiplus::Graphics&   graphics,
                                                   bool&                redrawCanvas)
{
    redrawCanvas = false; // Initialise!

    FolioStatus status = ERR_SUCCESS;

    bool    finished = false;   // Initialise!

    for (Folio::Core::Game::ItemsList::iterator itr = m_itemsList.begin ();
         !finished && (status == ERR_SUCCESS) && (itr != m_itemsList.end ());
         ++itr)
    {
        // Get the information panel item's identifier.

        INFORMATION_PANEL_ITEM_ID   itemId = static_cast<INFORMATION_PANEL_ITEM_ID> (itr->get ()->GetItemId ());
         
        if (((itemId == INFORMATION_PANEL_ITEM_PLAYER_1_UP) && (m_currentPlayer == PLAYER_1)) ||
            ((itemId == INFORMATION_PANEL_ITEM_PLAYER_2_UP) && (m_currentPlayer == PLAYER_2)))
        {
            // Invert the information panel text item's text.

            m_invertPlayerText = !m_invertPlayerText;

            // Get the information panel text item.

            Folio::Core::Game::TextItemPtr  item(std::dynamic_pointer_cast<Folio::Core::Game::TextItem> (*itr));

            // Invert the information panel text item.

            status = item->SetInvert (m_invertPlayerText, graphics, redrawCanvas);

            // Finished.

            finished = true;
        } // Endif.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus InformationPanel::Reset ()
{                   
    FolioStatus status = ERR_SUCCESS;

    // Get the canvas graphics.

    Gdiplus::Graphics   *graphics = m_canvas.GetCanvasGraphics ();

    // Reset the information panel items.

    bool    finished        = false;   // Initialise!
    bool    redrawCanvas    = false;

    for (Folio::Core::Game::ItemsList::iterator itr = m_itemsList.begin ();
         !finished && (status == ERR_SUCCESS) && (itr != m_itemsList.end ());
         ++itr)
    {
        // Get the information panel item's identifier.

        INFORMATION_PANEL_ITEM_ID   itemId = static_cast<INFORMATION_PANEL_ITEM_ID> (itr->get ()->GetItemId ());
         
        switch (itemId)
        {
        case INFORMATION_PANEL_ITEM_PLAYER_1_UP:
        case INFORMATION_PANEL_ITEM_PLAYER_2_UP:
            {
                m_invertPlayerText = false; // Reset.

                // Get the information panel text item.

                Folio::Core::Game::TextItemPtr  item(std::dynamic_pointer_cast<Folio::Core::Game::TextItem> (*itr));

                // Don't invert the information panel text item's text.

                status = item->SetInvert (m_invertPlayerText, *graphics, redrawCanvas);

                // Finished?
            
                finished = (itemId == INFORMATION_PANEL_ITEM_PLAYER_2_UP);
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

        m_canvas.SetRedrawRqd ();
    } // Endif.

    return (status);
} // Endproc.


void    InformationPanel::SetItemText (Folio::Core::Game::TextItemPtr::element_type& item)
{
    switch (item.GetItemId ())
    {
    case INFORMATION_PANEL_ITEM_PLAYER_1_UP:
        item.GetGdiRasterText ()->SetTextString ("1UP");
        break;

    case INFORMATION_PANEL_ITEM_PLAYER_1_SCORE:
        item.GetGdiRasterText ()->SetTextString (DescribeScore (m_playerStatistics [PLAYER_1].GetScore ()));
        break;

    case INFORMATION_PANEL_ITEM_PLAYER_1_LIVES:
        item.GetGdiRasterText ()->SetTextString (DescribeLives (m_playerStatistics [PLAYER_1].GetLives ()));
        break;

    case INFORMATION_PANEL_ITEM_PLAYER_1_GRAPHIC_CHARACTER:
        item.GetGdiRasterText ()->SetTextString (DescribeLivesCharacter (m_playerStatistics [PLAYER_1].GetLives ()));
        break;

    case INFORMATION_PANEL_ITEM_HI_TEXT:
        item.GetGdiRasterText ()->SetTextString ("HI");
        break;

    case INFORMATION_PANEL_ITEM_HI_SCORE:
        item.GetGdiRasterText ()->SetTextString (DescribeScore (g_highScoreTable.GetHighestScore ()));
        break;

    case INFORMATION_PANEL_ITEM_PLAYER_2_LIVES:
        item.GetGdiRasterText ()->SetTextString (DescribeLives (m_playerStatistics [PLAYER_2].GetLives ()));
        break;

    case INFORMATION_PANEL_ITEM_PLAYER_2_GRAPHIC_CHARACTER:
        item.GetGdiRasterText ()->SetTextString (DescribeLivesCharacter (m_playerStatistics [PLAYER_2].GetLives ()));
        break;

    case INFORMATION_PANEL_ITEM_PLAYER_2_UP:
        item.GetGdiRasterText ()->SetTextString ("2UP");
        break;

    case INFORMATION_PANEL_ITEM_PLAYER_2_SCORE:
        item.GetGdiRasterText ()->SetTextString (DescribeScore (m_playerStatistics [PLAYER_2].GetScore ()));
        break;

    default:
        break;
    } // Endswitch.

} // Endproc.


FolioStatus CreateInformationPanel (Folio::Core::Applet::Canvas&    canvas, 
                                    InformationPanelPtr&            informationPanel)
{
    // Create the information panel.

    informationPanel.reset (new InformationPanelPtr::element_type(canvas));

    return (informationPanel->Create (ScreenMap::GetTotalNumScreens ()));
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
