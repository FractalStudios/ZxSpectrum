// "Home-made" includes.
#include    "StdAfx.h"
#include    "CollisionGrid.h"
#include    "DrawingElement.h"
#include    "SpriteGraphics.h"

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Sprite graphic attributes.
struct SpriteGraphicAttributes
{
    SPRITE_ID                               m_spriteId;                 // The identifier of the sprite.
    UInt16                                  m_bitmapResourceId;         // The sprite's bitmap resource identifier.
    DRAWING_ELEMENT_ID                      m_drawingElementId;         // The drawing element identifier of the sprite.
    Folio::Core::Game::ZxSpectrum::COLOUR   m_colour;                   // The colour of the sprite.
    CollisionGrid::CellValue                m_collisionGridCellValue;   // The collision grid cell value of the sprite.
 }; // Endstruct.

// Sprite graphic attributes table.
static  const   SpriteGraphicAttributes   g_spriteGraphicAttributesTable [] =
{
//      m_spriteId                                  m_bitmapResourceId                          m_drawingElementId                  m_colour                                                                                        m_collisionGridCellValue
    {   SPRITE_BOX,                                 IDB_BITMAP_BOX,                             DRAWING_ELEMENT_OBJECT_SPRITE,      Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, }, 
    {   SPRITE_RING,                                IDB_BITMAP_RING,                            DRAWING_ELEMENT_OBJECT_SPRITE,      Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, }, 
    {   SPRITE_APPLE,                               IDB_BITMAP_APPLE,                           DRAWING_ELEMENT_OBJECT_SPRITE,      Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, }, 
    {   SPRITE_CHARM,                               IDB_BITMAP_CHARM,                           DRAWING_ELEMENT_OBJECT_SPRITE,      Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, }, 
    {   SPRITE_AMULET,                              IDB_BITMAP_AMULET,                          DRAWING_ELEMENT_OBJECT_SPRITE,      Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, },
    {   SPRITE_EXTRA_LIFE,                          IDB_BITMAP_EXTRA_LIFE,                      DRAWING_ELEMENT_OBJECT_SPRITE,      Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, },  
    {   SPRITE_MONEY_BAG,                           IDB_BITMAP_MONEY_BAG,                       DRAWING_ELEMENT_OBJECT_SPRITE,      Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, }, 
    {   SPRITE_SPEAR,                               IDB_BITMAP_SPEAR,                           DRAWING_ELEMENT_OBJECT_SPRITE,      Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, }, 
    {   SPRITE_CHALICE,                             IDB_BITMAP_CHALICE,                         DRAWING_ELEMENT_OBJECT_SPRITE,      Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, }, 
    {   SPRITE_AMULET_PIECE_TOP_LEFT,               IDB_BITMAP_AMULET_PIECE_TOP_LEFT,           DRAWING_ELEMENT_OBJECT_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW),  CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, }, 
    {   SPRITE_AMULET_PIECE_TOP_RIGHT,              IDB_BITMAP_AMULET_PIECE_TOP_RIGHT,          DRAWING_ELEMENT_OBJECT_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW),  CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, }, 
    {   SPRITE_AMULET_PIECE_BOTTOM_LEFT,            IDB_BITMAP_AMULET_PIECE_BOTTOM_LEFT,        DRAWING_ELEMENT_OBJECT_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW),  CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, }, 
    {   SPRITE_AMULET_PIECE_BOTTOM_RIGHT,           IDB_BITMAP_AMULET_PIECE_BOTTOM_RIGHT,       DRAWING_ELEMENT_OBJECT_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW),  CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, }, 
    
    {   SPRITE_ORCHID_1,                            IDB_BITMAP_ORCHID_1,                        DRAWING_ELEMENT_ORCHID_SPRITE,      Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_ITEM,             }, 
    {   SPRITE_ORCHID_2,                            IDB_BITMAP_ORCHID_2,                        DRAWING_ELEMENT_ORCHID_SPRITE,      Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_ITEM,             }, 
    {   SPRITE_ORCHID_3,                            IDB_BITMAP_ORCHID_3,                        DRAWING_ELEMENT_ORCHID_SPRITE,      Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_ITEM,             }, 
    {   SPRITE_ORCHID_4,                            IDB_BITMAP_ORCHID_4,                        DRAWING_ELEMENT_ORCHID_SPRITE,      Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_ITEM,             }, 
    {   SPRITE_ORCHID_5,                            IDB_BITMAP_ORCHID_5,                        DRAWING_ELEMENT_ORCHID_SPRITE,      Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_ITEM,             }, 
    {   SPRITE_ORCHID_6,                            IDB_BITMAP_ORCHID_6,                        DRAWING_ELEMENT_ORCHID_SPRITE,      Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_ITEM,             }, 
    {   SPRITE_ORCHID_7,                            IDB_BITMAP_ORCHID_7,                        DRAWING_ELEMENT_ORCHID_SPRITE,      Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_ITEM,             },  
    {   SPRITE_ORCHID_8,                            IDB_BITMAP_ORCHID_8,                        DRAWING_ELEMENT_ORCHID_SPRITE,      Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_ITEM,             },  

    {   SPRITE_SABRE_MAN_UP,                        IDB_BITMAP_SABRE_MAN_UP,                    DRAWING_ELEMENT_PLAYER_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_WALKING_UP_1,              IDB_BITMAP_SABRE_MAN_WALKING_UP_1,          DRAWING_ELEMENT_PLAYER_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_WALKING_UP_2,              IDB_BITMAP_SABRE_MAN_WALKING_UP_2,          DRAWING_ELEMENT_PLAYER_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_DOWN,                      IDB_BITMAP_SABRE_MAN_DOWN,                  DRAWING_ELEMENT_PLAYER_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_WALKING_DOWN_1,            IDB_BITMAP_SABRE_MAN_WALKING_DOWN_1,        DRAWING_ELEMENT_PLAYER_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_WALKING_DOWN_2,            IDB_BITMAP_SABRE_MAN_WALKING_DOWN_2,        DRAWING_ELEMENT_PLAYER_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_LEFT,                      IDB_BITMAP_SABRE_MAN_LEFT,                  DRAWING_ELEMENT_PLAYER_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_WALKING_LEFT_1,            IDB_BITMAP_SABRE_MAN_WALKING_LEFT_1,        DRAWING_ELEMENT_PLAYER_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_WALKING_LEFT_2,            IDB_BITMAP_SABRE_MAN_WALKING_LEFT_2,        DRAWING_ELEMENT_PLAYER_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_RIGHT,                     IDB_BITMAP_SABRE_MAN_RIGHT,                 DRAWING_ELEMENT_PLAYER_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_WALKING_RIGHT_1,           IDB_BITMAP_SABRE_MAN_WALKING_RIGHT_1,       DRAWING_ELEMENT_PLAYER_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_WALKING_RIGHT_2,           IDB_BITMAP_SABRE_MAN_WALKING_RIGHT_2,       DRAWING_ELEMENT_PLAYER_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            },

    {   SPRITE_SABRE_MAN_SWORD_LEFT_1,              IDB_BITMAP_SABRE_MAN_SWORD_LEFT_1,          DRAWING_ELEMENT_PLAYER_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_SWORD_LEFT_2,              IDB_BITMAP_SABRE_MAN_SWORD_LEFT_2,          DRAWING_ELEMENT_PLAYER_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_SWORD_LEFT_3,              IDB_BITMAP_SABRE_MAN_SWORD_LEFT_3,          DRAWING_ELEMENT_PLAYER_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_SWORD_LEFT_4,              IDB_BITMAP_SABRE_MAN_SWORD_LEFT_4,          DRAWING_ELEMENT_PLAYER_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_SWORD_LEFT_5,              IDB_BITMAP_SABRE_MAN_SWORD_LEFT_5,          DRAWING_ELEMENT_PLAYER_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_SWORD_LEFT_6,              IDB_BITMAP_SABRE_MAN_SWORD_LEFT_6,          DRAWING_ELEMENT_PLAYER_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_SWORD_RIGHT_1,             IDB_BITMAP_SABRE_MAN_SWORD_RIGHT_1,         DRAWING_ELEMENT_PLAYER_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_SWORD_RIGHT_2,             IDB_BITMAP_SABRE_MAN_SWORD_RIGHT_2,         DRAWING_ELEMENT_PLAYER_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_SWORD_RIGHT_3,             IDB_BITMAP_SABRE_MAN_SWORD_RIGHT_3,         DRAWING_ELEMENT_PLAYER_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_SWORD_RIGHT_4,             IDB_BITMAP_SABRE_MAN_SWORD_RIGHT_4,         DRAWING_ELEMENT_PLAYER_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_SWORD_RIGHT_5,             IDB_BITMAP_SABRE_MAN_SWORD_RIGHT_5,         DRAWING_ELEMENT_PLAYER_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_SWORD_RIGHT_6,             IDB_BITMAP_SABRE_MAN_SWORD_RIGHT_6,         DRAWING_ELEMENT_PLAYER_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    
    {   SPRITE_SABRE_MAN_FALLING_LEFT,              IDB_BITMAP_SABRE_MAN_FALLING_LEFT,          DRAWING_ELEMENT_PLAYER_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_FALLING_RIGHT,             IDB_BITMAP_SABRE_MAN_FALLING_RIGHT,         DRAWING_ELEMENT_PLAYER_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 

    {   SPRITE_SABRE_MAN_SITTING_LEFT,              IDB_BITMAP_SABRE_MAN_SITTING_LEFT,          DRAWING_ELEMENT_PLAYER_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_SITTING_RIGHT,             IDB_BITMAP_SABRE_MAN_SITTING_RIGHT,         DRAWING_ELEMENT_PLAYER_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 

    {   SPRITE_SABRE_MAN_GAME_OVER_LEFT,            IDB_BITMAP_SABRE_MAN_GAME_OVER_LEFT,        DRAWING_ELEMENT_PLAYER_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_GAME_OVER_RIGHT,           IDB_BITMAP_SABRE_MAN_GAME_OVER_RIGHT,       DRAWING_ELEMENT_PLAYER_SPRITE,      Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 

    {   SPRITE_WOLF_WALKING_LEFT_1,                 IDB_BITMAP_WOLF_WALKING_LEFT_1,             DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_WOLF_WALKING_LEFT_2,                 IDB_BITMAP_WOLF_WALKING_LEFT_2,             DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_WOLF_WALKING_LEFT_3,                 IDB_BITMAP_WOLF_WALKING_LEFT_3,             DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_WOLF_WALKING_RIGHT_1,                IDB_BITMAP_WOLF_WALKING_RIGHT_1,            DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_WOLF_WALKING_RIGHT_2,                IDB_BITMAP_WOLF_WALKING_RIGHT_2,            DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_WOLF_WALKING_RIGHT_3,                IDB_BITMAP_WOLF_WALKING_RIGHT_3,            DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 

    {   SPRITE_WOLF_JUMPING_LEFT_1,                 IDB_BITMAP_WOLF_JUMPING_LEFT_1,             DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_WOLF_JUMPING_LEFT_2,                 IDB_BITMAP_WOLF_JUMPING_LEFT_2,             DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_WOLF_JUMPING_RIGHT_1,                IDB_BITMAP_WOLF_JUMPING_RIGHT_1,            DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_WOLF_JUMPING_RIGHT_2,                IDB_BITMAP_WOLF_JUMPING_RIGHT_2,            DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 

    {   SPRITE_RHINOCEROS_RUNNING_LEFT_1,           IDB_BITMAP_RHINOCEROS_RUNNING_LEFT_1,       DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::MAGENTA), CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_RHINOCEROS_RUNNING_LEFT_2,           IDB_BITMAP_RHINOCEROS_RUNNING_LEFT_2,       DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::MAGENTA), CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_RHINOCEROS_RUNNING_RIGHT_1,          IDB_BITMAP_RHINOCEROS_RUNNING_RIGHT_1,      DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::MAGENTA), CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_RHINOCEROS_RUNNING_RIGHT_2,          IDB_BITMAP_RHINOCEROS_RUNNING_RIGHT_2,      DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::MAGENTA), CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 

    {   SPRITE_HIPPOPOTAMUS_RUNNING_LEFT_1,         IDB_BITMAP_HIPPOPOTAMUS_RUNNING_LEFT_1,     DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW),  CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_HIPPOPOTAMUS_RUNNING_LEFT_2,         IDB_BITMAP_HIPPOPOTAMUS_RUNNING_LEFT_2,     DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW),  CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_HIPPOPOTAMUS_RUNNING_RIGHT_1,        IDB_BITMAP_HIPPOPOTAMUS_RUNNING_RIGHT_1,    DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW),  CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_HIPPOPOTAMUS_RUNNING_RIGHT_2,        IDB_BITMAP_HIPPOPOTAMUS_RUNNING_RIGHT_2,    DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW),  CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_HIPPOPOTAMUS_SLEEPING,               IDB_BITMAP_HIPPOPOTAMUS_SLEEPING,           DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW),  CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 

    {   SPRITE_WARTHOG_RUNNING_LEFT_1,              IDB_BITMAP_WARTHOG_RUNNING_LEFT_1,          DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_WARTHOG_RUNNING_LEFT_2,              IDB_BITMAP_WARTHOG_RUNNING_LEFT_2,          DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_WARTHOG_RUNNING_RIGHT_1,             IDB_BITMAP_WARTHOG_RUNNING_RIGHT_1,         DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_WARTHOG_RUNNING_RIGHT_2,             IDB_BITMAP_WARTHOG_RUNNING_RIGHT_2,         DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_WARTHOG_SLEEPING,                    IDB_BITMAP_WARTHOG_SLEEPING,                DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 

    {   SPRITE_INDIAN_LEFT_1,                       IDB_BITMAP_INDIAN_LEFT_1,                   DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_INDIAN_LEFT_2,                       IDB_BITMAP_INDIAN_LEFT_2,                   DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_INDIAN_LEFT_3,                       IDB_BITMAP_INDIAN_LEFT_3,                   DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_INDIAN_RIGHT_1,                      IDB_BITMAP_INDIAN_RIGHT_1,                  DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_INDIAN_RIGHT_2,                      IDB_BITMAP_INDIAN_RIGHT_2,                  DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_INDIAN_RIGHT_3,                      IDB_BITMAP_INDIAN_RIGHT_3,                  DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 

    {   SPRITE_GUARDIAN_1,                          IDB_BITMAP_GUARDIAN_1,                      DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_GUARDIAN_2,                          IDB_BITMAP_GUARDIAN_2,                      DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 

    {   SPRITE_FIRE_1,                              IDB_BITMAP_FIRE_1,                          DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_FIRE_2,                              IDB_BITMAP_FIRE_2,                          DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_FIRE_3,                              IDB_BITMAP_FIRE_3,                          DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      },
    {   SPRITE_FIRE_4,                              IDB_BITMAP_FIRE_4,                          DRAWING_ELEMENT_BOSS_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 

    {   SPRITE_NASTY_ALIVE_1,                       IDB_BITMAP_NASTY_ALIVE_1,                   DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_NASTY_ALIVE_2,                       IDB_BITMAP_NASTY_ALIVE_2,                   DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_NASTY_ALIVE_3,                       IDB_BITMAP_NASTY_ALIVE_3,                   DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_NASTY_ALIVE_4,                       IDB_BITMAP_NASTY_ALIVE_4,                   DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_NASTY_ALIVE_5,                       IDB_BITMAP_NASTY_ALIVE_5,                   DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_NASTY_ALIVE_6,                       IDB_BITMAP_NASTY_ALIVE_6,                   DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_EMPTY,            }, 

    {   SPRITE_NASTY_DEAD_1,                        IDB_BITMAP_NASTY_DEAD_1,                    DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_NASTY_DEAD_2,                        IDB_BITMAP_NASTY_DEAD_2,                    DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_NASTY_DEAD_3,                        IDB_BITMAP_NASTY_DEAD_3,                    DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_NASTY_DEAD_4,                        IDB_BITMAP_NASTY_DEAD_4,                    DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_EMPTY,            }, 

    {   SPRITE_SPIDER_LEFT_1,                       IDB_BITMAP_SPIDER_LEFT_1,                   DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_SPIDER_LEFT_2,                       IDB_BITMAP_SPIDER_LEFT_2,                   DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_SPIDER_RIGHT_1,                      IDB_BITMAP_SPIDER_RIGHT_1,                  DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_SPIDER_RIGHT_2,                      IDB_BITMAP_SPIDER_RIGHT_2,                  DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 

    {   SPRITE_SCORPION_LEFT_1,                     IDB_BITMAP_SCORPION_LEFT_1,                 DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_SCORPION_LEFT_2,                     IDB_BITMAP_SCORPION_LEFT_2,                 DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_SCORPION_RIGHT_1,                    IDB_BITMAP_SCORPION_RIGHT_1,                DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_SCORPION_RIGHT_2,                    IDB_BITMAP_SCORPION_RIGHT_2,                DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 

    {   SPRITE_BAT_LEFT_1,                          IDB_BITMAP_BAT_LEFT_1,                      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_BAT_LEFT_2,                          IDB_BITMAP_BAT_LEFT_2,                      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_BAT_RIGHT_1,                         IDB_BITMAP_BAT_RIGHT_1,                     DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_BAT_RIGHT_2,                         IDB_BITMAP_BAT_RIGHT_2,                     DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 

    {   SPRITE_PARROT_LEFT_1,                       IDB_BITMAP_PARROT_LEFT_1,                   DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_PARROT_LEFT_2,                       IDB_BITMAP_PARROT_LEFT_2,                   DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_PARROT_RIGHT_1,                      IDB_BITMAP_PARROT_RIGHT_1,                  DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_PARROT_RIGHT_2,                      IDB_BITMAP_PARROT_RIGHT_2,                  DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 

    {   SPRITE_MONKEY_LEFT_1,                       IDB_BITMAP_MONKEY_LEFT_1,                   DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_MONKEY_LEFT_2,                       IDB_BITMAP_MONKEY_LEFT_2,                   DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_MONKEY_RIGHT_1,                      IDB_BITMAP_MONKEY_RIGHT_1,                  DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_MONKEY_RIGHT_2,                      IDB_BITMAP_MONKEY_RIGHT_2,                  DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    
    {   SPRITE_LIZARD_LEFT_1,                       IDB_BITMAP_LIZARD_LEFT_1,                   DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_LIZARD_LEFT_2,                       IDB_BITMAP_LIZARD_LEFT_2,                   DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_LIZARD_RIGHT_1,                      IDB_BITMAP_LIZARD_RIGHT_1,                  DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_LIZARD_RIGHT_2,                      IDB_BITMAP_LIZARD_RIGHT_2,                  DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    
    {   SPRITE_SNAKE_LEFT_1,                        IDB_BITMAP_SNAKE_LEFT_1,                    DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_SNAKE_LEFT_2,                        IDB_BITMAP_SNAKE_LEFT_2,                    DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_SNAKE_RIGHT_1,                       IDB_BITMAP_SNAKE_RIGHT_1,                   DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_SNAKE_RIGHT_2,                       IDB_BITMAP_SNAKE_RIGHT_2,                   DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 

    {   SPRITE_RAT_LEFT_1,                          IDB_BITMAP_RAT_LEFT_1,                      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_RAT_LEFT_2,                          IDB_BITMAP_RAT_LEFT_2,                      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_RAT_RIGHT_1,                         IDB_BITMAP_RAT_RIGHT_1,                     DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_RAT_RIGHT_2,                         IDB_BITMAP_RAT_RIGHT_2,                     DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    
    {   SPRITE_BIRD_LEFT_1,                         IDB_BITMAP_BIRD_LEFT_1,                     DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_BIRD_LEFT_2,                         IDB_BITMAP_BIRD_LEFT_2,                     DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_BIRD_RIGHT_1,                        IDB_BITMAP_BIRD_RIGHT_1,                    DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_BIRD_RIGHT_2,                        IDB_BITMAP_BIRD_RIGHT_2,                    DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    
    {   SPRITE_FLY_LEFT_1,                          IDB_BITMAP_FLY_LEFT_1,                      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_FLY_LEFT_2,                          IDB_BITMAP_FLY_LEFT_2,                      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_FLY_RIGHT_1,                         IDB_BITMAP_FLY_RIGHT_1,                     DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_FLY_RIGHT_2,                         IDB_BITMAP_FLY_RIGHT_2,                     DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    
    {   SPRITE_FROG_LEFT_1,                         IDB_BITMAP_FROG_LEFT_1,                     DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_FROG_LEFT_2,                         IDB_BITMAP_FROG_LEFT_2,                     DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_FROG_RIGHT_1,                        IDB_BITMAP_FROG_RIGHT_1,                    DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_FROG_RIGHT_2,                        IDB_BITMAP_FROG_RIGHT_2,                    DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 

    {   SPRITE_BUG_LEFT_1,                          IDB_BITMAP_BUG_LEFT_1,                      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_BUG_LEFT_2,                          IDB_BITMAP_BUG_LEFT_2,                      DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_BUG_RIGHT_1,                         IDB_BITMAP_BUG_RIGHT_1,                     DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_BUG_RIGHT_2,                         IDB_BITMAP_BUG_RIGHT_2,                     DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 

    {   SPRITE_SKUNK_LEFT_1,                        IDB_BITMAP_SKUNK_LEFT_1,                    DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_SKUNK_LEFT_2,                        IDB_BITMAP_SKUNK_LEFT_2,                    DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_SKUNK_RIGHT_1,                       IDB_BITMAP_SKUNK_RIGHT_1,                   DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_SKUNK_RIGHT_2,                       IDB_BITMAP_SKUNK_RIGHT_2,                   DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 

    {   SPRITE_EARWIG_LEFT_1,                       IDB_BITMAP_EARWIG_LEFT_1,                   DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_EARWIG_LEFT_2,                       IDB_BITMAP_EARWIG_LEFT_2,                   DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_EARWIG_RIGHT_1,                      IDB_BITMAP_EARWIG_RIGHT_1,                  DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_EARWIG_RIGHT_2,                      IDB_BITMAP_EARWIG_RIGHT_2,                  DRAWING_ELEMENT_NASTY_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     },
};


FolioStatus CreateSpriteGraphics (FolioHandle           dcHandle, 
                                  FolioHandle           instanceHandle,
                                  SpriteGraphicsMapPtr  &spriteGraphicsMap)
{
    FolioStatus status = ERR_SUCCESS;

    // Create the sprite graphics map.

    spriteGraphicsMap.reset (new SpriteGraphicsMapPtr::element_type);

    // Build the sprite graphics map. 

    for (UInt32 index = 0; 
         (status == ERR_SUCCESS) && (index < (sizeof (g_spriteGraphicAttributesTable) / sizeof (SpriteGraphicAttributes)));
         ++index)
    {              
        // Create a sprite graphic.

        Folio::Core::Game::SpriteGraphic    spriteGraphic(new Folio::Core::Game::SpriteGraphic::element_type);

        status = spriteGraphic->Create (dcHandle,
                                        instanceHandle,
                                        g_spriteGraphicAttributesTable [index].m_drawingElementId,
                                        g_spriteGraphicAttributesTable [index].m_bitmapResourceId,
                                        Folio::Core::Game::ZxSpectrum::GetBitmapChangeColour (),
                                        Folio::Core::Game::ZxSpectrum::MapInkColour (g_spriteGraphicAttributesTable [index].m_colour),
                                        true,   // Require a masked bitmap drawing element.
                                        g_spriteGraphicAttributesTable [index].m_collisionGridCellValue);

        if (status == ERR_SUCCESS)
        {
            // Store the sprite graphic in the sprite graphics map.

            spriteGraphicsMap->insert (SpriteGraphicsMap::value_type(g_spriteGraphicAttributesTable [index].m_spriteId, 
                                                                     spriteGraphic));
        } // Endif.
       
    } // Endfor.

    if (status != ERR_SUCCESS)
    {
        spriteGraphicsMap->clear ();
    } // Endif.
   
    return (status);
} // Endproc.


FolioStatus FindSpriteGraphic (SPRITE_ID                                spriteId,
                               const SpriteGraphicsMapPtr               &spriteGraphicsMap,
                               Folio::Core::Game::SpriteGraphic         &spriteGraphic,
                               Folio::Core::Game::ZxSpectrum::COLOUR    spriteColour)
{
    FolioStatus status = ERR_SUCCESS;

    // Find the sprite graphic in the sprite graphics map.

    SpriteGraphicsMap::const_iterator   spriteGraphicsMapItr = spriteGraphicsMap->find (spriteId);

    if (spriteGraphicsMapItr != spriteGraphicsMap->end ())
    {
        // Get the sprite graphic.

        spriteGraphic = spriteGraphicsMapItr->second;

        if (spriteColour != Folio::Core::Game::ZxSpectrum::UNDEFINED)
        {
            // Change the colour of the sprite graphic.

            status = spriteGraphic->ChangeColour (Folio::Core::Game::ZxSpectrum::MapInkColour (spriteColour));
        } // Endif.

    } // Endif.        

    else
    {
        // Didn't find the sprite graphic in the sprite graphics map.

        status = ERR_NOT_FOUND;
    } // Endelse.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
