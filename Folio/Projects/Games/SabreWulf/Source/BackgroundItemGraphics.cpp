// "Home-made" includes.
#include    "StdAfx.h"
#include    "CollisionGrid.h"
#include    "DrawingElement.h"
#include    "BackgroundItemGraphics.h"

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Background item graphic attributes.
struct BackgroundItemGraphicAttributes
{
    BACKGROUND_ITEM_ID          m_backgroundItemId;         // The identifier of the background item.
    UInt16                      m_bitmapResourceId;         // The background item's bitmap resource identifier.
    CollisionGrid::CellValue    m_collisionGridCellValue;   // The collision grid cell value of the background item.
}; // Endstruct.

// Background item graphic attributes table.
static  const   BackgroundItemGraphicAttributes g_backgroundItemGraphicAttributesTable [] =
{
//      m_backgroundItemId                                                  m_bitmapResourceId                                              m_collisionGridCellValue
    {   BACKGROUND_ITEM_70bc,                                               IDB_BITMAP_BACKGROUND_ITEM_70bc,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_71b3,                                               IDB_BITMAP_BACKGROUND_ITEM_71b3,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_7298,                                               IDB_BITMAP_BACKGROUND_ITEM_7298,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_72f6,                                               IDB_BITMAP_BACKGROUND_ITEM_72f6,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_7462,                                               IDB_BITMAP_BACKGROUND_ITEM_7462,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_7523,                                               IDB_BITMAP_BACKGROUND_ITEM_7523,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_771f,                                               IDB_BITMAP_BACKGROUND_ITEM_771f,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_785e,                                               IDB_BITMAP_BACKGROUND_ITEM_785e,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_78f2,                                               IDB_BITMAP_BACKGROUND_ITEM_78f2,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_7947,                                               IDB_BITMAP_BACKGROUND_ITEM_7947,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_7981,                                               IDB_BITMAP_BACKGROUND_ITEM_7981,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_7b11,                                               IDB_BITMAP_BACKGROUND_ITEM_7b11,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_7bb7,                                               IDB_BITMAP_BACKGROUND_ITEM_7bb7,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_7c0c,                                               IDB_BITMAP_BACKGROUND_ITEM_7c0c,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_7ccd,                                               IDB_BITMAP_BACKGROUND_ITEM_7ccd,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_7e4b,                                               IDB_BITMAP_BACKGROUND_ITEM_7e4b,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_8047,                                               IDB_BITMAP_BACKGROUND_ITEM_8047,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_81c5,                                               IDB_BITMAP_BACKGROUND_ITEM_81c5,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_8382,                                               IDB_BITMAP_BACKGROUND_ITEM_8382,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_83aa,                                               IDB_BITMAP_BACKGROUND_ITEM_83aa,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_83d2,                                               IDB_BITMAP_BACKGROUND_ITEM_83d2,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_8427,                                               IDB_BITMAP_BACKGROUND_ITEM_8427,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_847c,                                               IDB_BITMAP_BACKGROUND_ITEM_847c,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_8558,                                               IDB_BITMAP_BACKGROUND_ITEM_8558,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_85c8,                                               IDB_BITMAP_BACKGROUND_ITEM_85c8,                                CollisionGrid::CELL_VALUE_EXIT,         },
    {   BACKGROUND_ITEM_86da,                                               IDB_BITMAP_BACKGROUND_ITEM_86da,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_8702,                                               IDB_BITMAP_BACKGROUND_ITEM_8702,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_872a,                                               IDB_BITMAP_BACKGROUND_ITEM_872a,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_8806,                                               IDB_BITMAP_BACKGROUND_ITEM_8806,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_89c3,                                               IDB_BITMAP_BACKGROUND_ITEM_89c3,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_8b80,                                               IDB_BITMAP_BACKGROUND_ITEM_8b80,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_8c5c,                                               IDB_BITMAP_BACKGROUND_ITEM_8c5c,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_8ccc,                                               IDB_BITMAP_BACKGROUND_ITEM_8ccc,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_8d3c,                                               IDB_BITMAP_BACKGROUND_ITEM_8d3c,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_8e18,                                               IDB_BITMAP_BACKGROUND_ITEM_8e18,                                CollisionGrid::CELL_VALUE_SOLID_ITEM,   },
    {   BACKGROUND_ITEM_8f2a,                                               IDB_BITMAP_BACKGROUND_ITEM_8f2a,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_90a8,                                               IDB_BITMAP_BACKGROUND_ITEM_90a8,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_93c4,                                               IDB_BITMAP_BACKGROUND_ITEM_93c4,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_955d,                                               IDB_BITMAP_BACKGROUND_ITEM_955d,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_95cd,                                               IDB_BITMAP_BACKGROUND_ITEM_95cd,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_9673,                                               IDB_BITMAP_BACKGROUND_ITEM_9673,                                CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_BACKGROUND_ITEM_e1ec,                               IDB_BITMAP_BACKGROUND_ITEM_e1ec,                                CollisionGrid::CELL_VALUE_EMPTY,        },
    {   BACKGROUND_ITEM_BACKGROUND_ITEM_e3a0_AMULET_PIECE_TOP_LEFT,         IDB_BITMAP_BACKGROUND_ITEM_e3a0_AMULET_PIECE_TOP_LEFT,          CollisionGrid::CELL_VALUE_EMPTY,        },
    {   BACKGROUND_ITEM_BACKGROUND_ITEM_e3a0_AMULET_BLANK_TOP_LEFT,         IDB_BITMAP_BACKGROUND_ITEM_e3a0_AMULET_BLANK_TOP_LEFT,          CollisionGrid::CELL_VALUE_EMPTY,        },
    {   BACKGROUND_ITEM_BACKGROUND_ITEM_e494_AMULET_PIECE_TOP_RIGHT,        IDB_BITMAP_BACKGROUND_ITEM_e494_AMULET_PIECE_TOP_RIGHT,         CollisionGrid::CELL_VALUE_EMPTY,        },
    {   BACKGROUND_ITEM_BACKGROUND_ITEM_e494_AMULET_BLANK_TOP_RIGHT,        IDB_BITMAP_BACKGROUND_ITEM_e494_AMULET_BLANK_TOP_RIGHT,         CollisionGrid::CELL_VALUE_EMPTY,        },
    {   BACKGROUND_ITEM_BACKGROUND_ITEM_e588_AMULET_PIECE_BOTTOM_LEFT,      IDB_BITMAP_BACKGROUND_ITEM_e588_AMULET_PIECE_BOTTOM_LEFT,       CollisionGrid::CELL_VALUE_EMPTY,        },
    {   BACKGROUND_ITEM_BACKGROUND_ITEM_e588_AMULET_BLANK_BOTTOM_LEFT,      IDB_BITMAP_BACKGROUND_ITEM_e588_AMULET_BLANK_BOTTOM_LEFT,       CollisionGrid::CELL_VALUE_EMPTY,        },
    {   BACKGROUND_ITEM_BACKGROUND_ITEM_e67c_AMULET_PIECE_BOTTOM_RIGHT,     IDB_BITMAP_BACKGROUND_ITEM_e67c_AMULET_PIECE_BOTTOM_RIGHT,      CollisionGrid::CELL_VALUE_EMPTY,        },
    {   BACKGROUND_ITEM_BACKGROUND_ITEM_e67c_AMULET_BLANK_BOTTOM_RIGHT,     IDB_BITMAP_BACKGROUND_ITEM_e67c_AMULET_BLANK_BOTTOM_RIGHT,      CollisionGrid::CELL_VALUE_EMPTY,        },
};


