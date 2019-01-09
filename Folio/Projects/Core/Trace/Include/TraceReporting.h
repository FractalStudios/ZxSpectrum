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

#ifdef _DEBUG
    #ifdef FOLIO_ANSI
        #define AssertReport(line, file, txt)   _CrtDbgReport(_CRT_ASSERT, file, line, 0, txt)
        #define ErrorReport(line, file, txt)    _CrtDbgReport(_CRT_ERROR, file, line, 0, txt)
    #else
        #define AssertReport(line, file, txt)   _CrtDbgReportW(_CRT_ASSERT, file, line, 0, txt)
        #define ErrorReport(line, file, txt)    _CrtDbgReportW(_CRT_ERROR, file, line, 0, txt)
    #endif

    #define FOLIO_NOTIFY_TO_DEBUGGER(line, file, txt) \
        { \
            int previousMode = _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG); \
            if (AssertReport(line, file, txt) == 1) \
                _CrtDbgBreak(); \
            _CrtSetReportMode(_CRT_ASSERT, previousMode); \
        }

    #define FOLIO_NOTIFY_TO_WINDOW(line, file, txt) \
        { \
            int previousMode = _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_WNDW); \
            if (AssertReport(line, file, txt) == 1) \
                _CrtDbgBreak(); \
            _CrtSetReportMode(_CRT_ASSERT, previousMode); \
        }

    #define FOLIO_NOTIFY_TO_ALL(line, file, txt) \
        { \
            int previousMode = _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG | _CRTDBG_MODE_WNDW); \
            if (AssertReport(line, file, txt) == 1) \
                _CrtDbgBreak(); \
            _CrtSetReportMode(_CRT_ASSERT, previousMode); \
        }

    #define FOLIO_LOG_TO_DEBUGGER(line, file, txt) \
        { \
            int previousMode = _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG); \
            ErrorReport(line, file, txt); \
            _CrtSetReportMode(_CRT_ERROR, previousMode); \
        }

    #define FOLIO_LOG_TO_WINDOW(line, file, txt) \
        { \
            int previousMode = _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_WNDW); \
            ErrorReport(line, file, txt); \
            _CrtSetReportMode(_CRT_ERROR, previousMode); \
        }

    #define FOLIO_LOG_TO_ALL(line, file, txt) \
        { \
            int previousMode = _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG | _CRTDBG_MODE_WNDW); \
            ErrorReport(line, file, txt); \
            _CrtSetReportMode(_CRT_ERROR, previousMode); \
        }

    #define FOLIO_NOTIFY(line, file, txt)   FOLIO_NOTIFY_TO_WINDOW(line, file, txt);
#else
    #define FOLIO_NOTIFY_TO_DEBUGGER(line, file, txt)
    #define FOLIO_NOTIFY_TO_WINDOW(line, file, txt)
    #define FOLIO_NOTIFY_TO_ALL(line, file, txt)
    
    #define FOLIO_LOG_TO_DEBUGGER(line, file, txt)
    #define FOLIO_LOG_TO_WINDOW(line, file, txt)
    #define FOLIO_LOG_TO_ALL(line, file, txt)

    #define FOLIO_NOTIFY(line, file, txt)
#endif

// Macros for building a log stream.
#define FOLIO_LOG_STREAM            FolioOStringStream logStream; logStream.setf(std::ios_base::boolalpha);

// Macros for building log variables.
#define FOLIO_LOG_VARIABLE_STREAM   logStream << TXT(' ');
#define FOLIO_LOG_VARIABLE(v)       logStream << FOLIO_STREAM_OUT_VARIABLE(v);
#define FOLIO_LOG_MID_VARIABLE      logStream << FOLIO_MID_VARIABLE_PREFIX;

