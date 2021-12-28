// "Home-made" includes.
#include    "StdAfx.h"
#include    "Globals.h"
#include    "Screen.h"
#include    "StaticSprite.h"

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Static sprite attributes.
struct StaticSpriteAttributes
{
    STATIC_SPRITE_ID                        m_staticSpriteId;       // The identifier of the static sprite.
    Int32                                   m_initialScreenNumber;  // The initial screen number of the static sprite.
    Int32                                   m_initialScreenXLeft;   // The initial screen X left (in pixels) of the static sprite.
    Int32                                   m_initialScreenYBottom; // The initial screen Y bottom (in pixels) of the static sprite.
    Folio::Core::Game::ZxSpectrum::COLOUR   m_staticSpriteColour;   // The colour of the static sprite.
    UInt32                                  m_staticSpriteFlags;    // The flags of the static sprite.
}; // Endstruct.

// Static sprite attributes table.
static  const   StaticSpriteAttributes  g_staticSpriteAttributesTable [] =
{
//      m_staticSpriteId                    m_initialScreenNumber   m_initialScreenXLeft    m_initialScreenYBottom      m_staticSpriteColour                                                                m_staticSpriteFlags
    {   STATIC_SPRITE_ACG_KEY_LEFT,           0,                     88,                     88,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,      StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_ACG_KEY_MIDDLE,         0,                     88,                     88,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,      StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_ACG_KEY_RIGHT,          0,                     88,                     88,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,      StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_KEY,                    0,                    112,                     96,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_KEY,                    0,                    128,                     64,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_KEY,                    0,                     88,                     88,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,        StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_KEY,                    0,                     48,                    135,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,      StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_LEAF,                   9,                     64,                     64,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CRUCIFIX,               5,                     64,                    112,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,      StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_SPANNER,               48,                     64,                    112,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,        StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_MEDICINE_BOTTLE,       59,                     96,                     96,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_GOBSTOPPER,            72,                    112,                    112,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,        StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BROKEN,               100,                    128,                    128,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,      StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_ROPE,                 107,                     64,                     64,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,        StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_ARM,                   19,                     80,                     80,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_AMULET,               132,                     96,                     64,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_MONEY_BAG,             31,                    112,                    112,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_SKULL,                 73,                     80,                     64,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CAN,                   39,                     87,                    103,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CAN,                  127,                     64,                     64,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,      StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CAN,                   30,                     80,                     87,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,      StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CAN,                   12,                     96,                     96,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CAN,                  103,                     87,                     64,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CAN,                   65,                     87,                    103,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CANDY_BAR,            117,                     48,                     64,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CANDY_BAR,            131,                     48,                     64,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,      StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CANDY_BAR,             12,                     96,                    112,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CANDY_BAR,            104,                     87,                     64,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CANDY_BAR,             69,                     87,                     70,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,        StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CANDY_BAR,             70,                     67,                    123,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,        StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_HAM,                  134,                     71,                     96,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_HAM,                  110,                     96,                    119,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_HAM,                  125,                     87,                    103,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_HAM,                  106,                     48,                    103,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_HAM,                   62,                     67,                    123,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_HAM,                   53,                     87,                    103,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_LOLLIPOP,              43,                     64,                    128,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,      StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_LOLLIPOP,             138,                     87,                    103,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,        StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_LOLLIPOP,               9,                    128,                    144,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_LOLLIPOP,             112,                    128,                    144,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_LOLLIPOP,             116,                     87,                    135,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_LOLLIPOP,              51,                     87,                    103,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,        StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_ICE_CREAM_CONE,       120,                     55,                     55,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_ICE_CREAM_CONE,       138,                    127,                    127,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_ICE_CREAM_CONE,        11,                     87,                    103,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,      StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_ICE_CREAM_CONE,       101,                     87,                    135,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,      StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_ICE_CREAM_CONE,        83,                     67,                    123,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_ICE_CREAM_CONE,        76,                    107,                    123,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,      StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOWL,                 123,                     80,                     96,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,        StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOWL,                 135,                     87,                    103,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,        StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOWL,                  13,                     48,                    103,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOWL,                 102,                     67,                    135,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOWL,                  83,                    107,                    123,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOWL,                  79,                     87,                    103,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_APPLE,                126,                     55,                    128,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_APPLE,                140,                     87,                    103,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_APPLE,                112,                     48,                    144,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_APPLE,                102,                    107,                    135,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_APPLE,                 60,                     67,                    123,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_APPLE,                 57,                     67,                    123,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOTTLE,               126,                    135,                    128,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOTTLE,                36,                     96,                    112,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOTTLE,               112,                     87,                    144,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOTTLE,                18,                     87,                     64,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOTTLE,                94,                     87,                    103,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOTTLE,                29,                     48,                    103,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CAN,                   23,                     64,                     64,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CAN,                  115,                     48,                    103,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CAN,                    7,                     87,                    103,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CAN,                    2,                     87,                    103,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CANDY_BAR,             15,                     87,                    103,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CANDY_BAR,             58,                     48,                     72,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CANDY_BAR,             65,                    128,                    103,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CANDY_BAR,            133,                     67,                    123,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_HAM,                  108,                     87,                     71,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_HAM,                   58,                     87,                     72,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_HAM,                  105,                     48,                     64,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_HAM,                  128,                     48,                     64,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_LOLLIPOP,               4,                     87,                    103,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_LOLLIPOP,              75,                     48,                    136,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_LOLLIPOP,              17,                     87,                    103,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,      StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_LOLLIPOP,             128,                     87 ,                    64,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_ICE_CREAM_CONE,       105,                     48,                    103,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,      StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_ICE_CREAM_CONE,        53,                     87,                    144,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,      StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_ICE_CREAM_CONE,       105,                     48,                    144,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,      StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_ICE_CREAM_CONE,       128,                    128,                    128,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOWL,                  87,                     87,                     64,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,      StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOWL,                  53,                     87,                     64,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,      StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOWL,                  37,                    107,                    123,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOWL,                  27,                     87,                    103,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_APPLE,                 88,                     87,                     64,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_APPLE,                 78,                    103,                     64,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_APPLE,                 55,                     87,                    103,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,      StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_APPLE,                133,                    107,                    123,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOTTLE,                91,                     87,                    103,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOTTLE,                78,                     64,                    103,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOTTLE,                73,                     87,                    103,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOTTLE,                40,                     87,                    103,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_MUSHROOM,              80,                     87,                     64,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE, },
    {   STATIC_SPRITE_MUSHROOM,              67,                    107,                     84,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE, },
    {   STATIC_SPRITE_MUSHROOM,              64,                     67,                    123,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE, },
    {   STATIC_SPRITE_MUSHROOM,             143,                     87,                    143,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE, },
    {   STATIC_SPRITE_MUSHROOM,             143,                     67,                    123,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE, },
    {   STATIC_SPRITE_MUSHROOM,             143,                    107,                    123,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE, },
    {   STATIC_SPRITE_MUSHROOM,              69,                    128,                    103,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE, },
    {   STATIC_SPRITE_MUSHROOM,              56,                    107,                     84,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE, },
    {   STATIC_SPRITE_MUSHROOM,             116,                     48,                     64,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE, },
    {   STATIC_SPRITE_MUSHROOM,             116,                     48,                    136,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE, },
    {   STATIC_SPRITE_MUSHROOM,             116,                    120,                    136,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE, },
    {   STATIC_SPRITE_MUSHROOM,             116,                    128,                     64,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE, },
    {   STATIC_SPRITE_MUSHROOM,              84,                     87,                     64,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE, },
    {   STATIC_SPRITE_MUSHROOM,              59,                     67,                    123,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE, },
    {   STATIC_SPRITE_MUSHROOM,              59,                    107,                    123,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE, },
    {   STATIC_SPRITE_MUSHROOM,              83,                    128,                     64,                        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,         StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE, },
};


