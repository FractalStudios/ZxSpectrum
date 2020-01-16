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

    virtual FolioStatus UpdateDirection (Direction  direction, 
                                         bool       keyDown);

    void    SetGameOver ();
    bool    IsGameOver () const;

    void    SetGameCompleted ();
    bool    IsGameCompleted () const;

protected:
    APlayerSprite ();

    FolioStatus Restart (Int32      screenXLeft,
                         Int32      screenYTop,
                         Direction  direction);

    STATE   GetAutoMoveState (bool keyUp = true);
    bool    IsInAutoMoveMode () const;

    // Colour list.
    typedef std::vector<Gdiplus::ARGB>  ColourList;

    FolioStatus SetBottomUpInitialisingMode (const ColourList&                          initialisingColourList, 
                                             const SpriteStationarySoundSamplesList&    initialisingSpriteSoundSamplesList);
    FolioStatus SetTopDownInitialisingMode (const ColourList&                       initialisingColourList,
                                            const SpriteStationarySoundSamplesList& initialisingSpriteSoundSamplesList);

    FolioStatus SetBottomUpTerminatingMode (const ColourList&                       terminatingColourList,
                                            const SpriteStationarySoundSamplesList& terminatingSpriteSoundSamplesList);
    FolioStatus SetTopDownTerminatingMode (const ColourList&                        terminatingColourList,
                                           const SpriteStationarySoundSamplesList&  terminatingSpriteSoundSamplesList);

private:
    bool    m_inAutoMoveMode;   // Indicates if the player sprite is in auto-move mode.
    bool    m_isGameOver;       // Indicates if the player sprite's game is over.
    bool    m_isGameCompleted;  // Indicates if the player sprite has completed the game.

    ColourList  m_initialisingColourList;   // The initialising colour list (used in DM_BOTTOM_UP and DM_TOP_DOWN). 
    ColourList  m_terminatingColourList;    // The terminating colour list (used in DM_BOTTOM_UP and DM_TOP_DOWN). 
    
    // Drawing mode enumeration.
    enum DRAWING_MODE
    {
        DM_BOTTOM_UP = -1,
        DM_TOP_DOWN = 1,
    }; // Endenum.
    
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
