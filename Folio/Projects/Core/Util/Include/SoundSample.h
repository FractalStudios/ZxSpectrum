#pragma once

// STL includes.
#include    <vector>

// "Home-made" includes.
#include    <Base.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Util
{

namespace Sound
{

/// Sound channels enumeration.
enum SOUND_CHANNELS
{
    MONO = 1,
    STEREO = 2,
    DEFAULT_SOUND_CHANNELS = MONO,
}; // Endenum.


/// Sound sample class.
class SoundSample
{
public:
    /// The default samples per second.
    static  const   UInt32  DEFAULT_SAMPLES_PER_SECOND = 44100;

    /// Signal procedure type. 
    typedef float (* SIGNAL_PROC) (const float& timeInSeconds, 
                                   const float& frequency,
                                   UInt32       channel);
    
    /// Sample buffer (for WAVE_FORMAT_PCM). 
    typedef std::vector<UInt8>  SampleBuffer;

    SoundSample ();
    SoundSample (UInt32         duration,
                 const float&   frequency, 
                 SOUND_CHANNELS numSoundChannels = DEFAULT_SOUND_CHANNELS,
                 UInt32         samplesPerSecond = DEFAULT_SAMPLES_PER_SECOND,
                 SIGNAL_PROC    signalProc = PureToneWave);
    ~SoundSample ();

    FolioStatus Create (UInt32          duration,
                        const float&    frequency, 
                        SOUND_CHANNELS  numSoundChannels = DEFAULT_SOUND_CHANNELS,
                        UInt32          samplesPerSecond = DEFAULT_SAMPLES_PER_SECOND,
                        SIGNAL_PROC     signalProc = PureToneWave);
    FolioStatus AddSoundSample (const SoundSample& soundSample);

    UInt32          GetDuration () const;
    float           GetFrequency () const;
    SOUND_CHANNELS  GetNumSoundChannels () const;
    UInt32          GetSamplesPerSecond () const;
    SIGNAL_PROC     GetSignalProc () const;
    
    const SampleBuffer& GetSampleBuffer () const;

    bool    IsSoundSampleGenerated () const;

    static  float   TriangleWave (const float&  timeInSeconds, 
                                  const float&  frequency,
                                  UInt32        channel = 0);
    static  float   PureToneWave (const float&  timeInSeconds, 
                                  const float&  frequency,
                                  UInt32        channel = 0);

private:
    UInt32          m_duration;         ///< The sound's duration (in milliseconds).
    float           m_frequency;        ///< The sound's frequency.
    SOUND_CHANNELS  m_numSoundChannels; ///< The number of sound channels to use when generating the sound sample.
    UInt32          m_samplesPerSecond; ///< The sample frequency to use when generating the sound sample.
    SIGNAL_PROC     m_signalProc;       ///< The signal procedure to use when generating the sound sample.

    SampleBuffer    m_sampleBuffer; ///< Holds the generated sound sample.

    void    GenerateSoundSample ();
}; // Endclass.

// Sound samples list.
typedef std::vector<SoundSample>    SoundSamplesList;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
