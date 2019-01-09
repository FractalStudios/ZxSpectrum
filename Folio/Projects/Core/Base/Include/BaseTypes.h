#pragma once

// C includes.
#include    <string.h>

#pragma pack(push, 1)

namespace Folio
{
                                         
#ifndef __cplusplus
    #ifndef bool
        #define bool int
    #endif

    #ifndef true
        #define true 1
    #endif

    #ifndef false
        #define false 0
    #endif
#endif

// Constant sized integer types.
typedef signed char        Int8;    ///< Folio 8-bit signed integer.
typedef short              Int16;   ///< Folio 16-bit signed integer.
typedef int                Int32;   ///< Folio 32-bit signed integer.
typedef long long          Int64;   ///< Folio 64-bit signed integer.

typedef unsigned char      UInt8;   ///< Folio 8-bit usigned integer.
typedef unsigned short     UInt16;  ///< Folio 16-bit usigned integer.
typedef unsigned int       UInt32;  ///< Folio 32-bit usigned integer.
typedef unsigned long long UInt64;  ///< Folio 64-bit usigned integer.
typedef unsigned char      Byte;    ///< Folio byte.

// Strings are 16-bit Unicode by default, but can be compiled as 8-bit ANSI by 
// defining FOLIO_ANSI.
#ifdef FOLIO_ANSI
    typedef char        Char;   ///< 8-bit ANSI character.

    #define TXT(x)      x

    #define STRCAT      ::strcat
    #define STRCPY      ::strcpy
    #define STRNCPY     ::strncpy
    #define STRLEN      ::strlen
    #define STRCMP      ::strcmp
    #define STRNCMP     ::strncmp
    #define STRICMP     ::_stricmp
    #define STRNICMP    ::_strnicmp
    #define STRCHR      ::strchr
    #define STRRCHR     ::strrchr
    #define STRTOL      ::strtol
    #define SNPRINTF    ::_snprintf

    #define STRCAT_S    ::strcat_s
    #define STRCPY_S    ::strcpy_s
    #define STRNCPY_S   ::strncpy_s
    #define STRLEN_S    ::strlen_s
    #define STRCMP_S    ::strcmp_s
    #define STRNCMP_S   ::strncmp_s
    #define STRICMP_S   ::_stricmp_s
    #define STRNICMP_S  ::_strnicmp_s
    #define STRCHR_S    ::strchr_s
    #define STRRCHR_S   ::strrchr_s
    #define STRTOL_S    ::strtol_s
    #define SNPRINTF_S  ::_snprintf_s
#else
    typedef wchar_t     Char;   ///< 16-bit Unicode character.

    #define TXT(x)      L##x

    #define STRCAT      ::wcscat
    #define STRCPY      ::wcscpy
    #define STRNCPY     ::wcsncpy
    #define STRLEN      ::wcslen
    #define STRCMP      ::wcscmp
    #define STRNCMP     ::wcsncmp
    #define STRICMP     ::_wcsicmp
    #define STRNICMP    ::_wcsnicmp
    #define STRCHR      ::wcschr
    #define STRRCHR     ::wcsrchr
    #define STRTOL      ::wcstol
    #define SNPRINTF    ::swprintf

    #define STRCAT_S    ::wcscat_s
    #define STRCPY_S    ::wcscpy_s
    #define STRNCPY_S   ::wcsncpy_s
    #define STRLEN_S    ::wcslen_s
    #define STRCMP_S    ::wcscmp_s
    #define STRNCMP_S   ::wcsncmp_s
    #define STRICMP_S   ::_wcsicmp_s
    #define STRNICMP_S  ::_wcsnicmp_s
    #define STRCHR_S    ::wcschr_s
    #define STRRCHR_S   ::wcsrchr_s
    #define STRTOL_S    ::wcstol_s
    #define SNPRINTF_S  ::swprintf_s
#endif

// Miscellaneous types.
typedef Char*   FolioCString;   ///< Folio C string.
typedef void*   FolioHandle;    ///< Folio handle.

// Definitions to factor out common text from all approaches.
#define FOLIO_CONTAINER_PREFIX          TXT('[')
#define FOLIO_CONTAINER_SUFFIX          TXT(']')

#define FOLIO_FIRST_VARIABLE_PREFIX     TXT('{')
#define FOLIO_MID_VARIABLE_PREFIX       TXT(',')
#define FOLIO_LAST_VARIABLE_SUFFIX      TXT('}')
#define FOLIO_VARIABLE_NAME_SUFFIX      TXT('=')
#define FOLIO_VARIABLE_TYPE_PREFIX      TXT(':')

#define FOLIO_FIRST_MEMBER_PREFIX       FOLIO_FIRST_VARIABLE_PREFIX
#define FOLIO_MID_MEMBER_PREFIX         FOLIO_MID_VARIABLE_PREFIX  
#define FOLIO_LAST_MEMBER_SUFFIX        FOLIO_LAST_VARIABLE_SUFFIX 
#define FOLIO_MEMBER_NAME_SUFFIX        FOLIO_VARIABLE_NAME_SUFFIX 
#define FOLIO_MEMBER_TYPE_PREFIX        FOLIO_VARIABLE_TYPE_PREFIX 

#define FOLIO_UNKNOWN                   TXT("Unknown")
#define FOLIO_UNKNOWN_TYPE              FOLIO_UNKNOWN
#define FOLIO_UNKNOWN_VARIABLE          FOLIO_UNKNOWN
#define FOLIO_UNKNOWN_ENUM              FOLIO_UNKNOWN

// Miscellaneous definitions.
#define FOLIO_CALL      _stdcall
#define FOLIO_UNALIGNED UNALIGNED

#pragma pack(pop)

} // Endnamespace.

/******************************* End of File *******************************/
