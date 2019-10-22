// "Home-made" includes.
#include    "StdAfx.h"
#include    "HighScoreScreen.h"

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// High score screen item attributes.
static  const   Folio::Core::Game::ItemAttributesList<HIGH_SCORE_SCREEN_ITEM_ID>    g_highScoreScreenAttributes =
{
//      m_itemId                                        m_screenXLeft           m_screenYTop        m_colour
    {   HIGH_SCORE_SCREEN_ITEM_INFORMATION_PANEL,       0,                       0,                 Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       },
    {   HIGH_SCORE_SCREEN_ITEM_BORDER,                  0,                      16,                 Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       },
    {   HIGH_SCORE_SCREEN_ITEM_TITLE,                   COLUMN_TO_PIXEL( 5),    ROW_TO_PIXEL( 6),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   },
    {   HIGH_SCORE_SCREEN_ITEM_1_POSITION_TEXT,         COLUMN_TO_PIXEL( 7),    ROW_TO_PIXEL( 9),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   },
    {   HIGH_SCORE_SCREEN_ITEM_1_SCORE,                 COLUMN_TO_PIXEL(13),    ROW_TO_PIXEL( 9),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   },
    {   HIGH_SCORE_SCREEN_ITEM_1_INITIALS,              COLUMN_TO_PIXEL(22),    ROW_TO_PIXEL( 9),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   },
    {   HIGH_SCORE_SCREEN_ITEM_2_POSITION_TEXT,         COLUMN_TO_PIXEL( 7),    ROW_TO_PIXEL(11),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   },
    {   HIGH_SCORE_SCREEN_ITEM_2_SCORE,                 COLUMN_TO_PIXEL(13),    ROW_TO_PIXEL(11),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   },
    {   HIGH_SCORE_SCREEN_ITEM_2_INITIALS,              COLUMN_TO_PIXEL(22),    ROW_TO_PIXEL(11),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   },
    {   HIGH_SCORE_SCREEN_ITEM_3_POSITION_TEXT,         COLUMN_TO_PIXEL( 7),    ROW_TO_PIXEL(13),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW),  },
    {   HIGH_SCORE_SCREEN_ITEM_3_SCORE,                 COLUMN_TO_PIXEL(13),    ROW_TO_PIXEL(13),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW),  },
    {   HIGH_SCORE_SCREEN_ITEM_3_INITIALS,              COLUMN_TO_PIXEL(22),    ROW_TO_PIXEL(13),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW),  },
    {   HIGH_SCORE_SCREEN_ITEM_4_POSITION_TEXT,         COLUMN_TO_PIXEL( 7),    ROW_TO_PIXEL(15),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW),  },
    {   HIGH_SCORE_SCREEN_ITEM_4_SCORE,                 COLUMN_TO_PIXEL(13),    ROW_TO_PIXEL(15),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW),  },
    {   HIGH_SCORE_SCREEN_ITEM_4_INITIALS,              COLUMN_TO_PIXEL(22),    ROW_TO_PIXEL(15),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW),  },
    {   HIGH_SCORE_SCREEN_ITEM_5_POSITION_TEXT,         COLUMN_TO_PIXEL( 7),    ROW_TO_PIXEL(17),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    },
    {   HIGH_SCORE_SCREEN_ITEM_5_SCORE,                 COLUMN_TO_PIXEL(13),    ROW_TO_PIXEL(17),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    },
    {   HIGH_SCORE_SCREEN_ITEM_5_INITIALS,              COLUMN_TO_PIXEL(22),    ROW_TO_PIXEL(17),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    },
    {   HIGH_SCORE_SCREEN_ITEM_6_POSITION_TEXT,         COLUMN_TO_PIXEL( 7),    ROW_TO_PIXEL(19),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    },
    {   HIGH_SCORE_SCREEN_ITEM_6_SCORE,                 COLUMN_TO_PIXEL(13),    ROW_TO_PIXEL(19),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    },
    {   HIGH_SCORE_SCREEN_ITEM_6_INITIALS,              COLUMN_TO_PIXEL(22),    ROW_TO_PIXEL(19),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    },
    {   HIGH_SCORE_SCREEN_ITEM_COPYRIGHT_TEXT,          COLUMN_TO_PIXEL( 9),    ROW_TO_PIXEL(22),   Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   },
};


