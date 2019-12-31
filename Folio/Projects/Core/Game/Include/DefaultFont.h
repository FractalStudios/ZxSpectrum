#pragma once

// STL includes.
#include    <memory>

// "Home-made" includes.
#include    <Graphic.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Game
{

namespace ZxSpectrum
{

// The font pointer.
typedef std::shared_ptr<Folio::Core::Graphic::GdiRasterFont>    FontPtr;


// Routines.

extern  FontPtr GetFont ();

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
