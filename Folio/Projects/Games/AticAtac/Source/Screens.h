#pragma once

// STL includes.
#include    <memory>
#include    <vector>

// "Home-made" includes.
#include    <Applet.h>
#include    <Game.h>
#include    "BackgroundItems.h"
#include    "BossSprites.h"
#include    "DrawingElement.h"
#include    "FallingSimulationScreen.h"
#include    "InformationPanel.h"
#include    "NastySprites.h"
#include    "PlayerSprites.h"
#include    "RoomGraphics.h"
#include    "StaticSprites.h"
#include    "WeaponSprites.h"
#include    "ZxSpectrum.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Initial  screen number.
const   UInt32  INITIAL_SCREEN_NUMBER = 0;

// Undefined screen number.
const   UInt32  SCREEN_NUMBER_UNDEFINED = -1;

// Screen.
class Screen
{
public:
    Screen ();
    Screen (UInt32              screenNumber,
            ROOM_ID             roomId,
            ZxSpectrum::COLOUR  roomColour);
    ~Screen ();

    void    SetCanvasBag (Folio::Core::Applet::CanvasBag &canvasBag);
    void    SetRoomGraphic (const RoomGraphicsMap &roomGraphicsMap);
    void    SetSpriteGraphicsMap (const SpriteGraphicsMap &spriteGraphicsMap);
    void    SetInformationPanel (const InformationPanel &informationPanel);

    UInt32              GetScreenNumber () const;
    ROOM_ID             GetRoomId () const;
    ZxSpectrum::COLOUR  GetRoomColour () const;

    void    SetBackgroundItemsList (const BackgroundItemsList &backgroundItemsList);
    void    SetStaticSpritesList (const StaticSpritesList &staticSpritesList);

    FolioStatus QueryDrawingElements (const PlayerSpritePtr                     &mainPlayer,
                                      Folio::Core::Game::DrawingElementsList    &drawingElementsList);
    FolioStatus HandleProcessFrame (bool    &isStarting,
                                    UInt32  *frameRateIncrement = 0);
    
    UInt32  MoveToNewScreen (const BackgroundItemsList &backgroundItemsList);

    FolioStatus StoreSpriteBackgrounds (Gdiplus::Graphics &graphics);
    FolioStatus RestoreSpriteBackgrounds (Gdiplus::Graphics &graphics);
    FolioStatus DrawSprites (Gdiplus::Graphics &graphics);

    FolioStatus AddGravestone ();

    static  UInt32  GetTotalNumRooms ();

private:
    static  const   UInt32  MAX_NUM_NASTY_SPRITES               = 3;            // The maximum number of nasty sprites that can be displayed on a screen.
    static  const   UInt32  MAX_REMOVE_NASTY_SPRITES_TICK_COUNT = 10 * 1000;    // The maximum tick count to remove the nasty sprites.
    
    Folio::Core::Applet::CanvasBag* m_canvasBag;            // The canvas bag.
    SpriteGraphicsMap*              m_spriteGraphicsMap;    // The sprite graphics map.
    InformationPanel*               m_informationPanel;     // The information panel.
    PlayerSpritePtr                 m_mainPlayer;           // The main player.

    UInt32                  m_screenNumber;                 // The screen number.
    ROOM_ID                 m_roomId;                       // The identifier of the room.
    ZxSpectrum::COLOUR      m_roomColour;                   // The colour of the room.
    RoomGraphicPtr          m_roomGraphic;                  // The room's graphic.
    UInt32                  m_exitScreenTickCount;          // The tick count when the screen was exited.
    UInt32                  m_createNastySpriteTickCount;   // Create nasty sprite tick count.

    BackgroundItemsList     m_backgroundItemsList;          // The screen's background items list.
    StaticSpritesList       m_staticSpritesList;            // The screen's static sprites list.

    Folio::Core::Game::DrawingElementsSet   m_drawingElementsSet;               // The screen's drawing elements set.
    StaticSpriteDrawingElementsList         m_staticSpriteDrawingElementsList;  // The screen's static sprite drawing elements list.
    NastySpriteDrawingElementsList          m_nastySpriteDrawingElementsList;   // The screen's nasty sprite drawing elements list.
    BossSpriteDrawingElement                m_bossSpriteDrawingElement;         // The screen's boss sprite drawing element.
    WeaponSpriteDrawingElement              m_weaponSpriteDrawingElement;       // The screen's weapon sprite drawing element.
    Folio::Core::Game::CollisionGrid        m_collisionGrid;                    // The screen's collision grid.

    FolioStatus InitialiseScreen ();
    FolioStatus UpdateScreen ();

    FolioStatus InitialiseDoors ();
    FolioStatus CheckDoors (bool buildingScreen = false);
    FolioStatus OpenDoor (BackgroundItem &backgroundItem);
    FolioStatus CloseDoor (BackgroundItem &backgroundItem);
    FolioStatus UpdateDoor (BackgroundItem  &backgroundItem,
                            bool            openDoor);
    bool    Screen::IsDoor(const BackgroundItem &backgroundItem) const;
    Folio::Core::Game::CollisionGrid::ScreenExit::STATE     GetDoorState (const BackgroundItem &backgroundItem) const;
    bool    CanDoorBeUnlocked (const BackgroundItem &backgroundItem) const;

