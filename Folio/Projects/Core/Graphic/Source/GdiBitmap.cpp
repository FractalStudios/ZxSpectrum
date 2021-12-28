// "Home-made" includes.
#include    <Util.h>
#include    "..\Include\Gdi.h"
#include    "..\Include\GdiBitmap.h"

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
GdiBitmap::GdiBitmap ()
:   m_id(FOLIO_UNDEFINED),
    m_isMonochrome(false),
    m_dcHandle(FOLIO_INVALID_HANDLE),
    m_memoryDcHandle(FOLIO_INVALID_HANDLE),
    m_bitmapHandle(FOLIO_INVALID_HANDLE),
    m_oldBitmapHandle(FOLIO_INVALID_HANDLE),
    m_horizontalFlip(false),
    m_verticalFlip(false),
    m_drawingMode(SRCCOPY),
    m_drawingAdjustmentMode(NONE),
    m_drawingWidthAdjustment(0),
    m_drawingHeightAdjustment(0)
{
} // Endproc.


/**
 * The class destructor.
 */
GdiBitmap::~GdiBitmap ()
{
    // Destroy the bitmap.

    Destroy ();
} // Endproc.


/**
 * The class copy constructor.
 */
GdiBitmap::GdiBitmap (const GdiBitmap& rhs)
{
    Create (rhs.GetBitmapDcHandle (), rhs);
} // Endproc.


/**
 * The class assignment operator.
 */
GdiBitmap&  GdiBitmap::operator = (const GdiBitmap& rhs)
{
    if (this != &(rhs))
    {
        Create (rhs.GetBitmapDcHandle (), rhs);
    } // Endif.

    return (*this);
} // Endproc.


