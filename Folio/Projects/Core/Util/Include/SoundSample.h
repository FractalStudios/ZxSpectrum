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
    DEFAULT_SOUND_CHANNELS = STEREO,
}; // Endenum.


/// Sound sample class.
class SoundSample
{
public:
    /// The default samples per second.
    static  const   UInt32  DEFAULT_SAMPLES_PER_SECOND = 44100;

    // Sound sample wave enumeration.
    enum SOUND_SAMPLE_WAVE
    {
        TRIANGLE_WAVE = 0,
        PURE_TONE_WAVE,
        SQUARE_WAVE,
        BAND_LIMITED_SQUARE_WAVE,
        DEFAULT_SOUND_SAMPLE_WAVE = PURE_TONE_WAVE,
    }; // Endenum

    SoundSample ();
    SoundSample (UInt32             soundDuration,
                 const float&       soundFrequency, 
                 SOUND_CHANNELS     soundChannels = DEFAULT_SOUND_CHANNELS,
                 UInt32             samplesPerSecond = DEFAULT_SAMPLES_PER_SECOND,
                 SOUND_SAMPLE_WAVE  soundSampleWave = DEFAULT_SOUND_SAMPLE_WAVE);
    ~SoundSample ();

    FolioStatus Create (UInt32              soundDuration,
                        const float&        soundFrequency, 
                        SOUND_CHANNELS      soundChannels = DEFAULT_SOUND_CHANNELS,
                        UInt32              samplesPerSecond = DEFAULT_SAMPLES_PER_SECOND,
                        SOUND_SAMPLE_WAVE   soundSampleWave = DEFAULT_SOUND_SAMPLE_WAVE);
    FolioStatus AddSoundSample (const SoundSample& soundSample);

    UInt32              GetSoundDuration () const;
    float               GetSoundFrequency () const;
    SOUND_CHANNELS      GetSoundChannels () const;
    UInt32              GetSamplesPerSecond () const;
    SOUND_SAMPLE_WAVE   GetSoundSampleWave () const;
    
    /// Sample buffer.
    typedef std::vector<UInt8>  SampleBuffer;

    const SampleBuffer& GetSampleBuffer () const;

    bool    IsSoundSampleGenerated () const;

private:
    static  const   UInt32  DEFAULT_VOLUME = 127;

    UInt32              m_soundDuration;    ///< The sound's duration (in milliseconds).
    float               m_soundFrequency;   ///< The sound's frequency.
    SOUND_CHANNELS      m_soundChannels;    ///< The sound channels to use when generating the sound sample.
    UInt32              m_samplesPerSecond; ///< The sample frequency to use when generating the sound sample.
    SOUND_SAMPLE_WAVE   m_soundSampleWave;  ///< The wave type algorithm to use when generating the sound sample.

    SampleBuffer    m_sampleBuffer; ///< Holds the generated sound sample.

    // Coefficients.
    typedef std::vector<float>  Coefficients;  

    void    GenerateSoundSample ();

    void    GenerateTriangleWave (const float&  seconds,
                                  UInt32        numSamples);
    void    GeneratePureToneWave (const float&  seconds,
                                  UInt32        numSamples);
    void    GenerateSquareWave (const float&    seconds,
                                UInt32          numSamples);
    void    GenerateBandLimitedSquareWave (const float& seconds,
                                           UInt32       numSamples);

    float   TriangleWave (const float&  time, 
                          UInt32        channel);
    float   PureToneWave (const float&  time, 
                          UInt32        channel); 
    float   SquareWave (UInt32          sample,
                        const float&    scaler);
    float   BandLimitedSquareWave (UInt32               sample,
                                   const float&         scaler,
                                   const Coefficients&  coefficients); 
}; // Endclass.

// Sound samples list.
typedef std::vector<SoundSample>    SoundSamplesList;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
