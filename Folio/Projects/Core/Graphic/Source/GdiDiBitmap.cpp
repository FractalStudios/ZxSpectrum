// "Home-made" includes.
#include    <Util.h>
#include    "..\Include\Gdi.h"
#include    "GdiDiBitmap.h"

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
GdiDiBitmap::GdiDiBitmap ()
:   m_resourceId(FOLIO_UNDEFINED),
    m_bitmapHandle(FOLIO_INVALID_HANDLE)
{
} // Endproc.


/**
 * The class destructor.
 */
GdiDiBitmap::~GdiDiBitmap ()
{
    // Destroy the bitmap.

    Destroy ();
} // Endproc.


/**
 * The class copy constructor.
 */
GdiDiBitmap::GdiDiBitmap (const GdiDiBitmap& rhs)
{
    Create (rhs);
} // Endproc.


/**
 * The class assignment operator.
 */
GdiDiBitmap&    GdiDiBitmap::operator = (const GdiDiBitmap &rhs)
{
    if (this != &(rhs))
    {
        Create (rhs);
    } // Endif.

    return (*this);
} // Endproc.


/**
 * Method that is used to create the bitmap.
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
FolioStatus GdiDiBitmap::Create (FolioHandle    instanceHandle,
                                 UInt16         resourceId)
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

        status = LoadBitmap (instanceHandle, resourceId, true, m_bitmapHandle);

        if (status == ERR_SUCCESS)
        {
            // Initialise the bitmap.

            status = InitialiseBitmap (resourceId);
        } // Endif.

    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to create the bitmap.
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
FolioStatus GdiDiBitmap::Create (const FolioString &fileName)
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

        status = LoadBitmap (fileName, true, m_bitmapHandle);

        if (status == ERR_SUCCESS)
        {
            // Initialise the bitmap.

            status = InitialiseBitmap (FOLIO_UNDEFINED);
        } // Endif.

    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to create a bitmap from a GDI device-independent bitmap.
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
FolioStatus GdiDiBitmap::Create (const GdiDiBitmap& gdiDiBitmap)
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
        // Create a display compatible memory DC.

        FolioHandle memoryDcHandle = FOLIO_INVALID_HANDLE;

        FolioStatus status = CreateCompatibleMemoryDC (0, memoryDcHandle);

        if (status == ERR_SUCCESS)
        {
            // Create the copied bitmap.

            status = CreateCopiedDiBitmap (memoryDcHandle,
                                           gdiDiBitmap.GetBitmapHandle (), 
                                           m_bitmapHandle);

            if (status == ERR_SUCCESS)
            {
                // Add to the handle monitor.

                //Folio::Core::Util::g_handleMonitor.AddHandle (m_bitmapHandle,
                //                                              gdiDiBitmap.GetResourceId (),
                //                                              TXT("GdiDiBitmap::Create::CreateCopiedDiBitmap"));

                // Initialise the bitmap.

                status = InitialiseBitmap (gdiDiBitmap.GetResourceId ());
            } // Endif.

            // Destroy the memory device context.

            DestroyMemoryDC (memoryDcHandle);
        } // Endif.

    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will create a bitmap, from a specified device-independent bitmap 
 * rotated at a specific angle.
 *
 * @param [in] diBitmap
 * The device-independent bitmap.
 *
 * @param [in] radians
 * The angle to rotate.
 *
 * @param [in] backgroundColourRef
 * The default bacground colour.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a bitmap has been previously created using 
 *     this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiDiBitmap::Create (const GdiDiBitmap      &gdiDiBitmap,
                                 const double&          radians, 
                                 const Gdiplus::Color&  backgroundColour)
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
        // No. Create a display compatible memory DC.

        FolioHandle memoryDcHandle = FOLIO_INVALID_HANDLE;

        status = CreateCompatibleMemoryDC (0, memoryDcHandle);

        if (status == ERR_SUCCESS)
        {
            // Create the rotated bitmap.

            status = CreateRotatedDiBitmap (memoryDcHandle,
                                            gdiDiBitmap.GetBitmapHandle (), 
                                            radians, 
                                            backgroundColour.ToCOLORREF (),
                                            m_bitmapHandle);

            if (status == ERR_SUCCESS)
            {
                // Add to the handle monitor.

                //Folio::Core::Util::g_handleMonitor.AddHandle (m_bitmapHandle,
                //                                              gdiDiBitmap.GetResourceId (),
                //                                              TXT("GdiDiBitmap::Create::CreateRotateddDiBitmap"));

                // Initialise the bitmap.

                status = InitialiseBitmap (gdiDiBitmap.GetResourceId ());
            } // Endif.

            // Destroy the memory device context.

            DestroyMemoryDC (memoryDcHandle);
        } // Endif.

    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will obtain the colour table index of a specified colour in the 
 * bitmap's colour table.
 *
 * @param [in] colour
 * The colour.
 *
 * @return
 * The index of the colour within the colour table. FOLIO_INVALID_INDEX if the 
 * colour is not in the colour table.
 */
