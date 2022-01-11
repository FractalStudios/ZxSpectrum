// "Home-made" includes.
#include    "StdAfx.h"
#include    "Globals.h"
#include    "NastySprite.h"
#include    "OrchidSprite.h"
#include    "PlayerSprite.h"
#include    "Screen.h"

//#define _DRAW_ORCHID_
//#define _DRAW_NASTIES_
//#define _DRAW_BOSS_

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

Screen::Screen (Folio::Core::Applet::Canvas&    canvas,
                const CollisionGridPtr&         screenCollisionGrid,
                const BackgroundItemsList&      backgroundItemsList)
:   m_canvas(canvas),
    m_screenCollisionGrid(*screenCollisionGrid),
    m_screenInitialised(false),
    m_addNastySpriteTickCount(0),
    m_backgroundItemsList(backgroundItemsList)
{
} // Endproc.


Screen::~Screen ()
{
    // Release the screen's graphics from the resource graphics cache.

    ReleaseResourceGraphics ();
} // Endproc.


FolioStatus Screen::Draw (bool redisplay)
{
    // Get the canvas device context.

    FolioHandle dcHandle = m_canvas.GetCanvasDcHandle ();

    // Query the screen's drawing elements.

    Folio::Core::Game::DrawingElementsList  screenDrawingElementsList;

    FolioStatus status = QueryScreenDrawingElements (dcHandle, screenDrawingElementsList);

    // Is the screen being redisplayed?

    if (!redisplay && (status == ERR_SUCCESS))
    {
        // No. Is the screen initialised?

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
            m_addNastySpriteTickCount = 0;    // Reset the screen's add nasty sprite tick count.
        } // Endif.

    } // Endif.

    if (status == ERR_SUCCESS)
    {
        // Draw the information panel.

        status = g_informationPanel->Draw (redisplay);

        if (status == ERR_SUCCESS)
        {
            // Draw the screen.

            status = DrawScreen (redisplay, screenDrawingElementsList);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::HandleProcessFrame (bool& isStarting)
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
                                                Folio::Core::Game::DrawingElementsList& screenDrawingElementsList)
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
                                      const Folio::Core::Game::DrawingElementsList& screenDrawingElementsList)
{                      
    // Initialise the screen's object sprites.

    FolioStatus status = InitialiseScreenObjectSprites (dcHandle, 
                                                        m_objectSpriteDrawingElementsList, 
                                                        m_screenCollisionGrid);

    if (status == ERR_SUCCESS)
    {
        // Initialise the screen's orchid sprite.
#ifdef _DRAW_ORCHID_
        status = InitialiseScreenOrchidSprite (m_screenCollisionGrid);
#endif
        if (status == ERR_SUCCESS)
        {
            // Remove the screen's boss sprites.

            status = RemoveScreenBossSprites (m_screenCollisionGrid);

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
                                  const Folio::Core::Game::DrawingElementsList& screenDrawingElementsList)
{
    FolioStatus status = ERR_SUCCESS;

    // Update the screen's orchid sprite.
#ifdef _DRAW_ORCHID_
    status = UpdateScreenOrchidSprite ();
#endif

    if (status == ERR_SUCCESS)
    {
        // Remove the screen's boss sprites.

        status = RemoveScreenBossSprites (m_screenCollisionGrid);
    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::DrawScreen (bool                                            redisplay,
                                const Folio::Core::Game::DrawingElementsList&   screenDrawingElementsList)
{
    // Clear the canvas rectangle occupied by the screen.

    FolioStatus status = m_canvas.ClearCanvasRectangle (m_screenCollisionGrid.GetFloorRect ());

    if (status == ERR_SUCCESS)
    {
        // Draw the screen's drawing elements in the canvas.

        status = m_canvas.DrawDrawingElements (screenDrawingElementsList);

        if (status == ERR_SUCCESS)
        {
            // Is the screen being redisplayed?

            if (!redisplay)
            {
                // No. Set the player's position at the screen's entrance.

                status = g_playerSprite->SetScreenEntranceTopLeft (m_screenCollisionGrid.GetFloorRect (),
                                                                   &(m_screenCollisionGrid));  
            } // Endif.

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


Folio::Core::Game::ResourceGraphicsCache::OwnerId   Screen::MakeOwnerId (UInt32 screenNumber)
{
    return (TXT("Screen ") + Folio::Core::Game::ResourceGraphicsCache::MakeOwnerId (screenNumber));
} // Endproc.


FolioStatus Screen::ExitScreen ()
{
    // Release the screen's graphics from the resource graphics cache.

    FolioStatus status = ReleaseResourceGraphics ();

    return (status);
} // Endproc.


FolioStatus Screen::StoreScreenSpriteBackgrounds (Gdiplus::Graphics& graphics)
{
    // Store the screen's object sprites' underlying backgrounds.
    
    FolioStatus status = StoreScreenObjectSpriteBackgrounds (graphics, 
                                                             m_objectSpriteDrawingElementsList);

    if (status == ERR_SUCCESS)
    {
        // Store the screen's orchid sprite's underlying background.
#ifdef _DRAW_ORCHID_
        status = StoreScreenOrchidSpriteBackground (graphics);
#endif
        if (status == ERR_SUCCESS)
        {
            // Store the screen's nasty sprites' underlying backgrounds.
#ifdef _DRAW_NASTIES_
            status = StoreScreenNastySpriteBackgrounds (graphics);
#endif
            if (status == ERR_SUCCESS)
            {
                // Store the screen's boss sprites' underlying background.
#ifdef _DRAW_BOSS_
                status = StoreScreenBossSpriteBackgrounds (graphics);
#endif
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


FolioStatus Screen::RestoreScreenSpriteBackgrounds (Gdiplus::Graphics& graphics)
{
    // Restore the screen's object sprites' underlying backgrounds.
    
    FolioStatus status = RestoreScreenObjectSpriteBackgrounds (graphics, 
                                                               m_objectSpriteDrawingElementsList);

    if (status == ERR_SUCCESS)
    {
        // Restore the screen's orchid sprite's underlying background.
#ifdef _DRAW_ORCHID_
        status = RestoreScreenOrchidSpriteBackground (graphics);
#endif
        if (status == ERR_SUCCESS)
        {
            // Restore the screen's nasty sprites' underlying backgrounds.
#ifdef _DRAW_NASTIES_
            status = RestoreScreenNastySpriteBackgrounds (graphics);
#endif
            if (status == ERR_SUCCESS)
            {
                // Restore the screen's boss sprites' underlying background.
#ifdef _DRAW_BOSS_
                status = RestoreScreenBossSpriteBackgrounds (graphics);
#endif
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


FolioStatus Screen::DrawScreenSprites (Gdiplus::Graphics& graphics)
{
    // Draw the screen's object sprites.
    
    FolioStatus status = DrawScreenObjectSprites (graphics, 
                                                  m_objectSpriteDrawingElementsList);

    if (status == ERR_SUCCESS)
    {
        // Draw the screen's orchid sprite.
#ifdef _DRAW_ORCHID_
        status = DrawScreenOrchidSprite (graphics);
#endif
        if (status == ERR_SUCCESS)
        {
            // Draw the screen's nasty sprites.
#ifdef _DRAW_NASTIES_
            status = DrawScreenNastySprites (graphics);
#endif
            if (status == ERR_SUCCESS)
            {
                // Draw the screen's boss sprites.
#ifdef _DRAW_BOSS_
                status = DrawScreenBossSprites (graphics);
#endif
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


FolioStatus Screen::CheckScreenSprites (Gdiplus::Graphics& graphics)
{
    // Check the screen's object sprites.

    FolioStatus status = CheckScreenObjectSprites (graphics, 
                                                   m_objectSpriteDrawingElementsList);

    if (status == ERR_SUCCESS)
    {
        // Check the screen's orchid sprite.
#ifdef _DRAW_ORCHID_
        status = CheckScreenOrchidSprite (graphics);
#endif
        if (status == ERR_SUCCESS)
        {
            // Check the screen's nasty sprites.
#ifdef _DRAW_NASTIES_
            status = CheckScreenNastySprites (m_canvas.GetCanvasDcHandle (),
                                              graphics, 
                                              m_screenCollisionGrid, 
                                              m_addNastySpriteTickCount);
#endif
            if (status == ERR_SUCCESS)
            {
                // Check ALL the boss sprites.
#ifdef _DRAW_BOSS_
                status = CheckBossSprites (m_canvas.GetCanvasDcHandle (), graphics, m_screenCollisionGrid);
#endif
                if (status == ERR_SUCCESS)
                {
                    // Check the player sprite.

                    status = g_playerSprite->CheckPlayerSprite (graphics, 
                                                                m_screenCollisionGrid,
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

    return (g_resourceGraphicsCache.ReleaseResourceGraphics (Screen::MakeOwnerId (g_screenMap.GetCurrentScreenMapIndex ())));
} // Endproc.


FolioStatus BuildScreens (Folio::Core::Applet::Canvas&  canvas,
                          ScreensList&                  screensList)
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
        // Get the screen number.

        ScreenMap::ScreenNumber screenNumber = g_screenMap.GetScreenNumber (screenIndex);

        // Get the screen's background items list.

        BackgroundItemsList backgroundItemsList;

        status = QueryScreenBackgroundList (screenNumber, backgroundItemsList);
        
        if (status == ERR_SUCCESS)
        {
            // Get the screen's collision grid.

            CollisionGridPtr    screenCollisionGrid;

            status = QueryScreenCollisionGrid (screenNumber, screenCollisionGrid);
        
            if (status == ERR_SUCCESS)
            {
                // Add the screen to the screens list.

                screensList.push_back (ScreenPtr(new ScreenPtr::element_type(canvas,
                                                                             screenCollisionGrid,
                                                                             backgroundItemsList)));
            } // Endif.

        } // Endif.

    } // Endfor.

    if (status != ERR_SUCCESS)
    {
        screensList.clear ();
    } // Endif.
                                                         
    return (status);
} // Endproc.


FolioStatus CreateScreenCollisionGrids (ScreenCollisionGridMap& screenCollisionGridMap)
{
    FolioStatus status = ERR_SUCCESS;

    screenCollisionGridMap.clear ();   // Initialise!

    // Build the screen collision grid map. 

    for (ScreenMap::ScreenNumber screenNumber = ScreenMap::MIN_SCREEN_NUMBER; 
        (status == ERR_SUCCESS) && (screenNumber <= ScreenMap::MAX_SCREEN_NUMBER); 
        ++screenNumber)
    {
        // Get the screen's background items list.

        BackgroundItemsList backgroundItemsList;

        status = QueryScreenBackgroundList (screenNumber, backgroundItemsList);

        if (status == ERR_SUCCESS)
        {
            // Create the screen's collision grid.

            CollisionGridPtr    screenCollisionGrid(new CollisionGridPtr::element_type);

            status = screenCollisionGrid->Create (Gdiplus::Rect(Screen::SCREEN_X_ORIGIN, 
                                                                Screen::SCREEN_Y_ORIGIN, 
                                                                Screen::SCREEN_WIDTH, 
                                                                Screen::SCREEN_HEIGHT));

            if (status == ERR_SUCCESS)
            {
                // Add the screen's background items to the screen's collision grid.

                for (BackgroundItemsList::iterator itr = backgroundItemsList.begin ();
                     (status == ERR_SUCCESS) && (itr != backgroundItemsList.end ());
                     ++itr)
                {
                    screenCollisionGrid->AddCellElement (CollisionGrid::CellElement (Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BACKGROUND_ITEM,
                                                                                     CollisionGrid::CELL_VALUE_WALL,
                                                                                     itr->GetScreenRect ()));
                } // Endfor.

                if (status == ERR_SUCCESS)
                {
                    // Store the screen's collision grid in the screen collision grid map.

                    screenCollisionGridMap.insert (ScreenCollisionGridMap::value_type(screenNumber, 
                                                                                      screenCollisionGrid));
                } // Endif.

            } // Endif.

        } // Endif.

    } // Endfor.

    if (status != ERR_SUCCESS)
    {
        screenCollisionGridMap.clear ();
    } // Endif.

    return (status);
} // Endproc.


FolioStatus QueryScreenCollisionGrid (ScreenMap::ScreenNumber   screenNumber,
                                      CollisionGridPtr&         screenCollisionGrid)
{
    FolioStatus status = ERR_SUCCESS;

    screenCollisionGrid.reset ();   // Initialise!

    // Find the screen in the screen collision grid map.

    ScreenCollisionGridMap::const_iterator  itr = g_screenCollisionGridMap.find (screenNumber);
    
    if (itr != g_screenCollisionGridMap.end ())
    {
        // Get the screen's collision grid.

        screenCollisionGrid = itr->second;
    } // Endif.

    else
    {
        status = ERR_NOT_FOUND;
    } // Endelse.
    
    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
