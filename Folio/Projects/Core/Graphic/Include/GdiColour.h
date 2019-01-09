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

namespace Colour
{

// Routines.
void    ChangeColourIntensity (Int32            intensity, 
                               Gdiplus::Color&  colour);
void    ChangeAlphaIntensity (Int32             intensity, 
                              Gdiplus::Color&   colour);
void    ChangeRedIntensity (Int32           intensity, 
                            Gdiplus::Color& colour);
void    ChangeGreenIntensity (Int32             intensity, 
                              Gdiplus::Color&   colour);
void    ChangeBlueIntensity (Int32              intensity, 
                             Gdiplus::Color&    colour);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
