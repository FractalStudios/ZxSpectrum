#pragma once

// "Home-made" includes.
#include    "BaseTypes.h"

#pragma pack(push, 1)

namespace Folio
{

// Macros to aid streaming.
#define FOLIO_STREAM_OUT_VARIABLE(v)                    TXT(#v) << FOLIO_VARIABLE_NAME_SUFFIX << v << FOLIO_VARIABLE_TYPE_PREFIX  << GetTypeDescription(v)
#define FOLIO_STREAM_OUT_MEMBER(_class, m)              TXT(#m) << FOLIO_MEMBER_NAME_SUFFIX << _class.m << FOLIO_MEMBER_TYPE_PREFIX  << GetTypeDescription(_class.m)
#define FOLIO_STREAM_OUT_TO_HEX(value)                  TXT("0x") << std::setfill(TXT('0')) << std::hex << std::setw(8) << (value)

// Macros to stream variables.
#define FOLIO_STREAM_ONLY_VARIABLE(stream, v)           stream << FOLIO_FIRST_VARIABLE_PREFIX; stream << FOLIO_STREAM_OUT_VARIABLE(v); stream << FOLIO_LAST_VARIABLE_SUFFIX; 
#define FOLIO_STREAM_FIRST_VARIABLE(stream, v)          stream << FOLIO_FIRST_VARIABLE_PREFIX; stream << FOLIO_STREAM_OUT_VARIABLE(v); stream << FOLIO_MID_VARIABLE_PREFIX;
#define FOLIO_STREAM_VARIABLE(stream, v)                stream << FOLIO_STREAM_OUT_VARIABLE(v); stream << FOLIO_MID_VARIABLE_PREFIX; 
#define FOLIO_STREAM_LAST_VARIABLE(stream, v)           stream << FOLIO_STREAM_OUT_VARIABLE(v); stream << FOLIO_LAST_VARIABLE_SUFFIX;

// Macros to stream class members.
#define FOLIO_STREAM_ONLY_MEMBER(stream, _class, m)     stream << FOLIO_FIRST_MEMBER_PREFIX; stream << FOLIO_STREAM_OUT_MEMBER(_class, m); stream << FOLIO_LAST_MEMBER_SUFFIX; 
#define FOLIO_STREAM_FIRST_MEMBER(stream, _class, m)    stream << FOLIO_FIRST_MEMBER_PREFIX; stream << FOLIO_STREAM_OUT_MEMBER(_class, m); stream << FOLIO_MID_MEMBER_PREFIX;
#define FOLIO_STREAM_MEMBER(stream, _class, m)          stream << FOLIO_STREAM_OUT_MEMBER(_class, m); stream << FOLIO_MID_MEMBER_PREFIX; 
#define FOLIO_STREAM_LAST_MEMBER(stream, _class, m)     stream << FOLIO_STREAM_OUT_MEMBER(_class, m); stream << FOLIO_LAST_MEMBER_SUFFIX;

// Macro to ensure a string is 16-bit Unicode.
#define FOLIO_WIDEN(x)  TXT(x)

// Source file definitions and macros.
#define FOLIO_SOURCE_FILE_LINE          __LINE__
#define FOLIO_SOURCE_FILE_NAME          FOLIO_WIDEN(__FILE__)
#define FOLIO_SOURCE_FILE_FUNCTION_NAME FOLIO_WIDEN(__FUNCTION__)

// Macro to use for referencing an unreferenced parameter.
#define FOLIO_UNREFERENCED(p) (p);

// Macro to use when declaring an empty cpp file (with include file only). Avoids 
// the linker "warning LNK4221: no public symbols found; archive member will be 
// inaccessible".

#define FOLIO_NO_EMPTY_FILE namespace {char FolioNoEmptyFile##FOLIO_SOURCE_FILE_LINE_;} 

#ifdef _DEBUG
    #define FOLIO_DEBUG_BREAK   _asm {int 3};
#else
    #define FOLIO_DEBUG_BREAK
#endif

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
