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

/// The file class.
/**
 * This class provides for access to a disk based file.
 *
 * This class does not support copy construction or assignment.
 */
class File
{
public:
    File ();
    ~File ();

    FolioStatus Create (const FolioString&  fileName,
                        UInt32              desiredAccess,
                        UInt32              shareMode,
                        UInt32              creationDisposition,
                        UInt32              attributes);
    FolioStatus Close ();

    FolioStatus Read (void*         buffer,
                      UInt32&       numOfBytes,
                      LPOVERLAPPED  overlapped = 0) const;
    FolioStatus Write (const void*  buffer,
                       UInt32&      numOfBytes,
                       LPOVERLAPPED overlapped = 0) const;
    FolioStatus GetOverlappedResult (OVERLAPPED&    overlapped,
                                     bool           waitForCompletion,
                                     UInt32&        numOfBytes) const;

    FolioStatus QuerySize (UInt32& size) const;
    FolioStatus SetFilePointer (UInt32 distanceFromStart) const;
    FolioStatus SetEndOfFile (UInt32 distanceFromStart) const;
    FolioStatus Clear () const;

    FolioString GetFileName () const;
    FolioHandle GetFileHandle () const;

    static  FolioStatus Copy (const FolioString&    existingFileName,
                              const FolioString&    newFileName);
    static  FolioStatus Move (const FolioString&    existingFileName,
                              const FolioString&    newFileName);

private:
    FolioString m_fileName;     ///< The file name.
    FolioHandle m_fileHandle;   ///< The file handle.

    /// Private copy constructor to prevent copying.
    File (const File& rhs);

    /// Private assignment operator to prevent copying.
    File& operator= (const File& rhs);

    // The stream operator is our friend.
    friend  FolioOStream&   operator<< (FolioOStream&   outputStream, 
                                        const File&     rhs);
}; // Endclass.

// The stream operator.
FolioOStream&   operator<< (Folio::FolioOStream&    outputStream, 
                            const File&             rhs);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