UInt32  GdiDiBitmap::GetColourTableIndex (const Gdiplus::Color& colour)
{  
    UInt32  colourTableIndex = FOLIO_INVALID_INDEX; // Initialise!

    // Have we created a bitmap?

    if (IsCreated ())
    {
        // Yes. Create a display compatible memory DC.

        FolioHandle memoryDcHandle = FOLIO_INVALID_HANDLE;

        if (CreateCompatibleMemoryDC (0, memoryDcHandle) == ERR_SUCCESS)
        {
            // Query the colour table index in the bitmap colour table.

            if (QueryColourTableIndexInDiBitmap (memoryDcHandle,
                                                 m_bitmapHandle,
                                                 colour.ToCOLORREF (),
                                                 colourTableIndex) != ERR_SUCCESS)
            {
                colourTableIndex = FOLIO_INVALID_INDEX; // Initialise!
            } // Endif.

            // Destroy the memory device context.

            DestroyMemoryDC (memoryDcHandle);
        } // Endif.

    } // Endif.

    return (colourTableIndex);
} // Endproc. 


/**
 * Method that will query the colour of a specified colour table index in the 
 * bitmap's colour table.
 *
 * @param [in] colourTableIndex
 * The index of the colour within the colour table.
 *
 * @param [out] colour
 * The colour.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the bitmap colour was queried successfully.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiDiBitmap::QueryColour (UInt32            colourTableIndex,
                                      Gdiplus::Color&   colour)
{  
    FolioStatus status = ERR_SUCCESS;

    // Have we created a bitmap?

    if (IsCreated ())
    {
        // Yes. Create a display compatible memory DC.

        FolioHandle memoryDcHandle = FOLIO_INVALID_HANDLE;

        status = CreateCompatibleMemoryDC (0, memoryDcHandle);

        if (status == ERR_SUCCESS)
        {
            // Query the bitmap colour.

            COLORREF    colourRef = 0;  // Initialise!

            status = QueryColourInDiBitmap (memoryDcHandle, 
                                            m_bitmapHandle,
                                            colourTableIndex,
                                            colourRef);

            if (status == ERR_SUCCESS)
            {
                colour.SetFromCOLORREF (colourRef);
            } // Endif.

            // Destroy the memory device context.

            DestroyMemoryDC (memoryDcHandle);
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
 * Method that will change a colour in the bitmap's colour table.
 *
 * @param [in] colourTableIndex
 * The index of the colour within the colour table.
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
FolioStatus GdiDiBitmap::ChangeColour (UInt32                   colourTableIndex,
                                       const Gdiplus::Color&    newColour)
{  
    FolioStatus status = ERR_SUCCESS;

    // Have we created a bitmap?

    if (IsCreated ())
    {
        // Yes. Create a display compatible memory DC.

        FolioHandle memoryDcHandle = FOLIO_INVALID_HANDLE;

        status = CreateCompatibleMemoryDC (0, memoryDcHandle);

        if (status == ERR_SUCCESS)
        {
            // Change the bitmap colour.

            status = ChangeColourInDiBitmap (memoryDcHandle, 
                                             m_bitmapHandle,
                                             colourTableIndex,
                                             newColour.ToCOLORREF ());

            // Destroy the memory device context.

            DestroyMemoryDC (memoryDcHandle);
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
 * Method that will change a colour in the bitmap's colour table.
 *
 * @param [in] colour
 * The colour.
 *
 * @param [in] newColour
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
FolioStatus GdiDiBitmap::ChangeColour (const Gdiplus::Color&    colour,
                                       const Gdiplus::Color&    newColour,
                                       UInt32&                  colourTableIndex)
{  
    FolioStatus status = ERR_SUCCESS;

    // Have we created a bitmap?

    if (IsCreated ())
    {
        // Yes. Create a display compatible memory DC.

        FolioHandle memoryDcHandle = FOLIO_INVALID_HANDLE;

        status = CreateCompatibleMemoryDC (0, memoryDcHandle);

        if (status == ERR_SUCCESS)
        {
            // Change the bitmap colour.

            status = ChangeColourInDiBitmap (memoryDcHandle, 
                                             m_bitmapHandle,
                                             colour.ToCOLORREF (),
                                             newColour.ToCOLORREF (),
                                             colourTableIndex);

            // Destroy the memory device context.

            DestroyMemoryDC (memoryDcHandle);
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
 * Method that is used to get the resource identifier of the bitmap.
 *
 * @return
 * The resource identifier of the bitmap.
 */
