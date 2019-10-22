#include "stdafx.h"
#include "ZxSpectrum.h"

namespace ZxSpectrum
{

// Attributes.
static  const   BYTE    ATTRIBUTE_MASK  = 0xc0;
static  const   BYTE    FLASH           = 0x80;
static  const   BYTE    BRIGHT          = 0x40;

// Colours
static  const   BYTE    INK_COLOUR_MASK     = 0x38; // Swapped ?
static  const   BYTE    PAPER_COLOUR_MASK   = 0x07; // Swapped ?

static  const   BYTE    BLACK       = 0;  
static  const   BYTE    BLUE        = 1;  
static  const   BYTE    RED         = 2;  
static  const   BYTE    MAGENTA     = 3;  
static  const   BYTE    GREEN       = 4;  
static  const   BYTE    CYAN        = 5;  
static  const   BYTE    YELLOW      = 6;  
static  const   BYTE    WHITE       = 7;


std::wstring    DescribeAttribute (BYTE byAttribute)
{
    std::wostringstream str;

    if (byAttribute & FLASH)
    {
        str << L"Flash ";
    } // Endif.

    if (byAttribute & BRIGHT)
    {
        str << L"Bright ";
    } // Endif.

    return (str.str ());
} // Endproc.


std::wstring    DescribeColour (BYTE byColour)
{
    std::wostringstream str;
    str << L"Ink=";

    switch (byColour & INK_COLOUR_MASK)
    {
    case BLACK:
        str << L"Black";
        break;
    case BLUE:
        str << L"Blue";
        break;
    case RED:
        str << L"Red";
        break;
    case MAGENTA:
        str << L"Magenta";
        break;
    case GREEN:
        str << L"Green";
        break;
    case CYAN:
        str << L"Cyan";
        break;
    case YELLOW:
        str << L"Yellow";
        break;
    case WHITE:
        str << L"White";
        break;
    default:
        str << static_cast<int> (byColour & INK_COLOUR_MASK);
        break;
    } // Endswitch.

    str << L" Paper=";

    switch ((byColour & PAPER_COLOUR_MASK) >> 3)
    {
    case BLACK:
        str << L"Black";
        break;
    case BLUE:
        str << L"Blue";
        break;
    case RED:
        str << L"Red";
        break;
    case MAGENTA:
        str << L"Magenta";
        break;
    case GREEN:
        str << L"Green";
        break;
    case CYAN:
        str << L"Cyan";
        break;
    case YELLOW:
        str << L"Yellow";
        break;
    case WHITE:
        str << L"White";
        break;
    default:
        str << static_cast<int> ((byColour & PAPER_COLOUR_MASK) >> 3);
        break;
    } // Endswitch.

    return (str.str ());
} // Endproc.


COLORREF    MapInkColour (BYTE byColour)
{
    // Special case for undefined colour.

    if (byColour == 0xff)
    {
        return (DEFAULT_COLOUR);
    } // Endif.

    switch ((byColour >> 3) & 0x07)
    {
    case BLACK:
        return (RGB(0x00, 0x00, 0x00));
    case BLUE:
        return ((byColour & BRIGHT) ? RGB(0x00, 0x00, 0xff) : RGB(0x00, 0x00, 0xd7));
    case RED:
        return ((byColour & BRIGHT) ? RGB(0xff, 0x00, 0x00) : RGB(0xd7, 0x00, 0x00));
    case MAGENTA:
        return ((byColour & BRIGHT) ? RGB(0xff, 0x00, 0xff) : RGB(0xd7, 0x00, 0xd7));
    case GREEN:
        return ((byColour & BRIGHT) ? RGB(0x00, 0xff, 0x00) : RGB(0x00, 0xd7, 0x00));
    case CYAN:
        return ((byColour & BRIGHT) ? RGB(0x00, 0xff, 0xff) : RGB(0x00, 0xd7, 0xd7));
    case YELLOW:
        return ((byColour & BRIGHT) ? RGB(0xff, 0xff, 0x00) : RGB(0xd7, 0xd7, 0x00));
    case WHITE:
        return ((byColour & BRIGHT) ? RGB(0xff, 0xff, 0xff) : RGB(0xd7, 0xd7, 0xd7));
    default:
        return (DEFAULT_COLOUR);
        break;
    } // Endswitch.

} // Endproc.

COLORREF    MapPaperColour (BYTE byColour)
{
    // Special case for undefined colour.

    if (byColour == 0xff)
    {
        return (DEFAULT_COLOUR);
    } // Endif.

    switch (byColour & PAPER_COLOUR_MASK)
    {
    case BLACK:
        return (RGB(0x00, 0x00, 0x00));
    case BLUE:
        return ((byColour & BRIGHT) ? RGB(0x00, 0x00, 0xff) : RGB(0x00, 0x00, 0xd7));
    case RED:
        return ((byColour & BRIGHT) ? RGB(0xff, 0x00, 0x00) : RGB(0xd7, 0x00, 0x00));
    case MAGENTA:
        return ((byColour & BRIGHT) ? RGB(0xff, 0x00, 0xff) : RGB(0xd7, 0x00, 0xd7));
    case GREEN:
        return ((byColour & BRIGHT) ? RGB(0x00, 0xff, 0x00) : RGB(0x00, 0xd7, 0x00));
    case CYAN:
        return ((byColour & BRIGHT) ? RGB(0x00, 0xff, 0xff) : RGB(0x00, 0xd7, 0xd7));
    case YELLOW:
        return ((byColour & BRIGHT) ? RGB(0xff, 0xff, 0x00) : RGB(0xd7, 0xd7, 0x00));
    case WHITE:
        return ((byColour & BRIGHT) ? RGB(0xff, 0xff, 0xff) : RGB(0xd7, 0xd7, 0xd7));
    default:
        return (DEFAULT_COLOUR);
        break;
    } // Endswitch.

} // Endproc.

}; // Endnamespace.

/******************************* End of File *******************************/
