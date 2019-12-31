// "Home-made" includes.
#include    "StdAfx.h"
#include    "DrawingElement.h"
#include    "Globals.h"
#include    "RoomGraphics.h"

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
    Int32       m_floorXLeft;       // The X left of the room's floor.
    Int32       m_floorYTop;        // The Y top of the room's floor.
    Int32       m_floorWidth;       // The width of the room's floor.
    Int32       m_floorHeight;      // The height of the room's floor.
}; // Endstruct.

// Room graphic attributes table.
static  const   RoomGraphicAttributes   g_roomGraphicAttributesTable [] =
{
//      m_roomId    m_floorXLeft    m_floorYTop     m_floorWidth    m_floorHeight
    {   ROOM_0,     32,             32,             128,            128,    },
    {   ROOM_1,     48,             48,              96,             96,    },
    {   ROOM_2,     32,             32,             128,            128,    },
    {   ROOM_3,     32,             64,             128,             64,    },
    {   ROOM_4,     64,             32,              64,            128,    },
    {   ROOM_5,     72,             41,              48,            110,    },
    {   ROOM_6,     72,             41,              48,            110,    },
    {   ROOM_7,     42,             72,             110,             48,    },
    {   ROOM_8,     42,             72,             110,             48,    },
    {   ROOM_9,     40,             64,             112,             64,    },
    {   ROOM_10,    64,             40,              64,            112,    },
    {   ROOM_11,     0,              0,               0,              0,    },
};


RoomGraphic::RoomGraphic ()
{
} // Endproc.


RoomGraphic::~RoomGraphic ()
{
} // Endproc.


FolioStatus RoomGraphic::Create (FolioHandle    instanceHandle,
                                 UInt16         bitmapResourceId,
                                 Int32          floorXLeft,
                                 Int32          floorYTop,
                                 Int32          floorWidth,
                                 Int32          floorHeight)
{
    FolioStatus status = ResourceGraphic::Create (instanceHandle, 
                                                  DRAWING_ELEMENT_ROOM, 
                                                  bitmapResourceId,
                                                  Folio::Core::Game::ZxSpectrum::GetBitmapChangeColour ());
    
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
                                               Folio::Core::Game::ZxSpectrum::COLOUR    roomColour,
                                               Folio::Core::Game::DrawingElementsList   &drawingElementsList)
{
    return (Folio::Core::Game::ResourceGraphic::QueryDrawingElements (dcHandle, 
                                                                      0,    // Screen X left.
                                                                      0,    // Screen Y top.
                                                                      Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE,     
                                                                      Folio::Core::Game::ZxSpectrum::MapInkColour (roomColour),
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


CollisionGrid   RoomGraphic::GetCollisionGrid () const
{
    return (m_collisionGrid);
} // Endproc.


FolioStatus CreateRoomGraphics (FolioHandle instanceHandle)
{
    FolioStatus status = ERR_SUCCESS;

    // Add the room graphics into the resource graphics cache. 

    for (UInt32 index = 0; 
         (status == ERR_SUCCESS) && (index < (sizeof (g_roomGraphicAttributesTable) / sizeof (RoomGraphicAttributes)));
         ++index)
    {              
        // Create a room graphic.

        RoomGraphicPtr  roomGraphic(new RoomGraphicPtr::element_type);

        status = roomGraphic->Create (instanceHandle,
                                      g_roomGraphicAttributesTable [index].m_roomId,
                                      g_roomGraphicAttributesTable [index].m_floorXLeft,
                                      g_roomGraphicAttributesTable [index].m_floorYTop,
                                      g_roomGraphicAttributesTable [index].m_floorWidth,
                                      g_roomGraphicAttributesTable [index].m_floorHeight);
        
        if (status == ERR_SUCCESS)
        {
            // Store the room graphic in the resource graphics cache.

            g_resourceGraphicsCache.Add (DRAWING_ELEMENT_ROOM, roomGraphic);
        } // Endif.
       
    } // Endfor.

    return (status);
} // Endproc.


FolioStatus QueryRoomGraphic (Folio::Core::Game::ResourceGraphicsCache::OwnerId ownerId,
                              ROOM_ID                                           roomId, 
                              RoomGraphicPtr                                    &roomGraphic)
{
    Folio::Core::Game::ResourceGraphicPtr   resourceGraphic;

    FolioStatus status = g_resourceGraphicsCache.GainResourceGraphic (ownerId,
                                                                      DRAWING_ELEMENT_ROOM, 
                                                                      roomId, 
                                                                      resourceGraphic);

    if (status == ERR_SUCCESS)
    {
        roomGraphic = std::static_pointer_cast<RoomGraphic> (resourceGraphic);
    } // Endif.

    return (status);
} // Endproc.


FolioStatus ReleaseRoomGraphic (const RoomGraphic &roomGraphic)
{
    Folio::Core::Game::ResourceGraphicPtr   resourceGraphic = std::make_shared<Folio::Core::Game::ResourceGraphic> (roomGraphic);

    return (g_resourceGraphicsCache.ReleaseResourceGraphic (resourceGraphic));
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
