// C includes.
#include    <eh.h>

// "Home-made" includes.
#include    <Trace.h>
#include    "StaticMap.h"
#include    "ValueDescriptor.h"
#include    "Win32Exception.h"

namespace Folio
{

namespace Core
{

namespace Util
{

/**
 * Function that will set up a handler to allow Win32 exceptions (C structured
 * exceptions) to be processed as C++ typed exceptions.
 */
void    Win32Exception::CatchWin32Exceptions ()
{
    ::_set_se_translator ((_se_translator_function) (TranslatorProc));
} // Endproc.


/**
 * Function that is used to handle Win32 exceptions (C structured  exceptions)
 * as as C++ typed exceptions.
 *
 * @param [in] exceptionCode
 * The exception code.
 *
 * @param [in] exceptionInformation
 * The exception information.
 */
void   __cdecl  Win32Exception::TranslatorProc (UInt32                  exceptionCode,
                                                LPEXCEPTION_POINTERS    exceptionInformation)
{
    // Create and throw a Win32Exception.

    throw Win32Exception(exceptionCode, exceptionInformation);
} // Endproc.


/**
 * The class constructor.
 *
 * @param [in] exceptionCode
 * The exception code.
 *
 * @param [in] exceptionInformation
 * The exception information.
 */
Win32Exception::Win32Exception (UInt32                  exceptionCode,
                                LPEXCEPTION_POINTERS    exceptionInformation)
:   m_sourceFileLine(0),
    m_exceptionCode(exceptionCode),
    m_exceptionInformation(*exceptionInformation)
{
    // Allow someone debugging to debug!

    FOLIO_NOTIFY(FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME, TXT("Win32Exception!"));
} // Endproc.


/**
 * The class destructor.
 */
Win32Exception::~Win32Exception ()
{
} // Endproc.


/**
 * Function that will process a structured exception.
 *
 * @param [in] sourceFileLine
 * Line number of the source file which made the call.
 *
 * @param [in] sourceFileName
 * Name of the source file from where the call was made.
 */
void    Win32Exception::Process (UInt32             sourceFileLine,
                                 const FolioString& sourceFileName)
{
    try
    {
        m_sourceFileLine    = sourceFileLine;
        m_sourceFileName    = sourceFileName;

        // Format the structured exception details.

        FolioOStringStream  outputStringStream;
        
        FormatStructuredExceptionDetails (outputStringStream);

        // Log the exception.

        FOLIO_LOG_ERROR (outputStringStream.str ().c_str ());
    } // Endtry.

    catch (...)
    {
        // Problem when processing structured exception. At least log an error.

        FOLIO_LOG_ERROR (TXT("Caught an exception whilst processing structured exception."));
    } // Endcatch.

} // Endproc.


/**
 * Method that is used to get the exception code.
 *
 * @return
 * The exception code.
 */
UInt32  Win32Exception::GetExceptionCode () const
{
    return (m_exceptionCode);
} // Endproc.


/**
 * Function that will format the structured exception details.
 *
 * @param [in, out] outputStringStream
 * The string stream to format the structured exception details to.
 */
void    Win32Exception::FormatStructuredExceptionDetails (FolioOStringStream& outputStringStream) const
{
    // Add the module file name.

    outputStringStream << GetModuleFileName ()
                       << TXT(' ')
                       << ::GetModuleHandle (0)
                       << TXT(' ')
                       << m_sourceFileName
                       << TXT(' ')
                       << m_sourceFileLine
                       << TXT('.');

    // Sort out the exception data and format in a nice readable form.

    outputStringStream << TXT(" Structured exception ")
                       << m_exceptionInformation.ExceptionRecord->ExceptionCode
                       << TXT('(') << FOLIO_STREAM_OUT_TO_HEX(m_exceptionInformation.ExceptionRecord->ExceptionCode) << TXT(')')
                       << TXT(' ')
                       << GetStructuredExceptionDescription (m_exceptionInformation.ExceptionRecord->ExceptionCode)
                       << TXT('.');

    outputStringStream << TXT(" Exception Flags: ")
                       << FOLIO_STREAM_OUT_TO_HEX(m_exceptionInformation.ExceptionRecord->ExceptionFlags);

    switch (m_exceptionInformation.ExceptionRecord->ExceptionFlags)
    {
    case 0:
        outputStringStream << TXT(" CONTINUABLE EXCEPTION.");
        break;

    case EXCEPTION_NONCONTINUABLE:
        outputStringStream << TXT(" NONCONTINUABLE EXCEPTION.");
        break;

    default:
        outputStringStream << TXT(".");
        break;
    } // Endswitch.

    if (m_exceptionInformation.ExceptionRecord->ExceptionRecord)
    {
        outputStringStream << TXT(" Next Exception Record: ")
                           << FOLIO_STREAM_OUT_TO_HEX(m_exceptionInformation.ExceptionRecord->ExceptionRecord)
                           << TXT('.');
    } // Endif.

    outputStringStream << TXT(" Exception Address: ")
                       << FOLIO_STREAM_OUT_TO_HEX(m_exceptionInformation.ExceptionRecord->ExceptionAddress)
                       << TXT('.');

    outputStringStream << TXT(" Exception Parameters: ")
                       << m_exceptionInformation.ExceptionRecord->NumberParameters
                       << TXT('[');

    for (UInt32 parameterIndex = 0;
         parameterIndex < m_exceptionInformation.ExceptionRecord->NumberParameters;
         ++parameterIndex)
    {
        if (parameterIndex)
        {
            outputStringStream << TXT(',');
        } // Endif.

        outputStringStream << FOLIO_STREAM_OUT_TO_HEX(m_exceptionInformation.ExceptionRecord->ExceptionInformation [parameterIndex]);
    } // Endfor.

    outputStringStream << TXT("]. Context Flags:")
                       << FOLIO_STREAM_OUT_TO_HEX(m_exceptionInformation.ContextRecord->ContextFlags);

    if (m_exceptionInformation.ContextRecord->ContextFlags & CONTEXT_CONTROL)
    {
        // Add the control registers.

        outputStringStream << TXT(" cs: ")
                           << FOLIO_STREAM_OUT_TO_HEX(m_exceptionInformation.ContextRecord->SegCs)
                           << TXT(" eip: ")
                           << FOLIO_STREAM_OUT_TO_HEX(m_exceptionInformation.ContextRecord->Eip)
                           << TXT(" ebp: ")
                           << FOLIO_STREAM_OUT_TO_HEX(m_exceptionInformation.ContextRecord->Ebp)
                           << TXT(" ss: ")
                           << FOLIO_STREAM_OUT_TO_HEX(m_exceptionInformation.ContextRecord->SegSs)
                           << TXT(" esp: ")
                           << FOLIO_STREAM_OUT_TO_HEX(m_exceptionInformation.ContextRecord->Esp)
                           << TXT(" eflags: ")
                           << FOLIO_STREAM_OUT_TO_HEX(m_exceptionInformation.ContextRecord->EFlags);

        // Decode the flags register.

        // Input/output privilege levels.

        outputStringStream << TXT(" iopl: ")
                           << FOLIO_STREAM_OUT_TO_HEX((m_exceptionInformation.ContextRecord->EFlags & 0x00003000) >> 12);

        // Overflow flag.

        outputStringStream << TXT(" ov: ")
                           << (m_exceptionInformation.ContextRecord->EFlags & 0x00000800) ? 1 : 0;

        // Direction flag.

        outputStringStream << TXT(" up: ")
                           << (m_exceptionInformation.ContextRecord->EFlags & 0x00000400) ? 1 : 0;

        // Interrupt enable flag.

        outputStringStream << TXT(" ei: ")
                           << (m_exceptionInformation.ContextRecord->EFlags & 0x00000200) ? 1 : 0;

        // Sign flag.

        outputStringStream << TXT(" pl: ")
                           << (m_exceptionInformation.ContextRecord->EFlags & 0x00000080) ? 1 : 0;

        // Zero flag.

        outputStringStream << TXT(" zr: ")
                           << (m_exceptionInformation.ContextRecord->EFlags & 0x00000040) ? 1 : 0;

        // Auxiliary carry.

        outputStringStream << TXT(" ac: ")
                           << (m_exceptionInformation.ContextRecord->EFlags & 0x00000010) ? 1 : 0;

        // Parity flag.

        outputStringStream << TXT(" pe: ")
                           << (m_exceptionInformation.ContextRecord->EFlags & 0x00000004) ? 1 : 0;

        // Carry flag.

        outputStringStream << TXT(" cy: ")
                           << (m_exceptionInformation.ContextRecord->EFlags & 0x00000001) ? 1 : 0;
    } // Endif.

    if (m_exceptionInformation.ContextRecord->ContextFlags & CONTEXT_INTEGER)
    {
        // Add the base registers.

        outputStringStream << TXT(" eax: ")
                           << FOLIO_STREAM_OUT_TO_HEX(m_exceptionInformation.ContextRecord->Eax)
                           << TXT(" ebx: ")
                           << FOLIO_STREAM_OUT_TO_HEX(m_exceptionInformation.ContextRecord->Ebx)
                           << TXT(" ecv: ")
                           << FOLIO_STREAM_OUT_TO_HEX(m_exceptionInformation.ContextRecord->Ecx)
                           << TXT(" edx: ")
                           << FOLIO_STREAM_OUT_TO_HEX(m_exceptionInformation.ContextRecord->Edx)
                           << TXT(" esi: ")
                           << FOLIO_STREAM_OUT_TO_HEX(m_exceptionInformation.ContextRecord->Esi)
                           << TXT(" edi: ")
                           << FOLIO_STREAM_OUT_TO_HEX(m_exceptionInformation.ContextRecord->Edi);
    } // Endif.

    if (m_exceptionInformation.ContextRecord->ContextFlags & CONTEXT_SEGMENTS)
    {
        // Add the segment registers.

        outputStringStream << TXT(" ds: ")
                           << FOLIO_STREAM_OUT_TO_HEX(m_exceptionInformation.ContextRecord->SegDs)
                           << TXT(" es: ")
                           << FOLIO_STREAM_OUT_TO_HEX(m_exceptionInformation.ContextRecord->SegEs)
                           << TXT(" fs: ")
                           << FOLIO_STREAM_OUT_TO_HEX(m_exceptionInformation.ContextRecord->SegFs)
                           << TXT(" gs: ")
                           << FOLIO_STREAM_OUT_TO_HEX(m_exceptionInformation.ContextRecord->SegGs);
    } // Endif.

    if (m_exceptionInformation.ContextRecord->ContextFlags & CONTEXT_DEBUG_REGISTERS)
    {
        // Add the debug registers.

        outputStringStream << TXT(" dr0: ")
                           << FOLIO_STREAM_OUT_TO_HEX(m_exceptionInformation.ContextRecord->Dr0)
                           << TXT(" dr1: ")
                           << FOLIO_STREAM_OUT_TO_HEX(m_exceptionInformation.ContextRecord->Dr1)
                           << TXT(" dr2: ")
                           << FOLIO_STREAM_OUT_TO_HEX(m_exceptionInformation.ContextRecord->Dr2)
                           << TXT(" dr3: ")
                           << FOLIO_STREAM_OUT_TO_HEX(m_exceptionInformation.ContextRecord->Dr3)
                           << TXT(" dr6: ")
                           << FOLIO_STREAM_OUT_TO_HEX(m_exceptionInformation.ContextRecord->Dr6)
                           << TXT(" dr7: ")
                           << FOLIO_STREAM_OUT_TO_HEX(m_exceptionInformation.ContextRecord->Dr7);
    } // Endif.

    outputStringStream << TXT('.');
} // Endproc.


/**
 * Function that will get the description of a structured exception.
 *
 * @param [in] exceptionCode
 * The structured exception.
 * 
 * @return
 * The description of a structured exception status.
 */
FolioString Win32Exception::GetStructuredExceptionDescription (UInt32 exceptionCode)
{
    // Create a static map that will be used to change the value into strings.
    
    static  ValueDescriptor<UInt32>::DescriptionMapElement descriptions [] =
    {
        {EXCEPTION_ACCESS_VIOLATION,            TXT("EXCEPTION_ACCESS_VIOLATION"),          },
        {EXCEPTION_BREAKPOINT,                  TXT("EXCEPTION_BREAKPOINT"),                },
        {EXCEPTION_DATATYPE_MISALIGNMENT,       TXT("EXCEPTION_DATATYPE_MISALIGNMENT"),     },
        {EXCEPTION_SINGLE_STEP,                 TXT("EXCEPTION_SINGLE_STEP"),               },
        {EXCEPTION_ARRAY_BOUNDS_EXCEEDED,       TXT("EXCEPTION_ARRAY_BOUNDS_EXCEEDED"),     },
        {EXCEPTION_FLT_DENORMAL_OPERAND,        TXT("EXCEPTION_FLT_DENORMAL_OPERAND"),      },
        {EXCEPTION_FLT_DIVIDE_BY_ZERO,          TXT("EXCEPTION_FLT_DIVIDE_BY_ZERO"),        },
        {EXCEPTION_FLT_INEXACT_RESULT,          TXT("EXCEPTION_FLT_INEXACT_RESULT"),        },
        {EXCEPTION_FLT_INVALID_OPERATION,       TXT("EXCEPTION_FLT_INVALID_OPERATION"),     },
        {EXCEPTION_FLT_OVERFLOW,                TXT("EXCEPTION_FLT_OVERFLOW"),              },
        {EXCEPTION_FLT_STACK_CHECK,             TXT("EXCEPTION_FLT_STACK_CHECK"),           },
        {EXCEPTION_FLT_UNDERFLOW,               TXT("EXCEPTION_FLT_UNDERFLOW"),             },
        {EXCEPTION_INT_DIVIDE_BY_ZERO,          TXT("EXCEPTION_INT_DIVIDE_BY_ZERO"),        },
        {EXCEPTION_INT_OVERFLOW,                TXT("EXCEPTION_INT_OVERFLOW"),              },
        {EXCEPTION_PRIV_INSTRUCTION,            TXT("EXCEPTION_PRIV_INSTRUCTION"),          },
        {EXCEPTION_IN_PAGE_ERROR,               TXT("EXCEPTION_IN_PAGE_ERROR"),             },
        {EXCEPTION_ILLEGAL_INSTRUCTION,         TXT("EXCEPTION_ILLEGAL_INSTRUCTION"),       },
        {EXCEPTION_NONCONTINUABLE_EXCEPTION,    TXT("EXCEPTION_NONCONTINUABLE_EXCEPTION"),  },
        {EXCEPTION_STACK_OVERFLOW,              TXT("EXCEPTION_STACK_OVERFLOW"),            },
        {EXCEPTION_INVALID_DISPOSITION,         TXT("EXCEPTION_INVALID_DISPOSITION"),       },
        {EXCEPTION_GUARD_PAGE,                  TXT("EXCEPTION_GUARD_PAGE"),                },
        {EXCEPTION_INVALID_HANDLE,              TXT("EXCEPTION_INVALID_HANDLE"),            },
    };

    // Build the value descriptor.

    ValueDescriptor<UInt32> valueDescriptor(sizeof (descriptions) / sizeof (descriptions [0]),
                                            descriptions);

    return (valueDescriptor.ToString (exceptionCode));
} // Endproc.


/**
 * Function that will get the module file name.
 *
 * @return
 * The module file name.
 */
FolioString Win32Exception::GetModuleFileName () const
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
