// "Home-made" includes.
#include    <Trace.h>
#include    "Window.h"

namespace Folio
{

namespace Core
{

namespace Util
{

namespace Wnd
{

/**
 * Function that will register a window class.
 *
 * @param [in] wndClassEx
 * The window class to register.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the window class was successfully registered.
 * <li><b>ERR_ALREADY_EXISTS</b> if the window class was already
 *     registered.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus RegisterWndClass (WNDCLASSEX& wndClassEx)
{
    FolioStatus status = ERR_SUCCESS;

    // Register the window class.

    if (!::RegisterClassEx (&(wndClassEx)))
    {
        // Did the class already exist?

        if (::GetLastError () == ERROR_CLASS_ALREADY_EXISTS)
        {
            status = ERR_ALREADY_EXISTS;
        } // Endif.

        else
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());
            
            FOLIO_LOG_CALL_ERROR (TXT("RegisterClassEx"),
                                  status);
        } // Endelse.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that will deregister a window class.
 *
 * @param [in] wndClassName
 * The name of the window class to deregister.
 *
 * @param [in] instanceHandle
 * The module instance that created the window class.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the window class was successfully deregistered.
 * <li><b>ERR_IN_USE</b> if the window class is still being used.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus DeregisterWndClass (const FolioString&  wndClassName,
                                FolioHandle         instanceHandle)
{
    FolioStatus status = ERR_SUCCESS;

    // Unregister the window class.

    if (!::UnregisterClass (wndClassName,
                            reinterpret_cast<HINSTANCE> (instanceHandle)))
    {
        // Is the class still being used?

        if (::GetLastError () == ERROR_CLASS_HAS_WINDOWS)
        {
            status = ERR_IN_USE;
        } // Endif.

        else
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR (TXT("UnregisterClass"),
                                  status);
        } // Endelse.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that will create a window.
 *
 * @param [in] wndClassName
 * The window class associated with the window.
 *
 * @param [in] wndName
 * The window name associated with the window; its title.
 *
 * @param [in] style
 * The style of the window.
 *
 * @param [in] styleEx
 * The extended style of the window.
 *
 * @param [in] xPos
 * The window's X position.
 *
 * @param [in] yPos
 * The window's Y position.
 *
 * @param [in] width
 * The window's width.
 *
 * @param [in] height
 * The window's height.
 *
 * @param [in] instanceHandle
 * The module instance associated with the window.
 *
 * @param [in] param
 * Pointer to a value to be passed to the window on creation. This parameter
 * may be zero, if no value is to be passed to the window on creation.
 *
 * @param [out] wndHandle
 * On return, will hold the handle to the created window, if successful. If 
 * this method fails then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the window was successfully created.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus CreateWnd (const FolioString&   wndClassName,
                       const FolioString&   wndName,
                       UInt32               style,
                       UInt32               styleEx,
                       UInt32               xPos,
                       UInt32               yPos,
                       UInt32               width,
                       UInt32               height,
                       FolioHandle          instanceHandle,
                       void*                param,
                       FolioHandle&         wndHandle)
{
    FolioStatus status = ERR_SUCCESS;

    // Create the window.

    wndHandle = ::CreateWindowEx (styleEx,
                                  wndClassName,
                                  wndName,
                                  style,
                                  xPos,
                                  yPos,
                                  width,
                                  height,
                                  0,    // No parent.
                                  0,    // No menu.
                                  reinterpret_cast<HINSTANCE> (instanceHandle),
                                  param);

    if (wndHandle == FOLIO_INVALID_HANDLE)
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_6 (TXT("CreateWindowEx"),
                                status,
                                wndClassName,
                                wndName,
                                style,
                                styleEx,
                                instanceHandle,
                                param);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that will destroy a window.
 *
 * @param [in] wndHandle
 * The handle to the window to be destroyed.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the window was successfully destroyed.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus DestroyWnd (FolioHandle wndHandle)
{
    FolioStatus status = ERR_SUCCESS;

    // Destroy the window.

    if (!::DestroyWindow (reinterpret_cast<HWND> (wndHandle)))
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_1 (TXT("DestroyWindow"),
                                status,
                                wndHandle);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that will show a window.
 *
 * @param [in] wndHandle
 * The handle to the window to be shown.
 *
 * @param [in] cmdShow
 * How the window is to be shown. 
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the window was successfully shown.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus ShowWnd (FolioHandle    wndHandle,
                     Int32          cmdShow)
{
    FolioStatus status = ERR_SUCCESS;

    // Show the window.

    if (!::ShowWindow (reinterpret_cast<HWND> (wndHandle), cmdShow))
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_2 (TXT("ShowWindow"),
                                status,
                                wndHandle,
                                cmdShow);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that will update a window.
 *
 * @param [in] wndHandle
 * The handle to the window to be updated.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the window was successfully updated.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus UpdateWnd (FolioHandle wndHandle)
{
    FolioStatus status = ERR_SUCCESS;

    // Update the window.

    if (!::UpdateWindow (reinterpret_cast<HWND> (wndHandle)))
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_1 (TXT("UpdateWindow"),
                                status,
                                wndHandle);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that will indicate if a window handle is valid.
 *
 * @param [in] wndHandle
 * The window handle to validate.
 *
 * @param [in] nullAllowed
 * Indicates if a NULL window is valid.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>true</b> if the window handle is valid.
 * <li><b>false</b> otherwise.
 * </ul>
 */
bool    IsValidWnd (FolioHandle wndHandle,
                    bool        nullAllowed)
{
    bool    isValidWnd = false;

    if (wndHandle)
    {
        isValidWnd = (::IsWindow (reinterpret_cast<HWND> (wndHandle)) == TRUE);
    } // Endif.

    else if (nullAllowed)
    {
        isValidWnd = true;
    } // Endelseif.

    if (!isValidWnd)
    {
        // Build and log an error.

        FOLIO_LOG_WARNING_1 (TXT("Invalid window."),
                             wndHandle);
    } // Endif.

    return (isValidWnd);
} // Endproc.


/**
 * Function that gets a message from the calling thread's message queue.
 *
 * @param [in] wndHandle
 * The window handle.
 *
 * @param [in] minMsgFilter
 * The lowest message value to be retrieved.
 *
 * @param [in] maxMsgFilter
 * The highest message value to be retrieved.
 *
 * @param [out] msg
 * On return, will hold the received message, if successful. If this method 
 * fails then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_STOPPED</b> if the WM_QUIT message has been received.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GetWndMessage (FolioHandle  wndHandle,
                           UInt32       minMsgFilter,
                           UInt32       maxMsgFilter,
                           MSG&         msg)
{
    FolioStatus status = ERR_SUCCESS;

    // Get a message.

    switch (::GetMessage (&(msg),
                          reinterpret_cast<HWND> (wndHandle),
                          minMsgFilter,
                          maxMsgFilter))
    {
    case -1:
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_3 (TXT("GetMessage"),
                                status,
                                wndHandle,
                                minMsgFilter,
                                maxMsgFilter);
        break;

    case 0:
        // WM_QUIT received.

        status = ERR_STOPPED;
        break;

    default:
        break;
    } // Endswitch.

    return (status);
} // Endproc.


/**
 * Function that translates virtual-key messages into character messages.
 *
 * @param [in] msg
 * The message.
 */
void    TranslateWndMessage (MSG& msg)
{
    // Translate the message.

    ::TranslateMessage (&(msg));
} // Endproc.


/**
 * Function that dispatches a message to a window procedure.
 *
 * @param [in] msg
 * The message.
 */
void    DispatchWndMessage (MSG& msg)
{
    // Dispatch the message.

    ::DispatchMessage (&(msg));
} // Endproc.


/**
 * Function that peeks for a message from the calling thread's message queue.
 *
 * @param [in] wndHandle
 * The window handle.
 *
 * @param [in] minMsgFilter
 * The lowest message value to be retrieved.
 *
 * @param [in] maxMsgFilter
 * The highest message value to be retrieved.
 *
 * @param [in] removeMsg
 * Specifies how the message is to be handled.
 *
 * @param [out] msg
 * On return, will hold the received message, if successful. If this method 
 * fails then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_NO_MSG</b> if there is no message in the thread's message queue.
 * <li><b>ERR_STOPPED</b> if the WM_QUIT message has been received.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus PeekWndMessage (FolioHandle  wndHandle,
                            UInt32       minMsgFilter,
                            UInt32       maxMsgFilter,
                            UInt32       removeMsg,
                            MSG&         msg)
{
    FolioStatus status = ERR_SUCCESS;

    // Peek for a message.

    switch (::PeekMessage (&(msg),
                           reinterpret_cast<HWND> (wndHandle),
                           minMsgFilter,
                           maxMsgFilter,
                           removeMsg))
    {
    case -1:
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_4 (TXT("PeekMessage"),
                                status,
                                wndHandle,
                                minMsgFilter,
                                maxMsgFilter,
                                removeMsg);
        break;

    case 0:
        status = ERR_NO_MSG;
        break;

    default:
        if (msg.message == WM_QUIT) 
        {
            status = ERR_STOPPED;
        } // Endif.
        break;
    } // Endswitch.

    return (status);
} // Endproc.


/**
 * Function that will post a message to a window.
 *
 * @param [in] wndHandle
 * The window handle to post the message to.
 *
 * @param [in] msg
 * The message to post.
 *
 * @param [in] wParam
 * The wParam associated with the message to post.
 *
 * @param [in] lParam
 * The lParam associated with the message to post.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the message was successfully posted.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus PostWndMessage (FolioHandle wndHandle,
                            UInt32      msg,
                            WPARAM      wParam,
                            LPARAM      lParam)
{
    FolioStatus status = ERR_SUCCESS;

    // Post the message to the window.

    if (!::PostMessage (reinterpret_cast<HWND> (wndHandle),
                        msg,
                        wParam,
                        lParam))
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_4 (TXT("PostMessage"),
                                status,
                                wndHandle,
                                msg,
                                wParam,
                                lParam);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that will send a message to a window.
 *
 * @param [in] wndHandle
 * The window handle to send the message to.
 *
 * @param [in] msg
 * The message to send.
 *
 * @param [in] wParam
 * The wParam associated with the message to send.
 *
 * @param [in] lParam
 * The lParam associated with the message to send.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the message was successfully sended.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus SendWndMessage (FolioHandle wndHandle,
                            UInt32      msg,
                            WPARAM      wParam,
                            LPARAM      lParam)
{
    // Send the message to the window.

    ::SendMessage (reinterpret_cast<HWND> (wndHandle),
                   msg,
                   wParam,
                   lParam);

    return (ERR_SUCCESS);
} // Endproc.


/**
 * Function that will call a window's default window procedure
 *
 * @param [in] wndHandle
 * The window handle of the window that received the message.
 *
 * @param [in] msg
 * The message received.
 *
 * @param [in] wParam
 * The wParam associated with the message received.
 *
 * @param [in] lParam
 * The lParam associated with the message to received.
 *
 * @return
 * The return value is the result of the message processing 
 * and depends on the message. 
 */
FolioStatus DefWindowProc (FolioHandle  wndHandle,
                           UInt32       msg,
                           WPARAM       wParam,
                           LPARAM       lParam)
{
    // Call default window procedure.

    return (::DefWindowProc (reinterpret_cast<HWND> (wndHandle),
                             msg,
                             wParam,
                             lParam));
} // Endproc.


/**
 * Function that sets a window's text.
 *
 * @param [in] wndHandle
 * The window handle.
 *
 *
 * @param [in] wndText
 * The window text to set.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus SetWndText (FolioHandle         wndHandle,
                        const FolioString&  wndText)
{
    FolioStatus status = ERR_SUCCESS;

    // Set window text.

    if (!::SetWindowText (reinterpret_cast<HWND> (wndHandle),
                          wndText.c_str ()))
    {
        // Was there an error?

        if (::GetLastError () != ERROR_SUCCESS)
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_2 (TXT("SetWindowText"),
                                    status,
                                    wndHandle,
                                    wndText);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that sets extra data in a window.
 *
 * @param [in] wndHandle
 * The window handle.
 *
 * @param [in] dataIndex
 * The index into the window's extra data.
 *
 * @param [in] data
 * The data.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus SetWndData (FolioHandle wndHandle,
                        UInt32      dataIndex,
                        void*       data)
{
    FolioStatus status = ERR_SUCCESS;

    // If the previous value is zero and SetWindowLongPtr succeeds, the return
    // value is zero, but SetWindowLongPtr does not clear the last error
    // information. So to determine success or failure, we clear the last
    // error information by calling SetLastError (0), then call
    // SetWindowLongPtr. Failure will be indicated by a return value of zero
    // and a GetLastError result that is nonzero.

    ::SetLastError (0);

    // Set extra data in window.

    if (!::SetWindowLongPtr (reinterpret_cast<HWND> (wndHandle),
                             dataIndex,
                             reinterpret_cast<LONG_PTR> (data)))
    {
        // Was there an error?

        if (::GetLastError () != ERROR_SUCCESS)
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_3 (TXT("SetWindowLongPtr"),
                                    status,
                                    wndHandle,
                                    dataIndex,
                                    data);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that obtains extra data from a window.
 *
 * @param [in] wndHandle
 * The window handle.
 *
 * @param [in] dataIndex
 * The index into the window's extra data.
 *
 * @param [out] data
 * On return, will hold the data, if successful. If this method fails then 
 * this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus QueryWndData (FolioHandle   wndHandle,
                          UInt32        dataIndex,
                          void*&        data)
{
    FolioStatus status = ERR_SUCCESS;

    // Get extra data from window.

    data = reinterpret_cast<void*> (::GetWindowLongPtr (reinterpret_cast<HWND> (wndHandle),
                                                        dataIndex));

    // If the data is really zero, then GetWindowLongPtr will return zero, so
    // make sure that we do have an error.

    if ((data == 0) &&
        (::GetLastError () != ERROR_SUCCESS))
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_3 (TXT("GetWindowLongPtr"),
                                status,
                                wndHandle,
                                dataIndex,
                                data);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that obtains the rect of a window.
 *
 * @param [in] wndHandle
 * The window handle.
 *
 * @param [out] rect
 * On return, will hold the window rect, if successful. If this method fails
 * then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus QueryWndRect (FolioHandle   wndHandle,
                          RECT&         rect)
{
    FolioStatus status = ERR_SUCCESS;

    if (!::GetWindowRect (reinterpret_cast<HWND> (wndHandle), 
                          &(rect)))
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_1 (TXT("GetWindowRect"),
                                status,
                                wndHandle);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that obtains the rect of a window's client area.
 *
 * @param [in] wndHandle
 * The window handle.
 *
 * @param [out] rect
 * On return, will hold the windows's client rect, if successful. If this 
 * method fails then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus QueryClientRect (FolioHandle    wndHandle,
                             RECT&          rect)
{
    FolioStatus status = ERR_SUCCESS;

    if (!::GetClientRect (reinterpret_cast<HWND> (wndHandle), 
                          &(rect)))
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_1 (TXT("GetClientRect"),
                                status,
                                wndHandle);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that invalidates the rect of a window's client area.
 *
 * @param [in] wndHandle
 * The window handle.
 *
 * @param [in] rect
 * The windows's client rect to invalidate.
 *
 * @param [in] eraseBackground
 * Indicates if the background should be erased.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus InvalidateClientRect (FolioHandle   wndHandle,
                                  RECT*         rect,
                                  bool          eraseBackground)
{
    FolioStatus status = ERR_SUCCESS;

    if (!::InvalidateRect (reinterpret_cast<HWND> (wndHandle), 
                           rect,
                           eraseBackground))
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_1 (TXT("InvalidateRect"),
                                status,
                                wndHandle);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that shows/hides the cursor.
 *
 * @param [in] showCursor
 * Indicates if the cursoer should be shown.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus ShowCursor (bool showCursor)
{
    ::ShowCursor (showCursor);

    return (ERR_SUCCESS);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
