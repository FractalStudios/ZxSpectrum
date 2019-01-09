#pragma once

// "Home-made" includes.
#include    <Base.h>
#include    <StaticMap.h>
#include    "TraceClient.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Trace
{

// If the FOLIO_TRACE_AREA isn't set, there's no point in continuing.
#ifndef FOLIO_TRACE_AREA
    #error You must define the FOLIO_TRACE_AREA in the project settings.
#endif

// Macros for building trace variables.
#define FOLIO_TRACE_VARIABLE_STREAM     FolioOStringStream variablesStream; variablesStream.setf(std::ios_base::boolalpha);
#define FOLIO_TRACE_VARIABLE(v)         variablesStream << FOLIO_STREAM_OUT_VARIABLE(v);
#define FOLIO_TRACE_MID_VARIABLE        variablesStream << FOLIO_MID_VARIABLE_PREFIX;

#define FOLIO_TRACE_VARIABLES_1(v1)                                 FOLIO_TRACE_VARIABLE_STREAM; FOLIO_TRACE_VARIABLE(v1);
#define FOLIO_TRACE_VARIABLES_2(v1, v2)                             FOLIO_TRACE_VARIABLES_1(v1); FOLIO_TRACE_MID_VARIABLE; FOLIO_TRACE_VARIABLE(v2);
#define FOLIO_TRACE_VARIABLES_3(v1, v2, v3)                         FOLIO_TRACE_VARIABLES_2(v1, v2); FOLIO_TRACE_MID_VARIABLE; FOLIO_TRACE_VARIABLE(v3);
#define FOLIO_TRACE_VARIABLES_4(v1, v2, v3, v4)                     FOLIO_TRACE_VARIABLES_3(v1, v2, v3); FOLIO_TRACE_MID_VARIABLE; FOLIO_TRACE_VARIABLE(v4);
#define FOLIO_TRACE_VARIABLES_5(v1, v2, v3, v4, v5)                 FOLIO_TRACE_VARIABLES_4(v1, v2, v3, v4); FOLIO_TRACE_MID_VARIABLE; FOLIO_TRACE_VARIABLE(v5);
#define FOLIO_TRACE_VARIABLES_6(v1, v2, v3, v4, v5, v6)             FOLIO_TRACE_VARIABLES_5(v1, v2, v3, v4, v5); FOLIO_TRACE_MID_VARIABLE; FOLIO_TRACE_VARIABLE(v6);
#define FOLIO_TRACE_VARIABLES_7(v1, v2, v3, v4, v5, v6, v7)         FOLIO_TRACE_VARIABLES_6(v1, v2, v3, v4, v5, v6); FOLIO_TRACE_MID_VARIABLE; FOLIO_TRACE_VARIABLE(v7);
#define FOLIO_TRACE_VARIABLES_8(v1, v2, v3, v4, v5, v6, v7, v8)     FOLIO_TRACE_VARIABLES_7(v1, v2, v3, v4, v5, v6, v7); FOLIO_TRACE_MID_VARIABLE; FOLIO_TRACE_VARIABLE(v8);
#define FOLIO_TRACE_VARIABLES_9(v1, v2, v3, v4, v5, v6, v7, v8, v9) FOLIO_TRACE_VARIABLES_8(v1, v2, v3, v4, v5, v6, v7, v8); FOLIO_TRACE_MID_VARIABLE; FOLIO_TRACE_VARIABLE(v9);

// Macros for building trace returns.
#define FOLIO_TRACE_RETURN_STREAM       FolioOStringStream returnStream; returnStream.setf(std::ios_base::boolalpha);
#define FOLIO_TRACE_RETURN(r)           returnStream << TXT("Return") << FOLIO_VARIABLE_NAME_SUFFIX << r << FOLIO_VARIABLE_TYPE_PREFIX << GetTypeDescription(r);

// Macros to trace interface entry.
#define FOLIO_TRACE_INTERFACE_ENTRY \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsInterfaceEntryRequired()) \
        { \
            traceClient.InterfaceEntry(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, TXT("")); \
        } \
    }
