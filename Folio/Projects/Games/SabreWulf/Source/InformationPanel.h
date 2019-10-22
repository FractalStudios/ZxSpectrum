#pragma once

// STL includes.
#include    <memory>
#include    <vector>

// "Home-made" includes.
#include    <Applet.h>
#include    <Game.h>
#include    <Util.h>
#include    "DrawingElement.h"
#include    "HighScoreTable.h"
#include    "ObjectSprite.h"
#include    "PlayerSprite.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Information panel item identifier enumeration.
enum INFORMATION_PANEL_ITEM_ID
{
    INFORMATION_PANEL_ITEM_PLAYER_1_UP = DRAWING_ELEMENT_INFORMATION_PANEL_ITEM * MAX_NUM_DRAWING_ELEMENTS_PER_ITEM,
    INFORMATION_PANEL_ITEM_PLAYER_1_SCORE,
    INFORMATION_PANEL_ITEM_PLAYER_1_LIVES,
    INFORMATION_PANEL_ITEM_PLAYER_1_GRAPHIC_CHARACTER,
    INFORMATION_PANEL_ITEM_HI_TEXT,
    INFORMATION_PANEL_ITEM_HI_SCORE,
    INFORMATION_PANEL_ITEM_PLAYER_2_LIVES,
    INFORMATION_PANEL_ITEM_PLAYER_2_GRAPHIC_CHARACTER,
    INFORMATION_PANEL_ITEM_PLAYER_2_UP,
    INFORMATION_PANEL_ITEM_PLAYER_2_SCORE,
}; // Endenum.


// Information panel.
class InformationPanel
{
public:
    static  const   UInt32  SCORE_OBJECT_COLLECTED      = 150;
    static  const   UInt32  SCORE_AMULET_PIECE_FOUND    = 7350;
    static  const   UInt32  SCORE_NASTY_SPRITE_DEAD     = 165;

    InformationPanel (Folio::Core::Applet::Canvas   &canvas,
                      const HighScoreTable          &highScoreTable);
    ~InformationPanel ();

    FolioStatus Create (UInt32 totalNumScreens);
    FolioStatus Start ();
    FolioStatus Draw ();
    FolioStatus QueryItems (Folio::Core::Game::ItemsList &itemsList) const;
    FolioStatus HandleProcessFrame (bool &isStarting);

    // Player enumeration.
    enum PLAYER
    {
        PLAYER_1 = 0,
        PLAYER_2,
        MAX_NUM_PLAYERS,
    }; // Endenum.

    void    SetNumPlayers (UInt32 numPlayers);
    void    SetCurrentPlayer (PLAYER player);
    PLAYER  GetCurrentPlayer () const;

    FolioStatus IncrementScore (UInt32 scoreIncrement);
    UInt32      GetScore () const;

    FolioStatus IncrementPlayerLife (PlayerSpritePtr *playerSprite = 0);
    FolioStatus DecrementPlayerLife (PlayerSpritePtr *playerSprite = 0);

    void    IncrementNumScreensVisited ();
    UInt32  GetPercentageCompleted () const;

    void    SetFoundAmuletPiece (OBJECT_SPRITE_ID objectSpriteId);
    bool    IsFoundAmuletPieceTopLeft () const;
    bool    IsFoundAmuletPieceTopRight () const;
    bool    IsFoundAmuletPieceBottomLeft () const;
    bool    IsFoundAmuletPieceBottomRight () const;
    UInt32  GetNumFoundAmuletPieces () const;

    static  FolioNarrowString   DescribeLives (Int32 lives);
    static  FolioNarrowString   DescribeLivesCharacter (Int32 lives);
    static  FolioNarrowString   DescribeScore (UInt32 score);
    static  FolioNarrowString   DescribePercentage (UInt32 percentage);
    static  FolioNarrowString   DescribePlayer (PLAYER player);

private:
    static  const   Int32   SCREEN_X_ORIGIN = 0;
    static  const   Int32   SCREEN_Y_ORIGIN = 0;
    static  const   Int32   SCREEN_WIDTH    = Folio::Core::Game::ZxSpectrum::MAX_SCREEN_X_PIXELS;
    static  const   Int32   SCREEN_HEIGHT   = 16;

    static  const   Int32   INITIAL_NUM_LIVES   = 99;        // The initial number of lives a player can have.
    static  const   UInt32  MAX_SCORE           = 999999;   // The maximum score a player can have.

    Gdiplus::Rect   m_informationPanelScreenRect;   // The information panel's screen rect.

    Folio::Core::Applet::Canvas &m_canvas;          // The canvas.
    const HighScoreTable        &m_highScoreTable;  // The high score table.

    UInt32  m_totalNumScreens;      // The total number of screens. 
    bool    m_invertScoreColours;   // Indicates if the score colours should be inverted. 

    UInt32  m_numPlayers;       // The number of players.
    PLAYER  m_currentPlayer;    // The current player.

    // Player statistics.
    struct PlayerStats
    {
        PlayerStats ()
        :   m_startCount(0),
            m_score(0),
            m_previousScoreFrameTickCount(0),
            m_lives(INITIAL_NUM_LIVES),
            m_numScreensVisited(0),
            m_amuletPieceFound{false, false, false, false}
        {} // Endproc.

        ~PlayerStats ()
        {} // Endproc.

        void    Reset ()
        {
            m_startCount                    = 0;
            m_score                         = 0;
            m_previousScoreFrameTickCount   = 0;
            m_lives                         = INITIAL_NUM_LIVES;
            m_numScreensVisited             = 0;

            ::memset (m_amuletPieceFound, false, sizeof (m_amuletPieceFound));
        } // Endproc.

        UInt32  m_startCount;                   // The start count.
        UInt32  m_score;                        // The player's score. 
        UInt32  m_previousScoreFrameTickCount;  // The player's previous score frame tick count.
        Int32   m_lives;                        // The player's current number of lives.
        UInt32  m_numScreensVisited;            // The number of screens visited by the player.

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
    }; // Endstruct.

    PlayerStats m_playerStats [MAX_NUM_PLAYERS];    // The player statistics.

    static  Folio::Core::Util::Sound::SoundSample   m_startingSoundSample;  // Starting sound sample.

    Folio::Core::Game::ItemsList            m_itemsList;            // The information panel's items.
    Folio::Core::Game::DrawingElementsList  m_drawingElementsList;  // The information panel's drawing elements.

    FolioStatus BuildItems (FolioHandle dcHandle, 
                            FolioHandle instanceHandle);
    FolioStatus BuildDrawingElements (FolioHandle dcHandle);
    FolioStatus CheckPlayerUp (UInt32   currentTickCount,
                               bool     &isStarting);
                                                        
    // The update enumeration.
    enum UPDATE
    {
        UPDATE_LIVES = 0,
        UPDATE_PLAYER_UP,
        UPDATE_SCORE,
    }; // Endenum.

    FolioStatus Update (UPDATE update);
    FolioStatus Reset ();

    FolioStatus UpdateTextItem (Folio::Core::Game::TextItemPtr::element_type    &item,
                                bool                                            invertColours,
                                Gdiplus::Graphics                               &graphics, 
                                bool                                            &redrawCanvas);

    void    SetItemText (Folio::Core::Game::TextItemPtr::element_type &item);
    
    // Private copy constructor to prevent copying.
    InformationPanel (const InformationPanel& rhs);

    // Private assignment operator to prevent copying.
    InformationPanel& operator= (const InformationPanel& rhs);
}; // Endclass.

// Information panel pointer.
typedef std::shared_ptr<InformationPanel>   InformationPanelPtr;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
