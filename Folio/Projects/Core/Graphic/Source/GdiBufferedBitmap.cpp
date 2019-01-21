// "Home-made" includes.
#include    <Util.h>
#include    "..\Include\Gdi.h"
#include    "GdiBufferedBitmap.h"

namespace Folio
{

namespace Core
{

namespace Graphic
{

using   namespace   Gdiplus;
using   namespace   Folio::Core::Util::Gdi;

/**
 * The default class constructor.
 */
GdiBufferedBitmap::GdiBufferedBitmap ()
:   m_dcHandle(FOLIO_INVALID_HANDLE),
    m_memoryDcHandle(FOLIO_INVALID_HANDLE),
    m_bitmapHandle(FOLIO_INVALID_HANDLE),
    m_oldBitmapHandle(FOLIO_INVALID_HANDLE)
{
} // Endproc.


/**
 * The class destructor.
 */
GdiBufferedBitmap::~GdiBufferedBitmap ()
{
    // Destroy the buffered bitmap.

    Destroy ();
} // Endproc.


/**
 * Method that is used to create the buffered bitmap.
 *
 * @param [in] dcHandle
 * The device context handle.
 *
 * @param [in] bufferedBitmapRect
 * The rect of the buffered bitmap.
 *
 * @param [in] drawToRequired
 * Indicates if it is required to draw into the buffered bitmap.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a buffered bitmap has been previously 
 *     created using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiBufferedBitmap::Create (FolioHandle          dcHandle,
                                       const Gdiplus::Rect& bufferedBitmapRect,
                                       bool                 drawToRequired)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a buffered bitmap already?

    if (IsCreated ())
    {
        // Yes.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // No. Create a display compatible bitmap.

        status = CreateCompatibleBitmap (dcHandle,
                                         bufferedBitmapRect.Width,
                                         bufferedBitmapRect.Height,
                                         m_bitmapHandle);

        if (status == ERR_SUCCESS)
        {
            // Initialise the bitmap.

            status = InitialiseBitmap (dcHandle, bufferedBitmapRect, drawToRequired);
        } // Endif.

    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to get the rect of the buffered bitmap.
 *
 * @return
 * The rect of the buffered bitmap.
 */
Gdiplus::Rect   GdiBufferedBitmap::GetBufferedBitmapRect () const
{
    return (m_bufferedBitmapRect);
} // Endproc.


/**
 * Method that is used to get the X left position of the buffered bitmap.
 *
 * @return
 * The X left position of the buffered bitmap.
 */
Int32   GdiBufferedBitmap::GetBufferedBitmapXLeft () const
{
    return (m_bufferedBitmapRect.X);
} // Endproc.


/**
 * Method that is used to get the Y top position of the buffered bitmap.
 *
 * @return
 * The Y top position of the buffered bitmap.
 */
Int32   GdiBufferedBitmap::GetBufferedBitmapYTop () const
{
    return (m_bufferedBitmapRect.Y);
} // Endproc.


/**
 * Method that is used to get the width of the buffered bitmap.
 *
 * @return
 * The width of the buffered bitmap.
 */
Int32   GdiBufferedBitmap::GetBufferedBitmapWidth () const
{
    return (m_bufferedBitmapRect.Width);
} // Endproc.


/**
 * Method that is used to get the height of the buffered bitmap.
 *
 * @return
 * The height of the buffered bitmap.
 */
Int32   GdiBufferedBitmap::GetBufferedBitmapHeight () const
{
    return (m_bufferedBitmapRect.Height);
} // Endproc.


/**
 * Method that is used to get the handle of the buffered bitmap.
 *
 * @return
 * The handle of the buffered bitmap.
 */
FolioHandle GdiBufferedBitmap::GetBufferedBitmapHandle () const
{
    return (m_bitmapHandle);
} // Endproc.


/**
 * Method that is used to get the device context handle of the buffered bitmap.
 *
 * @return
 * The device context handle of the buffered bitmap.
 */
FolioHandle GdiBufferedBitmap::GetBufferedBitmapDcHandle () const
{
    // The memory device context is the device context handle of the buffered 
    // bitmap.

    return (m_memoryDcHandle);
} // Endproc.


/**
 * Method that is used to get the buffered bitmap graphics object.
 *
 * @return
 * The buffered bitmap graphics object.
 */
Gdiplus::Graphics*  GdiBufferedBitmap::GetBufferedBitmapGraphics () const
{
    return (m_graphics.get ());
} // Endproc.


/**
 * Method that is used to buffer the buffered bitmap from the specified position.
 *
 * @param [in, out] graphics
 * The graphics object to draw to.
 *
 * @param [in] sourcePoint
 * The position where the buffered bitmap is to be buffered from.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a buffered bitmap has not been created for 
 *     this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiBufferedBitmap::Buffer (Gdiplus::Graphics&       graphics,
                                       const Gdiplus::Point&    sourcePoint)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a buffered bitmap?

    if (IsCreated ())
    {
        // Yes. Get the graphics device context.
     
        HDC graphicsDcHandle = graphics.GetHDC ();
     
        // Copy the bitmap from the graphics device context at the source 
        // position to the memory device context.

        status = CopyBitmap (m_memoryDcHandle,
                             0,
                             0,
                             m_bufferedBitmapRect.Width,
                             m_bufferedBitmapRect.Height,
                             graphicsDcHandle,
                             sourcePoint.X,
                             sourcePoint.Y,
                             SRCCOPY);

        // Release the graphics device context.
 
        graphics.ReleaseHDC (graphicsDcHandle);

        if (status == ERR_SUCCESS)
        {
            // Update the buffered bitmap rect position.

            m_bufferedBitmapRect.X = sourcePoint.X;
            m_bufferedBitmapRect.Y = sourcePoint.Y;
        } // Endif.

    } // Endif.

    else
    {
        // No.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to buffer the buffered bitmap with the specified rect.
 *
 * @param [in, out] graphics
 * The graphics object to draw to.
 *
 * @param [in] bufferedBitmapRect
 * The rect of the buffered bitmap.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a buffered bitmap has not been created for 
 *     this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiBufferedBitmap::Buffer (Gdiplus::Graphics&   graphics,
                                       const Gdiplus::Rect& bufferedBitmapRect)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a buffered bitmap?

    if (IsCreated ())
    {
        // Yes. Select the old bitmap into the memory device context.

        status = SelectObjectIntoDC (m_memoryDcHandle, m_oldBitmapHandle);

        if (status == ERR_SUCCESS)
        {
            // Destroy the buffered bitmap.

            status = DestroyBitmap (m_bitmapHandle);

            if (status == ERR_SUCCESS)
            {
                // Create a display compatible bitmap.

                status = CreateCompatibleBitmap (m_dcHandle,
                                                 bufferedBitmapRect.Width,
                                                 bufferedBitmapRect.Height,
                                                 m_bitmapHandle);

                if (status == ERR_SUCCESS)
                {
                    // Select the bitmap into the memory device context.

                    status = SelectObjectIntoDC (m_memoryDcHandle, m_bitmapHandle, &(m_oldBitmapHandle));

                    if (status == ERR_SUCCESS)
                    {
                        // Note the buffered bitmap rect.

                        m_bufferedBitmapRect = bufferedBitmapRect;
                
                        HDC graphicsDcHandle = graphics.GetHDC ();
                 
                        // Copy the bitmap from the graphics device context to the memory 
                        // device context.
            
                        status = CopyBitmap (m_memoryDcHandle,
                                             0,
                                             0,
                                             m_bufferedBitmapRect.Width,
                                             m_bufferedBitmapRect.Height,
                                             graphicsDcHandle,
                                             m_bufferedBitmapRect.X,
                                             m_bufferedBitmapRect.Y,
                                             SRCCOPY);
            
                        // Release the graphics device context.
             
                        graphics.ReleaseHDC (graphicsDcHandle);
                    } // Endif.

                } // Endif.
        
            } // Endif.

        } // Endif.

    } // Endif.

    else
    {
        // No.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to clear the buffered bitmap.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a buffered bitmap has not been created for 
 *     this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiBufferedBitmap::Clear (const Gdiplus::Color& clearColour)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a buffered bitmap?

    if (IsCreated ())
    {
        // Yes. Clear the buffered bitmap.

        status = ClearRectangle (m_memoryDcHandle,
                                 0,
                                 0,
                                 m_bufferedBitmapRect.Width,
                                 m_bufferedBitmapRect.Height,
                                 clearColour.ToCOLORREF ());
    } // Endif.

    else
    {
        // No.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to draw the buffered bitmap at the specified position.
 *
 * @param [in, out] graphics
 * The graphics object to draw to.
 *
 * @param [in] destinationPoint
 * The position where the buffered bitmap is to be drawn to.
 *
 * @param [out] rects
 * On return, will hold the rects of the buffered bitmap, if successful. If this 
 * method fails then this parameter is undefined. May be zero if not required.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a buffered bitmap has not been created for 
 *     this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiBufferedBitmap::Draw (Gdiplus::Graphics&     graphics,
                                     const Gdiplus::Point&  destinationPoint,
                                     RectList*              rects)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a buffered bitmap?

    if (IsCreated ())
    {
        // Yes. No. Get the graphics device context.
     
        HDC graphicsDcHandle = graphics.GetHDC ();
     
        // Copy the bitmap from the memory device context to the graphics 
        // device context at the destination position.

        status = CopyBitmap (graphicsDcHandle,
                             destinationPoint.X,
                             destinationPoint.Y,
                             m_bufferedBitmapRect.Width,
                             m_bufferedBitmapRect.Height,
                             m_memoryDcHandle,
                             0,
                             0,
                             SRCCOPY);

        // Release the graphics device context.
 
        graphics.ReleaseHDC (graphicsDcHandle);

        if (status == ERR_SUCCESS)
        {
            // Update the buffered bitmap rect position.

            m_bufferedBitmapRect.X = destinationPoint.X;
            m_bufferedBitmapRect.Y = destinationPoint.Y;

            // Does the caller want to know the rects?

            if (rects)
            {
                // Yes.
                
                rects->push_back (m_bufferedBitmapRect);
            } // Endif.

        } // Endif.

    } // Endif.
    
    else
    {
        // No.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to set the top-left hand corner of the buffered bitmap's 
 * screen point.
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
FolioStatus GdiBufferedBitmap::SetScreenTopLeft (Int32  screenXLeft,
                                                 Int32  screenYTop)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a buffered bitmap?

    if (IsCreated ())
    {
        // Yes. Set the screen rect.

        SetScreenRect (Gdiplus::Rect(screenXLeft, 
                                     screenYTop,
                                     m_bufferedBitmapRect.Width,
                                     m_bufferedBitmapRect.Height));
    } // Endif.

    else
    {
        // No.

        status = ERR_NOT_INITIALISED;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to draw the buffered bitmap.
 *
 * @param [in, out] graphics
 * The graphics object to draw to.
 *
 * @param [out] rects
 * On return, will hold the rects of the buffered bitmap, if successful. If this 
 * method fails then this parameter is undefined. May be zero if not required.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a buffered bitmap has not been created for 
 *     this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiBufferedBitmap::Draw (Gdiplus::Graphics& graphics,
                                     RectList*          rects)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a buffered bitmap?

    if (IsCreated ())
    {
        // Yes. Get the graphics device context.
         
        HDC graphicsDcHandle = graphics.GetHDC ();

        // Copy the bitmap from the memory device context to the graphics 
        // device context.
       
        status = CopyBitmap (graphicsDcHandle,
                             m_bufferedBitmapRect.X,
                             m_bufferedBitmapRect.Y,
                             m_bufferedBitmapRect.Width,
                             m_bufferedBitmapRect.Height,
                             m_memoryDcHandle,
                             0,
                             0,
                             SRCCOPY);
       
        // Release the graphics device context.
    
        graphics.ReleaseHDC (graphicsDcHandle);
    
        // Does the caller want to know the rects?
       
        if (rects && (status == ERR_SUCCESS))
        {
            // Yes.
            
            rects->push_back (m_bufferedBitmapRect);
        } // Endif.

    } // Endif.

    else
    {
        // No.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to initialise the buffered bitmap.
 *
 * @param [in] dcHandle
 * The device context handle.
 *
 * @param [in] bufferedBitmapRect
 * The rect of the buffered bitmap.
 *
 * @param [in] drawToRequired
 * Indicates if it is required to draw into the buffered bitmap.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiBufferedBitmap::InitialiseBitmap (FolioHandle            dcHandle,
                                                 const Gdiplus::Rect&   bufferedBitmapRect,
                                                 bool                   drawToRequired)
{
    // Create a display compatible memory DC.

    FolioStatus status = CreateCompatibleMemoryDC (dcHandle, m_memoryDcHandle);

    if (status == ERR_SUCCESS)
    {
        // Select the bitmap into the memory device context.

        status = SelectObjectIntoDC (m_memoryDcHandle, m_bitmapHandle, &(m_oldBitmapHandle));

        if (status == ERR_SUCCESS)
        {          
            // Set the bitmap's attributes.

            m_dcHandle              = dcHandle;
            m_bufferedBitmapRect    = bufferedBitmapRect;

            // Copy the bitmap from the device context to the memory device context.
            
            status = CopyBitmap (m_memoryDcHandle,
                                 0,
                                 0,
                                 m_bufferedBitmapRect.Width,
                                 m_bufferedBitmapRect.Height,
                                 m_dcHandle,
                                 m_bufferedBitmapRect.X,
                                 m_bufferedBitmapRect.Y,
                                 SRCCOPY);

            // If the buffered bitmap is to be drawn to then we must create its graphics object.

            if (drawToRequired && (status == ERR_SUCCESS))
            {
                // Create the graphics object.

                status = CreateGraphics ();
            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that is used to destroy the buffered bitmap.
 */
void    GdiBufferedBitmap::Destroy ()
{
    // Make sure that our graphics object is destroyed before any memory device 
    // context.

    DestroyGraphics ();

    // Select the old bitmap in the memory device context?

    if (m_oldBitmapHandle != FOLIO_INVALID_HANDLE)
    {
        // Yes.

        SelectObjectIntoDC (m_memoryDcHandle, m_oldBitmapHandle);
    } // Endif.

    // Destroy the memory device context?

    if (m_memoryDcHandle != FOLIO_INVALID_HANDLE)
    {
        // Yes.

        DestroyMemoryDC (m_memoryDcHandle);
    } // Endif.

    // Destroy the bitmap?

    if (m_bitmapHandle != FOLIO_INVALID_HANDLE)
    {
        // Yes.

        DestroyBitmap (m_bitmapHandle);
    } // Endif.

} // Endproc.


/**
 * Method that is used to determine if the buffered bitmap has been created.
 *
 * @return
 * <b>true</b> if the buffered bitmap has been created, <b>false</b> otherwise.
 */
bool    GdiBufferedBitmap::IsCreated () const
{
    // If the bitmap handle is valid, then the bitmap has been created.

    return (m_bitmapHandle != FOLIO_INVALID_HANDLE);
} // Endproc.


/**
 * Method that is used to create the graphics object.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiBufferedBitmap::CreateGraphics ()
{
    // Create the graphics object.

    m_graphics.reset (new Graphics (reinterpret_cast<HDC> (m_memoryDcHandle)));

    // Initialise it!

    return (Gdi::InitializeGraphics (*m_graphics.get ()));
} // Endproc.


/**
 * Method that is used to destroy the graphics object.
 */
void    GdiBufferedBitmap::DestroyGraphics ()
{
    m_graphics.reset ();
} // Endproc.


/**
 * Method that is used to determine if the graphics object has been created.
 *
 * @return
 * <b>true</b> if the graphics object has been created, <b>false</b> otherwise.
 */
bool    GdiBufferedBitmap::IsGraphics () const
{
    return (m_graphics.get () != 0);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
