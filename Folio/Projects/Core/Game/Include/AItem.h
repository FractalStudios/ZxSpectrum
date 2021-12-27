#pragma once

// STL includes.
#include    <memory>
#include    <vector>

// "Home-made" includes.
#include    <Graphic.h>
#include    "DrawingElement.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Game
{

class AItem
{
public:
    // Item identifier.
    typedef UInt32  Id;

    static  const   Id  ITEM_ID_UNDEFINED = FOLIO_UNDEFINED;    // Undefined item identifier.

    virtual ~AItem ();

    Id                  GetItemId () const;
    Gdiplus::ARGB       GetForegroundColour () const;
    Gdiplus::ARGB       GetBackgroundColour () const;
    DrawingElementsList GetDrawingElementsList () const;

    Gdiplus::Rect   GetScreenRect () const;
    Int32           GetScreenXLeft () const;
    Int32           GetScreenYTop () const;
    Int32           GetScreenXRight () const;
    Int32           GetScreenYBottom () const;
    Int32           GetScreenWidth () const;
    Int32           GetScreenHeight () const;

    Folio::Core::Graphic::GdiGraphicElementPtr  GetGdiGraphicElement () const;

    FolioStatus SetScreenTopLeft (Int32 screenXLeft,    
                                  Int32 screenYTop);
    FolioStatus Draw (Gdiplus::Graphics&                                    graphics,
                      Folio::Core::Graphic::AGdiGraphicElement::RectList*   rects = 0);
    FolioStatus Draw (Int32                                                 screenXLeft,    
                      Int32                                                 screenYTop,
                      Gdiplus::Graphics&                                    graphics,
                      Folio::Core::Graphic::AGdiGraphicElement::RectList*   rects = 0);

protected:
    Id                  m_itemId;               // The identifier of the item.
    Int32               m_screenXLeft;          // The screen X left of the item.
    Int32               m_screenYTop;           // The screen Y top of the item.
    UInt32              m_screenScale;          // The screen scale of the item.
    Gdiplus::ARGB       m_foregroundColour;     // The foreground colour of the item.
    Gdiplus::ARGB       m_backgroundColour;     // The background colour of the item.
    DrawingElementsList m_drawingElementsList;  // The drawing elements list of the item.

    AItem ();
}; // Endclass.

// Item pointer.
typedef std::shared_ptr<Folio::Core::Game::AItem>   ItemPtr;

// Items list.
typedef std::vector<ItemPtr>    ItemsList;


// Routines.

extern  ItemsList::const_iterator FindItem (AItem::Id           itemId, 
                                            const ItemsList&    itemsList);
extern  ItemsList::iterator FindItem (AItem::Id     itemId, 
                                      ItemsList&    itemsList);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
