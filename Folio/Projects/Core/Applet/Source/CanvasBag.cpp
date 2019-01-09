// STL includes.
#include    <algorithm>
#include    <iterator>

// "Home-made" includes.
#include    <Trace.h>
#include    "CanvasBag.h"
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
CanvasBag::CanvasBag (Int32     maxScreenXPixels,
                      Int32     maxScreenYPixels,
                      UInt32    screenScale)
:   m_maxScreenXPixels(maxScreenXPixels),
    m_maxScreenYPixels(maxScreenYPixels),
    m_screenScale(screenScale),
    m_appletWnd(Folio::Core::Applet::AppletWnd::GetInstance ()),
    m_drawingElementsAltered(false),
    m_redrawRqd(false)
{
    // Create the canvas bitmap.

    m_gdiBitmap.Create (m_appletWnd->GetAppletWndDCHandle (), 
                        Gdiplus::Rect(0, 0, maxScreenXPixels * screenScale, maxScreenYPixels * screenScale));

    // Set the screen top-left of the bitmap.

    m_gdiBitmap.SetScreenTopLeft (0, 0);
} // Endproc.


/**
 * The class destructor.
 */
CanvasBag::~CanvasBag ()
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
FolioHandle CanvasBag::GetAppletInstanceHandle () const
{
    return (m_appletWnd->GetAppletInstanceHandle ());
} // Endproc.


/**
 * Method that is used to get the canvas screen rect.
 *
 * @return
 * The canvas screen rect.
 */
Gdiplus::Rect   CanvasBag::GetCanvasScreenRect () const
{
    return (Gdiplus::Rect(0, 0, m_maxScreenXPixels, m_maxScreenYPixels));
} // Endproc.


/**
 * Method that is used to get the canvas window handle.
 *
 * @return
 * The canvas window handle.
 */
FolioHandle CanvasBag::GetCanvasWndHandle () const
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
FolioHandle CanvasBag::GetCanvasDcHandle () const
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
Gdiplus::Graphics*  CanvasBag::GetCanvasGraphics () const
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
Folio::Core::Game::Gamepad* CanvasBag::GetCanvasGamepad () const
{
    return (m_appletWnd->GetAppletWndGamepad ());
} // Endproc.


/**
 * Method that is used to get the default canvas background colour.
 *
 * @return
 * The default canvas background colour.
 */
Gdiplus::Color  CanvasBag::GetDefaultCanvasBackgroundColour () const
{
    // The applet window background colour is the default canvas background 
    // colour.

    return (m_appletWnd->GetAppletWndBackgroundColour ());
} // Endproc.


/**
 * Method that is used to lock the canvas bag.
 */
void    CanvasBag::Lock ()
{
    m_lock.Lock ();
} // Endproc.


/**
 * Method that is used to unlock the canvas bag.
 */
void    CanvasBag::Unlock ()
{
    m_lock.Unlock ();
} // Endproc.


