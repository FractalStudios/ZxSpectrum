// Windows includes.
#include    <Windows.h>

// "Home-made" includes.
#include    <Trace.h>
#include    "ProcessInfo.h"

namespace Folio
{

namespace Core
{

namespace Util
{

namespace ProcessInfo
{

/**
 * Function that will get the current process handle.
 *
 * @return
 * The current process handle.
 */
FolioHandle GetCurrentProcessHandle ()
{
    return (::GetCurrentProcess ());
} // Endproc.


/**
 * Function that will get the current process identifier.
 *
 * @return
 * The current process identifier.
 */
UInt32  GetCurrentProcessId ()
{
    return (::GetCurrentProcessId ());
} // Endproc.


/**
 * Function that will get the current thread identifier.
 *
 * @return
 * The current thread identifier.
 */
UInt32  GetCurrentThreadId ()
{
    return (::GetCurrentThreadId ());
} // Endproc.


/**
 * Function that will get the current module handle.
 *
 * @return
 * The current module handle.
 */
FolioHandle GetCurrentModuleHandle ()
{
    // Return handle to file used to create current process.

    return (::GetModuleHandle (0));
} // Endproc.


#pragma pack(push,8)
/// The thread name information structure.
struct  ThreadNameInfo
{
    UInt32  m_type;     ///< Must be 0x1000.
    LPCSTR  m_name;     ///< The thread name (in process address space).
    UInt32  m_threadId; ///< The thread identifier (-1 = current thread).
    UInt32  m_flags;    ///< Reserved for future use, must be zero.
}; // Endstruct.
#pragma pack (pop)

/**
 * Function that will set the name of the thread.
 *
 * @param [in] threadId
 * The thread identifier of the thread. -1 for the current thread.
 *
 * @param [in] threadName
 * The name of the thread.
 */
void    SetThreadName (UInt32                   threadId,
                       const FolioNarrowString& threadName)
{
    ThreadNameInfo  threadNameInfo;
    ::memset (&(threadNameInfo), 0, sizeof (threadNameInfo));
    threadNameInfo.m_type       = 0x1000;
    threadNameInfo.m_name       = threadName.c_str ();
    threadNameInfo.m_threadId   = threadId;
    threadNameInfo.m_flags      = 0;
  
    __try
    {
        ::RaiseException (0x406D1388,   // MS VC exception. 
                          0,
                          sizeof (threadNameInfo) / sizeof (ULONG_PTR), 
                          reinterpret_cast<ULONG_PTR*> (&(threadNameInfo)));
    } // Endtry.

    __except (EXCEPTION_CONTINUE_EXECUTION)
    {
    } // Endexcept.

} // Endproc.


/**
 * Function that will indicate if a thread identifier is valid.
 *
 * @param [in] threadId
 * The thread identifier to validate.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>true</b> if the thread identifier is valid.
 * <li><b>false</b> otherwise.
 * </ul>
 */
bool    IsValidThread (UInt32 threadId)
{
    bool    isValidThread = false;  // Initialise!

    // Open the thread.

    FolioHandle threadHandle = ::OpenThread (THREAD_QUERY_INFORMATION,
                                             FALSE,   // Don't inherit handle.
                                             threadId);

    if (threadHandle)
    {
        isValidThread = true;

        // Close the thread.

        ::CloseHandle (threadHandle);
    } // Endif.

    else
    {
        // Build and log an error.

        FOLIO_LOG_WARNING_1 (TXT("Invalid thread identifier."),
                             threadId);
    } // Endelse.

    return (isValidThread);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
