#pragma once

// STL includes.
#include    <map>
#include    <memory>
#include    <vector>

// "Home-made" includes.
#include    <Game.h>
#include    "CollisionGrid.h"
#include    "InformationPanel.h"
#include    "NastySprite.h"
#include    "StaticSprite.h"

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
    // Boss sprite flags.
    static  const   UInt32  FLAGS_NONE                      = NastySprite::FLAGS_NONE;
    static  const   UInt32  FLAGS_INITIALISED_BY_GRAPHIC    = NastySprite::FLAGS_INITIALISED_BY_GRAPHIC;
    static  const   UInt32  FLAGS_TERMINATED_BY_GRAPHIC     = NastySprite::FLAGS_TERMINATED_BY_GRAPHIC;
    
    BossSprite ();
    ~BossSprite ();

    FolioStatus Create (FolioHandle                             dcHandle,
                        BOSS_SPRITE_ID                          bossSpriteId,
                        Folio::Core::Game::ZxSpectrum::COLOUR   bossSpriteColour,
                        UInt32                                  bossSpriteFlags = FLAGS_NONE);
    FolioStatus Start (const InformationPanel   &informationPanel,
                       const CollisionGrid      &collisionGrid);
    FolioStatus Move (Gdiplus::Graphics         &graphics,
                      const InformationPanel    &informationPanel,
                      CollisionGrid             &collisionGrid);

    BOSS_SPRITE_ID  GetBossSpriteId () const;
    UInt32          GetBossSpriteFlags () const;

    bool    CanBeKilled (const InformationPanel &informationPanel) const;

    static  BOSS_SPRITE_ID  GetScreenBossSpriteId (UInt32   screenNumber, 
                                                   UInt32   totalNumRooms);

private:
    static  const   UInt32  BOSS_SPRITE_SPEED = 1;  // Boss sprite speed.

    BOSS_SPRITE_ID  m_bossSpriteId;     // The identifier of the boss sprite.
    UInt32          m_bossSpriteFlags;  // The flags of the boss sprite.

    static  Folio::Core::Game::SpriteStationarySoundSamplesList m_bossSpriteTerminatingSoundSamplesList;    // The boss sprite's terminating sound samples.

    FolioStatus SetInitialisingMode (FolioHandle                            dcHandle,
                                     Folio::Core::Game::ZxSpectrum::COLOUR  bossSpriteColour,
                                     UInt32                                 bossSpriteFlags);
    FolioStatus SetTerminatingMode (FolioHandle                             dcHandle,
                                    Folio::Core::Game::ZxSpectrum::COLOUR   bossSpriteColour,
                                    UInt32                                  bossSpriteFlags);

    bool    IsUpdateDirectionRqd (const CollisionGrid &collisionGrid) const;
    Folio::Core::Game::Direction    GetDirection (const InformationPanel    &informationPanel,
                                                  const CollisionGrid       &collisionGrid) const;
    Folio::Core::Game::Direction    GetDirectionToAttractedStaticSprite (const CollisionGrid    &collisionGrid,
                                                                         bool                   &staticSpriteFound) const;
    
    UInt32  GetSpeed (const InformationPanel    &informationPanel,
                      const CollisionGrid       &collisionGrid) const;
    
    UInt32  GetSpeedToAttractedStaticSprite (const CollisionGrid    &collisionGrid,
                                             bool                   &staticSpriteFound) const;
    bool    IsAnyAttractedStaticSprite (const CollisionGrid &collisionGrid) const;

    static  Int32   GetInitialScreenXLeft (BOSS_SPRITE_ID       bossSpriteId,
                                           const CollisionGrid  &collisionGrid);
    static  Int32   GetInitialScreenYTop (BOSS_SPRITE_ID        bossSpriteId,
                                          const CollisionGrid   &collisionGrid);
    
    static  bool    IsAttractedToStaticSprite (BOSS_SPRITE_ID       bossSpriteId,
                                               const StaticSprite   &staticSprite);

    static  Folio::Core::Game::SpriteStationarySoundSamplesList GetBossSpriteTerminatingSoundSamples ();

    // Private copy constructor to prevent copying.
    BossSprite (const BossSprite& rhs);

    // Private assignment operator to prevent copying.
    BossSprite& operator= (const BossSprite& rhs);
}; // Endclass.                         

// Boss sprite pointer.
typedef std::shared_ptr<BossSprite> BossSpritePtr;

// Boss sprites map.
typedef std::map<BOSS_SPRITE_ID, BossSpritePtr> BossSpritesMap;

// Boss sprite drawing element.
typedef Folio::Core::Game::SpriteDrawingElement<BossSpritePtr> BossSpriteDrawingElement;

// Boss sprite drawing elements list.
typedef std::vector<BossSpriteDrawingElement> BossSpriteDrawingElementsList;


// Routines.

FolioStatus CreateBossSprites (FolioHandle      dcHandle,
                               BossSpritesMap   &bossSpritesMap);
void    SetBossSpritesAlive (BossSpritesMap &bossSpritesMap);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
