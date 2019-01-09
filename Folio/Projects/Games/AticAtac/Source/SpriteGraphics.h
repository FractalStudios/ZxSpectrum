#pragma once

// STL includes.
#include    <map>

// "Home-made" includes.
#include    <Game.h>
#include    "ZxSpectrum.h"

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
    SPRITE_LEAF = 0,
    SPRITE_KEY,
    SPRITE_BOTTLE,
    SPRITE_MEDICINE_BOTTLE,
    SPRITE_BROKEN,
    SPRITE_ROPE,
    SPRITE_ARM,
    SPRITE_BOWL,
    SPRITE_APPLE,
    SPRITE_CANDY_BAR,
    SPRITE_HAM,
    SPRITE_LOLLIPOP,
    SPRITE_MONEY_BAG,
    SPRITE_GOBSTOPPER,
    SPRITE_AMULET,
    SPRITE_CAN,
    SPRITE_ICE_CREAM_CONE,
    SPRITE_CRUCIFIX,
    SPRITE_SKULL,
    SPRITE_SPANNER,
    SPRITE_ACG_KEY_LEFT,
    SPRITE_ACG_KEY_MIDDLE,
    SPRITE_ACG_KEY_RIGHT,
    SPRITE_MUSHROOM,
    SPRITE_GRAVESTONE,

    SPRITE_KNIGHT_WALKING_UP_1,
    SPRITE_KNIGHT_UP,
    SPRITE_KNIGHT_WALKING_UP_2,
    SPRITE_KNIGHT_WALKING_DOWN_1,
    SPRITE_KNIGHT_DOWN,
    SPRITE_KNIGHT_WALKING_DOWN_2,
    SPRITE_KNIGHT_WALKING_LEFT_1,
    SPRITE_KNIGHT_LEFT,
    SPRITE_KNIGHT_WALKING_LEFT_2,
    SPRITE_KNIGHT_WALKING_RIGHT_1,
    SPRITE_KNIGHT_RIGHT,
    SPRITE_KNIGHT_WALKING_RIGHT_2,

    SPRITE_WIZARD_WALKING_UP_1,
    SPRITE_WIZARD_UP,
    SPRITE_WIZARD_WALKING_UP_2,
    SPRITE_WIZARD_WALKING_DOWN_1,
    SPRITE_WIZARD_DOWN,
    SPRITE_WIZARD_WALKING_DOWN_2,
    SPRITE_WIZARD_WALKING_LEFT_1,
    SPRITE_WIZARD_LEFT,
    SPRITE_WIZARD_WALKING_LEFT_2,
    SPRITE_WIZARD_WALKING_RIGHT_1,
    SPRITE_WIZARD_RIGHT,
    SPRITE_WIZARD_WALKING_RIGHT_2,

    SPRITE_SERF_WALKING_UP_1,
    SPRITE_SERF_UP,
    SPRITE_SERF_WALKING_UP_2,
    SPRITE_SERF_WALKING_DOWN_1,
    SPRITE_SERF_DOWN,
    SPRITE_SERF_WALKING_DOWN_2,
    SPRITE_SERF_WALKING_LEFT_1,
    SPRITE_SERF_LEFT,
    SPRITE_SERF_WALKING_LEFT_2,
    SPRITE_SERF_WALKING_RIGHT_1,
    SPRITE_SERF_RIGHT,
    SPRITE_SERF_WALKING_RIGHT_2,

    SPRITE_NASTY_ALIVE_1,
    SPRITE_NASTY_ALIVE_2,
    SPRITE_NASTY_ALIVE_3,
    SPRITE_NASTY_ALIVE_4,

    SPRITE_NASTY_DEAD_1,
    SPRITE_NASTY_DEAD_2,
    SPRITE_NASTY_DEAD_3,
    SPRITE_NASTY_DEAD_4,

    SPRITE_PUMPKIN_1,            
    SPRITE_PUMPKIN_2,            

    SPRITE_SPIDER_1,             
    SPRITE_SPIDER_2,             

    SPRITE_GHOST_1,              
    SPRITE_GHOST_2,              

    SPRITE_BOUNCY_1,             
    SPRITE_BOUNCY_2,             

    SPRITE_SMORPH_1,             
    SPRITE_SMORPH_2,             

    SPRITE_JELLY_GHOUL_1,        
    SPRITE_JELLY_GHOUL_2,        

    SPRITE_BAT_1,                
    SPRITE_BAT_2,                

    SPRITE_GHOUL_1,              
    SPRITE_GHOUL_2,

    SPRITE_WITCH_FLYING_LEFT_1,  
    SPRITE_WITCH_FLYING_LEFT_2,  
    SPRITE_WITCH_FLYING_RIGHT_1, 
    SPRITE_WITCH_FLYING_RIGHT_2, 

    SPRITE_GHOUL_FLYING_LEFT_1,  
    SPRITE_GHOUL_FLYING_LEFT_2,  
    SPRITE_GHOUL_FLYING_RIGHT_1, 
    SPRITE_GHOUL_FLYING_RIGHT_2, 

    SPRITE_BAT_FLYING_LEFT_1,    
    SPRITE_BAT_FLYING_LEFT_2,    
    SPRITE_BAT_FLYING_RIGHT_1,   
    SPRITE_BAT_FLYING_RIGHT_2,

    SPRITE_KNIGHT_AXE_1,
    SPRITE_KNIGHT_AXE_2,
    SPRITE_KNIGHT_AXE_3,
    SPRITE_KNIGHT_AXE_4,
    SPRITE_KNIGHT_AXE_5,
    SPRITE_KNIGHT_AXE_6,
    SPRITE_KNIGHT_AXE_7,
    SPRITE_KNIGHT_AXE_8,
    
    SPRITE_WIZARD_POTION_1,
    SPRITE_WIZARD_POTION_2,
    SPRITE_WIZARD_POTION_3,
    
    SPRITE_SERF_SWORD_1,    
    SPRITE_SERF_SWORD_2,    
    SPRITE_SERF_SWORD_3,    
    SPRITE_SERF_SWORD_4,    
    SPRITE_SERF_SWORD_5,    
    SPRITE_SERF_SWORD_6,    
    SPRITE_SERF_SWORD_7,    
    SPRITE_SERF_SWORD_8,    
    
    SPRITE_MUMMY_1,    
    SPRITE_MUMMY_2,    
    SPRITE_MUMMY_3,    
    
    SPRITE_DRACULA_1,    
    SPRITE_DRACULA_2,    
    SPRITE_DRACULA_3,    
    
    SPRITE_FRANKENSTEIN_1,    
    SPRITE_FRANKENSTEIN_2,    
    SPRITE_FRANKENSTEIN_3,    
    
    SPRITE_HUNCHBACK_1,    
    SPRITE_HUNCHBACK_2,    
    SPRITE_HUNCHBACK_3,    
    
    SPRITE_DEVIL_1,    
    SPRITE_DEVIL_2,    
    SPRITE_DEVIL_3,    
}; // Endenum.

