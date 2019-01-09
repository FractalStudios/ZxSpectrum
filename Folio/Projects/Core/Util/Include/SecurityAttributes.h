#pragma once

// Windows includes.
#include    <Windows.h>

// "Home-made" includes.
#include    <Base.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Util
{

/// The security attributes class.
/**
 * This class controls the default security attributes required by most
 * Windows handle based objects.
 *
 * This class does not support copy construction or assignment.
 */
class SecurityAttributes
{
public:
    SecurityAttributes ();
    ~SecurityAttributes ();

    const LPSECURITY_ATTRIBUTES GetSecurityAttributes () const;

private:
    FolioStatus m_status;   ///< The current object status.

    SECURITY_ATTRIBUTES m_securityAttributes;   ///< The security attributes.
    SECURITY_DESCRIPTOR m_securityDescriptor;   ///< The security descriptor.

    // Private copy constructor to prevent copying.
    SecurityAttributes (const SecurityAttributes& rhs);

    // Private assignment operator to prevent copying.
    SecurityAttributes& operator= (const SecurityAttributes& rhs);
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
