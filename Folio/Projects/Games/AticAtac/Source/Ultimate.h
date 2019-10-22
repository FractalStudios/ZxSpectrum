#pragma once

// "Home-made" includes.
#include    <Game.h>
#include    <Util.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace Ultimate
{

// Routines.

extern  UInt32  MapMakeSoundDuration (Folio::Core::Game::ZxSpectrum::BYTE   frequency,
                                      Folio::Core::Game::ZxSpectrum::BYTE   numLoops);
extern  float   MapMakeSoundFrequency (Folio::Core::Game::ZxSpectrum::BYTE frequency);
extern  Folio::Core::Util::Sound::SoundSample   MapMakeSound (Folio::Core::Game::ZxSpectrum::BYTE   frequency,
                                                              Folio::Core::Game::ZxSpectrum::BYTE   numLoops);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
