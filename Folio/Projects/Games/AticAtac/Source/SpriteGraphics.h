#pragma once

// "Home-made" includes.
#include    <Game.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Sprite identifier enumeration.
enum SPRITE_ID
{
    SPRITE_UNDEFINED = Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_ID_UNDEFINED,
    SPRITE_LEAF                     = IDB_BITMAP_LEAF,                    
    SPRITE_KEY                      = IDB_BITMAP_KEY,                     
    SPRITE_BOTTLE                   = IDB_BITMAP_BOTTLE,                  
    SPRITE_MEDICINE_BOTTLE          = IDB_BITMAP_MEDICINE_BOTTLE,         
    SPRITE_BROKEN                   = IDB_BITMAP_BROKEN,                  
    SPRITE_ROPE                     = IDB_BITMAP_ROPE,                    
    SPRITE_ARM                      = IDB_BITMAP_ARM,                     
    SPRITE_BOWL                     = IDB_BITMAP_BOWL,                    
    SPRITE_APPLE                    = IDB_BITMAP_APPLE,                   
    SPRITE_CANDY_BAR                = IDB_BITMAP_CANDY_BAR,               
    SPRITE_HAM                      = IDB_BITMAP_HAM,                     
    SPRITE_LOLLIPOP                 = IDB_BITMAP_LOLLIPOP,                
    SPRITE_MONEY_BAG                = IDB_BITMAP_MONEY_BAG,               
    SPRITE_GOBSTOPPER               = IDB_BITMAP_GOBSTOPPER,              
    SPRITE_AMULET                   = IDB_BITMAP_AMULET,                  
    SPRITE_CAN                      = IDB_BITMAP_CAN,                     
    SPRITE_ICE_CREAM_CONE           = IDB_BITMAP_ICE_CREAM_CONE,          
    SPRITE_CRUCIFIX                 = IDB_BITMAP_CRUCIFIX,                
    SPRITE_SKULL                    = IDB_BITMAP_SKULL,                   
    SPRITE_SPANNER                  = IDB_BITMAP_SPANNER,                 
    SPRITE_ACG_KEY_LEFT             = IDB_BITMAP_ACG_KEY_LEFT,            
    SPRITE_ACG_KEY_MIDDLE           = IDB_BITMAP_ACG_KEY_MIDDLE,          
    SPRITE_ACG_KEY_RIGHT            = IDB_BITMAP_ACG_KEY_RIGHT,           
    SPRITE_MUSHROOM                 = IDB_BITMAP_MUSHROOM,                
    SPRITE_GRAVESTONE               = IDB_BITMAP_GRAVESTONE,              

    SPRITE_KNIGHT_WALKING_UP_1      = IDB_BITMAP_KNIGHT_WALKING_UP_1,     
    SPRITE_KNIGHT_UP                = IDB_BITMAP_KNIGHT_UP,               
    SPRITE_KNIGHT_WALKING_UP_2      = IDB_BITMAP_KNIGHT_WALKING_UP_2,     
    SPRITE_KNIGHT_WALKING_DOWN_1    = IDB_BITMAP_KNIGHT_WALKING_DOWN_1,   
    SPRITE_KNIGHT_DOWN              = IDB_BITMAP_KNIGHT_DOWN,             
    SPRITE_KNIGHT_WALKING_DOWN_2    = IDB_BITMAP_KNIGHT_WALKING_DOWN_2,   
    SPRITE_KNIGHT_WALKING_LEFT_1    = IDB_BITMAP_KNIGHT_WALKING_LEFT_1,   
    SPRITE_KNIGHT_LEFT              = IDB_BITMAP_KNIGHT_LEFT,             
    SPRITE_KNIGHT_WALKING_LEFT_2    = IDB_BITMAP_KNIGHT_WALKING_LEFT_2,   
    SPRITE_KNIGHT_WALKING_RIGHT_1   = IDB_BITMAP_KNIGHT_WALKING_RIGHT_1,  
    SPRITE_KNIGHT_RIGHT             = IDB_BITMAP_KNIGHT_RIGHT,            
    SPRITE_KNIGHT_WALKING_RIGHT_2   = IDB_BITMAP_KNIGHT_WALKING_RIGHT_2,  

    SPRITE_WIZARD_WALKING_UP_1      = IDB_BITMAP_WIZARD_WALKING_UP_1,     
    SPRITE_WIZARD_UP                = IDB_BITMAP_WIZARD_UP,               
    SPRITE_WIZARD_WALKING_UP_2      = IDB_BITMAP_WIZARD_WALKING_UP_2,     
    SPRITE_WIZARD_WALKING_DOWN_1    = IDB_BITMAP_WIZARD_WALKING_DOWN_1,   
    SPRITE_WIZARD_DOWN              = IDB_BITMAP_WIZARD_DOWN,             
    SPRITE_WIZARD_WALKING_DOWN_2    = IDB_BITMAP_WIZARD_WALKING_DOWN_2,   
    SPRITE_WIZARD_WALKING_LEFT_1    = IDB_BITMAP_WIZARD_WALKING_LEFT_1,   
    SPRITE_WIZARD_LEFT              = IDB_BITMAP_WIZARD_LEFT,             
    SPRITE_WIZARD_WALKING_LEFT_2    = IDB_BITMAP_WIZARD_WALKING_LEFT_2,   
    SPRITE_WIZARD_WALKING_RIGHT_1   = IDB_BITMAP_WIZARD_WALKING_RIGHT_1,  
    SPRITE_WIZARD_RIGHT             = IDB_BITMAP_WIZARD_RIGHT,            
    SPRITE_WIZARD_WALKING_RIGHT_2   = IDB_BITMAP_WIZARD_WALKING_RIGHT_2,  

