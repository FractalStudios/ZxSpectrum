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

/// The Win32 exception class.
/**
 * This class will allow a Win32 exception to be thrown or caught.
 *
 * This class does not support copy construction or assignment.
 */
class Win32Exception
{
public:
    static  void    CatchWin32Exceptions ();
    static  void    __cdecl     TranslatorProc (UInt32                  exceptionCode,
                                                LPEXCEPTION_POINTERS    exceptionInformation);

    Win32Exception (UInt32                  exceptionCode,
                    LPEXCEPTION_POINTERS    exceptionInformation);
    ~Win32Exception ();

    void    Process (UInt32             sourceFileLine,
                     const FolioString& sourceFileName);

    UInt32  GetExceptionCode () const;

private:
    UInt32              m_sourceFileLine;       ///< Line number of the source file where the exception occurred.
    FolioString         m_sourceFileName;       ///< Name of the source file where the exception occurred.
    UInt32              m_exceptionCode;        ///< The exception code.
    EXCEPTION_POINTERS  m_exceptionInformation; ///< The exception information.

    void    FormatStructuredExceptionDetails (FolioOStringStream& outputStringStream) const;
    
    static  FolioString GetStructuredExceptionDescription (UInt32 exceptionCode);

    FolioString GetModuleFileName () const;

    /// Private copy constructor to prevent copying.
    Win32Exception (const Win32Exception& rhs);

    /// Private assignment operator to prevent copying.
    Win32Exception& operator= (const Win32Exception& rhs);
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
