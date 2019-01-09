#pragma once

// C includes.
#include    <stdlib.h>

// "Home-made" includes.
#include    "CriticalSection.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Util
{

/// The process singleton class.
/**
 * This class provides a template implementation that can be used to wrap
 * any standard (non-singleton) class to provide a singleton implementation
 * based upon the wrapped class.
 *
 * The singleton object is reference counted and will be created when the first
 * reference is taken through <b>GetInstance</b> and deleted when the last
 * reference is returned through <b>ReleaseInstance</b>.
 *
 * The singleton object will be cleaned up on process exit regardless of any
 * remaining references at that time.
 *
 * This class does not support copy construction or assignment.
 */
template <typename T>
class ProcessSingleton
{
public:
    static  T*  GetInstance ();
    void        ReleaseInstance ();

    CriticalSection&    GetLocker ();

protected:
    ProcessSingleton ();
    virtual ~ProcessSingleton ();

private:
    /// The singleton holder class.
    /**
     * The <b>SingletonHolder</b> class is used to ensure that the singleton 
     * object is safely destroyed at program exit and to manage locking and 
     * reference counting.
     */
    class SingletonHolder
    {
    public:
        SingletonHolder ();
        ~SingletonHolder ();

        T*      GetInstance ();
        void    ReleaseInstance ();
        void    DeleteSingleton ();

    private:
        friend class ProcessSingleton<T>;

        CriticalSection  m_singletonLock;       ///< The singleton lock.
        T*               m_singletonInstance;   ///< The singleton instance.
        UInt32           m_usageCount;          ///< Usage count to the singleton instance.

        void    Lock ();
        void    Unlock ();
    }; // Endclass.

    static  SingletonHolder s_singletonHolder;  ///< The singleton holder instance for this process.

    // These methods allow the <b>SingletonHolder</b> to delegate the new and 
    // delete calls for type T to the enclosing/base singleton class.

    static  T*      ProxyNew ();
    static  void    ProxyDelete (T* singletonInstance);
    static  void    _cdecl  AtExitHook ();

    /// Private copy constructor to prevent copying.
    ProcessSingleton (const ProcessSingleton& rhs);

    /// Private assignment operator to prevent copying.
    ProcessSingleton& operator= (const ProcessSingleton& rhs);
}; // Endclass.

/// A convenience type for a <b>ProcessSingleton</b> used in a <b>ScopedLock</b>.
typedef ScopedCriticalSection   ScopedProcessSingleton;

/// The singleton static members.
template <typename T>
typename ProcessSingleton<T>::SingletonHolder  ProcessSingleton<T>::s_singletonHolder;


/**
 * This method returns a pointer to the single object instance of the templated
 * type T for this process. The reference count is incremented and the single 
 * object instance is created if it does not yet exist.
 *
 * @return
 * A pointer to a process singleton of type T.
 */
template <typename T>
T*  ProcessSingleton<T>::GetInstance ()
{
    return (s_singletonHolder.GetInstance ());
} // Endproc.


/**
 * This method releases the reference count held by a client that previously 
 * made a call to <b>GetInstance</b>. The single process instance may be 
 * destroyed if this is the last reference held to the singleton.
 */
template <typename T>
void    ProcessSingleton<T>::ReleaseInstance ()
{
    s_singletonHolder.ReleaseInstance ();
} // Endproc.


/**
 * This method get the process singleton locker.
 */
template <typename T>
CriticalSection&    ProcessSingleton<T>::GetLocker ()
{
    return (s_singletonHolder.m_singletonLock);
} // Endproc.


/**
 * The default constructor can only be called from specializations of this 
 * class to prevent direct instantiation.
 */
template <typename T>
inline  ProcessSingleton<T>::ProcessSingleton ()
{
} // Endproc.


/**
 * The destructor can only be called from specialisations of this class to 
 * prevent direct destruction.
 */
template <typename T>
inline  ProcessSingleton<T>::~ProcessSingleton ()
{
} // Endproc.


/**
 * This method will create the singleton instance. It provides a method in the
 * <b>ProcessSingleton</b> class that can be called by the
 * <b>SingletonHolder</b> class.
 *
 * @return
 * A pointer to an object of type T.
 */
template <typename T>
T*  ProcessSingleton<T>::ProxyNew ()
{
    return (new T);
} // Endproc.


/**
 * This method will destroy the singleton instance. It provides a method in the
 * <b>ProcessSingleton</b> class that can be called by the
 * <b>SingletonHolder</b> class.
 *
 * @param [in] singletonInstance
 * The object to be deleted.
 */
template <typename T>
void    ProcessSingleton<T>::ProxyDelete (T* singletonInstance)
{
    delete singletonInstance;
} // Endproc.


/**
 * This method is called at exit to clean up the singleton instance.
 */
template <typename T>
void    _cdecl  ProcessSingleton<T>::AtExitHook ()
{
    s_singletonHolder.DeleteSingleton ();
} // Endproc.


/**
 * The constructor initialises the reference count to zero and singleton
 * instance pointer to zero.
 */
template <typename T>
ProcessSingleton<T>::SingletonHolder::SingletonHolder ()
:   m_singletonInstance(0),
    m_usageCount(0)
{
} // Endproc.


/**
 * The class destructor.
 */
template <typename T>
ProcessSingleton<T>::SingletonHolder::~SingletonHolder ()
{
} // Endproc.


/**
 * This method returns a pointer to the single object instance of the
 * templated type T for this process. The reference count is incremented
 * and the single object instance is created if it does not yet exist.
 *
 * @return
 * A pointer to a process singleton of type T.
 */
template <typename T>
T*  ProcessSingleton<T>::SingletonHolder::GetInstance ()
{
    // Get exclusive access to the singleton lock.

    Lock ();

    // See if the singleton already exists for this process.

    if (m_singletonInstance == 0)
    {
        // No, so create it.

        m_singletonInstance = ProcessSingleton<T>::ProxyNew ();

        // Register the singleton "atexit" function to destroy on
        // program exit.

        ::atexit (ProcessSingleton<T>::AtExitHook);
    } // Endif.

    // If the singleton exists, increment its usage count.

    if (m_singletonInstance)
    {
        ++m_usageCount;
    } // Endif.

    // Release exclusive access to the singleton lock.

    Unlock ();

    return (m_singletonInstance);
} // Endproc.


/**
 * This static method releases the reference count held by a client that 
 * previously made a call to <b>GetInstance</b>. The single process instance 
 * may be destroyed if this is the last reference held to the singleton.
 */
template <typename T>
void    ProcessSingleton<T>::SingletonHolder::ReleaseInstance ()
{
    // Get exclusive access to the singleton lock.

    Lock ();

    // Delete this object if there are no more users.

    if (--m_usageCount == 0)
    {
        ProcessSingleton<T>::ProxyDelete (m_singletonInstance);

        m_singletonInstance = 0;
    } // Endif.

    // Release exclusive access to the singleton lock.

    Unlock ();
} // Endproc.


/**
 * Delete the singleton object under lock conditions.
 */
template <typename T>
void    ProcessSingleton<T>::SingletonHolder::DeleteSingleton ()
{
    // Get exclusive access to the singleton lock.

    Lock ();

    ProcessSingleton<T>::ProxyDelete (m_singletonInstance);
    m_singletonInstance = 0;

    // Release exclusive access to the singleton lock.

    Unlock ();
} // Endproc.


/**
 * This method locks the process singleton.
 */
template <typename T>
void    ProcessSingleton<T>::SingletonHolder::Lock ()
{
    // Get exclusive access to the singleton lock.

    m_singletonLock.Lock ();
} // Endproc.


/**
 * This method unlocks the process singleton.
 */
template <typename T>
void    ProcessSingleton<T>::SingletonHolder::Unlock ()
{
    // Release exclusive access to the singleton lock.

    m_singletonLock.Unlock ();
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
