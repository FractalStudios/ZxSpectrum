#pragma once

// STL includes.
#include    <memory>

// "Home-made" includes.
#include    <Applet.h>
#include    <Game.h>
#include    <Util.h>
#include    "CollisionGrid.h"
#include    "DrawingElement.h"
#include    "SpriteGraphics.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Player sprite identifier enumeration.
enum PLAYER_SPRITE_ID
{
    PLAYER_SPRITE_UNDEFINED = DRAWING_ELEMENT_UNDEFINED,
    PLAYER_SPRITE_SABRE_MAN = DRAWING_ELEMENT_PLAYER_SPRITE * MAX_NUM_DRAWING_ELEMENTS_PER_ITEM,
}; // Endenum.


// Player sprite.
class PlayerSprite : public Folio::Core::Game::APlayerSprite
{
public:
    static  const   Folio::Core::Game::Action   ACTION_SWIPE_SWORD  = 0x00000001;    // Swipe sword action.
    static  const   Folio::Core::Game::Action   ACTION_FALLING      = 0x00000002;    // Falling action.
    static  const   Folio::Core::Game::Action   ACTION_SITTING      = 0x00000004;    // Sitting action.
    static  const   Folio::Core::Game::Action   ACTION_GAME_OVER    = 0x00000008;    // Game over action.

    PlayerSprite ();
    ~PlayerSprite ();

    FolioStatus Create (FolioHandle                 dcHandle,
                        const SpriteGraphicsMapPtr  &spriteGraphicsMap);
    FolioStatus Start ();
    Folio::Core::Game::Direction    UpdateDirection (Folio::Core::Game::Direction   direction, 
                                                     bool                           keyDown);
    FolioStatus CheckPlayer (Gdiplus::Graphics      &graphics,
                             const CollisionGrid    &collisionGrid);

    FolioStatus SetTemporaryImmunity (Folio::Core::Game::ZxSpectrum::COLOUR playerSpriteColour);
    FolioStatus SetTemporaryConfusion (Folio::Core::Game::ZxSpectrum::COLOUR playerSpriteColour);
    FolioStatus SetTemporarySpeed (Folio::Core::Game::ZxSpectrum::COLOUR playerSpriteColour);
    FolioStatus SetTemporarySickness (Folio::Core::Game::ZxSpectrum::COLOUR playerSpriteColour);
    FolioStatus ResetTemporaryState ();

    void    SetFireKeyDown (bool fireKeyDown);
    void    SetGameOver ();

    bool    IsImmune () const;
    bool    IsSick () const;
    bool    IsDead (const CollisionGrid::CellElement& cellElement);

    void    SetFoundAmuletPiece (bool foundAmuletPiece);
    bool    FoundAmuletPiece () const;

private:
    static  const   UInt32  DEFAULT_SPEED       = 4;  // The default speed of the player sprite.
    static  const   UInt32  SWIPE_SWORD_SPEED   = 1;  // The speed of the player sprite (when swipping the sword).
    static  const   UInt32  FAST_SPEED          = 8;  // The fast speed of the player sprite (when its temporary state is SPEED).

    static  const   Int32   INITIAL_SCREEN_X_LEFT   = 120;  // The initial screen X left (in pixels) of the player sprite.
    static  const   Int32   INITIAL_SCREEN_Y_TOP    =  96;  // The initial screen Y top (in pixels) of the player sprite.

    static  const   Folio::Core::Game::ZxSpectrum::COLOUR   INITIAL_COLOUR = Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE); // The initial colour of the player sprite.
    
    static  const   Folio::Core::Game::Direction    INITIAL_DIRECTION = Folio::Core::Game::W;   // The initial direction of the player sprite.

    UInt32  m_playerSpriteSpeed;    // The speed of the player sprite.

    // Temporary state enumeration.
    enum TEMPORARY_STATE
    {
        NO_TEMPORARY_STATE = 0,
        IMMUNITY,
        CONFUSION,
        SPEED,
        SICKNESS,
    }; // Endenum.

    TEMPORARY_STATE m_temporaryState;   // The player sprite's temporary state.
    UInt32  m_temporaryStateTickCount;  // The temporary state timing (in milliseconds) of the player sprite.

    bool    m_foundAmuletPiece; // Indicates if the player sprite has found an amulet piece.

    FolioStatus SetTerminatingMode (FolioHandle                 dcHandle,
                                    const SpriteGraphicsMapPtr  &spriteGraphicsMap);

    FolioStatus SetTemporaryState (TEMPORARY_STATE                          temporaryState,
                                   Folio::Core::Game::ZxSpectrum::COLOUR    playerSpriteColour);
    void    StartTemporaryStateTickCount ();
    bool    IsTemporaryState () const;
    bool    IsTemporaryStateFinished () const;
    bool    IsTemporaryImmunity () const;
    bool    IsTemporaryConfusion () const;
    bool    IsTemporarySickness () const;

    void    SetMovementSoundSamples ();

    // APlayerSprite method(s).
    virtual Int32   CalculateCollisionXLeft () const;
    virtual Int32   CalculateScreenXLeft (CollisionGrid::DIRECTION collisionGridDirection) const;
    virtual Int32   CalculateScreenXLeft (Int32 bitmapScreenWidth) const;
    
    // Private copy constructor to prevent copying.
    PlayerSprite (const PlayerSprite& rhs);

    // Private assignment operator to prevent copying.
    PlayerSprite& operator= (const PlayerSprite& rhs);
}; // Endclass.                         

// Player sprite pointer.
typedef std::shared_ptr<PlayerSprite>   PlayerSpritePtr;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
