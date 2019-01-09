#pragma once

// STL includes.
#include    <map>
#include    <memory>

// "Home-made" includes.
#include    <Game.h>
#include    "ZxSpectrum.h"

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
    ROOM_UNDEFINED = Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_ID_UNDEFINED,
    ROOM_0 = 0,
    ROOM_1,
    ROOM_2,
    ROOM_3,
    ROOM_4,
    ROOM_5,
    ROOM_6,
    ROOM_7,
    ROOM_8,
    ROOM_9,
    ROOM_10,
    ROOM_11,
}; // Endenum.


// Room graphic.
class RoomGraphic : public Folio::Core::Game::ResourceGraphic
{
public:
    RoomGraphic ();
    ~RoomGraphic ();

    FolioStatus Create (FolioHandle dcHandle,
                        FolioHandle instanceHandle,
                        UInt16      bitmapResourceId,
                        Int32       floorXLeft,
                        Int32       floorYTop,
                        Int32       floorWidth,
                        Int32       floorHeight);
    FolioStatus QueryDrawingElements (FolioHandle                               dcHandle,
                                      ZxSpectrum::COLOUR                        roomColour,
                                      Folio::Core::Game::DrawingElementsList    &drawingElementsList);

    Gdiplus::Rect   GetFloorRect () const;
    Int32           GetFloorXLeft () const;
    Int32           GetFloorYTop () const;
    Int32           GetFloorWidth () const;
    Int32           GetFloorHeight () const;

    Folio::Core::Game::CollisionGrid GetCollisionGrid () const;

private:
    Gdiplus::Rect   m_floorRect;    // The rect of the room's floor.

    Folio::Core::Game::CollisionGrid    m_collisionGrid;    // The room's collision grid.
}; // Endclass.

// Room graphics pointer.
typedef std::shared_ptr<RoomGraphic>    RoomGraphicPtr;

// Room graphics map.
typedef std::map<ROOM_ID, RoomGraphicPtr>  RoomGraphicsMap;
             

// Routines.

extern  FolioStatus BuildRoomGraphics (FolioHandle      dcHandle, 
                                       FolioHandle      instanceHandle,
                                       RoomGraphicsMap  &roomGraphicsMap);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
