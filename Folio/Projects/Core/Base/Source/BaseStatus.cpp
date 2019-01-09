// "Home-made" includes.
#include    "BaseMacros.h"
#include    "BaseStatus.h"

namespace Folio
{

/**
 * Method that is used to obtain the description of a specified <b>FolioStatus</b>.
 * 
 * @param [in] status
 * The <b>FolioStatus</b>.
 * 
 * @return
 * The description of the <b>FolioStatus</b>.
 */
FolioString GetFolioStatusDescription (FolioStatus status)
{
    FolioOStringStream  outputStringStream;
    
    outputStringStream << status
                       << TXT('(') << FOLIO_STREAM_OUT_TO_HEX(status) << TXT(')')
                       << TXT(' ');

    if (FOLIO_IS_OS_ERROR(status))
    {
        outputStringStream << TXT("Operating System error");
    } // Endif.

    else
    if (FOLIO_IS_GDI_ERROR(status))
    {
        outputStringStream << TXT("GDI+ error");
    } // Endelseif.

    else
    {
        switch (status)
        {
        case ERR_SUCCESS:
            outputStringStream << TXT("ERR_SUCCESS");
            break;
        case ERR_INVALID_PARAM1:
            outputStringStream << TXT("ERR_INVALID_PARAM1");
            break;
        case ERR_INVALID_PARAM2:
            outputStringStream << TXT("ERR_INVALID_PARAM2");
            break;
        case ERR_INVALID_PARAM3:
            outputStringStream << TXT("ERR_INVALID_PARAM3");
            break;
        case ERR_INVALID_PARAM4:
            outputStringStream << TXT("ERR_INVALID_PARAM4");
            break;
        case ERR_INVALID_PARAM5:
            outputStringStream << TXT("ERR_INVALID_PARAM5");
            break;
        case ERR_INVALID_PARAM6:
            outputStringStream << TXT("ERR_INVALID_PARAM6");
            break;
        case ERR_INVALID_PARAM7:
            outputStringStream << TXT("ERR_INVALID_PARAM7");
            break;
        case ERR_INVALID_PARAM8:
            outputStringStream << TXT("ERR_INVALID_PARAM8");
            break;
        case ERR_INVALID_PARAM9:
            outputStringStream << TXT("ERR_INVALID_PARAM9");
            break;
        case ERR_INVALID_PARAM10:
            outputStringStream << TXT("ERR_INVALID_PARAM10");
            break;
        case ERR_INVALID_PARAM11:
            outputStringStream << TXT("ERR_INVALID_PARAM11");
            break;
        case ERR_INVALID_PARAM12:
            outputStringStream << TXT("ERR_INVALID_PARAM12");
            break;
        case ERR_INVALID_PARAM13:
            outputStringStream << TXT("ERR_INVALID_PARAM13");
            break;
        case ERR_INVALID_PARAM14:
            outputStringStream << TXT("ERR_INVALID_PARAM14");
            break;
        case ERR_INVALID_PARAM15:
            outputStringStream << TXT("ERR_INVALID_PARAM15");
            break;
        case ERR_INTERNAL_ERROR:
            outputStringStream << TXT("ERR_INTERNAL_ERROR");
            break;
        case ERR_PROGRAMMING_LOGIC:
            outputStringStream << TXT("ERR_PROGRAMMING_LOGIC");
            break;
        case ERR_INVALID_SEQUENCE:
            outputStringStream << TXT("ERR_INVALID_SEQUENCE");
            break;
        case ERR_NOT_ENOUGH_MEMORY:
            outputStringStream << TXT("ERR_NOT_ENOUGH_MEMORY");
            break;
        case ERR_BUFFER_TOO_SMALL:
            outputStringStream << TXT("ERR_BUFFER_TOO_SMALL");
            break;
        case ERR_BUFFER_TOO_LARGE:
            outputStringStream << TXT("ERR_BUFFER_TOO_LARGE");
            break;
        case ERR_NO_IMPLEMENTATION_CLASS:
            outputStringStream << TXT("ERR_NO_IMPLEMENTATION_CLASS");
            break;
        case ERR_NOT_SUPPORTED:
            outputStringStream << TXT("ERR_NOT_SUPPORTED");
            break;
        case ERR_INVALID:
            outputStringStream << TXT("ERR_INVALID");
            break;
        case ERR_PENDING:
            outputStringStream << TXT("ERR_PENDING");
            break;
        case ERR_TIMEOUT:
            outputStringStream << TXT("ERR_TIMEOUT");
            break;
        case ERR_CANCELED:
            outputStringStream << TXT("ERR_CANCELED");
            break;
        case ERR_ABANDONED:
            outputStringStream << TXT("ERR_ABANDONED");
            break;
        case ERR_IO_ERROR:
            outputStringStream << TXT("ERR_IO_ERROR");
            break;
        case ERR_ACCESS_DENIED:
            outputStringStream << TXT("ERR_ACCESS_DENIED");
            break;
        case ERR_MORE_DATA:
            outputStringStream << TXT("ERR_MORE_DATA");
            break;
        case ERR_NO_MORE_DATA:
            outputStringStream << TXT("ERR_NO_MORE_DATA");
            break;
        case ERR_ALREADY_EXISTS:
            outputStringStream << TXT("ERR_ALREADY_EXISTS");
            break;
        case ERR_NOT_FOUND:
            outputStringStream << TXT("ERR_NOT_FOUND");
            break;
        case ERR_ALREADY_IN_USE:
            outputStringStream << TXT("ERR_ALREADY_IN_USE");
            break;
        case ERR_NOT_IN_USE:
            outputStringStream << TXT("ERR_NOT_IN_USE");
            break;
        case ERR_ALREADY_INITIALISED:
            outputStringStream << TXT("ERR_ALREADY_INITIALISED");
            break;
        case ERR_NOT_INITIALISED:
            outputStringStream << TXT("ERR_NOT_INITIALISED");
            break;
        case ERR_ALREADY_STARTED:
            outputStringStream << TXT("ERR_ALREADY_STARTED");
            break;
        case ERR_NOT_STARTED:
            outputStringStream << TXT("ERR_NOT_STARTED");
            break;
        case ERR_NOT_STOPPED:
            outputStringStream << TXT("ERR_NOT_STOPPED");
            break;
        case ERR_ALREADY_ACTIVE:
            outputStringStream << TXT("ERR_ALREADY_ACTIVE");
            break;
        case ERR_NOT_ACTIVE:
            outputStringStream << TXT("ERR_NOT_ACTIVE");
            break;
        case ERR_NAME_TOO_SHORT:
            outputStringStream << TXT("ERR_NAME_TOO_SHORT");
            break;
        case ERR_NAME_TOO_LONG:
            outputStringStream << TXT("ERR_NAME_TOO_LONG");
            break;
    
        case ERR_UTIL_FILE_NOT_FOUND:
            outputStringStream << TXT("ERR_UTIL_FILE_NOT_FOUND");
            break;
        case ERR_UTIL_PATH_NOT_FOUND:
            outputStringStream << TXT("ERR_UTIL_PATH_NOT_FOUND");
            break;
        case ERR_UTIL_KEY_NOT_FOUND:
            outputStringStream << TXT("ERR_UTIL_KEY_NOT_FOUND");
            break;
        case ERR_UTIL_VALUE_NOT_FOUND:
            outputStringStream << TXT("ERR_UTIL_VALUE_NOT_FOUND");
            break;
        case ERR_UTIL_BUFFER_OVERRUN: 
            outputStringStream << TXT("ERR_UTIL_BUFFER_OVERRUN");
            break;
        case ERR_UTIL_BUFFER_UNDERRUN:
            outputStringStream << TXT("ERR_UTIL_BUFFER_UNDERRUN");
            break;

        case ERR_GRAPHIC_OUT_OF_BOUNDS:
            outputStringStream << TXT("ERR_GRAPHIC_OUT_OF_BOUNDS");
            break;


        default:
            outputStringStream << FOLIO_UNKNOWN;
            break;
        } // Endswitch.

    } // Endelse.

    outputStringStream << TXT('.');

    return (outputStringStream.str ());
} // Endproc.

} // Endnamespace.

//****************************** End of File *******************************/
