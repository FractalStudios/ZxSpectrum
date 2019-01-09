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

namespace Random
{

// Routines.
void    SetRandomSeed ();
UInt32  GetRandomNumber (UInt32 max);
UInt32  GetRandomNumber (UInt32 min, UInt32 max);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
