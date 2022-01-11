// "Home-made" includes.
#include    "SpriteGraphics.h"

namespace Folio        
{

namespace Core
{

namespace Game
{

FolioString DescribeDirection (Direction direction)
{
    FolioOStringStream  str;

    if (direction == NO_DIRECTION)
    {
        str << TXT("None");
    } // Endif.

    else
    if (direction == ALL_DIRECTIONS)
    {
        str << TXT("All");
    } // Endelseif.

    else
    {
        if (direction & N)
        {
            str << TXT("N");
        } // Endif.

        else
        if (direction & S)
        {
            str << TXT("S");
        } // Endif.

        if (direction & E)
        {
            str << TXT("E");
        } // Endif.

        else
        if (direction & W)
        {
            str << TXT("W");
        } // Endif.

    } // Endelse.

    return (str.str ());
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.
/******************************* End of File *******************************/
