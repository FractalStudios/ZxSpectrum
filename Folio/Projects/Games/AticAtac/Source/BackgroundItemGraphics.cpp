// "Home-made" includes.
#include    "StdAfx.h"
#include    "BackgroundItem.h"
#include    "BackgroundItemGraphics.h"
#include    "CollisionGrid.h"
#include    "DrawingElement.h"
#include    "Globals.h"

namespace Folio
{

namespace Games
{

namespace AticAtac
{


// Background item graphic attributes.
struct BackgroundItemGraphicAttributes
{
    BACKGROUND_ITEM_ID          m_backgroundItemId;         // The identifier of the background item.
    bool                        m_supportsRoomColouring;    // true if the background item supports room colouring.
    bool                        m_maskRqd;                  // true if the background item requires a mask.
    CollisionGrid::CellValue    m_collisionGridCellValue;   // The collision grid cell value of the background item.
}; // Endstruct.

// Background item graphic attributes table.
static  const   BackgroundItemGraphicAttributes g_backgroundItemGraphicAttributesTable [] =
{
//      m_backgroundItemId                              m_supportsRoomColouring m_maskRqd   m_collisionGridCellValue
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,                true,                   false,      CollisionGrid::CELL_VALUE_EXIT,         },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,              false,                  false,      CollisionGrid::CELL_VALUE_EXIT,         },
    {   BACKGROUND_ITEM_BIG_DOOR_FRAME,                 false,                  false,      CollisionGrid::CELL_VALUE_EXIT,         },
    {   BACKGROUND_ITEM_RED_LOCKED_NORMAL_DOOR,         false,                  false,      CollisionGrid::CELL_VALUE_EXIT,         },
    {   BACKGROUND_ITEM_GREEN_LOCKED_NORMAL_DOOR,       false,                  false,      CollisionGrid::CELL_VALUE_EXIT,         },
    {   BACKGROUND_ITEM_CYAN_LOCKED_NORMAL_DOOR,        false,                  false,      CollisionGrid::CELL_VALUE_EXIT,         },
    {   BACKGROUND_ITEM_YELLOW_LOCKED_NORMAL_DOOR,      false,                  false,      CollisionGrid::CELL_VALUE_EXIT,         },
    {   BACKGROUND_ITEM_RED_LOCKED_CAVE_DOOR,           true,                   false,      CollisionGrid::CELL_VALUE_EXIT,         },
    {   BACKGROUND_ITEM_GREEN_LOCKED_CAVE_DOOR,         true,                   false,      CollisionGrid::CELL_VALUE_EXIT,         },
    {   BACKGROUND_ITEM_CYAN_LOCKED_CAVE_DOOR,          true,                   false,      CollisionGrid::CELL_VALUE_EXIT,         },
    {   BACKGROUND_ITEM_YELLOW_LOCKED_CAVE_DOOR,        true,                   false,      CollisionGrid::CELL_VALUE_EXIT,         },
    {   BACKGROUND_ITEM_CLOCK,                          true,                   false,      CollisionGrid::CELL_VALUE_EXIT,         },
    {   BACKGROUND_ITEM_PICTURE,                        true,                   false,      CollisionGrid::CELL_VALUE_EMPTY,        },
    {   BACKGROUND_ITEM_TABLE,                          false,                  false,      CollisionGrid::CELL_VALUE_SOLID_ITEM,   },
    {   BACKGROUND_ITEM_ANTLER_TROPHY,                  false,                  false,      CollisionGrid::CELL_VALUE_EMPTY,        },
    {   BACKGROUND_ITEM_TROPHY,                         false,                  false,      CollisionGrid::CELL_VALUE_EMPTY,        },
    {   BACKGROUND_ITEM_BOOKCASE,                       true,                   false,      CollisionGrid::CELL_VALUE_EXIT,         },
    {   BACKGROUND_ITEM_CLOSED_TRAP_DOOR,               false,                  false,      CollisionGrid::CELL_VALUE_EXIT,         },
    {   BACKGROUND_ITEM_OPEN_TRAP_DOOR,                 false,                  false,      CollisionGrid::CELL_VALUE_EXIT,         },
    {   BACKGROUND_ITEM_BARREL,                         false,                  false,      CollisionGrid::CELL_VALUE_EXIT,         },
    {   BACKGROUND_ITEM_RUG,                            false,                  false,      CollisionGrid::CELL_VALUE_EMPTY,        },
    {   BACKGROUND_ITEM_ACG_SHIELD,                     false,                  false,      CollisionGrid::CELL_VALUE_EMPTY,        },
    {   BACKGROUND_ITEM_SHIELD,                         true,                   false,      CollisionGrid::CELL_VALUE_EMPTY,        },
    {   BACKGROUND_ITEM_KNIGHT,                         false,                  false,      CollisionGrid::CELL_VALUE_EMPTY,        },
    {   BACKGROUND_ITEM_CLOSED_NORMAL_DOOR,             false,                  true,       CollisionGrid::CELL_VALUE_EXIT,         },
    {   BACKGROUND_ITEM_OPEN_NORMAL_DOOR,               false,                  false,      CollisionGrid::CELL_VALUE_EXIT,         },
    {   BACKGROUND_ITEM_CLOSED_CAVE_DOOR,               true,                   true,       CollisionGrid::CELL_VALUE_EXIT,         },
    {   BACKGROUND_ITEM_OPEN_CAVE_DOOR,                 true,                   false,      CollisionGrid::CELL_VALUE_EXIT,         },
    {   BACKGROUND_ITEM_ACG_EXIT_DOOR,                  true,                   false,      CollisionGrid::CELL_VALUE_EXIT,         },
    {   BACKGROUND_ITEM_PICTURE_2,                      false,                  false,      CollisionGrid::CELL_VALUE_EMPTY,        },
    {   BACKGROUND_ITEM_SKELETON,                       true,                   false,      CollisionGrid::CELL_VALUE_EMPTY,        },
    {   BACKGROUND_ITEM_BARRELS,                        false,                  false,      CollisionGrid::CELL_VALUE_EMPTY,        },
};                                                                                                             


FolioStatus CreateBackgroundItemGraphics (FolioHandle instanceHandle)
{
    FolioStatus status = ERR_SUCCESS;

    // Add the background item graphics into the resource graphics cache. 

    for (UInt32 index = 0; 
         (status == ERR_SUCCESS) && (index < (sizeof (g_backgroundItemGraphicAttributesTable) / sizeof (BackgroundItemGraphicAttributes)));
         ++index)
    {   
        // Get the maximum background items on any single screen; use to build the resource graphics cache.

        UInt32  maxBackgroundItemsOnScreen = std::max (static_cast<UInt32> (1), GetMaxBackgroundItemsOnScreen (g_backgroundItemGraphicAttributesTable [index].m_backgroundItemId));

        for (UInt32 cacheCount = 0; 
             (status == ERR_SUCCESS) && (cacheCount < maxBackgroundItemsOnScreen);
             ++cacheCount)
        {            
            // Create a background item graphic.

            BackgroundItemGraphic   backgroundItemGraphic(new BackgroundItemGraphic::element_type);

            // Does the background item graphic support room colouring?

            if (g_backgroundItemGraphicAttributesTable [index].m_supportsRoomColouring)
            {
                // Yes.

                status = backgroundItemGraphic->Create (instanceHandle,
                                                        DRAWING_ELEMENT_BACKGROUND_ITEM,
                                                        g_backgroundItemGraphicAttributesTable [index].m_backgroundItemId,
                                                        Folio::Core::Game::ZxSpectrum::GetBitmapChangeColour (),
                                                        g_backgroundItemGraphicAttributesTable [index].m_maskRqd,
                                                        g_backgroundItemGraphicAttributesTable [index].m_collisionGridCellValue);
            } // Endif.

            else
            {
                // No.

                status = backgroundItemGraphic->Create (instanceHandle,
                                                        DRAWING_ELEMENT_BACKGROUND_ITEM,
                                                        g_backgroundItemGraphicAttributesTable [index].m_backgroundItemId,
                                                        g_backgroundItemGraphicAttributesTable [index].m_maskRqd,
                                                        g_backgroundItemGraphicAttributesTable [index].m_collisionGridCellValue);
            } // Endelse.                       
        
            if (status == ERR_SUCCESS)
            {
                // Store the background item graphic in the resource graphics cache.

                g_resourceGraphicsCache.Add (DRAWING_ELEMENT_BACKGROUND_ITEM, backgroundItemGraphic);
            } // Endif.
       
        } // Endfor.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus QueryBackgroundItemGraphic (Folio::Core::Game::ResourceGraphicsCache::OwnerId   ownerId,    
                                        BACKGROUND_ITEM_ID                                  backgroundItemId, 
                                        BackgroundItemGraphic                               &backgroundItemGraphic)
{
    return (g_resourceGraphicsCache.GainResourceGraphic (ownerId,
                                                         DRAWING_ELEMENT_BACKGROUND_ITEM, 
                                                         backgroundItemId, 
                                                         backgroundItemGraphic));
} // Endproc.


FolioStatus ReleaseBackgroundItemGraphic (const BackgroundItemGraphic &backgroundItemGraphic)
{
    return (g_resourceGraphicsCache.ReleaseResourceGraphic (backgroundItemGraphic));
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
