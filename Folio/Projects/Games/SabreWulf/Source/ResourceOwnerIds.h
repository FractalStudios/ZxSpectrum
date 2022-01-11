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

// The maximum number of object sprite drawing elements.
const   UInt32  MAX_OBJECT_SPRITE_DRAWING_ELEMENTS = 2;

// The maximum number of nasty sprite drawing elements.
const   UInt32  MAX_NASTY_SPRITE_DRAWING_ELEMENTS = 6;

// The maximum number of native sprite drawing elements.
const   UInt32  MAX_NATIVE_SPRITE_DRAWING_ELEMENTS = 3;

// The maximum number of player sprite sitting drawing elements.
const   UInt32  MAX_PLAYER_SPRITE_SITTING_DRAWING_ELEMENTS = 6;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
