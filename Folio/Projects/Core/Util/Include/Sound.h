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

extern  FolioStatus LoadSound (FolioHandle  instanceHandle,
                               UInt16       resourceId,
                               FolioHandle& soundHandle);
extern  FolioStatus PlayAsyncSound (FolioHandle soundHandle);
extern  FolioStatus PlaySoundSample (const SoundSample& soundSample);
extern  FolioStatus PlaySoundSamples (const SoundSamplesList& soundSamplesList);
extern  FolioStatus PlayAsyncSoundSample (const SoundSample& soundSample);
extern  FolioStatus PlayAsyncSoundSamples (const SoundSamplesList& soundSamplesList);

extern  FolioStatus Beep (UInt32                            soundDuration,
                          const float&                      soundFrequency, 
                          SOUND_CHANNELS                    soundChannels = DEFAULT_SOUND_CHANNELS,
                          UInt32                            samplesPerSecond = SoundSample::DEFAULT_SAMPLES_PER_SECOND,
                          SoundSample::SOUND_SAMPLE_WAVE    soundSampleWave = SoundSample::DEFAULT_SOUND_SAMPLE_WAVE);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
