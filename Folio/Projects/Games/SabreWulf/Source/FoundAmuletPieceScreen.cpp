// "Home-made" includes.
#include    "StdAfx.h"
#include    "BackgroundItemGraphics.h"
#include    "FoundAmuletPieceScreen.h"

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Found amulet piece screen item attributes.
static  const   Folio::Core::Game::ItemAttributesList<FOUND_AMULET_PIECE_SCREEN_ITEM_ID> g_gameOverScreenAttributes =
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


FoundAmuletPieceScreen::FoundAmuletPieceScreen (const InformationPanelPtr &informationPanel)
:   m_informationPanel(informationPanel)
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

    for (Folio::Core::Game::ItemAttributesList<FOUND_AMULET_PIECE_SCREEN_ITEM_ID>::const_iterator itr = g_gameOverScreenAttributes.begin (); 
         (status == ERR_SUCCESS) && (itr != g_gameOverScreenAttributes.end ());
         ++itr)
    {              
        // Build the found amulet piece screen item.

        switch (itr->m_itemId)
        {
        case FOUND_AMULET_PIECE_SCREEN_ITEM_INFORMATION_PANEL:
            // Query the information panel's items.

            status = m_informationPanel->QueryItems (m_itemsList);
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
                    bitmapResourceId = m_informationPanel->IsFoundAmuletPieceTopLeft () 
                                       ? BACKGROUND_ITEM_BACKGROUND_ITEM_e3a0_AMULET_PIECE_TOP_LEFT
                                       : BACKGROUND_ITEM_BACKGROUND_ITEM_e3a0_AMULET_BLANK_TOP_LEFT;
                    break;
                case FOUND_AMULET_PIECE_SCREEN_ITEM_AMULET_PIECE_TOP_RIGHT: 
                    bitmapResourceId = m_informationPanel->IsFoundAmuletPieceTopRight () 
                                       ? BACKGROUND_ITEM_BACKGROUND_ITEM_e494_AMULET_PIECE_TOP_RIGHT
                                       : BACKGROUND_ITEM_BACKGROUND_ITEM_e494_AMULET_BLANK_TOP_RIGHT;
                    break;
                case FOUND_AMULET_PIECE_SCREEN_ITEM_AMULET_PIECE_BOTTOM_LEFT: 
                    bitmapResourceId = m_informationPanel->IsFoundAmuletPieceBottomLeft () 
                                       ? BACKGROUND_ITEM_BACKGROUND_ITEM_e588_AMULET_PIECE_BOTTOM_LEFT
                                       : BACKGROUND_ITEM_BACKGROUND_ITEM_e588_AMULET_BLANK_BOTTOM_LEFT;
                    break;
                case FOUND_AMULET_PIECE_SCREEN_ITEM_AMULET_PIECE_BOTTOM_RIGHT:
                default:
                    bitmapResourceId = m_informationPanel->IsFoundAmuletPieceBottomRight () 
                                       ? BACKGROUND_ITEM_BACKGROUND_ITEM_e67c_AMULET_PIECE_BOTTOM_RIGHT
                                       : BACKGROUND_ITEM_BACKGROUND_ITEM_e67c_AMULET_BLANK_BOTTOM_RIGHT;
                    break;
                } // Endswitch.

                // Create a found amulet piece screen graphic item.
            
                Folio::Core::Game::GraphicItemPtr   item(new Folio::Core::Game::GraphicItemPtr::element_type);
            
                status = item->Create (dcHandle,
                                       instanceHandle,
                                       DRAWING_ELEMENT_FOUND_AMULET_PIECE_SCREEN_ITEM,
                                       bitmapResourceId,
                                       itr->m_itemId,
                                       itr->m_screenXLeft, 
                                       itr->m_screenYTop,
                                       Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE);

                if (status == ERR_SUCCESS)
                {
                    // Store the found amulet piece screen item in the screen's items list.

                    m_itemsList.push_back (item);
                } // Endif.

            } // Endscope.
            break;

        case FOUND_AMULET_PIECE_SCREEN_ITEM_POEM_TEXT_1:
        case FOUND_AMULET_PIECE_SCREEN_ITEM_POEM_TEXT_2:
        case FOUND_AMULET_PIECE_SCREEN_ITEM_POEM_TEXT_3:
        case FOUND_AMULET_PIECE_SCREEN_ITEM_POEM_TEXT_4:
            { 
                // Create a found amulet piece screen text item.

                Folio::Core::Game::TextItemPtr  item(new Folio::Core::Game::TextItemPtr::element_type);
                
                status = item->Create (dcHandle,
                                       DRAWING_ELEMENT_FOUND_AMULET_PIECE_SCREEN_ITEM,
                                       *Folio::Core::Game::ZxSpectrum::GetFont (),
                                       itr->m_itemId,
                                       itr->m_screenXLeft, 
                                       itr->m_screenYTop,
                                       Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE, 
                                       Folio::Core::Game::ZxSpectrum::MapInkColour (itr->m_colour));

                if (status == ERR_SUCCESS)
                {
                    // Set the found amulet piece screen item's text.

                    SetItemText (*item.get ());
            
                    // Store the found amulet piece screen item in the found amulet piece screen items list.

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


FolioStatus FoundAmuletPieceScreen::ProcessScreenInput ()
{
    if (Folio::Core::Util::KeyInput::IsAnyKeyDown ())
    {
        // Stop displaying the found amulet piece screen.

        StopDisplaying ();
    } // Endif.

    return (ERR_SUCCESS);
} // Endproc.


void    FoundAmuletPieceScreen::SetItemText (Folio::Core::Game::TextItemPtr::element_type &item)
{
    switch (item.GetItemId ())
    {
    case FOUND_AMULET_PIECE_SCREEN_ITEM_POEM_TEXT_1:
        switch (m_informationPanel->GetNumFoundAmuletPieces ())
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
        switch (m_informationPanel->GetNumFoundAmuletPieces ())
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
        switch (m_informationPanel->GetNumFoundAmuletPieces ())
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
        switch (m_informationPanel->GetNumFoundAmuletPieces ())
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
