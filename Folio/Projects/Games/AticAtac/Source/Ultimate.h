#pragma once

// "Home-made" includes.
#include    <Game.h>
#include    <Util.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace AticAtac
{

namespace Ultimate
{

// Routines.

extern  Folio::Core::Util::Sound::SoundSample   CreateSoundSample (Folio::Core::Game::ZxSpectrum::BYTE  frequency,
                                                                   Folio::Core::Game::ZxSpectrum::BYTE  numLoops);
extern  Folio::Core::Util::Sound::SoundSample   CreateDoorSoundSample ();

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