#define FOLIO_TRACE_INTERFACE_ENTRY_1(v1) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsInterfaceEntryRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_1(v1); \
            traceClient.InterfaceEntry(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_INTERFACE_ENTRY_2(v1, v2) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsInterfaceEntryRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_2(v1, v2); \
            traceClient.InterfaceEntry(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_INTERFACE_ENTRY_3(v1, v2, v3) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsInterfaceEntryRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_3(v1, v2, v3); \
            traceClient.InterfaceEntry(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_INTERFACE_ENTRY_4(v1, v2, v3, v4) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsInterfaceEntryRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_4(v1, v2, v3, v4); \
            traceClient.InterfaceEntry(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_INTERFACE_ENTRY_5(v1, v2, v3, v4, v5) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsInterfaceEntryRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_5(v1, v2, v3, v4, v5); \
            traceClient.InterfaceEntry(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_INTERFACE_ENTRY_6(v1, v2, v3, v4, v5, v6) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsInterfaceEntryRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_6(v1, v2, v3, v4, v5, v6); \
            traceClient.InterfaceEntry(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_INTERFACE_ENTRY_7(v1, v2, v3, v4, v5, v6, v7) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsInterfaceEntryRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_7(v1, v2, v3, v4, v5, v6, v7); \
            traceClient.InterfaceEntry(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_INTERFACE_ENTRY_8(v1, v2, v3, v4, v5, v6, v7, v8) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsInterfaceEntryRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_8(v1, v2, v3, v4, v5, v6, v7, v8); \
            traceClient.InterfaceEntry(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_INTERFACE_ENTRY_9(v1, v2, v3, v4, v5, v6, v7, v8, v9) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsInterfaceEntryRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_9(v1, v2, v3, v4, v5, v6, v7, v8, v9); \
            traceClient.InterfaceEntry(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str()); \
        } \
    }

// Macros to trace interface exit.
#define FOLIO_TRACE_INTERFACE_EXIT \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsInterfaceExitRequired()) \
        { \
            traceClient.InterfaceExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, TXT(""), TXT("")); \
        } \
    }
#define FOLIO_TRACE_INTERFACE_EXIT_1(v1) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsInterfaceExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_1(v1); \
            traceClient.InterfaceExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), TXT("")); \
        } \
    }
#define FOLIO_TRACE_INTERFACE_EXIT_2(v1, v2) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsInterfaceExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_2(v1, v2); \
            traceClient.InterfaceExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), TXT("")); \
        } \
    }
#define FOLIO_TRACE_INTERFACE_EXIT_3(v1, v2, v3) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsInterfaceExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_3(v1, v2, v3); \
            traceClient.InterfaceExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), TXT("")); \
        } \
    }
#define FOLIO_TRACE_INTERFACE_EXIT_4(v1, v2, v3, v4) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsInterfaceExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_4(v1, v2, v3, v4); \
            traceClient.InterfaceExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), TXT("")); \
        } \
    }
#define FOLIO_TRACE_INTERFACE_EXIT_5(v1, v2, v3, v4, v5) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsInterfaceExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_5(v1, v2, v3, v4, v5); \
            traceClient.InterfaceExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), TXT("")); \
        } \
    }
#define FOLIO_TRACE_INTERFACE_EXIT_6(v1, v2, v3, v4, v5, v6) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsInterfaceExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_6(v1, v2, v3, v4, v5, v6); \
            traceClient.InterfaceExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), TXT("")); \
        } \
    }
#define FOLIO_TRACE_INTERFACE_EXIT_7(v1, v2, v3, v4, v5, v6, v7) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsInterfaceExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_7(v1, v2, v3, v4, v5, v6, v7); \
            traceClient.InterfaceExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), TXT("")); \
        } \
    }
#define FOLIO_TRACE_INTERFACE_EXIT_8(v1, v2, v3, v4, v5, v6, v7, v8) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsInterfaceExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_8(v1, v2, v3, v4, v5, v6, v7, v8); \
            traceClient.InterfaceExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), TXT("")); \
        } \
    }
#define FOLIO_TRACE_INTERFACE_EXIT_9(v1, v2, v3, v4, v5, v6, v7, v8, v9) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsInterfaceExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_9(v1, v2, v3, v4, v5, v6, v7, v8, v9); \
            traceClient.InterfaceExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), TXT("")); \
        } \
    }

// Macros to trace interface exit with return.
#define FOLIO_TRACE_INTERFACE_EXIT_RET(r) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsInterfaceExitRequired()) \
        { \
            FOLIO_TRACE_RET(r); \
            traceClient.InterfaceExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, TXT(""), returnStream.str()); \
        } \
    }
#define FOLIO_TRACE_INTERFACE_EXIT_RETURN_1(r, v1) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsInterfaceExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_1(v1); \
            FOLIO_TRACE_RET(r); \
            traceClient.InterfaceExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), returnStream.str()); \
        } \
    }
