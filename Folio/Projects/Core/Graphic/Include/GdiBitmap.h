#pragma once

// STL includes.
#include    <memory>

// "Home-made" includes.
#include    "AGdiGraphicElement.h"
#include    "GraphicConstsAndTypes.h"
#include    "GdiDiBitmap.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Graphic
{

/// The GDI bitmap class.
/**
 * This class provides for a GDI bitmap.
 */
class GdiBitmap : public AGdiGraphicElement
{
public:    
    GdiBitmap ();
    ~GdiBitmap ();

    GdiBitmap (const GdiBitmap& rhs);
    GdiBitmap& operator= (const GdiBitmap& rhs);

    FolioStatus Create (FolioHandle             dcHandle,
                        const Gdiplus::Rect&    bitmapRect);
    FolioStatus Create (FolioHandle dcHandle,
                        FolioHandle instanceHandle,
                        UInt16      resourceId);
    FolioStatus Create (FolioHandle         dcHandle,
                        const FolioString   &fileName);
    FolioStatus Create (FolioHandle         dcHandle,
                        const GdiBitmap&    gdiBitmap);
    FolioStatus Create (FolioHandle             dcHandle,
                        const GdiBitmap&        gdiBitmap,
                        const Gdiplus::Color&   transparentColour);
    FolioStatus Create (FolioHandle         dcHandle,
                        const GdiDiBitmap&  gdiDiBitmap);

    FolioStatus ChangeColour (const Gdiplus::Color& colour,
                              const Gdiplus::Color& newColour);

    UInt32  GetId () const;

    bool    IsMonochrome () const;

    Gdiplus::Rect   GetBitmapRect () const;
    Int32           GetBitmapXLeft () const;
    Int32           GetBitmapYTop () const;
    Int32           GetBitmapWidth () const;
    Int32           GetBitmapHeight () const;

    void    SetDrawingFlip (bool    horizontalFlip,
                            bool    verticalFlip);
    bool    IsDrawingHorizontalFlip () const;
    bool    IsDrawingVerticalFlip () const;

    void    SetDrawingMode (UInt32 drawingMode);
    UInt32  GetDrawingMode () const;

    FolioStatus SetDrawingWidth (Int32 drawingWidth);
    FolioStatus SetDrawingHeight (Int32 drawingHeight);

    FolioStatus IncrementDrawingWidth (Int32 drawingWidthAdjustment);
    FolioStatus IncrementDrawingHeight (Int32 drawingHeightAdjustment);

    FolioStatus DecrementDrawingWidth (Int32 drawingWidthAdjustment);
    FolioStatus DecrementDrawingHeight (Int32 drawingHeightAdjustment);

    void    ResetDrawingAdjustmentMode ();
    UInt32  GetDrawingAdjustmentMode () const;
    Int32   GetDrawingWidthAdjustment () const;
    Int32   GetDrawingHeightAdjustment () const;
    bool    IsDrawingAdjustmentMode () const;

    bool    IsBitmapFullyDrawn ();
    bool    IsBitmapNoLongerDrawn ();

    FolioHandle         GetBitmapHandle () const;
    FolioHandle         GetDcHandle () const;
    FolioHandle         GetBitmapDcHandle () const;
    Gdiplus::Graphics*  GetBitmapGraphics () const;
    
    FolioStatus Clear (const Gdiplus::Color& clearColour = DEFAULT_BACKGROUND_COLOUR);
    FolioStatus Draw (Gdiplus::Graphics&    graphics,
                      const Gdiplus::Rect&  rect);
    FolioStatus Draw (Gdiplus::Graphics&    graphics,
                      Int32                 destinationWidth,
                      Int32                 destinationHeight);

    // AGdiGraphicElement method(s).
    virtual FolioStatus Draw (Int32                 screenXLeft,
                              Int32                 screenYTop,
                              Gdiplus::Graphics&    graphics,
                              RectList*             rects = 0);

private:
    UInt32          m_id;               ///< The identifier of the bitmap (based on the GDI device-independent bitmap resource identifier).
    bool            m_isMonochrome;     ///< true if the bitmap is monochrome.
    Gdiplus::Rect   m_bitmapRect;       ///< The rect of the bitmap.
    FolioHandle     m_dcHandle;         ///< The handle to the display compatible device context associated with the bitmap.
    FolioHandle     m_memoryDcHandle;   ///< The handle to the display compatible memory device context associated with the bitmap.
    FolioHandle     m_bitmapHandle;     ///< The handle to the bitmap
    FolioHandle     m_oldBitmapHandle;  ///< The old handle to the bitmap.
    bool            m_horizontalFlip;   ///< true if the bitmap should be flipped horizontally.
    bool            m_verticalFlip;     ///< true if the bitmap should be flipped vertically.
    UINT32          m_drawingMode;      ///< The bitmap's drawing mode (raster mode).

    static  const   UInt32  NONE                = 0x00;
    static  const   UInt32  SET_MASK            = 0x03;
    static  const   UInt32  SET_HEIGHT          = 0x01;
    static  const   UInt32  SET_WIDTH           = 0x02;
    static  const   UInt32  INCREMENT_MASK      = 0x0c;
    static  const   UInt32  INCREMENT_HEIGHT    = 0x04;
    static  const   UInt32  INCREMENT_WIDTH     = 0x08;
    static  const   UInt32  DECREMENT_MASK      = 0x30;
    static  const   UInt32  DECREMENT_HEIGHT    = 0x10;
    static  const   UInt32  DECREMENT_WIDTH     = 0x20;

    UInt32  m_drawingAdjustmentMode;    ///< The drawing adjustment mode.
    Int32   m_drawingWidthAdjustment;   ///< The drawing width adjustment.
    Int32   m_drawingHeightAdjustment;  ///< The drawing height adjustment.

    std::unique_ptr<Gdiplus::Graphics>  m_graphics; ///< The GDI+ graphics object associated with the bitmap.

    FolioStatus InitialiseBitmap (FolioHandle   dcHandle, 
                                  UInt32        id = FOLIO_UNDEFINED,
                                  bool          isMonochrome = false);
    FolioStatus DrawPartialBitmap (HDC              graphicsDcHandle,
                                   Int32            screenXLeft,
                                   Int32            screenYTop,
                                   Gdiplus::Rect    &drawingRect) const;
    FolioStatus DrawFullBitmap (HDC             graphicsDcHandle,
                                Int32           screenXLeft,
                                Int32           screenYTop,
                                Gdiplus::Rect   &drawingRect) const;

    void    Destroy ();
    bool    IsCreated () const;

    FolioStatus CreateGraphics ();
    void        DestroyGraphics ();
    bool    IsGraphics () const;
}; // Endclass.

/// GDI bitmap pointer.
typedef std::shared_ptr<GdiBitmap>  GdiBitmapPtr;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
