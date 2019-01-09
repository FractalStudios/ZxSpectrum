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

/// The process loader class.
/**
 * This class allows a user thread to start another process.
 *
 * The <b>Start</b> method is used to start a process.
 *
 * This class can only start and provide management of one process at a time.
 * However, once a process started by this class terminates, the <b>Start</b>
 * method can be used to start a subsequent process. This may be a completely
 * different process or a similar process to that started before.
 *
 * The running state of a started process is unaltered, when an object of
 * this class is destroyed. This allows a process to be started and remain
 * running when an object of this class has been destroyed. If this
 * functionality is not required then the started process must be terminated
 * before the class object is destroyed. The <b>IsRunning</b> method can be
 * used to determine if a process is running.
 *
 * The <b>Wait</b> method may be used to wait for a specified time for the
 * started process to terminate.
 *
 * This class does not support copy construction or assignment.
 */
class ProcessLoader : public Sync
{
public:
    ProcessLoader ();
    ~ProcessLoader ();

    FolioStatus Start (const FolioString&   processName,
                       const FolioString&   commandLine,
                       UInt32               creationFlags);

    bool    IsRunning () const;

    UInt32      GetProcessId () const;
    FolioStatus QueryProcessExitCode (UInt32& exitCode) const;

private:
    UInt32  m_id;   ///< The process identifier.

    /// Private copy constructor to prevent copying.
    ProcessLoader (const ProcessLoader& rhs);

    /// Private assignment operator to prevent copying.
    ProcessLoader& operator= (const ProcessLoader& rhs);
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
