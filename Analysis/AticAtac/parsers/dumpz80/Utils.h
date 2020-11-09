#pragma once

#include    <set>
#include    <string>
#include    <vector>

extern  char*           stristr (const char* str1, const char* str2);
extern  unsigned short* wcsistr (const unsigned short* str1, const unsigned short* str2);

namespace Utils
{

typedef std::vector<std::wstring>   StringList;
typedef std::set<std::wstring>      StringSet;
typedef std::vector<BYTE>           DataList;
typedef std::set<BYTE>              DataSet;

// Convert ASCII string to Unicode.

#define     __TEXTW(string) L##string
#define     TEXTW(string)   __TEXTW(string)

const   UINT    LOG_UTILS_ERROR     = 1;
const   UINT    LOG_WIN32_ERROR     = 2;

const   UINT    MAX_OUTPUT_LENGTH   = 2048;
const   UINT    MAX_ERROR_LENGTH    = 2048;

#define LogWin32ErrorWithStatus(uiLineNumber, szFileName, szWin32Function, dwWin32Error)    {WCHAR  szWin32Error [Utils::MAX_ERROR_LENGTH];\
                                                                                             ::wsprintfW (szWin32Error,\
                                                                                                          L"Error from ::%ws. dwWin3Error=%u(0x%08.08x)",\
                                                                                                          szWin32Function,\
                                                                                                          dwWin32Error,\
                                                                                                          dwWin32Error);\
                                                                                             Utils::LogError (uiLineNumber, szFileName, Utils::LOG_WIN32_ERROR, szWin32Error);}

#define LogWin32Error(uiLineNumber, szFileName, szWin32Function)    {LogWin32ErrorWithStatus (uiLineNumber, szFileName, szWin32Function, ::GetLastError ());}

#ifdef _DEBUG
    #define BREAKPOINT _asm {int 3};
#else
    #define BREAKPOINT
#endif


// Classes.

class File
{
public:
    static  const   DWORD   CURRENT_FILE_OFFSET = -1;

    File (bool bLogError = true)
    :   m_hFile(INVALID_HANDLE_VALUE),
        m_bLogError(bLogError),
        m_dwLastError(ERROR_SUCCESS)
    {}

    File (const std::wstring    &filePath,
          bool                  bLogError = true)
    :   m_filePath(filePath),
        m_hFile(INVALID_HANDLE_VALUE),
        m_bLogError(bLogError),
        m_dwLastError(ERROR_SUCCESS)
    {}

    ~File ();

    void    EnableLogError (bool bLogError = true)
    {m_bLogError = bLogError;}

    bool    Create (bool    bReadAccess, 
                    bool    bWriteAccess);
    bool    Open (bool  bReadAccess, 
                  bool  bWriteAccess);
    bool    Close ();
    bool    Delete ();

    bool    Read (DWORD dwFileOffset,
                  DWORD dwSizeofBuffer, 
                  BYTE  &byBuffer,
                  DWORD &dwNumBytesRead);
    bool    Write (DWORD        dwFileOffset,
                   DWORD        dwSizeofBuffer, 
                   const BYTE   &byBuffer,
                   DWORD        &dwNumBytesWritten);

    bool    SetFilePointer (DWORD dwFileOffset);
    bool    SetEof (DWORD dwFileOffset);

    bool    SetFileSize (DWORD dwFileSize);
    DWORD   GetFileSize () const;
    DWORD   GetFileOffset () const;

    FILETIME    GetCreationTime () const;
    FILETIME    GetLastAccessTime () const;
    FILETIME    GetLastWriteTime () const;

    void    SetFilePath (const std::wstring &filePath)
    {m_filePath = filePath;}

    std::wstring    GetFilePath () const
    {return (m_filePath);}

    std::wstring    GetFileName () const;

    bool    IsOpen () const
    {return (m_hFile != INVALID_HANDLE_VALUE);}

    HANDLE  GetFileHandle () const
    {return (m_hFile);}

    DWORD   GetLastError () const
    {return (m_dwLastError);}

    static  bool    IsValidFileName (const std::wstring &fileName);
    static  bool    IsValidPath (const std::wstring &path);

    static  std::wstring    AddBackslashToPath (const std::wstring  &path, 
                                                bool                bToEnd = true);
    static  std::wstring    RemoveBackslashFromPath (const std::wstring &path,
                                                     bool               bFromEnd = true);

    static  bool    IsWildcard (const std::wstring &filePath);
    static  bool    IsDirectory (const std::wstring &filepath);
    static  bool    IsFile (const std::wstring &filePath);
    static  bool    IsFileReadOnly (const std::wstring &filePath);

    static  bool    MakeFileWriteable (const std::wstring &filePath);
    static  bool    MakeFileReadOnly (const std::wstring &filePath);

    static  bool    QueryFileAttributes (const std::wstring &filePath,
                                         UINT               &uiFileAttributes);
    static  bool    SetFileAttributes (const std::wstring   &filePath,
                                       UINT                 uiFileAttributes);

    static  StringList  EnumFiles (const std::wstring   &path,
                                   bool                 bRecurse);

private:
    std::wstring    m_filePath;
    HANDLE          m_hFile;
    bool            m_bLogError;
    mutable DWORD   m_dwLastError;
}; // Endclass.


// Routines.

extern  void    LogError (UINT                  uiLineNumber, 
                          const std::wstring    &fileName, 
                          UINT                  uiLogId, 
                          const std::wstring    &errorString);
extern  void    LogInformation (UINT                uiLineNumber, 
                                const std::wstring  &fileName, 
                                UINT                uiLogId, 
                                const std::wstring  &infoString);

extern  void    OutputDebug (const std::wstring &string);

extern  std::wstring    GetComputerName ();
extern  std::wstring    GetTimeStamp ();