#define FOLIO_TRACE_INTERFACE_EXIT_RETURN_2(r, v1, v2) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsInterfaceExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_2(v1, v2); \
            FOLIO_TRACE_RET(r); \
            traceClient.InterfaceExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), returnStream.str()); \
        } \
    }
#define FOLIO_TRACE_INTERFACE_EXIT_RETURN_3(r, v1, v2, v3) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsInterfaceExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_3(v1, v2, v3); \
            FOLIO_TRACE_RET(r); \
            traceClient.InterfaceExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), returnStream.str()); \
        } \
    }
#define FOLIO_TRACE_INTERFACE_EXIT_RETURN_4(r, v1, v2, v3, v4) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsInterfaceExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_4(v1, v2, v3, v4); \
            FOLIO_TRACE_RET(r); \
            traceClient.InterfaceExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), returnStream.str()); \
        } \
    }
#define FOLIO_TRACE_INTERFACE_EXIT_RETURN_5(r, v1, v2, v3, v4, v5) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsInterfaceExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_5(v1, v2, v3, v4, v5); \
            FOLIO_TRACE_RET(r); \
            traceClient.InterfaceExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), returnStream.str()); \
        } \
    }
#define FOLIO_TRACE_INTERFACE_EXIT_RETURN_6(r, v1, v2, v3, v4, v5, v6) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsInterfaceExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_6(v1, v2, v3, v4, v5, v6); \
            FOLIO_TRACE_RET(r); \
            traceClient.InterfaceExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), returnStream.str()); \
        } \
    }
#define FOLIO_TRACE_INTERFACE_EXIT_RETURN_7(r, v1, v2, v3, v4, v5, v6, v7) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsInterfaceExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_7(v1, v2, v3, v4, v5, v6, v7); \
            FOLIO_TRACE_RET(r); \
            traceClient.InterfaceExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), returnStream.str()); \
        } \
    }
#define FOLIO_TRACE_INTERFACE_EXIT_RETURN_8(r, v1, v2, v3, v4, v5, v6, v7, v8) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsInterfaceExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_8(v1, v2, v3, v4, v5, v6, v7, v8); \
            FOLIO_TRACE_RET(r); \
            traceClient.InterfaceExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), returnStream.str()); \
        } \
    }
#define FOLIO_TRACE_INTERFACE_EXIT_RETURN_9(r, v1, v2, v3, v4, v5, v6, v7, v8, v9) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsInterfaceExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_9(v1, v2, v3, v4, v5, v6, v7, v8, v9); \
            FOLIO_TRACE_RET(r); \
            traceClient.InterfaceExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), returnStream.str()); \
        } \
    }

// Macros to trace implementation entry.
#define FOLIO_TRACE_IMPLEMENTATION_ENTRY \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsImplementationEntryRequired()) \
        { \
            traceClient.ImplementationEntry(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, TXT("")); \
        } \
    }
#define FOLIO_TRACE_IMPLEMENTATION_ENTRY_1(v1) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsImplementationEntryRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_1(v1); \
            traceClient.ImplementationEntry(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_IMPLEMENTATION_ENTRY_2(v1, v2) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsImplementationEntryRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_2(v1, v2); \
            traceClient.ImplementationEntry(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_IMPLEMENTATION_ENTRY_3(v1, v2, v3) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsImplementationEntryRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_3(v1, v2, v3); \
            traceClient.ImplementationEntry(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_IMPLEMENTATION_ENTRY_4(v1, v2, v3, v4) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsImplementationEntryRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_4(v1, v2, v3, v4); \
            traceClient.ImplementationEntry(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_IMPLEMENTATION_ENTRY_5(v1, v2, v3, v4, v5) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsImplementationEntryRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_5(v1, v2, v3, v4, v5); \
            traceClient.ImplementationEntry(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_IMPLEMENTATION_ENTRY_6(v1, v2, v3, v4, v5, v6) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsImplementationEntryRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_6(v1, v2, v3, v4, v5, v6); \
            traceClient.ImplementationEntry(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_IMPLEMENTATION_ENTRY_7(v1, v2, v3, v4, v5, v6, v7) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsImplementationEntryRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_7(v1, v2, v3, v4, v5, v6, v7); \
            traceClient.ImplementationEntry(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_IMPLEMENTATION_ENTRY_8(v1, v2, v3, v4, v5, v6, v7, v8) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsImplementationEntryRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_8(v1, v2, v3, v4, v5, v6, v7, v8); \
            traceClient.ImplementationEntry(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_IMPLEMENTATION_ENTRY_9(v1, v2, v3, v4, v5, v6, v7, v8, v9) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsImplementationEntryRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_9(v1, v2, v3, v4, v5, v6, v7, v8, v9); \
            traceClient.ImplementationEntry(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str()); \
        } \
    }

// Macros to trace implementation exit.
#define FOLIO_TRACE_IMPLEMENTATION_EXIT \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsImplementationExitRequired()) \
        { \
            traceClient.ImplementationExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, TXT(""), TXT("")); \
        } \
    }
#define FOLIO_TRACE_IMPLEMENTATION_EXIT_1(v1) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsImplementationExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_1(v1); \
            traceClient.ImplementationExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), TXT("")); \
        } \
    }
