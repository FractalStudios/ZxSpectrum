// "Home-made" includes.
#include    "StdAfx.h"
#include    "DrawingElement.h"
#include    "Font.h"
#include    "GameOverScreen.h"
#include    "InformationPanel.h"
#include    "ZxSpectrum.h"

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Game over screen item attributes.
struct GameOverScreenItemAttributes
{
    // Flags.
    static  const   UInt32  ADD_ALWAYS                  = 0x00000001;
    static  const   UInt32  ADD_IF_COMPLETED_GAME       = 0x00000002;
    static  const   UInt32  ADD_IF_NOT_COMPLETED_GAME   = 0x00000004;

    GAME_OVER_SCREEN_ITEM_ID    m_itemId;           // The identifier of the game over screen item.
    UInt32                      m_flags;            // The flags of the game over screen item
    UInt16                      m_bitmapResourceId; // The game over screen item's bitmap resource identifier (if it's a graphic item).
    Int32                       m_screenXLeft;      // The screen X left of the game over screen item.
    Int32                       m_screenYTop;       // The screen Y top of the game over screen item.
    ZxSpectrum::COLOUR          m_colour;           // The colour of the game over screen item.
 }; // Endstruct.

// Game over screen item attributes table.
static  const   GameOverScreenItemAttributes    g_gameOverScreenAttributesTable [] =
{
//      m_itemId                                            m_flags                                                     m_bitmapResourceId      m_screenXLeft   m_screenYTop    m_colour
    {   GAME_OVER_SCREEN_ITEM_ROOM,                         GameOverScreenItemAttributes::ADD_IF_COMPLETED_GAME,        IDB_BITMAP_ROOM_11,       0,             0,             ZxSpectrum::BRIGHT | ZxSpectrum::WHITE, },
    {   GAME_OVER_SCREEN_ITEM_CONGRATULATIONS_TEXT,         GameOverScreenItemAttributes::ADD_IF_COMPLETED_GAME,        0,                       64,            32,             ZxSpectrum::BRIGHT | ZxSpectrum::WHITE, },
    {   GAME_OVER_SCREEN_ITEM_YOU_HAVE_ESCAPED_TEXT,        GameOverScreenItemAttributes::ADD_IF_COMPLETED_GAME,        0,                       64,            48,             ZxSpectrum::BRIGHT | ZxSpectrum::WHITE, },
    {   GAME_OVER_SCREEN_ITEM_GAME_OVER_TEXT,               GameOverScreenItemAttributes::ADD_IF_NOT_COMPLETED_GAME,    0,                       64,            48,             ZxSpectrum::BRIGHT | ZxSpectrum::WHITE, },
    {   GAME_OVER_SCREEN_ITEM_TIME_TEXT,                    GameOverScreenItemAttributes::ADD_ALWAYS,                   0,                       64,            64,             ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,  },
    {   GAME_OVER_SCREEN_ITEM_TIME_VALUE,                   GameOverScreenItemAttributes::ADD_ALWAYS,                   0,                      128,            64,             ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,  },
    {   GAME_OVER_SCREEN_ITEM_SCORE_TEXT,                   GameOverScreenItemAttributes::ADD_ALWAYS,                   0,                       64,            80,             ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,  },
    {   GAME_OVER_SCREEN_ITEM_SCORE_VALUE,                  GameOverScreenItemAttributes::ADD_ALWAYS,                   0,                      128,            80,             ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,  },
    {   GAME_OVER_SCREEN_ITEM_PERCENTAGE_COMPLETED_TEXT,    GameOverScreenItemAttributes::ADD_ALWAYS,                   0,                       64,            96,             ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,  },
    {   GAME_OVER_SCREEN_ITEM_PERCENTAGE_COMPLETED_VALUE,   GameOverScreenItemAttributes::ADD_ALWAYS,                   0,                      128,            96,             ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,  },
};


GameOverScreen::GameOverScreen (bool    mainPlayerCompletedGame,
                                UInt32  timeInSeconds,
                                UInt32  score,
                                UInt32  percentageCompleted)
