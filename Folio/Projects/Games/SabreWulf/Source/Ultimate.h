#pragma once

// STL includes.
#include    <vector>

// "Home-made" includes.
#include    <Game.h>
#include    <Util.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

namespace Ultimate
{

// BYTE list.
typedef std::vector<Folio::Core::Game::ZxSpectrum::BYTE>    ByteList;


// Routines.

extern  Folio::Core::Util::Sound::SoundSample   CreateSoundSample (Folio::Core::Game::ZxSpectrum::BYTE  frequency,
                                                                   Folio::Core::Game::ZxSpectrum::BYTE  numLoops);
extern  Folio::Core::Util::Sound::SoundSamplesList  CreateMusicSamples (const ByteList& tune);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
