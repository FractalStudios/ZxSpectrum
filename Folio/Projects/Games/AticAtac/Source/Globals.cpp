// "Home-made" includes.
#include    "StdAfx.h"
#include    "Globals.h"

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Globals.

// The resource graphics cache.
Folio::Core::Game::ResourceGraphicsCache    g_resourceGraphicsCache;

// The background items list.
BackgroundItemsList g_backgroundItemsList;      

// The static sprites list.
StaticSpritesList   g_staticSpritesList;        

// The main player.
PlayerSpritePtr g_mainPlayer;

// The player sprites map.
PlayerSpritesMap    g_playerSpritesMap;         

// The nasty sprite drawing elements list.
NastySpriteDrawingElementsList  g_nastySpriteDrawingElementsList;

// The boss sprite drawing element.
BossSpriteDrawingElement    g_bossSpriteDrawingElement;

// The boss sprites map.
BossSpritesMap  g_bossSpritesMap;         

// The weapon sprite drawing element.
WeaponSpriteDrawingElement  g_weaponSpriteDrawingElement;

// The weapon sprites map.
WeaponSpritesMap    g_weaponSpritesMap;         


FolioStatus InitialiseGlobals (FolioHandle dcHandle)
{
    // Create the background items.

    FolioStatus status = CreateBackgroundItems (g_backgroundItemsList);

    if (status == ERR_SUCCESS)
    {
        // Create the static sprites.

        status = CreateStaticSprites (g_staticSpritesList);

        if (status == ERR_SUCCESS)
        {
            // Destroy the main player.
            
            g_mainPlayer.reset ();

            // Create the player sprites map.

            status = CreatePlayerSprites (dcHandle, g_playerSpritesMap);

            if (status == ERR_SUCCESS)
            {
                // Clear the nasty sprite drawing elements list.

                g_nastySpriteDrawingElementsList.clear ();

                // Destroy the boss sprite drawing element.
            
                g_bossSpriteDrawingElement.Destroy ();

                // Create the boss sprites map.

                status = CreateBossSprites (dcHandle, g_bossSpritesMap);

                if (status == ERR_SUCCESS)
                {
                    // Destroy the weapon sprite drawing element.
            
                    g_weaponSpriteDrawingElement.Destroy ();

                    // Create the weapon sprites map.

                    status = CreateWeaponSprites (dcHandle, g_weaponSpritesMap);
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
