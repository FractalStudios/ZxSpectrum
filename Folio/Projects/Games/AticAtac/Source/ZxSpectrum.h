#pragma once

// "Home-made" includes.
#include    <Game.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace ZxSpectrum
{

// Definitions and Types.

typedef unsigned    BYTE;   // BYTE type.
typedef unsigned    WORD;   // WORD type.

const   unsigned    UNDEFINED = -1;

// Screen size.
const   BYTE    MAX_SCREEN_X_PIXELS = 256;
const   BYTE    MAX_SCREEN_Y_PIXELS = 192;

const   BYTE    NUM_PIXELS_PER_TEXT_POSITION = 8;

const   BYTE    MAX_NUM_COLUMNS = MAX_SCREEN_X_PIXELS / NUM_PIXELS_PER_TEXT_POSITION;
const   BYTE    MAX_NUM_ROWS    = MAX_SCREEN_Y_PIXELS / NUM_PIXELS_PER_TEXT_POSITION;

// Screen scale.
const   BYTE    DEFAULT_SCREEN_SCALE = 4;

// Timings.
const   BYTE    FLASH_MS = 250; // Flash time (in milliseconds).

// Masks.
const   BYTE    INK_COLOUR_MASK     = 0x07;
const   BYTE    PAPER_COLOUR_MASK   = 0x38;
const   BYTE    ATTRIBUTE_MASK      = 0xc0;

typedef BYTE    COLOUR; // COLOUR type.

// Attributes.
const   COLOUR  FLASH   = 0x80;
const   COLOUR  BRIGHT  = 0x40;

// Colours.
const   COLOUR  BLACK   = 0x00;  
const   COLOUR  BLUE    = 0x01;  
const   COLOUR  RED     = 0x02;  
const   COLOUR  MAGENTA = 0x03;  
const   COLOUR  GREEN   = 0x04;  
const   COLOUR  CYAN    = 0x05;  
const   COLOUR  YELLOW  = 0x06;  
const   COLOUR  WHITE   = 0x07;


// Routines.

extern  Gdiplus::ARGB   MapInkColour (COLOUR colour);
extern  Gdiplus::ARGB   MapPaperColour (COLOUR colour);
extern  Gdiplus::ARGB   GetBitmapChangeColour ();

extern  COLOUR  MapColour (Gdiplus::ARGB colour);

extern  Int32   CalculateScreenYTop (Int32  screenYBottom,
                                     Int32  screenWidth,
                                     Int32  screenHeight,
                                     UInt32 drawingFlags = Folio::Core::Game::ResourceGraphic::NO_DRAWING_FLAGS);
extern  Int32   CalculateScreenYBottom (Int32   screenYTop,
                                        Int32   screenWidth,
                                        Int32   screenHeight,
                                        UInt32  drawingFlags = Folio::Core::Game::ResourceGraphic::NO_DRAWING_FLAGS);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
