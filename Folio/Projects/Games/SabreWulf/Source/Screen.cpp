// "Home-made" includes.
#include    "StdAfx.h"
#include    "Globals.h"
#include    "NastySprite.h"
#include    "OrchidSprite.h"
#include    "PlayerSprite.h"
#include    "Screen.h"

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

Screen::Screen (Folio::Core::Applet::Canvas &canvas,
                const BackgroundItemsList   &backgroundItemsList)
:   m_canvas(canvas),
    m_screenScreenRect(SCREEN_X_ORIGIN, SCREEN_Y_ORIGIN, SCREEN_WIDTH, SCREEN_HEIGHT),
    m_screenInitialised(false),
    m_exitScreenTickCount(0),       
    m_addNastySpriteTickCount(0),
    m_backgroundItemsList(backgroundItemsList)
{
} // Endproc.


Screen::~Screen ()
{
    // Release the screen's graphics from the resource graphics cache.

    ReleaseResourceGraphics ();
} // Endproc.


FolioStatus Screen::Draw ()
{
    // Get the canvas device context.

    FolioHandle dcHandle = m_canvas.GetCanvasDcHandle ();

    // Query the screen's drawing elements.

    Folio::Core::Game::DrawingElementsList  screenDrawingElementsList;

    FolioStatus status = QueryScreenDrawingElements (dcHandle, screenDrawingElementsList);

    // Is the screen initialised?

    if (IsScreenInitialised ())
    {
        // Yes. Update the screen.

        status = UpdateScreen (dcHandle, screenDrawingElementsList);
    } // Endif.

    else
    {
        // No. Initialise the screen.

        status = InitialiseScreen (dcHandle, screenDrawingElementsList);
    } // Endelse.

    if (status == ERR_SUCCESS)
    {
        m_exitScreenTickCount       = 0;    // Reset the screen's exit screen tick count.
        m_addNastySpriteTickCount   = 0;    // Reset the screen's add nasty sprite tick count.

        // Draw the information panel.

        status = g_informationPanel->Draw ();

        if (status == ERR_SUCCESS)
        {
            // Draw the screen.

            status = DrawScreen (screenDrawingElementsList);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::HandleProcessFrame (bool    &isStarting,
                                        UInt32  *frameRateIncrement)
{
    // Get the canvas graphics.

    Gdiplus::Graphics   *graphics = m_canvas.GetCanvasGraphics ();

    // Restore the screen's sprite backgrounds.

    FolioStatus status = RestoreScreenSpriteBackgrounds (*graphics);

    if (status == ERR_SUCCESS)
    {
        // Check the screen's sprites.

        status = CheckScreenSprites (*graphics);

        if (status == ERR_SUCCESS)
        {
            // Let the information panel process the frame.

            status = g_informationPanel->HandleProcessFrame (isStarting);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


bool    Screen::IsScreenInitialised () const
{
    return (m_screenInitialised);
} // Endproc.


FolioStatus Screen::QueryScreenDrawingElements (FolioHandle                             dcHandle,
                                                Folio::Core::Game::DrawingElementsList  &screenDrawingElementsList)
{
    FolioStatus status = ERR_SUCCESS;

    screenDrawingElementsList.clear ();   // Initialise!

    // Add the screen's background items to the screen's drawing elements.

    for (BackgroundItemsList::iterator itr = m_backgroundItemsList.begin ();
         (status == ERR_SUCCESS) && (itr != m_backgroundItemsList.end ());
         ++itr)
    {
        // Get the background item's drawing elements.

        Folio::Core::Game::DrawingElementsList  backgroundItemDrawingElementsList;

        status = itr->QueryDrawingElements (dcHandle, backgroundItemDrawingElementsList);

        if (status == ERR_SUCCESS)
        {
            // Add the background item's drawing elements to the screen's 
            // drawing elements list.

            screenDrawingElementsList.insert (screenDrawingElementsList.end (),
                                              backgroundItemDrawingElementsList.begin (),
                                              backgroundItemDrawingElementsList.end ());
        } // Endif.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus Screen::InitialiseScreen (FolioHandle                                   dcHandle,
                                      const Folio::Core::Game::DrawingElementsList  &screenDrawingElementsList)
{                      
    // Create the screen's collision grid.

    FolioStatus status = m_collisionGrid.Create (m_screenScreenRect, 
                                                 screenDrawingElementsList);

    if (status == ERR_SUCCESS)
    {
        // Initialise the screen's object sprites.

        status = InitialiseScreenObjectSprites (dcHandle, 
                                                m_objectSpriteDrawingElementsList, 
                                                m_collisionGrid);

        if (status == ERR_SUCCESS)
        {
            // Initialise the screen's orchid sprite.

            status = InitialiseScreenOrchidSprite (m_collisionGrid);

            if (status == ERR_SUCCESS)
            {
                // Increment the player's number of screens visited.

                g_informationPanel->IncrementPlayerNumScreensVisited ();

                // The screen is initialised.

                m_screenInitialised = true;
            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::UpdateScreen (FolioHandle                                   dcHandle,
                                  const Folio::Core::Game::DrawingElementsList  &screenDrawingElementsList)
{
    // Update the screen's orchid sprite.

    FolioStatus status = UpdateScreenOrchidSprite ();

    if (status == ERR_SUCCESS)
    {
        // Update the screen's nasty sprites.
        
        status = UpdateScreenNastySprites (m_exitScreenTickCount, m_collisionGrid);
   } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::DrawScreen (const Folio::Core::Game::DrawingElementsList &screenDrawingElementsList)
{
    // Clear the canvas rectangle occupied by the screen.

    FolioStatus status = m_canvas.ClearCanvasRectangle (m_screenScreenRect);

    if (status == ERR_SUCCESS)
    {
        // Draw the screen's drawing elements in the canvas.

        status = m_canvas.DrawDrawingElements (screenDrawingElementsList);

        if (status == ERR_SUCCESS)
        {
            // Set the player's position at the screen's entrance.

            status = g_playerSprite->SetScreenEntranceTopLeft (m_screenScreenRect,
                                                               m_collisionGrid);  
                
            if (status == ERR_SUCCESS)
            {
                // Get the canvas graphics.

                Gdiplus::Graphics   *graphics = m_canvas.GetCanvasGraphics ();
    
                // Store the screen's sprite backgrounds.

                status = StoreScreenSpriteBackgrounds (*graphics);

                if (status == ERR_SUCCESS)
                {
                    // Draw the screen's sprites.

                    status = DrawScreenSprites (*graphics);
                } // Endif.

            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::MoveToNewScreen ()
{
    // Exit the current screen.

    FolioStatus status = ExitScreen ();

    if (status == ERR_SUCCESS)
    {
        // Get the screen exit that the player has exited from.

        CollisionGrid::ScreenExit   screenExit(g_playerSprite->GetScreenExit ());

        // Move to the new screen.

        g_screenMap.MoveToNewScreen (screenExit.m_orientation);
    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::ExitScreen ()
{
    // Release the screen's graphics from the resource graphics cache.

    FolioStatus status = ReleaseResourceGraphics ();

    if (status == ERR_SUCCESS)
    {
        // Note the screen's exit screen tick count.

        m_exitScreenTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount ();
    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::StoreScreenSpriteBackgrounds (Gdiplus::Graphics &graphics)
{
    // Store the screen's object sprites' underlying backgrounds.
    
    FolioStatus status = StoreScreenObjectSpriteBackgrounds (graphics, 
                                                             m_objectSpriteDrawingElementsList);

    if (status == ERR_SUCCESS)
    {
        // Store the screen's orchid sprite's underlying background.
    
        status = StoreScreenOrchidSpriteBackground (graphics);

        if (status == ERR_SUCCESS)
        {
            // Store the screen's nasty sprites' underlying backgrounds.
    
            status = StoreNastySpriteBackgrounds (graphics);

            if (status == ERR_SUCCESS)
            {
                // Store the screen's boss sprites' underlying background.
    
                //status = StoreScreenBossSpriteBackgrounds (graphics);

                if (status == ERR_SUCCESS)
                {
                    // Store the player sprite's underlying background.

                    status = StorePlayerSpriteBackground (graphics);
                } // Endif.

            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::RestoreScreenSpriteBackgrounds (Gdiplus::Graphics &graphics)
{
    // Restore the screen's object sprites' underlying backgrounds.
    
    FolioStatus status = RestoreScreenObjectSpriteBackgrounds (graphics, 
                                                               m_objectSpriteDrawingElementsList);

    if (status == ERR_SUCCESS)
    {
        // Restore the screen's orchid sprite's underlying background.
    
        status = RestoreScreenOrchidSpriteBackground (graphics);

        if (status == ERR_SUCCESS)
        {
            // Restore the screen's nasty sprites' underlying backgrounds.
    
            status = RestoreNastySpriteBackgrounds (graphics);

            if (status == ERR_SUCCESS)
            {
                // Restore the screen's boss sprites' underlying background.
    
                //status = RestoreScreenBossSpriteBackgrounds (graphics);

                if (status == ERR_SUCCESS)
                {
                    // Restore the player sprite's underlying background.
        
                    status = RestorePlayerSpriteBackground (graphics);
                } // Endif.

            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::DrawScreenSprites (Gdiplus::Graphics &graphics)
{
    // Draw the screen's object sprites.
    
    FolioStatus status = DrawScreenObjectSprites (graphics, 
                                                  m_objectSpriteDrawingElementsList);

    if (status == ERR_SUCCESS)
    {
        // Draw the screen's orchid sprite.
    
        status = DrawScreenOrchidSprite (graphics);

        if (status == ERR_SUCCESS)
        {
            // Draw the screen's nasty sprites.
    
            status = DrawNastySprites (graphics);

            if (status == ERR_SUCCESS)
            {
                // Draw the screen's boss sprites.
    
                //status = DrawScreenBossSprites (graphics);

                if (status == ERR_SUCCESS)
                {
                    // Draw the player sprite.

                    status = DrawPlayerSprite (graphics);

                    if (status == ERR_SUCCESS)
                    {
                        // The canvas should be redrawn on the next draw.

                        m_canvas.SetRedrawRqd ();
                    } // Endif.
    
                } // Endif.
    
            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::CheckScreenSprites (Gdiplus::Graphics &graphics)
{
    // Check the screen's object sprites.

    FolioStatus status = CheckScreenObjectSprites (graphics, 
                                                   m_objectSpriteDrawingElementsList);

    if (status == ERR_SUCCESS)
    {
        // Check the screen's orchid sprite.

        status = CheckScreenOrchidSprite (graphics);

        if (status == ERR_SUCCESS)
        {
            // Check the screen's nasty sprites.

            status = CheckScreenNastySprites (m_canvas.GetCanvasDcHandle (),
                                              graphics, 
                                              m_collisionGrid, 
                                              m_addNastySpriteTickCount);

            if (status == ERR_SUCCESS)
            {
                // Check the screen's boss sprites.

                //status = CheckScreenBossSprites (graphics);

                if (status == ERR_SUCCESS)
                {
                    // Check the player sprite .

                    status = g_playerSprite->CheckPlayerSprite (graphics, 
                                                                m_collisionGrid,
                                                                m_objectSpriteDrawingElementsList);

                    if (status == ERR_SUCCESS)
                    {
                        // Has the player exited the screen?

                        if (g_playerSprite->IsExitedScreen ())
                        {
                            // Yes. Move to the new screen.

                            status = MoveToNewScreen ();
                        } // Endif.

                        else
                        {
                            // No. Store the screen's sprite backgrounds.

                            status = StoreScreenSpriteBackgrounds (graphics);

                            if (status == ERR_SUCCESS)
                            {            
                                // Draw the screen's sprites.

                                status = DrawScreenSprites (graphics);
                            } // Endif.

                        } // Endelse.

                    } // Endif.

                } // Endif.

            } // Endif.

        } // Endif.

    } // Endif.
    
    return (status);
} // Endproc.


FolioStatus Screen::ReleaseResourceGraphics ()
{
    // Release the screen's graphics from the resource graphics cache.

    return (g_resourceGraphicsCache.ReleaseResourceGraphics (g_screenMap.GetCurrentScreenMapIndex ()));
} // Endproc.


FolioStatus BuildScreens (Folio::Core::Applet::Canvas   &canvas,
                          ScreensList                   &screensList)
{
    FolioStatus status = ERR_SUCCESS;

    screensList.clear ();   // Initialise!

    // Scatter the screen objects.

    g_screenMap.ScatterObjects ();

    // Build the screens.

    for (UInt32 screenIndex = 0; 
         (status == ERR_SUCCESS) && (screenIndex < g_screenMap.GetTotalNumScreens ()); 
         ++screenIndex)
    {
        // Get the screen's background items list.

        BackgroundItemsList backgroundItemsList;

        status = QueryScreenBackgroundList (g_screenMap.GetScreenNumber (screenIndex),
                                            backgroundItemsList);
        
        if (status == ERR_SUCCESS)
        {
            // Add the screen to the screens list.

            screensList.push_back (ScreenPtr(new ScreenPtr::element_type(canvas, 
                                                                         backgroundItemsList)));
        } // Endif.

    } // Endfor.

    if (status != ERR_SUCCESS)
    {
        screensList.clear ();
    } // Endif.
                                                         
    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
