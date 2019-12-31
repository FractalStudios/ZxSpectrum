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

// Routines.

extern  FolioString DescribeId (UInt16 id);

/// The handle monitor class.
class HandleMonitor
{
public:
    HandleMonitor (UInt32 dumpListSize = 1024);
    ~HandleMonitor ();

    void    SetDumpListSize (UInt32 dumpListSize);
    void    AddHandle (FolioHandle          handle, 
                       UInt32               id,
                       const FolioString&   name);
    void    RemoveHandle (FolioHandle handle);
    void    Dump () const; 

private:
    /// Handle list entry.
    struct HandleListEntry
    {
        HandleListEntry (FolioHandle        handle,
                         UInt32             id,
                         const FolioString& name)
        :   m_handle(handle),
            m_id(id),
            m_name(name)
        {} // Endproc.

        ~HandleListEntry ()
        {} // Endproc.

        FolioString Describe () const
        {
            FolioOStringStream  str;
            str << TXT("0x") << std::setw(8) << std::setfill(TXT('0')) << std::hex << m_handle
                << (' ') << DescribeId (m_id)
                << TXT(' ') << m_name;

            return (str.str ());
        } // Endproc.

        FolioHandle m_handle;   ///< The handle. 
        UInt32      m_id;       ///< The identifier associated with the handle.
        FolioString m_name;     ///< The name associated with the handle.
    }; // Endstruct.
    
    /// Handle list.
    typedef std::vector<HandleListEntry>    HandleList;
    
    HandleList  m_handleList;   ///< Handle list.

    UInt32  m_dumpListSize;    ///< The size of the handle list when it should be dumped;

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
