// "Home-made" includes.
#include    "StdAfx.h"
#include    <Util.h>
#include    "Globals.h"
#include    "MainCanvasMsgHandler.h"

//#define _AUTO_TEST_
#define AUTO_TEST_SCREEN_TIME 5 * 1000

namespace Folio
{

namespace Core
{

namespace Applet
{

ACanvasMsgHandler*  CreateCanvasMsgHandler ()
{
    // Create our initial canvas message handler.

    return (new Folio::Games::SabreWulf::MainCanvasMsgHandler(Folio::Core::Game::ZxSpectrum::MAX_SCREEN_X_PIXELS, 
                                                              Folio::Core::Game::ZxSpectrum::MAX_SCREEN_Y_PIXELS,
                                                              Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE));
} // Endproc.

} // Endnamespace.

} // Endnamespace.

namespace Games
{

namespace SabreWulf
{

MainCanvasMsgHandler::MainCanvasMsgHandler (Int32   maxScreenXPixels,           
                                            Int32   maxScreenYPixels,
                                            UInt32  screenScale)
:   ACanvasMsgHandler(maxScreenXPixels, maxScreenYPixels, screenScale),
    m_state(STATE_LOADING_SCREEN),
    m_currentScreenListIndex(ScreenMap::INITIAL_SCREEN_INDEX)
{
} // Endproc.


MainCanvasMsgHandler::~MainCanvasMsgHandler ()
{
} // Endproc.


FolioStatus MainCanvasMsgHandler::HandleCreateCanvasMsg (FolioHandle    wndHandle,
                                                         UInt32         wParam,
                                                         UInt32         lParam)
{
    // Set the canvas's window text.

    Folio::Core::Util::Wnd::SetWndText (wndHandle, TXT("Sabre Wulf by fractal studios"));

    // Initialise.

    return (Initialise ());
} // Endproc.


FolioStatus MainCanvasMsgHandler::HandleDestroyCanvasMsg (FolioHandle   wndHandle,
                                                          UInt32        wParam,
                                                          UInt32        lParam)
{
    // Terminate.

    return (Terminate ());
} // Endproc.


FolioStatus MainCanvasMsgHandler::HandleProcessFrame (FolioHandle wndHandle)
{
#ifdef _DEBUG
    DisplayFrameRate ();
#endif

    FolioStatus status = ERR_SUCCESS;

    // Processing the frame is dependent on our state.

    switch (m_state)
    {
    case STATE_LOADING_SCREEN:
        status = HandleProcessLoadingScreenFrame (wndHandle);
        break;

    case STATE_SELECTION_SCREEN:
        status = HandleProcessSelectionScreenFrame (wndHandle);
        break;

    case STATE_HIGH_SCORE_SCREEN:
        status = HandleProcessHighScoreScreenFrame (wndHandle);
        break;

    case STATE_FOUND_AMULET_PIECE_SCREEN:
        status = HandleProcessFoundAmuletPieceScreenFrame (wndHandle);
        break;

    case STATE_GAME_COMPLETED_SCREEN:
        status = HandleProcessGameCompletedScreenFrame (wndHandle);
        break;

    case STATE_GAME_OVER_SCREEN:
        status = HandleProcessGameOverScreenFrame (wndHandle);
        break;

    case STATE_ENTER_HIGH_SCORE_SCREEN:
        status = HandleProcessEnterHighScoreScreenFrame (wndHandle);
        break;

    case STATE_STARTING_GAME:
        status = HandleProcessStartingGameStateFrame (wndHandle);
        break;

    case STATE_PLAYING_GAME:
        status = HandleProcessPlayingGameStateFrame (wndHandle);
        break;

    case STATE_PAUSED_GAME:
        status = HandleProcessPausedGameStateFrame (wndHandle);
        break;

    default:
        break;
    } // Endswitch.

    if (status == ERR_SUCCESS)
    {
        // Draw the canvas.

        status = m_canvas->DrawCanvas (m_canvas->IsRedrawRqd ());
    } // Endif.
    
    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::Initialise ()
{
    // Set random seed.

    Folio::Core::Util::Random::SetRandomSeed ();

    // Initialise globals.

    return (InitialiseGlobals (*m_canvas));
} // Endproc.


FolioStatus MainCanvasMsgHandler::Terminate ()
{
    // Terminate globals.

    return (TerminateGlobals ());
} // Endproc.


FolioStatus MainCanvasMsgHandler::HandleProcessLoadingScreenFrame (FolioHandle wndHandle)
{
    FolioStatus status = ERR_SUCCESS;

    // Has the loading screen been created?

    if (!m_loadingScreen)
    {
        // No. Create the loading screen.

        m_loadingScreen.reset (new LoadingScreenPtr::element_type);

        status = m_loadingScreen->Create (*m_canvas, m_canvas->GetCanvasScreenRect (), 2 * 1000);
    } // Endif.

    if (status == ERR_SUCCESS)
    {
        // Let the loading screen process the frame.

        status = m_loadingScreen->HandleProcessFrame ();

        // Is the loading screen complete?

        if ((status == ERR_SUCCESS) && m_loadingScreen->IsComplete ())
        {
            // Yes. Destroy the loading screen.

            m_loadingScreen.reset ();

            // Move to the selection screen.

            m_state = STATE_SELECTION_SCREEN;
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::HandleProcessSelectionScreenFrame (FolioHandle wndHandle)
{
    FolioStatus status = ERR_SUCCESS;

    // Has the selection screen been created?

    if (!m_selectionScreen)
    {
        // No. Create the selection screen.

        m_selectionScreen.reset (new SelectionScreenPtr::element_type);

        status = m_selectionScreen->Create (*m_canvas, m_canvas->GetCanvasScreenRect ());
    } // Endif.

    if (status == ERR_SUCCESS)
    {
        // Let the selection screen process the frame.

        status = m_selectionScreen->HandleProcessFrame ();

        // Is the selection screen complete?

        if ((status == ERR_SUCCESS) && m_selectionScreen->IsComplete ())
        {
            // Yes. Ready to start the game?
        
            if (m_selectionScreen->IsStartGame ())
            {
                // Yes. Start playing the game.

                status = StartPlayingGame ();
            } // Endif.

            else
            {
                // No. Move to the high score screen.
            
                m_state = STATE_HIGH_SCORE_SCREEN;
            } // Endelse.
        
        } // Endif.
    
    } // Endif.

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::HandleProcessHighScoreScreenFrame (FolioHandle wndHandle)
{
    FolioStatus status = ERR_SUCCESS;

    // Has the high score screen been created?

    if (!m_highScoreScreen)
    {
        // No. Create the high score screen.

        m_highScoreScreen.reset (new HighScoreScreenPtr::element_type);

        status = m_highScoreScreen->Create (*m_canvas, m_canvas->GetCanvasScreenRect ());
    } // Endif.

    if (status == ERR_SUCCESS)
    {
        // Let the high score screen process the frame.

        status = m_highScoreScreen->HandleProcessFrame ();

        // Is the high score screen complete?

        if ((status == ERR_SUCCESS) && m_highScoreScreen->IsComplete ())
        {
            // Yes. Destroy the high score screen.

            m_highScoreScreen.reset ();
            
            // Move to the selection screen.
            
            m_state = STATE_SELECTION_SCREEN;
        } // Endif.
    
    } // Endif.

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::HandleProcessFoundAmuletPieceScreenFrame (FolioHandle wndHandle)
{
    FolioStatus status = ERR_SUCCESS;

    // Has the found amulet piece screen been created?

    if (!m_foundAmuletPieceScreen)
    {
        // No. Create the found amulet piece screen.

        m_foundAmuletPieceScreen.reset (new FoundAmuletPieceScreenPtr::element_type);

        status = m_foundAmuletPieceScreen->Create (*m_canvas, m_canvas->GetCanvasScreenRect ());
    } // Endif.

    if (status == ERR_SUCCESS)
    {
        // Let the found amulet piece screen process the frame.

        status = m_foundAmuletPieceScreen->HandleProcessFrame ();

        // Is the found amulet piece screen complete?

        if ((status == ERR_SUCCESS) && m_foundAmuletPieceScreen->IsComplete ())
        {
            // Yes. Destroy the found amulet piece screen.

            m_foundAmuletPieceScreen.reset ();
            
            // The player has not just found an amulet piece.

            g_playerSprite->ResetJustFoundAmuletPiece ();

            // Display the current screen.

            status = DisplayScreen ();
                
            if (status == ERR_SUCCESS)
            {        
                // We're back playing.

                m_state = STATE_PLAYING_GAME;
            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::HandleProcessGameCompletedScreenFrame (FolioHandle wndHandle)
{
    FolioStatus status = ERR_SUCCESS;

    // Has the game completed screen been created?

    if (!m_gameCompletedScreen)
    {
        // No. Create the game completed screen.

        m_gameCompletedScreen.reset (new GameCompletedScreenPtr::element_type);

        status = m_gameCompletedScreen->Create (*m_canvas, m_canvas->GetCanvasScreenRect ());
    } // Endif.

    if (status == ERR_SUCCESS)
    {
        // Let the game completed screen process the frame.

        status = m_gameCompletedScreen->HandleProcessFrame ();

        // Is the game completed screen complete?

        if ((status == ERR_SUCCESS) && m_gameCompletedScreen->IsComplete ())
        {
            // Yes. Destroy the game completed screen.

            m_gameCompletedScreen.reset ();

            // Move to the game over screen.

            m_state = STATE_GAME_OVER_SCREEN;
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::HandleProcessGameOverScreenFrame (FolioHandle wndHandle)
{
    FolioStatus status = ERR_SUCCESS;

    // Has the game over screen been created?

    if (!m_gameOverScreen)
    {
        // No. Create the game over screen.

        m_gameOverScreen.reset (new GameOverScreenPtr::element_type);

        status = m_gameOverScreen->Create (*m_canvas, m_canvas->GetCanvasScreenRect ());
    } // Endif.

    if (status == ERR_SUCCESS)
    {
        // Let the game over screen process the frame.

        status = m_gameOverScreen->HandleProcessFrame ();

        // Is the game over screen complete?

        if ((status == ERR_SUCCESS) && m_gameOverScreen->IsComplete ())
        {
            // Yes. Destroy the game over screen.

            m_gameOverScreen.reset ();

            // Did the player register a high score?

            if (g_highScoreTable.IsHighScore (g_informationPanel->GetPlayerScore ()))
            {
                // Yes. Move to the enter high score screen.

                m_state = STATE_ENTER_HIGH_SCORE_SCREEN;
            } // Endif.

            else
            {
                // No. Move to the selection screen.

                m_state = STATE_SELECTION_SCREEN;
            } // Endelse.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::HandleProcessEnterHighScoreScreenFrame (FolioHandle wndHandle)
{
    FolioStatus status = ERR_SUCCESS;

    // Has the enter high score screen been created?

    if (!m_enterHighScoreScreen)
    {
        // No. Create the enter high score screen.

        m_enterHighScoreScreen.reset (new EnterHighScoreScreenPtr::element_type(m_selectionScreen));

        status = m_enterHighScoreScreen->Create (*m_canvas, m_canvas->GetCanvasScreenRect ());
    } // Endif.

    if (status == ERR_SUCCESS)
    {
        // Let the enter high score screen process the frame.

        status = m_enterHighScoreScreen->HandleProcessFrame ();

        // Is the enter high score screen complete?

        if ((status == ERR_SUCCESS) && m_enterHighScoreScreen->IsComplete ())
        {
            // Yes. Destroy the enter high score screen.

            m_enterHighScoreScreen.reset ();

            // Move to the high score screen.
                             
            m_state = STATE_HIGH_SCORE_SCREEN;
        } // Endif.
        
    } // Endif.

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::HandleProcessStartingGameStateFrame (FolioHandle wndHandle)
{
    // Let the current screen process the frame.

    bool    isStarting = true;  // Initialise!

    FolioStatus status = m_screensList [m_currentScreenListIndex]->HandleProcessFrame (isStarting);

    // Still starting?

    if (!isStarting && (status == ERR_SUCCESS))
    {
        // No. We're playing.

        m_state = STATE_PLAYING_GAME;
    } // Endif.

    return (status);
} // Endproc.


#ifdef _AUTO_TEST_
FolioStatus MainCanvasMsgHandler::HandleProcessPlayingGameStateFrame (FolioHandle wndHandle)
{
    static  UInt32  s_screenTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount ();

    // Let the current screen process the frame.

    bool    isStarting = false; // Initialise!

    FolioStatus status = m_screensList [m_currentScreenListIndex]->HandleProcessFrame (isStarting);
        
    if (status == ERR_SUCCESS)
    {
        //if (m_selectionScreen->IsPlayerFireKeyDown ())
        if (Folio::Core::Util::DateTime::GetCurrentTickCount () > (s_screenTickCount + AUTO_TEST_SCREEN_TIME))
        {
            m_screensList [m_currentScreenListIndex]->ExitScreen ();

            s_screenTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount ();

            if (++g_screenMap.m_currentScreenMapIndex >= g_screenMap.GetTotalNumScreens ())
            {
                //Folio::Core::Util::g_handleMonitor.Dump ();
                //g_resourceGraphicsCache.Dump (false);
                g_resourceGraphicsCache.DumpNumUsedBitmaps (false);

                g_screenMap.m_currentScreenMapIndex = 0;
            } // Endif.
            
            status = DisplayScreen ();
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.
#else
FolioStatus MainCanvasMsgHandler::HandleProcessPlayingGameStateFrame (FolioHandle wndHandle)
{
    // Check input.

    FolioStatus status = CheckPlayingGameStateInput ();

    if (status == ERR_SUCCESS)
    {
        // Let the current screen process the frame.

        bool    isStarting = false; // Initialise!

        status = m_screensList [m_currentScreenListIndex]->HandleProcessFrame (isStarting);
        
        if (status == ERR_SUCCESS)
        {
            // Reset player fire key down.

            g_playerSprite->SetFireKeyDown (false);

            // Has the player exited a screen?

            if (g_playerSprite->IsExitedScreen ())
            {
                // Yes. Display the new screen.

               status = DisplayScreen ();
            } // Endif.

            // Has the player just found an amulet piece?
            
            else
            if (g_playerSprite->IsJustFoundAmuletPiece ())
            {
                // Yes. Display the found amulet piece screen.

                m_state = STATE_FOUND_AMULET_PIECE_SCREEN;
            } // Endelseif.

            // Is the game over?

            else
            if (g_playerSprite->IsGameOver ())
            {
                // Yes. Display the game over screen.

                m_state = STATE_GAME_OVER_SCREEN;
            } // Endelseif.

           // Has the player completed the game?
            
            else
            if (g_playerSprite->IsGameCompleted ())
            {
                // Yes. Display the game completed screen.

                m_state = STATE_GAME_COMPLETED_SCREEN;
            } // Endelseif.

        } // Endif.
    
    } // Endif.

    return (status);
} // Endproc.
#endif

FolioStatus MainCanvasMsgHandler::HandleProcessPausedGameStateFrame (FolioHandle wndHandle)
{
    FolioStatus status = ERR_SUCCESS;

    // Pause game key down?  

    if (m_selectionScreen->IsPauseGameKeyDown ())
    {
        // Yes. We're back playing.

        m_state = STATE_PLAYING_GAME;
    } // Endif.

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::CheckPlayingGameStateInput ()
{
    FolioStatus status = ERR_SUCCESS;

    // Is the player ready?

    if (g_playerSprite->IsReady ())
    {
        // Is the pause game key down?  

        if (m_selectionScreen->IsPauseGameKeyDown ())
        {
            // Yes. Pause the game.

            m_state = STATE_PAUSED_GAME;
        } // Endif.

        else
        {
            // Is the player fire key down?  

            if (m_selectionScreen->IsPlayerFireKeyDown ())
            {
                // Yes. Set player fire key down.

                g_playerSprite->SetFireKeyDown (true);
            } // Endif.

            // Is a player's direction key down?

            Folio::Core::Game::Direction    direction = Folio::Core::Game::NO_DIRECTION;    // Initialise!

            if (m_selectionScreen->IsPlayerDirectionKeyDown (direction))
            {
                // Yes. Update the player's direction.

                status = g_playerSprite->UpdateDirection (direction, true);
            } // Endif.

            // Is the player moving?

            else
            if (g_playerSprite->IsMoving ())
            {
                // Yes. Update the player's direction.

                status = g_playerSprite->UpdateDirection (direction, false);
            } // Endelseif.

        } // Endelse.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::StartPlayingGame ()
{
    // Initialise globals.

    FolioStatus status = InitialiseGlobals (*m_canvas, false);

    if (status == ERR_SUCCESS)
    {
        // Start the information panel.

        status = g_informationPanel->Start ();

        if (status == ERR_SUCCESS)
        {
            // Start the player.

            status = g_playerSprite->Start ();

            if (status == ERR_SUCCESS)
            {
                // Build the screens.

                status = BuildScreens (*m_canvas, m_screensList);

                if (status == ERR_SUCCESS)
                {        
                    // Display the initial screen.

                    status = DisplayScreen ();
                
                    if (status == ERR_SUCCESS)
                    {        
                        // We're starting.

                        m_state = STATE_STARTING_GAME;
                    } // Endif.

                } // Endif.

            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::DisplayScreen ()
{
    // Get the current screen map index.

    m_currentScreenListIndex = g_screenMap.GetCurrentScreenMapIndex ();

    // Draw the current screen.

    return (m_screensList [m_currentScreenListIndex]->Draw ());
} // Endproc.


void    MainCanvasMsgHandler::DisplayFrameRate () const
{
    static  Int64   s_previousTickCount     = Folio::Core::Util::DateTime::GetCurrentPerformanceCounter (); // Initialise!
    static  Int64   s_performanceFrequency  = Folio::Core::Util::DateTime::GetPerformanceFrequency ();

    UInt32  elapsedTime = Folio::Core::Util::DateTime::CalculateElapsedTime (s_previousTickCount,
                                                                             s_performanceFrequency);
    s_previousTickCount = Folio::Core::Util::DateTime::GetCurrentPerformanceCounter ();

    FolioOStringStream  str;
    str << TXT("FrameRate: ") << elapsedTime
        << TXT(" ScreenListIndex: ") << m_currentScreenListIndex
        << TXT(" ScreenNumber: ") << g_screenMap.GetCurrentScreenNumber ();
    Folio::Core::Util::Wnd::SetWndText (m_canvas->GetCanvasWndHandle (), str.str ().c_str ());
    
    str << std::endl;
    ::OutputDebugString (str.str ().c_str ());
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
