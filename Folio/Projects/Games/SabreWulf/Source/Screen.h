#pragma once

// STL includes.
#include    <memory>
#include    <vector>

// "Home-made" includes.
#include    <Applet.h>
#include    <Game.h>
#include    "BackgroundItem.h"
//#include    "BossSprite.h"
#include    "CollisionGrid.h"
#include    "InformationPanel.h"
#include    "NastySprite.h"
#include    "ObjectSprite.h"
#include    "OrchidSprite.h"
#include    "PlayerSprite.h"
#include    "ScreenBackground.h"
#include    "ScreenMap.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Screen.
class Screen
{
public:
    Screen (Folio::Core::Applet::Canvas &canvas,
            const ScreenMapPtr          &screenMap,
            const InformationPanelPtr   &informationPanel,
            const BackgroundItemsList   &backgroundItemsList,
            const SpriteGraphicsMapPtr  &spriteGraphicsMap);
    ~Screen ();

    FolioStatus Draw (const PlayerSpritePtr &playerSprite, 
                      OrchidSpritePtr       &orchidSprite);
    FolioStatus HandleProcessFrame (bool    &isStarting,
                                    UInt32  *frameRateIncrement = 0);
    
private:
    static  const   Int32   SCREEN_X_ORIGIN = 0;
    static  const   Int32   SCREEN_Y_ORIGIN = 16;
    static  const   Int32   SCREEN_WIDTH    = Folio::Core::Game::ZxSpectrum::MAX_SCREEN_X_PIXELS;
    static  const   Int32   SCREEN_HEIGHT   = Folio::Core::Game::ZxSpectrum::MAX_SCREEN_Y_PIXELS - SCREEN_Y_ORIGIN;

    static  const   UInt32  MAX_NUM_NASTY_SPRITES = 1;  // The maximum number of nasty sprites that can be displayed on a screen.

    Gdiplus::Rect   m_screenScreenRect; // The screen's screen rect.

    Folio::Core::Applet::Canvas &m_canvas;          // The canvas.
    ScreenMapPtr                m_screenMap;        // The screen map.
    InformationPanelPtr         m_informationPanel; // The information panel.

    UInt32  m_exitScreenTickCount;          // The tick count when the screen was exited.
    UInt32  m_createNastySpriteTickCount;   // The create nasty sprite tick count.

    BackgroundItemsList             m_backgroundItemsList;              // The screen's background items list.
    SpriteGraphicsMapPtr            m_spriteGraphicsMap;                // The screen's sprite graphics.
    ObjectSpriteDrawingElementsList m_objectSpriteDrawingElementsList;  // The screen's object sprite drawing elements list.
    OrchidSpriteDrawingElement      m_orchidSpriteDrawingElement;       // The screen's orchid sprite drawing element.
    NastySpriteDrawingElementsList  m_nastySpriteDrawingElementsList;   // The screen's nasty sprite drawing elements list.
    //BossSpriteDrawingElement                m_bossSpriteDrawingElement;         // The screen's boss sprite drawing element.

    CollisionGrid   m_collisionGrid;    // The screen's collision grid.

    PlayerSpritePtr m_playerSprite; // The player sprite.

    FolioStatus QueryDrawingElements (FolioHandle                               dcHandle,
                                      Folio::Core::Game::DrawingElementsList    &drawingElementsList);
    FolioStatus InitialiseScreen (FolioHandle                                   dcHandle,
                                  const Folio::Core::Game::DrawingElementsList  &drawingElementsList,
                                  const PlayerSpritePtr                         &playerSprite,
                                  OrchidSpritePtr                               &orchidSprite);
    FolioStatus UpdateScreen (FolioHandle                                   dcHandle,
                              const Folio::Core::Game::DrawingElementsList  &drawingElementsList,
                              OrchidSpritePtr                               &orchidSprite);

    FolioStatus InitialiseCollisionGrid (const Folio::Core::Game::DrawingElementsList &drawingElementsList);
    FolioStatus InitialiseSprites (FolioHandle      dcHandle,
                                   OrchidSpritePtr  &orchidSprite);

    FolioStatus StoreSpriteBackgrounds (Gdiplus::Graphics &graphics);
    FolioStatus RestoreSpriteBackgrounds (Gdiplus::Graphics &graphics);
    FolioStatus DrawSprites (Gdiplus::Graphics &graphics);
    FolioStatus CheckSprites (Gdiplus::Graphics &graphics);

    UInt32  MoveToNewScreen ();

    FolioStatus InitialiseObjectSprites (FolioHandle dcHandle);
    FolioStatus CheckObjectSprites (Gdiplus::Graphics &graphics);
    FolioStatus AddObjectSprite (const ObjectSpritePtr &objectSprite);

    FolioStatus InitialiseOrchidSprite (OrchidSpritePtr &orchidSprite);
    FolioStatus UpdateOrchidSprite (OrchidSpritePtr &orchidSprite);
    FolioStatus CheckOrchidSprite (Gdiplus::Graphics &graphics);

    FolioStatus CheckNastySprites (Gdiplus::Graphics &graphics);
    FolioStatus StartNastySprites (Gdiplus::Graphics &graphics);
    FolioStatus AddNastySprite (NASTY_SPRITE_ID nastySpriteId);
    FolioStatus RemoveNastySprites ();
    FolioStatus KillNastySprites ();

    //FolioStatus CheckBossSprite (Gdiplus::Graphics &graphics);
    //FolioStatus StartBossSprite ();
    //FolioStatus AddBossSprite (BOSS_SPRITE_ID bossSpriteId);
    //FolioStatus RemoveBossSprite ();

    FolioStatus CheckPlayer (Gdiplus::Graphics &graphics);
    FolioStatus HandleSickPlayer ();
    FolioStatus HandleDeadPlayer ();

    FolioStatus HandleCollision (const CollisionGrid::CellElements  &cellElements,
                                 bool                               player = true);
    FolioStatus HandleItemCollision (const CollisionGrid::CellElement   &cellElement,
                                     bool                               player = true);
    FolioStatus HandleSolidItemCollision (const CollisionGrid::CellElement  &cellElement,
                                          bool                              player = true);
    FolioStatus HandleCollectableItemCollision (const CollisionGrid::CellElement    &cellElement,
                                                bool                                player = true);
    FolioStatus HandleNastySpriteCollision (const CollisionGrid::CellElement    &cellElement,
                                            bool                                player = true);
    //FolioStatus HandleBossSpriteCollision (const CollisionGrid::CellElement  &cellElement,
    //                                       bool                              player = true);

    // Private copy constructor to prevent copying.
    Screen (const Screen& rhs);

    // Private assignment operator to prevent copying.
    Screen& operator= (const Screen& rhs);
}; // Endclass.

// Screen pointer.
typedef std::shared_ptr<Screen> ScreenPtr;
             
// Screens list.
typedef std::vector<ScreenPtr>  ScreensList;


// Routines.

extern  FolioStatus BuildScreens (Folio::Core::Applet::Canvas   &canvas,
                                  const ScreenMapPtr            &screenMap,
                                  const InformationPanelPtr     &informationPanel,
                                  const ScreenBackgroundsMap    &screenBackgroundsMap,
                                  const SpriteGraphicsMapPtr    &spriteGraphicsMap,
                                  ScreensList                   &screensList);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
