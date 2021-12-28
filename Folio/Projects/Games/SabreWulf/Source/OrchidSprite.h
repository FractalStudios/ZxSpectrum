#pragma once

// STL includes.
#include    <memory>

// "Home-made" includes.
#include    <Game.h>
#include    "CollisionGrid.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Orchid sprite identifier enumeration.
enum ORCHID_SPRITE_ID
{
    ORCHID_SPRITE_UNDEFINED = Folio::Core::Game::AItem::ITEM_ID_UNDEFINED,
    ORCHID_SPRITE,
}; // Endenum.


// Orchid sprite.
class OrchidSprite : public Folio::Core::Game::AStaticSprite
{
public:
    OrchidSprite ();
    ~OrchidSprite ();

    FolioStatus Create (FolioHandle dcHandle);

    FolioStatus SetScreenBottomLeft (Int32  screenXLeft,
                                     Int32  screenYBottom);

    void    StartTransitionTickCount (bool newScreen = true);
    void    CheckTransition ();

    // Orchid sprite type enumeration.
    enum ORCHID_SPRITE_TYPE
    {
        ORCHID_TYPE_UNDEFINED = Folio::Core::Game::AItem::ITEM_ID_UNDEFINED,
        IMMUNITY,   // Red.
        CONFUSION,  // Magenta.
        SPEED,      // Cyan.
        SICKNESS,   // Yellow.
        CURE,       // White.
    }; // Endenum.

    FolioStatus HandlePlayerCollision (ORCHID_SPRITE_TYPE&                      orchidSpriteType,
                                       Folio::Core::Game::ZxSpectrum::COLOUR&   orchidSpriteColour);

private:
    static  const   Int32   INITIAL_SCREEN_X_LEFT   = 120;  // The initial screen X left (in pixels) of the orchid sprite.
    static  const   Int32   INITIAL_SCREEN_Y_TOP    =  80;  // The initial screen Y top (in pixels) of the orchid sprite.

    Folio::Core::Game::ZxSpectrum::COLOUR   m_orchidSpriteColour;   // The colour of the orchid sprite.
    UInt32                                  m_transitionTickCount;  // The transition tick count of the orchid sprite.

    UInt32  m_colourChangeIndex;    // The colour change index of the orchid sprite.
    bool    m_infectedPlayer;       // Indicates if the orchid sprite has infected the player.

    FolioStatus SetInitialisingMode (FolioHandle                            dcHandle,
                                     Folio::Core::Game::ZxSpectrum::COLOUR  orchidSpriteColour);
    FolioStatus SetTerminatingMode (FolioHandle                             dcHandle,
                                    Folio::Core::Game::ZxSpectrum::COLOUR   orchidSpriteColour);

    FolioStatus ChangeOrchidSpriteColour ();

    void    SetOrchidSpriteGrowing ();
    bool    IsOrchidSpriteGrowing () const;

    void    SetOrchidSpriteGrown ();
    bool    IsOrchidSpriteGrown () const;

    void    SetOrchidSpriteShrinking ();
    bool    IsOrchidSpriteShrinking () const;

    void    SetOrchidSpriteShrunk ();
    bool    IsOrchidSpriteShrunk () const;

    bool    IsOrchidSpriteInfectious () const;

    static  ORCHID_SPRITE_TYPE  GetOrchidSpriteType (Folio::Core::Game::ZxSpectrum::COLOUR orchidSpriteColour);
    static  Folio::Core::Game::ZxSpectrum::COLOUR   GetOrchidSpriteColour ();

    // Private copy constructor to prevent copying.
    OrchidSprite (const OrchidSprite& rhs);

    // Private assignment operator to prevent copying.
    OrchidSprite& operator= (const OrchidSprite& rhs);
}; // Endclass.                         

// Orchid sprite pointer.
typedef std::shared_ptr<OrchidSprite>    OrchidSpritePtr;

// Orchid sprite drawing element.
typedef Folio::Core::Game::SpriteDrawingElement<OrchidSpritePtr>    OrchidSpriteDrawingElement;


// Routines.

extern  FolioStatus CreateOrchidSpriteDrawingElement (FolioHandle                   dcHandle,
                                                      OrchidSpriteDrawingElement&   orchidSpriteDrawingElement);
extern  FolioStatus InitialiseScreenOrchidSprite (CollisionGrid& collisionGrid);
extern  FolioStatus UpdateScreenOrchidSprite ();
extern  FolioStatus CheckScreenOrchidSprite (Gdiplus::Graphics& graphics);
extern  FolioStatus StoreScreenOrchidSpriteBackground (Gdiplus::Graphics& graphics);
extern  FolioStatus RestoreScreenOrchidSpriteBackground (Gdiplus::Graphics& graphics);
extern  FolioStatus DrawScreenOrchidSprite (Gdiplus::Graphics& graphics);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
