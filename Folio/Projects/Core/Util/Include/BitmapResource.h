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

// Undefined bitmap resource identifier.
const   UInt16  UNDEFINED_BITMAP_RESOURCE_ID = 0xffff;


// Routines.

extern  FolioString DescribeBitmapResourceId (UInt16 resourceId);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
