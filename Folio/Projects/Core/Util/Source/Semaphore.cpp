// Windows includes.
#include    <Windows.h>

// "Home-made" includes.
#include    <Trace.h>
#include    "SecurityAttributes.h"
#include    "Semaphore.h"

namespace Folio
{

namespace Core
{

namespace Util
{

/**
 * The default class constructor.
 */
Semaphore::Semaphore ()
{
} // Endproc.


/**
 * The class destructor. If required it will remove any OS reference to the
 * semaphore from this object.
 */
Semaphore::~Semaphore ()
{
} // Endproc.


/**
 * Method that will create an unnamed semaphore.
 *
 * @param [in] maxCount
 * The maximum count for the semapahore. This value must be greater than zero.
 *
 * @param [in] initialCount
 * The initial count for the semapahore. This value must be greater than or
 * equal to zero and less than or equal to <i>maxCount</i>. The state of
 * the semaphore is signaled when its count is greater than zero and
 * nonsignaled when it is zero. The count is decreased by one whenever
 * <b>Lock</b> releases a thread that was waiting for the semaphore.
 * The count is increased by a specified amount by calling the <b>UnLock</b>
 * method.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the semaphore was successfully created.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a semaphore has been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Semaphore::Create (UInt32   maxCount,
                               UInt32   initialCount)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a handle to a semaphore already?

    if (m_syncHandle == FOLIO_INVALID_HANDLE)
    {
        SecurityAttributes  securityAttributes;

        // Create the semaphore.

        m_syncHandle = ::CreateSemaphore (securityAttributes.GetSecurityAttributes (),
                                          initialCount,
                                          maxCount,
                                          0);

        if (m_syncHandle == FOLIO_INVALID_HANDLE)
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_2 (TXT("CreateSemaphore"),
                                    status,
                                    initialCount,
                                    maxCount);
        } // Endif.

    } // Endif.

    else
    {
        // Already have a semaphore handle for this object.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will create a named semaphore.
 *
 * If a semaphore of the same name already exists then it will be opened.
 * In this case, the <i>initialCount</i> and <i>maxCount</i> parameters
 * are ignored (i.e. the signaled state of the semaphore is unaltered) and
 * <b>ERR_ALREADY_EXISTS</b> will be returned.
 *
 * @param [in] semaphoreName
 * The name of the semaphore. The name is case sensitive.
 *
 * @param [in] maxCount
 * The maximum count for the semapahore. This value must be greater than zero.
 *
 * @param [in] initialCount
 * The initial count for the semapahore. This value must be greater than or
 * equal to zero and less than or equal to <i>maxCount</i>. The state of
 * the semaphore is signaled when its count is greater than zero and
 * nonsignaled when it is zero. The count is decreased by one whenever
 * <b>Lock</b> releases a thread that was waiting for the semaphore.
 * The count is increased by a specified amount by calling the <b>UnLock</b>
 * method.
 *
 * @param [in] useRawName
 * Indicates if the raw <i>semaphoreName</i> parameter should be used as the 
 * semaphore name. <b>true</b> if the raw <i>semaphoreName</i> parameter should 
 * be used as the semaphore name, <b>false</b> otherwise.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the semaphore was successfully created.
 * <li><b>ERR_ALREADY_EXISTS</b> if the named sempahore was successfully
 *     opened.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a semaphore has been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Semaphore::Create (const FolioString&   semaphoreName,
                               UInt32               maxCount,
                               UInt32               initialCount,
                               bool                 useRawName)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a handle to a semaphore already?

    if (m_syncHandle == FOLIO_INVALID_HANDLE)
    {
        SecurityAttributes  securityAttributes;

        // Set the shared name.

        if (useRawName)
        {
            m_sharedSemaphoreName.SetRawName (semaphoreName);
        } // Endif.

        else
        {
            m_sharedSemaphoreName = semaphoreName;
        } // Endelse.

        // Create the semaphore.

        m_syncHandle = ::CreateSemaphore (securityAttributes.GetSecurityAttributes (),
                                          initialCount,
                                          maxCount,
                                          m_sharedSemaphoreName.GetSharedName ());

        if (m_syncHandle == FOLIO_INVALID_HANDLE)
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_3 (TXT("CreateSemaphore"),
                                    status,
                                    initialCount,
                                    maxCount,
                                    m_sharedSemaphoreName);
        } // Endif.

        // Did the semaphore already exist?

        else if (::GetLastError () == ERROR_ALREADY_EXISTS)
        {
            status = ERR_ALREADY_EXISTS;
        } // Endelseif.

    } // Endif.

    else
    {
        // Already have a semaphore handle for this object.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will open an <b>existing</b> named semaphore.
 *
 * This method will succeed if the named semaphore has previously been
 * created using <b>Create</b>.
 *
 * @param [in] semaphoreName
 * The name of the semaphore. The name is case sensitive.
 *
 * @param [in] useRawName
 * Indicates if the raw <i>semaphoreName</i> parameter should be used as the 
 * semaphore name. <b>true</b> if the raw <i>semaphoreName</i> parameter should 
 * be used as the semaphore name, <b>false</b> otherwise.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_NOT_FOUND</b> if the named semaphore was not found.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a semaphore has been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Semaphore::Open (const FolioString& semaphoreName,
                             bool               useRawName)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a handle to a semaphore already?

    if (m_syncHandle == FOLIO_INVALID_HANDLE)
    {
        // Set the shared name.

        if (useRawName)
        {
            m_sharedSemaphoreName.SetRawName (semaphoreName);
        } // Endif.

        else
        {
            m_sharedSemaphoreName = semaphoreName;
        } // Endelse.

        // Open the semaphore.

        m_syncHandle = ::OpenSemaphore (SEMAPHORE_ALL_ACCESS,
                                        FALSE,  // Don't inherit.
                                        m_sharedSemaphoreName.GetSharedName ());

        if (m_syncHandle == FOLIO_INVALID_HANDLE)
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            switch (status)
            {
            case ERROR_FILE_NOT_FOUND:
                FOLIO_LOG_CALL_WARNING_1 (TXT("OpenSemaphore"),
                                          status,
                                          m_sharedSemaphoreName);

                status = ERR_NOT_FOUND;
                break;

            default:
                FOLIO_LOG_CALL_ERROR_1 (TXT("OpenSemaphore"),
                                        status,
                                        m_sharedSemaphoreName);
                break;
            } // Endswitch.

        } // Endif.

    } // Endif.

    else
    {
        // Already have a semaphore handle for this object.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will wait for either the semaphore to be signaled or the
 * time-out interval to elapse.
 *
 * Each time a waiting thread is released because of the semaphore's signaled
 * state, the count of the semaphore is decreased by one. The thread's
 * "ownership" of the semaphore increases by one. To release its ownership,
 * the thread must call <b>Unlock</b> where it can specify up to its
 * ownership count.
 *
 * @param [in] timeout
 * Time to wait in milliseconds. If <b>FOLIO_INFINITE</b> is specified then
 * the calling thread will be blocked indefinately until the semaphore is
 * signaled.
 *
 * @param [in] logOnInfiniteTimeout
 * In order to allow for problem reporting of potential system hang
 * scenarios, that parameter is used to indicate if a warning should be
 * logged if a <b>FOLIO_INFINITE</b> <i>timeout</i> has been specified and
 * the semaphore has not been signaled within 150 seconds. Note that if the
 * 150 seconds timeout occurs then, after logging a warning, the method will
 * subsequently wait infinitely for the semaphore to be signaled. <b>true</b>
 * if the warning should be logged, <b>false</b> otherwise.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_TIMEOUT</b> if the time-out interval elapsed before the
 *     semaphorewas signaled.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a semaphore has not been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Semaphore::Lock (UInt32 timeout,
                             bool   logOnInfiniteTimeout)
{
    return (Wait (timeout, logOnInfiniteTimeout));
} // Endproc.


/**
 * Method that will increase the count of the semaphore by a specified amount.
 *
 * If a thread calls <b>Unlock</b> when it does not have any "ownership" of
 * the semaphore, or the specified amount is greater than the ownership count,
 * the count is not changed and the method will fail.
 *
 * @param [in] unlockCount
 * Amount by which the semaphore current count is to be increased. The value
 * must be greater than zero. If the specified amount would cause the
 * semaphore's count to exceed the maximum count that was specified when
 * the semaphore was created, the count is not changed and the method will
 * fail.
 *
 * @param [out] previousCount
 * Will hold the previous count of the semaphore. This parameter may be zero
 * if not required. Defaults to zero.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a semaphore has not been previously
 *     createdor opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Semaphore::Unlock (UInt32   unlockCount,
                               UInt32*  previousCount)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a handle to a semaphore?

    if (m_syncHandle == FOLIO_INVALID_HANDLE)
    {
        // No semaphore handle.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // Release the semaphore.

        if (!::ReleaseSemaphore (m_syncHandle,
                                 unlockCount,
                                 reinterpret_cast<LPLONG> (previousCount)))
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_4 (TXT("ReleaseSemaphore"),
                                    status,
                                    m_syncHandle,
                                    unlockCount,
                                    previousCount,
                                    m_sharedSemaphoreName);
        } // Endif.

    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will set the semaphore to the nonsignaled state.
 *
 * Resetting a semaphore that is already reset has no effect.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a semaphore has not been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Semaphore::Reset ()
{
    FolioStatus status = ERR_SUCCESS;

    // Loop until the semaphore count has been reduced.

    do
    {
        status = Lock (0);
    } // Endif.
    while (status == ERR_SUCCESS);

    if (status == ERR_TIMEOUT)
    {
        // The semaphore is in the nonsignaled state.

        status = ERR_SUCCESS;
    } // Endif.

    return (status);
} // Endproc.


/**
 * <b>Semaphore</b> output stream operator.
 *
 * @param [in, out] outputStream
 * The output stream to add the <b>Semaphore</b> to.
 *
 * @param [in] rhs
 * The <b>Semaphore</b> to add to the output stream.
 *
 * @return
 * The output stream with added <b>Semaphore</b>.
 */
FolioOStream&   operator<< (Folio::FolioOStream&    outputStream, 
                            const Semaphore&        rhs)
{
    FOLIO_STREAM_FIRST_MEMBER(outputStream, rhs, m_syncHandle);
    FOLIO_STREAM_LAST_MEMBER(outputStream, rhs, m_sharedSemaphoreName);

    return (outputStream);
} // Endproc.


/**
 * <b>SharedSemaphoreName</b> output stream operator.
 *
 * @param [in, out] outputStream
 * The output stream to add the <b>SharedSemaphoreName</b> to.
 *
 * @param [in] rhs
 * The <b>SharedSemaphoreName</b> to add to the output stream.
 *
 * @return
 * The output stream with added <b>SharedSemaphoreName</b>.
 */
FolioOStream&   operator<< (Folio::FolioOStream&        outputStream, 
                            const SharedSemaphoreName&  rhs)
{
    FOLIO_STREAM_ONLY_VARIABLE(outputStream, rhs.c_str ());

    return (outputStream);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