// Static sprite graphic characteristics.
static  const   Folio::Core::Game::SpriteGraphicCharacteristicsList<STATIC_SPRITE_ID, SPRITE_ID>    g_staticSpriteGraphicCharacteristics =
{
//      m_spriteId                          m_direction                         m_spriteGraphicIdsList
    {   STATIC_SPRITE_LEAF,                 Folio::Core::Game::NO_DIRECTION,    {   SPRITE_LEAF,            },  },  
    {   STATIC_SPRITE_KEY,                  Folio::Core::Game::NO_DIRECTION,    {   SPRITE_KEY,             },  },
    {   STATIC_SPRITE_BOTTLE,               Folio::Core::Game::NO_DIRECTION,    {   SPRITE_BOTTLE,          },  },
    {   STATIC_SPRITE_MEDICINE_BOTTLE,      Folio::Core::Game::NO_DIRECTION,    {   SPRITE_MEDICINE_BOTTLE, },  },
    {   STATIC_SPRITE_BROKEN,               Folio::Core::Game::NO_DIRECTION,    {   SPRITE_BROKEN,          },  },
    {   STATIC_SPRITE_ROPE,                 Folio::Core::Game::NO_DIRECTION,    {   SPRITE_ROPE,            },  },
    {   STATIC_SPRITE_ARM,                  Folio::Core::Game::NO_DIRECTION,    {   SPRITE_ARM,             },  },
    {   STATIC_SPRITE_BOWL,                 Folio::Core::Game::NO_DIRECTION,    {   SPRITE_BOWL,            },  },
    {   STATIC_SPRITE_APPLE,                Folio::Core::Game::NO_DIRECTION,    {   SPRITE_APPLE,           },  },
    {   STATIC_SPRITE_CANDY_BAR,            Folio::Core::Game::NO_DIRECTION,    {   SPRITE_CANDY_BAR,       },  },
    {   STATIC_SPRITE_HAM,                  Folio::Core::Game::NO_DIRECTION,    {   SPRITE_HAM,             },  },
    {   STATIC_SPRITE_LOLLIPOP,             Folio::Core::Game::NO_DIRECTION,    {   SPRITE_LOLLIPOP,        },  },
    {   STATIC_SPRITE_MONEY_BAG,            Folio::Core::Game::NO_DIRECTION,    {   SPRITE_MONEY_BAG,       },  },
    {   STATIC_SPRITE_GOBSTOPPER,           Folio::Core::Game::NO_DIRECTION,    {   SPRITE_GOBSTOPPER,      },  },
    {   STATIC_SPRITE_AMULET,               Folio::Core::Game::NO_DIRECTION,    {   SPRITE_AMULET,          },  },
    {   STATIC_SPRITE_CAN,                  Folio::Core::Game::NO_DIRECTION,    {   SPRITE_CAN,             },  },
    {   STATIC_SPRITE_ICE_CREAM_CONE,       Folio::Core::Game::NO_DIRECTION,    {   SPRITE_ICE_CREAM_CONE,  },  },
    {   STATIC_SPRITE_CRUCIFIX,             Folio::Core::Game::NO_DIRECTION,    {   SPRITE_CRUCIFIX,        },  },
    {   STATIC_SPRITE_SKULL,                Folio::Core::Game::NO_DIRECTION,    {   SPRITE_SKULL,           },  },
    {   STATIC_SPRITE_SPANNER,              Folio::Core::Game::NO_DIRECTION,    {   SPRITE_SPANNER,         },  },
    {   STATIC_SPRITE_ACG_KEY_LEFT,         Folio::Core::Game::NO_DIRECTION,    {   SPRITE_ACG_KEY_LEFT,    },  },
    {   STATIC_SPRITE_ACG_KEY_MIDDLE,       Folio::Core::Game::NO_DIRECTION,    {   SPRITE_ACG_KEY_MIDDLE,  },  },
    {   STATIC_SPRITE_ACG_KEY_RIGHT,        Folio::Core::Game::NO_DIRECTION,    {   SPRITE_ACG_KEY_RIGHT,   },  },
    {   STATIC_SPRITE_MUSHROOM,             Folio::Core::Game::NO_DIRECTION,    {   SPRITE_MUSHROOM,        },  },
    {   STATIC_SPRITE_GRAVESTONE,           Folio::Core::Game::NO_DIRECTION,    {   SPRITE_GRAVESTONE,      },  },
};


