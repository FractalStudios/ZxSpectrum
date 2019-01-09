// Windows includes.
#include    <Windows.h>

// "Home-made" includes.
#include    <Trace.h>
#include    "SecurityAttributes.h"
#include    "SharedMemory.h"

namespace Folio
{

namespace Core
{

namespace Util
{

/**
 * The default class constructor.
 */
SharedMemory::SharedMemory ()
:   m_baseAddress(0),
    m_size(0),
    m_data(0),
    m_fileMapHandle(FOLIO_INVALID_HANDLE),
    m_fileHandle(FOLIO_INVALID_FILE_HANDLE)
{
} // Endproc.


/**
 * The class destructor. If required it will close the shared memory and
 * remove any OS reference to the shared memory from this object.
 */
SharedMemory::~SharedMemory ()
{
    // Close any open handle to shared memory.

    Close ();
} // Endproc.


/**
 * Method to create the shared memory.
 *
 * If shared memory of the same name already exists then it will be opened.
 * In this case, the <i>size</i> and <i>fileName</i> parameters are
 * ignored and <b>ERR_ALREADY_EXISTS</b> will be returned.
 *
 * @param [in] sharedMemoryName
 * The name of the shared memory. The name is case sensitive.
 *
 * @param [in] size
 * The size (in bytes) of the shared memory.
 *
 * @param [in] fileName
 * The file name of the shared memory. The name is case sensitive. This
 * parameter may be zero or empty, if the Windows' system paging file should
 * be used. Defaults to zero.
 *
 * @param [in] baseAddress
 * The base address of the shared memory. This parameter may be zero, if the
 * base address can be chosen by Windows. Defaults to zero.
 *
 * @param [in] useRawName
 * Indicates if the raw <i>sharedMemoryName</i> parameter should be used as the
 * shared memory name. <b>true</b> if the raw <i>sharedMemoryName</i> parameter 
 * should be used as the shared memory name, <b>false</b> otherwise.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the shared memory was successfully created.
 * <li><b>ERR_ALREADY_EXISTS</b> if the shared memory was successfully
 *     opened.
 * <li><b>ERR_INVALID_SEQUENCE</b> if shared memory has been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus SharedMemory::Create (const FolioString&    sharedMemoryName,
                                  UInt32                size,
                                  const FolioString*    fileName,
                                  void*                 baseAddress,
                                  bool                  useRawName)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a handle to a shared memory file map already?

    if (m_fileMapHandle == FOLIO_INVALID_HANDLE)
    {
        // Initialise the shared memory file.

        status = InitializeFile (fileName);

        if (status == ERR_SUCCESS)
        {
            SecurityAttributes  securityAttributes;

            // Set the shared name.

            if (useRawName)
            {
               m_sharedMemoryName.SetRawName (sharedMemoryName);
            } // Endif.

            else
            {
               m_sharedMemoryName = sharedMemoryName;
            } // Endelse.

            // Map enough for the shared memory management also.

            m_size = size + sizeof (MemoryHeader) + sizeof (MemoryTail);

            // Create the shared memory file map.

            m_fileMapHandle =
                ::CreateFileMapping (m_fileHandle,
                                     securityAttributes.GetSecurityAttributes (),
                                     PAGE_READWRITE,
                                     0,    // High-order 32 bits.
                                     m_size,
                                     m_sharedMemoryName.GetSharedName ());

            if (m_fileMapHandle == FOLIO_INVALID_HANDLE)
            {
                // Build and log an error.

                status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

                FOLIO_LOG_CALL_ERROR_4 (TXT("CreateFileMapping"),
                                        status,
                                        m_fileHandle,
                                        m_size,
                                        m_sharedMemoryName,
                                        m_fileName);
            } // Endif.

            // Did the shared memory file map already exist?

            else
            if (::GetLastError () == ERROR_ALREADY_EXISTS)
            {
                status = ERR_ALREADY_EXISTS;
            } // Endif.

            // Should we map the file into process space?

            if ((status == ERR_SUCCESS) ||
                (status == ERR_ALREADY_EXISTS))
            {
                // Map the shared memory file map.

                // Use a temp status as we don'T want to change the
                // ERR_ALREADY_EXISTS status on success. If there
                // is an error we must return the result code.

                FolioStatus tempStatus = MapFile (baseAddress,
                                                  status == ERR_SUCCESS);

                if (tempStatus != ERR_SUCCESS)
                {
                    status = tempStatus;
                } // Endif.

            } // Endelse.

        } // Endif.

    } // Endif.

    else
    {
        // Already have a shared memory file map handle for this object.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will open <b>existing</b> named shared memory.
 *
 * This method will succeed if the named shared memory has previously
 * been created using <b>Create</b>.
 *
 * @param [in] sharedMemoryName
 * The name of the shared memory. The name is case sensitive.
 *
 * @param [in] baseAddress
 * The base address of the shared memory. This parameter may be zero, if the
 * base address can be chosen by Windows. Defaults to zero.
 *
 * @param [in] useRawName
 * Indicates if the raw <i>sharedMemoryName</i> parameter should be used as the
 * shared memory name. <b>true</b> if the raw <i>sharedMemoryName</i> parameter 
 * should be used as the shared memory name, <b>false</b> otherwise.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_NOT_FOUND</b> if the named shared memory was not found.
 * <li><b>ERR_INVALID_SEQUENCE</b> if shared memory has been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus SharedMemory::Open (const FolioString&  sharedMemoryName,
                                void*               baseAddress,
                                bool                useRawName)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a handle to a shared memory file map already?

    if (m_fileMapHandle == FOLIO_INVALID_HANDLE)
    {
        // Set the shared name.

        if (useRawName)
        {
           m_sharedMemoryName.SetRawName (sharedMemoryName);
        } // Endif.

        else
        {
           m_sharedMemoryName = sharedMemoryName;
        } // Endelse.

        // Open the shared memory file map.

        m_fileMapHandle = ::OpenFileMapping (FILE_MAP_ALL_ACCESS,
                                             FALSE, // Don't inherit.
                                             m_sharedMemoryName.GetSharedName ());

        if (m_fileMapHandle == FOLIO_INVALID_HANDLE)
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            switch (status)
            {
            case ERROR_FILE_NOT_FOUND:
                FOLIO_LOG_CALL_WARNING_1 (TXT("OpenFileMapping"),
                                          status,
                                          m_sharedMemoryName);

                status = ERR_NOT_FOUND;
                break;

            default:
                FOLIO_LOG_CALL_ERROR_1 (TXT("OpenFileMapping"),
                                        status,
                                        m_sharedMemoryName);
                break;
            } // Endswitch.

        } // Endif.

        if (status == ERR_SUCCESS)
        {
            // Map the shared memory file map.

            status = MapFile (baseAddress, false);
        } // Endelse.

    } // Endif.

    else
    {
        // Already have a shared memory file map handle for this object.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method to close the shared memory, that had previously been
 * created or opened. If this is the final user of the shared memory then
 * the shared memory is released.
 *
 * If the <b>Create</b> or <b>Open</b> methods have not been used previously,
 * or the shared memory has already been closed, then no action will be taken
 * and <b>ERR_SUCCESS</b> will be returned.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus SharedMemory::Close ()
{
    FolioStatus status = ERR_SUCCESS;

    // Have we mapped a shared memory file map?

    if (m_data)
    {
        status = UnmapFile ();
    } // Endif.

    if (status == ERR_SUCCESS)
    {
        // Have we obtained a handle to shared memory file map?

        if (m_fileMapHandle != FOLIO_INVALID_HANDLE)
        {
            // Close the shared memory file map handle.

            if (::CloseHandle (m_fileMapHandle))
            {
                m_fileMapHandle = FOLIO_INVALID_HANDLE; // Gone.
            } // Endif.

            else
            {
                // Build and log an error.

                status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

                FOLIO_LOG_CALL_ERROR_6 (TXT("CloseHandle"),
                                        status,
                                        m_fileHandle,
                                        m_baseAddress,
                                        m_size,
                                        m_sharedMemoryName,
                                        m_fileName,
                                        m_fileMapHandle);
            } // Endelse.

        } // Endif.

        // Have we obtained a handle to the shared memory file?

        if (m_fileHandle != FOLIO_INVALID_FILE_HANDLE)
        {
            // Terminate the shared memory file.

            status = TerminateFile ();
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Method to get the base address of the shared memory.
 *
 * @return
 * The possible return values are:<ul>
 * <li>The shared memory data.
 * <li>Zero if the shared memory base address is invalid.
 * </ul>
 */
void*   SharedMemory::GetBaseAddress () const
{
    return ((m_data == 0) ? 0: (m_data + sizeof (MemoryHeader)));
} // Endproc.


/**
 * Method to get the size of the shared memory.
 *
 * @return
 * The shared memory size (in bytes).
 */
UInt32  SharedMemory::GetSize () const
{
    return ((m_size == 0) ? 0 : (m_size - sizeof (MemoryHeader) - sizeof (MemoryTail)));
} // Endproc.


/**
 * Method that will initialise the shared memory file.
 *
 * @param [in] fileName
 * The file name of the shared memory. The name is case sensitive. This
 * parameter may be zero or empty, if the Windows' system paging file should be
 * used.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus SharedMemory::InitializeFile (const FolioString* fileName)
{
    FolioStatus status = ERR_SUCCESS;

    // Are we using the system paging file for the shared memory file?

    if (fileName && !fileName->empty ())
    {
        // No. Create a file for the shared memory file.

        SecurityAttributes  securityAttributes;

        m_fileName = *fileName;

        m_fileHandle = ::CreateFile (m_fileName,
                                     GENERIC_READ | GENERIC_WRITE,
                                     FILE_SHARE_READ | FILE_SHARE_WRITE,
                                     securityAttributes.GetSecurityAttributes (),
                                     OPEN_ALWAYS,
                                     FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS,
                                     0); // No template.

        if (m_fileHandle == FOLIO_INVALID_FILE_HANDLE)
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_1 (TXT("CreateFile"),
                                    status,
                                    m_fileName);
        } // Endif.

    } // Endif.

    else
    {
        // No.

        m_fileHandle = FOLIO_INVALID_FILE_HANDLE; // System paging file.
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will terminate the shared memory file.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus SharedMemory::TerminateFile ()
{
    FolioStatus status = ERR_SUCCESS;

    // Close the file handle.

    if (::CloseHandle (m_fileHandle))
    {
        m_fileHandle = FOLIO_INVALID_FILE_HANDLE; // Gone.
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

    return (status);
} // Endproc.


/**
 * Method that will map the shared memory file map.
 *
 * @param [in] baseAddress
 * The base address of the shared memory. This parameter may be zero, if the
 * base address can be chosen by Windows.
 *
 * @param [in] initialise
 * Indicates if the shared memory file map should be initialised.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus SharedMemory::MapFile (void*    baseAddress,
                                   bool     initialise)
{
    FolioStatus status = ERR_SUCCESS;

    // Map the shared memory file map.

    m_baseAddress = baseAddress;

    m_data = reinterpret_cast<LPBYTE> (::MapViewOfFileEx (m_fileMapHandle,
                                                          FILE_MAP_ALL_ACCESS,
                                                          0, // Map start.
                                                          0, // ditto.
                                                          0, // Map entire file.
                                                          m_baseAddress));

    if (m_data == 0)
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_6 (TXT("MapViewOfFileEx"),
                                status,
                                m_fileHandle,
                                m_baseAddress,
                                m_size,
                                m_sharedMemoryName,
                                m_fileName,
                                m_fileMapHandle);
    } // Endif.

    else if (initialise)
    {
        // Laydown the shared memory management.

        LaydownMemoryManagement ();
    } // Endelseif.

    else
    {
        // Verify the shared memory management.

        status = VerifyMemoryManagement ();
    } // Endelse.

    if (status != ERR_SUCCESS)
    {
        Close ();   // Tidy up.
    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that will unmap the shared memory file map.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus SharedMemory::UnmapFile ()
{
    FolioStatus status = ERR_SUCCESS;

    // Unmap the shared memory file map.

    if (::UnmapViewOfFile (m_data))
    {
        m_data          = 0;
        m_size          = 0;
        m_baseAddress   = 0;
    } // Endif.

    else
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_7 (TXT("UnmapViewOfFile"),
                                status,
                                m_fileHandle,
                                m_baseAddress,
                                m_size,
                                m_sharedMemoryName,
                                m_fileName,
                                m_fileMapHandle,
                                m_data);
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will lay down the shared memory management data; the header
 * and tail.
 */
void    SharedMemory::LaydownMemoryManagement () const
{
    // Point to the shared memory header.

    MemoryHeader*   header =
        reinterpret_cast<MemoryHeader*> (m_data);

    // Point to the shared memory tail.

    MemoryTail*     tail =
        reinterpret_cast<MemoryTail*> (m_data + m_size - sizeof (MemoryTail));

    // Lay down the shared memory managment data.

    // Under Windows, it's not possible to determine the allocated size
    // of paged file mapped memory when opened. Store the shared memory
    // size in the header.

    header->m_size        = m_size;
    header->m_sentinel    = MEMORY_SENTINEL;
    tail->m_sentinel      = MEMORY_SENTINEL;
} // Endproc.


/**
 * Method that will verify the shared memory management data; the header
 * and tail.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus SharedMemory::VerifyMemoryManagement ()
{
    FolioStatus status = ERR_SUCCESS;

    // Point to the shared memory header.

    MemoryHeader*   header =
        reinterpret_cast<MemoryHeader*> (m_data);

    // Verify the header sentinel.

    if (header->m_sentinel == MEMORY_SENTINEL)
    {
        // Pick up the shared memory size.

        m_size = header->m_size;

        // Point to the shared memory tail.

        MemoryTail* tail =
            reinterpret_cast<MemoryTail*> (m_data + m_size - sizeof (MemoryTail));

        // Verify the tail sentinel.

        if (tail->m_sentinel != MEMORY_SENTINEL)
        {
            FOLIO_LOG_ERROR_4 (TXT("Buffer over-run detected. No end sentinel found in memory block."),
                               m_fileHandle,
                               m_sharedMemoryName,
                               m_fileMapHandle,
                               m_data);

            status = ERR_UTIL_BUFFER_OVERRUN;
        } // Endelse.

    } // Endif.

    else
    {
        FOLIO_LOG_ERROR_4 (TXT("Buffer under-run detected. No start sentinel found in memory block."),
                           m_fileHandle,
                           m_sharedMemoryName,
                           m_fileMapHandle,
                           m_data);

        status = ERR_UTIL_BUFFER_UNDERRUN;
    } // Endelse.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/

