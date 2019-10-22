#pragma once

// STL includes.
#include    <vector>

// "Home-made" includes.
#include    <Game.h>
#include    "BackgroundItemGraphics.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Background item.
class BackgroundItem
{
public:
    BackgroundItem (BACKGROUND_ITEM_ID  backgroundItemId,
                    Int32               screenXLeft,    
                    Int32               screenYTop);
    ~BackgroundItem ();

    void                    SetBackgroundItemGraphic (const BackgroundItemGraphicsMapPtr &backgroundItemGraphicsMap);
    BackgroundItemGraphic   GetBackgroundItemGraphic () const;

    BACKGROUND_ITEM_ID  GetBackgroundItemId () const;
    UInt16              GetBitmapResourceId () const;

    Gdiplus::Rect   GetScreenRect () const;
    Int32           GetScreenXLeft () const;
    Int32           GetScreenYTop () const;
    Int32           GetScreenXRight () const;
    Int32           GetScreenYBottom () const;
    Int32           GetScreenWidth () const;
    Int32           GetScreenHeight () const;

    FolioStatus QueryDrawingElements (FolioHandle                               dcHandle,
                                      Folio::Core::Game::DrawingElementsList    &drawingElementsList);

private:
    BACKGROUND_ITEM_ID  m_backgroundItemId; // The identifier of the background item.
    Int32               m_screenXLeft;      // The screen X left (in pixels) of the background item.
    Int32               m_screenYTop;       // The screen Y bottom (in pixels) of the background item.

    BackgroundItemGraphic                   m_backgroundItemGraphic;    // The background item's graphic.
    Folio::Core::Game::DrawingElementsList  m_drawingElementsList;      // The background item's drawing elements.
}; // Endclass.

// Background items list.
typedef std::vector<BackgroundItem> BackgroundItemsList;
             
} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
