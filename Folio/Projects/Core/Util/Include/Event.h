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

/// The event class.
/**
 * This class provides for a synchronization object that can be explicitly
 * set to signaled and is used to notify one or more waiting threads that
 * an event has occurred. Any number of waiting threads, or threads that
 * subsequently begin wait operations for the specified event object, can
 * be released while the event's state is signaled. The synchronization
 * object can be either named (shared cross-process) or unnamed (single
 * process).
 *
 * This class supports a <i>Manual-reset event</i> only - an event
 * object whose state remains signaled until it is explicitly reset to
 * nonsignaled by the <b>Reset</b> method. While it is signaled, any number
 * of waiting (or subsequently waiting) threads can be released.
 *
 * This class does not support copy construction or assignment.
 */
class Event : public Sync
{
public:
    Event ();
    ~Event ();

    FolioStatus Create (bool signaled = false);
    FolioStatus Create (const FolioString&  eventName,
                        bool                signaled = false,
                        bool                useRawName = false);

    FolioStatus Open (const FolioString&    eventName,
                      bool                  useRawName = false);

    FolioStatus Set ();
    FolioStatus Reset ();

private:
    SharedName  m_sharedEventName;   ///< The shared name of the event.

    /// Private copy constructor to prevent copying.
    Event (const Event& rhs);

    /// Private assignment operator to prevent copying.
    Event& operator= (const Event& rhs);

    // The stream operator is our friend.
    friend  FolioOStream&   operator<< (FolioOStream&   outputStream, 
                                        const Event&    rhs);
}; // Endclass.

// The stream operator.
FolioOStream&   operator<< (Folio::FolioOStream&    outputStream, 
                            const Event&            rhs);

/// The shared event name.
class SharedEventName : public FolioString
{
public:
    SharedEventName (const FolioString& base)
    :   FolioString(base)
    {*this += TXT("::Event::");} // Endproc.

    ~SharedEventName () {};
}; // Endclass.

// The stream operator.
FolioOStream&   operator<< (Folio::FolioOStream&    outputStream, 
                            const SharedEventName&  rhs);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
