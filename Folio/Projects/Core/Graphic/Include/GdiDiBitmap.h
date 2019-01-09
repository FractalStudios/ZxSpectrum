#pragma once

// STL includes.
#include    <memory>

// "Home-made" includes.
#include    "GraphicConstsAndTypes.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Graphic
{

/// The GDI device-independent bitmap class.
/**
 * This class provides for a GDI device-independent bitmap.
 */
class GdiDiBitmap
{
public:    
    GdiDiBitmap ();
    ~GdiDiBitmap ();

    GdiDiBitmap (const GdiDiBitmap& rhs);
    GdiDiBitmap& operator= (const GdiDiBitmap& rhs);

    FolioStatus Create (FolioHandle instanceHandle,
                        UInt16      resourceId);
    FolioStatus Create (const FolioString &fileName);
    FolioStatus Create (const GdiDiBitmap& gdiDiBitmap);
    FolioStatus Create (const GdiDiBitmap&      gdiDiBitmap,
                        const double&           radians, 
                        const Gdiplus::Color&   backgroundColour);

    UInt32  GetColourTableIndex (const Gdiplus::Color& colour);

    FolioStatus ChangeColour (UInt32                colourTableIndex,
                              const Gdiplus::Color& newColour);
    FolioStatus ChangeColour (const Gdiplus::Color& colour,
                              const Gdiplus::Color& newColour,
                              UInt32&               colourTableIndex);

    Gdiplus::Rect   GetBitmapRect () const;
    Int32           GetBitmapXLeft () const;
    Int32           GetBitmapYTop () const;
    Int32           GetBitmapWidth () const;
    Int32           GetBitmapHeight () const;
    
    FolioHandle     GetBitmapHandle () const;

private:
    Gdiplus::Rect   m_bitmapRect;   ///< The rect of the bitmap.
    FolioHandle     m_bitmapHandle; ///< The handle to the bitmap

    FolioStatus InitialiseBitmap ();

    bool    IsCreated () const;
}; // Endclass.

/// GDI device-independent bitmap pointer.
typedef std::shared_ptr<GdiDiBitmap>    GdiDiBitmapPtr;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
