// "Home-made" includes.
#include    <Trace.h>
#include    "DateTime.h"

namespace Folio
{

namespace Core
{

namespace Util
{

namespace DateTime
{

/**
 * Function that will query the current local time.
 *
 * @param [out] localTime
 * On return, will hold the local time, if successful. If this method fails 
 * then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus QueryCurrentLocalTime (SYSTEMTIME& localTime)
{
    ::GetLocalTime (&(localTime));

    return (ERR_SUCCESS);
} // Endproc.


/**
 * Function that will query the current system time.
 *
 * @param [out] systemTime
 * On return, will hold the local time, if successful. If this method fails 
 * then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus QueryCurrentSystemTime (SYSTEMTIME& systemTime)
{
    ::GetSystemTime (&(systemTime));

    return (ERR_SUCCESS);
} // Endproc.


/**
 * Function that will get the current tick count.
 *
 * @return
 * The current tick count
 */
UInt32  GetCurrentTickCount ()
{
    return (::timeGetTime ());
} // Endproc.


/**
 * Function that get the currrent value of the high-resolution 
 * performance counter.
 *
 * @return
 * The currrent value of the high-resolution performance counter.
 */
Int64   GetCurrentPerformanceCounter ()
{
    Int64   tickCounter = 0;    // Initialise!

    // Query the high-resolution performance counter.

    LARGE_INTEGER   PerformanceCounter;

    if (::QueryPerformanceCounter (&(PerformanceCounter)))
    {
        tickCounter = PerformanceCounter.QuadPart;
    } // Endif.

    else
    {
        // Build and log an error.

        FolioStatus status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR (TXT("QueryPerformanceCounter"),
                              status);
    } // Endelse.

    return (tickCounter);
} // Endproc.


/**
 * Function that get the value of the high-resolution performance frequency.
 *
 * @return
 * The value of the high-resolution performance frequency.
 */
Int64   GetPerformanceFrequency ()
{
    Int64   frequency = 0;  // Initialise!

    // Query the high-resolution performance frequency.

    LARGE_INTEGER   PerformanceFrequency;

    if (::QueryPerformanceFrequency (&(PerformanceFrequency)))
    {
        frequency = PerformanceFrequency.QuadPart;
    } // Endif.

    else
    {
        // Build and log an error.

        FolioStatus status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR (TXT("QueryPerformanceFrequency"),
                              status);
    } // Endelse.

    return (frequency);
} // Endproc.


/**
 * Function that calculates the elpased time (in milliseconds).
 *
 * @param [in] startTickCounter
 * The start tick counter (a measurement of the high-resolution performance 
 * counter).
 *
 * @param [in] performanceFrequency
 * The value of the high-resolution performance frequency.
 *
 * @return
 * The elapsed time (in milliseconds).
 */
UInt32  CalculateElapsedTime (const Int64&    startTickCounter, 
                              const Int64&    performanceFrequency)
{
    Int64   elapsedTime = GetCurrentPerformanceCounter () - startTickCounter;
    elapsedTime *= 1000000;
    elapsedTime /= performanceFrequency;

    return (static_cast<UInt32> (elapsedTime / 1000));
} // Endproc.


/**
 * Function that will set the system time to the top of the hour.
 *
 * @param [in, out] systemTime
 * On return, will hold the update system time.
 */
void    SetSystemTimeToTopOfHour (SYSTEMTIME& systemTime)
{
    // Set the next hour.

    ++systemTime.wHour;

    // Have we moved to a new day?

    if (systemTime.wHour > 23)
    {
        systemTime.wHour = 0;   // New day.
        ++systemTime.wDay;

        // Have we moved to a new month?

        switch (systemTime.wMonth)
        {
        case JANUARY:
        case MARCH:
        case MAY:
        case JULY:
        case AUGUST:
        case OCTOBER:
        case DECEMBER:
            if (systemTime.wDay > 31)
            {
                systemTime.wDay = 1;   // New month.
                ++systemTime.wMonth;

                // Have we moved to a new year?

                if (systemTime.wMonth > DECEMBER)
                {
                    systemTime.wMonth = 1; // New year.
                    ++systemTime.wYear;
                } // Endif.

            } // Endif.
            break;

        case FEBRUARY:
            // Check for leap year. A leap year is any year divisible by four 
            // except years both divisible by 100 and not divisible by 400.

            if ((systemTime.wYear % 4) ||
                (!(systemTime.wYear % 100) && 
                  (systemTime.wYear % 400)))
            {
                // Not a leap year.

                if (systemTime.wDay > 28)
                {
                    systemTime.wDay = 1;    // New month.
                    ++systemTime.wMonth;
                } // Endif.

            } // Endif.

            else 
            {
                // Leap year.

                if (systemTime.wDay > 29)
                {
                    systemTime.wDay = 1;    // New month.
                    ++systemTime.wMonth;
                } // Endif.

            } // Endelse.
            break;

        case APRIL:
        case JUNE:
        case SEPTEMBER:
        case NOVEMBER:
            if (systemTime.wDay > 30)
            {
                systemTime.wDay = 1;    // New month.
                ++systemTime.wMonth;
            } // Endif.
            break;

        default:
            break;
        } // Endswitch.

    } // Endif.

    systemTime.wMinute          = 0;
    systemTime.wSecond          = 0;
    systemTime.wMilliseconds    = 0;
} // Endproc.


/**
 * Function that will convert the specified system time to a file time.
 *
 * @param [in] systemTime
 * The system time to convert.
 *
 * @param [out] fileTime
 * On return, will hold the file time, if successful. If this method fails 
 * then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus ConvertSystemTimeToFileTime (const SYSTEMTIME&  systemTime,
                                         FILETIME&          fileTime)
{
    FolioStatus status = ERR_SUCCESS;

    if (!::SystemTimeToFileTime (&(systemTime), &(fileTime)))
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR (TXT("SystemTimeToFileTime"),
                              status);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Function that will convert the specified file time to a system time.
 *
 * @param [in] fileTime
 * The file time to convert.
 *
 * @param [out] systemTime
 * On return, will hold the system time, if successful. If this method fails 
 * then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus ConvertFileTimeToSystemTime (const FILETIME&    fileTime,
                                         SYSTEMTIME&        systemTime)
{
    FolioStatus status = ERR_SUCCESS;

    if (!::FileTimeToSystemTime (&(fileTime), &(systemTime)))
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR (TXT("FileTimeToSystemTime"),
                              status);
    } // Endif.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