// Static sprite location.
struct StaticSpriteLocation
{ 
    UInt32  m_acgKeyLeft;
    UInt32  m_acgKeyMiddle;
    UInt32  m_acgKeyRight;
    UInt32  m_redKey;
    UInt32  m_greenKey;
    UInt32  m_cyanKey;
    UInt32  m_yellowKey; 
 }; // Endstruct.

// Static sprite locations table.
static  const   StaticSpriteLocation    g_staticSpriteLocationsTable [] =
{
//      m_acgKeyLeft    m_acgKeyMiddle  m_acgKeyRight   m_redKey    m_greenKey  m_cyanKey   m_yellowKey 
    {   129,             69,            124,             23,          5,         51,        102,    },
    {   133,             73,             43,             19,          6,        145,        102,    },
    {   106,             59,            124,              9,          7,         57,        102,    },
    {   105,            113,             43,             13,        109,         51,        102,    },
    {   103,            133,            124,            137,         37,        145,        102,    },
    {   104,            127,             43,            135,         36,         57,        102,    },
    {    77,            115,            124,            128,         35,         51,        102,    },
    {    23,             16,             43,            133,         34,        145,        102,    },
};


// Static sprite locations table index.
static  UInt32  g_staticSpriteLocationTableIndex = 0;


static  UInt32  CalculateStaticSpriteLocationTableIndex ()
{
    g_staticSpriteLocationTableIndex = Folio::Core::Util::Random::GetRandomNumber ((sizeof (g_staticSpriteLocationsTable) / sizeof (StaticSpriteLocation)) - 1);

    return (g_staticSpriteLocationTableIndex);
} // Endproc.


