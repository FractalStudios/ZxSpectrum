#pragma once

// STL includes.
#include    <vector>

// "Home-made" includes.
#include    <Base.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// High score table.
class HighScoreTable
{
public:
    HighScoreTable ();
    ~HighScoreTable ();

    // High score.
    struct HighScore
    {
        static  const   UInt32  MAX_INITIALS = 3;   // The maximum number of initials.

        HighScore ()
        :   m_score(0)
        {} // Endproc.

        HighScore (UInt32                   score,
                   const FolioNarrowString  &initials)
        :   m_score(score),
            m_initials(initials)
        {} // Endproc.

        ~HighScore ()
        {} // Endproc.

        bool    operator < (const HighScore &rhs)
        {
            // Sort from high to low.

            return (m_score > rhs.m_score);
        } // Endproc.

        UInt32              m_score;    // The score.
        FolioNarrowString   m_initials; // The player's initials.
    }; // Endstruct.

    bool    IsHighScore (UInt32 score) const;
    UInt32  GetHighScorePosition (UInt32 score) const;
    void    AddHighScore (const HighScore &highScore);
    
    HighScore   GetHighScore (UInt32 highScorePosition) const;
    UInt32      GetHighestScore () const;

    static  FolioNarrowString   DescribeHighScorePosition (UInt32 highScorePosition);

private:
    // High score list.
    typedef std::vector<HighScore>  HighScoreList;

    HighScoreList   m_highScoreList;    // The high score list.

    void    SortHighScoreList ();
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
