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

typedef ASprite AStaticSprite;

// Static sprite pointer.
typedef std::shared_ptr<AStaticSprite>  AStaticSpritePtr;

// Static sprites list.
typedef std::vector<AStaticSpritePtr>   AStaticSpritesList;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
