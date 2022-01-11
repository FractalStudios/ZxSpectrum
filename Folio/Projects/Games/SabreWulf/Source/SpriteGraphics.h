#pragma once

// "Home-made" includes.
#include    <Game.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Sprite identifier enumeration.
enum SPRITE_ID
{
    SPRITE_BOX                          = IDB_BITMAP_BOX,                               // 16 x 16.
    SPRITE_RING                         = IDB_BITMAP_RING,                              // 16 x 16.
    SPRITE_APPLE                        = IDB_BITMAP_APPLE,                             // 16 x 16.
    SPRITE_CHARM                        = IDB_BITMAP_CHARM,                             // 16 x 16.
    SPRITE_AMULET                       = IDB_BITMAP_AMULET,                            // 16 x 16.
    SPRITE_EXTRA_LIFE                   = IDB_BITMAP_EXTRA_LIFE,                        // 16 x 16.
    SPRITE_MONEY_BAG                    = IDB_BITMAP_MONEY_BAG,                         // 16 x 16.
    SPRITE_SPEAR                        = IDB_BITMAP_SPEAR,                             // 16 x 16.
    SPRITE_CHALICE                      = IDB_BITMAP_CHALICE,                           // 16 x 16.
    SPRITE_AMULET_PIECE_TOP_LEFT        = IDB_BITMAP_AMULET_PIECE_TOP_LEFT,             // 16 x 16.     
    SPRITE_AMULET_PIECE_TOP_RIGHT       = IDB_BITMAP_AMULET_PIECE_TOP_RIGHT,            // 16 x 16.     
    SPRITE_AMULET_PIECE_BOTTOM_LEFT     = IDB_BITMAP_AMULET_PIECE_BOTTOM_LEFT,          // 16 x 16.
    SPRITE_AMULET_PIECE_BOTTOM_RIGHT    = IDB_BITMAP_AMULET_PIECE_BOTTOM_RIGHT,         // 16 x 16.     
    
    SPRITE_ORCHID_1                     = IDB_BITMAP_ORCHID_1,                          // 24 x 16.
    SPRITE_ORCHID_2                     = IDB_BITMAP_ORCHID_2,                          // 24 x 16.
    SPRITE_ORCHID_3                     = IDB_BITMAP_ORCHID_3,                          // 24 x 16.
    SPRITE_ORCHID_4                     = IDB_BITMAP_ORCHID_4,                          // 24 x 16.
    SPRITE_ORCHID_5                     = IDB_BITMAP_ORCHID_5,                          // 24 x 16.
    SPRITE_ORCHID_6                     = IDB_BITMAP_ORCHID_6,                          // 24 x 16.
    SPRITE_ORCHID_7                     = IDB_BITMAP_ORCHID_7,                          // 24 x 16.
    SPRITE_ORCHID_8                     = IDB_BITMAP_ORCHID_8,                          // 24 x 16.

    SPRITE_SABRE_MAN_UP                 = IDB_BITMAP_SABRE_MAN_UP,                      // 16 x 21.
    SPRITE_SABRE_MAN_WALKING_UP_1       = IDB_BITMAP_SABRE_MAN_WALKING_UP_1,            // 16 x 21.
    SPRITE_SABRE_MAN_WALKING_UP_2       = IDB_BITMAP_SABRE_MAN_WALKING_UP_2,            // 16 x 21.
    SPRITE_SABRE_MAN_DOWN               = IDB_BITMAP_SABRE_MAN_DOWN,                    // 16 x 21.
    SPRITE_SABRE_MAN_WALKING_DOWN_1     = IDB_BITMAP_SABRE_MAN_WALKING_DOWN_1,          // 16 x 21.
    SPRITE_SABRE_MAN_WALKING_DOWN_2     = IDB_BITMAP_SABRE_MAN_WALKING_DOWN_2,          // 16 x 21.
    SPRITE_SABRE_MAN_LEFT               = IDB_BITMAP_SABRE_MAN_LEFT,                    // 16 x 21.
    SPRITE_SABRE_MAN_WALKING_LEFT_1     = IDB_BITMAP_SABRE_MAN_WALKING_LEFT_1,          // 16 x 21.
    SPRITE_SABRE_MAN_WALKING_LEFT_2     = IDB_BITMAP_SABRE_MAN_WALKING_LEFT_2,          // 16 x 21.
    SPRITE_SABRE_MAN_RIGHT              = IDB_BITMAP_SABRE_MAN_RIGHT,                   // 16 x 21.
    SPRITE_SABRE_MAN_WALKING_RIGHT_1    = IDB_BITMAP_SABRE_MAN_WALKING_RIGHT_1,         // 16 x 21.
    SPRITE_SABRE_MAN_WALKING_RIGHT_2    = IDB_BITMAP_SABRE_MAN_WALKING_RIGHT_2,         // 16 x 21.

