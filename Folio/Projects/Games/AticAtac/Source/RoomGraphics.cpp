// "Home-made" includes.
#include    "StdAfx.h"
#include    "DrawingElement.h"
#include    "RoomGraphics.h"
#include    "ZxSpectrum.h"

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Room graphic attributes.
struct RoomGraphicAttributes
{
    ROOM_ID     m_roomId;           // The identifier of the room.
    UInt16      m_bitmapResourceId; // The room's bitmap resource identifier.
    Int32       m_floorXLeft;       // The X left of the room's floor.
    Int32       m_floorYTop;        // The Y top of the room's floor.
    Int32       m_floorWidth;       // The width of the room's floor.
    Int32       m_floorHeight;      // The height of the room's floor.
}; // Endstruct.

// Room graphic attributes table.
static  const   RoomGraphicAttributes   g_roomGraphicAttributesTable [] =
{
//      m_roomId    m_bitmapResourceId      m_floorXLeft    m_floorYTop     m_floorWidth    m_floorHeight
    {   ROOM_0,     IDB_BITMAP_ROOM_0,      32,             32,             128,            128,    },
    {   ROOM_1,     IDB_BITMAP_ROOM_1,      48,             48,              96,             96,    },
    {   ROOM_2,     IDB_BITMAP_ROOM_2,      32,             32,             128,            128,    },
    {   ROOM_3,     IDB_BITMAP_ROOM_3,      32,             64,             128,             64,    },
    {   ROOM_4,     IDB_BITMAP_ROOM_4,      64,             32,              64,            128,    },
    {   ROOM_5,     IDB_BITMAP_ROOM_5,      72,             41,              48,            110,    },
    {   ROOM_6,     IDB_BITMAP_ROOM_6,      72,             41,              48,            110,    },
    {   ROOM_7,     IDB_BITMAP_ROOM_7,      42,             72,             110,             48,    },
    {   ROOM_8,     IDB_BITMAP_ROOM_8,      42,             72,             110,             48,    },
    {   ROOM_9,     IDB_BITMAP_ROOM_9,      40,             64,             112,             64,    },
    {   ROOM_10,    IDB_BITMAP_ROOM_10,     64,             40,              64,            112,    },
    {   ROOM_11,    IDB_BITMAP_ROOM_11,      0,              0,               0,              0,    },
};


RoomGraphic::RoomGraphic ()
{
} // Endproc.


RoomGraphic::~RoomGraphic ()
{
} // Endproc.


FolioStatus RoomGraphic::Create (FolioHandle    dcHandle,
                                 FolioHandle    instanceHandle,
                                 UInt16         bitmapResourceId,
                                 Int32          floorXLeft,
                                 Int32          floorYTop,
                                 Int32          floorWidth,
                                 Int32          floorHeight)
{
    FolioStatus status = ResourceGraphic::Create (dcHandle, 
                                                  instanceHandle, 
                                                  DRAWING_ELEMENT_ROOM, 
                                                  bitmapResourceId,
                                                  ZxSpectrum::GetBitmapChangeColour ());
    
    if (status == ERR_SUCCESS)
    {
        // Note the room's attributes.

        m_floorRect.X       = floorXLeft;
        m_floorRect.Y       = floorYTop;
        m_floorRect.Width   = floorWidth;
        m_floorRect.Height  = floorHeight;

        if (m_floorRect.Width && m_floorRect.Height)
        {
            // Create the room's collision grid.

            status = m_collisionGrid.Create (m_floorRect);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus RoomGraphic::QueryDrawingElements (FolioHandle                              dcHandle,
                                               ZxSpectrum::COLOUR                       roomColour,
                                               Folio::Core::Game::DrawingElementsList   &drawingElementsList)
{
    return (Folio::Core::Game::ResourceGraphic::QueryDrawingElements (dcHandle, 
                                                                      0,    // Screen X left.
                                                                      0,    // Screen Y top.
                                                                      ZxSpectrum::DEFAULT_SCREEN_SCALE,     
                                                                      ZxSpectrum::MapInkColour (roomColour),
                                                                      Folio::Core::Game::ResourceGraphic::NO_DRAWING_FLAGS, 
                                                                      const_cast<RoomGraphic *> (this), // Drawing element user data.
                                                                      drawingElementsList));
} // Endproc.


Gdiplus::Rect   RoomGraphic::GetFloorRect () const
{
    return (m_floorRect);
} // Endproc.


Int32   RoomGraphic::GetFloorXLeft () const
{
    return (m_floorRect.X);
} // Endproc.


Int32   RoomGraphic::GetFloorYTop () const
{
    return (m_floorRect.Y);
} // Endproc.


Int32   RoomGraphic::GetFloorWidth () const
{
    return (m_floorRect.Width);
} // Endproc.


Int32   RoomGraphic::GetFloorHeight () const
{
    return (m_floorRect.Height);
} // Endproc.


Folio::Core::Game::CollisionGrid    RoomGraphic::GetCollisionGrid () const
{
    return (m_collisionGrid);
} // Endproc.


FolioStatus BuildRoomGraphics (FolioHandle      dcHandle, 
                               FolioHandle      instanceHandle,
                               RoomGraphicsMap  &roomGraphicsMap)
{
    FolioStatus status = ERR_SUCCESS;

    roomGraphicsMap.clear ();    // Initialise!

    // Build the room graphics map. 

    for (UInt32 index = 0; 
         (status == ERR_SUCCESS) && (index < (sizeof (g_roomGraphicAttributesTable) / sizeof (RoomGraphicAttributes)));
         ++index)
    {              
        // Create a room graphic.

        RoomGraphicPtr  roomGraphic(new RoomGraphicPtr::element_type);

        status = roomGraphic->Create (dcHandle,
                                      instanceHandle,
                                      g_roomGraphicAttributesTable [index].m_bitmapResourceId,
                                      g_roomGraphicAttributesTable [index].m_floorXLeft,
                                      g_roomGraphicAttributesTable [index].m_floorYTop,
                                      g_roomGraphicAttributesTable [index].m_floorWidth,
                                      g_roomGraphicAttributesTable [index].m_floorHeight);
        
        if (status == ERR_SUCCESS)
        {
            // Store the room graphic in the room graphics map.

            roomGraphicsMap.insert (RoomGraphicsMap::value_type(g_roomGraphicAttributesTable [index].m_roomId, 
                                                                roomGraphic));
        } // Endif.
       
    } // Endfor.

    if (status != ERR_SUCCESS)
    {
        roomGraphicsMap.clear ();
    } // Endif.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
