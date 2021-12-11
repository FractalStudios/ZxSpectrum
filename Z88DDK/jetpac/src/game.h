#ifndef _GAME_H_
#define _GAME_H_

#include "defn.h"

// Definitions and Types.

// Score BDC digits.
#define NUM_SCORE_BCD_DIGITS    6

// Score text.
typedef  char   ScoreText [NUM_SCORE_BCD_DIGITS + 1];

// Routines.

extern  void    DisplayMainMenuScreen ();
extern  void    DisplayGameScreen (UINT8 currentPlayer);
extern  void    DisplayGameOverScreen (UINT8 currentPlayer);

#endif

/******************************* End of File *******************************/
