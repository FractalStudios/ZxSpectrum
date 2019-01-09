#pragma once

// "Home-made" includes.
#include    <Base.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Util
{

// Exception macros.
#define THROW(excep)                        throw Folio::Core::Util::Exception(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, FOLIO_SOURCE_FILE_FUNCTION_NAME, excep)
#define THROW_FOLIO_STATUS(excep, status)   throw Folio::Core::Util::Exception(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, FOLIO_SOURCE_FILE_FUNCTION_NAME, excep, status)


/// The exception class.
/**
 * This class will allow an exception to be thrown or caught.
 *
 * This class does not support copy construction or assignment.
 */
class Exception
{
public:
    /// Exception status.
    enum ExceptionStatus
    {
        EXCEPTION_STATUS_LOGIC_ERROR,                   ///< Logical error exception.
        EXCEPTION_STATUS_OUT_OF_RANGE,                  ///< Out of range exception.
        EXCEPTION_STATUS_OVERFLOW_ERROR,                ///< Overflow exception.
        EXCEPTION_STATUS_RUNTIME_ERROR,                 ///< Runtime exception.
        EXCEPTION_STATUS_ILLEGAL_OPERATION,             ///< Illegal operation exception.
        EXCEPTION_STATUS_INSUFFICIENT_MEMORY,           ///< Insufficient memory exception.
        EXCEPTION_STATUS_OBJECT_CREATION_FAILED,        ///< Object creation failed exception.
        EXCEPTION_STATUS_OBJECT_CONSTRUCTOR_FAILED,     ///< Object constructor failed exception.
    }; // Endenum.

    Exception (UInt32               sourceFileLine,
               const FolioString&   sourceFileName,
               const FolioCString   functionName,
               ExceptionStatus      exceptionStatus,
               FolioStatus          status = ERR_SUCCESS);
    ~Exception ();

    void    Process () const;

    ExceptionStatus GetExceptionStatus () const;

private:
    UInt32          m_sourceFileLine;   ///< Line number of the source file where the exception occurred.
    FolioString     m_sourceFileName;   ///< Name of the source file where the exception occurred.
    FolioString     m_functionName;     ///< Name of the function where the exception occurred.
    ExceptionStatus m_exceptionStatus;  ///< The exception status.
    FolioStatus     m_status;           ///< The status error code.

    void    FormatExceptionDetails (FolioOStringStream& outputStringStream) const;

    static  FolioString GetExceptionStatusDescription (ExceptionStatus exceptionStatus);

    FolioString GetModuleFileName () const;

    /// Private copy constructor to prevent copying.
    Exception (const Exception& rhs);

    /// Private assignment operator to prevent copying.
    Exception& operator= (const Exception& rhs);
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
