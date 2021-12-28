// "Home-made" includes.
#include    "StdAfx.h"
#include    "GameOverScreen.h"
#include    "Globals.h"

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Game over screen item attributes.
static  const   Folio::Core::Game::ItemAttributesList<GAME_OVER_SCREEN_ITEM_ID> g_gameOverScreenAttributes =
{
//      m_itemId                                            m_screenXLeft           m_screenYTop        m_colour
    {   GAME_OVER_SCREEN_ITEM_INFORMATION_PANEL,            0,                      0,                  Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       },
    {   GAME_OVER_SCREEN_ITEM_GAME_OVER_TEXT,               COLUMN_TO_PIXEL( 7),    ROW_TO_PIXEL(12),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   },
    {   GAME_OVER_SCREEN_ITEM_PLAYER_TEXT,                  COLUMN_TO_PIXEL(17),    ROW_TO_PIXEL(12),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   },
    {   GAME_OVER_SCREEN_ITEM_ADVENTURE_COMPLETED_TEXT,     COLUMN_TO_PIXEL( 4),    ROW_TO_PIXEL(15),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   },
    {   GAME_OVER_SCREEN_ITEM_PERCENTAGE_COMPLETE,          COLUMN_TO_PIXEL(24),    ROW_TO_PIXEL(15),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   },
};


GameOverScreen::GameOverScreen ()
:   m_finishedPlayingGameOverMusic(false)
{
} // Endproc.


GameOverScreen::~GameOverScreen ()
{
} // Endproc.


FolioStatus GameOverScreen::BuildScreenItems (FolioHandle   dcHandle, 
                                              FolioHandle   instanceHandle)
{                               
    FolioStatus status = ERR_SUCCESS;

    // Build the game over screen items. 

    for (Folio::Core::Game::ItemAttributesList<GAME_OVER_SCREEN_ITEM_ID>::const_iterator itr = g_gameOverScreenAttributes.begin (); 
         (status == ERR_SUCCESS) && (itr != g_gameOverScreenAttributes.end ());
         ++itr)
    {              
        // Build the game over screen item.

        switch (itr->m_itemId)
        {
        case GAME_OVER_SCREEN_ITEM_INFORMATION_PANEL:
            // No players.

            g_informationPanel->SetNumPlayers (0);

            // Query the information panel's items.

            status = g_informationPanel->QueryItems (m_itemsList);
            break;

        case GAME_OVER_SCREEN_ITEM_GAME_OVER_TEXT:
        case GAME_OVER_SCREEN_ITEM_PLAYER_TEXT:
        case GAME_OVER_SCREEN_ITEM_ADVENTURE_COMPLETED_TEXT:
        case GAME_OVER_SCREEN_ITEM_PERCENTAGE_COMPLETE:
            // Add game over screen text item.

            status = AddTextItem (dcHandle, 
                                  Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_GAME_OVER_SCREEN_ITEM,
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


FolioStatus GameOverScreen::ProcessScreenInput ()
{
    // Only process screen input once the game over music has finished playing.

    if (m_finishedPlayingGameOverMusic &&
        Folio::Core::Util::KeyInput::IsAnyKeyDown ())
    {
        // Stop displaying the game over screen.

        StopDisplaying ();
    } // Endif.

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus GameOverScreen::ProcessScreenFrame ()
{
    // Play the game over music.

    return (PlayGameOverMusic ());
} // Endproc.


FolioStatus GameOverScreen::PlayGameOverMusic ()
{
    FolioStatus status = ERR_SUCCESS;

    // Have we finished playing the game over music?

    if (!m_finishedPlayingGameOverMusic)
    {
        // No. Play the game over music.

        status = g_musicJukebox.PlayGameOverMusic (m_finishedPlayingGameOverMusic);
    } // Endif.

    return (status);
} // Endproc.


void    GameOverScreen::SetItemText (Folio::Core::Game::TextItemPtr::element_type& item)
{
    switch (item.GetItemId ())
    {
    case GAME_OVER_SCREEN_ITEM_GAME_OVER_TEXT:
        item.GetGdiRasterText ()->SetTextString ("GAME OVER");
        break;

    case GAME_OVER_SCREEN_ITEM_PLAYER_TEXT:
        item.GetGdiRasterText ()->SetTextString (InformationPanel::DescribePlayer (g_informationPanel->GetCurrentPlayer ()));
        break;

    case GAME_OVER_SCREEN_ITEM_ADVENTURE_COMPLETED_TEXT:
        item.GetGdiRasterText ()->SetTextString ("ADVENTURE COMPLETED");
        break;

    case GAME_OVER_SCREEN_ITEM_PERCENTAGE_COMPLETE:
        item.GetGdiRasterText ()->SetTextString (InformationPanel::DescribePercentage (g_informationPanel->GetPlayerPercentageGameCompleted ()));
        break;

    default:
        break;
    } // Endswitch.

} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
