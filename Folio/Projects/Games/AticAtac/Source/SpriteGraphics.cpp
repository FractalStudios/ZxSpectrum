// "Home-made" includes.
#include    "StdAfx.h"
#include    "CollisionGrid.h"
#include    "DrawingElement.h"
#include    "Globals.h"
#include    "Screen.h"
#include    "SpriteGraphics.h"

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Sprite graphic attributes.
struct SpriteGraphicAttributes
{
    SPRITE_ID                               m_spriteId;                 // The identifier of the sprite.
    UInt32                                  m_maxOnScreen;              // The maximum number of sprites per screen.
    DRAWING_ELEMENT_ID                      m_drawingElementId;         // The drawing element identifier of the sprite.
    Folio::Core::Game::ZxSpectrum::COLOUR   m_colour;                   // The colour of the sprite.
    CollisionGrid::CellValue                m_collisionGridCellValue;   // The collision grid cell value of the sprite.
 }; // Endstruct.

// Sprite graphic attributes table.
static  const   SpriteGraphicAttributes   g_spriteGraphicAttributesTable [] =
{
//      m_spriteId                      m_maxOnScreen                           m_drawingElementId                  m_colour                                                                        m_collisionGridCellValue
    {   SPRITE_LEAF,                    0,                                      DRAWING_ELEMENT_STATIC_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM  },
    {   SPRITE_KEY,                     0,                                      DRAWING_ELEMENT_STATIC_SPRITE,      Folio::Core::Game::ZxSpectrum::UNDEFINED,                                       CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, },
    {   SPRITE_BOTTLE,                  0,                                      DRAWING_ELEMENT_STATIC_SPRITE,      Folio::Core::Game::ZxSpectrum::UNDEFINED,                                       CollisionGrid::CELL_VALUE_HEALTH_ITEM,      },
    {   SPRITE_MEDICINE_BOTTLE,         0,                                      DRAWING_ELEMENT_STATIC_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, },
    {   SPRITE_BROKEN,                  0,                                      DRAWING_ELEMENT_STATIC_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, },
    {   SPRITE_ROPE,                    0,                                      DRAWING_ELEMENT_STATIC_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, },
    {   SPRITE_ARM,                     0,                                      DRAWING_ELEMENT_STATIC_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, },
    {   SPRITE_BOWL,                    0,                                      DRAWING_ELEMENT_STATIC_SPRITE,      Folio::Core::Game::ZxSpectrum::UNDEFINED,                                       CollisionGrid::CELL_VALUE_HEALTH_ITEM,      },
    {   SPRITE_APPLE,                   0,                                      DRAWING_ELEMENT_STATIC_SPRITE,      Folio::Core::Game::ZxSpectrum::UNDEFINED,                                       CollisionGrid::CELL_VALUE_HEALTH_ITEM,      },
    {   SPRITE_CANDY_BAR,               0,                                      DRAWING_ELEMENT_STATIC_SPRITE,      Folio::Core::Game::ZxSpectrum::UNDEFINED,                                       CollisionGrid::CELL_VALUE_HEALTH_ITEM,      },
    {   SPRITE_HAM,                     0,                                      DRAWING_ELEMENT_STATIC_SPRITE,      Folio::Core::Game::ZxSpectrum::UNDEFINED,                                       CollisionGrid::CELL_VALUE_HEALTH_ITEM,      },
    {   SPRITE_LOLLIPOP,                0,                                      DRAWING_ELEMENT_STATIC_SPRITE,      Folio::Core::Game::ZxSpectrum::UNDEFINED,                                       CollisionGrid::CELL_VALUE_HEALTH_ITEM,      },
    {   SPRITE_MONEY_BAG,               0,                                      DRAWING_ELEMENT_STATIC_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, },
    {   SPRITE_GOBSTOPPER,              0,                                      DRAWING_ELEMENT_STATIC_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, },
    {   SPRITE_AMULET,                  0,                                      DRAWING_ELEMENT_STATIC_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, },
    {   SPRITE_CAN,                     0,                                      DRAWING_ELEMENT_STATIC_SPRITE,      Folio::Core::Game::ZxSpectrum::UNDEFINED,                                       CollisionGrid::CELL_VALUE_HEALTH_ITEM,      },
    {   SPRITE_ICE_CREAM_CONE,          0,                                      DRAWING_ELEMENT_STATIC_SPRITE,      Folio::Core::Game::ZxSpectrum::UNDEFINED,                                       CollisionGrid::CELL_VALUE_HEALTH_ITEM,      },
    {   SPRITE_CRUCIFIX,                0,                                      DRAWING_ELEMENT_STATIC_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, },
    {   SPRITE_SKULL,                   0,                                      DRAWING_ELEMENT_STATIC_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, },
    {   SPRITE_SPANNER,                 0,                                      DRAWING_ELEMENT_STATIC_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, },
    {   SPRITE_ACG_KEY_LEFT,            0,                                      DRAWING_ELEMENT_STATIC_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, },
    {   SPRITE_ACG_KEY_MIDDLE,          0,                                      DRAWING_ELEMENT_STATIC_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, },
    {   SPRITE_ACG_KEY_RIGHT,           0,                                      DRAWING_ELEMENT_STATIC_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, },
    {   SPRITE_MUSHROOM,                0,                                      DRAWING_ELEMENT_STATIC_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     CollisionGrid::CELL_VALUE_HARMFUL_ITEM,     },
    {   SPRITE_GRAVESTONE,              0,                                      DRAWING_ELEMENT_STATIC_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    CollisionGrid::CELL_VALUE_EMPTY,            },

    {   SPRITE_KNIGHT_WALKING_UP_1,     1,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_KNIGHT_UP,               2,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_KNIGHT_WALKING_UP_2,     1,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_KNIGHT_WALKING_DOWN_1,   1,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_KNIGHT_DOWN,             2,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_KNIGHT_WALKING_DOWN_2,   1,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_KNIGHT_WALKING_LEFT_1,   1,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_KNIGHT_LEFT,             2,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_KNIGHT_WALKING_LEFT_2,   1,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_KNIGHT_WALKING_RIGHT_1,  1,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_KNIGHT_RIGHT,            2,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_KNIGHT_WALKING_RIGHT_2,  1,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },

    {   SPRITE_WIZARD_WALKING_UP_1,     1,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_WIZARD_UP,               2,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_WIZARD_WALKING_UP_2,     1,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_WIZARD_WALKING_DOWN_1,   1,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_WIZARD_DOWN,             2,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_WIZARD_WALKING_DOWN_2,   1,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_WIZARD_WALKING_LEFT_1,   1,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_WIZARD_LEFT,             2,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_WIZARD_WALKING_LEFT_2,   1,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_WIZARD_WALKING_RIGHT_1,  1,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_WIZARD_RIGHT,            2,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_WIZARD_WALKING_RIGHT_2,  1,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },

    {   SPRITE_SERF_WALKING_UP_1,       1,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_SERF_UP,                 2,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_SERF_WALKING_UP_2,       1,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_SERF_WALKING_DOWN_1,     1,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_SERF_DOWN,               2,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_SERF_WALKING_DOWN_2,     1,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_SERF_WALKING_LEFT_1,     1,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_SERF_LEFT,               2,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_SERF_WALKING_LEFT_2,     1,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_SERF_WALKING_RIGHT_1,    1,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_SERF_RIGHT,              2,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_SERF_WALKING_RIGHT_2,    1,                                      DRAWING_ELEMENT_MAIN_PLAYER_SPRITE, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_EMPTY,            },

    {   SPRITE_NASTY_ALIVE_1,           MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_NASTY_ALIVE_2,           MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_NASTY_ALIVE_3,           MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_NASTY_ALIVE_4,           MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   CollisionGrid::CELL_VALUE_EMPTY,            },

    {   SPRITE_NASTY_DEAD_1,            1 + MAX_NASTY_SPRITE_DRAWING_ELEMENTS,  DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_NASTY_DEAD_2,            1 + MAX_NASTY_SPRITE_DRAWING_ELEMENTS,  DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_NASTY_DEAD_3,            1 + MAX_NASTY_SPRITE_DRAWING_ELEMENTS,  DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   CollisionGrid::CELL_VALUE_EMPTY,            },
    {   SPRITE_NASTY_DEAD_4,            1 + MAX_NASTY_SPRITE_DRAWING_ELEMENTS,  DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   CollisionGrid::CELL_VALUE_EMPTY,            },
    
    {   SPRITE_PUMPKIN_1,               MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  CollisionGrid::CELL_VALUE_NASTY_SPRITE,     },
    {   SPRITE_PUMPKIN_2,               MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  CollisionGrid::CELL_VALUE_NASTY_SPRITE,     },
    
    {   SPRITE_SPIDER_1,                MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  CollisionGrid::CELL_VALUE_NASTY_SPRITE,     },
    {   SPRITE_SPIDER_2,                MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  CollisionGrid::CELL_VALUE_NASTY_SPRITE,     },
    
    {   SPRITE_GHOST_1,                 MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   CollisionGrid::CELL_VALUE_NASTY_SPRITE,     },
    {   SPRITE_GHOST_2,                 MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   CollisionGrid::CELL_VALUE_NASTY_SPRITE,     },
    
    {   SPRITE_BOUNCY_1,                MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   CollisionGrid::CELL_VALUE_NASTY_SPRITE,     },
    {   SPRITE_BOUNCY_2,                MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   CollisionGrid::CELL_VALUE_NASTY_SPRITE,     },
    
    {   SPRITE_SMORPH_1,                MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  CollisionGrid::CELL_VALUE_NASTY_SPRITE,     },
    {   SPRITE_SMORPH_2,                MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  CollisionGrid::CELL_VALUE_NASTY_SPRITE,     },
    
    {   SPRITE_JELLY_GHOUL_1,           MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   CollisionGrid::CELL_VALUE_NASTY_SPRITE,     },
    {   SPRITE_JELLY_GHOUL_2,           MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   CollisionGrid::CELL_VALUE_NASTY_SPRITE,     },
    
    {   SPRITE_BAT_1,                   MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, CollisionGrid::CELL_VALUE_NASTY_SPRITE,     },
    {   SPRITE_BAT_2,                   MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, CollisionGrid::CELL_VALUE_NASTY_SPRITE,     },
    
    {   SPRITE_GHOUL_1,                 MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    CollisionGrid::CELL_VALUE_NASTY_SPRITE,     },
    {   SPRITE_GHOUL_2,                 MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    CollisionGrid::CELL_VALUE_NASTY_SPRITE,     },
    
    {   SPRITE_WITCH_FLYING_LEFT_1,     MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, CollisionGrid::CELL_VALUE_NASTY_SPRITE,     },
    {   SPRITE_WITCH_FLYING_LEFT_2,     MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, CollisionGrid::CELL_VALUE_NASTY_SPRITE,     },
    {   SPRITE_WITCH_FLYING_RIGHT_1,    MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, CollisionGrid::CELL_VALUE_NASTY_SPRITE,     },
    {   SPRITE_WITCH_FLYING_RIGHT_2,    MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, CollisionGrid::CELL_VALUE_NASTY_SPRITE,     },
    
    {   SPRITE_GHOUL_FLYING_LEFT_1,     MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     CollisionGrid::CELL_VALUE_NASTY_SPRITE,     },
    {   SPRITE_GHOUL_FLYING_LEFT_2,     MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     CollisionGrid::CELL_VALUE_NASTY_SPRITE,     },
    {   SPRITE_GHOUL_FLYING_RIGHT_1,    MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     CollisionGrid::CELL_VALUE_NASTY_SPRITE,     },
    {   SPRITE_GHOUL_FLYING_RIGHT_2,    MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     CollisionGrid::CELL_VALUE_NASTY_SPRITE,     },
    
    {   SPRITE_BAT_FLYING_LEFT_1,       MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     CollisionGrid::CELL_VALUE_NASTY_SPRITE,     },
    {   SPRITE_BAT_FLYING_LEFT_2,       MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     CollisionGrid::CELL_VALUE_NASTY_SPRITE,     },
    {   SPRITE_BAT_FLYING_RIGHT_1,      MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     CollisionGrid::CELL_VALUE_NASTY_SPRITE,     },
    {   SPRITE_BAT_FLYING_RIGHT_2,      MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     CollisionGrid::CELL_VALUE_NASTY_SPRITE,     },

    {   SPRITE_KNIGHT_AXE_1,            1,                                      DRAWING_ELEMENT_WEAPON_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     CollisionGrid::CELL_VALUE_WEAPON_SPRITE,    },
    {   SPRITE_KNIGHT_AXE_2,            1,                                      DRAWING_ELEMENT_WEAPON_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     CollisionGrid::CELL_VALUE_WEAPON_SPRITE,    },
    {   SPRITE_KNIGHT_AXE_3,            1,                                      DRAWING_ELEMENT_WEAPON_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     CollisionGrid::CELL_VALUE_WEAPON_SPRITE,    },
    {   SPRITE_KNIGHT_AXE_4,            1,                                      DRAWING_ELEMENT_WEAPON_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     CollisionGrid::CELL_VALUE_WEAPON_SPRITE,    },
    {   SPRITE_KNIGHT_AXE_5,            1,                                      DRAWING_ELEMENT_WEAPON_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     CollisionGrid::CELL_VALUE_WEAPON_SPRITE,    },
    {   SPRITE_KNIGHT_AXE_6,            1,                                      DRAWING_ELEMENT_WEAPON_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     CollisionGrid::CELL_VALUE_WEAPON_SPRITE,    },
    {   SPRITE_KNIGHT_AXE_7,            1,                                      DRAWING_ELEMENT_WEAPON_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     CollisionGrid::CELL_VALUE_WEAPON_SPRITE,    },
    {   SPRITE_KNIGHT_AXE_8,            1,                                      DRAWING_ELEMENT_WEAPON_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     CollisionGrid::CELL_VALUE_WEAPON_SPRITE,    },

    {   SPRITE_WIZARD_POTION_1,         1,                                      DRAWING_ELEMENT_WEAPON_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    CollisionGrid::CELL_VALUE_WEAPON_SPRITE,    },
    {   SPRITE_WIZARD_POTION_2,         1,                                      DRAWING_ELEMENT_WEAPON_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_WEAPON_SPRITE,    },
    {   SPRITE_WIZARD_POTION_3,         1,                                      DRAWING_ELEMENT_WEAPON_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    CollisionGrid::CELL_VALUE_WEAPON_SPRITE,    },

    {   SPRITE_SERF_SWORD_1,            1,                                      DRAWING_ELEMENT_WEAPON_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  CollisionGrid::CELL_VALUE_WEAPON_SPRITE,    },
    {   SPRITE_SERF_SWORD_2,            1,                                      DRAWING_ELEMENT_WEAPON_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  CollisionGrid::CELL_VALUE_WEAPON_SPRITE,    },
    {   SPRITE_SERF_SWORD_3,            1,                                      DRAWING_ELEMENT_WEAPON_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  CollisionGrid::CELL_VALUE_WEAPON_SPRITE,    },
    {   SPRITE_SERF_SWORD_4,            1,                                      DRAWING_ELEMENT_WEAPON_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  CollisionGrid::CELL_VALUE_WEAPON_SPRITE,    },
    {   SPRITE_SERF_SWORD_5,            1,                                      DRAWING_ELEMENT_WEAPON_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  CollisionGrid::CELL_VALUE_WEAPON_SPRITE,    },
    {   SPRITE_SERF_SWORD_6,            1,                                      DRAWING_ELEMENT_WEAPON_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  CollisionGrid::CELL_VALUE_WEAPON_SPRITE,    },
    {   SPRITE_SERF_SWORD_7,            1,                                      DRAWING_ELEMENT_WEAPON_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  CollisionGrid::CELL_VALUE_WEAPON_SPRITE,    },
    {   SPRITE_SERF_SWORD_8,            1,                                      DRAWING_ELEMENT_WEAPON_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  CollisionGrid::CELL_VALUE_WEAPON_SPRITE,    },

    {   SPRITE_MUMMY_1,                 1,                                      DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_BOSS_SPRITE,      },
    {   SPRITE_MUMMY_2,                 2,                                      DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_BOSS_SPRITE,      },
    {   SPRITE_MUMMY_3,                 1,                                      DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   CollisionGrid::CELL_VALUE_BOSS_SPRITE,      },

    {   SPRITE_DRACULA_1,               1,                                      DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   CollisionGrid::CELL_VALUE_BOSS_SPRITE,      },
    {   SPRITE_DRACULA_2,               2,                                      DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   CollisionGrid::CELL_VALUE_BOSS_SPRITE,      },
    {   SPRITE_DRACULA_3,               1,                                      DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   CollisionGrid::CELL_VALUE_BOSS_SPRITE,      },
    
    {   SPRITE_FRANKENSTEIN_1,          1,                                      DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     CollisionGrid::CELL_VALUE_BOSS_SPRITE,      },
    {   SPRITE_FRANKENSTEIN_2,          2,                                      DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     CollisionGrid::CELL_VALUE_BOSS_SPRITE,      },
    {   SPRITE_FRANKENSTEIN_3,          1,                                      DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     CollisionGrid::CELL_VALUE_BOSS_SPRITE,      },
    
    {   SPRITE_HUNCHBACK_1,             1,                                      DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     CollisionGrid::CELL_VALUE_BOSS_SPRITE,      },
    {   SPRITE_HUNCHBACK_2,             2,                                      DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     CollisionGrid::CELL_VALUE_BOSS_SPRITE,      },
    {   SPRITE_HUNCHBACK_3,             1,                                      DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     CollisionGrid::CELL_VALUE_BOSS_SPRITE,      },
    
    {   SPRITE_DEVIL_1,                 1,                                      DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, CollisionGrid::CELL_VALUE_BOSS_SPRITE,      },
    {   SPRITE_DEVIL_2,                 2,                                      DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, CollisionGrid::CELL_VALUE_BOSS_SPRITE,      },
    {   SPRITE_DEVIL_3,                 1,                                      DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, CollisionGrid::CELL_VALUE_BOSS_SPRITE,      },
};


