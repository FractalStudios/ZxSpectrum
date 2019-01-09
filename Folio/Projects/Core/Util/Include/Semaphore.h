#pragma once

// "Home-made" includes.
#include    <Base.h>
#include    "ScopedLock.h"
#include    "SharedName.h"
#include    "Sync.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Util
{

/// The semaphore class.
/**
 * This class provides for a synchronization object that maintains a
 * count between zero and some maximum value, limiting the number of
 * threads that are simultaneously accessing a shared resource.
 * The synchronization object can be either named (shared cross-process) or
 * unnamed (single process).
 *
 * The <b>Lock</b> method will return when the state of the specified object
 * is signaled. When the <b>Lock</b> method returns, the waiting thread is
 * released to continue its execution.
 *
 * The state of a semaphore is signaled when its count is greater than zero,
 * and nonsignaled when its count is equal to zero. Each time a waiting
 * thread is released because of the semaphore's signaled state, the count
 * of the semaphore is decreased by one. As a semaphore has no ownership
 * concept, any thread may use the <b>Unlock</b> method to increment a
 * semaphore's count by a specified amount. The count can never be less than
 * zero or greater than the maximum count that was specified when the
 * semaphore was created.
 *
 * Multiple processes can have handles of the same semaphore object, enabling
 * use of the object for interprocess synchronization.
 *
 * This class does not support copy construction or assignment.
 */
class Semaphore : public Sync
{
public:
    Semaphore ();
    ~Semaphore ();

    FolioStatus Create (UInt32  maxCount,
                        UInt32  initialCount = 0);
    FolioStatus Create (const FolioString&  semaphoreName,
                        UInt32              maxCount,
                        UInt32              initialCount = 0,
                        bool                useRawName = false);

    FolioStatus Open (const FolioString&    semaphoreName,
                      bool                  useRawName = false);

    FolioStatus Lock (UInt32    timeout = FOLIO_INFINITE,
                      bool      logOnInfiniteTimeout = true);
    FolioStatus Unlock (UInt32  unlockCount,
                        UInt32* previousCount = 0);
    FolioStatus Reset ();

private:
    SharedName  m_sharedSemaphoreName;  ///< The shared name of the semaphore.

    /// Private copy constructor to prevent copying.
    Semaphore (const Semaphore& rhs);

    /// Private assignment operator to prevent copying.
    Semaphore& operator= (const Semaphore& rhs);

    // The stream operator is our friend.
    friend  FolioOStream&   operator<< (FolioOStream&       outputStream, 
                                        const Semaphore&    rhs);
}; // Endclass.

// The stream operator.
FolioOStream&   operator<< (Folio::FolioOStream&    outputStream, 
                            const Semaphore&        rhs);

/// A convenience type for a <b>Semaphore</b> used in a <b>ScopedLock</b>.
typedef ScopedLock<Semaphore>   ScopedSemaphore;

/// The shared semaphore name.
class SharedSemaphoreName : public FolioString
{
public:
    SharedSemaphoreName (const FolioString& base)
    :   FolioString(base)
    {*this += TXT("::Semaphore::");} // Endproc.
    
    ~SharedSemaphoreName () {};
}; // Endclass.

// The stream operator.
FolioOStream&   operator<< (FolioOStream&               outputStream, 
                            const SharedSemaphoreName&  rhs);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
