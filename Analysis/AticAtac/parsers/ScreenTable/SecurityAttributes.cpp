#include    "stdafx.h"
#include    "SecurityAttributes.h"

namespace Utils
{

SecurityAttributes::SecurityAttributes ()
:   m_dwWin32Error(ERROR_INTERNAL_ERROR)
{
    // Initialise the security descriptor.

    if (::InitializeSecurityDescriptor (&(m_securityDesc),
                                        SECURITY_DESCRIPTOR_REVISION))
    {
        // Setup the descriptor which is now NULL.

        if (::SetSecurityDescriptorDacl (&(m_securityDesc),
                                         TRUE,      // Discretionary ACL present.
                                         0,         // NULL discretionary ACL required.
                                         FALSE))    // User defined discretionary ACL.
        {
            // Fill in the security attributes.

            m_securityAttributes.nLength              = sizeof (SECURITY_ATTRIBUTES);
            m_securityAttributes.lpSecurityDescriptor = &(m_securityDesc);
            m_securityAttributes.bInheritHandle       = FALSE;

            m_dwWin32Error = ERROR_SUCCESS;
        } // Endif.

        else
        {
            m_dwWin32Error = ::GetLastError ();
        } // Endelse.

    } // Endif.

    else
    {
        m_dwWin32Error = ::GetLastError ();
    } // Endelse.

} // Endproc.


SecurityAttributes::~SecurityAttributes ()
{
} // Endproc.


SecurityAttributes::operator    const LPSECURITY_ATTRIBUTES () const
{
    return ((m_dwWin32Error == ERROR_SUCCESS) ? const_cast<LPSECURITY_ATTRIBUTES> (&(m_securityAttributes)) : 0);
} // Endproc.

}; // Endnamespace.

/******************************* End of File *******************************/

