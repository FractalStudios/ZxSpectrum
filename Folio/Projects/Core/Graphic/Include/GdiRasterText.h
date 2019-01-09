#pragma once

// STL includes.
#include    <memory>

// "Home-made" includes.
#include    "AGdiGraphicElement.h"
#include    "GraphicConstsAndTypes.h"
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
                   const Gdiplus::Color&    backgroundColour = DEFAULT_BACKGROUND_COLOUR);
    ~GdiRasterText ();

    void                SetTextString (const FolioNarrowString& textString);
    FolioNarrowString   GetTextString () const;

    void            SetTextColour (const Gdiplus::Color& textColour);
    Gdiplus::Color  GetTextColour () const;

    void            SetBackgroundColour (const Gdiplus::Color& backgroundColour);
    Gdiplus::Color  GetBackgroundColour () const;

    void    InvertColours ();
    void    ResetColours ();
    bool    IsInvertedColours ();

    void            SetTextHorizontalAlignment (TextAlignment textAlignment);
    TextAlignment   GetTextHorizontalAlignment () const;

    void            SetTextVerticalAlignment (TextAlignment textAlignment);
    TextAlignment   GetTextVerticalAlignment () const;

    FolioStatus QueryTextExtent (const FolioNarrowString&   textString,
                                 Gdiplus::Rect&             textExtent);
    FolioStatus QueryTextBoundingArea (const FolioNarrowString& textString,
                                       int                      xPos,
                                       int                      yPos,
                                       int                      width,
                                       Gdiplus::Rect&           textBoundingArea);

    // AGdiGraphicElement method(s).
    virtual FolioStatus SetScreenTopLeft (Int32 screenXLeft,    
                                          Int32 screenYTop);
    virtual FolioStatus Draw (Gdiplus::Graphics&    graphics,
                              RectList*             rects = 0);

private:
    GdiRasterFont&    m_gdiRasterFont; ///< The text's raster font.

    FolioNarrowString   m_textString;               ///< The text string.           
    Gdiplus::Color      m_textColour;               ///< The colour of the pen used to draw the text.
    Gdiplus::Color      m_orgTextColour;            ///< The orignal colour of the pen used to draw the text.
    Gdiplus::Color      m_backgroundColour;         ///< The colour of the brush used to draw the background.
    Gdiplus::Color      m_orgBackgroundColour;      ///< The orignal colour of the brush used to draw the background.
    TextAlignment       m_textHorizontalAlignment;  ///< The horizontal alignment of the text.
    TextAlignment       m_textVerticalAlignment;    ///< The vertical alignment of the text.

    FolioByteBuffer m_textStringBitBuffer;  /// The raster bit buffer representing the text string.

    void    DrawCharacter (FolioHandle                          dcHandle,
                           Int32                                drawingX,
                           Int32                                drawingY,
                           UInt32                               characterWidth,          
                           Int32                                characterWidthInPixels,  
                           Int32                                characterHeightInPixels,
                           const FolioByteBuffer::value_type*   characterBitBuffer) const;
}; // Endclass.

/// GDI raster text pointer.
typedef std::shared_ptr<GdiRasterText>  GdiRasterTextPtr;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
