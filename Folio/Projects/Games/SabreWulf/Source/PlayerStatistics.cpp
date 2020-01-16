// "Home-made" includes.
#include    "StdAfx.h"
#include    "PlayerStatistics.h"

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

PlayerStatistics::PlayerStatistics ()
:   m_score(0),
    m_lives(INITIAL_NUM_LIVES),
    m_numScreensVisited(0),
    m_amuletPieceFound{false, false, false, false}
{
} // Endproc.


PlayerStatistics::~PlayerStatistics ()
{
} // Endproc.


void    PlayerStatistics::Reset ()
{
    m_score             = 0;
    m_lives             = INITIAL_NUM_LIVES;
    m_numScreensVisited = 0;

    ::memset (m_amuletPieceFound, false, sizeof (m_amuletPieceFound));
} // Endproc.


UInt32  PlayerStatistics::AddScore (UInt32 score)
{
    m_score += score;

    if (m_score > MAX_SCORE)
    {
        m_score = 0;
    } // Endif.

    return (m_score);
} // Endproc.


UInt32  PlayerStatistics::GetScore () const
{
    return (m_score);
} // Endproc.


Int32   PlayerStatistics::IncrementLives ()
{
    return (++m_lives);
} // Endproc.


Int32   PlayerStatistics::DecrementLives ()
{
    return (--m_lives);
} // Endproc.


Int32   PlayerStatistics::GetLives () const
{
    return (m_lives);
} // Endproc.


bool    PlayerStatistics::IsAlive () const
{
    return (m_lives >= 0);
} // Endproc.


UInt32  PlayerStatistics::IncrementNumScreensVisited ()
{
    return (++m_numScreensVisited);
} // Endproc.


UInt32  PlayerStatistics::GetNumScreensVisited () const
{
    return (m_numScreensVisited);
} // Endproc.


void    PlayerStatistics::SetFoundAmuletPieceTopLeft ()
{
    m_amuletPieceFound [AMULET_PIECE_TOP_LEFT] = true;
} // Endproc.


bool    PlayerStatistics::IsFoundAmuletPieceTopLeft () const
{
    return (m_amuletPieceFound [AMULET_PIECE_TOP_LEFT]);
} // Endproc.


void    PlayerStatistics::SetFoundAmuletPieceTopRight ()
{
    m_amuletPieceFound [AMULET_PIECE_TOP_RIGHT] = true;
} // Endproc.


bool    PlayerStatistics::IsFoundAmuletPieceTopRight () const
{
    return (m_amuletPieceFound [AMULET_PIECE_TOP_RIGHT]);
} // Endproc.


void    PlayerStatistics::SetFoundAmuletPieceBottomLeft ()
{
    m_amuletPieceFound [AMULET_PIECE_BOTTOM_LEFT] = true;
} // Endproc.


bool    PlayerStatistics::IsFoundAmuletPieceBottomLeft () const
{
    return (m_amuletPieceFound [AMULET_PIECE_BOTTOM_LEFT]);
} // Endproc.


void    PlayerStatistics::SetFoundAmuletPieceBottomRight ()
{
    m_amuletPieceFound [AMULET_PIECE_BOTTOM_RIGHT] = true;
} // Endproc.


bool    PlayerStatistics::IsFoundAmuletPieceBottomRight () const
{
    return (m_amuletPieceFound [AMULET_PIECE_BOTTOM_RIGHT]);
} // Endproc.


UInt32  PlayerStatistics::GetNumFoundAmuletPieces () const
{
    UInt32  numFoundAmuletPieces = 0;   // Initialise!

    for (UInt32 index = AMULET_PIECE_TOP_LEFT; 
         index <= AMULET_PIECE_BOTTOM_RIGHT; 
         ++index)
    {
        if (m_amuletPieceFound [index])
        {
            numFoundAmuletPieces++;
        } // Endif.

    } // Endfor.

    return (numFoundAmuletPieces);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
