// Windows includes.
#include    <Windows.h>

// "Home-made" includes.
#include    "TraceClient.h"

namespace Folio
{

namespace Core
{

namespace Trace
{

/**
 * A class constructor.
 *
 * @param [in] traceArea
 * The trace area.
 */
TraceClient::TraceClient (const FolioString& traceArea)
:   m_traceArea(traceArea),
    m_obtainedAreaSupplyPoint(false),
    m_areaSupplyPoint(0),
    m_eventLogHandle(FOLIO_INVALID_HANDLE)
{
} // Endproc.


/**
 * A class constructor.
 *
 * @param [in] traceArea
 * The trace area.
 *
 * @param [in] functionName
 * The function name.
 */
TraceClient::TraceClient (const FolioString&    traceArea,
                          const FolioString&    functionName)
:   m_traceArea(traceArea),
    m_functionName(functionName),
    m_obtainedAreaSupplyPoint(false),
    m_areaSupplyPoint(0),
    m_eventLogHandle(FOLIO_INVALID_HANDLE)
{
} // Endproc.


/**
 * The class destructor.
 */
TraceClient::~TraceClient ()
{
    if (m_eventLogHandle != FOLIO_INVALID_HANDLE)
    {
        // Close the event log handle.

        ::DeregisterEventSource (m_eventLogHandle);
    } // Endif.

} // Endproc.


/**
 * Method that is used to indicate if an interface entry supply point is 
 * required.
 * 
 * @return
 * <b>true</b> if an interface entry supply point is required, <b>false</b> 
 * otherwise.
 */
bool    TraceClient::IsInterfaceEntryRequired () const
{
    return (IsSupplyPointRequired (SUPPLY_POINT_INTERFACE_ENTRY));
} // Endproc.


/**
 * Method that is used to indicate if an interface exit supply point is 
 * required.
 * 
 * @return
 * <b>true</b> if an interface exit supply point is required, <b>false</b> 
 * otherwise.
 */
bool    TraceClient::IsInterfaceExitRequired () const
{
    return (IsSupplyPointRequired (SUPPLY_POINT_INTERFACE_EXIT));
} // Endproc.


/**
 * Method that is used to indicate if an implementation entry supply point is 
 * required.
 * 
 * @return
 * <b>true</b> if an implementation entry supply point is required, <b>false</b> 
 * otherwise.
 */
bool    TraceClient::IsImplementationEntryRequired () const
{
    return (IsSupplyPointRequired (SUPPLY_POINT_IMPLEMENTATION_ENTRY));
} // Endproc.


/**
 * Method that is used to indicate if an implementation exit supply point is 
 * required.
 * 
 * @return
 * <b>true</b> if an implementation exit supply point is required, <b>false</b> 
 * otherwise.
 */
bool    TraceClient::IsImplementationExitRequired () const
{
    return (IsSupplyPointRequired (SUPPLY_POINT_IMPLEMENTATION_EXIT));
} // Endproc.


/**
 * Method that is used to indicate if an event fired supply point is 
 * required.
 * 
 * @return
 * <b>true</b> if an event fired supply point is required, <b>false</b> 
 * otherwise.
 */
bool    TraceClient::IsEventFiredRequired () const
{
    return (IsSupplyPointRequired (SUPPLY_POINT_EVENT_FIRED));
} // Endproc.


/**
 * Method that is used to indicate if an event arrived supply point is 
 * required.
 * 
 * @return
 * <b>true</b> if an event arrived supply point is required, <b>false</b> 
 * otherwise.
 */
bool    TraceClient::IsEventArrivedRequired () const
{
    return (IsSupplyPointRequired (SUPPLY_POINT_EVENT_ARRIVED));
} // Endproc.


/**
 * Method that is used to indicate if an error supply point is 
 * required.
 * 
 * @return
 * <b>true</b> if an error supply point is required, <b>false</b> 
 * otherwise.
 */
bool    TraceClient::IsErrorRequired () const
{
    // Error supply points are always required.
    
    return (true);
} // Endproc.


/**
 * Method that is used to indicate if a warning supply point is 
 * required.
 * 
 * @return
 * <b>true</b> if a warning supply point is required, <b>false</b> 
 * otherwise.
 */
bool    TraceClient::IsWarningRequired () const
{
    return (IsSupplyPointRequired (SUPPLY_POINT_WARNING));
} // Endproc.


/**
 * Method that is used to indicate if a general supply point is 
 * required.
 * 
 * @return
 * <b>true</b> if a general supply point is required, <b>false</b> 
 * otherwise.
 */
bool    TraceClient::IsGeneralRequired () const
{
    return (IsSupplyPointRequired (SUPPLY_POINT_GENERAL));
} // Endproc.


/**
 * Method that is used to supply an interface entry supply point.
 * 
 * @param [in] sourceFileLine
 * The supply point source file line.
 * 
 * @param [in] sourceFileName 
 * The supply point source file name.
 * 
 * @param [in] variablesString
 * The supply point variables string.
 */
void    TraceClient::InterfaceEntry (UInt32             sourceFileLine,
                                     const FolioString& sourceFileName, 
                                     const FolioString& variablesString)
{
    if (IsInterfaceEntryRequired ())
    {
        if (IsOutputToDebugRequired (m_areaSupplyPoint))
        {
            OutputToDebug (m_traceArea,
                           SUPPLY_POINT_INTERFACE_ENTRY,
                           sourceFileLine,
                           sourceFileName, 
                           m_functionName,
                           variablesString);
        } // Endif.

        if (IsOutputToLogRequired (m_areaSupplyPoint))
        {
            OutputToLog (GetEventLogHandle (),
                         m_traceArea,
                         SUPPLY_POINT_INTERFACE_ENTRY,
                         sourceFileLine,
                         sourceFileName, 
                         m_functionName,
                         variablesString);
        } // Endif.

    } // Endif.

} // Endproc.


/**
 * Method that is used to supply an interface exit supply point.
 * 
 * @param [in] sourceFileLine
 * The supply point source file line.
 * 
 * @param [in] sourceFileName 
 * The supply point source file name.
 * 
 * @param [in] variablesString
 * The supply point variables string.
 * 
 * @param [in] returnString
 * The supply point return string.
 */
void    TraceClient::InterfaceExit (UInt32              sourceFileLine,
                                    const FolioString&  sourceFileName, 
                                    const FolioString&  variablesString,
                                    const FolioString&  returnString)
{
    if (IsInterfaceExitRequired ())
    {
        FolioOStringStream  outputStringStream;
        outputStringStream << variablesString
                           << TXT(' ')
                           << returnString;

        if (IsOutputToDebugRequired (m_areaSupplyPoint))
        {
            OutputToDebug (m_traceArea,
                           SUPPLY_POINT_INTERFACE_EXIT,
                           sourceFileLine,
                           sourceFileName, 
                           m_functionName,
                           outputStringStream.str ());
        } // Endif.

        if (IsOutputToLogRequired (m_areaSupplyPoint))
        {
            OutputToLog (GetEventLogHandle (),
                         m_traceArea,
                         SUPPLY_POINT_INTERFACE_EXIT,
                         sourceFileLine,
                         sourceFileName, 
                         m_functionName,
                         outputStringStream.str ());
        } // Endif.

    } // Endif.

} // Endproc.


/**
 * Method that is used to supply an implementation entry supply point.
 * 
 * @param [in] sourceFileLine
 * The supply point source file line.
 * 
 * @param [in] sourceFileName 
 * The supply point source file name.
 * 
 * @param [in] variablesString
 * The supply point variables string.
 */
void    TraceClient::ImplementationEntry (UInt32                sourceFileLine,
                                          const FolioString&    sourceFileName, 
                                          const FolioString&    variablesString)
{
    if (IsImplementationEntryRequired ())
    {
        if (IsOutputToDebugRequired (m_areaSupplyPoint))
        {
            OutputToDebug (m_traceArea,
                           SUPPLY_POINT_IMPLEMENTATION_ENTRY,
                           sourceFileLine,
                           sourceFileName, 
                           m_functionName,
                           variablesString);
        } // Endif.

        if (IsOutputToLogRequired (m_areaSupplyPoint))
        {
            OutputToLog (GetEventLogHandle (),
                         m_traceArea,
                         SUPPLY_POINT_IMPLEMENTATION_ENTRY,
                         sourceFileLine,
                         sourceFileName, 
                         m_functionName,
                         variablesString);
        } // Endif.

    } // Endif.

} // Endproc.


/**
 * Method that is used to supply an implementation exit supply point.
 * 
 * @param [in] sourceFileLine
 * The supply point source file line.
 * 
 * @param [in] sourceFileName 
 * The supply point source file name.
 * 
 * @param [in] variablesString
 * The supply point variables string.
 * 
 * @param [in] returnString
 * The supply point return string.
 */
void    TraceClient::ImplementationExit (UInt32             sourceFileLine,
                                         const FolioString& sourceFileName, 
                                         const FolioString& variablesString,
                                         const FolioString& returnString)
{
    if (IsImplementationExitRequired ())
    {
        FolioOStringStream  outputStringStream;
        outputStringStream << variablesString
                           << TXT(' ')
                           << returnString;

        if (IsOutputToDebugRequired (m_areaSupplyPoint))
        {
            OutputToDebug (m_traceArea,
                           SUPPLY_POINT_IMPLEMENTATION_EXIT,
                           sourceFileLine,
                           sourceFileName, 
                           m_functionName,
                           outputStringStream.str ());
        } // Endif.

        if (IsOutputToLogRequired (m_areaSupplyPoint))
        {
            OutputToLog (GetEventLogHandle (),
                         m_traceArea,
                         SUPPLY_POINT_IMPLEMENTATION_EXIT,
                         sourceFileLine,
                         sourceFileName, 
                         m_functionName,
                         outputStringStream.str ());
        } // Endif.

    } // Endif.

} // Endproc.


/**
 * Method that is used to supply an event fired supply point.
 * 
 * @param [in] sourceFileLine
 * The supply point source file line.
 * 
 * @param [in] sourceFileName 
 * The supply point source file name.
 * 
 * @param [in] userString
 * The supply point user string.
 * 
 * @param [in] variablesString
 * The supply point variables string.
 */
void    TraceClient::EventFired (UInt32             sourceFileLine,
                                 const FolioString& sourceFileName, 
                                 const FolioString& userString,
                                 const FolioString& variablesString)
{
    if (IsEventFiredRequired ())
    {
        FolioOStringStream  outputStringStream;
        outputStringStream << userString
                           << TXT(' ')
                           << variablesString;

        if (IsOutputToDebugRequired (m_areaSupplyPoint))
        {
            OutputToDebug (m_traceArea,
                           SUPPLY_POINT_EVENT_FIRED,
                           sourceFileLine,
                           sourceFileName, 
                           m_functionName,
                           outputStringStream.str ());
        } // Endif.

        if (IsOutputToLogRequired (m_areaSupplyPoint))
        {
            OutputToLog (GetEventLogHandle (),
                         m_traceArea,
                         SUPPLY_POINT_EVENT_FIRED,
                         sourceFileLine,
                         sourceFileName, 
                         m_functionName,
                         outputStringStream.str ());
        } // Endif.

    } // Endif.

} // Endproc.


/**
 * Method that is used to supply an event arrived supply point.
 * 
 * @param [in] sourceFileLine
 * The supply point source file line.
 * 
 * @param [in] sourceFileName 
 * The supply point source file name.
 * 
 * @param [in] userString
 * The supply point user string.
 * 
 * @param [in] variablesString
 * The supply point variables string.
 */
void    TraceClient::EventArrived (UInt32               sourceFileLine,
                                   const FolioString&   sourceFileName, 
                                   const FolioString&   userString,
                                   const FolioString&   variablesString)
{
    if (IsEventArrivedRequired ())
    {
        FolioOStringStream  outputStringStream;
        outputStringStream << userString
                           << TXT(' ')
                           << variablesString;

        if (IsOutputToDebugRequired (m_areaSupplyPoint))
        {
            OutputToDebug (m_traceArea,
                           SUPPLY_POINT_EVENT_ARRIVED,
                           sourceFileLine,
                           sourceFileName, 
                           m_functionName,
                           outputStringStream.str ());
        } // Endif.

        if (IsOutputToLogRequired (m_areaSupplyPoint))
        {
            OutputToLog (GetEventLogHandle (),
                         m_traceArea,
                         SUPPLY_POINT_EVENT_ARRIVED,
                         sourceFileLine,
                         sourceFileName, 
                         m_functionName,
                         outputStringStream.str ());
        } // Endif.

    } // Endif.

} // Endproc.


/**
 * Method that is used to supply an error supply point.
 * 
 * @param [in] sourceFileLine
 * The supply point source file line.
 * 
 * @param [in] sourceFileName 
 * The supply point source file name.
 * 
 * @param [in] userString
 * The supply point user string.
 * 
 * @param [in] variablesString
 * The supply point variables string.
 */
void    TraceClient::Error (UInt32              sourceFileLine,
                            const FolioString&  sourceFileName, 
                            const FolioString&  userString,
                            const FolioString&  variablesString)
{
    if (IsErrorRequired ())
    {
        FolioOStringStream  outputStringStream;
        outputStringStream << userString
                           << TXT(' ')
                           << variablesString;

        if (IsOutputToDebugRequired (m_areaSupplyPoint))
        {
            OutputToDebug (m_traceArea,
                           SUPPLY_POINT_ERROR,
                           sourceFileLine,
                           sourceFileName, 
                           m_functionName,
                           outputStringStream.str ());
        } // Endif.

        // Error supply points are always logged.

        OutputToLog (GetEventLogHandle (),
                     m_traceArea,
                     SUPPLY_POINT_ERROR,
                     sourceFileLine,
                     sourceFileName, 
                     m_functionName,
                     outputStringStream.str ());
    } // Endif.

} // Endproc.


/**
 * Method that is used to supply a warning supply point.
 * 
 * @param [in] sourceFileLine
 * The supply point source file line.
 * 
 * @param [in] sourceFileName 
 * The supply point source file name.
 * 
 * @param [in] userString
 * The supply point user string.
 * 
 * @param [in] variablesString
 * The supply point variables string.
 */
void    TraceClient::Warning (UInt32                sourceFileLine,
                              const FolioString&    sourceFileName, 
                              const FolioString&    userString,
                              const FolioString&    variablesString)
{
    if (IsWarningRequired ())
    {
        FolioOStringStream  outputStringStream;
        outputStringStream << userString
                           << TXT(' ')
                           << variablesString;

        if (IsOutputToDebugRequired (m_areaSupplyPoint))
        {
            OutputToDebug (m_traceArea,
                           SUPPLY_POINT_WARNING,
                           sourceFileLine,
                           sourceFileName, 
                           m_functionName,
                           outputStringStream.str ());
        } // Endif.

        if (IsOutputToLogRequired (m_areaSupplyPoint))
        {
            OutputToLog (GetEventLogHandle (),
                         m_traceArea,
                         SUPPLY_POINT_WARNING,
                         sourceFileLine,
                         sourceFileName, 
                         m_functionName,
                         outputStringStream.str ());
        } // Endif.

    } // Endif.

} // Endproc.


/**
 * Method that is used to supply a general supply point.
 * 
 * @param [in] sourceFileLine
 * The supply point source file line.
 * 
 * @param [in] sourceFileName 
 * The supply point source file name.
 * 
 * @param [in] userString
 * The supply point user string.
 * 
 * @param [in] variablesString
 * The supply point variables string.
 */
void    TraceClient::General (UInt32                sourceFileLine,
                              const FolioString&    sourceFileName, 
                              const FolioString&    userString,
                              const FolioString&    variablesString)
{
    if (IsGeneralRequired ())
    {
        FolioOStringStream  outputStringStream;
        outputStringStream << userString
                           << TXT(' ')
                           << variablesString;

        if (IsOutputToDebugRequired (m_areaSupplyPoint))
        {
            OutputToDebug (m_traceArea,
                           SUPPLY_POINT_GENERAL,
                           sourceFileLine,
                           sourceFileName, 
                           m_functionName,
                           outputStringStream.str ());
        } // Endif.

        if (IsOutputToLogRequired (m_areaSupplyPoint))
        {
            OutputToLog (GetEventLogHandle (),
                         m_traceArea,
                         SUPPLY_POINT_GENERAL,
                         sourceFileLine,
                         sourceFileName, 
                         m_functionName,
                         outputStringStream.str ());
        } // Endif.
 
    } // Endif.

} // Endproc.


/**
 * Method that is used to indicate if a particular trace area is required to 
 * supply a specified supply point.
 *
 * @param [in] supplyPoint
 * The supply point.
 *
 * @return
 * <b>true</b> if the trace area is required to supply the supply point, 
 * <b>false</b> otherwise.
 */
bool    TraceClient::IsSupplyPointRequired (SupplyPoint supplyPoint) const
{
    // Have we obtained the trace area supply point?

    if (!m_obtainedAreaSupplyPoint)
    {
        // No. Open the trace registry key.

        HKEY    traceKeyHandle;

        if (::RegOpenKey (HKEY_LOCAL_MACHINE,
                          TXT("Software\\Folio\\Core\\Trace"),
                          &(traceKeyHandle)) == ERROR_SUCCESS)
        {
            // Query the registry value.

            UInt32  registryData;
            UInt32  sizeofRegistryData = sizeof (registryData);

            if (::RegQueryValueEx (traceKeyHandle,
                                   m_traceArea,
                                   0, // Reserved.
                                   0, // Data type is not required.
                                   reinterpret_cast<LPBYTE> (&(registryData)),
                                   reinterpret_cast<LPDWORD> (&(sizeofRegistryData))) == ERROR_SUCCESS)
            {
                // Note the trace area supply point.

                m_areaSupplyPoint           = registryData;
                m_obtainedAreaSupplyPoint   = true;
            } // Endif.

            // Close the registry key.

            ::RegCloseKey (traceKeyHandle);
        } // Endif.

    } // Endif.

    // Is the supply point required?

    return (m_obtainedAreaSupplyPoint           && 
            (m_areaSupplyPoint & supplyPoint)   &&
            (IsOutputToDebugRequired (m_areaSupplyPoint) ||
             IsOutputToLogRequired (m_areaSupplyPoint)));
} // Endproc.


/**
 * Method that is used to obtain a handle to the Windows event log.
 *
 * @return
 * The handle to the Windows event log.
 */
FolioHandle TraceClient::GetEventLogHandle ()
{
    // Have we obtained a handle to an event log?

    if (m_eventLogHandle == FOLIO_INVALID_HANDLE)
    {
        // No. Register the Windows event log source.

        m_eventLogHandle = ::RegisterEventSource (0, // Local.
                                                  TXT("Folio"));
    } // Endif.
    
    return (m_eventLogHandle);
} // Endproc.


/**
 * Method that is used to indicate if a specified supply point should be output 
 * as a Windows debug string.
 *
 * @param [in] supplyPoint
 * The supply point.
 *
 * @return
 * <b>true</b> if the supply point should be output as a Windows debug string,
 * <b>false</b> otherwise.
 */
bool    TraceClient::IsOutputToDebugRequired (SupplyPoint supplyPoint)
{
    return ((supplyPoint & OUTPUT_TO_DEBUG) == OUTPUT_TO_DEBUG);
} // Endproc.


/**
 * Method that is used to indicate if a specified supply point should be output 
 * to the Windows event log.
 *
 * @param [in] supplyPoint
 * The supply point.
 *
 * @return
 * <b>true</b> if the supply point should be output to the Windows event log,
 * <b>false</b> otherwise.
 */
bool    TraceClient::IsOutputToLogRequired (SupplyPoint supplyPoint)
{
    return ((supplyPoint & OUTPUT_TO_LOG) == OUTPUT_TO_LOG);
} // Endproc.


/**
 * Method that is used to supply a supply point as a Windows debug string.
 *
 * @param [in] traceArea
 * The trace area.
 * 
 * @param [in] supplyPoint
 * The supply point.
 * 
 * @param [in] sourceFileLine
 * The supply point source file line.
 *
 * @param [in] sourceFileName 
 * The supply point source file name.
 * 
 * @param [in] functionName
 * The function name.
 * 
 * @param [in] supplyString
 * The supply point string.
 */
void    TraceClient::OutputToDebug (const FolioString&  traceArea,
                                    SupplyPoint         supplyPoint,
                                    UInt32              sourceFileLine,
                                    const FolioString&  sourceFileName, 
                                    const FolioString&  functionName, 
                                    const FolioString&  supplyString)
{
    // Format the supply.

    FolioOStringStream  outputStringStr;

    outputStringStr << FormatSupply (traceArea,
                                     supplyPoint,
                                     sourceFileLine, 
                                     sourceFileName, 
                                     functionName, 
                                     supplyString);

    ::OutputDebugString (outputStringStr.str ().c_str ());
} // Endproc.


/**
 * Method that is used to supply a supply point to the Windows event log.
 *
 * @param [in] eventLogHandle
 * The handle to the Windows event log.
 * 
 * @param [in] traceArea
 * The trace area.
 * 
 * @param [in] supplyPoint
 * The supply point.
 * 
 * @param [in] sourceFileLine
 * The supply point source file line.
 *
 * @param [in] sourceFileName 
 * The supply point source file name.
 * 
 * @param [in] functionName
 * The function name.
 * 
 * @param [in] supplyString
 * The supply point string.
 */
void    TraceClient::OutputToLog (FolioHandle           eventLogHandle,
                                  const FolioString&    traceArea,
                                  SupplyPoint           supplyPoint,
                                  UInt32                sourceFileLine,
                                  const FolioString&    sourceFileName, 
                                  const FolioString&    functionName, 
                                  const FolioString&    supplyString)
{
    // Format the supply.

    FolioOStringStream  outputStringStr;

    outputStringStr << FormatSupply (traceArea,
                                     supplyPoint,
                                     sourceFileLine, 
                                     sourceFileName, 
                                     functionName, 
                                     supplyString);

    // Get the Windows event log type.

    WORD    eventLogType = EVENTLOG_INFORMATION_TYPE;

    switch (supplyPoint)
    {
    case SUPPLY_POINT_ERROR:
        eventLogType = EVENTLOG_ERROR_TYPE;
        break;
    case SUPPLY_POINT_WARNING:
        eventLogType = EVENTLOG_WARNING_TYPE;
        break;
    case SUPPLY_POINT_INTERFACE_ENTRY:
    case SUPPLY_POINT_INTERFACE_EXIT:
    case SUPPLY_POINT_IMPLEMENTATION_ENTRY:
    case SUPPLY_POINT_IMPLEMENTATION_EXIT:
    case SUPPLY_POINT_EVENT_FIRED:
    case SUPPLY_POINT_EVENT_ARRIVED:
    case SUPPLY_POINT_GENERAL:
    default:
        eventLogType = EVENTLOG_INFORMATION_TYPE;
        break;
    } // Endswitch.

    LPCTSTR eventMsg = outputStringStr.str ().c_str ();

    // Report the event.

    ::ReportEvent (eventLogHandle,
                   eventLogType,
                   1,   // Folio category.
                   101, // Folio event id.
                   0,   // No user security id.
                   1,   // 1 string.
                   0,   // No binary data.
                   &(eventMsg),
                   0);  // No binary data.
} // Endproc.


/**
 * Method that is used to format a supply point.
 *
 * @param [in] traceArea
 * The trace area.
 * 
 * @param [in] supplyPoint
 * The supply point.
 * 
 * @param [in] sourceFileLine
 * The supply point source file line.
 *
 * @param [in] sourceFileName 
 * The supply point source file name.
 * 
 * @param [in] functionName
 * The function name.
 * 
 * @param [in] supplyString
 * The supply point string.
 *
 * @return
 * The formatted the supply point.
 */
FolioString TraceClient::FormatSupply (const FolioString&   traceArea,
                                       SupplyPoint          supplyPoint,
                                       UInt32               sourceFileLine,
                                       const FolioString&   sourceFileName, 
                                       const FolioString&   functionName, 
                                       const FolioString&   supplyString)
{
    FolioOStringStream  outputStringStr;

    // Format the supply point.

    outputStringStr << ::GetCurrentProcessId ()
                    << TXT(' ')
                    << ::GetCurrentThreadId ()
                    << TXT(' ')
                    << traceArea
                    << TXT(' ')
                    << GetSupplyPointDescription (supplyPoint)
                    << TXT(' ')
                    << sourceFileLine 
                    << TXT(' ')
                    << sourceFileName
                    << TXT(' ')
                    << functionName 
                    << TXT(' ')
                    << supplyString;

    return (outputStringStr.str ());
} // Endproc.


/**
 * Method that is used to obtain the description of a specified <b>SupplyPoint</b>.
 * 
 * @param [in] supplyPoint
 * The <b>SupplyPoint</b>.
 * 
 * @return
 * The description of the <b>SupplyPoint</b>.
 */
FolioString TraceClient::GetSupplyPointDescription (SupplyPoint supplyPoint)
{
    FolioOStringStream  outputStringStream;
    
    outputStringStream << supplyPoint << TXT('(');

    switch (supplyPoint)
    {
    case SUPPLY_POINT_INTERFACE_ENTRY:
        outputStringStream << TXT("InterfaceEntry");
        break;
    case SUPPLY_POINT_INTERFACE_EXIT:
        outputStringStream << TXT("InterfaceExit");
        break;
    case SUPPLY_POINT_IMPLEMENTATION_ENTRY:
        outputStringStream << TXT("ImplementationEntry");
        break;
    case SUPPLY_POINT_IMPLEMENTATION_EXIT:
        outputStringStream << TXT("ImplementationExit");
        break;
    case SUPPLY_POINT_EVENT_FIRED:
        outputStringStream << TXT("EventFired");
        break;
    case SUPPLY_POINT_EVENT_ARRIVED:
        outputStringStream << TXT("EventArrived");
        break;
    case SUPPLY_POINT_ERROR:
        outputStringStream << TXT("Error");
        break;
    case SUPPLY_POINT_WARNING:
        outputStringStream << TXT("Warning");
        break;
    case SUPPLY_POINT_GENERAL:
        outputStringStream << TXT("General");
        break;
    default:
        outputStringStream << FOLIO_UNKNOWN;
        break;
    } // Endswitch.

    outputStringStream << TXT(')');

    return (outputStringStream.str ());
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