StaticSprite::StaticSprite ()
:   m_staticSpriteId(STATIC_SPRITE_UNDEFINED),
    m_screenNumber(Folio::Core::Game::ZxSpectrum::UNDEFINED),
    m_screenXLeft(Folio::Core::Game::ZxSpectrum::UNDEFINED),
    m_screenYTop(Folio::Core::Game::ZxSpectrum::UNDEFINED),
    m_staticSpriteColour(Folio::Core::Game::ZxSpectrum::UNDEFINED),
    m_staticSpriteFlags(FLAGS_NONE),
    m_colourChangeIndex(FOLIO_INVALID_INDEX)
{
} // Endproc.


StaticSprite::StaticSprite (STATIC_SPRITE_ID                        staticSpriteId,
                            UInt32                                  initialScreenNumber,
                            Int32                                   initialScreenXLeft,
                            Int32                                   initialScreenYBottom,
                            Folio::Core::Game::ZxSpectrum::COLOUR   staticSpriteColour,
                            UInt32                                  staticSpriteFlags)
:   m_staticSpriteId(staticSpriteId),
    m_screenNumber(initialScreenNumber),
    m_screenXLeft(initialScreenXLeft),
    m_screenYTop(initialScreenYBottom), // Need to calculate.
    m_staticSpriteColour(staticSpriteColour),
    m_staticSpriteFlags(staticSpriteFlags),
    m_colourChangeIndex(FOLIO_INVALID_INDEX)
{
} // Endproc.


StaticSprite::~StaticSprite ()
{
} // Endproc.