#define FOLIO_LOG_VARIABLES_1(v1)                                           FOLIO_LOG_VARIABLE_STREAM; FOLIO_LOG_VARIABLE(v1);
#define FOLIO_LOG_VARIABLES_2(v1, v2)                                       FOLIO_LOG_VARIABLES_1(v1); FOLIO_LOG_MID_VARIABLE; FOLIO_LOG_VARIABLE(v2);
#define FOLIO_LOG_VARIABLES_3(v1, v2, v3)                                   FOLIO_LOG_VARIABLES_2(v1, v2); FOLIO_LOG_MID_VARIABLE; FOLIO_LOG_VARIABLE(v3);
#define FOLIO_LOG_VARIABLES_4(v1, v2, v3, v4)                               FOLIO_LOG_VARIABLES_3(v1, v2, v3); FOLIO_LOG_MID_VARIABLE; FOLIO_LOG_VARIABLE(v4);
#define FOLIO_LOG_VARIABLES_5(v1, v2, v3, v4, v5)                           FOLIO_LOG_VARIABLES_4(v1, v2, v3, v4); FOLIO_LOG_MID_VARIABLE; FOLIO_LOG_VARIABLE(v5);
#define FOLIO_LOG_VARIABLES_6(v1, v2, v3, v4, v5, v6)                       FOLIO_LOG_VARIABLES_5(v1, v2, v3, v4, v5); FOLIO_LOG_MID_VARIABLE; FOLIO_LOG_VARIABLE(v6);
#define FOLIO_LOG_VARIABLES_7(v1, v2, v3, v4, v5, v6, v7)                   FOLIO_LOG_VARIABLES_6(v1, v2, v3, v4, v5, v6); FOLIO_LOG_MID_VARIABLE; FOLIO_LOG_VARIABLE(v7);
#define FOLIO_LOG_VARIABLES_8(v1, v2, v3, v4, v5, v6, v7, v8)               FOLIO_LOG_VARIABLES_7(v1, v2, v3, v4, v5, v6, v7); FOLIO_LOG_MID_VARIABLE; FOLIO_LOG_VARIABLE(v8);
#define FOLIO_LOG_VARIABLES_9(v1, v2, v3, v4, v5, v6, v7, v8, v9)           FOLIO_LOG_VARIABLES_8(v1, v2, v3, v4, v5, v6, v7, v8); FOLIO_LOG_MID_VARIABLE; FOLIO_LOG_VARIABLE(v9);
#define FOLIO_LOG_VARIABLES_10(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10)     FOLIO_LOG_VARIABLES_9(v1, v2, v3, v4, v5, v6, v7, v8, v9); FOLIO_LOG_MID_VARIABLE; FOLIO_LOG_VARIABLE(v10);

// Macros for building logs.
#define FOLIO_LOG(txt)  FOLIO_LOG_STREAM; logStream << txt;

#define FOLIO_LOG_1(txt, v1)                                        FOLIO_LOG(txt); FOLIO_LOG_VARIABLES_1(v1);
#define FOLIO_LOG_2(txt, v1, v2)                                    FOLIO_LOG_1(txt, v1); FOLIO_LOG_MID_VARIABLE; FOLIO_LOG_VARIABLES_1(v2);
#define FOLIO_LOG_3(txt, v1, v2, v3)                                FOLIO_LOG_1(txt, v1); FOLIO_LOG_MID_VARIABLE; FOLIO_LOG_VARIABLES_2(v2, v3);
#define FOLIO_LOG_4(txt, v1, v2, v3, v4)                            FOLIO_LOG_1(txt, v1); FOLIO_LOG_MID_VARIABLE; FOLIO_LOG_VARIABLES_3(v2, v3, v4);
#define FOLIO_LOG_5(txt, v1, v2, v3, v4, v5)                        FOLIO_LOG_1(txt, v1); FOLIO_LOG_MID_VARIABLE; FOLIO_LOG_VARIABLES_4(v2, v3, v4, v5);
#define FOLIO_LOG_6(txt, v1, v2, v3, v4, v5, v6)                    FOLIO_LOG_1(txt, v1); FOLIO_LOG_MID_VARIABLE; FOLIO_LOG_VARIABLES_5(v2, v3, v4, v5, v6);
#define FOLIO_LOG_7(txt, v1, v2, v3, v4, v5, v6, v7)                FOLIO_LOG_1(txt, v1); FOLIO_LOG_MID_VARIABLE; FOLIO_LOG_VARIABLES_6(v2, v3, v4, v5, v6, v7);
#define FOLIO_LOG_8(txt, v1, v2, v3, v4, v5, v6, v7, v8)            FOLIO_LOG_1(txt, v1); FOLIO_LOG_MID_VARIABLE; FOLIO_LOG_VARIABLES_7(v2, v3, v4, v5, v6, v7, v8);
#define FOLIO_LOG_9(txt, v1, v2, v3, v4, v5, v6, v7, v8, v9)        FOLIO_LOG_1(txt, v1); FOLIO_LOG_MID_VARIABLE; FOLIO_LOG_VARIABLES_8(v2, v3, v4, v5, v6, v7, v8, v9);
#define FOLIO_LOG_10(txt, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10)  FOLIO_LOG_1(txt, v1); FOLIO_LOG_MID_VARIABLE; FOLIO_LOG_VARIABLES_9(v2, v3, v4, v5, v6, v7, v8, v9, v10);

