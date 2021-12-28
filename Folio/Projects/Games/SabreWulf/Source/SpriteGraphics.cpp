// "Home-made" includes.
#include    "StdAfx.h"
#include    "CollisionGrid.h"
#include    "DrawingElementIds.h"
#include    "Globals.h"
#include    "ResourceOwnerIds.h"
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
    SPRITE_ID                                           m_spriteId;                         // The identifier of the sprite.
    UInt32                                              m_maxResourceGraphicsCacheCount;    // The maximum number required in the resource graphics cache.
    Folio::Core::Game::DrawingElement::DrawingElementId m_drawingElementId;                 // The drawing element identifier of the sprite.
    Folio::Core::Game::ZxSpectrum::COLOUR               m_colour;                           // The colour of the sprite.
    CollisionGrid::CellValue                            m_collisionGridCellValue;           // The collision grid cell value of the sprite.
 }; // Endstruct.

// Sprite graphic attributes table.
static  const   SpriteGraphicAttributes   g_spriteGraphicAttributesTable [] =
{
//      m_spriteId                                  m_maxResourceGraphicsCacheCount         m_drawingElementId                                                      m_colour                                                                                        m_collisionGridCellValue
    {   SPRITE_BOX,                                 MAX_OBJECT_SPRITES_PER_SCREEN,          Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_OBJECT_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, }, 
    {   SPRITE_RING,                                MAX_OBJECT_SPRITES_PER_SCREEN,          Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_OBJECT_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, }, 
    {   SPRITE_APPLE,                               MAX_OBJECT_SPRITES_PER_SCREEN,          Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_OBJECT_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, }, 
    {   SPRITE_CHARM,                               MAX_OBJECT_SPRITES_PER_SCREEN,          Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_OBJECT_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, }, 
    {   SPRITE_AMULET,                              MAX_OBJECT_SPRITES_PER_SCREEN,          Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_OBJECT_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, },
    {   SPRITE_EXTRA_LIFE,                          MAX_OBJECT_SPRITES_PER_SCREEN,          Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_OBJECT_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, },  
    {   SPRITE_MONEY_BAG,                           MAX_OBJECT_SPRITES_PER_SCREEN,          Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_OBJECT_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, }, 
    {   SPRITE_SPEAR,                               MAX_OBJECT_SPRITES_PER_SCREEN,          Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_OBJECT_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, }, 
    {   SPRITE_CHALICE,                             MAX_OBJECT_SPRITES_PER_SCREEN,          Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_OBJECT_SPRITE,       Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, }, 
    {   SPRITE_AMULET_PIECE_TOP_LEFT,               1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_OBJECT_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW),  CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, }, 
    {   SPRITE_AMULET_PIECE_TOP_RIGHT,              1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_OBJECT_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW),  CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, }, 
    {   SPRITE_AMULET_PIECE_BOTTOM_LEFT,            1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_OBJECT_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW),  CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, }, 
    {   SPRITE_AMULET_PIECE_BOTTOM_RIGHT,           1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_OBJECT_SPRITE,       Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW),  CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM, }, 
    
    {   SPRITE_ORCHID_1,                            2,                                      DRAWING_ELEMENT_ORCHID_SPRITE,                                          Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_ITEM,             }, 
    {   SPRITE_ORCHID_2,                            2,                                      DRAWING_ELEMENT_ORCHID_SPRITE,                                          Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_ITEM,             }, 
    {   SPRITE_ORCHID_3,                            2,                                      DRAWING_ELEMENT_ORCHID_SPRITE,                                          Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_ITEM,             }, 
    {   SPRITE_ORCHID_4,                            2,                                      DRAWING_ELEMENT_ORCHID_SPRITE,                                          Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_ITEM,             }, 
    {   SPRITE_ORCHID_5,                            2,                                      DRAWING_ELEMENT_ORCHID_SPRITE,                                          Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_ITEM,             }, 
    {   SPRITE_ORCHID_6,                            2,                                      DRAWING_ELEMENT_ORCHID_SPRITE,                                          Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_ITEM,             }, 
    {   SPRITE_ORCHID_7,                            2,                                      DRAWING_ELEMENT_ORCHID_SPRITE,                                          Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_ITEM,             },  
    {   SPRITE_ORCHID_8,                            2,                                      DRAWING_ELEMENT_ORCHID_SPRITE,                                          Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_ITEM,             },  

    {   SPRITE_SABRE_MAN_UP,                        2,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,  Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_WALKING_UP_1,              1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,  Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_WALKING_UP_2,              1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,  Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_DOWN,                      2,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,  Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_WALKING_DOWN_1,            1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,  Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_WALKING_DOWN_2,            1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,  Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_LEFT,                      2,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,  Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_WALKING_LEFT_1,            1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,  Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_WALKING_LEFT_2,            1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,  Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_RIGHT,                     2,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,  Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_WALKING_RIGHT_1,           1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,  Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_WALKING_RIGHT_2,           1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,  Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            },

    {   SPRITE_SABRE_MAN_SWORD_LEFT_1,              1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,  Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_SWORD_LEFT_2,              2,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,  Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_SWORD_LEFT_3,              1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,  Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_SWORD_LEFT_4,              2,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,  Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_SWORD_LEFT_5,              1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,  Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_SWORD_LEFT_6,              1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,  Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_SWORD_RIGHT_1,             1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,  Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_SWORD_RIGHT_2,             2,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,  Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_SWORD_RIGHT_3,             1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,  Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_SWORD_RIGHT_4,             2,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,  Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_SWORD_RIGHT_5,             1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,  Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_SWORD_RIGHT_6,             1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,  Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    
    {   SPRITE_SABRE_MAN_FALLING_LEFT,              1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,  Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_FALLING_RIGHT,             1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,  Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 

    {   SPRITE_SABRE_MAN_SITTING_LEFT,              6,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,  Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_SITTING_RIGHT,             6,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,  Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 

    {   SPRITE_SABRE_MAN_GAME_OVER_LEFT,            1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,  Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_SABRE_MAN_GAME_OVER_RIGHT,           1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,  Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE),   CollisionGrid::CELL_VALUE_EMPTY,            }, 

    {   SPRITE_WOLF_WALKING_LEFT_1,                 1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_WOLF_WALKING_LEFT_2,                 1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_WOLF_WALKING_LEFT_3,                 1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_WOLF_WALKING_RIGHT_1,                1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_WOLF_WALKING_RIGHT_2,                1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_WOLF_WALKING_RIGHT_3,                1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 

    {   SPRITE_WOLF_JUMPING_LEFT_1,                 1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_WOLF_JUMPING_LEFT_2,                 1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_WOLF_JUMPING_RIGHT_1,                1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_WOLF_JUMPING_RIGHT_2,                1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN),    CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 

    {   SPRITE_RHINOCEROS_RUNNING_LEFT_1,           1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::MAGENTA), CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_RHINOCEROS_RUNNING_LEFT_2,           1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::MAGENTA), CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_RHINOCEROS_RUNNING_RIGHT_1,          1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::MAGENTA), CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_RHINOCEROS_RUNNING_RIGHT_2,          1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::MAGENTA), CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 

    {   SPRITE_HIPPOPOTAMUS_RUNNING_LEFT_1,         1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW),  CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_HIPPOPOTAMUS_RUNNING_LEFT_2,         1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW),  CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_HIPPOPOTAMUS_RUNNING_RIGHT_1,        1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW),  CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_HIPPOPOTAMUS_RUNNING_RIGHT_2,        1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW),  CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_HIPPOPOTAMUS_SLEEPING,               1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW),  CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 

    {   SPRITE_WARTHOG_RUNNING_LEFT_1,              1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_WARTHOG_RUNNING_LEFT_2,              1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_WARTHOG_RUNNING_RIGHT_1,             1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_WARTHOG_RUNNING_RIGHT_2,             1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_WARTHOG_SLEEPING,                    1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 

    {   SPRITE_NATIVE_LEFT_1,                       MAX_NATIVE_SPRITE_DRAWING_ELEMENTS,     Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_NATIVE_LEFT_2,                       MAX_NATIVE_SPRITE_DRAWING_ELEMENTS,     Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_NATIVE_LEFT_3,                       MAX_NATIVE_SPRITE_DRAWING_ELEMENTS,     Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_NATIVE_RIGHT_1,                      MAX_NATIVE_SPRITE_DRAWING_ELEMENTS,     Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_NATIVE_RIGHT_2,                      MAX_NATIVE_SPRITE_DRAWING_ELEMENTS,     Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_NATIVE_RIGHT_3,                      MAX_NATIVE_SPRITE_DRAWING_ELEMENTS,     Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 

    {   SPRITE_GUARDIAN_1,                          1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_GUARDIAN_2,                          1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 

    {   SPRITE_FIRE_1,                              1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_FIRE_2,                              1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 
    {   SPRITE_FIRE_3,                              1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      },
    {   SPRITE_FIRE_4,                              1,                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,         Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_BOSS_SPRITE,      }, 

    {   SPRITE_NASTY_ALIVE_1,                       MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_NASTY_ALIVE_2,                       MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_NASTY_ALIVE_3,                       MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_NASTY_ALIVE_4,                       MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_NASTY_ALIVE_5,                       MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_NASTY_ALIVE_6,                       MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_EMPTY,            }, 

    {   SPRITE_NASTY_DEAD_1,                        2 * MAX_NASTY_SPRITE_DRAWING_ELEMENTS,  Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_NASTY_DEAD_2,                        2 * MAX_NASTY_SPRITE_DRAWING_ELEMENTS,  Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_NASTY_DEAD_3,                        MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_EMPTY,            }, 
    {   SPRITE_NASTY_DEAD_4,                        MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_EMPTY,            }, 

    {   SPRITE_SPIDER_LEFT_1,                       MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_SPIDER_LEFT_2,                       MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_SPIDER_RIGHT_1,                      MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_SPIDER_RIGHT_2,                      MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 

    {   SPRITE_SCORPION_LEFT_1,                     MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_SCORPION_LEFT_2,                     MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_SCORPION_RIGHT_1,                    MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_SCORPION_RIGHT_2,                    MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 

    {   SPRITE_BAT_LEFT_1,                          MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_BAT_LEFT_2,                          MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_BAT_RIGHT_1,                         MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_BAT_RIGHT_2,                         MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 

    {   SPRITE_PARROT_LEFT_1,                       MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_PARROT_LEFT_2,                       MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_PARROT_RIGHT_1,                      MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_PARROT_RIGHT_2,                      MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 

    {   SPRITE_MONKEY_LEFT_1,                       MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_MONKEY_LEFT_2,                       MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_MONKEY_RIGHT_1,                      MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_MONKEY_RIGHT_2,                      MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    
    {   SPRITE_LIZARD_LEFT_1,                       MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_LIZARD_LEFT_2,                       MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_LIZARD_RIGHT_1,                      MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_LIZARD_RIGHT_2,                      MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    
    {   SPRITE_SNAKE_LEFT_1,                        MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_SNAKE_LEFT_2,                        MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_SNAKE_RIGHT_1,                       MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_SNAKE_RIGHT_2,                       MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 

    {   SPRITE_RAT_LEFT_1,                          MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_RAT_LEFT_2,                          MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_RAT_RIGHT_1,                         MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_RAT_RIGHT_2,                         MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    
    {   SPRITE_BIRD_LEFT_1,                         MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_BIRD_LEFT_2,                         MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_BIRD_RIGHT_1,                        MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_BIRD_RIGHT_2,                        MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    
    {   SPRITE_FLY_LEFT_1,                          MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_FLY_LEFT_2,                          MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_FLY_RIGHT_1,                         MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_FLY_RIGHT_2,                         MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    
    {   SPRITE_FROG_LEFT_1,                         MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_FROG_LEFT_2,                         MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_FROG_RIGHT_1,                        MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_FROG_RIGHT_2,                        MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 

    {   SPRITE_BUG_LEFT_1,                          MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_BUG_LEFT_2,                          MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_BUG_RIGHT_1,                         MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_BUG_RIGHT_2,                         MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 

    {   SPRITE_SKUNK_LEFT_1,                        MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_SKUNK_LEFT_2,                        MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_SKUNK_RIGHT_1,                       MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_SKUNK_RIGHT_2,                       MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 

    {   SPRITE_EARWIG_LEFT_1,                       MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_EARWIG_LEFT_2,                       MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_EARWIG_RIGHT_1,                      MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     }, 
    {   SPRITE_EARWIG_RIGHT_2,                      MAX_NASTY_SPRITE_DRAWING_ELEMENTS,      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,        Folio::Core::Game::ZxSpectrum::UNDEFINED,                                                       CollisionGrid::CELL_VALUE_NASTY_SPRITE,     },
};


FolioStatus CreateSpriteGraphics (FolioHandle                               instanceHandle,
                                  Folio::Core::Game::ResourceGraphicsCache& resourceGraphicsCache)
{
    FolioStatus status = ERR_SUCCESS;

    // Add the sprite graphics into the resource graphics cache. 

    for (UInt32 index = 0; 
         (status == ERR_SUCCESS) && (index < (sizeof (g_spriteGraphicAttributesTable) / sizeof (SpriteGraphicAttributes)));
         ++index)
    {          
        for (UInt32 resourceGraphicsCacheCount = 0; 
             (status == ERR_SUCCESS) && (resourceGraphicsCacheCount < g_spriteGraphicAttributesTable [index].m_maxResourceGraphicsCacheCount);
             ++resourceGraphicsCacheCount)
        {            
            // Create a sprite graphic.

            Folio::Core::Game::SpriteGraphic    spriteGraphic(new Folio::Core::Game::SpriteGraphic::element_type);

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

                resourceGraphicsCache.Add (spriteGraphic);
            } // Endif.
       
        } // Endfor.

    } // Endfor.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
