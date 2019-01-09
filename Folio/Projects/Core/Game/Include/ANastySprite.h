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

typedef ASprite ANastySprite;

// Nasty sprite pointer.
typedef std::shared_ptr<ANastySprite>   ANastySpritePtr;

// Nasty sprites list.
typedef std::vector<ANastySpritePtr>    ANastySpritesList;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
