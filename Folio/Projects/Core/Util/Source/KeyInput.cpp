// Windows includes.
#include    <Windows.h>

// "Home-made" includes.
#include    <Trace.h>
#include    "KeyInput.h"

namespace Folio
{

namespace Core
{

namespace Util
{

namespace KeyInput
{

/**
 * Function that determines whether any key is down at the time the function is 
 * called.
 *
 * @return
 * <b>true</b> if any key is down, <b>false</b> otherwise.
 */
bool    IsAnyKeyDown ()
{
    bool    isAnyKeyDown = false;

    BYTE    keyState [256] = {0};   // Initialise!

    if (::GetKeyboardState (keyState))
    {
        for (UInt32 virtualKey = 0; 
             !isAnyKeyDown && (virtualKey < sizeof (keyState)); 
             ++virtualKey)
        {
            isAnyKeyDown = ((keyState [virtualKey] & 0x80) == 0x80);
        } // Endfor.

    } // Endif.

    else
    {
        // Build and log an error.

        FolioStatus status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR (TXT("GetKeyboardState"),
                              status);
    } // Endelse.

    return (isAnyKeyDown);
} // Endproc.


/**
 * Function that determines whether a key is down at the time the function is 
 * called.
 *
 * @param [in] virtualKey
 * The virtual-key code.
 *
 * @return
 * <b>true</b> if the key is down, <b>false</b> otherwise.
 */
bool    IsKeyDown (Int32 virtualKey)
{
    return ((::GetAsyncKeyState (virtualKey) & 0x8000) ? true : false);
} // Endproc.


/**
 * Function that determines whether a key is up at the time the function is 
 * called.
 *
 * @param [in] virtualKey
 * The virtual-key code.
 *
 * @return
 * <b>true</b> if the key is up, <b>false</b> otherwise.
 */
bool    IsKeyUp (Int32 virtualKey)
{
    return ((::GetAsyncKeyState(virtualKey) & 0x8000) ? false : true);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
