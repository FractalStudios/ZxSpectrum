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
    m_collisionGridCellValue(ACollisionGrid::CELL_VALUE_EMPTY),
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
                                     ACollisionGrid::CellValue  collisionGridCellValue,
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
                                     ACollisionGrid::CellValue  collisionGridCellValue,
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
                                     ACollisionGrid::CellValue  collisionGridCellValue,
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

            if ((status == ERR_SUCCESS) && m_gdiBitmap)
            {
                // Destroy the GDI bitmap.

                m_gdiBitmap.reset ();
            } // Endif.

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
    FolioStatus status = ERR_SUCCESS;

    drawingElementsList.clear ();   // Initialise!

    // Have we created a resource graphic?

    if (IsCreated ())
    {
        // Yes. Is a new drawing element required?
        
        bool    isNewDrawingElementRqd = IsNewDrawingElementRqd (drawingFlags);
        
        Folio::Core::Graphic::GdiBitmapPtr  gdiBitmap;

        if (!isNewDrawingElementRqd)
        {
            // Use the existing GDI bitmap.

            gdiBitmap = m_gdiBitmap;
        } // Endif.

        // Create the GDI bitmap from the device-independent GDI bitmap.

        status = CreateGdiBitmap (dcHandle,
                                  screenScale,
                                  drawingFlags,
                                  m_gdiDiBitmap,
                                  gdiBitmap);

        // Is a masked GDI bitmap required?

        if ((status == ERR_SUCCESS) && m_maskedGdiBitmapRqd && maskedDrawingElementRqd)
        {
            // Yes.

            Folio::Core::Graphic::GdiBitmapPtr  maskedGdiBitmap;

            if (!isNewDrawingElementRqd)
            {
                // Use the existing masked GDI bitmap.

                maskedGdiBitmap = m_maskedGdiBitmap;
            } // Endif.

            // Create the masked GDI bitmap from the GDI bitmap.

            status = CreateMaskedGdiBitmap (dcHandle, 
                                            m_maskColour,
                                            screenScale,
                                            drawingFlags,
                                            gdiBitmap,
                                            maskedGdiBitmap);

            if (status == ERR_SUCCESS)
            {
                // Add the masked GDI bitmap to the list of drawing elements.

                drawingElementsList.push_back (DrawingElement(m_drawingElementId,
                                                              screenXLeft,
                                                              screenYTop,
                                                              maskedGdiBitmap,
                                                              drawingElementUserData,
                                                              m_collisionGridCellValue));

                if (!isNewDrawingElementRqd && !m_maskedGdiBitmap)
                {
                    // Set the masked GDI bitmap.

                    m_maskedGdiBitmap = maskedGdiBitmap;
                } // Endif.

            } // Endif.
                    
        } // Endif.

        if (status == ERR_SUCCESS)
        {
            // Add the GDI bitmap to the list of drawing elements.

            drawingElementsList.push_back (DrawingElement(m_drawingElementId,
                                                          screenXLeft,
                                                          screenYTop,
                                                          gdiBitmap, 
                                                          drawingElementUserData,
                                                          m_collisionGridCellValue));

            if (!isNewDrawingElementRqd && !m_gdiBitmap)
            {
                // Set the GDI bitmap.

                m_gdiBitmap = gdiBitmap;
            } // Endif.

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

            if ((status == ERR_SUCCESS) && m_gdiBitmap)
            {
                // Destroy the GDI bitmap.

                m_gdiBitmap.reset ();
            } // Endif.

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


ACollisionGrid::CellValue   ResourceGraphic::GetCollisionGridCellValue () const
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


FolioStatus ResourceGraphic::CreateGdiBitmap (FolioHandle                                   dcHandle,
                                              UInt32                                        screenScale,
                                              UInt32                                        drawingFlags,
                                              const Folio::Core::Graphic::GdiDiBitmapPtr&   gdiDiBitmap,
                                              Folio::Core::Graphic::GdiBitmapPtr&           gdiBitmap)
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

    // Does the GDI bitmap need to be created?

    if (!gdiBitmap || IsNewDrawingElementRqd (drawingFlags))
    {
        // Yes. Create the GDI bitmap from the device-independent GDI bitmap.

        gdiBitmap.reset (new Folio::Core::Graphic::GdiBitmapPtr::element_type);

        // Should the GDI bitmap be rotated?

        if (IsRotated (drawingFlags))
        {
            // Yes. Rotate the device-independent GDI bitmap.

            Folio::Core::Graphic::GdiDiBitmapPtr  rotatedGdiDiBitmap(new Folio::Core::Graphic::GdiDiBitmapPtr::element_type);

            status = rotatedGdiDiBitmap->Create (*gdiDiBitmap,
                                                 s_rotationTable [(drawingFlags & ROTATION_MASK) >> 2].m_radians,
                                                 Folio::Core::Graphic::DEFAULT_BACKGROUND_COLOUR);

            if (status == ERR_SUCCESS)
            {
                // Create the GDI bitmap from the rotated device-independent GDI bitmap.

                status = gdiBitmap->Create (dcHandle, *rotatedGdiDiBitmap);
            } // Endif.

        } // Endif.

        else
        {
            // No. Create the GDI bitmap from the device-independent GDI bitmap.

            status = gdiBitmap->Create (dcHandle, *gdiDiBitmap);
        } // Endelse.

        // Should the GDI bitmap be flipped?

        if (IsFlipped (drawingFlags))
        {
            // Yes. Flip the GDI bitmap.

            gdiBitmap->SetDrawingFlip (IsFlipHorizontal (drawingFlags), 
                                       IsFlipVertical (drawingFlags));
        } // Endif.

        // Scale the GDI bitmap.

        gdiBitmap->SetScreenScale (screenScale);
    } // Endif.

    return (status);
} // Endproc.


FolioStatus ResourceGraphic::CreateMaskedGdiBitmap (FolioHandle                         dcHandle,
                                                    Gdiplus::ARGB                       maskColour,
                                                    UInt32                              screenScale,
                                                    UInt32                              drawingFlags,
                                                    Folio::Core::Graphic::GdiBitmapPtr& gdiBitmap,
                                                    Folio::Core::Graphic::GdiBitmapPtr& maskedGdiBitmap)
{
    FolioStatus status = ERR_SUCCESS;

    // Does the masked GDI bitmap need to be created?

    if (!maskedGdiBitmap || IsNewDrawingElementRqd (drawingFlags))
    {
        // Yes. Create the masked GDI bitmap from the GDI bitmap.

        maskedGdiBitmap.reset (new Folio::Core::Graphic::GdiBitmapPtr::element_type);

        status = maskedGdiBitmap->Create (dcHandle,
                                          *gdiBitmap, 
                                          maskColour);

        if (status == ERR_SUCCESS)
        {
            // Should the masked GDI bitmap be flipped?

            if (IsFlipped (drawingFlags))
            {
                // Yes. Flip the masked GDI bitmap.

                maskedGdiBitmap->SetDrawingFlip (IsFlipHorizontal (drawingFlags), 
                                                 IsFlipVertical (drawingFlags));
            } // Endif.

            // Scale the masked GDI bitmap.

            maskedGdiBitmap->SetScreenScale (screenScale);

            // Set the masked GDI bitmap's drawing mode.

            maskedGdiBitmap->SetDrawingMode (SRCAND);

            // Make sure and set the GDI bitmap's drawing mode.

            gdiBitmap->SetDrawingMode (SRCPAINT);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


bool    ResourceGraphic::IsNewDrawingElementRqd (UInt32 drawingFlags)
{
    return (IsRotated (drawingFlags) || IsFlipped (drawingFlags));
} // Endproc.

                                
bool    ResourceGraphic::IsCreated () const
{
    return (m_gdiDiBitmap.get () != 0);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
