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

    // Direction.
    typedef UInt32  Direction;

    // Sprite directions.
    static  const   Direction   NO_DIRECTION        = 0x00000000;
    static  const   Direction   N                   = 0x00000001;   // North.
    static  const   Direction   S                   = 0x00000002;   // South.
    static  const   Direction   E                   = 0x00000004;   // East.
    static  const   Direction   W                   = 0x00000008;   // West.
    static  const   Direction   NE                  = N | E;        // North-East.
    static  const   Direction   NW                  = N | W;        // North-West.
    static  const   Direction   SE                  = S | E;        // South-East.
    static  const   Direction   SW                  = S | W;        // South-West.
    static  const   Direction   ALL_DIRECTIONS      = N | S | E | W;
    static  const   Direction   DEFAULT_DIRECTION   = E;

    // Action.
    typedef UInt32  Action;

    // Sprite Actions.
    static  const   Action  DEFAULT_ACTION = 0;

    // Sprite graphic.
    typedef ResourceGraphicPtr  SpriteGraphic;

    // Sprite bitmaps list.
    typedef std::vector<SpriteGraphic>  SpriteGraphicsList;

    // Sprite graphic attributes.
    struct SpriteGraphicAttributes
    {
        SpriteGraphicAttributes ()
        :   m_direction(NO_DIRECTION),
            m_action(DEFAULT_ACTION)
        {} // Endproc.

        SpriteGraphicAttributes (Direction                 direction,
                                 Action                    action,
                                 const SpriteGraphicsList  &spriteGraphics)
        :   m_direction(direction),
            m_action(action),
            m_spriteGraphics(spriteGraphics)
        {} // Endproc.

        Direction           m_direction;        // The direction(s) of the sprite.
        Action              m_action;           // The action(s) of the sprite.
        SpriteGraphicsList  m_spriteGraphics;   // The sprite graphics representing the direction(s).
    }; // Endstruct.

    // Sprite attributes list.
    typedef std::vector<SpriteGraphicAttributes>    SpriteGraphicAttributesList;

    virtual ~ASprite ();

    FolioStatus Create (FolioHandle                         dcHandle,
                        const SpriteGraphicAttributesList&  spriteGraphicAttributesList,
                        Int32                               initialScreenXLeft,
                        Int32                               initialScreenYTop,
                        UInt32                              screenScale,
                        Gdiplus::ARGB                       spriteInkColour,
                        Direction                           initialDirection = DEFAULT_DIRECTION,
                        UInt32                              maxNumAutoMoves = 0);

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

    // Sprite initialising sound sample.
    struct SpriteInitialisingSoundSample
    {
        SpriteInitialisingSoundSample ()
        :   m_numSoundSamplesPerFrame(0)
        {} // Endproc.

        SpriteInitialisingSoundSample (const Folio::Core::Util::Sound::SoundSample  &soundSample,
                                       UInt32                                       numSoundSamplesPerFrame = 1)
        :   m_soundSample(soundSample),
            m_numSoundSamplesPerFrame(numSoundSamplesPerFrame)
        {} // Endproc.

        ~SpriteInitialisingSoundSample ()
        {} // Endproc.

        Folio::Core::Util::Sound::SoundSample   m_soundSample;              // The sound sample.
        UInt32                                  m_numSoundSamplesPerFrame;  // The number of sound samples per frane.
    }; // Endstruct.

    // Sprite initialising sound samples list.
    typedef std::vector<SpriteInitialisingSoundSample>  SpriteInitialisingSoundSamplesList;

    // Sprite terminating sound sample.
    typedef SpriteInitialisingSoundSample   SpriteTerminatingSoundSample;

    // Sprite terminating sound samples list.
    typedef SpriteInitialisingSoundSamplesList  SpriteTerminatingSoundSamplesList;

    // Sprite movement sound sample.
    typedef std::shared_ptr<Folio::Core::Util::Sound::SoundSample>  SpriteMovementSoundSample;

    // Sprite movement sound samples list.
    typedef std::vector<SpriteMovementSoundSample>  SpriteMovementSoundSamplesList;

    // Sprite movement sound attributes.
    struct SpriteMovementSoundAttributes
    {
        SpriteMovementSoundAttributes ()
        :   m_direction(NO_DIRECTION)
        {} // Endproc.

        SpriteMovementSoundAttributes (Direction                            direction,
                                       const SpriteMovementSoundSamplesList &spriteMovementSoundSamples)
        :   m_direction(direction),
            m_spriteMovementSoundSamples(spriteMovementSoundSamples)
        {} // Endproc.

        Direction                       m_direction;                    // The direction(s) of the sprite.
        SpriteMovementSoundSamplesList  m_spriteMovementSoundSamples;   // The sprite movement sound samples representing the direction(s).
    }; // Endstruct.

    // Sprite movement sound attributes list.
    typedef std::vector<SpriteMovementSoundAttributes>  SpriteMovementSoundAttributesList;

    FolioStatus SetSpriteMovementSoundSamples (const SpriteMovementSoundAttributesList& spriteMovementSoundSamplesAttributesList);

    // Sprite rebound sound sample.
    typedef std::shared_ptr<Folio::Core::Util::Sound::SoundSample>  SpriteReboundSoundSample;

    // Sprite rebound sound attributes.
    struct SpriteReboundSoundAttributes
    {
        SpriteReboundSoundAttributes ()
        :   m_direction(NO_DIRECTION)
        {} // Endproc.

        SpriteReboundSoundAttributes (Direction                         direction,
                                      const SpriteReboundSoundSample&   spriteReboundSoundSample)
        :   m_direction(direction),
            m_spriteReboundSoundSample(spriteReboundSoundSample)
        {} // Endproc.

        Direction                   m_direction;                // The direction(s) of the sprite.
        SpriteReboundSoundSample    m_spriteReboundSoundSample; // The sprite rebound sound sample representing the direction(s).
    }; // Endstruct.

    // Sprite rebound sound attributes list.
    typedef std::vector<SpriteReboundSoundAttributes>   SpriteReboundSoundAttributesList;

    FolioStatus SetSpriteReboundSoundSamples (const SpriteReboundSoundAttributesList& spriteReboundSoundSamplesAttributesList);

    FolioStatus ChangeSpriteInkColour (Gdiplus::ARGB    spriteInkColour, 
                                       bool             includeInitialisingGraphics = true,
                                       bool             includeTerminatingGraphics = true);

    ACollisionGrid::CellValue   GetCollisionGridCellValue () const;

    UInt32  GetMaxNumAutoMoves () const;
    UInt32  GetRemainingNumAutoMoves () const;

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

    void    SetState (STATE state);
    STATE   GetState () const;
    
    void    SetAlive (bool playSpriteInitialisingSound = true);
    bool    IsAlive () const;

    void    SetDead (bool playSpriteTerminatingSound = true);
    bool    IsDying () const;
    bool    IsDead () const;

    bool    IsReady () const;

    bool    IsInitialiseRqd () const;
    bool    IsInitialising () const;
    bool    IsInitialised () const;
    bool    IsTerminateRqd () const;
    bool    IsTerminating () const;
    bool    IsTerminated () const;
    bool    IsStatic () const;
    bool    IsMoving () const;
    bool    IsFalling () const;

    FolioStatus SetGraphicInitialisingMode (FolioHandle                                 dcHandle,
                                            const SpriteGraphicAttributesList&          initialisingSpriteGraphicAttributesList,
                                            UInt32                                      initialisingMaxSequenceCount,
                                            const SpriteInitialisingSoundSamplesList&   initialisingSoundSamplesList = SpriteInitialisingSoundSamplesList());
    FolioStatus SetGraphicTerminatingMode (FolioHandle                              dcHandle,
                                           const SpriteGraphicAttributesList&       terminatingSpriteGraphicAttributesList,
                                           UInt32                                   terminatingMaxSequenceCount,
                                           const SpriteTerminatingSoundSamplesList& terminatingSoundSamplesList = SpriteTerminatingSoundSamplesList());

    void    SetPlaySpriteInitialisingSound (bool playSpriteInitialisingSound);
    void    SetPlaySpriteTerminatingSound (bool playSpriteTerminatingSound);

    Direction   UpdateDirection (Direction direction);
    void        SetDirection (Direction direction);
    Direction   GetDirection () const;
    bool    IsDirection () const;

    void    SetAction (Action action);
    Action  GetAction () const;
    bool    IsAction () const;

    bool    IsAtLockedScreenExit () const;

    bool    IsInScreenExit () const;
    bool    IsInScreenExit (const Gdiplus::Rect& screenRect) const;
    bool    IsExitedScreen () const;

    void    SetScreenEntrance (ACollisionGrid::ScreenEntrance& screenEntrance);
    void    ResetScreenEntrance (); 
    bool    IsEnteringScreen () const;

    ACollisionGrid::ScreenExit      GetScreenExit () const;
    ACollisionGrid::ScreenEntrance  GetScreenEntrance () const;

    FolioStatus SetScreenEntranceTopLeft (const Gdiplus::Rect&  screenScreenRect,
                                          const ACollisionGrid& collisionGrid);

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

    Direction   GetFloorBoundDirection (ACollisionGrid::DIRECTION collisionGridDirection) const;

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
    UInt32          m_speed;            // The speed of the sprite.
    Action          m_action;           // The current sprite action.

    Direction   m_previousHorizontalDirection;  // The previous horizontal direction of the sprite.
    Direction   m_previousVerticalDirection;    // The previous vertical direction of the sprite.

    UInt32  m_maxNumAutoMoves;          // The maximum number of sprite auto-moves.
    UInt32  m_remainingNumAutoMoves;    // The remaining number of sprite auto-moves.

    Folio::Core::Graphic::GdiBufferedBitmap   m_underlyingBackground;   // The underlying background of the sprite.

    // Sprite drawing bitmap.
    typedef std::shared_ptr<Folio::Core::Graphic::GdiBitmap>    SpriteDrawingBitmap;

    // Sprite drawing bitmaps list.
    typedef std::vector<SpriteDrawingBitmap>    SpriteDrawingBitmapsList;

    // Sprite drawing attributes.
    struct SpriteDrawingAttributes
    {
        SpriteDrawingAttributes ()
        :   m_direction(NO_DIRECTION),
            m_action(DEFAULT_ACTION),
            m_maxNumSpriteBitmaps(0),
            m_currentSpriteBitmapIndex(0)
        {} // Endproc.

        SpriteDrawingAttributes (Direction                  direction,
                                 Action                     action,
                                 const SpriteDrawingBitmap& spriteDrawingBitmap,           
                                 const SpriteDrawingBitmap& spriteMaskedDrawingBitmap)
        :   m_direction(direction),
            m_action(action),
            m_maxNumSpriteBitmaps(1),
            m_currentSpriteBitmapIndex(0),
            m_spriteDrawingBitmaps{spriteDrawingBitmap},
            m_spriteMaskedDrawingBitmaps{spriteMaskedDrawingBitmap}
        {} // Endproc.

        void    AddSpriteDrawingBitmaps (const SpriteDrawingBitmap&  spriteDrawingBitmap,           
                                         const SpriteDrawingBitmap&  spriteMaskedDrawingBitmap)
        {
            m_spriteDrawingBitmaps.push_back (spriteDrawingBitmap);
            m_spriteMaskedDrawingBitmaps.push_back (spriteMaskedDrawingBitmap);
            
            m_maxNumSpriteBitmaps++;
        } // Endproc.

        void    QueryCurrentSpriteDrawingBitmaps (STATE                 state,
                                                  SpriteDrawingBitmap&  spriteDrawingBitmap,           
                                                  SpriteDrawingBitmap&  spriteMaskedDrawingBitmap,
                                                  bool                  incrementSpriteBitmapIndex = true)
        {
            spriteDrawingBitmap         = m_spriteDrawingBitmaps [m_currentSpriteBitmapIndex];
            spriteMaskedDrawingBitmap   = m_spriteMaskedDrawingBitmaps [m_currentSpriteBitmapIndex];

            switch (state)
            {
            case STATE_STATIC:
                break;

            default:
                if (incrementSpriteBitmapIndex && 
                    (++m_currentSpriteBitmapIndex >= m_maxNumSpriteBitmaps))
                {
                    m_currentSpriteBitmapIndex = 0;
                } // Endif.
                break;
            } // Endswitch

        } // Endproc.
        
        SpriteDrawingBitmap GetCurrentSpriteDrawingBitmap () const
        {
            return (m_spriteDrawingBitmaps [m_currentSpriteBitmapIndex]);
        } // Endproc.

        SpriteDrawingBitmap GetCurrentSpriteMaskedDrawingBitmap () const
        {
            return (m_spriteMaskedDrawingBitmaps [m_currentSpriteBitmapIndex]);
        } // Endproc.

        Direction                   m_direction;                    // The direction(s) of the sprite.
        Action                      m_action;                       // The action(s) of the sprite.
        UInt32                      m_maxNumSpriteBitmaps;          // The sprite's maximum number of bitmaps (in this direction).
        UInt32                      m_currentSpriteBitmapIndex;     // The sprite's current bitmap index (in this direction).
        SpriteDrawingBitmapsList    m_spriteDrawingBitmaps;         // The sprite's drawing bitmaps representing the direction(s).
        SpriteDrawingBitmapsList    m_spriteMaskedDrawingBitmaps;   // The sprite's masked drawing bitmaps representing the direction(s).
    }; // Endstruct.

    // Sprite drawing attributes list.
    typedef std::vector<SpriteDrawingAttributes>    SpriteDrawingAttributesList;

    SpriteDrawingAttributesList m_spriteDrawingAttributesList;              // The sprite's drawing attributes list.
    SpriteDrawingAttributesList m_initialisingSpriteDrawingAttributesList;  // The initialising sprite's drawing attributes list.
    SpriteDrawingAttributesList m_terminatingSpriteDrawingAttributesList;   // The terminating sprite's drawing attributes list.
    SpriteDrawingAttributes*    m_currentSpriteDrawingAttributes;           // The current sprite's drawing attributes.

    Int32   m_initialisingDrawingMode;  // The initialising drawing mode of the player sprite.
    Int32   m_terminatingDrawingMode;   // The terminating drawing mode of the player sprite.
    
    bool    m_playSpriteInitialisingSound;  // Indicates if the sprite's initialising sound should be played.
    UInt32  m_initialisingCurrentSoundSamplesListIndex; // The current initialising sound samples list index.   
    SpriteInitialisingSoundSamplesList  m_initialisingSoundSamplesList; // The initialising sound samples list.

    bool    m_playSpriteTerminatingSound;   // Indicates if the sprite's terminating sound should be played.
    UInt32  m_terminatingCurrentSoundSamplesListIndex;  // The current terminating sound samples list index.   
    SpriteTerminatingSoundSamplesList   m_terminatingSoundSamplesList;  // The terminating sound samples list.

    ACollisionGrid::ScreenExit   m_screenExit;  // The screen exit of the sprite.
    bool    m_isAtLockedScreenExit; // Indicates if the sprite is at a locked screen exit.
    bool    m_isInScreenExit;       // Indicates if the sprite is in a screen exit.
    bool    m_isExitedScreen;       // Indicates if the sprite has exited the screen.
    bool    m_isEnteringScreen;     // Indicates if the sprite is entering the screen.

    // Wall bound.
    struct WallBound
    {
        WallBound ()
        :   m_direction(NO_DIRECTION)
        {} // Endproc.

        WallBound (Direction            direction,
                   const Gdiplus::Rect& screenRect)
        :   m_direction(direction),
            m_screenRect(screenRect)
        {} // Endproc.

        Direction       m_direction;    // The direction of the sprite at the wall bound
        Gdiplus::Rect   m_screenRect;   // The screen rect of the sprite at the wall bound.
    }; // Endstruct.

    bool        m_isAtWall;     // Indicates if the sprite is at a wall.
    WallBound   m_wallBound;    // The sprite's wall bound (if it is at a wall).

    ASprite ();

    FolioStatus CreateSpriteDrawingAttributes (FolioHandle                  dcHandle,
                                               const SpriteGraphicsList&    spriteGraphics,
                                               UInt32                       screenScale,
                                               SpriteDrawingAttributes&     spriteDrawingAttributes);
    FolioStatus CreateSpriteDrawingAttributesList (FolioHandle                          dcHandle,
                                                   const SpriteGraphicAttributesList&   spriteGraphicAttributesList,
                                                   UInt32                               screenScale,
                                                   SpriteDrawingAttributesList&         spriteDrawingAttributesList);
    FolioStatus CreateSpriteDrawingAttributesList (FolioHandle                          dcHandle,
                                                   const SpriteGraphicAttributesList&   spriteGraphicAttributesList,
                                                   UInt32                               screenScale,
                                                   Direction                            direction,
                                                   SpriteDrawingAttributesList&         spriteDrawingAttributesList);

    FolioStatus SetCurrentSpriteBitmaps (Direction                      direction,
                                         SpriteDrawingAttributesList&   spriteDrawingAttributesList,
                                         bool                           isSetSpriteScreenAttributes = false,
                                         bool                           ignoreAction = false);
    FolioStatus QueryCurrentSpriteBitmaps (SpriteDrawingBitmap& spriteDrawingBitmap,
                                           SpriteDrawingBitmap& spriteMaskedDrawingBitmap,
                                           bool                 incrementSpriteBitmapIndex = true);
    
    void    SetSpriteScreenAttributes (const SpriteDrawingBitmap& spriteDrawingBitmap1);

    void    PlaySpriteInitialisingSound (UInt32 initialisingSoundSamplesListIndex) const;
    void    PlaySpriteTerminatingSound (UInt32 terminatingSoundSamplesListIndex) const;

    FolioStatus PlaySpriteMovementSound ();
    bool    IsSpriteMovementSoundSupported ();

    FolioStatus SetCurrentSpriteMovementSoundSample (Direction direction);
    FolioStatus QueryCurrentSpriteMovementSoundSample (SpriteMovementSoundSample& spriteMovementSoundSamplesSample);

    FolioStatus UpdateSpriteMovementAudioAttributes (Direction direction);

    virtual Int32   CalculateCollisionXLeft () const;
    virtual Int32   CalculateCollisionYTop () const;
    virtual Int32   CalculateScreenXLeft (ACollisionGrid::DIRECTION collisionGridDirection) const;
    virtual Int32   CalculateScreenYTop (ACollisionGrid::DIRECTION collisionGridDirection) const;
    virtual Int32   CalculateScreenXLeft (Int32 bitmapScreenWidth) const;
    virtual Int32   CalculateScreenYTop (Int32 bitmapScreenHeight) const;

    virtual FolioStatus HandleInitialiseSprite (Gdiplus::Graphics&  graphics,
                                                RectList*           rects = 0);
    virtual FolioStatus HandleTerminateSprite (Gdiplus::Graphics&   graphics,
                                               RectList*            rects = 0);

    virtual FolioStatus HandleMoveSprite (Gdiplus::Graphics&    graphics,
                                          UInt32                speed, 
                                          const ACollisionGrid& collisionGrid);
    virtual FolioStatus HandleStaticSprite (Gdiplus::Graphics&      graphics,
                                            const ACollisionGrid&   collisionGrid);

