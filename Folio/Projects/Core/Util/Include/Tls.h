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

namespace Tls
{

// Routines.
FolioStatus Alloc (UInt32& tlsIndex);
FolioStatus Free (UInt32 tlsIndex);
FolioStatus SetData (UInt32 tlsIndex,
                     void*  data);
FolioStatus QueryData (UInt32   tlsIndex,
                       void*&   data);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
