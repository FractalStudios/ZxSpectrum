#pragma once

// STL includes.
#include    <memory>
#include    <vector>

// "Home-made" includes.
#include    "GraphicConstsAndTypes.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Graphic
{

/// The GDI graphic element abstract class.
/**
 * This class provides for an abstract GDI graphic element.
 */
class AGdiGraphicElement
{
public: 
    /// The rect list.
    typedef std::vector<Gdiplus::Rect>  RectList;

    virtual ~AGdiGraphicElement ();

    virtual FolioStatus Draw (Int32                 screenXLeft,    
                              Int32                 screenYTop,
                              Gdiplus::Graphics&    graphics,
                              RectList*             rects) = 0;

    Int32   GetScreenWidth () const;
    Int32   GetScreenHeight() const;

    void    SetScreenScale (UInt32 screenScale);
    UInt32  GetScreenScale () const;

    Gdiplus::Rect   GetScaledRect  (Int32   screenXLeft,
                                    Int32   screenYTop) const;
    Int32   GetScaledWidth () const;
    Int32   GetScaledHeight() const;

protected:
    Int32   m_screenWidth;  ///< The screen width of the graphic element.
    Int32   m_screenHeight; ///< The screen height of the graphic element.
    UInt32  m_screenScale;  ///< The screen scale of the graphic element.
    Int32   m_scaledWidth;  ///< The scaled width of the graphic element.
    Int32   m_scaledHeight; ///< The scaled height of the graphic element.

    AGdiGraphicElement ();

    void    SetScreenWidth (Int32 screenWidth);
    void    SetScreenHeight (Int32 screenHeight);

    void    Clone (const AGdiGraphicElement& rhs);
}; // Endclass.

/// GDI graphic element pointer.
typedef std::shared_ptr<AGdiGraphicElement> GdiGraphicElementPtr;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
