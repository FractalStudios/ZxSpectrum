// Windows includes.
#include    <Windows.h>

// "Home-made" includes.
#include    <Trace.h>
#include    "Heap.h"
                         
namespace Folio
{

namespace Core
{

namespace Util
{

/**
 * The class constructor.
 *
 * @param [in] processHeap
 * Indicates if the heap used is the process heap.
 */
Heap::Heap (bool processHeap)
:   m_processHeap(processHeap),
    m_heapHandle(processHeap ? ::GetProcessHeap () : FOLIO_INVALID_HANDLE)
{
} // Endproc.


/**
 * The class destructor. If required it will remove any OS reference to the
 * heap from this object.
 */
Heap::~Heap ()
{
    // Have we created a heap?

    if (m_heapHandle != FOLIO_INVALID_HANDLE)
    {
        // Destroy the heap.

        if (!::HeapDestroy (m_heapHandle))
        {
            // Build and log an error.

            FolioStatus status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_1 (TXT("HeapDestroy"),
                                    status,
                                    m_heapHandle);
        } // Endif.

    } // Endif.

} // Endproc.


/**
 * Method that will create a heap.
 *
 * @param [in] initialSize
 * The initial size (in bytes) of the heap. This value determines the initial
 * amount of physical storage that is allocated for the heap. The value is
 * rounded up to the next page boundary.
 *
 * @param [in] maxSize
 * If this is a nonzero value, it specifies the maximum size (in bytes) of the
 * heap. This method rounds <i>maxSize</i> up to the next page boundary, and
 * then reserves a block of that size in the process's virtual address space
 * for the heap. If allocation requests made by the <b>Allocate</b> method
 * exceed the initial amount of physical storage specified by
 * <i>initialSize</i>, the system allocates additional pages of physical
 * storage for the heap, up to the heap's maximum size.
 *
 * If <i>maxSize</i> is zero, it specifies that the heap is growable. The
 * heap's size is limited only by available memory.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the heap was successfully created.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a heap has been previously created
 *     using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Heap::Create (UInt32    initialSize,
                          UInt32    maxSize)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a heap already?

    if (m_heapHandle == FOLIO_INVALID_HANDLE)
    {
        m_heapHandle = ::HeapCreate (0,  // No options.
                                     initialSize,
                                     maxSize);

        if (m_heapHandle == FOLIO_INVALID_HANDLE)
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_2 (TXT("HeapCreate"),
                                    status,
                                    initialSize,
                                    maxSize);
        } // Endif.

    } // Endif.

    else
    {
        // Already have a heap handle for this object.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will allocate an unmoveable block of memory from the heap.
 *
 * @param [in] size
 * The size (in bytes) of the memory block to allocate.
 *
 * @param [out] buffer
 * Location in which the address of the allocated memory block will be returned
 * if this method is successful. Will be set to zero if the allocation fails.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the memory block was successfully allocated.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a heap has not been previously
 *     created using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Heap::Allocate (UInt32  size,
                            void*&  buffer)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a heap?

    if (m_heapHandle == FOLIO_INVALID_HANDLE)
    {
        // No heap handle.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        buffer = ::HeapAlloc (m_heapHandle,
                              HEAP_ZERO_MEMORY,
                              size);

        if (buffer == 0)
        {
            // On failure, SetLastError is not called by HeapAlloc, so
            // should not call GetLastError to get reason for faillure.
            // Assume that we're out of memory.

            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(STATUS_NO_MEMORY);

            FOLIO_LOG_CALL_ERROR_2 (TXT("HeapAlloc"),
                                    status,
                                    m_heapHandle,
                                    size);
        } // Endif.

    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will free an allocated block of memory from the heap.
 *
 * @param [in] buffer
 * The address of the memory block to be freed.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the memory block was successfully freed.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a heap has not been previously
 *     created using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Heap::Free (void* buffer)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a heap?

    if (m_heapHandle == FOLIO_INVALID_HANDLE)
    {
        // No heap handle.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        if (!::HeapFree (m_heapHandle,
                         0, // No flags.
                         buffer))
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_2 (TXT("HeapFree"),
                                    status,
                                    m_heapHandle,
                                    buffer);
        } // Endif.

    } // Endelse.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
