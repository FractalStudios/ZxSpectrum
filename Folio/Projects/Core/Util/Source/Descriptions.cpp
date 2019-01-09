// STL includes.
#include    <iomanip>
#include    <sstream>

// "Home-mcde" includes.
#include    "Descriptions.h"

namespace Folio
{

namespace Core
{
    
namespace Util
{

FolioString     DescribeDecimal (UInt32                     number,
                                 UInt32                     numOfDigits,
                                 FolioString::value_type    padChar,
                                 bool                       signedNumber)
{
    FolioOStringStream  str;

    if (numOfDigits)
    {
        str << std::setfill(padChar) << std::setw(numOfDigits);
    } // Endif.

    if (signedNumber)
    {
        str << static_cast<int> (number);
    } // Endif.

    else
    {
        str << number;
    } // Endelse.

    return (str.str ());
} // Endproc.


FolioString     DescribeHexadecimal (UInt32                     number,
                                     UInt32                     sizeofNumber,
                                     FolioString::value_type    padChar)
{
    FolioOStringStream  str;

    str << TXT("0x");

    if (sizeofNumber)
    {
        str << std::setfill(padChar) << std::setw(2 * sizeofNumber);
    } // Endif.

    str << std::hex << std::uppercase << number;

    return (str.str ());
} // Endproc.


FolioString     DescribeDayOfWeek (UInt32 dayOfWeek)
{
    static  FolioCString    dayOfWeekDescription [7] = {TXT("Sun"), TXT("Mon"), TXT("Tue"), TXT("Wed"), TXT("Thu"), TXT("Fri"), TXT("Sat")};

    if ((dayOfWeek >= 0) && (dayOfWeek <= 6))
    {
        return (dayOfWeekDescription [dayOfWeek]);
    } // Endif.

    else
    {
        return (TXT("???"));
    } // Endelse.

} // Endproc.


FolioString     DescribeMonth (UInt32 month)
{
    static  FolioCString    monthDescription [12] = {TXT("Jan"), TXT("Feb"), TXT("Mar"), TXT("Apr"), TXT("May"), TXT("Jun"), 
                                                     TXT("Jul"), TXT("Aug"), TXT("Sep"), TXT("Oct"), TXT("Nov"), TXT("Dec")};

    if ((month >= 1) && (month <= 12))
    {
        return (monthDescription [month - 1]);
    } // Endif.

    else
    {
        return (TXT("???"));
    } // Endelse.

} // Endproc.


FolioString     DescribeDateTime (const SYSTEMTIME& systemTime, 
                                  bool              monthDescriptionRqd,
                                  bool              secondsRqd,
                                  bool              millisecondsRqd)
{
    return (DescribeDateTime (systemTime.wDay,
                              systemTime.wMonth,
                              systemTime.wYear,
                              systemTime.wHour, 
                              systemTime.wMinute, 
                              systemTime.wSecond, 
                              systemTime.wMilliseconds,
                              monthDescriptionRqd,
                              secondsRqd,
                              millisecondsRqd));
} // Endproc.


FolioString     DescribeDateTime (UInt32    day,
                                  UInt32    month,
                                  UInt32    year,
                                  UInt32    hour, 
                                  UInt32    minute, 
                                  UInt32    second, 
                                  UInt32    milliseconds,
                                  bool      monthDescriptionRqd,
                                  bool      secondsRqd,
                                  bool      millisecondsRqd)
{
    FolioOStringStream  str;

    str << DescribeDate (day,
                         month,
                         year,
                         monthDescriptionRqd);

    str << TXT(' ');

    str << DescribeTime (hour, 
                         minute, 
                         second, 
                         milliseconds,
                         secondsRqd,
                         millisecondsRqd);

    return (str.str ());
} // Endproc.


FolioString     DescribeDate (const SYSTEMTIME& systemTime,
                              bool              monthDescriptionRqd)
{
    return (DescribeDate (systemTime.wDay,
                          systemTime.wMonth,
                          systemTime.wYear,
                          monthDescriptionRqd));
} // Endproc.


FolioString     DescribeDate (UInt32    day,
                              UInt32    month,
                              UInt32    year,
                              bool      monthDescriptionRqd)
{
    FolioOStringStream  str;

    str << std::setfill(TXT('0')) << std::setw(2) << day
        << TXT('/');

    if (monthDescriptionRqd)
    {
        str << DescribeMonth (month);
    } // Endif.

    else
    {
        str << std::setw(2) << month;
    } // Endelse.

    str << TXT('/') << std::setw(4) << year;

    return (str.str ());
} // Endproc.


FolioString     DescribeTime (const SYSTEMTIME& systemTime,
                              bool              secondsRqd,
                              bool              millisecondsRqd)
{
    return (DescribeTime (systemTime.wHour, 
                          systemTime.wMinute, 
                          systemTime.wSecond, 
                          systemTime.wMilliseconds,
                          secondsRqd,
                          millisecondsRqd));
} // Endproc.


FolioString     DescribeTime (UInt32    hour, 
                              UInt32    minute, 
                              UInt32    second, 
                              UInt32    milliseconds,
                              bool      secondsRqd,
                              bool      millisecondsRqd)
{
    FolioOStringStream  str;

    str << std::setfill(TXT('0')) << std::setw(2) << hour
        << TXT(':') << std::setw(2) << minute;

    // If milliseconds are required, then automatically include seconds.

    if (millisecondsRqd)
    {
        secondsRqd = true;
    } // Endif.

    if (secondsRqd)
    {
        str << TXT(':') << std::setw(2) << second;
    } // Endif.

    if (millisecondsRqd)
    {
        str << TXT(':') << std::setw(3) << milliseconds;
    } // Endif.

    return (str.str ());
} // Endproc.


FolioString     DescribeByteBuffer (const FolioByteBuffer& buffer)
{
    FolioOStringStream  str;

    for (FolioByteBuffer::const_iterator itr = buffer.begin ();
         itr != buffer.end ();
         ++itr)
    {
        if (itr != buffer.begin ())
        {
            str << TXT(' ');
        } // Endif.

        int n = *itr;

        str << std::setfill(TXT('0')) << std::setw(2) << std::hex << n;
    } // Endfor.

    return (str.str ());
} // Endproc.


FolioString     DescribeByteBuffer (const Byte* buffer,
                                    UInt32      numOfBytes)
{
    return (DescribeByteBuffer (FolioByteBuffer(buffer, buffer + numOfBytes)));
} // Endproc.

}; // Endnamespace.

}; // Endnamespace.

}; // Endnamespace.

/******************************* End of File *******************************/