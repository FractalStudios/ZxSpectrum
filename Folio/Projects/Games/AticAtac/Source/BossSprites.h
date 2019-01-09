#pragma once

// STL includes.
#include    <memory>
#include    <vector>

// "Home-made" includes.
#include    <Applet.h>
#include    <Game.h>
#include    "InformationPanel.h"
#include    "NastySprites.h"
#include    "PlayerSprites.h"
#include    "SpriteGraphics.h"
#include    "StaticSprites.h"
#include    "ZxSpectrum.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Boss sprite identifier enumeration.
enum BOSS_SPRITE_ID
{
    BOSS_SPRITE_UNDEFINED = Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_ID_UNDEFINED,
    BOSS_SPRITE_MUMMY = 0,            
    BOSS_SPRITE_HUNCHBACK,             
    BOSS_SPRITE_DRACULA,             
    BOSS_SPRITE_FRANKENSTEIN,              
    BOSS_SPRITE_DEVIL,             
}; // Endenum.


// Boss sprite.
class BossSprite : public Folio::Core::Game::ABossSprite
{
public:
    BossSprite ();
    ~BossSprite ();

    FolioStatus Create (FolioHandle                             dcHandle,
                        BOSS_SPRITE_ID                          bossSpriteId,
                        const SpriteGraphicsMap                 &spriteGraphicsMap,
                        const PlayerSpritePtr                   &mainPlayer,                
                        const InformationPanel                  &informationPanel,
                        const Folio::Core::Game::CollisionGrid  &collisionGrid);                
    FolioStatus Reset (const Folio::Core::Game::CollisionGrid   &collisionGrid,
                       bool                                     &removeBossSprite);
    FolioStatus Move (Gdiplus::Graphics                 &graphics,
                      const InformationPanel            &informationPanel,
                      Folio::Core::Game::CollisionGrid  &collisionGrid);

    BOSS_SPRITE_ID  GetBossSpriteId () const;
    UInt32          GetBossSpriteFlags () const;

    bool    CanBeKilled (const InformationPanel &informationPanel) const;

private:
    static  const   UInt32  BOSS_SPRITE_SPEED = 1;  // Boss sprite speed.

    PlayerSpritePtr m_mainPlayer;   // The main player.

    BOSS_SPRITE_ID      m_bossSpriteId;     // The identifier of the boss sprite.
    UInt32              m_bossSpriteFlags;  // The flags of the boss sprite.

    SpriteGraphicsList  m_bossSpriteInitialisingGraphics;   // The initialising graphics of the boss sprite.
    SpriteGraphicsList  m_bossSpriteTerminatingGraphics;    // The terminating graphics of the boss sprite.

    FolioStatus SetInitialisingMode (FolioHandle                dcHandle,
                                     const SpriteGraphicsMap    &spriteGraphicsMap,
                                     ZxSpectrum::COLOUR         bossSpriteColour,
                                     UInt32                     bossSpriteFlags);
    FolioStatus SetTerminatingMode (FolioHandle             dcHandle,
                                    const SpriteGraphicsMap &spriteGraphicsMap,
                                    ZxSpectrum::COLOUR      bossSpriteColour,
                                    UInt32                  bossSpriteFlags);

    bool        IsUpdateDirectionRqd (const Folio::Core::Game::CollisionGrid &collisionGrid) const;
    Direction   GetDirection (const InformationPanel                    &informationPanel,
                              const Folio::Core::Game::CollisionGrid    &collisionGrid) const;
    Direction   GetDirectionToAttractedStaticSprite (const Folio::Core::Game::CollisionGrid &collisionGrid,
                                                     bool                                   &staticSpriteFound) const;
    UInt32      GetSpeed (const InformationPanel                    &informationPanel,
                          const Folio::Core::Game::CollisionGrid    &collisionGrid) const;
    UInt32      GetSpeedToAttractedStaticSprite (const Folio::Core::Game::CollisionGrid &collisionGrid,
                                                 bool                                   &staticSpriteFound) const;
    bool    IsAnyAttractedStaticSprite (const Folio::Core::Game::CollisionGrid &collisionGrid) const;

    static  Int32               GetInitialScreenXLeft (BOSS_SPRITE_ID                           bossSpriteId,
                                                       const PlayerSpritePtr                    &mainPlayer,
                                                       const Folio::Core::Game::CollisionGrid   &collisionGrid);
    static  Int32               GetInitialScreenYTop (BOSS_SPRITE_ID                            bossSpriteId,
                                                      const PlayerSpritePtr                     &mainPlayer,
                                                      const Folio::Core::Game::CollisionGrid    &collisionGrid);
    static  ZxSpectrum::COLOUR  GetColour (BOSS_SPRITE_ID bossSpriteId);
    static  UInt32              GetBossSpriteFlags (BOSS_SPRITE_ID bossSpriteId);
    static  bool                IsAttractedToStaticSprite (BOSS_SPRITE_ID       bossSpriteId,
                                                           const StaticSprite   &staticSprite);

    // Private copy constructor to prevent copying.
    BossSprite (const BossSprite& rhs);

    // Private assignment operator to prevent copying.
    BossSprite& operator= (const BossSprite& rhs);
}; // Endclass.                         

// Boss sprite pointer.
typedef std::shared_ptr<BossSprite> BossSpritePtr;

// Boss sprites list.
typedef std::vector<BossSpritePtr>  BossSpritesList;

// Boss sprite drawing element.
typedef Folio::Core::Game::SpriteDrawingElement<BossSpritePtr> BossSpriteDrawingElement;

// Boss sprite drawing elements list.
typedef std::vector<BossSpriteDrawingElement> BossSpriteDrawingElementsList;


// Routines.

BOSS_SPRITE_ID  GetScreenBossSpriteId (UInt32   screenNumber, 
                                       UInt32   totalNumRooms);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