    SPRITE_SABRE_MAN_SWORD_LEFT_1       = IDB_BITMAP_SABRE_MAN_SWORD_LEFT_1,            // 24 x 21.
    SPRITE_SABRE_MAN_SWORD_LEFT_2       = IDB_BITMAP_SABRE_MAN_SWORD_LEFT_2,            // 24 x 21.
    SPRITE_SABRE_MAN_SWORD_LEFT_3       = IDB_BITMAP_SABRE_MAN_SWORD_LEFT_3,            // 24 x 21.
    SPRITE_SABRE_MAN_SWORD_LEFT_4       = IDB_BITMAP_SABRE_MAN_SWORD_LEFT_4,            // 24 x 21.
    SPRITE_SABRE_MAN_SWORD_LEFT_5       = IDB_BITMAP_SABRE_MAN_SWORD_LEFT_5,            // 24 x 21.
    SPRITE_SABRE_MAN_SWORD_LEFT_6       = IDB_BITMAP_SABRE_MAN_SWORD_LEFT_6,            // 24 x 21.
    SPRITE_SABRE_MAN_SWORD_RIGHT_1      = IDB_BITMAP_SABRE_MAN_SWORD_RIGHT_1,           // 24 x 21.
    SPRITE_SABRE_MAN_SWORD_RIGHT_2      = IDB_BITMAP_SABRE_MAN_SWORD_RIGHT_2,           // 24 x 21.
    SPRITE_SABRE_MAN_SWORD_RIGHT_3      = IDB_BITMAP_SABRE_MAN_SWORD_RIGHT_3,           // 24 x 21.
    SPRITE_SABRE_MAN_SWORD_RIGHT_4      = IDB_BITMAP_SABRE_MAN_SWORD_RIGHT_4,           // 24 x 21.
    SPRITE_SABRE_MAN_SWORD_RIGHT_5      = IDB_BITMAP_SABRE_MAN_SWORD_RIGHT_5,           // 24 x 21.
    SPRITE_SABRE_MAN_SWORD_RIGHT_6      = IDB_BITMAP_SABRE_MAN_SWORD_RIGHT_6,           // 24 x 21.
    
    SPRITE_SABRE_MAN_FALLING_LEFT       = IDB_BITMAP_SABRE_MAN_FALLING_LEFT,            // 16 x 21.
    SPRITE_SABRE_MAN_FALLING_RIGHT      = IDB_BITMAP_SABRE_MAN_FALLING_RIGHT,           // 16 x 21.

    SPRITE_SABRE_MAN_SITTING_LEFT       = IDB_BITMAP_SABRE_MAN_SITTING_LEFT,            // 16 x 21.
    SPRITE_SABRE_MAN_SITTING_RIGHT      = IDB_BITMAP_SABRE_MAN_SITTING_RIGHT,           // 16 x 21

