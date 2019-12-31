// "Home-made" includes.
#include    "StdAfx.h"
#include    <Trace.h>
#include    <Util.h>
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

    return (new Folio::Games::AticAtac::MainCanvasMsgHandler(Folio::Core::Game::ZxSpectrum::MAX_SCREEN_X_PIXELS, 
                                                             Folio::Core::Game::ZxSpectrum::MAX_SCREEN_Y_PIXELS,
                                                             Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE));
} // Endproc.

} // Endnamespace.

} // Endnamespace.

namespace Games
{

namespace AticAtac
{
      
MainCanvasMsgHandler::MainCanvasMsgHandler (Int32   maxScreenXPixels,           
                                            Int32   maxScreenYPixels,
                                            UInt32  screenScale)
:   ACanvasMsgHandler(maxScreenXPixels, maxScreenYPixels, screenScale),
    m_state(STATE_LOADING),
    m_currentScreenNumber(INITIAL_SCREEN_NUMBER),
    m_currentScreen(0)
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

    Folio::Core::Util::Wnd::SetWndText (wndHandle, TXT("AticAtac by fractal studios"));

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


FolioStatus MainCanvasMsgHandler::HandleProcessFrame (FolioHandle   wndHandle, 
                                                      UInt32        &frameRateIncrement)
{
#ifdef _DEBUG
    //DisplayFrameRate ();
#endif

    FolioStatus status = ERR_SUCCESS;

    frameRateIncrement = 0; // Initialise!

    // Processing the frame is dependent on our state.

    switch (m_state)
    {
    case STATE_LOADING:
        status = HandleProcessLoadingStateFrame (wndHandle, &(frameRateIncrement));
        break;

    case STATE_SELECTING:
        status = HandleProcessSelectingStateFrame (wndHandle, &(frameRateIncrement));
        break;

    case STATE_STARTING:
        status = HandleProcessStartingStateFrame (wndHandle, &(frameRateIncrement));
        break;

    case STATE_PLAYING:
        status = HandleProcessPlayingStateFrame (wndHandle, &(frameRateIncrement));
        break;

    case STATE_MAIN_PLAYER_FALLING:
        status = HandleProcessMainPlayerFallingStateFrame (wndHandle, &(frameRateIncrement));
        break;

    case STATE_PAUSED:
        status = HandleProcessPausedStateFrame (wndHandle, &(frameRateIncrement));
        break;

    case STATE_GAME_OVER:
        status = HandleProcessGameOverStateFrame (wndHandle, &(frameRateIncrement));
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


FolioStatus MainCanvasMsgHandler::HandleProcessLoadingStateFrame (FolioHandle   wndHandle,
                                                                  UInt32        *frameRateIncrement)
{
    // Let the loading screen process the frame.

    FolioStatus status = m_loadingScreen.HandleProcessFrame (frameRateIncrement);

    // Is the loading screen complete?

    if ((status == ERR_SUCCESS) && m_loadingScreen.IsComplete ())
    {
        // Yes. We're selecting.

        m_state = STATE_SELECTING;
    } // Endif.

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::HandleProcessSelectingStateFrame (FolioHandle wndHandle,
                                                                    UInt32      *frameRateIncrement)
{
    // Let the selection screen process the frame.

    FolioStatus status = m_selectionScreen.HandleProcessFrame (frameRateIncrement);

    // Is the selection screen complete?

    if ((status == ERR_SUCCESS) && m_selectionScreen.IsComplete ())
    {
        // Yes. Start playing.

        status = StartPlaying ();
    } // Endif.

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::HandleProcessStartingStateFrame (FolioHandle  wndHandle,
                                                                   UInt32       *frameRateIncrement)
{
    // Let the current screen process the frame.

    bool    isStarting = true;  // Initialise!

    FolioStatus status = m_currentScreen->HandleProcessFrame (isStarting, frameRateIncrement);

    // Still starting?

    if (!isStarting && (status == ERR_SUCCESS))
    {
        // No. We're playing.

        m_state = STATE_PLAYING;
        
        // The main player is alive.

        g_mainPlayer->SetAlive ();
    } // Endif.

    return (status);
} // Endproc.

#ifdef _AUTO_TEST_
FolioStatus MainCanvasMsgHandler::HandleProcessPlayingStateFrame (FolioHandle   wndHandle,
                                                                  UInt32        *frameRateIncrement)
{
    static  UInt32  s_screenTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount ();

    // Let the current screen process the frame.

    bool    isStarting = false; // Initialise!

    FolioStatus status = m_currentScreen->HandleProcessFrame (isStarting, frameRateIncrement);
        
    if (status == ERR_SUCCESS)
    {
        //if (m_selectionScreen.IsMainPlayerFireWeaponKeyDown ())
        if (Folio::Core::Util::DateTime::GetCurrentTickCount () > (s_screenTickCount + AUTO_TEST_SCREEN_TIME))
        {
            m_currentScreen->ExitScreen ();

            s_screenTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount ();

            m_currentScreenNumber++;

            if (m_currentScreenNumber > MAX_SCREEN_NUMBER)
            {
                //Folio::Core::Util::g_handleMonitor.Dump ();
                //g_resourceGraphicsCache.Dump (false);
                g_resourceGraphicsCache.DumpNumUsedBitmaps (false);

                m_currentScreenNumber = INITIAL_SCREEN_NUMBER;
            } // Endif.
            
            status = DisplayScreen (m_currentScreenNumber);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.
#else
FolioStatus MainCanvasMsgHandler::HandleProcessPlayingStateFrame (FolioHandle   wndHandle,
                                                                  UInt32        *frameRateIncrement)
{
    // Check input.

    FolioStatus status = CheckPlayingStateInput ();

    if (status == ERR_SUCCESS)
    {
        // Let the current screen process the frame.

        bool    isStarting = false; // Initialise!

        status = m_currentScreen->HandleProcessFrame (isStarting, frameRateIncrement);
        
        if (status == ERR_SUCCESS)
        {
            // Has the main player completed the game?

            if (g_mainPlayer->IsGameCompleted ())
            {
                // Yes. Display the game over screen.

                status = DisplayGameOverScreen (true);
            } // Endif.

            // Has the main player exited a screen?
        
            else
            if (g_mainPlayer->IsExitedScreen ())
            {
                // Yes. Is the main player falling?

                if (g_mainPlayer->IsFalling ())
                {
                    // Yes. We're falling.

                    m_state = STATE_MAIN_PLAYER_FALLING;
                } // Endif.

                else
                {
                    // No. Query the new screen.
                    
                    UInt32  newScreenNumber = SCREEN_NUMBER_UNDEFINED;  // Initialise!

                    status = m_currentScreen->QueryNewScreen (newScreenNumber);

                    if (status == ERR_SUCCESS)
                    {
                        // Display the new screen.

                        status = DisplayScreen (newScreenNumber);
                    } // Endif.

                } // Endelse.

            } // Endelseif.

            // Is the main player dead?
        
            else
            if (g_mainPlayer->IsDead ())
            {
                // Yes. Add a gravestone to the current screen.

                status = m_currentScreen->AddGravestone ();

                if (status == ERR_SUCCESS)
                {
                    // Decrement a main player life in the information panel.

                    bool    isGameOver = false;     // Initialise!

                    status = m_informationPanel.DecrementMainPlayerLife (isGameOver);

                    if (status == ERR_SUCCESS)
                    {
                        // Is the games over?

                        if (isGameOver)
                        {
                            // Yes. Display the game over screen.

                            status = DisplayGameOverScreen (false);
                        } // Endif.

                        else
                        {
                            // No. Restart the main player.

                            status = g_mainPlayer->Restart ();

                            if (status == ERR_SUCCESS)
                            {
                                // We're starting.

                                m_state = STATE_STARTING;
                            } // Endif.

                        } // Endelse.

                    } // Endif.
            
                } // Endif.

            } // Endelseif.

        } // Endif.
    
        // The main player can no longer fire a weapon.

        g_mainPlayer->SetCanFireWeapon (false);

        // The main player can no longer collect items.

        g_mainPlayer->SetCanCollectItems (false);
    } // Endif.

    return (status);
} // Endproc.
#endif

FolioStatus MainCanvasMsgHandler::HandleProcessMainPlayerFallingStateFrame (FolioHandle wndHandle,
                                                                            UInt32      *frameRateIncrement)
{
    // Let the falling simulation screen process the frame.

    FolioStatus status = m_fallingSimulationScreen.HandleProcessFrame (frameRateIncrement);

    if (status == ERR_SUCCESS)
    {
        // Is the falling simulation screen complete?

        if (m_fallingSimulationScreen.IsComplete ())
        {    
            // Yes. We're back playing.

            m_state = STATE_PLAYING;

            // The main player is moving.

            g_mainPlayer->SetState (PlayerSprite::STATE_MOVING);

            // Query the new screen.

            UInt32  newScreenNumber = SCREEN_NUMBER_UNDEFINED;  // Initialise!

            status = m_currentScreen->QueryNewScreen (newScreenNumber);

            if (status == ERR_SUCCESS)
            {
                // Display the new screen.

                status = DisplayScreen (newScreenNumber);
            } // Endif.

        } // Endif.

        else
        {
            // Let the information panel process the frame.

            bool    isStarting          = false;    // Initialise!
            bool    mainPlayerIsDead    = false;

            status = m_informationPanel.HandleProcessFrame (isStarting, mainPlayerIsDead);
        } // Endelse.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::HandleProcessPausedStateFrame (FolioHandle    wndHandle,
                                                                 UInt32         *frameRateIncrement)
{
    FolioStatus status = ERR_SUCCESS;

    // Pause game key down?  

    if (m_selectionScreen.IsPauseGameKeyDown ())
    {
        // Yes. We're back playing.

        m_state = STATE_PLAYING;
    } // Endif.

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::HandleProcessGameOverStateFrame (FolioHandle  wndHandle,
                                                                   UInt32       *frameRateIncrement)
{
    // Let the game over screen process the frame.

    FolioStatus status = m_gameOverScreen->HandleProcessFrame (frameRateIncrement);

    // Is the game over screen complete?

    if ((status == ERR_SUCCESS) && m_gameOverScreen->IsComplete ())
    {
        // Yes. Remove the game over screen. 
        
        m_gameOverScreen.reset ();

        // We're selecting.

        m_state = STATE_SELECTING;
    } // Endif.

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::CheckPlayingStateInput ()
{
    FolioStatus status = ERR_SUCCESS;

    // Is the main player ready?

    if (g_mainPlayer->IsReady ())
    {
        // Yes. Main player fire weapon key down?  

        if (m_selectionScreen.IsMainPlayerFireWeaponKeyDown ())
        {
            // Yes. The main player can fire a weapon.

            g_mainPlayer->SetCanFireWeapon (true);
        } // Endif.

        // Main player collect items key down?  

        else
        if (m_selectionScreen.IsMainPlayerCollectItemsKeyDown ())
        {
            // Yes. The main player can collect items.

            g_mainPlayer->SetCanCollectItems (true);
        } // Endelseif.

        // Pause game key down?  

        else
        if (m_selectionScreen.IsPauseGameKeyDown ())
        {
            // Yes. Pause game.

            m_state = STATE_PAUSED;
        } // Endelseif.

        else
        {
            // Is a main player's direction key down?

            Folio::Core::Game::Direction direction =  
                Folio::Core::Game::NO_DIRECTION;    // Initialise!

            if (m_selectionScreen.IsMainPlayerDirectionKeyDown (direction))
            {
                // Yes. Update the main player's direction.

                g_mainPlayer->UpdateDirection (direction, true);
            } // Endif.

            // Is the main player moving?

            else
            if (g_mainPlayer->IsMoving ())
            {
                // Yes. Update the main player's direction.

                g_mainPlayer->UpdateDirection (direction, false);
            } // Endelseif.

        } // Endelse.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::StartPlaying ()
{
    // Get the canvas device context.

    FolioHandle dcHandle = m_canvas->GetCanvasDcHandle ();
    
    // Initialise globals.

    FolioStatus status = InitialiseGlobals (dcHandle);

    if (status == ERR_SUCCESS)
    {
        // Get our main player (hero!).

        g_mainPlayer = g_playerSpritesMap [static_cast<PLAYER_SPRITE_ID> (m_selectionScreen.GetMainPlayer ())];

        // All the boss sprites are alive.

        SetBossSpritesAlive (g_bossSpritesMap);

        // Set our main player's weapon sprite.

        g_weaponSpriteDrawingElement.SetSprite (g_weaponSpritesMap [WeaponSprite::GetMainPlayerWeaponSpriteId ()]);

        // Restart the main player.

        status = g_mainPlayer->Restart ();

        if (status == ERR_SUCCESS)
        {
            // Create the information panel.

            status = m_informationPanel.Create (*m_canvas,
                                                Screen::GetTotalNumRooms (),
                                                m_selectionScreen.GetMainPlayerResourceId ());

            if (status == ERR_SUCCESS)
            {
                // Scatter the static sprites.

                ScatterStaticSprites (g_staticSpritesList);

                // Build the screens.

                status = BuildScreens (*m_canvas,
                                       g_backgroundItemsList,
                                       g_staticSpritesList,
                                       m_informationPanel,
                                       m_screensList);

                if (status == ERR_SUCCESS)
                {        
                    m_currentScreenNumber = INITIAL_SCREEN_NUMBER;  // The initial screen. 

                    // Display the intial screen.
                    
                    status = DisplayInitialScreen (m_currentScreenNumber);
                
                    if (status == ERR_SUCCESS)
                    {        
                        // We're starting.

                        m_state = STATE_STARTING;
                    } // Endif.

                } // Endif.

            } // Endif.

        } // Endif.
    
    } // Endif.

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::DisplayInitialScreen (UInt32 screenNumber)
{
    // Set the background colour of the canvas.

    FolioStatus status = SetCanvasBackground ();

    if (status == ERR_SUCCESS)
    {
        // Display the initial screen.

        status = DisplayScreen (screenNumber);
    } // Endif.

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::DisplayScreen (UInt32 screenNumber)
{
    // Note the current screen number.

    m_currentScreenNumber = screenNumber;

    // Note the current screen.

    m_currentScreen = &(m_screensList [m_currentScreenNumber]);

    // Does this screen support a boss sprite?

    BOSS_SPRITE_ID  bossSpriteId = BossSprite::GetScreenBossSpriteId (m_currentScreenNumber, Screen::GetTotalNumRooms ());
    
    if (bossSpriteId != BOSS_SPRITE_UNDEFINED)
    {
        // Yes. Set the screen's boss sprite.

        g_bossSpriteDrawingElement.SetSprite (g_bossSpritesMap [bossSpriteId]);
    } // Endif.

    else
    {
        // Destroy the boss sprite.

        g_bossSpriteDrawingElement.Destroy ();
    } // Endelse.

    // Get the current screen's drawing elements.
    
    Folio::Core::Game::DrawingElementsList  drawingElementsList;

    FolioStatus status = m_currentScreen->QueryDrawingElements (drawingElementsList);

    if (status == ERR_SUCCESS)
    {
        // Draw the current screen's drawing elements in the canvas.

        status = m_canvas->DrawDrawingElements (drawingElementsList, true); // Draw into the canvas.

        if (status == ERR_SUCCESS)
        {
            // Get the canvas graphics.

            Gdiplus::Graphics   *graphics = m_canvas->GetCanvasGraphics ();
    
            // Store the current screen's sprite backgrounds.

            status = m_currentScreen->StoreSpriteBackgrounds (*graphics);

            if (status == ERR_SUCCESS)
            {
                // Draw the current screen's sprites.

                status = m_currentScreen->DrawSprites (*graphics);
            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::DisplayGameOverScreen (bool mainPlayerCompletedGame)
{
    // Create game over screen.

    m_gameOverScreen.reset (new GameOverScreen(mainPlayerCompletedGame,
                                               m_informationPanel.GetTimeInSeconds (),
                                               m_informationPanel.GetScore (),
                                               m_informationPanel.GetPercentageCompleted ()));

    FolioStatus status = m_gameOverScreen->Create (*m_canvas,
                                                   Gdiplus::Rect(0, 0, MAX_ROOM_WIDTH, MAX_ROOM_HEIGHT),
                                                   10 * 1000);

    if (status == ERR_SUCCESS)
    {
        // Our game is over.

        m_state = STATE_GAME_OVER;
    } // Endif.

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::SetCanvasBackground (const Gdiplus::Region *clippingRegion)
{
    // Fill the canvas background.

    return (m_canvas->FillCanvasBackground (Gdiplus::SolidBrush(Folio::Core::Graphic::DEFAULT_BACKGROUND_COLOUR), 
                                            false, 
                                            clippingRegion));
} // Endproc.


FolioStatus MainCanvasMsgHandler::Initialise ()
{
    // Set random seed.

    Folio::Core::Util::Random::SetRandomSeed ();

    // Get the canvas device context.

    FolioHandle dcHandle = m_canvas->GetCanvasDcHandle ();
    
    // Get the canvas application instance.
    
    FolioHandle instanceHandle = m_canvas->GetAppletInstanceHandle ();

    // Create loading screen.

    FolioStatus status = m_loadingScreen.Create (*m_canvas, m_canvas->GetCanvasScreenRect (), 2 * 1000);

    if (status == ERR_SUCCESS)
    {
        // Create selection screen.

        status = m_selectionScreen.Create (*m_canvas, m_canvas->GetCanvasScreenRect ());

        if (status == ERR_SUCCESS)
        {
            // Create falling simulation screen.

            status = m_fallingSimulationScreen.Create (*m_canvas,
                                                        Gdiplus::Rect(0, 0, MAX_ROOM_WIDTH, MAX_ROOM_HEIGHT));

            if (status == ERR_SUCCESS)
            {
                // Create the room graphics.

                status = CreateRoomGraphics (instanceHandle);

                if (status == ERR_SUCCESS)
                {
                    // Create the background item graphics.

                    status = CreateBackgroundItemGraphics (instanceHandle);

                    if (status == ERR_SUCCESS)
                    {
                        // Create the sprite graphics.

                        status = CreateSpriteGraphics (instanceHandle);
                    } // Endif.
    
                } // Endif.

            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::Terminate ()
{
    // Terminate globals.

    return (TerminateGlobals ());
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
            << TXT(" ScreenNumber: ") << m_currentScreenNumber; 
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
