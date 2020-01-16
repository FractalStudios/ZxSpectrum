// "Home-made" includes.
#include    <Applet.h>
#include    <Game.h>
#include    "BackgroundItemGraphics.h"
#include    "HighScoreTable.h"
#include    "InformationPanel.h"
#include    "MusicJukebox.h"
#include    "NastySprite.h"
#include    "OrchidSprite.h"
#include    "PlayerSprite.h"
#include    "ScreenBackground.h" 
#include    "ScreenMap.h" 

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Globals.

// The resource graphics cache.
extern  Folio::Core::Game::ResourceGraphicsCache    g_resourceGraphicsCache;

// The background item graphics.
extern  BackgroundItemGraphicsMap   g_backgroundItemGraphicsMap;

// The high score table.
extern  HighScoreTable  g_highScoreTable;

// The information panel.
extern  InformationPanelPtr g_informationPanel;         

// The music jukebox.
extern  MusicJukebox    g_musicJukebox;

// The screen backgrounds map.
extern  ScreenBackgroundsMap    g_screenBackgroundsMap;

// The screen map.
extern  ScreenMap    g_screenMap;

// The player sprite.
extern  PlayerSpritePtr g_playerSprite;

// The orchid sprite drawing element.
extern  OrchidSpriteDrawingElement  g_orchidSpriteDrawingElement;

// The nasty sprite drawing elements list.
extern  NastySpriteDrawingElementsList  g_nastySpriteDrawingElementsList;


// Routines.

extern  FolioStatus InitialiseGlobals (Folio::Core::Applet::Canvas  &canvas,
                                       bool                         applicationInitialise = true);
extern  FolioStatus TerminateGlobals ();

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/