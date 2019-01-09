#pragma once

// "Home-made" includes.
#include    <Base.h>
#include    "SharedName.h"
#include    "Sync.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Util
{

/// The waitable timer class.
/**
 * This class provides for a synchronization object whose state is set to 
 * signaled when a specific due time arrives and is used to notify one or more 
 * waiting threads that a waitable time has occurred. Any number of waiting 
 * threads, or threads thats ubsequently begin wait operations for the specified 
 * waitable timer object, can be released while the waitable timer's state is 
 * signaled. The synchronization object can be either named (shared 
 * cross-process) or unnamed (single process).
 *
 * This class supports a <i>Synchronization waitable timer</i> only - a waitable timer
 * object whose state remains signaled until a thread completes a wait operation on it.
 *
 * This class does not support copy construction or assignment.
 */
class WaitableTimer : public Sync
{
public:
    // Timer callback routine.
    typedef void    (FOLIO_CALL *TimerCallback) (void*  args,
                                                 UInt32 timerLowValue,
                                                 UInt32 timerHighValue);

    WaitableTimer ();
    ~WaitableTimer ();

    FolioStatus Create ();
    FolioStatus Create (const FolioString&  waitableTimerName,
                        bool                useRawName = false);

    FolioStatus Open (const FolioString&    waitableTimerName,
                      bool                  useRawName = false);

    FolioStatus Start (UInt32           timeout,
                       bool             periodic = false,
                       TimerCallback    timerCallback = 0,
                       void*            args = 0);
    FolioStatus Start (const FILETIME&   dueTime,
                       TimerCallback     timerCallback = 0,
                       void*             args = 0);
    FolioStatus Cancel ();

private:
    SharedName  m_sharedWaitableTimerName;   ///< The shared name of the waitable timer.

    /// Private copy constructor to prevent copying.
    WaitableTimer (const WaitableTimer& rhs);

    /// Private assignment operator to prevent copying.
    WaitableTimer& operator= (const WaitableTimer& rhs);

    // The stream operator is our friend.
    friend  FolioOStream&   operator<< (FolioOStream&           outputStream, 
                                        const WaitableTimer&    rhs);
}; // Endclass.

// The stream operator.
FolioOStream&   operator<< (Folio::FolioOStream&    outputStream, 
                            const WaitableTimer&    rhs);

/// The shared waitable timer name.
class SharedWaitableTimerName : public FolioString
{
public:
    SharedWaitableTimerName (const FolioString& base)
    :   FolioString(base)
    {*this += TXT("::WaitableTimer::");} // Endproc.

    ~SharedWaitableTimerName () {};
}; // Endclass.

// The stream operator.
FolioOStream&   operator<< (Folio::FolioOStream&            outputStream, 
                            const SharedWaitableTimerName&  rhs);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
