// "Home-made" includes.
#include    "StdAfx.h"
#include    "EnterHighScoreScreen.h"
#include    "Globals.h"
#include    "Ultimate.h"

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Enter high score screen item attributes.
static  const   Folio::Core::Game::ItemAttributesList<ENTER_HIGH_SCORE_SCREEN_ITEM_ID>  g_highScoreScreenAttributes =
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
    {   ENTER_HIGH_SCORE_SCREEN_ITEM_INITIAL_INPUT_1,           COLUMN_TO_PIXEL(13),    ROW_TO_PIXEL(19),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   },
    {   ENTER_HIGH_SCORE_SCREEN_ITEM_INITIAL_INPUT_2,           COLUMN_TO_PIXEL(15),    ROW_TO_PIXEL(19),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   },
    {   ENTER_HIGH_SCORE_SCREEN_ITEM_INITIAL_INPUT_3,           COLUMN_TO_PIXEL(17),    ROW_TO_PIXEL(19),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   },
};


// Enter high score screen static members.
Folio::Core::Util::Sound::SoundSample   EnterHighScoreScreen::m_selectingInitialSoundSample(Ultimate::CreateSoundSample (0x80, 0x10));  // The selecting initial sound sample.
Folio::Core::Util::Sound::SoundSample   EnterHighScoreScreen::m_enteredInitialSoundSample(Ultimate::CreateSoundSample (0x40, 0x30));    // The entered initial sound sample.

EnterHighScoreScreen::EnterHighScoreScreen (const SelectionScreenPtr &selectionScreen)
:   m_selectionScreen(selectionScreen),
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

            g_informationPanel->SetNumPlayers (0);

            // Query the information panel's items.

            status = g_informationPanel->QueryItems (m_itemsList);
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
            // Add enter high score screen text item.

            status = AddTextItem (dcHandle, 
                                  DRAWING_ELEMENT_ENTER_HIGH_SCORE_SCREEN_ITEM,
                                  *Folio::Core::Game::ZxSpectrum::GetFont (),
                                  *itr,
                                  SetItemText);
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

    Folio::Core::Game::Direction    direction = Folio::Core::Game::NO_DIRECTION;    // Initialise!

    // Is a player direction key down?

    if (m_selectionScreen->IsPlayerDirectionKeyDown (direction))
    {
        // Yes. 
        
        switch (direction)
        {
        case Folio::Core::Game::E:
            // Update the current initial.

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

            status = UpdateScreen (UPDATE_INITIAL);
            break;

        case Folio::Core::Game::W:
            // Update the current initial.

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

            status = UpdateScreen (UPDATE_INITIAL);
            break;

        default:
            break;
        } // Endswitch.

    } // Endif.

    // Is a player fire key down?

    else
    if (m_selectionScreen->IsPlayerFireKeyDown ())
    {
        // Yes. Add the current initial to the high score.

        m_highScore.m_initials += m_currentInitial;

        // Have the required number of initials been entered?

        if (m_highScore.m_initials.size () >= HighScoreTable::HighScore::MAX_INITIALS)
        {
            // Yes. Add the player's score to the high score table.

            m_highScore.m_score = g_informationPanel->GetPlayerScore ();

            g_highScoreTable.AddHighScore (m_highScore);

            // Stop displaying the enter high score screen.

            StopDisplaying ();
        } // Endif.

        else
        {
            // No. Initialise the current initial.

            m_currentInitial = ' ';
        } // Endelse.

        // Play the entered initial sound.

        Folio::Core::Util::Sound::PlaySoundSample (m_enteredInitialSoundSample);
    } // Endelseif.

    return (status);
} // Endproc.


FolioStatus EnterHighScoreScreen::UpdateScreen (UPDATE update)
{
    FolioStatus status = ERR_SUCCESS;

    // Get the canvas graphics.

    Gdiplus::Graphics   *graphics = m_canvas->GetCanvasGraphics ();

    // Update the enter high score screen items (depending on the type of 
    // update required).

    bool    redrawCanvas = false;   // Initialise!

    switch (update)
    {
    case UPDATE_INITIAL:
        status = UpdateInitial (*graphics, redrawCanvas);

        if (status == ERR_SUCCESS)
        {
            // Play the selecting initial sound.

            Folio::Core::Util::Sound::PlaySoundSample (m_selectingInitialSoundSample);
        } // Endif.
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


FolioStatus EnterHighScoreScreen::UpdateInitial (Gdiplus::Graphics  &graphics,
                                                 bool               &redrawCanvas)
{
    redrawCanvas = false;   // Initialise!

    FolioStatus status = ERR_SUCCESS;

    bool    finished = false;   // Initialise!

    // Reverse order for performance.

    for (Folio::Core::Game::ItemsList::reverse_iterator ritr = m_itemsList.rbegin ();
         !finished && (status == ERR_SUCCESS) && (ritr != m_itemsList.rend ());
         ++ritr)
    {
        // Get the enter high score screen item's identifier.

        ENTER_HIGH_SCORE_SCREEN_ITEM_ID itemId = static_cast<ENTER_HIGH_SCORE_SCREEN_ITEM_ID> (ritr->get ()->GetItemId ());
         
        switch (itemId)
        {
        case ENTER_HIGH_SCORE_SCREEN_ITEM_INITIAL_INPUT_1:   
        case ENTER_HIGH_SCORE_SCREEN_ITEM_INITIAL_INPUT_2:   
        case ENTER_HIGH_SCORE_SCREEN_ITEM_INITIAL_INPUT_3:   
            if (m_highScore.m_initials.size () == (itemId - ENTER_HIGH_SCORE_SCREEN_ITEM_INITIAL_INPUT_1))
            {
                // Get the enter high score text item.

                Folio::Core::Game::TextItemPtr  item(std::dynamic_pointer_cast<Folio::Core::Game::TextItem> (*ritr));

                // Set the enter high score text item's text.

                item->GetGdiRasterText ()->SetTextString (FolioNarrowString(1, m_currentInitial));

                // Draw the enter high score text item.

                status = item->Draw (graphics);

                redrawCanvas = true;

                // Finished.

                finished = true;
            } // Endif.
            break;

        default:
            break;
        } // Endswitch.

    } // Endfor.

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
        item.GetGdiRasterText ()->SetTextString (InformationPanel::DescribePlayer (g_informationPanel->GetCurrentPlayer ()));
        break;

    case ENTER_HIGH_SCORE_SCREEN_ITEM_YOU_HAVE_ACHIEVED_TEXT:
        item.GetGdiRasterText ()->SetTextString ("YOU HAVE ACHIEVED");
        break;

    case ENTER_HIGH_SCORE_SCREEN_ITEM_TODAYS_TEXT:       
        item.GetGdiRasterText ()->SetTextString ("TODAY'S");
        break;

    case ENTER_HIGH_SCORE_SCREEN_ITEM_POSITION:
        item.GetGdiRasterText ()->SetTextString (HighScoreTable::DescribeHighScorePosition (g_highScoreTable.GetHighScorePosition (g_informationPanel->GetPlayerScore ())));
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
