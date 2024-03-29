#pragma once

// STL includes.
#include    <vector>

// "Home-made" includes.
#include    <Applet.h>
#include    <Game.h>
#include    "BackgroundItem.h"
#include    "CollisionGrid.h"
#include    "ObjectSprite.h"
#include    "ScreenMap.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Screen.
class Screen
{
public:
    // Screen screen attributes.
    static  const   Int32   SCREEN_X_ORIGIN = 0;
    static  const   Int32   SCREEN_Y_ORIGIN = 16;
    static  const   Int32   SCREEN_WIDTH    = Folio::Core::Game::ZxSpectrum::MAX_SCREEN_X_PIXELS;
    static  const   Int32   SCREEN_HEIGHT   = Folio::Core::Game::ZxSpectrum::MAX_SCREEN_Y_PIXELS - SCREEN_Y_ORIGIN;

    Screen (Folio::Core::Applet::Canvas&    canvas,
            const CollisionGridPtr&         screenCollisionGrid,
            const BackgroundItemsList&      backgroundItemsList);
    ~Screen ();

    FolioStatus Draw (bool redisplay = false);
    FolioStatus HandleProcessFrame (bool& isStarting);

    static  Folio::Core::Game::ResourceGraphicsCache::OwnerId   MakeOwnerId (UInt32 screenNumber);

    FolioStatus ExitScreen ();
    
private:
    Folio::Core::Applet::Canvas &m_canvas;  // The canvas.

    CollisionGrid   m_screenCollisionGrid;    // The screen's collision grid.

    bool    m_screenInitialised;        // Indicates if the screen is initialised.
    UInt32  m_addNastySpriteTickCount;  // The add nasty sprite tick count.

    BackgroundItemsList             m_backgroundItemsList;              // The screen's background items list.
    ObjectSpriteDrawingElementsList m_objectSpriteDrawingElementsList;  // The screen's object sprite drawing elements list.

    bool    IsScreenInitialised () const;

    FolioStatus QueryScreenDrawingElements (FolioHandle                             dcHandle,
                                            Folio::Core::Game::DrawingElementsList& screenDrawingElementsList);
    FolioStatus InitialiseScreen (FolioHandle                                   dcHandle,
                                  const Folio::Core::Game::DrawingElementsList& screenDrawingElementsList);
    FolioStatus UpdateScreen (FolioHandle                                   dcHandle,
                              const Folio::Core::Game::DrawingElementsList& screenDrawingElementsList);
    FolioStatus DrawScreen (bool                                            redisplay,
                            const Folio::Core::Game::DrawingElementsList&   screenDrawingElementsList);
    FolioStatus MoveToNewScreen ();

    FolioStatus StoreScreenSpriteBackgrounds (Gdiplus::Graphics& graphics);
    FolioStatus RestoreScreenSpriteBackgrounds (Gdiplus::Graphics& graphics);
    FolioStatus DrawScreenSprites (Gdiplus::Graphics& graphics);
    FolioStatus CheckScreenSprites (Gdiplus::Graphics& graphics);

    FolioStatus ReleaseResourceGraphics ();

    // Private copy constructor to prevent copying.
    Screen (const Screen& rhs);

    // Private assignment operator to prevent copying.
    Screen& operator= (const Screen& rhs);
}; // Endclass.

// Screen pointer.
typedef std::shared_ptr<Screen> ScreenPtr;
             
// Screens list.
typedef std::vector<ScreenPtr>  ScreensList;

// Screen collision grid map.
typedef std::map<ScreenMap::ScreenNumber, CollisionGridPtr> ScreenCollisionGridMap;


// Routines.

extern  FolioStatus BuildScreens (Folio::Core::Applet::Canvas&  canvas,
                                  ScreensList&                  screensList);
extern  FolioStatus CreateScreenCollisionGrids (ScreenCollisionGridMap& screenCollisionGridMap);
extern  FolioStatus QueryScreenCollisionGrid (ScreenMap::ScreenNumber   screenNumber,
                                              CollisionGridPtr&         screenCollisionGrid);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
