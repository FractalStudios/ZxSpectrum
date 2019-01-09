#pragma once

// Windows includes.
#define NOMINMAX
#include    <Windows.h>

// STL includes.
#include    <algorithm>
#include    <vector>

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

namespace Physics
{

/// The graphic element interface class.
/**
 * This class provides for an interface to a graphic element.
 */
class IGraphicElement
{
public:    
    /// The rect list.
    typedef std::vector<Gdiplus::Rect>  RectList;

    virtual ~IGraphicElement ();

    virtual FolioStatus Draw (Gdiplus::Graphics&    graphics,
                              RectList*             rects) = 0;
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
