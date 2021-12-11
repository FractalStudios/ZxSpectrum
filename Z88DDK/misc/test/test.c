#pragma output REGISTER_SP = 0xD000

#include <arch/zx.h>
#include <arch/zx/sp1.h>
#include <intrinsic.h>
#include <z80.h>
#include <im2.h>
#include <input.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define clock(x)	(*tick)
unsigned char *tick = 0x5c78;
unsigned char timer = 0;

#ifndef WFRAMES
#define WFRAMES		4
#endif // WFRAMES

void    wait ()
{
	while ((*tick - timer) < WFRAMES)
    {
        intrinsic_halt();
    }
	timer = *tick;
}


IM2_DEFINE_ISR(isr) 
{
	// update the clock
	(*tick)++;
}
#define TABLE_HIGH_BYTE        ((unsigned int)0xD0)
#define JUMP_POINT_HIGH_BYTE   ((unsigned int)0xD1)

#define UI_256                 ((unsigned int)256)
#define TABLE_ADDR             ((void*)(TABLE_HIGH_BYTE*UI_256))
#define JUMP_POINT             ((unsigned char*)( (unsigned int)(JUMP_POINT_HIGH_BYTE*UI_256) + JUMP_POINT_HIGH_BYTE ))


unsigned char g_colour = 0;

void initialiseColour(unsigned int count, struct sp1_cs *c)
{
  (void)count;    /* Suppress compiler warning about unused parameter */

  c->attr_mask = SP1_AMASK_INK | SP1_AMASK_PAPER;
  c->attr      = BRIGHT | g_colour;
}
extern unsigned char bubble_col1[];
extern unsigned char bubble_col2[];

struct sp1_Rect full_screen = {0, 0, 32, 24};


typedef struct
{
  struct sp1_ss  *sprite;
  int   x_pos;
  int   y_pos;
  //int   x_inc;
  //int   y_inc;
} CIRCLE_SPRITE;

#define NUM_SPRITES  2

CIRCLE_SPRITE circle_sprites[NUM_SPRITES];

#define INC 1

int main()
{
  unsigned char i;

  memset( TABLE_ADDR, JUMP_POINT_HIGH_BYTE, 257 );
  z80_bpoke( JUMP_POINT,   195 );
  z80_wpoke( JUMP_POINT+1, (unsigned int)isr );
  im2_init( TABLE_ADDR );
  intrinsic_ei();

  zx_border(INK_BLUE);

  sp1_Initialize( SP1_IFLAG_MAKE_ROTTBL | SP1_IFLAG_OVERWRITE_TILES | SP1_IFLAG_OVERWRITE_DFILE,
                  INK_BLACK | PAPER_BLACK,
                  ' ' );
  sp1_Invalidate(&full_screen);         
  sp1_UpdateNow();
 
  srand (*tick);

  int   spriteWidthInPixels     = 16;
  int   spriteHeightInPixels    = (bubble_col2 - bubble_col1 - 16) / 2;

  int   spriteMaxX = 256 - spriteWidthInPixels;
  int   spriteMaxY = 192 - spriteHeightInPixels;

  for( i=0; i<NUM_SPRITES; i++ )
  {
      if (i == 0)
      {
          circle_sprites[i].sprite = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, spriteHeightInPixels / 8 + 1, (int)bubble_col1, 0);
          sp1_AddColSpr(circle_sprites[i].sprite, SP1_DRAW_MASK2, SP1_TYPE_2BYTE,(int)bubble_col2, 0);
          sp1_AddColSpr(circle_sprites[i].sprite, SP1_DRAW_MASK2RB, SP1_TYPE_2BYTE, 0, 0);
      }
      else
      {
          circle_sprites[i].sprite = sp1_CreateSpr(SP1_DRAW_MASK2LB, SP1_TYPE_2BYTE, spriteHeightInPixels / 8 + 1, (int)bubble_col2, 0);
          sp1_AddColSpr(circle_sprites[i].sprite, SP1_DRAW_MASK2RB, SP1_TYPE_2BYTE, 0, 0);
      }
    circle_sprites[i].x_pos = 10;//200;//rand () % (255 + 1);
    circle_sprites[i].y_pos = 10;//80;//rand () % (192 + 1);
    //circle_sprites[i].x_inc = rand () % 2 ? INC : -INC;
    //circle_sprites[i].y_inc = rand () % 2 ? INC : -INC;

    g_colour = 1 + rand () % (6 + 1) | PAPER_BLUE;
    g_colour = INK_WHITE | PAPER_BLUE;
    sp1_IterateSprChar(circle_sprites[i].sprite, initialiseColour);  
  }


  i = 0;
  int xRot = 0;
  sp1_MoveSprAbs(circle_sprites[i].sprite, &full_screen, 0, 10, 10, 0, xRot);
  sp1_UpdateNow();
  while(1)
  {
/*    if (circle_sprites[i].y_pos < 0)
    {
        circle_sprites[i].y_pos = 0;
        circle_sprites[i].y_inc = INC;
    }
    else
    if (circle_sprites[i].y_pos > spriteMaxY)
    {
        circle_sprites[i].y_pos = spriteMaxY - 1;
        circle_sprites[i].y_inc = -INC;
    }
  
    if (circle_sprites[i].x_pos < 0)
    {
        circle_sprites[i].x_pos = 0;
        //circle_sprites[i].x_inc = INC;
    }
    else
    if (circle_sprites[i].x_pos > 210)
    {
        sp1_MoveSprRel(circle_sprites[i].sprite, &full_screen, 0, 0, 1, 0, 7);

        //circle_sprites[i].x_pos = -10;
        //circle_sprites[i].x_inc = -INC;
    }
    else
    {
        sp1_MoveSprRel(circle_sprites[i].sprite, &full_screen, 0, 0, 1, 0, 7);
    }
    */       

    if (in_key_pressed (IN_KEY_SCANCODE_p) == 0xFFFF) 
    {
        // Right.

        if (++xRot > 7)
        {
            xRot = 0;
            circle_sprites[i].x_pos++;
        }
        sp1_MoveSprAbs(circle_sprites[i].sprite, &full_screen, 0, circle_sprites[i].y_pos, circle_sprites[i].x_pos, 0, xRot);

        if (circle_sprites[i].x_pos == 31)
        {
            circle_sprites[1].x_pos = 0;
            sp1_MoveSprAbs(circle_sprites[1].sprite, &full_screen, 0, circle_sprites[1].y_pos, circle_sprites[1].x_pos, 0, 0);
        }
        sp1_UpdateNow();
        z80_delay_ms(10);
    }
    else
    if (in_key_pressed (IN_KEY_SCANCODE_o) == 0xFFFF) 
    {
        // Left.

        if (--xRot < 0)
        {
            xRot = 7;
            circle_sprites[i].x_pos--;
        }
        sp1_MoveSprAbs(circle_sprites[i].sprite, &full_screen, 0, circle_sprites[i].y_pos, circle_sprites[i].x_pos, 0, xRot);
        sp1_UpdateNow();
        z80_delay_ms(10);
    }

    
    //circle_sprites[i].y_pos += circle_sprites[i].y_inc;
    //circle_sprites[i].x_pos++;//= circle_sprites[i].x_inc;
    //if (++i == NUM_SPRITES)
    //    i = 0;
  }
}