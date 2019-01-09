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

/// The mutex class.
/**
 * This class provides for a synchronization object that can be
 * owned by only one thread at a time, enabling threads to coordinate
 * mutually exclusive access to a shared resource. The synchronization
 * object can be either named (shared cross-process) or unnamed (single
 * process).
 *
 * The state of the mutex is signaled when it is not owned by any thread.
 * The creating thread can use the <i>locked</i> flag to request immediate
 * ownership of the mutex. Otherwise, a thread must use the <b>Lock</b>
 * method to request ownership or pass the <b>Mutex</b> object to an
 * <b>WaitAny</b> object. When the mutex's state is signaled, one waiting thread
 * is granted ownership, the mutex's state changes to nonsignaled, and the
 * <b>Lock</b> method returns. Only one thread can own a mutex at any given
 * time. The owning thread uses the <b>Unlock</b> method to release its
 * ownership.
 *
 * The thread that owns a mutex can specify the same mutex in repeated <b>Lock</b>
 * method calls without blocking its execution. Typically, you would not wait
 * repeatedly for the same mutex, but this mechanism prevents a thread from
 * deadlocking itself while waiting for a mutex that it already owns. However,
 * to release its ownership, the thread must call <b>Unlock</b> once for each
 * time that the mutex satisfied a wait.
 *
 * Multiple processes can have handles of the same mutex, enabling use of the
 * mutex for interprocess synchronization.
 *
 * Two or more processes can call <b>Create</b> to create the same named mutex.
 * The first process actually creates the mutex, and subsequent processes simply
 * open a handle to the existing mutex. This enables multiple processes to get
 * handles of the same mutex, while relieving the user of the responsibility of
 * ensuring that the creating process is started first. When using this
 * technique, you should set the <i>locked</i> flag to <b>false</b>; otherwise,
 * it can be difficult to be certain which process has initial ownership.
 *
 * This class does not support copy construction or assignment.
 */
class Mutex : public Sync
{
public:
    Mutex ();
    ~Mutex ();

    FolioStatus Create (bool locked = false);
    FolioStatus Create (const FolioString&  mutexName,
                        bool                locked = false,
                        bool                useRawName = false);

    FolioStatus Open (const FolioString&    mutexName,
                      bool                  useRawName = false);

    FolioStatus Lock (UInt32    timeout = FOLIO_INFINITE,
                      bool      logOnInfiniteTimeout = true);
    FolioStatus Unlock ();

private:
    SharedName  m_sharedMutexName;  ///< The shared name of the mutex.

    /// Private copy constructor to prevent copying.
    Mutex (const Mutex& rhs);

    /// Private assignment operator to prevent copying.
    Mutex& operator= (const Mutex& rhs);

    // The stream operator is our friend.
    friend  FolioOStream&   operator<< (FolioOStream&   outputStream, 
                                        const Mutex&    rhs);
}; // Endclass.

// The stream operator.
FolioOStream&   operator<< (Folio::FolioOStream&    outputStream, 
                            const Mutex&            rhs);

/// A convenience type for a <b>Mutex</b> used in a <b>ScopedLock</b>.
typedef ScopedLock<Mutex> ScopedMutex;

/// The shared mutex name.
class SharedMutexName : public FolioString
{
public:
    SharedMutexName (const FolioString& base)
    :   FolioString(base)
    {*this += TXT("::Mutex::");} // Endproc.
    
    ~SharedMutexName () {};
}; // Endclass.

// The stream operator.
FolioOStream&   operator<< (FolioOStream&           outputStream, 
                            const SharedMutexName&  rhs);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
