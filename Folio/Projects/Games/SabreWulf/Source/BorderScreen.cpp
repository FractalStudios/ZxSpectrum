// "Home-made" includes.
#include    "StdAfx.h"
#include    "BackgroundItem.h"
#include    "BorderScreen.h"

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// The border.
static  const   BackgroundItemsList g_border = 
{    
    {   { BACKGROUND_ITEM_7981,   0,  16, }, {BACKGROUND_ITEM_7981,   0, 104, }, {BACKGROUND_ITEM_7981, 224,  16, }, {BACKGROUND_ITEM_7981, 224, 104, }, {BACKGROUND_ITEM_7947,  32,  16, }, {BACKGROUND_ITEM_70bc,  48,  16, }, {BACKGROUND_ITEM_7947, 120,  16, }, {BACKGROUND_ITEM_70bc, 136,  16, }, {BACKGROUND_ITEM_7947, 208,  16, }, {BACKGROUND_ITEM_7947,  32, 168, }, {BACKGROUND_ITEM_70bc,  48, 168, }, {BACKGROUND_ITEM_7947, 120, 168, }, {BACKGROUND_ITEM_70bc, 136, 168, }, {BACKGROUND_ITEM_7947, 208, 168, },    }, 
};


BorderScreen::BorderScreen ()
{
} // Endproc.


BorderScreen::~BorderScreen ()
{
} // Endproc.


FolioStatus BorderScreen::AddBorderScreenItems (FolioHandle dcHandle, 
                                                FolioHandle instanceHandle)
{                               
    FolioStatus status = ERR_SUCCESS;

    // Add the border screen items to the screen's item list.

    for (BackgroundItemsList::const_iterator itr = g_border.begin ();
         (status == ERR_SUCCESS) && (itr != g_border.end ());
         ++itr)
    {
        // Create a border screen graphic item.
            
        Folio::Core::Game::GraphicItemPtr   item(new Folio::Core::Game::GraphicItemPtr::element_type);
            
        status = item->Create (dcHandle,
                               instanceHandle,
                               DRAWING_ELEMENT_BORDER_SCREEN_ITEM,
                               itr->GetBitmapResourceId (),
                               itr->GetBackgroundItemId (),
                               itr->GetScreenXLeft (), 
                               itr->GetScreenYTop (),
                               Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE);

        if (status == ERR_SUCCESS)
        {
            // Store the border screen item in the screen's items list.

            m_itemsList.push_back (item);
        } // Endif.

    } // Endfor.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
