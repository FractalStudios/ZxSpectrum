#include "includes.h"
#include "globals.h"
#include "game.h"

// Platform.
#define MAX_NUM_PLATFORMS    4
#define PLATFORM_LHS    0
#define PLATFORM_MIDDLE 1
#define PLATFORM_RHS    2

typedef struct _Platform
{
    UINT8   m_row;
    UINT8   m_column;
    UINT8   m_width;
    UINT8   m_colour;
} Platform;


static  const   Platform    g_platform [] = 
{
    {  6, 24,  6, BRIGHT | INK_GREEN  | PAPER_BLACK },
    {  9,  4,  6, BRIGHT | INK_GREEN  | PAPER_BLACK },
    { 12, 15,  4, BRIGHT | INK_GREEN  | PAPER_BLACK },
    { 23,  0, 32, BRIGHT | INK_YELLOW | PAPER_BLACK },
};

static  const   UDG g_platformUDG [] = 
{ 
    { 0x2F, 0x7F, 0xFF, 0xDD, 0xFB, 0x7B, 0x71, 0x21 },
    { 0xBD, 0xFF, 0xFF, 0xF7, 0xEB, 0xDD, 0xAD, 0x04 },
    { 0x4C, 0xFE, 0xFF, 0x3E, 0xFF, 0xFE, 0x9C, 0x08 },
};

static  void    QueryScoreText (UINT32      score, 
                                ScoreText   scoreText)
{
    UINT8   byDigit = 0;    // Initialise!

    //iac
    scoreText [byDigit] = 0x00; // NULL terminate.
} // Endproc.


static  void    DisplayScore (UINT8     row, 
                              UINT8     column,
                              UINT32    score)
{
    // Query the score text.

    ScoreText   scoreText;

    QueryScoreText (score, scoreText);

    // Display the score text.

    PrintAt (row, column, scoreText, BRIGHT | INK_YELLOW | PAPER_BLACK);
} // Endproc.


static  void    DisplayPlayerSelections ()
{       
    PrintAt (7, 6, "1   1 PLAYER GAME", g_gameSelection.m_1PlayerGame ? FLASH | BRIGHT | INK_WHITE | PAPER_BLACK : BRIGHT | INK_WHITE | PAPER_BLACK);
    PrintAt (9, 6, "2   2 PLAYER GAME", !g_gameSelection.m_1PlayerGame ? FLASH | BRIGHT | INK_WHITE | PAPER_BLACK : BRIGHT | INK_WHITE | PAPER_BLACK);
} // Endproc.


static  void    DisplayControllerSelections ()
{                                                  
    PrintAt (11, 6, "3   KEYBOARD", g_gameSelection.m_keyboard ? FLASH | BRIGHT | INK_WHITE | PAPER_BLACK : BRIGHT | INK_WHITE | PAPER_BLACK);
    PrintAt (13, 6, "4   KEMPSTON JOYSTICK", !g_gameSelection.m_keyboard ? FLASH | BRIGHT | INK_WHITE | PAPER_BLACK : BRIGHT | INK_WHITE | PAPER_BLACK);
} // Endproc.


