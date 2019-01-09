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

/// The GDI font class.
/**
 * This class provides for a GDI font.
 *
 * This class does not support copy construction or assignment.
 */
class GdiFont
{
public:    
    // Font format.
    typedef UInt32  FontFormat; ///< Font format.
    static  const   FontFormat  FONT_FORMAT_NORMAL      = 0x00; ///< Normal font format.
    static  const   FontFormat  FONT_FORMAT_BOLD        = 0x01; ///< Bold font format.
    static  const   FontFormat  FONT_FORMAT_ITALIC      = 0x02; ///< Italic font format.
    static  const   FontFormat  FONT_FORMAT_UNDERLINE   = 0x04; ///< Underline font format.

    static  const   FontFormat  DEFAULT_FONT_FORMAT = FONT_FORMAT_NORMAL;  ///< The default font format.
    
    /// Font size enumeration.
    enum    FontSize
    {
        FONT_SIZE_SMALL = 0,    ///< Small font size.
        FONT_SIZE_MEDIUM,       ///< Medium font size.
        FONT_SIZE_LARGE,        ///< Large font size.
    }; // Endenum.

    static  const   FontSize    DEFAULT_FONT_SIZE = FONT_SIZE_MEDIUM;   //< The default font size.

    GdiFont ();
    ~GdiFont ();

    void        SetFontFamily (const FolioString& fontFamily);
    FolioString GetFontFamily () const;
    
    void        SetFontFormat (FontFormat fontFormat);
    FontFormat  GetFontFormat () const;

    void        SetFontSize (FontSize fontSize);
    FontSize    GetFontSize () const;

    Gdiplus::Font*  GetGdiplusFont ();

private:
    FolioString m_fontFamily;           ///< The font family.
    FontFormat  m_fontFormat;           ///< The font format.
    FontSize    m_fontSize;             ///< The font size.
    bool        m_attributesAltered;    ///< Indicates if the font attributes have been altered.

    std::unique_ptr<Gdiplus::Font>  m_font;  ///< The font.

    UInt32  GetFontPixelSize () const;
    UInt32  GetFontStyle () const;
    
    bool    IsBold () const;
    bool    IsItalic () const;
    bool    IsUnderline () const;

    FolioStatus CreateFont ();
    bool        IsFont () const;

    /// Private copy constructor to prevent copying.
    GdiFont (const GdiFont& rhs);

    /// Private assignment operator to prevent copying.
    GdiFont& operator= (const GdiFont& rhs);
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
