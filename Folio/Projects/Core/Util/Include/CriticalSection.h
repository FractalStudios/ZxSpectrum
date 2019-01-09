#pragma once

// Windows includes.
#include    <Windows.h>

// "Home-made" includes.
#include    <Base.h>
#include    "ScopedLock.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Util
{

/// The critical section class.
/**
 * This class provides for a synchronization object similar to that provided
 * by a mutex object, except that a critical section can be used only by the
 * threads of a single process. Therefore a named critical section has no
 * relevance and is not supported.
 *
 * The <b>Wait</b> method is not supported by a critical section and it is not
 * possible to specify a wait time period when requesting ownership of a
 * critical section. A critical section object cannot be specified when using
 * <b>WaitAny</b>.
 *
 * After a thread has ownership of a critical section, it can make additional
 * calls to <b>Lock</b> or <b>TryLock</b> without blocking its execution. The
 * thread enters the critical section each time <b>Lock</b> or <b>TryLock</b>
 * succeed. A thread must call <b>Unlock</b> once for each time that it locked
 * the critical section.
 *
 * This class does not support copy construction or assignment.
 */
class CriticalSection
{
public:
    CriticalSection ();
    ~CriticalSection ();

    FolioStatus Lock ();
    FolioStatus TryLock ();
    FolioStatus Unlock ();

private:
    CRITICAL_SECTION    m_criticalSection;  ///< The critical section.

    /// Private copy constructor to prevent copying.
    CriticalSection (const CriticalSection& rhs);

    /// Private assignment operator to prevent copying.
    CriticalSection& operator= (const CriticalSection& rhs);
}; // Endclass.

// A convenience type for a <b>CriticalSection</b> used in a <b>ScopedLock</b>.
typedef ScopedLock<CriticalSection> ScopedCriticalSection;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
