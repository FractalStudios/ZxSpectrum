#pragma once

// STL includes.
#include    <memory>

// "Home-made" includes.
#include    <Game.h>
#include    "CollisionGrid.h"
#include    "ObjectSprite.h"

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
    PLAYER_SPRITE_UNDEFINED = Folio::Core::Game::AItem::ITEM_ID_UNDEFINED,
    PLAYER_SPRITE_SABRE_MAN,
}; // Endenum.


// Player sprite.
class PlayerSprite : public Folio::Core::Game::APlayerSprite
{
public:
    static  const   Folio::Core::Game::Action   ACTION_SWIPE_SWORD  = 1;    // Swipe sword action.
    static  const   Folio::Core::Game::Action   ACTION_FALLING      = 2;    // Falling action.
    static  const   Folio::Core::Game::Action   ACTION_SITTING      = 3;    // Sitting action.
    static  const   Folio::Core::Game::Action   ACTION_LYING_DEAD   = 4;    // Lying dead action.

    PlayerSprite ();
    ~PlayerSprite ();

    FolioStatus Create (FolioHandle dcHandle);
    FolioStatus Start ();
    FolioStatus UpdateDirection (Folio::Core::Game::Direction   direction, 
                                 bool                           keyDown = true);
    FolioStatus CheckPlayerSprite (Gdiplus::Graphics&               graphics,
                                   CollisionGrid&                   collisionGrid,
                                   ObjectSpriteDrawingElementsList& screenObjectSpriteDrawingElementsList);

    FolioStatus SetFireKeyDown (bool fireKeyDown);
    FolioStatus Alive ();
    FolioStatus Dead ();

    void    ResetJustFoundAmuletPiece ();
    bool    IsJustFoundAmuletPiece () const;

    // ASprite method(s).
    virtual bool    IsReady () const;

private:
    static  const   Int32   INITIAL_SCREEN_X_LEFT   = 120;  // The initial screen X left (in pixels) of the player sprite.
    static  const   Int32   INITIAL_SCREEN_Y_TOP    =  96;  // The initial screen Y top (in pixels) of the player sprite.

    static  const   UInt32  DEFAULT_SPEED       = 4;  // The default speed of the player sprite.
    static  const   UInt32  SWIPE_SWORD_SPEED   = 2;  // The speed of the player sprite when swipping the sword.
    static  const   UInt32  FAST_SPEED          = 8;  // The speed of the player sprite when its infection is SPEED.

    static  const   Folio::Core::Game::ZxSpectrum::COLOUR   INITIAL_COLOUR = Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE); // The initial colour of the player sprite.
    
    static  const   Folio::Core::Game::Direction    INITIAL_DIRECTION = Folio::Core::Game::W;   // The initial direction of the player sprite.

    static  const   UInt32  INFECTION_COUNTDOWN     = 3;            // The countdown (in seconds) whist the player sprite is infected.
    static  const   UInt32  INFECTION_TICK_COUNT    = 15 * 1000;    // The time (in tick counts) the player sprite can be infected.

    UInt32  m_playerSpriteSpeed;    // The speed of the player sprite.

    // Infection enumeration.
    enum INFECTION
    {
        NO_INFECTION = 0,
        IMMUNITY,   // Player is immune from nasties.
        CONFUSION,  // Player direction is reversed.
        SPEED,      // Player moves faster and is immune from nasties.
        SICKNESS,   // Player is sick.
    }; // Endenum.

    INFECTION                               m_infection;            // The player sprite's infection.
    Folio::Core::Game::ZxSpectrum::COLOUR   m_infectionColour;      // The player sprite's infection colour.
    bool                                    m_infectionColourSet;   // true if the infection colour is set, false otherwise.
    UInt32                                  m_infectionTickCount;   // The infection tick count of the player sprite.
    mutable Int32                           m_infectionCountdown;   // The remaining countdown (in seconds) whilst the player sprite is infected.

    bool    m_justFoundAmuletPiece; // Indicates if the player sprite has just found an amulet piece.

    FolioStatus SetTerminatingMode (FolioHandle dcHandle);

    FolioStatus HandleCollision (const CollisionGrid::CellElements& cellElements,
                                 CollisionGrid&                     collisionGrid,
                                 ObjectSpriteDrawingElementsList&   screenObjectSpriteDrawingElementsList);
    FolioStatus HandleItemCollision (const CollisionGrid::CellElement&  cellElement,
                                     CollisionGrid&                     collisionGrid);
    FolioStatus HandleSolidItemCollision (const CollisionGrid::CellElement& cellElement, 
                                          CollisionGrid&                    collisionGrid);
    FolioStatus HandleCollectableItemCollision (const CollisionGrid::CellElement&   cellElement,
                                                CollisionGrid&                      collisionGrid,
                                                ObjectSpriteDrawingElementsList&    screenObjectSpriteDrawingElementsList);
    FolioStatus HandleNastySpriteCollision (const CollisionGrid::CellElement&   cellElement,
                                            CollisionGrid&                      collisionGrid);
    FolioStatus HandleBossSpriteCollision (const CollisionGrid::CellElement&    cellElement,
                                           CollisionGrid&                       collisionGrid);
    FolioStatus HandleGameCompleteCollision (const CollisionGrid::CellElement&  cellElement,
                                             CollisionGrid&                     collisionGrid);

    bool    CheckPlayerSpriteDead (const Folio::Core::Game::ASprite&    nastySprite,
                                   bool*                                changeDirection = 0);

    FolioStatus SetInfection (INFECTION                             infection,
                              Folio::Core::Game::ZxSpectrum::COLOUR playerSpriteColour);
    FolioStatus ClearInfection ();
    FolioStatus InfectionFinishing ();

    void    StartInfectionTickCount ();
    void    ResetInfectionTickCount ();
    bool    IsImmune () const;
    bool    IsInfection () const;
    bool    IsInfectionFinishing () const;
    bool    IsInfectionFinished () const;
    bool    IsInfectionImmunity () const;
    bool    IsInfectionConfusion () const;
    bool    IsInfectionSickness () const;

    FolioStatus SetSwipeSword ();
    FolioStatus ResetSwipeSword ();

    FolioStatus SetSitting ();
    FolioStatus ResetSitting ();

    FolioStatus SetFalling (Folio::Core::Game::Direction direction);
    FolioStatus ResetFalling ();

    void    SetMovementSoundSamples ();

    // APlayerSprite method(s).
    virtual Int32   CalculateMovingXLeft (Int32 bitmapScreenWidth) const;
    virtual Int32   CalculateScreenXLeft (Folio::Core::Game::ACollisionGrid::DIRECTION collisionGridDirection) const;
    virtual Int32   CalculateScreenXLeft (Int32 bitmapScreenWidth) const;
    
    // Private copy constructor to prevent copying.
    PlayerSprite (const PlayerSprite& rhs);

    // Private assignment operator to prevent copying.
    PlayerSprite& operator= (const PlayerSprite& rhs);
}; // Endclass.                         

// Player sprite pointer.
typedef std::shared_ptr<PlayerSprite>   PlayerSpritePtr;


// Routines.

extern  FolioStatus CreatePlayerSprite (FolioHandle         dcHandle, 
                                        PlayerSpritePtr&    playerSprite);
extern  FolioStatus StorePlayerSpriteBackground (Gdiplus::Graphics& graphics);
extern  FolioStatus RestorePlayerSpriteBackground (Gdiplus::Graphics& graphics);
extern  FolioStatus DrawPlayerSprite (Gdiplus::Graphics& graphics);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
