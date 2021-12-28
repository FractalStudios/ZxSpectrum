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

// Resource graphics cache owner identifiers.
const   Folio::Core::Game::ResourceGraphicsCache::OwnerId   OWNER_ID_ORCHID_SPRITE = TXT("Orchid Sprite");

// The maximum number of object sprites per screen.
const   UInt32  MAX_OBJECT_SPRITES_PER_SCREEN = 2 * 2;  //iac

// The maximum number of nasty sprite drawing elements.
const   UInt32  MAX_NASTY_SPRITE_DRAWING_ELEMENTS = 6;

// The maximum number of native sprite drawing elements.
const   UInt32  MAX_NATIVE_SPRITE_DRAWING_ELEMENTS = 3;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
