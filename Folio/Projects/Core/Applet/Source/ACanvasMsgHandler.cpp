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
:   m_canvasBag(new CanvasBag(maxScreenXPixels, maxScreenYPixels, screenScale))
{
} // Endproc.


/**
 * The class destructor.
 */
ACanvasMsgHandler::~ACanvasMsgHandler ()
{
} // Endproc.


/**
 * Method that is used to get the canvas bag of the canvas message
 * handler.
 *
 * @return
 * The canvas bag of the canvas message handler.
 */
CanvasBag*  ACanvasMsgHandler::GetCanvasBag ()
{
    return (m_canvasBag.get ());
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
    // Resize the canvas bag.

    return (m_canvasBag->ResizeCanvas (wParam, LOWORD(lParam), HIWORD(lParam)));

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
    // Paint the canvas bag.

    return (m_canvasBag->PaintCanvas ());

    FOLIO_UNREFERENCED(wndHandle);
    FOLIO_UNREFERENCED(wParam);
    FOLIO_UNREFERENCED(lParam);
} // Endproc.


/**
 * Method that is used to handle a WM_KEYDOWN or WM_KEYUP message received by the 
 * applet window.
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
 * @param [in] keyDown
 * <b>true</b> of the message was WM_KEYDOW .
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus ACanvasMsgHandler::HandleKeyboardMsg (FolioHandle   wndHandle,
                                                  UInt32        wParam,
                                                  UInt32        lParam,
                                                  bool          keyDown)
{
    return (ERR_SUCCESS);

    FOLIO_UNREFERENCED(wndHandle);
    FOLIO_UNREFERENCED(wParam);
    FOLIO_UNREFERENCED(lParam);
    FOLIO_UNREFERENCED(keyDown);
} // Endproc.


/**
 * Method that is used to handle a WM_MOUSEMOVE message received by the applet 
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
FolioStatus ACanvasMsgHandler::HandleMouseMoveMsg (FolioHandle  wndHandle,
                                                   UInt32       wParam,
                                                   UInt32       lParam)
{
    return (ERR_SUCCESS);

    FOLIO_UNREFERENCED(wndHandle);
    FOLIO_UNREFERENCED(wParam);
    FOLIO_UNREFERENCED(lParam);
} // Endproc.


/**
 * Method that is used to handle a WM_LBUTTONDOWN, WM_LBUTTONUP, 
 * WM_RBUTTONDOWN, WM_RBUTTONUP, WM_MBUTTONDOWN, WM_MBUTTONUP message received 
 * by the applet window.
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
FolioStatus ACanvasMsgHandler::HandleMouseButtonMsg (FolioHandle    wndHandle,
                                                     UInt32         wParam,
                                                     UInt32         lParam)
{
    return (ERR_SUCCESS);

    FOLIO_UNREFERENCED(wndHandle);
    FOLIO_UNREFERENCED(wParam);
    FOLIO_UNREFERENCED(lParam);
} // Endproc.


/**
 * Method that is used to handle a WM_TIMER message received by the applet 
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
FolioStatus ACanvasMsgHandler::HandleTimerMsg (FolioHandle  wndHandle,
                                               UInt32       wParam,
                                               UInt32       lParam)
{
    return (ERR_SUCCESS);

    FOLIO_UNREFERENCED(wndHandle);
    FOLIO_UNREFERENCED(wParam);
    FOLIO_UNREFERENCED(lParam);
} // Endproc.


/**
 * Method that is used process a frame in the applet window.
 *
 * @param [in] wndHandle
 * The handle of the applet window.
 *
 * @param [out] frameRateIncrement
 * The frame rate increment.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus ACanvasMsgHandler::HandleProcessFrame (FolioHandle  wndHandle,
                                                   UInt32&      frameRateIncrement)
{
    return (ERR_SUCCESS);

    FOLIO_UNREFERENCED(wndHandle);
    FOLIO_UNREFERENCED(frameRateIncrement);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
