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

namespace Ptr
{

// Routines.
bool    IsValidReadPtr (void*   pointer,
                        UInt32  size = sizeof (Byte),
                        bool    nullAllowed = false);
bool    IsValidWritePtr (void*  pointer,
                         UInt32 size = sizeof (Byte),
                         bool   nullAllowed = false);
bool    IsValidReadWritePtr (void*  pointer,
                             UInt32 size = sizeof (Byte),
                             bool   nullAllowed = false);
bool    IsValidStringPtrA (const char*  pointer,
                           bool         nullAllowed = false);
bool    IsValidStringPtrW (const wchar_t*   pointer,
                           bool             nullAllowed = false);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
