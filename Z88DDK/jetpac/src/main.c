#include "includes.h"
#include "game.h"
#include "globals.h"
#include "spritedata.h"

static  void    InitialiseGame ()
{
    // Initialise the display.

    InitialiseDisplay ();

    // Game selection.

    g_gameSelection.m_1PlayerGame   = TRUE;
    g_gameSelection.m_keyboard      = TRUE;

    // Player 1 score.
    
    g_player1Score = 0;

    // Player 2 score.
    
    g_player2Score = 0;

    // Hi score.

    g_hiScore = 0;

    // Current player.

    g_currentPlayer = 1;
} // Endproc.


void    Play ()
{
    struct sp1_Rect full_screen = {0, 0, 32, 24};

    sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                    INK_BLACK | PAPER_BLACK,
                    ' ' );
    sp1_Invalidate(&full_screen);
    sp1_UpdateNow();
 
    struct sp1_ss  *jetman_sprite = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, (g_jetman.m_maskedSpriteBase.m_heightInPixels / 8) + 1, 0, 0);
    sp1_AddColSpr(jetman_sprite, SP1_DRAW_MASK2, SP1_TYPE_2BYTE, 2 * (g_jetman.m_maskedSpriteBase.m_heightInPixels + 8), 0);
    sp1_AddColSpr(jetman_sprite, SP1_DRAW_MASK2RB, SP1_TYPE_2BYTE, 0, 0);
    g_colour = 7;
    sp1_IterateSprChar(jetman_sprite, initialiseColour); 

    srand ((int) (jetman_sprite));

    int x = 128;
    int y = 192-24;
    unsigned char state = MOVING_RIGHT;
    unsigned char bFlying = 0;
    unsigned char bMoving = 0;

    unsigned int  animation_offset = 0;

    sp1_MoveSprPix(jetman_sprite, &full_screen, &(jetman_state[state].graphicWalk [animation_offset]), x, y);
    sp1_UpdateNow();

    int loop = 0;
    while(1)
    { 
        if (in_key_pressed (IN_KEY_SCANCODE_p) == 0xFFFF) 
        {
            // Right.

            state = MOVING_RIGHT;
            bMoving = 1;

            x += JETMAN_DELTA;

            if (x > 256 - 16)
                x = 256 - 16;
        }
        else
        if (in_key_pressed (IN_KEY_SCANCODE_o) == 0xFFFF) 
        {
            // Left.

            state = MOVING_LEFT;
            bMoving = 1;

            x -= JETMAN_DELTA;

            if (x < 0)
                x = 0;
        }

        if (in_key_pressed (IN_KEY_SCANCODE_q) == 0xFFFF)
        {
            // Up.

            bFlying = 1;
            bMoving = 1;

            y -= JETMAN_DELTA;
            if (y < 0)
                y = 0;
        }
        else
        if (y != 192 - 24)
        {
            // Down.

            bFlying = 1;
            bMoving = 1;

            y += JETMAN_DELTA;
            if (y > 192 - 24)
                y = 192 - 24;
        }

        else
        if (bFlying)
        {
            // Not flying.

            bFlying = 0;
            bMoving = 1;
        } 

        if (bMoving)
        {
            bMoving = 0;

            sp1_MoveSprPix(jetman_sprite, &full_screen, bFlying ? &(jetman_state[state].graphicFly [animation_offset]) : &(jetman_state[state].graphicWalk [animation_offset]), x, y);

            animation_offset+=64*2;
            if (animation_offset >= 64*2*4)
                animation_offset = 0;
        }
        else
            z80_delay_ms(5);

        sp1_UpdateNow();
    }
 }

int main ()
{
    // Initialise the game.

    InitialiseGame ();

    while (1)
    {
        // Display the main menu screen.

        DisplayMainMenuScreen ();

        // Display the game screen.

        DisplayGameScreen (g_currentPlayer);

        Play ();

        // Display the game over screen.

        DisplayGameOverScreen (g_currentPlayer);
    } // Endwhile.

    return (0);
} // Endproc.

/******************************* End of File *******************************/
