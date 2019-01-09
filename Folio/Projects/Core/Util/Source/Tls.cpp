// Windows includes.
#include    <Windows.h>

// "Home-made" includes.
#include    <Trace.h>
#include    "Tls.h"

namespace Folio
{

namespace Core
{

namespace Util
{

namespace Tls
{

/**
 * Function that allocates thread local storage.
 *
 * @param [out] tlsIndex
 * On return, will hold the index into thread local storage, if successful. If
 * this method fails then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Alloc (UInt32& tlsIndex)
{
    FolioStatus status = ERR_SUCCESS;

    // Allocate TLS.

    tlsIndex = ::TlsAlloc ();

    if (tlsIndex == TLS_OUT_OF_INDEXES)
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR (TXT("TlsAlloc"),
                              status);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that frees thread local storage.
 *
 * @param [in] tlsIndex
 * The index into thread local storage.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Free (UInt32 tlsIndex)
{
    FolioStatus status = ERR_SUCCESS;

    // Free TLS.

    if (!::TlsFree (tlsIndex))
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_1 (TXT("TlsFree"),
                                status,
                                tlsIndex);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that sets data in thread local storage.
 *
 * @param [in] tlsIndex
 * The index into thread local storage.
 *
 * @param [in] data
 * The data.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus SetData (UInt32 tlsIndex,
                     void*  data)
{
    FolioStatus status = ERR_SUCCESS;

    // Set data in TLS.

    if (!::TlsSetValue (tlsIndex, data))
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_2 (TXT("TlsSetValue"),
                                status,
                                tlsIndex,
                                data);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that obtains data from thread local storage.
 *
 * @param [in] tlsIndex
 * The index into thread local storage.
 *
 * @param [out] data
 * On return, will hold the data, if successful. If this method fails then this 
 * parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus QueryData (UInt32   tlsIndex,
                       void*&   data)
{
    FolioStatus status = ERR_SUCCESS;

    // Get the data in TLS.

    data = ::TlsGetValue (tlsIndex);

    // If the data is really zero, then TlsGetValue will return zero, so
    // make sure that we do have an error.

    if ((data == 0) &&
        (::GetLastError () != ERR_SUCCESS))
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_2 (TXT("TlsGetValue"),
                                status,
                                tlsIndex,
                                data);
    } // Endif.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