/**
 * Method that is used to fill the canvas background.
 *
 * @param [in] brush
 * The brush to use to fill the canvas background.
 *
 * @param [in] drawCanvasBag
 * Indicates if the canvas bag should be drawn to the applet window if the canvas 
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
FolioStatus CanvasBag::FillCanvasBackground (const Gdiplus::Brush&  brush,
                                             bool                   drawCanvasBag,
                                             const Gdiplus::Region* clippingRegion)
{
    FolioStatus status = ERR_SUCCESS;

    // Support multi-threaded synchronization.

    SingleThreadAccess  singleThreadAccess(m_lock);

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
            // Should we draw the canvas bag?
    
            if (drawCanvasBag)
            {
                // Yes. Draw the canvas bag.
    
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
 * Method that is used to set the canvas bag clipping region.
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
FolioStatus CanvasBag::SetClippingRegion (const Gdiplus::Region&    clippingRegion,
                                          FolioHandle&              clippingRegionHandle)
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
 * Method that is used to reset the canvas bag clipping region.
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
FolioStatus CanvasBag::ResetClippingRegion (FolioHandle clippingRegionHandle)
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
 * Method that is used to add the specified drawing elements to the canvas bag. 
 *
 * @param [in] drawingElementsList
 * The drawing elements to add.
 *
 * @param [in]  drawIntoCanvasBag
 * Indicates if the drawing elements should be drawn into the canvas bag if the 
 * drawing elements are added successfully.
 *
 * @param [in] clippingRegion
 * The clipping region to be used when drawing the drawing elements - if
 * <i>drawIntoCanvasBag</i> is <b>true</b> and the drawing elements are added 
 * successfully. May be zero if the clipping region is infinite.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_ALREADY_EXISTS</b> if at least one of the drawing elements has 
 *     previously been added to the canvas bag. None of the drawing elements 
 *     will be added the canvas bag.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus CanvasBag::AddDrawingElements (const Folio::Core::Game::DrawingElementsList&    drawingElementsList,
                                           bool                                             drawIntoCanvasBag,
                                           const Gdiplus::Region*                           clippingRegion)
{
    FolioStatus status = ERR_SUCCESS;

    // Support multi-threaded synchronization.

    SingleThreadAccess  singleThreadAccess(m_lock);

    // Make sure that all the drawing elements are not in the canvas bag.

    if (VerifyDrawingElements (drawingElementsList))
    {
        status = ERR_ALREADY_EXISTS;
    } // Endif.

    else
    {
        // Add each drawing element.
    
        Folio::Core::Game::DrawingElementsList::const_iterator  itrEnd = drawingElementsList.end ();
    
        for (Folio::Core::Game::DrawingElementsList::const_iterator itr = drawingElementsList.begin ();
             (status == ERR_SUCCESS) && (itr != itrEnd);
             ++itr)
        {
            status = AddDrawingElement (*itr);
        } // Endfor.

        // Should we draw the drawing elements into the canvas bag?

        if (drawIntoCanvasBag && (status == ERR_SUCCESS))
        {
            // Yes. Draw the drawing elements into the canvas bag.

            status = Draw (drawingElementsList, clippingRegion);
        } // Endif.

    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to remove the specified drawing elements from the canvas 
 * bag. 
 *
 * @param [in] drawingElementsList
 * The drawing elements to remove.
 *
 * @param [in] clearDrawingElementRect
 * Indicates if each drawing element's rect should be cleared.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_NOT_FOUND</b> if at least one of the drawing element is not found 
 *     in the canvas bag. None of the drawing elements will be removed from the 
 *     canvas bag.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus CanvasBag::RemoveDrawingElements (const Folio::Core::Game::DrawingElementsList& drawingElementsList,
                                              bool                                          clearDrawingElementRect)
{
    FolioStatus status = ERR_SUCCESS;

    // Support multi-threaded synchronization.

    SingleThreadAccess  singleThreadAccess(m_lock);

    // Make sure that all the drawing elements are in the canvas bag.

    if (VerifyDrawingElements (drawingElementsList))
    {
        // Remove each drawing element.

        Folio::Core::Game::DrawingElementsList::const_iterator  itrEnd = drawingElementsList.end ();

        for (Folio::Core::Game::DrawingElementsList::const_iterator itr = drawingElementsList.begin ();
             (status == ERR_SUCCESS) && (itr != itrEnd);
             ++itr)
        {
            status = RemoveDrawingElement (*itr, clearDrawingElementRect);
        } // Endfor.

    } // Endif.

    else
    {
        status = ERR_NOT_FOUND;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to add a drawing element to the canvas bag.
 *
 * @param [in] drawingElement
 * The drawing element to add.
 *
 * @param [in] drawIntoCanvasBag
 * Indicates if the drawing element should be drawn into the canvas bag if the 
 * drawing element is added successfully.
 *
 * @param [in] clippingRegion
 * The clipping region to be used when drawing the drawing element - if
 * <i>drawIntoCanvasBag</i> is <b>true</b> and the drawing element is added 
 * successfully. May be zero if the clipping region is infinite.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_ALREADY_EXISTS</b> if the drawing element has previously been 
 *     added to the canvas bag.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus CanvasBag::AddDrawingElement (const Folio::Core::Game::DrawingElement&  drawingElement,
                                          bool                                      drawIntoCanvasBag,
                                          const Gdiplus::Region*                    clippingRegion)
{
    FolioStatus status = ERR_SUCCESS;

    // Support multi-threaded synchronization.

    SingleThreadAccess  singleThreadAccess(m_lock);

    // Is the drawing element already in the canvas bag?

    if (FindDrawingElement (drawingElement))
    {
        // Yes.

        status = ERR_ALREADY_EXISTS;
    } // Endif.

    else
    {
        // No. Add the drawing element to the canvas bag.

        m_drawingElements.insert (drawingElement);
        m_drawingElementsAltered = true;

        // Should we draw the drawing element into the canvas bag?

        if (drawIntoCanvasBag && (status == ERR_SUCCESS))
        {
            // Yes. Draw the drawing element into the canvas bag.

            status = Draw (Folio::Core::Game::DrawingElementsList(1, drawingElement), 
                           clippingRegion);
        } // Endif.

    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to remove a drawing element from the canvas bag.
 *
 * @param [in] drawingElement
 * The drawing element to remove.
 *
 * @param [in] clearDrawingElementRect
 * Indicates if the drawing element rect should be cleared.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_NOT_FOUND</b> if the drawing element is not found in the canvas 
 *     bag.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus CanvasBag::RemoveDrawingElement (const Folio::Core::Game::DrawingElement&   drawingElement,
                                             bool                                       clearDrawingElementRect)
{
    FolioStatus status = ERR_SUCCESS;

    // Support multi-threaded synchronization.

    SingleThreadAccess  singleThreadAccess(m_lock);

    // Is the drawing element in the canvas bag?

    Folio::Core::Game::DrawingElementsSet::iterator itr;

    if (FindDrawingElement (drawingElement, &(itr)))
    {
        // Yes. Clear the drawing element's rect?

        if (clearDrawingElementRect)
        {
            // Yes. Clear the rect occupied by the drawing element.

            status = ClearCanvasRectangle (drawingElement.GetScreenRect ());
        } // Endif.

        if (status == ERR_SUCCESS)
        {
            // Remove the drawing element from the canvas bag.

            m_drawingElements.erase (itr);
            m_drawingElementsAltered = true;
        } // Endif.

    } // Endif.

    else
    {
        // No.

        status = ERR_NOT_FOUND;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to draw all the drawing elements in the canvas bag.
 *
 * @param [in] drawCanvasBag
 * Indicates if the the canvas bag should be drawn to the applet window.
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
FolioStatus CanvasBag::DrawAllDrawingElements (bool                     drawCanvasBag,
                                               const Gdiplus::Region*   clippingRegion)
{
    // Support multi-threaded synchronization.

    SingleThreadAccess  singleThreadAccess(m_lock);

    // Draw all the drawing elements in the canvas bag.

    Folio::Core::Game::DrawingElementsList  drawingElementsList;

    std::copy (m_drawingElements.begin (), 
               m_drawingElements.end (), 
               std::back_inserter (drawingElementsList));

    return (Draw (drawingElementsList, clippingRegion, drawCanvasBag));
} // Endproc.


/**
 * Method that is used to draw the specified drawing elements in the canvas 
 * bag.
 *
 * @param [in] drawingElementsList
 * The drawing elements to draw.
 *
 * @param [in] drawCanvasBag
 * Indicates if the the canvas bag should be drawn to the applet window.
 *
 * @param [in] clippingRegion
 * The clipping region to be used when drawing the drawing elements. May be 
 * zero if the clipping region is infinite.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if at least one of the drawing elements has 
 *     not been added to the canvas bag.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus CanvasBag::DrawDrawingElements (const Folio::Core::Game::DrawingElementsList&   drawingElementsList,
                                            bool                                            drawCanvasBag,
                                            const Gdiplus::Region*                          clippingRegion)
{
    FolioStatus status = ERR_SUCCESS;
    
    // Support multi-threaded synchronization.

    SingleThreadAccess  singleThreadAccess(m_lock);

    // Make sure that all the drawing elements are in the canvas bag.

    if (VerifyDrawingElements (drawingElementsList))
    {
        // Draw the drawing elements.

        status = Draw (drawingElementsList, clippingRegion, drawCanvasBag);
    } // Endif.

    else
    {
        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to draw the specified drawing element in the canvas 
 * bag.
 *
 * @param [in] drawingElement
 * The drawing element to draw.
 *
 * @param [in] drawCanvasBag
 * Indicates if the the canvas bag should be drawn to the applet window.
 *
 * @param [in] clippingRegion
 * The clipping region to be used when drawing the drawing elements. May be 
 * zero if the clipping region is infinite.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if at least one of the drawing elements has 
 *     not been added to the canvas bag.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus CanvasBag::DrawDrawingElement (const Folio::Core::Game::DrawingElement& drawingElement,
                                           bool                                     drawCanvasBag,
                                           const Gdiplus::Region*                   clippingRegion)
{
    FolioStatus status = ERR_SUCCESS;
    
    // Support multi-threaded synchronization.

    SingleThreadAccess  singleThreadAccess(m_lock);

    // Is the drawing element in the canvas bag?

    if (FindDrawingElement (drawingElement))
    {
        // Yes. Draw the drawing element.

        status = Draw (Folio::Core::Game::DrawingElementsList(1, drawingElement), 
                       clippingRegion, 
                       drawCanvasBag);
    } // Endif.

    else
    {
        // No.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will set that the canvas bag needs to be redrawn.
 */
