#pragma once

// "Home-made" includes.
#include    <Base.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Trace
{

/// The trace client class.
/**
 * This class provides support for trace supply points.
 *
 * This class does not support copy construction or assignment.
 */
class TraceClient
{
public:
    TraceClient (const FolioString& traceArea);
    TraceClient (const FolioString& traceArea,
                 const FolioString& functionName);
    ~TraceClient ();

    bool    IsInterfaceEntryRequired () const;
    bool    IsInterfaceExitRequired () const;
    bool    IsImplementationEntryRequired () const;
    bool    IsImplementationExitRequired () const;
    bool    IsEventFiredRequired () const;
    bool    IsEventArrivedRequired () const;
    bool    IsErrorRequired () const;
    bool    IsWarningRequired () const;
    bool    IsGeneralRequired () const;

    void    InterfaceEntry (UInt32              sourceFileLine,
                            const FolioString&  sourceFileName, 
                            const FolioString&  variableString);
    void    InterfaceExit (UInt32               sourceFileLine,
                           const FolioString&   sourceFileName, 
                           const FolioString&   variableString,
                           const FolioString&   returnString);
    void    ImplementationEntry (UInt32             sourceFileLine,
                                 const FolioString& sourceFileName, 
                                 const FolioString& variableString);
    void    ImplementationExit (UInt32              sourceFileLine,
                                const FolioString&  sourceFileName, 
                                const FolioString&  variableString,
                                const FolioString&  returnString);
    void    EventFired (UInt32              sourceFileLine, 
                        const FolioString&  sourceFileName, 
                        const FolioString&  userString,
                        const FolioString&  variableString);
    void    EventArrived (UInt32                sourceFileLine, 
                          const FolioString&    sourceFileName, 
                          const FolioString&    userString,
                          const FolioString&    variableString);
    void    Error (UInt32               sourceFileLine, 
                   const FolioString&   sourceFileName, 
                   const FolioString&   userString,
                   const FolioString&   variableString);
    void    Warning (UInt32             sourceFileLine, 
                     const FolioString& sourceFileName, 
                     const FolioString& userString,
                     const FolioString& variableString);
    void    General (UInt32             sourceFileLine, 
                     const FolioString& sourceFileName, 
                     const FolioString& userString,
                     const FolioString& variableString);

private:
    typedef UInt32  SupplyPoint;    /// Supply point type.
    static  const   SupplyPoint SUPPLY_POINT_INTERFACE_ENTRY        = 0x00000001;   ///< Interface entry supply point.
    static  const   SupplyPoint SUPPLY_POINT_INTERFACE_EXIT         = 0x00000002;   ///< Interface exit supply point.
    static  const   SupplyPoint SUPPLY_POINT_IMPLEMENTATION_ENTRY   = 0x00000004;   ///< Implementation entry supply point.
    static  const   SupplyPoint SUPPLY_POINT_IMPLEMENTATION_EXIT    = 0x00000008;   ///< Implementation exit supply point.
    static  const   SupplyPoint SUPPLY_POINT_EVENT_FIRED            = 0x00000010;   ///< Event fired supply point.
    static  const   SupplyPoint SUPPLY_POINT_EVENT_ARRIVED          = 0x00000020;   ///< Event arrived supply point.
    static  const   SupplyPoint SUPPLY_POINT_ERROR                  = 0x00000040;   ///< Error supply point.
    static  const   SupplyPoint SUPPLY_POINT_WARNING                = 0x00000080;   ///< Warning supply point.
    static  const   SupplyPoint SUPPLY_POINT_GENERAL                = 0x00000100;   ///< General supply point.

    static  const   SupplyPoint OUTPUT_TO_DEBUG = 0x01000000;   ///< The supply point should be output as a Windows debug string.
    static  const   SupplyPoint OUTPUT_TO_LOG   = 0x02000000;   ///< The supply point should be logged to the Windows event log.

    FolioString m_traceArea;    ///< The trace area.
    FolioString m_functionName; ///< The function name.

    mutable bool        m_obtainedAreaSupplyPoint;  ///< Indicates if the trace area suppy point has been obtained.
    mutable SupplyPoint m_areaSupplyPoint;          ///< The trace area supply point.

    FolioHandle m_eventLogHandle;   ///< Handle to the Windows event log.

    bool    IsSupplyPointRequired (SupplyPoint supplyPoint) const;
    
    FolioHandle GetEventLogHandle ();

    static  bool    IsOutputToDebugRequired (SupplyPoint supplyPoint);
    static  bool    IsOutputToLogRequired (SupplyPoint supplyPoint);
    
    static  void    OutputToDebug (const FolioString&   traceArea,
                                   SupplyPoint          supplyPoint,
                                   UInt32               sourceFileLine, 
                                   const FolioString&   sourceFileName, 
                                   const FolioString&   functionName, 
                                   const FolioString&   supplyString);

    static  void    OutputToLog (FolioHandle        eventLogHandle,
                                 const FolioString& traceArea,
                                 SupplyPoint        supplyPoint,
                                 UInt32             sourceFileLine, 
                                 const FolioString& sourceFileName, 
                                 const FolioString& functionName, 
                                 const FolioString& supplyString);

    static  FolioString FormatSupply (const FolioString&    traceArea,
                                      SupplyPoint           supplyPoint,
                                      UInt32                sourceFileLine, 
                                      const FolioString&    sourceFileName, 
                                      const FolioString&    functionName, 
                                      const FolioString&    supplyString);
    static  FolioString GetSupplyPointDescription (SupplyPoint supplyPoint);

    /// Private copy constructor to prevent copying.
    TraceClient (const TraceClient& rhs);

    /// Private assignment operator to prevent copying.
    TraceClient& operator= (const TraceClient& rhs);
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
