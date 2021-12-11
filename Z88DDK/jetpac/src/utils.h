#ifndef _UTILS_H_
#define _UTILS_H_

#include "defn.h"
#include "speccy.h"

// Routines.

extern  void    ClearDisplay (UINT8 row, 
                              UINT8 column, 
                              UINT8 width, 
                              UINT8 height,
                              UINT8 colour);
extern  void    PrintAt (UINT8  row, 
                         UINT8  column, 
                         char*  text,
                         UINT8  colour);
extern  void    PrintUDGAt (UINT8   row, 
                            UINT8   column, 
                            UDG     udgData,
                            UINT8   numUDGs,
                            UINT8   colour);
extern  void    InitialiseDisplay ();

#endif

/******************************* End of File *******************************/