void    CanvasBag::SetRedrawRqd ()
{
    m_redrawRqd = true;
} // Endproc.


/**
 * Method that will indicate if the canvas bag needs to be redrawn.
 *
 * @return
 * <b>true</b> if the canvas bag needs to be redrawn, <b>false</b> otherwise.
 */
bool    CanvasBag::IsRedrawRqd ()
{
    return (m_redrawRqd);
} // Endproc.


/**
 * Method that is used to clear the canvas rectangle of the specified screen rect.
 *
 * @param [in] screenRect
 * The screen rect to clear.
 *
 * @param [in] drawCanvasBag
 * Indicates if the the canvas bag should be drawn to the applet window.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus CanvasBag::ClearCanvasRectangle (const Gdiplus::Rect&   screenRect,
                                             bool                   drawCanvasBag)
{
    // Support multi-threaded synchronization.

    SingleThreadAccess  singleThreadAccess(m_lock);

    // Copy the screen rect.

    Gdiplus::Rect   rect(screenRect);

    // Scale it.

    rect.X      *= m_screenScale;
    rect.Y      *= m_screenScale;
    rect.Width  *= m_screenScale;
    rect.Height *= m_screenScale;

    return (ClearRects (Folio::Core::Graphic::AGdiGraphicElement::RectList(1, rect), 
                        drawCanvasBag));
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
FolioStatus CanvasBag::ClearCanvas ()
{
    // Support multi-threaded synchronization.

    SingleThreadAccess  singleThreadAccess(m_lock);

    // Remove the drawing elements from the canvas bag.

    m_drawingElements.clear ();
    m_drawingElementsAltered = false;

    // Remove the rects to be drawn.

    m_rectsToDraw.clear ();

    // Redraw is no longer required.

    m_redrawRqd = false;

    return (ERR_SUCCESS);
} // Endproc.


/**
 * Method that is used to draw the canvas bag into the applet window.
 *
 * @param [in] drawAlways
 * Indicates if the canvas bag should be always drawn.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus CanvasBag::DrawCanvas (bool drawAlways)
{
    FolioStatus status = ERR_SUCCESS;

    // Support multi-threaded synchronization.

    SingleThreadAccess  singleThreadAccess(m_lock);

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
 * Method that is used to paint the canvas bag into the applet window.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus CanvasBag::PaintCanvas ()
{
    // Support multi-threaded synchronization.

    SingleThreadAccess  singleThreadAccess(m_lock);

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
 * Method that is used to resize the canvas bag in the applet window.
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
FolioStatus CanvasBag::ResizeCanvas (UInt32 resizeType,
                                     Int32  clientAreaWidth,
                                     Int32  clientAreaHeight)
{
    // Support multi-threaded synchronization.

    SingleThreadAccess  singleThreadAccess(m_lock);

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
 * Method that is used to draw the specified drawing elements.
 *
 * @param [in] drawingElementsList
 * The drawing elements to draw.
 *
 * @param [in] clippingRegion
 * The clipping region to be used when drawing the drawing elements. May be 
 * zero if the clipping region is infinite.
 *
 * @param [in] drawCanvasBag
 * Indicates if the canvas bag should be drawn to the applet window.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus CanvasBag::Draw (const Folio::Core::Game::DrawingElementsList&  drawingElementsList,
                             const Gdiplus::Region*                         clippingRegion,
                             bool                                           drawCanvasBag)
{
    FolioStatus status = ERR_SUCCESS;

    Folio::Core::Graphic::AGdiGraphicElement::RectList  dirtyRects;

    // We only need to draw the drawing elements into our bitmap graphics 
    // object if the drawing elements have been altered.

    if (m_drawingElementsAltered)
    {
        // Is a clipping region required?

        FolioHandle clippingRegionHandle = FOLIO_INVALID_HANDLE;   // Initialise!

        if (clippingRegion)
        {
            // Yes. Set the clipping region.

            status = SetClippingRegion (*clippingRegion, clippingRegionHandle);
        } // Endif.

        if (status == ERR_SUCCESS)
        {
            // Get the bitmap graphics object to draw into.
    
            Gdiplus::Graphics*  graphics = m_gdiBitmap.GetBitmapGraphics ();
    
            // Draw the drawing elements into the bitmap graphics object.
        
            Folio::Core::Game::DrawingElementsList::const_iterator  itrEnd = drawingElementsList.end ();
        
            for (Folio::Core::Game::DrawingElementsList::const_iterator itr = drawingElementsList.begin ();
                 (status == ERR_SUCCESS) && (itr != itrEnd);
                 ++itr)
            {
                status = const_cast<Folio::Core::Game::DrawingElement *> (&(*itr))->Draw (*graphics, &(dirtyRects));
            } // Endfor.
        
            // If we successully drew the bitmap then the graphics elements are no 
            // longer altered.

            if (status == ERR_SUCCESS)
            {
                m_drawingElementsAltered = false;
            } // Endif.

            // Reset clipping region?
    
            if (clippingRegion)
            {
                // Yes. Reset the clipping region.
    
                status = ResetClippingRegion (clippingRegionHandle);
            } // Endif.

        } // Endif.

    } // Endif.

    if (status == ERR_SUCCESS)
    {
        // Should we draw the canvas bag?

        if (drawCanvasBag)
        {
            // Yes. Merge any dirty rects.

            MergeRects (dirtyRects);

            // Draw the dirty rects of the bitmap into the applet window.
        
            status = DrawRects (dirtyRects);
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
 * Method that is used to draw the specified rects.
 *
 * @param [in] rects
 * The rects to draw.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus CanvasBag::DrawRects (const Folio::Core::Graphic::AGdiGraphicElement::RectList& rects)
{
    FolioStatus status = ERR_SUCCESS;

    // Get the applet window graphics object to draw into.

    Gdiplus::Graphics*   graphics = m_appletWnd->GetAppletWndGraphics ();

    // Draw the rects into the applet window.

    Folio::Core::Graphic::AGdiGraphicElement::RectList::const_iterator  itrEnd = rects.end ();

    for (Folio::Core::Graphic::AGdiGraphicElement::RectList::const_iterator itr = rects.begin ();
         (status == ERR_SUCCESS) && (itr != itrEnd);
         ++itr)
    {
        status = m_gdiBitmap.Draw (*graphics, *itr);
    } // Endfor.

    return (status);
} // Endproc.


/**
 * Method that is used to clear the specified rects.
 *
 * @param [in] rects
 * The rects to clear.
 *
 * @param [in] drawCanvasBag
 * Indicates if the canvas bag should be drawn to the applet window.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus CanvasBag::ClearRects (const Folio::Core::Graphic::AGdiGraphicElement::RectList&    rects,
                                   bool                                                         drawCanvasBag)
{
    FolioStatus status = ERR_SUCCESS;

    // Get the bitmap graphics object.

    Gdiplus::Graphics*  graphics = m_gdiBitmap.GetBitmapGraphics ();

    // Get the applet window background colour.

    Gdiplus::Color  colour(m_appletWnd->GetAppletWndBackgroundColour ());

    // Create the solid brush.

    Gdiplus::SolidBrush brush(colour);
    
    // Draw the rects into the bitmap graphics object.

    Folio::Core::Graphic::AGdiGraphicElement::RectList::const_iterator  itrEnd = rects.end ();

    for (Folio::Core::Graphic::AGdiGraphicElement::RectList::const_iterator itr = rects.begin ();
         (status == ERR_SUCCESS) && (itr != itrEnd);
         ++itr)
    {
        // Fill the rect.

        status = Folio::Core::Graphic::Gdi::FillRectangle (*graphics, *itr, brush);
    } // Endfor.

    if (status == ERR_SUCCESS)
    {
        // Should we draw the canvas bag?

        if (drawCanvasBag)
        {
            // Yes. Draw the rects into the applet window.

            status = DrawRects (rects);
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
 * Method that is used to merge the specified rects.
 *
 * @param [in] rects
 * The rects to merge.
 *
 * @return
 * <b>true</b> if at least two of the rects were merged, <b>false</b> otherwise.
 */
