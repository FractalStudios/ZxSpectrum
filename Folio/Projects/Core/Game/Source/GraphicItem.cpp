// "Home-made" includes.
#include    "ResourceGraphic.h"
#include    "GraphicItem.h"

namespace Folio
{

namespace Core
{

namespace Game
{

GraphicItem::GraphicItem ()
{
} // Endproc.


GraphicItem::~GraphicItem ()
{
} // Endproc.


FolioStatus GraphicItem::Create (FolioHandle                                dcHandle,
                                 FolioHandle                                instanceHandle,
                                 const DrawingElement::DrawingElementId&    drawingElementId,
                                 UInt16                                     bitmapResourceId,
                                 Id                                         itemId,
                                 Int32                                      screenXLeft,
                                 Int32                                      screenYTop,
                                 UInt32                                     screenScale,
                                 bool                                       maskedBitmapDrawingElementRqd,
                                 Gdiplus::ARGB                              maskColour)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a graphic item already?

    if (IsCreated ())
    {
        // Yes.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // No. Note the item's attributes.

        m_itemId        = itemId;
        m_screenXLeft   = screenXLeft;
        m_screenYTop    = screenYTop;
        m_screenScale   = screenScale;
    
        // Create a resource graphic.

        m_resourceGraphic.reset (new ResourceGraphicPtr::element_type);

        status = m_resourceGraphic->Create (instanceHandle,
                                            drawingElementId,
                                            bitmapResourceId,
                                            maskedBitmapDrawingElementRqd,
                                            ACollisionGrid::CELL_VALUE_EMPTY,
                                            0,
                                            maskColour);

        if (status == ERR_SUCCESS)
        {
            // Create the drawing elements.

            status = CreateDrawingElements (dcHandle,
                                            drawingElementId,
                                            screenXLeft,
                                            screenYTop,
                                            screenScale);
        } // Endif.

    } // Endelse.

    return (status);
} // Endproc.


FolioStatus GraphicItem::Create (FolioHandle                                dcHandle,
                                 FolioHandle                                instanceHandle,
                                 const DrawingElement::DrawingElementId&    drawingElementId,
                                 UInt16                                     bitmapResourceId,
                                 Id                                         itemId,
                                 Int32                                      screenXLeft,
                                 Int32                                      screenYTop,
                                 UInt32                                     screenScale,
                                 Gdiplus::ARGB                              changeColour,
                                 Gdiplus::ARGB                              foregroundColour,
                                 Gdiplus::ARGB                              backgroundColour,
                                 bool                                       maskedBitmapDrawingElementRqd,
                                 Gdiplus::ARGB                              maskColour)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a graphic item already?

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
        m_foregroundColour  = foregroundColour;
        m_backgroundColour  = backgroundColour;
    
        // Create a resource graphic.

        m_resourceGraphic.reset (new ResourceGraphicPtr::element_type);

        status = m_resourceGraphic->Create (instanceHandle,
                                            drawingElementId,
                                            bitmapResourceId,
                                            changeColour,
                                            maskedBitmapDrawingElementRqd,
                                            ACollisionGrid::CELL_VALUE_EMPTY,
                                            0,
                                            maskColour);

        if (status == ERR_SUCCESS)
        {
            // Create the drawing elements.

            status = CreateDrawingElements (dcHandle,
                                            drawingElementId,
                                            screenXLeft,
                                            screenYTop,
                                            screenScale,
                                            foregroundColour);
        } // Endif.

    } // Endelse.

    return (status);
} // Endproc.


FolioStatus GraphicItem::Create (FolioHandle                dcHandle,
                                 const ResourceGraphicPtr&  resourceGraphic,
                                 Id                         itemId,
                                 Int32                      screenXLeft,
                                 Int32                      screenYTop,
                                 UInt32                     screenScale)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a graphic item already?

    if (IsCreated ())
    {
        // Yes.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // No. Note the item's attributes.

        m_itemId        = itemId;
        m_screenXLeft   = screenXLeft;
        m_screenYTop    = screenYTop;
        m_screenScale   = screenScale;

        m_resourceGraphic = resourceGraphic;

        // Create the drawing elements.

        status = CreateDrawingElements (dcHandle,
                                        m_resourceGraphic->GetDrawingElementId (),
                                        screenXLeft,
                                        screenYTop,
                                        screenScale);
    } // Endelse.

    return (status);
} // Endproc.


FolioStatus GraphicItem::QueryDrawingElements (FolioHandle              dcHandle,
                                               Gdiplus::ARGB            foregroundColour,
                                               DrawingElementsList&     drawingElementsList)
{
    FolioStatus status = ERR_SUCCESS;

    drawingElementsList.clear ();   // Initialise!

    // Have we created a graphic item?

    if (IsCreated ())
    {
        // Yes. Has the item's foreground colour changed?

        if (m_foregroundColour != foregroundColour)
        {
            // Yes. Note the item's foreground colour.

            m_foregroundColour = foregroundColour;

            m_drawingElementsList.clear (); // Initialise!

            status = m_resourceGraphic->QueryDrawingElements (dcHandle,
                                                              m_screenXLeft,
                                                              m_screenYTop,
                                                              m_screenScale,
                                                              m_foregroundColour,
                                                              ResourceGraphic::NO_DRAWING_FLAGS,
                                                              this, // Drawing element user data.
                                                              m_drawingElementsList);
        } // Endif.

        if ((status == ERR_SUCCESS) && !m_drawingElementsList.empty ())
        {
            drawingElementsList = m_drawingElementsList;
        } // Endif.

    } // Endif.

    else
    {
        // No.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


Folio::Core::Graphic::GdiBitmapPtr  GraphicItem::GetGdiBitmap () const
{
    return (std::dynamic_pointer_cast<Folio::Core::Graphic::GdiBitmap> (GetGdiGraphicElement ()));
} // Endproc.


FolioStatus GraphicItem::CreateDrawingElements (FolioHandle                             dcHandle,
                                                const DrawingElement::DrawingElementId& drawingElementId,
                                                Int32                                   screenXLeft,
                                                Int32                                   screenYTop,
                                                UInt32                                  screenScale)
{
    m_drawingElementsList.clear (); // Initialise!

    // Query the resource graphic's drawing elements.

    return (m_resourceGraphic->QueryDrawingElements (dcHandle,
                                                     screenXLeft,
                                                     screenYTop,
                                                     screenScale,
                                                     ResourceGraphic::NO_DRAWING_FLAGS,
                                                     this, // Drawing element user data.
                                                     m_drawingElementsList));
} // Endproc.


FolioStatus GraphicItem::CreateDrawingElements (FolioHandle                             dcHandle,
                                                const DrawingElement::DrawingElementId& drawingElementId,
                                                Int32                                   screenXLeft,
                                                Int32                                   screenYTop,
                                                UInt32                                  screenScale,
                                                Gdiplus::ARGB                           foregroundColour)
{
    m_drawingElementsList.clear (); // Initialise!

    // Query the resource graphic's drawing elements.

    return (m_resourceGraphic->QueryDrawingElements (dcHandle,
                                                     screenXLeft,
                                                     screenYTop,
                                                     screenScale,
                                                     foregroundColour,
                                                     ResourceGraphic::NO_DRAWING_FLAGS,
                                                     this, // Drawing element user data.
                                                     m_drawingElementsList));
} // Endproc.


bool    GraphicItem::IsCreated () const
{
    return (m_resourceGraphic != 0);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
