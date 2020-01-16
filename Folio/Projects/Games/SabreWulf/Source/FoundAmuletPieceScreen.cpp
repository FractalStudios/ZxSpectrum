// "Home-made" includes.
#include    "StdAfx.h"
#include    "BackgroundItemGraphics.h"
#include    "FoundAmuletPieceScreen.h"
#include    "Globals.h"

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Found amulet piece screen item attributes.
static  const   Folio::Core::Game::ItemAttributesList<FOUND_AMULET_PIECE_SCREEN_ITEM_ID>    g_foundAmuletPieceScreenAttributes =
{
//      m_itemId                                                    m_screenXLeft           m_screenYTop        m_colour
    {   FOUND_AMULET_PIECE_SCREEN_ITEM_INFORMATION_PANEL,             0,                     0,                 Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       },
    {   FOUND_AMULET_PIECE_SCREEN_ITEM_AMULET_PIECE_TOP_LEFT,        80,                    56,                 Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       },
    {   FOUND_AMULET_PIECE_SCREEN_ITEM_AMULET_PIECE_TOP_RIGHT,      128,                    56,                 Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       },
    {   FOUND_AMULET_PIECE_SCREEN_ITEM_AMULET_PIECE_BOTTOM_LEFT,     80,                    88,                 Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       },
    {   FOUND_AMULET_PIECE_SCREEN_ITEM_AMULET_PIECE_BOTTOM_RIGHT,   128,                    88,                 Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       },
    {   FOUND_AMULET_PIECE_SCREEN_ITEM_POEM_TEXT_1,                 COLUMN_TO_PIXEL( 3),    ROW_TO_PIXEL(16),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   },
    {   FOUND_AMULET_PIECE_SCREEN_ITEM_POEM_TEXT_2,                 COLUMN_TO_PIXEL(11),    ROW_TO_PIXEL(18),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   },
    {   FOUND_AMULET_PIECE_SCREEN_ITEM_POEM_TEXT_3,                 COLUMN_TO_PIXEL( 4),    ROW_TO_PIXEL(20),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    },
    {   FOUND_AMULET_PIECE_SCREEN_ITEM_POEM_TEXT_4,                 COLUMN_TO_PIXEL( 9),    ROW_TO_PIXEL(22),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    },
};


FoundAmuletPieceScreen::FoundAmuletPieceScreen ()
:   m_finishedPlayingFoundAmuletPieceMusic(false)
{
} // Endproc.


FoundAmuletPieceScreen::~FoundAmuletPieceScreen ()
{
} // Endproc.


