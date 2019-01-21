#pragma once

// "Home-made" includes.
#include    <Util.h>
#include    "ASprite.h"

#pragma pack(push, 1)

namespace Folio        
{

namespace Core
{

namespace Game
{

template <typename T>
class SpriteMovementSoundAttributes
{
public:
    // Sprite movement sound samples list.
    typedef Folio::Core::Util::Sound::SoundSamplesList  SpriteMovementSoundSamplesList;

    T                               m_spriteId;                         // The identifier of the sprite.
    ASprite::Direction              m_direction;                        // The direction of the sprite.
    SpriteMovementSoundSamplesList  m_spriteMovementSoundSamplesList;   // The sprite movement sound samples for the sprite's direction.
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
