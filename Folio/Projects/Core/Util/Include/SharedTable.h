#pragma once

// STL includes
#include    <memory>

// "Home-made" includes.
#include    "Mutex.h"
#include    "SharedMemory.h"

#pragma pack(push, 1)

#pragma warning(push)
#pragma warning(disable : 4996)

namespace Folio
{

namespace Core
{

namespace Util
{

/// The shared table template class.
/**
 * This class provides a simple template wrapper for access to a table
 * in shared memory.
 *
 * This class does not support copy construction or assignment.
 */
template <typename T>
class SharedTable : public Mutex
{
public:
    /// Type definition for a constant reference to type T.
    typedef const T&    const_reference;
    /// Type definition for a reference to type T.
    typedef       T&    reference;
    /// Type definition for a constant interator to type T.
    typedef const T*    const_iterator;
    /// Type definition for an interator to type T.
    typedef       T*    iterator;

    /// Type definition for a constant reverse interator to type T.
    typedef typename std::reverse_iterator<const T*>    const_reverse_iterator;
    /// Type definition for a reverse interator to type T.
    typedef typename std::reverse_iterator<T*>          reverse_iterator;

    /// Type definition for size types used in the <b>SharedTable</b> interface.
    typedef UInt32  size_type;

    // Construct and destroy.
    SharedTable (const FolioString& sharedMemoryName, 
                 size_type          size);
    virtual ~SharedTable ();

    // Forward iterators.
    iterator        begin ();
    const_iterator  begin () const;
    iterator        end ();
    const_iterator  end () const;

    // Reverse iterators.
    reverse_iterator        rbegin ();
    const_reverse_iterator  rbegin () const;
    reverse_iterator        rend ();
    const_reverse_iterator  rend () const;

    // Entry access.
    reference       front ();
    const_reference front () const;
    reference       back ();
    const_reference back () const;

    reference       at (size_type pos);
    const_reference at (size_type pos) const;
    reference       operator [] (size_type pos);
    const_reference operator [] (size_type pos) const;

    // Sizes.
    size_type   size () const;
    size_type   max_size () const;
    size_type   capacity () const;
    bool        empty () const;
    bool        full () const;

    // Modifiers.
    iterator    insert (iterator    whereFrom,
                        const T&    value);
    void        insert (iterator    whereFrom,
                        size_type   count,
                        const T&    value);
    void        insert (iterator        whereFrom,
                        const_iterator  first,
                        const_iterator  last);
    iterator    erase (iterator whereFrom);
    iterator    erase (iterator first,
                       iterator last);
    void        assign (size_type   count,
                        const T&    value);
    void        assign (const_iterator  first,
                        const_iterator  last);

    void        pop_back ();
    void        push_back (const T& value);
    void        clear ();

private:
    /// The shared table structure.
    struct  SharedTableStruct
    {
        size_type   m_maxNumEntries;        ///< Maximum number of table entries.
        size_type   m_currentNumEntries;    ///< Current number of table entries.
        T           m_entry [1];            ///< Entry.
    }; // Endstruct.

    SharedTableStruct*  m_table;       ///< The shared table.
    SharedMemory        m_sharedMemory; ///< The shared memory of the table.

    /// Scope lock type for the shared table.
    typedef ScopedMutex AccessSharedTableScopeLock;

    void    Initialise (const FolioString&  sharedMemoryName, 
                        size_type           size);
    void    Terminate ();

    void        Destroy (iterator   first,
                         iterator   last);
    iterator    UCopy (const_iterator   first,
                       const_iterator   last,
                       iterator         whereFrom);
    void        UFill (iterator     first,
                       size_type    count,
                       const T&     value);

    /// Private copy constructor to prevent copying.
    SharedTable (const SharedTable<T>& rhs);

