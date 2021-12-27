#pragma once

// STL includes.
#include    <memory>

// "Home-made" includes.
#include    <Graphic.h>
#include    "ACollisionGrid.h"
#include    "DrawingElement.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Game
{

class ResourceGraphic
{
public:
    // Resource graphic orientation.
    static  const   UInt32  ORIENTATION_MASK    = 0x00000003;   // The orientation mask.
    static  const   UInt32  ORIENTATION_NONE    = 0x00000000;   // No orientation.
    static  const   UInt32  ORIENTATION_TOP     = 0x00000000;   // Orientation at top.
    static  const   UInt32  ORIENTATION_BOTTOM  = 0x00000001;   // Orientation at bottom.
    static  const   UInt32  ORIENTATION_LEFT    = 0x00000002;   // Orientation at left.
    static  const   UInt32  ORIENTATION_RIGHT   = 0x00000003;   // Orientation at right

    // Resource graphic rotation.
    static  const   UInt32  ROTATION_MASK       = 0x0000000c;   // The rotation mask.
    static  const   UInt32  ROTATION_NONE       = 0x00000000;   // No rotation.
    static  const   UInt32  ROTATION_180        = 0x00000004;   // Rotate 180 degrees.
    static  const   UInt32  ROTATION_LEFT_90    = 0x00000008;   // Rotate 90 degrees left.
    static  const   UInt32  ROTATION_RIGHT_90   = 0x0000000c;   // Rotate 90 degrees right.

    // Resource graphic flip.
    static  const   UInt32  FLIP_MASK           = 0x00000030;   // The flip mask.
    static  const   UInt32  FLIP_NONE           = 0x00000000;   // No flip.
    static  const   UInt32  FLIP_HORIZONTAL     = 0x00000010;   // Flip horizontally.
    static  const   UInt32  FLIP_VERTICAL       = 0x00000020;   // Flip vertically.

    // No drawing flags.
    static  const   UInt32  NO_DRAWING_FLAGS = ORIENTATION_NONE | ROTATION_NONE | FLIP_NONE;

    ResourceGraphic ();
    ~ResourceGraphic ();

    bool    IsCreated () const;

    FolioStatus Create (FolioHandle                             instanceHandle,
                        const DrawingElement::DrawingElementId& drawingElementId,
                        UInt16                                  bitmapResourceId,
                        bool                                    maskedGdiBitmapRqd = false,
                        ACollisionGrid::CellValue               collisionGridCellValue = ACollisionGrid::CELL_VALUE_EMPTY,
                        Gdiplus::ARGB                           maskColour = Folio::Core::Graphic::DEFAULT_BACKGROUND_COLOUR);
    FolioStatus Create (FolioHandle                             instanceHandle,
                        const DrawingElement::DrawingElementId& drawingElementId,
                        UInt16                                  bitmapResourceId,
                        Gdiplus::ARGB                           changeColour, 
                        bool                                    maskedGdiBitmapRqd = false,
                        ACollisionGrid::CellValue               collisionGridCellValue = ACollisionGrid::CELL_VALUE_EMPTY,
                        Gdiplus::ARGB                           maskColour = Folio::Core::Graphic::DEFAULT_BACKGROUND_COLOUR);
    FolioStatus Create (FolioHandle                             instanceHandle,
                        const DrawingElement::DrawingElementId& drawingElementId,
                        UInt16                                  bitmapResourceId,
                        Gdiplus::ARGB                           changeColour, 
                        Gdiplus::ARGB                           newColour, 
                        bool                                    maskedGdiBitmapRqd = false,
                        ACollisionGrid::CellValue               collisionGridCellValue = ACollisionGrid::CELL_VALUE_EMPTY,
                        Gdiplus::ARGB                           maskColour = Folio::Core::Graphic::DEFAULT_BACKGROUND_COLOUR);

    FolioStatus CreateGdiBitmap (FolioHandle    dcHandle,
                                 UInt32         screenScale,
                                 UInt32         drawingFlags);
    FolioStatus CreateMaskedGdiBitmap (FolioHandle dcHandle);

    FolioStatus ChangeColour (Gdiplus::ARGB newColour);

    FolioStatus QueryDrawingElements (FolioHandle                       dcHandle,
                                      Int32                             screenXLeft,
                                      Int32                             screenYTop,
                                      UInt32                            screenScale,
                                      UInt32                            drawingFlags,
                                      const DrawingElement::UserData&   drawingElementUserData,
                                      DrawingElementsList&              drawingElementsList,
                                      bool                              maskedDrawingElementRqd = true);
    FolioStatus QueryDrawingElements (FolioHandle                       dcHandle,
                                      Int32                             screenXLeft,
                                      Int32                             screenYTop,
                                      UInt32                            screenScale,
                                      Gdiplus::ARGB                     colour,
                                      UInt32                            drawingFlags,
                                      const DrawingElement::UserData&   drawingElementUserData,
                                      DrawingElementsList&              drawingElementsList,
                                      bool                              maskedDrawingElementRqd = true);

    DrawingElement::DrawingElementId    GetDrawingElementId () const;
    UInt16                              GetBitmapResourceId () const;
    UInt32                              GetChangeableColourTableIndex () const;
    Gdiplus::ARGB                       GetCurrentChangeableColour () const;
    ACollisionGrid::CellValue           GetCollisionGridCellValue () const;
    bool                                IsMaskedBitmapDrawingElementRqd () const;
    Gdiplus::ARGB                       GetMaskColour () const;

    bool    IsGdiDiBitmap () const;
    bool    IsGdiBitmap () const;
    bool    IsMaskedGdiBitmap () const;

    Folio::Core::Graphic::GdiDiBitmapPtr    GetGdiDiBitmap () const;
    Folio::Core::Graphic::GdiBitmapPtr      GetGdiBitmap () const;
    Folio::Core::Graphic::GdiBitmapPtr      GetMaskedGdiBitmap () const;

    UInt32  GetGraphicWidth () const;
    UInt32  GetGraphicHeight () const;

    FolioString Describe () const;

    static   UInt32  GetOrientation (UInt32 drawingFlags);
    static   bool    IsOrientationTop (UInt32 drawingFlags);
    static   bool    IsOrientationBottom (UInt32 drawingFlags);
    static   bool    IsOrientationLeft (UInt32 drawingFlags);
    static   bool    IsOrientationRight (UInt32 drawingFlags);

    static   UInt32  GetRotation (UInt32 drawingFlags);
    static   bool    IsRotated (UInt32 drawingFlags);
    static   bool    IsRotation180 (UInt32 drawingFlags);
    static   bool    IsRotationLeft90 (UInt32 drawingFlags);
    static   bool    IsRotationRight90 (UInt32 drawingFlags);

    static   UInt32  GetFlip (UInt32 drawingFlags);
    static   bool    IsFlipped (UInt32 drawingFlags);
    static   bool    IsFlipHorizontal (UInt32 drawingFlags);
    static   bool    IsFlipVertical (UInt32 drawingFlags);

private:
    DrawingElement::DrawingElementId    m_drawingElementId;             // The drawing element identifier of the resource graphic.
    UInt16                              m_bitmapResourceId;             // The bitmap resource identifier of the resource graphic.
    UInt32                              m_changeableColourTableIndex;   // The colour table index of the changeable colour within the resource graphic's GDI device-independent bitmap.
    Gdiplus::ARGB                       m_currentChangeableColour;      // The current changeable colour of the resource graphic.
    ACollisionGrid::CellValue           m_collisionGridCellValue;       // The collision grid cell value of the resource graphic.
    UInt32                              m_screenScale;                  // The screen scale of the GDI bitmap.
    UInt32                              m_drawingFlags;                 // The drawing flags of the GDI bitmap.
    bool                                m_maskedGdiBitmapRqd;           // Indicates if a masked GDI bitmap is required.
    Gdiplus::ARGB                       m_maskColour;                   // The mask colour of the masked GDI bitmap.

    Folio::Core::Graphic::GdiDiBitmapPtr    m_gdiDiBitmap;      // The GDI device-independent bitmap of the resource graphic.
    Folio::Core::Graphic::GdiBitmapPtr      m_gdiBitmap;        // The GDI bitmap of the resource graphic.
    Folio::Core::Graphic::GdiBitmapPtr      m_maskedGdiBitmap;  // The masked GDI bitmap of the resource graphic.

    bool    IsGdiBitmapMatch (FolioHandle                               dcHandle,
                              UInt32                                    screenScale,
                              UInt32                                    drawingFlags,
                              const Folio::Core::Graphic::GdiBitmapPtr& gdiBitmap) const;

    static  FolioStatus CreateGdiBitmap (FolioHandle                                    dcHandle,
                                         UInt32                                         screenScale,
                                         UInt32                                         drawingFlags,
                                         const Folio::Core::Graphic::GdiDiBitmapPtr&    gdiDiBitmap,
                                         Folio::Core::Graphic::GdiBitmapPtr&            gdiBitmap);
    static  FolioStatus CreateMaskedGdiBitmap (FolioHandle                          dcHandle,
                                               Gdiplus::ARGB                        maskColour,
                                               UInt32                               screenScale,
                                               UInt32                               drawingFlags,
                                               Folio::Core::Graphic::GdiBitmapPtr&  gdiBitmap,
                                               Folio::Core::Graphic::GdiBitmapPtr&  maskedGdiBitmap);
}; // Endclass.

// Resource graphic pointer.
typedef std::shared_ptr<ResourceGraphic> ResourceGraphicPtr;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
