#pragma once

// STL includes
#include    <memory>

// "Home-made" includes.
#include    "Mutex.h"
#include    "SharedMemory.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Util
{

/// The shared atom template class.
/**
 * This class provides a simple template wrapper for atomic access to an item
 * in shared memory.
 *
 * This class does not support copy construction or assignment.
 */
template <typename T>
class SharedAtom : public Mutex
{
public:
    /// Type definition for a constant reference to type T.
    typedef const T&    const_reference;
    /// Type definition for a reference to type T.
    typedef       T&    reference;

    // Construct and destroy.
    SharedAtom (const FolioString&  sharedMemoryName,
                reference           object);
    virtual ~SharedAtom ();

    // Accessors.
    void        Set (reference object);
    reference   Get ();

    // Overloaded operator* provides unlocked access.
    const_reference operator* () const;

    // Overloaded operator* provides unlocked access.
    reference       operator* ();

    // Overloaded operator-> provides locked access.
    std::tr1::shared_ptr<T> operator-> ();

private:
    T*  m_atom; ///< The atom.

    SharedMemory    m_sharedMemory; ///< The shared memory of the atom.

    /// Scope lock type for the shared atom.
    typedef ScopedMutex AccessSharedAtomScopeLock;

    void    Initialise (const FolioString&  sharedMemoryName,
                        reference           object);
    void    Terminate ();

    /// Private functor class used to release a lock on a shared atom.
    class Unlocker
    {
    public:
        /**
         * Construct from a <b>SharedAtom</b> object - we need to call
         * <b>Unlock</b> on a specific instance.
         */
        explicit Unlocker (SharedAtom<T>* thisPtr)
        : m_this(thisPtr)
        {} // Endproc.

        /**
         * Operator () will be called from shared_ptr destructor, causing the
         * lock to be released.
         */
        void    operator() (void const *) const
        {
            m_this->Unlock ();
        } // Endproc.

    private:
        SharedAtom<T>*  m_this; ///< The shared atom object to be unlocked.
    }; // Endclass.

    /// Private copy constructor to prevent copying.
    SharedAtom (const SharedAtom<T>& rhs);

    /// Private assignment operator to prevent copying.
    SharedAtom& operator= (const SharedAtom<T>& rhs);
}; // Endclass.

/// A convenience type for a <b>SharedAtom</b> used in a <b>ScopedLock</b>.
typedef ScopedMutex ScopedSharedAtom;


/**
 * The class constructor. Place a copy of an object instance of type T in
 * a shared memory object.
 *
 * @param [in] sharedMemoryName
 * The name of the shared memory.
 *
 * @param [in] object
 * The object instance to be copied into shared memory.
 */
template <typename T>
inline  SharedAtom<T>::SharedAtom (const FolioString&   sharedMemoryName,
                                   reference            object)
:   m_atom(0)
{
    Initialise (sharedMemoryName, object);
} // Endproc.


/**
 * The class destructor. Closes the reference to the shared memory object.
 */
template <typename T>
inline  SharedAtom<T>::~SharedAtom ()
{
    Terminate ();
} // Endproc.


/**
 * Method that will set the shared atom to a new value. This method
 * must be called under lock conditions.
 *
 * @param [in] object
 * The new object instance to be copied into shared memory.
 */
template <typename T>
inline  void    SharedAtom<T>::Set (reference object)
{
    *m_atom = object;
} // Endproc.


/**
 * Method that will get the shared atom. This method must be called under
 * lock conditions.
 *
 * @return
 * The object instance of the shared atom.
 */
template <typename T>
inline  typename SharedAtom<T>::reference   SharedAtom<T>::Get ()
{
    return (*m_atom);
} // Endproc.


/**
 * Method that initialise the shared atom.
 *
 * @param [in] sharedMemoryName
 * The name of the shared memory.
 *
 * @param [in] object
 * The object instance to be copied into shared memory.
 */
template <typename T>
inline  void    SharedAtom<T>::Initialise (const FolioString&   sharedMemoryName,
                                            reference           object)
{
    // Create the shared atom access mutex (unowned).

    SharedMutexName mutexName(sharedMemoryName);
    mutexName += TXT("AccessSharedAtom");

    FolioStatus status = Create (mutexName.c_str ());

    if ((status == ERR_SUCCESS) ||
        (status == ERR_ALREADY_EXISTS))
    {
        // Make sure we own the shared atom.

        AccessSharedAtomScopeLock   ScopeLocker(*this);

        // Create the shared memory for the atom

        status = m_sharedMemory.Create (sharedMemoryName,
                                        sizeof (object));

        if ((status == ERR_SUCCESS) ||
            (status == ERR_ALREADY_EXISTS))
        {
            // Note the pointer to the atom.

            m_atom = reinterpret_cast<typename T*> (m_sharedMemory.GetBaseAddress ());

            // If we have just created the atom, then set it.

            if (status == ERR_SUCCESS)
            {
                // Set the atom.

                Set (object);
            } // Endif.

        } // Endif.

    } // Endif.

} // Endproc.


/**
 * Method that terminate the shared atom.
 */
template <typename T>
inline  void    SharedAtom<T>::Terminate ()
{
    // Make sure we own the shared atom.

    AccessSharedAtomScopeLock ScopeLocker(*this);

    // Did we create the shared memory atom?

    if (m_atom)
    {
        // Yes. Close the shared memory for the atom.

        m_sharedMemory.Close ();
    } // Endif.

} // Endproc.


/**
 * Method that provides unlocked access to the methods or member
 * data of the shared atom.
 *
 * @return
 * A reference to the underlying shared atom data..
 */
template <typename T>
inline  typename SharedAtom<T>::const_reference SharedAtom<T>::operator* () const
{
    return (*m_atom);
} // Endproc.


/**
 * Method that provides unlocked access to the methods or member
 * data of the shared atom.
 *
 * @return
 * A reference to the underlying shared atom data..
 */
template <typename T>
inline  typename SharedAtom<T>::reference   SharedAtom<T>::operator* ()
{
    return (*m_atom);
} // Endproc.


/**
 * Method that provides locked access to the methods or member data of the
 * shared atom.
 *
 * @return
 * A shared_ptr to the underlying shared atom data that unlocks the shared
 * atom on destruction.
 */
template <typename T>
inline  std::tr1::shared_ptr<T> SharedAtom<T>::operator-> ()
{
    std::tr1::shared_ptr<T> pObj;

    // Gain access to the shared atom.

    if (Lock () == ERR_SUCCESS)
    {
        // Instantiate an <b>Unlocker</b> instance that will release our lock.

        Unlocker    unlocker(this);

        // Build a custom shared_ptr that will release our lock when it
        // is destroyed.

        pObj = std::tr1::shared_ptr<T>(m_atom, unlocker);
    } // Endif.

    // Don't release the lock.

    return (pObj);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