FolioStatus StaticSprite::Create (FolioHandle                           dcHandle, 
                                  STATIC_SPRITE_ID                      staticSpriteId,
                                  UInt32                                initialScreenNumber,
                                  Int32                                 initialScreenXLeft,
                                  Int32                                 initialScreenYBottom,
                                  Folio::Core::Game::ZxSpectrum::COLOUR staticSpriteColour,
                                  UInt32                                staticSpriteFlags)
{
    // Query the static sprite's graphics.

    Folio::Core::Game::SpriteGraphicAttributesList  spriteGraphicAttributesList;

    FolioStatus status = Folio::Core::Game::QuerySpriteGraphicAttributes<STATIC_SPRITE_ID, SPRITE_ID> (dcHandle,
                                                                                                       g_resourceGraphicsCache,
                                                                                                       Screen::MakeOwnerId (initialScreenNumber),
                                                                                                       Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_STATIC_SPRITE,
                                                                                                       staticSpriteId,
                                                                                                       staticSpriteColour,
                                                                                                       g_staticSpriteGraphicCharacteristics,
                                                                                                       spriteGraphicAttributesList);

    if (status == ERR_SUCCESS)
    {
        // Get the current sprite graphic.

        SpriteGraphic   spriteGraphic(spriteGraphicAttributesList.front ().m_spriteGraphicsList.front ());

        // Calculate the initial screen Y top.

        Int32   initialScreenYTop = Folio::Core::Game::ZxSpectrum::CalculateScreenYTop (initialScreenYBottom, 
                                                                                        spriteGraphic->GetGraphicWidth (),
                                                                                        spriteGraphic->GetGraphicHeight ());

        // Create the static sprite.

        status = Folio::Core::Game::AStaticSprite::Create (dcHandle,
                                                           spriteGraphicAttributesList,
                                                           initialScreenXLeft,
                                                           initialScreenYTop,
                                                           Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE,
                                                           Folio::Core::Game::ZxSpectrum::MapInkColour (staticSpriteColour),
                                                           Folio::Core::Game::NO_DIRECTION,
                                                           &(g_resourceGraphicsCache));

        if (status == ERR_SUCCESS)
        {
            // Static sprite is static.

            SetState (STATE_STATIC);

            // Set the static sprite attributes.

            m_staticSpriteId        = staticSpriteId;
            m_screenNumber          = initialScreenNumber;
            m_screenXLeft           = initialScreenXLeft;
            m_screenYTop            = initialScreenYTop;
            m_staticSpriteColour    = staticSpriteColour;
            m_staticSpriteFlags     = staticSpriteFlags;
        } // Endif.

    } // Endif.
    
    return (status);
} // Endproc.


FolioStatus StaticSprite::Create (FolioHandle dcHandle)
{
    FolioStatus status = ERR_SUCCESS;

    // Has the static sprite already been created?

    if (IsCreated ())
    {
        // Yes. Gain the static sprite's graphic from the resource cache.

        status = GainResourceGraphics (Screen::MakeOwnerId (m_screenNumber));

        if (status == ERR_SUCCESS)
        {
            // Get the mapped sprite colour.

            Gdiplus::ARGB   mappedSpriteColour = Folio::Core::Game::ZxSpectrum::MapInkColour (m_staticSpriteColour);

            // Does the static sprite's colour need to be changed?

            if (mappedSpriteColour != GetCurrentSpriteGraphic ()->GetCurrentChangeableColour ())
            {
                // Yes. Change the static sprite's colour.

                status = ChangeSpriteInkColour (mappedSpriteColour,
                                                true,   // Change the sprite's initialising graphics.
                                                true,   // Change the sprite's terminating graphics.
                                                true);  // Force the colour change.
            } // Endif.

        } // Endif.

    } // Endif.

    else
    {
        status = Create (dcHandle, 
                         m_staticSpriteId,
                         m_screenNumber,
                         m_screenXLeft,
                         m_screenYTop,
                         m_staticSpriteColour,
                         m_staticSpriteFlags);
    } // Endelse.

    return (status);
} // Endproc.


