#pragma once

// STL includes.
#include    <memory>
#include    <vector>

// "Home-made" includes.
#include    <Applet.h>
#include    <Game.h>
#include    "BackgroundItem.h"
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

// Min/Max screen number.
const   UInt32  MIN_SCREEN_NUMBER = 0;
const   UInt32  MAX_SCREEN_NUMBER = 148;

// Initial screen number.
const   UInt32  INITIAL_SCREEN_NUMBER = 0;

// Undefined screen number.
const   UInt32  SCREEN_NUMBER_UNDEFINED = -1;

// The maximum nasty sprites that can be displayed on a screen.
const   UInt32  MAX_NASTY_SPRITES_PER_SCREEN = 3;


// Screen.
class Screen
{
public:
    Screen ();
    Screen (UInt32                                  screenNumber,
            ROOM_ID                                 roomId,
            Folio::Core::Game::ZxSpectrum::COLOUR   roomColour);
    ~Screen ();

    void    SetCanvas (Folio::Core::Applet::Canvas &canvas);
    void    SetBackgroundItemsList (const BackgroundItemsList &backgroundItemsList);
    void    SetStaticSpritesList (const StaticSpritesList &staticSpritesList);
    void    SetInformationPanel (const InformationPanel &informationPanel);

    UInt32                                  GetScreenNumber () const;
    ROOM_ID                                 GetRoomId () const;
    Folio::Core::Game::ZxSpectrum::COLOUR   GetRoomColour () const;

    FolioStatus QueryDrawingElements (Folio::Core::Game::DrawingElementsList &drawingElementsList);
    FolioStatus HandleProcessFrame (bool &isStarting);
    FolioStatus QueryNewScreen (UInt32 &newScreenNumber);

    FolioStatus StoreSpriteBackgrounds (Gdiplus::Graphics &graphics);
    FolioStatus RestoreSpriteBackgrounds (Gdiplus::Graphics &graphics);
    FolioStatus DrawSprites (Gdiplus::Graphics &graphics);

    FolioStatus AddGravestone ();

    static  UInt32  GetTotalNumRooms ();

private:
    static  const   UInt32  MAX_REMOVE_NASTY_SPRITES_TICK_COUNT = 10 * 1000;    // The maximum tick count to remove the nasty sprites.
    static  const   UInt32  MAX_OPEN_CLOSE_DOORS_TICK_COUNT     = 15 * 1000;    // The maximum tick count to open/close the screen's doors.
    
    Folio::Core::Applet::Canvas*    m_canvas;           // The canvas.
    InformationPanel*               m_informationPanel; // The information panel.

    bool                                    m_screenInitialised;            // Indicates if the screen is initialised.
    UInt32                                  m_screenNumber;                 // The screen number.
    ROOM_ID                                 m_roomId;                       // The identifier of the room.
    Folio::Core::Game::ZxSpectrum::COLOUR   m_roomColour;                   // The colour of the room.
    UInt32                                  m_exitScreenTickCount;          // The tick count when the screen was exited.
    UInt32                                  m_createNastySpriteTickCount;   // Create nasty sprite tick count.

    BackgroundItemsList m_backgroundItemsList;  // The screen's background items list.
    StaticSpritesList   m_staticSpritesList;    // The screen's static sprites list.
    CollisionGrid       m_collisionGrid;        // The screen's collision grid.

    Folio::Core::Game::DrawingElementsSet   m_drawingElementsSet;               // The screen's drawing elements set (room, background items and information panel).
    StaticSpriteDrawingElementsList         m_staticSpriteDrawingElementsList;  // The screen's static sprite drawing elements list.

    static  bool    m_playEnteredScreenSound;               // Indicates if the entered screen sound should be played.
    static  UInt32  m_currentEnteredScreenSoundSampleIndex; // The current entered screen sound sample index.
    static  Folio::Core::Util::Sound::SoundSamplesList  m_enteredScreenSoundSamples;  // The entered screen sound samples.

    static  Folio::Core::Util::Sound::SoundSample   m_openDoorSoundSample;  // The open door sound sample.
    static  Folio::Core::Util::Sound::SoundSample   m_closeDoorSoundSample; // The close door sound sample.

    bool    IsScreenInitialised () const;

    FolioStatus InitialiseScreen ();
    FolioStatus EnterScreen ();
    FolioStatus ExitScreen ();

    FolioStatus InitialiseDoors ();
    FolioStatus CheckDoors (bool enteringScreen = false);
    FolioStatus OpenDoor (BackgroundItem    &backgroundItem,
                          bool              enteringScreen = false);
    FolioStatus CloseDoor (BackgroundItem   &backgroundItem,
                           bool             enteringScreen = false);
    FolioStatus UpdateDoor (BackgroundItem  &backgroundItem,
                            bool            openDoor,
                            bool            enteringScreen = false);
    bool    Screen::IsDoor (const BackgroundItem &backgroundItem) const;
    CollisionGrid::ScreenExit::STATE    GetDoorState (const BackgroundItem &backgroundItem) const;
    bool    CanDoorBeUnlocked (const BackgroundItem &backgroundItem) const;

    FolioStatus CheckSprites (Gdiplus::Graphics &graphics);

    FolioStatus BuildStaticSprites (bool initialise);
    FolioStatus CheckStaticSprites (Gdiplus::Graphics &graphics);
    FolioStatus AddStaticSprite (const StaticSpritePtr  &staticSprite,
                                 bool                   addToStaticSpritesList = true);
    FolioStatus AddStaticSprite (STATIC_SPRITE_ID       staticSpriteId,
                                 const Gdiplus::Rect    &screenRect);
    FolioStatus RemoveStaticSprite (const StaticSpritePtr &staticSprite);
    StaticSpriteDrawingElementsList::iterator   FindStaticSprite (const StaticSpritePtr &staticSprite);

