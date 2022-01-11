#pragma once

// "Home-made" includes.
#include    <Game.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace AticAtac
{

class CollisionGrid : public Folio::Core::Game::ACollisionGrid
{
public:
    CollisionGrid ();
    ~CollisionGrid ();

    // ACollisionGrid method(s).
    virtual bool    IsExitedScreen (DIRECTION       direction,
                                    bool            externalToFloorBound,
                                    Gdiplus::Rect&  spriteScreenRect,
                                    bool&           isAtLockedScreenExit,
                                    bool&           isInScreenExit,
                                    ScreenExit&     screenExit) const;
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
