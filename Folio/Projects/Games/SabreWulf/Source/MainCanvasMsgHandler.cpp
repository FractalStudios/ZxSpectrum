// "Home-made" includes.
#include    "StdAfx.h"
#include    <Util.h>
#include    "MainCanvasMsgHandler.h"

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
    m_currentScreenIndex(ScreenMap::INITIAL_SCREEN_INDEX)
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


FolioStatus MainCanvasMsgHandler::HandleProcessFrame (FolioHandle   wndHandle, 
                                                      UInt32        &frameRateIncrement)
{
#ifdef _DEBUG
    DisplayFrameRate ();
#endif

    FolioStatus status = ERR_SUCCESS;

    frameRateIncrement = 0; // Initialise!

    // Processing the frame is dependent on our state.

    switch (m_state)
    {
    case STATE_LOADING_SCREEN:
        status = HandleProcessLoadingScreenFrame (wndHandle, &(frameRateIncrement));
        break;

    case STATE_SELECTION_SCREEN:
        status = HandleProcessSelectionScreenFrame (wndHandle, &(frameRateIncrement));
        break;

    case STATE_HIGH_SCORE_SCREEN:
        status = HandleProcessHighScoreScreenFrame (wndHandle, &(frameRateIncrement));
        break;

    case STATE_FOUND_AMULET_PIECE_SCREEN:
        status = HandleProcessFoundAmuletPieceScreenFrame (wndHandle, &(frameRateIncrement));
        break;

    case STATE_GAME_COMPLETED_SCREEN:
        status = HandleProcessGameCompletedScreenFrame (wndHandle, &(frameRateIncrement));
        break;

    case STATE_GAME_OVER_SCREEN:
        status = HandleProcessGameOverScreenFrame (wndHandle, &(frameRateIncrement));
        break;

    case STATE_ENTER_HIGH_SCORE_SCREEN:
        status = HandleProcessEnterHighScoreScreenFrame (wndHandle, &(frameRateIncrement));
        break;

    case STATE_STARTING_GAME:
        status = HandleProcessStartingGameStateFrame (wndHandle, &(frameRateIncrement));
        break;

    case STATE_PLAYING_GAME:
        status = HandleProcessPlayingGameStateFrame (wndHandle, &(frameRateIncrement));
        break;

    case STATE_PAUSED_GAME:
        status = HandleProcessPausedGameStateFrame (wndHandle, &(frameRateIncrement));
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


FolioStatus MainCanvasMsgHandler::HandleProcessLoadingScreenFrame (FolioHandle  wndHandle,
                                                                   UInt32       *frameRateIncrement)
{
    FolioStatus status = ERR_SUCCESS;

    if (!m_loadingScreen)
    {
        // Create the loading screen.

        m_loadingScreen.reset (new LoadingScreenPtr::element_type);

        status = m_loadingScreen->Create (*m_canvas, m_canvas->GetCanvasScreenRect (), 2 * 1000);
    } // Endif.

    if (status == ERR_SUCCESS)
    {
        // Let the loading screen process the frame.

        status = m_loadingScreen->HandleProcessFrame (frameRateIncrement);

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


FolioStatus MainCanvasMsgHandler::HandleProcessSelectionScreenFrame (FolioHandle    wndHandle,
                                                                     UInt32         *frameRateIncrement)
{
    FolioStatus status = ERR_SUCCESS;

    if (!m_selectionScreen)
    {
        // Create the selection screen.

        m_selectionScreen.reset (new SelectionScreenPtr::element_type(m_informationPanel));

        status = m_selectionScreen->Create (*m_canvas, m_canvas->GetCanvasScreenRect ());
    } // Endif.

    if (status == ERR_SUCCESS)
    {
        // Let the selection screen process the frame.

        status = m_selectionScreen->HandleProcessFrame (frameRateIncrement);

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


FolioStatus MainCanvasMsgHandler::HandleProcessHighScoreScreenFrame (FolioHandle    wndHandle,
                                                                     UInt32         *frameRateIncrement)
{
    FolioStatus status = ERR_SUCCESS;

    if (!m_highScoreScreen)
    {
        // Create the high score screen.

        m_highScoreScreen.reset (new HighScoreScreenPtr::element_type(m_informationPanel, m_highScoreTable));

        status = m_highScoreScreen->Create (*m_canvas, m_canvas->GetCanvasScreenRect ());
    } // Endif.

    if (status == ERR_SUCCESS)
    {
        // Let the high score screen process the frame.

        status = m_highScoreScreen->HandleProcessFrame (frameRateIncrement);

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


FolioStatus MainCanvasMsgHandler::HandleProcessFoundAmuletPieceScreenFrame (FolioHandle wndHandle,
                                                                            UInt32      *frameRateIncrement)
{
    FolioStatus status = ERR_SUCCESS;

    if (!m_foundAmuletPieceScreen)
    {
        // Create the found amulet piece screen.

        m_foundAmuletPieceScreen.reset (new FoundAmuletPieceScreenPtr::element_type(m_informationPanel));

        status = m_foundAmuletPieceScreen->Create (*m_canvas, m_canvas->GetCanvasScreenRect (), 10 * 1000);
    } // Endif.

    if (status == ERR_SUCCESS)
    {
        // Let the found amulet piece screen process the frame.

        status = m_foundAmuletPieceScreen->HandleProcessFrame (frameRateIncrement);

        // Is the found amulet piece screen complete?

        if ((status == ERR_SUCCESS) && m_foundAmuletPieceScreen->IsComplete ())
        {
            // Yes. Destroy the found amulet piece screen.

            m_foundAmuletPieceScreen.reset ();
            
            // Reset the found amulet piece.

            m_playerSprite->SetFoundAmuletPiece (false);

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


FolioStatus MainCanvasMsgHandler::HandleProcessGameCompletedScreenFrame (FolioHandle    wndHandle,
                                                                         UInt32         *frameRateIncrement)
{
    FolioStatus status = ERR_SUCCESS;

    if (!m_gameCompletedScreen)
    {
        // Create the game completed screen.

        m_gameCompletedScreen.reset (new GameCompletedScreenPtr::element_type(m_informationPanel));

        status = m_gameCompletedScreen->Create (*m_canvas, m_canvas->GetCanvasScreenRect (), 10 * 1000);
    } // Endif.

    if (status == ERR_SUCCESS)
    {
        // Let the game completed screen process the frame.

        status = m_gameCompletedScreen->HandleProcessFrame (frameRateIncrement);

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


FolioStatus MainCanvasMsgHandler::HandleProcessGameOverScreenFrame (FolioHandle wndHandle,
                                                                    UInt32      *frameRateIncrement)
{
    FolioStatus status = ERR_SUCCESS;

    if (!m_gameOverScreen)
    {
        // Create the game over screen.

        m_gameOverScreen.reset (new GameOverScreenPtr::element_type(m_informationPanel));

        status = m_gameOverScreen->Create (*m_canvas, m_canvas->GetCanvasScreenRect (), 10 * 1000);
    } // Endif.

    if (status == ERR_SUCCESS)
    {
        // Let the game over screen process the frame.

        status = m_gameOverScreen->HandleProcessFrame (frameRateIncrement);

        // Is the game over screen complete?

        if ((status == ERR_SUCCESS) && m_gameOverScreen->IsComplete ())
        {
            // Yes. Destroy the game over screen.

            m_gameOverScreen.reset ();

            // Did the player register a high score?

            if (m_highScoreTable.IsHighScore (m_informationPanel->GetScore ()))
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


FolioStatus MainCanvasMsgHandler::HandleProcessEnterHighScoreScreenFrame (FolioHandle   wndHandle,
                                                                          UInt32        *frameRateIncrement)
{
    FolioStatus status = ERR_SUCCESS;

    if (!m_enterHighScoreScreen)
    {
        // Create the enter high score screen.

        m_enterHighScoreScreen.reset (new EnterHighScoreScreenPtr::element_type(m_informationPanel, 
                                                                                m_selectionScreen, 
                                                                                m_highScoreTable));

        status = m_enterHighScoreScreen->Create (*m_canvas, m_canvas->GetCanvasScreenRect ());
    } // Endif.

    if (status == ERR_SUCCESS)
    {
        // Let the enter high score screen process the frame.

        status = m_enterHighScoreScreen->HandleProcessFrame (frameRateIncrement);

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


FolioStatus MainCanvasMsgHandler::HandleProcessStartingGameStateFrame (FolioHandle  wndHandle,
                                                                       UInt32       *frameRateIncrement)
{
    // Let the current screen process the frame.

    bool    isStarting = true;  // Initialise!

    FolioStatus status = m_screensList [m_currentScreenIndex]->HandleProcessFrame (isStarting,
                                                                                   frameRateIncrement);

    // Still starting?

    if (!isStarting && (status == ERR_SUCCESS))
    {
        // No. We're playing.

        m_state = STATE_PLAYING_GAME;
        
        // The player is alive.

        m_playerSprite->SetAlive ();
    } // Endif.

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::HandleProcessPlayingGameStateFrame (FolioHandle   wndHandle,
                                                                      UInt32        *frameRateIncrement)
{
    // Check input.

    FolioStatus status = CheckPlayingGameStateInput ();

    if (status == ERR_SUCCESS)
    {
        // Let the current screen process the frame.

        bool    isStarting = false; // Initialise!

        status = m_screensList [m_currentScreenIndex]->HandleProcessFrame (isStarting, 
                                                                           frameRateIncrement);
        
        if (status == ERR_SUCCESS)
        {
            // Reset player fire key down.

            m_playerSprite->SetFireKeyDown (false);

            // Has the player exited a screen?

            if (m_playerSprite->IsExitedScreen ())
            {
                // Yes. Display the new screen.

               status = DisplayScreen ();
            } // Endif.

            // Has the player found an amulet piece?
            
            else
            if (m_playerSprite->FoundAmuletPiece ())
            {
                // Yes. Display the found amulet piece screen.

                m_state = STATE_FOUND_AMULET_PIECE_SCREEN;
            } // Endelseif.

            // Is the games over?

            else
            if (m_playerSprite->IsGameOver ())
            {
                // Yes. Display the game over screen.

                m_state = STATE_GAME_OVER_SCREEN;
            } // Endelseif.

           // Has the player completed the game?
            
            else
            if (m_playerSprite->IsGameCompleted ())
            {
                // Yes. Display the game completed screen.

                m_state = STATE_GAME_COMPLETED_SCREEN;
            } // Endelseif.

        } // Endif.
    
    } // Endif.

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::HandleProcessPausedGameStateFrame (FolioHandle    wndHandle,
                                                                     UInt32         *frameRateIncrement)
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

    if (m_playerSprite->IsReady ())
    {
        // Pause game key down?  

        if (m_selectionScreen->IsPauseGameKeyDown ())
        {
            // Yes. Pause game.

            m_state = STATE_PAUSED_GAME;
        } // Endelseif.

        else
        {
            // Player fire key down?  

            if (m_selectionScreen->IsPlayerFireKeyDown ())
            {
                // Yes. Set player fire key down.

                m_playerSprite->SetFireKeyDown (true);
            } // Endif.

            // Is a player's direction key down?

            Folio::Core::Game::APlayerSprite::Direction direction =  
                Folio::Core::Game::APlayerSprite::NO_DIRECTION; // Initialise!

            if (m_selectionScreen->IsPlayerDirectionKeyDown (direction))
            {
                // Yes. Update the player's direction.

                m_playerSprite->UpdateDirection (direction, true);
            } // Endif.

            // Is the player moving?

            else
            if (m_playerSprite->IsMoving ())
            {
                // Yes. Update the player's direction.

                m_playerSprite->UpdateDirection (direction, false);
            } // Endelseif.

        } // Endelse.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::StartPlayingGame ()
{
    // Start the information panel.

    FolioStatus status = m_informationPanel->Start ();

    if (status == ERR_SUCCESS)
    {
        // Start the player.

        status = m_playerSprite->Start ();

        if (status == ERR_SUCCESS)
        {
            // Build the screens.

            status = BuildScreens (*m_canvas,
                                    m_screenMap,
                                    m_informationPanel,
                                    m_screenBackgroundsMap,
                                    m_spriteGraphicsMap,
                                    m_screensList);

            if (status == ERR_SUCCESS)
            {        
                // Display the intial screen.

                status = DisplayScreen ();
                
                if (status == ERR_SUCCESS)
                {        
                    // We're starting.

                    m_state = STATE_STARTING_GAME;
                } // Endif.

            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::DisplayScreen ()
{
    // Get the current screen index.

    m_currentScreenIndex = m_screenMap->GetCurrentScreenIndex ();

    // Draw the current screen.

    return (m_screensList [m_currentScreenIndex]->Draw (m_playerSprite, m_orchidSprite));
} // Endproc.


FolioStatus MainCanvasMsgHandler::Initialise ()
{
    // Set random seed.

    Folio::Core::Util::Random::SetRandomSeed ();

    // Get the canvas device context.

    FolioHandle dcHandle = m_canvas->GetCanvasDcHandle ();
    
    // Get the canvas application instance.
    
    FolioHandle instanceHandle = m_canvas->GetAppletInstanceHandle ();

    // Create the background item graphics.

    FolioStatus status = CreateBackgroundItemGraphics (dcHandle,
                                                       instanceHandle,
                                                       m_backgroundItemGraphicsMap);

    if (status == ERR_SUCCESS)
    {
        // Create the sprite graphics.

        status = CreateSpriteGraphics (dcHandle,
                                       instanceHandle,
                                       m_spriteGraphicsMap);

        if (status == ERR_SUCCESS)
        {
            // Create the player sprite.

            m_playerSprite.reset (new PlayerSpritePtr::element_type);

            status = m_playerSprite->Create (dcHandle, m_spriteGraphicsMap);

            if (status == ERR_SUCCESS)
            {
                // Create the orchid sprite.

                m_orchidSprite.reset (new OrchidSpritePtr::element_type);

                status = m_orchidSprite->Create (dcHandle, m_spriteGraphicsMap);

                if (status == ERR_SUCCESS)
                {
                    // Create the screen map.

                    m_screenMap.reset (new ScreenMap(m_spriteGraphicsMap));

                    if (status == ERR_SUCCESS)
                    {
                        // Create the information panel.

                        m_informationPanel.reset (new InformationPanelPtr::element_type(*m_canvas, 
                                                                                        m_highScoreTable));

                        status = m_informationPanel->Create (m_screenMap->GetTotalNumScreens ());

                        if (status == ERR_SUCCESS)
                        {
                            // Create the selection screen.

                            m_selectionScreen.reset (new SelectionScreenPtr::element_type(m_informationPanel));

                            status = m_selectionScreen->Create (*m_canvas,  
                                                                m_canvas->GetCanvasScreenRect ());

                            if (status == ERR_SUCCESS)
                            {
                                // Build the screen backgrounds.

                                status = BuildScreenBackgrounds (m_backgroundItemGraphicsMap,
                                                                 m_screenBackgroundsMap);
                            } // Endif.

                        } // Endif.

                    } // Endif.
    
                } // Endif.

            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


void    MainCanvasMsgHandler::DisplayFrameRate () const
{
    static  float   s_previousTickCount = static_cast<float> (Folio::Core::Util::DateTime::GetCurrentTickCount ());  // Initialise!
    static  float   s_frameCount        = 0.0f;
           
    s_frameCount++;

    float   currentTickCount = static_cast<float> (Folio::Core::Util::DateTime::GetCurrentTickCount ());

    if ((currentTickCount - s_previousTickCount) > 1000)
    {
        float   frameRate = s_frameCount / ((currentTickCount - s_previousTickCount) / 1000.0f);

        FolioOStringStream  str;
        str << TXT("FrameRate: ") << frameRate
            << TXT(" FrameCount: ") << s_frameCount
            << TXT(" ScreenIndex: ") << m_currentScreenIndex
            << TXT(" ScreenNumber: ") << m_screenMap->GetCurrentScreenNumber ();
        Folio::Core::Util::Wnd::SetWndText (m_canvas->GetCanvasWndHandle (), str.str ().c_str ());
    
        str << std::endl;
        ::OutputDebugString (str.str ().c_str ());
    
        s_previousTickCount = currentTickCount;
        s_frameCount        = 0.0f;
    } // Endif.
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
