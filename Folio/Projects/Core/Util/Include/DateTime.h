#pragma once

// Windows includes.
#include    <Windows.h>

// "Home-made" includes.
#include    <Base.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Util
{

namespace DateTime
{

/// Months of the year.
const UInt16 JANUARY    = 1;    ///< January.
const UInt16 FEBRUARY   = 2;    ///< February.
const UInt16 MARCH      = 3;    ///< March.
const UInt16 APRIL      = 4;    ///< April.
const UInt16 MAY        = 5;    ///< May.
const UInt16 JUNE       = 6;    ///< June.
const UInt16 JULY       = 7;    ///< July.
const UInt16 AUGUST     = 8;    ///< August.
const UInt16 SEPTEMBER  = 9;    ///< September.
const UInt16 OCTOBER    = 10;   ///< October.
const UInt16 NOVEMBER   = 11;   ///< November.
const UInt16 DECEMBER   = 12;   ///< December.

// Routines.
FolioStatus QueryCurrentLocalTime (SYSTEMTIME& localTime);
FolioStatus QueryCurrentSystemTime (SYSTEMTIME& systemTime);
UInt32      GetCurrentTickCount ();
FolioStatus QueryPerformanceCounter (UInt32&    low, 
                                     UInt32&    high);
void    SetSystemTimeToTopOfHour (SYSTEMTIME& systemTime);
FolioStatus ConvertSystemTimeToFileTime (const SYSTEMTIME&  systemTime,
                                         FILETIME&          fileTime);
FolioStatus ConvertFileTimeToSystemTime (const FILETIME&    fileTime,
                                         SYSTEMTIME&        systemTime);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
