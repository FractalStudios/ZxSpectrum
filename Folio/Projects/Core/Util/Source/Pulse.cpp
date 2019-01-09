// Windows includes.
#include    <Windows.h>

// "Home-made" includes.
#include    <Trace.h>
#include    "Pulse.h"
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
Pulse::Pulse ()
{
} // Endproc.


/**
 * The class destructor. If required it will remove any OS reference to the
 * pulse from this object. The signaled state of the pulse is unaltered.
 */
Pulse::~Pulse ()
{
} // Endproc.


/**
 * Method that will create an unnamed pulse.
 *
 * @param [in] signaled
 * Initial state of the pulse. <b>true</b> if initially the pulse is
 * signaled, <b>false</b> otherwise.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the pulse was successfully created.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a pulse has been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Pulse::Create (bool signaled)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a handle to a pulse already?

    if (m_syncHandle == FOLIO_INVALID_HANDLE)
    {
        SecurityAttributes  securityAttributes;

        // Create the pulse.

        m_syncHandle = ::CreateEvent (securityAttributes.GetSecurityAttributes (),
                                      FALSE,    // Always auto reset.
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
        // Already have a pulse handle for this object.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will set the pulse to the signaled state. The state of a
 * pulse remains signaled until one of the one waiting thread (of many), that
 * subsequently begin wait operations for the specified pulse by calling one of
 * the wait functions, can be released, at which time the state is automatically
 * reset to nonsignaled.
 *
 * Setting a pulse that is already set has no effect.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a pulse has not been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Pulse::Set ()
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a handle to a pulse?

    if (m_syncHandle == FOLIO_INVALID_HANDLE)
    {
        // No pulse handle.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        if (!::SetEvent (m_syncHandle))
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_1 (TXT("SetEvent"),
                                    status,
                                    m_syncHandle);
        } // Endif.

    } // Endelse.

    return (status);
} // Endproc.


/**
 * <b>Pulse</b> output stream operator.
 *
 * @param [in, out] outputStream
 * The output stream to add the <b>Pulse</b> to.
 *
 * @param [in] rhs
 * The <b>Pulse</b> to add to the output stream.
 *
 * @return
 * The output stream with added <b>Pulse</b>.
 */
FolioOStream&   operator<< (Folio::FolioOStream&    outputStream, 
                            const Pulse&            rhs)
{
    FOLIO_STREAM_ONLY_MEMBER(outputStream, rhs, m_syncHandle);

    return (outputStream);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
