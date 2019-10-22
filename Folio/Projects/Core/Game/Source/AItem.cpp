// "Home-made" includes.
#include    "AItem.h"

namespace Folio
{

namespace Core
{

namespace Game
{

AItem::AItem ()
:   m_itemId(ITEM_ID_UNDEFINED),
    m_screenXLeft(FOLIO_UNDEFINED),
    m_screenYTop(FOLIO_UNDEFINED),
    m_screenScale(1),
    m_foregroundColour(Folio::Core::Graphic::DEFAULT_FOREGROUND_COLOUR),
    m_backgroundColour(Folio::Core::Graphic::DEFAULT_BACKGROUND_COLOUR)
{
} // Endproc.


AItem::~AItem ()
{
} // Endproc.


AItem::Id   AItem::GetItemId () const
{
    return (m_itemId);
} // Endproc.


Gdiplus::ARGB   AItem::GetForegroundColour () const
{
    return (m_foregroundColour);
} // Endproc.


Gdiplus::ARGB   AItem::GetBackgroundColour () const
{
    return (m_backgroundColour);
} // Endproc.


DrawingElementsList AItem::GetDrawingElementsList () const
{
    return (m_drawingElementsList);
} // Endproc.


Gdiplus::Rect   AItem::GetScreenRect () const
{
    return (m_drawingElementsList.empty () ? Gdiplus::Rect () : m_drawingElementsList.back ().GetScreenRect ());
} // Endproc.


Int32   AItem::GetScreenXLeft () const
{
    return (m_drawingElementsList.empty () ? FOLIO_UNDEFINED : m_drawingElementsList.back ().GetScreenXLeft ());
} // Endproc.


Int32   AItem::GetScreenYTop () const
{
    return (m_drawingElementsList.empty () ? FOLIO_UNDEFINED : m_drawingElementsList.back ().GetScreenYTop ());
} // Endproc.


Int32   AItem::GetScreenXRight () const
{
    return (m_drawingElementsList.empty () ? FOLIO_UNDEFINED : m_drawingElementsList.back ().GetScreenXRight ());
} // Endproc.


Int32   AItem::GetScreenYBottom () const
{
    return (m_drawingElementsList.empty () ? FOLIO_UNDEFINED : m_drawingElementsList.back ().GetScreenYBottom ());
} // Endproc.


Int32   AItem::GetScreenWidth () const
{
    return (m_drawingElementsList.empty () ? FOLIO_UNDEFINED : m_drawingElementsList.back ().GetScreenWidth ());
} // Endproc.


Int32   AItem::GetScreenHeight () const
{
    return (m_drawingElementsList.empty () ? FOLIO_UNDEFINED : m_drawingElementsList.back ().GetScreenHeight ());
} // Endproc.


Folio::Core::Graphic::GdiGraphicElementPtr  AItem::GetGdiGraphicElement () const
{
    return (m_drawingElementsList.empty () ? Folio::Core::Graphic::GdiGraphicElementPtr() : m_drawingElementsList.back ().GetGdiGraphicElement ());
} // Endproc.


FolioStatus AItem::SetScreenTopLeft (Int32  screenXLeft,    
                                     Int32  screenYTop)
{
    return (m_drawingElementsList.empty () ? ERR_INVALID_SEQUENCE : m_drawingElementsList.back ().SetScreenTopLeft (screenXLeft, screenYTop));
} // Endproc.


FolioStatus AItem::Draw (Gdiplus::Graphics&                                     graphics,
                         Folio::Core::Graphic::AGdiGraphicElement::RectList*    rects)
{
    return (m_drawingElementsList.empty () ? ERR_INVALID_SEQUENCE : m_drawingElementsList.back ().Draw (graphics, rects));
} // Endproc.


FolioStatus AItem::Draw (Int32                                                  screenXLeft,    
                         Int32                                                  screenYTop,
                         Gdiplus::Graphics&                                     graphics,
                         Folio::Core::Graphic::AGdiGraphicElement::RectList*    rects)
{
    // Set the item's top-left position.

    FolioStatus status = SetScreenTopLeft (screenXLeft,  screenYTop);

    if (status == ERR_SUCCESS)
    {
        // Draw it.

        status = Draw (graphics, rects);
    } // Endif.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
