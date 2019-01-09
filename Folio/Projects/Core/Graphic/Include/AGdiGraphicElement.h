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

    virtual FolioStatus SetScreenTopLeft (Int32 screenXLeft,    
                                          Int32 screenYTop) = 0;
    virtual FolioStatus Draw (Gdiplus::Graphics&    graphics,
                              RectList*             rects) = 0;

    Gdiplus::Rect   GetScreenRect () const;
    Int32           GetScreenXLeft () const;
    Int32           GetScreenYTop () const;
    Int32           GetScreenXRight () const;
    Int32           GetScreenYBottom () const;
    Int32           GetScreenWidth () const;
    Int32           GetScreenHeight () const;

    void    SetScreenScale (UInt32 screenScale);
    UInt32  GetScreenScale () const;

    bool    IsOverlap (const Gdiplus::Rect& screenRect) const;

protected:
    Gdiplus::Rect   m_screenRect;   ///< The screen rect of the graphic element (not scaled).
    UInt32          m_screenScale;  ///< The screen scale of the graphic element.
    Gdiplus::Rect   m_scaledRect;   ///< The scaled rect of the graphic element.

    AGdiGraphicElement ();

    virtual void    SetScreenRect (const Gdiplus::Rect& screenRect);
    virtual void    SetScreenScaledRect ();

    void    Clone (const AGdiGraphicElement& rhs);
}; // Endclass.

/// GDI graphic element pointer.
typedef std::shared_ptr<AGdiGraphicElement> GdiGraphicElementPtr;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
