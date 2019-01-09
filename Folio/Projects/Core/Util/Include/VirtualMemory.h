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

namespace VirtualMemory
{

// Routines.
FolioStatus QueryVirtualMemory (FolioHandle                 processHandle,
                                void*                       address,
                                MEMORY_BASIC_INFORMATION&   memoryBasicInfo);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
