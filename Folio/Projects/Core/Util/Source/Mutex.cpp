// "Home-made" includes.
#include    <Trace.h>
#include    "Mutex.h"
#include    "SecurityAttributes.h"

namespace Folio
{

namespace Core
{

namespace Util
{

/**
 * The default class constructor.
 */
Mutex::Mutex ()
{
} // Endproc.


/**
 * The class destructor. If required it will remove any OS reference to the
 * mutex from this object.
 */
Mutex::~Mutex ()
{
} // Endproc.


/**
 * Method that will create an unnamed mutex.
 *
 * @param [in] locked
 * Initial lock state of the mutex. <b>true</b> will wait until ownership
 * of the mutex is gained, <b>false</b> does not wait for ownership.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the mutex was successfully created.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a mutex has been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Mutex::Create (bool locked)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a handle to a mutex already?

    if (m_syncHandle == FOLIO_INVALID_HANDLE)
    {
        SecurityAttributes  securityAttributes;

        // Create the mutex.

        m_syncHandle = ::CreateMutex (securityAttributes.GetSecurityAttributes (),
                                      locked ? TRUE : FALSE,    // Ownership.
                                      0);

        if (m_syncHandle == FOLIO_INVALID_HANDLE)
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_1 (TXT("CreateMutex"),
                                    status,
                                    locked);
        } // Endif.

    } // Endif.

    else
    {
        // Already have a mutex handle for this object.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will create a named mutex.
 *
 * If a mutex of the same name already exists then it will be opened. In
 * this case, the <i>locked</i> parameter is ignored and
 * <b>ERR_ALREADY_EXISTS</b> will be returned.
 *
 * @param [in] mutexName
 * The name of the mutex. The name is case sensitive.
 *
 * @param [in] locked
 * Initial lock state of the mutex. <b>true</b> will wait until ownership
 * of the mutex is gained, <b>false</b> does not wait for ownership.
 *
 * @param [in] useRawName
 * Indicates if the raw <i>mutexName</i> parameter should be used as the mutex 
 * name. <b>true</b> if the raw <i>mutexName</i> parameter should be used as 
 * the mutex name, <b>false</b> otherwise.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the mutex was successfully created.
 * <li><b>ERR_ALREADY_EXISTS</b> if the named mutex was successfully
 *     opened.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a mutex has been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Mutex::Create (const FolioString&   mutexName,
                           bool                 locked,
                           bool                 useRawName)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a handle to a mutex already?

    if (m_syncHandle == FOLIO_INVALID_HANDLE)
    {
        SecurityAttributes  securityAttributes;

        // Set the shared name.

        if (useRawName)
        {
            m_sharedMutexName.SetRawName (mutexName);
        } // Endif.

        else
        {
            m_sharedMutexName = mutexName;
        } // Endelse.

        // Create the mutex.

        m_syncHandle = ::CreateMutex (securityAttributes.GetSecurityAttributes (),
                                      locked ? TRUE : FALSE,    // Ownership.
                                      m_sharedMutexName.GetSharedName ());

        if (m_syncHandle == FOLIO_INVALID_HANDLE)
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_2 (TXT("CreateMutex"),
                                    status,
                                    locked,
                                    m_sharedMutexName);
        } // Endif.

        // Did the mutex already exist?

        else if (::GetLastError () == ERROR_ALREADY_EXISTS)
        {
            // Ownership is ignored if the mutex already existed,
            // so no need to increment the lock usage count.

            status = ERR_ALREADY_EXISTS;
        } // Endelseif.

    } // Endif.

    else
    {
        // Already have a mutex handle for this object.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will open an <b>existing</b> named mutex.
 *
 * This method will succeed if the named mutex has previously been created
 * using <b>Create</b>.
 *
 * @param [in] mutexName
 * The name of the mutex. The name is case sensitive.
 *
 * @param [in] useRawName
 * Indicates if the raw <i>mutexName</i> parameter should be used as the mutex 
 * name. <b>true</b> if the raw <i>mutexName</i> parameter should be used as 
 * the mutex name, <b>false</b> otherwise.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_NOT_FOUND</b> if the named mutex was not found.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a mutex has been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Mutex::Open (const FolioString& mutexName,
                         bool               useRawName)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a handle to a mutex already?

    if (m_syncHandle == FOLIO_INVALID_HANDLE)
    {
        // Set the shared name.

        if (useRawName)
        {
            m_sharedMutexName.SetRawName (mutexName);
        } // Endif.

        else
        {
            m_sharedMutexName = mutexName;
        } // Endelse.

        // Open the mutex.

        m_syncHandle = ::OpenMutex (MUTEX_ALL_ACCESS,
                                    FALSE, // Don't inherit.
                                    m_sharedMutexName.GetSharedName ());

        if (m_syncHandle == FOLIO_INVALID_HANDLE)
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            switch (status)
            {
            case ERROR_FILE_NOT_FOUND:
                FOLIO_LOG_CALL_WARNING_1 (TXT("OpenMutex"),
                                          status,
                                          m_sharedMutexName);

                status = ERR_NOT_FOUND;
                break;

            default:
                FOLIO_LOG_CALL_ERROR_1 (TXT("OpenMutex"),
                                        status,
                                        m_sharedMutexName);
                break;
            } // Endswitch.

        } // Endif.

    } // Endif.

    else
    {
        // Already have a mutex handle for this object.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will wait for either the mutex to be signaled or the time-out
 * interval to elapse.
 *
 * A thread can specify a mutex that it already owns without blocking its
 * execution. This prevents a thread from deadlocking itself while waiting for
 * a mutex that it already owns. However, to release its ownership, the thread
 * must call <b>Unlock</b> one time for each time that it obtained ownership.
 *
 * @param [in] timeout
 * Time to wait in milliseconds. If <b>FOLIO_INFINITE</b> is specified then
 * the calling thread will be blocked indefinately until the mutex is
 * signaled.
 *
 * @param [in] logOnInfiniteTimeout
 * In order to allow for problem reporting of potential system hang
 * scenarios, that parameter is used to indicate if a warning should be
 * logged if a <b>FOLIO_INFINITE</b> <i>timeout</i> has been specified and
 * the mutex has not been signaled within 150 seconds. Note that if the 150
 * seconds timeout occurs then, after logging a warning, the method will
 * subsequently wait infinitely for the mutex to be signaled. <b>true</b> if
 * the warning should be logged, <b>false</b> otherwise.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_TIMEOUT</b> if the time-out interval elapsed before the
 *     mutex was signaled.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a mutex has not been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Mutex::Lock (UInt32 timeout,
                         bool   logOnInfiniteTimeout)
{
    return (Wait (timeout, logOnInfiniteTimeout));
} // Endproc.


/**
 * Method that will release the thread's ownership of the mutex.
 *
 * If a thread calls <b>Unlock</b> when it does not have ownership of the
 * mutex, then no action will be taken and <b>ERR_SUCCESS</b> will be
 * returned.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a mutex has not been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Mutex::Unlock ()
{
    FolioStatus status = ERR_SUCCESS;

     // Have we obtained a handle to a mutex?

    if (m_syncHandle == FOLIO_INVALID_HANDLE)
    {
        // No mutex handle.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    // Release the mutex.

    else
    if (!::ReleaseMutex (m_syncHandle))
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_2 (TXT("ReleaseMutex"),
                                status,
                                m_syncHandle,
                                m_sharedMutexName);
    } // Endelse.

    return (status);
} // Endproc.


/**
 * <b>Mutex</b> output stream operator.
 *
 * @param [in, out] outputStream
 * The output stream to add the <b>Mutex</b> to.
 *
 * @param [in] rhs
 * The <b>Mutex</b> to add to the output stream.
 *
 * @return
 * The output stream with added <b>Mutex</b>.
 */
FolioOStream&   operator<< (Folio::FolioOStream&    outputStream, 
                            const Mutex&            rhs)
{
    FOLIO_STREAM_FIRST_MEMBER(outputStream, rhs, m_syncHandle);
    FOLIO_STREAM_LAST_MEMBER(outputStream, rhs, m_sharedMutexName);

    return (outputStream);
} // Endproc.


/**
 * <b>SharedMutexName</b> output stream operator.
 *
 * @param [in, out] outputStream
 * The output stream to add the <b>SharedMutexName</b> to.
 *
 * @param [in] rhs
 * The <b>SharedMutexName</b> to add to the output stream.
 *
 * @return
 * The output stream with added <b>SharedMutexName</b>.
 */
FolioOStream&   operator<< (Folio::FolioOStream&    outputStream, 
                            const SharedMutexName&  rhs)
{
    FOLIO_STREAM_ONLY_VARIABLE(outputStream, rhs.c_str ());

    return (outputStream);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/

