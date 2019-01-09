// Windows includes.
#include    <Windows.h>

// "Home-made" includes.
#include    <Trace.h>
#include    "Timer.h"

namespace Folio
{

namespace Core
{

namespace Util
{

namespace Timer
{

/**
 * Method that will start a timer.
 *
 * @param [in] wndHandle
 * The window handle associated with the timer.
 *
 * @param [in] timerId
 * The timer identifier associated with the timer.
 *
 * @param [in] timeout
 * The timeout associated with the timer.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the timer was successfully started.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Start (FolioHandle  wndHandle,
                   UInt32       timerId,
                   UInt32       timeout)
{
    FolioStatus status = ERR_SUCCESS;

    // Start a timer.

    if (!::SetTimer (reinterpret_cast<HWND> (wndHandle),
                     timerId,
                     timeout,
                     0))    // No timer callback.
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_3 (TXT("SetTimer"),
                                status,
                                wndHandle,
                                timerId,
                                timeout);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that will start a timer.
 *
 * @param [in] timerCallback
 * The timer callback associated with the timer.
 *
 * @param [in] timeout
 * The timeout associated with the timer.
 *
 * @param [out] timerId
 * On return, will hold the timer identifier associated with the timer, if 
 * successful. If this method fails then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the timer was successfully started.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Start (TimerCallback    timerCallback,
                   UInt32           timeout,
                   UInt32&          timerId)
{
    FolioStatus status = ERR_SUCCESS;

    // Start a timer.

    timerId = ::SetTimer (0,    // No window.
                          0,    // Don't replace existing timer identifier.
                          timeout,
                          reinterpret_cast<TIMERPROC> (timerCallback));

    if (!timerId)
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        void*   callback = reinterpret_cast<void*> (timerCallback);

        FOLIO_LOG_CALL_ERROR_2 (TXT("SetTimer"),
                                status,
                                callback,
                                timeout);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that will stop a previously started timer.
 *
 * @param [in] wndHandle
 * The window handle associated with the timer.
 *
 * @param [in] timerId
 * The timer identifier associated with the timer.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the timer was successfully stopped.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Stop (FolioHandle   wndHandle,
                  UInt32        timerId)
{
    FolioStatus status = ERR_SUCCESS;

    // Stop the timer.

    if (!::KillTimer (reinterpret_cast<HWND> (wndHandle), 
                      timerId))
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_2 (TXT("KillTimer"),
                                status,
                                wndHandle,
                                timerId);
    } // Endif.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
