#pragma once

// STL includes.
#include    <memory>
#include    <vector>

// "Home-made" includes.
#include    <Game.h>
#include    "CollisionGrid.h"
#include    "ObjectSprite.h"

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
    static  const   UInt32  INITIAL_SCREEN_INDEX    = 168;                  // Index to the initial screen.
    static  const   UInt32  UNDEFINED_SCREEN_INDEX  = FOLIO_INVALID_INDEX;  // Undefined screen index.

    ScreenMap ();
    ~ScreenMap ();

    void    ScatterObjects ();

    UInt32  GetCurrentScreenMapIndex () const;
    UInt32  MoveToNewScreen (CollisionGrid::ScreenExit::ORIENTATION orientation);

    // The screen number (0x00-0x2f).
    typedef UInt8   ScreenNumber;

    ScreenNumber    GetCurrentScreenNumber () const;
    ScreenNumber    GetScreenNumber (UInt32 screenMapIndex) const;

    bool    IsScreenOrchidSprite () const;
    Int32   GetScreenOrchidSpriteScreenXLeft () const;
    Int32   GetScreenOrchidSpriteScreenYBottom () const;

    FolioStatus QueryScreenObjectSprites (FolioHandle       dcHandle,
                                          ObjectSpritesList &objectSpritesList) const;

    static  UInt32  GetTotalNumScreens ();

private:
    // Screen map size.
    static  const   UInt32  MAX_SCREEN_MAP_ROWS     = 16;
    static  const   UInt32  MAX_SCREEN_MAP_COLUMNS  = 16;

    static  const   UInt32  MAX_SCREEN_OBJECT_SPRITES = 2;  // Maximum number of screen object sprites.

    // Screen numbers list.
    typedef std::vector<ScreenNumber>   ScreenNumbersList;
    
    static  const   ScreenNumbersList   m_screenMap;    // Screen map.
    UInt32  m_currentScreenMapIndex;    // The current index into the screen map.

    // Screen position.
    typedef Gdiplus::Point  ScreenPosition;

    // Screen positions list.
    typedef std::vector<ScreenPosition> ScreenPositionsList;

    static  const   ScreenPositionsList m_orchidScreenPositions;    // Orchid screen positions.

    static  const   UInt32  MAX_OBJECT_POSITIONS_PER_SCREEN = 4;        // Maximum number of object screen positions per screen.
    static  const   ScreenPositionsList     m_objectScreenPositions;    // Object screen positions.
    
    // Screen index list.
    typedef std::vector<UInt32> ScreenIndexList;
    
    static  const   UInt32  MAX_AMULET_PIECES = 4;                  // Maximum number of amulet pieces.
    static  const   ScreenIndexList m_amuletPieceScreenIndexList;   // Amulet piece screen index list.
    static  UInt32  m_amuletPieceScreenIndexListIndex;  // The index into the amulet piece screen index list.

    static  bool    IsAmuletPieceOnScreen (UInt32           screenMapIndex,
                                           OBJECT_SPRITE_ID &amuletPieceId);

    // Private copy constructor to prevent copying.
    ScreenMap (const ScreenMap& rhs);

    // Private assignment operator to prevent copying.
    ScreenMap& operator= (const ScreenMap& rhs);
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
