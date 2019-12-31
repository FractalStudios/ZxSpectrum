// "Home-made" includes.
#include    <Trace.h>
#include    "File.h"
#include    "SecurityAttributes.h"

namespace Folio
{

namespace Core
{

namespace Util
{

/**
 * The default class constructor.
 */
File::File ()
:   m_fileHandle(FOLIO_INVALID_FILE_HANDLE)
{
} // Endproc.


/**
 * The class destructor. If required it will remove any OS reference to the
 * file from this object.
 */
File::~File ()
{
    // Close any file handle.

    Close ();
} // Endproc.


/**
 * Method that will create a file.
 *
 * If a file of the same name already exists then it will be opened. In
 * this case <b>ERR_ALREADY_EXISTS</b> will be returned.
 *
 * @param [in] fileName
 * The name of the file. The name is case sensitive.
 *
 * @param [in] desiredAccess
 * The required access to the file.
 *
 * @param [in] shareMode
 * The sharing mode of the file.
 *
 * @param [in] creationDisposition
 * The action to take if the file exists or does not exist.
 *
 * @param [in] attributes
 * The attributes and flags of the file.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the file was successfully created.
 * <li><b>ERR_ALREADY_EXISTS</b> if the file was successfully opened.
 * <li><b>ERR_UTIL_FILE_NOT_FOUND</b> if the file was not found.
 * <li><b>ERR_UTIL_PATH_NOT_FOUND</b> if the file path was not found.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a file has been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus File::Create (const FolioString&    fileName,
                          UInt32                desiredAccess,
                          UInt32                shareMode,
                          UInt32                creationDisposition,
                          UInt32                attributes)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a handle to a file already?

    if (m_fileHandle == FOLIO_INVALID_FILE_HANDLE)
    {
        SecurityAttributes  securityAttributes;

        m_fileName = fileName;

        // Create the file.

        m_fileHandle = ::CreateFile (m_fileName,
                                     desiredAccess,
                                     shareMode,
                                     securityAttributes.GetSecurityAttributes (),
                                     creationDisposition,
                                     attributes,
                                     0);  // No template.

        if (m_fileHandle == FOLIO_INVALID_FILE_HANDLE)
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            switch (status)
            {
            case ERROR_FILE_NOT_FOUND:
                FOLIO_LOG_CALL_WARNING_5 (TXT("CreateFile"),
                                          status,
                                          m_fileName,
                                          desiredAccess,
                                          shareMode,
                                          creationDisposition,
                                          attributes);

                status = ERR_UTIL_FILE_NOT_FOUND;
                break;

            case ERROR_PATH_NOT_FOUND:
                FOLIO_LOG_CALL_WARNING_5 (TXT("CreateFile"),
                                          status,
                                          m_fileName,
                                          desiredAccess,
                                          shareMode,
                                          creationDisposition,
                                          attributes);

                status = ERR_UTIL_PATH_NOT_FOUND;
                break;

            default:
                FOLIO_LOG_CALL_ERROR_5 (TXT("CreateFile"),
                                        status,
                                        m_fileName,
                                        desiredAccess,
                                        shareMode,
                                        creationDisposition,
                                        attributes);
                break;
            } // Endswitch.

        } // Endif.

        // Did the file already exist?

        else if (::GetLastError () == ERROR_ALREADY_EXISTS)
        {
            status = ERR_ALREADY_EXISTS;
        } // Endelseif.

    } // Endif.

    else
    {
        // Already have a file handle for this object.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will close the file.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus File::Close ()
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a file handle?

    if (m_fileHandle != FOLIO_INVALID_FILE_HANDLE)
    {
        // Close the file handle.

        if (::CloseHandle (m_fileHandle))
        {
            m_fileHandle = FOLIO_INVALID_FILE_HANDLE;    // Gone.
        } // Endif.

        else
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_2 (TXT("CloseHandle"),
                                    status,
                                    m_fileName,
                                    m_fileHandle);
        } // Endelse.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that will read from the file.
 *
 * @param [out] buffer
 * On return, will hold the read buffer, if successful. If this method fails 
 * then this parameter is undefined.
 *
 * @param [in, out] numOfBytes
 * On entry holds the size (in bytes) of the <i>buffer</i> parameter. On
 * return, will hold the number of bytes read, if successful.
 *
 * @param [in] overlapped
 * A pointer to an <b>OVERLAPPED</b> structure. This parameter may be zero if
 * overlapped I/O is not required. Defaults to zero.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a file has not been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus File::Read (void*           buffer,
                        UInt32&         numOfBytes,
                        LPOVERLAPPED    overlapped) const
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a file handle?

    if (m_fileHandle == FOLIO_INVALID_FILE_HANDLE)
    {
        // No file handle.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // Read from the file.

        if (!::ReadFile (m_fileHandle,
                         buffer,
                         numOfBytes,
                         reinterpret_cast<LPDWORD> (&(numOfBytes)),
                         overlapped))
        {
            // Are we using overlapped I/O and is I/O pending?

            if (overlapped && 
                (::GetLastError () == ERROR_IO_PENDING))
            {
                // Yes.

                status = ERR_PENDING;
            } // Endif.

            else
            {
                // Build and log an error.
    
                status = FOLIO_MAKE_OS_ERROR(::GetLastError ());
    
                FOLIO_LOG_CALL_ERROR_5 (TXT("ReadFile"),
                                        status,
                                        m_fileName,
                                        m_fileHandle,
                                        buffer,
                                        numOfBytes,
                                        overlapped);
            } // Endelse.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that will write to the file.
 *
 * @param [in] buffer
 * The buffer to write.
 *
 * @param [in, out] numOfBytes
 * On entry holds the size (in bytes) of the <i>buffer</i> parameter. On
 * return, will hold the number of bytes written, if successful.
 *
 * @param [in] overlapped
 * A pointer to an <b>OVERLAPPED</b> structure. This parameter may be zero if
 * overlapped I/O is not required. Defaults to zero.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a file has not been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus File::Write (const void*    buffer,
                         UInt32&        numOfBytes,
                         LPOVERLAPPED   overlapped) const
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a file handle?

    if (m_fileHandle == FOLIO_INVALID_FILE_HANDLE)
    {
        // No file handle.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // Write to the file.

        if (!::WriteFile (m_fileHandle,
                          buffer,
                          numOfBytes,
                          reinterpret_cast<LPDWORD> (&(numOfBytes)),
                          overlapped))
        {
            // Are we using overlapped I/O and is I/O pending?

            if (overlapped && 
                (::GetLastError () == ERROR_IO_PENDING))
            {
                // Yes.

                status = ERR_PENDING;
            } // Endif.

            else
            {
                // Build and log an error.

                status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

                FOLIO_LOG_CALL_ERROR_5 (TXT("WriteFile"),
                                        status,
                                        m_fileName,
                                        m_fileHandle,
                                        buffer,
                                        numOfBytes,
                                        overlapped);
            } // Endelse.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that will get the result of an overlapped I/O file operation.
 *
 * @param [in] overlapped
 * An <b>OVERLAPPED</b> structure that was specified when the I/O file 
 * operation was started.
 *
 * @param [in] waitForCompletion
 * Indicates if this method should wait for the overlapped I/O file 
 * operation to complete. 
 *
 * @param [out] numOfBytes
 * Will hold the number of bytes transferred by the I/O file operation, 
 * if successful.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a file has not been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus File::GetOverlappedResult (OVERLAPPED&  overlapped,
                                       bool         waitForCompletion,
                                       UInt32&      numOfBytes) const
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a file handle?

    if (m_fileHandle == FOLIO_INVALID_FILE_HANDLE)
    {
        // No file handle.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // Get the overlapped result.

        if (!::GetOverlappedResult (m_fileHandle,
                                    &(overlapped),
                                    reinterpret_cast<LPDWORD> (&(numOfBytes)),
                                    waitForCompletion ? TRUE : FALSE))  // Wait for the I/O operation to complete?
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_4 (TXT("GetOverlappedResult"),
                                    status,
                                    m_fileName,
                                    m_fileHandle,
                                    waitForCompletion,
                                    numOfBytes);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that will get the size of the file.
 *
 * @param [out] size
 * On return, will hold the size of the file, if successful. If this method 
 * fails then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a file has not been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus File::QuerySize (UInt32& size) const
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a file handle?

    if (m_fileHandle == FOLIO_INVALID_FILE_HANDLE)
    {
        // No file handle.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // Get the file size.

        size = ::GetFileSize (m_fileHandle,
                              0); // Don't need high-order size.

        if (size == INVALID_FILE_SIZE)
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_2 (TXT("GetFileSize"),
                                    status,
                                    m_fileName,
                                    m_fileHandle);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that will set the file pointer from the start of the file.
 *
 * @param [in] distanceFromStart
 * The distance from the start of the file.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a file has not been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus File::SetFilePointer (UInt32 distanceFromStart) const
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a file handle?

    if (m_fileHandle == FOLIO_INVALID_FILE_HANDLE)
    {
        // No file handle.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // Set the file pointer to the beginning of the file.

        if ((::SetFilePointer (m_fileHandle,
                               distanceFromStart,
                               0, 
                               FILE_BEGIN) == INVALID_SET_FILE_POINTER) &&
            (::GetLastError () != ERROR_SUCCESS))
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_3 (TXT("SetFilePointer"),
                                    status,
                                    m_fileName,
                                    m_fileHandle,
                                    distanceFromStart);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that will set the end of the file.
 *
 * @param [in] distanceFromStart
 * The distance from the start of the file.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a file has not been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus File::SetEndOfFile (UInt32 distanceFromStart) const
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a file handle?

    if (m_fileHandle == FOLIO_INVALID_FILE_HANDLE)
    {
        // No file handle.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // Set the file pointer (from the beginning of the file).

        status = SetFilePointer (distanceFromStart);

        if (status == ERR_SUCCESS)
        {
            // Set the end of file.

            if (!::SetEndOfFile (m_fileHandle))
            {
                // Build and log an error.

                status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

                FOLIO_LOG_CALL_ERROR_2 (TXT("SetEndOfFile"),
                                        status,
                                        m_fileName,
                                        m_fileHandle);
            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that will clear the file.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a file has not been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus File::Clear () const
{
    return (SetEndOfFile (0));
} // Endproc.


/**
 * Method that will return the file name.
 *
 * @return
 * The file name.
 */
FolioString File::GetFileName () const
{
    return (m_fileName);
} // Endproc.


/**
 * Method that will return the file handle.
 *
 * @return
 * The possible return values are:<ul>
 * <li>The file handle.
 * <li><b>FOLIO_INVALID_HANDLE</b> if the file handle is invalid.
 * </ul>
 */
FolioHandle File::GetFileHandle () const
{
    return ((m_fileHandle == FOLIO_INVALID_FILE_HANDLE) ? FOLIO_INVALID_HANDLE : m_fileHandle);
} // Endproc.


/**
 * Method that will copy a file.
 *
 * @param [in] existingFileName
 * The existing file name.
 *
 * @param [in] newFileName
 * The new file name.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus File::Copy (const FolioString&  existingFileName,
                        const FolioString&  newFileName)
{
    FolioStatus status = ERR_SUCCESS;

    if (!::CopyFile (existingFileName,
                     newFileName,
                     FALSE))    // Replace existing file.
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_2 (TXT("CopyFile"),
                                status,
                                existingFileName,
                                newFileName);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that will move a file.
 *
 * @param [in] existingFileName
 * The existing file name.
 *
 * @param [in] newFileName
 * The new file name.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus File::Move (const FolioString&  existingFileName,
                        const FolioString&  newFileName)
{
    FolioStatus status = ERR_SUCCESS;

    if (!::MoveFileEx (existingFileName,
                       newFileName,
                       MOVEFILE_REPLACE_EXISTING))
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_2 (TXT("MoveFileEx"),
                                status,
                                existingFileName,
                                newFileName);
    } // Endif.

    return (status);
} // Endproc.


/**
 * <b>File</b> output stream operator.
 *
 * @param [in, out] outputStream
 * The output stream to add the <b>File</b> to.
 *
 * @param [in] rhs
 * The <b>File</b> to add to the output stream.
 *
 * @return
 * The output stream with added <b>File</b>.
 */
FolioOStream&   operator<< (Folio::FolioOStream&    outputStream, 
                            const File&             rhs)
{
    FOLIO_STREAM_FIRST_MEMBER(outputStream, rhs, m_fileName);
    FOLIO_STREAM_LAST_MEMBER(outputStream, rhs, m_fileHandle);

    return (outputStream);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/

