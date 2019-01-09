#pragma once

// "Home-made" includes.
#include    <Base.h>

#pragma pack(push, 1)

namespace Folio
{
    
namespace Core
{

namespace Util
{

/// The shared name class.
/**
 * This class will create a shared name to be used for multiple process
 * interaction.
 */
class SharedName
{
public:
    SharedName ();
    explicit SharedName (const FolioString& baseName);
    ~SharedName ();

    SharedName& operator= (const FolioString& baseName);

    void    SetRawName (const FolioString& rawName);

    const FolioCString GetSharedName () const;

private:
    FolioString m_sharedName;   ///< The shared name.

    // The stream operator is our friend.
    friend  FolioOStream&   operator<< (FolioOStream&       outputStream, 
                                        const SharedName&   rhs);
}; // Endclass.

// The stream operator.
FolioOStream&   operator<< (Folio::FolioOStream&    outputStream, 
                            const SharedName&       rhs);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