    SPRITE_SABRE_MAN_LYING_DEAD_LEFT    = IDB_BITMAP_SABRE_MAN_LYING_DEAD_LEFT,         // 24 x 21.
    SPRITE_SABRE_MAN_LYING_DEAD_RIGHT   = IDB_BITMAP_SABRE_MAN_LYING_DEAD_RIGHT,        // 24 x 21.

    SPRITE_WOLF_WALKING_LEFT_1          = IDB_BITMAP_WOLF_WALKING_LEFT_1,               // 32 x 24.
    SPRITE_WOLF_WALKING_LEFT_2          = IDB_BITMAP_WOLF_WALKING_LEFT_2,               // 32 x 24.
    SPRITE_WOLF_WALKING_LEFT_3          = IDB_BITMAP_WOLF_WALKING_LEFT_3,               // 32 x 24.
    SPRITE_WOLF_WALKING_RIGHT_1         = IDB_BITMAP_WOLF_WALKING_RIGHT_1,              // 32 x 24.
    SPRITE_WOLF_WALKING_RIGHT_2         = IDB_BITMAP_WOLF_WALKING_RIGHT_2,              // 32 x 24.
    SPRITE_WOLF_WALKING_RIGHT_3         = IDB_BITMAP_WOLF_WALKING_RIGHT_3,              // 32 x 24.

    SPRITE_WOLF_JUMPING_LEFT_1          = IDB_BITMAP_WOLF_JUMPING_LEFT_1,               // 32 x 24.
    SPRITE_WOLF_JUMPING_LEFT_2          = IDB_BITMAP_WOLF_JUMPING_LEFT_2,               // 32 x 24.
    SPRITE_WOLF_JUMPING_RIGHT_1         = IDB_BITMAP_WOLF_JUMPING_RIGHT_1,              // 32 x 24.
    SPRITE_WOLF_JUMPING_RIGHT_2         = IDB_BITMAP_WOLF_JUMPING_RIGHT_2,              // 32 x 24.

    SPRITE_RHINOCEROS_RUNNING_LEFT_1    = IDB_BITMAP_RHINOCEROS_RUNNING_LEFT_1,         // 32 x 19.
    SPRITE_RHINOCEROS_RUNNING_LEFT_2    = IDB_BITMAP_RHINOCEROS_RUNNING_LEFT_2,         // 32 x 19.
    SPRITE_RHINOCEROS_RUNNING_RIGHT_1   = IDB_BITMAP_RHINOCEROS_RUNNING_RIGHT_1,        // 32 x 19.
    SPRITE_RHINOCEROS_RUNNING_RIGHT_2   = IDB_BITMAP_RHINOCEROS_RUNNING_RIGHT_2,        // 32 x 19.

    SPRITE_HIPPOPOTAMUS_RUNNING_LEFT_1  = IDB_BITMAP_HIPPOPOTAMUS_RUNNING_LEFT_1,       // 32 x 24.
    SPRITE_HIPPOPOTAMUS_RUNNING_LEFT_2  = IDB_BITMAP_HIPPOPOTAMUS_RUNNING_LEFT_2,       // 32 x 24.
    SPRITE_HIPPOPOTAMUS_RUNNING_RIGHT_1 = IDB_BITMAP_HIPPOPOTAMUS_RUNNING_RIGHT_1,      // 32 x 24.
    SPRITE_HIPPOPOTAMUS_RUNNING_RIGHT_2 = IDB_BITMAP_HIPPOPOTAMUS_RUNNING_RIGHT_2,      // 32 x 24.
    SPRITE_HIPPOPOTAMUS_SLEEPING        = IDB_BITMAP_HIPPOPOTAMUS_SLEEPING,             // 24 x 24.