/**
 * Method that is used to create the bitmap.
 *
 * @param [in] dcHandle
 * The device context handle.
 *
 * @param [in] bitmapRect
 * The rect of the bitmap.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a bitmap has been previously created using 
 *     this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiBitmap::Create (FolioHandle          dcHandle,
                               const Gdiplus::Rect& bitmapRect)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a bitmap already?

    if (IsCreated ())
    {
        // Yes.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // No. Create a display compatible bitmap.

        status = CreateCompatibleBitmap (dcHandle,
                                         bitmapRect.Width,
                                         bitmapRect.Height,
                                         m_bitmapHandle);

        if (status == ERR_SUCCESS)
        {
            // Add to the handle monitor.

            Folio::Core::Util::g_handleMonitor.AddHandle (m_bitmapHandle,
                                                          FOLIO_UNDEFINED,
                                                          TXT("GdiBitmap::Create::CreateCompatibleBitmap"));

            // Initialise the bitmap.

            status = InitialiseBitmap (dcHandle);
        } // Endif.

    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to create the bitmap.
 *
 * @param [in] dcHandle
 * The device context handle.
 *
 * @param [in] instanceHandle
 * The application instance handle.
 *
 * @param [in] resourceId
 * The resource identifier of the bitmap.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a bitmap has been previously created using 
 *     this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiBitmap::Create (FolioHandle  dcHandle,
                               FolioHandle  instanceHandle,
                               UInt16       resourceId)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a bitmap already?

    if (IsCreated ())
    {
        // Yes.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // No. Load the bitmap.

        status = LoadBitmap (instanceHandle, resourceId, false, m_bitmapHandle);

        if (status == ERR_SUCCESS)
        {
            // Initialise the bitmap.

            status = InitialiseBitmap (dcHandle, resourceId);
        } // Endif.

    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to create the bitmap.
 *
 * @param [in] dcHandle
 * The device context handle.
 *
 * @param [in] fileName
 * The file name of the bitmap.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a bitmap has been previously created using 
 *     this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiBitmap::Create (FolioHandle          dcHandle,
                               const FolioString&   fileName)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a bitmap already?

    if (IsCreated ())
    {
        // Yes.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // No. Load the bitmap.

        status = LoadBitmap (fileName, false, m_bitmapHandle);

        if (status == ERR_SUCCESS)
        {
            // Initialise the bitmap.

            status = InitialiseBitmap (dcHandle);
        } // Endif.

    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to create a bitmap from a GDI bitmap.
 *
 * @param [in] dcHandle
 * The device context handle.
 *
 * @param [in] gdiBitmap
 * The GDI bitmap.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a bitmap has been previously created using 
 *     this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiBitmap::Create (FolioHandle      dcHandle,
                               const GdiBitmap& gdiBitmap)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a bitmap already?

    if (IsCreated ())
    {
        // Yes.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // No. Create a display compatible bitmap.

        status = CreateCompatibleBitmap (dcHandle,
                                         gdiBitmap.GetBitmapWidth (),
                                         gdiBitmap.GetBitmapHeight (),
                                         m_bitmapHandle);

        if (status == ERR_SUCCESS)
        {
            // Add to the handle monitor.

            Folio::Core::Util::g_handleMonitor.AddHandle (m_bitmapHandle,
                                                          gdiBitmap.GetId (),
                                                          TXT("GdiBitmap::Create::CreateCompatibleBitmap"));

            // Initialise the bitmap.

            status = InitialiseBitmap (dcHandle, 
                                       gdiBitmap.GetId (), 
                                       gdiBitmap.IsMonochrome ());

            if (status == ERR_SUCCESS)
            {
                // Copy the bitmap into the memory device context.

                status = CopyBitmap (m_memoryDcHandle,
                                     m_bitmapRect.X,
                                     m_bitmapRect.Y,
                                     m_bitmapRect.Width,
                                     m_bitmapRect.Height,
                                     gdiBitmap.GetBitmapDcHandle (),
                                     0,
                                     0,
                                     SRCCOPY);

                if (status == ERR_SUCCESS)
                {
                    // Note the bitmap's attributes.

                    Clone (gdiBitmap);

                    m_horizontalFlip    = gdiBitmap.IsDrawingHorizontalFlip ();
                    m_verticalFlip      = gdiBitmap.IsDrawingVerticalFlip ();
                    m_drawingMode       = gdiBitmap.GetDrawingMode ();

                    m_drawingAdjustmentMode     = gdiBitmap.GetDrawingAdjustmentMode ();
                    m_drawingWidthAdjustment    = gdiBitmap.GetDrawingWidthAdjustment ();
                    m_drawingHeightAdjustment   = gdiBitmap.GetDrawingHeightAdjustment ();
                } // Endif.
                
            } // Endif.

        } // Endif.

    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to create a monochrome bitmap mask from a GDI bitmap.
 *
 * @param [in] dcHandle
 * The device context handle.
 *
 * @param [in] gdiBitmap
 * The GDI bitmap.
 *
 * @param [in] transparentColour
 * The GDI bitmap's transparent colour (normally it's background colour).
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a bitmap has been previously created using 
 *     this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiBitmap::Create (FolioHandle              dcHandle,
                               const GdiBitmap&         gdiBitmap,
                               const Gdiplus::Color&    transparentColour)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a bitmap already?

    if (IsCreated ())
    {
        // Yes.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // No. Create a monochrome bitmap.

        status = CreateMonochromeBitmap (gdiBitmap.GetBitmapDcHandle (),    // GDI bitmap will already be selected into its DC.
                                         gdiBitmap.GetBitmapHandle (),
                                         transparentColour.ToCOLORREF (),
                                         m_bitmapHandle);

        if (status == ERR_SUCCESS)
        {
            // Add to the handle monitor.

            Folio::Core::Util::g_handleMonitor.AddHandle (m_bitmapHandle,
                                                          gdiBitmap.GetId (),
                                                          TXT("GdiBitmap::Create::CreateMonochromeBitmap"));

            // Initialise the bitmap.

            status = InitialiseBitmap (dcHandle, 
                                       gdiBitmap.GetId (), 
                                       true); // Monochrome.
        } // Endif.

    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to create a bitmap from a GDI device-independent bitmap.
 *
 * @param [in] dcHandle
 * The device context handle.
 *
 * @param [in] gdiDiBitmap
 * The GDI device-independent bitmap.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a bitmap has been previously created using 
 *     this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiBitmap::Create (FolioHandle          dcHandle,
                               const GdiDiBitmap&   gdiDiBitmap)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a bitmap already?

    if (IsCreated ())
    {
        // Yes.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // No. Create a display compatible bitmap.

        status = CreateCompatibleBitmap (dcHandle,
                                         gdiDiBitmap.GetBitmapHandle (),
                                         m_bitmapHandle);

        if (status == ERR_SUCCESS)
        {
            // Add to the handle monitor.

            Folio::Core::Util::g_handleMonitor.AddHandle (m_bitmapHandle,
                                                          gdiDiBitmap.GetResourceId (),
                                                          TXT("GdiBitmap::Create::CreateCompatibleBitmap"));

            // Initialise the bitmap.

            status = InitialiseBitmap (dcHandle, gdiDiBitmap.GetResourceId ());
        } // Endif.

    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will change a colour in the bitmap.
 *
 * @param [in] colour
 * The colour.
 *
 * @param [in] newColour
 * The new colour.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the bitmap colour was changed successfully.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiBitmap::ChangeColour (const Gdiplus::Color&  colour,
                                     const Gdiplus::Color&  newColour)
{  
    FolioStatus status = ERR_SUCCESS;

    // Have we created a bitmap?

    if (IsCreated ())
    {
        // Yes. Cannot change the colour of a monochrome bitmap.

        if (!m_isMonochrome)
        {
            // Change the bitmap colour.

            status = ChangeColourInBitmap (m_memoryDcHandle, 
                                           m_bitmapHandle,
                                           colour.ToCOLORREF (),
                                           newColour.ToCOLORREF ());
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
 * Method that is used to get the identifer of the bitmap.
 *
 * @return
 * The identifer of the bitmap.
 */
UInt32  GdiBitmap::GetId () const
{
    return (m_id);
} // Endproc.


