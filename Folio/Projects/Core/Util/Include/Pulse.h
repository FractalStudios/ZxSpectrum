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

/// The pulse class.
/**
 * This class provides for a synchronization object that can be explicitly
 * set to signaled and is used to notify one (and only one) of any waiting
 * threads that a pulse has occurred, at which time the pulse object is
 * automatically set to nonsignaled. Only one waiting thread (of many), that
 * subsequently begin wait operations for the specified pulse object, can
 * be released while the pulse's state is signaled at which time the state
 * is automatically reset to nonsignaled. The synchronization object can only
 * be unnamed (single process).
 *
 * This class supports an <i>Auto-reset event</i> only - an event object
 * whose state remains signaled until a single waiting thread is released,
 * at which time is is set to nonsignaled. If no threads are waiting, the
 * object's state remains signaled. If more than one thread is waiting, a
 * waiting thread is selected.
 *
 * This class does not support copy construction or assignment.
 */
class Pulse : public Sync
{
public:
    Pulse ();
    ~Pulse ();

    FolioStatus Create (bool signaled = false);

    FolioStatus Set ();

private:
    /// Private copy constructor to prevent copying.
    Pulse (const Pulse& rhs);

    /// Private assignment operator to prevent copying.
    Pulse& operator= (const Pulse& rhs);

    // The stream operator is our friend.
    friend  FolioOStream&   operator<< (FolioOStream&   outputStream, 
                                        const Pulse&    rhs);
}; // Endclass.

// The stream operator.
FolioOStream&   operator<< (Folio::FolioOStream&    outputStream, 
                            const Pulse&            rhs);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
