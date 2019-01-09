#pragma once

// STL includes.
#include    <memory>
#include    <vector>

// "Home-made" includes.
#include    <Game.h>
#include    "StaticSpriteGraphics.h"
#include    "ZxSpectrum.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Static sprite.
class StaticSprite : public Folio::Core::Game::AStaticSprite
{
public:
    // Static sprite flags.
    static  const   UInt32  FLAGS_NONE                      = 0x00000000;
    static  const   UInt32  FLAGS_SUPPORTS_COLOUR_CHANGE    = 0x00000001;   // If the static sprite supports colour change.

    StaticSprite (STATIC_SPRITE_ID      staticSpriteId,
                  UInt32                screenNumber,
                  Int32                 screenXLeft,
                  Int32                 screenYBottom,
                  ZxSpectrum::COLOUR    colour,
                  UInt32                staticSpriteFlags = FLAGS_NONE);
    ~StaticSprite ();

    void                SetStaticSpriteGraphic (const StaticSpriteGraphicsMap &staticSpriteGraphicsMap);
    StaticSpriteGraphic GetStaticSpriteGraphic () const;

    STATIC_SPRITE_ID    GetStaticSpriteId () const;
    UInt32              GetScreenNumber () const;
    Gdiplus::ARGB       GetColour () const;
    UInt32              GetStaticSpriteFlags () const;
    
    void    SetScreenNumber (UInt32 screenNumber);
    void    SetScreenTopLeft (Int32 screenXLeft,
                              Int32 screenYTop);

    Gdiplus::Rect   GetScreenRect () const;
    Int32           GetScreenXLeft () const;
    Int32           GetScreenYTop () const;
    Int32           GetScreenXRight () const;
    Int32           GetScreenYBottom () const;
    Int32           GetScreenWidth () const;
    Int32           GetScreenHeight () const;

    FolioStatus QueryDrawingElements (FolioHandle                               dcHandle,
                                      Folio::Core::Game::DrawingElementsList    &drawingElementsList) const;

    Gdiplus::ARGB   ChangeColour ();

    bool    operator == (const StaticSprite &rhs) const;

    static  bool    SupportsColourChange (UInt32 staticSpriteFlags);

private:
    STATIC_SPRITE_ID    m_staticSpriteId;       // The identifier of the static sprite.
    UInt32              m_screenNumber;         // The screen number the static sprite belongs to.
    Int32               m_screenXLeft;          // The screen X left (in pixels) of the static sprite.
    Int32               m_screenYBottom;        // The screen Y bottom in pixels) of the static sprite.
    Gdiplus::ARGB       m_colour;               // The colour of the static sprite.
    UInt32              m_staticSpriteFlags;    // The flags of the static sprite.

    UInt32  m_colourChangeIndex;    // The colour change index.

    StaticSpriteGraphicsMap*    m_staticSpriteGraphicsMap;  // The static sprite graphics map.
    StaticSpriteGraphic         m_staticSpriteGraphic;      // The static sprite's graphic.
    
    void    SetStaticSpriteGraphic (STATIC_SPRITE_ID staticSpriteId);
}; // Endclass.

// Static sprite pointer.
typedef std::shared_ptr<StaticSprite>   StaticSpritePtr;

// Static sprites list.
typedef std::vector<StaticSpritePtr>    StaticSpritesList;
             

// Routines.

extern  FolioStatus BuildStaticSprites (const StaticSpriteGraphicsMap   &staticSpriteGraphicsMap,
                                        StaticSpritesList               &staticSpritesList);
extern  StaticSpritesList   GetScreenStaticSpritesList (UInt32                  screenNumber,
                                                        const StaticSpritesList &staticSpritesList);
extern  FolioStatus ScatterStaticSprites (StaticSpritesList &staticSpritesList);
extern  ZxSpectrum::COLOUR  GetStaticSpriteColour (STATIC_SPRITE_ID staticSpriteId);

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
