#pragma once

// STL includes.
#include    <memory>
#include    <vector>

// "Home-made" includes.
#include    <Applet.h>
#include    <Game.h>
#include    "DrawingElement.h"
#include    "PlayerSprite.h"
#include    "SpriteGraphics.h"

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
    ORCHID_SPRITE_UNDEFINED = DRAWING_ELEMENT_UNDEFINED,
    ORCHID_SPRITE = DRAWING_ELEMENT_ORCHID_SPRITE * MAX_NUM_DRAWING_ELEMENTS_PER_ITEM,                              
}; // Endenum.


// Orchid sprite.
class OrchidSprite : public Folio::Core::Game::AStaticSprite
{
public:
    OrchidSprite ();
    ~OrchidSprite ();

    FolioStatus Create (FolioHandle                 dcHandle,
                        const SpriteGraphicsMapPtr  &spriteGraphicsMap);

    FolioStatus SetScreenBottomLeft (Int32  screenXLeft,
                                     Int32  screenYBottom);

    void    StartTransitionTickCount (bool newScreen = true);
    void    CheckTransition ();

    FolioStatus HandlePlayerCollision (PlayerSpritePtr &platerSprite);

private:
    static  const   Int32   INITIAL_SCREEN_X_LEFT   = 120;  // The initial screen X left (in pixels) of the ocrhid sprite.
    static  const   Int32   INITIAL_SCREEN_Y_TOP    =  80;  // The initial screen Y top (in pixels) of the ocrhid sprite

    Folio::Core::Game::ZxSpectrum::COLOUR   m_orchidSpriteColour;   // The colour of the orchid sprite.
    UInt32                                  m_transitionTickCount;  // The transition timing (in milliseconds) of the orchid sprite.

    UInt32  m_colourChangeIndex;    // The colour change index.

    bool    m_infectedPlayer;   // Indicates if the orhid sprite has infected the player.

    FolioStatus SetInitialisingMode (FolioHandle                            dcHandle,
                                     const SpriteGraphicsMapPtr             &spriteGraphicsMap,
                                     Folio::Core::Game::ZxSpectrum::COLOUR  orchidSpriteColour);
    FolioStatus SetTerminatingMode (FolioHandle                             dcHandle,
                                    const SpriteGraphicsMapPtr              &spriteGraphicsMap,
                                    Folio::Core::Game::ZxSpectrum::COLOUR   orchidSpriteColour);

    FolioStatus ChangeOrchidSpriteColour ();

    bool    IsOrchidSpriteInfectious () const;

    // Orchid type enumeration.
    enum ORCHID_TYPE
    {
        IMMUNITY = 0,   // Red.
        CONFUSION,      // Magenta.
        SPEED,          // Cyan.
        SICKNESS,       // Yellow.
        CURE,           // White.
        DEFAULT_ORCHID_TYPE = CURE,
    }; // Endenum.

    static  ORCHID_TYPE GetOrchidType (Folio::Core::Game::ZxSpectrum::COLOUR orchidSpriteColour);
    static  Folio::Core::Game::ZxSpectrum::COLOUR   GetOrchidSpriteColour ();

    // Private copy constructor to prevent copying.
    OrchidSprite (const OrchidSprite& rhs);

    // Private assignment operator to prevent copying.
    OrchidSprite& operator= (const OrchidSprite& rhs);
}; // Endclass.                         

// Orchid sprite pointer.
typedef std::shared_ptr<OrchidSprite>    OrchidSpritePtr;

// Orchid sprites list.
typedef std::vector<OrchidSpritePtr>     OrchidSpritesList;

// Orchid sprite drawing element.
typedef Folio::Core::Game::SpriteDrawingElement<OrchidSpritePtr> OrchidSpriteDrawingElement;

// Orchid sprite drawing elements list.
typedef std::vector<OrchidSpriteDrawingElement> OrchidSpriteDrawingElementsList;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
