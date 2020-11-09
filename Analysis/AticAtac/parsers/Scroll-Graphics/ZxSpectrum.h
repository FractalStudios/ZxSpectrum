#pragma once

#include <string>

#pragma pack(push, 1)

namespace ZxSpectrum
{

// Definitions and Types.

// Default colour.

static  const   COLORREF    DEFAULT_COLOUR = RGB(0xc0, 0xc0, 0xc0);


// Routines.

extern  std::wstring    DescribeAttribute (BYTE byAttribute);
extern  std::wstring    DescribeColour (BYTE byColour);

extern  COLORREF    MapInkColour (BYTE byColour);

}; // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
