// "Home-made" includes.
#include    "StdAfx.h"
#include    <Trace.h>
#include    <Util.h>
#include    "MainCanvasMsgHandler.h"
#include    "ZxSpectrum.h"

namespace Folio
{

namespace Core
{

namespace Applet
{

ACanvasMsgHandler*  CreateCanvasMsgHandler ()
{
    // Create our initial canvas message handler.

    return (new Folio::Games::AticAtac::MainCanvasMsgHandler(Folio::Games::ZxSpectrum::MAX_SCREEN_X_PIXELS, 
                                                             Folio::Games::ZxSpectrum::MAX_SCREEN_Y_PIXELS,
                                                             Folio::Games::ZxSpectrum::DEFAULT_SCREEN_SCALE));
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
    // Set the canvas bag's window text.

    Folio::Core::Util::Wnd::SetWndText (wndHandle, TXT("ATICATAC by fractal studios"));

    // Initialise.

    return (Initialise ());
} // Endproc.


FolioStatus MainCanvasMsgHandler::HandleKeyboardMsg (FolioHandle    wndHandle,
                                                     UInt32         wParam,
                                                     UInt32         lParam,
                                                     bool           keyDown)
{
    FolioStatus status = ERR_SUCCESS;

    // Lock the canvas bag.

    m_canvasBag->Lock ();

    // Handling the keyboard message is dependent on our state.

    switch (m_state)
    {
    case STATE_LOADING:
        status = HandleLoadingStateKeyboardMsg (wndHandle, wParam, lParam, keyDown);
        break;

    case STATE_SELECTING:
        status = HandleSelectingStateKeyboardMsg (wndHandle, wParam, lParam, keyDown);
        break;

    case STATE_PLAYING:
        status = HandlePlayingStateKeyboardMsg (wndHandle, wParam, lParam, keyDown);
        break;

    case STATE_PAUSED:
        status = HandlePausedStateKeyboardMsg (wndHandle, wParam, lParam, keyDown);
        break;

    case STATE_GAME_OVER:
        status = HandleGameOverStateKeyboardMsg (wndHandle, wParam, lParam, keyDown);
        break;

    default:
        break;
    } // Endswitch.

    if (status == ERR_SUCCESS)
    {
        // Draw the canvas bag.

        m_canvasBag->DrawCanvas (m_canvasBag->IsRedrawRqd ());
    } // Endif.
    
    // Unlock the canvas bag.

    m_canvasBag->Unlock ();

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::HandleProcessFrame (FolioHandle   wndHandle, 
                                                      UInt32        &frameRateIncrement)
{
#ifdef _DEBUG
    DisplayFrameRate ();
#endif

    FolioStatus status = ERR_SUCCESS;

    frameRateIncrement = 0; // Initialise!

    // Lock the canvas bag.

    m_canvasBag->Lock ();

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

    case STATE_GAME_OVER:
        status = HandleProcessGameOverStateFrame (wndHandle, &(frameRateIncrement));
        break;

    default:
        break;
    } // Endswitch.

    if (status == ERR_SUCCESS)
    {
        // Draw the canvas bag.

        m_canvasBag->DrawCanvas (m_canvasBag->IsRedrawRqd ());
    } // Endif.
    
    // Unlock the canvas bag.

    m_canvasBag->Unlock ();

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::HandleLoadingStateKeyboardMsg (FolioHandle    wndHandle,
                                                                 UInt32         wParam,
                                                                 UInt32         lParam,
                                                                 bool           keyDown)
{
    // Let the loading screen process the keyboard message.

    FolioStatus status = m_loadingScreen.HandleProcessKeyboardMsg (wParam, lParam, keyDown);

    // Is the loading screen complete?

    if ((status == ERR_SUCCESS) && m_loadingScreen.IsComplete ())
    {
        // Yes. We're selecting.

        m_state = STATE_SELECTING;
    } // Endif.

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::HandleSelectingStateKeyboardMsg (FolioHandle  wndHandle,
                                                                   UInt32       wParam,
                                                                   UInt32       lParam,
                                                                   bool         keyDown)
{
    // Let the selection screen process the keyboard message.

    FolioStatus status = m_selectionScreen.HandleProcessKeyboardMsg (wParam, lParam, keyDown);

    // Is the selection screen complete?

    if ((status == ERR_SUCCESS) && m_selectionScreen.IsComplete ())
    {
        // Yes. Start playing.

        status = StartPlaying ();
    } // Endif.

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::HandlePlayingStateKeyboardMsg (FolioHandle    wndHandle,
                                                                 UInt32         wParam,
                                                                 UInt32         lParam,
                                                                 bool           keyDown)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the main player ready?

    if (m_mainPlayer->IsReady ())
    {
        // Yes. Fire weapon key?  

        if (m_selectionScreen.IsFireWeaponKey (wParam, keyDown))
        {
            // Yes. The main player can fire a weapon.

            m_mainPlayer->SetCanFireWeapon (true);

            // Process the playing state frame.

            status = HandleProcessPlayingStateFrame (wndHandle);

            // The main player can no longer fire a weapon.

            m_mainPlayer->SetCanFireWeapon (false);
        } // Endif.

        // Collect items key?  

        else
        if (m_selectionScreen.IsCollectItemsKey (wParam, keyDown))
        {
            // Yes. The main player can collect items.

            m_mainPlayer->SetCanCollectItems (true);

            // Process the playing state frame.

            status = HandleProcessPlayingStateFrame (wndHandle);

            // The main player can no longer collect items.

            m_mainPlayer->SetCanCollectItems (false);
        } // Endelseif.

        // Pause game key?  

        else
        if (m_selectionScreen.IsPauseGameKey (wParam, keyDown))
        {
            // Yes. Pause game.

            m_state = STATE_PAUSED;
        } // Endelseif.

        else
        {
            // No. Get the main player's direction.

            Folio::Core::Game::APlayerSprite::Direction     direction = 
                m_selectionScreen.GetMainPlayerDirection (wParam);

            if (direction != Folio::Core::Game::APlayerSprite::NO_DIRECTION)
            {
                if (keyDown)
                {
                    // Update the main player's direction.

                    m_mainPlayer->UpdateDirection (direction, keyDown);
                } // Endif.

                else
                {
                    // Get the main player's direction.

                    Folio::Core::Game::APlayerSprite::Direction mainPlayerDirection = m_mainPlayer->GetDirection ();

                    switch (mainPlayerDirection)
                    {
                    case PlayerSprite::N:
                    case PlayerSprite::S:
                    case PlayerSprite::E:
                    case PlayerSprite::W:
                        // Update the main player's direction.

                        m_mainPlayer->UpdateDirection (direction, keyDown);
                        break;

                    case PlayerSprite::NE:
                    case PlayerSprite::NW:
                    case PlayerSprite::SE:
                    case PlayerSprite::SW:
                        // Update the main player's direction.

                        m_mainPlayer->UpdateDirection (direction, 
                                                       keyDown, 
                                                       m_selectionScreen.IsOtherKeyDown (mainPlayerDirection, direction, keyDown));
                        break;

                    default:
                        break;
                    } // Endswitch.
                
                } // Endelse.

                // Process the playing state frame.

                status = HandleProcessPlayingStateFrame (wndHandle);
            } // Endif.

        } // Endelse.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::HandlePausedStateKeyboardMsg (FolioHandle wndHandle,
                                                                UInt32      wParam,
                                                                UInt32      lParam,
                                                                bool        keyDown)
{
    FolioStatus status = ERR_SUCCESS;

    // Pause game key?  

    if (m_selectionScreen.IsPauseGameKey (wParam, keyDown))
    {
        // Yes. We're back playing.

        m_state = STATE_PLAYING;
    } // Endif.

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::HandleGameOverStateKeyboardMsg (FolioHandle   wndHandle,
                                                                  UInt32        wParam,
                                                                  UInt32        lParam,
                                                                  bool          keyDown)
{
    // Let the game over screen process the keyboard message.

    FolioStatus status = m_gameOverScreen->HandleProcessKeyboardMsg (wParam, lParam, keyDown);

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


FolioStatus MainCanvasMsgHandler::HandleProcessLoadingStateFrame (FolioHandle   wndHandle,
                                                                  UInt32        *frameRateIncrement)
{
    // Let the loading screen process the frame.

    return (m_loadingScreen.HandleProcessFrame (frameRateIncrement));
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

        m_mainPlayer->SetAlive ();
    } // Endif.

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::HandleProcessPlayingStateFrame (FolioHandle   wndHandle,
                                                                  UInt32        *frameRateIncrement)
{
    // Let the current screen process the frame.

    bool    isStarting = false; // Initialise!

    FolioStatus status = m_currentScreen->HandleProcessFrame (isStarting, frameRateIncrement);
        
    if (status == ERR_SUCCESS)
    {
        // Has the main player completed the game?

        if (m_mainPlayer->CompletedGame ())
        {
            // Yes. Display the game over screen.

            status = DisplayGameOverScreen (true);
        } // Endif.

        // Has the main player exited a screen?
        
        else
        if (m_mainPlayer->IsExitedScreen ())
        {
            // Yes. Is the main player falling?

            if (m_mainPlayer->IsFalling ())
            {
                // Yes. We're falling.

                m_state = STATE_MAIN_PLAYER_FALLING;
            } // Endif.

            else
            {
                // No. Display the new screen.

                status = DisplayScreen (m_currentScreen->MoveToNewScreen (m_backgroundItemsList));
            } // Endelse.

        } // Endelseif.

        // Is the main player dead?
        
        else
        if (m_mainPlayer->IsDead ())
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

                        status = m_mainPlayer->Restart ();

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

    return (status);
} // Endproc.


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

            m_mainPlayer->SetState (PlayerSprite::STATE_MOVING);

            // Display the new screen.

            status = DisplayScreen (m_currentScreen->MoveToNewScreen (m_backgroundItemsList));
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


FolioStatus MainCanvasMsgHandler::HandleProcessGameOverStateFrame (FolioHandle  wndHandle,
                                                                   UInt32       *frameRateIncrement)
{
    // Let the game over screen process the frame.

    return (m_gameOverScreen->HandleProcessFrame (frameRateIncrement));
} // Endproc.


FolioStatus MainCanvasMsgHandler::StartPlaying ()
{
    // Yes. Get our main player (hero!).

    m_mainPlayer = m_playerSpritesMap [static_cast<PLAYER_SPRITE_ID> (m_selectionScreen.GetMainPlayer ())];

    // Restart the main player.

    FolioStatus status = m_mainPlayer->Restart ();

    if (status == ERR_SUCCESS)
    {
        // Create the information panel.

        status = m_informationPanel.Create (*m_canvasBag,
                                            Screen::GetTotalNumRooms (),
                                            m_selectionScreen.GetMainPlayerResourceId ());

        if (status == ERR_SUCCESS)
        {
            // Scatter the static sprites.

            status = ScatterStaticSprites (m_staticSpritesList);

            if (status == ERR_SUCCESS)
            {
                // Build the screens.

                status = BuildScreens (*m_canvasBag,
                                       m_roomGraphicsMap, 
                                       m_backgroundItemGraphicsMap,
                                       m_spriteGraphicsMap,
                                       m_backgroundItemsList,
                                       m_staticSpritesList,
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
    // Set the background colour of the canvas bag.

    FolioStatus status = SetCanvasBagBackground ();

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

    // Get the current screen's drawing elements.
    
    Folio::Core::Game::DrawingElementsList  drawingElementsList;

    FolioStatus status = m_currentScreen->QueryDrawingElements (m_mainPlayer, drawingElementsList);

    if (status == ERR_SUCCESS)
    {
        // Clear the canvas bag.

        m_canvasBag->ClearCanvas ();

        // Add the current screen's drawing elements to the canvas bag.

        status = m_canvasBag->AddDrawingElements (drawingElementsList, true); // Draw into the canvas bag.

        if (status == ERR_SUCCESS)
        {
            // Get the canvas bag graphics.

            Gdiplus::Graphics   *graphics = m_canvasBag->GetCanvasGraphics ();
    
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

    FolioStatus status = m_gameOverScreen->Create (*m_canvasBag,
                                                   Gdiplus::Rect(0, 0, MAX_ROOM_WIDTH, MAX_ROOM_HEIGHT),
                                                   10 * 1000);

    if (status == ERR_SUCCESS)
    {
        // Our game is over.

        m_state = STATE_GAME_OVER;
    } // Endif.

    return (status);
} // Endproc.


FolioStatus MainCanvasMsgHandler::SetCanvasBagBackground (const Gdiplus::Region *clippingRegion)
{
    // Fill the canvas background.

    return (m_canvasBag->FillCanvasBackground (Gdiplus::SolidBrush(Folio::Core::Graphic::DEFAULT_BACKGROUND_COLOUR), false, clippingRegion));
} // Endproc.


FolioStatus MainCanvasMsgHandler::Initialise ()
{
    // Set random seed.

    Folio::Core::Util::Random::SetRandomSeed ();

    // Get the canvas bag device context.

    FolioHandle dcHandle = m_canvasBag->GetCanvasDcHandle ();
    
    // Get the canvas bag application instance.
    
    FolioHandle instanceHandle = m_canvasBag->GetAppletInstanceHandle ();

    // Create loading screen.

    FolioStatus status = m_loadingScreen.Create (*m_canvasBag, m_canvasBag->GetCanvasScreenRect (), 2 * 1000);

    if (status == ERR_SUCCESS)
    {
        // Create selection screen.

        status = m_selectionScreen.Create (*m_canvasBag, m_canvasBag->GetCanvasScreenRect ());

        if (status == ERR_SUCCESS)
        {
            // Create falling simulation screen.

            status = m_fallingSimulationScreen.Create (*m_canvasBag,
                                                       Gdiplus::Rect(0, 0, MAX_ROOM_WIDTH, MAX_ROOM_HEIGHT));

            if (status == ERR_SUCCESS)
            {
                // Build the room graphics.

                status = BuildRoomGraphics (dcHandle,
                                            instanceHandle,
                                            m_roomGraphicsMap);

                if (status == ERR_SUCCESS)
                {
                    // Build the background item graphics.

                    status = BuildBackgroundItemGraphics (dcHandle,
                                                          instanceHandle,
                                                          m_backgroundItemGraphicsMap);

                    if (status == ERR_SUCCESS)
                    {
                        // Build the background items.

                        status = BuildBackgroundItems (m_backgroundItemGraphicsMap,
                                                       m_backgroundItemsList);

                        if (status == ERR_SUCCESS)
                        {
                            // Build the sprite graphics.

                            status = BuildSpriteGraphics (dcHandle,
                                                          instanceHandle,
                                                          m_spriteGraphicsMap);

                            if (status == ERR_SUCCESS)
                            {
                                // Build the static sprites.

                                status = BuildStaticSprites (dcHandle,
                                                             m_spriteGraphicsMap,
                                                             m_staticSpritesList);

                                if (status == ERR_SUCCESS)
                                {
                                    // Build the player sprites.

                                    status = BuildPlayerSprites (dcHandle,
                                                                 m_spriteGraphicsMap,
                                                                 m_playerSpritesMap);
                                } // Endif.

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
            << TXT(" ScreenNumber: ") << m_currentScreenNumber; 
        Folio::Core::Util::Wnd::SetWndText (m_canvasBag->GetCanvasWndHandle (), str.str ().c_str ());
    
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
