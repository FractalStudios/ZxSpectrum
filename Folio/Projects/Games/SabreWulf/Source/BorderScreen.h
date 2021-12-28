#pragma once

// "Home-made" includes.
#include    <Applet.h>

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
    BORDER_SCREEN_ITEM_UNDEFINED = Folio::Core::Game::AItem::ITEM_ID_UNDEFINED,
    BORDER_SCREEN_ITEM_BORDER,
}; // Endenum.


// Border screen.
class BorderScreen : public Folio::Core::Applet::AScreen
{
public:
    virtual ~BorderScreen ();

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
