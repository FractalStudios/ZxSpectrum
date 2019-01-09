// Windows includes.
#include    <Windows.h>

// "Home-made" includes.
#include    <Trace.h>
#include    "ModuleLoader.h"

namespace Folio
{

namespace Core
{

namespace Util
{

/**
 * The default class constructor.
 */
ModuleLoader::ModuleLoader ()
:   m_moduleHandle(FOLIO_INVALID_HANDLE)
{
} // Endproc.


/**
 * The class destructor. If required it will unload the library and remove
 * any OS reference to it from this object.
 */
ModuleLoader::~ModuleLoader ()
{
    // Unload any loaded library.

    UnloadLibrary ();
} // Endproc.


/**
 * Method that will load a library. Mapping the specified executable module
 * into the address space of the calling process.
 *
 * @param [in] moduleName
 * The OS name of the library to load. Cannot be empty. The OS name can be
 * obtained by using the <b>GetOSLibraryName</b> method.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_UTIL_FILE_NOT_FOUND</b> if the library was not found.
 * <li><b>ERR_UTIL_PATH_NOT_FOUND</b> if the library path was not found.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a library has been previously
 *     loaded using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus ModuleLoader::LoadLibrary (const FolioString& moduleName)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we loaded a library already?

    if (m_moduleHandle == FOLIO_INVALID_HANDLE)
    {
        // No. Note the name of the library.

        m_moduleName = moduleName;

        // Load the libray.

        m_moduleHandle = ::LoadLibrary (m_moduleName);

        if (m_moduleHandle == FOLIO_INVALID_HANDLE)
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            switch (status)
            {
            case ERROR_FILE_NOT_FOUND:
                FOLIO_LOG_CALL_WARNING_1 (TXT("LoadLibrary"),
                                          status,
                                          m_moduleName);

                status = ERR_UTIL_FILE_NOT_FOUND;
                break;

            case ERROR_PATH_NOT_FOUND:
                FOLIO_LOG_CALL_WARNING_1 (TXT("LoadLibrary"),
                                          status,
                                          m_moduleName);

                status = ERR_UTIL_PATH_NOT_FOUND;
                break;

            default:
                FOLIO_LOG_CALL_ERROR_1 (TXT("LoadLibrary"),
                                        status,
                                        m_moduleName);
                break;
            } // Endswitch.

        } // Endif.

    } // Endif.

    else
    {
        // Already loaded a library for this object.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will unload a library.
 *
 * This method cannot be called within a loaded library to unload itself.
 * Care must be taken when unloading a library that can potentially have
 * more than one executing thread. Calling <b>UnloadLibrary</b> when
 * multiple threads are running within the library may lead to undefined
 * results.
 *
 * If the <b>LoadLibrary</b> method has not been used previously, or the
 * library has already been unloaded, then no action will be taken and
 * <b>ERR_SUCCESS</b> will be returned.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus ModuleLoader::UnloadLibrary ()
{
    FolioStatus status = ERR_SUCCESS;

    // Have we obtained a handle to a loaded library?

    if (m_moduleHandle != FOLIO_INVALID_HANDLE)
    {
        // Yes. Free the loaded library.

        if (::FreeLibrary (reinterpret_cast<HMODULE> (m_moduleHandle)))
        {
            m_moduleHandle = FOLIO_INVALID_HANDLE;  // Gone.
        } // Endif.

        else
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_WARNING_2 (TXT("FreeLibrary"),
                                      status,
                                      m_moduleName,
                                      m_moduleHandle);
        } // Endelse.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that will get a procedure address from a library.
 *
 * @param [in] procedureName
 * The name of the procedure.
 *
 * @param [out] procedureAddress
 * Will hold the address of the procedure.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a library has not been previously
 *     loaded using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus ModuleLoader::QueryProcedureAddress (const FolioString& procedureName,
                                                 void*&             procedureAddress)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we loaded a library?

    if (m_moduleHandle != FOLIO_INVALID_HANDLE)
    {
        // Yes. Get the procedure address.

        procedureAddress = ::GetProcAddress (reinterpret_cast<HMODULE> (m_moduleHandle),
                                             FolioNarrowString(procedureName).c_str ());

        if (!procedureAddress)
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_3 (TXT("GetProcAddress"),
                                    status,
                                    m_moduleName,
                                    m_moduleHandle,
                                    procedureName);
        } // Endif.

    } // Endif.

    else
    {
        // Not loaded a library for this object.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will return the module handle.
 *
 * @return
 * The possible return values are:<ul>
 * <li>The module handle.
 * <li>Zero if the module handle is invalid.
 * </ul>
 */
FolioHandle ModuleLoader::GetModuleHandle () const
{
    return (m_moduleHandle);
} // Endproc.


/**
 * <b>ModuleLoader</b> output stream operator.
 *
 * @param [in, out] outputStream
 * The output stream to add the <b>ModuleLoader</b> to.
 *
 * @param [in] rhs
 * The <b>ModuleLoader</b> to add to the output stream.
 *
 * @return
 * The output stream with added <b>ModuleLoader</b>.
 */
FolioOStream&   operator<< (Folio::FolioOStream&    outputStream, 
                            const ModuleLoader&     rhs)
{
    FOLIO_STREAM_FIRST_MEMBER(outputStream, rhs, m_moduleName);
    FOLIO_STREAM_LAST_MEMBER(outputStream, rhs, m_moduleHandle);

    return (outputStream);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
