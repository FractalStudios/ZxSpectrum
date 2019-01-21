// Windows includes.
#include    <Windows.h>

// STL includes.
#include    <algorithm>

// "Home-made" includes.
#include    <Trace.h>
#include    "WaitAny.h"

namespace Folio
{

namespace Core
{

namespace Util
{

/**
 * The default class constructor.
 */
WaitAny::WaitAny ()
:   m_signalIndex(NO_SIGNAL)
{
} // Endproc.


/**
 * A class constructor.
 *
 * @param [in] syncList
 * A list of synchronization objects.
 */
WaitAny::WaitAny (SyncList& syncList)
:   m_signalIndex(NO_SIGNAL)
{
    if (syncList.size ())
    {
        // Fill synchronization handle list.

        m_syncHandleList.resize (syncList.size ());

        for (UInt32 handleIndex = 0;
             handleIndex < syncList.size ();
             ++handleIndex)
        {
            m_syncHandleList [handleIndex] = syncList [handleIndex]->GetSyncHandle ();
        } // Endfor.

    } // Endif.

} // Endproc.


/**
 * The default class constructor. Ensure that any allocated synchronization
 * handle list is freed.
 */
WaitAny::~WaitAny ()
{
} // Endproc.


/**
 * Method that will add a synchronization object to be waited on by
 * the <b>WaitAny</b> object.
 *
 * @param [in] syncObject
 * The synchronization object.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the synchronization object was
 *      successfully added.
 * <li><b>ERR_ALREADY_EXISTS</b> if the synchronization object is
 *      already in the list of synchronization objects to be waited on.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus WaitAny::Add (Sync& syncObject)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the synchronization object already in the synchronization
    // handle list?

    SyncHandleList::iterator    itr;

    if (FindSyncHandle (syncObject.GetSyncHandle (), itr))
    {
        // Yes.

        status = ERR_ALREADY_EXISTS;
    } // Endif.

    else
    {
        // No. Add it.

        m_syncHandleList.push_back (syncObject.GetSyncHandle ());
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will remove a synchronization object that was to be
 * waited on, or has already been waited on, by the <b>WaitAny</b> object.
 *
 * If this method is called after a successful <b>Wait</b>, and the
 * synchronization object that is to be removed is the object that satisfied
 * the wait (i.e. it is in the signaled state) then subsequent calls to the
 * <b>GetSyncIndex</b> method and the <b>GetSyncHandle</b> method will return
 * <b>NO_SIGNAL</b> and zero respectively.
 *
 * @param [in] syncObject
 * The synchronization object.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the synchronization object was successfully
 *     removed.
 * <li><b>ERR_NOT_FOUND</b> if the synchronization object was not found
 *     in the list of synchronization objects to be waited on.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus WaitAny::Remove (Sync& syncObject)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the synchronization object in the synchronization handle list?

    SyncHandleList::iterator    itr;

    if (FindSyncHandle (syncObject.GetSyncHandle (), itr))
    {
        // Yes. Remove it.

        // Get the index of the synchronization object that is to be
        // removed.

        UInt32  syncIndex = itr - m_syncHandleList.begin ();

        m_syncHandleList.erase (itr);

        // If we are in a signaled state, then the index of the
        // synchronization object that is signaled may have been affected.

        if (m_signalIndex != WaitAny::NO_SIGNAL)
        {
            // Did we just remove the synchronization object that has
            // been signaled?

            if (syncIndex == m_signalIndex)
            {
                // Yes. We have no signaled synchronization object.

                m_signalIndex = WaitAny::NO_SIGNAL;
            } // Endif.

            // Has removing this synchronization object affected the
            // index of the synchronization object that is signaled?

            else if (syncIndex < m_signalIndex)
            {
                // Yes. Decrement the index of the signaled
                // synchronization object.

                m_signalIndex--;
            } // Endelseif.

        } // Endif.

    } // Endif.

    else
    {
        // No.

        status = ERR_NOT_FOUND;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method to get the index to the synchronization object signaled
 * on a successful <b>Wait</b>.
 *
 * @return
 * The possible return values are:<ul>
 * <li>The index to the synchronization object.
 * <li><b>NO_SIGNAL</b> if no synchronization object has been signaled.
 * </ul>
 */
UInt32  WaitAny::GetSyncIndex () const
{
    return (m_signalIndex);
} // Endproc.


/**
 * Method to get the handle of the synchronization object signaled
 * on a successful <b>Wait</b>.
 *
 * @return
 * The possible return values are:<ul>
 * <li>The handle of the synchronization object.
 * <li><b>FOLIO_INVALID_HANDLE</b> if no synchronization object has been 
 *     signaled.
 * </ul>
 */
FolioHandle WaitAny::GetSyncHandle () const
{
    return ((m_signalIndex == NO_SIGNAL) ? FOLIO_INVALID_HANDLE : m_syncHandleList [m_signalIndex]);
} // Endproc.


/**
 * Method to wait for any synchronization object to be signaled or the
 * time-out interval to elapse.
 *
 * @param [in] timeout
 * Time to wait in milliseconds. If <b>FOLIO_INFINITE</b> is specified then
 * the calling thread will be blocked indefinately until one of the
 * synchronization objects is signaled.
 *
 * @param [in] logOnInfiniteTimeout
 * In order to allow for problem reporting of potential system hang
 * scenarios, that parameter is used to indicate if a warning should be
 * logged if a <b>FOLIO_INFINITE</b> <i>timeout</i> has been specified and
 * no synchronization object has been signaled within 150 seconds. Note that
 * if the 150 seconds timeout occurs then, after logging a warning, the
 * method will subsequently wait infinitely for any synchronization object
 * to be signaled. <b>true</b> if the warning should be logged, <b>false</b>
 * otherwise.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_TIMEOUT</b> if the time-out interval elapsed before any
 *     synchronization object was signaled.
 * <li><b>ERR_INVALID_SEQUENCE</b> if there are no of synchronization
 *     objects to wait on.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus WaitAny::Wait (UInt32   timeout,
                           bool     logOnInfiniteTimeout)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we allocated a synchronization handle list?

    if (m_syncHandleList.empty ())
    {
        // We were passed an empty list of synchronization objects
        // on construction.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // If "logOnInfiniteTimeout" has been specified and the caller wishes 
        // to wait infinitely, then wait for 150 seconds. If there is a 
        // subsequent timeout then log a warning before subsequently waiting 
        // infinitely.

        if (logOnInfiniteTimeout &&
            (timeout == FOLIO_INFINITE))
        {
            status = Wait (150 * 1000, false);  // Recurse.

            if (status == ERR_TIMEOUT)
            {
                // Warn that there may be a problem waiting on the
                // synchronization handle list.

                FOLIO_LOG_WARNING_1 (TXT("Waited 150 seconds for synchronization object(s), now waiting infinitely."),
                                     m_syncHandleList);

                // Wait infinitely for the synchronization handle list.

                status = Wait (INFINITE, false);    // Recurse.
            } // Endif.

        } // Endif.

        else
        {
            // Wait for any synchronization handle.

            UInt32  numHandles = m_syncHandleList.size ();

            UInt32  exception =
                ::WaitForMultipleObjects (numHandles,
                                          &(m_syncHandleList [0]),
                                          FALSE, // Wait any.
                                          timeout);

            if ((exception >= WAIT_OBJECT_0) &&
                (exception < (WAIT_OBJECT_0 + numHandles)))
            {
                // A handle has been signaled within the wait time.

                m_signalIndex = exception - WAIT_OBJECT_0;
            } // Endif.

            else if ((exception >= WAIT_ABANDONED_0) &&
                     (exception < (WAIT_ABANDONED_0 + numHandles)))
            {
                // The wait was satisfied by an abandoned mutex handle.

                m_signalIndex = exception - WAIT_ABANDONED_0;

                FolioHandle handle = m_syncHandleList [m_signalIndex];

                FOLIO_LOG_WARNING_1 (TXT("Wait abandoned."),
                                     handle);
            } // Endelseif.

            else if (exception == WAIT_TIMEOUT)
            {
                // The wait time elapsed without a handle being signaled.

                status = ERR_TIMEOUT;
            } // Endelseif.

            else
            {
                // Build and log an error.

                status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

                FOLIO_LOG_CALL_ERROR_2 (TXT("WaitForMultipleObjects"),
                                        status,
                                        m_syncHandleList,
                                        timeout);
            } // Endelse.

        } // Endelse.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that is used to find a synchronization handle in the synchronization
 * handle list.
 *
 * @param [in] syncHandle
 * The synchronization handle.
 *
 * @param [out] itr
 * On return, will hold the reference to the synchronization handle in the
 * synchronization handle list, if found. If not found this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>true</b> if the synchronization handle was found in the
 *     synchronization handle list.
 * <li><b>false</b> otherwise.
 * </ul>
 */
bool    WaitAny::FindSyncHandle (FolioHandle                syncHandle,
                                 SyncHandleList::iterator&  itr) const
{
    itr = std::find (m_syncHandleList.begin (), 
                     m_syncHandleList.end (),
                     syncHandle);

    return (itr != m_syncHandleList.end ());
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
