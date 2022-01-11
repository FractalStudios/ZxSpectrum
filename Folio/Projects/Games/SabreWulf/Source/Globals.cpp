// "Home-made" includes.
#include    "StdAfx.h"
#include    "Globals.h"
#include    "Screen.h"
#include    "SpriteGraphics.h"

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Globals.

// The resource graphics cache.
Folio::Core::Game::ResourceGraphicsCache    g_resourceGraphicsCache;

// The background item graphics.
BackgroundItemGraphicsMap   g_backgroundItemGraphicsMap;

// The high score table.
HighScoreTable  g_highScoreTable;

// The information panel.
InformationPanelPtr g_informationPanel;         

// The sound resources.
SoundResources  g_soundResources;

// The music jukebox.
MusicJukebox    g_musicJukebox;

// The screen backgrounds map.
ScreenBackgroundsMap    g_screenBackgroundsMap;

// The screen map.
ScreenMap    g_screenMap;

// The screen collision grid map.
ScreenCollisionGridMap  g_screenCollisionGridMap;

// The player sprite.
PlayerSpritePtr g_playerSprite;

// The orchid sprite drawing element.
OrchidSpriteDrawingElement  g_orchidSpriteDrawingElement;

// The nasty sprite drawing elements list.
NastySpriteDrawingElementsList  g_nastySpriteDrawingElementsList;

// The boss sprite drawing elements list.
BossSpriteDrawingElementsList   g_bossSpriteDrawingElementsList;


FolioStatus InitialiseGlobals (Folio::Core::Applet::Canvas& canvas,
                               bool                         applicationInitialise)
{
    FolioStatus status = ERR_SUCCESS;

    // Get the canvas device context.

    FolioHandle dcHandle = canvas.GetCanvasDcHandle ();
    
    if (applicationInitialise)
    {
        // Get the canvas application instance.
    
        FolioHandle instanceHandle = canvas.GetAppletInstanceHandle ();

        // Create the background item graphics.

        status = CreateBackgroundItemGraphics (instanceHandle,
                                               g_backgroundItemGraphicsMap);

        if (status == ERR_SUCCESS)
        {
            // Create the sprite graphics.

            status = CreateSpriteGraphics (instanceHandle,
                                           g_resourceGraphicsCache);

            if (status == ERR_SUCCESS)
            {
                // Create the information panel.

                status = CreateInformationPanel (canvas, g_informationPanel);

                if (status == ERR_SUCCESS)
                {
                    // Create the sound resources.

                    status = g_soundResources.Create ();

                    if (status == ERR_SUCCESS)
                    {
                        // Create the music jukebox.

                        status = g_musicJukebox.Create ();

                        if (status == ERR_SUCCESS)
                        {
                            // Create the screen backgrounds.

                            status = CreateScreenBackgrounds (g_backgroundItemGraphicsMap,
                                                              g_screenBackgroundsMap);

                            if (status == ERR_SUCCESS)
                            {
                                // Create the screen collision grids.

                                status = CreateScreenCollisionGrids (g_screenCollisionGridMap);
                            } // Endif.

                        } // Endif.

                    } // Endif.

                } // Endif.

            } // Endif.

        } // Endif.
    
    } // Endif.

    if (status == ERR_SUCCESS)
    {
        // Create the player sprite.

        status = CreatePlayerSprite (dcHandle, g_playerSprite);

        if (status == ERR_SUCCESS)
        {
            // Create the orchid sprite drawing element.

            status = CreateOrchidSpriteDrawingElement (dcHandle);

            if (status == ERR_SUCCESS)
            {
                // Create the boss sprite drawing elements.

                status = CreateBossSpriteDrawingElements (dcHandle);

                if (status == ERR_SUCCESS)
                {
                    // Clear the nasty sprite drawing elements list.

                    g_nastySpriteDrawingElementsList.clear ();
                } // Endif.

            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus TerminateGlobals ()
{
    FolioStatus status = ERR_SUCCESS;

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