// Macros for building log calls.
#define FOLIO_LOG_CALL(call, status)    FOLIO_LOG_STREAM; logStream << TXT('\'') << call << TXT('\'') << TXT(" status") << FOLIO_VARIABLE_NAME_SUFFIX << Folio::GetFolioStatusDescription (status);

#define FOLIO_LOG_CALL_1(call, status, v1)                                              FOLIO_LOG_CALL(call, status); FOLIO_LOG_VARIABLES_1(v1);
#define FOLIO_LOG_CALL_2(call, status, v1, v2)                                          FOLIO_LOG_CALL_1(call, status, v1); FOLIO_LOG_MID_VARIABLE; FOLIO_LOG_VARIABLES_1(v2);
#define FOLIO_LOG_CALL_3(call, status, v1, v2, v3)                                      FOLIO_LOG_CALL_1(call, status, v1); FOLIO_LOG_MID_VARIABLE; FOLIO_LOG_VARIABLES_2(v2, v3);
#define FOLIO_LOG_CALL_4(call, status, v1, v2, v3, v4)                                  FOLIO_LOG_CALL_1(call, status, v1); FOLIO_LOG_MID_VARIABLE; FOLIO_LOG_VARIABLES_3(v2, v3, v4);
#define FOLIO_LOG_CALL_5(call, status, v1, v2, v3, v4, v5)                              FOLIO_LOG_CALL_1(call, status, v1); FOLIO_LOG_MID_VARIABLE; FOLIO_LOG_VARIABLES_4(v2, v3, v4, v5);
#define FOLIO_LOG_CALL_6(call, status, v1, v2, v3, v4, v5, v6)                          FOLIO_LOG_CALL_1(call, status, v1); FOLIO_LOG_MID_VARIABLE; FOLIO_LOG_VARIABLES_5(v2, v3, v4, v5, v6);
#define FOLIO_LOG_CALL_7(call, status, v1, v2, v3, v4, v5, v6, v7)                      FOLIO_LOG_CALL_1(call, status, v1); FOLIO_LOG_MID_VARIABLE; FOLIO_LOG_VARIABLES_6(v2, v3, v4, v5, v6, v7);
#define FOLIO_LOG_CALL_8(call, status, v1, v2, v3, v4, v5, v6, v7, v8)                  FOLIO_LOG_CALL_1(call, status, v1); FOLIO_LOG_MID_VARIABLE; FOLIO_LOG_VARIABLES_7(v2, v3, v4, v5, v6, v7, v8);
#define FOLIO_LOG_CALL_9(call, status, v1, v2, v3, v4, v5, v6, v7, v8, v9)              FOLIO_LOG_CALL_1(call, status, v1); FOLIO_LOG_MID_VARIABLE; FOLIO_LOG_VARIABLES_8(v2, v3, v4, v5, v6, v7, v8, v9);
#define FOLIO_LOG_CALL_10(call, status, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10)        FOLIO_LOG_CALL_1(call, status, v1); FOLIO_LOG_MID_VARIABLE; FOLIO_LOG_VARIABLES_9(v2, v3, v4, v5, v6, v7, v8, v9, v10);
#define FOLIO_LOG_CALL_11(call, status, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11)   FOLIO_LOG_CALL_1(call, status, v1); FOLIO_LOG_MID_VARIABLE; FOLIO_LOG_VARIABLES_10(v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);

// Macros to log an error.
#define FOLIO_LOG_ERROR(txt) \
    { \
        FOLIO_TRACE_ERROR(txt); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt); \
    }

