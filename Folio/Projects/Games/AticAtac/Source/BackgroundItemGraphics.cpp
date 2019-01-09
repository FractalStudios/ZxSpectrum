// "Home-made" includes.
#include    "StdAfx.h"
#include    "DrawingElement.h"
#include    "BackgroundItemGraphics.h"
#include    "ZxSpectrum.h"

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Background item graphic attributes.
struct BackgroundItemGraphicAttributes
{
    BACKGROUND_ITEM_ID                              m_backgroundItemId;         // The identifier of the background item.
    UInt16                                          m_bitmapResourceId;         // The background item's bitmap resource identifier.
    bool                                            m_supportsRoomColouring;    // true if the background item supports room colouring.
    bool                                            m_maskRqd;                  // true if the background item requires a mask.
    Folio::Core::Game::CollisionGrid::CellValue     m_collisionGridCellValue;   // The collision grid cell value of the background item.
}; // Endstruct.

// Background item graphic attributes table.
static  const   BackgroundItemGraphicAttributes g_backgroundItemGraphicAttributesTable [] =
{
//      m_backgroundItemId                              m_bitmapResourceId                      m_supportsRoomColouring m_maskRqd   m_collisionGridCellValue
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,                IDB_BITMAP_CAVE_DOOR_FRAME,             true,                   false,      Folio::Core::Game::CollisionGrid::CELL_VALUE_EXIT,          },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,              IDB_BITMAP_NORMAL_DOOR_FRAME,           false,                  false,      Folio::Core::Game::CollisionGrid::CELL_VALUE_EXIT,          },
    {   BACKGROUND_ITEM_BIG_DOOR_FRAME,                 IDB_BITMAP_BIG_DOOR_FRAME,              false,                  false,      Folio::Core::Game::CollisionGrid::CELL_VALUE_EXIT,          },
    {   BACKGROUND_ITEM_RED_LOCKED_NORMAL_DOOR,         IDB_BITMAP_RED_LOCKED_NORMAL_DOOR,      false,                  false,      Folio::Core::Game::CollisionGrid::CELL_VALUE_EXIT,          },
    {   BACKGROUND_ITEM_GREEN_LOCKED_NORMAL_DOOR,       IDB_BITMAP_GREEN_LOCKED_NORMAL_DOOR,    false,                  false,      Folio::Core::Game::CollisionGrid::CELL_VALUE_EXIT,          },
    {   BACKGROUND_ITEM_CYAN_LOCKED_NORMAL_DOOR,        IDB_BITMAP_CYAN_LOCKED_NORMAL_DOOR,     false,                  false,      Folio::Core::Game::CollisionGrid::CELL_VALUE_EXIT,          },
    {   BACKGROUND_ITEM_YELLOW_LOCKED_NORMAL_DOOR,      IDB_BITMAP_YELLOW_LOCKED_NORMAL_DOOR,   false,                  false,      Folio::Core::Game::CollisionGrid::CELL_VALUE_EXIT,          },
    {   BACKGROUND_ITEM_RED_LOCKED_CAVE_DOOR,           IDB_BITMAP_RED_LOCKED_CAVE_DOOR,        true,                   false,      Folio::Core::Game::CollisionGrid::CELL_VALUE_EXIT,          },
    {   BACKGROUND_ITEM_GREEN_LOCKED_CAVE_DOOR,         IDB_BITMAP_GREEN_LOCKED_CAVE_DOOR,      true,                   false,      Folio::Core::Game::CollisionGrid::CELL_VALUE_EXIT,          },
    {   BACKGROUND_ITEM_CYAN_LOCKED_CAVE_DOOR,          IDB_BITMAP_CYAN_LOCKED_CAVE_DOOR,       true,                   false,      Folio::Core::Game::CollisionGrid::CELL_VALUE_EXIT,          },
    {   BACKGROUND_ITEM_YELLOW_LOCKED_CAVE_DOOR,        IDB_BITMAP_YELLOW_LOCKED_CAVE_DOOR,     true,                   false,      Folio::Core::Game::CollisionGrid::CELL_VALUE_EXIT,          },
    {   BACKGROUND_ITEM_CLOCK,                          IDB_BITMAP_CLOCK,                       true,                   false,      Folio::Core::Game::CollisionGrid::CELL_VALUE_EXIT,          },
    {   BACKGROUND_ITEM_PICTURE,                        IDB_BITMAP_PICTURE,                     true,                   false,      Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,         },
    {   BACKGROUND_ITEM_TABLE,                          IDB_BITMAP_TABLE,                       false,                  false,      Folio::Core::Game::CollisionGrid::CELL_VALUE_SOLID_ITEM,    },
    {   BACKGROUND_ITEM_ANTLER_TROPHY,                  IDB_BITMAP_ANTLER_TROPHY,               false,                  false,      Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,         },
    {   BACKGROUND_ITEM_TROPHY,                         IDB_BITMAP_TROPHY,                      false,                  false,      Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,         },
    {   BACKGROUND_ITEM_BOOKCASE,                       IDB_BITMAP_BOOKCASE,                    true,                   false,      Folio::Core::Game::CollisionGrid::CELL_VALUE_EXIT,          },
    {   BACKGROUND_ITEM_CLOSED_TRAP_DOOR,               IDB_BITMAP_CLOSED_TRAP_DOOR,            false,                  false,      Folio::Core::Game::CollisionGrid::CELL_VALUE_EXIT,          },
    {   BACKGROUND_ITEM_OPEN_TRAP_DOOR,                 IDB_BITMAP_OPEN_TRAP_DOOR,              false,                  false,      Folio::Core::Game::CollisionGrid::CELL_VALUE_EXIT,          },
    {   BACKGROUND_ITEM_BARREL,                         IDB_BITMAP_BARREL,                      false,                  false,      Folio::Core::Game::CollisionGrid::CELL_VALUE_EXIT,          },
    {   BACKGROUND_ITEM_RUG,                            IDB_BITMAP_RUG,                         false,                  false,      Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,         },
    {   BACKGROUND_ITEM_ACG_SHIELD,                     IDB_BITMAP_ACG_SHIELD,                  false,                  false,      Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,         },
    {   BACKGROUND_ITEM_SHIELD,                         IDB_BITMAP_SHIELD,                      true,                   false,      Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,         },
    {   BACKGROUND_ITEM_KNIGHT,                         IDB_BITMAP_KNIGHT,                      false,                  false,      Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,         },
    {   BACKGROUND_ITEM_CLOSED_NORMAL_DOOR,             IDB_BITMAP_CLOSED_NORMAL_DOOR,          false,                  true,       Folio::Core::Game::CollisionGrid::CELL_VALUE_EXIT,          },
    {   BACKGROUND_ITEM_OPEN_NORMAL_DOOR,               IDB_BITMAP_OPEN_NORMAL_DOOR,            false,                  false,      Folio::Core::Game::CollisionGrid::CELL_VALUE_EXIT,          },
    {   BACKGROUND_ITEM_CLOSED_CAVE_DOOR,               IDB_BITMAP_CLOSED_CAVE_DOOR,            true,                   true,       Folio::Core::Game::CollisionGrid::CELL_VALUE_EXIT,          },
    {   BACKGROUND_ITEM_OPEN_CAVE_DOOR,                 IDB_BITMAP_OPEN_CAVE_DOOR,              true,                   false,      Folio::Core::Game::CollisionGrid::CELL_VALUE_EXIT,          },
    {   BACKGROUND_ITEM_ACG_EXIT_DOOR,                  IDB_BITMAP_ACG_EXIT_DOOR,               true,                   false,      Folio::Core::Game::CollisionGrid::CELL_VALUE_EXIT,          },
    {   BACKGROUND_ITEM_PICTURE_2,                      IDB_BITMAP_PICTURE_2,                   false,                  false,      Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,         },
    {   BACKGROUND_ITEM_SKELETON,                       IDB_BITMAP_SKELETON,                    true,                   false,      Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,         },
    {   BACKGROUND_ITEM_BARRELS,                        IDB_BITMAP_BARRELS,                     false,                  false,      Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,         },
};                                                                                                             


