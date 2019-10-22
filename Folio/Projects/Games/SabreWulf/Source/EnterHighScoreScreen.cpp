// "Home-made" includes.
#include    "StdAfx.h"
#include    "EnterHighScoreScreen.h"

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Enter high score screen item attributes.
static  const   Folio::Core::Game::ItemAttributesList<ENTER_HIGH_SCORE_SCREEN_ITEM_ID>    g_highScoreScreenAttributes =
{
//      m_itemId                                                m_screenXLeft           m_screenYTop        m_colour
    {   ENTER_HIGH_SCORE_SCREEN_ITEM_INFORMATION_PANEL,         0,                       0,                 Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       },
    {   ENTER_HIGH_SCORE_SCREEN_ITEM_BORDER,                    0,                      16,                 Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       },
    {   ENTER_HIGH_SCORE_SCREEN_ITEM_CONGRATULATIONS_TEXT,      COLUMN_TO_PIXEL( 8),    ROW_TO_PIXEL( 5),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    },
    {   ENTER_HIGH_SCORE_SCREEN_ITEM_PLAYER_TEXT,               COLUMN_TO_PIXEL(12),    ROW_TO_PIXEL( 7),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    },
    {   ENTER_HIGH_SCORE_SCREEN_ITEM_YOU_HAVE_ACHIEVED_TEXT,    COLUMN_TO_PIXEL( 7),    ROW_TO_PIXEL( 9),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    },
    {   ENTER_HIGH_SCORE_SCREEN_ITEM_TODAYS_TEXT,               COLUMN_TO_PIXEL( 6),    ROW_TO_PIXEL(11),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    },
    {   ENTER_HIGH_SCORE_SCREEN_ITEM_POSITION,                  COLUMN_TO_PIXEL(14),    ROW_TO_PIXEL(11),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    },
    {   ENTER_HIGH_SCORE_SCREEN_ITEM_HIGHEST_TEXT,              COLUMN_TO_PIXEL(18),    ROW_TO_PIXEL(11),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    },
    {   ENTER_HIGH_SCORE_SCREEN_ITEM_SCORE_TEXT,                COLUMN_TO_PIXEL(13),    ROW_TO_PIXEL(13),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    },
    {   ENTER_HIGH_SCORE_SCREEN_ITEM_REGISTER_TEXT,             COLUMN_TO_PIXEL( 8),    ROW_TO_PIXEL(15),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::MAGENTA), },
    {   ENTER_HIGH_SCORE_SCREEN_ITEM_YOUR_INITIALS_TEXT,        COLUMN_TO_PIXEL( 9),    ROW_TO_PIXEL(17),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::MAGENTA), },
    {   ENTER_HIGH_SCORE_SCREEN_ITEM_INITIAL_INPUT_1,           COLUMN_TO_PIXEL(13),    ROW_TO_PIXEL(19),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),    },
    {   ENTER_HIGH_SCORE_SCREEN_ITEM_INITIAL_INPUT_2,           COLUMN_TO_PIXEL(15),    ROW_TO_PIXEL(19),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),    },
    {   ENTER_HIGH_SCORE_SCREEN_ITEM_INITIAL_INPUT_3,           COLUMN_TO_PIXEL(17),    ROW_TO_PIXEL(19),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),    },
};


EnterHighScoreScreen::EnterHighScoreScreen (const InformationPanelPtr   &informationPanel,
                                            const SelectionScreenPtr    &selectionScreen,
                                            HighScoreTable              &highScoreTable)
:   m_informationPanel(informationPanel),
    m_selectionScreen(selectionScreen),
    m_highScoreTable(highScoreTable),
    m_currentInitial(' ')
{
} // Endproc.


EnterHighScoreScreen::~EnterHighScoreScreen ()
{
} // Endproc.


