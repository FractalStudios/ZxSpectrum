// Windows includes.
#include    <Windows.h>

// "Home-made" includes.
#include    <Trace.h>
#include    "Event.h"
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
Event::Event ()
{
} // Endproc.


/**
 * The class destructor. If required it will remove any OS reference to the
 * event from this object. The signaled state of the event is unaltered.
 */
Event::~Event ()
{
} // Endproc.


/**
 * Method that will create an unnamed event.
 *
 * @param [in] signaled
 * Initial state of the event. <b>true</b> if initially the event is
 * signaled, <b>false</b> otherwise.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the event was successfully created.
 * <li><b>ERR_INVALID_SEQUENCE</b> if an event has been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Event::Create (bool signaled)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a handle to an event already?

    if (m_syncHandle == FOLIO_INVALID_HANDLE)
    {
        SecurityAttributes  securityAttributes;

        // Create the event.

        m_syncHandle = ::CreateEvent (securityAttributes.GetSecurityAttributes (),
                                      TRUE, // Always manual reset.
                                      signaled ? TRUE : FALSE,
                                      0);

        if (m_syncHandle == FOLIO_INVALID_HANDLE)
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_1 (TXT("CreateEvent"),
                                    status,
                                    signaled);
        } // Endif.

    } // Endif.

    else
    {
        // Already have an event handle for this object.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will create a named event.
 *
 * If an event of the same name already exists then it will be opened. In
 * this case, the <i>signaled</i> parameter is ignored (i.e. the signaled
 * state of the event is unaltered) and <b>ERR_ALREADY_EXISTS</b> will
 * be returned.
 *
 * @param [in] eventName
 * The name of the event. The name is case sensitive.
 *
 * @param [in] signaled
 * Initial state of the event. <b>true</b> if initially the event is
 * signaled, <b>false</b> otherwise.
 *
 * @param [in] useRawName
 * Indicates if the raw <i>eventName</i> parameter should be used as the event 
 * name. <b>true</b> if the raw <i>eventName</i> parameter should be used as 
 * the event name, <b>false</b> otherwise.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the event was successfully created.
 * <li><b>ERR_ALREADY_EXISTS</b> if the named event was successfully
 *     opened.
 * <li><b>ERR_INVALID_SEQUENCE</b> if an event has been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Event::Create (const FolioString&   eventName,
                           bool                 signaled,
                           bool                 useRawName)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a handle to an event already?

    if (m_syncHandle == FOLIO_INVALID_HANDLE)
    {
        SecurityAttributes  securityAttributes;

        // Set the shared name.

        if (useRawName)
        {
            m_sharedEventName.SetRawName (eventName);
        } // Endif.

        else
        {
            m_sharedEventName = eventName;
        } // Endelse.

        // Create the event.

        m_syncHandle = ::CreateEvent (securityAttributes.GetSecurityAttributes (),
                                      TRUE, // Always manual reset.
                                      signaled ? TRUE : FALSE,
                                      m_sharedEventName.GetSharedName ());

        if (m_syncHandle == FOLIO_INVALID_HANDLE)
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_2 (TXT("CreateEvent"),
                                    status,
                                    signaled,
                                    m_sharedEventName);
        } // Endif.

        // Did the event already exist?

        else
        if (::GetLastError () == ERROR_ALREADY_EXISTS)
        {
            status = ERR_ALREADY_EXISTS;
        } // Endif.

    } // Endif.

    else
    {
        // Already have an event handle for this object.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will open an <b>existing</b> named event.
 *
 * This method will succeed if the named event has previously been created
 * using <b>Create</b>.
 *
 * @param [in] eventName
 * The name of the event. The name is case sensitive.
 *
 * @param [in] useRawName
 * Indicates if the raw <i>eventName</i> parameter should be used as the event 
 * name. <b>true</b> if the raw <i>eventName</i> parameter should be used as 
 * the event name, <b>false</b> otherwise.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_NOT_FOUND</b> if the named event was not found.
 * <li><b>ERR_INVALID_SEQUENCE</b> if an event has been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Event::Open (const FolioString& eventName,
                         bool               useRawName)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a handle to an event already?

    if (m_syncHandle == FOLIO_INVALID_HANDLE)
    {
        // Set the shared name.

        if (useRawName)
        {
            m_sharedEventName.SetRawName (eventName);
        } // Endif.

        else
        {
            m_sharedEventName = eventName;
        } // Endelse.

        // Open the event.

        m_syncHandle = ::OpenEvent (EVENT_ALL_ACCESS,
                                    FALSE,  // Don't inherit.
                                    m_sharedEventName.GetSharedName ());

        if (m_syncHandle == FOLIO_INVALID_HANDLE)
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            switch (status)
            {
            case ERROR_FILE_NOT_FOUND:
                FOLIO_LOG_CALL_WARNING_1 (TXT("OpenEvent"),
                                          status,
                                          m_sharedEventName);

                status = ERR_NOT_FOUND;
                break;

            default:
                FOLIO_LOG_CALL_ERROR_1 (TXT("OpenEvent"),
                                        status,
                                        m_sharedEventName);
                break;
            } // Endswitch.

        } // Endif.

    } // Endif.

    else
    {
        // Already have an event handle for this object.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will set the event to the signaled state. The state of a
 * manual-reset event remains signaled until it is set explicitly to the
 * nonsignaled state by the <b>Reset</b> method. Any number of waiting
 * threads, or threads that subsequently begin wait operations for the
 * specified event by calling one of the wait functions, can be released
 * while the object's state is signaled.
 *
 * Setting an event that is already set has no effect.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if an event has not been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Event::Set ()
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a handle to an event?

    if (m_syncHandle == FOLIO_INVALID_HANDLE)
    {
        // No event handle.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        if (!::SetEvent (m_syncHandle))
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_2 (TXT("SetEvent"),
                                    status,
                                    m_syncHandle,
                                    m_sharedEventName);
        } // Endif.

    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will set the event to the nonsignaled state.
 *
 * Resetting an event that is already reset has no effect.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if an event has not been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Event::Reset ()
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a handle to an event?

    if (m_syncHandle == FOLIO_INVALID_HANDLE)
    {
        // No event handle.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        if (!::ResetEvent (m_syncHandle))
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_2 (TXT("ResetEvent"),
                                    status,
                                    m_syncHandle,
                                    m_sharedEventName);
        } // Endif.

    } // Endelse.

    return (status);
} // Endproc.


/**
 * <b>Event</b> output stream operator.
 *
 * @param [in, out] outputStream
 * The output stream to add the <b>Event</b> to.
 *
 * @param [in] rhs
 * The <b>Event</b> to add to the output stream.
 *
 * @return
 * The output stream with added <b>Event</b>.
 */
FolioOStream&   operator<< (Folio::FolioOStream&    outputStream, 
                            const Event&            rhs)
{
    FOLIO_STREAM_FIRST_MEMBER(outputStream, rhs, m_syncHandle);
    FOLIO_STREAM_LAST_MEMBER(outputStream, rhs, m_sharedEventName);

    return (outputStream);
} // Endproc.


/**
 * <b>SharedEventName</b> output stream operator.
 *
 * @param [in, out] outputStream
 * The output stream to add the <b>SharedEventName</b> to.
 *
 * @param [in] rhs
 * The <b>SharedEventName</b> to add to the output stream.
 *
 * @return
 * The output stream with added <b>SharedEventName</b>.
 */
FolioOStream&   operator<< (Folio::FolioOStream&    outputStream, 
                            const SharedEventName&  rhs)
{
    FOLIO_STREAM_ONLY_VARIABLE(outputStream, rhs.c_str ());

    return (outputStream);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
