// "Home-made" includes.
#include    "StdAfx.h"
#include    "ZxSpectrum.h"

namespace Folio
{

namespace Games
{

namespace ZxSpectrum
{

static  Gdiplus::ARGB   MapColour (COLOUR   colour, 
                                   bool     bright)
{
    switch (colour)
    {
    case BLACK:
        return (0xff000000);
    case BLUE:
        return (bright ? 0xff0000ff : 0xff0000d7);
    case RED:
        return (bright ? 0xffff0000 : 0xffd70000);
    case MAGENTA:
        return (bright ? 0xffff00ff : 0xffd700d7);
    case GREEN:
        return (bright ? 0xff00ff00 : 0xff00d700);
    case CYAN:
        return (bright ? 0xff00ffff : 0xff00d7d7);
    case YELLOW:
        return (bright ? 0xffffff00 : 0xffd7d700);
    case WHITE:
        return (bright ? 0xffffffff : 0xffd7d7d7);
    default:
        return (GetBitmapChangeColour ());
    } // Endswitch.

} // Endproc.


Gdiplus::ARGB   MapInkColour (COLOUR colour)
{
    // Special case for undefined colour.

    if (colour == UNDEFINED)
    {
        return (GetBitmapChangeColour ());
    } // Endif.

    return (MapColour (colour & INK_COLOUR_MASK, (colour & BRIGHT) == BRIGHT));
} // Endproc.


Gdiplus::ARGB    MapPaperColour (COLOUR colour)
{
    // Special case for undefined colour.

    if (colour == UNDEFINED)
    {
        return (GetBitmapChangeColour ());
    } // Endif.

    return (MapColour (colour & PAPER_COLOUR_MASK, (colour & BRIGHT) == BRIGHT));
} // Endproc.


Gdiplus::ARGB   GetBitmapChangeColour ()
{
    return (0x00c0c0c0);
} // Endproc.


COLOUR  MapColour (Gdiplus::ARGB colour)
{
    switch (colour)
    {
    case 0xff000000:
        return (BLACK);
    case 0xff0000ff:
        return (BRIGHT | BLUE);
    case 0xff0000d7:
        return (BLUE);
    case 0xffff0000:
        return (BRIGHT | RED);
    case 0xffd70000:
        return (RED);
    case 0xffff00ff:
        return (BRIGHT | MAGENTA);
    case 0xffd700d7:
        return (MAGENTA);
    case 0xff00ff00:
        return (BRIGHT | GREEN);
    case 0xff00d700:
        return (GREEN);
    case 0xff00ffff:
        return (BRIGHT | CYAN);
    case 0xff00d7d7:
        return (CYAN);
    case 0xffffff00:
        return (BRIGHT | YELLOW);
    case 0xffd7d700:
        return (YELLOW);
    case 0xffffffff:
        return (BRIGHT | WHITE);
    case 0xffd7d7d7:
    default:
        return (WHITE);
    } // Endswitch.

} // Endproc.


Int32   CalculateScreenYTop (Int32  screenYBottom,
                             Int32  screenWidth,
                             Int32  screenHeight,
                             UInt32 drawingFlags)
{
    if (!Folio::Core::Game::ResourceGraphic::IsRotated (drawingFlags) ||
         Folio::Core::Game::ResourceGraphic::IsRotation180 (drawingFlags))
    {
        return (screenYBottom - screenHeight + 1);
    } // Endif

    return (screenYBottom - screenWidth + 1);
} // Endproc.


Int32   CalculateScreenYBottom (Int32   screenYTop,
                                Int32   screenWidth,
                                Int32   screenHeight,
                                UInt32  drawingFlags)
{
    if (!Folio::Core::Game::ResourceGraphic::IsRotated (drawingFlags) ||
         Folio::Core::Game::ResourceGraphic::IsRotation180 (drawingFlags))
    {
        return (screenYTop + screenHeight - 1);
    } // Endif

    return (screenYTop + screenWidth - 1);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
