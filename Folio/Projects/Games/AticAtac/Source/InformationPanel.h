#pragma once

// STL includes.
#include    <memory>
#include    <list>

// "Home-made" includes.
#include    <Applet.h>
#include    <Game.h>
#include    <Util.h>
#include    "RoomGraphics.h"
#include    "StaticSprites.h"
#include    "ZxSpectrum.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Information panel item identifier enumeration.
enum INFORMATION_PANEL_ITEM_ID
{
    INFORMATION_PANEL_ITEM_UNDEFINED = Folio::Core::Game::AItem::ITEM_ID_UNDEFINED,
    INFORMATION_PANEL_ITEM_SCROLL,
    INFORMATION_PANEL_ITEM_SCROLL_SEAL,
    INFORMATION_PANEL_ITEM_HELD_ITEM_1,
    INFORMATION_PANEL_ITEM_HELD_ITEM_2,
    INFORMATION_PANEL_ITEM_HELD_ITEM_3,
    INFORMATION_PANEL_ITEM_TIME_TEXT,
    INFORMATION_PANEL_ITEM_TIME_VALUE,
    INFORMATION_PANEL_ITEM_SCORE_TEXT,
    INFORMATION_PANEL_ITEM_SCORE_VALUE,
    INFORMATION_PANEL_ITEM_TURKEY_CARCASS,
    INFORMATION_PANEL_ITEM_TURKEY,
    INFORMATION_PANEL_ITEM_PLAYER_LIFE_1,
    INFORMATION_PANEL_ITEM_PLAYER_LIFE_2,
    INFORMATION_PANEL_ITEM_PLAYER_LIFE_3,
}; // Endenum.


// Information panel.
class InformationPanel
{
public:
    static  const   Int32   PLAYER_HEALTH_HEALTH_ITEM_INCREMENT     = 15;
    static  const   Int32   PLAYER_HEALTH_DECREMENT                 = 3;
    static  const   Int32   PLAYER_HEALTH_TIME_DECREMENT            = PLAYER_HEALTH_DECREMENT;    
    static  const   Int32   PLAYER_HEALTH_HARMFUL_ITEM_DECREMENT    = 1;    
    static  const   Int32   PLAYER_HEALTH_NASTY_SPRITE_DECREMENT    = 3;
    static  const   Int32   PLAYER_HEALTH_BOSS_SPRITE_DECREMENT     = 1;

    static  const   UInt32  SCORE_NASTY_SPRITE_DEAD = 155;
    static  const   UInt32  SCORE_BOSS_SPRITE_DEAD  = 1155;

    InformationPanel ();
    ~InformationPanel ();

    FolioStatus Create (Folio::Core::Applet::Canvas &canvas,
                        UInt32                      totalNumRooms,
                        UInt16                      mainPlayerBitmapResourceId);
    FolioStatus QueryDrawingElements (FolioHandle                               dcHandle,
                                      ZxSpectrum::COLOUR                        roomColour,
                                      Folio::Core::Game::DrawingElementsList    &drawingElementsList);
    FolioStatus HandleProcessFrame (bool    &isStarting,
                                    bool    &mainPlayerIsDead);

    // Held item.
    struct HeldItem
    {      
        HeldItem (INFORMATION_PANEL_ITEM_ID itemId = INFORMATION_PANEL_ITEM_UNDEFINED)
        :   m_itemId(itemId)
        {} // Endproc.

        HeldItem (const StaticSpritePtr &staticSprite) 
        :   m_itemId(INFORMATION_PANEL_ITEM_UNDEFINED),
            m_staticSprite(staticSprite)
        {} // Endproc.

        bool    IsPopulated () const
        {
            return (m_staticSprite != 0);
        } // Endproc.

        INFORMATION_PANEL_ITEM_ID   m_itemId;       // The information panel item identifier of the held item.
        StaticSpritePtr             m_staticSprite; // The static sprite of the held item.
    }; // Endstruct.

    typedef HeldItem    DroppedItem;    // Dropped item.