// Sprite graphic.
typedef Folio::Core::Game::ResourceGraphicPtr   SpriteGraphic;

// Sprite graphics map.
typedef std::map<SPRITE_ID, SpriteGraphic>      SpriteGraphicsMap;
             

// Routines.

extern  FolioStatus BuildSpriteGraphics (FolioHandle        dcHandle, 
                                         FolioHandle        instanceHandle,
                                         SpriteGraphicsMap  &spriteGraphicsMap);

template <typename T, typename U>
FolioStatus QuerySpriteGraphics (FolioHandle                                                dcHandle,
                                 T                                                          spriteId,
                                 const SpriteGraphicsMap                                    &spriteGraphicsMap,
                                 ZxSpectrum::COLOUR                                         spriteColour,
                                 UInt32                                                     numSpriteGraphicAttributes,
                                 const U                                                    *spriteGraphicAttributesTable,
                                 Folio::Core::Game::ASprite::SpriteGraphicAttributesList    &spriteGraphicAttributesList)
{
    FolioStatus status = ERR_SUCCESS;

    spriteGraphicAttributesList.clear (); // Initialise!

    // Get the mapped sprite colour.

    Gdiplus::ARGB   mappedSpriteColour = ZxSpectrum::MapInkColour (spriteColour);

    // Build the sprite's bitmaps.

    for (UInt32 index = 0; 
         (status == ERR_SUCCESS) && (index < numSpriteGraphicAttributes);
         ++index)
    {              
        // Does this sprite match the sprite in the sprite graphics atttribute table?

        if (spriteGraphicAttributesTable [index].m_spriteId == spriteId)
        {
            // Yes. Add the sprite graphics.

            Folio::Core::Game::ASprite::SpriteGraphicsList  spriteGraphicsList;

            for (U::SpriteGraphicIdsList::const_iterator itr = spriteGraphicAttributesTable [index].m_spriteGraphicIdsList.begin ();     
                 (status == ERR_SUCCESS) && (itr != spriteGraphicAttributesTable [index].m_spriteGraphicIdsList.end ());
                 ++itr)
            {
                // Find the sprite graphic in the sprite graphics map.

                SpriteGraphicsMap::const_iterator spriteGraphicsMapItr = spriteGraphicsMap.find (*itr);

                if (spriteGraphicsMapItr != spriteGraphicsMap.end ())
                {
                    // Get the sprite graphic.

                    SpriteGraphic   spriteGraphic(spriteGraphicsMapItr->second);

                    // Change the colour of the sprite graphic.

                    status = spriteGraphic->ChangeColour (mappedSpriteColour);

                    if (status == ERR_SUCCESS)
                    {
                        // Add the sprite graphic.

                        spriteGraphicsList.push_back (spriteGraphicsMapItr->second);
                    } // Endif.
        
                } // Endif.

                else
                {
                    // Didn't find the sprite graphic in the sprite graphics map.

                    status = ERR_NOT_FOUND;
                } // Endelse.

            } // Endfor.            

            if (status == ERR_SUCCESS)
            {
                spriteGraphicAttributesList.push_back (Folio::Core::Game::ASprite::SpriteGraphicAttributesList::value_type(spriteGraphicAttributesTable [index].m_direction,
                                                                                                                           spriteGraphicsList));
            } // Endif.

        } // Endif.

    } // Endfor.

    if (status != ERR_SUCCESS)
    {
        spriteGraphicAttributesList.clear ();
    } // Endif.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
