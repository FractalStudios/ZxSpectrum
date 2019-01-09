// "Home-made" includes.
#include    "StdAfx.h"
#include    "Screens.h"
#include    "StaticSprites.h"
#include    "ZxSpectrum.h"

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Static sprites table.
static  const   StaticSprite  g_staticSpritesTable [] =
{
//      m_staticSpriteId                                m_screenNumber  m_screenXLeft   m_screenYBottom     m_colour                                    m_staticSpriteFlags
    {   STATIC_SPRITE_ACG_KEY_LEFT,                       0,             88,             88,                ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_ACG_KEY_MIDDLE,                     0,             88,             88,                ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_ACG_KEY_RIGHT,                      0,             88,             88,                ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_KEY,                                0,            112,             96,                ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_KEY,                                0,            128,             64,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_KEY,                                0,             88,             88,                ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_KEY,                                0,             48,            135,                ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_LEAF,                               9,             64,             64,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CRUCIFIX,                           5,             64,            112,                ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_SPANNER,                           48,             64,            112,                ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_MEDICINE_BOTTLE,                   59,             96,             96,                ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_GOBSTOPPER,                        72,            112,            112,                ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BROKEN,                           100,            128,            128,                ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_ROPE,                             107,             64,             64,                ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_ARM,                               19,             80,             80,                ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_AMULET,                           132,             96,             64,                ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_MONEY_BAG,                         31,            112,            112,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_SKULL,                             73,             80,             64,                ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CAN,                               39,             87,            103,                ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CAN,                              127,             64,             64,                ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CAN,                               30,             80,             87,                ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CAN,                               12,             96,             96,                ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CAN,                              103,             87,             64,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CAN,                               65,             87,            103,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CANDY_BAR,                        117,             48,             64,                ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CANDY_BAR,                        131,             48,             64,                ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CANDY_BAR,                         12,             96,            112,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CANDY_BAR,                        104,             87,             64,                ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CANDY_BAR,                         69,             87,             70,                ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CANDY_BAR,                         70,             67,            123,                ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_HAM,                              134,             71,             96,                ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_HAM,                              110,             96,            119,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_HAM,                              125,             87,            103,                ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_HAM,                              106,             48,            103,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_HAM,                               62,             67,            123,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_HAM,                               53,             87,            103,                ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_LOLLIPOP,                          43,             64,            128,                ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_LOLLIPOP,                         138,             87,            103,                ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_LOLLIPOP,                           9,            128,            144,                ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_LOLLIPOP,                         112,            128,            144,                ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_LOLLIPOP,                         116,             87,            135,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_LOLLIPOP,                          51,             87,            103,                ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_ICE_CREAM_CONE,                   120,             55,             55,                ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_ICE_CREAM_CONE,                   138,            127,            127,                ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_ICE_CREAM_CONE,                    11,             87,            103,                ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_ICE_CREAM_CONE,                   101,             87,            135,                ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_ICE_CREAM_CONE,                    83,             67,            123,                ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_ICE_CREAM_CONE,                    76,            107,            123,                ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOWL,                             123,             80,             96,                ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOWL,                             135,             87,            103,                ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOWL,                              13,             48,            103,                ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOWL,                             102,             67,            135,                ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOWL,                              83,            107,            123,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOWL,                              79,             87,            103,                ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_APPLE,                            126,             55,            128,                ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_APPLE,                            140,             87,            103,                ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_APPLE,                            112,             48,            144,                ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_APPLE,                            102,            107,            135,                ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_APPLE,                             60,             67,            123,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_APPLE,                             57,             67,            123,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOTTLE,                           126,            135,            128,                ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOTTLE,                            36,             96,            112,                ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOTTLE,                           112,             87,            144,                ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOTTLE,                            18,             87,             64,                ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOTTLE,                            94,             87,            103,                ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOTTLE,                            29,             48,            103,                ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CAN,                               23,             64,             64,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CAN,                              115,             48,            103,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CAN,                                7,             87,            103,                ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CAN,                                2,             87,            103,                ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CANDY_BAR,                         15,             87,            103,                ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CANDY_BAR,                         58,             48,             72,                ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CANDY_BAR,                         65,            128,            103,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_CANDY_BAR,                        133,             67,            123,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_HAM,                              108,             87,             71,                ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_HAM,                               58,             87,             72,                ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_HAM,                              105,             48,             64,                ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_HAM,                              128,             48,             64,                ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_LOLLIPOP,                           4,             87,            103,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_LOLLIPOP,                          75,             48,            136,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_LOLLIPOP,                          17,             87,            103,                ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_LOLLIPOP,                         128,             87 ,            64,                ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_ICE_CREAM_CONE,                   105,             48,            103,                ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_ICE_CREAM_CONE,                    53,             87,            144,                ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_ICE_CREAM_CONE,                   105,             48,            144,                ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_ICE_CREAM_CONE,                   128,            128,            128,                ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOWL,                              87,             87,             64,                ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOWL,                              53,             87,             64,                ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOWL,                              37,            107,            123,                ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOWL,                              27,             87,            103,                ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_APPLE,                             88,             87,             64,                ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_APPLE,                             78,            103,             64,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_APPLE,                             55,             87,            103,                ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_APPLE,                            133,            107,            123,                ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOTTLE,                            91,             87,            103,                ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOTTLE,                            78,             64,            103,                ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOTTLE,                            73,             87,            103,                ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_BOTTLE,                            40,             87,            103,                ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     StaticSprite::FLAGS_NONE,                   },
    {   STATIC_SPRITE_MUSHROOM,                          80,             87,             64,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE, },
    {   STATIC_SPRITE_MUSHROOM,                          67,            107,             84,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE, },
    {   STATIC_SPRITE_MUSHROOM,                          64,             67,            123,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE, },
    {   STATIC_SPRITE_MUSHROOM,                         143,             87,            143,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE, },
    {   STATIC_SPRITE_MUSHROOM,                         143,             67,            123,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE, },
    {   STATIC_SPRITE_MUSHROOM,                         143,            107,            123,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE, },
    {   STATIC_SPRITE_MUSHROOM,                          69,            128,            103,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE, },
    {   STATIC_SPRITE_MUSHROOM,                          56,            107,             84,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE, },
    {   STATIC_SPRITE_MUSHROOM,                         116,             48,             64,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE, },
    {   STATIC_SPRITE_MUSHROOM,                         116,             48,            136,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE, },
    {   STATIC_SPRITE_MUSHROOM,                         116,            120,            136,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE, },
    {   STATIC_SPRITE_MUSHROOM,                         116,            128,             64,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE, },
    {   STATIC_SPRITE_MUSHROOM,                          84,             87,             64,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE, },
    {   STATIC_SPRITE_MUSHROOM,                          59,             67,            123,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE, },
    {   STATIC_SPRITE_MUSHROOM,                          59,            107,            123,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE, },
    {   STATIC_SPRITE_MUSHROOM,                          83,            128,             64,                ZxSpectrum::BRIGHT | ZxSpectrum::RED,       StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE, },
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
    m_screenNumber(ZxSpectrum::UNDEFINED),
    m_screenXLeft(ZxSpectrum::UNDEFINED),
    m_screenYBottom(ZxSpectrum::UNDEFINED),
    m_colour(ZxSpectrum::UNDEFINED),
    m_staticSpriteFlags(FLAGS_NONE),
    m_colourChangeIndex(FOLIO_INVALID_INDEX)
{
} // Endproc.


StaticSprite::StaticSprite (STATIC_SPRITE_ID    staticSpriteId,
                            UInt32              screenNumber,
                            Int32               screenXLeft,
                            Int32               screenYBottom,
                            ZxSpectrum::COLOUR  colour,
                            UInt32              staticSpriteFlags)
:   m_staticSpriteId(staticSpriteId),
    m_screenNumber(screenNumber),
    m_screenXLeft(screenXLeft),
    m_screenYBottom(screenYBottom),
    m_colour(ZxSpectrum::MapInkColour (colour)),
    m_staticSpriteFlags(staticSpriteFlags),
    m_colourChangeIndex(FOLIO_INVALID_INDEX)
{
} // Endproc.


StaticSprite::~StaticSprite ()
{
} // Endproc.


void    StaticSprite::SetStaticSpriteGraphic (const StaticSpriteGraphicsMap &staticSpriteGraphicsMap)
{
    // Note the static sprite graphics map.

    m_staticSpriteGraphicsMap = const_cast<StaticSpriteGraphicsMap *> (&(staticSpriteGraphicsMap));

    // Set the static sprite's graphic.

    SetStaticSpriteGraphic (m_staticSpriteId);
} // Endproc.


StaticSpriteGraphic StaticSprite::GetStaticSpriteGraphic () const
{
    return (m_staticSpriteGraphic);
} // Endproc.


STATIC_SPRITE_ID    StaticSprite::GetStaticSpriteId () const
{
    return (m_staticSpriteId);
} // Endproc.


UInt32  StaticSprite::GetScreenNumber () const
{
    return (m_screenNumber);
} // Endproc.


Gdiplus::ARGB   StaticSprite::GetColour () const
{
    return (m_colour);
} // Endproc.


UInt32  StaticSprite::GetStaticSpriteFlags () const
{
    return (m_staticSpriteFlags);
} // Endproc.


void    StaticSprite::SetScreenNumber (UInt32 screenNumber)
{
    m_screenNumber = screenNumber;
} // Endproc.


void    StaticSprite::SetScreenTopLeft (Int32   screenXLeft,
                                        Int32   screenYTop)
{
    if (m_staticSpriteGraphic)
    {
        m_screenXLeft   = screenXLeft;
        m_screenYBottom = ZxSpectrum::CalculateScreenYBottom (screenYTop, 
                                                              m_staticSpriteGraphic->GetGraphicWidth (),
                                                              m_staticSpriteGraphic->GetGraphicHeight ());
    } // Endif.

} // Endproc.


Gdiplus::Rect   StaticSprite::GetScreenRect () const
{
    return (Gdiplus::Rect(GetScreenXLeft(), 
                          GetScreenYTop (), 
                          GetScreenWidth (), 
                          GetScreenHeight ()));
} // Endproc.


Int32   StaticSprite::GetScreenXLeft () const
{
    return (m_staticSpriteGraphic ? m_screenXLeft : ZxSpectrum::UNDEFINED);
} // Endproc.


Int32   StaticSprite::GetScreenYTop () const
{
    Int32   screenYTop = ZxSpectrum::UNDEFINED;   

    if (m_staticSpriteGraphic)
    {
        screenYTop = ZxSpectrum::CalculateScreenYTop (m_screenYBottom, 
                                                      m_staticSpriteGraphic->GetGraphicWidth (),
                                                      m_staticSpriteGraphic->GetGraphicHeight ());
    } // Endif.

    return (screenYTop);
} // Endproc.


Int32   StaticSprite::GetScreenXRight () const
{
    return (m_staticSpriteGraphic ? m_screenXLeft + m_staticSpriteGraphic->GetGraphicWidth () - 1 : ZxSpectrum::UNDEFINED);
} // Endproc.


Int32   StaticSprite::GetScreenYBottom () const
{
    return (m_screenYBottom);
} // Endproc.


Int32   StaticSprite::GetScreenWidth () const
{
    return (m_staticSpriteGraphic ? m_staticSpriteGraphic->GetGraphicWidth () : ZxSpectrum::UNDEFINED);
} // Endproc.


Int32   StaticSprite::GetScreenHeight () const
{
    return (m_staticSpriteGraphic ? m_staticSpriteGraphic->GetGraphicHeight () : ZxSpectrum::UNDEFINED);
} // Endproc.


FolioStatus StaticSprite::QueryDrawingElements (FolioHandle                             dcHandle,
                                                Folio::Core::Game::DrawingElementsList  &drawingElementsList) const
{
    FolioStatus status = ERR_SUCCESS;

    drawingElementsList.clear ();   // Initialise!

    if (m_staticSpriteGraphic)
    {
        // Query the static sprite graphic's drawing elements.

        Int32   screenYTop = ZxSpectrum::CalculateScreenYTop (m_screenYBottom, 
                                                              m_staticSpriteGraphic->GetGraphicWidth (),
                                                              m_staticSpriteGraphic->GetGraphicHeight ());

        status = m_staticSpriteGraphic->QueryDrawingElements (dcHandle,
                                                              m_screenXLeft,
                                                              screenYTop,
                                                              ZxSpectrum::DEFAULT_SCREEN_SCALE,
                                                              m_colour,
                                                              Folio::Core::Game::ResourceGraphic::NO_DRAWING_FLAGS,
                                                              const_cast<StaticSprite *> (this),    // Drawing element user data.
                                                              drawingElementsList);

        if (status != ERR_SUCCESS)
        {
            drawingElementsList.clear ();
        } // Endif.

     } // Endif.

    else
    {
        status = ERR_NOT_INITIALISED;
    } // Endelse.

    return (status);
} // Endproc.


Gdiplus::ARGB   StaticSprite::ChangeColour ()
{
    // Colour list type.
    typedef std::vector<Gdiplus::ARGB>  ColourList;

    // The colour list.
    static  const   ColourList  s_colourList =
    {
        {   ZxSpectrum::MapInkColour (ZxSpectrum::BRIGHT | ZxSpectrum::RED),        },
        {   ZxSpectrum::MapInkColour (ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA),    },
        {   ZxSpectrum::MapInkColour (ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW),     },
        {   ZxSpectrum::MapInkColour (ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA),    },
    };

    if (m_colourChangeIndex == FOLIO_INVALID_INDEX)
    {
        // Start randomly within the colour list.
        
        m_colourChangeIndex = Folio::Core::Util::Random::GetRandomNumber (s_colourList.size () - 1);
    } // Endif.

    // Change the colour.

    m_colour = s_colourList [m_colourChangeIndex];

    if (++m_colourChangeIndex >= s_colourList.size ()) 
    {
        m_colourChangeIndex = 0;
    } // Endif.

    return (m_colour);
} // Endproc.


bool    StaticSprite::operator == (const StaticSprite &rhs) const
{
    return ((m_screenNumber     == rhs.m_screenNumber)      &&
            (m_staticSpriteId   == rhs.m_staticSpriteId)    &&
            (m_screenXLeft      == rhs.m_screenXLeft)       &&
            (m_screenYBottom    == rhs.m_screenYBottom));
} // Endproc.


bool    StaticSprite::SupportsColourChange (UInt32 staticSpriteFlags)
{
    return ((staticSpriteFlags & StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE) == StaticSprite::FLAGS_SUPPORTS_COLOUR_CHANGE);
} // Endproc.


void    StaticSprite::SetStaticSpriteGraphic (STATIC_SPRITE_ID staticSpriteId)
{
    StaticSpriteGraphicsMap::const_iterator   itr = m_staticSpriteGraphicsMap->find (staticSpriteId);

    if (itr != m_staticSpriteGraphicsMap->end ())
    {
        // Note the static sprite's graphic.

        m_staticSpriteGraphic = itr->second;
    } // Endif.

} // Endproc.


FolioStatus BuildStaticSprites (const StaticSpriteGraphicsMap   &staticSpriteGraphicsMap,
                                StaticSpritesList               &staticSpritesList)
{
    FolioStatus status = ERR_SUCCESS;

    staticSpritesList.clear ();   // Initialise!

    // Build the static sprites list.

    for (UInt32 index = 0; 
         (status == ERR_SUCCESS) && (index < (sizeof (g_staticSpritesTable) / sizeof (StaticSprite)));
         ++index)
    {              
        // Create a static sprite.

        StaticSpritePtr staticSprite(new StaticSprite(g_staticSpritesTable [index]));

        // Set the static sprite's graphic.

        staticSprite.get ()->SetStaticSpriteGraphic (staticSpriteGraphicsMap);

        // Store the static sprite in the list of static sprites.

        staticSpritesList.push_back (staticSprite);
    } // Endif.

    if (status != ERR_SUCCESS)
    {
        staticSpritesList.clear ();
    } // Endif.

    return (status);
} // Endproc.


StaticSpritesList   GetScreenStaticSpritesList (UInt32                  screenNumber,
                                                const StaticSpritesList &staticSpritesList)
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


FolioStatus ScatterStaticSprites (StaticSpritesList &staticSpritesList)
{
    FolioStatus status = ERR_SUCCESS;

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
            switch (staticSprite->GetColour ())
            {
            case Gdiplus::Color::Red:
                staticSprite->SetScreenNumber (GetRedKeyLocation ());
                break;

            case Gdiplus::Color::Lime:
                staticSprite->SetScreenNumber (GetGreenKeyLocation ());
                break;

            case Gdiplus::Color::Cyan:
                staticSprite->SetScreenNumber (GetCyanKeyLocation ());
                break;

            case Gdiplus::Color::Yellow:
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

    return (status);
} // Endproc.


ZxSpectrum::COLOUR  GetStaticSpriteColour (STATIC_SPRITE_ID staticSpriteId)
{
    ZxSpectrum::COLOUR  staticSpriteColour = ZxSpectrum::WHITE; // Initialise!

    // Get the static sprite's colour.

    switch (staticSpriteId)
    {
    case STATIC_SPRITE_GRAVESTONE:
        staticSpriteColour = ZxSpectrum::BRIGHT | ZxSpectrum::CYAN;
        break;

    default:
        staticSpriteColour = ZxSpectrum::WHITE;
        break;
    } // Endswitch.

    return (staticSpriteColour);
} // Endproc.


UInt32  GetAcgKeyLeftLocation ()
{
    return (g_staticSpriteLocationsTable [g_staticSpriteLocationTableIndex].m_acgKeyLeft);
} // Endproc.


bool    IsAcgKeyLeftLocation (UInt32 screenNumber)
{
    return (g_staticSpriteLocationsTable [g_staticSpriteLocationTableIndex].m_acgKeyLeft == screenNumber);
} // Endproc.


UInt32  GetAcgKeyMiddleLocation ()
{
    return (g_staticSpriteLocationsTable [g_staticSpriteLocationTableIndex].m_acgKeyMiddle);
} // Endproc.


bool    IsAcgKeyMiddleLocation (UInt32 screenNumber)
{
    return (g_staticSpriteLocationsTable [g_staticSpriteLocationTableIndex].m_acgKeyMiddle == screenNumber);
} // Endproc.


UInt32  GetAcgKeyRightLocation ()
{
    return (g_staticSpriteLocationsTable [g_staticSpriteLocationTableIndex].m_acgKeyRight);
} // Endproc.


bool    IsAcgKeyRightLocation (UInt32 screenNumber)
{
    return (g_staticSpriteLocationsTable [g_staticSpriteLocationTableIndex].m_acgKeyRight == screenNumber);
} // Endproc.


UInt32  GetRedKeyLocation ()
{
    return (g_staticSpriteLocationsTable [g_staticSpriteLocationTableIndex].m_redKey);
} // Endproc.


bool    IsRedKeyLocation (UInt32 screenNumber)
{
    return (g_staticSpriteLocationsTable [g_staticSpriteLocationTableIndex].m_redKey == screenNumber);
} // Endproc.


UInt32  GetGreenKeyLocation ()
{
    return (g_staticSpriteLocationsTable [g_staticSpriteLocationTableIndex].m_greenKey);
} // Endproc.


bool    IsGreenKeyLocation (UInt32 screenNumber)
{
    return (g_staticSpriteLocationsTable [g_staticSpriteLocationTableIndex].m_greenKey == screenNumber);
} // Endproc.


UInt32  GetCyanKeyLocation ()
{
    return (g_staticSpriteLocationsTable [g_staticSpriteLocationTableIndex].m_cyanKey);
} // Endproc.


bool    IsCyanKeyLocation (UInt32 screenNumber)
{
    return (g_staticSpriteLocationsTable [g_staticSpriteLocationTableIndex].m_cyanKey == screenNumber);
} // Endproc.


UInt32  GetYellowKeyLocation ()
{
    return (g_staticSpriteLocationsTable [g_staticSpriteLocationTableIndex].m_yellowKey);
} // Endproc.


bool    IsYellowKeyLocation (UInt32 screenNumber)
{
    return (g_staticSpriteLocationsTable [g_staticSpriteLocationTableIndex].m_yellowKey == screenNumber);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
