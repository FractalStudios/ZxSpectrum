// "Home-made" includes.
#include    "StdAfx.h"
#include    "BackgroundItem.h"
#include    "BorderScreen.h"
#include    "DrawingElementIds.h"

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
        // Add border screen graphic item.

        status = AddGraphicItem (dcHandle, 
                                 instanceHandle,
                                 DRAWING_ELEMENT_BORDER_SCREEN_ITEM,
                                 Folio::Core::Game::ItemAttributes<BACKGROUND_ITEM_ID> (*itr));
    } // Endfor.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
