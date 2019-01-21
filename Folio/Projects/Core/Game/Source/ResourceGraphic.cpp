// "Home-made" includes.
#include    "ResourceGraphic.h"

namespace Folio
{

namespace Core
{

namespace Game
{

ResourceGraphic::ResourceGraphic ()
:   m_drawingElementId(DrawingElement::DRAWING_ELEMENT_ID_UNDEFINED),
    m_bitmapResourceId(FOLIO_UNDEFINED),
    m_colourTableIndex(FOLIO_INVALID_INDEX),
    m_collisionGridCellValue(CollisionGrid::CELL_VALUE_EMPTY),
    m_maskedGdiBitmapRqd(false),
    m_maskColour(Folio::Core::Graphic::DEFAULT_BACKGROUND_COLOUR)
{
} // Endproc.


ResourceGraphic::~ResourceGraphic ()
{
} // Endproc.


FolioStatus ResourceGraphic::Create (FolioHandle                dcHandle,
                                     FolioHandle                instanceHandle,
                                     DrawingElement::Id         drawingElementId,
                                     UInt16                     bitmapResourceId,
                                     bool                       maskedGdiBitmapRqd,
                                     CollisionGrid::CellValue   collisionGridCellValue,
                                     Gdiplus::ARGB              maskColour)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a resource graphic already?

    if (IsCreated ())
    {
        // Yes.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // No. Create the resource graphic.
    
        // Create a device-independent GDI bitmap.

        m_gdiDiBitmap.reset (new Folio::Core::Graphic::GdiDiBitmapPtr::element_type);
    
        status = m_gdiDiBitmap->Create (instanceHandle, bitmapResourceId);
    
        if (status == ERR_SUCCESS)
        {
            // Note the resource graphic's attributes.

            m_drawingElementId          = drawingElementId;
            m_bitmapResourceId          = bitmapResourceId;
            m_maskedGdiBitmapRqd        = maskedGdiBitmapRqd;
            m_maskColour                = maskColour;
            m_collisionGridCellValue    = collisionGridCellValue;
        } // Endif.

    } // Endelse.