/**
 * Method that indicates if the bitmap is monochrome.
 *
 * @return
 * <b>true</b> if the bitmap is monochrome, <b>false</b> otherwise.
 */
bool    GdiBitmap::IsMonochrome () const
{
    return (m_isMonochrome);
} // Endproc.


/**
 * Method that is used to get the rect of the bitmap.
 *
 * @return
 * The rect of the bitmap.
 */
Gdiplus::Rect   GdiBitmap::GetBitmapRect () const
{
    return (m_bitmapRect);
} // Endproc.


/**
 * Method that is used to get the X left position of the bitmap.
 *
 * @return
 * The X left position of the bitmap.
 */
Int32   GdiBitmap::GetBitmapXLeft () const
{
    return (m_bitmapRect.X);
} // Endproc.


/**
 * Method that is used to get the Y top position of the bitmap.
 *
 * @return
 * The Y top position of the bitmap.
 */
Int32   GdiBitmap::GetBitmapYTop () const
{
    return (m_bitmapRect.Y);
} // Endproc.


/**
 * Method that is used to get the width of the bitmap.
 *
 * @return
 * The width of the bitmap.
 */
Int32   GdiBitmap::GetBitmapWidth () const
{
    return (m_bitmapRect.Width);
} // Endproc.


/**
 * Method that is used to get the height of the bitmap.
 *
 * @return
 * The height of the bitmap.
 */
Int32   GdiBitmap::GetBitmapHeight () const
{
    return (m_bitmapRect.Height);
} // Endproc.


/**
 * Method that will set the bitmap's drawing flip.
 *
 * @param [in] horizontalFlip
 * The horizontal flip.
 *
 * @param [in] verticalFlip
 * The vertical flip.
 */
void    GdiBitmap::SetDrawingFlip (bool horizontalFlip,
                                   bool verticalFlip)
{
    m_horizontalFlip    = horizontalFlip;
    m_verticalFlip      = verticalFlip;
} // Endproc.


/**
 * Method that indicates if the bitmap is flipped horizontally.
 *
 * @return
 * <b>true</b> if the bitmap is flipped horizontally, <b>false</b> otherwise.
 */
bool    GdiBitmap::IsDrawingHorizontalFlip () const
{
    return (m_horizontalFlip);
} // Endproc.


/**
 * Method that indicates if the bitmap is flipped vertically.
 *
 * @return
 * <b>true</b> if the bitmap is flipped vertically, <b>false</b> otherwise.
 */
bool    GdiBitmap::IsDrawingVerticalFlip () const
{
    return (m_verticalFlip);
} // Endproc.


/**
 * Method that is used to set the bitmap's drawing mode.
 *
 * @param [in] drawingMode
 * The drawing mode.
 */
void    GdiBitmap::SetDrawingMode (UInt32 drawingMode)
{
    m_drawingMode = drawingMode;
} // Endproc.


/**
 * Method that is used to get the drawing mode of the bitmap.
 *
 * @return
 * The drawing mode of the bitmap.
 */
UInt32  GdiBitmap::GetDrawingMode () const
{
    return (m_drawingMode);
} // Endproc.


