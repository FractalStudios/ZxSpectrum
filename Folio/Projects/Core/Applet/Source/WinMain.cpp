// "Home-made" includes.
#include    <Util.h>
#include    "AppletConstsAndTypes.h"
#include    "AppletWnd.h"
#include    "WinMain.h"

/**
 * The main windows start function.
 *
 * @param [in] instanceHandle
 * Handle to the current instance of the application.
 *
 * @param [in] previousInstanceHandle
 * Handle to the previous instance of the application. This parameter is always 
 * NULL.
 *
 * @param [in] commandLine
 * Pointer to a null-terminated string specifying the command line for the 
 * application, excluding the program name.
 *
 * @param [in] cmdShow
 * Specifies how the window is to be shown.
 *
 * @return
 * The result of processing.
 */
int WINAPI  WinMain (HINSTANCE  instanceHandle,
                     HINSTANCE  previousInstanceHandle,
                     LPSTR      commandLine,
                     int        cmdShow)
{
    int returnValue = 0;

    try
    {
        // Get the applet window instance.

        Folio::Core::Applet::AppletWnd  *appletWnd = 
            Folio::Core::Applet::AppletWnd::GetInstance ();

        // Process.

        returnValue = appletWnd->Process (instanceHandle,
                                          Folio::FolioString(commandLine));

        // Release the applet window instance.

        appletWnd->ReleaseInstance ();
    } // Endtry.

    catch (const Folio::Core::Util::Exception& exception)
    {
        exception.Process ();

        returnValue = -1;
    } // Endcatch.

//    catch (Folio::Core::Util::Win32Exception& win32Exception)
//    {
//        win32Exception.Process (FOLIO_SOURCE_FILE_LINE, FOLIO_SOURCE_FILE_NAME);
//
//        returnValue = -1;
//    } // Endcatch.
    
    return (returnValue);

    FOLIO_UNREFERENCED(previousInstanceHandle);
    FOLIO_UNREFERENCED(cmdShow);
} // Endproc.

/******************************* End of File *******************************/