    FolioStatus AddCollectedItem (const HeldItem    &heldItem,
                                  DroppedItem       &droppedItem);
    FolioStatus CycleCollectedItems (DroppedItem &droppedItem);
    bool    IsAnyCollectedItem () const;
    bool    IsRedKeyCollected () const;
    bool    IsGreenKeyCollected () const;
    bool    IsCyanKeyCollected () const;
    bool    IsYellowKeyCollected () const;
    bool    IsAcgKeyCollected () const;
    bool    IsCrucifixCollected () const;
    bool    IsSpannerCollected () const;

    FolioStatus IncrementScore (UInt32 scoreIncrement);

    void    IncrementNumRoomsVisited ();
    
    FolioStatus IncrementMainPlayerHealth (UInt32   healthIncrement,
                                           bool     playSound = true);
    FolioStatus DecrementMainPlayerHealth (UInt32   healthDecrement, 
                                           bool     &mainPlayerIsDead,
                                           bool     playSound = true);
    FolioStatus DecrementMainPlayerLife (bool &gameOver);

    UInt32          GetTimeInSeconds () const;
    UInt32          GetScore () const;
    UInt32          GetPercentageCompleted () const;
    Int32           GetCurrentHealth () const;

    static  FolioNarrowString   DescribeTime (UInt32 timeInSeconds);
    static  FolioNarrowString   DescribeScore (UInt32 score);
    static  FolioNarrowString   DescribePercentage (UInt32 percentage);

private:
    static  const   Int32   ORIGIN_X_LEFT = MAX_ROOM_WIDTH; // Origin X left of the information panel.
    static  const   Int32   ORIGIN_Y_TOP  = 0;              // Origin Y top of the information panel.

    static  const   Int32   HELD_ITEM_ORIGIN_X_LEFT     = 8 + ORIGIN_X_LEFT; 
    static  const   Int32   HELD_ITEM_ORIGIN_Y_TOP      = 25 + ORIGIN_Y_TOP;
    static  const   Int32   MAX_HELD_ITEM_WIDTH         = 16;
    static  const   Int32   MAX_HELD_ITEM_HEIGHT        = 20;
    static  const   Int32   HELD_ITEM_ORIGIN_Y_BOTTOM   = HELD_ITEM_ORIGIN_Y_TOP + MAX_HELD_ITEM_HEIGHT;

    static  const   UInt32  MAX_NUM_HELD_ITEMS  = 3;                // The maximum number of items that can be held by the main player.
    static  const   Int32   MIN_HEALTH          = 0;                // The maximum health the main player can have.
    static  const   Int32   MAX_HEALTH          = 90;               // The maximum health the main player can have.
    static  const   Int32   MAX_NUM_LIVES       = 4;                // The maximum number of lives the main player can have.
    static  const   Int32   MAX_TIME_IN_SECONDS = 999 * 60 + 59;    // The maximum time in seconds.
    static  const   Int32   MAX_SCORE           = 999999;           // The maximum health the main player can have.

    Folio::Core::Applet::Canvas*    m_canvas;   // The canvas.

    UInt32  m_startCount;                   // The start count.
    UInt32  m_previousTimeFrameTickCount;   // The previous time frame tick count.
    UInt32  m_previousScoreFrameTickCount;  // The previous score frame tick count.

    // Held items list.
    typedef std::list<HeldItem>   HeldItemsList;

    HeldItemsList   m_heldItemsList;        // The list of held items.

    UInt32  m_timeInSeconds;        // The current game's time (in seconds). 
    UInt32  m_score;                // The current game's score. 
    Int32   m_health;               // The main player's current health. 
    Int32   m_lives;                // The main player's current number of lives.

    UInt32  m_totalNumRooms;    // The total number of rooms. 
    UInt32  m_numRoomsVisited;  // The number of rooms visited.

    bool    m_invertScoreColours;   // Indicates if the score colours should be inverted. 
                             
    static  Folio::Core::Util::Sound::SoundSample   m_startingSoundSample;      // Starting sound sample.
    static  Folio::Core::Util::Sound::SoundSample   m_collectedItemSoundSample; // Collected item sound sample.
    static  Folio::Core::Util::Sound::SoundSample   m_droppedItemSoundSample;   // Dropped item sound sample.

