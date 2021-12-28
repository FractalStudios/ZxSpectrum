#pragma once

// "Home-made" includes.
#include    <Game.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Applet
{

class   AppletWnd;  // Predeclare class.

/// The canvas class.
/**
 * This class provides for a canvas.
 *
 * This class does not support copy construction or assignment.
 */
class Canvas
{
public:
    Canvas (Int32   maxScreenXPixels,
            Int32   maxScreenYPixels,
            UInt32  screenScale);
    ~Canvas ();

    FolioHandle GetAppletInstanceHandle () const;

    Gdiplus::Rect               GetCanvasScreenRect () const;
    FolioHandle                 GetCanvasWndHandle () const;
    FolioHandle                 GetCanvasDcHandle () const;
    Gdiplus::Graphics*          GetCanvasGraphics () const;
    Folio::Core::Game::Gamepad* GetCanvasGamepad () const;
    
    Gdiplus::Color  GetDefaultCanvasBackgroundColour () const;

    FolioStatus SetClippingRegion (const Gdiplus::Region&   clippingRegion,
                                   FolioHandle&             clippingRegionHandle);
    FolioStatus ResetClippingRegion (FolioHandle clippingRegionHandle);

    FolioStatus FillCanvasBackground (const Gdiplus::Brush&     brush,
                                      bool                      drawCanvas = false,
                                      const Gdiplus::Region*    clippingRegion = 0);
    FolioStatus DrawDrawingElement (const Folio::Core::Game::DrawingElement&    drawingElement,
                                    bool                                        drawCanvas = false,
                                    const Gdiplus::Region*                      clippingRegion = 0);
    FolioStatus DrawDrawingElements (const Folio::Core::Game::DrawingElementsList&  drawingElementsList,
                                     bool                                           drawCanvas = false,
                                     const Gdiplus::Region*                         clippingRegion = 0);

    void    SetRedrawRqd ();
    bool    IsRedrawRqd ();

    FolioStatus ClearCanvasRectangle (const Gdiplus::Rect&  screenRect,
                                      bool                  drawCanvas = false);
    FolioStatus ClearCanvas ();
    FolioStatus DrawCanvas (bool drawAlways = true);
    FolioStatus PaintCanvas ();
    FolioStatus ResizeCanvas (UInt32    resizeType,
                              Int32     clientAreaWidth,
                              Int32     clientAreaHeight);
    FolioStatus SaveCanvas (const FolioString& fileName);

private:
    AppletWnd*  m_appletWnd;    ///< The applet window.

    Int32   m_maxScreenXPixels; ///< Maximum screen X pixels of the canvas.
    Int32   m_maxScreenYPixels; ///< Maximum screen Y pixels of the canvas.
    UInt32  m_screenScale;      ///< Screen scale of the canvas.
    bool    m_redrawRqd;        ///< Indicates if the canvas must be redrawn.
    
    Folio::Core::Graphic::GdiBitmap m_gdiBitmap;    ///< The bitmap to draw into and from.

    /// Private copy constructor to prevent copying.
    Canvas (const Canvas& rhs);

    /// Private assignment operator to prevent copying.
    Canvas& operator= (const Canvas& rhs);
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