    FolioStatus CheckSprites (Gdiplus::Graphics &graphics);

    FolioStatus InitialiseStaticSprites ();
    FolioStatus CheckStaticSprites (Gdiplus::Graphics &graphics);
    FolioStatus AddStaticSprite (const StaticSpritePtr &staticSprite);
    FolioStatus AddStaticSprite (STATIC_SPRITE_ID       staticSpriteId,
                                 const Gdiplus::Rect    &screenRect);
    FolioStatus RemoveStaticSprite (const StaticSpritePtr &staticSprite);
    StaticSpriteDrawingElementsList::iterator   FindStaticSprite (const StaticSpritePtr &staticSprite);

    FolioStatus CheckNastySprites (Gdiplus::Graphics &graphics);
    FolioStatus StartNastySprites (Gdiplus::Graphics &graphics);
    FolioStatus AddNastySprite (NASTY_SPRITE_ID nastySpriteId);
    FolioStatus RemoveNastySprites ();
    FolioStatus KillNastySprites ();
    void    SetCreateNastySpriteTickCount (UInt32   currentTickCount, 
                                           UInt32   minNumSeconds, 
                                           UInt32   maxNumSeconds);

    FolioStatus CheckBossSprite (Gdiplus::Graphics &graphics);
    FolioStatus StartBossSprite ();
    FolioStatus AddBossSprite (BOSS_SPRITE_ID bossSpriteId);

    FolioStatus CheckWeaponSprite (Gdiplus::Graphics &graphics);
    FolioStatus StartWeaponSprite ();
    FolioStatus AddWeaponSprite (WEAPON_SPRITE_ID weaponSpriteId);
    FolioStatus RemoveWeaponSprite ();

    FolioStatus CheckMainPlayer (Gdiplus::Graphics &graphics);
    FolioStatus ProcessMainPlayer (Gdiplus::Graphics &graphics);

    FolioStatus HandleCollision (const Folio::Core::Game::CollisionGrid::CellElements   &cellCollisionElements,
                                 bool                                                   mainPlayer = true);
    FolioStatus HandleSolidItemCollision (const Folio::Core::Game::DrawingElement   &drawingElement,
                                           bool                                     mainPlayer = true);
    FolioStatus HandleCollectableItemCollision (const Folio::Core::Game::DrawingElement &drawingElement,
                                                bool                                    mainPlayer = true);
    FolioStatus HandleHealthItemCollision (const Folio::Core::Game::DrawingElement  &drawingElement,
                                           bool                                     mainPlayer = true);
    FolioStatus HandleHarmfulItemCollision (const Folio::Core::Game::DrawingElement &drawingElement,
                                            bool                                    mainPlayer = true);
    FolioStatus HandleNastySpriteCollision (const Folio::Core::Game::DrawingElement &drawingElement,
                                            bool                                    mainPlayer = true);
    FolioStatus HandleBossSpriteCollision (const Folio::Core::Game::DrawingElement  &drawingElement,
                                           bool                                     mainPlayer = true);

    FolioStatus DecrementMainPlayerHealth (UInt32 healthDecrement);
    FolioStatus IncrementMainPlayerHealth (UInt32 healthIncrement);

    FolioStatus AddDroppedItem (InformationPanel::DroppedItem &droppedItem);

    FolioStatus InitialiseCollisionGrid ();
    FolioStatus AddCollisionGridDrawingElements (const Folio::Core::Game::DrawingElementsList &drawingElementsList);
    FolioStatus AddCollisionGridDrawingElement (const Folio::Core::Game::DrawingElement &drawingElement);
    FolioStatus RemoveCollisionGridDrawingElement (const Folio::Core::Game::DrawingElement &drawingElement);
    FolioStatus UpdateCollisionGridDrawingElement (const Folio::Core::Game::DrawingElement &drawingElement);

    FolioStatus AddBackgroundItemDrawingElements (const Folio::Core::Game::DrawingElementsList &drawingElementsList);

    FolioStatus BuildScreenDrawingElements ();
    FolioStatus RemoveScreenDrawingElements (Folio::Core::Game::DrawingElement::UserData userData);
    FolioStatus RemoveScreenDrawingElements (DRAWING_ELEMENT_ID drawingElementId);

    UInt32  GetFrameRateIncrement () const;
}; // Endclass.

// Screens list.
typedef std::vector<Screen> ScreensList;
             

// Routines.

extern  FolioStatus BuildScreens (Folio::Core::Applet::CanvasBag    &canvasBag,
                                  const RoomGraphicsMap             &roomGraphicsMap,
                                  const BackgroundItemGraphicsMap   &backgroundItemGraphicsMap,
                                  const SpriteGraphicsMap           &spriteGraphicsMap,
                                  const BackgroundItemsList         &backgroundItemsList,
                                  const StaticSpritesList           &staticSpritesList,
                                  const InformationPanel            &informationPanel,
                                  ScreensList                       &screensList);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
