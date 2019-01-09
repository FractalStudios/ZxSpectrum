#pragma once

// Windows includes.
#define NOMINMAX
#include    <Windows.h>

// STL includes.
#include    <algorithm>

// GDI+ includes.
namespace Gdiplus
{
    using   std::min;
    using   std::max;
}; // Endnamespace.
#include    <gdiplus.h>

// "Home-made" includes.
#include    <Base.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Graphic
{

static  const   UInt32  DEFAULT_PEN_WDITH = 1;  ///< The default pen width.

// Default colours.
static  const   Gdiplus::ARGB   DEFAULT_FOREGROUND_COLOUR   = Gdiplus::Color::White;        ///< The default foreground colour.
static  const   Gdiplus::ARGB   DEFAULT_BACKGROUND_COLOUR   = Gdiplus::Color::Black;        ///< The default background colour.
static  const   Gdiplus::ARGB   DEFAULT_TEXT_COLOUR         = DEFAULT_FOREGROUND_COLOUR;    ///< The default text colour.
static  const   Gdiplus::ARGB   DEFAULT_PEN_COLOUR          = DEFAULT_FOREGROUND_COLOUR;    ///< The default pen colour.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
