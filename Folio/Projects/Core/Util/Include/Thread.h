#pragma once

// "Home-made" includes.
#include    <Base.h>
#include    "Sync.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Util
{

/// The thread class.
/**
 * This class allows a user thread to start another thread of execution. It
 * also provides the capability to wait on the started thread to terminate.
 *
 * The <b>Start</b> method is used to start a thread. Any synchronization
 * that may be required between the thread that creates this object and the
 * thread started by this object (using the <b>Start</b> method) must be
 * handled by the user. This class does not provide for this synchronization;
 * particularly with regard to stopping the started thread.
 *
 * This class can only start and provide management of one thread at a time.
 * However, once a thread started by this class terminates, the <b>Start</b>
 * method can be used to start a subsequent thread. This may be a completely
 * different thread of execution or a similar thread to that started before.
 *
 * The running state of a started thread is unaltered, when an object of
 * this class is destroyed. This allows a thread to be started and remain
 * running when an object of this class has been destroyed. If this
 * functionality is not required then the started thread must be terminated
 * before the class object is destroyed. The <b>IsRunning</b> method can be
 * used to determine if a thread is running.
 *
 * The <b>Wait</b> method may be used to wait for a specified time for the
 * started thread to terminate.
 *
 * This class does not support copy construction or assignment.
 */
class Thread : public Sync
{
public:
    typedef FolioStatus (FOLIO_CALL *ThreadCallback) (void* args); ///< Thread callback routine.
    
    Thread ();
    ~Thread ();

    FolioStatus Start (ThreadCallback   threadCallback,
                       void*            threadArgs = 0);

    bool    IsRunning () const;

    UInt32      GetThreadId () const;
    FolioStatus QueryThreadExitCode (FolioStatus& exitCode) const;

    static  void    Sleep (UInt32 numMilliseconds);

private:
    UInt32  m_id;   ///< The thread identifier.

    /// The thread data structure.
    struct  ThreadData
    {
        ThreadCallback  m_threadCallback;   ///< The user defined thread callback.
        void*           m_threadArgs;       ///< The user defined thread arguments.
    }; // Endstruct.

    static  unsigned    _stdcall    ThreadProcedure (void* args);

    /// Private copy constructor to prevent copying.
    Thread (const Thread& rhs);

    /// Private assignment operator to prevent copying.
    Thread& operator= (const Thread& rhs);
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