/**
 * Method that is used to set the bitmap's drawing width.
 *
 * @param [in] drawingWidth
 * The drawing width.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_OUT_OF_BOUNDS</b> if the width set is larger than the 
 *     width of the bitmap.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiBitmap::SetDrawingWidth (Int32 drawingWidth)
{
    FolioStatus status = ERR_SUCCESS;

    // Check for out of bounds.

    if (std::abs (drawingWidth) <= m_bitmapRect.Width)
    {
        // Set the drawing width.

        m_drawingWidthAdjustment = drawingWidth;

        m_drawingAdjustmentMode &= ~(INCREMENT_MASK | DECREMENT_MASK);
        m_drawingAdjustmentMode |= SET_WIDTH;
    } // Endif.

    else
    {
        status = ERR_OUT_OF_BOUNDS;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to set the bitmap's drawing height.
 *
 * @param [in] drawingHeight
 * The drawing height.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_OUT_OF_BOUNDS</b> if the height set is larger than the 
 *     height of the bitmap.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiBitmap::SetDrawingHeight (Int32 drawingHeight)
{
    FolioStatus status = ERR_SUCCESS;

    // Check for out of bounds.

    if (std::abs (drawingHeight) <= m_bitmapRect.Height)
    {
        // Set the drawing height.

        m_drawingHeightAdjustment = drawingHeight;

        m_drawingAdjustmentMode &= ~(INCREMENT_MASK | DECREMENT_MASK);
        m_drawingAdjustmentMode |= SET_HEIGHT;
    } // Endif.

    else
    {
        status = ERR_OUT_OF_BOUNDS;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to increment the bitmap's drawing width.
 *
 * @param [in] drawingWidthAdjustment
 * The drawing width increment.
 * A positive value will draw the bitmap from the left to the right.
 * A negative value will draw the bitmap from the right to the left.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_OUT_OF_BOUNDS</b> if the width increment is larger than the 
 *     width of the bitmap.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiBitmap::IncrementDrawingWidth (Int32 drawingWidthAdjustment)
{
    FolioStatus status = ERR_SUCCESS;

    // Check for out of bounds.

    if ((std::abs (m_drawingWidthAdjustment) + std::abs (drawingWidthAdjustment)) <= m_bitmapRect.Width)
    {
        // Set the drawing width increment.

        m_drawingWidthAdjustment += drawingWidthAdjustment;

        m_drawingAdjustmentMode &= ~(SET_MASK | DECREMENT_MASK);
        m_drawingAdjustmentMode |= INCREMENT_WIDTH;
    } // Endif.

    else
    {
        status = ERR_OUT_OF_BOUNDS;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to increment the bitmap's drawing height.
 *
 * @param [in] drawingHeightAdjustment
 * The drawing height increment.
 * A positive value will draw the bitmap from the bottom to the top.
 * A negative value will draw the bitmap from the top to the bottom.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_OUT_OF_BOUNDS</b> if the height increment is larger than the 
 *     height of the bitmap.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiBitmap::IncrementDrawingHeight (Int32 drawingHeightAdjustment)
{
    FolioStatus status = ERR_SUCCESS;

    // Check for out of bounds.

    if ((std::abs (m_drawingHeightAdjustment) + std::abs (drawingHeightAdjustment)) <= m_bitmapRect.Height)
    {
        // Set the drawing height increment.

        m_drawingHeightAdjustment += drawingHeightAdjustment;
        
        m_drawingAdjustmentMode &= ~(SET_MASK | DECREMENT_MASK);
        m_drawingAdjustmentMode |= INCREMENT_HEIGHT;
    } // Endif.

    else
    {
        status = ERR_OUT_OF_BOUNDS;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to decrement the bitmap's drawing width.
 *
 * @param [in] drawingWidthAdjustment
 * The drawing width decrement.
 * A positive value will remove the bitmap from the right to the left.
 * A negative value will remove the bitmap from the left to the right.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_OUT_OF_BOUNDS</b> if the width decrement is larger than the 
 *     width of the bitmap.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiBitmap::DecrementDrawingWidth (Int32 drawingWidthAdjustment)
{
    FolioStatus status = ERR_SUCCESS;

    // Check for out of bounds.

    if ((std::abs (m_drawingWidthAdjustment) + std::abs (drawingWidthAdjustment)) <= m_bitmapRect.Width)
    {
        // Set the drawing width decrement.

        m_drawingWidthAdjustment += drawingWidthAdjustment;
       
        m_drawingAdjustmentMode &= ~(SET_MASK | INCREMENT_MASK);
        m_drawingAdjustmentMode |= DECREMENT_WIDTH;
    } // Endif.

    else
    {
        status = ERR_OUT_OF_BOUNDS;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to decrement the bitmap's drawing height.
 *
 * @param [in] drawingHeightAdjustment
 * The drawing height decrement.
 * A positive value will remove the bitmap from the top to the bottom.
 * A negative value will remove the bitmap from the bottom to the top.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_OUT_OF_BOUNDS</b> if the height decrement is larger than the 
 *     height of the bitmap.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiBitmap::DecrementDrawingHeight (Int32 drawingHeightAdjustment)
{
    FolioStatus status = ERR_SUCCESS;

    // Check for out of bounds.

    if ((std::abs (m_drawingHeightAdjustment) + std::abs (drawingHeightAdjustment)) <= m_bitmapRect.Height)
    {
        // Set the drawing height decrement.

        m_drawingHeightAdjustment += drawingHeightAdjustment;
        
        m_drawingAdjustmentMode &= ~(SET_MASK | INCREMENT_MASK);
        m_drawingAdjustmentMode |= DECREMENT_HEIGHT;
    } // Endif.

    else
    {
        status = ERR_OUT_OF_BOUNDS;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to reset the drawing adjustment mode of the bitmap.
 */
void    GdiBitmap::ResetDrawingAdjustmentMode ()
{
    m_drawingAdjustmentMode     = NONE;
    m_drawingWidthAdjustment    = 0;
    m_drawingHeightAdjustment   = 0;
} // Endproc.


/**
 * Method that is used to get the drawing adjustment mode of the bitmap.
 *
 * @return
 * The drawing adjustment of the bitmap.
 */
UInt32  GdiBitmap::GetDrawingAdjustmentMode () const
{
    return (m_drawingAdjustmentMode);
} // Endproc.


/**
 * Indicates if there is a drawing adjustment mode for the bitmap.
 *
 * @return
 * <b>true</b> if there is a drawing adjustment for the bitmap, <b>false</b> otherwise.
 */
bool    GdiBitmap::IsDrawingAdjustmentMode () const
{
    return (m_drawingAdjustmentMode != NONE);
} // Endproc.


