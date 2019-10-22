// "Home-made" includes.
#include    "StdAfx.h"
#include    "HighScoreTable.h"

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

HighScoreTable::HighScoreTable ()
:   m_highScoreList{ {102275, "ULT"}, {55150, "ACG"}, {37895, "CTJ"}, {24320, "TDJ"}, {12775, "JSL"}, {8250, "CLW"} }
{
    // Sort the high score list.

    SortHighScoreList ();
} // Endproc.


HighScoreTable::~HighScoreTable ()
{
} // Endproc.


bool    HighScoreTable::IsHighScore (UInt32 score) const
{
    return (score >= m_highScoreList.back ().m_score);
} // Endproc.


UInt32  HighScoreTable::GetHighScorePosition (UInt32 score) const
{
    UInt32  highScorePosition = 0;  // Initialise!

    for (;
         highScorePosition < m_highScoreList.size ();
         ++highScorePosition)
    {
        if (score >= m_highScoreList [highScorePosition].m_score)
        {
            break;
        } // Endif.

    } // Endfor.

    return (highScorePosition);
} // Endproc.


void    HighScoreTable::AddHighScore (const HighScore &highScore)
{
    // Is this a high score?

    if (IsHighScore (highScore.m_score))
    {
        // Yes. Remove the last high score in the high score list.

        m_highScoreList.pop_back ();

        // Add the high score to the high score list.

        m_highScoreList.push_back (highScore);

        // Sort the high score list.

        SortHighScoreList ();
    } // Endif.

} // Endproc.


HighScoreTable::HighScore   HighScoreTable::GetHighScore (UInt32 highScorePosition) const
{
    return ((highScorePosition < m_highScoreList.size ()) ? m_highScoreList [highScorePosition] : HighScore());
} // Endproc.


UInt32  HighScoreTable::GetHighestScore () const
{
    return (m_highScoreList.front ().m_score);
} // Endproc.


FolioNarrowString   HighScoreTable::DescribeHighScorePosition (UInt32 highScorePosition)
{
    switch (highScorePosition)
    {
    case 0:
        return ("1ST");

    case 1:
        return ("2ND");

    case 2:
        return ("3RD");

    case 3:
        return ("4TH");

    case 4:
        return ("5TH");

    case 5:
        return ("6TH");

    default:
        return ("???");
    } // Endswitch.

} // Endproc.


void    HighScoreTable::SortHighScoreList ()
{
    // Sort the high score list.

    std::sort (m_highScoreList.begin (), m_highScoreList.end ());
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
