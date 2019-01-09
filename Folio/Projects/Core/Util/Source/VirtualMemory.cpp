// "Home-made" includes.
#include    <Trace.h>
#include    "VirtualMemory.h"

namespace Folio
{

namespace Core
{

namespace Util
{

namespace VirtualMemory
{

/**
 * Function that will get information about a range of pages within the
 * virtual address space of a specified process.
 *
 * @param [in] processHandle
 * The handle to the process whose memory information is queried. The handle
 * must have been opened with the PROCESS_QUERY_INFORMATION access right,
 * which enables using the handle to read information from the process object.
 *
 * @param [in] address
 * A pointer to the base address of the region of pages to be queried. This
 * value is rounded down to the next page boundary.
 *
 * @param [out] memoryBasicInfo
 * On return, will hold information about the specified page range, if
 * successful. If this method fails then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a mutex has been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus QueryVirtualMemory (FolioHandle                 processHandle,
                                void*                       address,
                                MEMORY_BASIC_INFORMATION&   memoryBasicInfo)
{
    FolioStatus status = ERR_SUCCESS;

    // Virutal query

    if (!::VirtualQueryEx (processHandle,
                           address,
                           &(memoryBasicInfo),
                           sizeof (memoryBasicInfo)))
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_2 (TXT("VirtualQueryEx"),
                                status,
                                processHandle,
                                address);
    } // Endif.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
