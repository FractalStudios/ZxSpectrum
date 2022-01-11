// "Home-made" includes.
#include    <Applet.h>
#include    "EnterHighScoreScreen.h"
#include    "FoundAmuletPieceScreen.h"
#include    "GameCompletedScreen.h"
#include    "GameOverScreen.h"
#include    "HighScoreScreen.h"
#include    "LoadingScreen.h"
#include    "Screen.h" 
#include    "SelectionScreen.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

class MainCanvasMsgHandler : public Folio::Core::Applet::ACanvasMsgHandler
{
public:
    MainCanvasMsgHandler (Int32     maxScreenXPixels,
                          Int32     maxScreenYPixels,
                          UInt32    screenScale);
    ~MainCanvasMsgHandler ();

    // ACanvasMsgHandler method(s).
    virtual FolioStatus HandleCreateCanvasMsg (FolioHandle  wndHandle,
                                               UInt32       wParam,
                                               UInt32       lParam);
    virtual FolioStatus HandleDestroyCanvasMsg (FolioHandle wndHandle,
                                                UInt32      wParam,
                                                UInt32      lParam);
    virtual FolioStatus HandleProcessFrame (FolioHandle wndHandle);

private:
    // State enumeration.
    enum STATE
    {
        STATE_UNKNOWN = 0,
        STATE_LOADING_SCREEN,
        STATE_SELECTION_SCREEN,
        STATE_HIGH_SCORE_SCREEN,
        STATE_FOUND_AMULET_PIECE_SCREEN,
        STATE_GAME_COMPLETED_SCREEN,
        STATE_GAME_OVER_SCREEN,
        STATE_ENTER_HIGH_SCORE_SCREEN,
        STATE_STARTING_GAME,
        STATE_PLAYING_GAME,
        STATE_PAUSED_GAME,
    }; // Endenum.

    STATE   m_state;    // Our current state.

    LoadingScreenPtr            m_loadingScreen;            // The loading screen.
    SelectionScreenPtr          m_selectionScreen;          // The selection screen.
    HighScoreScreenPtr          m_highScoreScreen;          // The high score screen.
    FoundAmuletPieceScreenPtr   m_foundAmuletPieceScreen;   // The found amulet piece screen.
    GameCompletedScreenPtr      m_gameCompletedScreen;      // The game completed screen.
    GameOverScreenPtr           m_gameOverScreen;           // The game over screen.
    EnterHighScoreScreenPtr     m_enterHighScoreScreen;     // The enter high score screen.
    ScreensList                 m_screensList;              // The screens.

    UInt32  m_currentScreenListIndex;   // The current screen list index.

    FolioStatus Initialise ();
    FolioStatus Terminate ();

    FolioStatus HandleProcessLoadingScreenFrame (FolioHandle wndHandle);
    FolioStatus HandleProcessSelectionScreenFrame (FolioHandle wndHandle);
    FolioStatus HandleProcessHighScoreScreenFrame (FolioHandle wndHandle);
    FolioStatus HandleProcessFoundAmuletPieceScreenFrame (FolioHandle wndHandle);
    FolioStatus HandleProcessGameCompletedScreenFrame (FolioHandle wndHandle);
    FolioStatus HandleProcessGameOverScreenFrame (FolioHandle wndHandle);
    FolioStatus HandleProcessEnterHighScoreScreenFrame (FolioHandle wndHandle);
    FolioStatus HandleProcessStartingGameStateFrame (FolioHandle wndHandle);
    FolioStatus HandleProcessPlayingGameStateFrame (FolioHandle wndHandle);
    FolioStatus HandleProcessPausedGameStateFrame (FolioHandle wndHandle);

    FolioStatus CheckPlayingGameStateInput ();
    FolioStatus StartPlayingGame ();
    FolioStatus DisplayScreen (bool redisplay = false);

    void    DisplayFrameRate () const;

    // Private copy constructor to prevent copying.
    MainCanvasMsgHandler (const MainCanvasMsgHandler& rhs);

    // Private assignment operator to prevent copying.
    MainCanvasMsgHandler& operator= (const MainCanvasMsgHandler& rhs);
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/