/**
 * Method that is used to get the drawing width adjustment of the bitmap.
 *
 * @return
 * The drawing width adjustment of the bitmap.
 */
Int32   GdiBitmap::GetDrawingWidthAdjustment () const
{
    return (m_drawingWidthAdjustment);
} // Endproc.


/**
 * Method that is used to get the drawing height adjustment of the bitmap.
 *
 * @return
 * The drawing height adjustment of the bitmap.
 */
Int32   GdiBitmap::GetDrawingHeightAdjustment () const
{
    return (m_drawingHeightAdjustment);
} // Endproc.


/**
 * Indicates if the bitmap is fully drawn.
 *
 * @return
 * <b>true</b> if the bitmap is fully drawn, <b>false</b> otherwise.
 */
bool    GdiBitmap::IsBitmapFullyDrawn ()
{
    bool    isBitmapFullyDrawn = true;

    if (m_drawingAdjustmentMode != NONE)
    {
        if (m_drawingWidthAdjustment != 0)
        {
            isBitmapFullyDrawn = (std::abs (m_drawingWidthAdjustment) == m_bitmapRect.Width);
        } // Endif.

        if (isBitmapFullyDrawn && (m_drawingHeightAdjustment != 0))
        {
            isBitmapFullyDrawn = (::abs (m_drawingHeightAdjustment) == m_bitmapRect.Height);
        } // Endif.

        // If the bitmap is fully drawn then reset the drawing adjustment mode.

        if (isBitmapFullyDrawn)
        {
            ResetDrawingAdjustmentMode ();
        } // Endif.

    } // Endif.

    return (isBitmapFullyDrawn);
} // Endproc.


/**
 * Indicates if the bitmap is no longer drawn.
 *
 * @return
 * <b>true</b> if the bitmap is no longer drawn, <b>false</b> otherwise.
 */
bool    GdiBitmap::IsBitmapNoLongerDrawn ()
{
    bool    isBitmapNoLongerDrawn = false;

    if (m_drawingAdjustmentMode != NONE)
    {
        if (m_drawingWidthAdjustment != 0)
        {
            isBitmapNoLongerDrawn = ((std::abs (m_drawingWidthAdjustment) - m_bitmapRect.Width) == 0);
        } // Endif.

        if (!isBitmapNoLongerDrawn && (m_drawingHeightAdjustment != 0))
        {
            isBitmapNoLongerDrawn = ((::abs (m_drawingHeightAdjustment) - m_bitmapRect.Height) == 0);
        } // Endif.

        // If the bitmap is no longer drawn then reset the drawing adjustment mode.

        if (isBitmapNoLongerDrawn)
        {
            ResetDrawingAdjustmentMode ();
        } // Endif.

    } // Endif.

    return (isBitmapNoLongerDrawn);
} // Endproc.


/**
 * Method that is used to get the handle of the bitmap.
 *
 * @return
 * The device context handle of the bitmap.
 */
FolioHandle GdiBitmap::GetBitmapHandle () const
{
    return (m_bitmapHandle);
} // Endproc.


/**
 * Method that is used to get the display compatible device context handle of 
 * the bitmap.
 *
 * @return
 * The display compatible device context handle of the bitmap.
 */
FolioHandle GdiBitmap::GetDcHandle () const
{
    return (m_dcHandle);
} // Endproc.


/**
 * Method that is used to get the display compatible memory device context 
 * handle of the bitmap.
 *
 * @return
 * The display compatible memory device context handle of the bitmap.
 */
FolioHandle GdiBitmap::GetBitmapDcHandle () const
{
    return (m_memoryDcHandle);
} // Endproc.


/**
 * Method that is used to get the bitmap graphics object.
 *
 * @return
 * The bitmap graphics object.
 */
Gdiplus::Graphics*  GdiBitmap::GetBitmapGraphics () const
{
    return (m_graphics.get ());
} // Endproc.