void    DisplayMainMenuScreen ()
{
    // Clear display (leave status panel).

    ClearDisplay (2, 0, 32, 22, BRIGHT | INK_BLACK | PAPER_BLACK);

    PrintAt (0, 3, "1UP", BRIGHT | INK_WHITE | PAPER_BLACK);
    PrintAt (0, 15, "HI", BRIGHT | INK_CYAN | PAPER_BLACK);
    PrintAt (0, 27, "2UP", BRIGHT | INK_WHITE | PAPER_BLACK);

    // Display player 1 score.
    
    DisplayScore (1, 1, g_player1Score);

    // Display player 2 score.

    DisplayScore (1, 13, g_player2Score);

    // Display HI score.
    
    DisplayScore (1, 25, g_hiScore);

    PrintAt (4, 6, "JETPAC GAME SELECTION", BRIGHT | INK_WHITE | PAPER_BLACK);
    
    // Display player selections.

    DisplayPlayerSelections ();

    // Display controller selections.

    DisplayControllerSelections ();

    PrintAt (19, 6, "5   START GAME", BRIGHT | INK_WHITE | PAPER_BLACK);
    PrintAt (23, 0, "\x7f", BRIGHT | INK_WHITE | PAPER_BLACK);  // Copyright.
    PrintAt (23, 1, "1983 A.C.G. ALL RIGHTS RESERVED", BRIGHT | INK_WHITE | PAPER_BLACK);

    // Get the main menu selections.

    UINT8   byKeyPress = 0; // Initialise!

    do
    {
        // Wait for keypress.

        in_wait_key ();

        // Get keypress.

        byKeyPress = in_inkey ();
        
        // Wait for no keypress.

        in_wait_nokey ();

        switch (byKeyPress)
        {
        case 0x31:  // Key 1.
            if (!g_gameSelection.m_1PlayerGame)
            {
                // Toggle the player selection.

                g_gameSelection.m_1PlayerGame = !g_gameSelection.m_1PlayerGame;

                DisplayPlayerSelections ();
            } // Endif.
            break;

        case 0x32:  // Key 2.
            if (g_gameSelection.m_1PlayerGame)
            {
                // Toggle the player selection.

                g_gameSelection.m_1PlayerGame = !g_gameSelection.m_1PlayerGame;

                DisplayPlayerSelections ();
            } // Endif.
            break;

        case 0x33:  // Key 3.
            if (!g_gameSelection.m_keyboard)
            {
                // Toggle the controller selection.

                g_gameSelection.m_keyboard = !g_gameSelection.m_keyboard;

                DisplayControllerSelections ();
            } // Endif.
            break;

        case 0x34:  // Key 4.
            if (g_gameSelection.m_keyboard)
            {
                // Toggle the controller selection.

                g_gameSelection.m_keyboard = !g_gameSelection.m_keyboard;

                DisplayControllerSelections ();
            } // Endif.
            break;

        default:
            break;
        } // Endswitch.

    } // Enddo.
    while (byKeyPress != 0x35); // Wait for key 5.
} // Endproc.


void    DisplayGameOverScreen (UINT8 currentPlayer)
{
    // Clear display (leave status panel).

    ClearDisplay (2, 0, 32, 22, BRIGHT | INK_BLACK | PAPER_BLACK);

    PrintAt (14, 7, "GAME OVER PLAYER", BRIGHT | INK_WHITE | PAPER_BLACK);
    PrintAt (14, 24, (currentPlayer == 1) ? "1" : "2", BRIGHT | INK_WHITE | PAPER_BLACK);

    in_wait_key ();
    in_wait_nokey ();
} // Endproc.


void    DisplayGameScreen (UINT8 currentPlayer)
{
    (void*) currentPlayer;

    // Clear display (leave status panel).

    ClearDisplay (2, 0, 32, 22, BRIGHT | INK_BLACK | PAPER_BLACK);

    for (UINT8 n = 0; n < MAX_NUM_PLATFORMS; ++n)
    {
        PrintUDGAt (g_platform [n].m_row, 
                    g_platform [n].m_column, 
                    g_platformUDG [PLATFORM_LHS], 
                    1, 
                    g_platform [n].m_colour);

        PrintUDGAt (g_platform [n].m_row, 
                    g_platform [n].m_column + 1, 
                    g_platformUDG [PLATFORM_MIDDLE], 
                    g_platform [n].m_width - 2, 
                    g_platform [n].m_colour);

        PrintUDGAt (g_platform [n].m_row, 
                    g_platform [n].m_column + 1 + g_platform [n].m_width - 2, 
                    g_platformUDG [PLATFORM_RHS], 
                    1, 
                    g_platform [n].m_colour);
    } // Endfor.

    in_wait_key ();
    in_wait_nokey ();
} // Endproc.

/******************************* End of File *******************************/
