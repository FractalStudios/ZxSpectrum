#pragma once

// STL includes.
#include    <map>
#include    <vector>

// "Home-made" includes.
#include    "ResourceGraphic.h"
#include    "ResourceGraphicsCache.h"
#include    "ZxSpectrum.h"

#pragma pack(push, 1)

namespace Folio        
{

namespace Core
{

namespace Game
{

// Direction.
typedef UInt32  Direction;

// Sprite directions.
const   Direction   NO_DIRECTION        = 0x00000000;
const   Direction   N                   = 0x00000001;   // North.
const   Direction   S                   = 0x00000002;   // South.
const   Direction   E                   = 0x00000004;   // East.
const   Direction   W                   = 0x00000008;   // West.
const   Direction   NE                  = N | E;        // North-East.
const   Direction   NW                  = N | W;        // North-West.
const   Direction   SE                  = S | E;        // South-East.
const   Direction   SW                  = S | W;        // South-West.
const   Direction   ALL_DIRECTIONS      = N | S | E | W;


// Action.
typedef UInt32  Action;

// Sprite actions.
const   Action  NO_ACTION = 0;


// Sprite graphic identifiers list.
template <typename U>
using SpriteGraphicIdsList = std::vector<U>;

// Sprite graphic characteristics.
template <typename T, typename U>
class SpriteGraphicCharacteristics
{
public:
    SpriteGraphicCharacteristics (T                                 spriteId,
                                  Direction                         direction,
                                  const SpriteGraphicIdsList<U>&    spriteGraphicIdsList,
                                  Action                            action = NO_ACTION)
    :   m_spriteId(spriteId),
        m_direction(direction),
        m_spriteGraphicIdsList(spriteGraphicIdsList),
        m_action(action)
    {} // Endproc.
    
    T                       m_spriteId;             // The identifier of the sprite.
    Direction               m_direction;            // The direction(s) of the sprite.
    SpriteGraphicIdsList<U> m_spriteGraphicIdsList; // The sprite graphic identifiers representing the sprite's direction(s).
    Action                  m_action;               // The action(s) of the sprite.
}; // Endclass.

// Sprite graphic characteristics list.
template <typename T, typename U>
using SpriteGraphicCharacteristicsList = std::vector<SpriteGraphicCharacteristics<T, U> >;


// Sprite graphic.
typedef ResourceGraphicPtr  SpriteGraphic;

// Sprite graphics list.
typedef std::vector<SpriteGraphic>  SpriteGraphicsList;

// Sprite graphics map.
template <typename U>
using SpriteGraphicsMap = std::map<U, SpriteGraphic>;


// Sprite graphic attributes.
class SpriteGraphicAttributes
{
public:
    SpriteGraphicAttributes ()
    :   m_direction(NO_DIRECTION),
        m_action(NO_ACTION)
    {} // Endproc.

    SpriteGraphicAttributes (Direction                  direction,
                             const SpriteGraphicsList   &spriteGraphicsList,
                             Action                     action = NO_ACTION)
    :   m_direction(direction),
        m_spriteGraphicsList(spriteGraphicsList),
        m_action(action)
    {} // Endproc.

