// "Home-made" includes.
#include    <Util.h>
#include    "ResourceGraphic.h"
#include    "ZxSpectrum.h"

//#define _OUTPUT_RESOURCE_GRAPHIC_

namespace Folio
{

namespace Core
{

namespace Game
{

ResourceGraphic::ResourceGraphic ()
:   m_drawingElementId(DrawingElement::DRAWING_ELEMENT_ID_UNDEFINED),
    m_bitmapResourceId(FOLIO_UNDEFINED),
    m_changeableColourTableIndex(FOLIO_INVALID_INDEX),
    m_currentChangeableColour(Folio::Core::Game::ZxSpectrum::GetBitmapChangeColour ()),
    m_collisionGridCellValue(ACollisionGrid::CELL_VALUE_EMPTY),
    m_screenScale(1),
    m_drawingFlags(NO_DRAWING_FLAGS),
    m_maskedGdiBitmapRqd(false),
    m_maskColour(Folio::Core::Graphic::DEFAULT_BACKGROUND_COLOUR)
{
} // Endproc.


ResourceGraphic::~ResourceGraphic ()
{
} // Endproc.


bool    ResourceGraphic::IsCreated () const
{
    return (m_gdiDiBitmap != 0);
} // Endproc.


FolioStatus ResourceGraphic::Create (FolioHandle                instanceHandle,
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

        #ifdef _OUTPUT_RESOURCE_GRAPHIC_
        FolioOStringStream  str;
        str << TXT("ResourceGraphic::Create ") << Folio::Core::Util::DescribeId (bitmapResourceId)
            << TXT(" 0x") << std::setw(8) << std::setfill(TXT('0')) << std::hex << this
            << std::endl;
        ::OutputDebugString (str.str ().c_str ());
        #endif
        
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


FolioStatus ResourceGraphic::Create (FolioHandle                instanceHandle,
                                     DrawingElement::Id         drawingElementId,
                                     UInt16                     bitmapResourceId,
                                     Gdiplus::ARGB              changeColour, 
                                     bool                       maskedGdiBitmapRqd,
                                     ACollisionGrid::CellValue  collisionGridCellValue,
                                     Gdiplus::ARGB              maskColour)
{
    // Create the resource graphic.

    FolioStatus status = Create (instanceHandle,
                                 drawingElementId,
                                 bitmapResourceId,
                                 maskedGdiBitmapRqd,
                                 collisionGridCellValue,
                                 maskColour);

    if (status == ERR_SUCCESS)
    {
        // Get the colour table index of the GDI bitmap colour to change.

        m_changeableColourTableIndex = m_gdiDiBitmap->GetColourTableIndex (changeColour);

        // Does the resource graphic support colour change?

        if (m_changeableColourTableIndex == FOLIO_INVALID_INDEX)
        {
            // No.

            status = ERR_NOT_SUPPORTED;
        } // Endif.

        else
        {
            // Yes. Note the current changeable colour of the device-independent 
            // GDI bitmap.

            m_currentChangeableColour = changeColour;
        } // Endelse.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus ResourceGraphic::Create (FolioHandle                instanceHandle,
                                     DrawingElement::Id         drawingElementId,
                                     UInt16                     bitmapResourceId,
                                     Gdiplus::ARGB              changeColour, 
                                     Gdiplus::ARGB              newColour, 
                                     bool                       maskedGdiBitmapRqd,
                                     ACollisionGrid::CellValue  collisionGridCellValue,
                                     Gdiplus::ARGB              maskColour)
{
    // Create the resource graphic.

    FolioStatus status = Create (instanceHandle,
                                 drawingElementId,
                                 bitmapResourceId,
                                 maskedGdiBitmapRqd,
                                 collisionGridCellValue,
                                 maskColour);

    if (status == ERR_SUCCESS)
    {
        // Change the colour of the device-independent GDI bitmap.

        status = m_gdiDiBitmap->ChangeColour (changeColour,
                                              newColour, 
                                              m_changeableColourTableIndex);

        if (status == ERR_SUCCESS)
        {
            // Does the resource graphic support colour change?

            if (m_changeableColourTableIndex == FOLIO_INVALID_INDEX)
            {
                // No.

                status = ERR_NOT_SUPPORTED;
            } // Endif.

            else
            {
                // Yes. Note the current changeable colour of the device-independent 
                // GDI bitmap.

                m_currentChangeableColour = newColour;
            } // Endelse.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus ResourceGraphic::CreateGdiBitmap (FolioHandle   dcHandle,
                                              UInt32        screenScale,
                                              UInt32        drawingFlags)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a resource graphic?

    if (IsCreated ())
    {
        // Yes. Have we created a GDI bitmap?

        if (IsGdiBitmap ())
        {
            // Yes. Does the created GDI bitmap match the required attributes?

            if (!IsGdiBitmapMatch (dcHandle,
                                   screenScale,
                                   drawingFlags,
                                   m_gdiBitmap))
            {
                // No.

                status = ERR_IN_USE;
            } // Endif.

        } // Endif.

        else
        {
            // No. Create the GDI bitmap from the device-independent GDI bitmap.

            status = CreateGdiBitmap (dcHandle,
                                      screenScale,
                                      drawingFlags,
                                      m_gdiDiBitmap,
                                      m_gdiBitmap);

            if (status == ERR_SUCCESS)
            {
                // Note the attributes.

                m_screenScale   = screenScale;
                m_drawingFlags  = drawingFlags;
            } // Endif.

        } // Endelse.

    } // Endif.

    else
    {
        // No.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


FolioStatus ResourceGraphic::CreateMaskedGdiBitmap (FolioHandle dcHandle)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a resource graphic and a GDI bitmap?

    if (IsCreated () && IsGdiBitmap ())
    {
        // Yes. Have we created a masked GDI bitmap?

        if (IsMaskedGdiBitmap ())
        {
            // Yes. Does the created masked GDI bitmap match the required attributes?

            if (!IsGdiBitmapMatch (dcHandle,
                                   m_screenScale,
                                   m_drawingFlags,
                                   m_maskedGdiBitmap))
            {
                // No.

                status = ERR_IN_USE;
            } // Endif.

        } // Endif.

        else
        {
            // No. Create the masked GDI bitmap from the GDI bitmap.

            status = CreateMaskedGdiBitmap (dcHandle,
                                            m_maskColour,
                                            m_screenScale,
                                            m_drawingFlags,
                                            m_gdiBitmap,
                                            m_maskedGdiBitmap);
        } // Endelse.

    } // Endif.

    else
    {
        // No.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


FolioStatus ResourceGraphic::ChangeColour (Gdiplus::ARGB newColour)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a resource graphic?

    if (IsCreated ())
    {
        // Yes. Does the resource graphic support colour change?

        if (m_changeableColourTableIndex == FOLIO_INVALID_INDEX)
        {
            // No.

            status = ERR_NOT_SUPPORTED;
        } // Endif.

        else
        {
            // Yes. Does the current changeable colour of the device-independent 
            // GDI bitmap match the required colour?

            if (newColour != m_currentChangeableColour)
            {
                // No. Change the colour of the device-independent GDI bitmap.

                status = m_gdiDiBitmap->ChangeColour (m_changeableColourTableIndex, newColour);

                if (status == ERR_SUCCESS)
                {
                    // Note the current changeable colour of the device-independent 
                    // GDI bitmap.

                    m_currentChangeableColour = newColour;

                    // As the device-independent GDI bitmap's colour has been 
                    // changed, the GDI bitmap and masked GDI bitmap must be 
                    // destroyed; in order that they are recreated.

                    m_gdiBitmap.reset ();
                    m_maskedGdiBitmap.reset ();

                    #ifdef _OUTPUT_RESOURCE_GRAPHIC_
                    FolioOStringStream  str;
                    str << TXT("ResourceGraphic::ChangeColour ") << Folio::Core::Util::DescribeId (m_bitmapResourceId)
                        << TXT(" 0x") << std::setw(8) << std::setfill(TXT('0')) << newColour
                        << TXT(" 0x") << std::setw(8) << std::setfill(TXT('0')) << std::hex << this
                        << std::endl;
                    ::OutputDebugString (str.str ().c_str ());
                    #endif
                } // Endif.

            } // Endif.

        } // Endelse.

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
        #ifdef _OUTPUT_RESOURCE_GRAPHIC_
        FolioOStringStream  str;
        str << TXT("ResourceGraphic::QueryDrawingElements ") << Folio::Core::Util::DescribeId (m_bitmapResourceId)
            << TXT(" 0x") << std::setw(8) << std::setfill(TXT('0')) << std::hex << this
            << std::endl;
        ::OutputDebugString (str.str ().c_str ());
        #endif

        // Yes. Does the current GDI bitmap match the required attributes?

        bool    isGdiBitmapMatch = IsGdiBitmapMatch (dcHandle,
                                                     screenScale,
                                                     drawingFlags,
                                                     m_gdiBitmap);

        if (!isGdiBitmapMatch)
        {
            // No. Create the GDI bitmap from the device-independent GDI bitmap.

            status = CreateGdiBitmap (dcHandle,
                                      screenScale,
                                      drawingFlags,
                                      m_gdiDiBitmap,
                                      m_gdiBitmap);
        } // Endif.

        if (status == ERR_SUCCESS) 
        {
            // Is a masked GDI bitmap required?

            if (m_maskedGdiBitmapRqd && maskedDrawingElementRqd)
            {
                // Yes. If the GDI bitmap did not match the required attributes 
                // then a masked GDI bitmap is required.

                bool    isMaskedGdiBitmapMatch = isGdiBitmapMatch;

                if (isMaskedGdiBitmapMatch)
                {
                    // Does the current masked GDI bitmap match the required 
                    // attributes?
                    
                    isMaskedGdiBitmapMatch = IsGdiBitmapMatch (dcHandle,
                                                               screenScale,
                                                               drawingFlags,
                                                               m_maskedGdiBitmap);
                } // Endif.

                if (!isMaskedGdiBitmapMatch)
                {
                    // No. Create the masked GDI bitmap from the GDI bitmap.

                    status = CreateMaskedGdiBitmap (dcHandle, 
                                                    m_maskColour,
                                                    screenScale,
                                                    drawingFlags,
                                                    m_gdiBitmap,
                                                    m_maskedGdiBitmap);

                    if (status == ERR_SUCCESS)
                    {
                        // Add the masked GDI bitmap to the list of drawing elements.

                        drawingElementsList.push_back (DrawingElement(m_drawingElementId,
                                                                      screenXLeft,
                                                                      screenYTop,
                                                                      m_maskedGdiBitmap,
                                                                      drawingElementUserData,
                                                                      m_collisionGridCellValue));
                    } // Endif.

                } // Endif.

                else
                {
                    // Make sure and set the GDI bitmap's drawing mode.

                    m_gdiBitmap->SetDrawingMode (SRCPAINT);
                } // Endelse.
                    
            } // Endif.

            else
            if (isGdiBitmapMatch && 
                m_maskedGdiBitmapRqd && !maskedDrawingElementRqd)
            {
                // Make sure and set the GDI bitmap's drawing mode.

                m_gdiBitmap->SetDrawingMode (SRCCOPY);
            } // Endelseif.

            if (status == ERR_SUCCESS)
            {
                // Add the GDI bitmap to the list of drawing elements.

                drawingElementsList.push_back (DrawingElement(m_drawingElementId,
                                                              screenXLeft,
                                                              screenYTop,
                                                              m_gdiBitmap, 
                                                              drawingElementUserData,
                                                              m_collisionGridCellValue));

                // Note the attributes.

                m_screenScale   = screenScale;
                m_drawingFlags  = drawingFlags;
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
         // Yes. Change the colour of the resource graphic.

        status = ChangeColour (colour);
          
        if ((status == ERR_SUCCESS) ||
            (status == ERR_NOT_SUPPORTED))
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


UInt32  ResourceGraphic::GetChangeableColourTableIndex () const
{
    return (m_changeableColourTableIndex);
} // Endproc.


Gdiplus::ARGB   ResourceGraphic::GetCurrentChangeableColour () const
{
    return (m_currentChangeableColour);
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


bool    ResourceGraphic::IsGdiDiBitmap () const
{
    return (m_gdiDiBitmap != 0);
} // Endproc.


bool    ResourceGraphic::IsGdiBitmap () const
{
    return (m_gdiBitmap != 0);
} // Endproc.


bool    ResourceGraphic::IsMaskedGdiBitmap () const
{
    return (m_maskedGdiBitmap != 0);
} // Endproc.


Folio::Core::Graphic::GdiDiBitmapPtr    ResourceGraphic::GetGdiDiBitmap () const
{
    return (m_gdiDiBitmap);
} // Endproc.


Folio::Core::Graphic::GdiBitmapPtr  ResourceGraphic::GetGdiBitmap () const
{
    return (m_gdiBitmap);
} // Endproc.


Folio::Core::Graphic::GdiBitmapPtr  ResourceGraphic::GetMaskedGdiBitmap () const
{
    return (m_maskedGdiBitmap);
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


bool    ResourceGraphic::IsGdiBitmapMatch (FolioHandle                              dcHandle,
                                           UInt32                                   screenScale,
                                           UInt32                                   drawingFlags,
                                           const Folio::Core::Graphic::GdiBitmapPtr &gdiBitmap) const
{
    return (gdiBitmap                                   &&
            (m_screenScale  == screenScale)             && 
            (m_drawingFlags == drawingFlags)            &&
            (gdiBitmap->GetDcHandle () == dcHandle));
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

    #ifdef _OUTPUT_RESOURCE_GRAPHIC_
    FolioOStringStream  str;
    str << TXT("ResourceGraphic::CreateGdiBitmap ") << Folio::Core::Util::DescribeId (gdiDiBitmap->GetResourceId ())
        << std::endl;
    ::OutputDebugString (str.str ().c_str ());
    #endif

    // Create the GDI bitmap from the device-independent GDI bitmap.

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

    // Make sure and set the GDI bitmap's drawing mode.

    gdiBitmap->SetDrawingMode (SRCCOPY);

    return (status);
} // Endproc.


FolioStatus ResourceGraphic::CreateMaskedGdiBitmap (FolioHandle                         dcHandle,
                                                    Gdiplus::ARGB                       maskColour,
                                                    UInt32                              screenScale,
                                                    UInt32                              drawingFlags,
                                                    Folio::Core::Graphic::GdiBitmapPtr& gdiBitmap,
                                                    Folio::Core::Graphic::GdiBitmapPtr& maskedGdiBitmap)
{
    #ifdef _OUTPUT_RESOURCE_GRAPHIC_
    FolioOStringStream  str;
    str << TXT("ResourceGraphic::CreateMaskedGdiBitmap ") << Folio::Core::Util::DescribeId (gdiBitmap->GetId ())
        << std::endl;
    ::OutputDebugString (str.str ().c_str ());
    #endif

    // Yes. Create the masked GDI bitmap from the GDI bitmap.

    maskedGdiBitmap.reset (new Folio::Core::Graphic::GdiBitmapPtr::element_type);

    FolioStatus status = maskedGdiBitmap->Create (dcHandle,
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

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
