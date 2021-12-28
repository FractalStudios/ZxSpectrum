// "Home-made" includes.
#include    "StdAfx.h"
#include    "BackgroundItemGraphics.h"
#include    "CollisionGrid.h"

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
    CollisionGrid::CellValue    m_collisionGridCellValue;   // The collision grid cell value of the background item.
}; // Endstruct.

// Background item graphic attributes table.
static  const   BackgroundItemGraphicAttributes g_backgroundItemGraphicAttributesTable [] =
{
//      m_backgroundItemId                                                  m_collisionGridCellValue
    {   BACKGROUND_ITEM_70bc,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_71b3,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_7298,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_72f6,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_7462,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_7523,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_771f,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_785e,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_78f2,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_7947,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_7981,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_7b11,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_7bb7,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_7c0c,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_7ccd,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_7e4b,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_8047,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_81c5,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_8382,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_83aa,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_83d2,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_8427,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_847c,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_8558,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_85c8,                                               CollisionGrid::CELL_VALUE_EXIT,         },
    {   BACKGROUND_ITEM_86da,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_8702,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_872a,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_8806,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_89c3,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_8b80,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_8c5c,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_8ccc,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_8d3c,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_8e18,                                               CollisionGrid::CELL_VALUE_SOLID_ITEM,   },
    {   BACKGROUND_ITEM_8f2a,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_90a8,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_93c4,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_955d,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_95cd,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_9673,                                               CollisionGrid::CELL_VALUE_WALL,         },
    {   BACKGROUND_ITEM_e1ec,                                               CollisionGrid::CELL_VALUE_EMPTY,        },
    {   BACKGROUND_ITEM_BACKGROUND_ITEM_e3a0_AMULET_PIECE_TOP_LEFT,         CollisionGrid::CELL_VALUE_EMPTY,        },
    {   BACKGROUND_ITEM_BACKGROUND_ITEM_e3a0_AMULET_BLANK_TOP_LEFT,         CollisionGrid::CELL_VALUE_EMPTY,        },
    {   BACKGROUND_ITEM_BACKGROUND_ITEM_e494_AMULET_PIECE_TOP_RIGHT,        CollisionGrid::CELL_VALUE_EMPTY,        },
    {   BACKGROUND_ITEM_BACKGROUND_ITEM_e494_AMULET_BLANK_TOP_RIGHT,        CollisionGrid::CELL_VALUE_EMPTY,        },
    {   BACKGROUND_ITEM_BACKGROUND_ITEM_e588_AMULET_PIECE_BOTTOM_LEFT,      CollisionGrid::CELL_VALUE_EMPTY,        },
    {   BACKGROUND_ITEM_BACKGROUND_ITEM_e588_AMULET_BLANK_BOTTOM_LEFT,      CollisionGrid::CELL_VALUE_EMPTY,        },
    {   BACKGROUND_ITEM_BACKGROUND_ITEM_e67c_AMULET_PIECE_BOTTOM_RIGHT,     CollisionGrid::CELL_VALUE_EMPTY,        },
    {   BACKGROUND_ITEM_BACKGROUND_ITEM_e67c_AMULET_BLANK_BOTTOM_RIGHT,     CollisionGrid::CELL_VALUE_EMPTY,        },
};


FolioStatus CreateBackgroundItemGraphics (FolioHandle                   instanceHandle,
                                          BackgroundItemGraphicsMap&    backgroundItemGraphicsMap)
{
    FolioStatus status = ERR_SUCCESS;

    backgroundItemGraphicsMap.clear (); // Initialise!

    // Build the background item graphics map. 

    for (UInt32 index = 0; 
         (status == ERR_SUCCESS) && (index < (sizeof (g_backgroundItemGraphicAttributesTable) / sizeof (BackgroundItemGraphicAttributes)));
         ++index)
    {              
        // Create a background item graphic.

        BackgroundItemGraphic   backgroundItemGraphic(new BackgroundItemGraphic::element_type);

        status = backgroundItemGraphic->Create (instanceHandle,
                                                Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BACKGROUND_ITEM,
                                                g_backgroundItemGraphicAttributesTable [index].m_backgroundItemId,
                                                false,  // Masked GDI bitmap is not required.
                                                g_backgroundItemGraphicAttributesTable [index].m_collisionGridCellValue);
        
        if (status == ERR_SUCCESS)
        {
            // Store the background item graphic in the background item graphics map.

            backgroundItemGraphicsMap.insert (BackgroundItemGraphicsMap::value_type(g_backgroundItemGraphicAttributesTable [index].m_backgroundItemId, 
                                                                                    backgroundItemGraphic));
        } // Endif.
       
    } // Endfor.

    if (status != ERR_SUCCESS)
    {
        backgroundItemGraphicsMap.clear ();
    } // Endif.

    return (status);
} // Endproc.


FolioStatus FindBackgroundItemGraphic (BACKGROUND_ITEM_ID               backgroundItemId,
                                       const BackgroundItemGraphicsMap& backgroundItemGraphicsMap,
                                       BackgroundItemGraphic&           backgroundItemGraphic)
{
    FolioStatus status = ERR_SUCCESS;

    // Find the background item graphic in the background item graphics map.

    BackgroundItemGraphicsMap::const_iterator   backgroundItemGraphicsMapItr = backgroundItemGraphicsMap.find (backgroundItemId);

    if (backgroundItemGraphicsMapItr != backgroundItemGraphicsMap.end ())
    {
        // Note the background item's graphic.

        backgroundItemGraphic = backgroundItemGraphicsMapItr->second;
    } // Endif.        

    else
    {
        status = ERR_NOT_FOUND;
    } // Endelse.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
