// "Home-made" includes.
#include    <Trace.h>
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
SecurityAttributes::SecurityAttributes ()
:   m_status(ERR_NOT_INITIALISED)
{
    // Initialise the security descriptor.

    if (::InitializeSecurityDescriptor (&(m_securityDescriptor),
                                        SECURITY_DESCRIPTOR_REVISION))
    {
        // Setup the descriptor which is now NULL.

        if (::SetSecurityDescriptorDacl (&(m_securityDescriptor),
                                         TRUE,      // Discretionary ACL present.
                                         0,         // NULL discretionary ACL required.
                                         FALSE))    // User defined discretionary ACL.
        {
            // Fill in the security attributes.

            m_securityAttributes.nLength                = sizeof (SECURITY_ATTRIBUTES);
            m_securityAttributes.lpSecurityDescriptor   = &(m_securityDescriptor);
            m_securityAttributes.bInheritHandle         = FALSE;

            m_status = ERR_SUCCESS;
        } // Endif.

        else
        {
            // Build and log an error.

            m_status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR (TXT("SetSecurityDescriptorDacl"),
                                  FOLIO_GET_STATUS_CODE(m_status));
        } // Endelse.

    } // Endif.

    else
    {
        // Build and log an error.

        m_status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR (TXT("InitializeSecurityDescriptor"),
                              FOLIO_GET_STATUS_CODE(m_status));
    } // Endelse.

} // Endproc.


/**
 * The class destructor.
 */
SecurityAttributes::~SecurityAttributes ()
{
} // Endproc.


/**
 * Method that will get the default security attributes.
 *
 * @return
 * The default security attributes.
 */
const LPSECURITY_ATTRIBUTES SecurityAttributes::GetSecurityAttributes () const
{
    return ((m_status == ERR_SUCCESS) ? const_cast<LPSECURITY_ATTRIBUTES> (&(m_securityAttributes)) : 0);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