    return (status);
} // Endproc.


FolioStatus ResourceGraphic::Create (FolioHandle                dcHandle,
                                     FolioHandle                instanceHandle,
                                     DrawingElement::Id         drawingElementId,
                                     UInt16                     bitmapResourceId,
                                     Gdiplus::ARGB              changeColour, 
                                     bool                       maskedGdiBitmapRqd,
                                     CollisionGrid::CellValue   collisionGridCellValue,
                                     Gdiplus::ARGB              maskColour)
{
    // Create the resource graphic.

    FolioStatus status = Create (dcHandle,
                                 instanceHandle,
                                 drawingElementId,
                                 bitmapResourceId,
                                 maskedGdiBitmapRqd,
                                 collisionGridCellValue,
                                 maskColour);

    if (status == ERR_SUCCESS)
    {
        // Get the colour table index of the GDI bitmap colour to change.

        m_colourTableIndex = m_gdiDiBitmap->GetColourTableIndex (changeColour);

        if (m_colourTableIndex == FOLIO_INVALID_INDEX)
        {
            status = ERR_INVALID;
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus ResourceGraphic::Create (FolioHandle                dcHandle,
                                     FolioHandle                instanceHandle,
                                     DrawingElement::Id         drawingElementId,
                                     UInt16                     bitmapResourceId,
                                     Gdiplus::ARGB              changeColour, 
                                     Gdiplus::ARGB              newColour, 
                                     bool                       maskedGdiBitmapRqd,
                                     CollisionGrid::CellValue   collisionGridCellValue,
                                     Gdiplus::ARGB              maskColour)
{
    // Create the resource graphic.

    FolioStatus status = Create (dcHandle,
                                 instanceHandle,
                                 drawingElementId,
                                 bitmapResourceId,
                                 maskedGdiBitmapRqd,
                                 collisionGridCellValue,
                                 maskColour);

    if (status == ERR_SUCCESS)
    {
        // Change the colour of the device-independent GDI bitmap element.

        status = m_gdiDiBitmap->ChangeColour (changeColour,
                                              newColour, 
                                              m_colourTableIndex);

        if ((status == ERR_SUCCESS) && (m_colourTableIndex == FOLIO_INVALID_INDEX))
        {
            status = ERR_INVALID;
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus ResourceGraphic::ChangeColour (Gdiplus::ARGB changeColour)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a resource graphic?

    if (IsCreated ())
    {
        if (m_colourTableIndex != FOLIO_INVALID_INDEX)
        {
            // Change the colour of the device-independent GDI bitmap.

            status = m_gdiDiBitmap->ChangeColour (m_colourTableIndex, changeColour);
        } // Endif. 

    } // Endif.

    else
    {
        // No.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);

} // Endproc.


FolioStatus ResourceGraphic::QueryDrawingElements (FolioHandle                      dcHandle,
                                                   Int32                            screenXLeft,
                                                   Int32                            screenYTop,
                                                   UInt32                           screenScale,
                                                   UInt32                           drawingFlags,
                                                   const DrawingElement::UserData&  drawingElementUserData,
                                                   DrawingElementsList              &drawingElementsList,
                                                   bool                             maskedDrawingElementRqd)
{
    static  const   double PI = 3.14159265358979323846; // PI.

    // Rotation.
    struct Rotation
    {
        UInt32  m_rotation;
        double  m_radians;
    }; // Endstruct.

    // Rotation table.
    static  const   Rotation    s_rotationTable [] =
    {
    //      m_rotation          m_radians
        {   ROTATION_NONE,      0,          },
        {   ROTATION_180,       PI,         },
        {   ROTATION_LEFT_90,   PI / 2,     },
        {   ROTATION_RIGHT_90,  -PI / 2,    },
    }; 

    FolioStatus status = ERR_SUCCESS;

    drawingElementsList.clear ();   // Initialise!

    // Have we created a resource graphic?

    if (IsCreated ())
    {
        // Yes. Create a device-independent GDI bitmap.

        Folio::Core::Graphic::GdiDiBitmapPtr    gdiDiBitmap(new Folio::Core::Graphic::GdiDiBitmapPtr::element_type);

        // Should the GDI bitmap be rotated?

        if (IsRotated (drawingFlags))
        {
            // Yes. Rotate the device-independent GDI bitmap.

            status = gdiDiBitmap->Create (*m_gdiDiBitmap,
                                          s_rotationTable [(drawingFlags & ROTATION_MASK) >> 2].m_radians,
                                          Folio::Core::Graphic::DEFAULT_BACKGROUND_COLOUR);
        } // Endif.

        else
        {
            // No. Copy the device-independent GDI bitmap.

            *gdiDiBitmap = *m_gdiDiBitmap;
        } // Endelse.

        if (status == ERR_SUCCESS)
        {
            // Create the GDI bitmap from the device-independent GDI bitmap.

            Folio::Core::Graphic::GdiBitmapPtr  gdiBitmap(new Folio::Core::Graphic::GdiBitmapPtr::element_type);

            status = gdiBitmap->Create (dcHandle, *gdiDiBitmap);

            if (status == ERR_SUCCESS)
            {
                // Is a masked GDI bitmap required?

                if (m_maskedGdiBitmapRqd && maskedDrawingElementRqd)
                {
                    // Yes. Create the masked GDI bitmap from the GDI bitmap.

                    Folio::Core::Graphic::GdiBitmapPtr  maskedBitmapDrawingElement;

                    status = CreateMaskedBitmapDrawingElement (dcHandle, 
                                                               gdiBitmap,
                                                               m_maskColour,
                                                               screenXLeft,
                                                               screenYTop,
                                                               screenScale,
                                                               drawingFlags,
                                                               maskedBitmapDrawingElement);

                    if (status == ERR_SUCCESS)
                    {
                        // Add the masked GDI bitmap to the list of drawing elements.

                        drawingElementsList.push_back (DrawingElement(m_drawingElementId,
                                                                      maskedBitmapDrawingElement,
                                                                      drawingElementUserData,
                                                                      m_collisionGridCellValue));

                        // Makes sure and set the GDI bitmap's drawing mode.

                        gdiBitmap->SetDrawingMode (SRCPAINT);
                    } // Endif.
                    
                } // Endif.

                if (status == ERR_SUCCESS)
                {
                    // Should the GDI bitmap be flipped?

                    if (IsFlipped (drawingFlags))
                    {
                        // Yes. Flip the GDI bitmap.

                        gdiBitmap->SetDrawingFlip (IsFlipHorizontal (drawingFlags), 
                                                   IsFlipVertical (drawingFlags));
                    } // Endif.

                    // Set the GDI bitmap's top-left screen position.

                    status = gdiBitmap->SetScreenTopLeft (screenXLeft, screenYTop);

                    if (status == ERR_SUCCESS)
                    {
                        // Scale the GDI bitmap.

                        gdiBitmap->SetScreenScale (screenScale);

                        // Add the GDI bitmap to the list of drawing elements.

                        drawingElementsList.push_back (DrawingElement(m_drawingElementId,
                                                                      gdiBitmap, 
                                                                      drawingElementUserData,
                                                                      m_collisionGridCellValue));
                    } // Endif.

                } // Endif.

            } // Endif.
    
        } // Endif.

        if (status != ERR_SUCCESS)
        {
            drawingElementsList.clear ();
        } // Endif.

    } // Endif.

    else
    {
        // No.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


FolioStatus ResourceGraphic::QueryDrawingElements (FolioHandle                      dcHandle,
                                                   Int32                            screenXLeft,
                                                   Int32                            screenYTop,
                                                   UInt32                           screenScale,
                                                   Gdiplus::ARGB                    colour, 
                                                   UInt32                           drawingFlags,
                                                   const DrawingElement::UserData&  drawingElementUserData,
                                                   DrawingElementsList              &drawingElementsList,
                                                   bool                             maskedDrawingElementRqd)
{
    FolioStatus status = ERR_SUCCESS;

    drawingElementsList.clear ();   // Initialise!

    // Have we created a resource graphic?

    if (IsCreated ())
    {
        if (m_colourTableIndex != FOLIO_INVALID_INDEX)
        {
            // Change the colour of the device-independent GDI bitmap.

            status = m_gdiDiBitmap->ChangeColour (m_colourTableIndex, colour);
        } // Endif. 
          
        if (status == ERR_SUCCESS)
        {
            // Query the resource graphic's drawing elements.

            status = QueryDrawingElements (dcHandle,
                                           screenXLeft,
                                           screenYTop,
                                           screenScale,
                                           drawingFlags,
                                           drawingElementUserData,
                                           drawingElementsList,
                                           maskedDrawingElementRqd);
        } // Endif.

        else
        {
            drawingElementsList.clear ();
        } // Endelse.

    } // Endif.

    else
    {
        // No.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


DrawingElement::Id  ResourceGraphic::GetDrawingElementId () const
{
    return (m_drawingElementId);
} // Endproc.


UInt16  ResourceGraphic::GetBitmapResourceId () const
{
    return (m_bitmapResourceId);
} // Endproc.


UInt32  ResourceGraphic::GetChangeColourTableIndex () const
{
    return (m_colourTableIndex);
} // Endproc.


CollisionGrid::CellValue    ResourceGraphic::GetCollisionGridCellValue () const
{
    return (m_collisionGridCellValue);
} // Endproc.


bool    ResourceGraphic::IsMaskedBitmapDrawingElementRqd () const
{
    return (m_maskedGdiBitmapRqd);
} // Endproc.


Gdiplus::ARGB   ResourceGraphic::GetMaskColour () const
{
    return (m_maskColour);
} // Endproc.


Folio::Core::Graphic::GdiDiBitmapPtr    ResourceGraphic::GetGdiDiBitmap () const
{
    return (m_gdiDiBitmap);
} // Endproc.


UInt32  ResourceGraphic::GetGraphicWidth () const
{
    return (m_gdiDiBitmap ? m_gdiDiBitmap->GetBitmapWidth () : FOLIO_UNDEFINED);
} // Endproc.


UInt32  ResourceGraphic::GetGraphicHeight () const
{
    return (m_gdiDiBitmap ? m_gdiDiBitmap->GetBitmapHeight() : FOLIO_UNDEFINED);
} // Endproc.


UInt32  ResourceGraphic::GetOrientation (UInt32 drawingFlags)
{
    return (drawingFlags & ORIENTATION_MASK);
} // Endproc.


bool    ResourceGraphic::IsOrientationTop (UInt32 drawingFlags)
{
    return (GetOrientation (drawingFlags) == ORIENTATION_TOP);
} // Endproc.


bool    ResourceGraphic::IsOrientationBottom (UInt32 drawingFlags)
{
    return (GetOrientation (drawingFlags) == ORIENTATION_BOTTOM);
} // Endproc.


bool    ResourceGraphic::IsOrientationLeft (UInt32 drawingFlags)
{
    return (GetOrientation (drawingFlags) == ORIENTATION_LEFT);
} // Endproc.


bool    ResourceGraphic::IsOrientationRight (UInt32 drawingFlags)
{
    return (GetOrientation (drawingFlags) == ORIENTATION_RIGHT);
} // Endproc.


UInt32  ResourceGraphic::GetRotation (UInt32 drawingFlags)
{
    return (drawingFlags & ROTATION_MASK);
} // Endproc.


bool    ResourceGraphic::IsRotated (UInt32 drawingFlags)
{
    return (GetRotation (drawingFlags) != ROTATION_NONE);
} // Endproc.


bool    ResourceGraphic::IsRotation180 (UInt32 drawingFlags)
{
    return (GetRotation (drawingFlags) == ROTATION_180);
} // Endproc.


bool    ResourceGraphic::IsRotationLeft90 (UInt32 drawingFlags)
{
    return (GetRotation (drawingFlags) == ROTATION_LEFT_90);
} // Endproc.


bool    ResourceGraphic::IsRotationRight90 (UInt32 drawingFlags)
{
    return (GetRotation (drawingFlags) == ROTATION_RIGHT_90);
} // Endproc.


UInt32  ResourceGraphic::GetFlip (UInt32 drawingFlags)
{
    return (drawingFlags & FLIP_MASK);
} // Endproc.


bool    ResourceGraphic::IsFlipped (UInt32 drawingFlags)
{
    return (GetFlip (drawingFlags) != FLIP_NONE);
} // Endproc.


bool    ResourceGraphic::IsFlipHorizontal (UInt32 drawingFlags)
{
    return (GetFlip (drawingFlags) == FLIP_HORIZONTAL);
} // Endproc.


bool    ResourceGraphic::IsFlipVertical (UInt32 drawingFlags)
{
    return (GetFlip (drawingFlags) == FLIP_VERTICAL);
} // Endproc.


FolioStatus ResourceGraphic::CreateMaskedBitmapDrawingElement (FolioHandle                                  dcHandle,
                                                               const Folio::Core::Graphic::GdiBitmapPtr&    gdiBitmap,
                                                               Gdiplus::ARGB                                maskColour,
                                                               Int32                                        screenXLeft,
                                                               Int32                                        screenYTop,
                                                               UInt32                                       screenScale,
                                                               UInt32                                       drawingFlags,
                                                               Folio::Core::Graphic::GdiBitmapPtr&          maskedBitmapDrawingElement)
{
    // Create the masked GDI bitmap drawing element.

    maskedBitmapDrawingElement.reset (new Folio::Core::Graphic::GdiBitmapPtr::element_type);

    FolioStatus status = maskedBitmapDrawingElement->Create (dcHandle,
                                                             *gdiBitmap, 
                                                             maskColour);

    if (status == ERR_SUCCESS)
    {
        // Set the masked GDI bitmap drawing element's drawing mode.

        maskedBitmapDrawingElement->SetDrawingMode (SRCAND);

        // Should the masked GDI bitmap be flipped?

        if (IsFlipped (drawingFlags))
        {
            // Yes. Flip the masked GDI bitmap drawing element.

            maskedBitmapDrawingElement->SetDrawingFlip (IsFlipHorizontal (drawingFlags), 
                                                        IsFlipVertical (drawingFlags));
        } // Endif.

        // Set the masked GDI bitmap drawing element's top-left screen position.

        status = maskedBitmapDrawingElement->SetScreenTopLeft (screenXLeft, screenYTop);

        if (status == ERR_SUCCESS)
        {
            // Scale the masked GDI bitmap drawing element.

            maskedBitmapDrawingElement->SetScreenScale (screenScale);
        } // Endif.
    
    } // Endif.

    return (status);
} // Endproc.


bool    ResourceGraphic::IsCreated () const
{
    return (m_gdiDiBitmap.get () != 0);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
