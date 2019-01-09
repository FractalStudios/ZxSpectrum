#pragma once

// STL includes.
#include    <vector>

// "Home-made" includes.
#include    <ASprite.h>

#pragma pack(push, 1)

namespace Folio        
{

namespace Core
{

namespace Game
{

template <typename T, typename U>
class SpriteGraphicsAttributes
{
public:
    // Sprite graphic identifiers list.
    typedef std::vector<U>  SpriteGraphicIdsList;

    T                       m_spriteId;             // The identifier of the sprite.
    ASprite::Direction      m_direction;            // The direction of the sprite.
    SpriteGraphicIdsList    m_spriteGraphicIdsList; // The sprite graphic identifiers representing the sprite's direction.
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