FolioStatus CreateBackgroundItemGraphics (FolioHandle                   dcHandle, 
                                          FolioHandle                   instanceHandle,
                                          BackgroundItemGraphicsMapPtr  &backgroundItemGraphicsMap)
{
    FolioStatus status = ERR_SUCCESS;

    // Create the background item graphics map.

    backgroundItemGraphicsMap.reset (new BackgroundItemGraphicsMapPtr::element_type);

    // Build the background item graphics map. 

    for (UInt32 index = 0; 
         (status == ERR_SUCCESS) && (index < (sizeof (g_backgroundItemGraphicAttributesTable) / sizeof (BackgroundItemGraphicAttributes)));
         ++index)
    {              
        // Create a background item graphic.

        BackgroundItemGraphic   backgroundItemGraphic(new BackgroundItemGraphic::element_type);

        status = backgroundItemGraphic->Create (dcHandle,
                                                instanceHandle,
                                                DRAWING_ELEMENT_BACKGROUND_ITEM,
                                                g_backgroundItemGraphicAttributesTable [index].m_bitmapResourceId,
                                                false,  // Masked GDI bitmap is not required.
                                                g_backgroundItemGraphicAttributesTable [index].m_collisionGridCellValue);
        
        if (status == ERR_SUCCESS)
        {
            // Store the background item graphic in the background item graphics map.

            backgroundItemGraphicsMap->insert (BackgroundItemGraphicsMap::value_type(g_backgroundItemGraphicAttributesTable [index].m_backgroundItemId, 
                                                                                     backgroundItemGraphic));
        } // Endif.
       
    } // Endfor.

    if (status != ERR_SUCCESS)
    {
        backgroundItemGraphicsMap->clear ();
    } // Endif.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