extern  std::string     WideStringToNarrowString (const std::wstring &string);
extern  std::wstring    NarrowStringToWideString (const std::string &string);

extern  std::wstring    GetDayOfWeekDescription (UINT uiDayOfWeek);
extern  std::wstring    GetMonthDescription (UINT uiMonth);
extern  UINT    GetMonth (const std::wstring &month);

extern  bool    IsDecimal (std::wstring::value_type digit, 
                           int                      &nValue);
extern  bool    IsHexadecimal (std::wstring::value_type  digit, 
                               int                      &nValue);
extern  bool    StringToDecimal (const std::wstring &string,
                                 int                &nValue);
extern  bool    StringToHexadecimal (const std::wstring &string,
                                     DataList           &data);
extern  bool    StringToHexadecimal (const std::wstring &string,
                                     int                &nValue);
extern  bool    StringToInteger (const std::wstring &string,
                                 int                &nValue);

extern  SYSTEMTIME  GetLocalDateTimeStamp ();

extern  bool    IsDate (const SYSTEMTIME &systemTime);
extern  bool    IsDate (const FILETIME &fileTime);
extern  bool    IsDateForward (const FILETIME   &currentFileTime,
                               const FILETIME   &previousFileTime,
                               bool             bCheckHoursMinutes);
extern  bool    IsDateBackward (const FILETIME  &currentFileTime,
                                const FILETIME  &previousFileTime,
                                bool            bCheckHoursMinutes);
extern  bool    IsDateEqual (const FILETIME &currentFileTime,
                             const FILETIME &previousFileTime,
                             bool           bCheckHoursMinutes);
extern  SYSTEMTIME  FileTimeToSystemTime (const FILETIME &fileTime);
extern  SYSTEMTIME  FileTimeToLocalTime (const FILETIME &fileTime);
extern  FILETIME    FileTimeToLocalFileTime (const FILETIME &fileTime);
extern  FILETIME    SystemTimeToFileTime (const SYSTEMTIME &systemTime);
extern  FILETIME    LocalTimeToFileTime (const SYSTEMTIME &localTime);
extern  FILETIME    TimetToFileTime (time_t t);
extern  FILETIME    DateTimeStringToFileTime (const std::wstring &dateTime);

extern  UINT    GetDayOfWeek (UINT  uiDay,
                              UINT  uiMonth, 
                              UINT  uiYear);

extern  bool    IsWhiteSpace (std::wstring::value_type character);
extern  void    RemoveWhiteSpace (std::string   &line, 
                                  bool          bStartOfLine);
extern  void    RemoveWhiteSpace (std::wstring  &line, 
                                  bool          bStartOfLine);
extern  void    RemoveNumbers (std::string &string);
extern  void    RemoveNumbers (std::wstring &string);

extern  UINT    QueryRegistryValue (HKEY                hKey,
                                    const std::wstring  &valueName,
                                    UINT                &value);
extern  UINT    QueryRegistryValue (HKEY                hKey,
                                    const std::wstring  &valueName,
                                    std::wstring        &value);

extern  std::wstring    BuildByteBuffer (UINT           uiBufferLength,
                                         const LPBYTE   lpbyBuffer);
extern  std::wstring    ByteBufferToCString (const DataList &byBuffer);
extern  DataList        CStringToByteBuffer (const std::wstring &string);

extern  std::wstring    BuildDateTime (const SYSTEMTIME &systemTime,
                                       bool             bSecondsRqd = true,
                                       bool             bMillisecondsRqd = true,
                                       bool             bMonthDescriptionRqd = true);
extern  std::wstring    BuildDateTime (UINT uiDay,
                                       UINT uiMonth,
                                       UINT uiYear,
                                       UINT uiHour, 
                                       UINT uiMinute, 
                                       UINT uiSecond, 
                                       UINT uiMilliseconds = 0,
                                       bool bSecondsRqd = true,
                                       bool bMillisecondsRqd = true,
                                       bool bMonthDescriptionRqd = true);
extern  std::wstring    BuildDate (const SYSTEMTIME &systemTime,
                                   bool             bMonthDescriptionRqd = true);
extern  std::wstring    BuildDate (UINT uiDay,
                                   UINT uiMonth,
                                   UINT uiYear,
                                   bool bMonthDescriptionRqd = true);
extern  std::wstring    BuildTime (const SYSTEMTIME &systemTime,
                                   bool             bSecondsRqd = true,
                                   bool             bMillisecondsRqd = true);
extern  std::wstring    BuildTime (UINT uiHour, 
                                   UINT uiMinute, 
                                   UINT uiSecond, 
                                   UINT uiMilliseconds = 0,
                                   bool bSecondsRqd = true,
                                   bool bMillisecondsRqd = true);
extern  std::wstring    BuildByteBuffer (const DataList &byBuffer);
extern  std::wstring    BuildStringData (const std::wstring &stringData,
                                         bool               bAddQuotes = true);

extern  std::wstring    SplitPath (const std::wstring &path,
                                   bool               bDrive = false,
                                   bool               bDirectory = false,
                                   bool               bFileName = true,
                                   bool               bFileNameExt = false);
extern  std::wstring    SplitPathToDrive (const std::wstring &path);
extern  std::wstring    SplitPathToDirectory (const std::wstring &path);
extern  std::wstring    SplitPathToFileName (const std::wstring &path);
extern  std::wstring    SplitPathToFileNameExt (const std::wstring &path);

extern  std::wstring    ToUpper (const std::wstring &string);
extern  std::wstring    ToLower (const std::wstring &string);

extern  std::wstring    GetCommandLine (int     argc, 
                                        TCHAR   *argv []);

} // Endnamespace.

/******************************* End of File *******************************/
