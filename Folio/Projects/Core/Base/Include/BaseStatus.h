#pragma once

// "Home-made" includes.
#include    "BaseStrings.h"
#include    "BaseTypes.h"

#pragma pack(push, 1)

namespace Folio
{

typedef UInt32  FolioStatus;    ///< Folio status.

// Good.
enum 
{
    ERR_SUCCESS = 0, // Success.
}; // Endenum.

// Invalid parameter.
enum 
{
    ERR_INVALID_PARAM1 = 1, //  1st parameter passed to a method or function call is invalid.
    ERR_INVALID_PARAM2,     //  2nd parameter passed to a method or function call is invalid.
    ERR_INVALID_PARAM3,     //  3rd parameter passed to a method or function call is invalid.
    ERR_INVALID_PARAM4,     //  4th parameter passed to a method or function call is invalid.
    ERR_INVALID_PARAM5,     //  5th parameter passed to a method or function call is invalid.
    ERR_INVALID_PARAM6,     //  6th parameter passed to a method or function call is invalid.
    ERR_INVALID_PARAM7,     //  7th parameter passed to a method or function call is invalid.
    ERR_INVALID_PARAM8,     //  8th parameter passed to a method or function call is invalid.
    ERR_INVALID_PARAM9,     //  9th parameter passed to a method or function call is invalid.
    ERR_INVALID_PARAM10,    // 10th parameter passed to a method or function call is invalid.
    ERR_INVALID_PARAM11,    // 11th parameter passed to a method or function call is invalid.
    ERR_INVALID_PARAM12,    // 12th parameter passed to a method or function call is invalid.
    ERR_INVALID_PARAM13,    // 13th parameter passed to a method or function call is invalid.
    ERR_INVALID_PARAM14,    // 14th parameter passed to a method or function call is invalid.
    ERR_INVALID_PARAM15,    // 15th parameter passed to a method or function call is invalid.
}; // Endenum.

// Normalised.
enum 
{
    ERR_INTERNAL_ERROR = 100,                   // A catastrophic software error has occurred in the implementation. An error used as a last resort.
    ERR_PROGRAMMING_LOGIC,                      // A logical programming error has occurred in the implementation. Less severe than ERR_INTERNAL_ERROR.
    ERR_INVALID_SEQUENCE,                       // A pre-defined user sequence of method or function calls has not been followed.
    ERR_NOT_ENOUGH_MEMORY,                      // There is not enough memory to process this request.
    ERR_OUT_OF_MEMORY = ERR_NOT_ENOUGH_MEMORY,
    ERR_BUFFER_TOO_SMALL,                       // A buffer is too small.
    ERR_BUFFER_TOO_LARGE,                       // A buffer is too large.
    ERR_NO_IMPLEMENTATION_CLASS,                // An interface class employing the PIMPL idiom has failed to create its implementation class.
    ERR_NOT_SUPPORTED,                          // An operation or entity is not supported.
    ERR_INVALID,                                // An operation or entity is invalid.
    ERR_PENDING,                                // An operation is pending.
    ERR_TIMEOUT,                                // An operation timed out.
    ERR_CANCELED,                               // An operation was canceled.
    ERR_ABANDONED,                              // An operation was abandoned.
    ERR_IO_ERROR,                               // An error occurred sending data to or receiving data from a device.
    ERR_ACCESS_DENIED,                          // Access is denied.
    ERR_MORE_DATA,                              // More data is available.
    ERR_NO_MORE_DATA,                           // No more data is available.
    ERR_NO_MSG,                                 // No message is available.
    ERR_ALREADY_EXISTS,                         // An entity already exists.
    ERR_NOT_FOUND,                              // An entity is not found.
    ERR_ALREADY_IN_USE,                         // An entity is already in use.
    ERR_IN_USE = ERR_ALREADY_IN_USE,            // An entity is in use.
    ERR_NOT_IN_USE,                             // An entity is not in use.
    ERR_ALREADY_INITIALISED,                    // An entity is already initialised.
    ERR_NOT_INITIALISED,                        // An entity is not initialised.
    ERR_ALREADY_STARTED,                        // An entity is already started.
    ERR_STARTED = ERR_ALREADY_STARTED,          // An entity is started.
    ERR_NOT_STARTED,                            // An entity is not started.
    ERR_ALREADY_STOPPED = ERR_NOT_STARTED,      // An entity is already stopped.
    ERR_STOPPED = ERR_ALREADY_STOPPED,          // An entity is stopped.
    ERR_NOT_STOPPED,                            // An entity is not stopped.
    ERR_ALREADY_ACTIVE,                         // An entity is already active.
    ERR_NOT_ACTIVE,                             // An entity is not active.
    ERR_NAME_TOO_SHORT,                         // The name of an entity is too short.
    ERR_NAME_TOO_LONG,                          // The name of an entity is too long.
    ERR_OUT_OF_BOUNDS,                          // An out of bounds condition has arisen.
}; // Endenum.

// Util.
enum 
{
    ERR_UTIL_FILE_NOT_FOUND = 200,  // A file is not found.
    ERR_UTIL_PATH_NOT_FOUND,        // A path is not found.
    ERR_UTIL_KEY_NOT_FOUND,         // A registry key is not found.
    ERR_UTIL_VALUE_NOT_FOUND,       // A registry value is not found.
    ERR_UTIL_BUFFER_OVERRUN,        // A buffer overrun has been detected.
    ERR_UTIL_BUFFER_UNDERRUN,       // A buffer underrun has been detected.
}; // Endenum.

// Graphic.
enum 
{
    ERR_GRAPHIC_OUT_OF_BOUNDS = 300,    // A graphic entity is out of bounds.
}; // Endenum.


// Values are 32 bit values layed out as follows:
//
//  3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//  1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
// +---+-+-+-----------------------+-------------------------------+
// |Sev|C|R|     Facility          |               Code            |
// |0 0|1|0|                       |                               |
// +---+-+-+-----------------------+-------------------------------+
//
// where:
//     Sev - is the severity code, 0 always.
//     C - is the Customer code flag, 1 always.
//     R - is a reserved bit, 0 always.
//     Facility - is the facility code.
//     Code - is the facility's status code.

// Macro to get a status code.
#define FOLIO_GET_STATUS_CODE(x)        (x & 0x0000ffff)

// Macros to set a major/minor Folio facility.
#define FOLIO_MAKE_MAJOR_FACILITY(x)    (x << 26)
#define FOLIO_MAKE_MINOR_FACILITY(x)    (x << 16)

// Define the major facility codes in Folio.
#define FOLIO_FACILITY_OS       0x01    // Operating System error.
#define FOLIO_FACILITY_GDI      0x02    // GDI+ error.

// Macros to set/get an Operating System error.
#define FOLIO_OS_ERROR              (0x20000000 | FOLIO_MAKE_MAJOR_FACILITY(FOLIO_FACILITY_OS))
#define FOLIO_MAKE_OS_ERROR(x)      (x | FOLIO_OS_ERROR)
#define FOLIO_IS_OS_ERROR(x)        (x & FOLIO_OS_ERROR)

// Macros to set/get an GDI+ error.
#define FOLIO_GDI_ERROR             (0x20000000 | FOLIO_MAKE_MAJOR_FACILITY(FOLIO_FACILITY_GDI))
#define FOLIO_MAKE_GDI_ERROR(x)     (x | FOLIO_GDI_ERROR)
#define FOLIO_IS_GDI_ERROR(x)       (x & FOLIO_GDI_ERROR)


// Routines.
FolioString GetFolioStatusDescription (FolioStatus status);

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