HighScoreScreen::HighScoreScreen (const InformationPanelPtr &informationPanel,
                                  const HighScoreTable      &highScoreTable)
:   m_informationPanel(informationPanel),
    m_highScoreTable(highScoreTable)
{
} // Endproc.


HighScoreScreen::~HighScoreScreen ()
{
} // Endproc.


FolioStatus HighScoreScreen::BuildScreenItems (FolioHandle  dcHandle, 
                                               FolioHandle  instanceHandle)
{                               
    FolioStatus status = ERR_SUCCESS;

    // Build the high score screen items. 

    for (Folio::Core::Game::ItemAttributesList<HIGH_SCORE_SCREEN_ITEM_ID>::const_iterator itr = g_highScoreScreenAttributes.begin (); 
         (status == ERR_SUCCESS) && (itr != g_highScoreScreenAttributes.end ());
         ++itr)
    {              
        // Build the high score screen item.

        switch (itr->m_itemId)
        {
        case HIGH_SCORE_SCREEN_ITEM_INFORMATION_PANEL:
            // No players.

            m_informationPanel->SetNumPlayers (0);

            // Query the information panel's items.

            status = m_informationPanel->QueryItems (m_itemsList);
            break;

        case HIGH_SCORE_SCREEN_ITEM_BORDER:
            // Add the border screen's items.
            
            status = AddBorderScreenItems (dcHandle, instanceHandle);
            break;

        case HIGH_SCORE_SCREEN_ITEM_TITLE:
        case HIGH_SCORE_SCREEN_ITEM_1_POSITION_TEXT:
        case HIGH_SCORE_SCREEN_ITEM_1_SCORE:
        case HIGH_SCORE_SCREEN_ITEM_1_INITIALS:
        case HIGH_SCORE_SCREEN_ITEM_2_POSITION_TEXT:
        case HIGH_SCORE_SCREEN_ITEM_2_SCORE:
        case HIGH_SCORE_SCREEN_ITEM_2_INITIALS:
        case HIGH_SCORE_SCREEN_ITEM_3_POSITION_TEXT:
        case HIGH_SCORE_SCREEN_ITEM_3_SCORE:
        case HIGH_SCORE_SCREEN_ITEM_3_INITIALS:
        case HIGH_SCORE_SCREEN_ITEM_4_POSITION_TEXT:
        case HIGH_SCORE_SCREEN_ITEM_4_SCORE:
        case HIGH_SCORE_SCREEN_ITEM_4_INITIALS:
        case HIGH_SCORE_SCREEN_ITEM_5_POSITION_TEXT:
        case HIGH_SCORE_SCREEN_ITEM_5_SCORE:
        case HIGH_SCORE_SCREEN_ITEM_5_INITIALS:
        case HIGH_SCORE_SCREEN_ITEM_6_POSITION_TEXT:
        case HIGH_SCORE_SCREEN_ITEM_6_SCORE:
        case HIGH_SCORE_SCREEN_ITEM_6_INITIALS:
        case HIGH_SCORE_SCREEN_ITEM_COPYRIGHT_TEXT:
            { 
                // Create a high score screen text item.

                Folio::Core::Game::TextItemPtr  item(new Folio::Core::Game::TextItemPtr::element_type);
                
                status = item->Create (dcHandle,
                                       DRAWING_ELEMENT_HIGH_SCORE_SCREEN_ITEM,
                                       *Folio::Core::Game::ZxSpectrum::GetFont (),
                                       itr->m_itemId,
                                       itr->m_screenXLeft, 
                                       itr->m_screenYTop,
                                       Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE, 
                                       Folio::Core::Game::ZxSpectrum::MapInkColour (itr->m_colour));

                if (status == ERR_SUCCESS)
                {
                    // Set the high score screen item's text.

                    SetItemText (*item.get ());
            
                    // Store the high score screen item in the high score screen items list.

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


FolioStatus HighScoreScreen::ProcessScreenInput ()
{
    if (Folio::Core::Util::KeyInput::IsAnyKeyDown ())
    {
        // Stop displaying the high score screen.

        StopDisplaying ();
    } // Endif.

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus HighScoreScreen::ProcessScreenFrame (UInt32 *frameRateIncrement)
{
    FolioStatus status = ERR_SUCCESS;

    if (Folio::Core::Util::DateTime::GetCurrentTickCount () >= (m_initialFrameTickCount + MAX_DISPLAY_SCREEN_TIME))
    {
        // Stop displaying the selection screen.

        StopDisplaying ();
    } // Endif.

    return (status);
} // Endproc.


void    HighScoreScreen::SetItemText (Folio::Core::Game::TextItemPtr::element_type &item)
{
    switch (item.GetItemId ())
    {
    case HIGH_SCORE_SCREEN_ITEM_TITLE:
        item.GetGdiRasterText ()->SetTextString ("ULTIMATE HALL OF FAME");
        break;

    case HIGH_SCORE_SCREEN_ITEM_1_POSITION_TEXT:
        item.GetGdiRasterText ()->SetTextString ("1ST");
        break;

    case HIGH_SCORE_SCREEN_ITEM_1_SCORE:
        item.GetGdiRasterText ()->SetTextString (InformationPanel::DescribeScore (m_highScoreTable.GetHighScore (0).m_score));
        break;

    case HIGH_SCORE_SCREEN_ITEM_1_INITIALS:
        item.GetGdiRasterText ()->SetTextString (m_highScoreTable.GetHighScore (0).m_initials);
        break;

    case HIGH_SCORE_SCREEN_ITEM_2_POSITION_TEXT:
        item.GetGdiRasterText ()->SetTextString ("2ND");
        break;

    case HIGH_SCORE_SCREEN_ITEM_2_SCORE:
        item.GetGdiRasterText ()->SetTextString (InformationPanel::DescribeScore (m_highScoreTable.GetHighScore (1).m_score));
        break;

    case HIGH_SCORE_SCREEN_ITEM_2_INITIALS:
        item.GetGdiRasterText ()->SetTextString (m_highScoreTable.GetHighScore (1).m_initials);
        break;

    case HIGH_SCORE_SCREEN_ITEM_3_POSITION_TEXT:
        item.GetGdiRasterText ()->SetTextString ("3RD");
        break;

    case HIGH_SCORE_SCREEN_ITEM_3_SCORE:
        item.GetGdiRasterText ()->SetTextString (InformationPanel::DescribeScore (m_highScoreTable.GetHighScore (2).m_score));
        break;

    case HIGH_SCORE_SCREEN_ITEM_3_INITIALS:
        item.GetGdiRasterText ()->SetTextString (m_highScoreTable.GetHighScore (2).m_initials);
        break;

    case HIGH_SCORE_SCREEN_ITEM_4_POSITION_TEXT:
        item.GetGdiRasterText ()->SetTextString ("4TH");
        break;

    case HIGH_SCORE_SCREEN_ITEM_4_SCORE:
        item.GetGdiRasterText ()->SetTextString (InformationPanel::DescribeScore (m_highScoreTable.GetHighScore (3).m_score));
        break;

    case HIGH_SCORE_SCREEN_ITEM_4_INITIALS:
        item.GetGdiRasterText ()->SetTextString (m_highScoreTable.GetHighScore (3).m_initials);
        break;

    case HIGH_SCORE_SCREEN_ITEM_5_POSITION_TEXT:
        item.GetGdiRasterText ()->SetTextString ("5TH");
        break;

    case HIGH_SCORE_SCREEN_ITEM_5_SCORE:
        item.GetGdiRasterText ()->SetTextString (InformationPanel::DescribeScore (m_highScoreTable.GetHighScore (4).m_score));
        break;

    case HIGH_SCORE_SCREEN_ITEM_5_INITIALS:
        item.GetGdiRasterText ()->SetTextString (m_highScoreTable.GetHighScore (4).m_initials);
        break;

    case HIGH_SCORE_SCREEN_ITEM_6_POSITION_TEXT:
        item.GetGdiRasterText ()->SetTextString ("6TH");
        break;

    case HIGH_SCORE_SCREEN_ITEM_6_SCORE:
        item.GetGdiRasterText ()->SetTextString (InformationPanel::DescribeScore (m_highScoreTable.GetHighScore (5).m_score));
        break;

    case HIGH_SCORE_SCREEN_ITEM_6_INITIALS:
        item.GetGdiRasterText ()->SetTextString (m_highScoreTable.GetHighScore (5).m_initials);
        break;

    case HIGH_SCORE_SCREEN_ITEM_COPYRIGHT_TEXT:
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
