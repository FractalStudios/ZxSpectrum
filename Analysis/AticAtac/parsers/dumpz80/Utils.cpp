#include    "stdafx.h"
#include    "Utils.h"

char*   stristr (const char* str1, const char* str2)
{
    const   char*   p1  = str1;
    const   char*   p2  = str2;
    const   char*   r   = *p2 == 0 ? str1 : 0;

    while ((*p1 != 0) && (*p2 != 0))
    {
        if (tolower (static_cast<unsigned char> (*p1)) == tolower (static_cast<unsigned char> (*p2)))
        {
            if (r == 0)
            {
                r = p1;
            } // Endif.

            p2++;
        } // Endif.

        else
        {
            p2 = str2;
        
            if (r != 0)
            {
                p1 = r + 1;
            } // Endif.

            if (tolower (static_cast<unsigned char> (*p1)) == tolower (static_cast<unsigned char> (*p2)))
            {
                r = p1;
                p2++;
            } // Endif.

            else
            {
                r = 0;
            } // Endelse.
        
        } // Endif.

        p1++;
    } // Endwhile

    return (*p2 == 0 ? const_cast<char *> (r) : 0);
} // Endproc.


unsigned short*   wcsistr (const unsigned short* str1, const unsigned short* str2)
{
    const   unsigned short*   p1  = str1;
    const   unsigned short*   p2  = str2;
    const   unsigned short*   r   = *p2 == 0 ? str1 : 0;

    while ((*p1 != 0) && (*p2 != 0))
    {
        if (tolower (static_cast<unsigned short> (*p1)) == tolower (static_cast<unsigned short> (*p2)))
        {
            if (r == 0)
            {
                r = p1;
            } // Endif.

            p2++;
        } // Endif.

        else
        {
            p2 = str2;
        
            if (r != 0)
            {
                p1 = r + 1;
            } // Endif.

            if (tolower (static_cast<unsigned short> (*p1)) == tolower (static_cast<unsigned short> (*p2)))
            {
                r = p1;
                p2++;
            } // Endif.

            else
            {
                r = 0;
            } // Endelse.
        
        } // Endif.

        p1++;
    } // Endwhile

    return (*p2 == 0 ? const_cast<unsigned short *> (r) : 0);
} // Endproc.


