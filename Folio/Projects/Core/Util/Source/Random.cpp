// C includes.
#include    <stdlib.h>
#include    <time.h>

// "Home-made" includes.
#include    "Random.h"

namespace Folio
{

namespace Core
{

namespace Util
{

namespace Random
{

/**
 * Function that will set a random seed.
 */
void    SetRandomSeed ()
{
    // Set random seed.

    ::srand (static_cast<unsigned int> (::time (0)));
} // Endproc.


/**
 * Function that will obtain a random number between zero and a specified 
 * maximum number (inclusive).
 *
 * @param [in] max
 * The maximum number.
 *
 * @return
 * The random number.
 */
UInt32  GetRandomNumber (UInt32 max)
{
    return (::rand () % (max + 1)); 
} // Endproc.


/**
 * Function that will obtain a random number between a specified minimum number 
 * and a specified maximum number (inclusive).
 *
 * @param [in] min
 * The minimum number.
 *
 * @param [in] max
 * The maximum number.
 *
 * @return
 * The random number.
 */
UInt32  GetRandomNumber (UInt32 min, UInt32 max)
{
    return ((::rand() % (max - min + 1)) + min); 
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
