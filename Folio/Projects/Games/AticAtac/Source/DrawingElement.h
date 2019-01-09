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

// Drawing element identifier enumeration.
enum DRAWING_ELEMENT_ID
{
    DRAWING_ELEMENT_UNDEFINED = Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_ID_UNDEFINED,
    DRAWING_ELEMENT_ROOM = 0,               // Part of a screen's reported drawing elements.
    DRAWING_ELEMENT_BACKGROUND_ITEM,        // Part of a screen's reported drawing elements.
    DRAWING_ELEMENT_INFORMATION_PANEL_ITEM, // Part of a screen's reported drawing elements.
    DRAWING_ELEMENT_STATIC_SPRITE,
    DRAWING_ELEMENT_NASTY_SPRITE,
    DRAWING_ELEMENT_BOSS_SPRITE,
    DRAWING_ELEMENT_WEAPON_SPRITE,
    DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,
    DRAWING_ELEMENT_FALLING_SIMULATION_SCREEN_ITEM,
    DRAWING_ELEMENT_SELECTION_SCREEN_ITEM,
    DRAWING_ELEMENT_LOADING_SCREEN_ITEM,
    DRAWING_ELEMENT_GAME_OVER_SCREEN_ITEM,
}; // Endenum.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