#define FOLIO_TRACE_IMPLEMENTATION_EXIT_2(v1, v2) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsImplementationExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_2(v1, v2); \
            traceClient.ImplementationExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), TXT("")); \
        } \
    }
#define FOLIO_TRACE_IMPLEMENTATION_EXIT_3(v1, v2, v3) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsImplementationExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_3(v1, v2, v3); \
            traceClient.ImplementationExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), TXT("")); \
        } \
    }
#define FOLIO_TRACE_IMPLEMENTATION_EXIT_4(v1, v2, v3, v4) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsImplementationExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_4(v1, v2, v3, v4); \
            traceClient.ImplementationExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), TXT("")); \
        } \
    }
#define FOLIO_TRACE_IMPLEMENTATION_EXIT_5(v1, v2, v3, v4, v5) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsImplementationExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_5(v1, v2, v3, v4, v5); \
            traceClient.ImplementationExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), TXT("")); \
        } \
    }
#define FOLIO_TRACE_IMPLEMENTATION_EXIT_6(v1, v2, v3, v4, v5, v6) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsImplementationExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_6(v1, v2, v3, v4, v5, v6); \
            traceClient.ImplementationExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), TXT("")); \
        } \
    }
#define FOLIO_TRACE_IMPLEMENTATION_EXIT_7(v1, v2, v3, v4, v5, v6, v7) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsImplementationExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_7(v1, v2, v3, v4, v5, v6, v7); \
            traceClient.ImplementationExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), TXT("")); \
        } \
    }
#define FOLIO_TRACE_IMPLEMENTATION_EXIT_8(v1, v2, v3, v4, v5, v6, v7, v8) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsImplementationExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_8(v1, v2, v3, v4, v5, v6, v7, v8); \
            traceClient.ImplementationExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), TXT("")); \
        } \
    }
#define FOLIO_TRACE_IMPLEMENTATION_EXIT_9(v1, v2, v3, v4, v5, v6, v7, v8, v9) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsImplementationExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_9(v1, v2, v3, v4, v5, v6, v7, v8, v9); \
            traceClient.ImplementationExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), TXT("")); \
        } \
    }

// Macros to trace implementation exit with return.
#define FOLIO_TRACE_IMPLEMENTATION_EXIT_RET(r) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsImplementationExitRequired()) \
        { \
            FOLIO_TRACE_RET(r); \
            traceClient.ImplementationExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, TXT(""), returnStream.str()); \
        } \
    }
#define FOLIO_TRACE_IMPLEMENTATION_EXIT_RETURN_1(r, v1) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsImplementationExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_1(v1); \
            FOLIO_TRACE_RET(r); \
            traceClient.ImplementationExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), returnStream.str()); \
        } \
    }
#define FOLIO_TRACE_IMPLEMENTATION_EXIT_RETURN_2(r, v1, v2) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsImplementationExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_2(v1, v2); \
            FOLIO_TRACE_RET(r); \
            traceClient.ImplementationExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), returnStream.str()); \
        } \
    }
#define FOLIO_TRACE_IMPLEMENTATION_EXIT_RETURN_3(r, v1, v2, v3) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsImplementationExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_3(v1, v2, v3); \
            FOLIO_TRACE_RET(r); \
            traceClient.ImplementationExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), returnStream.str()); \
        } \
    }
#define FOLIO_TRACE_IMPLEMENTATION_EXIT_RETURN_4(r, v1, v2, v3, v4) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsImplementationExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_4(v1, v2, v3, v4); \
            FOLIO_TRACE_RET(r); \
            traceClient.ImplementationExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), returnStream.str()); \
        } \
    }
