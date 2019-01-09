#pragma once

#include    <string>

#pragma pack(push, 1)

namespace Utils
{

class File
{
public:
    File ();
    virtual ~File ();

    DWORD   Create (const std::wstring  &filePath,
                    UINT                uiDesiredAccess,
                    UINT                uiShareMode,
                    UINT                uiCreationDisposition,
                    UINT                uiAttributes = FILE_ATTRIBUTE_NORMAL);
    DWORD   Close ();
    DWORD   Read (LPVOID        lpvBuffer,
                  UINT          &uiNumOfBytes,
                  LPOVERLAPPED  lpOverlapped = 0) const;
    DWORD   Write (const LPVOID lpvBuffer,
                   UINT         &uiNumOfBytes,
                   LPOVERLAPPED lpOverlapped = 0) const;
    DWORD   GetOverlappedResult (const OVERLAPPED   &overlapped,
                                 bool               bWaitForCompletion,
                                 UINT               &uiNumOfBytes) const;
    DWORD   QuerySize (UINT &uiLowOrderSize,
                       UINT &uiHighOrderSize) const;
    DWORD   SetFilePointer (UINT uiDistanceFromStart) const;
    DWORD   MoveToStartOfFile () const;
    DWORD   MoveToEndOfFile () const;
    DWORD   SetEndOfFile (UINT uiDistanceFromStart) const;
    DWORD   Clear () const;

    HANDLE          GetFileHandle () const;
    std::wstring    GetFilePath () const;
    bool            IsFileOpen () const;

private:
    std::wstring    m_filePath;   // The name of the file.

    HANDLE  m_hFile;    // The file handle.

    // Private copy constructor to prevent copying.
    File (const File &rhs);

    // Private assignment operator to prevent copying.
    File &operator = (const File &rhs);
}; // Endclass.

}; // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