void    StaticSprite::SetScreenNumber (UInt32 screenNumber)
{
    m_screenNumber = screenNumber;
} // Endproc.


UInt32  StaticSprite::GetScreenNumber () const
{
    return (m_screenNumber);
} // Endproc.


STATIC_SPRITE_ID    StaticSprite::GetStaticSpriteId () const
{
    return (m_staticSpriteId);
} // Endproc.


Folio::Core::Game::ZxSpectrum::COLOUR   StaticSprite::GetStaticSpriteColour () const
{
    return (m_staticSpriteColour);
} // Endproc.


UInt32  StaticSprite::GetStaticSpriteFlags () const
{
    return (m_staticSpriteFlags);
} // Endproc.


FolioStatus StaticSprite::ChangeStaticSpriteColour ()
{
    // Colour list type.
    typedef std::vector<Gdiplus::ARGB>  ColourList;

    // The colour list.
    static  const   ColourList  s_colourList =
    {
        {   Folio::Core::Game::ZxSpectrum::MapInkColour (Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED),       },
        {   Folio::Core::Game::ZxSpectrum::MapInkColour (Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA),   },
        {   Folio::Core::Game::ZxSpectrum::MapInkColour (Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW),    },
        {   Folio::Core::Game::ZxSpectrum::MapInkColour (Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA),   },
    };

    FolioStatus status = ERR_NOT_SUPPORTED;

    // Does the static sprite support colour change?

    if (SupportsColourChange (m_staticSpriteFlags))
    {
        // Yes.

        if (m_colourChangeIndex == FOLIO_INVALID_INDEX)
        {
            // Start randomly within the colour list.
        
            m_colourChangeIndex = Folio::Core::Util::Random::GetRandomNumber (s_colourList.size () - 1);
        } // Endif.

        // Change the static sprite's colour.

        status = ChangeSpriteInkColour (s_colourList [m_colourChangeIndex]);

        if (++m_colourChangeIndex >= s_colourList.size ()) 
        {
            m_colourChangeIndex = 0;
        } // Endif.
    
    } // Endif.

    return (status);
} // Endproc.


bool    StaticSprite::SupportsColourChange (UInt32 staticSpriteFlags)
{
    return ((staticSpriteFlags & FLAGS_SUPPORTS_COLOUR_CHANGE) == FLAGS_SUPPORTS_COLOUR_CHANGE);
} // Endproc.


Folio::Core::Game::ZxSpectrum::COLOUR   StaticSprite::GetStaticSpriteColour (STATIC_SPRITE_ID staticSpriteId)
{
    Folio::Core::Game::ZxSpectrum::COLOUR   staticSpriteColour = Folio::Core::Game::ZxSpectrum::WHITE; // Initialise!

    // Get the static sprite's colour.

    switch (staticSpriteId)
    {
    case STATIC_SPRITE_GRAVESTONE:
        staticSpriteColour = Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN;
        break;

    default:
        staticSpriteColour = Folio::Core::Game::ZxSpectrum::WHITE;
        break;
    } // Endswitch.

    return (staticSpriteColour);
} // Endproc.


