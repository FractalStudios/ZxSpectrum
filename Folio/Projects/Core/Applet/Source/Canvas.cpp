// STL includes.
#include    <algorithm>
#include    <iterator>

// "Home-made" includes.
#include    <Trace.h>
#include    "Canvas.h"
#include    "AppletWnd.h"

namespace Folio
{

namespace Core
{

namespace Applet
{

/**
 * The default class constructor.
 */
Canvas::Canvas (Int32   maxScreenXPixels,
                Int32   maxScreenYPixels,
                UInt32  screenScale)
:   m_maxScreenXPixels(maxScreenXPixels),
    m_maxScreenYPixels(maxScreenYPixels),
    m_screenScale(screenScale),
    m_appletWnd(Folio::Core::Applet::AppletWnd::GetInstance ()),
    m_redrawRqd(false)
{
    // Create the canvas bitmap.

    m_gdiBitmap.Create (m_appletWnd->GetAppletWndDCHandle (), 
                        Gdiplus::Rect(0, 0, maxScreenXPixels * screenScale, maxScreenYPixels * screenScale));
} // Endproc.


/**
 * The class destructor.
 */
Canvas::~Canvas ()
{
    // Release the applet window instance.

    m_appletWnd->ReleaseInstance ();
} // Endproc.


/**
 * Method that is used to get the applet instance handle.
 *
 * @return
 * The applet instance handle.
 */
FolioHandle Canvas::GetAppletInstanceHandle () const
{
    return (m_appletWnd->GetAppletInstanceHandle ());
} // Endproc.


/**
 * Method that is used to get the canvas screen rect.
 *
 * @return
 * The canvas screen rect.
 */
Gdiplus::Rect   Canvas::GetCanvasScreenRect () const
{
    return (Gdiplus::Rect(0, 0, m_maxScreenXPixels, m_maxScreenYPixels));
} // Endproc.


/**
 * Method that is used to get the canvas window handle.
 *
 * @return
 * The canvas window handle.
 */
FolioHandle Canvas::GetCanvasWndHandle () const
{
    // The applet window handle is the canvas window handle.

    return (m_appletWnd->GetAppletWndHandle ());
} // Endproc.


/**
 * Method that is used to get the canvas device context handle.
 *
 * @return
 * The canvas device context handle.
 */
FolioHandle Canvas::GetCanvasDcHandle () const
{
    // The bitmap device context handle is the canvas device context handle.

    return (m_gdiBitmap.GetBitmapDcHandle ());
} // Endproc.


/**
 * Method that is used to get the canvas graphics object.
 *
 * @return
 * The canvas graphics object.
 */
Gdiplus::Graphics*  Canvas::GetCanvasGraphics () const
{
    // The bitmap graphics object is the canvas graphics object.

    return (m_gdiBitmap.GetBitmapGraphics ());
} // Endproc.


/**
 * Method that is used to get the canvas gamepad object.
 *
 * @return
 * The canvas gamepad object.
 */
Folio::Core::Game::Gamepad* Canvas::GetCanvasGamepad () const
{
    return (m_appletWnd->GetAppletWndGamepad ());
} // Endproc.


/**
 * Method that is used to get the default canvas background colour.
 *
 * @return
 * The default canvas background colour.
 */
Gdiplus::Color  Canvas::GetDefaultCanvasBackgroundColour () const
{
    // The applet window background colour is the default canvas background 
    // colour.

    return (m_appletWnd->GetAppletWndBackgroundColour ());
} // Endproc.


/**
 * Method that is used to set the canvas clipping region.
 *
 * @param [in] clippingRegion
 * The clipping region to be set.
 *
 * @param [out] clippingRegionHandle
 * On return, will hold the clipping region handle, if successful. If this 
 * method fails then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Canvas::SetClippingRegion (const Gdiplus::Region&   clippingRegion,
                                       FolioHandle&             clippingRegionHandle)
{
    // Get the bitmap graphics object.

    Gdiplus::Graphics*  graphics = m_gdiBitmap.GetBitmapGraphics ();

    // Set the clipping region.

    FolioStatus status = Folio::Core::Graphic::Gdi::SetClippingRegion (*graphics, 
                                                                       clippingRegion, 
                                                                       Gdiplus::CombineModeReplace);

    if (status == ERR_SUCCESS)
    {
        status = Folio::Core::Graphic::Gdi::QueryClippingRegionHandle (*graphics,
                                                                       clippingRegionHandle);

        if (status == ERR_SUCCESS)
        {
            // Get the graphics device context.
         
            HDC graphicsDcHandle = graphics->GetHDC ();
            
            // Select the clipping region into the graphics device context.
    
            status = Folio::Core::Util::Gdi::SelectClippingRegion (graphicsDcHandle, 
                                                                   clippingRegionHandle);
    
            // Release the graphics device context.
    
            graphics->ReleaseHDC (graphicsDcHandle);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that is used to reset the canvas clipping region.
 *
 * @param [in] clippingRegionHandle
 * The clipping region handle.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Canvas::ResetClippingRegion (FolioHandle clippingRegionHandle)
{
    // Destroy the clipping region.

    FolioStatus status = Folio::Core::Util::Gdi::DestroyClippingRegion (clippingRegionHandle);

    if (status == ERR_SUCCESS)
    {
        // Get the bitmap graphics object.
    
        Gdiplus::Graphics*  graphics = m_gdiBitmap.GetBitmapGraphics ();

        // Get the graphics device context.
     
        HDC graphicsDcHandle = graphics->GetHDC ();
            
        // Remove the clipping region from the graphics device context.
    
        status = Folio::Core::Util::Gdi::SelectClippingRegion (graphicsDcHandle, 0); 

        // Release the graphics device context.
    
        graphics->ReleaseHDC (graphicsDcHandle);
    
        if (status == ERR_SUCCESS)
        {
            // Reset the clipping region.
    
            status = Folio::Core::Graphic::Gdi::ResetClippingRegion (*graphics);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that is used to fill the canvas background.
 *
 * @param [in] brush
 * The brush to use to fill the canvas background.
 *
 * @param [in] drawCanvas
 * Indicates if the canvas should be drawn to the applet window if the canvas 
 * background is filled successfully.
 *
 * @param [in] clippingRegion
 * The clipping region to be used when filling the canvas background. May be 
 * zero if the clipping region is infinite.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Canvas::FillCanvasBackground (const Gdiplus::Brush&     brush,
                                          bool                      drawCanvas,
                                          const Gdiplus::Region*    clippingRegion)
{
    FolioStatus status = ERR_SUCCESS;

    // Is a clipping region required?

    FolioHandle clippingRegionHandle = FOLIO_INVALID_HANDLE;   // Initialise!

    if (clippingRegion)
    {
        // Yes. Set the clipping region.

        status = SetClippingRegion (*clippingRegion, clippingRegionHandle);
    } // Endif.

    if (status == ERR_SUCCESS)
    {
        // Get the bitmap graphics object.

        Gdiplus::Graphics*  graphics = m_gdiBitmap.GetBitmapGraphics ();

        // Fill the background rect.
    
        status = Folio::Core::Graphic::Gdi::FillRectangle (*graphics,
                                                           m_gdiBitmap.GetBitmapRect (),
                                                           brush);

        // Reset clipping region?

        if (clippingRegion)
        {
            // Yes. Reset the clipping region.

            ResetClippingRegion (clippingRegionHandle);
        } // Endif.
    
        if (status == ERR_SUCCESS)
        {
            // Should we draw the canvas?
    
            if (drawCanvas)
            {
                // Yes. Draw the canvas.
    
                status = DrawCanvas ();
            } // Endif.

            else
            {
                // No. We require a redraw.

                m_redrawRqd = true;
            } // Endelse.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that is used to draw the specified drawing element.
 *
 * @param [in] drawingElement
 * The drawing elemens to draw.
 *
 * @param [in] drawCanvas
 * Indicates if the canvas should be drawn to the applet window if the canvas 
 * background is filled successfully.
 *
 * @param [in] clippingRegion
 * The clipping region to be used when drawing the drawing elements. May be 
 * zero if the clipping region is infinite.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Canvas::DrawDrawingElement (const Folio::Core::Game::DrawingElement&    drawingElement,
                                        bool                                        drawCanvas,
                                        const Gdiplus::Region*                      clippingRegion)
{
    FolioStatus status = ERR_SUCCESS;

    // Is a clipping region required?

    FolioHandle clippingRegionHandle = FOLIO_INVALID_HANDLE;   // Initialise!

    if (clippingRegion)
    {
        // Yes. Set the clipping region.

        status = SetClippingRegion (*clippingRegion, clippingRegionHandle);
    } // Endif.

    if (status == ERR_SUCCESS)
    {
        // Get the bitmap graphics object.
    
        Gdiplus::Graphics*  graphics = m_gdiBitmap.GetBitmapGraphics ();
    
        // Draw the drawing element into the bitmap graphics object.
        
        status = const_cast<Folio::Core::Game::DrawingElement *> (&(drawingElement))->Draw (*graphics);
        
        // Reset clipping region?
    
        if (clippingRegion)
        {
            // Yes. Reset the clipping region.
    
            status = ResetClippingRegion (clippingRegionHandle);
        } // Endif.

        if (status == ERR_SUCCESS)
        {
            // Should we draw the canvas?
    
            if (drawCanvas)
            {
                // Yes. Draw the canvas.
    
                status = DrawCanvas ();
            } // Endif.

            else
            {
                // No. We require a redraw.

                m_redrawRqd = true;
            } // Endelse.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that is used to draw the specified drawing elements.
 *
 * @param [in] drawingElementsList
 * The drawing elements to draw.
 *
 * @param [in] drawCanvas
 * Indicates if the canvas should be drawn to the applet window if the canvas 
 * background is filled successfully.
 *
 * @param [in] clippingRegion
 * The clipping region to be used when drawing the drawing elements. May be 
 * zero if the clipping region is infinite.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Canvas::DrawDrawingElements (const Folio::Core::Game::DrawingElementsList&  drawingElementsList,
                                         bool                                           drawCanvas,
                                         const Gdiplus::Region*                         clippingRegion)
{
    FolioStatus status = ERR_SUCCESS;

    // Is a clipping region required?

    FolioHandle clippingRegionHandle = FOLIO_INVALID_HANDLE;   // Initialise!

    if (clippingRegion)
    {
        // Yes. Set the clipping region.

        status = SetClippingRegion (*clippingRegion, clippingRegionHandle);
    } // Endif.

    if (status == ERR_SUCCESS)
    {
        // Get the bitmap graphics object.
    
        Gdiplus::Graphics*  graphics = m_gdiBitmap.GetBitmapGraphics ();
    
        // Draw the drawing elements into the bitmap graphics object.
        
        Folio::Core::Game::DrawingElementsList::const_iterator  itrEnd = drawingElementsList.end ();
        
        for (Folio::Core::Game::DrawingElementsList::const_iterator itr = drawingElementsList.begin ();
             (status == ERR_SUCCESS) && (itr != itrEnd);
             ++itr)
        {
            status = const_cast<Folio::Core::Game::DrawingElement *> (&(*itr))->Draw (*graphics);
        } // Endfor.
        
        // Reset clipping region?
    
        if (clippingRegion)
        {
            // Yes. Reset the clipping region.
    
            status = ResetClippingRegion (clippingRegionHandle);
        } // Endif.

        if (status == ERR_SUCCESS)
        {
            // Should we draw the canvas?
    
            if (drawCanvas)
            {
                // Yes. Draw the canvas.
    
                status = DrawCanvas ();
            } // Endif.

            else
            {
                // No. We require a redraw.

                m_redrawRqd = true;
            } // Endelse.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that will set that the canvas needs to be redrawn.
 */
void    Canvas::SetRedrawRqd ()
{
    m_redrawRqd = true;
} // Endproc.


/**
 * Method that will indicate if the canvas needs to be redrawn.
 *
 * @return
 * <b>true</b> if the canvas needs to be redrawn, <b>false</b> otherwise.
 */
bool    Canvas::IsRedrawRqd ()
{
    return (m_redrawRqd);
} // Endproc.


/**
 * Method that is used to clear the canvas rectangle of the specified screen rect.
 *
 * @param [in] screenRect
 * The screen rect to clear.
 *
 * @param [in] drawCanvas
 * Indicates if the canvas should be drawn to the applet window.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Canvas::ClearCanvasRectangle (const Gdiplus::Rect&  screenRect,
                                          bool                  drawCanvas)
{
    // Copy the screen rect.

    Gdiplus::Rect   rect(screenRect);

    // Scale it.

    rect.X      *= m_screenScale;
    rect.Y      *= m_screenScale;
    rect.Width  *= m_screenScale;
    rect.Height *= m_screenScale;

    // Fill the rect.

    FolioStatus status = Folio::Core::Graphic::Gdi::FillRectangle (*m_gdiBitmap.GetBitmapGraphics (), 
                                                                   rect, 
                                                                   Gdiplus::SolidBrush(m_appletWnd->GetAppletWndBackgroundColour ()));

    if (status == ERR_SUCCESS)
    {
        // Should we draw the canvas?

        if (drawCanvas)
        {
            // Yes. Draw the canvas.
    
            status = DrawCanvas ();
        } // Endif.

        else
        {
            // No. We require a redraw.

            m_redrawRqd = true;
        } // Endelse.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that is used to clear the canvas.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Canvas::ClearCanvas ()
{
    return (m_gdiBitmap.Clear ());
} // Endproc.


/**
 * Method that is used to draw the canvas into the applet window.
 *
 * @param [in] drawAlways
 * Indicates if the canvas should be always drawn.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Canvas::DrawCanvas (bool drawAlways)
{
    FolioStatus status = ERR_SUCCESS;

    // Only draw the canvas if we should always draw it or it requires redraw.

    if (drawAlways || m_redrawRqd)
    {
        // Draw the whole bitmap into the applet window.

        status = m_gdiBitmap.Draw (*(m_appletWnd->GetAppletWndGraphics ()), 
                                   m_appletWnd->GetAppletWndRect ());

        if (m_redrawRqd && (status == ERR_SUCCESS))
        {
            // Refresh is no longer required.

            m_redrawRqd = false; 
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that is used to paint the canvas into the applet window.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Canvas::PaintCanvas ()
{
    // Get the applet window handle.

    FolioHandle wndHandle = m_appletWnd->GetAppletWndHandle ();

    // Begin the paint.

    PAINTSTRUCT ps;

    ::BeginPaint (reinterpret_cast<HWND> (wndHandle), &(ps));

    // Draw the whole bitmap into the applet window.

    FolioStatus status = m_gdiBitmap.Draw (*(m_appletWnd->GetAppletWndGraphics ()), 
                                           m_appletWnd->GetAppletWndRect ());

    // End the paint.

    ::EndPaint (reinterpret_cast<HWND> (wndHandle), &(ps));

    return (status);
} // Endproc.


/**
 * Method that is used to resize the canvas in the applet window.
 *
 * @param [in] resizeType
 * The resize type.
 *
 * @param [in] clientAreaWidth
 * The client area width.
 *
 * @param [in] clientAreaHeight
 * The client area height.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Canvas::ResizeCanvas (UInt32    resizeType,
                                  Int32     clientAreaWidth,
                                  Int32     clientAreaHeight)
{
    // Draw the whole bitmap into the applet window.

    FolioStatus status = m_gdiBitmap.Draw (*(m_appletWnd->GetAppletWndGraphics ()), 
                                           m_appletWnd->GetAppletWndRect ());

    if (status == ERR_SUCCESS)
    {
        // Invalidate the applet window client rect.

        status = Folio::Core::Util::Wnd::InvalidateClientRect (m_appletWnd->GetAppletWndHandle ());
    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that is used to save the canvas in the applet window.
 *
 * @param [in] fileName
 * The file name to save.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Canvas::SaveCanvas (const FolioString& fileName)
{
    // Save the whole bitmap from the applet window.

    return (m_gdiBitmap.Save (*(m_appletWnd->GetAppletWndGraphics ()), fileName)); 
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
