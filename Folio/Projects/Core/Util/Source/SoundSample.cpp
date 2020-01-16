// "Home-made" includes.
#include    <Trace.h>
#include    "SoundSample.h"

namespace Folio
{

namespace Core
{

namespace Util
{

namespace Sound
{

static  const   double PI = 3.14159265358979323846; // PI.

static  const   float   DUTY_CYCLE  = 0.5f; // Required duty cycle.


/**
 * The default class constructor.
 */
SoundSample::SoundSample ()
:   m_soundDuration(0),
    m_soundFrequency(0.0f),
    m_soundChannels(DEFAULT_SOUND_CHANNELS),
    m_samplesPerSecond(DEFAULT_SAMPLES_PER_SECOND),
    m_soundSampleWave(DEFAULT_SOUND_SAMPLE_WAVE)
{
} // Endproc.


/**
 * The class constructor.
 *
 * @param [in] soundDuration
 * The sound's duration (in milliseconds).
 *
 * @param [in] soundFrequency
 * The sound's frequency.
 *
 * @param [in] soundChannels
 * The sound channels to use when generating the sound sample.
 *
 * @param [in] samplesPerSecond
 * The sample frequency to use when generating the sound sample.
 *
 * @param [in] soundSampleWave
 * The wave type algorithm to use when generating the sound sample.
 */
SoundSample::SoundSample (UInt32            soundDuration,
                          const float&      soundFrequency, 
                          SOUND_CHANNELS    soundChannels,
                          UInt32            samplesPerSecond,
                          SOUND_SAMPLE_WAVE soundSampleWave)
:   m_soundDuration(soundDuration),
    m_soundFrequency(soundFrequency),
    m_soundChannels(soundChannels),
    m_samplesPerSecond(samplesPerSecond),
    m_soundSampleWave(soundSampleWave)
{
    // Generate the sound sample.

    GenerateSoundSample ();
} // Endproc.


/**
 * The class destructor.
 */
SoundSample::~SoundSample ()
{
} // Endproc.


/**
 * Method that will create the sound sample.
 *
 * @param [in] soundDuration
 * The sound's duration (in milliseconds).
 *
 * @param [in] soundFrequency
 * The sound's frequency.
 *
 * @param [in] soundChannels
 * The sound channels to use when generating the sound sample.
 *
 * @param [in] samplesPerSecond
 * The sample frequency to use when generating the sound sample.
 *
 * @param [in] soundSampleWave
 * The wave type algorithm to use when generating the sound sample.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus SoundSample::Create (UInt32             soundDuration,
                                 const float&       soundFrequency, 
                                 SOUND_CHANNELS     soundChannels,
                                 UInt32             samplesPerSecond,
                                 SOUND_SAMPLE_WAVE  soundSampleWave)
{
    FolioStatus status = ERR_SUCCESS;

    // Has the sound sample been generated?

    if (IsSoundSampleGenerated ())
    {
        // Yes.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // No. Note the sound sample attributes.

        m_soundDuration     = soundDuration;
        m_soundFrequency    = soundFrequency;
        m_soundChannels     = soundChannels;
        m_samplesPerSecond  = samplesPerSecond;
        m_soundSampleWave   = soundSampleWave;

        // Generate the sound sample.

        GenerateSoundSample ();
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will add a sound sample to this sound sample.
 *
 * @param [in] soundSample
 * The sound sample to add.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus SoundSample::AddSoundSample (const SoundSample& soundSample)
{
    FolioStatus status = ERR_SUCCESS;

    // Has a sound sample been generated?

    if (IsSoundSampleGenerated ())
    {
        // No. Verify the sound sample attributes.

        if ((m_soundChannels == soundSample.m_soundChannels) &&
            (m_samplesPerSecond == soundSample.m_samplesPerSecond))
        {
            // Increment the sound sample's duration.

            m_soundDuration += soundSample.m_soundDuration;

            // Add the sound sample buffer.

            m_sampleBuffer.insert (m_sampleBuffer.end (), 
                                   soundSample.m_sampleBuffer.begin (), 
                                   soundSample.m_sampleBuffer.end ());
        } // Endif.

        else
        {
            status = ERR_INVALID_PARAM1;
        } // Endelse.

    } // Endif.

    else
    {
        // No. Note the sound sample attributes.

        m_soundDuration     = soundSample.m_soundDuration;
        m_soundFrequency    = soundSample.m_soundFrequency;        
        m_soundChannels     = soundSample.m_soundChannels; 
        m_samplesPerSecond  = soundSample.m_samplesPerSecond; 
        m_soundSampleWave   = soundSample.m_soundSampleWave;
        m_sampleBuffer      = soundSample.m_sampleBuffer;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will return the sound's duration.
 *
 * @return
 * The sound's duration (in milliseconds).
 */
UInt32  SoundSample::GetSoundDuration () const
{
    return (m_soundDuration);
} // Endproc.


/**
 * Method that will return the sound's frequency.
 *
 * @return
 * The sound's frequency.
 */
float   SoundSample::GetSoundFrequency () const
{
    return (m_soundFrequency);
} // Endproc.


/**
 * Method that will return the sound channels used when generating the sound 
 * sample.
 *
 * @return
 * The sound channels used when generating the sound sample.
 */
SOUND_CHANNELS  SoundSample::GetSoundChannels () const
{
    return (m_soundChannels);
} // Endproc.


/**
 * Method that will return the sample frequency used when generating 
 * the sound sample.
 *
 * @return
 * The sample frequency used when generating the sound sample.
 */
UInt32  SoundSample::GetSamplesPerSecond () const
{
    return (m_samplesPerSecond);
} // Endproc.


/**
 * Method that will return the wave type algorithm used to generate the sound sample.
 *
 * @return
 * The wave type algorithm used to generate the sound sample.
 */
SoundSample::SOUND_SAMPLE_WAVE  SoundSample::GetSoundSampleWave () const
{
    return (m_soundSampleWave);
} // Endproc.


/**
 * Method that will return the sound sample buffer.
 *
 * @return
 * The sound sample buffer.
 */
const SoundSample::SampleBuffer&  SoundSample::GetSampleBuffer () const
{
    return (m_sampleBuffer);
} // Endproc.


/**
 * Method that indicates if the sound sample has been generated.
 *
 * @return
 * <b>true</b> if the sound sample has been generated, <b>false</b> otherwise.
 */
bool    SoundSample::IsSoundSampleGenerated () const
{
    return (!m_sampleBuffer.empty ());
} // Endproc.


/**
 * Method that generates the sound sample.
 */
void    SoundSample::GenerateSoundSample ()
{
    m_sampleBuffer.clear ();    // Initialise!
    
    if (m_soundDuration)
    {
        // Convert sound duration to seconds.

        float   seconds = static_cast<float > (m_soundDuration / 1000.0f);

        // Calculate the number of samples.

        UInt32    numSamples = static_cast<UInt32> (std::round (seconds * m_soundChannels * m_samplesPerSecond));
        m_sampleBuffer.reserve (numSamples);

        // Generate the sound sample.

        switch (m_soundSampleWave)
        {
        case TRIANGLE_WAVE:
            GenerateTriangleWave (seconds, numSamples);
            break;

        case PURE_TONE_WAVE:
            GeneratePureToneWave (seconds, numSamples);
            break;

        case SQUARE_WAVE:
            GenerateSquareWave (seconds, numSamples);
            break;

        case BAND_LIMITED_SQUARE_WAVE:
            GenerateBandLimitedSquareWave (seconds, numSamples);
            break;

        default:
            break;
        } // Endswitch.

    } // Endif.

} // Endproc.


/**
 * Function that generates a triangle wave.
 *
 * @param [in] seconds
 * The sound's duration (in seconds).
 *
 * @param [in] numSamples
 * The number of samples to use when generating the sound sample.
 */
void    SoundSample::GenerateTriangleWave (const float& seconds,
                                           UInt32       numSamples)
{
    // Build sample buffer.

    m_sampleBuffer.clear ();  // Initialise!

    for (UInt32 sample = 0; sample < numSamples; sample += m_soundChannels)
    {
        for (UInt32 channel = 0; channel < static_cast<UInt32> (m_soundChannels); ++channel)
        {
            float   amplitude = TriangleWave ((sample + channel) * seconds / numSamples, channel);

            m_sampleBuffer.push_back (static_cast<SampleBuffer::value_type> (std::round (amplitude * DEFAULT_VOLUME)));
        } // Endfor.

    } // Endfor.

} // Endproc.


/**
 * Function that generates a pure tone wave.
 *
 * @param [in] seconds
 * The sound's duration (in seconds).
 *
 * @param [in] numSamples
 * The number of samples to use when generating the sound sample.
 */
void    SoundSample::GeneratePureToneWave (const float&     seconds,
                                           UInt32           numSamples)
{
    // Build sample buffer.

    m_sampleBuffer.clear ();  // Initialise!

    for (UInt32 sample = 0; sample < numSamples; sample += m_soundChannels)
    {
        for (UInt32 channel = 0; channel < static_cast<UInt32> (m_soundChannels); ++channel)
        {
            float   amplitude = PureToneWave ((sample + channel) * seconds / numSamples, channel);

            m_sampleBuffer.push_back (static_cast<SampleBuffer::value_type> (std::round (amplitude * DEFAULT_VOLUME)));
        } // Endfor.

    } // Endfor.

} // Endproc.


/**
 * Function that generates a square wave.
 *
 * @param [in] seconds
 * The sound's duration (in seconds).
 *
 * @param [in] numSamples
 * The number of samples to use when generating the sound sample.
 */
void    SoundSample::GenerateSquareWave (const float&   seconds,
                                         UInt32         numSamples)
{
    float   scaler = m_soundFrequency / m_samplesPerSecond;

    // Build sample buffer.

    m_sampleBuffer.clear ();  // Initialise!

    for (UInt32 sample = 0; sample < numSamples / m_soundChannels; ++sample)
    {
        float   amplitude = std::round (SquareWave (sample, scaler) * DEFAULT_VOLUME);

        for (UInt32 channel = 0; channel < static_cast<UInt32> (m_soundChannels); ++channel)
        {
            m_sampleBuffer.push_back (static_cast<SampleBuffer::value_type> (amplitude));
        } // Endfor.

    } // Endfor.

} // Endproc.


/**
 * Function that generates a band limited square wave.
 *
 * @param [in] seconds
 * The sound's duration (in seconds).
 *
 * @param [in] numSamples
 * The number of samples to use when generating the sound sample.
 */
void    SoundSample::GenerateBandLimitedSquareWave (const float&    seconds,
                                                    UInt32          numSamples)
{
    // Calculate harmonic amplitudes.

    UInt32  numHarmonics = static_cast<UInt32> (std::round (m_samplesPerSecond / (m_soundFrequency * 2.0f)));

    // Build harmonic amplitudes.

    Coefficients    coefficients;
    coefficients.reserve (numHarmonics + 1);

    coefficients.push_back (DUTY_CYCLE - 0.5f);    // Start with DC coefficient.

    for (UInt32 i = 1; i < numHarmonics; ++i)
    {
        coefficients.push_back (static_cast<float> (2.0 * std::sin (i * DUTY_CYCLE * PI) / (i * PI)));
    } // Endfor.

    float   scaler = static_cast<float> (m_soundFrequency * PI * 2.0 / m_samplesPerSecond);

    // Build sample buffer.

    m_sampleBuffer.clear ();  // Initialise!

    for (UInt32 sample = 0; sample < numSamples / m_soundChannels; ++sample)
    {
        float    amplitude = std::round (BandLimitedSquareWave (sample, scaler, coefficients) * DEFAULT_VOLUME);

        for (UInt32 channel = 0; channel < static_cast<UInt32> (m_soundChannels); ++channel)
        {
            m_sampleBuffer.push_back (static_cast<SampleBuffer::value_type> (amplitude));
        } // Endfor.

    } // Endfor.

} // Endproc.


/**
 * Function that determines an amplitude using triangle wave generation.
 *
 * @param [in] time
 * The time.
 *
 * @param [in] channel
 * The sound channel.
 *
 * @return
 * The amplitude.
 */
float   SoundSample::TriangleWave (const float& time,
                                   UInt32       channel) 
{
    // amplitude = asin (sin (2 * pi * frequency * time + phaseOffset)) * 2 / pi

    float   angle = static_cast<float> (2.0 * PI * m_soundFrequency * time);

    return (static_cast<float> ((std::asin (std::sin (angle + channel * PI / 2.0))) * 2.0 / PI));
} // Endproc.


/**
 * Function that determines an amplitude using pure tone wave generation.
 *
 * @param [in] time
 * The time.
 *
 * @param [in] channel
 * The sound channel.
 *
 * @return
 * The amplitude.
 */
float   SoundSample::PureToneWave (const float& time, 
                                   UInt32       channel) 
{
    // amplitude = sin (2 * pi * frequency * time + phaseOffset)

    float    angle = static_cast<float> (2.0 * PI * m_soundFrequency * time);
    
    return (static_cast<float> (std::sin (angle + channel * PI / 2.0)));
} // Endproc.


/**
 * Function that determines an amplitude using square wave generation.
 *
 * @param [in] sample
 * The current sample.
 *
 * @param [in] scaler
 * The sound's scaler.
 *
 * @return
 * The amplitude.
 */
float   SoundSample::SquareWave (UInt32         sample,
                                 const float&   scaler)
{
    return (std::fmod (sample * scaler + DUTY_CYCLE / 2.0f, 1.0f) < DUTY_CYCLE ? 0.5f : -0.5f);
} // Endproc.


/**
 * Function that determines an amplitude using band limited square wave generation.
 *
 * @param [in] seconds
 * The time in seconds.
 *
 * @param [in] scaler
 * The sound's scaler.
 *
 * @return
 * The amplitude.
 */
float   SoundSample::BandLimitedSquareWave (UInt32              sample,
                                            const float&        scaler,
                                            const Coefficients& coefficients)
{
    float    scale = sample * scaler;

    float    angle = coefficients [0];

    for (UInt32 i = 1; i < coefficients.size (); ++i)
    {
        angle += std::cos (i * scale) * coefficients [i];
    } // Endfor.

    return (angle);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
