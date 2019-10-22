#pragma once

// STL includes.
#include    <memory>
#include    <vector>

// "Home-made" includes.
#include    <Applet.h>
#include    <Game.h>
#include    "SpriteGraphics.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Static sprite identifier enumeration.
enum STATIC_SPRITE_ID
{
    STATIC_SPRITE_UNDEFINED = Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_ID_UNDEFINED,
    STATIC_SPRITE_LEAF = 0,
    STATIC_SPRITE_KEY,
    STATIC_SPRITE_BOTTLE,
    STATIC_SPRITE_MEDICINE_BOTTLE,
    STATIC_SPRITE_BROKEN,
    STATIC_SPRITE_ROPE,
    STATIC_SPRITE_ARM,
    STATIC_SPRITE_BOWL,
    STATIC_SPRITE_APPLE,
    STATIC_SPRITE_CANDY_BAR,
    STATIC_SPRITE_HAM,
    STATIC_SPRITE_LOLLIPOP,
    STATIC_SPRITE_MONEY_BAG,
    STATIC_SPRITE_GOBSTOPPER,
    STATIC_SPRITE_AMULET,
    STATIC_SPRITE_CAN,
    STATIC_SPRITE_ICE_CREAM_CONE,
    STATIC_SPRITE_CRUCIFIX,
    STATIC_SPRITE_SKULL,
    STATIC_SPRITE_SPANNER,
    STATIC_SPRITE_ACG_KEY_LEFT,
    STATIC_SPRITE_ACG_KEY_MIDDLE,
    STATIC_SPRITE_ACG_KEY_RIGHT,
    STATIC_SPRITE_MUSHROOM,
    STATIC_SPRITE_GRAVESTONE,
    MAX_STATIC_SPRITE = STATIC_SPRITE_GRAVESTONE, 
}; // Endenum.


// Static sprite.
class StaticSprite : public Folio::Core::Game::AStaticSprite
{
public:
    // Static sprite flags.
    static  const   UInt32  FLAGS_NONE                      = 0x00000000;
    static  const   UInt32  FLAGS_SUPPORTS_COLOUR_CHANGE    = 0x00000001;   // If the static sprite supports colour change.

    StaticSprite ();
    ~StaticSprite ();

    FolioStatus Create (FolioHandle                             dcHandle,
                        STATIC_SPRITE_ID                        staticSpriteId,
                        const SpriteGraphicsMap                 &spriteGraphicsMap,
                        UInt32                                  initialScreenNumber,
                        Int32                                   initialScreenXLeft,
                        Int32                                   initialScreenYBottom,
                        Folio::Core::Game::ZxSpectrum::COLOUR   staticSpriteColour,
                        UInt32                                  staticSpriteFlags = FLAGS_NONE);

    STATIC_SPRITE_ID                        GetStaticSpriteId () const;
    Folio::Core::Game::ZxSpectrum::COLOUR   GetStaticSpriteColour () const;
    UInt32                                  GetStaticSpriteFlags () const;
  
    SpriteGraphic   GetSpriteGraphic () const;

    void    SetScreenNumber (UInt32 screenNumber);
    UInt32  GetScreenNumber () const;

    FolioStatus ChangeStaticSpriteColour ();

    static  bool    SupportsColourChange (UInt32 staticSpriteFlags);

private:
    STATIC_SPRITE_ID                        m_staticSpriteId;       // The identifier of the static sprite.
    UInt32                                  m_screenNumber;         // The screen number the static sprite belongs to.
    Int32                                   m_screenXLeft;          // The screen X left (in pixels) of the static sprite.
    Int32                                   m_screenYTop;           // The screen Y bottom in pixels) of the static sprite.
    Folio::Core::Game::ZxSpectrum::COLOUR   m_staticSpriteColour;   // The colour of the static sprite.
    UInt32                                  m_staticSpriteFlags;    // The flags of the static sprite.

    UInt32  m_colourChangeIndex;    // The colour change index.

    SpriteGraphic   m_spriteGraphic;    // The static sprite's graphic.

    // Private copy constructor to prevent copying.
    StaticSprite (const StaticSprite& rhs);

    // Private assignment operator to prevent copying.
    StaticSprite& operator= (const StaticSprite& rhs);
}; // Endclass.                         

// Static sprite pointer.
typedef std::shared_ptr<StaticSprite>   StaticSpritePtr;

// Static sprites list.
typedef std::vector<StaticSpritePtr>    StaticSpritesList;

// Static sprite drawing element.
typedef Folio::Core::Game::SpriteDrawingElement<StaticSpritePtr> StaticSpriteDrawingElement;

// Static sprite drawing elements list.
typedef std::vector<StaticSpriteDrawingElement> StaticSpriteDrawingElementsList;


// Routines.

extern  FolioStatus ScatterStaticSprites (StaticSpritesList &staticSpritesList);
extern  FolioStatus BuildStaticSprites (FolioHandle             dcHandle,
                                        const SpriteGraphicsMap &spriteGraphicsMap,
                                        StaticSpritesList       &staticSpritesList);
extern  StaticSpritesList   GetScreenStaticSpritesList (UInt32                  screenNumber,
                                                        const StaticSpritesList &staticSpritesList);
extern  Folio::Core::Game::ZxSpectrum::COLOUR   GetStaticSpriteColour (STATIC_SPRITE_ID staticSpriteId);

extern  UInt32  GetAcgKeyLeftLocation ();
extern  bool    IsAcgKeyLeftLocation (UInt32 screenNumber);
extern  UInt32  GetAcgKeyMiddleLocation ();
extern  bool    IsAcgKeyMiddleLocation (UInt32 screenNumber);
extern  UInt32  GetAcgKeyRightLocation ();
extern  bool    IsAcgKeyRightLocation (UInt32 screenNumber);
extern  UInt32  GetRedKeyLocation ();
extern  bool    IsRedKeyLocation (UInt32 screenNumber);
extern  UInt32  GetGreenKeyLocation ();
extern  bool    IsGreenKeyLocation (UInt32 screenNumber);
extern  UInt32  GetCyanKeyLocation ();
extern  bool    IsCyanKeyLocation (UInt32 screenNumber);
extern  UInt32  GetYellowKeyLocation ();
extern  bool    IsYellowKeyLocation (UInt32 screenNumber);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