:   m_mainPlayerCompletedGame(mainPlayerCompletedGame),
    m_timeInSeconds(timeInSeconds),
    m_score(score),
    m_percentageCompleted(percentageCompleted)
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

    for (UInt32 index = 0; 
         (status == ERR_SUCCESS) && (index < (sizeof (g_gameOverScreenAttributesTable) / sizeof (GameOverScreenItemAttributes)));
         ++index)
    {   
        // Should the game over item be added to the game over screen?

        if ((g_gameOverScreenAttributesTable [index].m_flags == GameOverScreenItemAttributes::ADD_ALWAYS)                                                   ||
            (!m_mainPlayerCompletedGame && (g_gameOverScreenAttributesTable [index].m_flags == GameOverScreenItemAttributes::ADD_IF_NOT_COMPLETED_GAME))    ||
            ( m_mainPlayerCompletedGame && (g_gameOverScreenAttributesTable [index].m_flags == GameOverScreenItemAttributes::ADD_IF_COMPLETED_GAME)))
        {
            // Yes. Build the game over screen item.

            switch (g_gameOverScreenAttributesTable [index].m_itemId)
            {
            case GAME_OVER_SCREEN_ITEM_ROOM:
                {
                    // Create a game over screen graphic item.
            
                    Folio::Core::Game::GraphicItemPtr   item(new Folio::Core::Game::GraphicItemPtr::element_type);
            
                    status = item->Create (dcHandle,
                                           instanceHandle,
                                           DRAWING_ELEMENT_GAME_OVER_SCREEN_ITEM,
                                           g_gameOverScreenAttributesTable [index].m_bitmapResourceId,
                                           g_gameOverScreenAttributesTable [index].m_itemId,
                                           g_gameOverScreenAttributesTable [index].m_screenXLeft, 
                                           g_gameOverScreenAttributesTable [index].m_screenYTop,
                                           ZxSpectrum::DEFAULT_SCREEN_SCALE, 
                                           ZxSpectrum::GetBitmapChangeColour (),
                                           ZxSpectrum::MapInkColour (g_gameOverScreenAttributesTable [index].m_colour));

                    if (status == ERR_SUCCESS)
                    {
                        // Store the game over screen item in the game over screen items list.

                        m_itemsList.push_back (item);
                    } // Endif.
            
                } // Endscope.
                break;

            case GAME_OVER_SCREEN_ITEM_CONGRATULATIONS_TEXT:      
            case GAME_OVER_SCREEN_ITEM_YOU_HAVE_ESCAPED_TEXT:     
            case GAME_OVER_SCREEN_ITEM_GAME_OVER_TEXT:            
            case GAME_OVER_SCREEN_ITEM_TIME_TEXT:                 
            case GAME_OVER_SCREEN_ITEM_TIME_VALUE:                
            case GAME_OVER_SCREEN_ITEM_SCORE_TEXT:                
            case GAME_OVER_SCREEN_ITEM_SCORE_VALUE:               
            case GAME_OVER_SCREEN_ITEM_PERCENTAGE_COMPLETED_TEXT: 
            case GAME_OVER_SCREEN_ITEM_PERCENTAGE_COMPLETED_VALUE:
                {
                    // Create a game over screen text item.

                    Folio::Core::Game::TextItemPtr  item(new Folio::Core::Game::TextItemPtr::element_type);
        
                    status = item->Create (dcHandle,
                                           DRAWING_ELEMENT_GAME_OVER_SCREEN_ITEM,
                                           *GetFont (),
                                           g_gameOverScreenAttributesTable [index].m_itemId,
                                           g_gameOverScreenAttributesTable [index].m_screenXLeft, 
                                           g_gameOverScreenAttributesTable [index].m_screenYTop,
                                           ZxSpectrum::DEFAULT_SCREEN_SCALE, 
                                           ZxSpectrum::MapInkColour (g_gameOverScreenAttributesTable [index].m_colour));

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

        } // Endif.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus GameOverScreen::ProcessScreenKeyboardMsg (UInt32    wParam,
                                                      UInt32    lParam,
                                                      bool      keyDown)
{
    // Stop displaying the game over screen.

    StopDisplaying ();

    return (ERR_SUCCESS);
} // Endproc.


void    GameOverScreen::SetItemText (Folio::Core::Game::TextItemPtr::element_type &item)
{
    switch (item.GetItemId ())
    {
    case GAME_OVER_SCREEN_ITEM_CONGRATULATIONS_TEXT:
        item.GetGdiRasterText ()->SetTextString ("CONGRATULATIONS");
        break;

    case GAME_OVER_SCREEN_ITEM_YOU_HAVE_ESCAPED_TEXT:
        item.GetGdiRasterText ()->SetTextString ("YOU HAVE ESCAPED");
        break;

    case GAME_OVER_SCREEN_ITEM_GAME_OVER_TEXT:
        item.GetGdiRasterText ()->SetTextString ("GAME OVER");
        break;

    case GAME_OVER_SCREEN_ITEM_TIME_TEXT:
        item.GetGdiRasterText ()->SetTextString ("TIME");
        break;

    case GAME_OVER_SCREEN_ITEM_TIME_VALUE:
        item.GetGdiRasterText ()->SetTextString (InformationPanel::DescribeTime (m_timeInSeconds));
        break;

    case GAME_OVER_SCREEN_ITEM_SCORE_TEXT:
        item.GetGdiRasterText ()->SetTextString ("SCORE");
        break;

    case GAME_OVER_SCREEN_ITEM_SCORE_VALUE:
        item.GetGdiRasterText ()->SetTextString (InformationPanel::DescribeScore (m_score));
        break;

    case GAME_OVER_SCREEN_ITEM_PERCENTAGE_COMPLETED_TEXT:
        item.GetGdiRasterText ()->SetTextString ("%");
        break;

    case GAME_OVER_SCREEN_ITEM_PERCENTAGE_COMPLETED_VALUE:
        item.GetGdiRasterText ()->SetTextString (InformationPanel::DescribePercentage (m_percentageCompleted));
        break;

    default:
        break;
    } // Endswitch.

} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
