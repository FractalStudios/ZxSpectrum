// "Home-made" includes.
#include    <Trace.h>
#include    "Registry.h"
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
Registry::Registry ()
:   m_keyHandle(FOLIO_INVALID_HANDLE)
{
} // Endproc.


/**
 * The class destructor. If required it will remove any OS reference to the
 * registry from this object.
 */
Registry::~Registry ()
{
    // Close any registry key handle.

    CloseKey ();
} // Endproc.


/**
 * Method that will create a registry key.
 *
 * If a registry key of the same name already exists then it will be opened.
 * In this case <b>ERR_ALREADY_EXISTS</b> will be returned.
 *
 * @param [in] openKeyHandle
 * The handle to an open (parent) registry key.
 *
 * @param [in] keyName
 * The name of the registry key. The name is case sensitive.
 *
 * @param [in] desiredAccess
 * The required access to the registry key.
 *
 * @param [in] className
 * The class name of the registry key. The name is case sensitive. This
 * parameter may be empty if there is no class associated with the registry
 * key.
 *
 * @param [in] options
 * The required options of the registry key. Defaults to
 * <b>REG_OPTION_NON_VOLATILE</b>
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the registry was successfully created.
 * <li><b>ERR_ALREADY_EXISTS</b> if the registry key was successfully
 *     opened.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a registry key has been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Registry::CreateKey (FolioHandle        openKeyHandle,
                                 const FolioString& keyName,
                                 UInt32             desiredAccess,
                                 const FolioString* className,
                                 UInt32             options)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a handle to a registry key already?

    if (m_keyHandle == FOLIO_INVALID_HANDLE)
    {
        SecurityAttributes  securityAttributes;

        m_keyName = keyName;

        // Create the registry key.

        UInt32  creationDisposition;

        UInt32  win32Error = ::RegCreateKeyEx (reinterpret_cast<HKEY> (openKeyHandle),
                                               m_keyName,
                                               0,   // Reserved.
                                               (className == 0) ? 0 : const_cast<LPTSTR> (className->c_str ()),
                                               options,
                                               desiredAccess,
                                               securityAttributes.GetSecurityAttributes (),
                                               reinterpret_cast<PHKEY> (&(m_keyHandle)),
                                               reinterpret_cast<LPDWORD> (&(creationDisposition)));

        switch (win32Error)
        {
        case ERR_SUCCESS:
            // Did the registry already exist?

            if (creationDisposition == REG_OPENED_EXISTING_KEY)
            {
                status = ERR_ALREADY_EXISTS;
            } // Endelse.
            break;

        default:
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(win32Error);

            FOLIO_LOG_CALL_ERROR_4 (TXT("RegCreateKeyEx"),
                                    status,
                                    m_keyName,
                                    openKeyHandle,
                                    desiredAccess,
                                    options);
            break;
        } // Endswitch.

    } // Endif.

    else
    {
        // Already have a registry key handle for this object.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will open an <b>existing</b> registry key.
 *
 * @param [in] openKeyHandle
 * The handle to an open (parent) registry key.
 *
 * @param [in] keyName
 * The name of the registry key. The name is case sensitive.
 *
 * @param [in] desiredAccess
 * The required access to the registry key.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the registry was successfully opened.
 * <li><b>ERR_UTIK_KEY_NOT_FOUND</b> if the registry key was not found.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a registry key has been previously
 *     created or opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Registry::OpenKey (FolioHandle          openKeyHandle,
                               const FolioString&   keyName,
                               UInt32               desiredAccess)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a handle to a registry key already?

    if (m_keyHandle == FOLIO_INVALID_HANDLE)
    {
        SecurityAttributes  securityAttributes;

        m_keyName = keyName;

        // Open the registry key.

        UInt32  win32Error = ::RegOpenKeyEx (reinterpret_cast<HKEY> (openKeyHandle),
                                             m_keyName,
                                             0,  // Reserved.
                                             desiredAccess,
                                             reinterpret_cast<PHKEY> (&(m_keyHandle)));

        switch (win32Error)
        {
        case ERR_SUCCESS:
            break;

        default:
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(win32Error);

            switch (status)
            {
            case ERROR_FILE_NOT_FOUND:
                FOLIO_LOG_CALL_WARNING_3 (TXT("RegOpenKeyEx"),
                                          status,
                                          m_keyName,
                                          openKeyHandle,
                                          desiredAccess);
                
                status = ERR_UTIL_KEY_NOT_FOUND;
                break;

            default:
                FOLIO_LOG_CALL_ERROR_3 (TXT("RegOpenKeyEx"),
                                        status,
                                        m_keyName,
                                        openKeyHandle,
                                        desiredAccess);
                break;
            } // Endswitch.
            break;
        } // Endswitch.

    } // Endif.

    else
    {
        // Already have a registry key handle for this object.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will close the registry key.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Registry::CloseKey ()
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a registry key handle?

    if (m_keyHandle != FOLIO_INVALID_HANDLE)
    {
        // Close the registry key handle.

        UInt32  win32Error = ::RegCloseKey (reinterpret_cast<HKEY> (m_keyHandle));

        switch (win32Error)
        {
        case ERR_SUCCESS:
            m_keyHandle = FOLIO_INVALID_HANDLE; // Gone.
            break;

        default:
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(win32Error);

            FOLIO_LOG_CALL_ERROR_2 (TXT("RegCloseKey"),
                                    status,
                                    m_keyName,
                                    m_keyHandle);
            break;
        } // Endswitch.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that will read a value from the registry.
 *
 * @param [in] valueName
 * The name of the value in the registry.
 *
 * @param [out] buffer
 * On return, will hold the read buffer, if successful. If this method fails 
 * then this parameter is undefined.
 *
 * @param [in, out] numOfBytes
 * On entry holds the size (in bytes) of the <i>buffer</i> parameter. On
 * return, will hold the number of bytes read, if successful. If this method 
 * fails then this parameter is undefined.
 *
 * @param [out] dataType
 * On return, will hold the data type of the read value, if successful. This
 * parameter may be zero if the data type of the read value is not required. 
 * If this method fails then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the value was successfully read.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a registry key has not
 *     been previously created or opened opened using this object.
 * <li><b>ERR_BUFFER_TOO_SMALL</b> if the size of the buffer as specified
 *      by <i>numOfBytes</i> is too small.
 * <li><b>ERR_UTIL_VALUE_NOT_FOUND</b> if the registry value was not found.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Registry::ReadValue (const FolioString& valueName,
                                 void*              buffer,
                                 UInt32&            numOfBytes,
                                 UInt32*            dataType) const
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a registry key handle?

    if (m_keyHandle == FOLIO_INVALID_HANDLE)
    {
        // No registry key handle.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // Read value from the registry.

        UInt32  dataSize = numOfBytes;   // Note the required data buffer size.
        UInt32  win32DataType;

        UInt32  win32Error = ::RegQueryValueEx (reinterpret_cast<HKEY> (m_keyHandle),
                                                valueName,
                                                0,   // Reserved.
                                                reinterpret_cast<LPDWORD> (&(win32DataType)),
                                                reinterpret_cast<LPBYTE> (buffer),
                                                reinterpret_cast<LPDWORD> (&(dataSize)));

        switch (win32Error)
        {
        case ERR_SUCCESS:
            // Should we expand the data?

            if ((win32DataType  == REG_EXPAND_SZ) ||
                ((win32DataType == REG_SZ) &&
                 (STRCHR (reinterpret_cast<const Char*> (buffer), TXT('%')) != 0)))
            {
                // Yes. Allocate some memory to hold the expanded string.

                UInt32  numChars = dataSize / sizeof (Char);

                Char*   expandedString = new Char [numChars];

                // Expand the string.

                UInt32 numExpandedChars =
                    ::ExpandEnvironmentStrings (reinterpret_cast<const Char*> (buffer),
                                                expandedString,
                                                numChars);

                if (numExpandedChars == 0)
                {
                    // Build and log an error.
                    
                    status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

                    FOLIO_LOG_CALL_ERROR_2 (TXT("ExpandEnvironmentStrings"),
                                            status,
                                            buffer,
                                            numChars);
                } // Endif.

                // Will the expanded string fully fit into the supplied string?

                else if (numExpandedChars <= (numOfBytes / sizeof (Char)))
                {
                    // Yes. Copy the expanded string into the supplied string.

                    STRCPY_S (reinterpret_cast<Char*> (buffer),
                              numOfBytes / sizeof (Char),
                              expandedString);

                    // Note the string length (the number of expanded
                    // characters).

                    numOfBytes = numExpandedChars * sizeof (Char);
                } // Endelseif.

                else
                {
                    // No. The supplied string is too small.

                    status = ERR_BUFFER_TOO_SMALL;

                    // Note the string length (the number of expanded
                    // characters).

                    numOfBytes = numExpandedChars * sizeof (Char);
                } // Endelse.

                // Free the expanded string.

                delete [] expandedString;
            } // Endif.

            else
            {
                // No.

                numOfBytes = dataSize;
            } // Endif.

            // Does caller want to know the data type?

            if (dataType)
            {
                *dataType = win32DataType;
            } // Endif.
            break;

        case ERROR_MORE_DATA:
            // The supplied buffer is too small.

            status = ERR_BUFFER_TOO_SMALL;

            numOfBytes = dataSize;
            break;

        default:
            status = FOLIO_MAKE_OS_ERROR(win32Error);

            // Build and log an error.

            switch (status)
            {
            case ERROR_FILE_NOT_FOUND:
                FOLIO_LOG_CALL_WARNING_5 (TXT("RegQueryValueEx"),
                                          status,
                                          m_keyName,
                                          m_keyHandle,
                                          valueName,
                                          buffer,
                                          numOfBytes);

                status = ERR_UTIL_VALUE_NOT_FOUND;
                break;

            default:
                FOLIO_LOG_CALL_ERROR_5 (TXT("RegQueryValueEx"),
                                        status,
                                        m_keyName,
                                        m_keyHandle,
                                        valueName,
                                        buffer,
                                        numOfBytes);
                break;
            } // Endswitch.
            break;
        } // Endswitch.

    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will write a value to the registry.
 *
 * @param [in] valueName
 * The name of the value in the registry.
 *
 * @param [in] dataType
 * The data type of the value.
 *
 * @param [in] buffer
 * The value to write.
 *
 * @param [in, out] numOfBytes
 * On entry holds the size (in bytes) of the <i>buffer</i> parameter. On
 * return, will hold the number of bytes written, if successful.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the value was successfully written.
 * <li><b>ERR_INVALID_SEQUENCE</b> if the registry has not
 *     been previously opened using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus Registry::WriteValue (const FolioString&    valueName,
                                  UInt32                dataType,
                                  const void*           buffer,
                                  UInt32&               numOfBytes) const
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a registry key handle?

    if (m_keyHandle == FOLIO_INVALID_HANDLE)
    {
        // No registry key handle.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // Write value to the registry.

        UInt32  win32Error = ::RegSetValueEx (reinterpret_cast<HKEY> (m_keyHandle),
                                              valueName,
                                              0, // Reserved.
                                              dataType,
                                              reinterpret_cast<const LPBYTE> (const_cast<void*> (buffer)),
                                              numOfBytes);

        switch (win32Error)
        {
        case ERR_SUCCESS:
            break;

        default:
            status = FOLIO_MAKE_OS_ERROR(win32Error);

            // Build and log an error.

            FOLIO_LOG_CALL_ERROR_5 (TXT("RegSetValueEx"),
                                    status,
                                    m_keyName,
                                    m_keyHandle,
                                    valueName,
                                    buffer,
                                    numOfBytes);
            break;
        } // Endswitch.

    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will return the registry key handle.
 *
 * @return
 * The possible return values are:<ul>
 * <li>The registry key handle.
 * <li>Zero if the registry key handle is invalid.
 * </ul>
 */
FolioHandle Registry::GetKeyHandle () const
{
    return (m_keyHandle);
} // Endproc.


/**
 * <b>Registry</b> output stream operator.
 *
 * @param [in, out] outputStream
 * The output stream to add the <b>Registry</b> to.
 *
 * @param [in] rhs
 * The <b>Registry</b> to add to the output stream.
 *
 * @return
 * The output stream with added <b>Registry</b>.
 */
FolioOStream&   operator<< (Folio::FolioOStream&    outputStream, 
                            const Registry&         rhs)
{
    FOLIO_STREAM_FIRST_MEMBER(outputStream, rhs, m_keyName);
    FOLIO_STREAM_LAST_MEMBER(outputStream, rhs, m_keyHandle);

    return (outputStream);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