    SPRITE_SERF_WALKING_UP_1        = IDB_BITMAP_SERF_WALKING_UP_1,       
    SPRITE_SERF_UP                  = IDB_BITMAP_SERF_UP,                 
    SPRITE_SERF_WALKING_UP_2        = IDB_BITMAP_SERF_WALKING_UP_2,       
    SPRITE_SERF_WALKING_DOWN_1      = IDB_BITMAP_SERF_WALKING_DOWN_1,     
    SPRITE_SERF_DOWN                = IDB_BITMAP_SERF_DOWN,               
    SPRITE_SERF_WALKING_DOWN_2      = IDB_BITMAP_SERF_WALKING_DOWN_2,     
    SPRITE_SERF_WALKING_LEFT_1      = IDB_BITMAP_SERF_WALKING_LEFT_1,     
    SPRITE_SERF_LEFT                = IDB_BITMAP_SERF_LEFT,               
    SPRITE_SERF_WALKING_LEFT_2      = IDB_BITMAP_SERF_WALKING_LEFT_2,     
    SPRITE_SERF_WALKING_RIGHT_1     = IDB_BITMAP_SERF_WALKING_RIGHT_1,    
    SPRITE_SERF_RIGHT               = IDB_BITMAP_SERF_RIGHT,              
    SPRITE_SERF_WALKING_RIGHT_2     = IDB_BITMAP_SERF_WALKING_RIGHT_2,    

    SPRITE_NASTY_ALIVE_1            = IDB_BITMAP_NASTY_ALIVE_1,           
    SPRITE_NASTY_ALIVE_2            = IDB_BITMAP_NASTY_ALIVE_2,           
    SPRITE_NASTY_ALIVE_3            = IDB_BITMAP_NASTY_ALIVE_3,           
    SPRITE_NASTY_ALIVE_4            = IDB_BITMAP_NASTY_ALIVE_4,           

    SPRITE_NASTY_DEAD_1             = IDB_BITMAP_NASTY_DEAD_1,            
    SPRITE_NASTY_DEAD_2             = IDB_BITMAP_NASTY_DEAD_2,            
    SPRITE_NASTY_DEAD_3             = IDB_BITMAP_NASTY_DEAD_3,            
    SPRITE_NASTY_DEAD_4             = IDB_BITMAP_NASTY_DEAD_4,            

    SPRITE_PUMPKIN_1                = IDB_BITMAP_PUMPKIN_1,               
    SPRITE_PUMPKIN_2                = IDB_BITMAP_PUMPKIN_2,               

    SPRITE_SPIDER_1                 = IDB_BITMAP_SPIDER_1,                
    SPRITE_SPIDER_2                 = IDB_BITMAP_SPIDER_2,                

    SPRITE_GHOST_1                  = IDB_BITMAP_GHOST_1,                 
    SPRITE_GHOST_2                  = IDB_BITMAP_GHOST_2,                 

    SPRITE_BOUNCY_1                 = IDB_BITMAP_BOUNCY_1,                
    SPRITE_BOUNCY_2                 = IDB_BITMAP_BOUNCY_2,                

    SPRITE_SMORPH_1                 = IDB_BITMAP_SMORPH_1,                
    SPRITE_SMORPH_2                 = IDB_BITMAP_SMORPH_2,                

    SPRITE_JELLY_GHOUL_1            = IDB_BITMAP_JELLY_GHOUL_1,           
    SPRITE_JELLY_GHOUL_2            = IDB_BITMAP_JELLY_GHOUL_2,           

    SPRITE_BAT_1                    = IDB_BITMAP_BAT_1,                   
    SPRITE_BAT_2                    = IDB_BITMAP_BAT_2,                   

    SPRITE_GHOUL_1                  = IDB_BITMAP_GHOUL_1,                 
    SPRITE_GHOUL_2                  = IDB_BITMAP_GHOUL_2,                 

    SPRITE_WITCH_FLYING_LEFT_1      = IDB_BITMAP_WITCH_FLYING_LEFT_1,     
    SPRITE_WITCH_FLYING_LEFT_2      = IDB_BITMAP_WITCH_FLYING_LEFT_2,     
    SPRITE_WITCH_FLYING_RIGHT_1     = IDB_BITMAP_WITCH_FLYING_RIGHT_1,    
    SPRITE_WITCH_FLYING_RIGHT_2     = IDB_BITMAP_WITCH_FLYING_RIGHT_2,    

