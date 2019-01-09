#pragma once

// "Home-made" includes.
#include    <Base.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Applet
{

// KEYDOWN returns true if the key is down or false if not.
#define     KEYDOWN(vKeyCode)   ((::GetAsyncKeyState(vKeyCode) & 0x8000) ? true : false)

// KEYUP returns true if the key is up or false if not.
#define     KEYUP(vKeyCode)     ((::GetAsyncKeyState(vKeyCode) & 0x8000) ? false : true)

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