    static  bool    m_playIncrementMainPlayerHealthSound;               // Indicates if the increment main player health sound should be played.
    static  UInt32  m_currentIncrementMainPlayerHealthSoundSampleIndex; // The current entered increment main player health sample index.
    static  Folio::Core::Util::Sound::SoundSamplesList  m_incrementMainPlayerHealthSoundSamplesList;    // The increment main player health sound samples.

    static  bool    m_playDecrementMainPlayerHealthSound;               // Indicates if the decrement main player health sound should be played.
    static  UInt32  m_currentDecrementMainPlayerHealthSoundSampleIndex; // The current entered decrement main player health sample index.
    static  Folio::Core::Util::Sound::SoundSamplesList  m_decrementMainPlayerHealthSoundSamplesList;    // The decrement main player health sound samples.

    // Information panel item.
    typedef std::shared_ptr<Folio::Core::Game::AItem>    Item;

    // Information panel items list.
    typedef std::vector<Item>   ItemsList;

    ItemsList   m_itemsList; // The information panel items.

    FolioStatus BuildItems (FolioHandle dcHandle, 
                            FolioHandle instanceHandle,
                            UInt16      mainPlayerBitmapResourceId);
    FolioStatus CheckTime (UInt32   currentTickCount,
                           bool     isStarting,
                           bool     &mainPlayerIsDead);
    FolioStatus CheckScore (UInt32  currentTickCount,
                           bool     &isStarting);
                                                        
    FolioStatus IncrementTimeInSeconds (UInt32  currentTickCount,
                                        bool    isStarting,
                                        bool    &mainPlayerIsDead);
    FolioStatus ResetMainPlayerHealth ();
    
    Int32   GetLossOfHealth () const;

    // The update enumeration.
    enum UPDATE
    {
        UPDATE_NONE = 0,
        UPDATE_HELD_ITEMS,
        UPDATE_TIME,
        UPDATE_SCORE,
        UPDATE_SCORE_COLOURS,
        UPDATE_HEALTH,
        UPDATE_LIFE_1,
        UPDATE_LIFE_2,
        UPDATE_LIFE_3,
    }; // Endenum.

    FolioStatus Update (UPDATE update);
    FolioStatus Reset ();

    INFORMATION_PANEL_ITEM_ID  GetNextHeldItemId () const;
    FolioStatus AddHeldItem (const HeldItem &heldItem,
                             DroppedItem    &droppedItem);
    FolioStatus CycleHeldItems (DroppedItem &droppedItem);
    FolioStatus RemoveLastHeldItem (DroppedItem &droppedItem);
    FolioStatus ClearHeldItemsRectangle ();
    FolioStatus UpdateHeldItem (Folio::Core::Game::GraphicItemPtr::element_type &item);
    bool    IsAnyHeldItem () const;

    HeldItemsList::iterator FindHeldItem (INFORMATION_PANEL_ITEM_ID itemId);
    HeldItemsList::const_iterator   FindHeldItem (STATIC_SPRITE_ID      staticSpriteId,
                                                  ZxSpectrum::COLOUR    colour) const;

    FolioStatus UpdateTextItem (Folio::Core::Game::TextItemPtr::element_type    &item,
                                bool                                            invertColours,
                                Gdiplus::Graphics                               &graphics, 
                                bool                                            &redrawCanvas);

    void    SetItemText (Folio::Core::Game::TextItemPtr::element_type &item);
    bool    SetGraphicItemHeight (Folio::Core::Game::GraphicItemPtr::element_type &item);
    
    ItemsList::iterator FindItem (INFORMATION_PANEL_ITEM_ID itemId);
    
    ZxSpectrum::COLOUR  GetScrollItemColour (INFORMATION_PANEL_ITEM_ID  itemId,
                                             ZxSpectrum::COLOUR         roomColour) const;

    static  void    CreateInformationPanelSoundSamples ();
    static  void    CreateIncrementMainPlayerHealthSoundSamples ();
    static  void    CreateDecrementMainPlayerHealthSoundSamples ();

    static  void    PlayInformationPanelSounds ();
    static  bool    PlayIncrementMainPlayerHealthSound ();
    static  bool    PlayDecrementMainPlayerHealthSound ();

    // Private copy constructor to prevent copying.
    InformationPanel (const InformationPanel& rhs);

    // Private assignment operator to prevent copying.
    InformationPanel& operator= (const InformationPanel& rhs);
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
