#pragma once

// STL includes.
#include    <map>

// "Home-made" includes.
#include    <Game.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Background item identifier enumeration.
enum BACKGROUND_ITEM_ID
{
    BACKGROUND_ITEM_UNDEFINED = Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_ID_UNDEFINED,
    BACKGROUND_ITEM_CAVE_DOOR_FRAME = 0,
    BACKGROUND_ITEM_NORMAL_DOOR_FRAME,
    BACKGROUND_ITEM_BIG_DOOR_FRAME,
    BACKGROUND_ITEM_RED_LOCKED_NORMAL_DOOR,
    BACKGROUND_ITEM_GREEN_LOCKED_NORMAL_DOOR,
    BACKGROUND_ITEM_CYAN_LOCKED_NORMAL_DOOR,
    BACKGROUND_ITEM_YELLOW_LOCKED_NORMAL_DOOR,
    BACKGROUND_ITEM_RED_LOCKED_CAVE_DOOR,
    BACKGROUND_ITEM_GREEN_LOCKED_CAVE_DOOR,
    BACKGROUND_ITEM_CYAN_LOCKED_CAVE_DOOR,
    BACKGROUND_ITEM_YELLOW_LOCKED_CAVE_DOOR,
    BACKGROUND_ITEM_CLOCK,
    BACKGROUND_ITEM_PICTURE,
    BACKGROUND_ITEM_TABLE,
    BACKGROUND_ITEM_ANTLER_TROPHY,
    BACKGROUND_ITEM_TROPHY,
    BACKGROUND_ITEM_BOOKCASE,
    BACKGROUND_ITEM_CLOSED_TRAP_DOOR,
    BACKGROUND_ITEM_OPEN_TRAP_DOOR,
    BACKGROUND_ITEM_BARREL,
    BACKGROUND_ITEM_RUG,
    BACKGROUND_ITEM_ACG_SHIELD,
    BACKGROUND_ITEM_SHIELD,
    BACKGROUND_ITEM_KNIGHT,
    BACKGROUND_ITEM_CLOSED_NORMAL_DOOR,
    BACKGROUND_ITEM_OPEN_NORMAL_DOOR,
    BACKGROUND_ITEM_CLOSED_CAVE_DOOR,
    BACKGROUND_ITEM_OPEN_CAVE_DOOR,
    BACKGROUND_ITEM_ACG_EXIT_DOOR,
    BACKGROUND_ITEM_PICTURE_2,
    BACKGROUND_ITEM_SKELETON,
    BACKGROUND_ITEM_BARRELS,
}; // Endenum.

// Background item graphic.
typedef Folio::Core::Game::ResourceGraphicPtr   BackgroundItemGraphic;

// Background item graphics map.
typedef std::map<BACKGROUND_ITEM_ID, BackgroundItemGraphic> BackgroundItemGraphicsMap;
             

// Routines.

extern  FolioStatus BuildBackgroundItemGraphics (FolioHandle                dcHandle, 
                                                 FolioHandle                instanceHandle,
                                                 BackgroundItemGraphicsMap  &backgroundItemGraphicsMap);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
