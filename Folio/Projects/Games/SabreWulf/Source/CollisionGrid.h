#pragma once

// STL includes.
#include    <memory>

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
}; // Endclass.

// Collision grid pointer.
typedef std::shared_ptr<CollisionGrid>  CollisionGridPtr;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
