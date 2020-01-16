#pragma once

// "Home-made" includes.
#include    <Base.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Player statistics.
class PlayerStatistics
{
public:
    PlayerStatistics ();
    ~PlayerStatistics ();

    void    Reset ();

    UInt32  AddScore (UInt32 score);
    UInt32  GetScore () const;

    Int32   IncrementLives ();
    Int32   DecrementLives ();
    Int32   GetLives () const;
    bool    IsAlive () const;

    UInt32  IncrementNumScreensVisited ();
    UInt32  GetNumScreensVisited () const;

    void    SetFoundAmuletPieceTopLeft ();
    bool    IsFoundAmuletPieceTopLeft () const;
    
    void    SetFoundAmuletPieceTopRight ();
    bool    IsFoundAmuletPieceTopRight () const;
    
    void    SetFoundAmuletPieceBottomLeft ();
    bool    IsFoundAmuletPieceBottomLeft () const;
    
    void    SetFoundAmuletPieceBottomRight ();
    bool    IsFoundAmuletPieceBottomRight () const;
    
    UInt32  GetNumFoundAmuletPieces () const;

private:
    static  const   Int32   INITIAL_NUM_LIVES   = 4;        // The initial number of lives a player can have.
    static  const   UInt32  MAX_SCORE           = 999999;   // The maximum score a player can have.

    UInt32  m_score;                // The player's score. 
    Int32   m_lives;                // The player's current number of lives.
    UInt32  m_numScreensVisited;    // The number of screens visited by the player.

    // Amulet piece enumeration.
    enum AMULET_PIECE
    {
        AMULET_PIECE_TOP_LEFT = 0,
        AMULET_PIECE_TOP_RIGHT,
        AMULET_PIECE_BOTTOM_LEFT,
        AMULET_PIECE_BOTTOM_RIGHT,
        MAX_AMULET_PIECES,
    }; // Endenum.

    bool    m_amuletPieceFound [MAX_AMULET_PIECES]; // Indicates if each amulet piece (TL,TR,BL,BR) has been found by the player.
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
