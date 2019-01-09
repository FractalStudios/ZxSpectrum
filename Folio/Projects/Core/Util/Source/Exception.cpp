// Windows includes.
#include    <Windows.h>

// "Home-made" includes.
#include    <Trace.h>
#include    "Exception.h"
#include    "StaticMap.h"
#include    "ValueDescriptor.h"

namespace Folio
{

namespace Core
{

namespace Util
{

/**
 * The class constructor.
 *
 * @param [in] sourceFileLine
 * Line number of the source file which made the call.
 *
 * @param [in] sourceFileName
 * Name of the source file from where the call was made.
 *
 * @param [in] functionName
 * Name of the function from where the call was made. This parameter may be
 * zero.
 *
 * @param [in] exceptionStatus
 * The exception status.
 *
 * @param [in] status
 * The result error code.
 */
Exception::Exception (UInt32                sourceFileLine,
                      const FolioString&    sourceFileName,
                      const FolioCString    functionName,
                      ExceptionStatus       exceptionStatus,
                      FolioStatus           status)
:   m_sourceFileLine(sourceFileLine),
    m_sourceFileName(sourceFileName),
    m_functionName(functionName ? functionName : TXT("")),
    m_exceptionStatus(exceptionStatus),
    m_status(status)
{
    // Allow someone debugging to debug!

    FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, TXT("Exception!"));
} // Endproc.


/**
 * The class destructor.
 */
Exception::~Exception ()
{
} // Endproc.


/**
 * Function that will process an exception.
 */
void    Exception::Process () const
{
    try
    {
        // Format the exception details.

        FolioOStringStream  outputStringStream;
        FormatExceptionDetails (outputStringStream);

        // Log the exception.

        FOLIO_LOG_ERROR (outputStringStream.str ().c_str ());
    } // Endtry.

    catch (...)
    {
        // Problem when processing exception. At least log an error.

        FOLIO_LOG_ERROR (TXT("Caught an exception whilst processing one."));
    } // Endcatch.

} // Endproc.


/**
 * Method that is used to get the exception status.
 *
 * @return
 * The exception status.
 */
Exception::ExceptionStatus  Exception::GetExceptionStatus () const
{
    return (m_exceptionStatus);
} // Endproc.


/**
 * Function that will format the exception details.
 *
 * @param [in, out] outputStringStream
 * The string stream to format the exception details to.
 */
void    Exception::FormatExceptionDetails (FolioOStringStream& outputStringStream) const
{
    // Add the module file name.

    outputStringStream << GetModuleFileName ()
                       << TXT(' ')
                       << m_sourceFileName
                       << TXT(' ')
                       << m_sourceFileLine
                       << TXT('.');

    // Format the exception.

    outputStringStream << TXT(" Caught exception ")
                       << m_exceptionStatus
                       << TXT('(') << FOLIO_STREAM_OUT_TO_HEX(m_exceptionStatus) << TXT(')')
                       << TXT(' ')
                       << GetExceptionStatusDescription (m_exceptionStatus)
                       << TXT('.');

    outputStringStream << TXT(" Exception thrown from ")
                       << m_functionName
                       << TXT(" status") 
                       << FOLIO_VARIABLE_NAME_SUFFIX 
                       << Folio::GetFolioStatusDescription (m_status)
                       << TXT('.');
} // Endproc.


/**
 * Method that is used to obtain the description of a specified <b>ExceptionStatus</b>.
 * 
 * @param [in] exceptionStatus
 * The <b>ExceptionStatus</b>.
 * 
 * @return
 * The description of the <b>ExceptionStatus</b>.
 */
FolioString Exception::GetExceptionStatusDescription (ExceptionStatus exceptionStatus)
{
    // Create a static map that will be used to change the value into strings.
    
    static  ValueDescriptor<UInt32>::DescriptionMapElement descriptions [] =
    {
        { EXCEPTION_STATUS_LOGIC_ERROR,                 TXT("EXCEPTION_STATUS_LOGIC_ERROR"),                },
        { EXCEPTION_STATUS_OUT_OF_RANGE,                TXT("EXCEPTION_STATUS_OUT_OF_RANGE"),               },
        { EXCEPTION_STATUS_OVERFLOW_ERROR,              TXT("EXCEPTION_STATUS_OVERFLOW_ERROR"),             },
        { EXCEPTION_STATUS_RUNTIME_ERROR,               TXT("EXCEPTION_STATUS_RUNTIME_ERROR"),              },
        { EXCEPTION_STATUS_ILLEGAL_OPERATION,           TXT("EXCEPTION_STATUS_ILLEGAL_OPERATION"),          },
        { EXCEPTION_STATUS_INSUFFICIENT_MEMORY,         TXT("EXCEPTION_STATUS_INSUFFICIENT_MEMORY"),        },
        { EXCEPTION_STATUS_OBJECT_CREATION_FAILED,      TXT("EXCEPTION_STATUS_OBJECT_CREATION_FAILED"),     },
        { EXCEPTION_STATUS_OBJECT_CONSTRUCTOR_FAILED,   TXT("EXCEPTION_STATUS_OBJECT_CONSTRUCTOR_FAILED"),  },
    };

    // Build the value descriptor.

    ValueDescriptor<UInt32> valueDescriptor(sizeof (descriptions) / sizeof (descriptions [0]),
                                            descriptions);

    return (valueDescriptor.ToString (exceptionStatus));
} // Endproc.


/**
 * Function that will get the module file name.
 *
 * @return
 * The module file name.
 */
FolioString Exception::GetModuleFileName () const
{
    FolioString moduleFileName;

    Char    modulePathName [MAX_PATH + 1];    // +1 for NULL.

    // Get the module file name.

    if (::GetModuleFileName (0, // Current process.
                             modulePathName,
                             sizeof (modulePathName)))
    {
        moduleFileName = modulePathName;
        
        // Remove any module path.
        
        FolioString::size_type  fileNamePos = moduleFileName.find_last_of (TXT('\\'));
        
        if (fileNamePos != FolioString::npos)
        {
            moduleFileName.assign (&(moduleFileName.c_str () [fileNamePos]));
        } // Endif.

    } // Endif.

    return (moduleFileName);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
