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

// Background item identifier enumeration.
enum BACKGROUND_ITEM_ID
{
    BACKGROUND_ITEM_UNDEFINED                   = Folio::Core::Util::UNDEFINED_BITMAP_RESOURCE_ID,
    BACKGROUND_ITEM_CAVE_DOOR_FRAME             = IDB_BITMAP_CAVE_DOOR_FRAME,             
    BACKGROUND_ITEM_NORMAL_DOOR_FRAME           = IDB_BITMAP_NORMAL_DOOR_FRAME,           
    BACKGROUND_ITEM_BIG_DOOR_FRAME              = IDB_BITMAP_BIG_DOOR_FRAME,              
    BACKGROUND_ITEM_RED_LOCKED_NORMAL_DOOR      = IDB_BITMAP_RED_LOCKED_NORMAL_DOOR,      
    BACKGROUND_ITEM_GREEN_LOCKED_NORMAL_DOOR    = IDB_BITMAP_GREEN_LOCKED_NORMAL_DOOR,    
    BACKGROUND_ITEM_CYAN_LOCKED_NORMAL_DOOR     = IDB_BITMAP_CYAN_LOCKED_NORMAL_DOOR,     
    BACKGROUND_ITEM_YELLOW_LOCKED_NORMAL_DOOR   = IDB_BITMAP_YELLOW_LOCKED_NORMAL_DOOR,   
    BACKGROUND_ITEM_RED_LOCKED_CAVE_DOOR        = IDB_BITMAP_RED_LOCKED_CAVE_DOOR,        
    BACKGROUND_ITEM_GREEN_LOCKED_CAVE_DOOR      = IDB_BITMAP_GREEN_LOCKED_CAVE_DOOR,      
    BACKGROUND_ITEM_CYAN_LOCKED_CAVE_DOOR       = IDB_BITMAP_CYAN_LOCKED_CAVE_DOOR,       
    BACKGROUND_ITEM_YELLOW_LOCKED_CAVE_DOOR     = IDB_BITMAP_YELLOW_LOCKED_CAVE_DOOR,     
    BACKGROUND_ITEM_CLOCK                       = IDB_BITMAP_CLOCK,                       
    BACKGROUND_ITEM_PICTURE                     = IDB_BITMAP_PICTURE,                     
    BACKGROUND_ITEM_TABLE                       = IDB_BITMAP_TABLE,                       
    BACKGROUND_ITEM_ANTLER_TROPHY               = IDB_BITMAP_ANTLER_TROPHY,               
    BACKGROUND_ITEM_TROPHY                      = IDB_BITMAP_TROPHY,                      
    BACKGROUND_ITEM_BOOKCASE                    = IDB_BITMAP_BOOKCASE,                    
    BACKGROUND_ITEM_CLOSED_TRAP_DOOR            = IDB_BITMAP_CLOSED_TRAP_DOOR,            
    BACKGROUND_ITEM_OPEN_TRAP_DOOR              = IDB_BITMAP_OPEN_TRAP_DOOR,              
    BACKGROUND_ITEM_BARREL                      = IDB_BITMAP_BARREL,                      
    BACKGROUND_ITEM_RUG                         = IDB_BITMAP_RUG,                         
    BACKGROUND_ITEM_ACG_SHIELD                  = IDB_BITMAP_ACG_SHIELD,                  
    BACKGROUND_ITEM_SHIELD                      = IDB_BITMAP_SHIELD,                      
    BACKGROUND_ITEM_KNIGHT                      = IDB_BITMAP_KNIGHT,                      
    BACKGROUND_ITEM_CLOSED_NORMAL_DOOR          = IDB_BITMAP_CLOSED_NORMAL_DOOR,          
    BACKGROUND_ITEM_OPEN_NORMAL_DOOR            = IDB_BITMAP_OPEN_NORMAL_DOOR,            
    BACKGROUND_ITEM_CLOSED_CAVE_DOOR            = IDB_BITMAP_CLOSED_CAVE_DOOR,            
    BACKGROUND_ITEM_OPEN_CAVE_DOOR              = IDB_BITMAP_OPEN_CAVE_DOOR,              
    BACKGROUND_ITEM_ACG_EXIT_DOOR               = IDB_BITMAP_ACG_EXIT_DOOR,               
    BACKGROUND_ITEM_PICTURE_2                   = IDB_BITMAP_PICTURE_2,                   
    BACKGROUND_ITEM_SKELETON                    = IDB_BITMAP_SKELETON,                    
    BACKGROUND_ITEM_BARRELS                     = IDB_BITMAP_BARRELS,                     
}; // Endenum.

// Background item graphic.
typedef Folio::Core::Game::ResourceGraphicPtr   BackgroundItemGraphic;


// Routines.

extern  FolioStatus CreateBackgroundItemGraphics (FolioHandle instanceHandle);
extern  FolioStatus QueryBackgroundItemGraphic (const Folio::Core::Game::ResourceGraphicsCache::OwnerId&    ownerId,
                                                BACKGROUND_ITEM_ID                                          backgroundItemId, 
                                                BackgroundItemGraphic&                                      backgroundItemGraphic);
extern  FolioStatus ReleaseBackgroundItemGraphic (const BackgroundItemGraphic& backgroundItemGraphic);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
