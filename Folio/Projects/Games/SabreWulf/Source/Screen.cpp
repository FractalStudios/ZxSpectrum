// "Home-made" includes.
#include    "StdAfx.h"
#include    "Screen.h"

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

Screen::Screen (Folio::Core::Applet::Canvas &canvas,
                const ScreenMapPtr          &screenMap,
                const InformationPanelPtr   &informationPanel,
                const BackgroundItemsList   &backgroundItemsList,
                const SpriteGraphicsMapPtr  &spriteGraphicsMap)
:   m_screenScreenRect(SCREEN_X_ORIGIN, SCREEN_Y_ORIGIN, SCREEN_WIDTH, SCREEN_HEIGHT),
    m_canvas(canvas),
    m_screenMap(screenMap),
    m_informationPanel(informationPanel),
    m_backgroundItemsList(backgroundItemsList),
    m_spriteGraphicsMap(spriteGraphicsMap),
    m_exitScreenTickCount(0),       
    m_createNastySpriteTickCount(0)
{
} // Endproc.


Screen::~Screen ()
{
} // Endproc.


FolioStatus Screen::Draw (const PlayerSpritePtr &playerSprite, 
                          OrchidSpritePtr       &orchidSprite)
{
    // Get the canvas device context.

    FolioHandle dcHandle = m_canvas.GetCanvasDcHandle ();

    // Query the screen's drawing elements.

    Folio::Core::Game::DrawingElementsList  drawingElementsList;

    FolioStatus status = QueryDrawingElements (dcHandle, drawingElementsList);

    // If the screen's player sprite is not set then the screen needs to be initialised.

    if (!m_playerSprite)
    {
        // Initialise the screen.

        status = InitialiseScreen (dcHandle, drawingElementsList, playerSprite, orchidSprite);
    } // Endif.

    else
    {
        // Update the screen.

        status = UpdateScreen (dcHandle, drawingElementsList, orchidSprite);
    } // Endelse.

    if (status == ERR_SUCCESS)
    {
        // Draw the information panel.

        status = m_informationPanel->Draw ();

        if (status == ERR_SUCCESS)
        {
            // Clear the canvas rectangle occupied by the screen.

            status = m_canvas.ClearCanvasRectangle (m_screenScreenRect);

            if (status == ERR_SUCCESS)
            {
                // Draw the screen's drawing elements in the canvas.

                status = m_canvas.DrawDrawingElements (drawingElementsList);

                if (status == ERR_SUCCESS)
                {
                    // Set the player's position at the screen's entrance.

                    status = m_playerSprite->SetScreenEntranceTopLeft (m_screenScreenRect,
                                                                       m_collisionGrid);  
                
                    if (status == ERR_SUCCESS)
                    {
                        // Get the canvas graphics.

                        Gdiplus::Graphics   *graphics = m_canvas.GetCanvasGraphics ();
    
                        // Store the screen's sprite backgrounds.

                        status = StoreSpriteBackgrounds (*graphics);

                        if (status == ERR_SUCCESS)
                        {
                            // Draw the screen's sprites.

                            status = DrawSprites (*graphics);
                        } // Endif.

                    } // Endif.

                } // Endif.

            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::QueryDrawingElements (FolioHandle                               dcHandle,
                                          Folio::Core::Game::DrawingElementsList    &drawingElementsList)
{
    FolioStatus status = ERR_SUCCESS;

    drawingElementsList.clear ();   // Initialise!

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
            drawingElementsList.insert (drawingElementsList.end (),
                                        backgroundItemDrawingElementsList.begin (),
                                        backgroundItemDrawingElementsList.end ());
        } // Endif.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus Screen::HandleProcessFrame (bool    &isStarting,
                                        UInt32  *frameRateIncrement)
{
    // Get the canvas graphics.

    Gdiplus::Graphics   *graphics = m_canvas.GetCanvasGraphics ();

    // Restore the sprite backgrounds.

    FolioStatus status = RestoreSpriteBackgrounds (*graphics);

    if (status == ERR_SUCCESS)
    {
        // Check the sprites.

        status = CheckSprites (*graphics);

        if (status == ERR_SUCCESS)
        {
            // Let the information panel process the frame.

            status = m_informationPanel->HandleProcessFrame (isStarting);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::InitialiseScreen (FolioHandle                                   dcHandle,
                                      const Folio::Core::Game::DrawingElementsList  &drawingElementsList,
                                      const PlayerSpritePtr                         &playerSprite,
                                      OrchidSpritePtr                               &orchidSprite)
{                      
    // Note the player.

    m_playerSprite = playerSprite;

    // Initialise the screen's collision grid.

    FolioStatus status = InitialiseCollisionGrid (drawingElementsList);

    if (status == ERR_SUCCESS)
    {
        // Initialise the screen's sprites.

        status = InitialiseSprites (dcHandle, orchidSprite);

        if (status == ERR_SUCCESS)
        {
            // Increment the number of screens visited.

            m_informationPanel->IncrementNumScreensVisited ();
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::InitialiseCollisionGrid (const Folio::Core::Game::DrawingElementsList &drawingElementsList)
{
    // Create the screen's collision grid.

    FolioStatus status = m_collisionGrid.Create (m_screenScreenRect);

    if (status == ERR_SUCCESS)
    {
        // Initialise the screen's collision grid.

        for (Folio::Core::Game::DrawingElementsList::const_iterator itr = drawingElementsList.begin ();
             (status == ERR_SUCCESS) && (itr != drawingElementsList.end ());
             ++itr)
        {
            // Add the screen's drawing element to the screen's collision grid.

            status = m_collisionGrid.AddCellElement (*itr);
        } // Endfor.
    
    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::InitialiseSprites (FolioHandle      dcHandle,
                                       OrchidSpritePtr  &orchidSprite)
{
    // Initialise the object sprites.

    FolioStatus status = InitialiseObjectSprites (dcHandle);

    if (status == ERR_SUCCESS)
    {
        // Does the screen support an orchid sprite?

        if (m_screenMap->IsScreenOrchidSprite (orchidSprite))
        {
            // Yes. Initialise the orchid sprite.

            status = InitialiseOrchidSprite (orchidSprite);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::UpdateScreen (FolioHandle                                   dcHandle,
                                  const Folio::Core::Game::DrawingElementsList  &drawingElementsList,
                                  OrchidSpritePtr                               &orchidSprite)
{
    FolioStatus status = ERR_SUCCESS;

    // Does the screen support an orchid sprite?

    if (m_screenMap->IsScreenOrchidSprite (orchidSprite))
    {
        // Yes. Update the orchid sprite.

        status = UpdateOrchidSprite (orchidSprite);
    } // Endif.

    if (status == ERR_SUCCESS)
    {
        m_createNastySpriteTickCount = 0;   // Reset the create nasty sprite tick count.

        // Should the nasty sprites be removed?

        if (NastySprite::IsRemoveScreenNastySprites (m_exitScreenTickCount))
        {
            // Yes. Remove the nasty sprites.

            status = RemoveNastySprites ();
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::StoreSpriteBackgrounds (Gdiplus::Graphics &graphics)
{
    // Store the object sprites' underlying backgrounds.
    
    FolioStatus status = Folio::Core::Game::StoreSpriteBackgrounds<ObjectSpriteDrawingElementsList> (graphics, 
                                                                                                     m_objectSpriteDrawingElementsList);

    if (status == ERR_SUCCESS)
    {
        // Store the orchid sprite's underlying background.
    
        status = m_orchidSpriteDrawingElement.StoreSpriteBackground (graphics);

        if (status == ERR_SUCCESS)
        {
            // Store the nasty sprites' underlying backgrounds.
    
            status = Folio::Core::Game::StoreSpriteBackgrounds<NastySpriteDrawingElementsList> (graphics, 
                                                                                                m_nastySpriteDrawingElementsList);

            if (status == ERR_SUCCESS)
            {
    //        // Store the boss sprite's underlying background.
    //
    //        status = m_bossSpriteDrawingElement.StoreSpriteBackground (graphics);

    //        if (status == ERR_SUCCESS)
    //        {
                    // Store the player's underlying background.

                    status = m_playerSprite->StoreUnderlyingBackground (graphics);
    //        } // Endif.

            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::RestoreSpriteBackgrounds (Gdiplus::Graphics &graphics)
{
    // Restore the object sprites' underlying backgrounds.
    
    FolioStatus status = Folio::Core::Game::RestoreSpriteBackgrounds<ObjectSpriteDrawingElementsList> (graphics, 
                                                                                                       m_objectSpriteDrawingElementsList);

    if (status == ERR_SUCCESS)
    {
        // Restore the orchid sprite's underlying background.
    
        status = m_orchidSpriteDrawingElement.RestoreSpriteBackground (graphics);

        if (status == ERR_SUCCESS)
        {
            // Restore the nasty sprites' underlying backgrounds.
    
            status = Folio::Core::Game::RestoreSpriteBackgrounds<NastySpriteDrawingElementsList> (graphics, 
                                                                                                  m_nastySpriteDrawingElementsList);

            if (status == ERR_SUCCESS)
            {
    //        // Restore the boss sprite's underlying background.
    //
    //        status = m_bossSpriteDrawingElement.RestoreSpriteBackground (graphics);

    //        if (status == ERR_SUCCESS)
    //        {
                    // Restore the player's underlying background.
        
                    status = m_playerSprite->RestoreUnderlyingBackground (graphics);
    //        } // Endif.

            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::DrawSprites (Gdiplus::Graphics &graphics)
{
    // Draw the object sprites.
    
    FolioStatus status = Folio::Core::Game::DrawSprites<ObjectSpriteDrawingElementsList> (graphics, 
                                                                                          m_objectSpriteDrawingElementsList);

    if (status == ERR_SUCCESS)
    {
        // Draw the orchid sprite.
    
        status = m_orchidSpriteDrawingElement.DrawSprite (graphics);

        if (status == ERR_SUCCESS)
        {
            // Draw the nasty sprites.
    
            status = Folio::Core::Game::DrawSprites<NastySpriteDrawingElementsList> (graphics, 
                                                                                     m_nastySpriteDrawingElementsList);

            if (status == ERR_SUCCESS)
            {
    //        // Draw the boss sprite.
    //
    //        status = m_bossSpriteDrawingElement.DrawSprite (graphics);

    //        if (status == ERR_SUCCESS)
    //        {
                    // Draw the player.

                    status = m_playerSprite->Draw (graphics);

                    if (status == ERR_SUCCESS)
                    {
                        // The canvas should be redrawn on the next draw.

                        m_canvas.SetRedrawRqd ();
                    } // Endif.
    
    //        } // Endif.
    
            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::CheckSprites (Gdiplus::Graphics &graphics)
{
    // Check the object sprites.

    FolioStatus status = CheckObjectSprites (graphics);

    if (status == ERR_SUCCESS)
    {
        // Check the orchid sprite.

        status = CheckOrchidSprite (graphics);

        if (status == ERR_SUCCESS)
        {
            // Check the nasty sprites.

            status = CheckNastySprites (graphics);

            if (status == ERR_SUCCESS)
            {
    //        // Check the boss sprite.

    //        status = CheckBossSprite (graphics);

    //        if (status == ERR_SUCCESS)
    //        {
                    // Check the player.

                    status = CheckPlayer (graphics);

                    if (status == ERR_SUCCESS)
                    {
                        if (m_playerSprite->IsExitedScreen ())
                        {
                            // Move to the new screen.

                            MoveToNewScreen ();
                        } // Endif.

                        else
                        {
                            // Store the sprite backgrounds.

                            status = StoreSpriteBackgrounds (graphics);

                            if (status == ERR_SUCCESS)
                            {            
                                // Draw the sprites.

                                status = DrawSprites (graphics);
                            } // Endif.

                        } // Endelse.

                    } // Endif.

    //            } // Endif.

            } // Endif.

        } // Endif.

    } // Endif.
    
    return (status);
} // Endproc.


UInt32  Screen::MoveToNewScreen ()
{
    // Get the current screen exit.

    CollisionGrid::ScreenExit   screenExit(m_playerSprite->GetScreenExit ());

    // Get the next screen index.

    FolioStatus status = m_screenMap->GetNewScreenIndex (screenExit.m_orientation);

    if (status == ERR_SUCCESS)
    {
        // Note the exit screen tick count for the old screen.

        m_exitScreenTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount ();
    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::InitialiseObjectSprites (FolioHandle dcHandle)
{
    m_objectSpriteDrawingElementsList.clear (); // Initialise!
    
    // Query the screens's object sprites.

    ObjectSpritesList   objectSpritesList;

    FolioStatus status = m_screenMap->QueryScreenObjectSprites (dcHandle,
                                                                objectSpritesList);

    if ((status == ERR_SUCCESS) && !objectSpritesList.empty ())
    {
        // Add each object sprite to the screen.

        for (ObjectSpritesList::const_iterator itr = objectSpritesList.begin ();
             (status == ERR_SUCCESS) && (itr != objectSpritesList.end ());
             ++itr)
        {
            // Add the object sprite to the screen.

            status = AddObjectSprite (*itr);
        } // Endfor.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::CheckObjectSprites (Gdiplus::Graphics &graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // Any screen object sprites?

    if (!m_objectSpriteDrawingElementsList.empty ())
    {
        // Yes. Change the screen's object sprite colours.

        for (ObjectSpriteDrawingElementsList::iterator itr = m_objectSpriteDrawingElementsList.begin ();
             (status == ERR_SUCCESS) && (itr != m_objectSpriteDrawingElementsList.end ());
             ++itr)
        {
            // Get the object sprite.

            ObjectSpritePtr &objectSprite(itr->m_sprite);

            // Change the colour of the object sprite.

            status = objectSprite->ChangeObjectSpriteColour ();
        } // Endfor.
    
    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::AddObjectSprite (const ObjectSpritePtr &objectSprite)
{
    // Create an object sprite drawing element.

    ObjectSpriteDrawingElement  objectSpriteDrawingElement(DRAWING_ELEMENT_OBJECT_SPRITE, 
                                                           objectSprite, 
                                                           objectSprite->GetCollisionGridCellValue ());

    // Add the object sprite to the screen's collision grid.

    FolioStatus status = m_collisionGrid.AddCellElement (*(objectSpriteDrawingElement.m_drawingElement));

    if (status == ERR_SUCCESS)
    {
        // Add to the screen's object sprite drawing elements list.

        m_objectSpriteDrawingElementsList.push_back (objectSpriteDrawingElement);
    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::InitialiseOrchidSprite (OrchidSpritePtr &orchidSprite)
{
    // Create an orchid sprite drawing element.
    
    FolioStatus status = m_orchidSpriteDrawingElement.Create (DRAWING_ELEMENT_ORCHID_SPRITE, 
                                                              orchidSprite,
                                                              orchidSprite->GetCollisionGridCellValue ());

    if (status == ERR_SUCCESS)
    {
        // Add the orchid sprite to the screen's collision grid.

        status = m_collisionGrid.AddCellElement (*(m_orchidSpriteDrawingElement.m_drawingElement));
            
        if (status == ERR_SUCCESS)
        {
            // Start the orchid sprite's transition tick count.

            m_orchidSpriteDrawingElement.m_sprite->StartTransitionTickCount ();
        } // Endif.

    } // Endif.
    
    return (status);
} // Endproc.


FolioStatus Screen::UpdateOrchidSprite (OrchidSpritePtr &orchidSprite)
{
    // Is the orchid sprite drawing element created?

    if (m_orchidSpriteDrawingElement.IsCreated ())
    {
        // Yes. Start the orchid sprite's transition tick count.

        m_orchidSpriteDrawingElement.m_sprite->StartTransitionTickCount ();
    } // Endif.

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus Screen::CheckOrchidSprite (Gdiplus::Graphics &graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the orchid sprite drawing element created?

    if (m_orchidSpriteDrawingElement.IsCreated ())
    {
        // Yes. Check the orchid sprite's transition.

        m_orchidSpriteDrawingElement.m_sprite->CheckTransition ();
    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::CheckNastySprites (Gdiplus::Graphics &graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created all the nasty sprites?

    if (m_playerSprite->IsReady ()  &&  
        !m_playerSprite->IsSick ()  &&
        (m_nastySpriteDrawingElementsList.size () < MAX_NUM_NASTY_SPRITES))
    {
        // No. Start any nasty sprites.

        status = StartNastySprites (graphics);
    } // Endif.

    if ((status == ERR_SUCCESS) && !m_nastySpriteDrawingElementsList.empty ())
    {
        // Process the nasty sprites.

        NastySpriteDrawingElementsList::iterator    itr = m_nastySpriteDrawingElementsList.begin ();

        do
        {
            // Check the nasty sprite.

            status = itr->m_sprite->CheckNasty (itr->m_drawingElement, 
                                                graphics, 
                                                m_collisionGrid);

            // Is the nasty sprite dead?

            if (itr->m_sprite->IsDead ())
            {
                // Yes. Remove it from the the screen's nasty sprites list.

                itr = m_nastySpriteDrawingElementsList.erase (itr);
            } // Endif.
                
            else
            {
                ++itr;  // Next nasty sprite.
            } // Endelse.

        } // Enddo.
        while ((status == ERR_SUCCESS) && 
               (itr != m_nastySpriteDrawingElementsList.end ()));
    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::StartNastySprites (Gdiplus::Graphics &graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we already started the create nasty tick count?

    if (m_createNastySpriteTickCount)
    {
        // Yes. Should we create a nasty sprite?

        if (Folio::Core::Util::DateTime::GetCurrentTickCount () >= m_createNastySpriteTickCount)
        {
            // Yes. Calculate the number of nasty sprites to create.

            UInt32  numNastySpritesToCreate = 
                Folio::Core::Util::Random::GetRandomNumber(1, MAX_NUM_NASTY_SPRITES - m_nastySpriteDrawingElementsList.size ());

            // Add the nasty sprites.

            for (UInt32 nastySpriteCount = 0; 
                 (status == ERR_SUCCESS) && (nastySpriteCount < numNastySpritesToCreate); 
                 ++nastySpriteCount)
            {
                // Add a nasty sprite to the screen.

                status = AddNastySprite (NastySprite::GetNastySpriteToCreate (m_informationPanel->GetNumFoundAmuletPieces ()));
            } // Endfor.

            if (status == ERR_SUCCESS)
            {
                // Restart the create nasty sprite tick count.

                m_createNastySpriteTickCount = NastySprite::GetCreateNastySpriteTickCount ();
            } // Endif.

        } // Endif.

    } // Endif.

    else
    {
        // No. Start the create nasty sprite tick count.

        m_createNastySpriteTickCount = NastySprite::GetCreateNastySpriteTickCount ();
    } // Endelse.

    return (status);
} // Endproc.


FolioStatus Screen::AddNastySprite (NASTY_SPRITE_ID nastySpriteId)
{
    // Create the nasty sprite.

    NastySpritePtr  nastySprite(new NastySpritePtr::element_type(m_playerSprite));
    
    FolioStatus status = nastySprite->Create (m_canvas.GetCanvasDcHandle (),
                                              m_spriteGraphicsMap,
                                              nastySpriteId,
                                              m_collisionGrid);

    if (status == ERR_SUCCESS)
    {
        // Create a nasty sprite drawing element.

        NastySpriteDrawingElement   nastySpriteDrawingElement(DRAWING_ELEMENT_NASTY_SPRITE, 
                                                              nastySprite);

        // Add to the screen's nasty sprite drawing elements list.

        m_nastySpriteDrawingElementsList.push_back (nastySpriteDrawingElement);
    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::RemoveNastySprites ()
{
    FolioStatus status = ERR_SUCCESS;

    if (!m_nastySpriteDrawingElementsList.empty ())
    {
        // Remove all the nasty sprites.

        NastySpriteDrawingElementsList::iterator    itr = m_nastySpriteDrawingElementsList.begin ();

        do
        {
            // Remove the nasty sprite from the screen's collision grid.

            status = m_collisionGrid.RemoveCellElement (*(itr->m_drawingElement));

            if (status == ERR_SUCCESS)
            {
                // Remove from the screen's nasty sprite drawing elements list.

                itr = m_nastySpriteDrawingElementsList.erase (itr);
            } // Endif.

        } // Enddo.
        while ((status == ERR_SUCCESS) && 
               (itr != m_nastySpriteDrawingElementsList.end ()));
    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::KillNastySprites ()
{
    FolioStatus status = ERR_SUCCESS;

    if (!m_nastySpriteDrawingElementsList.empty ())
    {
        // Kill all the nasty sprites.

        for (NastySpriteDrawingElementsList::iterator itr = m_nastySpriteDrawingElementsList.begin ();
             (status == ERR_SUCCESS) && (itr != m_nastySpriteDrawingElementsList.end ());
             ++itr)
        {
            // Remove the nasty sprite from the screen's collision grid.

            status = m_collisionGrid.RemoveCellElement (*(itr->m_drawingElement));

            if (status == ERR_SUCCESS)
            {
                // The nasty sprite is dead.

                itr->m_sprite->SetDead (false); // Don't play its terminating sound.
            } // Endif.

        } // Endfor.
    
    } // Endif.

    return (status);
} // Endproc.


//FolioStatus Screen::CheckBossSprite (Gdiplus::Graphics &graphics)
//{
//    FolioStatus status = ERR_SUCCESS;
//
//    // Has the boss sprite been created?
//
//    if (m_bossSpriteDrawingElement.IsCreated ())
//    {
//        // Yes. Get the boss sprite.
//
//        BossSpritePtr   &bossSprite(m_bossSpriteDrawingElement.m_sprite);
//
//        // Get the state of the boss sprite.
//
//        switch (bossSprite->GetState ())
//        {
//        case BossSprite::STATE_INITIALISED:
//            // The boss sprite is initialised.
//
//            status = bossSprite->Static (graphics, m_collisionGrid);
//            break;
//
//        case BossSprite::STATE_TERMINATED:
//            // The boss sprite is terminated.
//
//            // Kill the boss sprite
//
//            m_bossSpriteDrawingElement.Kill ();
//            break;
//
//        case BossSprite::STATE_STATIC:
//        case BossSprite::STATE_MOVING:
//            // Move the boss sprite.
//
//            status = bossSprite->Move (graphics, *m_informationPanel, m_collisionGrid);
//
//            if (status == ERR_SUCCESS)
//            {
//                // Set the boss sprite's drawing element's top-left screen position.
//
//                m_bossSpriteDrawingElement.m_drawingElement->SetScreenTopLeft (bossSprite->GetScreenXLeft (), 
//                                                                               bossSprite->GetScreenYTop ());
//
//                // Update the boss sprite in the screen's collision grid.
//
//                status = UpdateCollisionGridDrawingElement (*(m_bossSpriteDrawingElement.m_drawingElement));
//            } // Endif.
//            break;
//
//        default:
//            break;
//        } // Endswitch.
//
//    } // Endif.
//
//    return (status);
//} // Endproc.
//
//
//FolioStatus Screen::StartBossSprite ()
//{
//    FolioStatus status = ERR_SUCCESS;
//
//    // Has the boss sprite been created?
//
//    if (m_bossSpriteDrawingElement.IsCreated ())
//    {
//        // Yes. Get the boss sprite.
//
//        BossSpritePtr   &bossSprite(m_bossSpriteDrawingElement.m_sprite);
//
//        // Reset the boss sprite.
//
//        bool    removeBossSprite = false;   // Initialise!
//
//        status = bossSprite->Reset (m_collisionGrid, removeBossSprite);
//
//        if (removeBossSprite && (status == ERR_SUCCESS))
//        {
//            // Remove the boss sprite from the screen's collision grid.
//
//            status = m_collisionGrid.RemoveCellElement (*(m_bossSpriteDrawingElement.m_drawingElement));
//
//            if (status == ERR_SUCCESS)
//            {
//                // Kill the boss sprite
//
//                m_bossSpriteDrawingElement.Kill ();
//            } // Endif.
//
//        } // Endif.
//
//    } // Endif.
//
//    // Has the boss sprite been killed?
//
//    else
//    if (!m_bossSpriteDrawingElement.IsKilled ())
//    {
//        // No. Is there a boss sprite on the screen?
//
//        BOSS_SPRITE_ID  bossSpriteId = GetScreenBossSpriteId (m_screenNumber);
//
//        if (bossSpriteId != BOSS_SPRITE_UNDEFINED)
//        {
//            // Yes. Add it.
//
//            status = AddBossSprite (bossSpriteId);
//        } // Endif.
//    
//    } // Endelse.
//
//    return (status);
//} // Endproc.
//
//
//FolioStatus Screen::AddBossSprite (BOSS_SPRITE_ID bossSpriteId)
//{
//    // Create the boss sprite.
//
//    BossSpritePtr   bossSprite(new BossSpritePtr::element_type);
//    
//    FolioStatus status = bossSprite->Create (m_canvas.GetCanvasDcHandle (),
//                                             bossSpriteId,
//                                             *m_spriteGraphicsMap,
//                                             m_playerSprite,
//                                             *m_informationPanel,
//                                             m_collisionGrid);
//
//    if (status == ERR_SUCCESS)
//    {
//        // The boss sprite is alive.
//
//        bossSprite->SetAlive ();
//
//        // Create a boss sprite drawing element.
//
//        status = m_bossSpriteDrawingElement.Create (bossSprite, 
//                                                    DRAWING_ELEMENT_BOSS_SPRITE, 
//                                                    bossSprite->GetCollisionGridCellValue ());
//    } // Endif.
//
//    return (status);
//} // Endproc.


FolioStatus Screen::CheckPlayer (Gdiplus::Graphics &graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // Get the state of the player.

    switch (m_playerSprite->GetState ())
    {
    case PlayerSprite::STATE_TERMINATED:
        // Decrement player's life.

        status = m_informationPanel->DecrementPlayerLife (&(m_playerSprite));
        break;

    case PlayerSprite::STATE_INITIALISED:
    case PlayerSprite::STATE_STATIC:
    case PlayerSprite::STATE_MOVING:
        // Check the player.

        status = m_playerSprite->CheckPlayer (graphics, m_collisionGrid);

        // Has the player exited the screen?

        if ((status == ERR_SUCCESS) && !m_playerSprite->IsExitedScreen ())
        {
            // No. Has the player collided with another object?

            CollisionGrid::CellElements cellElements;

            if (m_collisionGrid.IsCollision (m_playerSprite->GetCollisionRect (), 
                                             cellElements))
            {
                // Yes. Handle the collision.

                status = HandleCollision (cellElements, true); // Player collision.
            } // Endif.

        } // Endif.
        break;

    default:
        break;
    } // Endswitch.

    return (status);
} // Endproc.


FolioStatus Screen::HandleSickPlayer ()
{
    // Kill all the nasty sprites.

    return (KillNastySprites ());
} // Endproc.


FolioStatus Screen::HandleDeadPlayer ()
{
    // Kill all the nasty sprites.

    return (KillNastySprites ());
} // Endproc.


FolioStatus Screen::HandleCollision (const CollisionGrid::CellElements  &cellElements,
                                     bool                               player)
{
    FolioStatus status = ERR_SUCCESS;

    // Handle any collision.

    for (CollisionGrid::CellElements::const_iterator itr = cellElements.begin ();
         (status == ERR_SUCCESS) && (itr != cellElements.end ());
         ++itr)
    {
        switch (itr->m_cellValue)
        {
        case CollisionGrid::CELL_VALUE_ITEM:
            // Handle the collision with an item.

            status = HandleItemCollision (*itr, player);
            break;

        case CollisionGrid::CELL_VALUE_SOLID_ITEM:
            // Handle the collision with a solid item.

            status = HandleSolidItemCollision (*itr, player);
            break;

        case CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM:
            // Handle the collision with a collectable item.

            status = HandleCollectableItemCollision (*itr, player);
            break;

        case CollisionGrid::CELL_VALUE_NASTY_SPRITE:
            // Handle the collision with a nasty sprite.

            status = HandleNastySpriteCollision (*itr, player);
            break;

        //case CollisionGrid::CELL_VALUE_BOSS_SPRITE:
        //    // Handle the collision with a boss sprite.

        //    status = HandleBossSpriteCollision (*itr, player);
        //    break;

        default:
            break;
        } // Endswitch.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus Screen::HandleItemCollision (const CollisionGrid::CellElement   &cellElement,
                                         bool                               player)
{
    FolioStatus status = ERR_SUCCESS;

    // Is this a player collision?

    if (player)
    {
        // Yes. The only item on the screen is an orchid sprite.

        // Handle the player's collision with the orchid sprite.

        status = m_orchidSpriteDrawingElement.m_sprite->HandlePlayerCollision (m_playerSprite);

        // Is the player sick?

        if ((status == ERR_SUCCESS) && m_playerSprite->IsSick ())
        {
            // Yes.

            status = HandleSickPlayer ();
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::HandleSolidItemCollision (const CollisionGrid::CellElement  &cellElement,
                                              bool                              player)
{
    FolioStatus status = ERR_SUCCESS;

    // Is this a player collision?

    if (player)
    {
        // Yes. The player is bound to the solid item.

        Gdiplus::Rect   playerScreenRect(m_playerSprite->GetScreenRect ());
                
        m_collisionGrid.ToScreenRectBound (m_playerSprite->GetDirection (), 
                                           cellElement.m_screenRect,
                                           playerScreenRect);

        // Set the player's position.

        status = m_playerSprite->SetScreenTopLeft (playerScreenRect.X, playerScreenRect.Y);
    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::HandleCollectableItemCollision (const CollisionGrid::CellElement    &cellElement,
                                                    bool                                player)
{
    FolioStatus status = ERR_SUCCESS;

    // Is this a player collision?

    if (player)
    {
        // Yes. Find the collectable item that has been collided with.
        // Any collectable item is in the screen's object sprite drawing elements list.

        ObjectSpriteDrawingElementsList::iterator   itr = m_objectSpriteDrawingElementsList.begin ();

        bool    found = false;  // Initialise!

        do
        {              
            // Is this the collectable item that has been collided with?

            if (itr->m_sprite.get () == cellElement.m_userData)
            {
                // Yes. 
                
                found = true;   // Found the collectable item.
                
                // Remove the object sprite from the screen's collision grid.

                status = m_collisionGrid.RemoveCellElement (cellElement);

                if (status == ERR_SUCCESS)
                {
                    // Handle the player's collision with the object sprite.

                    status = itr->m_sprite->HandlePlayerCollision (m_playerSprite, 
                                                                   m_informationPanel);
                    
                    if (status == ERR_SUCCESS)
                    {
                        // Remove the object sprite from the screen's object sprite 
                        // drawing elements list.

                        m_objectSpriteDrawingElementsList.erase (itr);
                    } // Endif.

                } // Endif.

            } // Endif.

            else
            {
                ++itr;  // Next.
            } // Endelse.

        } // Enddo.
        while (!found                   && 
               (status == ERR_SUCCESS)  && 
               (itr != m_objectSpriteDrawingElementsList.end ()));
    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::HandleNastySpriteCollision (const CollisionGrid::CellElement    &cellElement,
                                                bool                                player)
{
    FolioStatus status = ERR_SUCCESS;

    // Get the nasty sprite that has been collided with.

    NastySprite *nastySprite(reinterpret_cast<NastySprite *> (cellElement.m_userData));

    // Is the nasty sprite ready and the player NOT immune?
            
    if (player && nastySprite->IsReady () && !m_playerSprite->IsImmune ())
    {
        // Yes. Remove the nasty sprite from the screen's collision grid.

        status = m_collisionGrid.RemoveCellElement (cellElement);

        if (status == ERR_SUCCESS)
        {
            // Is the player dead?

            if (m_playerSprite->IsDead (cellElement))
            {
                // Yes.
        
                status = HandleDeadPlayer ();
            } // Endif.

            if (status == ERR_SUCCESS)
            {
                // The nasty sprite is dead.

                nastySprite->SetDead ();

                // Increment the score.

                m_informationPanel->IncrementScore (InformationPanel::SCORE_NASTY_SPRITE_DEAD);
            } // Endif.
                    
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


//FolioStatus Screen::HandleBossSpriteCollision (const CollisionGrid::CellElement  &cellElement,
//                                               bool                              player)
//{
//    FolioStatus status = ERR_SUCCESS;
//
//    // Is this a player collision?
//
//    if (player)
//    {
//        // Yes. Get the boss sprite.
//
//        BossSpritePtr   &bossSprite(m_bossSpriteDrawingElement.m_sprite);
//
//        // Is the boss sprite ready?
//            
//        if (bossSprite->IsReady ())
//        {
//            // Can the boss sprite be killed?
//
//            if (bossSprite->CanBeKilled (*m_informationPanel))
//            {
//                // Yes. Remove the boss sprite from the screen's collision grid.
//
//                status = m_collisionGrid.RemoveCellElement (*(m_bossSpriteDrawingElement.m_drawingElement));
//
//                if (status == ERR_SUCCESS)
//                {
//                    // The boss sprite is dead.
//
//                    bossSprite->SetDead ();
//
//                    // Increment the score.
//
//                    m_informationPanel->IncrementScore (InformationPanel::SCORE_BOSS_SPRITE_DEAD);
//                } // Endif.
//
//            } // Endif.
//            
//            else
//            {
//                // No. The player is dead.
//        
//                status = HandleDeadPlayer ();
//            } // Endelse.
//
//        } // Endif.
//    
//    } // Endif.
//
//    return (status);
//} // Endproc.


FolioStatus BuildScreens (Folio::Core::Applet::Canvas   &canvas,
                          const ScreenMapPtr            &screenMap,
                          const InformationPanelPtr     &informationPanel,
                          const ScreenBackgroundsMap    &screenBackgroundsMap,
                          const SpriteGraphicsMapPtr    &spriteGraphicsMap,
                          ScreensList                   &screensList)
{
    FolioStatus status = ERR_SUCCESS;

    screensList.clear ();   // Initialise!

    // Scatter the objects.

    screenMap->ScatterObjects ();

    for (UInt32 screenIndex = 0; 
         (status == ERR_SUCCESS) && (screenIndex < screenMap->GetTotalNumScreens ()); 
         ++screenIndex)
    {
        // Get the screen number.

        ScreenMap::ScreenNumber screenNumber = screenMap->GetScreenNumber (screenIndex);

        // Add the screen to the screens list.

        screensList.push_back (ScreenPtr(new ScreenPtr::element_type(canvas,
                                                                     screenMap,
                                                                     informationPanel,
                                                                     screenBackgroundsMap.find (screenNumber)->second->GetBackgroundItemsList (),
                                                                     spriteGraphicsMap)));
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