FolioStatus FoundAmuletPieceScreen::BuildScreenItems (FolioHandle   dcHandle, 
                                                      FolioHandle   instanceHandle)
{                               
    FolioStatus status = ERR_SUCCESS;

    // Build the found amulet piece screen items. 

    for (Folio::Core::Game::ItemAttributesList<FOUND_AMULET_PIECE_SCREEN_ITEM_ID>::const_iterator itr = g_foundAmuletPieceScreenAttributes.begin (); 
         (status == ERR_SUCCESS) && (itr != g_foundAmuletPieceScreenAttributes.end ());
         ++itr)
    {              
        // Build the found amulet piece screen item.

        switch (itr->m_itemId)
        {
        case FOUND_AMULET_PIECE_SCREEN_ITEM_INFORMATION_PANEL:
            // Query the information panel's items.

            status = g_informationPanel->QueryItems (m_itemsList);
            break;

        case FOUND_AMULET_PIECE_SCREEN_ITEM_AMULET_PIECE_TOP_LEFT: 
        case FOUND_AMULET_PIECE_SCREEN_ITEM_AMULET_PIECE_TOP_RIGHT: 
        case FOUND_AMULET_PIECE_SCREEN_ITEM_AMULET_PIECE_BOTTOM_LEFT: 
        case FOUND_AMULET_PIECE_SCREEN_ITEM_AMULET_PIECE_BOTTOM_RIGHT: 
            { 
                UInt16  bitmapResourceId = BACKGROUND_ITEM_BACKGROUND_ITEM_e67c_AMULET_BLANK_BOTTOM_RIGHT;  // Initialise!

                switch (itr->m_itemId)
                {
                case FOUND_AMULET_PIECE_SCREEN_ITEM_AMULET_PIECE_TOP_LEFT: 
                    bitmapResourceId = g_informationPanel->IsFoundAmuletPieceTopLeft () 
                                       ? BACKGROUND_ITEM_BACKGROUND_ITEM_e3a0_AMULET_PIECE_TOP_LEFT
                                       : BACKGROUND_ITEM_BACKGROUND_ITEM_e3a0_AMULET_BLANK_TOP_LEFT;
                    break;

                case FOUND_AMULET_PIECE_SCREEN_ITEM_AMULET_PIECE_TOP_RIGHT: 
                    bitmapResourceId = g_informationPanel->IsFoundAmuletPieceTopRight () 
                                       ? BACKGROUND_ITEM_BACKGROUND_ITEM_e494_AMULET_PIECE_TOP_RIGHT
                                       : BACKGROUND_ITEM_BACKGROUND_ITEM_e494_AMULET_BLANK_TOP_RIGHT;
                    break;

                case FOUND_AMULET_PIECE_SCREEN_ITEM_AMULET_PIECE_BOTTOM_LEFT: 
                    bitmapResourceId = g_informationPanel->IsFoundAmuletPieceBottomLeft () 
                                       ? BACKGROUND_ITEM_BACKGROUND_ITEM_e588_AMULET_PIECE_BOTTOM_LEFT
                                       : BACKGROUND_ITEM_BACKGROUND_ITEM_e588_AMULET_BLANK_BOTTOM_LEFT;
                    break;

                case FOUND_AMULET_PIECE_SCREEN_ITEM_AMULET_PIECE_BOTTOM_RIGHT:
                    bitmapResourceId = g_informationPanel->IsFoundAmuletPieceBottomRight () 
                                       ? BACKGROUND_ITEM_BACKGROUND_ITEM_e67c_AMULET_PIECE_BOTTOM_RIGHT
                                       : BACKGROUND_ITEM_BACKGROUND_ITEM_e67c_AMULET_BLANK_BOTTOM_RIGHT;
                    break;

                default:
                    break;
                } // Endswitch.

                // Add found amulet piece screen graphic item.
            
                status = AddGraphicItem (dcHandle, 
                                         instanceHandle ,
                                         DRAWING_ELEMENT_FOUND_AMULET_PIECE_SCREEN_ITEM,
                                         Folio::Core::Game::ItemAttributes<FOUND_AMULET_PIECE_SCREEN_ITEM_ID> (itr->m_itemId,
                                                                                                               bitmapResourceId,
                                                                                                               itr->m_screenXLeft, 
                                                                                                               itr->m_screenYTop,
                                                                                                               itr->m_colour));
            } // Endscope.
            break;

        case FOUND_AMULET_PIECE_SCREEN_ITEM_POEM_TEXT_1:
        case FOUND_AMULET_PIECE_SCREEN_ITEM_POEM_TEXT_2:
        case FOUND_AMULET_PIECE_SCREEN_ITEM_POEM_TEXT_3:
        case FOUND_AMULET_PIECE_SCREEN_ITEM_POEM_TEXT_4:
            // Add found amulet piece screen text item.
            
            status = AddTextItem (dcHandle, 
                                  DRAWING_ELEMENT_FOUND_AMULET_PIECE_SCREEN_ITEM,
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


FolioStatus FoundAmuletPieceScreen::ProcessScreenInput ()
{
    // Only process screen input once the found amulet piece music has finished 
    // playing.

    if (m_finishedPlayingFoundAmuletPieceMusic &&
        Folio::Core::Util::KeyInput::IsAnyKeyDown ())
    {
        // Stop displaying the found amulet piece screen.

        StopDisplaying ();
    } // Endif.

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus FoundAmuletPieceScreen::ProcessScreenFrame (UInt32 *frameRateIncrement)
{
    // Play the found amulet piece music.

    return (PlayFoundAmuletPieceMusic ());
} // Endproc.


FolioStatus FoundAmuletPieceScreen::PlayFoundAmuletPieceMusic ()
{
    FolioStatus status = ERR_SUCCESS;

    // Have we finished playing the found amulet piece music?

    if (!m_finishedPlayingFoundAmuletPieceMusic)
    {
        // No. Play the found amulet piece music.

        status = g_musicJukebox.PlayFoundAmuletPieceMusic (m_finishedPlayingFoundAmuletPieceMusic);
    } // Endif.

    return (status);
} // Endproc.


void    FoundAmuletPieceScreen::SetItemText (Folio::Core::Game::TextItemPtr::element_type &item)
{
    switch (item.GetItemId ())
    {
    case FOUND_AMULET_PIECE_SCREEN_ITEM_POEM_TEXT_1:
        switch (g_informationPanel->GetNumFoundAmuletPieces ())
        {
        case 1:
            item.GetGdiRasterText ()->SetTextString (" ONE PIECE IS ALL THAT YOU");
            break;

        case 2:
            item.GetGdiRasterText ()->SetTextString ("TWO PIECES FOUND ARE YOURS");
            break;

        case 3:
            item.GetGdiRasterText ()->SetTextString ("    ONE PIECE MORE MUST");
            break;

        case 4:
            item.GetGdiRasterText ()->SetTextString ("FOUR PIECES FOUND HAVE NOW");
            break;

        default:
            break;
        } // Endswitch.
        break;

    case FOUND_AMULET_PIECE_SCREEN_ITEM_POEM_TEXT_2:
        switch (g_informationPanel->GetNumFoundAmuletPieces ())
        {
        case 1:
            item.GetGdiRasterText ()->SetTextString ("HAVE FOUND");
            break;

        case 2:
            item.GetGdiRasterText ()->SetTextString (" TO KEEP");
            break;

        case 3:
            item.GetGdiRasterText ()->SetTextString (" YOU AMASS");
            break;

        case 4:
            item.GetGdiRasterText ()->SetTextString ("MADE WHOLE");
            break;

        default:
            break;
        } // Endswitch.
        break;

    case FOUND_AMULET_PIECE_SCREEN_ITEM_POEM_TEXT_3:
        switch (g_informationPanel->GetNumFoundAmuletPieces ())
        {
        case 1:
            item.GetGdiRasterText ()->SetTextString (" COLLECT THREE MORE AND");
            break;

        case 2:
            item.GetGdiRasterText ()->SetTextString ("THIS SCORE AGAIN IS WHAT");
            break;

        case 3:
            item.GetGdiRasterText ()->SetTextString (" AND FIND THE KEEPER YOU");
            break;

        case 4:
            item.GetGdiRasterText ()->SetTextString ("TO FIND THE CAVE MUST BE");
            break;

        default:
            break;
        } // Endswitch.
        break;

    case FOUND_AMULET_PIECE_SCREEN_ITEM_POEM_TEXT_4:
        switch (g_informationPanel->GetNumFoundAmuletPieces ())
        {
        case 1:
            item.GetGdiRasterText ()->SetTextString ("OUTWARD BOUND");
            break;

        case 2:
            item.GetGdiRasterText ()->SetTextString ("   YOU SEEK");
            break;

        case 3:
            item.GetGdiRasterText ()->SetTextString ("   MAY PASS");
            break;

        case 4:
            item.GetGdiRasterText ()->SetTextString ("  YOUR GOAL");
            break;

        default:
            break;
        } // Endswitch.
        break;

    default:
        break;
    } // Endswitch.

} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