#define FOLIO_LOG_ERROR_1(txt, v1) \
    { \
        FOLIO_LOG_1(txt, v1); \
        FOLIO_TRACE_ERROR(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_ERROR_2(txt, v1, v2) \
    { \
        FOLIO_LOG_2(txt, v1, v2); \
        FOLIO_TRACE_ERROR(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_ERROR_3(txt, v1, v2, v3) \
    { \
        FOLIO_LOG_3(txt, v1, v2, v3); \
        FOLIO_TRACE_ERROR(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_ERROR_4(txt, v1, v2, v3, v4) \
    { \
        FOLIO_LOG_4(txt, v1, v2, v3, v4); \
        FOLIO_TRACE_ERROR(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_ERROR_5(txt, v1, v2, v3, v4, v5) \
    { \
        FOLIO_LOG_5(txt, v1, v2, v3, v4, v5); \
        FOLIO_TRACE_ERROR(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_ERROR_6(txt, v1, v2, v3, v4, v5, v6) \
    { \
        FOLIO_LOG_6(txt, v1, v2, v3, v4, v5, v6); \
        FOLIO_TRACE_ERROR(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_ERROR_7(txt, v1, v2, v3, v4, v5, v6, v7) \
    { \
        FOLIO_LOG_7(txt, v1, v2, v3, v4, v5, v6, v7); \
        FOLIO_TRACE_ERROR(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_ERROR_8(txt, v1, v2, v3, v4, v5, v6, v7, v8) \
    { \
        FOLIO_LOG_8(txt, v1, v2, v3, v4, v5, v6, v7, v8); \
        FOLIO_TRACE_ERROR(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_ERROR_9(txt, v1, v2, v3, v4, v5, v6, v7, v8, v9) \
    { \
        FOLIO_LOG_9(txt, v1, v2, v3, v4, v5, v6, v7, v8, v9); \
        FOLIO_TRACE_ERROR(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_ERROR_10(txt, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10) \
    { \
        FOLIO_LOG_10(txt, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10); \
        FOLIO_TRACE_ERROR(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

// Macros to log a warning.
#define FOLIO_LOG_WARNING(txt) \
    { \
        FOLIO_TRACE_WARNING(txt); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, txt); \
    }

#define FOLIO_LOG_WARNING_1(txt, v1) \
    { \
        FOLIO_LOG_1(txt, v1); \
        FOLIO_TRACE_WARNING(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_WARNING_2(txt, v1, v2) \
    { \
        FOLIO_LOG_2(txt, v1, v2); \
        FOLIO_TRACE_WARNING(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_WARNING_3(txt, v1, v2, v3) \
    { \
        FOLIO_LOG_3(txt, v1, v2, v3); \
        FOLIO_TRACE_WARNING(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_WARNING_4(txt, v1, v2, v3, v4) \
    { \
        FOLIO_LOG_4(txt, v1, v2, v3, v4); \
        FOLIO_TRACE_WARNING(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_WARNING_5(txt, v1, v2, v3, v4, v5) \
    { \
        FOLIO_LOG_5(txt, v1, v2, v3, v4, v5); \
        FOLIO_TRACE_WARNING(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_WARNING_6(txt, v1, v2, v3, v4, v5, v6) \
    { \
        FOLIO_LOG_6(txt, v1, v2, v3, v4, v5, v6); \
        FOLIO_TRACE_WARNING(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_WARNING_7(txt, v1, v2, v3, v4, v5, v6, v7) \
    { \
        FOLIO_LOG_7(txt, v1, v2, v3, v4, v5, v6, v7); \
        FOLIO_TRACE_WARNING(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_WARNING_8(txt, v1, v2, v3, v4, v5, v6, v7, v8) \
    { \
        FOLIO_LOG_8(txt, v1, v2, v3, v4, v5, v6, v7, v8); \
        FOLIO_TRACE_WARNING(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_WARNING_9(txt, v1, v2, v3, v4, v5, v6, v7, v8, v9) \
    { \
        FOLIO_LOG_9(txt, v1, v2, v3, v4, v5, v6, v7, v8, v9); \
        FOLIO_TRACE_WARNING(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_WARNING_10(txt, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10) \
    { \
        FOLIO_LOG_10(txt, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10); \
        FOLIO_TRACE_WARNING(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

// Macros to log a call error.
#define FOLIO_LOG_CALL_ERROR(call, status) \
    { \
        FOLIO_LOG_CALL(call, status); \
        FOLIO_TRACE_ERROR(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_CALL_ERROR_1(call, status, v1) \
    { \
        FOLIO_LOG_CALL_1(call, status, v1); \
        FOLIO_TRACE_ERROR(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_CALL_ERROR_2(call, status, v1, v2) \
    { \
        FOLIO_LOG_CALL_2(call, status, v1, v2); \
        FOLIO_TRACE_ERROR(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_CALL_ERROR_3(call, status, v1, v2, v3) \
    { \
        FOLIO_LOG_CALL_3(call, status, v1, v2, v3); \
        FOLIO_TRACE_ERROR(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_CALL_ERROR_4(call, status, v1, v2, v3, v4) \
    { \
        FOLIO_LOG_CALL_4(call, status, v1, v2, v3, v4); \
        FOLIO_TRACE_ERROR(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_CALL_ERROR_5(call, status, v1, v2, v3, v4, v5) \
    { \
        FOLIO_LOG_CALL_5(call, status, v1, v2, v3, v4, v5); \
        FOLIO_TRACE_ERROR(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_CALL_ERROR_6(call, status, v1, v2, v3, v4, v5, v6) \
    { \
        FOLIO_LOG_CALL_6(call, status, v1, v2, v3, v4, v5, v6); \
        FOLIO_TRACE_ERROR(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_CALL_ERROR_7(call, status, v1, v2, v3, v4, v5, v6, v7) \
    { \
        FOLIO_LOG_CALL_7(call, status, v1, v2, v3, v4, v5, v6, v7); \
        FOLIO_TRACE_ERROR(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_CALL_ERROR_8(call, status, v1, v2, v3, v4, v5, v6, v7, v8) \
    { \
        FOLIO_LOG_CALL_8(call, status, v1, v2, v3, v4, v5, v6, v7, v8); \
        FOLIO_TRACE_ERROR(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_CALL_ERROR_9(call, status, v1, v2, v3, v4, v5, v6, v7, v8, v9) \
    { \
        FOLIO_LOG_CALL_9(call, status, v1, v2, v3, v4, v5, v6, v7, v8, v9); \
        FOLIO_TRACE_ERROR(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_CALL_ERROR_10(call, status, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10) \
    { \
        FOLIO_LOG_CALL_10(call, status, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10); \
        FOLIO_TRACE_ERROR(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_CALL_ERROR_11(call, status, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11) \
    { \
        FOLIO_LOG_CALL_11(call, status, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11); \
        FOLIO_TRACE_ERROR(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }


#define FOLIO_LOG_CALL_ERROR(call, status) \
    { \
        FOLIO_LOG_CALL(call, status); \
        FOLIO_TRACE_ERROR(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

// Macros to log a call warning.
#define FOLIO_LOG_CALL_WARNING_1(call, status, v1) \
    { \
        FOLIO_LOG_CALL_1(call, status, v1); \
        FOLIO_TRACE_WARNING(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_CALL_WARNING_2(call, status, v1, v2) \
    { \
        FOLIO_LOG_CALL_2(call, status, v1, v2); \
        FOLIO_TRACE_WARNING(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_CALL_WARNING_3(call, status, v1, v2, v3) \
    { \
        FOLIO_LOG_CALL_3(call, status, v1, v2, v3); \
        FOLIO_TRACE_WARNING(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_CALL_WARNING_4(call, status, v1, v2, v3, v4) \
    { \
        FOLIO_LOG_CALL_4(call, status, v1, v2, v3, v4); \
        FOLIO_TRACE_WARNING(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_CALL_WARNING_5(call, status, v1, v2, v3, v4, v5) \
    { \
        FOLIO_LOG_CALL_5(call, status, v1, v2, v3, v4, v5); \
        FOLIO_TRACE_WARNING(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_CALL_WARNING_6(call, status, v1, v2, v3, v4, v5, v6) \
    { \
        FOLIO_LOG_CALL_6(call, status, v1, v2, v3, v4, v5, v6); \
        FOLIO_TRACE_WARNING(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_CALL_WARNING_7(call, status, v1, v2, v3, v4, v5, v6, v7) \
    { \
        FOLIO_LOG_CALL_7(call, status, v1, v2, v3, v4, v5, v6, v7); \
        FOLIO_TRACE_WARNING(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_CALL_WARNING_8(call, status, v1, v2, v3, v4, v5, v6, v7, v8) \
    { \
        FOLIO_LOG_CALL_8(call, status, v1, v2, v3, v4, v5, v6, v7, v8); \
        FOLIO_TRACE_WARNING(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_CALL_WARNING_9(call, status, v1, v2, v3, v4, v5, v6, v7, v8, v9) \
    { \
        FOLIO_LOG_CALL_9(call, status, v1, v2, v3, v4, v5, v6, v7, v8, v9); \
        FOLIO_TRACE_WARNING(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

#define FOLIO_LOG_CALL_WARNING_10(call, status, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10) \
    { \
        FOLIO_LOG_CALL_10(call, status, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10); \
        FOLIO_TRACE_WARNING(logStream.str().c_str()); \
        FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, logStream.str().c_str()); \
    }

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/