    Direction           m_direction;            // The direction(s) of the sprite.
    SpriteGraphicsList  m_spriteGraphicsList;   // The sprite graphics representing the sprite's direction(s).
    Action              m_action;               // The action(s) of the sprite.
}; // Endclass.

// Sprite graphic attributes list.
typedef std::vector<SpriteGraphicAttributes>    SpriteGraphicAttributesList;


// Routines.

template <typename T, typename U>
FolioStatus QuerySpriteGraphics (FolioHandle                            dcHandle,
                                 const SpriteGraphicIdsList<U>&         spriteGraphicIdsList,
                                 const SpriteGraphicsMap<U>&            spriteGraphicsMap,
                                 Folio::Core::Game::ZxSpectrum::COLOUR  spriteColour,
                                 SpriteGraphicsList&                    spriteGraphicsList)
{
    FolioStatus status = ERR_SUCCESS;

    spriteGraphicsList.clear (); // Initialise!

    // Get the mapped sprite colour.

    Gdiplus::ARGB   mappedSpriteColour = Folio::Core::Game::ZxSpectrum::MapInkColour (spriteColour);

    // Add the sprite graphics.

    for (SpriteGraphicIdsList<U>::const_iterator itr = spriteGraphicIdsList.begin ();     
         (status == ERR_SUCCESS) && (itr != spriteGraphicIdsList.end ());
         ++itr)
    {
        // Find the sprite graphic in the sprite graphics map.

        SpriteGraphicsMap<U>::const_iterator    spriteGraphicsMapItr = spriteGraphicsMap.find (*itr);

        if (spriteGraphicsMapItr != spriteGraphicsMap.end ())
        {
            // Get the sprite graphic.

            SpriteGraphic   spriteGraphic(spriteGraphicsMapItr->second);

            if ((spriteColour != Folio::Core::Game::ZxSpectrum::UNDEFINED) &&
                (spriteGraphic->GetCurrentChangeableColour () != mappedSpriteColour))
            {
                // Change the colour of the sprite graphic.

                status = spriteGraphic->ChangeColour (mappedSpriteColour);
            } // Endif.

            if (status == ERR_SUCCESS)
            {
                // Add the sprite graphic to the sprite graphics list.

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
FolioStatus QuerySpriteGraphics (FolioHandle                                        dcHandle,
                                 Folio::Core::Game::ResourceGraphicsCache&          resourceGraphicsCache,
                                 Folio::Core::Game::ResourceGraphicsCache::OwnerId  ownerId,
                                 Folio::Core::Game::DrawingElement::Id              drawingElementId,
                                 const SpriteGraphicIdsList<U>&                     spriteGraphicIdsList,
                                 Folio::Core::Game::ZxSpectrum::COLOUR              spriteColour,
                                 SpriteGraphicsList&                                spriteGraphicsList)
{
    FolioStatus status = ERR_SUCCESS;

    spriteGraphicsList.clear (); // Initialise!

    // Get the mapped sprite colour.

    Gdiplus::ARGB   mappedSpriteColour = Folio::Core::Game::ZxSpectrum::MapInkColour (spriteColour);

    // Add the sprite graphics.

    for (SpriteGraphicIdsList<U>::const_iterator itr = spriteGraphicIdsList.begin ();     
         (status == ERR_SUCCESS) && (itr != spriteGraphicIdsList.end ());
         ++itr)
    {
        // Gain the sprite's graphic from the resource graphics cache.

        SpriteGraphic   spriteGraphic;

        status = resourceGraphicsCache.GainResourceGraphic (ownerId,
                                                            drawingElementId, 
                                                            *itr, 
                                                            spriteGraphic);

        if (status == ERR_SUCCESS)
        {
            if ((spriteColour != Folio::Core::Game::ZxSpectrum::UNDEFINED) &&
                (spriteGraphic->GetCurrentChangeableColour () != mappedSpriteColour))
            {
                // Change the colour of the sprite graphic.

                status = spriteGraphic->ChangeColour (mappedSpriteColour);
            } // Endif.

            if (status == ERR_SUCCESS)
            {
                // Add the sprite graphic to the sprite graphics list.

                spriteGraphicsList.push_back (spriteGraphic);
            } // Endif.
        
        } // Endif.

    } // Endfor.            

    if (status != ERR_SUCCESS)
    {
        spriteGraphicsList.clear ();
    } // Endif.

    return (status);
} // Endproc.


template <typename T, typename U>
FolioStatus QuerySpriteGraphicAttributes (FolioHandle                                   dcHandle,
                                          const SpriteGraphicsMap<U>&                   spriteGraphicsMap,
                                          Folio::Core::Game::ZxSpectrum::COLOUR         spriteColour,
                                          const SpriteGraphicCharacteristicsList<T, U>& spriteGraphicCharacteristicsList,
                                          SpriteGraphicAttributesList&                  spriteGraphicAttributesList)
{
    FolioStatus status = ERR_SUCCESS;

    spriteGraphicAttributesList.clear (); // Initialise!

    // Build the sprite's graphic attributes from the sprite's graphic characteristics.

    for (SpriteGraphicCharacteristicsList<T, U>::const_iterator itr = spriteGraphicCharacteristicsList.begin ();
         (status == ERR_SUCCESS) && (itr != spriteGraphicCharacteristicsList.end ());
         ++itr)
    {              
        // Query the sprite graphics.

        SpriteGraphicsList  spriteGraphicsList;

        status = QuerySpriteGraphics<T, U> (dcHandle,
                                            itr->m_spriteGraphicIdsList,
                                            spriteGraphicsMap,
                                            spriteColour,
                                            spriteGraphicsList);

        if (status == ERR_SUCCESS)
        {
            // Add to the sprite graphic attributes list.

            spriteGraphicAttributesList.push_back (SpriteGraphicAttributesList::value_type(itr->m_direction,
                                                                                           spriteGraphicsList,
                                                                                           itr->m_action));
        } // Endif.

    } // Endfor.

    if (status != ERR_SUCCESS)
    {
        spriteGraphicAttributesList.clear ();
    } // Endif.

    return (status);
} // Endproc.


template <typename T, typename U>
FolioStatus QuerySpriteGraphicAttributes (FolioHandle                                       dcHandle,
                                          Folio::Core::Game::ResourceGraphicsCache&         resourceGraphicsCache,
                                          Folio::Core::Game::ResourceGraphicsCache::OwnerId ownerId,
                                          Folio::Core::Game::DrawingElement::Id             drawingElementId,
                                          Folio::Core::Game::ZxSpectrum::COLOUR             spriteColour,
                                          const SpriteGraphicCharacteristicsList<T, U>&     spriteGraphicCharacteristicsList,
                                          SpriteGraphicAttributesList&                      spriteGraphicAttributesList)
{
    FolioStatus status = ERR_SUCCESS;

    spriteGraphicAttributesList.clear (); // Initialise!

    // Build the sprite's graphic attributes from the sprite's graphic characteristics.

    for (SpriteGraphicCharacteristicsList<T, U>::const_iterator itr = spriteGraphicCharacteristicsList.begin ();
         (status == ERR_SUCCESS) && (itr != spriteGraphicCharacteristicsList.end ());
         ++itr)
    {              
        // Query the sprite graphics.

        SpriteGraphicsList  spriteGraphicsList;

        status = QuerySpriteGraphics<T, U> (dcHandle,
                                            resourceGraphicsCache,
                                            ownerId,
                                            drawingElementId,
                                            itr->m_spriteGraphicIdsList,
                                            spriteColour,
                                            spriteGraphicsList);

        if (status == ERR_SUCCESS)
        {
            // Add to the sprite graphic attributes list.

            spriteGraphicAttributesList.push_back (SpriteGraphicAttributesList::value_type(itr->m_direction,
                                                                                           spriteGraphicsList,
                                                                                           itr->m_action));
        } // Endif.

    } // Endfor.

    if (status != ERR_SUCCESS)
    {
        spriteGraphicAttributesList.clear ();
    } // Endif.

    return (status);
} // Endproc.


template <typename T, typename U>
FolioStatus QuerySpriteGraphicAttributes (FolioHandle                                   dcHandle,
                                          const SpriteGraphicsMap<U>&                   spriteGraphicsMap,
                                          T                                             spriteId,
                                          Folio::Core::Game::ZxSpectrum::COLOUR         spriteColour,
                                          const SpriteGraphicCharacteristicsList<T, U>& spriteGraphicCharacteristicsList,
                                          SpriteGraphicAttributesList&                  spriteGraphicAttributesList)
{
    FolioStatus status = ERR_SUCCESS;

    spriteGraphicAttributesList.clear (); // Initialise!

    // Build the sprite's graphic attributes from the sprite's graphic characteristics.

    bool    complete    = false;   // Initialise!
    bool    foundSprite = false;

    for (SpriteGraphicCharacteristicsList<T, U>::const_iterator itr = spriteGraphicCharacteristicsList.begin ();
         !complete && (status == ERR_SUCCESS) && (itr != spriteGraphicCharacteristicsList.end ());
         ++itr)
    {              
        // Does this sprite match the sprite in the sprite graphics atttribute table?

        if (itr->m_spriteId == spriteId)
        {
            // Yes. 
            
            foundSprite = true; // We've found the sprite.

            // Query the sprite graphics.

            SpriteGraphicsList  spriteGraphicsList;

            status = QuerySpriteGraphics<T, U> (dcHandle,
                                                itr->m_spriteGraphicIdsList,
                                                spriteGraphicsMap,
                                                spriteColour,
                                                spriteGraphicsList);

            if (status == ERR_SUCCESS)
            {
                // Add to the sprite graphic attributes list.

                spriteGraphicAttributesList.push_back (SpriteGraphicAttributesList::value_type(itr->m_direction,
                                                                                               spriteGraphicsList,
                                                                                               itr->m_action));
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


template <typename T, typename U>
FolioStatus QuerySpriteGraphicAttributes (FolioHandle                                       dcHandle,
                                          Folio::Core::Game::ResourceGraphicsCache&         resourceGraphicsCache,
                                          Folio::Core::Game::ResourceGraphicsCache::OwnerId ownerId,
                                          Folio::Core::Game::DrawingElement::Id             drawingElementId,
                                          T                                                 spriteId,
                                          Folio::Core::Game::ZxSpectrum::COLOUR             spriteColour,
                                          const SpriteGraphicCharacteristicsList<T, U>&     spriteGraphicCharacteristicsList,
                                          SpriteGraphicAttributesList&                      spriteGraphicAttributesList)
{
    FolioStatus status = ERR_SUCCESS;

    spriteGraphicAttributesList.clear (); // Initialise!

    // Build the sprite's graphic attributes from the sprite's graphic characteristics.

    bool    complete    = false;   // Initialise!
    bool    foundSprite = false;

    for (SpriteGraphicCharacteristicsList<T, U>::const_iterator itr = spriteGraphicCharacteristicsList.begin ();
         !complete && (status == ERR_SUCCESS) && (itr != spriteGraphicCharacteristicsList.end ());
         ++itr)
    {              
        // Does this sprite match the sprite in the sprite graphics atttribute table?

        if (itr->m_spriteId == spriteId)
        {
            // Yes. 
            
            foundSprite = true; // We've found the sprite.

            // Query the sprite graphics.

            SpriteGraphicsList  spriteGraphicsList;

            status = QuerySpriteGraphics<T, U> (dcHandle,
                                                resourceGraphicsCache,
                                                ownerId,
                                                drawingElementId,
                                                itr->m_spriteGraphicIdsList,
                                                spriteColour,
                                                spriteGraphicsList);

            if (status == ERR_SUCCESS)
            {
                // Add to the sprite graphic attributes list.

                spriteGraphicAttributesList.push_back (SpriteGraphicAttributesList::value_type(itr->m_direction,
                                                                                               spriteGraphicsList,
                                                                                               itr->m_action));
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
