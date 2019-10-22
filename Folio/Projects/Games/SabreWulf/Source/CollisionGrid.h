#pragma once

// "Home-made" includes.
#include    <Game.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

class CollisionGrid : public Folio::Core::Game::ACollisionGrid
{
public:
    CollisionGrid ();
    ~CollisionGrid ();

private:
    // Private copy constructor to prevent copying.
    CollisionGrid (const CollisionGrid& rhs);

    // Private assignment operator to prevent copying.
    CollisionGrid& operator= (const CollisionGrid& rhs);
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
