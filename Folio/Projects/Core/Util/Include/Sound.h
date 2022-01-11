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

extern  FolioStatus LoadSoundResource (FolioHandle      instanceHandle,
                                       UInt16           resourceId,
                                       FolioHandle&     soundHandle);
extern  FolioStatus PlaySoundResource (FolioHandle  soundHandle,
                                       bool         playAsynchronously = true);
extern  FolioStatus StopPlayingSoundResource (FolioHandle soundHandle);

extern  FolioStatus PlaySoundSample (const SoundSample& soundSample,
                                     bool               playAsynchronously = true);
extern  FolioStatus PlaySoundSamples (const SoundSamplesList&   soundSamplesList,
                                      bool                      playAsynchronously = true);
extern  FolioStatus StopPlayingSoundSamples ();
extern  bool    IsPlayingSoundSamples ();

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
