// "Home-made" includes.
#include    "ACanvasMsgHandler.h"

namespace Folio
{

namespace Core
{

namespace Applet
{

/**
 * The default class constructor.
 */
ACanvasMsgHandler::ACanvasMsgHandler (Int32     maxScreenXPixels,
                                      Int32     maxScreenYPixels,
                                      UInt32    screenScale)
:   m_canvas(new Canvas(maxScreenXPixels, maxScreenYPixels, screenScale))
{
} // Endproc.


/**
 * The class destructor.
 */
ACanvasMsgHandler::~ACanvasMsgHandler ()
{
} // Endproc.


/**
 * Method that is used to get the canvas of the canvas message handler.
 *
 * @return
 * The canvas of the canvas message handler.
 */
Canvas* ACanvasMsgHandler::GetCanvas ()
{
    return (m_canvas.get ());
} // Endproc.


/**
 * Method that is used to get the clipping region of the canvas message
 * handler.
 *
 * @return
 * The clipping region of the canvas message handler.
 */
Gdiplus::Region*    ACanvasMsgHandler::GetClippingRegion ()
{
    return (&(m_clippingRegion));
} // Endproc.


/**
 * Method that is used to handle a WM_CREATE message received by the applet 
 * window.
 *
 * @param [in] wndHandle
 * The handle of the applet window.
 *
 * @param [in] wParam
 * Contains additional data relevant to the message.
 *
 * @param [in] lParam
 * Contains additional data relevant to the message.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus ACanvasMsgHandler::HandleCreateCanvasMsg (FolioHandle   wndHandle,
                                                      UInt32        wParam,
                                                      UInt32        lParam)
{
    return (ERR_SUCCESS);

    FOLIO_UNREFERENCED(wndHandle);
    FOLIO_UNREFERENCED(wParam);
    FOLIO_UNREFERENCED(lParam);
} // Endproc.


/**
 * Method that is used to handle a WM_DESTROY message received by the applet 
 * window.
 *
 * @param [in] wndHandle
 * The handle of the applet window.
 *
 * @param [in] wParam
 * Contains additional data relevant to the message.
 *
 * @param [in] lParam
 * Contains additional data relevant to the message.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus ACanvasMsgHandler::HandleDestroyCanvasMsg (FolioHandle  wndHandle,
                                                       UInt32       wParam,
                                                       UInt32       lParam)
{
    return (ERR_SUCCESS);

    FOLIO_UNREFERENCED(wndHandle);
    FOLIO_UNREFERENCED(wParam);
    FOLIO_UNREFERENCED(lParam);
} // Endproc.


/**
 * Method that is used to handle a WM_SIZE message received by the applet 
 * window.
 *
 * @param [in] wndHandle
 * The handle of the applet window.
 *
 * @param [in] wParam
 * Contains additional data relevant to the message.
 *
 * @param [in] lParam
 * Contains additional data relevant to the message.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus ACanvasMsgHandler::HandleSizeMsg (FolioHandle   wndHandle,
                                              UInt32        wParam,
                                              UInt32        lParam)
{
    // Resize the canvas.

    return (m_canvas->ResizeCanvas (wParam, LOWORD(lParam), HIWORD(lParam)));

    FOLIO_UNREFERENCED(wndHandle);
    FOLIO_UNREFERENCED(wParam);
    FOLIO_UNREFERENCED(lParam);
} // Endproc.


/**
 * Method that is used to handle a WM_PAINT message received by the applet 
 * window.
 *
 * @param [in] wndHandle
 * The handle of the applet window.
 *
 * @param [in] wParam
 * Contains additional data relevant to the message.
 *
 * @param [in] lParam
 * Contains additional data relevant to the message.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus ACanvasMsgHandler::HandlePaintCanvasMsg (FolioHandle    wndHandle,
                                                     UInt32         wParam,
                                                     UInt32         lParam)
{
    // Paint the canvas.

    return (m_canvas->PaintCanvas ());

    FOLIO_UNREFERENCED(wndHandle);
    FOLIO_UNREFERENCED(wParam);
    FOLIO_UNREFERENCED(lParam);
} // Endproc.


/**
 * Method that is used to process a frame in the applet window.
 *
 * @param [in] wndHandle
 * The handle of the applet window.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus ACanvasMsgHandler::HandleProcessFrame (FolioHandle wndHandle)
{
    return (ERR_SUCCESS);

    FOLIO_UNREFERENCED(wndHandle);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
