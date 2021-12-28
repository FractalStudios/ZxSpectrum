// "Home-made" includes.
#include    <Trace.h>
#include    "..\Include\Gdi.h"

namespace Folio
{

namespace Core
{

namespace Graphic
{

namespace Gdi
{

using   namespace   Gdiplus;

/*
 * Function that is used to register with the GDI+ subsytem.
 *
 * @param [out] gdiHandle
 * On return, will hold the GDI+ handle, if successful. If this method 
 * fails then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus RegisterGdi (FolioHandle& gdiHandle)
{
    FolioStatus status = ERR_SUCCESS;

    // Startup GDI+.

    GdiplusStartupInput GdiStartupInput;

    Status  gdiStatus = GdiplusStartup (reinterpret_cast<ULONG_PTR*> (&(gdiHandle)), 
                                        &(GdiStartupInput), 
                                        0);

    if (gdiStatus != Ok)
    {
        // Build and log an error.

        status = FOLIO_MAKE_GDI_ERROR(gdiStatus);

        FOLIO_LOG_CALL_ERROR (TXT("GdiplusStartup"),
                              status);
    } // Endif.

    return (status);
} // Endproc.


/*
 * Function that is used to deregister from the GDI+ subsytem.
 *
 * @param [in] gdiHandle
 * The GDI+ handle obtained when registering with the GDI+ susbsystem.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus DeregisterGdi (FolioHandle gdiHandle)
{
    // Shutdown GDI+.

    GdiplusShutdown (reinterpret_cast<ULONG_PTR> (gdiHandle));

    return (ERR_SUCCESS);
} // Endproc.


/*
 * Function that is used to initialize a graphics object.
 *
 * @param [in, out] graphics
 * The graphics object.
 *
 * @param [in] eraseBackground
 * Indicates if the background should be erased.
 *
 * @param [in] backgroundColour
 * The background colour.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus InitializeGraphics (Gdiplus::Graphics&      graphics,
                                bool                    eraseBackground,
                                const Gdiplus::Color&   backgroundColour)
{
    FolioStatus status = ERR_SUCCESS;

    // Initialise the graphics.

    graphics.SetSmoothingMode (SmoothingModeNone);
    graphics.SetTextRenderingHint (TextRenderingHintAntiAlias); 

    // Erase the background?

    if (eraseBackground)
    {
        // Yes. Set the background colour.

        Status  gdiStatus = graphics.Clear (backgroundColour);

        if (gdiStatus != Ok)
        {
            // Build and log an error.
    
            status = FOLIO_MAKE_GDI_ERROR(gdiStatus);
    
            FOLIO_LOG_CALL_ERROR (TXT("Graphics::Clear"),
                                  status);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that is used to draw text.
 *
 * @param [in, out] graphics
 * The graphics object to draw to.
 *
 * @param [in] textString
 * The text string to draw.
 *
 * @param [in] font
 * The font to use when drawing the text.
 *
 * @param [in] xPos
 * The X position of the start of the text.
 *
 * @param [in] yPos
 * The Y position of the start of the text.
 *
 * @param [in] brush
 * The brush to use when drawing the text.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus DrawText (Gdiplus::Graphics&    graphics,
                      const FolioString&    textString,
                      const Gdiplus::Font&  font,
                      int                   xPos,
                      int                   yPos,
                      const Gdiplus::Brush& brush)
{
    FolioStatus status = ERR_SUCCESS;

    // Build a point.

    PointF  point(static_cast<REAL> (xPos),
                  static_cast<REAL> (yPos));

    // Make sure that the text string is 16-bit Unicode.

    FolioWideString string(textString);

    // Draw the string.

    Status  gdiStatus = graphics.DrawString (string.c_str (),
                                             string.size (),
                                             &(font),
                                             point,
                                             &(brush));

    if (gdiStatus != Ok)
    {
        // Build and log an error.

        status = FOLIO_MAKE_GDI_ERROR(gdiStatus);

        FOLIO_LOG_CALL_ERROR (TXT("Graphics::DrawString"),
                              status);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that is used to draw text in a rectangle.
 *
 * @param [in, out] graphics
 * The graphics object to draw to.
 *
 * @param [in] textString
 * The text string to draw.
 *
 * @param [in] font
 * The font to use when drawing the text.
 *
 * @param [in] area
 * The area of the rectangle to draw the text in.
 *
 * @param [in] stringFormat
 * The string format to use when drawing the text.
 *
 * @param [in] brush
 * The brush to use when drawing the text.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus DrawText (Gdiplus::Graphics&            graphics,
                      const FolioString&            textString,
                      const Gdiplus::Font&          font,
                      const Gdiplus::Rect&          area,
                      const Gdiplus::StringFormat&  stringFormat,
                      const Gdiplus::Brush&         brush)
{
    FolioStatus status = ERR_SUCCESS;

    RectF   layoutRect(static_cast<REAL> (area.X),
                       static_cast<REAL> (area.Y),
                       static_cast<REAL> (area.Width),
                       static_cast<REAL> (area.Height));

    // Make sure that the text string is 16-bit Unicode.

    FolioWideString string(textString);

    // Draw the string.

    Status  gdiStatus = graphics.DrawString (string.c_str (),
                                             string.size (),
                                             &(font),
                                             layoutRect,
                                             &(stringFormat),
                                             &(brush));

    if (gdiStatus != Ok)
    {
        // Build and log an error.

        status = FOLIO_MAKE_GDI_ERROR(gdiStatus);

        FOLIO_LOG_CALL_ERROR (TXT("Graphics::DrawString"),
                              status);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that is used to draw a line.
 *
 * @param [in, out] graphics
 * The graphics object to draw to.
 *
 * @param [in] xPosStart
 * The X position of the start point of the line.
 *
 * @param [in] yPosStart
 * The Y position of the start point of the line.
 *
 * @param [in] xPosEnd
 * The X position of the end point of the line.
 *
 * @param [in] yPosEnd
 * The Y position of the end point of the line.
 *
 * @param [in] pen
 * The pen to use to draw the line.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus DrawLine (Gdiplus::Graphics     &graphics, 
                      int                   xPosStart,
                      int                   yPosStart,
                      int                   xPosEnd,
                      int                   yPosEnd,
                      const Gdiplus::Pen&   pen)
{
    FolioStatus status = ERR_SUCCESS;

    // Draw the line.

    Status  gdiStatus = graphics.DrawLine (&(pen), 
                                           xPosStart, 
                                           yPosStart, 
                                           xPosEnd, 
                                           yPosEnd);

    if (gdiStatus != Ok)
    {
        // Build and log an error.

        status = FOLIO_MAKE_GDI_ERROR(gdiStatus);

        FOLIO_LOG_CALL_ERROR_4 (TXT("Graphics::DrawLine"),
                                status,
                                xPosStart, 
                                yPosStart, 
                                xPosEnd, 
                                yPosEnd);
    } // Endif.

    return (status);
} // Endproc


/**
 * Function that is used to draw a graphics path.
 *
 * @param [in, out] graphics
 * The graphics object to draw to.
 *
 * @param [in] graphicsPath
 * The graphics path object.
 *
 * @param [in] pen
 * The pen to use to draw the graphics path.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus DrawPath (Gdiplus::Graphics&            graphics, 
                      const Gdiplus::GraphicsPath&  graphicsPath,
                      const Gdiplus::Pen&           pen)
{
    FolioStatus status = ERR_SUCCESS;

    // Draw the path.

    Status  gdiStatus = graphics.DrawPath (&(pen), &(graphicsPath));

    if (gdiStatus != Ok)
    {
        // Build and log an error.

        status = FOLIO_MAKE_GDI_ERROR(gdiStatus);

        FOLIO_LOG_CALL_ERROR (TXT("Graphics::DrawPath"),
                              status);
    } // Endif.

    return (status);
} // Endproc


/**
 * Function that is used to fill a graphics path.
 *
 * @param [in, out] graphics
 * The graphics object to fill to.
 *
 * @param [in] graphicsPath
 * The graphics path object.
 *
 * @param [in] brush
 * The brush to use to fill the graphics path.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus FillPath (Gdiplus::Graphics&            graphics, 
                      const Gdiplus::GraphicsPath&  graphicsPath,
                      const Brush&                  brush)
{
    FolioStatus status = ERR_SUCCESS;

    // Fill the path.

    Status  gdiStatus = graphics.FillPath (&(brush), &(graphicsPath));

    if (gdiStatus != Ok)
    {
        // Build and log an error.

        status = FOLIO_MAKE_GDI_ERROR(gdiStatus);

        FOLIO_LOG_CALL_ERROR (TXT("Graphics::FillPath"),
                              status);
    } // Endif.

    return (status);
} // Endproc


/**
 * Function that is used to draw a rectangle.
 *
 * @param [in, out] graphics
 * The graphics object to draw to.
 *
 * @param [in] rect
 * The rect of the rectangle.
 *
 * @param [in] pen
 * The pen to use to draw the rectangle.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus DrawRectangle (Gdiplus::Graphics&   graphics, 
                           const Gdiplus::Rect& rect,
                           const Gdiplus::Pen&  pen)
{
    FolioStatus status = ERR_SUCCESS;

    // Draw the rectangle.

    Status  gdiStatus = graphics.DrawRectangle (&(pen), rect);

    if (gdiStatus != Ok)
    {
        // Build and log an error.

        status = FOLIO_MAKE_GDI_ERROR(gdiStatus);

        FOLIO_LOG_CALL_ERROR (TXT("Graphics::DrawRectangle"),
                              status);
    } // Endif.

    return (status);
} // Endproc


/**
 * Function that is used to fill a rectangle.
 *
 * @param [in, out] graphics
 * The graphics object to fill to.
 *
 * @param [in] rect
 * The rect of the rectangle.
 *
 * @param [in] brush
 * The brush to use to fill the rectangle.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus FillRectangle (Gdiplus::Graphics&   graphics, 
                           const Gdiplus::Rect& rect,
                           const Brush&         brush)
{
    FolioStatus status = ERR_SUCCESS;

    // Create a pen.

    Gdiplus::Pen    pen(&(brush));

    // Set its alignment.

    Status  gdiStatus = pen.SetAlignment (PenAlignmentInset);

    if (gdiStatus == Ok)
    {
        // Draw the rectangle.
        
        //gdiStatus = graphics.DrawRectangle (&(pen), rect);
    
        if (gdiStatus == Ok)
        {
            // Fill the rectangle.

            gdiStatus = graphics.FillRectangle (&(brush), rect);

            if (gdiStatus != Ok)
            {
                // Build and log an error.

                status = FOLIO_MAKE_GDI_ERROR(gdiStatus);

                FOLIO_LOG_CALL_ERROR (TXT("Graphics::FillRectangle"),
                                      status);
            } // Endif.

        } // Endif.

        else
        {
            // Build and log an error.

            status = FOLIO_MAKE_GDI_ERROR(gdiStatus);

            FOLIO_LOG_CALL_ERROR (TXT("Graphics::DrawRectangle"),
                                    status);
        } // Endelse.

    } // Endif.

    else
    {
        // Build and log an error.

        status = FOLIO_MAKE_GDI_ERROR(gdiStatus);

        FOLIO_LOG_CALL_ERROR (TXT("Pen::SetAlignment"),
                                status);
    } // Endelse.

    return (status);
} // Endproc


/**
 * Function that is used to draw an ellipse.
 *
 * @param [in, out] graphics
 * The graphics object to draw to.
 *
 * @param [in] rect
 * The rect of the ellipse.
 *
 * @param [in] pen
 * The pen to use to draw the ellipse.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus DrawEllipse (Gdiplus::Graphics&     graphics, 
                         const Gdiplus::Rect&   rect,
                         const Gdiplus::Pen&    pen)
{
    FolioStatus status = ERR_SUCCESS;

    // Draw the ellipse.

    Status  gdiStatus = graphics.DrawEllipse (&(pen), rect);

    if (gdiStatus != Ok)
    {
        // Build and log an error.

        status = FOLIO_MAKE_GDI_ERROR(gdiStatus);

        FOLIO_LOG_CALL_ERROR (TXT("Graphics::DrawEllipse"),
                              status);
    } // Endif.

    return (status);
} // Endproc


/**
 * Function that is used to fill an ellipse.
 *
 * @param [in, out] graphics
 * The graphics object to fill to.
 *
 * @param [in] rect
 * The rect of the ellipse.
 *
 * @param [in] brush
 * The brush to use to fill the ellipse.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus FillEllipse (Gdiplus::Graphics&     graphics, 
                         const Gdiplus::Rect&   rect,
                         const Brush&           brush)
{
    FolioStatus status = ERR_SUCCESS;

    // Create a pen.

    Gdiplus::Pen    pen(&(brush));

    // Set its alignment.

    Status  gdiStatus = pen.SetAlignment (PenAlignmentInset);

    if (gdiStatus == Ok)
    {
        // Draw the ellipse.
        
        gdiStatus = graphics.DrawEllipse (&(pen), rect);
    
        if (gdiStatus == Ok)
        {
            // Fill the ellipse.

            gdiStatus = graphics.FillEllipse (&(brush), rect);

            if (gdiStatus != Ok)
            {
                // Build and log an error.

                status = FOLIO_MAKE_GDI_ERROR(gdiStatus);

                FOLIO_LOG_CALL_ERROR (TXT("Graphics::FillEllipse"),
                                      status);
            } // Endif.

        } // Endif.

        else
        {
            // Build and log an error.

            status = FOLIO_MAKE_GDI_ERROR(gdiStatus);

            FOLIO_LOG_CALL_ERROR (TXT("Graphics::DrawEllipse"),
                                    status);
        } // Endelse.

    } // Endif.

    else
    {
        // Build and log an error.

        status = FOLIO_MAKE_GDI_ERROR(gdiStatus);

        FOLIO_LOG_CALL_ERROR (TXT("Pen::SetAlignment"),
                                status);
    } // Endelse.

        return (status);
} // Endproc


/**
 * Function that is used to draw a bitmap.
 *
 * @param [in, out] graphics
 * The graphics object to draw to.
 *
 * @param [in] bitmap
 * The bitmap object.
 *
 * @param [in] area
 * The area of the bitmap.
 *
 * @param [in] xPos
 * The X position of the start of the bitmap.
 *
 * @param [in] yPos
 * The Y position of the start of the bitmap.
 *
 * @param [in] width
 * The width of the bitmap.
 *
 * @param [in] height 
 * The height of the bitmap.
 *
 * @param [in] imageAttributes
 * The image attributes of the bitmap.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus DrawBitmap (Gdiplus::Graphics&              graphics, 
                        Gdiplus::Bitmap&                bitmap,
                        const Gdiplus::Rect&            area, 
                        int                             xPos,
                        int                             yPos,
                        int                             width,
                        int                             height,
                        const Gdiplus::ImageAttributes& imageAttributes)
{
    FolioStatus status = ERR_SUCCESS;

    // Draw the image.

    Status  gdiStatus = graphics.DrawImage (&(bitmap), 
                                            area, 
                                            xPos, 
                                            yPos, 
                                            width,
                                            height,
                                            UnitPixel,
                                            &(imageAttributes));

    if (gdiStatus != Ok)
    {
        // Build and log an error.

        status = FOLIO_MAKE_GDI_ERROR(gdiStatus);

        FOLIO_LOG_CALL_ERROR (TXT("Graphics::DrawImage"),
                              status);
    } // Endif.

    return (status);
} // Endproc


/**
 * Function that is used to save a bitmap.
 *
 * @param [in] fileName
 * The file name.
 *
 * @param [in] bitmap
 * The bitmap object.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus SaveBitmap (const FolioString&  fileName,
                        Gdiplus::Bitmap&    bitmap)
{
    CLSID   clsid;  

    FolioStatus status = QueryEncoderClsid (TXT("image/bmp"), clsid);

    if (status == ERR_SUCCESS)
    {
        // Save the bitmap.

        Status  gdiStatus = bitmap.Save (fileName.c_str (), 
                                         &(clsid), 
                                         NULL);

        if (gdiStatus != Ok)
        {
            // Build and log an error.

            status = FOLIO_MAKE_GDI_ERROR(gdiStatus);

            FOLIO_LOG_CALL_ERROR (TXT("Graphics::SetClip"),
                                  status);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that is used to set the specified clipping region of the specified 
 * graphics object.
 *
 * @param [in, out] graphics
 * The graphics object.
 *
 * @param [in] clippingRegion
 * The clipping region.
 *
 * @param [in] combineMode
 * The combine mode that specifies how the region is combined with any existing 
 * region.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus SetClippingRegion (Gdiplus::Graphics&       graphics,
                               const Gdiplus::Region&   clippingRegion,
                               Gdiplus::CombineMode     combineMode)
{
    FolioStatus status = ERR_SUCCESS;

    // Set the clipping region.

    Status  gdiStatus = graphics.SetClip (&(clippingRegion), combineMode);

    if (gdiStatus != Ok)
    {
        // Build and log an error.

        status = FOLIO_MAKE_GDI_ERROR(gdiStatus);

        FOLIO_LOG_CALL_ERROR (TXT("Graphics::SetClip"),
                              status);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that is used to reset the clipping region of the specified 
 * graphics object.
 *
 * @param [in, out] graphics
 * The graphics object.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus ResetClippingRegion (Gdiplus::Graphics& graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // Reset the clipping region.

    Status  gdiStatus = graphics.ResetClip ();

    if (gdiStatus != Ok)
    {
        // Build and log an error.

        status = FOLIO_MAKE_GDI_ERROR(gdiStatus);

        FOLIO_LOG_CALL_ERROR (TXT("Graphics::ResetClip"),
                              status);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that is used to obtain the clipping region of the specified graphics 
 * object.
 *
 * @param [in, out] graphics
 * The graphics object.
 *
 * @param [out] clippingRegion
 * On return, will hold the clipping region, if successful. If this method 
 * fails then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus QueryClippingRegion (Gdiplus::Graphics& graphics, 
                                 Gdiplus::Region&   clippingRegion)
{
    FolioStatus status = ERR_SUCCESS;

    // Get the clipping region.

    Status  gdiStatus = graphics.GetClip (&(clippingRegion));

    if (gdiStatus != Ok)
    {
        // Build and log an error.

        status = FOLIO_MAKE_GDI_ERROR(gdiStatus);

        FOLIO_LOG_CALL_ERROR (TXT("Graphics::GetClip"),
                              status);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that is used to obtain the clipping region handle of the specified 
 * graphics object.
 *
 * @param [in, out] graphics
 * The graphics object.
 *
 * @param [out] clippingRegionHandle
 * On return, will hold the clipping region handle, if successful. If this 
 * method fails then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus QueryClippingRegionHandle (Gdiplus::Graphics&   graphics, 
                                       FolioHandle&         clippingRegionHandle)
{
    // Query the clipping region.

    Region  clippingRegion;

    FolioStatus status = QueryClippingRegion (graphics, clippingRegion);

    if (status == ERR_SUCCESS)
    {
        clippingRegionHandle = clippingRegion.GetHRGN (&(graphics));
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that is used to query the encoded class identifier for a 
 * specified format.
 *
 * @param [in] format
 * The encoded format.
 *
 * @param [out] clsid
 * The class identiifer.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus   QueryEncoderClsid (const FolioString& format,
                                 CLSID&             clsid)
{
    FolioStatus status = ERR_SUCCESS;

    UInt32  numEncoders = 0;    // Initialise!
    UInt32  size        = 0;
   
    Status   gdiStatus = GetImageEncodersSize (&(numEncoders), &(size));

    if (gdiStatus == Ok)
    {
        if (size)
        {
            ImageCodecInfo* pImageCodecInfo = reinterpret_cast<ImageCodecInfo *> (new BYTE [size]);
   
            gdiStatus = GetImageEncoders (numEncoders, 
                                          size, 
                                          pImageCodecInfo);

            if (gdiStatus == Ok)
            {
                bool    found = false;

                for (UInt32 encoder = 0; 
                     !found && (encoder < numEncoders);
                     ++encoder)
                {
                    if (STRCMP (pImageCodecInfo [encoder].MimeType, 
                        format.c_str ()) == 0)
                    {
                        clsid = pImageCodecInfo [encoder].Clsid;

                        found = true;  
                    } // Endif.

                } // Endfor.

                if (!found)
                {
                    status = ERR_NOT_FOUND;
                } // Endif.

            } // Endif.

            else
            {
                // Build and log an error.

                status = FOLIO_MAKE_GDI_ERROR(gdiStatus);

                FOLIO_LOG_CALL_ERROR (TXT("Graphics::GetImageEncoders"),
                                      status);
            } // Endelse.

            delete [] pImageCodecInfo;
        } // Endif.

        else
        {
            status = ERR_NO_MORE_DATA;
        } // Endelse.

    } // Endif.

    else
    {
        // Build and log an error.

        status = FOLIO_MAKE_GDI_ERROR(gdiStatus);

        FOLIO_LOG_CALL_ERROR (TXT("Graphics::GetImageEncodersSize"),
                              status);
    } // Endelse.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
