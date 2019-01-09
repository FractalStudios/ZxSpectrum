#pragma once

// "Home-made" includes.
#include    <Base.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Util
{

/// The synchronization class.
/**
 * This abstract class provides the encapsulation of any fundamental
 * attribute associated with a synchronization object.
 *
 * This class does not support copy construction or assignment.
 */
class Sync
{
public:
    virtual ~Sync ();

    FolioHandle GetSyncHandle () const;

    FolioStatus Wait (UInt32    timeout,
                      bool      logOnInfiniteTimeout = true);

protected:
    Sync ();    // No direct construction.

    FolioStatus Close ();

    FolioHandle m_syncHandle;   ///< The synchronization handle.

private:
    /// Private copy constructor to prevent copying.
    Sync (const Sync& rhs);

    /// Private assignment operator to prevent copying.
    Sync& operator= (const Sync& rhs);
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
