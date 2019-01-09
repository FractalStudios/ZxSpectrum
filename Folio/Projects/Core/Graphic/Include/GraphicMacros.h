#pragma once

// "Home-made" includes.
#include    "GraphicConstsAndTypes.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Graphic
{

// Macro to round a REAL when casting to an int.
#define REAL_TO_INT(x)  (static_cast<int> (x + 0.5f))

// Macro to convert an ARGB to an RGB.
#define ARGB_TO_RGB(x)  (x & 0x00ffffff)

// Macro to convert an RGB to an ARGB.
#define RGB_TO_ARGB(x)  (x | 0xff000000)

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
