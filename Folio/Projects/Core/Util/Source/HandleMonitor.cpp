// Windows includes.
#include    <Windows.h>

// STL includes.
#include    <algorithm>

// "Home-made" includes.
#include    <Trace.h>
#include    "HandleMonitor.h"

//#define _OUTPUT_HANDLE_MONITOR_

namespace Folio
{

namespace Core
{

namespace Util
{

// Globals.

HandleMonitor   g_handleMonitor;    ///< The handle monitor.


/**
 * The default class constructor.
 */
HandleMonitor::HandleMonitor (UInt32 dumpListSize)
:   m_dumpListSize(dumpListSize)
{
} // Endproc.


/**
 * The class destructor. If required it will remove any OS reference to the
 * handle monitor from this object.
 */
HandleMonitor::~HandleMonitor ()
{
} // Endproc.


/**
 * Method that will set the dump list size for the handle monitor.
 *
 * @param [in] dumpListSize
 * The dump list size.
 */
void   HandleMonitor::SetDumpListSize (UInt32 dumpListSize)
{
    m_dumpListSize = dumpListSize;
} // Endproc.


/**
 * Method that will add a handle to the handle monitor.
 *
 * @param [in] handle
 * The handle to add.
 *
 * @param [in] id
 * The identifier associated with the handle.
 *
 * @param [in]  name
 * The name associated with the handle.
 */
void   HandleMonitor::AddHandle (FolioHandle        handle, 
                                 UInt32             id, 
                                 const FolioString& name)
{
    HandleListEntry handleListEntry(handle, id, name);

    #ifdef _OUTPUT_HANDLE_MONITOR_
    FolioOStringStream  str;
    str << std::setw(8) << std::setfill(TXT('0')) << m_handleList.size () << TXT(": Add    ")
        << handleListEntry.Describe ()
        << std::endl;
    ::OutputDebugString (str.str ().c_str ());
    #endif

    m_handleList.push_back (handleListEntry);

    if ((m_handleList.size () % m_dumpListSize) == 0)
    {
        Dump ();
    } // Endif.

} // Endproc.


/**
 * Method that will remove a handle from the handle monitor.
 *
 * @param [in] handle
 * The handle to remove.
 */
void   HandleMonitor::RemoveHandle (FolioHandle handle) 
{
     HandleList::iterator itr = std::find_if (m_handleList.begin (), m_handleList.end (), 
                                              [handle](const HandleListEntry& arg) 
                                              {return (arg.m_handle == handle);});

     if (itr != m_handleList.end ())
     {
        #ifdef _OUTPUT_HANDLE_MONITOR_
        FolioOStringStream  str;
        str << std::setw(8) << std::setfill(TXT('0')) << m_handleList.size () << TXT(": Remove ")
            << itr->Describe ()
            << std::endl;
        ::OutputDebugString (str.str ().c_str ());
        #endif
        
        m_handleList.erase (itr);
    } // Endif.

     else
     {
        FOLIO_DEBUG_BREAK;
     } // Endelse.

} // Endproc.


/**
 * Method that will dump all the handles in the handle monitor's list.
 */
void    HandleMonitor::Dump () const
{
    for (HandleList::const_iterator itr = m_handleList.begin ();
         itr != m_handleList.end ();
         ++itr)
    {
        FolioOStringStream  str;
        str << std::setw(8) << std::setfill(TXT('0')) << std::distance(m_handleList.begin (), itr) << TXT(", ")  
            << itr->Describe ()
            << std::endl;
        ::OutputDebugString (str.str ().c_str ());
    } // Endif.

} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/