private:
    DrawingElement::Id          m_drawingElementId;         // The drawing element identifier of the sprite.
    ACollisionGrid::CellValue   m_collisionGridCellValue;   // The collision grid cell value of the sprite.

    // Drawing mode enumeration.
    enum DRAWING_MODE
    {
        DM_NONE = 0,
        DM_GRAPHIC = 10,
    }; // Endenum.

    UInt32  m_initialisingMaxSequenceCount;     // Initialising sprite maximum sequence count.
    UInt32  m_initialisingCurrentSequenceCount; // Initialising sprite current sequence count.
    
    UInt32  m_terminatingMaxSequenceCount;      // Terminating sprite maximum sequence count.
    UInt32  m_terminatingCurrentSequenceCount;  // Terminating sprite current sequence count.
    
    // Sprite movement audio attributes.
    struct SpriteMovementAudioAttributes
    {
        SpriteMovementAudioAttributes ()
        :   m_direction(NO_DIRECTION),
            m_maxNumSpriteSoundSamples(0),
            m_currentSpriteSoundSampleIndex(0)
        {} // Endproc.

        SpriteMovementAudioAttributes (Direction                        direction,               
                                       const SpriteMovementSoundSample& spriteMovementSoundSample)           
        :   m_direction(direction),
            m_maxNumSpriteSoundSamples(1),
            m_currentSpriteSoundSampleIndex(0),
            m_spriteMovementSoundSamples{spriteMovementSoundSample}
        {} // Endproc.

        Direction                       m_direction;                        // The direction(s) of the sprite.
        UInt32                          m_maxNumSpriteSoundSamples;         // The sprite's maximum number of sound samples (in this direction).
        UInt32                          m_currentSpriteSoundSampleIndex;    // The sprite's current sound sample index (in this direction).
        SpriteMovementSoundSamplesList  m_spriteMovementSoundSamples;       // The sprite's movement sound samples representing the direction(s).
    }; // Endstruct.

    // Sprite movement audio attributes list.
    typedef std::vector<SpriteMovementAudioAttributes>  SpriteMovementAudioAttributesList;

    UInt32  m_spriteMovementAudioCount;
    SpriteMovementAudioAttributesList   m_spriteMovementAudioAttributesList;        // The sprite's movement audio attributes.
    SpriteMovementAudioAttributes*      m_currentSpriteMovementAudioAttributes;     // The current sprite's movement audio attributes.

    // Sprite rebound audio attributes.
    typedef SpriteReboundSoundAttributes    SpriteReboundAudioAttributes;

        // Sprite rebound audio attributes list.
    typedef std::vector<SpriteReboundAudioAttributes>   SpriteReboundAudioAttributesList;

    SpriteReboundAudioAttributesList    m_spriteReboundAudioAttributesList;     // The sprite's rebound audio attributes.

    FolioStatus InitialiseSprite (Gdiplus::Graphics&    graphics,
                                  RectList*             rects);
    FolioStatus TerminateSprite (Gdiplus::Graphics& graphics,
                                 RectList*          rects);
    FolioStatus DrawSprite (Gdiplus::Graphics&  graphics,
                            RectList*           rects);

    void    AddSpriteDrawingAttributes (Direction                       direction,
                                        Action                          action,
                                        const SpriteDrawingBitmap&      spriteDrawingBitmap,
                                        const SpriteDrawingBitmap&      spriteMaskedDrawingBitmap,
                                        SpriteDrawingAttributesList&    spriteDrawingAttributesList);

    FolioStatus ChangeSpriteDrawingBitmapsColour (Gdiplus::ARGB             spriteInkColour,
                                                  SpriteDrawingBitmapsList& spriteDrawingBitmaps);

    FolioStatus CreateSpriteMovementAudioAttributes (const SpriteMovementSoundSamplesList&  spriteMovementSoundSamples,
                                                     SpriteMovementAudioAttributes&         spriteMovementAudioAttributes);
    FolioStatus CreateSpriteMovementAudioAttributes (const SpriteMovementSoundAttributesList&   spriteMovementSoundSamplesAttributesList,
                                                     Direction                                  direction);

    void    AddSpriteMovementAudioAttributes (Direction                         direction,
                                              const SpriteMovementSoundSample&  spriteMovementSoundSample);

    FolioStatus PerformGraphicInitialising (Gdiplus::Graphics&  graphics,
                                            RectList*           rects = 0);
    FolioStatus PerformGraphicTerminating (Gdiplus::Graphics&   graphics,
                                           RectList*            rects = 0);

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
    void    CheckSpritePosition (const ACollisionGrid&      collisionGrid,
                                 ACollisionGrid::DIRECTION  collisionGridDirection);

    void    PlayReboundSound (Direction& direction) const;

    bool    IsCreated () const;
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
