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

// Drawing element identifier enumeration.
enum DRAWING_ELEMENT_ID
{
    DRAWING_ELEMENT_UNDEFINED = Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_ID_UNDEFINED,
    DRAWING_ELEMENT_BACKGROUND_ITEM = 0,
    DRAWING_ELEMENT_INFORMATION_PANEL_ITEM,
    DRAWING_ELEMENT_OBJECT_SPRITE,
    DRAWING_ELEMENT_ORCHID_SPRITE,
    DRAWING_ELEMENT_PLAYER_SPRITE,
    DRAWING_ELEMENT_NASTY_SPRITE,
    DRAWING_ELEMENT_BOSS_SPRITE,
    DRAWING_ELEMENT_BORDER_SCREEN_ITEM,
    DRAWING_ELEMENT_LOADING_SCREEN_ITEM,
    DRAWING_ELEMENT_SELECTION_SCREEN_ITEM,
    DRAWING_ELEMENT_HIGH_SCORE_SCREEN_ITEM,
    DRAWING_ELEMENT_FOUND_AMULET_PIECE_SCREEN_ITEM,
    DRAWING_ELEMENT_GAME_COMPLETED_SCREEN_ITEM,
    DRAWING_ELEMENT_GAME_OVER_SCREEN_ITEM,
    DRAWING_ELEMENT_ENTER_HIGH_SCORE_SCREEN_ITEM,
}; // Endenum.

// The maximum number of drawing elements per item.
const   UInt32  MAX_NUM_DRAWING_ELEMENTS_PER_ITEM = 256;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
