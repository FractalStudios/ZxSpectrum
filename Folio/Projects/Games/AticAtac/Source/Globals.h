// "Home-made" includes.
#include    <Game.h>
#include    "BackgroundItem.h"
#include    "BossSprite.h"
#include    "NastySprite.h"
#include    "PlayerSprite.h"
#include    "Screen.h"
#include    "StaticSprite.h"
#include    "WeaponSprite.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// The maximum number of nasty sprite drawing elements.
const   UInt32  MAX_NASTY_SPRITE_DRAWING_ELEMENTS = 6;


// Globals.

// The resource graphics cache.
extern  Folio::Core::Game::ResourceGraphicsCache    g_resourceGraphicsCache;

// The background items list.
extern  BackgroundItemsList g_backgroundItemsList;      

// The static sprites list.
extern  StaticSpritesList   g_staticSpritesList;        

// The main player.
extern  PlayerSpritePtr g_mainPlayer;

// The player sprites map.
extern  PlayerSpritesMap    g_playerSpritesMap;         

// The nasty sprite drawing elements list.
extern  NastySpriteDrawingElementsList  g_nastySpriteDrawingElementsList;

// The boss sprite drawing element.
extern  BossSpriteDrawingElement    g_bossSpriteDrawingElement;

// The boss sprites map.
extern  BossSpritesMap  g_bossSpritesMap;         

// The weapon sprite drawing element.
extern  WeaponSpriteDrawingElement  g_weaponSpriteDrawingElement;

// The weapon sprites map.
extern  WeaponSpritesMap    g_weaponSpritesMap;         


// Routines.

extern  FolioStatus InitialiseGlobals (FolioHandle dcHandle);
extern  FolioStatus TerminateGlobals ();

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/