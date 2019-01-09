// "Home-made" includes.
#include    <Trace.h>
#include    "Gdi.h"

namespace Folio
{

namespace Core
{

namespace Util
{

namespace Gdi
{

/**
 * Function that will create a memory device context compatible with the 
 * specified device context.
 *
 * @param [in] dcHandle
 * The device context handle.
 *
 * @param [out] memoryDcHandle
 * On return, will hold the memory device context handle, if successful. If 
 * this method fails then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the memory device context was successfully created.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus CreateCompatibleMemoryDC (FolioHandle   dcHandle,
                                      FolioHandle&  memoryDcHandle)
{
    FolioStatus status = ERR_SUCCESS;

    // Create a compatible device context.

    memoryDcHandle = ::CreateCompatibleDC (reinterpret_cast<HDC> (dcHandle));

    if (memoryDcHandle == FOLIO_INVALID_HANDLE)
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_1 (TXT("CreateCompatibleDC"),
                                status,
                                dcHandle);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that will destroy a memory device context.
 *
 * @param [in] memoryDcHandle
 * The memory device context handle.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the memory device context was successfully 
 *     destroyed.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus DestroyMemoryDC (FolioHandle memoryDcHandle)
{
    FolioStatus status = ERR_SUCCESS;

    // Delete the device context.

    if (!::DeleteDC (reinterpret_cast<HDC> (memoryDcHandle)))
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_1 (TXT("DeleteDC"),
                                status,
                                memoryDcHandle);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that will select an object into the specified device context.
 *
 * @param [in] dcHandle
 * The device context handle.
 *
 * @param [in] newObjectHandle
 * The new object handle.
 *
 * @param [out] oldObjectHandle
 * On return, will hold the old object handle, if successful. If this method fails 
 * then this parameter is undefined. May be 0.

 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the object was successfully selected to the device 
 *     context.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus SelectObjectIntoDC (FolioHandle     dcHandle,
                                FolioHandle     newObjectHandle,
                                FolioHandle*    oldObjectHandle)
{
    FolioStatus status = ERR_SUCCESS;

    // Select the object into the device context.

    HGDIOBJ objectHandle = ::SelectObject (reinterpret_cast<HDC> (dcHandle),
                                           newObjectHandle);

    if (objectHandle == FOLIO_INVALID_HANDLE)
    {
        if (::GetLastError () != ERROR_SUCCESS)
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_2 (TXT("SelectObject"),
                                    status,
                                    dcHandle,
                                    newObjectHandle);
       } // Endif.

    } // Endif.

    else
    if (oldObjectHandle)
    {
        *oldObjectHandle = objectHandle;
    } // Endelse.


    return (status);
} // Endproc.


/**
 * Function that will select a clipping region into the specified device 
 * context.
 *
 * @param [in] dcHandle
 * The device context handle.
 *
 * @param [in] clippingRegionHandle
 * The clipping region handle.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the clipping region was successfully selected to 
 *     the device context.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus SelectClippingRegion (FolioHandle   dcHandle,
                                  FolioHandle   clippingRegionHandle)
{
    FolioStatus status = ERR_SUCCESS;

    if (::SelectClipRgn (reinterpret_cast<HDC> (dcHandle),
                         reinterpret_cast<HRGN> (clippingRegionHandle)) == ERROR)
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_2 (TXT("SelectClipRgn"),
                                status,
                                dcHandle,
                                clippingRegionHandle);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that will destroy a clipping region.
 *
 * @param [in] clippingRegionHandle
 * The clipping region handle.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the clipping region was successfully destroyed.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus DestroyClippingRegion (FolioHandle clippingRegionHandle)
{
    FolioStatus status = ERR_SUCCESS;

    // Delete the object.

    if (!::DeleteObject (clippingRegionHandle))
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_1 (TXT("DeleteObject"),
                                status,
                                clippingRegionHandle);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that is used to clear a specified rectangle to a specified colour.
 *
 * @param [in] dcHandle
 * The device context handle.
 *
 * @param [in] x
 * The x position of the rectangle.
 *
 * @param [in] y
 * The y position of the rectangle.
 *
 * @param [in] width
 * The width of the rectangle.
 *
 * @param [in] height
 * The height of the rectangle.
 *
 * @param [in] colour
 * The colour of the rectangle.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus ClearRectangle (FolioHandle dcHandle,
                            Int32       x,
                            Int32       y,
                            Int32       width,
                            Int32       height,
                            COLORREF    colour)
{
    FolioStatus status = ERR_SUCCESS;

    // Build the pen's brush.
    
    LOGBRUSH    logicalBrush = {0}; // Initialise! 
    logicalBrush.lbStyle    = BS_SOLID; 
    logicalBrush.lbColor    = colour; 
    logicalBrush.lbHatch    = 0; 

    // Create a solid pen.

    HPEN    penHandle = ::ExtCreatePen (PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_SQUARE, 
                                        1,
                                        &(logicalBrush),
                                        0,
                                        NULL);

    if (penHandle)
    {
        // Select the pen into the DC.

        FolioHandle oldPenObjectHandle = FOLIO_UNDEFINED;

        status = SelectObjectIntoDC (dcHandle,
                                     penHandle,
                                     &(oldPenObjectHandle));

        if (status == ERR_SUCCESS)
        {
            // Create a solid brush.

            HBRUSH  brushHandle = ::CreateSolidBrush (colour);

            // Select the brush into the DC.

            FolioHandle oldBrushObjectHandle = FOLIO_UNDEFINED;

            status = SelectObjectIntoDC (dcHandle,
                                         brushHandle,
                                         &(oldBrushObjectHandle));

            if (status == ERR_SUCCESS)
            {
                // Draw the rectangle.

                if (!::Rectangle (static_cast<HDC> (dcHandle), x, y, width, height))
                {
                    // Build and log an error.

                    status = FOLIO_MAKE_GDI_ERROR(::GetLastError ());

                    FOLIO_LOG_CALL_ERROR_5 (TXT("Rectangle"),
                                            status,
                                            x,
                                            y,
                                            width,
                                            height,
                                            colour);
                } // Endif.

                // Reselect the old brush into the DC.
        
                SelectObjectIntoDC (dcHandle, oldBrushObjectHandle);  
            } // Endif.

            // Reselect the old pen into the DC.
        
            SelectObjectIntoDC (dcHandle, oldPenObjectHandle);  
        } // Endif.
    
    } // Endif.

    else
    {
        // Build and log an error.

        status = FOLIO_MAKE_GDI_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR (TXT("ExtCreatePen"),
                              status);
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Function that is used to draw a specified line of a specified colour.
 *
 * @param [in] dcHandle
 * The device context handle.
 *
 * @param [in] startX
 * The start X position of the line.
 *
 * @param [in] startY
 * The start Y position of the line.
 *
 * @param [in] endX
 * The end X position of the line.
 *
 * @param [in] endY
 * The end Y position of the line.
 *
 * @param [in] width
 * The width of the line.
 *
 * @param [in] colour
 * The colour of the rectangle.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus DrawLine (FolioHandle dcHandle,
                      Int32       startX,
                      Int32       startY,
                      Int32       endX,
                      Int32       endY,
                      Int32       width,
                      COLORREF    colour)
{
    FolioStatus status = ERR_SUCCESS;

    // Build the pen's brush.
    
    LOGBRUSH    logicalBrush = {0}; // Initialise! 
    logicalBrush.lbStyle    = BS_SOLID; 
    logicalBrush.lbColor    = colour; 
    logicalBrush.lbHatch    = 0; 

    // Create a solid pen.

    HPEN    penHandle = ::ExtCreatePen (PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_SQUARE, 
                                        width,
                                        &(logicalBrush),
                                        0,
                                        NULL);

    if (penHandle)
    {
        // Select the pen into the DC.

        FolioHandle oldPenObjectHandle = FOLIO_UNDEFINED;

        status = SelectObjectIntoDC (dcHandle,
                                     penHandle,
                                     &(oldPenObjectHandle));

        if (status == ERR_SUCCESS)
        {
            // Draw the line.

            if (::MoveToEx (static_cast<HDC> (dcHandle), startX, startY, NULL))
            {
                if (!::LineTo (static_cast<HDC> (dcHandle), endX, endY))
                {
                    // Build and log an error.

                    status = FOLIO_MAKE_GDI_ERROR(::GetLastError ());

                    FOLIO_LOG_CALL_ERROR_3 (TXT("LineTo"),
                                            status,
                                            endX,
                                            endY,
                                            colour);
                } // Endif.

            } // Endif.

            else
            {
                // Build and log an error.

                status = FOLIO_MAKE_GDI_ERROR(::GetLastError ());

                FOLIO_LOG_CALL_ERROR_3 (TXT("MoveToEx"),
                                        status,
                                        startX,
                                        startY,
                                        colour);
            } // Endelse.

            // Reselect the old pen into the DC.
        
            SelectObjectIntoDC (dcHandle, oldPenObjectHandle);  
        } // Endif.

    } // Endif.

    else
    {
        // Build and log an error.

        status = FOLIO_MAKE_GDI_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR (TXT("ExtCreatePen"),
                              status);
    } // Endelse.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
