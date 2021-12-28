#pragma once

// STL includes.
#include    <memory>
#include    <vector>

// "Home-made" includes.
#include    <Applet.h>
#include    <Game.h>
#include    <Util.h>
#include    "ObjectSprite.h"
#include    "PlayerSprite.h"
#include    "PlayerStatistics.h"

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
    INFORMATION_PANEL_ITEM_UNDEFINED = Folio::Core::Game::AItem::ITEM_ID_UNDEFINED,
    INFORMATION_PANEL_ITEM_PLAYER_1_UP,
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
    InformationPanel (Folio::Core::Applet::Canvas& canvas);
    ~InformationPanel ();

    FolioStatus Create (UInt32 totalNumScreens);
    FolioStatus Start ();
    FolioStatus Draw ();
    FolioStatus QueryItems (Folio::Core::Game::ItemsList& itemsList) const;
    FolioStatus HandleProcessFrame (bool& isStarting);

    // Player enumeration.
    enum PLAYER
    {
        PLAYER_1 = 0,
        PLAYER_2,
        MAX_PLAYERS,
    }; // Endenum.

    void    SetNumPlayers (UInt32 numPlayers);
    void    SetCurrentPlayer (PLAYER player);
    PLAYER  GetCurrentPlayer () const;

    // Scores.
    static  const   UInt32  SCORE_OBJECT_COLLECTED      = 150;
    static  const   UInt32  SCORE_AMULET_PIECE_FOUND    = 7350;
    static  const   UInt32  SCORE_NASTY_SPRITE_DEAD     = 165;

    FolioStatus AddPlayerScore (UInt32 score);
    UInt32      GetPlayerScore () const;

    FolioStatus IncrementPlayerLife (PlayerSpritePtr *playerSprite = 0);
    FolioStatus DecrementPlayerLife (PlayerSpritePtr *playerSprite = 0);

    void    IncrementPlayerNumScreensVisited ();
    UInt32  GetPlayerPercentageGameCompleted () const;

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
    // Information panel screen attributes.
    static  const   Int32   SCREEN_X_ORIGIN = 0;
    static  const   Int32   SCREEN_Y_ORIGIN = 0;
    static  const   Int32   SCREEN_WIDTH    = Folio::Core::Game::ZxSpectrum::MAX_SCREEN_X_PIXELS;
    static  const   Int32   SCREEN_HEIGHT   = 16;

    Folio::Core::Applet::Canvas &m_canvas;  // The canvas.

    Gdiplus::Rect   m_informationPanelScreenRect;   // The information panel's screen rect.

    UInt32  m_totalNumScreens;  // The total number of screens. 

    UInt32  m_numPlayers;       // The number of players.
    PLAYER  m_currentPlayer;    // The current player.
    bool    m_invertPlayerText; // Indicates if the player text should be inverted. 

    PlayerStatistics    m_playerStatistics [MAX_PLAYERS];   // The player statistics.

    // Player starting attributes.
    struct PlayerStartingAttributes
    {
        PlayerStartingAttributes ()
        :   m_startingCounter(0),
            m_startingPreviousFrameTickCount(0)
        {} // Endproc.

        void    Reset ()
        {
            m_startingCounter                   = 0;
            m_startingPreviousFrameTickCount    = 0;
        } // Endproc.

        UInt32  m_startingCounter;                  // The starting counter.
        UInt32  m_startingPreviousFrameTickCount;   // The starting previous frame tick count.
    }; // Endstruct.
                    
    PlayerStartingAttributes    m_playerStartingAtttributes [MAX_PLAYERS];  // The player starting attributes.

    Folio::Core::Game::ItemsList            m_itemsList;            // The information panel's items.
    Folio::Core::Game::DrawingElementsList  m_drawingElementsList;  // The information panel's drawing elements.

    static  Folio::Core::Util::Sound::SoundSample   m_startingSoundSample;  // The starting sound sample.

    FolioStatus BuildItems (FolioHandle dcHandle, 
                            FolioHandle instanceHandle);
    FolioStatus BuildDrawingElements (FolioHandle dcHandle);
    FolioStatus CheckPlayerUp (UInt32   currentTickCount,
                               bool&    isStarting);

    // The update enumeration.
    enum UPDATE
    {
        UPDATE_LIVES = 0,
        UPDATE_SCORE,
        UPDATE_FLASH_PLAYER_UP,
    }; // Endenum.

    FolioStatus Update (UPDATE update);
    FolioStatus UpdateLives (Gdiplus::Graphics& graphics,
                             bool               &redrawCanvas);
    FolioStatus UpdateScore (Gdiplus::Graphics& graphics,
                             bool&              redrawCanvas);
    FolioStatus UpdateFlashPlayerUp (Gdiplus::Graphics& graphics,
                                     bool&              redrawCanvas);
    FolioStatus Reset ();

    void    SetItemText (Folio::Core::Game::TextItemPtr::element_type& item);
    
    // Private copy constructor to prevent copying.
    InformationPanel (const InformationPanel& rhs);

    // Private assignment operator to prevent copying.
    InformationPanel& operator= (const InformationPanel& rhs);
}; // Endclass.

// Information panel pointer.
typedef std::shared_ptr<InformationPanel>   InformationPanelPtr;


// Routines.

extern  FolioStatus CreateInformationPanel (Folio::Core::Applet::Canvas&    canvas, 
                                            InformationPanelPtr&            informationPanel);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
