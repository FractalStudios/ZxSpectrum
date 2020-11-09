#pragma once

#pragma pack(push, 1)

namespace Utils
{

class SecurityAttributes
{
public:
    SecurityAttributes ();
    virtual ~SecurityAttributes ();

    operator    const LPSECURITY_ATTRIBUTES () const;

private:
    DWORD    m_dwWin32Error;    // The current object status.

    SECURITY_ATTRIBUTES m_securityAttributes;   // The security attributes.
    SECURITY_DESCRIPTOR m_securityDesc;         // The security descriptor.

    // Private copy constructor to prevent copying.
    SecurityAttributes (const SecurityAttributes &rhs);

    // Private assignment operator to prevent copying.
    SecurityAttributes &operator = (const SecurityAttributes &rhs);
}; // Endclass.

}; // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