    SPRITE_WARTHOG_RUNNING_LEFT_1       = IDB_BITMAP_WARTHOG_RUNNING_LEFT_1,            // 32 x 21.   
    SPRITE_WARTHOG_RUNNING_LEFT_2       = IDB_BITMAP_WARTHOG_RUNNING_LEFT_2,            // 32 x 21.   
    SPRITE_WARTHOG_RUNNING_RIGHT_1      = IDB_BITMAP_WARTHOG_RUNNING_RIGHT_1,           // 32 x 21.   
    SPRITE_WARTHOG_RUNNING_RIGHT_2      = IDB_BITMAP_WARTHOG_RUNNING_RIGHT_2,           // 32 x 21.   
    SPRITE_WARTHOG_SLEEPING             = IDB_BITMAP_WARTHOG_SLEEPING,                  // 24 x 21.   

    SPRITE_NATIVE_LEFT_1                = IDB_BITMAP_NATIVE_LEFT_1,                     // 16 x 23. 
    SPRITE_NATIVE_LEFT_2                = IDB_BITMAP_NATIVE_LEFT_2,                     // 16 x 23. 
    SPRITE_NATIVE_LEFT_3                = IDB_BITMAP_NATIVE_LEFT_3,                     // 16 x 23. 
    SPRITE_NATIVE_RIGHT_1               = IDB_BITMAP_NATIVE_RIGHT_1,                    // 16 x 23. 
    SPRITE_NATIVE_RIGHT_2               = IDB_BITMAP_NATIVE_RIGHT_2,                    // 16 x 23. 
    SPRITE_NATIVE_RIGHT_3               = IDB_BITMAP_NATIVE_RIGHT_3,                    // 16 x 23. 

    SPRITE_GUARDIAN_1                   = IDB_BITMAP_GUARDIAN_1,                        // 32 x 32.
    SPRITE_GUARDIAN_2                   = IDB_BITMAP_GUARDIAN_2,                        // 32 x 32.

    SPRITE_FIRE_1                       = IDB_BITMAP_FIRE_1,                            // 16 x 23.
    SPRITE_FIRE_2                       = IDB_BITMAP_FIRE_2,                            // 16 x 23.
    SPRITE_FIRE_3                       = IDB_BITMAP_FIRE_3,                            // 16 x 23.
    SPRITE_FIRE_4                       = IDB_BITMAP_FIRE_4,                            // 16 x 23.

    SPRITE_NASTY_ALIVE_1                = IDB_BITMAP_NASTY_ALIVE_1,                     // 24 x 23.          
    SPRITE_NASTY_ALIVE_2                = IDB_BITMAP_NASTY_ALIVE_2,                     // 24 x 23.          
    SPRITE_NASTY_ALIVE_3                = IDB_BITMAP_NASTY_ALIVE_3,                     // 24 x 23.          
    SPRITE_NASTY_ALIVE_4                = IDB_BITMAP_NASTY_ALIVE_4,                     // 24 x 23.          
    SPRITE_NASTY_ALIVE_5                = IDB_BITMAP_NASTY_ALIVE_5,                     // 24 x 23.           
    SPRITE_NASTY_ALIVE_6                = IDB_BITMAP_NASTY_ALIVE_6,                     // 24 x 23.           

    SPRITE_NASTY_DEAD_1                 = IDB_BITMAP_NASTY_DEAD_1,                      // 24 x 24.           
    SPRITE_NASTY_DEAD_2                 = IDB_BITMAP_NASTY_DEAD_2,                      // 24 x 24.           
    SPRITE_NASTY_DEAD_3                 = IDB_BITMAP_NASTY_DEAD_3,                      // 24 x 24.           
    SPRITE_NASTY_DEAD_4                 = IDB_BITMAP_NASTY_DEAD_4,                      // 24 x 24.

    SPRITE_SPIDER_LEFT_1                = IDB_BITMAP_SPIDER_LEFT_1,                     // 24 x 22.                   
    SPRITE_SPIDER_LEFT_2                = IDB_BITMAP_SPIDER_LEFT_2,                     // 24 x 22.           
    SPRITE_SPIDER_RIGHT_1               = IDB_BITMAP_SPIDER_RIGHT_1,                    // 24 x 22.           
    SPRITE_SPIDER_RIGHT_2               = IDB_BITMAP_SPIDER_RIGHT_2,                    // 24 x 22.           

