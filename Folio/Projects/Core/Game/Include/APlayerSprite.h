#pragma once

// STL includes.
#include    <memory>
#include    <vector>

// "Home-made" includes.
#include    <Util.h>
#include    "ASprite.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Game
{

class APlayerSprite : public ASprite
{
public:
    virtual ~APlayerSprite ();

    // Colour list.
    typedef std::vector<Gdiplus::ARGB>  ColourList;

    FolioStatus SetBottomUpInitialisingMode (const ColourList&                          initialisingColourList, 
                                             const SpriteInitialisingSoundSamplesList&  initialisingSoundSamplesList);
    FolioStatus SetTopDownInitialisingMode (const ColourList&                           initialisingColourList,
                                            const SpriteInitialisingSoundSamplesList&   initialisingSoundSamplesList);
    UInt32      GetInitialisingPauseTime () const;

    FolioStatus SetBottomUpTerminatingMode (const ColourList&                           terminatingColourList,
                                            const SpriteTerminatingSoundSamplesList&    terminatingSoundSamplesList);
    FolioStatus SetTopDownTerminatingMode (const ColourList&                            terminatingColourList,
                                           const SpriteTerminatingSoundSamplesList&     terminatingSoundSamplesList);
    UInt32      GetTerminatingPauseTime () const;

    virtual Direction   UpdateDirection (Direction  direction, 
                                         bool       keyDown);

    void    SetGameOver ();
    bool    IsGameOver () const;

    void    SetGameCompleted ();
    bool    IsGameCompleted () const;

protected:
    bool    m_inAutoMoveMode;   // Indicates if the player sprite is in auto-move mode.
    bool    m_isGameOver;       // Indicates if the player sprite's game is over.
    bool    m_isGameCompleted;  // Indicates if the player sprite has completed the game.

    APlayerSprite ();

    FolioStatus Recreate (Int32     screenXLeft,
                          Int32     screenYTop,
                          Direction direction = E);

    STATE    GetAutoMoveState (bool keyUp = true);

private:
    static  const   UInt32  DEFAULT_INITIALISING_PAUSE_TIME = 50;   // The default initialising pause time.
    static  const   UInt32  DEFAULT_TERMINATING_PAUSE_TIME  = 10;   // The default terminating pause time.

    // Drawing mode enumeration.
    enum DRAWING_MODE
    {
        DM_BOTTOM_UP = -1,
        DM_TOP_DOWN = 1,
    }; // Endenum.
    
    ColourList  m_initialisingColourList;   // The initialising colour list (used in DM_BOTTOM_UP and DM_TOP_DOWN). 
    ColourList  m_terminatingColourList;    // The terminating colour list (used in DM_BOTTOM_UP and DM_TOP_DOWN). 
    
    virtual FolioStatus HandleInitialiseSprite (Gdiplus::Graphics&  graphics,
                                                RectList*           rects = 0);
    virtual FolioStatus HandleTerminateSprite (Gdiplus::Graphics&   graphics,
                                               RectList*            rects = 0);

    virtual FolioStatus HandleMoveSprite (Gdiplus::Graphics&    graphics,
                                          UInt32                speed, 
                                          const ACollisionGrid& collisionGrid);
    virtual FolioStatus HandleStaticSprite (Gdiplus::Graphics&      graphics,
                                            const ACollisionGrid&   collisionGrid);

    FolioStatus PerformBottomUpOrTopDownInitialising (Gdiplus::Graphics&    graphics,
                                                      RectList*             rects);
    Gdiplus::ARGB   GetNewInitialisingColour (Gdiplus::ARGB& currentColour) const;

    FolioStatus PerformBottomUpOrTopDownTerminating (Gdiplus::Graphics& graphics,
                                                     RectList*          rects);
    Gdiplus::ARGB   GetNewTerminatingColour (Gdiplus::ARGB& currentColour) const;

    bool    CalculateScreenRect (UInt32                 speed,
                                 const ACollisionGrid&  collisionGrid);

    bool    MoveUp (UInt32                  speed,
                    const ACollisionGrid&   collisionGrid);
    bool    MoveDown (UInt32                speed,
                      const ACollisionGrid& collisionGrid);
    bool    MoveLeft (UInt32                speed,
                      const ACollisionGrid& collisionGrid);
    bool    MoveRight (UInt32               speed,
                      const ACollisionGrid& collisionGrid);
}; // Endclass.

// Player sprite pointer.
typedef std::shared_ptr<APlayerSprite>  APlayerSpritePtr;

// Player sprites list.
typedef std::vector<APlayerSpritePtr>   APlayerSpritesList;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
