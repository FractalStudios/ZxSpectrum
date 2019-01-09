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

/// The scoped lock template class.
/**
 * This class provides a simple template wrapper for synchronization objects
 * that use methods <b>Lock</b> and <b>Unlock</b> to provide synchronization.
 * The lock is held for the lifetime of this object, which should be
 * instantiated on the stack within a C++ code scope that matches the desired
 * lock lifetime.
 *
 * This class can be used to ensure that a lock is always unlocked when the lock
 * scope is exited, even in the case of an exception condition.
 *
 * This class does not support copy construction or assignment.
 */
template <typename T>
class ScopedLock
{
public:
    /**
     * The constructor calls the specified type <b>T::Lock</b> to
     * perform a lock that is scoped to the life of the <b>ScopedLock</b>
     * object.
     *
     * @param [in] lockObject
     * The object to be used as a scope based lock. The object must provide
     * <b>Lock</b> and <b>Unlock</b> methods.
     */
    explicit ScopedLock (T& lockObject) : m_lockObject(lockObject)
    {
        m_lockObject.Lock ();
    } // Endproc.

    /**
     * The destructor calls the specified type <b>T::Unlock</b> to
     * unlock a lock that is scoped to the life of the <b>ScopedLock</b>
     * object.
     */
    virtual ~ScopedLock ()
    {
        m_lockObject.Unlock ();
    } // Endproc.

private:
    T&  m_lockObject; ///< The wrapped (protected) locking object.

    // Private copy constructor to prevent copying.
    ScopedLock (const ScopedLock& rhs);

    // Private assignment operator to prevent copying.
    ScopedLock& operator= (const ScopedLock& rhs);
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