    SPRITE_SCORPION_LEFT_1              = IDB_BITMAP_SCORPION_LEFT_1,                   // 24 x 21.           
    SPRITE_SCORPION_LEFT_2              = IDB_BITMAP_SCORPION_LEFT_2,                   // 24 x 21.           
    SPRITE_SCORPION_RIGHT_1             = IDB_BITMAP_SCORPION_RIGHT_1,                  // 24 x 21.           
    SPRITE_SCORPION_RIGHT_2             = IDB_BITMAP_SCORPION_RIGHT_2,                  // 24 x 21.           

    SPRITE_BAT_LEFT_1                   = IDB_BITMAP_BAT_LEFT_1,                        // 16 x 17.           
    SPRITE_BAT_LEFT_2                   = IDB_BITMAP_BAT_LEFT_2,                        // 16 x 17.           
    SPRITE_BAT_RIGHT_1                  = IDB_BITMAP_BAT_RIGHT_1,                       // 16 x 17.           
    SPRITE_BAT_RIGHT_2                  = IDB_BITMAP_BAT_RIGHT_2,                       // 16 x 17.           

    SPRITE_PARROT_LEFT_1                = IDB_BITMAP_PARROT_LEFT_1,                     // 16 x 19.           
    SPRITE_PARROT_LEFT_2                = IDB_BITMAP_PARROT_LEFT_2,                     // 16 x 19.           
    SPRITE_PARROT_RIGHT_1               = IDB_BITMAP_PARROT_RIGHT_1,                    // 16 x 19.           
    SPRITE_PARROT_RIGHT_2               = IDB_BITMAP_PARROT_RIGHT_2,                    // 16 x 19.           

    SPRITE_MONKEY_LEFT_1                = IDB_BITMAP_MONKEY_LEFT_1,                     // 16 x 21.           
    SPRITE_MONKEY_LEFT_2                = IDB_BITMAP_MONKEY_LEFT_2,                     // 16 x 21.           
    SPRITE_MONKEY_RIGHT_1               = IDB_BITMAP_MONKEY_RIGHT_1,                    // 16 x 21.           
    SPRITE_MONKEY_RIGHT_2               = IDB_BITMAP_MONKEY_RIGHT_2,                    // 16 x 21.           
    
    SPRITE_LIZARD_LEFT_1                = IDB_BITMAP_LIZARD_LEFT_1,                     // 24 x 13.           
    SPRITE_LIZARD_LEFT_2                = IDB_BITMAP_LIZARD_LEFT_2,                     // 24 x 13.           
    SPRITE_LIZARD_RIGHT_1               = IDB_BITMAP_LIZARD_RIGHT_1,                    // 24 x 13.           
    SPRITE_LIZARD_RIGHT_2               = IDB_BITMAP_LIZARD_RIGHT_2,                    // 24 x 13.           
    
    SPRITE_SNAKE_LEFT_1                 = IDB_BITMAP_SNAKE_LEFT_1,                      // 24 x 13.           
    SPRITE_SNAKE_LEFT_2                 = IDB_BITMAP_SNAKE_LEFT_2,                      // 24 x 13.           
    SPRITE_SNAKE_RIGHT_1                = IDB_BITMAP_SNAKE_RIGHT_1,                     // 24 x 13.           
    SPRITE_SNAKE_RIGHT_2                = IDB_BITMAP_SNAKE_RIGHT_2,                     // 24 x 13.           