FolioStatus EnterHighScoreScreen::BuildScreenItems (FolioHandle dcHandle, 
                                                    FolioHandle instanceHandle)
{                               
    FolioStatus status = ERR_SUCCESS;

    // Build the enter high score screen items. 

    for (Folio::Core::Game::ItemAttributesList<ENTER_HIGH_SCORE_SCREEN_ITEM_ID>::const_iterator itr = g_highScoreScreenAttributes.begin (); 
         (status == ERR_SUCCESS) && (itr != g_highScoreScreenAttributes.end ());
         ++itr)
    {              
        // Build the enter high score screen item.

        switch (itr->m_itemId)
        {
        case ENTER_HIGH_SCORE_SCREEN_ITEM_INFORMATION_PANEL:
            // No players.

            m_informationPanel->SetNumPlayers (0);

            // Query the information panel's items.

            status = m_informationPanel->QueryItems (m_itemsList);
            break;

        case ENTER_HIGH_SCORE_SCREEN_ITEM_BORDER:
            // Add the border screen's items.
            
            status = AddBorderScreenItems (dcHandle, instanceHandle);
            break;

        case ENTER_HIGH_SCORE_SCREEN_ITEM_CONGRATULATIONS_TEXT:
        case ENTER_HIGH_SCORE_SCREEN_ITEM_PLAYER_TEXT:
        case ENTER_HIGH_SCORE_SCREEN_ITEM_YOU_HAVE_ACHIEVED_TEXT:
        case ENTER_HIGH_SCORE_SCREEN_ITEM_TODAYS_TEXT:
        case ENTER_HIGH_SCORE_SCREEN_ITEM_POSITION:
        case ENTER_HIGH_SCORE_SCREEN_ITEM_HIGHEST_TEXT:      
        case ENTER_HIGH_SCORE_SCREEN_ITEM_SCORE_TEXT:        
        case ENTER_HIGH_SCORE_SCREEN_ITEM_REGISTER_TEXT:     
        case ENTER_HIGH_SCORE_SCREEN_ITEM_YOUR_INITIALS_TEXT:     
        case ENTER_HIGH_SCORE_SCREEN_ITEM_INITIAL_INPUT_1:   
        case ENTER_HIGH_SCORE_SCREEN_ITEM_INITIAL_INPUT_2:   
        case ENTER_HIGH_SCORE_SCREEN_ITEM_INITIAL_INPUT_3:   
            { 
                // Create an enter high score screen text item.

                Folio::Core::Game::TextItemPtr  item(new Folio::Core::Game::TextItemPtr::element_type);
                
                status = item->Create (dcHandle,
                                       DRAWING_ELEMENT_ENTER_HIGH_SCORE_SCREEN_ITEM,
                                       *Folio::Core::Game::ZxSpectrum::GetFont (),
                                       itr->m_itemId,
                                       itr->m_screenXLeft, 
                                       itr->m_screenYTop,
                                       Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE, 
                                       Folio::Core::Game::ZxSpectrum::MapInkColour (itr->m_colour));

                if (status == ERR_SUCCESS)
                {
                    // Set the enter high score screen item's text.

                    SetItemText (*item.get ());
            
                    // Store the enter high score screen item in the enter high score screen items list.

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


FolioStatus EnterHighScoreScreen::ProcessScreenInput ()
{
    FolioStatus status = ERR_SUCCESS;

    Folio::Core::Game::APlayerSprite::Direction direction =  
        Folio::Core::Game::APlayerSprite::NO_DIRECTION; // Initialise!

    if (m_selectionScreen->IsPlayerDirectionKeyDown (direction))
    {
        // Yes. 
        
        switch (direction)
        {
        case Folio::Core::Game::APlayerSprite::E:
            // Update the initial.

            if (m_currentInitial == ' ')
            {
                m_currentInitial = 'A';
            } // Endif.

            else
            if (++m_currentInitial > 'Z') 
            {
                m_currentInitial = ' ';
            } // Endelseif.

            // Update the screen.

            status = UpdateScreen ();
            break;

        case Folio::Core::Game::APlayerSprite::W:
            // Update the initial.

            if (m_currentInitial == ' ')
            {
                m_currentInitial = 'Z';
            } // Endif.

            else
            if (--m_currentInitial < 'A') 
            {
                m_currentInitial = ' ';
            } // Endelseif.

            // Update the screen.

            status = UpdateScreen ();
            break;

        default:
            break;
        } // Endswitch.

    } // Endif.

    else
    if (m_selectionScreen->IsPlayerFireKeyDown ())
    {
        // Add the current initial to the high score.

        m_highScore.m_initials += m_currentInitial;

        // Have the required initials been entered?

        if (m_highScore.m_initials.size () == 3)
        {
            // Yes. Add the high score to the high score table.

            m_highScore.m_score = m_informationPanel->GetScore ();

            m_highScoreTable.AddHighScore (m_highScore);

            // Stop displaying the enter high score screen.

            StopDisplaying ();
        } // Endif.

        else
        {
            // No. Initialise the current initial.

            m_currentInitial = ' ';
        } // Endelse.

    } // Endelseif.

    return (status);
} // Endproc.


FolioStatus EnterHighScoreScreen::UpdateScreen ()
{
    FolioStatus status = ERR_SUCCESS;

    // Get the canvas graphics.

    Gdiplus::Graphics   *graphics = m_canvas->GetCanvasGraphics ();

    // Update the enter high score screen items.

    bool    finished        = false;   // Initialise!
    bool    redrawCanvas    = false;

    for (Folio::Core::Game::ItemsList::iterator itr = m_itemsList.begin ();
         !finished && (status == ERR_SUCCESS) && (itr != m_itemsList.end ());
         ++itr)
    {
        // Get the enter high score screen item's identifier.

        SELECTION_SCREEN_ITEM_ID    itemId = static_cast<SELECTION_SCREEN_ITEM_ID> (itr->get ()->GetItemId ());
         
        switch (itemId)
        {
        case ENTER_HIGH_SCORE_SCREEN_ITEM_INITIAL_INPUT_1:   
        case ENTER_HIGH_SCORE_SCREEN_ITEM_INITIAL_INPUT_2:   
        case ENTER_HIGH_SCORE_SCREEN_ITEM_INITIAL_INPUT_3:   
            if (m_highScore.m_initials.size () == (itemId - ENTER_HIGH_SCORE_SCREEN_ITEM_INITIAL_INPUT_1))
            {
                Folio::Core::Game::TextItemPtr  item(std::dynamic_pointer_cast<Folio::Core::Game::TextItem> (*itr));

                // Set the enter high score text item's text.

                item->GetGdiRasterText ()->SetTextString (FolioNarrowString(1, m_currentInitial));

                // Draw the enter high score text item.

                status = item->Draw (*graphics);

                redrawCanvas    = true;
                finished        = true;
            } // Endif.
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


void    EnterHighScoreScreen::SetItemText (Folio::Core::Game::TextItemPtr::element_type &item)
{
    switch (item.GetItemId ())
    {
    case ENTER_HIGH_SCORE_SCREEN_ITEM_CONGRATULATIONS_TEXT:
        item.GetGdiRasterText ()->SetTextString ("CONGRATULATIONS");
        break;

    case ENTER_HIGH_SCORE_SCREEN_ITEM_PLAYER_TEXT:
        item.GetGdiRasterText ()->SetTextString (InformationPanel::DescribePlayer (m_informationPanel->GetCurrentPlayer ()));
        break;

    case ENTER_HIGH_SCORE_SCREEN_ITEM_YOU_HAVE_ACHIEVED_TEXT:
        item.GetGdiRasterText ()->SetTextString ("YOU HAVE ACHIEVED");
        break;

    case ENTER_HIGH_SCORE_SCREEN_ITEM_TODAYS_TEXT:       
        item.GetGdiRasterText ()->SetTextString ("TODAY'S");
        break;

    case ENTER_HIGH_SCORE_SCREEN_ITEM_POSITION:
        item.GetGdiRasterText ()->SetTextString (HighScoreTable::DescribeHighScorePosition (m_highScoreTable.GetHighScorePosition (m_informationPanel->GetScore ())));
        break;

    case ENTER_HIGH_SCORE_SCREEN_ITEM_HIGHEST_TEXT:      
        item.GetGdiRasterText ()->SetTextString ("HIGHEST");
        break;

    case ENTER_HIGH_SCORE_SCREEN_ITEM_SCORE_TEXT:        
        item.GetGdiRasterText ()->SetTextString ("SCORE");
        break;

    case ENTER_HIGH_SCORE_SCREEN_ITEM_REGISTER_TEXT:     
        item.GetGdiRasterText ()->SetTextString ("PLEASE REGISTER");
        break;

    case ENTER_HIGH_SCORE_SCREEN_ITEM_YOUR_INITIALS_TEXT:     
        item.GetGdiRasterText ()->SetTextString ("YOUR INITIALS");
        break;

    case ENTER_HIGH_SCORE_SCREEN_ITEM_INITIAL_INPUT_1:   
        item.GetGdiRasterText ()->SetTextString ("-");
        break;

    case ENTER_HIGH_SCORE_SCREEN_ITEM_INITIAL_INPUT_2:   
        item.GetGdiRasterText ()->SetTextString ("-");
        break;

    case ENTER_HIGH_SCORE_SCREEN_ITEM_INITIAL_INPUT_3:   
        item.GetGdiRasterText ()->SetTextString ("-");
        break;

    default:
        break;
    } // Endswitch.

} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
