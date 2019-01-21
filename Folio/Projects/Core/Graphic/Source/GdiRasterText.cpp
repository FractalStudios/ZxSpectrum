// "Home-made" includes.
#include    "..\Include\Gdi.h"
#include    "GdiRasterText.h"

namespace Folio
{

namespace Core
{

namespace Graphic
{

using   namespace   Gdiplus;

/**
 * The class constructor.
 *
 * @param [in] gdiRasterFont
 * The raster font to be associated with the text. This object will hold a 
 * reference to this font so any changes made to the font are automatically 
 * picked up by this object.
 *
 * @param [in] textColour
 * The text colour of the text.
 *
 * @param [in] backgroundColour
 * The background colour of the text.
 */
GdiRasterText::GdiRasterText (GdiRasterFont&        gdiRasterFont,
                              const Gdiplus::Color& textColour,
                              const Gdiplus::Color& backgroundColour)
:   m_gdiRasterFont(gdiRasterFont),
    m_textColour(textColour),
    m_orgTextColour(textColour),
    m_backgroundColour(backgroundColour),
    m_orgBackgroundColour(backgroundColour),
    m_textHorizontalAlignment(DEFAULT_TEXT_ALIGNMENT),
    m_textVerticalAlignment(DEFAULT_TEXT_ALIGNMENT)
{
} // Endproc.


/**
 * The class destructor.
 */
GdiRasterText::~GdiRasterText ()
{
} // Endproc.


/**
 * Method that is used to set the text string of the text.
 *
 * @param [in] textString
 * The text string of the text.
 */
void    GdiRasterText::SetTextString (const FolioNarrowString& textString)
{
    m_textString = textString;

    // Get the raster bit buffer representing the text string.

    m_textStringBitBuffer = m_gdiRasterFont.GetTextStringBitBuffer (m_textString);

    // Set the new screen rect.

    SetScreenRect (Gdiplus::Rect(m_screenRect.X, 
                                 m_screenRect.Y,
                                 m_textString.size () * m_gdiRasterFont.GetCharacterWidthInPixels (),
                                 m_gdiRasterFont.GetCharacterHeightInPixels ()));
} // Endproc.


/**
 * Method that is used to get the text string of the text.
 *
 * @return
 * The text string of the text.
 */
FolioNarrowString   GdiRasterText::GetTextString () const
{
    return (m_textString);
} // Endproc.


/**
 * Method that is used to set the text colour of the text.
 *
 * @param [in] textColour
 * The text colour of the text.
 */
void    GdiRasterText::SetTextColour (const Gdiplus::Color& textColour)
{
    m_textColour    = textColour;
    m_orgTextColour = textColour;
} // Endproc.


/**
 * Method that is used to get the text colour of the text.
 *
 * @return
 * The text colour of the text.
 */
Gdiplus::Color  GdiRasterText::GetTextColour () const
{
    return (m_textColour);
} // Endproc.


/**
 * Method that is used to set the background colour of the text.
 *
 * @param [in] backgroundColour
 * The background colour of the text.
 */
void    GdiRasterText::SetBackgroundColour (const Gdiplus::Color& backgroundColour)
{
    m_backgroundColour = backgroundColour;
} // Endproc.


/**
 * Method that is used to get the background colour of the text.
 *
 * @return
 * The background colour of the text.
 */
Gdiplus::Color  GdiRasterText::GetBackgroundColour () const
{
    return (m_backgroundColour);
} // Endproc.


/**
 * Method that is used to invert the colours of the text.
 */
void    GdiRasterText::InvertColours ()
{
    Gdiplus::Color  orgTextColour = m_textColour;

    m_textColour        = m_backgroundColour;
    m_backgroundColour  = orgTextColour;
} // Endproc.


/**
 * Method that is used to reset the colours of the text.
 */
void    GdiRasterText::ResetColours ()
{
    m_textColour        = m_orgTextColour;
    m_backgroundColour  = m_orgBackgroundColour;
} // Endproc.


/**
 * Indicates of the text colours are inverted.
 *
 * @return
 * <b>true</b> of the text colours are inverted, <b>false</b> otherwise.
 */
bool    GdiRasterText::IsInvertedColours ()
{
    return ((m_textColour.ToCOLORREF () == m_orgBackgroundColour.ToCOLORREF () ) &&
            (m_backgroundColour.ToCOLORREF ()  == m_orgTextColour.ToCOLORREF () ));
} // Endproc.


/*
 * Method that is used to set the horizontal alignment of the text.
 *
 * @param [in] textAlignment
 * The horizontal alignment of the text.
 */
void    GdiRasterText::SetTextHorizontalAlignment (TextAlignment textAlignment)
{
    m_textHorizontalAlignment = textAlignment;
} // Endproc.


/**
 * Method that is used to get the horizontal alignment of the text.
 *
 * @return
 * The horizontal alignment of the text.
 */
GdiRasterText::TextAlignment  GdiRasterText::GetTextHorizontalAlignment () const
{
    return (m_textHorizontalAlignment);
} // Endproc.


/*
 * Method that is used to set the horizontal alignment of the text.
 *
 * @param [in] textAlignment
 * The horizontal alignment of the text.
 */
void    GdiRasterText::SetTextVerticalAlignment (TextAlignment textAlignment)
{
    m_textVerticalAlignment = textAlignment;
} // Endproc.


/**
 * Method that is used to get the horizontal alignment of the text.
 *
 * @return
 * The horizontal alignment of the text.
 */
GdiRasterText::TextAlignment  GdiRasterText::GetTextVerticalAlignment () const
{
    return (m_textVerticalAlignment);
} // Endproc.


/**
 * Method that is used to obtain the extent of a specified text string.
 *
 * @param [in] textString
 * The text string.
 *
 * @param [in, out] textExtent
 * On retun, will hold the text extent of the text string, if successful. If 
 * this method fails then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiRasterText::QueryTextExtent (const FolioNarrowString&    textString,
                                            Gdiplus::Rect&              textExtent)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the text string empty?

    if (textString.empty ())
    {
        // Yes. Text extent is empty.

        textExtent.Width    = 0;
        textExtent.Height   = 0;
    } // Endif.

    else
    {
        // No.

        textExtent.Width    = textString.size () * m_gdiRasterFont.GetCharacterWidthInPixels ();
        textExtent.Height   = m_gdiRasterFont.GetCharacterHeightInPixels ();
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to obtain the bounding area of a specified text string.
 *
 * @param [in] textString
 * The text string.
 *
 * @param [in] xPos
 * The X position of the start of the bounding area.
 *
 * @param [in] yPos
 * The Y position of the start of the bounding area.
 *
 * @param [in] width
 * The width of the bounding area.
 *
 * @param [out] textBoundingArea
 * On retun, will hold the text bounding area of the text string, if 
 * successful. If this method fails then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiRasterText::QueryTextBoundingArea (const FolioNarrowString&  textString,
                                                  int                       xPos,
                                                  int                       yPos,
                                                  int                       width,
                                                  Gdiplus::Rect&            textBoundingArea)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the text string empty?

    if (textString.empty () || (width == 0))
    {
        // Yes. Text bounding area is empty.

        textBoundingArea.X      = 0;
        textBoundingArea.Y      = 0;
        textBoundingArea.Width  = 0;
        textBoundingArea.Height = 0;
    } // Endif.

    else
    {
        // No.

        textBoundingArea.X      = xPos;
        textBoundingArea.Y      = yPos;
        textBoundingArea.Width  = width;

        // Calculate the bounding text area's height.

        UInt32  textStringWidth = textString.size () * m_gdiRasterFont.GetCharacterWidthInPixels ();

        textBoundingArea.Height = textStringWidth / width;

        if (textStringWidth % width)
        {
            textBoundingArea.Height++;
        } // Endif.

        textBoundingArea.Height *= m_gdiRasterFont.GetCharacterHeightInPixels ();
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to set the top-left hand corner of the text's screen 
 * point.
 *
 * @param [in] screenXLeft
 * The screen X left positoin of the graphic element.
 *
 * @param [in] screenYTop
 * The screen Y top positoin of the graphic element.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_NOT_INITIALISED</b> if the graphic element is not initialised.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiRasterText::SetScreenTopLeft (Int32  screenXLeft,
                                             Int32  screenYTop)
{
    // Set the screen rect.

    SetScreenRect (Gdiplus::Rect(screenXLeft, 
                                 screenYTop,
                                 m_textString.size () * m_gdiRasterFont.GetCharacterWidthInPixels (),
                                 m_gdiRasterFont.GetCharacterHeightInPixels ()));
    
    return (ERR_SUCCESS);
} // Endproc.


/**
 * Method that is used to draw the raster text.
 *
 * @param [in, out] graphics
 * The graphics object to draw to.
 *
 * @param [out] rects
 * On return, will hold the rects of the raster text, if successful. If this 
 * method fails then this parameter is undefined. May be zero if not required.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiRasterText::Draw (Gdiplus::Graphics& graphics,
                                 RectList*          rects)
{
    FolioStatus status = ERR_SUCCESS;

    // Get font attributes.

    UInt32  characterWidth          = m_gdiRasterFont.GetCharacterWidth ();
    Int32   characterWidthInPixels  = m_gdiRasterFont.GetCharacterWidthInPixels ();
    Int32   characterHeightInPixels = m_gdiRasterFont.GetCharacterHeightInPixels ();

    // Get the graphics device context.
     
    HDC graphicsDcHandle = graphics.GetHDC ();

    // Draw the text string.

    UInt32  textStringLength = m_textString.length ();

    for (UInt32 character = 0; character < textStringLength; ++character)
    {
        // Draw each character in the string.

        DrawCharacter (graphicsDcHandle,
                       m_scaledRect.X + (character * characterWidthInPixels * m_screenScale),
                       m_scaledRect.Y,
                       characterWidth,          
                       characterWidthInPixels,  
                       characterHeightInPixels,
                       &(m_textStringBitBuffer [character * characterWidth * characterHeightInPixels]));
    } // Endfor.

    // Release the graphics device context.
 
    graphics.ReleaseHDC (graphicsDcHandle);

    // Does the caller want to know the rects?

    if (rects && (status == ERR_SUCCESS))
    {
        // Yes.

        rects->push_back (m_scaledRect);
    } // Endif.

    return (status);
} // Endproc.


void    GdiRasterText::DrawCharacter (FolioHandle                           dcHandle,
                                      Int32                                 drawingX,
                                      Int32                                 drawingY,
                                      UInt32                                characterWidth,          
                                      Int32                                 characterWidthInPixels,  
                                      Int32                                 characterHeightInPixels,
                                      const FolioByteBuffer::value_type*    characterBitBuffer) const
{
    Int32   y = drawingY;
    
    for (Int32 height = 0; height < characterHeightInPixels; ++height)
    {
        Int32   x = drawingX;

        for (UInt32 width = 0; width < characterWidth; ++width)
        {
            FolioByteBuffer::value_type byte = *characterBitBuffer;

            for (Int32 bit = 7; bit >= 0; --bit)
            {
                COLORREF    colour = 
                    (byte & static_cast<Int32> (std::pow (2, bit))) ? m_textColour.ToCOLORREF () : m_backgroundColour.ToCOLORREF ();

                for (UInt32 yScale = 0; yScale < m_screenScale; ++yScale)
                {
                    for (UInt32 xScale = 0; xScale < m_screenScale; ++xScale)
                    {
                        ::SetPixel (static_cast<HDC> (dcHandle), 
                                    x + xScale,  
                                    y + yScale, 
                                    colour);
                    } // Endfor.

                } // Endfor.

                x += m_screenScale;
            } // Endfor.

        } // Endfor.

        y  += m_screenScale;

        characterBitBuffer++;   // Next line.
    } // Endfor.

} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