FolioStatus CreateSpriteGraphics (FolioHandle instanceHandle)
{
    FolioStatus status = ERR_SUCCESS;

    // Add the sprite graphics into the resource graphics cache. 

    for (UInt32 index = 0; 
         (status == ERR_SUCCESS) && (index < (sizeof (g_spriteGraphicAttributesTable) / sizeof (SpriteGraphicAttributes)));
         ++index)
    {              
        // Get the maximum sprites on any single screen; use to build the resource graphics cache.

        UInt32  maxSpritesOnScreen = g_spriteGraphicAttributesTable [index].m_maxOnScreen;

        switch (g_spriteGraphicAttributesTable [index].m_drawingElementId)
        {
        case DRAWING_ELEMENT_STATIC_SPRITE:
            maxSpritesOnScreen = std::max (static_cast<UInt32> (1), 
                                           GetMaxStaticSpritesOnScreen (static_cast<STATIC_SPRITE_ID> (g_spriteGraphicAttributesTable [index].m_spriteId)));
            break;
        default:
            break;
        } // Endswitch.

        for (UInt32 cacheCount = 0; 
             (status == ERR_SUCCESS) && (cacheCount < maxSpritesOnScreen);
             ++cacheCount)
        {            
            // Create a sprite graphic.

            SpriteGraphic   spriteGraphic(new SpriteGraphic::element_type);

            status = spriteGraphic->Create (instanceHandle,
                                            g_spriteGraphicAttributesTable [index].m_drawingElementId,
                                            g_spriteGraphicAttributesTable [index].m_spriteId,
                                            Folio::Core::Game::ZxSpectrum::GetBitmapChangeColour (),
                                            Folio::Core::Game::ZxSpectrum::MapInkColour (g_spriteGraphicAttributesTable [index].m_colour),
                                            true,   // Require a masked bitmap drawing element.
                                            g_spriteGraphicAttributesTable [index].m_collisionGridCellValue);

            if (status == ERR_SUCCESS)
            {
                // Store the sprite graphic in the resource graphics cache.

                g_resourceGraphicsCache.Add (g_spriteGraphicAttributesTable [index].m_drawingElementId, spriteGraphic);
            } // Endif.

        } // Endif.
       
    } // Endfor.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
