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

namespace Timer
{

// Timer callback routine.
typedef FolioStatus (FOLIO_CALL *TimerCallback) (FolioHandle    wndHandle, 
                                                 UInt32         msg, 
                                                 UInt32         timerId,
                                                 UInt32         elapsedTime);

FolioStatus Start (FolioHandle  wndHandle,
                   UInt32       timerId,
                   UInt32       timeout);
FolioStatus Start (TimerCallback    timerCallback,
                   UInt32           timeout,
                   UInt32&          timerId);
FolioStatus Stop (FolioHandle   wndHandle,
                  UInt32        timerId);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
