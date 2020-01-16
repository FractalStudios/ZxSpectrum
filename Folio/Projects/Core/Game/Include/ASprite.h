#pragma once

// STL includes.
#include    <map>
#include    <memory>
#include    <vector>

// "Home-made" includes.
#include    <Graphic.h>
#include    <Util.h>
#include    "ACollisionGrid.h"
#include    "DrawingElement.h"
#include    "ResourceGraphic.h"
#include    "ResourceGraphicsCache.h"
#include    "SpriteGraphics.h"
#include    "SpriteSound.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Game
{

class ASprite : public Folio::Core::Graphic::AGdiGraphicElement
{
public:
    static  const   UInt32  STATIC_SPEED = 0;   // Speed when static.

    virtual ~ASprite ();

    FolioStatus GainResourceGraphics (Folio::Core::Game::ResourceGraphicsCache::OwnerId ownerId);
    FolioStatus ReleaseResourceGraphics ();

    FolioStatus ChangeSpriteInkColour (Gdiplus::ARGB    spriteInkColour, 
                                       bool             includeInitialisingGraphics = true,
                                       bool             includeTerminatingGraphics = true,
                                       bool             forceColourChange = false);

    FolioStatus StoreUnderlyingBackground (Gdiplus::Graphics&   graphics,
                                           Gdiplus::Rect*       rect = 0);
    FolioStatus RestoreUnderlyingBackground (Gdiplus::Graphics& graphics,
                                             RectList*          rects = 0);
    FolioStatus Move (Gdiplus::Graphics&    graphics,
                      UInt32                speed, 
                      const ACollisionGrid& collisionGrid);
    FolioStatus Static (Gdiplus::Graphics&      graphics,
                        const ACollisionGrid&   collisionGrid);
    FolioStatus Draw (Gdiplus::Graphics&    graphics,
                      RectList*             rects = 0);

    FolioStatus SetScreenTopLeft (Int32 screenXLeft,
                                  Int32 screenYTop);

    Gdiplus::Rect   GetScreenRect () const;
    Int32           GetScreenXLeft () const;
    Int32           GetScreenYTop () const;
    Int32           GetScreenXRight () const;
    Int32           GetScreenYBottom () const;
    Int32           GetScreenWidth () const;
    Int32           GetScreenHeight () const;

    Gdiplus::Rect   GetCollisionRect () const;
    Int32           GetCollisionXLeft () const;
    Int32           GetCollisionYTop () const;
    Int32           GetCollisionXRight () const;
    Int32           GetCollisionYBottom () const;
    Int32           GetCollisionWidth () const;
    Int32           GetCollisionHeight () const;

    ACollisionGrid::CellValue   GetCollisionGridCellValue () const;

    SpriteGraphic   GetCurrentSpriteGraphic () const;
    Int32   GetCurrentSpriteGraphicWidth () const;
    Int32   GetCurrentSpriteGraphicHeight () const;

    // Sprite state enumeration.
    enum STATE
    {
        STATE_UNKNOWN = 0,
        STATE_CREATED,
        STATE_INITIALISE_RQD,
        STATE_INITIALISING,
        STATE_INITIALISED,
        STATE_TERMINATE_RQD,
        STATE_TERMINATING,
        STATE_TERMINATED,
        STATE_STATIC,
        STATE_MOVING,
        STATE_FALLING,
    }; // Endenum.

    void    SetState (STATE state, 
                      bool  playSpriteStateSound = true);
    STATE   GetState () const;
    
    bool    IsInitialiseRqd () const;
    bool    IsInitialising () const;
    bool    IsInitialised () const;
    bool    IsTerminateRqd () const;
    bool    IsTerminating () const;
    bool    IsTerminated () const;
    bool    IsStatic () const;
    bool    IsMoving () const;
    bool    IsFalling () const;

    bool    IsReady () const;

    void    SetAlive (bool playSpriteInitialisingSound = true);
    bool    IsAlive () const;

    void    SetDead (bool playSpriteTerminatingSound = true);
    bool    IsDying () const;
    bool    IsDead () const;

    Direction   GetDirection () const;
    Action      GetAction () const;

    FolioStatus SetScreenEntranceTopLeft (const Gdiplus::Rect&  screenScreenRect,
                                          const ACollisionGrid& collisionGrid);

    FolioStatus SetScreenEntrance (ACollisionGrid::ScreenEntrance& screenEntrance);
    void    ResetScreenEntrance (); 

    bool    IsAtLockedScreenExit () const;
    bool    IsInScreenExit () const;
    bool    IsInScreenExit (const Gdiplus::Rect& screenRect) const;
    bool    IsExitedScreen () const;
    bool    IsEnteringScreen () const;

    ACollisionGrid::ScreenExit      GetScreenExit () const;
    ACollisionGrid::ScreenEntrance  GetScreenEntrance () const;

    // AGdiGraphicElement method(s).
    virtual FolioStatus Draw (Int32                 screenXLeft,
                              Int32                 screenYTop,
                              Gdiplus::Graphics&    graphics,
                              RectList*             rects = 0);

protected:
    STATE   m_state;    // The state of the sprite.

    Gdiplus::Rect   m_screenRect;       // The screen rect of the sprite.
    Gdiplus::Rect   m_collisionRect;    // The collision rect of the sprite.
    Gdiplus::ARGB   m_spriteInkColour;  // The ink colour of the sprite.
    Direction       m_direction;        // The direction of the sprite.
    Action          m_action;           // The current sprite action.
    UInt32          m_speed;            // The speed of the sprite.

    // Sprite drawing.
    struct SpriteDrawing
    {
        // Sprite bitmap.
        typedef Folio::Core::Graphic::GdiBitmapPtr  SpriteBitmap;

        SpriteDrawing (const SpriteGraphicAttributes& spriteGraphicAttributes)
        :   m_direction(spriteGraphicAttributes.m_direction),
            m_action(spriteGraphicAttributes.m_action),
            m_spriteGraphicsList(spriteGraphicAttributes.m_spriteGraphicsList),
            m_currentSpriteGraphicsListIndex(FOLIO_INVALID_INDEX)
        {} // Endproc.

        FolioStatus CreateSpriteBitmaps (FolioHandle    dcHandle,
                                         UInt32         screenScale)
        {
            FolioStatus status = ERR_SUCCESS;

            for (SpriteGraphicsList::iterator itr = m_spriteGraphicsList.begin ();
                 (status == ERR_SUCCESS) && (itr != m_spriteGraphicsList.end ());
                 ++itr)
            {
                // Create the sprite bitmap.

                status = (*itr)->CreateGdiBitmap (dcHandle, 
                                                  screenScale, 
                                                  ResourceGraphic::NO_DRAWING_FLAGS);

                if (status == ERR_SUCCESS)
                {
                    // Create the sprite masked bitmap.

                    status = (*itr)->CreateMaskedGdiBitmap (dcHandle);
                } // Endif.

            } // Endfor.
            
            return (status);
        } // Endproc.

        void    Reset ()
        {
            m_currentSpriteGraphicsListIndex = 0;
        } // Endproc.

        void    QueryCurrentSpriteBitmaps (STATE            state,
                                           SpriteBitmap&    spriteBitmap,           
                                           SpriteBitmap&    spriteMaskedBitmap,
                                           bool             incrementCurrentSpriteGraphicsListIndex = true)
        {
            // Initialised?

            if (m_currentSpriteGraphicsListIndex == FOLIO_INVALID_INDEX)
            {
                // No.

                m_currentSpriteGraphicsListIndex = 0;
            } // Endif.

            else
            {
                switch (state)
                {
                case STATE_STATIC:
                    break;

                default:
                    if (incrementCurrentSpriteGraphicsListIndex &&
                        (++m_currentSpriteGraphicsListIndex >= m_spriteGraphicsList.size ()))
                    {
                        m_currentSpriteGraphicsListIndex = 0;
                    } // Endif.
                    break;
                } // Endswitch.
                
            } // Endelse.

            spriteBitmap        = m_spriteGraphicsList [m_currentSpriteGraphicsListIndex]->GetGdiBitmap ();
            spriteMaskedBitmap  = m_spriteGraphicsList [m_currentSpriteGraphicsListIndex]->GetMaskedGdiBitmap ();
        } // Endproc.
        
        SpriteGraphic   GetCurrentSpriteGraphic () const
        {
            return ((m_currentSpriteGraphicsListIndex == FOLIO_INVALID_INDEX) ? m_spriteGraphicsList [0] : m_spriteGraphicsList [m_currentSpriteGraphicsListIndex]);
        } // Endproc.

        SpriteBitmap    GetCurrentSpriteBitmap () const
        {
            return ((m_currentSpriteGraphicsListIndex == FOLIO_INVALID_INDEX) ? m_spriteGraphicsList [0]->GetGdiBitmap () : m_spriteGraphicsList [m_currentSpriteGraphicsListIndex]->GetGdiBitmap ());
        } // Endproc.

        SpriteBitmap    GetCurrentSpriteMaskedBitmap () const
        {
            return ((m_currentSpriteGraphicsListIndex == FOLIO_INVALID_INDEX) ? m_spriteGraphicsList [0]->GetMaskedGdiBitmap () : m_spriteGraphicsList [m_currentSpriteGraphicsListIndex]->GetMaskedGdiBitmap ());
        } // Endproc.

        FolioStatus ChangeSpriteGraphicColour (Gdiplus::ARGB spriteInkColour)
        {
            FolioStatus status = ERR_SUCCESS;
    
            // Change the ink colour of the sprite's graphics.

            for (SpriteGraphicsList::iterator itr = m_spriteGraphicsList.begin ();
                (status == ERR_SUCCESS) && (itr != m_spriteGraphicsList.end ());
                ++itr)
            {
                status = (*itr)->ChangeColour (spriteInkColour);
            } // Endfor.

            return (status);
        } // Endproc.

        FolioStatus GainResourceGraphics (Folio::Core::Game::ResourceGraphicsCache::OwnerId ownerId,
                                          Folio::Core::Game::ResourceGraphicsCache&         resourceGraphicsCache) const
        {
            FolioStatus status = ERR_SUCCESS;

            for (SpriteGraphicsList::const_iterator itr = m_spriteGraphicsList.begin ();
                (status == ERR_SUCCESS) && (itr != m_spriteGraphicsList.end ());
                ++itr)
            {
                status = resourceGraphicsCache.GainResourceGraphic (ownerId, *itr);
            } // Endfor.

            return (status);
        } // Endproc.

        FolioStatus ReleaseResourceGraphics (Folio::Core::Game::ResourceGraphicsCache& resourceGraphicsCache) const
        {
            FolioStatus status = ERR_SUCCESS;

            for (SpriteGraphicsList::const_iterator itr = m_spriteGraphicsList.begin ();
                (status == ERR_SUCCESS) && (itr != m_spriteGraphicsList.end ());
                ++itr)
            {
                status = resourceGraphicsCache.ReleaseResourceGraphic (*itr);
            } // Endfor.

            return (status);
        } // Endproc.

        Direction           m_direction;                        // The direction(s) of the sprite.
        Action              m_action;                           // The action(s) of the sprite.
        SpriteGraphicsList  m_spriteGraphicsList;               // The sprite's graphics list representing the direction(s).
        UInt32              m_currentSpriteGraphicsListIndex;   // Index to the sprite's current graphic in the sprite's graphics list.
    }; // Endstruct.

    // The sprite drawing list.
    typedef std::vector<SpriteDrawing>  SpriteDrawingList;

    SpriteDrawingList   m_initialisingSpriteDrawingList;    // The sprite's initialising drawing list.
    SpriteDrawingList   m_terminatingSpriteDrawingList;     // The sprite's terminating drawing list.
    SpriteDrawingList   m_spriteDrawingList;                // The sprite's drawing list.
    SpriteDrawingList*  m_currentSpriteDrawingList;         // The sprite's current drawing list.
    UInt32              m_currentSpriteDrawingListIndex;    // Index to the current sprite's current drawing list.

    Direction   m_previousHorizontalDirection;  // The previous horizontal direction of the sprite.
    Direction   m_previousVerticalDirection;    // The previous vertical direction of the sprite.

    UInt32  m_maxNumAutoMoves;          // The maximum number of sprite auto-moves.
    UInt32  m_remainingNumAutoMoves;    // The remaining number of sprite auto-moves.

    Int32   m_initialisingDrawingMode;  // The initialising drawing mode of the player sprite.
    Int32   m_terminatingDrawingMode;   // The terminating drawing mode of the player sprite.
    
    ACollisionGrid::ScreenExit   m_screenExit;  // The screen exit of the sprite.
    bool    m_isAtLockedScreenExit; // Indicates if the sprite is at a locked screen exit.
    bool    m_isInScreenExit;       // Indicates if the sprite is in a screen exit.
    bool    m_isExitedScreen;       // Indicates if the sprite has exited the screen.
    bool    m_isEnteringScreen;     // Indicates if the sprite is entering the screen.

    UInt32  m_initialisingMaxSequenceCount;     // Initialising sprite maximum sequence count.
    UInt32  m_currentInitialisingSequenceCount; // The current initialising sprite sequence count.
    
    UInt32  m_terminatingMaxSequenceCount;      // Terminating sprite maximum sequence count.
    UInt32  m_currentTerminatingSequenceCount;  // The current terminating sprite sequence count.

    bool    m_playSpriteInitialisingSound;  // Indicates if the sprite's initialising sound should be played.
    SpriteStationarySoundSamplesList    m_initialisingSpriteSoundSamplesList;   // The sprite's initialising sound samples list.
    UInt32  m_currentInitialisingSpriteSoundSamplesListIndex;                   // Index to the sprite's current initialising sound sample in the sprite's initialising sound samples list.

    bool    m_playSpriteTerminatingSound;   // Indicates if the sprite's terminating sound should be played.
    SpriteStationarySoundSamplesList    m_terminatingSpriteSoundSamplesList;    // The sprite's terminating sound samples list.
    UInt32  m_currentTerminatingSpriteSoundSamplesListIndex;                    // Index to the sprite's current terminating sound sample in the sprite's terminating sound samples list.

    bool        m_isAtWall;     // Indicates if the sprite is at a wall.
    WallBound   m_wallBound;    // The sprite's wall bound (if it is at a wall).

    ASprite ();

    bool    IsCreated () const;

    FolioStatus Create (FolioHandle                                 dcHandle,
                        const SpriteGraphicAttributesList&          spriteGraphicAttributesList,
                        Int32                                       initialScreenXLeft,
                        Int32                                       initialScreenYTop,
                        UInt32                                      screenScale,
                        Gdiplus::ARGB                               spriteInkColour,
                        Direction                                   initialDirection,
                        Folio::Core::Game::ResourceGraphicsCache    *resourceGraphicsCache = 0,
                        UInt32                                      maxNumAutoMoves = 0);
    FolioStatus Recreate (Int32     screenXLeft,
                          Int32     screenYTop,
                          Direction direction);
    FolioStatus Destroy ();

    void    SetSpriteMovementSoundSamples (const SpriteMovementSoundSamplesList& spriteMovementSoundSampleList);
    void    SetSpriteInitialisedSoundSample (const SpriteSoundSample& spriteInitialisedSoundSample);
    void    SetSpriteTerminatedSoundSample (const SpriteSoundSample& spriteTerminatedSoundSample);
    void    SetSpriteReboundSoundSample (const SpriteSoundSample& spriteReboundSoundSample);

    FolioStatus SetGraphicInitialisingMode (FolioHandle                             dcHandle,
                                            const SpriteGraphicAttributesList&      initialisingSpriteGraphicAttributesList,
                                            UInt32                                  initialisingMaxSequenceCount,
                                            const SpriteStationarySoundSamplesList* initialisingSpriteSoundSamplesList = 0);
    FolioStatus SetGraphicTerminatingMode (FolioHandle                              dcHandle,
                                           const SpriteGraphicAttributesList&       terminatingSpriteGraphicAttributesList,
                                           UInt32                                   terminatingMaxSequenceCount,
                                           const SpriteStationarySoundSamplesList*  terminatingSpriteSoundSamplesList = 0);

    void    SetPlaySpriteInitialisingSound (bool playSpriteInitialisingSound);
    void    SetPlaySpriteTerminatingSound (bool playSpriteTerminatingSound);
    void    SetPlaySpriteInitialisedSound (bool playSpriteInitialisedSound);
    void    SetPlaySpriteTerminatedSound (bool playSpriteTerminatedSound);
    void    SetPlaySpriteReboundSound (bool playSpriteReboundSound);

    FolioStatus SetDirection (Direction direction);
    bool    IsDirection () const;

    FolioStatus SetAction (Action action);
    bool    IsAction () const;

    void        SetPreviousSpriteDirection (Direction direction);
    Direction   GetPreviousSpriteDirection () const;
    
    Direction   GetDirectionToScreenTopLeft (Int32                  initialScreenXLeft,
                                             Int32                  initialScreenYTop,
                                             const ACollisionGrid&  collisionGrid,
                                             bool                   toScreenTopLeft = true) const;
    bool    IsAtScreenTopLeft (Int32    initialScreenXLeft,
                               Int32    initialScreenYTop) const;

    Direction   GetDirectionToScreenRect (const Gdiplus::Rect&  screenRect,
                                          const ACollisionGrid& collisionGrid,
                                          bool                  toScreenRect = true) const;
    bool    IsAtScreenRect (const Gdiplus::Rect& screenRect) const;
    
    Direction   GetDirectionToNearestCorner (const ACollisionGrid &collisionGrid) const;

    FolioStatus SetCurrentSpriteBitmaps (Direction          direction,
                                         SpriteDrawingList& spriteDrawingList,
                                         bool               setSpriteScreenSize = false,
                                         bool               ignoreAction = false);
    FolioStatus QueryCurrentSpriteBitmaps (SpriteDrawing::SpriteBitmap& spriteBitmap,
                                           SpriteDrawing::SpriteBitmap& spriteMaskedBitmap,
                                           bool                         incrementCurrentSpriteGraphicsListIndex = true);

    void    PlaySpriteInitialisingSound (UInt32 initialisingSpriteSoundSamplesListIndex,
                                         bool   playAsynchronously = true) const;
    void    PlaySpriteTerminatingSound (UInt32  terminatingSpriteSoundSamplesListIndex,
                                        bool    playAsynchronously = true) const;
    void    PlaySpriteInitialisedSound (bool playAsynchronously = true) const;
    void    PlaySpriteTerminatedSound (bool playAsynchronously = true) const;
    void    PlaySpriteReboundSound (bool playAsynchronously = true) const;

    void    PlaySpriteMovementSound (bool playAsynchronously = true);

    virtual Int32   CalculateCollisionXLeft () const;
    virtual Int32   CalculateCollisionYTop () const;
    virtual Int32   CalculateScreenXLeft (ACollisionGrid::DIRECTION collisionGridDirection) const;
    virtual Int32   CalculateScreenYTop (ACollisionGrid::DIRECTION collisionGridDirection) const;
    virtual Int32   CalculateScreenXLeft (Int32 bitmapScreenWidth) const;
    virtual Int32   CalculateScreenYTop (Int32 bitmapScreenHeight) const;

    virtual FolioStatus HandleInitialiseSprite (Gdiplus::Graphics&  graphics,
                                                RectList*           rects);
    virtual FolioStatus HandleTerminateSprite (Gdiplus::Graphics&   graphics,
                                               RectList*            rects);

    virtual FolioStatus HandleMoveSprite (Gdiplus::Graphics&    graphics,
                                          UInt32                speed, 
                                          const ACollisionGrid& collisionGrid);
    virtual FolioStatus HandleStaticSprite (Gdiplus::Graphics&      graphics,
                                            const ACollisionGrid&   collisionGrid);

private:
    Folio::Core::Game::ResourceGraphicsCache    *m_resourceGraphicsCache;   //  The resource graphics cache.

    FolioHandle                 m_dcHandle;                 // Handle to the DC.
    DrawingElement::Id          m_drawingElementId;         // The drawing element identifier of the sprite.
    ACollisionGrid::CellValue   m_collisionGridCellValue;   // The collision grid cell value of the sprite.

    // Drawing mode enumeration.
    enum DRAWING_MODE
    {
        DM_NONE = 0,
        DM_GRAPHIC = 10,
    }; // Endenum.

    Folio::Core::Graphic::GdiBufferedBitmap   m_underlyingBackground;   // The underlying background of the sprite.

    UInt32  m_spriteMovementAudioCount; // The sprite's movement audio count;

    SpriteMovementSoundSamplesList  m_spriteMovementSoundSamplesList;           // The sprite's movement sound samples list.
    SpriteSoundSamplesList          m_currentSpriteMovementSoundSamplesList;    // The current sprite's movement sound samples list.
    UInt32                          m_currentMovementSoundSamplesListIndex;     // Index to the sprite's current movement sound sample in the current sprite's movement sound samples list.

    bool    m_playSpriteInitialisedSound;   // Indicates if the sprite's initialised sound should be played.
    SpriteSoundSample   m_spriteInitialisedSoundSample; // The sprite's initialised sound sample.

    bool    m_playSpriteTerminatedSound;    // Indicates if the sprite's terminated sound should be played.
    SpriteSoundSample   m_spriteTerminatedSoundSample;  // The sprite's terminated sound sample.

    bool    m_playSpriteReboundSound;   // Indicates if the sprite's rebound sound should be played.
    SpriteSoundSample   m_spriteReboundSoundSample;     // The sprite's rebound sound sample.

    FolioStatus CreateSpriteDrawingList (FolioHandle                        dcHandle,
                                         const SpriteGraphicAttributesList& spriteGraphicAttributesList,
                                         UInt32                             screenScale,
                                         SpriteDrawingList&                 spriteDrawingList);
    FolioStatus CreateSpriteDrawingList (FolioHandle                        dcHandle,
                                         const SpriteGraphicAttributesList& spriteGraphicAttributesList,
                                         UInt32                             screenScale,
                                         Direction                          direction,
                                         SpriteDrawingList&                 spriteDrawingList);

    FolioStatus InitialiseSprite (Gdiplus::Graphics&    graphics,
                                  RectList*             rects);
    FolioStatus TerminateSprite (Gdiplus::Graphics& graphics,
                                 RectList*          rects);
    FolioStatus DrawSprite (Gdiplus::Graphics&  graphics,
                            RectList*           rects);

    FolioStatus PerformGraphicInitialising (Gdiplus::Graphics&  graphics,
                                            RectList*           rects = 0);
    FolioStatus PerformGraphicTerminating (Gdiplus::Graphics&   graphics,
                                           RectList*            rects = 0);

    SpriteDrawing::SpriteBitmap ResetCurrentSpriteBitmap ();
    SpriteDrawing::SpriteBitmap GetCurrentSpriteBitmap () const;
    SpriteDrawing::SpriteBitmap GetCurrentSpriteMaskedBitmap () const;

    void    SetSpriteScreenSize (const SpriteDrawing::SpriteBitmap& spriteBitmap);
    void    CalculateScreenRect (UInt32                 speed,
                                 const ACollisionGrid&  collisionGrid);

    void    MoveUp (UInt32                  speed,
                    const ACollisionGrid&   collisionGrid);
    void    MoveDown (UInt32                speed,
                      const ACollisionGrid& collisionGrid);
    void    MoveLeft (UInt32                speed,
                      const ACollisionGrid& collisionGrid);
    void    MoveRight (UInt32                   speed,
                       const ACollisionGrid&    collisionGrid);
    FolioStatus CheckSpritePosition (const ACollisionGrid&      collisionGrid,
                                     ACollisionGrid::DIRECTION  collisionGridDirection);

    Direction   GetFloorBoundDirection (ACollisionGrid::DIRECTION collisionGridDirection) const;

    void    PlaySpriteSoundSample (const SpriteSoundSample& spriteSoundSample,
                                   bool                     playAsynchronously) const;
    void    PlaySpriteStationarySoundSamples (const SpriteStationarySoundSamplesList&   stationarySpriteSoundSamplesList,
                                              UInt32                                    stationarySpriteSoundSamplesListIndex,
                                              bool                                      playAsynchronously) const;

    FolioStatus SetCurrentSpriteMovementSoundSample (Direction direction);
}; // Endclass.

// Sprite pointer.
typedef std::shared_ptr<ASprite>    ASpritePtr;

// Sprites list.
typedef std::vector<ASpritePtr>     ASpritesList;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
