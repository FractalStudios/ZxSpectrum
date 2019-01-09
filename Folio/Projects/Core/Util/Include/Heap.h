#pragma once

// "Home-made" includes.
#include    <Base.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Util
{

/// The heap class.
/**
 * This class provides a heap object.
 *
 * This class does not support copy construction or assignment.
 */
class Heap
{
public:
    explicit Heap (bool processHeap = true);
    ~Heap ();

    FolioStatus Create (UInt32  initialSize,
                        UInt32  maxSize);

    FolioStatus Allocate (UInt32    size,
                          void*&    buffer);
    FolioStatus Free (void* buffer);

private:
    bool        m_processHeap;  ///< Indicates if the heap used is the process heap.
    FolioHandle m_heapHandle;   ///< The heap handle.

    /// Private copy constructor to prevent copying.
    Heap (const Heap& rhs);

    /// Private assignment operator to prevent copying.
    Heap& operator= (const Heap& rhs);
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
