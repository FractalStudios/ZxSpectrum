// "Home-made" includes.
#include    "StdAfx.h"
#include    "DrawingElement.h"
#include    "SpriteGraphics.h"
#include    "ZxSpectrum.h"

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Sprite graphic attributes.
struct SpriteGraphicAttributes
{
    SPRITE_ID                                   m_spriteId;                 // The identifier of the sprite.
    UInt16                                      m_bitmapResourceId;         // The sprite's bitmap resource identifier.
    DRAWING_ELEMENT_ID                          m_drawingElementId;         // The drawing element identifier of the sprite.
    ZxSpectrum::COLOUR                          m_colour;                   // The colour of the sprite.
    Folio::Core::Game::CollisionGrid::CellValue m_collisionGridCellValue;   // The collision grid cell value of the sprite.
 }; // Endstruct.

// Sprite graphic attributes table.
static  const   SpriteGraphicAttributes   g_spriteGraphicAttributesTable [] =
{
//      m_spriteId                      m_bitmapResourceId                  m_drawingElementId                  m_colour                                    m_collisionGridCellValue
    {   SPRITE_LEAF,                    IDB_BITMAP_LEAF,                    DRAWING_ELEMENT_STATIC_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::RED,       Folio::Core::Game::CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM,  },
    {   SPRITE_KEY,                     IDB_BITMAP_KEY,                     DRAWING_ELEMENT_STATIC_SPRITE,      ZxSpectrum::UNDEFINED,                      Folio::Core::Game::CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM,  },
    {   SPRITE_BOTTLE,                  IDB_BITMAP_BOTTLE,                  DRAWING_ELEMENT_STATIC_SPRITE,      ZxSpectrum::UNDEFINED,                      Folio::Core::Game::CollisionGrid::CELL_VALUE_HEALTH_ITEM,       },
    {   SPRITE_MEDICINE_BOTTLE,         IDB_BITMAP_MEDICINE_BOTTLE,         DRAWING_ELEMENT_STATIC_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     Folio::Core::Game::CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM,  },
    {   SPRITE_BROKEN,                  IDB_BITMAP_BROKEN,                  DRAWING_ELEMENT_STATIC_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    Folio::Core::Game::CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM,  },
    {   SPRITE_ROPE,                    IDB_BITMAP_ROPE,                    DRAWING_ELEMENT_STATIC_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      Folio::Core::Game::CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM,  },
    {   SPRITE_ARM,                     IDB_BITMAP_ARM,                     DRAWING_ELEMENT_STATIC_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     Folio::Core::Game::CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM,  },
    {   SPRITE_BOWL,                    IDB_BITMAP_BOWL,                    DRAWING_ELEMENT_STATIC_SPRITE,      ZxSpectrum::UNDEFINED,                      Folio::Core::Game::CollisionGrid::CELL_VALUE_HEALTH_ITEM,       },
    {   SPRITE_APPLE,                   IDB_BITMAP_APPLE,                   DRAWING_ELEMENT_STATIC_SPRITE,      ZxSpectrum::UNDEFINED,                      Folio::Core::Game::CollisionGrid::CELL_VALUE_HEALTH_ITEM,       },
    {   SPRITE_CANDY_BAR,               IDB_BITMAP_CANDY_BAR,               DRAWING_ELEMENT_STATIC_SPRITE,      ZxSpectrum::UNDEFINED,                      Folio::Core::Game::CollisionGrid::CELL_VALUE_HEALTH_ITEM,       },
    {   SPRITE_HAM,                     IDB_BITMAP_HAM,                     DRAWING_ELEMENT_STATIC_SPRITE,      ZxSpectrum::UNDEFINED,                      Folio::Core::Game::CollisionGrid::CELL_VALUE_HEALTH_ITEM,       },
    {   SPRITE_LOLLIPOP,                IDB_BITMAP_LOLLIPOP,                DRAWING_ELEMENT_STATIC_SPRITE,      ZxSpectrum::UNDEFINED,                      Folio::Core::Game::CollisionGrid::CELL_VALUE_HEALTH_ITEM,       },
    {   SPRITE_MONEY_BAG,               IDB_BITMAP_MONEY_BAG,               DRAWING_ELEMENT_STATIC_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::RED,       Folio::Core::Game::CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM,  },
    {   SPRITE_GOBSTOPPER,              IDB_BITMAP_GOBSTOPPER,              DRAWING_ELEMENT_STATIC_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      Folio::Core::Game::CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM,  },
    {   SPRITE_AMULET,                  IDB_BITMAP_AMULET,                  DRAWING_ELEMENT_STATIC_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   Folio::Core::Game::CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM,  },
    {   SPRITE_CAN,                     IDB_BITMAP_CAN,                     DRAWING_ELEMENT_STATIC_SPRITE,      ZxSpectrum::UNDEFINED,                      Folio::Core::Game::CollisionGrid::CELL_VALUE_HEALTH_ITEM,       },
    {   SPRITE_ICE_CREAM_CONE,          IDB_BITMAP_ICE_CREAM_CONE,          DRAWING_ELEMENT_STATIC_SPRITE,      ZxSpectrum::UNDEFINED,                      Folio::Core::Game::CollisionGrid::CELL_VALUE_HEALTH_ITEM,       },
    {   SPRITE_CRUCIFIX,                IDB_BITMAP_CRUCIFIX,                DRAWING_ELEMENT_STATIC_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    Folio::Core::Game::CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM,  },
    {   SPRITE_SKULL,                   IDB_BITMAP_SKULL,                   DRAWING_ELEMENT_STATIC_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM,  },
    {   SPRITE_SPANNER,                 IDB_BITMAP_SPANNER,                 DRAWING_ELEMENT_STATIC_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      Folio::Core::Game::CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM,  },
    {   SPRITE_ACG_KEY_LEFT,            IDB_BITMAP_ACG_KEY_LEFT,            DRAWING_ELEMENT_STATIC_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    Folio::Core::Game::CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM,  },
    {   SPRITE_ACG_KEY_MIDDLE,          IDB_BITMAP_ACG_KEY_MIDDLE,          DRAWING_ELEMENT_STATIC_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    Folio::Core::Game::CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM,  },
    {   SPRITE_ACG_KEY_RIGHT,           IDB_BITMAP_ACG_KEY_RIGHT,           DRAWING_ELEMENT_STATIC_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    Folio::Core::Game::CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM,  },
    {   SPRITE_MUSHROOM,                IDB_BITMAP_MUSHROOM,                DRAWING_ELEMENT_STATIC_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::RED,       Folio::Core::Game::CollisionGrid::CELL_VALUE_HARMFUL_ITEM,      },
    {   SPRITE_GRAVESTONE,              IDB_BITMAP_GRAVESTONE,              DRAWING_ELEMENT_STATIC_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },

    {   SPRITE_KNIGHT_WALKING_UP_1,     IDB_BITMAP_KNIGHT_WALKING_UP_1,     DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_KNIGHT_UP,               IDB_BITMAP_KNIGHT_UP,               DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_KNIGHT_WALKING_UP_2,     IDB_BITMAP_KNIGHT_WALKING_UP_2,     DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_KNIGHT_WALKING_DOWN_1,   IDB_BITMAP_KNIGHT_WALKING_DOWN_1,   DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_KNIGHT_DOWN,             IDB_BITMAP_KNIGHT_DOWN,             DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_KNIGHT_WALKING_DOWN_2,   IDB_BITMAP_KNIGHT_WALKING_DOWN_2,   DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_KNIGHT_WALKING_LEFT_1,   IDB_BITMAP_KNIGHT_WALKING_LEFT_1,   DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_KNIGHT_LEFT,             IDB_BITMAP_KNIGHT_LEFT,             DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_KNIGHT_WALKING_LEFT_2,   IDB_BITMAP_KNIGHT_WALKING_LEFT_2,   DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_KNIGHT_WALKING_RIGHT_1,  IDB_BITMAP_KNIGHT_WALKING_RIGHT_1,  DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_KNIGHT_RIGHT,            IDB_BITMAP_KNIGHT_RIGHT,            DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_KNIGHT_WALKING_RIGHT_2,  IDB_BITMAP_KNIGHT_WALKING_RIGHT_2,  DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },

    {   SPRITE_WIZARD_WALKING_UP_1,     IDB_BITMAP_WIZARD_WALKING_UP_1,     DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_WIZARD_UP,               IDB_BITMAP_WIZARD_UP,               DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_WIZARD_WALKING_UP_2,     IDB_BITMAP_WIZARD_WALKING_UP_2,     DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_WIZARD_WALKING_DOWN_1,   IDB_BITMAP_WIZARD_WALKING_DOWN_1,   DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_WIZARD_DOWN,             IDB_BITMAP_WIZARD_DOWN,             DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_WIZARD_WALKING_DOWN_2,   IDB_BITMAP_WIZARD_WALKING_DOWN_2,   DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_WIZARD_WALKING_LEFT_1,   IDB_BITMAP_WIZARD_WALKING_LEFT_1,   DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_WIZARD_LEFT,             IDB_BITMAP_WIZARD_LEFT,             DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_WIZARD_WALKING_LEFT_2,   IDB_BITMAP_WIZARD_WALKING_LEFT_2,   DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_WIZARD_WALKING_RIGHT_1,  IDB_BITMAP_WIZARD_WALKING_RIGHT_1,  DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_WIZARD_RIGHT,            IDB_BITMAP_WIZARD_RIGHT,            DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_WIZARD_WALKING_RIGHT_2,  IDB_BITMAP_WIZARD_WALKING_RIGHT_2,  DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },

    {   SPRITE_SERF_WALKING_UP_1,       IDB_BITMAP_SERF_WALKING_UP_1,       DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_SERF_UP,                 IDB_BITMAP_SERF_UP,                 DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_SERF_WALKING_UP_2,       IDB_BITMAP_SERF_WALKING_UP_2,       DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_SERF_WALKING_DOWN_1,     IDB_BITMAP_SERF_WALKING_DOWN_1,     DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_SERF_DOWN,               IDB_BITMAP_SERF_DOWN,               DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_SERF_WALKING_DOWN_2,     IDB_BITMAP_SERF_WALKING_DOWN_2,     DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_SERF_WALKING_LEFT_1,     IDB_BITMAP_SERF_WALKING_LEFT_1,     DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_SERF_LEFT,               IDB_BITMAP_SERF_LEFT,               DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_SERF_WALKING_LEFT_2,     IDB_BITMAP_SERF_WALKING_LEFT_2,     DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_SERF_WALKING_RIGHT_1,    IDB_BITMAP_SERF_WALKING_RIGHT_1,    DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_SERF_RIGHT,              IDB_BITMAP_SERF_RIGHT,              DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_SERF_WALKING_RIGHT_2,    IDB_BITMAP_SERF_WALKING_RIGHT_2,    DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },

    {   SPRITE_NASTY_ALIVE_1,           IDB_BITMAP_NASTY_ALIVE_1,           DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_NASTY_ALIVE_2,           IDB_BITMAP_NASTY_ALIVE_2,           DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_NASTY_ALIVE_3,           IDB_BITMAP_NASTY_ALIVE_3,           DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_NASTY_ALIVE_4,           IDB_BITMAP_NASTY_ALIVE_4,           DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    
    {   SPRITE_NASTY_DEAD_1,            IDB_BITMAP_NASTY_DEAD_1,            DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_NASTY_DEAD_2,            IDB_BITMAP_NASTY_DEAD_2,            DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_NASTY_DEAD_3,            IDB_BITMAP_NASTY_DEAD_3,            DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    {   SPRITE_NASTY_DEAD_4,            IDB_BITMAP_NASTY_DEAD_4,            DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     Folio::Core::Game::CollisionGrid::CELL_VALUE_EMPTY,             },
    
    {   SPRITE_PUMPKIN_1,               IDB_BITMAP_PUMPKIN_1,               DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    Folio::Core::Game::CollisionGrid::CELL_VALUE_NASTY_SPRITE,      },
    {   SPRITE_PUMPKIN_2,               IDB_BITMAP_PUMPKIN_2,               DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    Folio::Core::Game::CollisionGrid::CELL_VALUE_NASTY_SPRITE,      },
    
    {   SPRITE_SPIDER_1,                IDB_BITMAP_SPIDER_1,                DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    Folio::Core::Game::CollisionGrid::CELL_VALUE_NASTY_SPRITE,      },
    {   SPRITE_SPIDER_2,                IDB_BITMAP_SPIDER_2,                DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    Folio::Core::Game::CollisionGrid::CELL_VALUE_NASTY_SPRITE,      },
    
    {   SPRITE_GHOST_1,                 IDB_BITMAP_GHOST_1,                 DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     Folio::Core::Game::CollisionGrid::CELL_VALUE_NASTY_SPRITE,      },
    {   SPRITE_GHOST_2,                 IDB_BITMAP_GHOST_2,                 DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     Folio::Core::Game::CollisionGrid::CELL_VALUE_NASTY_SPRITE,      },
    
    {   SPRITE_BOUNCY_1,                IDB_BITMAP_BOUNCY_1,                DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     Folio::Core::Game::CollisionGrid::CELL_VALUE_NASTY_SPRITE,      },
    {   SPRITE_BOUNCY_2,                IDB_BITMAP_BOUNCY_2,                DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     Folio::Core::Game::CollisionGrid::CELL_VALUE_NASTY_SPRITE,      },
    
    {   SPRITE_SMORPH_1,                IDB_BITMAP_SMORPH_1,                DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    Folio::Core::Game::CollisionGrid::CELL_VALUE_NASTY_SPRITE,      },
    {   SPRITE_SMORPH_2,                IDB_BITMAP_SMORPH_2,                DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    Folio::Core::Game::CollisionGrid::CELL_VALUE_NASTY_SPRITE,      },
    
    {   SPRITE_JELLY_GHOUL_1,           IDB_BITMAP_JELLY_GHOUL_1,           DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     Folio::Core::Game::CollisionGrid::CELL_VALUE_NASTY_SPRITE,      },
    {   SPRITE_JELLY_GHOUL_2,           IDB_BITMAP_JELLY_GHOUL_2,           DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     Folio::Core::Game::CollisionGrid::CELL_VALUE_NASTY_SPRITE,      },
    
    {   SPRITE_BAT_1,                   IDB_BITMAP_BAT_1,                   DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   Folio::Core::Game::CollisionGrid::CELL_VALUE_NASTY_SPRITE,      },
    {   SPRITE_BAT_2,                   IDB_BITMAP_BAT_2,                   DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   Folio::Core::Game::CollisionGrid::CELL_VALUE_NASTY_SPRITE,      },
    
    {   SPRITE_GHOUL_1,                 IDB_BITMAP_GHOUL_1,                 DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      Folio::Core::Game::CollisionGrid::CELL_VALUE_NASTY_SPRITE,      },
    {   SPRITE_GHOUL_2,                 IDB_BITMAP_GHOUL_2,                 DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      Folio::Core::Game::CollisionGrid::CELL_VALUE_NASTY_SPRITE,      },
    
    {   SPRITE_WITCH_FLYING_LEFT_1,     IDB_BITMAP_WITCH_FLYING_LEFT_1,     DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   Folio::Core::Game::CollisionGrid::CELL_VALUE_NASTY_SPRITE,      },
    {   SPRITE_WITCH_FLYING_LEFT_2,     IDB_BITMAP_WITCH_FLYING_LEFT_2,     DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   Folio::Core::Game::CollisionGrid::CELL_VALUE_NASTY_SPRITE,      },
    {   SPRITE_WITCH_FLYING_RIGHT_1,    IDB_BITMAP_WITCH_FLYING_RIGHT_1,    DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   Folio::Core::Game::CollisionGrid::CELL_VALUE_NASTY_SPRITE,      },
    {   SPRITE_WITCH_FLYING_RIGHT_2,    IDB_BITMAP_WITCH_FLYING_RIGHT_2,    DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   Folio::Core::Game::CollisionGrid::CELL_VALUE_NASTY_SPRITE,      },
    
    {   SPRITE_GHOUL_FLYING_LEFT_1,     IDB_BITMAP_GHOUL_FLYING_LEFT_1,     DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::RED,       Folio::Core::Game::CollisionGrid::CELL_VALUE_NASTY_SPRITE,      },
    {   SPRITE_GHOUL_FLYING_LEFT_2,     IDB_BITMAP_GHOUL_FLYING_LEFT_2,     DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::RED,       Folio::Core::Game::CollisionGrid::CELL_VALUE_NASTY_SPRITE,      },
    {   SPRITE_GHOUL_FLYING_RIGHT_1,    IDB_BITMAP_GHOUL_FLYING_RIGHT_1,    DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::RED,       Folio::Core::Game::CollisionGrid::CELL_VALUE_NASTY_SPRITE,      },
    {   SPRITE_GHOUL_FLYING_RIGHT_2,    IDB_BITMAP_GHOUL_FLYING_RIGHT_2,    DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::RED,       Folio::Core::Game::CollisionGrid::CELL_VALUE_NASTY_SPRITE,      },
    
    {   SPRITE_BAT_FLYING_LEFT_1,       IDB_BITMAP_BAT_FLYING_LEFT_1,       DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::RED,       Folio::Core::Game::CollisionGrid::CELL_VALUE_NASTY_SPRITE,      },
    {   SPRITE_BAT_FLYING_LEFT_2,       IDB_BITMAP_BAT_FLYING_LEFT_2,       DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::RED,       Folio::Core::Game::CollisionGrid::CELL_VALUE_NASTY_SPRITE,      },
    {   SPRITE_BAT_FLYING_RIGHT_1,      IDB_BITMAP_BAT_FLYING_RIGHT_1,      DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::RED,       Folio::Core::Game::CollisionGrid::CELL_VALUE_NASTY_SPRITE,      },
    {   SPRITE_BAT_FLYING_RIGHT_2,      IDB_BITMAP_BAT_FLYING_RIGHT_2,      DRAWING_ELEMENT_NASTY_SPRITE,       ZxSpectrum::BRIGHT | ZxSpectrum::RED,       Folio::Core::Game::CollisionGrid::CELL_VALUE_NASTY_SPRITE,      },

    {   SPRITE_KNIGHT_AXE_1,            IDB_BITMAP_KNIGHT_AXE_1,            DRAWING_ELEMENT_WEAPON_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::RED,       Folio::Core::Game::CollisionGrid::CELL_VALUE_WEAPON_SPRITE,     },
    {   SPRITE_KNIGHT_AXE_2,            IDB_BITMAP_KNIGHT_AXE_2,            DRAWING_ELEMENT_WEAPON_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::RED,       Folio::Core::Game::CollisionGrid::CELL_VALUE_WEAPON_SPRITE,     },
    {   SPRITE_KNIGHT_AXE_3,            IDB_BITMAP_KNIGHT_AXE_3,            DRAWING_ELEMENT_WEAPON_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::RED,       Folio::Core::Game::CollisionGrid::CELL_VALUE_WEAPON_SPRITE,     },
    {   SPRITE_KNIGHT_AXE_4,            IDB_BITMAP_KNIGHT_AXE_4,            DRAWING_ELEMENT_WEAPON_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::RED,       Folio::Core::Game::CollisionGrid::CELL_VALUE_WEAPON_SPRITE,     },
    {   SPRITE_KNIGHT_AXE_5,            IDB_BITMAP_KNIGHT_AXE_5,            DRAWING_ELEMENT_WEAPON_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::RED,       Folio::Core::Game::CollisionGrid::CELL_VALUE_WEAPON_SPRITE,     },
    {   SPRITE_KNIGHT_AXE_6,            IDB_BITMAP_KNIGHT_AXE_6,            DRAWING_ELEMENT_WEAPON_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::RED,       Folio::Core::Game::CollisionGrid::CELL_VALUE_WEAPON_SPRITE,     },
    {   SPRITE_KNIGHT_AXE_7,            IDB_BITMAP_KNIGHT_AXE_7,            DRAWING_ELEMENT_WEAPON_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::RED,       Folio::Core::Game::CollisionGrid::CELL_VALUE_WEAPON_SPRITE,     },
    {   SPRITE_KNIGHT_AXE_8,            IDB_BITMAP_KNIGHT_AXE_8,            DRAWING_ELEMENT_WEAPON_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::RED,       Folio::Core::Game::CollisionGrid::CELL_VALUE_WEAPON_SPRITE,     },

    {   SPRITE_WIZARD_POTION_1,         IDB_BITMAP_WIZARD_POTION_1,         DRAWING_ELEMENT_WEAPON_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      Folio::Core::Game::CollisionGrid::CELL_VALUE_WEAPON_SPRITE,     },
    {   SPRITE_WIZARD_POTION_2,         IDB_BITMAP_WIZARD_POTION_2,         DRAWING_ELEMENT_WEAPON_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_WEAPON_SPRITE,     },
    {   SPRITE_WIZARD_POTION_3,         IDB_BITMAP_WIZARD_POTION_3,         DRAWING_ELEMENT_WEAPON_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      Folio::Core::Game::CollisionGrid::CELL_VALUE_WEAPON_SPRITE,     },

    {   SPRITE_SERF_SWORD_1,            IDB_BITMAP_SERF_SWORD_1,            DRAWING_ELEMENT_WEAPON_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    Folio::Core::Game::CollisionGrid::CELL_VALUE_WEAPON_SPRITE,     },
    {   SPRITE_SERF_SWORD_2,            IDB_BITMAP_SERF_SWORD_2,            DRAWING_ELEMENT_WEAPON_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    Folio::Core::Game::CollisionGrid::CELL_VALUE_WEAPON_SPRITE,     },
    {   SPRITE_SERF_SWORD_3,            IDB_BITMAP_SERF_SWORD_3,            DRAWING_ELEMENT_WEAPON_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    Folio::Core::Game::CollisionGrid::CELL_VALUE_WEAPON_SPRITE,     },
    {   SPRITE_SERF_SWORD_4,            IDB_BITMAP_SERF_SWORD_4,            DRAWING_ELEMENT_WEAPON_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    Folio::Core::Game::CollisionGrid::CELL_VALUE_WEAPON_SPRITE,     },
    {   SPRITE_SERF_SWORD_5,            IDB_BITMAP_SERF_SWORD_5,            DRAWING_ELEMENT_WEAPON_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    Folio::Core::Game::CollisionGrid::CELL_VALUE_WEAPON_SPRITE,     },
    {   SPRITE_SERF_SWORD_6,            IDB_BITMAP_SERF_SWORD_6,            DRAWING_ELEMENT_WEAPON_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    Folio::Core::Game::CollisionGrid::CELL_VALUE_WEAPON_SPRITE,     },
    {   SPRITE_SERF_SWORD_7,            IDB_BITMAP_SERF_SWORD_7,            DRAWING_ELEMENT_WEAPON_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    Folio::Core::Game::CollisionGrid::CELL_VALUE_WEAPON_SPRITE,     },
    {   SPRITE_SERF_SWORD_8,            IDB_BITMAP_SERF_SWORD_8,            DRAWING_ELEMENT_WEAPON_SPRITE,      ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    Folio::Core::Game::CollisionGrid::CELL_VALUE_WEAPON_SPRITE,     },

    {   SPRITE_MUMMY_1,                 IDB_BITMAP_MUMMY_1,                 DRAWING_ELEMENT_BOSS_SPRITE,        ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_BOSS_SPRITE,       },
    {   SPRITE_MUMMY_2,                 IDB_BITMAP_MUMMY_2,                 DRAWING_ELEMENT_BOSS_SPRITE,        ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_BOSS_SPRITE,       },
    {   SPRITE_MUMMY_3,                 IDB_BITMAP_MUMMY_3,                 DRAWING_ELEMENT_BOSS_SPRITE,        ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     Folio::Core::Game::CollisionGrid::CELL_VALUE_BOSS_SPRITE,       },
    
    {   SPRITE_DRACULA_1,               IDB_BITMAP_DRACULA_1,               DRAWING_ELEMENT_BOSS_SPRITE,        ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     Folio::Core::Game::CollisionGrid::CELL_VALUE_BOSS_SPRITE,       },
    {   SPRITE_DRACULA_2,               IDB_BITMAP_DRACULA_2,               DRAWING_ELEMENT_BOSS_SPRITE,        ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     Folio::Core::Game::CollisionGrid::CELL_VALUE_BOSS_SPRITE,       },
    {   SPRITE_DRACULA_3,               IDB_BITMAP_DRACULA_3,               DRAWING_ELEMENT_BOSS_SPRITE,        ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     Folio::Core::Game::CollisionGrid::CELL_VALUE_BOSS_SPRITE,       },
    
    {   SPRITE_FRANKENSTEIN_1,          IDB_BITMAP_FRANKENSTEIN_1,          DRAWING_ELEMENT_BOSS_SPRITE,        ZxSpectrum::BRIGHT | ZxSpectrum::RED,       Folio::Core::Game::CollisionGrid::CELL_VALUE_BOSS_SPRITE,       },
    {   SPRITE_FRANKENSTEIN_2,          IDB_BITMAP_FRANKENSTEIN_2,          DRAWING_ELEMENT_BOSS_SPRITE,        ZxSpectrum::BRIGHT | ZxSpectrum::RED,       Folio::Core::Game::CollisionGrid::CELL_VALUE_BOSS_SPRITE,       },
    {   SPRITE_FRANKENSTEIN_3,          IDB_BITMAP_FRANKENSTEIN_3,          DRAWING_ELEMENT_BOSS_SPRITE,        ZxSpectrum::BRIGHT | ZxSpectrum::RED,       Folio::Core::Game::CollisionGrid::CELL_VALUE_BOSS_SPRITE,       },
    
    {   SPRITE_HUNCHBACK_1,             IDB_BITMAP_HUNCHBACK_1,             DRAWING_ELEMENT_BOSS_SPRITE,        ZxSpectrum::BRIGHT | ZxSpectrum::RED,       Folio::Core::Game::CollisionGrid::CELL_VALUE_BOSS_SPRITE,       },
    {   SPRITE_HUNCHBACK_2,             IDB_BITMAP_HUNCHBACK_2,             DRAWING_ELEMENT_BOSS_SPRITE,        ZxSpectrum::BRIGHT | ZxSpectrum::RED,       Folio::Core::Game::CollisionGrid::CELL_VALUE_BOSS_SPRITE,       },
    {   SPRITE_HUNCHBACK_3,             IDB_BITMAP_HUNCHBACK_3,             DRAWING_ELEMENT_BOSS_SPRITE,        ZxSpectrum::BRIGHT | ZxSpectrum::RED,       Folio::Core::Game::CollisionGrid::CELL_VALUE_BOSS_SPRITE,       },
    
    {   SPRITE_DEVIL_1,                 IDB_BITMAP_DEVIL_1,                 DRAWING_ELEMENT_BOSS_SPRITE,        ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   Folio::Core::Game::CollisionGrid::CELL_VALUE_BOSS_SPRITE,       },
    {   SPRITE_DEVIL_2,                 IDB_BITMAP_DEVIL_2,                 DRAWING_ELEMENT_BOSS_SPRITE,        ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   Folio::Core::Game::CollisionGrid::CELL_VALUE_BOSS_SPRITE,       },
    {   SPRITE_DEVIL_3,                 IDB_BITMAP_DEVIL_3,                 DRAWING_ELEMENT_BOSS_SPRITE,        ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   Folio::Core::Game::CollisionGrid::CELL_VALUE_BOSS_SPRITE,       },
};


FolioStatus BuildSpriteGraphics (FolioHandle        dcHandle, 
                                 FolioHandle        instanceHandle,
                                 SpriteGraphicsMap  &spriteGraphicsMap)
{
    FolioStatus status = ERR_SUCCESS;

    spriteGraphicsMap.clear ();    // Initialise!

    // Build the sprite graphics map. 

    for (UInt32 index = 0; 
         (status == ERR_SUCCESS) && (index < (sizeof (g_spriteGraphicAttributesTable) / sizeof (SpriteGraphicAttributes)));
         ++index)
    {              
        // Create a sprite graphic.

        SpriteGraphic   spriteGraphic(new SpriteGraphic::element_type);

        status = spriteGraphic->Create (dcHandle,
                                        instanceHandle,
                                        g_spriteGraphicAttributesTable [index].m_drawingElementId,
                                        g_spriteGraphicAttributesTable [index].m_bitmapResourceId,
                                        ZxSpectrum::GetBitmapChangeColour (),
                                        ZxSpectrum::MapInkColour (g_spriteGraphicAttributesTable [index].m_colour),
                                        true,   // Require a masked bitmap drawing element.
                                        g_spriteGraphicAttributesTable [index].m_collisionGridCellValue);

        if (status == ERR_SUCCESS)
        {
            // Store the sprite graphic in the sprite graphics map.

            spriteGraphicsMap.insert (SpriteGraphicsMap::value_type(g_spriteGraphicAttributesTable [index].m_spriteId, 
                                                                    spriteGraphic));
        } // Endif.
       
    } // Endfor.

    if (status != ERR_SUCCESS)
    {
        spriteGraphicsMap.clear ();
    } // Endif.
   
    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
