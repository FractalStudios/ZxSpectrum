// "Home-made" includes.
#include    "DrawingElement.h"

namespace Folio
{

namespace Core
{

namespace Game
{

DrawingElement::DrawingElement (Id                                                  id,
                                Int32                                               screenXLeft,
                                Int32                                               screenYTop,
                                const Folio::Core::Graphic::GdiGraphicElementPtr&   gdiGraphicElement,
                                UserData                                            userData,
                                UInt32                                              collisionGridCellValue)
:   m_id(id),
    m_screenRect(screenXLeft, screenYTop, gdiGraphicElement->GetScreenWidth (), gdiGraphicElement->GetScreenHeight ()),
    m_userData(userData),
    m_collisionGridCellValue(collisionGridCellValue),
    m_gdiGraphicElement(gdiGraphicElement)
{
} // Endproc.


DrawingElement::~DrawingElement ()
{
} // Endproc.


FolioStatus DrawingElement::SetScreenTopLeft (Int32 screenXLeft,    
                                              Int32 screenYTop)
{
    m_screenRect.X = screenXLeft;
    m_screenRect.Y = screenYTop;

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus DrawingElement::Draw (Gdiplus::Graphics&                                    graphics,
                                  Folio::Core::Graphic::AGdiGraphicElement::RectList*   rects)
{
    return (m_gdiGraphicElement->Draw (m_screenRect.X, m_screenRect.Y, graphics, rects));
} // Endproc.


FolioStatus DrawingElement::Draw (Int32                                                 screenXLeft,    
                                  Int32                                                 screenYTop,
                                  Gdiplus::Graphics&                                    graphics,
                                  Folio::Core::Graphic::AGdiGraphicElement::RectList*   rects)
{
    // Set the screen position.

    FolioStatus status = SetScreenTopLeft (screenXLeft,  screenYTop);

    if (status == ERR_SUCCESS)
    {
        // Draw it.

        status = m_gdiGraphicElement->Draw (m_screenRect.X, m_screenRect.Y, graphics, rects);
    } // Endif.

    return (status);
} // Endproc.


DrawingElement::Id  DrawingElement::GetDrawingElementId () const
{
    return (m_id);
} // Endproc.


Folio::Core::Graphic::GdiGraphicElementPtr  DrawingElement::GetGdiGraphicElement () const
{
    return (m_gdiGraphicElement);
} // Endproc.


Gdiplus::Rect   DrawingElement::GetScreenRect () const
{
    return (m_screenRect);
} // Endproc.


Int32   DrawingElement::GetScreenXLeft () const
{
    return (m_screenRect.X);
} // Endproc.


Int32   DrawingElement::GetScreenYTop () const
{
    return (m_screenRect.Y);
} // Endproc.


Int32   DrawingElement::GetScreenXRight () const
{
    return (m_screenRect.X + m_screenRect.Width - 1);
} // Endproc.


Int32   DrawingElement::GetScreenYBottom () const
{
    return (m_screenRect.Y + m_screenRect.Height - 1);
} // Endproc.


Int32   DrawingElement::GetScreenWidth () const
{
    return (m_screenRect.Width);
} // Endproc.


Int32   DrawingElement::GetScreenHeight () const
{
    return (m_screenRect.Height);
} // Endproc.


void    DrawingElement::SetUserData (const UserData& userData)
{
    m_userData = userData;
} // Endproc.


DrawingElement::UserData    DrawingElement::GetUserData () const
{
    return (m_userData);
} // Endproc.


void    DrawingElement::SetCollisionGridCellValue (UInt32 collisionGridCellValue)
{
    m_collisionGridCellValue = collisionGridCellValue;
} // Endproc.


UInt32  DrawingElement::GetCollisionGridCellValue () const
{
    return (m_collisionGridCellValue);
} // Endproc.


bool    DrawingElement::IsOverlap (const Gdiplus::Rect &screenRect) const
{
    return (!((m_screenRect.X > (  screenRect.X +   screenRect.Width  - 1)) ||
                (screenRect.X > (m_screenRect.X + m_screenRect.Width  - 1)) ||
              (m_screenRect.Y > (  screenRect.Y +   screenRect.Height - 1)) ||
                (screenRect.Y > (m_screenRect.Y + m_screenRect.Height - 1))));
} // Endproc.


bool    DrawingElement::operator < (const DrawingElement &rhs) const
{
    return (m_id < rhs.m_id);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
