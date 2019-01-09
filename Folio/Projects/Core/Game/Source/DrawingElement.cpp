// "Home-made" includes.
#include    "DrawingElement.h"

namespace Folio
{

namespace Core
{

namespace Game
{

DrawingElement::DrawingElement (Id                                                  id,
                                const Folio::Core::Graphic::GdiGraphicElementPtr&   gdiGraphicElement,
                                UserData                                            userData,
                                UInt32                                              collisionGridCellValue)
:   m_id(id),
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
    return (m_gdiGraphicElement->SetScreenTopLeft (screenXLeft, screenYTop));
} // Endproc.


FolioStatus DrawingElement::Draw (Gdiplus::Graphics&                                    graphics,
                                  Folio::Core::Graphic::AGdiGraphicElement::RectList*   rects)
{
    return (m_gdiGraphicElement->Draw (graphics, rects));
} // Endproc.


DrawingElement::Id  DrawingElement::GetDrawingElementId () const
{
    return (m_id);
} // Endproc.


Folio::Core::Graphic::GdiGraphicElementPtr  DrawingElement::GetGdiGraphicElement () const
{
    return (m_gdiGraphicElement);
} // Endproc.


void    DrawingElement::SetCollisionGridCellValue (UInt32 collisionGridCellValue)
{
    m_collisionGridCellValue = collisionGridCellValue;
} // Endproc.


UInt32  DrawingElement::GetCollisionGridCellValue () const
{
    return (m_collisionGridCellValue);
} // Endproc.


void    DrawingElement::SetUserData (const UserData& userData)
{
    m_userData = userData;
} // Endproc.


DrawingElement::UserData    DrawingElement::GetUserData () const
{
    return (m_userData);
} // Endproc.


Gdiplus::Rect   DrawingElement::GetScreenRect () const
{
    return (m_gdiGraphicElement->GetScreenRect ());
} // Endproc.


Int32   DrawingElement::GetScreenXLeft () const
{
    return (m_gdiGraphicElement->GetScreenXLeft ());
} // Endproc.


Int32   DrawingElement::GetScreenYTop () const
{
    return (m_gdiGraphicElement->GetScreenYTop ());
} // Endproc.


Int32   DrawingElement::GetScreenXRight () const
{
    return (m_gdiGraphicElement->GetScreenXRight ());
} // Endproc.


Int32   DrawingElement::GetScreenYBottom () const
{
    return (m_gdiGraphicElement->GetScreenYBottom ());
} // Endproc.


Int32   DrawingElement::GetScreenWidth () const
{
    return (m_gdiGraphicElement->GetScreenWidth ());
} // Endproc.


Int32   DrawingElement::GetScreenHeight () const
{
    return (m_gdiGraphicElement->GetScreenHeight ());
} // Endproc.


bool    DrawingElement::IsOverlap (const Gdiplus::Rect &screenRect) const
{
    return (m_gdiGraphicElement->IsOverlap (screenRect));
} // Endproc.


bool    DrawingElement::operator < (const DrawingElement &rhs) const
{
    return (m_id < rhs.m_id);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
