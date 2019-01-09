// Windows includes.
#include    <Windows.h>

// "Home-made" includes.
#include    <Trace.h>
#include    "Sync.h"

namespace Folio
{

namespace Core
{

namespace Util
{

/**
 * The default class constructor.
 */
Sync::Sync ()
:   m_syncHandle(FOLIO_INVALID_HANDLE)
{
} // Endproc.


/**
 * The class destructor. Will ensure that the synchronization handle is
 * closed.
 */
Sync::~Sync ()
{
    // Close any synchronization handle.

    Close ();
} // Endproc.


/**
 * Method that will return the synchronization handle. This handle
 * will be required when a user of the UTIL interface needs access to a
 * fundamental synchronization object.
 *
 * @return
 * The possible return values are:<ul>
 * <li>The synchronization handle.
 * <li>Zero if the synchronization handle is invalid.
 * </ul>
 */
FolioHandle Sync::GetSyncHandle () const
{
    return (m_syncHandle);
} // Endproc.


/**
 * Method that will wait for either the synchronization handle to be
 * signaled or the time-out interval to elapse.
 *
 * @param [in] timeout
 * Time to wait in milliseconds. If <b>FOLIO_INFINITE</b> is specified then
 * the calling thread will be blocked indefinately until the
 * synchronization handle is signaled.
 *
 * @param [in] logOnInfiniteTimeout
 * In order to allow for problem reporting of potential system hang
 * scenarios, that parameter is used to indicate if a warning should be
 * logged if a <b>FOLIO_INFINITE</b> <i>timeout</i> has been specified and
 * the synchronization handle has not been signaled within 150 seconds. The
 * use of the parameter is dependent on the type of synchronization handle
 * being waited on. Note that if the 150 seconds timeout occurs then, after
 * logging a warning, the method will subsequently wait infinitely for the
 * synchronization handle to be signaled. <b>true</b> if the warning should
 * be logged, <b>false</b> otherwise.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_TIMEOUT</b> if the time-out interval elapsed before the
 *      synchronization handle was signaled.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a synchronization handle has not
 *     been previously created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Sync::Wait (UInt32  timeout,
                        bool    logOnInfiniteTimeout)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a synchronization handle?

    if (m_syncHandle == FOLIO_INVALID_HANDLE)
    {
        // No synchronization handle.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // If "logOnInfiniteTimeout" has been specified and the caller wishes 
        // to wait infinitely, then wait for 150 seconds. If there is a 
        // subsequent timeout then log a warning before subsequently waiting 
        // infinitely.

        if (logOnInfiniteTimeout &&
            (timeout == FOLIO_INFINITE))
        {
            status = Wait (150 * 1000, false);  // Recurse.

            if (status == ERR_TIMEOUT)
            {
                // Warn that there may be a problem waiting on the
                // synchronization handle.

                FOLIO_LOG_WARNING_1 (TXT("Waited 150 seconds for synchronization object, now waiting infinitely."),
                                     m_syncHandle);

                // Wait infinitely for the synchronization handle.

                status = Wait (FOLIO_INFINITE, false);    // Recurse.
            } // Endif.

        } // Endif.

        else
        {
            // Wait for the synchronization handle.

            UInt32  exception = ::WaitForSingleObject (m_syncHandle, 
                                                       timeout);

            switch (exception)
            {
            case WAIT_OBJECT_0:
                // The handle has been signaled within the wait time.
                break;

            case WAIT_ABANDONED:
                // The wait was satisfied by an abandoned mutex handle.


                FOLIO_LOG_WARNING_2 (TXT("Wait abandoned."),
                                     m_syncHandle,
                                     timeout);
                break;

            case WAIT_TIMEOUT:
                // The wait time elapsed without the handle being signaled.

                status = ERR_TIMEOUT;
                break;

            default:
                // Build and log an error.

                status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

                FOLIO_LOG_CALL_ERROR_2 (TXT("WaitForSingleObject"),
                                        status,
                                        m_syncHandle,
                                        timeout);
                break;
            } // Endswitch.

        } // Endelse.

    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will close the synchronization handle.
 *
 * If the synchronization handle has already been closed, then no action
 * will be taken and <b>ERR_SUCCESS</b> will be returned.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Sync::Close ()
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a synchronization handle?

    if (m_syncHandle != FOLIO_INVALID_HANDLE)
    {
        // Close the synchronization handle.

        if (::CloseHandle (m_syncHandle))
        {
            m_syncHandle = FOLIO_INVALID_HANDLE;    // Gone.
        } // Endif.

        else
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_1 (TXT("CloseHandle"),
                                    status,
                                    m_syncHandle);
        } // Endelse.

    } // Endif.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/

