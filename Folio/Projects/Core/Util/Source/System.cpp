// "Home-made" includes.
#include    <Trace.h>
#include    "System.h"

namespace Folio
{

namespace Core
{

namespace Util
{

namespace System
{

/**
 * Function that will query the system information.
 *
 * @param [out] systemInfo
 * On return, will hold the system information, if successful. If this method 
 * fails then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus QuerySystemInfo (SYSTEM_INFO& systemInfo)
{
    ::GetSystemInfo (&(systemInfo));

    return (ERR_SUCCESS);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
