#pragma once

// STL includes.
#include    <memory>

// "Home-made" includes.
#include    "DrawingElement.h"
#include    "InformationPanel.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Found amulet piece screen item identifier enumeration.
enum FOUND_AMULET_PIECE_SCREEN_ITEM_ID
{
    FOUND_AMULET_PIECE_SCREEN_ITEM_INFORMATION_PANEL = DRAWING_ELEMENT_FOUND_AMULET_PIECE_SCREEN_ITEM * MAX_NUM_DRAWING_ELEMENTS_PER_ITEM,
    FOUND_AMULET_PIECE_SCREEN_ITEM_AMULET_PIECE_TOP_LEFT,   
    FOUND_AMULET_PIECE_SCREEN_ITEM_AMULET_PIECE_TOP_RIGHT,  
    FOUND_AMULET_PIECE_SCREEN_ITEM_AMULET_PIECE_BOTTOM_LEFT,
    FOUND_AMULET_PIECE_SCREEN_ITEM_AMULET_PIECE_BOTTOM_RIGHT,
    FOUND_AMULET_PIECE_SCREEN_ITEM_POEM_TEXT_1,
    FOUND_AMULET_PIECE_SCREEN_ITEM_POEM_TEXT_2,
    FOUND_AMULET_PIECE_SCREEN_ITEM_POEM_TEXT_3,
    FOUND_AMULET_PIECE_SCREEN_ITEM_POEM_TEXT_4,
}; // Endenum.


// Found amulet piece screen.
class FoundAmuletPieceScreen : public Folio::Core::Applet::AScreen
{
public:
    FoundAmuletPieceScreen (const InformationPanelPtr &informationPanel);
    ~FoundAmuletPieceScreen ();

private:
    const InformationPanelPtr  &m_informationPanel; // The information panel.

    // AScreen method(s).
    virtual FolioStatus BuildScreenItems (FolioHandle dcHandle, 
                                          FolioHandle instanceHandle);
    virtual FolioStatus ProcessScreenInput ();    

    void    SetItemText (Folio::Core::Game::TextItemPtr::element_type &item);

    // Private copy constructor to prevent copying.
    FoundAmuletPieceScreen (const FoundAmuletPieceScreen& rhs);

    // Private assignment operator to prevent copying.
    FoundAmuletPieceScreen& operator= (const FoundAmuletPieceScreen& rhs);
}; // Endclass.

// Found amulet piece screen pointer.
typedef std::shared_ptr<FoundAmuletPieceScreen> FoundAmuletPieceScreenPtr;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
