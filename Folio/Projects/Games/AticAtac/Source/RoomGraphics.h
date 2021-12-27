#pragma once

// STL includes.
#include    <memory>

// "Home-made" includes.
#include    <Game.h>
#include    "CollisionGrid.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace AticAtac
{

static  const   Int32   MAX_ROOM_WIDTH  = 192;  // Maximum width of a room.
static  const   Int32   MAX_ROOM_HEIGHT = 192;  // Maximum height of a room.

// Room identifier enumeration.
enum ROOM_ID
{
    ROOM_UNDEFINED = Folio::Core::Util::UNDEFINED_BITMAP_RESOURCE_ID,
    ROOM_0  = IDB_BITMAP_ROOM_0,
    ROOM_1  = IDB_BITMAP_ROOM_1,
    ROOM_2  = IDB_BITMAP_ROOM_2,
    ROOM_3  = IDB_BITMAP_ROOM_3,
    ROOM_4  = IDB_BITMAP_ROOM_4,
    ROOM_5  = IDB_BITMAP_ROOM_5,
    ROOM_6  = IDB_BITMAP_ROOM_6,
    ROOM_7  = IDB_BITMAP_ROOM_7,
    ROOM_8  = IDB_BITMAP_ROOM_8,
    ROOM_9  = IDB_BITMAP_ROOM_9,
    ROOM_10 = IDB_BITMAP_ROOM_10,
    ROOM_11 = IDB_BITMAP_ROOM_11,
}; // Endenum.


// Room graphic.
class RoomGraphic : public Folio::Core::Game::ResourceGraphic
{
public:
    RoomGraphic ();
    ~RoomGraphic ();

    FolioStatus Create (FolioHandle instanceHandle,
                        UInt16      bitmapResourceId,
                        Int32       floorXLeft,
                        Int32       floorYTop,
                        Int32       floorWidth,
                        Int32       floorHeight);
    FolioStatus QueryDrawingElements (FolioHandle                               dcHandle,
                                      Folio::Core::Game::ZxSpectrum::COLOUR     roomColour,
                                      Folio::Core::Game::DrawingElementsList&   drawingElementsList);

    Gdiplus::Rect   GetFloorRect () const;
    Int32           GetFloorXLeft () const;
    Int32           GetFloorYTop () const;
    Int32           GetFloorWidth () const;
    Int32           GetFloorHeight () const;

    CollisionGrid   GetCollisionGrid () const;

private:
    Gdiplus::Rect   m_floorRect;    // The rect of the room's floor.

    CollisionGrid   m_collisionGrid;    // The room's collision grid.
}; // Endclass.

// Room graphics pointer.
typedef std::shared_ptr<RoomGraphic>    RoomGraphicPtr;


// Routines.

extern  FolioStatus CreateRoomGraphics (FolioHandle instanceHandle);
extern  FolioStatus QueryRoomGraphic (const Folio::Core::Game::ResourceGraphicsCache::OwnerId&  ownerId,
                                      ROOM_ID                                                   roomId, 
                                      RoomGraphicPtr&                                           roomGraphic);
extern  FolioStatus ReleaseRoomGraphic (const RoomGraphic& roomGraphic);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