    SPRITE_GHOUL_FLYING_LEFT_1      = IDB_BITMAP_GHOUL_FLYING_LEFT_1,     
    SPRITE_GHOUL_FLYING_LEFT_2      = IDB_BITMAP_GHOUL_FLYING_LEFT_2,     
    SPRITE_GHOUL_FLYING_RIGHT_1     = IDB_BITMAP_GHOUL_FLYING_RIGHT_1,    
    SPRITE_GHOUL_FLYING_RIGHT_2     = IDB_BITMAP_GHOUL_FLYING_RIGHT_2,    

    SPRITE_BAT_FLYING_LEFT_1        = IDB_BITMAP_BAT_FLYING_LEFT_1,       
    SPRITE_BAT_FLYING_LEFT_2        = IDB_BITMAP_BAT_FLYING_LEFT_2,       
    SPRITE_BAT_FLYING_RIGHT_1       = IDB_BITMAP_BAT_FLYING_RIGHT_1,      
    SPRITE_BAT_FLYING_RIGHT_2       = IDB_BITMAP_BAT_FLYING_RIGHT_2,      

    SPRITE_KNIGHT_AXE_1             = IDB_BITMAP_KNIGHT_AXE_1,            
    SPRITE_KNIGHT_AXE_2             = IDB_BITMAP_KNIGHT_AXE_2,            
    SPRITE_KNIGHT_AXE_3             = IDB_BITMAP_KNIGHT_AXE_3,            
    SPRITE_KNIGHT_AXE_4             = IDB_BITMAP_KNIGHT_AXE_4,            
    SPRITE_KNIGHT_AXE_5             = IDB_BITMAP_KNIGHT_AXE_5,            
    SPRITE_KNIGHT_AXE_6             = IDB_BITMAP_KNIGHT_AXE_6,            
    SPRITE_KNIGHT_AXE_7             = IDB_BITMAP_KNIGHT_AXE_7,            
    SPRITE_KNIGHT_AXE_8             = IDB_BITMAP_KNIGHT_AXE_8,            
    
    SPRITE_WIZARD_POTION_1          = IDB_BITMAP_WIZARD_POTION_1,         
    SPRITE_WIZARD_POTION_2          = IDB_BITMAP_WIZARD_POTION_2,         
    SPRITE_WIZARD_POTION_3          = IDB_BITMAP_WIZARD_POTION_3,         
    
    SPRITE_SERF_SWORD_1             = IDB_BITMAP_SERF_SWORD_1,            
    SPRITE_SERF_SWORD_2             = IDB_BITMAP_SERF_SWORD_2,            
    SPRITE_SERF_SWORD_3             = IDB_BITMAP_SERF_SWORD_3,            
    SPRITE_SERF_SWORD_4             = IDB_BITMAP_SERF_SWORD_4,            
    SPRITE_SERF_SWORD_5             = IDB_BITMAP_SERF_SWORD_5,            
    SPRITE_SERF_SWORD_6             = IDB_BITMAP_SERF_SWORD_6,            
    SPRITE_SERF_SWORD_7             = IDB_BITMAP_SERF_SWORD_7,            
    SPRITE_SERF_SWORD_8             = IDB_BITMAP_SERF_SWORD_8,            
    
    SPRITE_MUMMY_1                  = IDB_BITMAP_MUMMY_1,                 
    SPRITE_MUMMY_2                  = IDB_BITMAP_MUMMY_2,                 
    SPRITE_MUMMY_3                  = IDB_BITMAP_MUMMY_3,                 
    
    SPRITE_DRACULA_1                = IDB_BITMAP_DRACULA_1,               
    SPRITE_DRACULA_2                = IDB_BITMAP_DRACULA_2,               
    SPRITE_DRACULA_3                = IDB_BITMAP_DRACULA_3,               
    
    SPRITE_FRANKENSTEIN_1           = IDB_BITMAP_FRANKENSTEIN_1,          
    SPRITE_FRANKENSTEIN_2           = IDB_BITMAP_FRANKENSTEIN_2,          
    SPRITE_FRANKENSTEIN_3           = IDB_BITMAP_FRANKENSTEIN_3,          
    
    SPRITE_HUNCHBACK_1              = IDB_BITMAP_HUNCHBACK_1,             
    SPRITE_HUNCHBACK_2              = IDB_BITMAP_HUNCHBACK_2,             
    SPRITE_HUNCHBACK_3              = IDB_BITMAP_HUNCHBACK_3,             
    
    SPRITE_DEVIL_1                  = IDB_BITMAP_DEVIL_1,                 
    SPRITE_DEVIL_2                  = IDB_BITMAP_DEVIL_2,                 
    SPRITE_DEVIL_3                  = IDB_BITMAP_DEVIL_3,                 
}; // Endenum.

// Sprite graphic.
typedef Folio::Core::Game::ResourceGraphicPtr   SpriteGraphic;
             

// Routines.

extern  FolioStatus CreateSpriteGraphics (FolioHandle instanceHandle);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
