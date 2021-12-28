#pragma once

// STL includes.
#include    <map>

// "Home-made" includes.
#include    <Game.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Background item identifier enumeration.
enum BACKGROUND_ITEM_ID
{
    BACKGROUND_ITEM_70bc                                            = IDB_BITMAP_BACKGROUND_ITEM_70bc,
    BACKGROUND_ITEM_71b3                                            = IDB_BITMAP_BACKGROUND_ITEM_71b3,
    BACKGROUND_ITEM_7298                                            = IDB_BITMAP_BACKGROUND_ITEM_7298,
    BACKGROUND_ITEM_72f6                                            = IDB_BITMAP_BACKGROUND_ITEM_72f6,
    BACKGROUND_ITEM_7462                                            = IDB_BITMAP_BACKGROUND_ITEM_7462,
    BACKGROUND_ITEM_7523                                            = IDB_BITMAP_BACKGROUND_ITEM_7523,
    BACKGROUND_ITEM_771f                                            = IDB_BITMAP_BACKGROUND_ITEM_771f,
    BACKGROUND_ITEM_785e                                            = IDB_BITMAP_BACKGROUND_ITEM_785e,
    BACKGROUND_ITEM_78f2                                            = IDB_BITMAP_BACKGROUND_ITEM_78f2,
    BACKGROUND_ITEM_7947                                            = IDB_BITMAP_BACKGROUND_ITEM_7947,
    BACKGROUND_ITEM_7981                                            = IDB_BITMAP_BACKGROUND_ITEM_7981,
    BACKGROUND_ITEM_7b11                                            = IDB_BITMAP_BACKGROUND_ITEM_7b11,
    BACKGROUND_ITEM_7bb7                                            = IDB_BITMAP_BACKGROUND_ITEM_7bb7,
    BACKGROUND_ITEM_7c0c                                            = IDB_BITMAP_BACKGROUND_ITEM_7c0c,
    BACKGROUND_ITEM_7ccd                                            = IDB_BITMAP_BACKGROUND_ITEM_7ccd,
    BACKGROUND_ITEM_7e4b                                            = IDB_BITMAP_BACKGROUND_ITEM_7e4b,
    BACKGROUND_ITEM_8047                                            = IDB_BITMAP_BACKGROUND_ITEM_8047,
    BACKGROUND_ITEM_81c5                                            = IDB_BITMAP_BACKGROUND_ITEM_81c5,
    BACKGROUND_ITEM_8382                                            = IDB_BITMAP_BACKGROUND_ITEM_8382,
    BACKGROUND_ITEM_83aa                                            = IDB_BITMAP_BACKGROUND_ITEM_83aa,
    BACKGROUND_ITEM_83d2                                            = IDB_BITMAP_BACKGROUND_ITEM_83d2,
    BACKGROUND_ITEM_8427                                            = IDB_BITMAP_BACKGROUND_ITEM_8427,
    BACKGROUND_ITEM_847c                                            = IDB_BITMAP_BACKGROUND_ITEM_847c,
    BACKGROUND_ITEM_8558                                            = IDB_BITMAP_BACKGROUND_ITEM_8558,
    BACKGROUND_ITEM_85c8                                            = IDB_BITMAP_BACKGROUND_ITEM_85c8,
    BACKGROUND_ITEM_86da                                            = IDB_BITMAP_BACKGROUND_ITEM_86da,
    BACKGROUND_ITEM_8702                                            = IDB_BITMAP_BACKGROUND_ITEM_8702,
    BACKGROUND_ITEM_872a                                            = IDB_BITMAP_BACKGROUND_ITEM_872a,
    BACKGROUND_ITEM_8806                                            = IDB_BITMAP_BACKGROUND_ITEM_8806,
    BACKGROUND_ITEM_89c3                                            = IDB_BITMAP_BACKGROUND_ITEM_89c3,
    BACKGROUND_ITEM_8b80                                            = IDB_BITMAP_BACKGROUND_ITEM_8b80,
    BACKGROUND_ITEM_8c5c                                            = IDB_BITMAP_BACKGROUND_ITEM_8c5c,
    BACKGROUND_ITEM_8ccc                                            = IDB_BITMAP_BACKGROUND_ITEM_8ccc,
    BACKGROUND_ITEM_8d3c                                            = IDB_BITMAP_BACKGROUND_ITEM_8d3c,
    BACKGROUND_ITEM_8e18                                            = IDB_BITMAP_BACKGROUND_ITEM_8e18,
    BACKGROUND_ITEM_8f2a                                            = IDB_BITMAP_BACKGROUND_ITEM_8f2a,
    BACKGROUND_ITEM_90a8                                            = IDB_BITMAP_BACKGROUND_ITEM_90a8,
    BACKGROUND_ITEM_93c4                                            = IDB_BITMAP_BACKGROUND_ITEM_93c4,
    BACKGROUND_ITEM_955d                                            = IDB_BITMAP_BACKGROUND_ITEM_955d,
    BACKGROUND_ITEM_95cd                                            = IDB_BITMAP_BACKGROUND_ITEM_95cd,
    BACKGROUND_ITEM_9673                                            = IDB_BITMAP_BACKGROUND_ITEM_9673,
    BACKGROUND_ITEM_e1ec                                            = IDB_BITMAP_BACKGROUND_ITEM_e1ec,
    BACKGROUND_ITEM_BACKGROUND_ITEM_e3a0_AMULET_PIECE_TOP_LEFT      = IDB_BITMAP_BACKGROUND_ITEM_e3a0_AMULET_PIECE_TOP_LEFT,
    BACKGROUND_ITEM_BACKGROUND_ITEM_e3a0_AMULET_BLANK_TOP_LEFT      = IDB_BITMAP_BACKGROUND_ITEM_e3a0_AMULET_BLANK_TOP_LEFT,
    BACKGROUND_ITEM_BACKGROUND_ITEM_e494_AMULET_PIECE_TOP_RIGHT     = IDB_BITMAP_BACKGROUND_ITEM_e494_AMULET_PIECE_TOP_RIGHT,
    BACKGROUND_ITEM_BACKGROUND_ITEM_e494_AMULET_BLANK_TOP_RIGHT     = IDB_BITMAP_BACKGROUND_ITEM_e494_AMULET_BLANK_TOP_RIGHT,
    BACKGROUND_ITEM_BACKGROUND_ITEM_e588_AMULET_PIECE_BOTTOM_LEFT   = IDB_BITMAP_BACKGROUND_ITEM_e588_AMULET_PIECE_BOTTOM_LEFT,
    BACKGROUND_ITEM_BACKGROUND_ITEM_e588_AMULET_BLANK_BOTTOM_LEFT   = IDB_BITMAP_BACKGROUND_ITEM_e588_AMULET_BLANK_BOTTOM_LEFT,
    BACKGROUND_ITEM_BACKGROUND_ITEM_e67c_AMULET_PIECE_BOTTOM_RIGHT  = IDB_BITMAP_BACKGROUND_ITEM_e67c_AMULET_PIECE_BOTTOM_RIGHT,
    BACKGROUND_ITEM_BACKGROUND_ITEM_e67c_AMULET_BLANK_BOTTOM_RIGHT  = IDB_BITMAP_BACKGROUND_ITEM_e67c_AMULET_BLANK_BOTTOM_RIGHT,
}; // Endenum.

// Background item graphic.
typedef Folio::Core::Game::ResourceGraphicPtr   BackgroundItemGraphic;

// Background item graphics map.
typedef std::map<BACKGROUND_ITEM_ID, BackgroundItemGraphic> BackgroundItemGraphicsMap;
             

// Routines.

extern  FolioStatus CreateBackgroundItemGraphics (FolioHandle                   instanceHandle,
                                                  BackgroundItemGraphicsMap&    backgroundItemGraphicsMap);
extern  FolioStatus FindBackgroundItemGraphic (BACKGROUND_ITEM_ID               backgroundItemId,
                                               const BackgroundItemGraphicsMap& backgroundItemGraphicsMap,
                                               BackgroundItemGraphic&           backgroundItemGraphic);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
