#pragma once

// "Home-made" includes.
#include    <Applet.h>
#include    <Game.h>
#include    "DrawingElement.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Border screen item identifier enumeration.
enum BORDER_SCREEN_ITEM_ID
{
    BORDER_SCREEN_ITEM_BORDER = DRAWING_ELEMENT_BORDER_SCREEN_ITEM * MAX_NUM_DRAWING_ELEMENTS_PER_ITEM,
}; // Endenum.


// Border screen.
class BorderScreen : public Folio::Core::Applet::AScreen
{
public:
    ~BorderScreen ();

protected:
    BorderScreen ();

    FolioStatus AddBorderScreenItems (FolioHandle   dcHandle, 
                                      FolioHandle   instanceHandle);

private:
    // Private copy constructor to prevent copying.
    BorderScreen (const BorderScreen& rhs);

    // Private assignment operator to prevent copying.
    BorderScreen& operator= (const BorderScreen& rhs);
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
