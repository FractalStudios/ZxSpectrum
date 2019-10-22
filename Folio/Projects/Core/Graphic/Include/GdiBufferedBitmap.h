#pragma once

// STL includes.
#include    <memory>

// "Home-made" includes.
#include    "AGdiGraphicElement.h"
#include    "GraphicConstsAndTypes.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Graphic
{

/// The GDI buffered bitmap class.
/**
 * This class provides for a GDI buffered bitmap.
 *
 * This class does not support copy construction or assignment.
 */
class GdiBufferedBitmap : public AGdiGraphicElement
{
public:    
    GdiBufferedBitmap ();
    ~GdiBufferedBitmap ();

    FolioStatus Create (FolioHandle             dcHandle,
                        const Gdiplus::Rect&    bufferedBitmapRect,
                        bool                    drawToRequired = false);

    Gdiplus::Rect   GetBufferedBitmapRect () const;
    Int32           GetBufferedBitmapXLeft () const;
    Int32           GetBufferedBitmapYTop () const;
    Int32           GetBufferedBitmapWidth () const;
    Int32           GetBufferedBitmapHeight () const;
    
    FolioHandle         GetBufferedBitmapHandle () const;
    FolioHandle         GetBufferedBitmapDcHandle () const;
    Gdiplus::Graphics*  GetBufferedBitmapGraphics () const;

    FolioStatus Buffer (Gdiplus::Graphics&      graphics,
                        const Gdiplus::Point&   sourcePoint);
    FolioStatus Buffer (Gdiplus::Graphics&      graphics,
                        const Gdiplus::Rect&    bufferedBitmapRect);
    FolioStatus Clear (const Gdiplus::Color& clearColour = DEFAULT_BACKGROUND_COLOUR);
    FolioStatus Draw (Gdiplus::Graphics&    graphics,
                      const Gdiplus::Point& destinationPoint,              
                      RectList*             rects = 0);

    // AGdiGraphicElement method(s).
    virtual FolioStatus Draw (Int32                 screenXLeft,
                              Int32                 screenYTop,
                              Gdiplus::Graphics&    graphics,
                              RectList*             rects = 0);

private:
    FolioHandle     m_dcHandle;             ///< The device context handle.
    Gdiplus::Rect   m_bufferedBitmapRect;   ///< The rect of the buffered bitmap.
    FolioHandle     m_memoryDcHandle;       ///< The handle to the display compatible memory device context associated with the buffered bitmap.
    FolioHandle     m_bitmapHandle;         ///< The handle to the buffered bitmap.
    FolioHandle     m_oldBitmapHandle;      ///< The old handle to the buffered bitmap.

    std::unique_ptr<Gdiplus::Graphics>  m_graphics; ///< The GDI+ graphics object associated with the buffered bitmap.

    FolioStatus InitialiseBitmap (FolioHandle           dcHandle,
                                  const Gdiplus::Rect&  bufferedBitmapRect,
                                  bool                  drawToRequired);

    void    Destroy ();
    bool    IsCreated () const;

    FolioStatus CreateGraphics ();
    void        DestroyGraphics ();
    bool    IsGraphics () const;
     
    /// Private copy constructor to prevent copying.
    GdiBufferedBitmap (const GdiBufferedBitmap& rhs);

    /// Private assignment operator to prevent copying.
    GdiBufferedBitmap& operator= (const GdiBufferedBitmap& rhs);
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
