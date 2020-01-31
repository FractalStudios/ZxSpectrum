// STL includes.
#define NOMINMAX 
#include    <algorithm>
#include    <memory>

// "Home-made" includes.
#include    <Trace.h>
#include    "Gdi.h"
#include    "GdiBitmap.h"
#include    "HandleMonitor.h"

namespace Folio
{

namespace Core
{

namespace Util
{

namespace Gdi
{

/**
 * Function that will create a bitmap compatible with the specified device 
 * context.
 *
 * @param [in] dcHandle
 * The device context handle.
 *
 * @param [in] bitmapWidth
 * The width of the bitmap.
 *
 * @param [in] bitmapHeight
 * The height of the bitmap.
 *
 * @param [out] bitmapHandle
 * On return, will hold the bitmap handle, if successful. If this method fails 
 * then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the bitmap was successfully created.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus CreateCompatibleBitmap (FolioHandle     dcHandle,
                                    Int32           bitmapWidth,
                                    Int32           bitmapHeight,
                                    FolioHandle&    bitmapHandle)
{
    FolioStatus status = ERR_SUCCESS;

    // Create a display compatible bitmap.

    bitmapHandle = ::CreateCompatibleBitmap (reinterpret_cast<HDC> (dcHandle),
                                             bitmapWidth,
                                             bitmapHeight);

    if (bitmapHandle == FOLIO_INVALID_HANDLE)
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_3 (TXT("CreateCompatibleBitmap"),
                                status,
                                dcHandle,
                                bitmapWidth,
                                bitmapHeight);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that will create a monochrome bitmap compatible with the specified device 
 * context, from the specified bitmap.
 *
 * @param [in] dcHandle
 * The device context handle.
 *
 * @param [in] sourceBitmapHandle
 * The source bitmap handle.
 *
 * @param [in] transparentColourRef
 * The transparent colour.
 *
 * @param [out] monochromeBitmapHandle
 * On return, will hold the monochrome bitmap handle, if successful. If this method fails 
 * then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the bitmap was successfully created.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus CreateMonochromeBitmap (FolioHandle         dcHandle,
                                    FolioHandle         sourceBitmapHandle,
                                    const COLORREF&     transparentColourRef,
                                    FolioHandle&        monochromeBitmapHandle)
{
    // Query the source bitmap's dimensions.

    BITMAP  bitmap = {0};   // Initialise!
    FolioStatus status = QueryBitmapDetails (sourceBitmapHandle, bitmap);

    if (status == ERR_SUCCESS)
    {
        // Create a monochrome bitmap.

        monochromeBitmapHandle = ::CreateBitmap (bitmap.bmWidth, 
                                                 bitmap.bmHeight, 
                                                 1, 
                                                 1, 
                                                 NULL);

        if (monochromeBitmapHandle != FOLIO_INVALID_HANDLE)
        {
            // Create a compatible memory DC for the monochrome bitmap.

            FolioHandle monochromeMemoryDcHandle = FOLIO_INVALID_HANDLE;    // Initialise!

            status = CreateCompatibleMemoryDC (dcHandle, monochromeMemoryDcHandle);

            if (status == ERR_SUCCESS)
            {
                // Select the monochrome bitmap into the DC.

                FolioHandle oldMonochromeObjectHandle = FOLIO_INVALID_HANDLE;    // Initialise!

                status = SelectObjectIntoDC (monochromeMemoryDcHandle, monochromeBitmapHandle, &(oldMonochromeObjectHandle));

                if (status == ERR_SUCCESS)
                {  
                    // Set the background colour of the source bitmap to the transparent colour.

                    ::SetBkColor (static_cast<HDC> (dcHandle), transparentColourRef);

                    // Copy the bits from the source bitmap to the monochrome bitmap. Everything
                    // with the background colour ends up white while everything else ends up
                    // black.

                    status = CopyBitmap (monochromeMemoryDcHandle, 
                                         0, 
                                         0, 
                                         bitmap.bmWidth, 
                                         bitmap.bmHeight, 
                                         dcHandle, 
                                         0,
                                         0, 
                                         SRCCOPY);

                    if (status == ERR_SUCCESS)
                    {
                        // Take our new mask and use it to turn the transparent colour in our
                        // original source bitmap to black so the transparency effect will
                        // work right.

                        status = CopyBitmap (dcHandle, 
                                             0, 
                                             0, 
                                             bitmap.bmWidth, 
                                             bitmap.bmHeight, 
                                             monochromeMemoryDcHandle, 
                                             0, 
                                             0, 
                                             SRCINVERT);
                    } // Endif.

                    // Reselect the old monochrome bitmap into the DC.
        
                    SelectObjectIntoDC (monochromeMemoryDcHandle, oldMonochromeObjectHandle);  
                } // Endif.

                // Destroy the monochrome memory device context.

                DestroyMemoryDC (monochromeMemoryDcHandle);
            } // Endif.

        } // Endif.

        else
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_2 (TXT("CreateBitmap"),
                                    status,
                                    bitmap.bmWidth,
                                    bitmap.bmHeight);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that will create a bitmap compatible with the specified device 
 * context, from the specified device-independent bitmap.
 *
 * @param [in] dcHandle
 * The device context handle.
 *
 * @param [in] diBitmapHandle
 * The device-independent bitmap handle.
 *
 * @param [out] bitmapHandle
 * On return, will hold the bitmap handle, if successful. If this method fails 
 * then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the bitmap was successfully created.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus CreateCompatibleBitmap (FolioHandle     dcHandle,
                                    FolioHandle     diBitmapHandle,
                                    FolioHandle&    bitmapHandle)
{
    // Query the device-independent bitmap details.

    DIBITMAPINFO    diBitmapInfo    = {0};   // Initialise!
    Byte*           diBitmapPixels  = 0;

    FolioStatus status = QueryDiBitmapDetails (dcHandle,
                                               diBitmapHandle,
                                               diBitmapInfo,
                                               diBitmapPixels);

    if (status == ERR_SUCCESS)
    {
        // Create a display compatible bitmap.

        bitmapHandle = ::CreateDIBitmap (static_cast<HDC> (dcHandle),
                                         &(diBitmapInfo.bmiHeader),
                                         CBM_INIT,
                                         diBitmapPixels,
                                         reinterpret_cast<BITMAPINFO *> (&(diBitmapInfo)),
                                         DIB_RGB_COLORS);

        if (bitmapHandle == FOLIO_INVALID_HANDLE)
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_2 (TXT("CreateDIBitmap"),
                                    status,
                                    dcHandle,
                                    diBitmapHandle);
        } // Endif.

        delete [] diBitmapPixels;
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that will create a device-independent bitmap, copied from a specified 
 * device-independent bitmap.
 *
 * @param [in] dcHandle
 * The device context handle.
 *
 * @param [in] diBitmapHandle
 * The device-independent bitmap handle.
 *
 * @param [out] copiedDiBitmapHandle
 * On return, will hold the bitmap handle, if successful. If this method fails 
 * then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the bitmap was successfully created.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus CreateCopiedDiBitmap (FolioHandle   dcHandle, 
                                  FolioHandle   diBitmapHandle, 
                                  FolioHandle&  copiedDiBitmapHandle)
{
    // Query the device-independent bitmap details.

    DIBITMAPINFO    diBitmapInfo    = {0};   // Initialise!
    Byte*           diBitmapPixels  = 0;

    FolioStatus status = QueryDiBitmapDetails (dcHandle,
                                               diBitmapHandle,
                                               diBitmapInfo,
                                               diBitmapPixels);

    if (status == ERR_SUCCESS)
    {
	    // Create a device-independent bitmap.

        Byte*   copiedDiBitmapPixels = 0;  // Initialise!

        copiedDiBitmapHandle = ::CreateDIBSection (static_cast<HDC> (dcHandle), 
                                                   reinterpret_cast<BITMAPINFO *> (&(diBitmapInfo)), 
                                                   DIB_RGB_COLORS,
                                                   reinterpret_cast<LPVOID *> (&(copiedDiBitmapPixels)),
                                                   NULL, 
                                                   0);

        if (copiedDiBitmapHandle != FOLIO_INVALID_HANDLE)
        {
            // Copy the device-independent bitmap's pixels.

            ::memcpy (copiedDiBitmapPixels, diBitmapPixels, diBitmapInfo.bmiHeader.biSizeImage);

            delete [] diBitmapPixels;
        } // Endif.

        else
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_2 (TXT("CreateDIBSection"),
                                    status,
                                    dcHandle,
                                    diBitmapHandle);
        } // Endelse.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that will create a device-independent bitmap, from a specified 
 * device-independent bitmap rotated at a specific angle.
 *
 * @param [in] dcHandle
 * The device context handle.
 *
 * @param [in] diBitmapHandle
 * The device-independent bitmap handle.
 *
 * @param [in] radians
 * The angle to rotate.
 *
 * @param [in] backgroundColourRef
 * The default bacground colour.
 *
 * @param [out] rotatedDiBitmapHandle
 * On return, will hold the bitmap handle, if successful. If this method fails 
 * then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the bitmap was successfully created.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus CreateRotatedDiBitmap (FolioHandle      dcHandle, 
                                   FolioHandle      diBitmapHandle, 
                                   const double&    radians, 
                                   const COLORREF&  backgroundColourRef,
                                   FolioHandle&     rotatedDiBitmapHandle)
{
    // Query the device-independent bitmap details.

    DIBITMAPINFO    diBitmapInfo    = {0};   // Initialise!
    Byte*           diBitmapPixels  = 0;

    FolioStatus status = QueryDiBitmapDetails (dcHandle,
                                               diBitmapHandle,
                                               diBitmapInfo,
                                               diBitmapPixels);

    if (status == ERR_SUCCESS)
    {
	    UInt32  bpp = diBitmapInfo.bmiHeader.biBitCount;  // Bits per pixel.
	
	    UInt32  numColours = 
            diBitmapInfo.bmiHeader.biClrUsed ? diBitmapInfo.bmiHeader.biClrUsed : 1 << bpp;

	    Int32   bitmapWidth     = diBitmapInfo.bmiHeader.biWidth;
	    Int32   bitmapHeight    = diBitmapInfo.bmiHeader.biHeight;
	    UInt32  bytesPerRow     = (((bitmapWidth * bpp) + 31) & ~31) / 8;
 
	    // Compute the cosine and sine only once.

	    double  cosine  = std::cos (radians);
	    double  sine    = std::sin (radians);
 
	    // Compute the dimensions of the resulting bitmap.

	    // First get the coordinates of the 3 corners other than origin.

	    Int32   x1 = static_cast<Int32> (0.5 - bitmapHeight * sine);
	    Int32   y1 = static_cast<Int32> (0.5 + bitmapHeight * cosine);
	    Int32   x2 = static_cast<Int32> (0.5 + bitmapWidth * cosine - bitmapHeight * sine);
	    Int32   y2 = static_cast<Int32> (0.5 + bitmapHeight * cosine + bitmapWidth * sine);
	    Int32   x3 = static_cast<Int32> (0.5 + bitmapWidth * cosine);
	    Int32   y3 = static_cast<Int32> (0.5 + bitmapWidth * sine);

	    Int32   minX = std::min (0, std::min (x1, std::min (x2, x3)));
	    Int32   minY = std::min (0, std::min (y1, std::min (y2, y3)));
	    Int32   maxX = std::max (x1, std::max (x2, x3));
	    Int32   maxY = std::max (y1, std::max (y2, y3));
 
	    Int32   rotatedDiBitmapWidth    = maxX - minX + ((minX < 0) ? 1 : 0);
	    Int32   rotatedDiBitmapHeight   = maxY - minY + ((minY < 0) ? 1 : 0);

	    UInt32  rotatedDiBitmapBytesPerRow  = (((rotatedDiBitmapWidth * bpp) + 31) & ~31) / 8;
	    UInt32  rotatedDiBitmapImageSize    = rotatedDiBitmapBytesPerRow * rotatedDiBitmapHeight;

        DIBITMAPINFO    rotatedDiBitmapInfo = diBitmapInfo;
	    rotatedDiBitmapInfo.bmiHeader.biWidth       = rotatedDiBitmapWidth;
	    rotatedDiBitmapInfo.bmiHeader.biHeight      = rotatedDiBitmapHeight;
	    rotatedDiBitmapInfo.bmiHeader.biSizeImage   = rotatedDiBitmapImageSize;

	    // Create a device-independent bitmap.

        Byte*   rotatedDiBitmapPixels = 0;  // Initialise!

        rotatedDiBitmapHandle = ::CreateDIBSection (static_cast<HDC> (dcHandle), 
                                                    reinterpret_cast<BITMAPINFO *> (&(rotatedDiBitmapInfo)), 
                                                    DIB_RGB_COLORS,
                                                    reinterpret_cast<LPVOID *> (&(rotatedDiBitmapPixels)),
                                                    NULL, 
                                                    0);

        if (rotatedDiBitmapHandle != FOLIO_INVALID_HANDLE)
        {
            // Find the background colour in the colour table.

		    for (UInt32 colourIndex = 0; colourIndex < numColours; ++colourIndex)
		    {
                COLORREF    colourTableRef = RGB(diBitmapInfo.bmiColors [colourIndex].rgbRed, 
                                                 diBitmapInfo.bmiColors [colourIndex].rgbGreen, 
                                                 diBitmapInfo.bmiColors [colourIndex].rgbBlue);

			    if (colourTableRef == backgroundColourRef)
			    {
                    // Set the background colour.

				    ::memset (rotatedDiBitmapPixels, 
                              colourIndex | colourIndex << 4, 
                              rotatedDiBitmapImageSize);

				    break; // Get-outta-here!
			    } // Endif.

		    } // Endfor.
 
	        // Now do the actual rotating a pixel at a time.
	        // Computing the destination point for each source point will leave a 
            // few pixels that do not get covered, so we use a reverse transform, 
            // i.e. compute the source point for each destination point.

	        for (Int32 y = 0; y < rotatedDiBitmapHeight; ++y)
	        {
		        for (Int32 x = 0; x < rotatedDiBitmapWidth; ++x)
		        {
                    Int32   sourceX = static_cast<Int32> (0.5 + (x + minX) * cosine + (y + minY) * sine);
			        Int32   sourceY = static_cast<Int32> (0.5 + (y + minY) * cosine - (x + minX) * sine);

			        if ((sourceX >= 0) && (sourceX < bitmapWidth) && 
                        (sourceY >= 0) && (sourceY < bitmapHeight))
			        {
                        // Set the destination pixel.

					    Byte    mask = *(diBitmapPixels + bytesPerRow * sourceY + sourceX / 2) & ((sourceX & 0x01) ? 0x0f : 0xf0);

					    // Adjust mask for rotated bitmap.

					    if ((sourceX & 0x01) != (x & 0x01))
                        {
						    mask = (mask & 0xf0) ? (mask >> 4) : (mask << 4);
                        } // Endif.

					    *(rotatedDiBitmapPixels + (rotatedDiBitmapBytesPerRow * y) + (x / 2)) &= ~((x & 0x01) ? 0x0f : 0xf0);
					    *(rotatedDiBitmapPixels + (rotatedDiBitmapBytesPerRow * y) + (x / 2)) |= mask;
                    } // Endif.

                } // Endfor.

            } // Endfor.

            delete [] diBitmapPixels;
        } // Endif.

        else
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_2 (TXT("CreateDIBSection"),
                                    status,
                                    dcHandle,
                                    diBitmapHandle);
        } // Endelse.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that will load a bitmap.
 *
 * @param [in] instanceHandle
 * The application instance handle.
 *
 * @param [in] resourceId
 * The resource identifier of the bitmap to load.
 *
 * @param [in] loadDiBitmap
 * Indicates if the bitmap should be loaded as a device-independent bitmap.
 *
 * @param [out] bitmapHandle
 * On return, will hold the bitmap handle, if successful. If this method fails 
 * then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the bitmap was successfully loaded.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus LoadBitmap (FolioHandle     instanceHandle,
                        UInt16          resourceId,
                        bool            loadDiBitmap,
                        FolioHandle&    bitmapHandle)
{
    FolioStatus status = ERR_SUCCESS;

    // Load the bitmap.

    bitmapHandle = ::LoadImage (static_cast<HINSTANCE> (instanceHandle), 
                                MAKEINTRESOURCE(resourceId),
                                IMAGE_BITMAP,
                                0,
                                0,
                                loadDiBitmap ? LR_CREATEDIBSECTION : LR_DEFAULTCOLOR);

    if (bitmapHandle == FOLIO_INVALID_HANDLE)
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_2 (TXT("LoadImage"),
                                status,
                                instanceHandle,
                                resourceId);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that will load a bitmap.
 *
 * @param [in] fileName
 * The file name of the bitmap.
 *
 * @param [in] loadDiBitmap
 * Indicates if the bitmap should be loaded as a device-independent bitmap.
 *
 * @param [out] bitmapHandle
 * On return, will hold the bitmap handle, if successful. If this method fails 
 * then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the bitmap was successfully loaded.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus LoadBitmap (const FolioString&  fileName,
                        bool                loadDiBitmap,
                        FolioHandle&        bitmapHandle)
{
    FolioStatus status = ERR_SUCCESS;

    // Load the bitmap.

    bitmapHandle = ::LoadImage (0,          
                                fileName.c_str (),
                                IMAGE_BITMAP,
                                0,
                                0,
                                loadDiBitmap ? LR_LOADFROMFILE | LR_CREATEDIBSECTION : LR_LOADFROMFILE | LR_DEFAULTCOLOR);

    if (bitmapHandle == FOLIO_INVALID_HANDLE)
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_1 (TXT("LoadImage"),
                                status,
                                fileName);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that will query a bitmap's details.
 *
 * @param [in] bitmapHandle
 * The handle of the bitmap.
 *
 * @param [out] bitmap
 * On return, will hold the bitmap's details, if successful. If this method fails 
 * then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the bitmap's details were successfully obtained.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus QueryBitmapDetails (FolioHandle bitmapHandle,
                                BITMAP&     bitmap)
{
    FolioStatus status = ERR_SUCCESS;

    // Initialise!

    ::ZeroMemory (&(bitmap), sizeof (bitmap));

    // Get the bitmap details.

    if (!::GetObject (bitmapHandle, sizeof (bitmap), &(bitmap)))
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_1 (TXT("GetObject"),
                                status,
                                bitmapHandle);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that will query a bitmap's dimensions.
 *
 * @param [in] bitmapHandle
 * The handle of the bitmap.
 *
 * @param [out] bitmapWidth
 * On return, will hold the bitmap's width, if successful. If this method fails 
 * then this parameter is undefined.
 *
 * @param [out] bitmapHeight
 * On return, will hold the bitmap's height, if successful. If this method fails 
 * then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the bitmap's dimensions were successfully 
 * obtained.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus QueryBitmapDimensions (FolioHandle  bitmapHandle,
                                   Int32&       bitmapWidth,
                                   Int32&       bitmapHeight)
{
    // Query the bitmap's details.
            
    BITMAP  bitmap = {0};   // Initialise!

    FolioStatus status = QueryBitmapDetails (bitmapHandle, bitmap);

    if (status == ERR_SUCCESS)
    {
        bitmapWidth     = bitmap.bmWidth;
        bitmapHeight    = bitmap.bmHeight;
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that will query the details of the specified device-independent bitmap.
 *
 * @param [in] dcHandle
 * The device context handle.
 *
 * @param [in] diBitmapHandle
 * The device-independent bitmap handle.
 *
 * @param [out] diBitmapInfo
 * On return, will hold the device-independent bitmap information, if successful. 
 * If this method fails then this parameter is undefined.
 *
 * @param [out] diBitmapPixels
 * On return, will hold the device-independent bitmap pixels, if successful. If 
 * this method fails then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the bitmap was successfully created.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus QueryDiBitmapDetails (FolioHandle   dcHandle,
                                  FolioHandle   diBitmapHandle,
                                  DIBITMAPINFO& diBitmapInfo,
                                  Byte*&        diBitmapPixels)
{
    FolioStatus status = ERR_SUCCESS;

    // Get the device-independent bitmap information.

    ::ZeroMemory (&(diBitmapInfo), sizeof (diBitmapInfo));  // Initialise!
    diBitmapInfo.bmiHeader.biSize = sizeof (diBitmapInfo.bmiHeader); 

    if (::GetDIBits (static_cast<HDC> (dcHandle), 
                     static_cast<HBITMAP> (diBitmapHandle), 
                     0, // First scan line.
                     0, // Number of scan lines.
                     0, 
                     reinterpret_cast<BITMAPINFO *> (&(diBitmapInfo)), 
                     DIB_RGB_COLORS))
    {
        // Allocate space for the device-independent bitmap's pixels.

        diBitmapPixels = new Byte [diBitmapInfo.bmiHeader.biSizeImage];

        if (!::GetDIBits (static_cast<HDC> (dcHandle), 
                          static_cast<HBITMAP> (diBitmapHandle), 
                          0, 
                          diBitmapInfo.bmiHeader.biHeight, 
                          diBitmapPixels, 
                          reinterpret_cast<BITMAPINFO *> (&(diBitmapInfo)), 
                          DIB_RGB_COLORS))
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_2 (TXT("GetDIBits"),
                                    status,
                                    dcHandle,
                                    diBitmapHandle);

            // Free device-independent bitmap's pixels.

            delete [] diBitmapPixels;
            diBitmapPixels = 0;
        } // Endif.

    } // Endif.

    else
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_2 (TXT("GetDIBits"),
                                status,
                                dcHandle,
                                diBitmapHandle);
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Function that will obtain the colour table index of a specified colour in a 
 * device-independent bitmap.
 *
 * @param [in] dcHandle
 * The device context handle.
 *
 * @param [in] bitmapHandle
 * The handle of the bitmap.
 *
 * @param [in] colourRef
 * The colour.
 *
 * @param [out] colourTableIndex
 * The index of the colour within the colour table. FOLIO_INVALID_INDEX if the 
 * colour is not in the colour table.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the colour table index was obtained successfully.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus QueryColourTableIndexInDiBitmap (FolioHandle        dcHandle,
                                             FolioHandle        bitmapHandle,
                                             const COLORREF&    colourRef,
                                             UInt32&            colourTableIndex)
{
    colourTableIndex = FOLIO_INVALID_INDEX; // Initialise!

    // Select the bitmap into the DC.
        
    FolioHandle oldBitmapHandle = FOLIO_INVALID_HANDLE; // Initialise!

    FolioStatus status = SelectObjectIntoDC (dcHandle, bitmapHandle, &(oldBitmapHandle));

    if (status == ERR_SUCCESS)
    {  
        // Get the colour table.

        RGBQUAD rgbColors [256] = {0};  // Initialise!

        UInt32  numColours = ::GetDIBColorTable (static_cast<HDC> (dcHandle), 
                                                 0, 
                                                 sizeof (rgbColors) / sizeof (RGBQUAD), 
                                                 rgbColors);

        if (numColours)
        {
            // Find the colour in the colour table.

            for (UInt32 colourIndex = 0; colourIndex < numColours; ++colourIndex)
            {
                COLORREF    colourTableRef = RGB(rgbColors [colourIndex].rgbRed, 
                                                 rgbColors [colourIndex].rgbGreen, 
                                                 rgbColors [colourIndex].rgbBlue);

                if (colourTableRef == colourRef)
                {
                    colourTableIndex = colourIndex;

                    break;  // Get-outta-here!
                } // Endif.

            } // Endfor.

        } // Endif.
        
        // Reselect the old bitmap into the DC.
        
        SelectObjectIntoDC (dcHandle, oldBitmapHandle);  
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that will obtain the colour of a specified colour table index in a 
 * device-independent bitmap.
 *
 * @param [in] dcHandle
 * The device context handle.
 *
 * @param [in] bitmapHandle
 * The handle of the bitmap.
 *
 * @param [in] colourTableIndex
 * The index of the colour within the colour table.
 *
 * @param [out] colourRef
 * The colour.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the colour was obtained successfully.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus QueryColourInDiBitmap (FolioHandle  dcHandle,
                                   FolioHandle  bitmapHandle,
                                   UInt32       colourTableIndex,
                                   COLORREF&    colourRef)
{
    colourRef = 0;   // Initialise!

    // Select the bitmap into the DC.
        
    FolioHandle oldBitmapHandle = FOLIO_INVALID_HANDLE; // Initialise!

    FolioStatus status = SelectObjectIntoDC (dcHandle, bitmapHandle, &(oldBitmapHandle));

    if (status == ERR_SUCCESS)
    {  
        // Get the colour table.

        RGBQUAD rgbColors [256] = {0};  // Initialise!

        UInt32  numColours = ::GetDIBColorTable (static_cast<HDC> (dcHandle), 
                                                 0, 
                                                 sizeof (rgbColors) / sizeof (RGBQUAD), 
                                                 rgbColors);

        if (numColours && (colourTableIndex < numColours))
        {
            // Find the colour in the colour table.

            colourRef = RGB(rgbColors [colourTableIndex].rgbRed, 
                            rgbColors [colourTableIndex].rgbGreen, 
                            rgbColors [colourTableIndex].rgbBlue);
        } // Endif.

        else
        {
            status = ERR_INVALID_PARAM3;
        } // Endelse.

        // Reselect the old bitmap into the DC.
        
        SelectObjectIntoDC (dcHandle, oldBitmapHandle);  
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that will change a colour in a device-independent bitmap.
 *
 * @param [in] dcHandle
 * The device context handle.
 *
 * @param [in] bitmapHandle
 * The handle of the bitmap.
 *
 * @param [in] colourTableIndex
 * The index of the changed colour within the colour table.
 *
 * @param [in] newColourRef
 * The new colour.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the bitmap colour was changed successfully.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus ChangeColourInDiBitmap (FolioHandle     dcHandle,
                                    FolioHandle     bitmapHandle,
                                    UInt32          colourTableIndex,
                                    const COLORREF& newColourRef)
{
    // Select the bitmap into the DC.
        
    FolioHandle oldBitmapHandle = FOLIO_INVALID_HANDLE; // Initialise!

    FolioStatus status = SelectObjectIntoDC (dcHandle, bitmapHandle, &(oldBitmapHandle));

    if (status == ERR_SUCCESS)
    {  
        // Get the colour table.

        RGBQUAD rgbColors [256] = {0};  // Initialise!

        UInt32  numColours = ::GetDIBColorTable (static_cast<HDC> (dcHandle), 
                                                 0,
                                                 sizeof (rgbColors) / sizeof (RGBQUAD), 
                                                 rgbColors);

        if (numColours && (colourTableIndex < numColours))
        {
            // Replace the old colour with the new colour.

            rgbColors [colourTableIndex].rgbRed   = GetRValue (newColourRef);
            rgbColors [colourTableIndex].rgbGreen = GetGValue (newColourRef);
            rgbColors [colourTableIndex].rgbBlue  = GetBValue (newColourRef);

            // Set the colour table.

            if (!::SetDIBColorTable (static_cast<HDC> (dcHandle), 
                                     0, // Start index.
                                     numColours, 
                                     rgbColors))
            {
                // Build and log an error.

                status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

                FOLIO_LOG_CALL_ERROR_1 (TXT("SetDIBColorTable"),
                                        status,
                                        bitmapHandle);
            } // Endif.

        } // Endif.

        else
        {
            status = ERR_INVALID_PARAM3;
        } // Endelse.
        
        // Reselect the old bitmap into the DC.
        
        SelectObjectIntoDC (dcHandle, oldBitmapHandle);  
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that will change a colour in a device-independent bitmap.
 *
 * @param [in] dcHandle
 * The device context handle.
 *
 * @param [in] bitmapHandle
 * The handle of the bitmap.
 *
 * @param [in] colourRef
 * The colour.
 *
 * @param [in] newColourRef
 * The new colour.
 *
 * @param [out] colourTableIndex
 * The index of the colour within the colour table. FOLIO_INVALID_INDEX if the 
 * colour is not in the colour table.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the bitmap colour was changed successfully.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus ChangeColourInDiBitmap (FolioHandle     dcHandle,
                                    FolioHandle     bitmapHandle,
                                    const COLORREF& colourRef,
                                    const COLORREF& newColourRef,
                                    UInt32&         colourTableIndex)
{
    colourTableIndex = FOLIO_INVALID_INDEX; // Initialise!

    // Select the bitmap into the DC.
        
    FolioHandle oldBitmapHandle = FOLIO_INVALID_HANDLE; // Initialise!

    FolioStatus status = SelectObjectIntoDC (dcHandle, bitmapHandle, &(oldBitmapHandle));

    if (status == ERR_SUCCESS)
    {  
        // Get the colour table.

        RGBQUAD rgbColors [256] = {0};  // Initialise!

        UInt32  numColours = ::GetDIBColorTable (static_cast<HDC> (dcHandle), 
                                                 0,
                                                 sizeof (rgbColors) / sizeof (RGBQUAD), 
                                                 rgbColors);

        if (numColours)
        {
            // Find the colour in the colour table.

            for (UInt32 colourIndex = 0; colourIndex < numColours; ++colourIndex)
            {
                COLORREF    colourTableRef = RGB(rgbColors [colourIndex].rgbRed, 
                                                 rgbColors [colourIndex].rgbGreen, 
                                                 rgbColors [colourIndex].rgbBlue);

                if (colourTableRef == colourRef)
                {
                    colourTableIndex = colourIndex;

                    // Is the new colour different to the old colour?

                    if (newColourRef != colourRef)
                    {
                        // Yes. Replace the old colour with the new colour.

                        rgbColors [colourTableIndex].rgbRed   = GetRValue (newColourRef);
                        rgbColors [colourTableIndex].rgbGreen = GetGValue (newColourRef);
                        rgbColors [colourTableIndex].rgbBlue  = GetBValue (newColourRef);

                        // Set the colour table.

                        if (!::SetDIBColorTable (static_cast<HDC> (dcHandle), 
                                                 0, // Start index.
                                                 numColours, 
                                                 rgbColors))
                        {
                            // Build and log an error.

                            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

                            FOLIO_LOG_CALL_ERROR_1 (TXT("SetDIBColorTable"),
                                                    status,
                                                    bitmapHandle);
                        } // Endif.

                    } // Endif.

                    break;  // Get-outta-here!
                } // Endif.

            } // Endfor.

        } // Endif.
        
        // Reselect the old bitmap into the DC.
        
        SelectObjectIntoDC (dcHandle, oldBitmapHandle);  
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that will change a colour in a bitmap.
 *
 * @param [in] dcHandle
 * The device context handle.
 *
 * @param [in] bitmapHandle
 * The handle of the bitmap.
 *
 * @param [in] colourRef
 * The colour.
 *
 * @param [in] newColourRef
 * The new colour.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the bitmap colour was changed successfully.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus ChangeColourInBitmap (FolioHandle     dcHandle,
                                  FolioHandle     bitmapHandle,
                                  const COLORREF& colourRef,
                                  const COLORREF& newColourRef)
{
    // Query the source bitmap's dimensions.

    BITMAP  bitmap = {0};   // Initialise!
    FolioStatus status = QueryBitmapDetails (bitmapHandle, bitmap);

    if (status == ERR_SUCCESS)
    {
        // Replace the colour with the new colour.
        
        for (int row = 0; row < bitmap.bmHeight; row++)
        {
            for (int column = 0; column < bitmap.bmWidth; column++)
            {
                if (::GetPixel (static_cast<HDC> (dcHandle), column, row) == colourRef)
                {
                    ::SetPixel (static_cast<HDC> (dcHandle), column, row, newColourRef);
                } // Endif.

            } // Endfor.
        
        } // Endfor.
        
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that will copy a bitmap from a source device context to a 
 * destination device context.
 *
 * @param [in] destinationDcHandle
 * The device context handle of the destination.
 *
 * @param [in] destinationX
 * The X position of the destination.
 *
 * @param [in] destinationY
 * The Y position of the destination.
 *
 * @param [in] destinationWidth
 * The width of the destination.
 *
 * @param [in] destinationHeight
 * The height of the destination.
 *
 * @param [in] sourceDcHandle
 * The device context handle of the source.
 *
 * @param [in] sourceX
 * The X position of the source.
 *
 * @param [in] sourceY
 * The Y position of the source.
 *
 * @param [in] rasterOperation
 * The raster operation to use when copying the bitmap.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the bitmap was successfully copied.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus CopyBitmap (FolioHandle destinationDcHandle,
                        Int32       destinationX,
                        Int32       destinationY,
                        Int32       destinationWidth,
                        Int32       destinationHeight,
                        FolioHandle sourceDcHandle,
                        Int32       sourceX,
                        Int32       sourceY,
                        UInt32      rasterOperation)
{
    FolioStatus status = ERR_SUCCESS;

    // BitBlt the bitmap.

    if (!::BitBlt (reinterpret_cast<HDC> (destinationDcHandle),
                   destinationX,
                   destinationY,
                   destinationWidth,
                   destinationHeight,
                   reinterpret_cast<HDC> (sourceDcHandle),
                   sourceX,
                   sourceY,
                   rasterOperation))
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_9 (TXT("BitBlt"),
                                status,
                                destinationDcHandle,
                                destinationX,
                                destinationY,
                                destinationWidth,
                                destinationHeight,
                                sourceDcHandle,
                                sourceX,
                                sourceY,
                                rasterOperation);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that will scale a bitmap from a source device context to a 
 * destination device context.
 *
 * @param [in] destinationDcHandle
 * The device context handle of the destination.
 *
 * @param [in] destinationX
 * The X position of the destination.
 *
 * @param [in] destinationY
 * The Y position of the destination.
 *
 * @param [in] destinationWidth
 * The width of the destination.
 *
 * @param [in] destinationHeight
 * The height of the destination.
 *
 * @param [in] sourceDcHandle
 * The device context handle of the source.
 *
 * @param [in] sourceX
 * The X position of the source.
 *
 * @param [in] sourceY
 * The Y position of the source.
 *
 * @param [in] sourceWidth
 * The width of the source.
 *
 * @param [in] sourceHeight
 * The height of the source.
 *
 * @param [in] rasterOperation
 * The raster operation to use when scaleing the bitmap.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the bitmap was successfully copied.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus ScaleBitmap (FolioHandle    destinationDcHandle,
                         Int32          destinationX,
                         Int32          destinationY,
                         Int32          destinationWidth,
                         Int32          destinationHeight,
                         FolioHandle    sourceDcHandle,
                         Int32          sourceX,
                         Int32          sourceY,
                         Int32          sourceWidth,
                         Int32          sourceHeight,
                         UInt32         rasterOperation)
{
    FolioStatus status = ERR_SUCCESS;

    // Stretch the bitmap.

    if (!::StretchBlt (reinterpret_cast<HDC> (destinationDcHandle),
                       destinationX,
                       destinationY,
                       destinationWidth,
                       destinationHeight,
                       reinterpret_cast<HDC> (sourceDcHandle),
                       sourceX,
                       sourceY,
                       sourceWidth,
                       sourceHeight,
                       rasterOperation))
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_11 (TXT("StretchBlt"),
                                 status,
                                 destinationDcHandle,
                                 destinationX,
                                 destinationY,
                                 destinationWidth,
                                 destinationHeight,
                                 sourceDcHandle,
                                 sourceX,
                                 sourceY,
                                 sourceWidth,
                                 sourceHeight,
                                 rasterOperation);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that will destroy a bitmap.
 *
 * @param [in] bitmapHandle
 * The bitmap handle of the bitmap.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the bitmap was successfully destroyed.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus DestroyBitmap (FolioHandle bitmapHandle)
{
    return (DestroyObject (bitmapHandle));
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
