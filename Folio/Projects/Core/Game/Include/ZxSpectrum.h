#pragma once

// "Home-made" includes.
#include    "ResourceGraphic.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Game
{

namespace ZxSpectrum
{

// Definitions and Types.

typedef unsigned    BYTE;   // BYTE type.
typedef unsigned    WORD;   // WORD type.

const   unsigned    UNDEFINED = -1;

// Clock frequency.
const   UInt32  CLOCK_FREQUENCY         = 3500000;
const   UInt32  TV_REFRESH_FREQUENCY    = 50;

// Screen size.
const   BYTE    MAX_SCREEN_X_PIXELS = 256;
const   BYTE    MAX_SCREEN_Y_PIXELS = 192;

const   BYTE    NUM_PIXELS_PER_TEXT_POSITION = 8;

const   BYTE    MAX_NUM_COLUMNS = MAX_SCREEN_X_PIXELS / NUM_PIXELS_PER_TEXT_POSITION;
const   BYTE    MAX_NUM_ROWS    = MAX_SCREEN_Y_PIXELS / NUM_PIXELS_PER_TEXT_POSITION;

// Screen macros.
#define COLUMN_TO_PIXEL(column) (column * 8)
#define ROW_TO_PIXEL(row)       (row * 8)

// Screen scale.
const   BYTE    DEFAULT_SCREEN_SCALE = 4;

// Flash.
const   BYTE    FLASH_FRAME_RATE    = 16;                                               // Flash frame rate.
const   BYTE    FLASH_MILLISECONDS  = 1000 * FLASH_FRAME_RATE / TV_REFRESH_FREQUENCY;   // Flash time (in milliseconds).

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

// Colour macros.
#define SET_INK_COLOUR(colour)       (colour & 0x07) 
#define GET_INK_COLOUR(colour)       (colour & Folio::Core::Game::ZxSpectrum::INK_COLOUR_MASK) 

#define SET_PAPER_COLOUR(colour)    ((colour & 0x07) << 3)
#define GET_PAPER_COLOUR(colour)    ((colour & Folio::Core::Game::ZxSpectrum::PAPER_COLOUR_MASK) >> 3)


// Routines.

extern  Gdiplus::ARGB   MapInkColour (COLOUR colour);
extern  Gdiplus::ARGB   MapPaperColour (COLOUR colour);
extern  Gdiplus::ARGB   GetBitmapChangeColour ();

extern  COLOUR  MapColour (Gdiplus::ARGB colour);

extern  Int32   CalculateScreenYTop (Int32  screenYBottom,
                                     Int32  screenWidth,
                                     Int32  screenHeight,
                                     UInt32 drawingFlags = ResourceGraphic::NO_DRAWING_FLAGS);
extern  Int32   CalculateScreenYBottom (Int32   screenYTop,
                                        Int32   screenWidth,
                                        Int32   screenHeight,
                                        UInt32  drawingFlags = ResourceGraphic::NO_DRAWING_FLAGS);

extern  UInt32  BeepDurationToMilliseconds (const float& beepDuration);
extern  float   BeepPitchToFrequency (Int32 beepPitch);
extern  UInt32  CalculateDuration (UInt32 numTStates);
extern  float   CalculateFrequency (UInt32 numTStates);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
