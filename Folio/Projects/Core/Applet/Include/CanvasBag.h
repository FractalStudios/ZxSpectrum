#pragma once

// STL includes.
#include    <vector>

// "Home-made" includes.
#include    <Game.h>
#include    <Util.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Applet
{

class   AppletWnd;  // Predeclare class.

/// The canvas bag class.
/**
 * This class provides for a canvas bag. It is used to hold a number of drawing 
 * elements. The canvas bag <b>must</b> always be used to draw the drawing 
 * elements to the applet window.
 *
 * This class does not support copy construction or assignment.
 */
class CanvasBag
{
public:
    CanvasBag (Int32    maxScreenXPixels,
               Int32    maxScreenYPixels,
               UInt32   screenScale);
    ~CanvasBag ();

    FolioHandle GetAppletInstanceHandle () const;

    Gdiplus::Rect               GetCanvasScreenRect () const;
    FolioHandle                 GetCanvasWndHandle () const;
    FolioHandle                 GetCanvasDcHandle () const;
    Gdiplus::Graphics*          GetCanvasGraphics () const;
    Folio::Core::Game::Gamepad* GetCanvasGamepad () const;
    
    Gdiplus::Color  GetDefaultCanvasBackgroundColour () const;

    void    Lock ();
    void    Unlock ();

    FolioStatus FillCanvasBackground (const Gdiplus::Brush&     brush,
                                      bool                      drawCanvasBag = false,
                                      const Gdiplus::Region*    clippingRegion = 0);

    FolioStatus SetClippingRegion (const Gdiplus::Region&   clippingRegion,
                                   FolioHandle&             clippingRegionHandle);
    FolioStatus ResetClippingRegion (FolioHandle clippingRegionHandle);

    FolioStatus AddDrawingElements (const Folio::Core::Game::DrawingElementsList&   drawingElementsList, 
                                    bool                                            drawIntoCanvasBag = false,
                                    const Gdiplus::Region*                          clippingRegion = 0);
    FolioStatus RemoveDrawingElements (const Folio::Core::Game::DrawingElementsList&    drawingElementsList,
                                       bool                                             clearDrawingElementRect = false);

    FolioStatus AddDrawingElement (const Folio::Core::Game::DrawingElement& drawingElement,
                                   bool                                     drawIntoCanvasBag = false,
                                   const Gdiplus::Region*                   clippingRegion = 0);
    FolioStatus RemoveDrawingElement (const Folio::Core::Game::DrawingElement&  drawingElement,
                                      bool                                      clearDrawingElementRect = false);

    FolioStatus DrawAllDrawingElements (bool                    drawCanvasBag = false,
                                        const Gdiplus::Region*  clippingRegion = 0);
    FolioStatus DrawDrawingElements (const Folio::Core::Game::DrawingElementsList&  drawingElementsList,
                                     bool                                           drawCanvasBag = false,
                                     const Gdiplus::Region*                         clippingRegion = 0);
    FolioStatus DrawDrawingElement (const Folio::Core::Game::DrawingElement&    drawingElement,
                                    bool                                        drawCanvasBag = false,
                                    const Gdiplus::Region*                      clippingRegion = 0);

    void    SetRedrawRqd ();
    bool    IsRedrawRqd ();

    FolioStatus ClearCanvasRectangle (const Gdiplus::Rect&  screenRect,
                                      bool                  drawCanvasBag = false);
    FolioStatus ClearCanvas ();
    FolioStatus DrawCanvas (bool drawAlways = true);
    FolioStatus PaintCanvas ();
    FolioStatus ResizeCanvas (UInt32    resizeType,
                              Int32     clientAreaWidth,
                              Int32     clientAreaHeight);

private:
    Int32   m_maxScreenXPixels;   // Maximum screen X pixels of the canvas.
    Int32   m_maxScreenYPixels;   // Maximum screen Y pixels of the canvas.
    UInt32  m_screenScale;        // Screen scale of the canvas.
    
    AppletWnd*  m_appletWnd;    ///< The applet window.

    Folio::Core::Graphic::GdiBitmap m_gdiBitmap;    ///< The bitmap to draw into and from.

    Folio::Core::Game::DrawingElementsSet   m_drawingElements;  ///< The drawing elements held within the canvas bag.
    bool    m_drawingElementsAltered;   ///< Indicates if any one of the drawing elements have been altered since the last draw.

    Folio::Core::Graphic::AGdiGraphicElement::RectList  m_rectsToDraw;  ///< Any rects still to be drawn within the canvas bag.

    bool    m_redrawRqd;    ///< Indicates if the canvas bag must be redrawn.

    /// Scope lock for single thread access.
    typedef Folio::Core::Util::ScopedCriticalSection    SingleThreadAccess;
    mutable Folio::Core::Util::CriticalSection  m_lock; ///< The (instance) single thread access lock.

    FolioStatus Draw (const Folio::Core::Game::DrawingElementsList& drawingElementsList, 
                      const Gdiplus::Region*                        clippingRegion,
                      bool                                          drawCanvasBag = false);
    FolioStatus DrawRects (const Folio::Core::Graphic::AGdiGraphicElement::RectList& rects);
    FolioStatus ClearRects (const Folio::Core::Graphic::AGdiGraphicElement::RectList&  rects,
                            bool                                                       drawCanvasBag = false);

    bool    MergeRects (Folio::Core::Graphic::AGdiGraphicElement::RectList& rects);
    bool    DoRectsIntersect (const Gdiplus::Rect&  firstRect,
                              const Gdiplus::Rect&  secondRect,
                              Gdiplus::Rect&        intersectRect) const;

    bool    VerifyDrawingElements (const Folio::Core::Game::DrawingElementsList& drawingElementsList);
    bool    FindDrawingElement (const Folio::Core::Game::DrawingElement&            drawingElement,
                                Folio::Core::Game::DrawingElementsSet::iterator*    itr = 0);

    /// Private copy constructor to prevent copying.
    CanvasBag (const CanvasBag& rhs);

    /// Private assignment operator to prevent copying.
    CanvasBag& operator= (const CanvasBag& rhs);
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
