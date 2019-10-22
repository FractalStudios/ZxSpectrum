// "Home-made" includes.
#include    "StdAfx.h"
#include    "GameOverScreen.h"

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


GameOverScreen::GameOverScreen (const InformationPanelPtr &informationPanel)
:   m_informationPanel(informationPanel)
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

            m_informationPanel->SetNumPlayers (0);

            // Query the information panel's items.

            status = m_informationPanel->QueryItems (m_itemsList);
            break;

        case GAME_OVER_SCREEN_ITEM_GAME_OVER_TEXT:
        case GAME_OVER_SCREEN_ITEM_PLAYER_TEXT:
        case GAME_OVER_SCREEN_ITEM_ADVENTURE_COMPLETED_TEXT:
        case GAME_OVER_SCREEN_ITEM_PERCENTAGE_COMPLETE:
            { 
                // Create a game over screen text item.

                Folio::Core::Game::TextItemPtr  item(new Folio::Core::Game::TextItemPtr::element_type);
                
                status = item->Create (dcHandle,
                                       DRAWING_ELEMENT_GAME_OVER_SCREEN_ITEM,
                                       *Folio::Core::Game::ZxSpectrum::GetFont (),
                                       itr->m_itemId,
                                       itr->m_screenXLeft, 
                                       itr->m_screenYTop,
                                       Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE, 
                                       Folio::Core::Game::ZxSpectrum::MapInkColour (itr->m_colour));

                if (status == ERR_SUCCESS)
                {
                    // Set the game over screen item's text.

                    SetItemText (*item.get ());
            
                    // Store the game over screen item in the game over screen items list.

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


FolioStatus GameOverScreen::ProcessScreenInput ()
{
    if (Folio::Core::Util::KeyInput::IsAnyKeyDown ())
    {
        // Stop displaying the game over screen.

        StopDisplaying ();
    } // Endif.

    return (ERR_SUCCESS);
} // Endproc.


void    GameOverScreen::SetItemText (Folio::Core::Game::TextItemPtr::element_type &item)
{
    switch (item.GetItemId ())
    {
    case GAME_OVER_SCREEN_ITEM_GAME_OVER_TEXT:
        item.GetGdiRasterText ()->SetTextString ("GAME OVER");
        break;

    case GAME_OVER_SCREEN_ITEM_PLAYER_TEXT:
        item.GetGdiRasterText ()->SetTextString (InformationPanel::DescribePlayer (m_informationPanel->GetCurrentPlayer ()));
        break;

    case GAME_OVER_SCREEN_ITEM_ADVENTURE_COMPLETED_TEXT:
        item.GetGdiRasterText ()->SetTextString ("ADVENTURE COMPLETED");
        break;

    case GAME_OVER_SCREEN_ITEM_PERCENTAGE_COMPLETE:
        item.GetGdiRasterText ()->SetTextString (InformationPanel::DescribePercentage (m_informationPanel->GetPercentageCompleted ()));
        break;

    default:
        break;
    } // Endswitch.

} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