namespace Utils
{

File::~File ()
{
    Close ();
} // Endproc.


bool    File::Create (bool  bReadAccess, 
                      bool  bWriteAccess)
{
    bool    bSuccess = true;

    // Check file is not already created/opened.

    if (m_hFile == INVALID_HANDLE_VALUE)
    {
        // Create the file.
        
        DWORD   dwDesiredAccess = (bReadAccess ? GENERIC_READ : 0) |
                                  (bWriteAccess ? GENERIC_WRITE : 0);
    
        DWORD   dwSharedAccess = FILE_SHARE_READ | 
                                 (bWriteAccess ? 0 : FILE_SHARE_WRITE);
    
        DWORD   dwFileAttributes = FILE_ATTRIBUTE_NORMAL    |
                                   FILE_FLAG_RANDOM_ACCESS  |
                                   FILE_FLAG_WRITE_THROUGH; 

        m_hFile = ::CreateFileW (m_filePath.c_str (),
                                 dwDesiredAccess,
                                 dwSharedAccess,
                                 NULL,
                                 CREATE_ALWAYS,   // Always create the file.
                                 dwFileAttributes,
                                 NULL);
            
        if (m_hFile == INVALID_HANDLE_VALUE)
        {
            m_dwLastError = ::GetLastError ();
    
            if (m_bLogError)
            {
                WCHAR   szError [MAX_ERROR_LENGTH];
                ::wsprintfW (szError,
                             L"Error from ::CreateFileW creating file '%ws'. dwWin32Error=%u(0x%08.08x)",
                             m_filePath.c_str (),
                             m_dwLastError, 
                             m_dwLastError);
                LogError (__LINE__, TEXTW(__FILE__), LOG_WIN32_ERROR, szError);
            } // Endif.
        
            bSuccess = false;
        } // Endif.

    } // Endif.

    return (bSuccess);
} // Endproc.


bool    File::Open (bool    bReadAccess, 
                    bool    bWriteAccess)
{
    bool    bSuccess = true;

    // Check file is not already created/opened.

    if (m_hFile == INVALID_HANDLE_VALUE)
    {
        // Open the file.
        
        DWORD   dwDesiredAccess = (bReadAccess ? GENERIC_READ : 0) |
                                  (bWriteAccess ? GENERIC_WRITE : 0);
    
        DWORD   dwSharedAccess = FILE_SHARE_READ | 
                                 (bWriteAccess ? 0 : FILE_SHARE_WRITE);
    
        DWORD   dwFileAttributes = FILE_ATTRIBUTE_NORMAL    |
                                   FILE_FLAG_RANDOM_ACCESS  |
                                   FILE_FLAG_WRITE_THROUGH; 

        m_hFile = ::CreateFileW (m_filePath.c_str (),
                                 dwDesiredAccess,
                                 dwSharedAccess,
                                 NULL,
                                 OPEN_EXISTING, // Open existing file.
                                 dwFileAttributes,
                                 NULL);
            
        if (m_hFile == INVALID_HANDLE_VALUE)
        {
            m_dwLastError = ::GetLastError ();
    
            if (m_bLogError)
            {
                WCHAR   szError [MAX_ERROR_LENGTH];
                ::wsprintfW (szError,
                             L"Error from ::CreateFileW creating file '%ws'. dwWin32Error=%u(0x%08.08x)",
                             m_filePath.c_str (),
                             m_dwLastError, 
                             m_dwLastError);
                LogError (__LINE__, TEXTW(__FILE__), LOG_WIN32_ERROR, szError);
            } // Endif.
        
            bSuccess = false;
        } // Endif.

    } // Endif.

    return (bSuccess);
} // Endproc.


bool    File::Close ()
{
    bool    bSuccess = true;

    // Check file is not already closed.

    if (m_hFile != INVALID_HANDLE_VALUE)
    {
        // Close the file.
    
        if (::CloseHandle (m_hFile))
        {
            m_hFile = INVALID_HANDLE_VALUE;
        } // Endif.

        else
        {
            m_dwLastError = ::GetLastError ();

            if (m_bLogError)
            {
                WCHAR   szError [MAX_ERROR_LENGTH];
                ::wsprintfW (szError,
                             L"Error from ::CloseHandle for file '%ws'. dwWin32Error=%u(0x%08.08x)",
                             m_filePath.c_str (),
                             m_dwLastError, 
                             m_dwLastError);
                LogError (__LINE__, TEXTW(__FILE__), LOG_WIN32_ERROR, szError);
            } // Endif.
    
            bSuccess = false;
        } // Endelse.

    } // Endif.

    return (bSuccess);
} // Endproc.


bool    File::Delete ()
{
    bool    bSuccess = true;

    bSuccess = Close ();

    if (bSuccess)
    {
        if (!::DeleteFileW (m_filePath.c_str ()))
        {
            m_dwLastError = ::GetLastError ();

            if (m_bLogError)
            {
                WCHAR   szError [MAX_ERROR_LENGTH];
                DWORD   dwWin32Error = ::GetLastError ();
                ::wsprintfW (szError,
                             L"Error from ::DeleteFile for file '%ws'. dwWin32Error=%u(0x%08.08x)",
                             m_filePath.c_str (),
                             m_dwLastError, 
                             m_dwLastError);
                LogError (__LINE__, TEXTW(__FILE__), LOG_WIN32_ERROR, szError);
            } // Endif.
    
            bSuccess = false;
        } // Endif.

    } // Endif.

    return (bSuccess);
} // Endproc.


bool    File::Read (DWORD   dwFileOffset,
                    DWORD   dwSizeofBuffer, 
                    BYTE    &byBuffer,
                    DWORD   &dwNumBytesRead)
{
    bool    bSuccess = true;

    dwNumBytesRead = 0;  // Intitialise!

    // Check file has been created/opened.

    if (m_hFile == INVALID_HANDLE_VALUE)
    {
        bSuccess = false;
    } // Endif.

    else
    {
        if ((dwFileOffset != CURRENT_FILE_OFFSET) && 
            (::SetFilePointer (m_hFile, dwFileOffset, 0, FILE_BEGIN) == INVALID_SET_FILE_POINTER))
        {
            m_dwLastError = ::GetLastError ();

            if (m_bLogError)
            {
                WCHAR   szError [MAX_ERROR_LENGTH];
                ::wsprintfW (szError,
                             L"Error from ::SetFilePointer %u reading from file '%ws'. dwWin32Error=%u(0x%08.08x)",
                             dwFileOffset,
                             m_filePath.c_str (),
                             m_dwLastError,
                             m_dwLastError);
                LogError (__LINE__, TEXTW(__FILE__), LOG_WIN32_ERROR, szError);
            } // Endif.

            bSuccess = false;
        } // Endif.

        if (bSuccess)
        {
            // Read the data from the file.
        
            if (!::ReadFile (m_hFile,
                             &(byBuffer),
                             dwSizeofBuffer,
                             &(dwNumBytesRead),
                             NULL))
            {
                m_dwLastError = ::GetLastError ();

                if (m_bLogError)
                {
                    WCHAR   szError [MAX_ERROR_LENGTH];
                    ::wsprintfW (szError,
                                 L"Error from ::ReadFile reading from file '%ws'. dwWin32Error=%u(0x%08.08x)",
                                 m_filePath.c_str (),
                                 m_dwLastError,
                                 m_dwLastError);
                    LogError (__LINE__, TEXTW(__FILE__), LOG_WIN32_ERROR, szError);
                } // Endif.
    
                bSuccess = false;
            } // Endif.

        } // Endif.

    } // Endelse.
    
    return (bSuccess);
} // Endproc.


bool    File::Write (DWORD      dwFileOffset,
                     DWORD      dwSizeofBuffer, 
                     const BYTE &byBuffer,
                     DWORD      &dwNumBytesWritten)
{
    bool    bSuccess = true;

    dwNumBytesWritten = 0;  // Intitialise!

    // Check file has been created/opened.

    if (m_hFile == INVALID_HANDLE_VALUE)
    {
        bSuccess = false;
    } // Endif.

    else
    {
        if ((dwFileOffset != CURRENT_FILE_OFFSET) && 
            (::SetFilePointer (m_hFile, dwFileOffset, 0, FILE_BEGIN) == INVALID_SET_FILE_POINTER))
        {
            m_dwLastError = ::GetLastError ();

            if (m_bLogError)
            {
                WCHAR   szError [MAX_ERROR_LENGTH];
                ::wsprintfW (szError,
                             L"Error from ::SetFilePointer %u writing to file '%ws'. dwWin32Error=%u(0x%08.08x)",
                             dwFileOffset,
                             m_filePath.c_str (),
                             m_dwLastError,
                             m_dwLastError);
                LogError (__LINE__, TEXTW(__FILE__), LOG_WIN32_ERROR, szError);
            } // Endif.

            bSuccess = false;
        } // Endif.

        if (bSuccess)
        {
            // Write the data to the file.
        
            if (!::WriteFile (m_hFile,
                              &(byBuffer),
                              dwSizeofBuffer,
                              &(dwNumBytesWritten),
                              NULL))
            {
                m_dwLastError = ::GetLastError ();

                if (m_bLogError)
                {
                    WCHAR   szError [MAX_ERROR_LENGTH];
                    ::wsprintfW (szError,
                                 L"Error from ::WriteFile writing to file '%ws'. dwWin32Error=%u(0x%08.08x)",
                                 m_filePath.c_str (),
                                 m_dwLastError,
                                 m_dwLastError);
                    LogError (__LINE__, TEXTW(__FILE__), LOG_WIN32_ERROR, szError);
                } // Endif.
    
                bSuccess = false;
            } // Endif.

        } // Endif.

    } // Endelse.
    
    return (bSuccess);
} // Endproc.


bool    File::SetFilePointer (DWORD dwFileOffset)
{
    bool    bSuccess = true;

    // Check file has been created/opened.

    if (m_hFile == INVALID_HANDLE_VALUE)
    {
        bSuccess = false;
    } // Endif.

    else
    {
        if ((dwFileOffset != CURRENT_FILE_OFFSET) && 
            (::SetFilePointer (m_hFile, dwFileOffset, 0, FILE_BEGIN) == INVALID_SET_FILE_POINTER))
        {
            m_dwLastError = ::GetLastError ();

            if (m_bLogError)
            {
                WCHAR   szError [MAX_ERROR_LENGTH];
                ::wsprintfW (szError,
                             L"Error from ::SetFilePointer %u writing to file '%ws'. dwWin32Error=%u(0x%08.08x)",
                             dwFileOffset,
                             m_filePath.c_str (),
                             m_dwLastError,
                             m_dwLastError);
                LogError (__LINE__, TEXTW(__FILE__), LOG_WIN32_ERROR, szError);
            } // Endif.

            bSuccess = false;
        } // Endif.

    } // Endelse.
    
    return (bSuccess);
} // Endproc.


bool    File::SetEof (DWORD dwFileOffset)
{
    bool    bSuccess = SetFilePointer (dwFileOffset);

    if (bSuccess)
    {
        // Set the end of the file.
        
        if (!::SetEndOfFile (m_hFile))
        {
            m_dwLastError = ::GetLastError ();
    
            if (m_bLogError)
            {
                WCHAR   szError [MAX_ERROR_LENGTH];
                ::wsprintfW (szError,
                             L"Error from ::SetEndOfFile %u writing to file '%ws'. dwWin32Error=%u(0x%08.08x)",
                             dwFileOffset,
                             m_filePath.c_str (),
                             m_dwLastError,
                             m_dwLastError);
                LogError (__LINE__, TEXTW(__FILE__), LOG_WIN32_ERROR, szError);
            } // Endif.
    
            bSuccess = false;
        } // Endif.

    } // Endif.

    return (bSuccess);
} // Endproc.


DWORD   File::GetFileSize () const
{
    DWORD   dwFileSize = INVALID_FILE_SIZE;

    // Check file has been created/opened.

    if (m_hFile != INVALID_HANDLE_VALUE)
    {
        dwFileSize = ::GetFileSize (m_hFile, NULL);

        if (dwFileSize == INVALID_FILE_SIZE)
        {
            m_dwLastError = ::GetLastError ();
    
            if (m_bLogError)
            {
                WCHAR   szError [MAX_ERROR_LENGTH];
                ::wsprintfW (szError,
                             L"Error from ::GetFileSize for file '%ws'. dwWin32Error=%u(0x%08x)",
                             m_filePath.c_str (),
                             m_dwLastError, 
                             m_dwLastError);
                LogError (__LINE__, TEXTW(__FILE__), LOG_WIN32_ERROR, szError);
            } // Endif.
    
        } // Endif.

    } // Endif.

    return (dwFileSize);
} // Endproc.


bool    File::SetFileSize (DWORD dwFileSize)
{
    bool    bSuccess = true;

    // Check file has been created/opened.

    if (m_hFile == INVALID_HANDLE_VALUE)
    {
        bSuccess = false;
    } // Endif.

    else
    {
        if (::SetFilePointer (m_hFile, dwFileSize, 0, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
        {
            m_dwLastError = ::GetLastError ();

            if (m_bLogError)
            {
                WCHAR   szError [MAX_ERROR_LENGTH];
                ::wsprintfW (szError,
                             L"Error from ::SetFilePointer %u setting file size for file '%ws'. dwWin3Error = %u(0x%08x)",
                             dwFileSize,
                             m_filePath.c_str (),
                             m_dwLastError,
                             m_dwLastError);
                LogError (__LINE__, TEXTW(__FILE__), LOG_WIN32_ERROR, szError);
            } // Endif.

            bSuccess = false;
        } // Endif.

        if (bSuccess)
        {
            // Set the end of file.
        
            if (!::SetEndOfFile (m_hFile))
            {
                m_dwLastError = ::GetLastError ();

                if (m_bLogError)
                {
                    WCHAR   szError [MAX_ERROR_LENGTH];
                    ::wsprintfW (szError,
                                 L"Error from ::SetEndOfFile setting file size for file '%ws'. dwWin3Error = %u(0x%08x)",
                                 m_filePath.c_str (),
                                 m_dwLastError,
                                 m_dwLastError);
                    LogError (__LINE__, TEXTW(__FILE__), LOG_WIN32_ERROR, szError);
                } // Endif.
    
                bSuccess = false;
            } // Endif.

        } // Endif.

    } // Endelse.
    
    return (bSuccess);
} // Endproc.


DWORD   File::GetFileOffset () const
{
    DWORD   dwFileOffset = -1;

    // Check file has been created/opened.

    if (m_hFile != INVALID_HANDLE_VALUE)
    {
        dwFileOffset = ::SetFilePointer (m_hFile, 0, NULL, FILE_CURRENT);
    } // Endif.

    return (dwFileOffset);
} // Endproc.


FILETIME    File::GetCreationTime () const
{
    FILETIME    fileTime = {0};

    // Check file has been created/opened.

    if (m_hFile != INVALID_HANDLE_VALUE)
    {
        BY_HANDLE_FILE_INFORMATION  fileInformation;
        if (::GetFileInformationByHandle (m_hFile, &(fileInformation)))
        {
            fileTime = fileInformation.ftCreationTime;
        } // Endif.

        else
        {
            m_dwLastError = ::GetLastError ();

            if (m_bLogError)
            {
                WCHAR   szError [MAX_ERROR_LENGTH];
                ::wsprintfW (szError,
                             L"Error from ::GetFileInformationByHandle for file '%ws'. dwWin32Error=%u(0x%08.08x)",
                             m_filePath.c_str (),
                             m_dwLastError,
                             m_dwLastError);
                LogError (__LINE__, TEXTW(__FILE__), LOG_WIN32_ERROR, szError);
            } // Endif.

        } // Endelse.

    } // Endif.

    return (fileTime);
} // Endproc.


FILETIME    File::GetLastAccessTime () const
{
    FILETIME    fileTime = {0};

    // Check file has been created/opened.

    if (m_hFile != INVALID_HANDLE_VALUE)
    {
        BY_HANDLE_FILE_INFORMATION  fileInformation;
        if (::GetFileInformationByHandle (m_hFile, &(fileInformation)))
        {
            fileTime = fileInformation.ftLastAccessTime;
        } // Endif.

        else
        {
            m_dwLastError = ::GetLastError ();

            if (m_bLogError)
            {
                WCHAR   szError [MAX_ERROR_LENGTH];
                ::wsprintfW (szError,
                             L"Error from ::GetFileInformationByHandle for file '%ws'. dwWin32Error=%u(0x%08.08x)",
                             m_filePath.c_str (),
                             m_dwLastError,
                             m_dwLastError);
                LogError (__LINE__, TEXTW(__FILE__), LOG_WIN32_ERROR, szError);
            } // Endif.

        } // Endelse.

    } // Endif.

    return (fileTime);
} // Endproc.


FILETIME    File::GetLastWriteTime () const
{
    FILETIME    fileTime = {0};

    // Check file has been created/opened.

    if (m_hFile != INVALID_HANDLE_VALUE)
    {
        BY_HANDLE_FILE_INFORMATION  fileInformation;
        if (::GetFileInformationByHandle (m_hFile, &(fileInformation)))
        {
            fileTime = fileInformation.ftLastWriteTime;
        } // Endif.

        else
        {
            m_dwLastError = ::GetLastError ();

            if (m_bLogError)
            {
                WCHAR   szError [MAX_ERROR_LENGTH];
                ::wsprintfW (szError,
                             L"Error from ::GetFileInformationByHandle for file '%ws'. dwWin32Error=%u(0x%08.08x)",
                             m_filePath.c_str (),
                             m_dwLastError,
                             m_dwLastError);
                LogError (__LINE__, TEXTW(__FILE__), LOG_WIN32_ERROR, szError);
            } // Endif.

        } // Endelse.

    } // Endif.

    return (fileTime);
} // Endproc.


std::wstring    File::GetFileName () const
{
    std::wstring    fileName (SplitPathToFileName (m_filePath));
    fileName += SplitPathToFileNameExt (m_filePath);

    return (fileName);
} // Endproc.


bool    File::IsValidFileName (const std::wstring &fileName)
{
    return ((fileName.find_first_of (L"\\/:*?\"<>") == std::wstring::npos) ? true : false);
} // Endproc.


bool    File::IsValidPath (const std::wstring &path)
{
    return ((path.find_first_of (L"/*?<>") == std::wstring::npos) ? true : false);
} // Endproc.


std::wstring    File::AddBackslashToPath (const std::wstring  &path, 
                                          bool                bToEnd)
{
    std::wstring    newPath(path);

    if (newPath.empty ())
    {
        newPath.push_back (L'\\');
    } // Endif.

    else
    if (bToEnd)
    {
        if (newPath [newPath.length () - 1] != L'\\')
        {
            newPath.push_back (L'\\');
        } // Endif.

    } // Endif.

    else
    if (newPath [0] != L'\\')
    {
        newPath.insert (newPath.begin (), L'\\');
    } // Endif.

    return (newPath);
} // Endproc.


std::wstring    File::RemoveBackslashFromPath (const std::wstring   &path,
                                               bool                 bFromEnd)
{
    std::wstring    newPath(path);

    if (!newPath.empty ())
    {
        if (bFromEnd)
        {
            if (newPath [newPath.length () - 1] == L'\\')
            {
                newPath.erase (newPath.length () - 1, 1);
            } // Endif.
    
        } // Endif.
    
        else
        if (newPath [0] == L'\\')
        {
            newPath.erase (0, 1);
        } // Endif.

    } // Endif.

    return (newPath);
} // Endproc.


bool    File::IsWildcard (const std::wstring &filePath)
{
    std::wstring    fileName (SplitPathToFileName (filePath));
    fileName += SplitPathToFileNameExt (filePath);

    return (fileName.find_first_of (L"*?") != std::wstring::npos);
} // Endproc.


bool    File::IsDirectory (const std::wstring &filePath)
{
    // Get the file attributes.

    UINT    uiFileAttributes = INVALID_FILE_ATTRIBUTES;
    return (QueryFileAttributes (filePath, uiFileAttributes) && 
            (uiFileAttributes & FILE_ATTRIBUTE_DIRECTORY));
} // Endproc.


bool    File::IsFile (const std::wstring &filePath)
{
    // Get the file attributes.

    UINT    uiFileAttributes = INVALID_FILE_ATTRIBUTES;
    return (QueryFileAttributes (filePath, uiFileAttributes) &&
            !(uiFileAttributes & FILE_ATTRIBUTE_DIRECTORY));
} // Endproc.


bool    File::IsFileReadOnly (const std::wstring &filePath)
{
    // Get the file attributes.

    UINT    uiFileAttributes = INVALID_FILE_ATTRIBUTES;
    return (QueryFileAttributes (filePath, uiFileAttributes) && 
            (uiFileAttributes & FILE_ATTRIBUTE_READONLY));
} // Endproc.


bool    File::MakeFileWriteable (const std::wstring &filePath)
{
    // Get the file attributes.

    UINT    uiFileAttributes = INVALID_FILE_ATTRIBUTES;
    bool    bSuccess = QueryFileAttributes (filePath, uiFileAttributes);

    // Is the file read only?

    if (bSuccess && (uiFileAttributes & FILE_ATTRIBUTE_READONLY))
    {
        // Yes. Make the file writeable.

        uiFileAttributes &= ~FILE_ATTRIBUTE_READONLY;

        bSuccess = SetFileAttributes (filePath, uiFileAttributes);
    } // Endif.

    return (bSuccess);
} // Endproc.


bool    File::MakeFileReadOnly (const std::wstring &filePath)
{
    // Get the file attributes.

    UINT    uiFileAttributes = INVALID_FILE_ATTRIBUTES;
    bool    bSuccess = QueryFileAttributes (filePath, uiFileAttributes);

    // Is the file writeable?

    if (bSuccess && !(uiFileAttributes & FILE_ATTRIBUTE_READONLY))
    {
        // Yes. Make the file read only.

        uiFileAttributes |= FILE_ATTRIBUTE_READONLY;

        bSuccess = SetFileAttributes (filePath, uiFileAttributes);
    } // Endif.

    return (bSuccess);
} // Endproc.


bool    File::QueryFileAttributes (const std::wstring   &filePath,
                                   UINT                 &uiFileAttributes)
{
    bool    bSuccess = true;

    // Get the file attributes.

    uiFileAttributes = ::GetFileAttributesW (filePath.c_str ());

    if (uiFileAttributes == INVALID_FILE_ATTRIBUTES)
    {
        DWORD   dwWin32Error = ::GetLastError ();

        if ((dwWin32Error != ERROR_FILE_NOT_FOUND) &&
            (dwWin32Error != ERROR_PATH_NOT_FOUND))
        {
            LogWin32Error (__LINE__, TEXTW(__FILE__), L"GetFileAttributesW");
        } // Endif.

        bSuccess = false;
    } // Endif.

    return (bSuccess);
} // Endproc.


bool    File::SetFileAttributes (const std::wstring &filePath,
                                 UINT               uiFileAttributes)
{
    bool    bSuccess = true;

    // Set the file attributes.

    if (!::SetFileAttributesW (filePath.c_str (), uiFileAttributes))
    {
        LogWin32Error (__LINE__, TEXTW(__FILE__), L"SetFileAttributesW");

        bSuccess = false;
    } // Endif.

    return (bSuccess);
} // Endproc.


StringList  File::EnumFiles (const std::wstring &path,
                             bool               bRecurse)
{
    StringList  fileList;

    // Is this a directory?

    if (IsDirectory (path))
    {
        // Yes. Build files to search for.

        std::wstring filePath(AddBackslashToPath (path));
        filePath += L"*.*";

        HANDLE          hFind = INVALID_HANDLE_VALUE;
        WIN32_FIND_DATA fileData = {0};
      
        if ((hFind = ::FindFirstFileW (filePath.c_str (), 
                                       &(fileData))) == INVALID_HANDLE_VALUE)
        {
            // No files found.
        } // Endif.
      
        else
        {
            // Find each file in turn.
      
            do
            {
                if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    // We have a directory.
      
                    if (!((::wcscmp (fileData.cFileName, L".")  == 0) || 
                          (::wcscmp (fileData.cFileName, L"..") == 0)))
                    {
                        if (bRecurse)
                        {
                            // Build new subpath.
        
                            std::wstring subPath(AddBackslashToPath (path));
                            subPath += fileData.cFileName;
      
                            // Enumerate its files.

                            StringList  subPathFileList(EnumFiles (subPath, bRecurse));
    
                            if (!subPathFileList.empty ())
                            {
                                // Add files.
    
                                fileList.insert (fileList.end (), 
                                                 subPathFileList.begin (), 
                                                 subPathFileList.end ());
                            } // Endif.
    
                        } // Endif.
    
                    } // Endif.
      
                } // Endif.
        
                else
                {
                    // Build the file path.
        
                    std::wstring    filePath(AddBackslashToPath (path));
                    filePath.append (fileData.cFileName);
    
                    fileList.push_back (filePath);
                } // Endelse.
        
            } // Enddo.
            while (::FindNextFile (hFind, &(fileData)));
      
            // Close file find handle.
      
            ::FindClose (hFind);
        } // Endelse.

    } // Endif.

    return (fileList);
} // Endproc.


void    LogError (UINT                  uiLineNumber, 
                  const std::wstring    &fileName, 
                  UINT                  uiLogId, 
                  const std::wstring    &errorString)
{
    std::wstringstream  str;
    str << SplitPathToFileName(fileName) << SplitPathToFileNameExt(fileName) 
        << L" (" << uiLineNumber << L") " << errorString << std::endl;
    ::wprintf (L"\n");
    ::wprintf (const_cast<LPWSTR> (str.str ().c_str ()));

    OutputDebug (str.str ());

    //BREAKPOINT;
} // Endproc.


void    LogInformation (UINT                uiLineNumber, 
                        const std::wstring  &fileName, 
                        UINT                uiLogId, 
                        const std::wstring  &infoString)
{
    std::wstringstream  str;
    str << SplitPathToFileName(fileName) << SplitPathToFileNameExt(fileName) 
        << L" (" << uiLineNumber << L") " << infoString << std::endl;
    ::wprintf (L"\n");
    ::wprintf (const_cast<LPWSTR> (str.str ().c_str ()));

    OutputDebug (str.str ());

    BREAKPOINT;
} // Endproc.


void    OutputDebug (const std::wstring &string)
{
    ::OutputDebugStringW (string.c_str ());
} // Endproc.


std::wstring    GetComputerName ()
{
    WCHAR   szComputerName [MAX_COMPUTERNAME_LENGTH + 1] = {0}; // Initialise!
    DWORD   dwComputerNameLength = MAX_COMPUTERNAME_LENGTH + 1;
    ::GetComputerNameW (szComputerName, &(dwComputerNameLength));

    return (szComputerName);
} // Endproc.


std::wstring    GetTimeStamp ()
{
    SYSTEMTIME  localTime = {0};
    ::GetLocalTime (&(localTime));

    std::wostringstream str;
    str << static_cast<UINT> (localTime.wDay)
        << static_cast<UINT> (localTime.wMonth)
        << static_cast<UINT> (localTime.wYear)
        << static_cast<UINT> (localTime.wHour)
        << static_cast<UINT> (localTime.wMinute)
        << static_cast<UINT> (localTime.wSecond)
        << static_cast<UINT> (localTime.wMilliseconds);

    return (str.str ());
} // Endproc.


std::string     WideStringToNarrowString (const std::wstring &string)
{
    std::string narrowString;

    int nLength = ::WideCharToMultiByte (CP_ACP, 
                                         0,
                                         string.c_str (), 
                                         -1, 
                                         NULL, 
                                         0,
                                         NULL, 
                                         NULL);

    if (nLength > 0)
    {
        std::vector<char>   narrowBuffer(nLength);

        if (::WideCharToMultiByte (CP_ACP, 
                                   0, 
                                   string.c_str (), 
                                   -1, 
                                   &(narrowBuffer [0]), 
                                   nLength,
                                   NULL,
                                   NULL) > 0)
        {
            narrowString = &(narrowBuffer [0]);
        } // Endif.

        else
        {
            LogWin32Error (__LINE__, TEXTW(__FILE__), L"WideCharToMultiByte");
        } // Endelse.

    } // Endif.

    else
    {
        LogWin32Error (__LINE__, TEXTW(__FILE__), L"WideCharToMultiByte");
    } // Endelse.

    return (narrowString);
} // Endproc.


std::wstring    NarrowStringToWideString (const std::string &string)
{
    std::wstring    wideString;

    int nLength = ::MultiByteToWideChar (CP_ACP, 
                                         0,
                                         string.c_str (), 
                                         -1, 
                                         NULL, 
                                         NULL);

    if (nLength > 0)
    {
        std::vector<wchar_t> wideBuffer(nLength);

        if (::MultiByteToWideChar (CP_ACP, 
                                   0, 
                                   string.c_str (), 
                                   -1, 
                                   &(wideBuffer [0]), 
                                   nLength) > 0)
        {
            wideString = &(wideBuffer [0]);
        } // Endif.

        else
        {
            LogWin32Error (__LINE__, TEXTW(__FILE__), L"MultiByteToWideChar");
        } // Endelse.

    } // Endif.

    else
    {
        LogWin32Error (__LINE__, TEXTW(__FILE__), L"MultiByteToWideChar");
    } // Endelse.

    return (wideString);
} // Endproc.


std::wstring    GetDayOfWeekDescription (UINT uiDayOfWeek)
{
    static  LPCWSTR szDayOfWeek [7] = {L"Sun", L"Mon", L"Tue", L"Wed", L"Thu", L"Fri", L"Sat"};

    if ((uiDayOfWeek >= 0) && (uiDayOfWeek <= 6))
    {
        return (szDayOfWeek [uiDayOfWeek]);
    } // Endif.

    else
    {
        return (L"???");
    } // Endelse.

} // Endproc.


std::wstring    GetMonthDescription (UINT uiMonth)
{
    static  LPCWSTR szMonthNames [12] = {L"Jan", L"Feb", L"Mar", L"Apr", L"May", L"Jun", 
                                         L"Jul", L"Aug", L"Sep", L"Oct", L"Nov", L"Dec"};

    if ((uiMonth >= 1) && (uiMonth <= 12))
    {
        return (szMonthNames [uiMonth - 1]);
    } // Endif.

    else
    {
        return (L"???");
    } // Endelse.

} // Endproc.


UINT    GetMonth (const std::wstring &month)
{
    static  LPCWSTR szMonthNames [12] = {L"Jan", L"Feb", L"Mar", L"Apr", L"May", L"Jun", 
                                         L"Jul", L"Aug", L"Sep", L"Oct", L"Nov", L"Dec"};

    for (UINT uiMonth = 0; uiMonth < sizeof (szMonthNames) / sizeof (LPCWSTR); ++uiMonth)
    {
        if (month == szMonthNames [uiMonth])
        {
            return (uiMonth + 1);
        } // Endif.

    } // Endfor.

    return (1);
} // Endproc.


SYSTEMTIME  GetLocalDateTimeStamp ()
{
    SYSTEMTIME  localDateTimeStamp = {0}; // Initialise!
    ::GetLocalTime (&(localDateTimeStamp));

    return (localDateTimeStamp);
} // Endproc.


bool    IsDate (const SYSTEMTIME &systemTime)

{
    // Day cannot be less than 1.

    if (systemTime.wDay < 1)
    {
        return (false);
    } // Endif.

    // Check for maximum number of days in the month.

    switch (systemTime.wMonth)
    {
    case 1:     // January.
    case 3:     // March.
    case 5:     // May.
    case 7:     // July.
    case 8:     // August.
    case 10:    // October.
    case 12:    // December.
        if (systemTime.wDay > 31)
        {
            return (false);
        } // Endif.
        break;

    case 2:     // February
        // Check for leap year. A leap year is any year divisible by
        // four except years both divisible by 100 and not divisible
        // by 400.                                                    

        if (systemTime.wYear % 4) 
        {
            // Not a leap year.

            if (systemTime.wDay > 28)
            {
                return (false);
            } // Endif.

        } // Endif.

        else
        if (!(systemTime.wYear % 100) && 
             (systemTime.wYear % 400)) 
        {
            // Not a leap year.

            if (systemTime.wDay > 28)
            {
                return (false);
            } // Endif.

        } // Endelse.

        else 
        {
            // Leap year.

            if (systemTime.wDay > 29)
            {
                return (false);
            } // Endif.

        } // Endelse.
        break;

    case 4:     // April.
    case 6:     // June.
    case 9:     // September.
    case 11:    // November.
        if (systemTime.wDay > 30)
        {
            return (false);
        } // Endif.
        break;

    default:
        return (false);
        break;
    } // Endswitch.

    // Year cannot be less than 1601.

    if (systemTime.wYear < 1601)
    {
        return (false);
    } // Endif.

    return (true);
} // Endproc.


bool    IsDecimal (std::wstring::value_type digit,  
                   int                      &nValue)
{
    bool    bIsDecimal = false;

    nValue = 0; // Initialise!

    if ((digit >= L'0') && (digit <= L'9'))
    {
        nValue = digit - L'0';

        bIsDecimal = true;
    } // Endif.

    return (bIsDecimal);
} // Endproc.


bool    IsHexadecimal (std::wstring::value_type digit, 
                       int                      &nValue)
{
    bool    bIsHexadecimal = false;

    nValue = 0;    // Initialise!

    if ((digit >= L'0') && (digit <= L'9'))
    {
        nValue = digit - L'0';

        bIsHexadecimal = true;
    } // Endif.

    else
    if ((digit >= L'A') && (digit <= L'F'))
    {
        nValue = digit - L'A' + 10;

        bIsHexadecimal = true;
    } // Endif.

    else
    if ((digit >= L'a') && (digit <= L'f'))
    {
        nValue = digit - L'a' + 10;

        bIsHexadecimal = true;
    } // Endif.

    return (bIsHexadecimal);
} // Endproc.


bool    StringToDecimal (const std::wstring &string,
                         int                &nValue)
{
    bool    bIsDecimal = false;

    nValue = 0; // Initialise!

    std::wstring    myString(string);
    RemoveWhiteSpace (myString, true);

    if (myString.find_first_not_of (L"-+0123456789") == std::wstring::npos)
    {
        bIsDecimal = true;

        bool    bFoundSign  = false; // Initialise!
        bool    bPositive   = true;

        for (std::wstring::const_iterator itr = myString.begin ();
             bIsDecimal && (itr != myString.end ());
             ++itr)
        {
            switch (*itr)
            {
            case '+':
                if (bFoundSign)
                {
                    bIsDecimal = false;
                } // Endif.

                else
                {
                    bFoundSign  = true;
                    bPositive   = true;
                } // Endif.
                break;

            case '-':
                if (bFoundSign)
                {
                    bIsDecimal = false;
                } // Endif.

                else
                {
                    bFoundSign  = true;
                    bPositive   = false;
                } // Endif.
                break;

            default:
                {
                    int nMyValue = 0;

                    if (IsDecimal (*itr, nMyValue))
                    {
                        nValue *= 10;
                        nValue += nMyValue;
                    } // Endif.
        
                    else
                    {
                        bIsDecimal = false;
                    } // Endelse.

                } // Endscope.
                break;
            } // Endswitch.
    
        } // Endfor.

        if (bIsDecimal && !bPositive)
        {
            nValue *= -1;
        } // Endif.

    } // Endif.

    if (!bIsDecimal)
    {
        nValue = 0; // Initialise!
    } // Endif.

    return (bIsDecimal);
} // Endproc.


bool    StringToHexadecimal (const std::wstring &string,
                             DataList           &data)
{
    data.clear ();  // Initialise!

    std::wstring    myString(string);
    RemoveWhiteSpace (myString, true);

    int nValue = 0; // Initialise!
    int nCount = 0;

    for (std::wstring::const_iterator itr = myString.begin ();
         itr != myString.end ();
         ++itr)
    {
        int nMyValue = 0;

        if (IsHexadecimal (*itr, nMyValue))
        {
            nValue *= 16;
            nValue += nMyValue;

            if (++nCount == 2)
            {
                data.push_back (nValue);

                nValue = 0;
                nCount = 0;
            } // Endif.

        } // Endif.

        else
        if (!IsWhiteSpace (*itr))
        {
            break;
        } // Endelse.

    } // Endfor.

    return (!data.empty ());
} // Endproc.


bool    StringToHexadecimal (const std::wstring &string,
                             int                &nValue)
{
    bool    bIsHexadecimal = false;

    nValue = 0; // Initialise!

    std::wstring    myString(string);
    RemoveWhiteSpace (myString, true);

    if (myString.find_first_not_of (L"0123456789abcdefABCDEF") == std::wstring::npos)
    {
        bIsHexadecimal = true;

        bool    bFoundSign  = false; // Initialise!

        for (std::wstring::const_iterator itr = myString.begin ();
             bIsHexadecimal && (itr != myString.end ());
             ++itr)
        {
            int nMyValue = 0;

            if (IsHexadecimal (*itr, nMyValue))
            {
                nValue *= 16;
                nValue += nMyValue;
            } // Endif.

            else
            {
                bIsHexadecimal = false;
            } // Endelse.
    
        } // Endfor.

    } // Endif.

    if (!bIsHexadecimal)
    {
        nValue = 0; // Initialise!
    } // Endif.

    return (bIsHexadecimal);
} // Endproc.


bool    StringToInteger (const std::wstring &string,
                         int                &nValue)
{
    bool    bIsInteger = false;

    nValue = 0; // Initialise!

    std::wstring    myString(string);
    RemoveWhiteSpace (myString, true);

    std::wstring::size_type pos = myString.find_first_not_of (L"-+0123456789abcdefABCDEF");
    
    if (pos != std::wstring::npos)
    {
        myString.erase (pos);

        if (myString.find_first_of (L"abcdefABCDEF") == std::wstring::npos)
        {
            bIsInteger = StringToDecimal (myString, nValue);
        } // Endif.
    
        else
        {
            bIsInteger = StringToHexadecimal (myString, nValue);
        } // Endelse.
    
    } // Endif.

    return (bIsInteger);
} // Endproc.


bool    IsDate (const FILETIME &fileTime)

{
    // Convert the file time to a system time.

    SYSTEMTIME  systemTime;
    if (!::FileTimeToSystemTime (&(fileTime), &(systemTime)))
    {
        return (false);
    } // Endif.

    return (IsDate (systemTime));
} // Endproc.


bool    IsDateForward (const FILETIME   &currentFileTime,
                       const FILETIME   &previousFileTime,
                       bool             bCheckHoursMins)
{
    // Are the file times valid?

    if (!IsDate (currentFileTime) || 
        !IsDate (previousFileTime))
    {
        return (false);
    } // Endif.

    return (::CompareFileTime (&(currentFileTime), &(previousFileTime)) == 1);
} // Endproc.


bool    IsDateBackward (const FILETIME  &currentFileTime,
                        const FILETIME  &previousFileTime,
                        bool            bCheckHoursMins)
{
    // Are the file times valid?

    if (!IsDate (currentFileTime) || 
        !IsDate (previousFileTime))
    {
        return (false);
    } // Endif.

    return (::CompareFileTime (&(currentFileTime), &(previousFileTime)) == -1);
} // Endproc.


bool    IsDateEqual (const FILETIME &currentFileTime,
                     const FILETIME &previousFileTime,
                     bool           bCheckHoursMins)
{
    // Are the file times valid?

    if (!IsDate (currentFileTime) || 
        !IsDate (previousFileTime))
    {
        return (false);
    } // Endif.

    return (::CompareFileTime (&(currentFileTime), &(previousFileTime)) == 0);
} // Endproc.


SYSTEMTIME  FileTimeToSystemTime (const FILETIME &fileTime)
{
    SYSTEMTIME  systemTime = {0};

    // Is the file time valid?

    if (IsDate (fileTime))
    {
        // Convert the file time to system time.
        ::FileTimeToSystemTime (&(fileTime), &(systemTime));
    } // Endif.

    return (systemTime);
} // Endproc.


SYSTEMTIME  FileTimeToLocalTime (const FILETIME &fileTime)
{
    SYSTEMTIME  localTime = {0};

    // Is the file time valid?

    if (IsDate (fileTime))
    {
        // Convert the file time to local file time.
        FILETIME    localFileTime;
        ::FileTimeToLocalFileTime (&(fileTime), &(localFileTime));
    
        // Convert the local file time to system time.
        ::FileTimeToSystemTime (&(localFileTime), &(localTime));
    } // Endif.

    return (localTime);
} // Endproc.


FILETIME    FileTimeToLocalFileTime (const FILETIME &fileTime)
{
    FILETIME  localFileTime = {0};

    // Is the file time valid?

    if (IsDate (fileTime))
    {
        // Convert the file time to local file time.
        ::FileTimeToLocalFileTime (&(fileTime), &(localFileTime));
    } // Endif.

    return (localFileTime);
} // Endproc.


FILETIME    SystemTimeToFileTime (const SYSTEMTIME &localTime)
{
    FILETIME  fileTime = {0};

    // Is the system time valid?

    if (IsDate (localTime))
    {
        // Convert the system time to file time.
        ::SystemTimeToFileTime (&(localTime), &(fileTime));
    } // Endif.

    return (fileTime);
} // Endproc.


FILETIME    LocalTimeToFileTime (const SYSTEMTIME &localTime)
{
    FILETIME  fileTime = {0};

    // Is the system time valid?

    if (IsDate (localTime))
    {
        // Convert the local time to file time.
        ::SystemTimeToFileTime (&(localTime), &(fileTime));
    } // Endif.

    return (fileTime);
} // Endproc.


FILETIME    TimetToFileTime (time_t t)
{
    LONGLONG ll = Int32x32To64(t, 10000000) + 116444736000000000;

    FILETIME  fileTime;
    fileTime.dwLowDateTime = (DWORD) ll;
    fileTime.dwHighDateTime = ll >> 32;

    return (fileTime);
} // Endproc.


// Format is MM/DD/YYYY HH:MM

#define SIZEOF_DATETIME             ::strlen("MM/DD/YYYY HH:MM")

#define TOD_STRING_MONTH_OFFSET     0
#define TOD_STRING_MONTH_SIZE       2

#define TOD_STRING_DAY_OFFSET       (TOD_STRING_MONTH_OFFSET + TOD_STRING_MONTH_SIZE + 1)
#define TOD_STRING_DAY_SIZE         2

#define TOD_STRING_YEAR_OFFSET      (TOD_STRING_DAY_OFFSET + TOD_STRING_DAY_SIZE + 1)
#define TOD_STRING_YEAR_SIZE        4

#define TOD_STRING_HOUR_OFFSET      (TOD_STRING_YEAR_OFFSET + TOD_STRING_YEAR_SIZE + 1)
#define TOD_STRING_HOUR_SIZE        2

#define TOD_STRING_MINUTE_OFFSET    (TOD_STRING_HOUR_OFFSET + TOD_STRING_HOUR_SIZE + 1)
#define TOD_STRING_MINUTE_SIZE      2

FILETIME    DateTimeStringToFileTime (const std::wstring &dateTime)
{
    FILETIME    fileTime    = {0};
    SYSTEMTIME  systemTime  = {0};

    std::wstring    line(dateTime);

    // Remove any white space from the start of the line.

    RemoveWhiteSpace (line, true);

    // Remove any white space from the end of the line.

    RemoveWhiteSpace (line, false);

    // Make sure that the string contains a valid date/time and then get it.

    // Format is MM/DD/YYYY HH:MM

    if ((line.length () == 0) || (line.length () < SIZEOF_DATETIME))
    {
        return (fileTime);
    } // Endif.

    if ((line [TOD_STRING_MONTH_OFFSET  + TOD_STRING_MONTH_SIZE ] != '/') ||
        (line [TOD_STRING_DAY_OFFSET    + TOD_STRING_DAY_SIZE   ] != '/') ||
        (line [TOD_STRING_YEAR_OFFSET   + TOD_STRING_YEAR_SIZE  ] != ' ') ||
        (line [TOD_STRING_HOUR_OFFSET   + TOD_STRING_HOUR_SIZE  ] != ':'))
    {
        return (fileTime);
    } // Endif.

    int nThousands  = 0;
    int nHundreds   = 0;
    int nTens       = 0;
    int nUnits      = 0;

    // Month.

    if (!IsDecimal (line [TOD_STRING_MONTH_OFFSET    ], nTens)    ||
        !IsDecimal (line [TOD_STRING_MONTH_OFFSET + 1], nUnits))
    {
        return (fileTime);
    } // Endif.

    systemTime.wMonth = nTens * 10 + nUnits;

    // Day.

    if (!IsDecimal (line [TOD_STRING_DAY_OFFSET    ], nTens)  ||
        !IsDecimal (line [TOD_STRING_DAY_OFFSET + 1], nUnits))
    {
        return (fileTime);
    } // Endif.

    systemTime.wDay = nTens * 10 + nUnits;

    // Year.

    if (!IsDecimal (line [TOD_STRING_YEAR_OFFSET    ], nThousands)    ||
        !IsDecimal (line [TOD_STRING_YEAR_OFFSET + 1], nHundreds)     ||
        !IsDecimal (line [TOD_STRING_YEAR_OFFSET + 2], nTens)         ||
        !IsDecimal (line [TOD_STRING_YEAR_OFFSET + 3], nUnits))
    {
        return (fileTime);
    } // Endif.

    systemTime.wYear = nThousands * 1000    + 
                       nHundreds  * 100     +
                       nTens      * 10      +
                       nUnits;

    // Zeller's algorithm is used to compute the day of the week on which 
    // a given date will fall (or fell).
    // 
    //      wMonth = the month of the year, with March having the value 1, 
    //               April the value 2, ..., December the value 10, and with
    //               January and February being counted as months 11 and 12
    //               of the preceding year (in which case, subtract 1 from 
    //               wYearInCentuary).
    // 
    //      wDay = the day of the month (1, 2, 3, ..., 28, 29, 30, 31).
    // 
    //      wYearInCentuary = the year of the century (this would be 95 for 
    //                        the year 1895).
    // 
    //      wCentuary = the century (this would be 18 for the year 1895). 
    // 
    // Next let W, X, Y, Z and R denote integer variables, and compute the 
    // following values in this order, using integer arithmetic.
    // 
    //      W = (13 * wMonth - 1) / 5
    //      X = wYearInCentuary / 4
    //      Y = wCentuary / 4
    //      Z = W + X + Y + wDay + wYearInCentuary - 2 * wCentuary
    //      R = the remainder obtained when Z is divided by 7.
    // 
    // The value of R represents the day of the week, where R=
    // 
    //      0 Sunday
    //      1 Monday
    //      2 Tuesday
    //      3 Wednesday
    //      4 Thursday
    //      5 Friday
    //      6 Saturday
    // 
    // If R turns out to have a negative value such as -4, add 7 to it to 
    // get a nonnegative value between 0 and 6.     
    
    WORD    wDay   = systemTime.wDay;
    WORD    wMonth = systemTime.wMonth;
    WORD    wYear  = systemTime.wYear;

    if (wMonth >= 3)    // March
    {
        wMonth -= 2;
    } // Endif.
    else
    {
        wMonth += 10;
    } // Endif.

    if ((wMonth == 11) || (wMonth == 12))
    {
        wYear--;
    } // Endif.

    WORD    wYearOfCentuary = wYear % 100;
    WORD    wCentuary       = wYear / 100;

    int     nDayOfWeek = (13 * wMonth - 1) / 5 + 
                         (wYearOfCentuary / 4) +
                         (wCentuary / 4)       +
                         wDay                  +
                         wYearOfCentuary       -
                         2 * wCentuary;

    nDayOfWeek %= 7;
    if (nDayOfWeek < 0)
    {
        nDayOfWeek += 7;
    } // Endif.

    systemTime.wDayOfWeek = (WORD) (nDayOfWeek);

    // Hour.

    if (!IsDecimal (line [TOD_STRING_HOUR_OFFSET    ], nTens)     ||
        !IsDecimal (line [TOD_STRING_HOUR_OFFSET + 1], nUnits))
    {
        return (fileTime);
    } // Endif.

    systemTime.wHour = nTens * 10 + nUnits;

    // Minute.

    if (!IsDecimal (line [TOD_STRING_MINUTE_OFFSET    ], nTens)   ||
        !IsDecimal (line [TOD_STRING_MINUTE_OFFSET + 1], nUnits))
    {
        return (fileTime);
    } // Endif.

    systemTime.wMinute = nTens * 10 + nUnits;

    // Second.

    systemTime.wSecond = 0;

    // Milliseconds.

    systemTime.wMilliseconds = 0;

    // Check the system time is valid.

    if (!IsDate (systemTime))
    {
        return (fileTime);
    } // Endif.

    // Convert the system time to file time.

    ::SystemTimeToFileTime (&(systemTime), &(fileTime));

    return (fileTime);
} // Endproc.


UINT    GetDayOfWeek (UINT   uiDay,
                      UINT   uiMonth, 
                      UINT   uiYear)
{ 
    static  UINT t [] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4}; 

    uiYear -= uiMonth < 3; 

    if (uiMonth > 1)
    {
        --uiMonth;
    } // Endif.

    return ((uiYear + (uiYear / 4) - (uiYear / 100) + (uiYear / 400) + t [uiMonth % 12] + uiDay) % 7); 
} // Endproc.


bool    IsWhiteSpace (std::wstring::value_type character)
{
    bool    bIsWhiteSpace = false;

    switch (character)
    {
    case L' ':
    case L'\t': // TAB
    case L'\r': // CR
    case L'\n': // LF
    case L'\v': // VT
    case L'\f': // FF
        bIsWhiteSpace = true;
        break;

    default:
        bIsWhiteSpace = false;
        break;
    } // Endswitch.

    return (bIsWhiteSpace);
} // Endproc.


void    RemoveWhiteSpace (std::string   &line, 
                          bool          bStartOfLine)
{
    if (line.length ())
    {
        bool    bFinished = false;
    
        if (bStartOfLine)
        {
            // Remove any white space from the start of the line.
        
            std::string::iterator   itrLine = line.begin ();
        
            do
            {
                switch (*itrLine)
                {
                case L' ':
                case L'\t': // TAB
                case L'\r': // CR
                case L'\n': // LF
                case L'\v': // VT
                case L'\f': // FF
                    itrLine = line.erase (itrLine);
                    break;
                default:
                    bFinished = true;
                    break;
                } // Endswitch.
        
            } // Enddo.
            while (!bFinished && (itrLine != line.end ()));
        } // Endif.
    
        else
        {
            // Remove any white space from the end of the line.
    
            std::string::reverse_iterator   ritrLine = line.rbegin ();
    
            do
            {
                switch (*ritrLine)
                {
                case L' ':
                case L'\t': // TAB
                case L'\r': // CR
                case L'\n': // LF
                case L'\v': // VT
                case L'\f': // FF
                    ritrLine = std::string::reverse_iterator(line.erase ((++ritrLine).base ()));
                    break;
                default:
                    bFinished = true;
                    break;
                } // Endswitch.
        
            } // Enddo.
            while (!bFinished && (ritrLine != line.rend ()));
        } // Endelse.

    } // Endif.

} // Endproc.


void    RemoveWhiteSpace (std::wstring  &line, 
                          bool          bStartOfLine)
{
    if (line.length ())
    {
        bool    bFinished = false;
    
        if (bStartOfLine)
        {
            // Remove any white space from the start of the line.
        
            std::wstring::iterator  itrLine = line.begin ();
        
            do
            {
                switch (*itrLine)
                {
                case L' ':
                case L'\t': // TAB
                case L'\r': // CR
                case L'\n': // LF
                case L'\v': // VT
                case L'\f': // FF
                    itrLine = line.erase (itrLine);
                    break;
                default:
                    bFinished = true;
                    break;
                } // Endswitch.
        
            } // Enddo.
            while (!bFinished && (itrLine != line.end ()));
        } // Endif.
    
        else
        {
            // Remove any white space from the end of the line.
    
            std::wstring::reverse_iterator  ritrLine = line.rbegin ();
    
            do
            {
                switch (*ritrLine)
                {
                case L' ':
                case L'\t': // TAB
                case L'\r': // CR
                case L'\n': // LF
                case L'\v': // VT
                case L'\f': // FF
                    ritrLine = std::wstring::reverse_iterator(line.erase ((++ritrLine).base ()));
                    break;
                default:
                    bFinished = true;
                    break;
                } // Endswitch.
        
            } // Enddo.
            while (!bFinished && (ritrLine != line.rend ()));
        } // Endelse.

    } // Endif.

} // Endproc.


void    RemoveNumbers (std::string &string)
{
    // Remove any numbers from the string.

    std::string::iterator   itrString = string.begin ();

    while (itrString != string.end ())
    {
        switch (*itrString)
        {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
            itrString = string.erase (itrString);
            break;
        default:
            ++itrString;
            break;
        } // Endswitch.

    } // Endwhile.

} // Endproc.


void    RemoveNumbers (std::wstring &string)
{
    // Remove any numbers from the string.

    std::wstring::iterator   itrString = string.begin ();

    while (itrString != string.end ())
    {
        switch (*itrString)
        {
        case L'1':
        case L'2':
        case L'3':
        case L'4':
        case L'5':
        case L'6':
        case L'7':
        case L'8':
        case L'9':
        case L'0':
            itrString = string.erase (itrString);
            break;
        default:
            ++itrString;
            break;
        } // Endswitch.

    } // Endwhile.

} // Endproc.


UINT    QueryRegistryValue (HKEY                hKey,
                            const std::wstring  &valueName,
                            UINT                &value)
{
    DWORD   dwWin32Error = ERROR_SUCCESS;

    value = -1; // Initialise!

    DWORD   dwValue     = -1;
    DWORD   dwValueSize = sizeof (dwValue);
    DWORD   dwValueType = 0;

    dwWin32Error = ::RegQueryValueExW (hKey,
                                       valueName.c_str (),
                                       NULL,
                                       &(dwValueType),
                                       reinterpret_cast<LPBYTE> (&(dwValue)),
                                       &(dwValueSize));

    if ((dwWin32Error == ERROR_SUCCESS) && (dwValueType == REG_DWORD))
    {
        value = dwValue;
    } // Endif.

    return (dwWin32Error);
} // Endproc.


UINT    QueryRegistryValue (HKEY                  hKey,
                            const std::wstring    &valueName,
                            std::wstring          &value)
{
    DWORD   dwWin32Error = ERROR_SUCCESS;

    value.clear ();   // Initialise!

    DataList   byValueBuffer;
    DWORD   dwValueBufferSize   = 1024;
    DWORD   dwValueType         = 0;

    do
    {
        byValueBuffer.resize (dwValueBufferSize);
        dwValueType = 0;
    
        dwWin32Error = ::RegQueryValueExW (hKey,
                                           valueName.c_str (),
                                           NULL,
                                           &(dwValueType),
                                           &(byValueBuffer [0]),
                                           &(dwValueBufferSize));
    } // Enddo.
    while (dwWin32Error == ERROR_MORE_DATA);

    if ((dwWin32Error == ERROR_SUCCESS) && (dwValueType == REG_SZ))
    {
        value = reinterpret_cast<LPWSTR> (&(byValueBuffer [0]));
    } // Endif.

    return (dwWin32Error);
} // Endproc.


std::wstring    BuildDateTime (const SYSTEMTIME &systemTime, 
                               bool             bSecondsRqd,
                               bool             bMillisecondsRqd,
                               bool             bMonthDescriptionRqd)
{
    return (BuildDateTime (systemTime.wDay,
                           systemTime.wMonth,
                           systemTime.wYear,
                           systemTime.wHour, 
                           systemTime.wMinute, 
                           systemTime.wSecond, 
                           systemTime.wMilliseconds,
                           bSecondsRqd,
                           bMillisecondsRqd,
                           bMonthDescriptionRqd));
} // Endproc.


std::wstring    BuildDateTime (UINT uiDay,
                               UINT uiMonth,
                               UINT uiYear,
                               UINT uiHour, 
                               UINT uiMinute, 
                               UINT uiSecond, 
                               UINT uiMilliseconds,
                               bool bSecondsRqd,
                               bool bMillisecondsRqd,
                               bool bMonthDescriptionRqd)
{
    WCHAR   szDateTime [256];

    UINT    uiLength = 0;
    
    if (bMonthDescriptionRqd)
    {
        uiLength = ::wsprintfW (szDateTime, 
                                L"%02d/%s/%04d %02d:%02d",
                                uiDay, 
                                GetMonthDescription (uiMonth).c_str (), 
                                uiYear,                    
                                uiHour,                    
                                uiMinute);
    } // Endif.

    else
    {
        uiLength = ::wsprintfW (szDateTime, 
                                L"%02d/%02d/%04d %02d:%02d",
                                uiDay, 
                                uiMonth, 
                                uiYear,
                                uiHour, 
                                uiMinute);
    } // Endelse.

    // If milliseconds are required, then automatically include seconds.

    if (bMillisecondsRqd)
    {
        bSecondsRqd = true;
    } // Endif.

    if (bSecondsRqd)
    {
        uiLength += ::wsprintfW (&(szDateTime [uiLength]), 
                                 L":%02d",
                                 uiSecond);
    } // Endif.

    if (bMillisecondsRqd)
    {
        ::wsprintfW (&(szDateTime [uiLength]), 
                     L":%03d",
                     uiMilliseconds);
    } // Endif.

    return (szDateTime);
} // Endproc.


std::wstring    BuildDate (const SYSTEMTIME &systemTime,
                           bool             bMonthDescriptionRqd)
{
    return (BuildDate (systemTime.wDay,
                       systemTime.wMonth,
                       systemTime.wYear,
                       bMonthDescriptionRqd));
} // Endproc.


std::wstring    BuildDate (UINT uiDay,
                           UINT uiMonth,
                           UINT uiYear,
                           bool bMonthDescriptionRqd)
{
    WCHAR   szDate [256];

    UINT    uiLength = 0;
    
    if (bMonthDescriptionRqd)
    {
        uiLength = ::wsprintfW (szDate, 
                                L"%02d/%s/%04d",
                                uiDay, 
                                GetMonthDescription (uiMonth).c_str (), 
                                uiYear);
    } // Endif.

    else
    {
        uiLength = ::wsprintfW (szDate, 
                                L"%02d/%02d/%04d",
                                uiDay, 
                                uiMonth, 
                                uiYear);
    } // Endelse.

    return (szDate);
} // Endproc.


std::wstring    BuildTime (const SYSTEMTIME &systemTime,
                           bool             bSecondsRqd,
                           bool             bMillisecondsRqd)
{
    return (BuildTime (systemTime.wHour, 
                       systemTime.wMinute, 
                       systemTime.wSecond, 
                       systemTime.wMilliseconds,
                       bSecondsRqd,
                       bMillisecondsRqd));
} // Endproc.


std::wstring    BuildTime (UINT uiHour, 
                           UINT uiMinute, 
                           UINT uiSecond, 
                           UINT uiMilliseconds,
                           bool bSecondsRqd,
                           bool bMillisecondsRqd)
{
    WCHAR   szTime [256];

    UINT    uiLength = ::wsprintfW (szTime, 
                                    L"%02d:%02d",
                                    uiHour, 
                                    uiMinute);

    // If milliseconds are required, then automatically include seconds.

    if (bMillisecondsRqd)
    {
        bSecondsRqd = true;
    } // Endif.

    if (bSecondsRqd)
    {
        uiLength += ::wsprintfW (&(szTime [uiLength]), 
                                 L":%02d",
                                 uiSecond);
    } // Endif.

    if (bMillisecondsRqd)
    {
        ::wsprintfW (&(szTime [uiLength]), 
                     L":%03d",
                     uiMilliseconds);
    } // Endif.

    return (szTime);
} // Endproc.


std::wstring    BuildByteBuffer (UINT           uiBufferLength,
                                 const LPBYTE   lpbyBuffer)
{
    std::wstringstream  str;

    for (UINT uiOffset = 0;
         uiOffset != uiBufferLength;
         ++uiOffset)
    {
        if (uiOffset != 0)
        {
            str << L' ';
        } // Endif.

        int n = lpbyBuffer [uiOffset];

        str << std::setfill(L'0') << std::setw(2) << std::hex << n;
    } // Endfor.

    return (str.str ());
} // Endproc.


std::wstring    BuildByteBuffer (const DataList &byBuffer)
{
    std::wstringstream  str;

    DataList::const_iterator   itrEnd = byBuffer.end ();

    for (DataList::const_iterator itr = byBuffer.begin ();
         itr != itrEnd;
         ++itr)
    {
        if (itr != byBuffer.begin ())
        {
            str << L' ';
        } // Endif.

        int n = *itr;

        str << std::setfill(L'0') << std::setw(2) << std::hex << n;
    } // Endfor.

    return (str.str ());
} // Endproc.


std::wstring    ByteBufferToCString (const DataList &byBuffer)
{
    std::wstringstream  str;

    DataList::const_iterator   itrEnd = byBuffer.end ();

    for (DataList::const_iterator itr = byBuffer.begin ();
         itr != itrEnd;
         ++itr)
    {
        int n = *itr;

        str << L"\\x" << std::setfill(L'0') << std::setw(2) << std::hex << n;
    } // Endfor.

    return (str.str ());
} // Endproc.


static  int ToHex (const std::wstring::value_type &ch)
{
    int value = -1;

    switch (ch)
    {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        value = ch - '0';
        break;

    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
        value = ch - 'A' + 10;
        break;

    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
        value = ch - 'a' + 10;
        break;

    default:
        value = -1;
        break;
    } // Endswitch.

    return (value);
} // Endproc.


DataList    CStringToByteBuffer (const std::wstring &string)
{
    DataList    byBuffer;

    std::wstring::const_iterator    itr    = string.begin ();
    std::wstring::const_iterator    itrEnd = string.end ();

    while (itr != itrEnd)
    {
        switch (*itr)
        {
        case L'\\':
        case L'x':
            ++itr;  // Skip
            break;

        default:
            byBuffer.push_back (ToHex(*itr) * 16 + ToHex(*(itr + 1)));
            itr += 2;
            break;
        } // Endswitch.

    } // Endwhile.

    return (byBuffer);
} // Endproc.


std::wstring    BuildStringData (const std::wstring &stringData,
                                 bool               bAddQuotes)
{
    std::wstringstream  str;

    if (bAddQuotes)
    {
        str << L'"';
    } // Endif.

    std::wstring::const_iterator   itrEnd = stringData.end ();

    for (std::wstring::const_iterator itr = stringData.begin ();
         itr != itrEnd;
         ++itr)
    {
        switch (*itr)
        {
        case '\r': // CR.
        case '\n': // LF.
        case '\v': // VT
        case '\f': // FF
            break;

        case L'\"':
            //str << L"'";
            break;

        default:
            str << *itr;
            break;
        } // Endswitch.

    } // Endfor.

    if (bAddQuotes)
    {
        str << L'"';
    } // Endif.

    return (str.str ());
} // Endproc.


std::wstring    SplitPath (const std::wstring &path,
                           bool               bDrive,
                           bool               bDirectory,
                           bool               bFileName,
                           bool               bFileNameExt)
{
    // Split the path into a drive.

    WCHAR   szDrive [_MAX_DRIVE] = {0};
    WCHAR   szDirectory [_MAX_DIR] = {0};
    WCHAR   szFileName [_MAX_FNAME] = {0};
    WCHAR   szFileNameExt [_MAX_EXT] = {0};
    ::_wsplitpath_s (path.c_str (), 
                     bDrive ? szDrive : NULL,
                     bDrive ? ARRAYSIZE(szDrive) : 0,
                     bDirectory ? szDirectory : NULL,
                     bDirectory ? ARRAYSIZE(szDirectory) : 0,
                     bFileName ? szFileName : NULL,
                     bFileName ? ARRAYSIZE(szFileName) : 0,
                     bFileNameExt ? szFileNameExt : NULL,
                     bFileNameExt ? ARRAYSIZE(szFileNameExt) : 0);

    std::wstring    splitPath;
    if (bDrive)
    {
        splitPath += szDrive;
    } // Endif.

    if (bDirectory)
    {
        splitPath += szDirectory;
    } // Endif.

    if (bFileName)
    {
        splitPath += szFileName;
    } // Endif.

    if (bFileNameExt)
    {
        splitPath += szFileNameExt;
    } // Endif.

    return (splitPath);
} // Endproc.


std::wstring    SplitPathToDrive (const std::wstring &path)
{
    // Split the path into a drive.

    WCHAR   szDrive [_MAX_DRIVE] = {0};
    ::_wsplitpath_s (path.c_str (), 
                     szDrive, ARRAYSIZE(szDrive),
                     NULL, 0,   // Directory.
                     NULL, 0,   // File name.
                     NULL, 0);  // File name ext.

    return (szDrive);
} // Endproc.


std::wstring    SplitPathToDirectory (const std::wstring &path)
{
    // Split the path into a directory .

    WCHAR   szDirectory [_MAX_DIR] = {0};
    ::_wsplitpath_s (path.c_str (), 
                     NULL, 0,   // Drive.
                     szDirectory, ARRAYSIZE(szDirectory),
                     NULL, 0,   // File name.
                     NULL, 0);  // File name ext.

    return (szDirectory);
} // Endproc.


std::wstring    SplitPathToFileName (const std::wstring &path)
{
    // Split the path into a file name.

    WCHAR   szFileName [_MAX_FNAME] = {0};
    ::_wsplitpath_s (path.c_str (), 
                     NULL, 0,   // Drive.
                     NULL, 0,   // Directory.
                     szFileName, ARRAYSIZE(szFileName),
                     NULL, 0);  // File name ext.

    return (szFileName);
} // Endproc.


std::wstring    SplitPathToFileNameExt (const std::wstring &path)
{
    // Split the path into a file extension.

    WCHAR   szFileNameExt [_MAX_EXT] = {0};
    ::_wsplitpath_s (path.c_str (), 
                     NULL, 0,   // Drive.
                     NULL, 0,   // Directory.
                     NULL, 0,   // File name.
                     szFileNameExt, ARRAYSIZE(szFileNameExt));

    return (szFileNameExt);
} // Endproc.


std::wstring    ToUpper (const std::wstring &string)
{
    std::wstring    convertedString(string);

    std::transform (convertedString.begin (),
                    convertedString.end (),
                    convertedString.begin (),
                    ::towupper);

    return (convertedString);
} // Endproc.


std::wstring    ToLower (const std::wstring &string)
{
    std::wstring    convertedString(string);

    std::transform (convertedString.begin (),
                    convertedString.end (),
                    convertedString.begin (),
                    ::towlower);

    return (convertedString);
} // Endproc.


std::wstring    GetCommandLine (int     argc, 
                                TCHAR   *argv [])
{
    std::wostringstream str;

    for (int nArgIndex = 0; 
         (nArgIndex < argc); 
         ++nArgIndex)
    {
        if (nArgIndex == 0)
        {
            str << SplitPath(argv [nArgIndex], false, false, true, true) << L' ';
        } // Endif.

        else
        {
            str << argv [nArgIndex] << L' ';
        } // Endelse.

    } // Endfor.

    return (str.str ());
} // Endproc.

} // Endnamespace.

/******************************* End of File *******************************/