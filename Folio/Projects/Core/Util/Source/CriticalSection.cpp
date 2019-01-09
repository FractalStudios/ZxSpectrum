// "Home-made" includes.
#include    "CriticalSection.h"

namespace Folio
{

namespace Core
{

namespace Util
{

/**
 * The default class constructor.
 */
CriticalSection::CriticalSection ()
{
    // Initialise the critical section.

    ::InitializeCriticalSection (&(m_criticalSection));
} // Endproc.


/**
 * The class destructor. If required it will remove any OS reference to the
 * critical section from this object.
 */
CriticalSection::~CriticalSection ()
{
    // Delete the critical section.

    ::DeleteCriticalSection (&(m_criticalSection));
} // Endproc.


/**
 * Method that will lock the critical section. The method returns when
 * the calling thread is granted ownership. After a thread has ownership of
 * a critical section, it can make additional calls to <b>Lock</b> without
 * blocking its execution. A thread must call <b>Unlock</b> once for each
 * time that it locked the critical section.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus CriticalSection::Lock ()
{
    FolioStatus status = ERR_SUCCESS;

    // Enter the critical section.

    ::EnterCriticalSection (&(m_criticalSection));

    return (status);
} // Endproc.


/**
 * Method that will try the lock for the critical section. The method
 * attempts to lock a critical section without blocking. After a thread
 * has ownership of a critical section, it can make additional calls to
 * <b>TryLock</b> without blocking its execution. A thread must call
 * <b>Unlock</b> once for each time that it locked the critical section.
 *
 * If another thread has locked the critical section then <b>TryLock</b>
 * will not lock the critical section. In this case <b>ERR_ALREADY_IN_USE</b>
 * will be returned.
 *
 * If <b>TryLock</b> is called when the calling thread has previously
 * locked the critical section using <b>Lock</b> or <b>TryLock</b> then
 * <b>ERR_SUCCESS</b> will be returned.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_ALREADY_IN_USE</b> if another thread has locked the critical
 *     section.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus CriticalSection::TryLock ()
{
    FolioStatus status = ERR_SUCCESS;

    // Try to enter the critical section.

    if (!::TryEnterCriticalSection (&(m_criticalSection)))
    {
        status = ERR_ALREADY_IN_USE;
    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that will unlock the critical section.
 *
 * If a thread calls <b>Unlock</b> when it does not have ownership of the
 * critical section, then no action will be taken and <b>ERR_SUCCESS</b>
 * will be returned.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus CriticalSection::Unlock ()
{
    FolioStatus status = ERR_SUCCESS;

    // Leave the critical section.

    ::LeaveCriticalSection (&(m_criticalSection));

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/

