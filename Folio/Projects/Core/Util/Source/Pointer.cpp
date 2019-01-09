// Windows includes.
#include    <Windows.h>

// "Home-made" includes.
#include    <Trace.h>
#include    "Pointer.h"

namespace Folio
{

namespace Core
{

namespace Util
{

namespace Ptr
{

/**
 * Function that will indicate if a pointer is valid for reading from.
 *
 * @param [in] pointer
 * The pointer to validate.
 *
 * @param [in] size
 * The size (in bytes) of the data pointed to by the pointer.
 *
 * @param [in] nullAllowed
 * Indicates if a NULL pointer is valid.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>true</b> if the pointer can be read from.
 * <li><b>false</b> otherwise.
 * </ul>
 */
bool    IsValidReadPtr (void*   pointer,
                        UInt32  size,
                        bool    nullAllowed)
{
    bool    isValidReadPtr = false; // Initialise!

    if (pointer)
    {
        isValidReadPtr = !::IsBadReadPtr (pointer, size);
    } // Endif.

    else if (nullAllowed)
    {
        isValidReadPtr = true;
    } // Endelseif.

    if (!isValidReadPtr)
    {
        // Build and log an error.

        FOLIO_LOG_WARNING_3 (TXT("Invalid read pointer."),
                             pointer,
                             size,
                             nullAllowed);
    } // Endif.

    return (isValidReadPtr);
} // Endproc.


/**
 * Function that will indicate if a pointer is valid for writing to.
 *
 * @param [in] pointer
 * The pointer to validate.
 *
 * @param [in] size
 * The size (in bytes) of the data pointed to by the pointer.
 *
 * @param [in] nullAllowed
 * Indicates if a NULL pointer is valid.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>true</b> if the pointer can be written to.
 * <li><b>false</b> otherwise.
 * </ul>
 */
bool    IsValidWritePtr (void*  pointer,
                         UInt32 size,
                         bool   nullAllowed)
{
    bool    isValidWritePtr = false;    // Initialise!

    if (pointer)
    {
        isValidWritePtr = !::IsBadWritePtr (pointer, size);
    } // Endif.

    else if (nullAllowed)
    {
        isValidWritePtr = true;
    } // Endelseif.

    if (!isValidWritePtr)
    {
        // Build and log an error.

        FOLIO_LOG_WARNING_3 (TXT("Invalid write pointer."),
                             pointer,
                             size,
                             nullAllowed);
    } // Endif.

    return (isValidWritePtr);
} // Endproc.


/**
 * Function that will indicate if a pointer is valid for reading from and
 * writing to.
 *
 * @param [in] pointer
 * The pointer to validate.
 *
 * @param [in] size
 * The size (in bytes) of the data pointed to by the pointer.
 *
 * @param [in] nullAllowed
 * Indicates if a NULL pointer is valid.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>true</b> if the pointer can be read from and written to.
 * <li><b>false</b> otherwise.
 * </ul>
 */
bool    IsValidReadWritePtr (void*  pointer,
                             UInt32 size,
                             bool   nullAllowed)
{
    return (IsValidReadPtr  (pointer, size, nullAllowed) &&
            IsValidWritePtr (pointer, size, nullAllowed));
} // Endproc.


/**
 * Function that will indicate if a pointer is a valid 8-bit ANSI string 
 * pointer.
 *
 * @param [in] pointer
 * The pointer to validate.
 *
 * @param [in] nullAllowed
 * Indicates if a NULL pointer is valid.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>true</b> if the pointer is a valid 8-bit ANSI string pointer.
 * <li><b>false</b> otherwise.
 * </ul>
 */
bool    IsValidStringPtrA (const char*  pointer,
                           bool         nullAllowed)
{
    bool    bValid = false;

    if (pointer)
    {
        bValid = !::IsBadStringPtrA (pointer, INFINITE);
    } // Endif.

    else if (nullAllowed)
    {
        bValid = true;
    } // Endelseif.

    if (!bValid)
    {
        // Build and log an error.

        const void* ptr = reinterpret_cast<const void*> (pointer);

        FOLIO_LOG_WARNING_2 (TXT("Invalid string pointer."),
                             ptr,
                             nullAllowed);
    } // Endif.

    return (bValid);
} // Endproc.


/**
 * Function that will indicate if a pointer is a valid 16-bit Unicode string 
 * pointer.
 *
 * @param [in] pointer
 * The pointer to validate.
 *
 * @param [in] nullAllowed
 * Indicates if a NULL pointer is valid.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>true</b> if the pointer is a valid 16-bit Unicode string pointer.
 * <li><b>false</b> otherwise.
 * </ul>
 */
bool    IsValidStringPtrW (const wchar_t*   pointer,
                           bool             nullAllowed)
{
    bool    bValid = false;

    if (pointer)
    {
        bValid = !::IsBadStringPtrW (pointer, INFINITE);
    } // Endif.

    else if (nullAllowed)
    {
        bValid = true;
    } // Endelseif.

    if (!bValid)
    {
        // Build and log an error.

        const void* ptr = reinterpret_cast<const void*> (pointer);

        FOLIO_LOG_WARNING_2 (TXT("Invalid string pointer."),
                             ptr,
                             nullAllowed);
    } // Endif.

    return (bValid);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
