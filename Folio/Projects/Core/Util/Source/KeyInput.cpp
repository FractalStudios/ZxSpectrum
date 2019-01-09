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
