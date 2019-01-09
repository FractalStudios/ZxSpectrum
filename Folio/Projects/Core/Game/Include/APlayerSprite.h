#pragma once

// STL includes.
#include    <memory>
#include    <vector>

// "Home-made" includes.
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

    FolioStatus SetBottomUpInitialisingMode (const ColourList& initialisingColourList);
    FolioStatus SetTopDownInitialisingMode (const ColourList& initialisingColourList);
    UInt32      GetInitialisingPauseTime () const;

    FolioStatus SetBottomUpTerminatingMode (const ColourList& terminatingColourList);
    FolioStatus SetTopDownTerminatingMode (const ColourList& terminatingColourList);
    UInt32      GetTerminatingPauseTime () const;

    Direction   UpdateDirection (Direction  direction, 
                                 bool       keyDown,
                                 bool       otherKeyDown = false);

    void    SetCanFireWeapon (bool canFireWeapon);
    bool    CanFireWeapon () const;

    void    SetCanCollectItems (bool canCollectItems);
    bool    CanCollectItems () const;

    void    SetCompletedGame ();
    bool    CompletedGame () const;

protected:
    bool    m_inAutoMoveMode;   // Indicates if the player sprite is in auto-move mode.
    bool    m_canFireWeapon;    // Indicates if the player sprite can fire a weapon.
    bool    m_canCollectItems;  // Indicates if the player sprite can collect an item.
    bool    m_completedGame;    // Indicates if the player sprite has completed the game.

    APlayerSprite ();

    FolioStatus Recreate (Int32     initialScreenXLeft,
                          Int32     initialScreenYTop,
                          Direction initialDirection = E,
                          UInt32    initialSpriteBitmapIndex = 0);

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
                                          const CollisionGrid&  collisionGrid);
    virtual FolioStatus HandleStaticSprite (Gdiplus::Graphics&      graphics,
                                            const CollisionGrid&    collisionGrid);

    FolioStatus PerformBottomUpOrTopDownInitialising (Gdiplus::Graphics&    graphics,
                                                      RectList*             rects);
    Gdiplus::ARGB   GetNewInitialisingColour (Gdiplus::ARGB& currentColour) const;

    FolioStatus PerformBottomUpOrTopDownTerminating (Gdiplus::Graphics& graphics,
                                                     RectList*          rects);
    Gdiplus::ARGB   GetNewTerminatingColour (Gdiplus::ARGB& currentColour) const;

    STATE    GetAutoMoveState (bool keyUp = true);

    bool    CalculateScreenRect (UInt32                 speed,
                                 const CollisionGrid&   collisionGrid);

    static  bool    MoveUp (UInt32                      speed,
                            const CollisionGrid&        collisionGrid,
                            Gdiplus::Rect&              spriteScreenRect,
                            bool&                       isEnteringScreen,
                            bool&                       isAtLockedScreenExit,
                            bool&                       IsInScreenExit,
                            CollisionGrid::ScreenExit&  screenExit);
    static  bool    MoveDown (UInt32                        speed,
                              const CollisionGrid&          collisionGrid,
                              Gdiplus::Rect&                spriteScreenRect,
                              bool&                         isEnteringScreen,
                              bool&                         isAtLockedScreenExit,
                              bool&                         IsInScreenExit,
                              CollisionGrid::ScreenExit&    screenExit);
    static  bool    MoveLeft (UInt32                        speed,
                              const CollisionGrid&          collisionGrid,
                              Gdiplus::Rect&                spriteScreenRect,
                              bool&                         isEnteringScreen,
                              bool&                         isAtLockedScreenExit,
                              bool&                         IsInScreenExit,
                              CollisionGrid::ScreenExit&    screenExit);
    static  bool    MoveRight (UInt32                       speed,
                               const CollisionGrid&         collisionGrid,
                               Gdiplus::Rect&               spriteScreenRect,
                               bool&                        isEnteringScreen,
                               bool&                        isAtLockedScreenExit,
                               bool&                        IsInScreenExit,
                               CollisionGrid::ScreenExit&   screenExit);
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
