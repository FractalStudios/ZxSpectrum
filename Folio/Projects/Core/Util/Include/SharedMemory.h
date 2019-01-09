#pragma once

// "Home-made" includes.
#include    <Base.h>
#include    "SharedName.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Util
{

/// The shared memory class.
/**
 * This class can be used to share memory between two or more processes.
 * To share memory, all of the processes must use the assigned name of the
 * shared memory.
 *
 * To create the shared memory, a process must use the <b>Create</b>method.
 * To access memory that has been created a process can use the <b>Open</b>
 * method.
 *
 * The shared memory will not be destroyed until all processes that use it
 * close their access to it by using the <b>Close</b> method.
 *
 * Processes that share memory must coordinate their access using
 * semaphores, mutexes, events, or some other mutual exclusion technique.
 *
 * This class does not support copy construction or assignment.
 */
class SharedMemory
{
public:
    SharedMemory ();
    ~SharedMemory ();

    FolioStatus Create (const FolioString&  sharedMemoryName,
                        UInt32              size,
                        const FolioString*  fileName = 0,
                        void*               baseAddress = 0,
                        bool                useRawName = false);

    FolioStatus Open (const FolioString&    sharedMemoryName,
                      void*                 baseAddress = 0,
                      bool                  useRawName = false);
    FolioStatus Close ();

    void*   GetBaseAddress () const;
    UInt32  GetSize () const;

private:
    SharedName  m_sharedMemoryName; ///< The shared name of the shared memory.
    void*       m_baseAddress;      ///< The base address of the shared memory.
    UInt32      m_size;             ///< The size (in bytes) of the shared memory (including the shared memory management).
    Byte*       m_data;             ///< The shared memory.
    FolioHandle m_fileMapHandle;    ///< The shared memory file map handle.
    FolioString m_fileName;         ///< The shared memory file name.
    FolioHandle m_fileHandle;       ///< The shared memory file handle.

    static  const   UInt32  MEMORY_SENTINEL = 0x6c697455;   ///< The sentinel used to mark the start and end of a shared user buffer boundary ("Util").

    /// The shared memory management header structure.
    /**
     * Under Windows it's not possible to determine the allocated size of
     * paged file mapped memory when opened. We will store the size during
     * the creation.
     *
     * Also instrumentation is employed in an attempt to ensure that memory
     * corruption (buffer over and under runs) is caught as soon possible.
     *
     * Memory Header <i>&lt;Size&gt;&lt;Start Sentinel&gt;</i><br>
     * User Buffer<br>
     * Memory Tail <i>&lt;End Sentinel&gt;</i>
     */
    struct  MemoryHeader
    {
        UInt32  m_size;     ///< User buffer size + <b>MemoryHeader</b> size (in bytes).
        UInt32  m_sentinel; ///< The start sentinel (check for buffer underrun).
    }; // Endstruct.

    /// The shared memory management tail structure.
    /**
     * Instrumentation is employed in an attempt to ensure that memory
     * corruption (buffer over and under runs) is caught as soon possible.
     *
     * Memory Header <i>&lt;"Size"&gt;&lt;"Start Sentinel"&gt;</i><br>
     * User Buffer<br>
     * Memory Tail <i>&lt;"End Sentinel"&gt;</i>
     */
    struct  MemoryTail
    {
        UInt32  m_sentinel; ///< The end sentinel (check for buffer overrun).
    }; // Endstruct.

    FolioStatus InitializeFile (const FolioString* fileName);
    FolioStatus TerminateFile ();

    FolioStatus MapFile (void*  baseAddress,
                         bool   initialise);
    FolioStatus UnmapFile ();

    void        LaydownMemoryManagement () const;
    FolioStatus VerifyMemoryManagement ();

    // Private copy constructor to prevent copying.
    SharedMemory (const SharedMemory& rhs);

    // Private assignment operator to prevent copying.
    SharedMemory& operator= (const SharedMemory& rhs);
}; // Endclass.

/// The shared memory name.
class SharedMemoryName : public FolioString
{
public:
    SharedMemoryName (const FolioString& base)
    :   FolioString(base)
    {*this += TXT("::Memory::");} // Endproc.
    
    ~SharedMemoryName () {};
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
