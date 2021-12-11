#ifndef _DEFN_H_
#define _DEFN_H_

#include <z80.h>

// Definitions and Types.

// Language types.
typedef uint8_t     UINT8;      //  8 bits = 1 byte.
typedef uint16_t    UINT16;     // 16 bits = 2 bytes.
typedef uint32_t    UINT32;     // 32 bits = 4 bytes.
typedef uint64_t    UINT64;     // 64 bits = 8 bytes.

typedef int8_t      INT8;       //  8 bits = 1 byte.
typedef int16_t     INT16;      // 16 bits = 2 bytes.
typedef int32_t     INT32;      // 32 bits = 4 bytes.
typedef int64_t     INT64;      // 64 bits = 8 bytes.


// Boolean type.
typedef uint8_t     BOOL;       //  8 bits = 1 byte.
#define FALSE   0
#define TRUE    1

#endif

/******************************* End of File *******************************/