    /// Private assignment operator to prevent copying.
    SharedTable& operator= (const SharedTable<T>& rhs);
}; // Endclass.

/// A convenience type for a <b>SharedTable</b> used in a <b>ScopedLock</b>.
typedef ScopedMutex ScopedSharedTable;


/**
 * The constructor places a copy of an array of type T in a shared memory
 * object.
 *
 * @param [in] sharedMemoryName
 * The name of the shared memory.
 *
 * @param [in] size
 * The number of array elements to be placed in shared memory.
 */
template <typename T>
inline  SharedTable<T>::SharedTable (const FolioString& sharedMemoryName, 
                                     size_type          size)
:   m_table(0)
{
    Initialise (sharedMemoryName, size);
} // Endproc.


/**
 * The destructor closes the reference to the shared memory object.
 */
template <typename T>
inline  SharedTable<T>::~SharedTable ()
{
    Terminate ();
} // Endproc.


/**
 * Returns an iterator referring to the first element in the shared table.
 *
 * @return
 * An iterator referring to the first element in the shared table.
 */
template <typename T>
inline  typename SharedTable<T>::iterator   SharedTable<T>::begin ()
{
    return (&(m_table->m_entry [0]));
} // Endproc.


/**
 * Returns a const iterator referring to the first element in the shared
 * table.
 *
 * @return
 * A const iterator referring to the first element in the shared table.
 */
template <typename T>
inline  typename SharedTable<T>::const_iterator SharedTable<T>::begin () const
{
    return (static_cast<const_iterator> (&(m_table->m_entry [0])));
} // Endproc.


/**
 * Returns an iterator referring to the last element in the shared table.
 *
 * @return
 * An iterator referring to just beyond the last element in the shared table.
 */
template <typename T>
inline  typename SharedTable<T>::iterator   SharedTable<T>::end ()
{
    return (&(m_table->m_entry [m_table->m_currentNumEntries]));
} // Endproc.


/**
 * Returns a const iterator referring to the last element in the shared table.
 *
 * @return
 * A const iterator referring to just beyond the last element in the shared
 * table.
 */
template <typename T>
inline  typename SharedTable<T>::const_iterator SharedTable<T>::end () const
{
    return (static_cast<const_iterator> (&(m_table->m_entry [m_table->m_currentNumEntries])));
} // Endproc.


/**
 * Returns a reverse iterator referring to the first element in the shared
 * table.
 *
 * @return
 * A reverse iterator referring to the first element in the shared table.
 */
template <typename T>
inline  typename SharedTable<T>::reverse_iterator   SharedTable<T>::rbegin ()
{
    return (reverse_iterator (end ()));
} // Endproc.


/**
 * Returns a const reverse iterator referring to the first element in the
 * shared table.
 *
 * @return
 * A const reverse iterator referring to the first element in the shared
 * table.
 */
template <typename T>
inline  typename SharedTable<T>::const_reverse_iterator SharedTable<T>::rbegin () const
{
    return (const_reverse_iterator (end ()));
} // Endproc.


/**
 * Returns a reverse iterator referring to the last element in the shared
 * table.
 *
 * @return
 * A reverse iterator referring to the last element in the shared table.
 */
template <typename T>
inline  typename SharedTable<T>::reverse_iterator   SharedTable<T>::rend ()
{
    return (reverse_iterator (begin ()));
} // Endproc.


/**
 * Returns a const reverse iterator referring to the last element in the
 * shared table.
 *
 * @return
 * A const reverse iterator referring to the last element in the shared
 * table.
 */
template <typename T>
inline  typename SharedTable<T>::const_reverse_iterator SharedTable<T>::rend () const
{
    return (const_reverse_iterator (begin ()));
} // Endproc.


/**
 * Returns a reference to the first element in the shared table.
 *
 * @return
 * A reference to the first element in the shared table.
 */
template <typename T>
inline  typename SharedTable<T>::reference  SharedTable<T>::front ()
{
    return (*begin ());
} // Endproc.


/**
 * Returns a const reference to the first element in the shared table.
 *
 * @return
 * A const reference to the first element in the shared table.
 */
template <typename T>
inline  typename SharedTable<T>::const_reference    SharedTable<T>::front () const
{
    return (*begin ());
} // Endproc.


/**
 * Returns a reference to the last element in the shared table.
 *
 * @return
 * A reference to the last element in the shared table.
 */
template <typename T>
inline  typename SharedTable<T>::reference  SharedTable<T>::back ()
{
    return (*(end () - 1));
} // Endproc.


/**
 * Returns a const reference to the last element in the shared table.
 *
 * @return
 * A const reference to the last element in the shared table.
 */
template <typename T>
inline  typename SharedTable<T>::const_reference    SharedTable<T>::back () const
{
    return (*(end () - 1));
} // Endproc.


/**
 * Returns a reference to the element in the shared table at an index.
 *
 * @param [in] pos
 * The index in the table of the element to return. If the index is not in
 * the range [0, size) then it defaults to zero.
 *
 * @return
 * A reference to the element in the shared table at index pos.
 */
template <typename T>
inline  typename SharedTable<T>::reference   SharedTable<T>::at (size_type pos)
{
    // Make sure that the position is in range.

    if (pos < size ())
        return (*(begin () + pos));

    return (*begin ());  // Undefined.
} // Endproc.


/**
 * Returns a const reference to the element in the shared table at an index.
 *
 * @param [in] pos
 * The index in the table of the element to return. If the index is not in the
 * range [0, size) then it defaults to zero.
 *
 * @return
 * A const reference to the element in the shared table at index pos.
 */
template <typename T>
inline  typename SharedTable<T>::const_reference  SharedTable<T>::at (size_type pos) const
{
    // Make sure that the position is in range.

    if (pos < size ())
        return (*(begin () + pos));

    return (*begin ());  // Undefined.
} // Endproc.


/**
 * Returns a reference to the element in the shared table at an index.
 *
 * @param [in] pos
 * The index in the table of the element to return. The index must be in the
 * range [0, size) where size is the object constructor parameter.
 *
 * @return
 * A reference to the element in the shared table at index pos.
 */
template <typename T>
inline  typename SharedTable<T>::reference   SharedTable<T>::operator [] (size_type pos)
{
    return (*(begin () + pos));
} // Endproc.


/**
 * Returns a const reference to the element in the shared table at an index.
 *
 * @param [in] pos
 * The index in the table of the element to return. The index must be in the
 * range [0, size) where size is the object constructor parameter.
 *
 * @return
 * A const ference to the element in the shared table at index pos.
 */
template <typename T>
inline  typename SharedTable<T>::const_reference  SharedTable<T>::operator [] (size_type pos) const
{
    return (*(begin () + pos));
} // Endproc.


/**
 * Query the current number of elements stored in the shared table.
 *
 * @return
 * The number of elements in the shared table. This is the number of actual
 * elements held in the shared table, which is not necessarily equal to its
 * storage capacity. To retrieve the current storage capacity of the shared
 * table you can call its member capacity.
 */
template <typename T>
inline  typename SharedTable<T>::size_type  SharedTable<T>::size () const
{
    // Return the number of entries.

    return (end () - begin ());
} // Endproc.


/**
 * Query the mamimum number of elements that can be stored in the shared table.
 *
 * @return
 * The maximum number of elements that the shared table can hold. This is the
 * maximum potential size the shared table could reach.
 */
template <typename T>
inline  typename SharedTable<T>::size_type  SharedTable<T>::max_size () const
{
    // Return the maximum number of entries.

    return (m_table->m_maxNumEntries);
} // Endproc.


/**
 * Query the current number of elements that can be stored in the memory
 * allocated for the shared table.
 *
 * @return
 * The size of the allocated storage space for the elements of the shared
 * table. In the case of the shared table capacity is the same as max_size
 * always.
 */
template <typename T>
inline  typename SharedTable<T>::size_type  SharedTable<T>::capacity () const
{
    return (max_size ());   // Always.
} // Endproc.


/**
 * Tests whether the shared table is empty, i.e. whether its size is zero.
 *
 * This method does not modify the content of the shared table in any way.
 * To clear the content of a shared table, use the clear method.
 *
 * @return
 * <b>true</b> if the table is empty, <b>false</b> otherwise.
 */
template <typename T>
inline  bool    SharedTable<T>::empty () const
{
    return (size () == 0);
} // Endproc.


/**
 * Tests whether the shared table is full, i.e. whether its size is max_size.
 *
 * @return
 * <b>true</b> if the table is full, <b>false</b> otherwise.
 */
template <typename T>
inline  bool    SharedTable<T>::full () const
{
    return (size () == max_size ());
} // Endproc.


/**
 * The shared table is extended by inserting a new element value before the
 * element at whereFrom. This effectively increases the shared table size
 *
 * Returns an iterator referring to the newly inserted element.
 *
 * Because the shared table keeps an array format, insertions on positions
 * other than the shared table end are performed by moving all the elements
 * between whereFrom and the end of the shared table to their new positions,
 * and then inserting the new element(s), which is not efficient.
 *
 * @param [in] whereFrom
 * An iterator to the insertion point.
 *
 * @param [in] value
 * The object to be inserted.
 *
 * @return
 * An iterator to the newly inserted object.
 */
template <typename T>
inline  typename SharedTable<T>::iterator   SharedTable<T>::insert (iterator    whereFrom,
                                                                    const T&    value)
{
    size_type   pos = whereFrom - begin ();

    insert (whereFrom, 1, value);

    return (begin () + pos);
} // Endproc.


/**
 * The shared table is extended by inserting count copies of a new element
 * value before the element at whereFrom. This effectively increases the shared
 * table size.
 *
 * Because the shared table keeps an array format, insertions on positions
 * other than the shared table end are performed by moving all the elements
 * between whereFrom and the end of the shared table to their new positions,
 * and then inserting the new element(s), which is not efficient.
 *
 * @param [in] whereFrom
 * An iterator to the insertion point.
 *
 * @param [in] count
 * The number of object copies to be inserted in the table.
 *
 * @param [in] value
 * The object to be inserted.
 */
template <typename T>
inline  void    SharedTable<T>::insert (iterator    whereFrom,
                                        size_type   count,
                                        const T&    value)
{
    if (!full ())
    {
        count = min((capacity () - m_table->m_currentNumEntries), count);

        if (empty ())
        {
            UFill (&(m_table->m_entry [0]), count, value);

            m_table->m_currentNumEntries += count; // More entries.
        } // Endif.

        else
        {
            iterator    end = end ();

            if ((size_type) (end - whereFrom) < count)
            {
                UCopy (whereFrom, end, whereFrom + count);
                UFill (end, count - (end - whereFrom), value);
                std::fill (whereFrom, end, value);

                m_table->m_currentNumEntries += count; // More entries.
            } // Endif.

            else
            if (0 < count)
            {
                UCopy (end - count, end, end);
                std::copy_backward (whereFrom, end - count, end);
                std::fill (whereFrom, whereFrom + count, value);

                m_table->m_currentNumEntries += count; // More entries.
            } // Endif.

        } // Endif.

    } // Endif.

} // Endproc.


/**
 * The shared table is extended by inserting a range of new elements before
 * the element at whereFrom. This effectively increases the shared table size
 *
 * Because the shared table keeps an array format, insertions on positions
 * other than the shared table end are performed by moving all the elements
 * between whereFrom and the end of the shared table to their new positions,
 * and then inserting the new element(s), which is not efficient.
 *
 * @param [in] whereFrom
 * An iterator to the insertion point.
 *
 * @param [in] first
 * An iterator to the beginning of the range to be inserted.
 *
 * @param [in] last
 * An iterator to the end of the range to be inserted.
 */
template <typename T>
inline  void    SharedTable<T>::insert (iterator        whereFrom,
                                        const_iterator  first,
                                        const_iterator  last)
{
    if (!full ())
    {
        size_type count =
            std::min((capacity () - m_table->m_currentNumEntries), (size_type) (last - first));

        if (empty ())
        {
            UCopy (first, first + count, &(m_table->m_entry [0]));

            m_table->m_currentNumEntries += count; // More entries.
        } // Endif.

        else
        {
            iterator    end = end ();

            if ((size_type) (end - whereFrom) < count)
            {
                UCopy (whereFrom, end, whereFrom + count);
                UCopy (first + (end - whereFrom), first + (end - whereFrom) + count, end);
                std::copy(first, first + (end - whereFrom), whereFrom);

                m_table->m_currentNumEntries += count; // More entries.
            } // Endif.

            else
            if (0 < count)
            {
                UCopy (end - count, end, end);
                std::copy_backward (whereFrom, end - count, end);
                std::copy (first, first + count, whereFrom);

                m_table->m_currentNumEntries += count; // More entries.
            } // Endif.

        } // Endif.

    } // Endif.

} // Endproc.


/**
 * Removes from the shared table a single element at whereFrom. This effectively
 * reduces the shared table size by the number of elements removed.
 *
 * Returns an iterator to the new location of the element that followed the
 * last element erased by the method call, which is the shared table end if
 * the operation erased the last element in the sequence.
 *
 * Because the shared table keeps an array format, erasing on positions other
 * than the shared table end also moves all the elements after the element
 * erased to their new positions, which is not efficient.
 *
 * This invalidates all iterator and references to elements after whereFrom.
 *
 * @param [in] whereFrom
 * An iterator to the element to be erased.
 *
 * @return
 * An iterator to the new location of the element that followed the last
 * element erased by the method call, which is the shared table end if the
 * operation erased the last element in the sequence.
 */
template <typename T>
inline  typename SharedTable<T>::iterator    SharedTable<T>::erase (iterator whereFrom)
{
    iterator    end = end ();

    std::copy (whereFrom + 1, end, whereFrom);

    Destroy (end - 1, end);

    m_table->m_currentNumEntries--; // One less entry.

    return (whereFrom);
} // Endproc.


/**
 * Removes from the shared table the range of elements [first, last). This
 * effectively reduces the shared table size by the number of elements
 * removed.
 *
 * Returns an iterator to the new location of the element that followed the
 * last element erased by the method call, which is the shared table end if
 * the operation erased the last element in the sequence.
 *
 * Because the shared table keeps an array format, erasing on positions other
 * than the shared table end also moves all the elements after the element
 * erased to their new positions, which is not efficient.
 *
 * This invalidates all iterators and references to elements after first.
 *
 * @param [in] first
 * An iterator to the beginning of the range to be erased.
 *
 * @param [in] last
 * An iterator to the end of the range to be erased.
*/
template <typename T>
inline  typename SharedTable<T>::iterator    SharedTable<T>::erase (iterator first,
                                                                    iterator last)
{
    iterator    end = end ();

    iterator    whereFrom = std::copy (last, end, first);

    Destroy (whereFrom, end);

    m_table->m_currentNumEntries -= (last - first);   // Reduce number of entries.

    return (first);
} // Endproc.


/**
 * Assigns new content to the shared table, dropping all the elements
 * contained in the shared table before the call and replacing them by
 * those specified.
 *
 * @param [in] count
 * The number of elements to be placed in the table.
 *
 * @param [in] value
 * The value to be assigned to each element in the table.
 */
template <typename T>
inline  void    SharedTable<T>::assign (size_type   count,
                                        const T&    value)
{
    erase (begin (), end ());

    insert (begin (), count, value);
} // Endproc.


/**
 * Assigns new content to the shared table, dropping all the elements
 * contained in the shared table before the call and replacing them by
 * those specified.
 *
 * The new contents are a copy of the elements in the sequence between first
 * and last (in the range [first, last).
 *
 * @param [in] first
 * An iterator to the beginning of the range to be assigned.
 *
 * @param [in] last
 * An iterator to the end of the range to be assigned.
 */
template <typename T>
inline  void    SharedTable<T>::assign (const_iterator  first,
                                        const_iterator  last)
{
    erase (begin (), end ());

    insert (begin (), first, last);
} // Endproc.


/**
 * Removes the last element in the shared table, effectively reducing the
 * shared table size by one and invalidating all iterators and references
 * to it.
 */
template <typename T>
inline  void    SharedTable<T>::pop_back ()
{
    erase (end () - 1);
} // Endproc.


/**
 * Adds a new element at the end of the shared table, after its current last
 * element. The content of this new element is initialized to a copy of value.
 * This effectively increases the shared table size by one.
 *
 * @param [in] value
 * The element to be added to the end of the shared table.
 */
template <typename T>
inline  void    SharedTable<T>::push_back (const T& value)
{
    insert (end (), value);
} // Endproc.


/**
 * All the elements of the shared table are removed, leaving the shared table
 * with a size of zero.
 */
template <typename T>
inline  void    SharedTable<T>::clear ()
{
    erase (begin (), end ());
} // Endproc.


/**
 * Method that initialise the shared table.
 *
 * @param [in] sharedMemoryName
 * The name of the shared memory.
 *
 * @param [in] size
 * The maximum number of elements that can be held in the table.
 */
template <typename T>
inline  void    SharedTable<T>::Initialise (const FolioString&  sharedMemoryName,
                                             size_type          size)
{
    // Create the shared table access mutex (unowned).

    SharedMutexName mutexName(sharedMemoryName);
    mutexName += "AccessSharedTable";

    FolioStatus status = Create (mutexName.c_str ());

    if ((status == ERR_SUCCESS) ||
        (status == ERR_ALREADY_EXISTS))
    {
        // Make sure we own the shared table.

        AccessSharedTableScopeLock  ScopeLocker(*this);

        // Create the shared memory for the table.

        status = m_sharedMemory.Create (sharedMemoryName,
                                        ((size - 1) * sizeof(T)) + sizeof (SharedTableStruct));

        if ((status == ERR_SUCCESS) ||
            (status == ERR_ALREADY_EXISTS))
        {
            // Note the pointer to the table.

            m_table = reinterpret_cast<SharedTableStruct*> (m_sharedMemory.GetBaseAddress ());

            // If we have just created the table, then initialise it.

            if (status == ERR_SUCCESS)
            {
                m_table->m_maxNumEntries     = size;
                m_table->m_currentNumEntries = 0;

                // Clear the table.

                ::memset (m_table->m_entry,
                          0x1c,
                          size * sizeof(T));
            } // Endif.

        } // Endif.

    } // Endif.

} // Endproc.


/**
 * Closes the named shared memory segment for the table.
 */
template <typename T>
inline  void    SharedTable<T>::Terminate ()
{
    // Make sure we own the shared table.

    AccessSharedTableScopeLock  ScopeLocker(*this);

    // Did we create the shared memory table?

    if (m_table)
    {
        // Yes. Close the shared memory for the table.

        m_sharedMemory.Close ();
    } // Endif.

} // Endproc.


/**
 * Overwrites the data in the shared memory behind the table with invalid
 * data.
 *
 * @param [in] first
 * An iterator to the beginning of the range to be destroyed.
 *
 * @param [in] last
 * An iterator to the end of the range to be destroyed.
 */
template <typename T>
inline  void    SharedTable<T>::Destroy (iterator   first, 
                                         iterator   last)
{
    for (; first != last; ++first)
    {
        ::memset (first, 0x1c, sizeof (T));
    } // Endfor.

} // Endproc.


/**
 * The data associated with a range of elements is copied to another position
 * in the table. This method allows data to be moved when elements are
 * inserted or erased by public methods.
 *
 * @param [in] whereFrom
 * An iterator to the destination.
 *
 * @param [in] first
 * An iterator to the beginning of the range to be copied.
 *
 * @param [in] last
 * An iterator to the end of the range to be copied.
 */
template <typename T>
inline  typename SharedTable<T>::iterator   SharedTable<T>::UCopy (const_iterator   first,
                                                                   const_iterator   last,
                                                                   iterator         whereFrom)
{
    for (; first != last; ++whereFrom, ++first)
    {
        *whereFrom = *first;
    } // Endfor.

    return (whereFrom);
} // Endproc.


/**
 * The elements in the range [first, first + count) are set to a new value.
 *
 * @param [in] first
 * An iterator to the beginning of the range to be filled.
 *
 * @param [in] count
 * The number of elements to fill.
 *
 * @param [in] value
 * The value to be used to fill each element.
 */
template <typename T>
inline  void    SharedTable<T>::UFill (iterator     first,
                                       size_type    count,
                                       const T&     value)
{
    for (; 0 < count; --count, ++first)
    {
        *first = value;
    } // Endfor.

} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma warning(pop)

#pragma pack(pop)

/******************************* End of File *******************************/
