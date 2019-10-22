#pragma once

// STL includes.
#include    "vector"

// "Home-made" includes.
#include    "ZxSpectrum.h"

#pragma pack(push, 1)

namespace Folio        
{

namespace Core
{

namespace Game
{

// Item attributes.
template <typename T>
class ItemAttributes
{
public:
    ItemAttributes (T                                       itemId,
                    UInt16                                  bitmapResourceId,
                    Int32                                   screenXLeft,
                    Int32                                   screenYTop,
                    Folio::Core::Game::ZxSpectrum::COLOUR   colour)
    :   m_itemId(itemId),
        m_bitmapResourceId(bitmapResourceId),
        m_screenXLeft(screenXLeft),
        m_screenYTop(screenYTop),
        m_colour(colour)
    {} // Endproc.

    ItemAttributes (T                                       itemId,
                    Int32                                   screenXLeft,
                    Int32                                   screenYTop,
                    Folio::Core::Game::ZxSpectrum::COLOUR   colour)
    :   m_itemId(itemId),
        m_bitmapResourceId(0),
        m_screenXLeft(screenXLeft),
        m_screenYTop(screenYTop),
        m_colour(colour)
    {} // Endproc.

    ~ItemAttributes ()
    {} // Endproc.

    T                                       m_itemId;           // The identifier of the screen item.
    UInt16                                  m_bitmapResourceId; // The screen item's bitmap resource identifier (if it's a graphic item).
    Int32                                   m_screenXLeft;      // The screen X left of the screen item.
    Int32                                   m_screenYTop;       // The screen Y top of the screen item.
    Folio::Core::Game::ZxSpectrum::COLOUR   m_colour;           // The colour of the screen item.
}; // Endclass.

// Item attributes list.
template <typename T>
using ItemAttributesList = std::vector<ItemAttributes<T> >;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
