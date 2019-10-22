// "Home-made" includes.
#include    "TextItem.h"

namespace Folio
{

namespace Core
{

namespace Game
{

TextItem::TextItem ()
{   
} // Endproc.


TextItem::~TextItem ()
{
} // Endproc.


FolioStatus TextItem::Create (FolioHandle                           dcHandle,
                              DrawingElement::Id                    drawingElementId,
                              Folio::Core::Graphic::GdiRasterFont&  gdiRasterFont,
                              Id                                    itemId,
                              Int32                                 screenXLeft,
                              Int32                                 screenYTop,
                              UInt32                                screenScale,
                              Gdiplus::ARGB                         textColour,
                              Gdiplus::ARGB                         backgroundColour)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a text item already?

    if (IsCreated ())
    {
        // Yes.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // No. Note the item's attributes.

        m_itemId            = itemId;
        m_screenXLeft       = screenXLeft;
        m_screenYTop        = screenYTop;
        m_screenScale       = screenScale;
        m_foregroundColour  = textColour;
        m_backgroundColour  = backgroundColour;
    
        // Create a GDI raster text.

        m_gdiRasterText.reset (new Folio::Core::Graphic::GdiRasterTextPtr::element_type(gdiRasterFont, 
                                                                                        textColour,
                                                                                        backgroundColour));

        if (status == ERR_SUCCESS)
        {
            // Scale the GDI raster text.

            m_gdiRasterText->SetScreenScale (screenScale);

            // Add the GDI raster text to the list of drawing elements.

            m_drawingElementsList.push_back (DrawingElement(drawingElementId,
                                                            screenXLeft, 
                                                            screenYTop,
                                                            m_gdiRasterText,
                                                            this)); // Drawing element user data.
        } // Endif.
    
    } // Endelse.

    return (status);
} // Endproc.


Folio::Core::Graphic::GdiRasterTextPtr  TextItem::GetGdiRasterText () const
{
    return (std::dynamic_pointer_cast<Folio::Core::Graphic::GdiRasterText> (GetGdiGraphicElement ()));
} // Endproc.


bool    TextItem::IsCreated () const
{
    return (m_gdiRasterText != 0);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
