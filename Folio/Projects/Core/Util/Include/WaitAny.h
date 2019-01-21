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

/// The wait any class.
/**
 * This class provides for simultaneous wait for at least one from a list
 * of many synchronization objects (e.g. <b>Mutex</b>, <b>Event</b>,
 * etc.) to become signaled or available.
 *
 * The <b>Wait</b> method will wait for a given time period until at least
 * one from a list of many synchronization objects is signaled.
 *
 * The <b>Wait</b> method checks the synchronization objects in the
 * order they are specified in the list (starting with index 0), until one
 * of the  synchronization objects is signaled. If multiple objects
 * become signaled, then the <b>GetSyncIndex</b> method will return the index 
 * of the first synchronization object in the list whose object was
 * signaled.
 */
class WaitAny
{
public:
    static  const   UInt32  NO_SIGNAL = 0xffffffff; ///< No signal index.

    /// Wait any synchronization list type.
    typedef std::vector<Sync*>  SyncList;

    WaitAny ();
    explicit WaitAny (SyncList& syncList);
    ~WaitAny ();

    FolioStatus Add (Sync& syncObject);
    FolioStatus Remove (Sync& syncObject);

    UInt32      GetSyncIndex () const;
    FolioHandle GetSyncHandle () const;

    FolioStatus Wait (UInt32    timeout,
                      bool      logOnInfiniteTimeout = true);

private:
    /// Synchronization handle list type.
    typedef std::vector<FolioHandle> SyncHandleList;
    mutable SyncHandleList  m_syncHandleList;   ///< The synchronization handles list.

    UInt32  m_signalIndex;  ///< Index of signaled handle (if wait satisfied).

    bool    FindSyncHandle (FolioHandle                 syncHandle,
                            SyncHandleList::iterator&   itr) const;

    /// Private copy constructor to prevent copying.
    WaitAny (const WaitAny& rhs);

    /// Private assignment operator to prevent copying.
    WaitAny& operator= (const WaitAny& rhs);
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
