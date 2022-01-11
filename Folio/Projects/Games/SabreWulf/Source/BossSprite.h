#pragma once

// STL includes.
#include    <memory>
#include    <vector>

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

// Boss sprite identifier enumeration.
enum BOSS_SPRITE_ID
{
    BOSS_SPRITE_UNDEFINED = Folio::Core::Game::AItem::ITEM_ID_UNDEFINED,
    BOSS_SPRITE_RHINOCEROS_1,
    BOSS_SPRITE_RHINOCEROS_2,
    BOSS_SPRITE_RHINOCEROS_3,
    BOSS_SPRITE_RHINOCEROS_4,
    BOSS_SPRITE_GUARDIAN,
}; // Endenum.


// Boss sprite.
class BossSprite : public Folio::Core::Game::ABossSprite
{
public:
    static  const   UInt32  DEFAULT_SPEED   = 1;  // The default speed of the boss sprite.
    static  const   UInt32  FAST_SPEED      = 2;  // The fast speed of the boss sprite.

    BossSprite ();
    ~BossSprite ();

    FolioStatus Create (FolioHandle                             dcHandle,
                        BOSS_SPRITE_ID                          bossSpriteId,
                        UInt32                                  initialScreenMapIndex,
                        Int32                                   initialScreenXLeft,
                        Int32                                   initialScreenYBottom,
                        Folio::Core::Game::Direction            initialDirection,
                        UInt32                                  initialSpeed,
                        Folio::Core::Game::ZxSpectrum::COLOUR   bossSpriteColour);
    FolioStatus CheckBossSprite (Folio::Core::Game::DrawingElementPtr&  drawingElement,
                                 Gdiplus::Graphics&                     graphics,
                                 bool&                                  onCurrentScreen,
                                 CollisionGrid&                         collisionGrid);
    FolioStatus ChangeDirection ();
    FolioStatus ChangeSpeed ();

    BOSS_SPRITE_ID  GetBossSpriteId () const;
    UInt32          GetBossSpriteScreenMapIndex () const;

private:  
    BOSS_SPRITE_ID  m_bossSpriteId;             // The identifier of the boss sprite.
    UInt32          m_bossSpriteScreenMapIndex; // The screen map index of the boss sprite.

    UInt32  m_bossSpriteSpeed;  // The speed of the boss sprite.

    FolioStatus Move (Folio::Core::Game::DrawingElementPtr& drawingElement,
                      Gdiplus::Graphics&                    graphics,
                      bool&                                 onCurrentScreen,
                      CollisionGrid&                        collisionGrid);

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

extern  FolioStatus CreateBossSpriteDrawingElements (FolioHandle dcHandle);
extern  FolioStatus CheckBossSprites (FolioHandle           dcHandle,
                                      Gdiplus::Graphics&    graphics,
                                      CollisionGrid&        collisionGrid);
extern  FolioStatus RemoveScreenBossSprites (CollisionGrid& collisionGrid);
extern  FolioStatus StoreScreenBossSpriteBackgrounds (Gdiplus::Graphics& graphics);
extern  FolioStatus RestoreScreenBossSpriteBackgrounds (Gdiplus::Graphics& graphics);
extern  FolioStatus DrawScreenBossSprites (Gdiplus::Graphics& graphics);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