#define FOLIO_TRACE_IMPLEMENTATION_EXIT_RETURN_5(r, v1, v2, v3, v4, v5) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsImplementationExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_5(v1, v2, v3, v4, v5); \
            FOLIO_TRACE_RET(r); \
            traceClient.ImplementationExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), returnStream.str()); \
        } \
    }
#define FOLIO_TRACE_IMPLEMENTATION_EXIT_RETURN_6(r, v1, v2, v3, v4, v5, v6) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsImplementationExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_6(v1, v2, v3, v4, v5, v6); \
            FOLIO_TRACE_RET(r); \
            traceClient.ImplementationExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), returnStream.str()); \
        } \
    }
#define FOLIO_TRACE_IMPLEMENTATION_EXIT_RETURN_7(r, v1, v2, v3, v4, v5, v6, v7) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsImplementationExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_7(v1, v2, v3, v4, v5, v6, v7); \
            FOLIO_TRACE_RET(r); \
            traceClient.ImplementationExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), returnStream.str()); \
        } \
    }
#define FOLIO_TRACE_IMPLEMENTATION_EXIT_RETURN_8(r, v1, v2, v3, v4, v5, v6, v7, v8) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsImplementationExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_8(v1, v2, v3, v4, v5, v6, v7, v8); \
            FOLIO_TRACE_RET(r); \
            traceClient.ImplementationExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), returnStream.str()); \
        } \
    }
#define FOLIO_TRACE_IMPLEMENTATION_EXIT_RETURN_9(r, v1, v2, v3, v4, v5, v6, v7, v8, v9) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsImplementationExitRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_9(v1, v2, v3, v4, v5, v6, v7, v8, v9); \
            FOLIO_TRACE_RET(r); \
            traceClient.ImplementationExit(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, variablesStream.str(), returnStream.str()); \
        } \
    }

// Macros to trace event fired.
#define FOLIO_TRACE_EVENT_ARRIVED(txt) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsEventFiredRequired()) \
        { \
            traceClient.EventFired(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, TXT("")); \
        } \
    }
