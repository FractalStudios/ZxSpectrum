#pragma once

#include    <map>
#include    <string>

#pragma pack(push, 1)

// Definitions and Types.

#define _GRAPHICS_ONLY_

// Data start address.

static  const   WORD    START_ADDRESS = 0x7796;


// Routines.

extern  std::wstring    DescribeBackgroundItem (BYTE byGraphicType);
extern  std::wstring    DescribeFlags (BYTE byFlags);

struct AddressDetails
{
    enum TYPE
    {
        UNKNOWN = 0,
        BACKGROUND_ITEM_ATTRIBUTE,
        BACKGROUND_ITEM_SPRITE,
        CHARACTER_SPRITE,
        FONT,
    };
    AddressDetails ()
    :   m_wAddress(0),
        m_byByte(0),
        m_type(UNKNOWN),
        m_bKnown(false)
    {} // Endproc.

    AddressDetails (WORD    wAddress,
                    BYTE    byByte)
    :   m_wAddress(wAddress),
        m_byByte(byByte),
        m_type(UNKNOWN),
        m_bKnown(false)
    {} // Endproc.

    static  std::string DescribeType (TYPE type)
    {
        switch (type)
        {
        case BACKGROUND_ITEM_ATTRIBUTE:
            return ("BackgroundItemAttribute");
        case BACKGROUND_ITEM_SPRITE:
            return ("BackgroundItemSprite");
        case CHARACTER_SPRITE:
            return ("CharacterSprite");
        case FONT:
            return ("Font");
        case UNKNOWN:
        default:
            return ("Unknown");
       }  // Endswitch.

    } // Endproc.

    WORD    m_wAddress;
    BYTE    m_byByte;
    TYPE    m_type;
    bool    m_bKnown;
}; // Endstruct.

typedef std::map<WORD, AddressDetails> AddressMap;

#pragma pack(pop)

/******************************* End of File *******************************/