    FolioStatus CheckNastySprites (Gdiplus::Graphics &graphics);
    FolioStatus StartNastySprites (Gdiplus::Graphics    &graphics, 
                                   UInt32               numNastySpritesOnScreen);
    FolioStatus AddNastySprite (NASTY_SPRITE_ID nastySpriteId);
    FolioStatus RemoveNastySprites (bool onScreenEntry = true);
    FolioStatus StoreNastySpriteBackgrounds (Gdiplus::Graphics &graphics);
    FolioStatus RestoreNastySpriteBackgrounds (Gdiplus::Graphics &graphics);
    FolioStatus DrawNastySprites (Gdiplus::Graphics &graphics);
    UInt32  GetNumNastySpritesOnScreen () const;
    
    void    SetCreateNastySpriteTickCount (UInt32   currentTickCount, 
                                           UInt32   minNumSeconds, 
                                           UInt32   maxNumSeconds);

    FolioStatus CheckBossSprite (Gdiplus::Graphics &graphics);
    FolioStatus StartBossSprite ();
    FolioStatus AddBossSprite ();
    FolioStatus RemoveBossSprite (bool onScreenExit = true);

    FolioStatus CheckWeaponSprite (Gdiplus::Graphics &graphics);
    FolioStatus StartWeaponSprite ();
    FolioStatus AddWeaponSprite ();
    FolioStatus RemoveWeaponSprite (bool bPlayTerminatedSound = true);

    FolioStatus CheckMainPlayer (Gdiplus::Graphics &graphics);
    FolioStatus ProcessMainPlayer (Gdiplus::Graphics &graphics);

    FolioStatus HandleCollision (const CollisionGrid::CellElements  &cellElements,
                                 bool                               mainPlayer = true);
    FolioStatus HandleSolidItemCollision (const CollisionGrid::CellElement  &cellElement,
                                           bool                             mainPlayer = true);
    FolioStatus HandleCollectableItemCollision (const CollisionGrid::CellElement    &cellElement,
                                                bool                                mainPlayer = true);
    FolioStatus HandleHealthItemCollision (const CollisionGrid::CellElement &cellElement,
                                           bool                             mainPlayer = true);
    FolioStatus HandleHarmfulItemCollision (const CollisionGrid::CellElement    &cellElement,
                                            bool                                mainPlayer = true);
    FolioStatus HandleNastySpriteCollision (const CollisionGrid::CellElement    &cellElement,
                                            bool                                mainPlayer = true);
    FolioStatus HandleBossSpriteCollision (const CollisionGrid::CellElement &cellElement,
                                           bool                             mainPlayer = true);

    FolioStatus DecrementMainPlayerHealth (UInt32 healthDecrement);
    FolioStatus IncrementMainPlayerHealth (UInt32 healthIncrement);
    FolioStatus HandleMainPlayerDead ();

    FolioStatus AddDroppedItem (InformationPanel::DroppedItem &droppedItem);

    FolioStatus BuildScreenDrawingElements (bool initialise);
    FolioStatus BuildRoomDrawingElements (FolioHandle   dcHandle, 
                                          bool          initialise);
    FolioStatus BuildBackgroundItemDrawingElements (FolioHandle dcHandle,
                                                    bool        initialise);
    FolioStatus BuildInformationPanelDrawingElements (FolioHandle   dcHandle,
                                                      bool          initialise);

    FolioStatus AddBackgroundItemDrawingElements (const Folio::Core::Game::DrawingElementsList &drawingElementsList);
    FolioStatus RemoveBackgroundItemDrawingElements (const Folio::Core::Game::DrawingElementsList &drawingElementsList);

    FolioStatus AddScreenDrawingElements (const Folio::Core::Game::DrawingElementsList  &drawingElementsList, 
                                          bool                                          addToCollisionGrid = true);
    FolioStatus RemoveScreenDrawingElements (const Folio::Core::Game::DrawingElementsList   &drawingElementsList,
                                             bool                                           removeFromCollisionGrid = true);
    FolioStatus RemoveScreenDrawingElements (Folio::Core::Game::DrawingElement::UserData userData);
    Folio::Core::Game::DrawingElementsList  FindScreenDrawingElements (Folio::Core::Game::DrawingElement::UserData userData) const;

    FolioStatus InitialiseCollisionGrid ();
    FolioStatus AddCollisionGridDrawingElements (const Folio::Core::Game::DrawingElementsList &drawingElementsList);
    FolioStatus AddCollisionGridDrawingElement (const Folio::Core::Game::DrawingElement &drawingElement);
    FolioStatus RemoveCollisionGridDrawingElements (const Folio::Core::Game::DrawingElementsList &drawingElementsList);
    FolioStatus RemoveCollisionGridDrawingElement (const Folio::Core::Game::DrawingElement &drawingElement);
    FolioStatus UpdateCollisionGridDrawingElement (const Folio::Core::Game::DrawingElement &drawingElement);

    FolioStatus ReleaseResourceGraphics ();

    static  void    CreateScreenSoundSamples ();
    static  void    CreateEnteredScreenSoundSamples ();

    static  void    PlayScreenSounds ();
    static  bool    PlayEnteredScreenSound ();
}; // Endclass.

// Screens list.
typedef std::vector<Screen> ScreensList;
             

// Routines.

extern  FolioStatus BuildScreens (Folio::Core::Applet::Canvas   &canvas,
                                  const BackgroundItemsList     &backgroundItemsList,
                                  const StaticSpritesList       &staticSpritesList,
                                  const InformationPanel        &informationPanel,
                                  ScreensList                   &screensList);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