FolioStatus BuildBackgroundItemGraphics (FolioHandle                dcHandle, 
                                         FolioHandle                instanceHandle,
                                         BackgroundItemGraphicsMap  &backgroundItemGraphicsMap)
{
    FolioStatus status = ERR_SUCCESS;

    backgroundItemGraphicsMap.clear ();    // Initialise!

    // Build the background item graphics map. 

    for (UInt32 index = 0; 
         (status == ERR_SUCCESS) && (index < (sizeof (g_backgroundItemGraphicAttributesTable) / sizeof (BackgroundItemGraphicAttributes)));
         ++index)
    {              
        // Create a background item graphic.

        BackgroundItemGraphic   backgroundItemGraphic(new BackgroundItemGraphic::element_type);

        // Does the background item graphic support room colouring?

        if (g_backgroundItemGraphicAttributesTable [index].m_supportsRoomColouring)
        {
            // Yes.

            status = backgroundItemGraphic->Create (dcHandle,
                                                    instanceHandle,
                                                    DRAWING_ELEMENT_BACKGROUND_ITEM,
                                                    g_backgroundItemGraphicAttributesTable [index].m_bitmapResourceId,
                                                    ZxSpectrum::GetBitmapChangeColour (),
                                                    g_backgroundItemGraphicAttributesTable [index].m_maskRqd,
                                                    g_backgroundItemGraphicAttributesTable [index].m_collisionGridCellValue);
        } // Endif.

        else
        {
            // No.

            status = backgroundItemGraphic->Create (dcHandle,
                                                    instanceHandle,
                                                    DRAWING_ELEMENT_BACKGROUND_ITEM,
                                                    g_backgroundItemGraphicAttributesTable [index].m_bitmapResourceId,
                                                    g_backgroundItemGraphicAttributesTable [index].m_maskRqd,
                                                    g_backgroundItemGraphicAttributesTable [index].m_collisionGridCellValue);
        } // Endelse.                       
        
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

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