bool    CanvasBag::MergeRects (Folio::Core::Graphic::AGdiGraphicElement::RectList& rects)
{
    bool    merged = false; // Initialise!

    // Can only merge the rects if there is more than one to merge.

    if (rects.size () > 1)
    {
        // Merge the rects.

        Gdiplus::Rect   intersectRect;

        Folio::Core::Graphic::AGdiGraphicElement::RectList  mergedRects;

        Folio::Core::Graphic::AGdiGraphicElement::RectList::const_iterator  itrEnd = rects.end ();

        for (Folio::Core::Graphic::AGdiGraphicElement::RectList::const_iterator itr = rects.begin ();
             !merged && (itr != itrEnd);
             ++itr)
        {
            for (Folio::Core::Graphic::AGdiGraphicElement::RectList::const_iterator itrNext = itr + 1;
                 !merged && (itrNext != itrEnd);
                 ++itrNext)
            {
                // Do the rects intersect?
    
                if (DoRectsIntersect (*itr, *itrNext, intersectRect))
                {
                    // Yes. Add the intersect rect to the list of merged rects.
    
                    mergedRects.push_back (intersectRect);
    
                    // Add any of the remaining rects.

                    if ((itr + 1) != itrNext)
                    {
                        mergedRects.insert (mergedRects.end (), itr + 1, itrNext);
                    } // Endif.

                    if ((itrNext + 1) != itrEnd)
                    {
                        mergedRects.insert (mergedRects.end (), itrNext + 1, itrEnd);
                    } // Endif.
    
                    merged = true;

                    // Recurse.

                    MergeRects (mergedRects);
                } // Endif.

            } // Endfor.

            // If the rect was not merged, then add this to our list of merged 
            // rects.

            if (!merged)
            {
                mergedRects.push_back (*itr);
            } // Endelse.

        } // Endfor.

        // If we merged any rects then replace the input rects.

        if (merged)
        {
            rects = mergedRects;
        } // Endif.

    } // Endif.

    return (merged);
} // Endproc.