UInt32  GetMaxStaticSpritesOnScreen (STATIC_SPRITE_ID staticSpriteId)
{
    UInt32  maxStaticSpritesOnScreen = 0;   // Initialise!

    switch (staticSpriteId)
    {
    case STATIC_SPRITE_ACG_KEY_LEFT:
    case STATIC_SPRITE_ACG_KEY_MIDDLE:
    case STATIC_SPRITE_ACG_KEY_RIGHT:
        maxStaticSpritesOnScreen = 1;
        break;

    case STATIC_SPRITE_KEY:
    case STATIC_SPRITE_GRAVESTONE:
        maxStaticSpritesOnScreen = 4;
        break;

    case STATIC_SPRITE_LEAF:
    case STATIC_SPRITE_BOTTLE:
    case STATIC_SPRITE_MEDICINE_BOTTLE:
    case STATIC_SPRITE_BROKEN:
    case STATIC_SPRITE_ROPE:
    case STATIC_SPRITE_ARM:
    case STATIC_SPRITE_BOWL:
    case STATIC_SPRITE_APPLE:
    case STATIC_SPRITE_CANDY_BAR:
    case STATIC_SPRITE_HAM:
    case STATIC_SPRITE_LOLLIPOP:
    case STATIC_SPRITE_MONEY_BAG:
    case STATIC_SPRITE_GOBSTOPPER:
    case STATIC_SPRITE_AMULET:
    case STATIC_SPRITE_CAN:
    case STATIC_SPRITE_ICE_CREAM_CONE:
    case STATIC_SPRITE_CRUCIFIX:
    case STATIC_SPRITE_SKULL:
    case STATIC_SPRITE_SPANNER:
    case STATIC_SPRITE_MUSHROOM:
    default:
        // Get the maximum static sprites on any single screen.

        for (UInt32 screenNumber = MIN_SCREEN_NUMBER; screenNumber <= MAX_SCREEN_NUMBER; ++screenNumber)
        {
            UInt32  numOfStaticSpritesOnScreen = 0;   // Initialise!

            for (UInt32 index = 0; 
                 index < (sizeof (g_staticSpriteAttributesTable) / sizeof (StaticSpriteAttributes));
                 ++index)
            {              
                if ((g_staticSpriteAttributesTable [index].m_initialScreenNumber == screenNumber) &&
                    (g_staticSpriteAttributesTable [index].m_staticSpriteId == staticSpriteId))
                {
                    numOfStaticSpritesOnScreen++;
                } // Endif.

            } // Endfor.

            if (numOfStaticSpritesOnScreen > maxStaticSpritesOnScreen)
            {
                maxStaticSpritesOnScreen = numOfStaticSpritesOnScreen;
            } // Endif.

        } // Endfor.
        break;
    } // Endswitch.

    return (maxStaticSpritesOnScreen);
} // Endproc.


FolioStatus CreateStaticSprites (StaticSpritesList& staticSpritesList)
{
    FolioStatus status = ERR_SUCCESS;

    staticSpritesList.clear ();   // Initialise!

    // Build the static sprites list.

    for (UInt32 index = 0; 
         (status == ERR_SUCCESS) && (index < (sizeof (g_staticSpriteAttributesTable) / sizeof (StaticSpriteAttributes)));
         ++index)
    {              
        // Store the static sprite in the static sprites list.

        staticSpritesList.push_back (StaticSpritePtr(new StaticSprite(g_staticSpriteAttributesTable [index].m_staticSpriteId,
                                                                      g_staticSpriteAttributesTable [index].m_initialScreenNumber,
                                                                      g_staticSpriteAttributesTable [index].m_initialScreenXLeft,
                                                                      g_staticSpriteAttributesTable [index].m_initialScreenYBottom,
                                                                      g_staticSpriteAttributesTable [index].m_staticSpriteColour,
                                                                      g_staticSpriteAttributesTable [index].m_staticSpriteFlags)));
    } // Endfor.

    if (status != ERR_SUCCESS)
    {
        staticSpritesList.clear ();
    } // Endif.

    return (status);
} // Endproc.


StaticSpritesList   GetScreenStaticSpritesList (UInt32                      screenNumber,
                                                const StaticSpritesList&    staticSpritesList)
{
    StaticSpritesList   screenStaticSpritesList;

    // Get the static sprites list for the specified screen number.

    for (StaticSpritesList::const_iterator itr = staticSpritesList.begin ();
         itr != staticSpritesList.end ();
         ++itr)
    {
        if (itr->get()->GetScreenNumber () == screenNumber)
        {
            // Add the static sprite.

            screenStaticSpritesList.push_back (*itr);
        } // Endif.

    } // Endfor.

    return (screenStaticSpritesList);
} // Endproc.