#define FOLIO_TRACE_EVENT_ARRIVED_1(txt, v1) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsEventFiredRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_1(v1); \
            traceClient.EventFired(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_EVENT_ARRIVED_2(txt, v1, v2) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsEventFiredRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_2(v1, v2); \
            traceClient.EventFired(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_EVENT_ARRIVED_3(txt, v1, v2, v3) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsEventFiredRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_3(v1, v2, v3); \
            traceClient.EventFired(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_EVENT_ARRIVED_4(txt, v1, v2, v3, v4) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsEventFiredRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_4(v1, v2, v3, v4); \
            traceClient.EventFired(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_EVENT_ARRIVED_5(txt, v1, v2, v3, v4, v5) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsEventFiredRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_5(v1, v2, v3, v4, v5); \
            traceClient.EventFired(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_EVENT_ARRIVED_6(txt, v1, v2, v3, v4, v5, v6) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsEventFiredRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_6(v1, v2, v3, v4, v5, v6); \
            traceClient.EventFired(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_EVENT_ARRIVED_7(txt, v1, v2, v3, v4, v5, v6, v7) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsEventFiredRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_7(v1, v2, v3, v4, v5, v6, v7); \
            traceClient.EventFired(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_EVENT_ARRIVED_8(txt, v1, v2, v3, v4, v5, v6, v7, v8) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsEventFiredRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_8(v1, v2, v3, v4, v5, v6, v7, v8); \
            traceClient.EventFired(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_EVENT_ARRIVED_9(txt, v1, v2, v3, v4, v5, v6, v7, v8, v9) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsEventFiredRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_9(v1, v2, v3, v4, v5, v6, v7, v8, v9); \
            traceClient.EventFired(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }

// Macros to trace error.
#define FOLIO_TRACE_ERROR(txt) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsErrorRequired()) \
        { \
            traceClient.Error(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, TXT("")); \
        } \
    }
#define FOLIO_TRACE_ERROR_1(txt, v1) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsErrorRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_1(v1); \
            traceClient.Error(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_ERROR_2(txt, v1, v2) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsErrorRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_2(v1, v2); \
            traceClient.Error(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_ERROR_3(txt, v1, v2, v3) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsErrorRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_3(v1, v2, v3); \
            traceClient.Error(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_ERROR_4(txt, v1, v2, v3, v4) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsErrorRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_4(v1, v2, v3, v4); \
            traceClient.Error(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_ERROR_5(txt, v1, v2, v3, v4, v5) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsErrorRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_5(v1, v2, v3, v4, v5); \
            traceClient.Error(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_ERROR_6(txt, v1, v2, v3, v4, v5, v6) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsErrorRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_6(v1, v2, v3, v4, v5, v6); \
            traceClient.Error(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_ERROR_7(txt, v1, v2, v3, v4, v5, v6, v7) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsErrorRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_7(v1, v2, v3, v4, v5, v6, v7); \
            traceClient.Error(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_ERROR_8(txt, v1, v2, v3, v4, v5, v6, v7, v8) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsErrorRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_8(v1, v2, v3, v4, v5, v6, v7, v8); \
            traceClient.Error(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_ERROR_9(txt, v1, v2, v3, v4, v5, v6, v7, v8, v9) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsErrorRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_9(v1, v2, v3, v4, v5, v6, v7, v8, v9); \
            traceClient.Error(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }

// Macros to trace warning.
#define FOLIO_TRACE_WARNING(txt) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsWarningRequired()) \
        { \
            traceClient.Warning(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, TXT("")); \
        } \
    }
#define FOLIO_TRACE_WARNING_1(txt, v1) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsWarningRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_1(v1); \
            traceClient.Warning(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_WARNING_2(txt, v1, v2) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsWarningRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_2(v1, v2); \
            traceClient.Warning(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_WARNING_3(txt, v1, v2, v3) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsWarningRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_3(v1, v2, v3); \
            traceClient.Warning(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_WARNING_4(txt, v1, v2, v3, v4) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsWarningRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_4(v1, v2, v3, v4); \
            traceClient.Warning(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_WARNING_5(txt, v1, v2, v3, v4, v5) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsWarningRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_5(v1, v2, v3, v4, v5); \
            traceClient.Warning(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_WARNING_6(txt, v1, v2, v3, v4, v5, v6) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsWarningRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_6(v1, v2, v3, v4, v5, v6); \
            traceClient.Warning(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_WARNING_7(txt, v1, v2, v3, v4, v5, v6, v7) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsWarningRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_7(v1, v2, v3, v4, v5, v6, v7); \
            traceClient.Warning(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_WARNING_8(txt, v1, v2, v3, v4, v5, v6, v7, v8) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsWarningRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_8(v1, v2, v3, v4, v5, v6, v7, v8); \
            traceClient.Warning(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_WARNING_9(txt, v1, v2, v3, v4, v5, v6, v7, v8, v9) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsWarningRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_9(v1, v2, v3, v4, v5, v6, v7, v8, v9); \
            traceClient.Warning(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }

// Macros to trace general.
#define FOLIO_TRACE_GENERAL(txt) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsGeneralRequired()) \
        { \
            traceClient.General(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, TXT("")); \
        } \
    }
#define FOLIO_TRACE_GENERAL_1(txt, v1) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsGeneralRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_1(v1); \
            traceClient.General(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_GENERAL_2(txt, v1, v2) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsGeneralRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_2(v1, v2); \
            traceClient.General(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_GENERAL_3(txt, v1, v2, v3) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsGeneralRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_3(v1, v2, v3); \
            traceClient.General(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_GENERAL_4(txt, v1, v2, v3, v4) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsGeneralRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_4(v1, v2, v3, v4); \
            traceClient.General(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_GENERAL_5(txt, v1, v2, v3, v4, v5) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsGeneralRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_5(v1, v2, v3, v4, v5); \
            traceClient.General(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_GENERAL_6(txt, v1, v2, v3, v4, v5, v6) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsGeneralRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_6(v1, v2, v3, v4, v5, v6); \
            traceClient.General(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_GENERAL_7(txt, v1, v2, v3, v4, v5, v6, v7) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsGeneralRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_7(v1, v2, v3, v4, v5, v6, v7); \
            traceClient.General(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_GENERAL_8(txt, v1, v2, v3, v4, v5, v6, v7, v8) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsGeneralRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_8(v1, v2, v3, v4, v5, v6, v7, v8); \
            traceClient.General(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }
#define FOLIO_TRACE_GENERAL_9(txt, v1, v2, v3, v4, v5, v6, v7, v8, v9) \
    { \
        Folio::Core::Trace::TraceClient traceClient(FOLIO_WIDEN(FOLIO_TRACE_AREA), FOLIO_SOURCE_FILE_FUNCTION_NAME); \
        if (traceClient.IsGeneralRequired()) \
        { \
            FOLIO_TRACE_VARIABLES_9(v1, v2, v3, v4, v5, v6, v7, v8, v9); \
            traceClient.General(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt, variablesStream.str()); \
        } \
    }

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