UInt16  GdiDiBitmap::GetResourceId () const
{
    return (m_resourceId);
} // Endproc.


/**
 * Method that is used to get the rect of the bitmap.
 *
 * @return
 * The rect of the bitmap.
 */
Gdiplus::Rect   GdiDiBitmap::GetBitmapRect () const
{
    return (m_bitmapRect);
} // Endproc.


/**
 * Method that is used to get the X left position of the bitmap.
 *
 * @return
 * The X left position of the bitmap.
 */
Int32   GdiDiBitmap::GetBitmapXLeft () const
{
    return (m_bitmapRect.X);
} // Endproc.


/**
 * Method that is used to get the Y top position of the bitmap.
 *
 * @return
 * The Y top position of the bitmap.
 */
Int32   GdiDiBitmap::GetBitmapYTop () const
{
    return (m_bitmapRect.Y);
} // Endproc.


/**
 * Method that is used to get the width of the bitmap.
 *
 * @return
 * The width of the bitmap.
 */
Int32   GdiDiBitmap::GetBitmapWidth () const
{
    return (m_bitmapRect.Width);
} // Endproc.


/**
 * Method that is used to get the height of the bitmap.
 *
 * @return
 * The height of the bitmap.
 */
Int32   GdiDiBitmap::GetBitmapHeight () const
{
    return (m_bitmapRect.Height);
} // Endproc.


/**
 * Method that is used to get the handle of the bitmap.
 *
 * @return
 * The device context handle of the bitmap.
 */
FolioHandle GdiDiBitmap::GetBitmapHandle () const
{
    return (m_bitmapHandle);
} // Endproc.


/**
 * Method that is used to initialise the bitmap.
 *
 * @param [in] resourceId
 * The resource identifier of the bitmap.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiDiBitmap::InitialiseBitmap (UInt16 resourceId)
{
    // Query the bitmap's dimensions.

    Int32   bitmapWidth     = 0;    // Initialise!
    Int32   bitmapHeight    = 0;

    FolioStatus status = QueryBitmapDimensions (m_bitmapHandle, bitmapWidth, bitmapHeight);

    if (status == ERR_SUCCESS)
    {
        // Set the bitmap's attributes.

        m_resourceId = resourceId;

        m_bitmapRect.X      = 0;
        m_bitmapRect.Y      = 0;
        m_bitmapRect.Width  = bitmapWidth;
        m_bitmapRect.Height = bitmapHeight;
    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that is used to destroy the bitmap.
 */
void    GdiDiBitmap::Destroy ()
{
    // Destroy the bitmap?

    if (m_bitmapHandle != FOLIO_INVALID_HANDLE)
    {
        // Yes.

        DestroyBitmap (m_bitmapHandle);
    } // Endif.

} // Endproc.


/**
 * Method that is used to determine if the bitmap has been created.
 *
 * @return
 * <b>true</b> if the bitmap has been created, <b>false</b> otherwise.
 */
bool    GdiDiBitmap::IsCreated () const
{
    // If the bitmap handle is valid, then the bitmap has been created.

    return (m_bitmapHandle != FOLIO_INVALID_HANDLE);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
