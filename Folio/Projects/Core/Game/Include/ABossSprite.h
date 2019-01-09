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

typedef ASprite ABossSprite;

// Boss sprite pointer.
typedef std::shared_ptr<ABossSprite>    ABossSpritePtr;

// Boss sprites list.
typedef std::vector<ABossSpritePtr>     ABossSpritesList;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
