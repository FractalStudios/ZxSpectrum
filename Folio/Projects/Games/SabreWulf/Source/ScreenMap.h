#pragma once

// STL includes.
#include    <memory>
#include    <vector>

// "Home-made" includes.
#include    <Game.h>
#include    "CollisionGrid.h"
#include    "ObjectSprite.h"
#include    "OrchidSprite.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Screen map.
class ScreenMap
{
public:
    static  const   UInt32  INITIAL_SCREEN_INDEX = 168; // Index to the initial screen.

    ScreenMap (const SpriteGraphicsMapPtr &spriteGraphicsMap);
    ~ScreenMap ();

    void    ScatterObjects ();

    UInt32  GetTotalNumScreens () const;
    UInt32  GetCurrentScreenIndex () const;
    UInt32  GetNewScreenIndex (CollisionGrid::ScreenExit::ORIENTATION orientation);

    // The screen number.
    typedef UInt8   ScreenNumber;

    ScreenNumber    GetCurrentScreenNumber () const;
    ScreenNumber    GetScreenNumber (UInt32 screenIndex) const;

    bool    IsScreenOrchidSprite (OrchidSpritePtr &orchidSprite) const;

    FolioStatus QueryScreenObjectSprites (FolioHandle       dcHandle,
                                          ObjectSpritesList &objectSpritesList) const;

private:           
    static  const   UInt32  MAX_SCREEN_MAP_ROWS     = 16;
    static  const   UInt32  MAX_SCREEN_MAP_COLUMNS  = 16;

    static  const   UInt32  MAX_SCREEN_OBJECT_SPRITES = 2;  // Maximum number of screen object sprites.

    const SpriteGraphicsMapPtr &m_spriteGraphicsMap;    // The sprite graphics map.

    // The map.
    typedef std::vector<ScreenNumber>   Map;

    Map m_map;  // The screen map.

    static  const   ScreenNumber    m_screenMapLayout [];   // Screen map layout.

    UInt32  m_currentScreenIndex;   // The current screen index into the screen map.

    // Screen position.
    typedef Gdiplus::Point  ScreenPosition;

    // Screen positions list.
    typedef std::vector<ScreenPosition> ScreenPositionsList;

    static  const   ScreenPositionsList m_orchidScreenPositions;    // Orchid screen positions.

    static  const   UInt32  MAX_OBJECT_POSITIONS_PER_SCREEN = 4;        // Maximum object screen positions per screen.
    static  const   ScreenPositionsList     m_objectScreenPositions;    // Object screen positions.
    
    typedef std::vector<UInt32>   AmuletPieceScreenLocationsList;   // Amulet piece screen locations list.

    static  const   UInt32  MAX_AMULET_PIECES = 4;                                  // Maximum amulet pieces.
    static  const   AmuletPieceScreenLocationsList   m_amuletPieceScreenLocations;  // Amulet piece screen locations.
    
    static  UInt32  m_amuletPieceScreenLocationsIndex;   // The amulet piece screen locations index.

    static  bool    IsAmuletPieceOnScreen (UInt32               screenIndex,
                                           OBJECT_SPRITE_ID     &amuletPieceId);

    // Private copy constructor to prevent copying.
    ScreenMap (const ScreenMap& rhs);

    // Private assignment operator to prevent copying.
    ScreenMap& operator= (const ScreenMap& rhs);
}; // Endclass.

// Screen map pointer.
typedef std::shared_ptr<ScreenMap>  ScreenMapPtr;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
