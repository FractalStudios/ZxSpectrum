#pragma once

// "Home-made" includes.
#include    "SoundSample.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Util
{

namespace Sound
{

// Routines.

extern  FolioStatus PlaySoundSample (const SoundSample& soundSample);
extern  FolioStatus PlayAsyncSoundSample (const SoundSample& soundSample);
extern  FolioStatus PlayAsyncSoundSamples (const SoundSamplesList& soundSamplesList);

extern  FolioStatus Beep (UInt32                    duration,
                          const float&              frequency, 
                          SOUND_CHANNELS            numSoundChannels = DEFAULT_SOUND_CHANNELS,
                          UInt32                    samplesPerSecond = SoundSample::DEFAULT_SAMPLES_PER_SECOND,
                          SoundSample::SIGNAL_PROC  signalProc = SoundSample::PureToneWave);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
