#include    "stdafx.h"
#include    "File.h"
#include    "SecurityAttributes.h"

namespace Utils
{

File::File ()
:   m_hFile(INVALID_HANDLE_VALUE)
{
} // Endproc.


File::~File ()
{
    // Have we opened a file?

    if (IsFileOpen ())
    {
        // Yes. Close it.

        Close ();
    } // Endif.

} // Endproc.


DWORD   File::Create (const std::wstring    &filePath,
                      UINT                  uiDesiredAccess,
                      UINT                  uiShareMode,
                      UINT                  uiCreationDisposition,
                      UINT                  uiAttributes)
{
    DWORD   dwWin32Error = ERROR_SUCCESS;

    // Have we created a file already?

    if (!IsFileOpen ())
    {
        // No.

        SecurityAttributes  securityAttributes;

        m_filePath = filePath;  // Note the file path.

        // Create the file.

        m_hFile = ::CreateFileW (m_filePath.c_str (),
                                 uiDesiredAccess,
                                 uiShareMode,
                                 securityAttributes,
                                 uiCreationDisposition,
                                 uiAttributes,
                                 NULL); // No template.

        // Always get the last error; as caller may want to know if the file 
        // existed before.

        dwWin32Error = ::GetLastError ();
    } // Endif.

    else
    {
        // Yes.

        dwWin32Error = ERROR_INTERNAL_ERROR;
    } // Endelse.

    return (dwWin32Error);
} // Endproc.


DWORD   File::Close ()
{
    DWORD   dwWin32Error = ERROR_SUCCESS;

    // Have we opened a file?

    if (IsFileOpen ())
    {
        // Yes. Close the file handle.

        if (::CloseHandle (m_hFile))
        {
            m_hFile = INVALID_HANDLE_VALUE;    // Gone.
            m_filePath.clear ();
        } // Endif.

        else
        {
            dwWin32Error = ::GetLastError ();
        } // Endelse.

    } // Endif.

    return (dwWin32Error);
} // Endproc.


DWORD   File::Read (LPVOID          lpvBuffer,
                    UINT            &uiNumOfBytes,
                    LPOVERLAPPED    lpOverlapped) const
{
    DWORD   dwWin32Error = ERROR_SUCCESS;

    // Have we opened a file?

    if (IsFileOpen ())
    {
        // Yes. Read from the file.

        if (!::ReadFile (m_hFile,
                         lpvBuffer,
                         uiNumOfBytes,
                         reinterpret_cast<LPDWORD> (&(uiNumOfBytes)),
                         lpOverlapped))
        {
            // Are we using overlapped I/O and is I/O pending?

            if (lpOverlapped &&
                (::GetLastError () == ERROR_IO_PENDING))
            {
                // Yes.

                dwWin32Error = ERROR_IO_PENDING;
            } // Endif.

            else
            {
                dwWin32Error = ::GetLastError ();
            } // Endelse.

        } // Endif.

    } // Endif.

    else
    {
        // No.

        dwWin32Error = ERROR_INTERNAL_ERROR;
    } // Endelse.

    return (dwWin32Error);
} // Endproc.


DWORD   File::Write (const LPVOID    lpvBuffer,
                     UINT            &uiNumOfBytes,
                     LPOVERLAPPED    lpOverlapped) const
{
    DWORD   dwWin32Error = ERROR_SUCCESS;

    // Have we opened a file?

    if (IsFileOpen ())
    {
        // Yes. Write to the file.

        if (!::WriteFile (m_hFile,
                          lpvBuffer,
                          uiNumOfBytes,
                          reinterpret_cast<LPDWORD> (&(uiNumOfBytes)),
                          lpOverlapped))
        {
            // Are we using overlapped I/O and is I/O pending?

            if (lpOverlapped &&
                (::GetLastError () == ERROR_IO_PENDING))
            {
                // Yes.

                dwWin32Error = ERROR_IO_PENDING;
            } // Endif.

            else
            {
                dwWin32Error = ::GetLastError ();
            } // Endelse.

        } // Endif.

    } // Endif.

    else
    {
        // No.

        dwWin32Error = ERROR_INTERNAL_ERROR;
    } // Endelse.

    return (dwWin32Error);
} // Endproc.


DWORD   File::GetOverlappedResult (const OVERLAPPED &overlapped,
                                   bool             bWaitForCompletion,
                                   UINT             &uiNumOfBytes) const
{
    DWORD   dwWin32Error = ERROR_SUCCESS;

    // Have we opened a file?

    if (IsFileOpen ())
    {
        // Yes. Get the overlapped result.

        if (!::GetOverlappedResult (m_hFile,
                                    const_cast<LPOVERLAPPED> (&(overlapped)),
                                    reinterpret_cast<LPDWORD> (&(uiNumOfBytes)),
                                    bWaitForCompletion ? TRUE : FALSE))  // Wait for the I/O operation to complete?
        {
            dwWin32Error = ::GetLastError ();
        } // Endif.

    } // Endif.

    else
    {
        // No.

        dwWin32Error = ERROR_INTERNAL_ERROR;
    } // Endelse.

    return (dwWin32Error);
} // Endproc.


DWORD   File::QuerySize (UINT   &uiLowOrderSize,
                         UINT   &uiHighOrderSize) const
{
    DWORD   dwWin32Error = ERROR_SUCCESS;

    // Have we opened a file?

    if (IsFileOpen ())
    {
        // Yes. Get the file size.

        uiLowOrderSize = ::GetFileSize (m_hFile,
                                        reinterpret_cast<LPDWORD> (&(uiHighOrderSize)));

        if (uiLowOrderSize == INVALID_FILE_SIZE)
        {
            dwWin32Error = ::GetLastError ();
        } // Endif.

    } // Endif.

    else
    {
        // No.

        dwWin32Error = ERROR_INTERNAL_ERROR;
    } // Endelse.

    return (dwWin32Error);
} // Endproc.


DWORD   File::SetFilePointer (UINT uiDistanceFromStart) const
{
    DWORD   dwWin32Error = ERROR_SUCCESS;

    // Have we opened a file?

    if (IsFileOpen ())
    {
        // Yes. Set the file pointer to the begining of the file.

        if ((::SetFilePointer (m_hFile,
                               uiDistanceFromStart,
                               0,
                               FILE_BEGIN) == INVALID_SET_FILE_POINTER) &&
            (::GetLastError () != ERROR_SUCCESS))
        {
            dwWin32Error = ::GetLastError ();
        } // Endif.

    } // Endif.

    else
    {
        // No.

        dwWin32Error = ERROR_INTERNAL_ERROR;
    } // Endelse.

    return (dwWin32Error);
} // Endproc.


DWORD   File::MoveToStartOfFile () const
{
    DWORD   dwWin32Error = ERROR_SUCCESS;

    // Have we opened a file?

    if (IsFileOpen ())
    {
        // Yes. Set the file pointer to the end of the file.

        if ((::SetFilePointer (m_hFile,
                               0,
                               0,
                               FILE_BEGIN) == INVALID_SET_FILE_POINTER) &&
            (::GetLastError () != ERROR_SUCCESS))
        {
            dwWin32Error = ::GetLastError ();
        } // Endif.

    } // Endif.

    else
    {
        // No.

        dwWin32Error = ERROR_INTERNAL_ERROR;
    } // Endelse.

    return (dwWin32Error);
} // Endproc.


DWORD   File::MoveToEndOfFile () const
{
    DWORD   dwWin32Error = ERROR_SUCCESS;

    // Have we opened a file?

    if (IsFileOpen ())
    {
        // Yes. Set the file pointer to the end of the file.

        if ((::SetFilePointer (m_hFile,
                               0,
                               0,
                               FILE_END) == INVALID_SET_FILE_POINTER) &&
            (::GetLastError () != ERROR_SUCCESS))
        {
            dwWin32Error = ::GetLastError ();
        } // Endif.

    } // Endif.

    else
    {
        // No.

        dwWin32Error = ERROR_INTERNAL_ERROR;
    } // Endelse.

    return (dwWin32Error);
} // Endproc.


DWORD   File::SetEndOfFile (UINT uiDistanceFromStart) const
{
    DWORD   dwWin32Error = ERROR_SUCCESS;

    // Have we opened a file?

    if (IsFileOpen ())
    {
        // Yes. Set the file pointer (from the begining of the file).

        dwWin32Error = SetFilePointer (uiDistanceFromStart);

        if (dwWin32Error == ERROR_SUCCESS)
        {
            // Set the end of file.

            if (!::SetEndOfFile (m_hFile))
            {
                dwWin32Error = ::GetLastError ();
            } // Endif.

        } // Endif.

    } // Endif.

    else
    {
        // No.

        dwWin32Error = ERROR_INTERNAL_ERROR;
    } // Endelse.

    return (dwWin32Error);
} // Endproc.


DWORD   File::Clear () const
{
    return (SetEndOfFile (0));
} // Endproc.


HANDLE  File::GetFileHandle () const
{
    return (IsFileOpen () ? m_hFile : 0);
} // Endproc.


std::wstring    File::GetFilePath () const
{
    return (m_filePath);
} // Endproc.


bool    File::IsFileOpen () const
{
    return (m_hFile != INVALID_HANDLE_VALUE);
} // Endproc.

}; // Endnamespace.

/******************************* End of File *******************************/
