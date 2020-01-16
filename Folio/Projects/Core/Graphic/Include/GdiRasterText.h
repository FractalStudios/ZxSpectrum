#pragma once

// STL includes.
#include    <memory>

// "Home-made" includes.
#include    "AGdiGraphicElement.h"
#include    "GraphicConstsAndTypes.h"
#include    "GdiBitmap.h"
#include    "GdiRasterFont.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Graphic
{

/// The GDI raster text class.
/**
 * This class provides for GDI raster text.
 */
class GdiRasterText : public AGdiGraphicElement
{
public:    
    /// Text alignment enumeration.
    enum    TextAlignment
    {
        TEXT_ALIGNMENT_LEFT = 0,    ///< Left text alignment.
        TEXT_ALIGNMENT_CENTER,      ///< Center text alignment.
        TEXT_ALIGNMENT_RIGHT,       ///< Right text alignment.
    }; // Endenum.

    static  const   TextAlignment   DEFAULT_TEXT_ALIGNMENT = TEXT_ALIGNMENT_LEFT;   ///< The default text alignment.

    GdiRasterText (GdiRasterFont&           gdiRasterFont,
                   const Gdiplus::Color&    textColour = DEFAULT_TEXT_COLOUR,
                   const Gdiplus::Color&    backgroundColour = DEFAULT_BACKGROUND_COLOUR,
                   FolioHandle              dcHandle = FOLIO_INVALID_HANDLE);
    ~GdiRasterText ();

    void                SetTextString (const FolioNarrowString& textString);
    FolioNarrowString   GetTextString () const;

    void            SetTextColour (const Gdiplus::Color& textColour);
    Gdiplus::Color  GetTextColour () const;

    void            SetBackgroundColour (const Gdiplus::Color& backgroundColour);
    Gdiplus::Color  GetBackgroundColour () const;

    FolioStatus CreateGdiBitmapCache ();
    FolioStatus CreateInvertedGdiBitmapCache ();

    void    SetNonInverted ();
    void    SetInverted ();
    void    ToggleInverted ();
    bool    IsInverted () const;

    FolioStatus QueryTextExtent (const FolioNarrowString&   textString,
                                 Gdiplus::Rect&             textExtent);
    FolioStatus QueryTextBoundingArea (const FolioNarrowString& textString,
                                       int                      xPos,
                                       int                      yPos,
                                       int                      width,
                                       Gdiplus::Rect&           textBoundingArea);

    // AGdiGraphicElement method(s).
    virtual FolioStatus Draw (Int32                 screenXLeft,
                              Int32                 screenYTop,
                              Gdiplus::Graphics&    graphics,
                              RectList*             rects = 0);

private:
    GdiRasterFont&    m_gdiRasterFont; ///< The text's raster font.

    FolioNarrowString   m_textString;       ///< The text string.           
    Gdiplus::Color      m_textColour;       ///< The colour of the pen used to draw the text.
    Gdiplus::Color      m_backgroundColour; ///< The colour of the brush used to draw the background.
    FolioHandle         m_dcHandle;         ///< The handle to the display compatible device context associated with the raster text.
    bool                m_isInverted;       ///< <b>true</b> if the raster text is inverted, <b>false</b> otherwise.

    FolioByteBuffer m_textStringBitBuffer;  /// The raster bit buffer representing the text string.

    bool    m_redrawGdiBitmapCache; ///< <b>true</b> if the GDI bitmap cache needs to be redrawn, <b>false</b> otherwise.
    std::unique_ptr<GdiBitmap>  m_gdiBitmapCache;   ///< The GDI bitmap associated with the raster text.
    
    bool    m_redrawInvertedGdiBitmapCache; ///< <b>true</b> if the inverted GDI bitmap cache needs to be redrawn, <b>false</b> otherwise.
    std::unique_ptr<GdiBitmap>  m_invertedGdiBitmapCache;   ///< The inverted GDI bitmap associated with the raster text.

    FolioStatus DrawRasterText (Int32               screenXLeft,
                                Int32               screenYTop,
                                Gdiplus::Graphics&  graphics,
                                RectList*           rects);

    void    DrawCharacter (FolioHandle                          dcHandle,
                           Int32                                drawingXStart,
                           Int32                                drawingYStart,
                           Int32                                characterWidthInPixels,  
                           Int32                                characterHeightInPixels,
                           const FolioByteBuffer::value_type*   characterBitBuffer,
                           const COLORREF&                      textColour,
                           const COLORREF&                      backgroundCOlour) const;

    COLORREF    GetTextColour (bool inverted) const;
    COLORREF    GetBackgroundColour (bool inverted) const;

    void    Destroy ();

    bool    IsGdiBitmapCacheSupported () const;
    bool    IsInvertedGdiBitmapCacheSupported () const;

    bool    IsGdiBitmapCacheRqd () const;
    bool    IsInvertedGdiBitmapCacheRqd () const;

    void    DestroyGdiBitmapCache ();
    bool    IsGdiBitmapCache () const;

    void    DestroyInvertedGdiBitmapCache ();
    bool    IsInvertedGdiBitmapCache () const;

    FolioStatus DrawGdiBitmapCache (Int32               screenXLeft,
                                    Int32               screenYTop,
                                    Gdiplus::Graphics&  graphics,
                                    RectList*           rects);
    FolioStatus DrawInvertedGdiBitmapCache (Int32               screenXLeft,
                                            Int32               screenYTop,
                                            Gdiplus::Graphics&  graphics,
                                            RectList*           rects);
    void    DrawGdiBitmapCache (GdiBitmap&  gdiBitmap, 
                                bool        inverted);
}; // Endclass.

/// GDI raster text pointer.
typedef std::shared_ptr<GdiRasterText>  GdiRasterTextPtr;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
