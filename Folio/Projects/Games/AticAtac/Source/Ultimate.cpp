// "Home-made" includes.
#include    "StdAfx.h"
#include    "Ultimate.h"

namespace Folio
{

namespace Games
{

namespace AticAtac
{

namespace Ultimate
{

// Jump condition instruction t-states.
static  const   UInt32  TSTATE_DJNZ_B_ZERO      = 8;
static  const   UInt32  TSTATE_DJNZ_B_NOT_ZERO  = 13;


// T-state macros.
#define SOUND_FREQUENCY_TSTATES(frequency)                      7 + 11 + 11 + 10 + 11 + 4 + 11 + 10 + 4 + 7 +\
                                                                (2 * (TSTATE_DJNZ_B_ZERO + (TSTATE_DJNZ_B_NOT_ZERO * (frequency - 1))))
#define SOUND_DURATION_TSTATES(frequency, numLoops)             numLoops * (17 + 4 + 12 + SOUND_FREQUENCY_TSTATES(frequency))

#define DOOR_SOUND_FREQUENCY_TSTATES(frequency)                 7 + 6 + 11 + 8 + 4 + 4 + 11 + 10 + 4 + 7 +\
                                                                (2 * (TSTATE_DJNZ_B_ZERO + (TSTATE_DJNZ_B_NOT_ZERO * (frequency - 1))))
#define DOOR_SOUND_DURATION_TSTATES(frequency, numLoops)        numLoops * (17 + 4 + 12 + SOUND_FREQUENCY_TSTATES(frequency))


static  UInt32  CalculateSoundDuration (Folio::Core::Game::ZxSpectrum::BYTE frequency,
                                        Folio::Core::Game::ZxSpectrum::BYTE numLoops)
{
    return (Folio::Core::Game::ZxSpectrum::CalculateDuration (SOUND_DURATION_TSTATES(frequency, numLoops)));
} // Endproc.


static  float   CalculateSoundFrequency (Folio::Core::Game::ZxSpectrum::BYTE frequency)
{
    return (Folio::Core::Game::ZxSpectrum::CalculateFrequency (SOUND_FREQUENCY_TSTATES(frequency)));
} // Endproc.


static  UInt32  CalculateDoorSoundDuration (Folio::Core::Game::ZxSpectrum::BYTE frequency,
                                            Folio::Core::Game::ZxSpectrum::BYTE numLoops)
{
    return (Folio::Core::Game::ZxSpectrum::CalculateDuration (DOOR_SOUND_DURATION_TSTATES(frequency, numLoops)));
} // Endproc.


static  float   CalculateDoorSoundFrequency (Folio::Core::Game::ZxSpectrum::BYTE frequency)
{
    return (Folio::Core::Game::ZxSpectrum::CalculateFrequency (DOOR_SOUND_FREQUENCY_TSTATES(frequency)));
} // Endproc.


Folio::Core::Util::Sound::SoundSample   CreateSoundSample (Folio::Core::Game::ZxSpectrum::BYTE  frequency,
                                                           Folio::Core::Game::ZxSpectrum::BYTE  numLoops)
{
    return (Folio::Core::Util::Sound::SoundSample(CalculateSoundDuration (frequency, numLoops),
                                                  CalculateSoundFrequency (frequency)));
} // Endproc.


Folio::Core::Util::Sound::SoundSample   CreateDoorSoundSample ()
{
    return (Folio::Core::Util::Sound::SoundSample(CalculateDoorSoundDuration (0x08, 0x30),
                                                  CalculateDoorSoundFrequency (0x08)));
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