/**
 * Method that is used to clear the bitmap.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a bitmap has not been created for 
 *     this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiBitmap::Clear (const Gdiplus::Color& clearColour)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a bitmap?

    if (IsCreated ())
    {
        // Yes. Clear the bitmap.

        status = ClearRectangle (m_memoryDcHandle,
                                 0,
                                 0,
                                 m_bitmapRect.Width,
                                 m_bitmapRect.Height,
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
 * Method that is used to draw a specified rect of the bitmap.
 *
 * @param [in, out] graphics
 * The graphics object to draw to.
 *
 * @param [in] rect
 * The rect of the bitmap to draw.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a bitmap has not been created for this 
 *     object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiBitmap::Draw (Gdiplus::Graphics&     graphics,
                             const Gdiplus::Rect&   rect)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a bitmap?

    if (IsCreated ())
    {
        // Yes. Get the graphics device context.
     
        HDC graphicsDcHandle = graphics.GetHDC ();
     
        if ((rect.Width     == m_bitmapRect.Width) &&
            (rect.Height    == m_bitmapRect.Height))
        {
            // Copy the rect of the bitmap from the memory device context to the 
            // graphics device context.

            status = CopyBitmap (graphicsDcHandle,
                                 rect.X,
                                 rect.Y,
                                 rect.Width,
                                 rect.Height,
                                 m_memoryDcHandle,
                                 rect.X,
                                 rect.Y,
                                 m_drawingMode);
        } // Endif.

        else
        {
            // Scale the rect of the bitmap from the memory device context to the 
            // graphics device context.

            status = ScaleBitmap (graphicsDcHandle,
                                  0,
                                  0,
                                  rect.Width,
                                  rect.Height,
                                  m_memoryDcHandle,
                                  0,
                                  0,
                                  m_bitmapRect.Width,
                                  m_bitmapRect.Height,
                                  m_drawingMode);
        } // Endelse.

        // Release the graphics device context.
 
        graphics.ReleaseHDC (graphicsDcHandle);
    } // Endif.

    else
    {
        // No.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to draw the bitmap into a destination width and height.
 *
 * @param [in, out] graphics
 * The graphics object to draw to.
 *
 * @param [in] destinationWidth 
 * The destination width to draw the bitmap to.
 *
 * @param [in] destinationHeight 
 * The destination height to draw the bitmap to.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a bitmap has not been created for this 
 *     object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiBitmap::Draw (Gdiplus::Graphics& graphics,
                             Int32              destinationWidth,
                             Int32              destinationHeight)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a bitmap?

    if (IsCreated ())
    {
        // Yes. Get the graphics device context.
     
        HDC graphicsDcHandle = graphics.GetHDC ();
     
        // Scale the rect of the bitmap from the memory device context to the 
        // graphics device context.

        status = ScaleBitmap (graphicsDcHandle,
                              0,
                              0,
                              destinationWidth,
                              destinationHeight,
                              m_memoryDcHandle,
                              0,
                              0,
                              m_bitmapRect.Width,
                              m_bitmapRect.Height,
                              m_drawingMode);

        // Release the graphics device context.
 
        graphics.ReleaseHDC (graphicsDcHandle);
    } // Endif.

    else
    {
        // No.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to save the bitmap.
 *
 * @param [in, out] graphics
 * The graphics object to save to.
 *
 * @param [in] fileName
 * The file name.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a bitmap has not been created for this 
 *     object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiBitmap::Save (Gdiplus::Graphics& graphics, 
                             const FolioString& fileName)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a bitmap?

    if (IsCreated ())
    {
        // Save the bitmap.

        SaveBitmap (fileName);
    } // Endif.

    else
    {
        // No.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to draw the bitmap.
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
 * On return, will hold the rects of the bitmap, if successful. If this method 
 * fails then this parameter is undefined. May be zero if not required.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a bitmap has not been created for this 
 *     object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiBitmap::Draw (Int32              screenXLeft,
                             Int32              screenYTop,
                             Gdiplus::Graphics& graphics,
                             RectList*          rects)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a bitmap?

    if (IsCreated ())
    {
        // Yes. Get the graphics device context.
     
        HDC graphicsDcHandle = graphics.GetHDC ();

        Gdiplus::Rect   drawingRect;

        if (m_drawingAdjustmentMode != NONE)
        {
            status = DrawPartialBitmap (graphicsDcHandle, 
                                        screenXLeft, 
                                        screenYTop,
                                        drawingRect);
        } // Endif.
        
        else
        {
            status = DrawFullBitmap (graphicsDcHandle, 
                                     screenXLeft,
                                     screenYTop,
                                     drawingRect);
        } // Endelse.

        // Release the graphics device context.
 
        graphics.ReleaseHDC (graphicsDcHandle);

        // Does the caller want to know the rects?

        if (rects && (status == ERR_SUCCESS))
        {
            // Yes.

            rects->push_back (drawingRect);
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
 * Method that is used to initialise the bitmap.
 *
 * @param [in] dcHandle
 * The device context handle.
 *
 * @param [in] id
 * The identifier of the bitmap.
 *
 * @param [in] isMonochrome
 * Indicates if the bitmap is monochrome.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiBitmap::InitialiseBitmap (FolioHandle    dcHandle,
                                         UInt32         id,
                                         bool           isMonochrome)
{
    m_dcHandle      = dcHandle;
    m_id            = id;
    m_isMonochrome  = isMonochrome;

    // Query the bitmap's dimensions.

    Int32   bitmapWidth     = 0;    // Initialise!
    Int32   bitmapHeight    = 0;

    FolioStatus status = QueryBitmapDimensions (m_bitmapHandle, bitmapWidth, bitmapHeight);

    if (status == ERR_SUCCESS)
    {
        // Set the bitmap's attributes.

        m_bitmapRect.X      = 0;
        m_bitmapRect.Y      = 0;
        m_bitmapRect.Width  = bitmapWidth;
        m_bitmapRect.Height = bitmapHeight;

        // Set the graphic element's width and height.

        SetScreenWidth (m_bitmapRect.Width);
        SetScreenHeight (m_bitmapRect.Height);

        // Create a display compatible memory DC.

        status = CreateCompatibleMemoryDC (dcHandle, m_memoryDcHandle);

        if (status == ERR_SUCCESS)
        {
            // Select the bitmap into the memory device context.

            status = SelectObjectIntoDC (m_memoryDcHandle, m_bitmapHandle, &(m_oldBitmapHandle));

            if (status == ERR_SUCCESS)
            {
                // Create the graphics object.

                status = CreateGraphics ();
            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that is used to partially draw the bitmap.
 *
 * @param [in] graphicsDcHandle
 * The graphics device context to draw to.
 *
 * @param [in] screenXLeft
 * The screen X left position of the graphic element.
 *
 * @param [in] screenYTop
 * The screen Y top position of the graphic element.
 *
 * @param [out] drawingRect
 * The scaled rect of the drawn bitmap.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiBitmap::DrawPartialBitmap (HDC               graphicsDcHandle,
                                          Int32             screenXLeft,
                                          Int32             screenYTop,
                                          Gdiplus::Rect&    drawingRect) const
{
    FolioStatus status = ERR_SUCCESS;

    Int32   sourceX         = 0;    // Initialise!
    Int32   sourceY         = 0;
    Int32   sourceWidth     = m_bitmapRect.Width;
    Int32   sourceHeight    = m_bitmapRect.Height;

    Int32   drawingWidthAdjustment  = m_drawingWidthAdjustment;
    Int32   drawingHeightAdjustment = m_drawingHeightAdjustment;

    // Calculate the scaled position.

    Int32   scaledXLeft = screenXLeft * m_screenScale;
    Int32   scaledYTop  = screenYTop * m_screenScale;

    // Build the scaled rect.

    if ((m_drawingAdjustmentMode & SET_WIDTH) ||
        (m_drawingAdjustmentMode & DECREMENT_WIDTH))
    {
        if (m_drawingWidthAdjustment < 0)
        {
            drawingWidthAdjustment *= -1;

            drawingRect.X   = (screenXLeft - m_drawingWidthAdjustment) * m_screenScale;
            sourceX        += drawingWidthAdjustment;
        } // Endif.

        else
        {
            drawingRect.X   = scaledXLeft;
        } // Endif.

        drawingRect.Width   = (m_bitmapRect.Width - drawingWidthAdjustment) * m_screenScale;
        sourceWidth         = m_bitmapRect.Width - drawingWidthAdjustment;
    } // Endif.

    else
    if (m_drawingAdjustmentMode & INCREMENT_WIDTH)
    {
        if (m_drawingWidthAdjustment < 0)
        {
            drawingWidthAdjustment *= -1;

            drawingRect.X   = (screenXLeft + sourceWidth - drawingWidthAdjustment) * m_screenScale;
            sourceX        += sourceWidth - drawingWidthAdjustment;
        } // Endif.

        else
        {
            drawingRect.X   = scaledXLeft;
        } // Endif.

        drawingRect.Width   = drawingWidthAdjustment * m_screenScale;
        sourceWidth         = drawingWidthAdjustment;
    } // Endelseif.

    else
    {
        drawingRect.X       = scaledXLeft;
        drawingRect.Width   = m_scaledWidth;
    } // Endelse.

    if ((m_drawingAdjustmentMode & SET_HEIGHT) ||
        (m_drawingAdjustmentMode & DECREMENT_HEIGHT))
    {
        if (m_drawingHeightAdjustment < 0)
        {
            drawingHeightAdjustment *= -1;
        
            drawingRect.Y   = (screenYTop - m_drawingHeightAdjustment) * m_screenScale;
            sourceY        += drawingHeightAdjustment;
        } // Endif.

        else
        {
            drawingRect.Y   = scaledYTop;
        } // Endelse.

        drawingRect.Height  = (m_bitmapRect.Height - drawingHeightAdjustment) * m_screenScale;
        sourceHeight        = m_bitmapRect.Height - drawingHeightAdjustment;
    } // Endif.

    else
    if (m_drawingAdjustmentMode & INCREMENT_HEIGHT)
    {
        if (m_drawingHeightAdjustment < 0)
        {
            drawingHeightAdjustment *= -1;
        
            drawingRect.Y   = (screenYTop + sourceHeight - drawingHeightAdjustment) * m_screenScale;
            sourceY        += sourceHeight - drawingHeightAdjustment;
        } // Endif.

        else
        {
            drawingRect.Y   = scaledYTop;
        } // Endelse.

        drawingRect.Height  = drawingHeightAdjustment * m_screenScale;
        sourceHeight        = drawingHeightAdjustment;
    } // Endelseif.

    else
    {
        drawingRect.Y       = scaledYTop;
        drawingRect.Height  = m_scaledHeight;
    } // Endelse.

    if (sourceWidth && sourceHeight && 
        drawingRect.Width && drawingRect.Height)
    {
        // Scale the rect of the bitmap from the memory device context to the 
        // graphics device context.

        status = ScaleBitmap (graphicsDcHandle,
                              drawingRect.X,
                              drawingRect.Y,
                              drawingRect.Width,
                              drawingRect.Height,
                              m_memoryDcHandle,
                              sourceX,
                              sourceY,
                              sourceWidth,
                              sourceHeight,
                              m_drawingMode);

        if ((status == ERR_SUCCESS) && 
            ((m_drawingAdjustmentMode & SET_WIDTH) ||
             (m_drawingAdjustmentMode & SET_HEIGHT)))
        {
            Int32   lineWidth   = m_screenScale;
            Int32   lineStartX  = drawingRect.X + lineWidth / 2;
            Int32   lineStartY  = drawingRect.Y + lineWidth / 2;
            Int32   lineEndX    = (m_drawingAdjustmentMode & SET_WIDTH) ? lineStartX : lineStartX + drawingRect.Width - lineWidth;
            Int32   lineEndY    = (m_drawingAdjustmentMode & SET_HEIGHT) ? lineStartY : lineStartY + drawingRect.Height - lineWidth;
    
            status = DrawLine (graphicsDcHandle,
                               lineStartX,
                               lineStartY,
                               lineEndX,
                               lineEndY,
                               lineWidth,
                               DEFAULT_BACKGROUND_COLOUR);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that is used to draw the bitmap.
 *
 * @param [in] graphicsDcHandle
 * The graphics device context to draw to.
 *
 * @param [in] screenXLeft
 * The screen X left position of the graphic element.
 *
 * @param [in] screenYTop
 * The screen Y top position of the graphic element.
 *
 * @param [out] drawingRect
 * The scaled rect of the drawn bitmap.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiBitmap::DrawFullBitmap (HDC              graphicsDcHandle,
                                       Int32            screenXLeft,
                                       Int32            screenYTop,
                                       Gdiplus::Rect&   drawingRect) const
{
    FolioStatus status = ERR_SUCCESS;

    // Note the drawing rect.

    drawingRect = Gdiplus::Rect(screenXLeft * m_screenScale,
                                screenYTop * m_screenScale,
                                m_scaledWidth,
                                m_scaledHeight);

    if ((m_screenScale == 1)    &&
        !m_horizontalFlip       && 
        !m_verticalFlip)
    {
        // Copy the rect of the bitmap from the memory device context to the 
        // graphics device context.

        status = CopyBitmap (graphicsDcHandle,
                             drawingRect.X,
                             drawingRect.Y,
                             drawingRect.Width,
                             drawingRect.Height,
                             m_memoryDcHandle,
                             0,
                             0,
                             m_drawingMode);
    } // Endif.

    else
    {
        // Scale the rect of the bitmap from the memory device context to the 
        // graphics device context.

        status = ScaleBitmap (graphicsDcHandle,
                              m_horizontalFlip ? (screenXLeft + m_screenWidth) * m_screenScale - 1 : drawingRect.X,
                              m_verticalFlip ? (screenYTop + m_screenHeight) * m_screenScale - 1 : drawingRect.Y,
                              m_horizontalFlip ? -drawingRect.Width : drawingRect.Width,
                              m_verticalFlip  ? -drawingRect.Height : drawingRect.Height,
                              m_memoryDcHandle,
                              0,
                              0,
                              m_bitmapRect.Width,
                              m_bitmapRect.Height,
                              m_drawingMode);
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to save the bitmap.
 *
 * @param [in] fileName
 * The file name.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiBitmap::SaveBitmap (const FolioString& fileName) const
{
    return (Folio::Core::Graphic::Gdi::SaveBitmap (fileName, 
                                                   Bitmap(reinterpret_cast<HBITMAP> (m_bitmapHandle), NULL)));
} // Endproc.


/**
 * Method that is used to destroy the bitmap.
 */
void    GdiBitmap::Destroy ()
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

        Folio::Core::Util::g_handleMonitor.RemoveHandle (m_bitmapHandle);
    } // Endif.

} // Endproc.


/**
 * Method that is used to determine if the bitmap has been created.
 *
 * @return
 * <b>true</b> if the bitmap has been created, <b>false</b> otherwise.
 */
bool    GdiBitmap::IsCreated () const
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
FolioStatus GdiBitmap::CreateGraphics ()
{
    // Create the graphics object.

    m_graphics.reset (new Graphics (reinterpret_cast<HDC> (m_memoryDcHandle)));

    // Initialise it!

    return (Gdi::InitializeGraphics (*m_graphics.get ()));
} // Endproc.


/**
 * Method that is used to destroy the graphics object.
 */
void    GdiBitmap::DestroyGraphics ()
{
    m_graphics.reset ();
} // Endproc.


/**
 * Method that is used to determine if the graphics object has been created.
 *
 * @return
 * <b>true</b> if the graphics object has been created, <b>false</b> otherwise.
 */
bool    GdiBitmap::IsGraphics () const
{
    return (m_graphics.get () != 0);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
