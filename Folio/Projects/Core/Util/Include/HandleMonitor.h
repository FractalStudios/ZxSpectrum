#pragma once

// STL includes.
#include    <vector>

// "Home-made" includes.
#include    <Base.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Util
{

/// The handle monitor class.
class HandleMonitor
{
public:
    HandleMonitor (UInt32 dumpListSize = 1024);
    ~HandleMonitor ();

    void    SetDumpListSize (UInt32 dumpListSize);
    void    AddHandle (FolioHandle          handle, 
                       const FolioString&   name);
    void    RemoveHandle (FolioHandle handle);
    void    DumpHandleList () const; 

private:
    /// Handle list entry.
    typedef std::pair<FolioHandle, FolioString> HandleListEntry;
    
    /// Handle list.
    typedef std::vector<HandleListEntry>    HandleList;
    
    HandleList  m_handleList;   ///< Handle list.

    UInt32  m_dumpListSize;    ///< The size of the handle list when it shold be dumped;

    FolioString DescribeHandleListEntry (const HandleListEntry& handleListEntry) const;

    /// Private copy constructor to prevent copying.
    HandleMonitor (const HandleMonitor& rhs);

    /// Private assignment operator to prevent copying.
    HandleMonitor& operator= (const HandleMonitor& rhs);
}; // Endclass.


// Globals.

extern  HandleMonitor   g_handleMonitor;    ///< The handle monitor.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
