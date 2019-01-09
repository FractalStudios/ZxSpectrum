#pragma once

// "Home-made" includes.
#include    "BaseStreams.h"
#include    "BaseStrings.h"
#include    "BaseTypes.h"

#pragma pack(push, 1)

namespace Folio
{

/**
 * Method that is used to obtain a description of a type.
 *
 * @return
 * The description of a type.
 */
template <typename T>
FolioString GetTypeDescription (const T&)
{
    return (FOLIO_UNKNOWN_TYPE);
} // Endproc.


/**
 * Method that is used to obtain a description of a pointer type.
 *
 * @return
 * The description of a pointer type.
 */
template <typename T>
FolioString GetTypeDescription (const T*&)
{
    FolioOStringStream  outputStringStream;

    typename T  value;

    outputStringStream << TXT("*") << GetTypeDescription (value);

    return (outputStringStream.str ());
} // Endproc.


/**
 * Pointer type output stream operator.
 *
 * @param [in, out] outputStream
 * The output stream to add the pointer type to.
 *
 * @param [in] rhs
 * The pointer type to add to the output stream.
 *
 * @return
 * The output stream with added pointer type.
 */
template <typename T>
FolioOStream&   operator<< (FolioOStream&   outputStream,
                            const T*&       rhs)
{
    outputStream << rhs;

    if (rhs)
    {
        outputStream << TXT('(') << *rhs << TXT(')');
    } // Endif.

    return (outputStream);
} // Endproc.


// Type descriptions.
FolioString GetTypeDescription (const bool&);
FolioString GetTypeDescription (const float&);
FolioString GetTypeDescription (const double&);
FolioString GetTypeDescription (const void*&);
FolioString GetTypeDescription (const UInt8&);
FolioString GetTypeDescription (const UInt16&);
FolioString GetTypeDescription (const UInt32&);
FolioString GetTypeDescription (const UInt64&);
FolioString GetTypeDescription (const Int8&);
FolioString GetTypeDescription (const Int16&);
FolioString GetTypeDescription (const Int32&);
FolioString GetTypeDescription (const Int64&);
FolioString GetTypeDescription (const Char&);
FolioString GetTypeDescription (const FolioCString&);
FolioString GetTypeDescription (const FolioHandle&);

#pragma pack(pop)

} // Endnamespace.

/******************************* End of File *******************************/