/**
 * Method that is used to determine if two specified rects intersect.
 *
 * @param [in] firstRect
 * The first rect.
 *
 * @param [in] secondRect
 * The second rect.
 *
 * @param [out] intersectRect
 * On return, will hold the intersect rect, if the two rects intersect. If the 
 * two rects do not intersect then this parameter is undefined.
 *
 * @return
 * <b>true<b> if the rects intersect, <b>false<b> otherwise.
 */
bool    CanvasBag::DoRectsIntersect (const Gdiplus::Rect&   firstRect,
                                     const Gdiplus::Rect&   secondRect,
                                     Gdiplus::Rect&         intersectRect) const
{
    // Do the rectangles intersect?

    bool    rectsIntersect = false; // Assume!

    if (Gdiplus::Rect::Intersect (intersectRect, firstRect, secondRect))
    {
        // Is the intersect rect the same as the first rect?

        if ((intersectRect.X        == firstRect.X)     &&
            (intersectRect.Y        == firstRect.Y)     &&
            (intersectRect.Width    == firstRect.Width) &&
            (intersectRect.Height   == firstRect.Height))
        {
            // Yes. The first rect can be replaced by the second rect.

            intersectRect = secondRect;

            rectsIntersect = true;
        } // Endif.

        // Is the intersect rect the same as the second rect?

        else
        if ((intersectRect.X        == secondRect.X)     &&
            (intersectRect.Y        == secondRect.Y)     &&
            (intersectRect.Width    == secondRect.Width) &&
            (intersectRect.Height   == secondRect.Height))
        {
            // Yes. The second rect can be replaced by the first rect.

            intersectRect = firstRect;

            rectsIntersect = true;
        } // Endelseif.

        else
        {
            Gdiplus::REAL   firstRectArea       = static_cast<Gdiplus::REAL> (firstRect.Width * firstRect.Height);
            Gdiplus::REAL   secondRectArea      = static_cast<Gdiplus::REAL> (secondRect.Width * secondRect.Height);
            Gdiplus::REAL   intersectRectArea   = static_cast<Gdiplus::REAL> (intersectRect.Width * intersectRect.Height);

            if (((firstRectArea >= secondRectArea) &&
                ((intersectRectArea / secondRectArea * 100) > 30)) ||
                ((intersectRectArea / firstRectArea * 100) > 30))
            {
                // Calculate the union.

                Gdiplus::Rect::Union (intersectRect, firstRect, secondRect);

                rectsIntersect = true;
            } // Endif.

        } // Endelse.

    } // Endif.

    return (rectsIntersect);
} // Endproc.