void    ScatterStaticSprites (StaticSpritesList& staticSpritesList)
{
    // Calculate the static sprite location table index.

    CalculateStaticSpriteLocationTableIndex ();

    for (StaticSpritesList::iterator itr = staticSpritesList.begin ();
         itr != staticSpritesList.end ();
         ++itr)
    {
        // Get the static sprite.

        StaticSpritePtr staticSprite(*itr);

        switch (staticSprite->GetStaticSpriteId ())
        {
        case STATIC_SPRITE_ACG_KEY_LEFT:
            staticSprite->SetScreenNumber (GetAcgKeyLeftLocation ());
            break;

        case STATIC_SPRITE_ACG_KEY_MIDDLE:
            staticSprite->SetScreenNumber (GetAcgKeyMiddleLocation ());
            break;

        case STATIC_SPRITE_ACG_KEY_RIGHT:
            staticSprite->SetScreenNumber (GetAcgKeyRightLocation ());
            break;

        case STATIC_SPRITE_KEY:
            switch (staticSprite->GetStaticSpriteColour ())
            {
            case Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED:
                staticSprite->SetScreenNumber (GetRedKeyLocation ());
                break;

            case Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN:
                staticSprite->SetScreenNumber (GetGreenKeyLocation ());
                break;

            case Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN:
                staticSprite->SetScreenNumber (GetCyanKeyLocation ());
                break;

            case Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW:
                staticSprite->SetScreenNumber (GetYellowKeyLocation ());
                break;

            default:
                break;
            } // Endswitch.
            break;

        default:
            break;
        } // Endswitch.
    
    } // Endfor.

} // Endproc.


UInt32  GetAcgKeyLeftLocation ()
{
    return (g_staticSpriteLocationsTable [g_staticSpriteLocationTableIndex].m_acgKeyLeft);
} // Endproc.


bool    IsAcgKeyLeftLocation (UInt32 screenNumber)
{
    return (GetAcgKeyLeftLocation () == screenNumber);
} // Endproc.


UInt32  GetAcgKeyMiddleLocation ()
{
    return (g_staticSpriteLocationsTable [g_staticSpriteLocationTableIndex].m_acgKeyMiddle);
} // Endproc.


bool    IsAcgKeyMiddleLocation (UInt32 screenNumber)
{
    return (GetAcgKeyMiddleLocation () == screenNumber);
} // Endproc.


UInt32  GetAcgKeyRightLocation ()
{
    return (g_staticSpriteLocationsTable [g_staticSpriteLocationTableIndex].m_acgKeyRight);
} // Endproc.


bool    IsAcgKeyRightLocation (UInt32 screenNumber)
{
    return (GetAcgKeyRightLocation () == screenNumber);
} // Endproc.


UInt32  GetRedKeyLocation ()
{
    return (g_staticSpriteLocationsTable [g_staticSpriteLocationTableIndex].m_redKey);
} // Endproc.


bool    IsRedKeyLocation (UInt32 screenNumber)
{
    return (GetRedKeyLocation () == screenNumber);
} // Endproc.


UInt32  GetGreenKeyLocation ()
{
    return (g_staticSpriteLocationsTable [g_staticSpriteLocationTableIndex].m_greenKey);
} // Endproc.


bool    IsGreenKeyLocation (UInt32 screenNumber)
{
    return (GetGreenKeyLocation () == screenNumber);
} // Endproc.


UInt32  GetCyanKeyLocation ()
{
    return (g_staticSpriteLocationsTable [g_staticSpriteLocationTableIndex].m_cyanKey);
} // Endproc.


bool    IsCyanKeyLocation (UInt32 screenNumber)
{
    return (GetCyanKeyLocation () == screenNumber);
} // Endproc.


UInt32  GetYellowKeyLocation ()
{
    return (g_staticSpriteLocationsTable [g_staticSpriteLocationTableIndex].m_yellowKey);
} // Endproc.


bool    IsYellowKeyLocation (UInt32 screenNumber)
{
    return (GetYellowKeyLocation () == screenNumber);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
