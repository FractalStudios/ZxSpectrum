// "Home-made" includes.
#include    "GdiFont.h"

namespace Folio
{

namespace Core
{

namespace Graphic
{

using   namespace   Gdiplus;

/**
 * The default class constructor.
 */
GdiFont::GdiFont ()
:   m_fontFamily(TXT("Arial")),
    m_fontFormat(DEFAULT_FONT_FORMAT),
    m_fontSize(DEFAULT_FONT_SIZE),
    m_attributesAltered(false)
{
} // Endproc.


/**
 * The class destructor.
 */
GdiFont::~GdiFont ()
{
} // Endproc.


/**
 * Method that is used to set the font family of the font.
 *
 * @param [in] fontFamily
 * The font family of the font.
 */
void    GdiFont::SetFontFamily (const FolioString& fontFamily)
{
    m_fontFamily = fontFamily;

    m_attributesAltered = true;   // New attributes.
} // Endproc.


/**
 * Method that is used to get the font family of the font.
 *
 * @return
 * The font family of the font.
 */
FolioString GdiFont::GetFontFamily () const
{
    return (m_fontFamily);
} // Endproc.


/**
 * Method that is used to set the font format of the font.
 *
 * @param [in] fontFormat
 * The font format of the font.
 */
void    GdiFont::SetFontFormat (FontFormat fontFormat)
{
    m_fontFormat = fontFormat;

    m_attributesAltered = true;   // New attributes.
} // Endproc.


/**
 * Method that is used to get the font format of the font.
 *
 * @return
 * The font format of the font.
 */
GdiFont::FontFormat GdiFont::GetFontFormat () const
{
    return (m_fontFormat);
} // Endproc.


/**
 * Method that is used to set the font size of the font.
 *
 * @param [in] fontSize
 * The font size of the font.
 */
void    GdiFont::SetFontSize (FontSize fontSize)
{
    m_fontSize = fontSize;

    m_attributesAltered = true;   // New attributes.
} // Endproc.


/**
 * Method that is used to get the font size of the font.
 *
 * @return
 * The font size of the font.
 */
GdiFont::FontSize  GdiFont::GetFontSize () const
{
    return (m_fontSize);
} // Endproc.


/**
 * Method that is used to get the GDI+ font of the font.
 *
 * @return
 * The GDI+ font of the font.
 */
Gdiplus::Font*  GdiFont::GetGdiplusFont ()
{
    // If we have not created a font, or the current font's attributes have 
    // been altered, then we need to create a font.

    if (!IsFont () || m_attributesAltered)
    {
        // Create the font.

        CreateFont ();
    } // Endif.

    return (m_font.get ());
} // Endproc.


/**
 * Method that is used to get the pixel size of the font.
 *
 * @return
 * The pixel size of the font.
 */
UInt32  GdiFont::GetFontPixelSize () const
{
    UInt32  pixelSize;

    switch (m_fontSize)
    {
    case FONT_SIZE_SMALL:
        pixelSize = 6;
        break;
    case FONT_SIZE_LARGE:
        pixelSize = 14;
        break;
    case FONT_SIZE_MEDIUM:
    default:
        pixelSize = 10;
        break;
    } // Endswitch.

    return (pixelSize);
} // Endproc.


/**
 * Method that is used to get the font style of the font.
 *
 * @return
 * The font style of the font.
 */
UInt32  GdiFont::GetFontStyle () const
{
    UInt32  fontStyle = FontStyleRegular;

    if (IsBold ())
    {
        fontStyle |= FontStyleBold;
    } // Endif.

    if (IsItalic ())
    {
        fontStyle |= FontStyleItalic;
    } // Endif.

    if (IsUnderline ())
    {
        fontStyle |= FontStyleUnderline;
    } // Endif.

    return (fontStyle);
} // Endproc.


/**
 * Method that is used to determine if the font is bold.
 *
 * @return
 * <b>true</b> if the font is bold, <b>false</b> otherwise.
 */
bool    GdiFont::IsBold () const
{
    return ((m_fontFormat & FONT_FORMAT_BOLD) == FONT_FORMAT_BOLD);
} // Endproc.


/**
 * Method that is used to determine if the font is italic.
 *
 * @return
 * <b>true</b> if the font is italic, <b>false</b> otherwise.
 */
bool    GdiFont::IsItalic () const
{
    return ((m_fontFormat & FONT_FORMAT_ITALIC) == FONT_FORMAT_ITALIC);
} // Endproc.


/**
 * Method that is used to determine if the font is underlined.
 *
 * @return
 * <b>true</b> if the font is underlined, <b>false</b> otherwise.
 */
bool    GdiFont::IsUnderline () const
{
    return ((m_fontFormat & FONT_FORMAT_UNDERLINE) == FONT_FORMAT_UNDERLINE);
} // Endproc.


/**
 * Method that is used to create the font.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiFont::CreateFont ()
{
    FolioStatus status = ERR_SUCCESS;

    // Build a font family.

    FontFamily  fontFamily(FolioWideString(m_fontFamily).c_str ());

    // Create the font.

    m_font.reset (new Font(&(fontFamily), 
                           static_cast<REAL> (GetFontPixelSize ()),
                           GetFontStyle (),
                           UnitPixel));

    m_attributesAltered = false;  // We're using them.

    return (status);
} // Endproc.


/**
 * Method that is used to determine if the font has been created.
 *
 * @return
 * <b>true</b> if the font has been created, <b>false</b> otherwise.
 */
bool    GdiFont::IsFont () const
{
    return (m_font.get () != 0);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
