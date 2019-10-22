// "Home-made" includes.
#include    "StdAfx.h"
#include    "Ultimate.h"

namespace Folio
{

namespace Games
{

namespace Ultimate
{

UInt32  MapMakeSoundDuration (Folio::Core::Game::ZxSpectrum::BYTE   frequency,
                              Folio::Core::Game::ZxSpectrum::BYTE   numLoops)
{
    static  const   UInt32  TSTATE_DJNZ_B_ZERO      = 8;   
    static  const   UInt32  TSTATE_DJNZ_B_NOT_ZERO  = 13;

    float   numTStatesPerLoop = 91.0f + 2.0f * (TSTATE_DJNZ_B_ZERO + (TSTATE_DJNZ_B_NOT_ZERO * (frequency - 1)));

    return (std::max(static_cast<UInt32> (1), static_cast<UInt32> (numTStatesPerLoop * numLoops / Folio::Core::Game::ZxSpectrum::CLOCK_FREQUENCY * 1000.0f + 0.5f)));
} // Endproc.


float   MapMakeSoundFrequency (Folio::Core::Game::ZxSpectrum::BYTE frequency)
{
    static  const   UInt32  TSTATE_DJNZ_B_ZERO      = 8;   
    static  const   UInt32  TSTATE_DJNZ_B_NOT_ZERO  = 13;

    float   numTStatesForFrequency = 47.0f + 2.0f * (TSTATE_DJNZ_B_ZERO + (TSTATE_DJNZ_B_NOT_ZERO * (frequency - 1)));

    return (Folio::Core::Game::ZxSpectrum::CLOCK_FREQUENCY / numTStatesForFrequency);
} // Endproc.


Folio::Core::Util::Sound::SoundSample   MapMakeSound (Folio::Core::Game::ZxSpectrum::BYTE   frequency,
                                                      Folio::Core::Game::ZxSpectrum::BYTE   numLoops)
{
    return (Folio::Core::Util::Sound::SoundSample(MapMakeSoundDuration (frequency, numLoops),
                                                  MapMakeSoundFrequency (frequency)));
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
