// Windows includes.
#include    <Windows.h>

// C includes.
#include    <process.h>

// "Home-made" includes.
#include    <Trace.h>
#include    "SecurityAttributes.h"
#include    "Thread.h"

namespace Folio
{

namespace Core
{

namespace Util
{

/**
 * The default class constructor.
 */
Thread::Thread ()
:   m_id(0)
{
} // Endproc.


/**
 * The class destructor. If required it will remove any OS reference to
 * the thread from this object. The running state of the thread is
 * unaltered.
 */
Thread::~Thread ()
{
} // Endproc.


/**
 * Method that will start the thread. Only one thread at a time can be
 * started and running. If a previously started thread is still running then
 * <b>ERR_INVALID_SEQUENCE</b> will be returned.
 *
 * @param [in] threadCallback
 * Callback function to be called by the started thread.
 *
 * @param [in] threadArgs
 * The arguments to be passed to the thread callback. If <i>threadArgs</i> is 0,
 * no arguments are passed to the thread callback. It should be noted that
 * the arguments passed to the thread callback are NOT copied to the thread
 * but are passed straight through, i.e. as supplied. Therefore any data
 * pointed to by <i>threadArgs</i> must be valid for the lifetime of the started
 * thread.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the thread was successfully started.
 * <li><b>ERR_INVALID_SEQUENCE</b> if previously started thread using this
 *     object is still running.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Thread::Start (ThreadCallback   threadCallback,
                           void*            threadArgs)
{
    FolioStatus status = ERR_SUCCESS;

    // Is there a thread running already?

    if (IsRunning ())
    {
        // Yes. Already have a running thread for this object.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // Create the thread data.

        ThreadData* threadData = new ThreadData;

        // Note the user defined thread callback and arguments.

        threadData->m_threadCallback    = threadCallback;
        threadData->m_threadArgs        = threadArgs;

        // Create the thread. Use our thread procedure and pass in the
        // thread data - which will give acccess to the user defined
        // thread callback and arguments.

        m_syncHandle =
            reinterpret_cast<FolioHandle> (_beginthreadex (0,   // Don't inherit.
                                                           0,   // Default stack size.
                                                           ThreadProcedure,
                                                           threadData,
                                                           0,   // Start thread immediately.
                                                           &(m_id)));

        if (m_syncHandle == FOLIO_INVALID_HANDLE)
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR (TXT("_beginthreadex"),
                                  status);
        } // Endif.

    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will indicate if the thread is running.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>true</b> if the thread is running,
 * <li><b>false</b> otherwise.
 * </ul>
 */
bool    Thread::IsRunning () const
{
    FolioStatus exitCode = ERR_SUCCESS;

    return (QueryThreadExitCode (exitCode) == ERR_STARTED);
} // Endproc.


/**
 * Method that will get the identifier of the thread.
 *
 * @return
 * The possible return values are:<ul>
 * <li>The identifier of the thread, if the thread is running or the thread
 *     had previously run and has now stopped.
 * <li>Zero if the thread has not been started.
 * </ul>
 */
UInt32  Thread::GetThreadId () const
{
    return (m_id);
} // Endproc.


/**
 * Method that will get the thread exit code of the thread.
 *
 * @param [out] exitCode
 * Will hold the exit code of the thread if successful, i.e. the thread
 * had previously been started and has now stopped. Otherwise the
 * <i>exitCode</i> value is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if no thread has been started using
 *     this object.
 * <li><b>ERR_STARTED</b> if the thread has been started (and is still
 *     running).
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Thread::QueryThreadExitCode (FolioStatus& exitCode) const
{
    FolioStatus status = ERR_SUCCESS;

    // Have we started a thread?

    if (m_syncHandle == FOLIO_INVALID_HANDLE)
    {
        // Thread not started.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // Has the thread exited?

        UINT32  win32ExitCode;

        if (::GetExitCodeThread (m_syncHandle,
                                 reinterpret_cast<LPDWORD> (&(win32ExitCode))))
        {
            if (win32ExitCode == STILL_ACTIVE)
            {
                // Thread has not exited.

                status = ERR_STARTED;
            } // Endif.

            else
            {
                exitCode = win32ExitCode;
            } // Endelse.

        } // Endif.

        else
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_2 (TXT("GetExitCodeThread"),
                                    status,
                                    m_syncHandle,
                                    m_id);
        } // Endelse.

    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will suspend the execution of the current thread for at least
 * the specified interval.
 *
 * @param [in] numMilliseconds
 * The minimum time interval (in milliseconds) for which execution is to be
 * suspended. A value of zero causes the thread to relinquish the remainder of
 * its time slice to any other thread of equal priority that is ready to run.
 * If there are no other threads of equal priority ready to run, the function
 * returns immediately, and the thread continues execution.
 */
void    Thread::Sleep (UInt32 numMilliseconds)
{
    ::Sleep (numMilliseconds);
} // Endproc.


/**
 * The thread procedure.
 *
 * @param [in] args
 * Pointer to the address of the <b>ThreadData</b>. This contains the user
 * defined thread callback and the arguments to be passed to the thread
 * callback.
 *
 * @return
 * The exit code of the thread.
 */
unsigned Thread::ThreadProcedure (void* args)
{
    FolioStatus status = ERR_SUCCESS;

    // Pick up the thread data.

    ThreadData* threadData = reinterpret_cast <ThreadData*> (args);

    // Do we have valid thread data?

    if (threadData)
    {
        // If there is a user defined callback, then call it.

        if (threadData->m_threadCallback)
        {
            // Call the user defined callback.

            status = threadData->m_threadCallback (threadData->m_threadArgs);
        } // Endif.

        // Don't forget - delete the thread data.

        delete threadData;
    } // Endif.

    else
    {
        // No.

        // Build and log an error.

        FOLIO_LOG_ERROR (TXT("Thread started with NULL pointer to ThreadData"));

        status = ERR_INTERNAL_ERROR;
    } // Endelse.

    // End the thread.

    _endthreadex (status);

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
