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
 *
 * @param [in] dcHandle
 * The device context handle.
 */
GdiRasterText::GdiRasterText (GdiRasterFont&        gdiRasterFont,
                              const Gdiplus::Color& textColour,
                              const Gdiplus::Color& backgroundColour,
                              FolioHandle           dcHandle)
:   m_gdiRasterFont(gdiRasterFont),
    m_textColour(textColour),
    m_backgroundColour(backgroundColour),
    m_dcHandle(dcHandle),
    m_isInverted(false),
    m_redrawGdiBitmapCache(true),
    m_redrawInvertedGdiBitmapCache(true)
{
} // Endproc.


/**
 * The class destructor.
 */
GdiRasterText::~GdiRasterText ()
{
    // Destroy the raster text.

    Destroy ();
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

    // Note the graphic element's current width and height.

    Int32   oldScreenWidth  = m_screenWidth;
    Int32   oldScreenHeight = m_screenHeight;

    // Set the graphic element's width and height.

    SetScreenWidth (m_textString.size () * m_gdiRasterFont.GetCharacterWidthInPixels ());
    SetScreenHeight (m_gdiRasterFont.GetCharacterHeightInPixels ());

    // Is the graphic element's width and height the same?

    if ((m_screenWidth  == oldScreenWidth) &&
        (m_screenHeight == oldScreenHeight))
    {
        // Yes. The GDI bitmap cache and inverted GDI bitmap cache will need to be 
        // redrawn.

        m_redrawGdiBitmapCache            = true;
        m_redrawInvertedGdiBitmapCache    = true;
    } // Endif.

    else
    {
        // No. The GDI bitmap cache and inverted GDI bitmap cache will need to be 
        // recreated.

        // Destroy the GDI bitmap cache.

        DestroyGdiBitmapCache ();

        // Destroy the inverted GDI bitmap cache.

        DestroyInvertedGdiBitmapCache ();
    } // Endelse.
    
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
    m_textColour = textColour;
    
    // The GDI bitmap cache and inverted GDI bitmap cache will need to be 
    // redrawn.

    m_redrawGdiBitmapCache          = true;
    m_redrawInvertedGdiBitmapCache  = true;
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
    
    // The GDI bitmap cache and inverted GDI bitmap cache will need to be 
    // redrawn.

    m_redrawGdiBitmapCache          = true;
    m_redrawInvertedGdiBitmapCache  = true;
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
 * Method that is used to create the GDI bitmap cache.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiRasterText::CreateGdiBitmapCache ()
{
    FolioStatus status = ERR_SUCCESS;

    // Is the GDI bitmap cache supported?

    if (IsGdiBitmapCacheSupported ())
    {
        // Yes. Create the GDI bitmap cache.

        m_gdiBitmapCache.reset (new GdiBitmap);

        status = m_gdiBitmapCache->Create (m_dcHandle,
                                           Gdiplus::Rect(0, 
                                           0, 
                                           m_scaledWidth, 
                                           m_scaledHeight));
        
        if (status == ERR_SUCCESS)
        {
            // Draw the GDI bitmap cache.

            DrawGdiBitmapCache (*m_gdiBitmapCache, false);  // Not inverted.
        
            // The GDI bitmap cache does not need redrawn.

            m_redrawGdiBitmapCache = false;
        } // Endif.
    
    } // Endif.

    else
    {
        // No.

        status = ERR_NOT_SUPPORTED;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to create the inverted GDI bitmap cache.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiRasterText::CreateInvertedGdiBitmapCache ()
{
    FolioStatus status = ERR_SUCCESS;

    // Is the inverted GDI bitmap cache supported?

    if (IsInvertedGdiBitmapCacheSupported ())
    {
        // Yes. Create the inverted GDI bitmap cache.

        m_invertedGdiBitmapCache.reset (new GdiBitmap);

        FolioStatus status = m_invertedGdiBitmapCache->Create (m_dcHandle,
                                                               Gdiplus::Rect(0, 
                                                                             0, 
                                                                             m_scaledWidth, 
                                                                             m_scaledHeight));

        if (status == ERR_SUCCESS)
        {
            // Draw the inverted GDI bitmap cache.

            DrawGdiBitmapCache (*m_invertedGdiBitmapCache, true);   // Inverted.
        
            // The inverted GDI bitmap cache does not need redrawn.

            m_redrawInvertedGdiBitmapCache = false;
        } // Endif.

    } // Endif.

    else
    {
        // No.

        status = ERR_NOT_SUPPORTED;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to set the raster text to non inverted.
 */
void    GdiRasterText::SetNonInverted ()
{
    m_isInverted = false;
} // Endproc.


/**
 * Method that is used to set the raster text to inverted.
 */
void    GdiRasterText::SetInverted ()
{
    m_isInverted = true;
} // Endproc.


/**
 * Method that is used to toggle the raster text to/from inverted.
 */
void    GdiRasterText::ToggleInverted ()
{
    m_isInverted = !m_isInverted;
} // Endproc.


/**
 * Indicates if the raster text is inverted.
 *
 * @return
 * <b>true</b> if the raster text is inverted, <b>false</b> otherwise.
 */
bool    GdiRasterText::IsInverted () const
{
    return (m_isInverted);
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
 * Method that is used to draw the raster text.
 *
 * @param [in] screenXLeft
 * The screen X left position of the graphic element.
 *
 * @param [in] screenYTop
 * The screen Y top position of the graphic element.
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
FolioStatus GdiRasterText::Draw (Int32              screenXLeft,
                                 Int32              screenYTop,
                                 Gdiplus::Graphics& graphics,
                                 RectList*          rects)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the GDI bitmap cache required?

    if (IsGdiBitmapCacheRqd ())
    {
        // Yes. Draw the GDI bitmap cache.

        status = DrawGdiBitmapCache (screenXLeft,
                                     screenYTop,
                                     graphics,
                                     rects);
    } // Endif.

    // Is the inverted GDI bitmap cache required?

    else
    if (IsInvertedGdiBitmapCacheRqd ())
    {
        // Yes. Draw the inverted GDI bitmap cache.

        status = DrawInvertedGdiBitmapCache (screenXLeft,
                                             screenYTop,
                                             graphics,
                                             rects);
    } // Endelseif.

    else
    {
        // No. Draw the raster text.

        status = DrawRasterText (screenXLeft,
                                 screenYTop,
                                 graphics,
                                 rects);
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to draw the raster text.
 *
 * @param [in] screenXLeft
 * The screen X left position of the graphic element.
 *
 * @param [in] screenYTop
 * The screen Y top position of the graphic element.
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
FolioStatus GdiRasterText::DrawRasterText (Int32                screenXLeft,
                                           Int32                screenYTop,
                                           Gdiplus::Graphics&   graphics,
                                           RectList*            rects)
{
    FolioStatus status = ERR_SUCCESS;

    // Get font attributes.

    UInt32  characterWidth          = m_gdiRasterFont.GetCharacterWidth ();
    Int32   characterWidthInPixels  = m_gdiRasterFont.GetCharacterWidthInPixels ();
    Int32   characterHeightInPixels = m_gdiRasterFont.GetCharacterHeightInPixels ();

    // Calculate the scaled position.

    Int32   scaledXLeft = screenXLeft * m_screenScale;
    Int32   scaledYTop  = screenYTop * m_screenScale;

    // Get the text and background colours.

    COLORREF    textColour          = GetTextColour (m_isInverted);
    COLORREF    backgroundColour    = GetBackgroundColour (m_isInverted);

    // Get the graphics device context.
     
    HDC graphicsDcHandle = graphics.GetHDC ();

    // Draw the text string.

    UInt32  textStringLength = m_textString.length ();

    for (UInt32 character = 0; character < textStringLength; ++character)
    {
        // Draw each character in the string.

        DrawCharacter (graphicsDcHandle,
                       scaledXLeft + (character * characterWidthInPixels * m_screenScale),
                       scaledYTop,
                       characterWidthInPixels,  
                       characterHeightInPixels,
                       &(m_textStringBitBuffer [character * characterWidth * characterHeightInPixels]),
                       textColour,      
                       backgroundColour);
    } // Endfor.

    // Release the graphics device context.
 
    graphics.ReleaseHDC (graphicsDcHandle);

    // Does the caller want to know the rects?

    if (rects && (status == ERR_SUCCESS))
    {
        // Yes.

        rects->push_back (Gdiplus::Rect(scaledXLeft, 
                                        scaledYTop,
                                        m_scaledWidth,
                                        m_scaledHeight));
    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that is used to draw a raster text character.
 *
 * @param [in] dcHandle
 * The device context handle.
 *
 * @param [in] drawingXStart
 * The drawing X start position.
 *
 * @param [in] drawingYStart
 * The drawing Y start position.
 *
 * @param [in] characterWidthInPixels
 * The raster text character width in pixels.
 *
 * @param [in] characterBitBuffer
 * The raster text character bit buffer.
 *
 * @param [in] inverted
 * <b>true</b> if the raster text character should be drawn inverted, 
 * <b>false</b> otherwise. 
 */
void    GdiRasterText::DrawCharacter (FolioHandle                           dcHandle,
                                      Int32                                 drawingXStart,
                                      Int32                                 drawingYStart,
                                      Int32                                 characterWidthInPixels,  
                                      Int32                                 characterHeightInPixels,
                                      const FolioByteBuffer::value_type*    characterBitBuffer,
                                      const COLORREF&                       textColour,
                                      const COLORREF&                       backgroundColour) const
{
    Int32   y = drawingYStart;
    
    for (Int32 height = 0; height < characterHeightInPixels; ++height)
    {
        Int32   x = drawingXStart;

        FolioByteBuffer::value_type characterByte = *characterBitBuffer;

        for (Int32 bit = 7; bit >= 0; --bit)
        {
            COLORREF    colour = (characterByte & static_cast<Int32> (std::pow (2, bit))) ? textColour : backgroundColour;

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

        y  += m_screenScale;

        characterBitBuffer++;   // Next line.
    } // Endfor.

} // Endproc.


/**
 * Method that is used to get the text colour of the text.
 *
 * @param [in] inverted
 * <b>true</b> if the inverted text colour is required, <b>false</b> otherwise. 
 *
 * @return
 * The text colour of the text.
 */
COLORREF    GdiRasterText::GetTextColour (bool inverted) const
{
    // The inverted text colour is the background colour.

    return (inverted ? m_backgroundColour.ToCOLORREF () : m_textColour.ToCOLORREF ());
} // Endproc.


/**
 * Method that is used to get the background colour of the text.
 *
 * @param [in] inverted
 * <b>true</b> if the inverted background colour is required, <b>false</b> otherwise. 
 *
 * @return
 * The background colour of the text.
 */
COLORREF    GdiRasterText::GetBackgroundColour (bool inverted) const
{
    // The inverted background colour is the text colour.
    
    return (inverted ? m_textColour.ToCOLORREF () : m_backgroundColour.ToCOLORREF ());
} // Endproc.


/**
 * Method that is used to destroy the raster text.
 */
void    GdiRasterText::Destroy ()
{
    // Destroy the GDI bitmap cache.

    DestroyGdiBitmapCache ();

    // Destroy the inverted GDI bitmap cache.

    DestroyInvertedGdiBitmapCache ();
} // Endproc.


/**
 * Method that is used to determine if the GDI bitmap cache is supported.
 *
 * @return
 * <b>true</b> if the GDI bitmap cache is supported, <b>false</b> otherwise.
 */
bool    GdiRasterText::IsGdiBitmapCacheSupported () const
{
    // If the device context has been specified then the GDI bitmap cache is 
    // supported.

    return (m_dcHandle != FOLIO_INVALID_HANDLE);
} // Endproc.


/**
 * Method that is used to determine if the inverted GDI bitmap cache is 
 * supported.
 *
 * @return
 * <b>true</b> if the inverted GDI bitmap cache is supported, <b>false</b> 
 * otherwise.
 */
bool    GdiRasterText::IsInvertedGdiBitmapCacheSupported () const
{
    // If the device context has been specified then the inverted GDI bitmap 
    // cache is supported.

    return (m_dcHandle != FOLIO_INVALID_HANDLE);
} // Endproc.


/**
 * Method that is used to determine if the GDI bitmap cache is required.
 *
 * @return
 * <b>true</b> if the GDI bitmap cache is required, <b>false</b> otherwise.
 */
bool    GdiRasterText::IsGdiBitmapCacheRqd () const
{
    // If the raster text is not inverted and the GDI bitmap cache is 
    // supported then the GDI bitmap cache is required.

    return (!m_isInverted && IsGdiBitmapCacheSupported ());
} // Endproc.


/**
 * Method that is used to determine if the inverted GDI bitmap cache is 
 * required.
 *
 * @return
 * <b>true</b> if the inverted GDI bitmap cache is required, <b>false</b> 
 * otherwise.
 */
bool    GdiRasterText::IsInvertedGdiBitmapCacheRqd () const
{
    // If the raster text is inverted and the inverted GDI bitmap cache is 
    // supported then the inverted GDI bitmap cache is required.

    return (m_isInverted && IsInvertedGdiBitmapCacheSupported ());
} // Endproc.


/**
 * Method that is used to destroy the GDI bitmap cache.
 */
void    GdiRasterText::DestroyGdiBitmapCache ()
{
    m_gdiBitmapCache.reset ();

    // The GDI bitmap cache will need to be redrawn.

    m_redrawGdiBitmapCache = true;
} // Endproc.


/**
 * Method that is used to determine if the GDI bitmap cache has been 
 * created.
 *
 * @return
 * <b>true</b> if the GDI bitmap cache has been created, <b>false</b> 
 * otherwise.
 */
bool    GdiRasterText::IsGdiBitmapCache () const
{
    return (m_gdiBitmapCache.get () != 0);
} // Endproc.


/**
 * Method that is used to destroy the inverted GDI bitmap cache.
 */
void    GdiRasterText::DestroyInvertedGdiBitmapCache ()
{
    m_invertedGdiBitmapCache.reset ();

    // The inverted GDI bitmap cache will need to be redrawn.

    m_redrawInvertedGdiBitmapCache = true;
} // Endproc.


/**
 * Method that is used to determine if the inverted GDI bitmap cache has been 
 * created.
 *
 * @return
 * <b>true</b> if the inverted GDI bitmap cache has been created, <b>false</b> 
 * otherwise.
 */
bool    GdiRasterText::IsInvertedGdiBitmapCache () const
{
    return (m_invertedGdiBitmapCache.get () != 0);
} // Endproc.


/**
 * Method that is used to draw the GDI bitmap cache.
 *
 * @param [in] screenXLeft
 * The screen X left position of the graphic element.
 *
 * @param [in] screenYTop
 * The screen Y top position of the graphic element.
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
FolioStatus GdiRasterText::DrawGdiBitmapCache (Int32                screenXLeft,
                                               Int32                screenYTop,
                                               Gdiplus::Graphics&   graphics,
                                               RectList*            rects)
{
    FolioStatus status = ERR_SUCCESS;

    // Does the GDI bitmap cache need to be created?

    if (!IsGdiBitmapCache ())
    {
        // Yes. Create the GDI bitmap cache.

        status = CreateGdiBitmapCache ();
    } // Endif.

    // Does the GDI bitmap cache need to be redrawn?

    else
    if (m_redrawGdiBitmapCache)
    {
        // Yes. Draw the GDI bitmap cache.

        DrawGdiBitmapCache (*m_gdiBitmapCache, false);  // Not inverted.
        
        // The GDI bitmap cache does not need redrawn.

        m_redrawGdiBitmapCache = false;
    } // Endelseif.

    if (status == ERR_SUCCESS)
    {
        // Draw the GDI bitmap cache.

        status = m_gdiBitmapCache->Draw (screenXLeft * m_screenScale,
                                         screenYTop * m_screenScale, 
                                         graphics,
                                         rects);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that is used to draw the inverted GDI bitmap cache.
 *
 * @param [in] screenXLeft
 * The screen X left position of the graphic element.
 *
 * @param [in] screenYTop
 * The screen Y top position of the graphic element.
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
FolioStatus GdiRasterText::DrawInvertedGdiBitmapCache (Int32                screenXLeft,
                                                       Int32                screenYTop,
                                                       Gdiplus::Graphics&   graphics,
                                                       RectList*            rects)
{
    FolioStatus status = ERR_SUCCESS;

    // Does the inverted GDI bitmap cache need to be created?

    if (!IsInvertedGdiBitmapCache ())
    {
        // Yes. Create the inverted GDI bitmap cache.

        status = CreateInvertedGdiBitmapCache ();
    } // Endif.

    // Does the inverted GDI bitmap cache need to be redrawn?

    else
    if (m_redrawInvertedGdiBitmapCache)
    {
        // Yes. Draw the inverted GDI bitmap cache.

        DrawGdiBitmapCache (*m_invertedGdiBitmapCache, true);   // Inverted.

        // The inverted GDI bitmap cache does not need redrawn.

        m_redrawInvertedGdiBitmapCache = false;
    } // Endelseif.

    if (status == ERR_SUCCESS)
    {
        // Draw the inverted GDI bitmap cache.

        status = m_invertedGdiBitmapCache->Draw (screenXLeft * m_screenScale,
                                                 screenYTop * m_screenScale, 
                                                 graphics,
                                                 rects);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that is used to draw a specified GDI bitmap cache.
 *
 * @param [in, out] gdiBitmap
 * The GDI bitmap cache to draw.
 *
 * @param [in] inverted
 * <b>true</b> if the GDI bitmap to be drawn should be inverted, <b>false</b> 
 * otherwise.
 */
void    GdiRasterText::DrawGdiBitmapCache (GdiBitmap&   gdiBitmap, 
                                           bool         inverted)
{
    // Get font attributes.

    UInt32  characterWidth          = m_gdiRasterFont.GetCharacterWidth ();
    Int32   characterWidthInPixels  = m_gdiRasterFont.GetCharacterWidthInPixels ();
    Int32   characterHeightInPixels = m_gdiRasterFont.GetCharacterHeightInPixels ();

    // Get the text and background colours.

    COLORREF    textColour          = GetTextColour (inverted);
    COLORREF    backgroundColour    = GetBackgroundColour (inverted);

    // Get the GDI bitmap device context.

    FolioHandle dcHandle = gdiBitmap.GetBitmapDcHandle ();

    // Draw the text string.

    UInt32  textStringLength = m_textString.length ();

    for (UInt32 character = 0; character < textStringLength; ++character)
    {
        // Draw each character in the string.

        DrawCharacter (dcHandle,
                       character * characterWidthInPixels * m_screenScale,
                       0,
                       characterWidthInPixels,  
                       characterHeightInPixels,
                       &(m_textStringBitBuffer [character * characterWidth * characterHeightInPixels]),
                       textColour,      
                       backgroundColour);
    } // Endfor.

} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
