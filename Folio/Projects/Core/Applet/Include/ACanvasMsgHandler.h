#pragma once

// STL includes.
#include    "memory"

// "Home-made" includes.
#include    "Canvas.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Applet
{

/// The canvas message handler abstract class.
/**
 * This class provides for a canvas message handler. It is used to handle 
 * specific messages received by the applet window.
 *
 * This class does not support copy construction or assignment.
 */
class ACanvasMsgHandler
{
public:
    virtual ~ACanvasMsgHandler ();

    Canvas*             GetCanvas ();
    Gdiplus::Region*    GetClippingRegion ();

    virtual FolioStatus HandleCreateCanvasMsg (FolioHandle  wndHandle,
                                               UInt32       wParam,
                                               UInt32       lParam);
    virtual FolioStatus HandleDestroyCanvasMsg (FolioHandle wndHandle,
                                                UInt32      wParam,
                                                UInt32      lParam);
    virtual FolioStatus HandleSizeMsg (FolioHandle  wndHandle,
                                       UInt32       wParam,
                                       UInt32       lParam);
    virtual FolioStatus HandlePaintCanvasMsg (FolioHandle   wndHandle,
                                              UInt32        wParam,
                                              UInt32        lParam);
    virtual FolioStatus HandleProcessFrame (FolioHandle wndHandle,
                                            UInt32&     frameRateIncrement);

protected:
    std::unique_ptr<Canvas> m_canvas;   ///< The canvas.

    Gdiplus::Region m_clippingRegion;   ///< The clipping region.
    
    ACanvasMsgHandler (Int32    maxScreenXPixels,
                       Int32    maxScreenYPixels,
                       UInt32   screenScale);

private:
    /// Private copy constructor to prevent copying.
    ACanvasMsgHandler (const ACanvasMsgHandler& rhs);

    /// Private assignment operator to prevent copying.
    ACanvasMsgHandler& operator= (const ACanvasMsgHandler& rhs);
}; // Endclass.

/// Factory function that <b>must</b> be implemented by a sub-class of 
/// <b>ACanvasMsgHandler</b>.
ACanvasMsgHandler*  CreateCanvasMsgHandler ();

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
