#pragma once

// "Home-made" includes.
#include    "BaseTypes.h"

#pragma pack(push, 1)

namespace Folio
{

const   UInt32  FOLIO_FINITE   = 10 * 1000;     ///< Folio finite.
const   UInt32  FOLIO_INFINITE = 0xffffffff;    ///< Folio infinite.

const   UInt32  FOLIO_UNDEFINED         = 0;    // Folio undefined.
const   UInt32  FOLIO_INVALID_INDEX     = -1;   // Folio invalid index.

const   FolioHandle FOLIO_INVALID_HANDLE        = reinterpret_cast<FolioHandle> (0);    // Folio invalid handle.
const   FolioHandle FOLIO_INVALID_FILE_HANDLE   = reinterpret_cast<FolioHandle> (-1);   // Folio invalid file handle.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
