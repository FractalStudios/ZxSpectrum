#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include "defn.h"

// Definitions and Types.

// Game selection.
typedef struct  _GameSelection
{
    BOOL    m_1PlayerGame;
    BOOL    m_keyboard;
} GameSelection;


// Globals.

// Game selection.
extern  GameSelection   g_gameSelection;

// Player 1 score.
extern  UINT32  g_player1Score;

// Player 2 score.
extern  UINT32  g_player2Score;

// Hi score.
extern  UINT32  g_hiScore;

// Current player (1 or 2).
extern  UINT8   g_currentPlayer;

#endif

/******************************* End of File *******************************/
