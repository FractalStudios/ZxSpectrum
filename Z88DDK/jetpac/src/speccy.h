#ifndef _SPECCY_H_
#define _SPECCY_H_

#include "defn.h"

// Definitions and Types.

// Spectrum addresses.

#define ADDRESS_ROM_CHARACTER_SET   0x3c00

// Maximum rows and columns.
#define MAX_NUM_ROWS    24
#define MAX_NUM_COLUMNS 32

// Maximum X and Y pixels.
#define MAX_NUM_PIXELS_X    256
#define MAX_NUM_PIXELS_Y    192

// Maximum UDG size.
#define MAX_UDG_SIZE    8

// UDG type.
typedef  UINT8  UDG [MAX_UDG_SIZE];

#endif

/******************************* End of File *******************************/
