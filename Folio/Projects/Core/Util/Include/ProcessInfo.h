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

namespace ProcessInfo
{

// Routines.
FolioHandle GetCurrentProcessHandle ();
UInt32      GetCurrentProcessId ();
UInt32      GetCurrentThreadId ();
FolioHandle GetCurrentModuleHandle ();
void    SetThreadName (UInt32                   threadId,
                       const FolioNarrowString& threadName);
bool    IsValidThread (UInt32 threadId);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
