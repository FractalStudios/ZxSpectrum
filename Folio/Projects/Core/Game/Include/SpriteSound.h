#pragma once

// STL includes.
#include    <memory>
#include    <vector>

// "Home-made" includes.
#include    <Util.h>
#include    "SpriteGraphics.h"

#pragma pack(push, 1)

namespace Folio        
{

namespace Core
{

namespace Game
{

// Sprite sound sample.
typedef std::shared_ptr<Folio::Core::Util::Sound::SoundSample>  SpriteSoundSample;

// Sprite sound samples list.
typedef std::vector<SpriteSoundSample>  SpriteSoundSamplesList;


// Sprite movement sound sample.
class SpriteMovementSoundSample
{
public:
    SpriteMovementSoundSample (Direction                        direction,
                               const SpriteSoundSamplesList&    spriteSoundSamplesList)
    :   m_direction(direction),
        m_spriteSoundSamplesList(spriteSoundSamplesList)
    {} // Endproc.
    
    Direction               m_direction;                // The direction(s) of the sprite.
    SpriteSoundSamplesList  m_spriteSoundSamplesList;   // The sprite sound samples representing the sprite's direction(s).
}; // Endclass.

// Sprite movement sound samples list.
typedef std::vector<SpriteMovementSoundSample>  SpriteMovementSoundSamplesList;


// Sprite stationary sound sample.
class SpriteStationarySoundSample
{
public:
    SpriteStationarySoundSample ()
    :   m_numSpriteSoundSamplesPerFrame(0)
    {} // Endproc.

    SpriteStationarySoundSample (const SpriteSoundSample&   spriteSoundSample,
                                 UInt32                     numSpriteSoundSamplesPerFrame = 1)
    :   m_spriteSoundSample(spriteSoundSample),
        m_numSpriteSoundSamplesPerFrame(numSpriteSoundSamplesPerFrame)
    {} // Endproc.

    SpriteStationarySoundSample (const Folio::Core::Util::Sound::SoundSample&   soundSample,
                                 UInt32                                         numSpriteSoundSamplesPerFrame = 1)
    :   m_spriteSoundSample(new Folio::Core::Game::SpriteSoundSample::element_type(soundSample)),
        m_numSpriteSoundSamplesPerFrame(numSpriteSoundSamplesPerFrame)
    {} // Endproc.

    operator Folio::Core::Util::Sound::SoundSample () const
    {
        return (*m_spriteSoundSample);
    } // Endproc.

    operator Folio::Core::Util::Sound::SoundSamplesList () const
    {
        return (Folio::Core::Util::Sound::SoundSamplesList(m_numSpriteSoundSamplesPerFrame, *m_spriteSoundSample));
    } // Endproc.

    SpriteSoundSample   m_spriteSoundSample;                // The sprite sound sample.
    UInt32              m_numSpriteSoundSamplesPerFrame;    // The number of sprite sound samples per frane.
}; // Endclass.

// Sprite stationary sound samples list.
typedef std::vector<SpriteStationarySoundSample>    SpriteStationarySoundSamplesList;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
