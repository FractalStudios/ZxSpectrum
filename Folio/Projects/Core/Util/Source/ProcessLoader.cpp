// Windows includes.
#include    <Windows.h>

// "Home-made" includes.
#include    <Trace.h>
#include    "ProcessLoader.h"

namespace Folio
{

namespace Core
{

namespace Util
{

/**
 * The default class constructor.
 */
ProcessLoader::ProcessLoader ()
:   m_id(0)
{
} // Endproc.


/**
 * The class destructor. If required it will remove any OS reference to
 * the process from this object. The running state of the process is
 * unaltered.
 */
ProcessLoader::~ProcessLoader ()
{
} // Endproc.


/**
 * Method that will start the process. Only one process at a time can be
 * started and running. If a previously started process is still running then
 * <b>ERR_INVALID_SEQUENCE</b> will be returned.
 *
 * @param [in] processName
 * The name of the process. The name is case sensitive.
 *
 * @param [in] commandLine
 * The process's command line arguments.
 *
 * @param [in] creationFlags
 * The flags that control the priority class and the creation of the process.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the process was successfully started.
 * <li><b>ERR_UTIL_FILE_NOT_FOUND</b> if the process was not found.
 * <li><b>ERR_UTIL_PATH_NOT_FOUND</b> if the process path was not found.
 * <li><b>ERR_INVALID_SEQUENCE</b> if previously started process using this
 *     object is still running.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus ProcessLoader::Start (const FolioString&    processName,
                                  const FolioString&    commandLine,
                                  UInt32                creationFlags)
{
    FolioStatus status = ERR_SUCCESS;

    // Is there a process running already?

    if (IsRunning ())
    {
        // Yes. Already have a running process for this object.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // Create the process data.

        STARTUPINFO startupInfo;
        ::memset (&(startupInfo), 0, sizeof (startupInfo));
        startupInfo.cb = sizeof (startupInfo);

        PROCESS_INFORMATION processInfo;
        ::memset (&(processInfo), 0, sizeof (processInfo));

        // Create the process.

        if (::CreateProcess (processName, 
                             commandLine,
                             0,     // No process handle inheritance.
                             0,     // No thread handle inheritance.
                             FALSE, // Don't inherit handles.
                             creationFlags,
                             0,     // Use our environment.
                             0,     // Current directory.
                             &(startupInfo),
                             &(processInfo)))
        {
            // Close the thread handle.

            ::CloseHandle (processInfo.hThread);

            // Note the process identifier and handle.

            m_id            = processInfo.dwProcessId;
            m_syncHandle    = processInfo.hProcess;
        } // Endif.

        else
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            switch (status)
            {
            case ERROR_FILE_NOT_FOUND:
                FOLIO_LOG_CALL_WARNING_3 (TXT("CreateProcess"),
                                          status,
                                          processName,
                                          commandLine,
                                          creationFlags);

                status = ERR_UTIL_FILE_NOT_FOUND;
                break;

            case ERROR_PATH_NOT_FOUND:
                FOLIO_LOG_CALL_WARNING_3 (TXT("CreateProcess"),
                                          status,
                                          processName,
                                          commandLine,
                                          creationFlags);

                status = ERR_UTIL_PATH_NOT_FOUND;
                break;

            default:
                FOLIO_LOG_CALL_ERROR_3 (TXT("CreateProcess"),
                                        status,
                                        processName,
                                        commandLine,
                                        creationFlags);
                break;
            } // Endswitch.

        } // Endelse.

    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will indicate if the process is running.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>true</b> if the process is running,
 * <li><b>false</b> otherwise.
 * </ul>
 */
bool    ProcessLoader::IsRunning () const
{
    UInt32  exitCode = ERR_SUCCESS;

    return (QueryProcessExitCode (exitCode) == ERR_STARTED);
} // Endproc.


/**
 * Method that will get the identifier of the process.
 *
 * @return
 * The possible return values are:<ul>
 * <li>The identifier of the process, if the process is running or the process
 *     had previously run and has now stopped.
 * <li>Zero if the process has not been started.
 * </ul>
 */
UInt32  ProcessLoader::GetProcessId () const
{
    return (m_id);
} // Endproc.


/**
 * Method that will get the process exit code of the process.
 *
 * @param [out] exitCode
 * Will hold the exit code of the process if successful, i.e. the process
 * had previously been started and has now stopped. Otherwise the
 * <i>exitCode</i> value is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if no process has been started using
 *     this object.
 * <li><b>ERR_STARTED</b> if the process has been started (and is still
 *     running).
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus ProcessLoader::QueryProcessExitCode (UInt32& exitCode) const
{
    FolioStatus status = ERR_SUCCESS;

    // Have we started a process?

    if (m_syncHandle == FOLIO_INVALID_HANDLE)
    {
        // Process not started.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // Has the process exited?

        UInt32  win32ExitCode;

        if (::GetExitCodeProcess (m_syncHandle, 
                                  reinterpret_cast<LPDWORD> (&(win32ExitCode))))
        {
            if (win32ExitCode == STILL_ACTIVE)
            {
                // Process has not exited.

                status = ERR_STARTED;
            } // Endif.

            else
            {
                exitCode = win32ExitCode;
            } // Endelse.

        } // Endif.

        else
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_2 (TXT("GetExitCodeProcess"),
                                    status,
                                    m_syncHandle,
                                    m_id);
        } // Endelse.

    } // Endelse.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
