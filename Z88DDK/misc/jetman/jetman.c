#pragma output REGISTER_SP = 0xD000

#include <arch/zx.h>
#include <arch/zx/sp1.h>
//#include <intrinsic.h>
#include <z80.h>
#include <input.h>
#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>

// Masked sprite 2.
#define SPRITE_GUARD_SIZE 7

typedef struct _JetmanSprite
{
    unsigned char    m_byWidth;
    unsigned char    m_byHeight;
    unsigned char    m_pbyGuard [2 * SPRITE_GUARD_SIZE];
    unsigned char    m_pbyWalkingRight [64 * 2 * 4];
    unsigned char    m_pbyWalkingLeft [64 * 2 * 4];
    unsigned char    m_pbyFlyingRight [64 * 2 * 4];
    unsigned char    m_pbyFlyingLeft [64 * 2 * 4];
} JetmanSprite;

typedef struct _MaskedSprite2
{
    unsigned char    m_byWidth;
    unsigned char    m_byHeight;
    unsigned char    m_pbyGuard [2 * SPRITE_GUARD_SIZE];
    unsigned char    m_pbyRight [12 * 16];
    unsigned char    m_pbyLeft [12 * 16];
} MaskedSprite2;

#include "SpriteData.h"

struct sp1_Rect full_screen = {0, 0, 32, 24};

typedef struct
{
  unsigned char *graphicWalk;
  unsigned char *graphicFly;
} JETMAN_SPRITE;

#define MOVING_RIGHT 0
#define MOVING_LEFT  1

JETMAN_SPRITE  jetman_state[] = 
{
    {g_jetman.m_pbyWalkingRight, g_jetman.m_pbyFlyingRight},
    {g_jetman.m_pbyWalkingLeft, g_jetman.m_pbyFlyingLeft},
};

typedef struct
{
  struct sp1_ss  *sprite;
  unsigned char *graphic[2];
  int   state;
  int   animation_offset;
  int   x_pos;
  int   y_pos;
  int   x_inc;
  int   y_inc;
} NASTY_SPRITE;

#define NUM_NASTY_SPRITES  6

NASTY_SPRITE nasty_sprite[NUM_NASTY_SPRITES];

#define JETMAN_DELTA 2
#define NASTY_SPRITE_DELTA 4

unsigned char g_colour;

void initialiseColour(unsigned int count, struct sp1_cs *c)
{
  (void)count;    // Suppress compiler warning about unused parameter

  c->attr_mask = SP1_AMASK_INK & SP1_AMASK_PAPER;
  c->attr      = BRIGHT | g_colour;
}

int main()
{
  zx_border(INK_BLUE);

  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_BLACK | PAPER_BLACK,
                  ' ' );
  sp1_Invalidate(&full_screen);
  sp1_UpdateNow();
 
  struct sp1_ss  *jetman_sprite = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, g_jetman.m_byHeight + 1, 0, 0);
  sp1_AddColSpr(jetman_sprite, SP1_DRAW_MASK2, SP1_TYPE_2BYTE, 2 * (g_jetman.m_byHeight + 1) * 8, 0);
  sp1_AddColSpr(jetman_sprite, SP1_DRAW_MASK2RB, SP1_TYPE_2BYTE, 0, 0);
  g_colour = 7;
  sp1_IterateSprChar(jetman_sprite, initialiseColour); 

  srand ((int) (jetman_sprite));

  for(unsigned char i=0; i<NUM_NASTY_SPRITES; i++ )
  {
      nasty_sprite[i].sprite = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, g_nastyMeteor.m_byHeight + 1, 0, 0);
      sp1_AddColSpr(nasty_sprite[i].sprite, SP1_DRAW_MASK2, SP1_TYPE_2BYTE, 2 * (g_nastyMeteor.m_byHeight + 1) * 8, 0);
      sp1_AddColSpr(nasty_sprite[i].sprite, SP1_DRAW_MASK2RB, SP1_TYPE_2BYTE, 0, 0);

      g_colour = 2 + rand () % (3 + 1);

      sp1_IterateSprChar(nasty_sprite[i].sprite, initialiseColour); 

      nasty_sprite[i].animation_offset = 0;
      nasty_sprite[i].state = 0;
      nasty_sprite[i].graphic[0] = g_nastyMeteor.m_pbyRight;
      nasty_sprite[i].graphic[1] = g_nastyMeteor.m_pbyLeft;
      nasty_sprite[i].x_pos = rand () % (255 + 1);
      nasty_sprite[i].y_pos = rand () % (192 + 1);
      nasty_sprite[i].x_inc = rand () % 2 ? NASTY_SPRITE_DELTA : -NASTY_SPRITE_DELTA;
      nasty_sprite[i].y_inc = rand () % 2 ? NASTY_SPRITE_DELTA : -NASTY_SPRITE_DELTA;
  }


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

        if (nasty_sprite[loop].y_pos < 0)
        {
            nasty_sprite[loop].y_pos = 0;
            nasty_sprite[loop].y_inc = NASTY_SPRITE_DELTA;
        }

        else
        if (nasty_sprite[loop].y_pos > 192-16)
        {
            nasty_sprite[loop].y_pos = 192-16;
            nasty_sprite[loop].y_inc = -NASTY_SPRITE_DELTA;
        }

        if (nasty_sprite[loop].x_pos < 0)
        {
            nasty_sprite[loop].state = MOVING_RIGHT;
            nasty_sprite[loop].x_pos = 0;
            nasty_sprite[loop].x_inc = NASTY_SPRITE_DELTA;
        }
        else
        if (nasty_sprite[loop].x_pos > 256-16)
        {
            nasty_sprite[loop].state = MOVING_LEFT;
            nasty_sprite[loop].x_pos = 256-16;
            nasty_sprite[loop].x_inc = -NASTY_SPRITE_DELTA;
        }
        sp1_MoveSprPix (nasty_sprite[loop].sprite, &full_screen, &(nasty_sprite[loop].graphic[nasty_sprite[loop].state][nasty_sprite[loop].animation_offset]), nasty_sprite[loop].x_pos, nasty_sprite[loop].y_pos);
        nasty_sprite[loop].y_pos += nasty_sprite[loop].y_inc;
        nasty_sprite[loop].x_pos += nasty_sprite[loop].x_inc;
        nasty_sprite[loop].animation_offset += 96;
        if (nasty_sprite[loop].animation_offset >= 96*2)
            nasty_sprite[loop].animation_offset = 0;

        if (++loop >= NUM_NASTY_SPRITES)
            loop = 0;

        if (bMoving)
        {
            bMoving = 0;

            //struct sp1_Rect clip = {y/8, x/8, 2 + 1, 3 + 1};

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