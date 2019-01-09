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

typedef ASprite AWeaponSprite;

// Weapon sprite pointer.
typedef std::shared_ptr<AWeaponSprite>  AWeaponSpritePtr;

// Weapon sprites list.
typedef std::vector<AWeaponSpritePtr>   AWeaponSpritesList;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
