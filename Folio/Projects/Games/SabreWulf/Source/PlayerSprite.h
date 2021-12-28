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
    static  const   Folio::Core::Game::Action   ACTION_SWIPE_SWORD  = 0x00000001;    // Swipe sword action.
    static  const   Folio::Core::Game::Action   ACTION_FALLING      = 0x00000002;    // Falling action.
    static  const   Folio::Core::Game::Action   ACTION_SITTING      = 0x00000004;    // Sitting action.
    static  const   Folio::Core::Game::Action   ACTION_GAME_OVER    = 0x00000008;    // Game over action.

    PlayerSprite ();
    ~PlayerSprite ();

    FolioStatus Create (FolioHandle dcHandle);
    FolioStatus Start ();
    FolioStatus UpdateDirection (Folio::Core::Game::Direction   direction, 
                                 bool                           keyDown);
    FolioStatus CheckPlayerSprite (Gdiplus::Graphics&               graphics,
                                   CollisionGrid&                   collisionGrid,
                                   ObjectSpriteDrawingElementsList& screenObjectSpriteDrawingElementsList);

    FolioStatus SetFireKeyDown (bool fireKeyDown);
    FolioStatus SetGameOver ();

    bool    IsImmune () const;
    bool    IsSick () const;

    void    ResetJustFoundAmuletPiece ();
    bool    IsJustFoundAmuletPiece () const;

private:
    static  const   Int32   INITIAL_SCREEN_X_LEFT   = 120;  // The initial screen X left (in pixels) of the player sprite.
    static  const   Int32   INITIAL_SCREEN_Y_TOP    =  96;  // The initial screen Y top (in pixels) of the player sprite.

    static  const   UInt32  DEFAULT_SPEED       = 4;  // The default speed of the player sprite.
    static  const   UInt32  SWIPE_SWORD_SPEED   = 1;  // The speed of the player sprite when swipping the sword.
    static  const   UInt32  FAST_SPEED          = 8;  // The speed of the player sprite when its infection is SPEED.

    static  const   Folio::Core::Game::ZxSpectrum::COLOUR   INITIAL_COLOUR = Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE); // The initial colour of the player sprite.
    
    static  const   Folio::Core::Game::Direction    INITIAL_DIRECTION = Folio::Core::Game::W;   // The initial direction of the player sprite.

    UInt32  m_playerSpriteSpeed;    // The speed of the player sprite.

    // Infection enumeration.
    enum INFECTION
    {
        NO_INFECTION = 0,
        IMMUNITY,
        CONFUSION,
        SPEED,
        SICKNESS,
    }; // Endenum.

    INFECTION   m_infection;            // The player sprite's infection.
    UInt32      m_infectionTickCount;   // The infection tick count of the player sprite.

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

    bool    IsDead (const CollisionGrid::CellElement& cellElement);

    FolioStatus SetInfection (INFECTION                             infection,
                              Folio::Core::Game::ZxSpectrum::COLOUR playerSpriteColour);
    FolioStatus ClearInfection ();

    void    StartInfectionTickCount ();
    bool    IsInfection () const;
    bool    IsInfectionFinished () const;
    bool    IsInfectionImmunity () const;
    bool    IsInfectionConfusion () const;
    bool    IsInfectionSickness () const;

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