    SPRITE_RAT_LEFT_1                   = IDB_BITMAP_RAT_LEFT_1,                        // 24 x 9.           
    SPRITE_RAT_LEFT_2                   = IDB_BITMAP_RAT_LEFT_2,                        // 24 x 9.           
    SPRITE_RAT_RIGHT_1                  = IDB_BITMAP_RAT_RIGHT_1,                       // 24 x 9.           
    SPRITE_RAT_RIGHT_2                  = IDB_BITMAP_RAT_RIGHT_2,                       // 24 x 9.           
    
    SPRITE_BIRD_LEFT_1                  = IDB_BITMAP_BIRD_LEFT_1,                       // 24 x 22.           
    SPRITE_BIRD_LEFT_2                  = IDB_BITMAP_BIRD_LEFT_2,                       // 24 x 22.           
    SPRITE_BIRD_RIGHT_1                 = IDB_BITMAP_BIRD_RIGHT_1,                      // 24 x 22.           
    SPRITE_BIRD_RIGHT_2                 = IDB_BITMAP_BIRD_RIGHT_2,                      // 24 x 22.           
    
    SPRITE_FLY_LEFT_1                   = IDB_BITMAP_FLY_LEFT_1,                        // 16 x 16.           
    SPRITE_FLY_LEFT_2                   = IDB_BITMAP_FLY_LEFT_2,                        // 16 x 16.           
    SPRITE_FLY_RIGHT_1                  = IDB_BITMAP_FLY_RIGHT_1,                       // 16 x 16.           
    SPRITE_FLY_RIGHT_2                  = IDB_BITMAP_FLY_RIGHT_2,                       // 16 x 16.           
    
    SPRITE_FROG_LEFT_1                  = IDB_BITMAP_FROG_LEFT_1,                       // 24 x 12.           
    SPRITE_FROG_LEFT_2                  = IDB_BITMAP_FROG_LEFT_2,                       // 24 x 12.           
    SPRITE_FROG_RIGHT_1                 = IDB_BITMAP_FROG_RIGHT_1,                      // 24 x 12.           
    SPRITE_FROG_RIGHT_2                 = IDB_BITMAP_FROG_RIGHT_2,                      // 24 x 12.           

    SPRITE_BUG_LEFT_1                   = IDB_BITMAP_BUG_LEFT_1,                        // 16 x 16.           
    SPRITE_BUG_LEFT_2                   = IDB_BITMAP_BUG_LEFT_2,                        // 16 x 16.           
    SPRITE_BUG_RIGHT_1                  = IDB_BITMAP_BUG_RIGHT_1,                       // 16 x 16.           
    SPRITE_BUG_RIGHT_2                  = IDB_BITMAP_BUG_RIGHT_2,                       // 16 x 16.           

    SPRITE_SKUNK_LEFT_1                 = IDB_BITMAP_SKUNK_LEFT_1,                      // 24 x 20.        
    SPRITE_SKUNK_LEFT_2                 = IDB_BITMAP_SKUNK_LEFT_2,                      // 24 x 20.        
    SPRITE_SKUNK_RIGHT_1                = IDB_BITMAP_SKUNK_RIGHT_1,                     // 24 x 20.        
    SPRITE_SKUNK_RIGHT_2                = IDB_BITMAP_SKUNK_RIGHT_2,                     // 24 x 20.        

    SPRITE_EARWIG_LEFT_1                = IDB_BITMAP_EARWIG_LEFT_1,                     // 24 x 18.           
    SPRITE_EARWIG_LEFT_2                = IDB_BITMAP_EARWIG_LEFT_2,                     // 24 x 18.           
    SPRITE_EARWIG_RIGHT_1               = IDB_BITMAP_EARWIG_RIGHT_1,                    // 24 x 18.           
    SPRITE_EARWIG_RIGHT_2               = IDB_BITMAP_EARWIG_RIGHT_2,                    // 24 x 18.
}; // Endenum.


// Routines.

extern  FolioStatus CreateSpriteGraphics (FolioHandle                               instanceHandle,
                                          Folio::Core::Game::ResourceGraphicsCache& resourceGraphicsCache);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