/**
 * Method that is used to verify that the specified drawing elements have been 
 * added to the canvas bag. 
 *
 * @param [in] drawingElementsList
 * The drawing elements to verify.
 *
 * @return
 * <b>true</b> if all the drawing elements have been added to the canvas bag,
 * <b>false</b> otherwise.
 */
bool    CanvasBag::VerifyDrawingElements (const Folio::Core::Game::DrawingElementsList& drawingElementsList)
{
    bool    found = true;   // Assume.

    // Verify each drawing element has been added to the canvas bag.

    Folio::Core::Game::DrawingElementsList::const_iterator  itrEnd = drawingElementsList.end ();

    for (Folio::Core::Game::DrawingElementsList::const_iterator itr = drawingElementsList.begin ();
         found && (itr != itrEnd);
         ++itr)
    {
        found = FindDrawingElement (*itr);
    } // Endfor.

    return (found);
} // Endproc.


/**
 * Method that is used to find a drawing element in the canvas bag.
 *
 * @param [in] drawingElement
 * The drawing element to find.
 *
 * @param [out] itr
 * On return, will hold the iterator to the drawing element in the canvas bag,
 * if found. If not found this parameter is undefined.
 *
 * @return
 * <b>true</b> if the drawing element was found, <b>false</b> otherwise.
 */
bool    CanvasBag::FindDrawingElement (const Folio::Core::Game::DrawingElement&         drawingElement,
                                       Folio::Core::Game::DrawingElementsSet::iterator* itr)
{
    Folio::Core::Game::DrawingElementsSet::iterator itrFound = 
        std::find_if (m_drawingElements.begin (), m_drawingElements.end (),
                      [&drawingElement](const Folio::Core::Game::DrawingElement& arg) 
                      {return (arg.GetGdiGraphicElement () == drawingElement.GetGdiGraphicElement ());});

    bool    found = (itrFound != m_drawingElements.end ());

    if (found && itr)
    {
        *itr = itrFound;
    } // Endif.

    return (found);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
