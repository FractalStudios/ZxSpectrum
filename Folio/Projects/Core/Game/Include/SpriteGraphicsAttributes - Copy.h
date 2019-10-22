#pragma once

// STL includes.
#include    <map>
#include    <vector>

// "Home-made" includes.
#include    "ASprite.h"
#include    "ResourceGraphic.h"
#include    "ZxSpectrum.h"

#pragma pack(push, 1)

namespace Folio        
{

namespace Core
{

namespace Game
{

// Sprite graphic identifiers list.
template <typename U>
using SpriteGraphicIdsList = std::vector<U>;

// Sprite graphics attributes.
template <typename T, typename U>
class SpriteGraphicsAttributes
{
public:
    T                       m_spriteId;             // The identifier of the sprite.
    ASprite::Direction      m_direction;            // The direction of the sprite.
    SpriteGraphicIdsList<U> m_spriteGraphicIdsList; // The sprite graphic identifiers representing the sprite's direction.
}; // Endclass.

// Sprite graphics attributes list.
template <typename T, typename U>
using SpriteGraphicsAttributesList = std::vector<SpriteGraphicsAttributes<T, U> >;


// Sprite graphic.
typedef Folio::Core::Game::ResourceGraphicPtr   SpriteGraphic;

// Sprite graphics map.
template <typename U>
using SpriteGraphicsMap = std::map<U, SpriteGraphic>;


// Routines.

template <typename T, typename U>
FolioStatus QuerySpriteGraphics (FolioHandle                                        dcHandle,
                                 const SpriteGraphicIdsList<U>&                     spriteIdsList,
                                 const SpriteGraphicsMap<U>&                        spriteGraphicsMap,
                                 Folio::Core::Game::ZxSpectrum::COLOUR              spriteColour,
                                 Folio::Core::Game::ASprite::SpriteGraphicsList&    spriteGraphicsList)
{
    spriteGraphicsList.clear (); // Terminate!

    // Add the sprite graphics.

    for (SpriteIdsList::const_iterator itr = spriteIdsList.begin ();     
         (status == ERR_SUCCESS) && (itr != spriteIdsList.end ());
         ++itr)
    {
        // Find the sprite graphic in the sprite graphics map.

        SpriteGraphicsMap::const_iterator   spriteGraphicsMapItr = spriteGraphicsMap.find (*itr);

        if (spriteGraphicsMapItr != spriteGraphicsMap.end ())
        {
            // Get the sprite graphic.

            SpriteGraphic   spriteGraphic(spriteGraphicsMapItr->second);

            if (spriteColour != Folio::Core::Game::ZxSpectrum::UNDEFINED)
            {
                // Change the colour of the sprite graphic.

                status = spriteGraphic->ChangeColour (mappedSpriteColour);
            } // Endif.

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

    if (status != ERR_SUCCESS)
    {
        spriteGraphicsList.clear ();
    } // Endif.

    return (status);
} // Endproc.


template <typename T, typename U>
FolioStatus QuerySpriteGraphicAttributes (FolioHandle                                               dcHandle,
                                          T                                                         spriteId,
                                          const SpriteGraphicsMap<U>&                               spriteGraphicsMap,
                                          Folio::Core::Game::ZxSpectrum::COLOUR                     spriteColour,
                                          const SpriteGraphicsAttributesList<T, U>&                 spriteGraphicAttributes,
                                          Folio::Core::Game::ASprite::SpriteGraphicAttributesList   &spriteGraphicAttributesList)
{
    FolioStatus status = ERR_SUCCESS;

    spriteGraphicAttributesList.clear (); // Initialise!

    // Get the mapped sprite colour.

    Gdiplus::ARGB   mappedSpriteColour = Folio::Core::Game::ZxSpectrum::MapInkColour (spriteColour);

    // Build the sprite's bitmaps.

    bool    complete    = false;   // Initialise!
    bool    foundSprite = false;

    for (SpriteGraphicsAttributesList<T, U>::const_iterator spriteGraphicAttributesItr = spriteGraphicAttributes.begin ();
         !complete && (status == ERR_SUCCESS) && (spriteGraphicAttributesItr != spriteGraphicAttributes.end ());
         ++spriteGraphicAttributesItr)
    {              
        // Does this sprite match the sprite in the sprite graphics atttribute table?

        if (spriteGraphicAttributesItr->m_spriteId == spriteId)
        {
            // Yes. 
            
            foundSprite = true; // We've found the sprite.

            // Query the sprite graphics.

            Folio::Core::Game::ASprite::SpriteGraphicsList  spriteGraphicsList;

            status = QuerySpriteGraphics (dcHandle,
                                          spriteGraphicAttributesItr->m_spriteGraphicIdsList,
                                          spriteGraphicsMap,
                                          spriteColour,
                                          spriteGraphicsList);

            //for (SpriteGraphicsAttributes<T, U>::SpriteGraphicIdsList::const_iterator spriteGraphicIdsListItr = t.begin ();     
            //     (status == ERR_SUCCESS) && (spriteGraphicIdsListItr != spriteGraphicAttributesItr->m_spriteGraphicIdsList.end ());
            //     ++spriteGraphicIdsListItr)
            //{
            //    // Find the sprite graphic in the sprite graphics map.

            //    SpriteGraphicsMap<U>::const_iterator    spriteGraphicsMapItr = spriteGraphicsMap.find (*spriteGraphicIdsListItr);

            //    if (spriteGraphicsMapItr != spriteGraphicsMap.end ())
            //    {
            //        // Get the sprite graphic.

            //        SpriteGraphic   spriteGraphic(spriteGraphicsMapItr->second);

            //        if (spriteColour != Folio::Core::Game::ZxSpectrum::UNDEFINED)
            //        {
            //            // Change the colour of the sprite graphic.

            //            status = spriteGraphic->ChangeColour (mappedSpriteColour);
            //        } // Endif.

            //        if (status == ERR_SUCCESS)
            //        {
            //            // Add the sprite graphic.

            //            spriteGraphicsList.push_back (spriteGraphicsMapItr->second);
            //        } // Endif.
        
            //    } // Endif.

            //    else
            //    {
            //        // Didn't find the sprite graphic in the sprite graphics map.

            //        status = ERR_NOT_FOUND;
            //    } // Endelse.

            //} // Endfor.            

            if (status == ERR_SUCCESS)
            {
                spriteGraphicAttributesList.push_back (Folio::Core::Game::ASprite::SpriteGraphicAttributesList::value_type(spriteGraphicAttributesItr->m_direction,
                                                                                                                           spriteGraphicsList));
            } // Endif.

        } // Endif.

        else
        if (foundSprite)
        {
            complete = true;    // We've found all the sprite's directions.
        } // Endelseif.

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
