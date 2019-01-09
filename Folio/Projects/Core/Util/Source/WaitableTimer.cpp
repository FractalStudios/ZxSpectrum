// Windows includes.
#include    <Windows.h>

// "Home-made" includes.
#include    <Trace.h>
#include    "WaitableTimer.h"
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
WaitableTimer::WaitableTimer ()
{
} // Endproc.


/**
 * The class destructor. If required it will remove any OS reference to the
 * waitable timer from this object. The signaled state of the waitable timer is unaltered.
 */
WaitableTimer::~WaitableTimer ()
{
} // Endproc.


/**
 * Method that will create an unnamed waitable timer.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the waitable timer was successfully created.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a waitable timer has been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus WaitableTimer::Create ()
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a handle to a waitable timer already?

    if (m_syncHandle == FOLIO_INVALID_HANDLE)
    {
        SecurityAttributes  securityAttributes;

        // Create the waitable timer.

        m_syncHandle = ::CreateWaitableTimer (securityAttributes.GetSecurityAttributes (),
                                              FALSE, // Always synchronization timer.
                                              0);

        if (m_syncHandle == FOLIO_INVALID_HANDLE)
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR (TXT("CreateWaitableTimer"),
                                  status);
        } // Endif.

    } // Endif.

    else
    {
        // Already have a waitable timer handle for this object.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will create a named waitable timer.
 *
 * If a waitable timer of the same name already exists then it will be opened. In
 * this case, the <i>signaled</i> parameter is ignored (i.e. the signaled
 * state of the waitable timer is unaltered) and <b>ERR_ALREADY_EXISTS</b> will
 * be returned.
 *
 * @param [in] waitableTimerName
 * The name of the waitable timer. The name is case sensitive.
 *
 * @param [in] useRawName
 * Indicates if the raw <i>waitableTimerName</i> parameter should be used as the waitable timer 
 * name. <b>true</b> if the raw <i>waitableTimerName</i> parameter should be used as 
 * the waitable timer name, <b>false</b> otherwise.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the waitable timer was successfully created.
 * <li><b>ERR_ALREADY_EXISTS</b> if the named waitable timer was successfully
 *     opened.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a waitable timer has been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus WaitableTimer::Create (const FolioString&   waitableTimerName,
                                   bool                 useRawName)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a handle to a waitable timer already?

    if (m_syncHandle == FOLIO_INVALID_HANDLE)
    {
        SecurityAttributes  securityAttributes;

        // Set the shared name.

        if (useRawName)
        {
            m_sharedWaitableTimerName.SetRawName (waitableTimerName);
        } // Endif.

        else
        {
            m_sharedWaitableTimerName = waitableTimerName;
        } // Endelse.

        // Create the waitable timer.

        m_syncHandle = ::CreateWaitableTimer (securityAttributes.GetSecurityAttributes (),
                                              FALSE, // Always synchronization timer.
                                              m_sharedWaitableTimerName.GetSharedName ());

        if (m_syncHandle == FOLIO_INVALID_HANDLE)
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_1 (TXT("CreateWaitableTimer"),
                                    status,
                                    m_sharedWaitableTimerName);
        } // Endif.

        // Did the waitable timer already exist?

        else
        if (::GetLastError () == ERROR_ALREADY_EXISTS)
        {
            status = ERR_ALREADY_EXISTS;
        } // Endif.

    } // Endif.

    else
    {
        // Already have a waitable timer handle for this object.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will open an <b>existing</b> named waitable timer.
 *
 * This method will succeed if the named waitable timer has previously been created
 * using <b>Create</b>.
 *
 * @param [in] waitableTimerName
 * The name of the waitable timer. The name is case sensitive.
 *
 * @param [in] useRawName
 * Indicates if the raw <i>waitableTimerName</i> parameter should be used as the waitable timer 
 * name. <b>true</b> if the raw <i>waitableTimerName</i> parameter should be used as 
 * the waitable timer name, <b>false</b> otherwise.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_NOT_FOUND</b> if the named waitable timer was not found.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a waitable timer has been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus WaitableTimer::Open (const FolioString& waitableTimerName,
                                 bool               useRawName)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a handle to a waitable timer already?

    if (m_syncHandle == FOLIO_INVALID_HANDLE)
    {
        // Set the shared name.

        if (useRawName)
        {
            m_sharedWaitableTimerName.SetRawName (waitableTimerName);
        } // Endif.

        else
        {
            m_sharedWaitableTimerName = waitableTimerName;
        } // Endelse.

        // Open the waitable timer.

        m_syncHandle = ::OpenWaitableTimer (TIMER_ALL_ACCESS,
                                            FALSE,  // Don't inherit.
                                            m_sharedWaitableTimerName.GetSharedName ());

        if (m_syncHandle == FOLIO_INVALID_HANDLE)
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            switch (status)
            {
            case ERROR_FILE_NOT_FOUND:
                FOLIO_LOG_CALL_WARNING_1 (TXT("OpenWaitableTimer"),
                                          status,
                                          m_sharedWaitableTimerName);

                status = ERR_NOT_FOUND;
                break;

            default:
                FOLIO_LOG_CALL_ERROR_1 (TXT("OpenWaitableTimer"),
                                        status,
                                        m_sharedWaitableTimerName);
                break;
            } // Endswitch.

        } // Endif.

    } // Endif.

    else
    {
        // Already have a waitable timer handle for this object.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will start the waitable timer. The timer is set relatively to the 
 * specified timeout. 
 *
 * Starting a waitable timer that is already active will stop the active timer 
 * and restart it.
 *
 * @param [in] timeout
 * The relative timeout associated with the timer. The time (in milliseconds) after 
 * which the state of the timer is to be set to signaled.
 *
 * @param [in] periodic
 * Indicates if the waitable timer is periodic.
 * 
 * @param [in] timerCallback
 * The timer callback associated with the timer. May be zero.
 *
 * @param [in] args
 * The arguements of the timer callback associated with the timer. May be zero.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a waitable timer has not been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus WaitableTimer::Start (UInt32        timeout,
                                  bool          periodic,
                                  TimerCallback timerCallback,
                                  void*         args)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a handle to a waitable timer?

    if (m_syncHandle == FOLIO_INVALID_HANDLE)
    {
        // No waitable timer handle.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        LARGE_INTEGER   dueTime;

        dueTime.HighPart = -1;
        dueTime.LowPart  = timeout * -10000;

        if (!::SetWaitableTimer (m_syncHandle,
                                 &(dueTime), 
                                 periodic ? timeout : 0,
                                 reinterpret_cast<PTIMERAPCROUTINE> (timerCallback),
                                 args,
                                 FALSE))    // Don't restart on resume.
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_2 (TXT("SetWaitableTimer"),
                                    status,
                                    m_syncHandle,
                                    m_sharedWaitableTimerName);
        } // Endif.

    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will start the waitable timer. The timer is set absolutely. 
 *
 * Starting a waitable timer that is already active will stop the active timer 
 * and restart it.
 *
 * @param [in] dueTime
 * The absolute time associated with the timer. The UTC-based absolute time 
 * after which the state of the timer is to be set to signaled.
 *
 * @param [in] timerCallback
 * The timer callback associated with the timer. May be zero.
 *
 * @param [in] args
 * The arguements of the timer callback associated with the timer. May be zero.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a waitable timer has not been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus WaitableTimer::Start (const FILETIME&   dueTime,
                                  TimerCallback     timerCallback,
                                  void*             args)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a handle to a waitable timer?

    if (m_syncHandle == FOLIO_INVALID_HANDLE)
    {
        // No waitable timer handle.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        if (!::SetWaitableTimer (m_syncHandle,
                                 reinterpret_cast<const LARGE_INTEGER*> (&(dueTime)), 
                                 0,         // Only signal once.
                                 reinterpret_cast<PTIMERAPCROUTINE> (timerCallback),
                                 args,
                                 FALSE))    // Don't restart on resume.
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_2 (TXT("SetWaitableTimer"),
                                    status,
                                    m_syncHandle,
                                    m_sharedWaitableTimerName);
        } // Endif.

    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will cancel the waitable timer, setting it inactive.
 *
 * Cancelling a waitable timer does not change its signaled state. It stops the 
 * timer before it can be set to the signaled state. Therefore, threads 
 * performing a wait operation on the timer remain waiting until they time out 
 * or the timer is reactivated and its state is set to signaled. If the timer 
 * is already in the signaled state, it remains in that state.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a waitable timer has not been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus WaitableTimer::Cancel ()
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a handle to a waitable timer?

    if (m_syncHandle == FOLIO_INVALID_HANDLE)
    {
        // No waitable timer handle.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        if (!::CancelWaitableTimer (m_syncHandle))
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_2 (TXT("CancelWaitableTimer"),
                                    status,
                                    m_syncHandle,
                                    m_sharedWaitableTimerName);
        } // Endif.

    } // Endelse.

    return (status);
} // Endproc.


/**
 * <b>WaitableTimer</b> output stream operator.
 *
 * @param [in, out] outputStream
 * The output stream to add the <b>WaitableTimer</b> to.
 *
 * @param [in] rhs
 * The <b>WaitableTimer</b> to add to the output stream.
 *
 * @return
 * The output stream with added <b>WaitableTimer</b>.
 */
FolioOStream&   operator<< (Folio::FolioOStream&    outputStream, 
                            const WaitableTimer&            rhs)
{
    FOLIO_STREAM_FIRST_MEMBER(outputStream, rhs, m_syncHandle);
    FOLIO_STREAM_LAST_MEMBER(outputStream, rhs, m_sharedWaitableTimerName);

    return (outputStream);
} // Endproc.


/**
 * <b>SharedWaitableTimerName</b> output stream operator.
 *
 * @param [in, out] outputStream
 * The output stream to add the <b>SharedWaitableTimerName</b> to.
 *
 * @param [in] rhs
 * The <b>SharedWaitableTimerName</b> to add to the output stream.
 *
 * @return
 * The output stream with added <b>SharedWaitableTimerName</b>.
 */
FolioOStream&   operator<< (Folio::FolioOStream&    outputStream, 
                            const SharedWaitableTimerName&  rhs)
{
    FOLIO_STREAM_ONLY_VARIABLE(outputStream, rhs.c_str ());

    return (outputStream);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
