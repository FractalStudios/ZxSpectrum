// "Home-made" includes.
#include    "StdAfx.h"
#include    "DrawingElement.h"
#include    "LoadingScreen.h"
#include    "ZxSpectrum.h"

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Loading screen item attributes.
struct LoadingScreenItemAttributes
{
    LOADING_SCREEN_ITEM_ID  m_itemId;           // The identifier of the loading screen item.
    UInt16                  m_bitmapResourceId; // The loading screen item's bitmap resource identifier (if it's a graphic item).
    Int32                   m_screenXLeft;      // The screen X left of the loading screen item.
    Int32                   m_screenYTop;       // The screen Y top of the loading screen item.
 }; // Endstruct.

// Loading screen item attributes table.
static  const   LoadingScreenItemAttributes   g_loadingScreenAttributesTable [] =
{
//      m_itemId                        m_bitmapResourceId          m_screenXLeft   m_screenYTop
    {   LOADING_SCREEN_ITEM_GRAPHIC,    IDB_BITMAP_LOADING_SCREEN,  0,              0,  },
};


LoadingScreen::LoadingScreen ()
{
} // Endproc.


LoadingScreen::~LoadingScreen ()
{
} // Endproc.


FolioStatus LoadingScreen::BuildScreenItems (FolioHandle    dcHandle, 
                                             FolioHandle    instanceHandle)
{                               
    FolioStatus status = ERR_SUCCESS;

    // Build the loading screen items. 

    for (UInt32 index = 0; 
         (status == ERR_SUCCESS) && (index < (sizeof (g_loadingScreenAttributesTable) / sizeof (LoadingScreenItemAttributes)));
         ++index)
    {              
        // Build the loading screen item.

        switch (g_loadingScreenAttributesTable [index].m_itemId)
        {
        case LOADING_SCREEN_ITEM_GRAPHIC:
            {
                // Create a loading screen graphic item.
            
                Folio::Core::Game::GraphicItemPtr   item(new Folio::Core::Game::GraphicItemPtr::element_type);
            
                status = item->Create (dcHandle,
                                       instanceHandle,
                                       DRAWING_ELEMENT_LOADING_SCREEN_ITEM,
                                       g_loadingScreenAttributesTable [index].m_bitmapResourceId,
                                       g_loadingScreenAttributesTable [index].m_itemId,
                                       g_loadingScreenAttributesTable [index].m_screenXLeft, 
                                       g_loadingScreenAttributesTable [index].m_screenYTop,
                                       ZxSpectrum::DEFAULT_SCREEN_SCALE);

                if (status == ERR_SUCCESS)
                {
                    // Store the loading screen item in the loading screen items list.

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


FolioStatus LoadingScreen::ProcessScreenKeyboardMsg (UInt32 wParam,
                                                     UInt32 lParam,
                                                     bool   keyDown)
{
    // Stop displaying the loading screen.

    StopDisplaying ();

    return (ERR_SUCCESS);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
