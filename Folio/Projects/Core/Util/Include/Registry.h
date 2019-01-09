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

/// The registry class.
/**
 * This class provides for access and control of a registry key.
 *
 * This class does not support copy construction or assignment.
 */
class Registry
{
public:
    Registry ();
    ~Registry ();

    FolioStatus CreateKey (FolioHandle          openKeyHandle,
                           const FolioString&   keyName,
                           UInt32               desiredAccess,
                           const FolioString*   className = 0,
                           UInt32               options = REG_OPTION_NON_VOLATILE);
    FolioStatus OpenKey (FolioHandle        openKeyHandle,
                         const FolioString& keyName,
                         UInt32             desiredAccess);
    FolioStatus CloseKey ();

    FolioStatus ReadValue (const FolioString&   valueName,
                           void*                buffer,
                           UInt32&              numOfBytes,
                           UInt32*              dataType = 0) const;
    FolioStatus WriteValue (const FolioString&  valueName,
                            UInt32              dataType,
                            const void*         buffer,
                            UInt32&             numOfBytes) const;

    FolioHandle GetKeyHandle () const;

private:
    FolioString m_keyName;      ///< The registry key name.
    FolioHandle m_keyHandle;    ///< The registry key handle.

    /// Private copy constructor to prevent copying.
    Registry (const Registry& rhs);

    /// Private assignment operator to prevent copying.
    Registry& operator= (const Registry& rhs);

    // The stream operator is our friend.
    friend  FolioOStream&   operator<< (FolioOStream&   outputStream, 
                                        const Registry& rhs);
}; // Endclass.

// The stream operator.
FolioOStream&   operator<< (Folio::FolioOStream&    outputStream, 
                            const Registry&         rhs);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
