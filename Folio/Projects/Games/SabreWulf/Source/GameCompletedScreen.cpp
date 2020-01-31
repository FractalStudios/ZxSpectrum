// "Home-made" includes.
#include    "StdAfx.h"
#include    "BackgroundItemGraphics.h"
#include    "GameCompletedScreen.h"
#include    "Globals.h"

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Game completed screen item attributes.
static  const   Folio::Core::Game::ItemAttributesList<GAME_COMPLETED_SCREEN_ITEM_ID>    g_gameCompletedScreenAttributes =
{
//      m_itemId                                            m_screenXLeft           m_screenYTop        m_colour
    {   GAME_COMPLETED_SCREEN_ITEM_INFORMATION_PANEL,       0,                      0,                  Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       },
    {   GAME_COMPLETED_SCREEN_ITEM_GAME_COMPLETED_1_TEXT,   COLUMN_TO_PIXEL(12),    ROW_TO_PIXEL( 4),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   },
    {   GAME_COMPLETED_SCREEN_ITEM_GAME_COMPLETED_2_TEXT,   COLUMN_TO_PIXEL( 5),    ROW_TO_PIXEL( 6),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   },
    {   GAME_COMPLETED_SCREEN_ITEM_GAME_COMPLETED_3_TEXT,   COLUMN_TO_PIXEL( 4),    ROW_TO_PIXEL( 8),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   },
    {   GAME_COMPLETED_SCREEN_ITEM_UNDERWURLDE_GRAPHIC,     64,                     88,                 Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       },
    {   GAME_COMPLETED_SCREEN_ITEM_UNDERWURLDE_TEXT,        COLUMN_TO_PIXEL( 2),    ROW_TO_PIXEL(16),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    },
    {   GAME_COMPLETED_SCREEN_ITEM_COPYRIGHT_TEXT,          COLUMN_TO_PIXEL( 9),    ROW_TO_PIXEL(18),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    },
    {   GAME_COMPLETED_SCREEN_ITEM_RIGHTS_TEXT,             COLUMN_TO_PIXEL( 6),    ROW_TO_PIXEL(20),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    },
};


GameCompletedScreen::GameCompletedScreen ()
:   m_finishedPlayingMainGameMusic(false)
{
} // Endproc.


GameCompletedScreen::~GameCompletedScreen ()
{
} // Endproc.


FolioStatus GameCompletedScreen::BuildScreenItems (FolioHandle  dcHandle, 
                                                   FolioHandle  instanceHandle)
{                               
    FolioStatus status = ERR_SUCCESS;

    // Build the game completed screen items. 

    for (Folio::Core::Game::ItemAttributesList<GAME_COMPLETED_SCREEN_ITEM_ID>::const_iterator itr = g_gameCompletedScreenAttributes.begin (); 
         (status == ERR_SUCCESS) && (itr != g_gameCompletedScreenAttributes.end ());
         ++itr)
    {              
        // Build the game completed screen item.

        switch (itr->m_itemId)
        {
        case GAME_COMPLETED_SCREEN_ITEM_INFORMATION_PANEL:
            // Query the information panel's items.

            status = g_informationPanel->QueryItems (m_itemsList);
            break;

        case GAME_COMPLETED_SCREEN_ITEM_UNDERWURLDE_GRAPHIC:
            // Add game completed screen graphic item.
            
            status = AddGraphicItem (dcHandle, 
                                     instanceHandle ,
                                     DRAWING_ELEMENT_GAME_COMPLETED_SCREEN_ITEM,
                                     Folio::Core::Game::ItemAttributes<GAME_COMPLETED_SCREEN_ITEM_ID> (itr->m_itemId,
                                                                                                       BACKGROUND_ITEM_e1ec,
                                                                                                       itr->m_screenXLeft, 
                                                                                                       itr->m_screenYTop,
                                                                                                       Folio::Core::Game::ZxSpectrum::UNDEFINED));
            break;

        case GAME_COMPLETED_SCREEN_ITEM_GAME_COMPLETED_1_TEXT:
        case GAME_COMPLETED_SCREEN_ITEM_GAME_COMPLETED_2_TEXT:
        case GAME_COMPLETED_SCREEN_ITEM_GAME_COMPLETED_3_TEXT:
        case GAME_COMPLETED_SCREEN_ITEM_UNDERWURLDE_TEXT:
        case GAME_COMPLETED_SCREEN_ITEM_COPYRIGHT_TEXT:
        case GAME_COMPLETED_SCREEN_ITEM_RIGHTS_TEXT:
            // Add game completed screen text item.
            
            status = AddTextItem (dcHandle, 
                                  DRAWING_ELEMENT_GAME_COMPLETED_SCREEN_ITEM,
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


FolioStatus GameCompletedScreen::ProcessScreenInput ()
{
    // Only process screen input once the main game music has finished playing.

    if (m_finishedPlayingMainGameMusic &&
        Folio::Core::Util::KeyInput::IsAnyKeyDown ())
    {
        // Stop displaying the game completed screen.

        StopDisplaying ();
    } // Endif.

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus GameCompletedScreen::ProcessScreenFrame ()
{
    // Play the main game music.

    return (PlayMainGameMusic ());
} // Endproc.


FolioStatus GameCompletedScreen::PlayMainGameMusic ()
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


void    GameCompletedScreen::SetItemText (Folio::Core::Game::TextItemPtr::element_type &item)
{
    switch (item.GetItemId ())
    {
    case GAME_COMPLETED_SCREEN_ITEM_GAME_COMPLETED_1_TEXT:
        item.GetGdiRasterText ()->SetTextString ("THE NEXT");
        break;

    case GAME_COMPLETED_SCREEN_ITEM_GAME_COMPLETED_2_TEXT:
        item.GetGdiRasterText ()->SetTextString ("ADVENTURES OF SABRE MAN");
        break;

    case GAME_COMPLETED_SCREEN_ITEM_GAME_COMPLETED_3_TEXT:
        item.GetGdiRasterText ()->SetTextString ("WILL BE CONTINUED IN THE");
        break;

    case GAME_COMPLETED_SCREEN_ITEM_UNDERWURLDE_TEXT:
        item.GetGdiRasterText ()->SetTextString ("THE UNDER-WURLDE \x7f COPYRIGHT");
        break;

    case GAME_COMPLETED_SCREEN_ITEM_COPYRIGHT_TEXT:
        item.GetGdiRasterText ()->SetTextString ("1984 A.C.G. LTD.");
        break;

    case GAME_COMPLETED_SCREEN_ITEM_RIGHTS_TEXT:
        item.GetGdiRasterText ()->SetTextString ("-ALL RIGHTS RESERVED-");
        break;

    default:
        break;
    } // Endswitch.

} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
