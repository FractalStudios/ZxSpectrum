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

// Routines.

extern  FolioString     DescribeDecimal (UInt32                     number,
                                         UInt32                     numOfDigits = 0,
                                         FolioString::value_type    padChar = TXT('0'),
                                         bool                       signedNumber = false);
extern  FolioString     DescribeHexadecimal (UInt32                     number,
                                             UInt32                     uiSizeofNumber = sizeof (UInt32),
                                             FolioString::value_type    padChar = TXT('0'));

extern  FolioString     DescribeDayOfWeek (UInt32 dayOfWeek);
extern  FolioString     DescribeMonth (UInt32 month);

extern  FolioString     DescribeDateTime (const SYSTEMTIME& systemTime,
                                          bool              monthDescriptionRqd = true,
                                          bool              secondsRqd = true,
                                          bool              millisecondsRqd = true);
extern  FolioString     DescribeDateTime (UInt32    day,
                                          UInt32    month,
                                          UInt32    year,
                                          UInt32    hour, 
                                          UInt32    minute, 
                                          UInt32    second, 
                                          UInt32    milliseconds = 0,
                                          bool      monthDescriptionRqd = true,
                                          bool      secondsRqd = true,
                                          bool      millisecondsRqd = true);
extern  FolioString     DescribeDate (const SYSTEMTIME& systemTime,
                                      bool              monthDescriptionRqd = true);
extern  FolioString     DescribeDate (UInt32    day,
                                      UInt32    month,
                                      UInt32    year,
                                      bool      monthDescriptionRqd = true);
extern  FolioString     DescribeTime (const SYSTEMTIME& systemTime,
                                      bool              secondsRqd = true,
                                      bool              millisecondsRqd = true);
extern  FolioString     DescribeTime (UInt32    hour, 
                                      UInt32    minute, 
                                      UInt32    second, 
                                      UInt32    milliseconds = 0,
                                      bool      secondsRqd = true,
                                      bool      millisecondsRqd = true);

extern  FolioString     DescribeByteBuffer (const FolioByteBuffer&  buffer);
extern  FolioString     DescribeByteBuffer (const Byte* buffer,
                                            UInt32      numOfBytes);

}; // Endnamespace.

}; // Endnamespace.

}; // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
