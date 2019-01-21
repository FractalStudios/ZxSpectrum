// "Home-made" includes.
#include    <Trace.h>
#include    "SoundSample.h"
#include    "WaveOut.h"

namespace Folio
{

namespace Core
{

namespace Util
{

namespace Sound
{

static  const   double PI = 3.14159265358979323846; // PI.


/**
 * The default class constructor.
 */
SoundSample::SoundSample ()
:   m_duration(0),
    m_frequency(0.0f),
    m_numSoundChannels(DEFAULT_SOUND_CHANNELS),
    m_samplesPerSecond(DEFAULT_SAMPLES_PER_SECOND),
    m_signalProc(PureToneWave)
{
} // Endproc.


/**
 * The class constructor.
 *
 * @param [in] duration
 * The sound's duration (in milliseconds).
 *
 * @param [in] frequency
 * The sound's frequency.
 *
 * @param [in] numSoundChannels
 * The number of channels to use when generating the sound sample.
 *
 * @param [in] samplesPerSecond
 * The sample frequency to use when generating the sound sample.
 *
 * @param [in] signalProc
 * The signal procedure to use when generating the sound sample.
 */
SoundSample::SoundSample (UInt32            duration,
                          const float&      frequency, 
                          SOUND_CHANNELS    numSoundChannels,
                          UInt32            samplesPerSecond,
                          SIGNAL_PROC       signalProc)
:   m_duration(duration),
    m_frequency(frequency),
    m_numSoundChannels(numSoundChannels),
    m_samplesPerSecond(samplesPerSecond),
    m_signalProc(signalProc)
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
 * @param [in] duration
 * The sound's duration (in milliseconds).
 *
 * @param [in] frequency
 * The sound's frequency.
 *
 * @param [in] numSoundChannels
 * The number of channels to use when generating the sound sample.
 *
 * @param [in] samplesPerSecond
 * The sample frequency to use when generating the sound sample.
 *
 * @param [in] signalProc
 * The signal procedure to use when generating the sound sample.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus SoundSample::Create (UInt32         duration,
                                 const float&   frequency, 
                                 SOUND_CHANNELS numSoundChannels,
                                 UInt32         samplesPerSecond,
                                 SIGNAL_PROC    signalProc)
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

        m_duration          = duration;
        m_frequency         = frequency;
        m_numSoundChannels  = numSoundChannels;
        m_samplesPerSecond  = samplesPerSecond;
        m_signalProc        = signalProc;

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

        if ((m_numSoundChannels == soundSample.m_numSoundChannels) &&
            (m_samplesPerSecond == soundSample.m_samplesPerSecond))
        {
            // Increment the sound sample's duration.

            m_duration += soundSample.m_duration;

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

        m_duration          = soundSample.m_duration;
        m_frequency         = soundSample.m_frequency;        
        m_numSoundChannels  = soundSample.m_numSoundChannels; 
        m_samplesPerSecond  = soundSample.m_samplesPerSecond; 
        m_signalProc        = soundSample.m_signalProc;
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
UInt32  SoundSample::GetDuration () const
{
    return (m_duration);
} // Endproc.


/**
 * Method that will return the sound's frequency.
 *
 * @return
 * The sound's frequency.
 */
float   SoundSample::GetFrequency () const
{
    return (m_frequency);
} // Endproc.


/**
 * Method that will return the number of sound channels used when generating 
 * the sound sample.
 *
 * @return
 * The number of sound channels used when generating the sound sample.
 */
SOUND_CHANNELS  SoundSample::GetNumSoundChannels () const
{
    return (m_numSoundChannels);
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
 * Method that will return the signal procedure used when generating 
 * the sound sample.
 *
 * @return
 * The signal procedure used when generating the sound sample.
 */
SoundSample::SIGNAL_PROC    SoundSample::GetSignalProc () const
{
    return (m_signalProc);
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
 * Function that determines an amplitude using triangle wave generation.
 *
 * @param [in] timeInSeconds
 * The time in seconds.
 *
 * @param [in] frequency
 * The sound's frequency.
 *
 * @param [in] channel
 * The sound channel.
 *
 * @return
 * The amplitude.
 */
float   SoundSample::TriangleWave (const float& timeInSeconds, 
                                   const float& frequency,
                                   UInt32       channel) 
{
    // amplitude = asin (sin (2 * pi * frequency * time + phaseOffset)) * 2 / pi

    float   angle = static_cast<float> (2 * PI * frequency * timeInSeconds);

    return (static_cast<float> ((::asin (::sin (angle + channel * PI / 2))) * 2 / PI));
} // Endproc.


/**
 * Function that determines an amplitude using pure tone wave generation.
 *
 * @param [in] timeInSeconds
 * The time in seconds.
 *
 * @param [in] frequency
 * The sound's frequency.
 *
 * @param [in] channel
 * The sound channel.
 *
 * @return
 * The amplitude.
 */
float   SoundSample::PureToneWave (const float& timeInSeconds, 
                                   const float& frequency,
                                   UInt32       channel) 
{
    // amplitude = sin (2 * pi * frequency * time + phaseOffset)

    float   angle = static_cast<float> (2 * PI * frequency * timeInSeconds);
    
    return (static_cast<float> (::sin (angle + channel * PI / 2)));
} // Endproc.


/**
 * Method that generates the sound sample.
 */
void    SoundSample::GenerateSoundSample ()
{
    m_sampleBuffer.clear ();    // Initialise!
    
    if (m_duration)
    {
        // Convert duration to seconds.

        float   seconds = static_cast<float> (m_duration / 1000.0f);

        // Calculate the sample size.

        UInt32    sampleSize = static_cast<UInt32> (seconds * m_numSoundChannels * m_samplesPerSecond + 0.5f);
        m_sampleBuffer.reserve (sampleSize);

        // Build sample buffer.

        for (UInt32 sample = 0; sample < sampleSize; sample += m_numSoundChannels)
        {
            for (UInt32 channel = 0; channel < static_cast<UInt32> (m_numSoundChannels); ++channel)
            {
                float   amplitude = m_signalProc ((sample + channel) * seconds / sampleSize, m_frequency, channel);

                m_sampleBuffer.push_back (static_cast<SampleBuffer::value_type> (amplitude * 127.0f));
            } // Endfor.

        } // Endfor.

    } // Endif.

    else
    {
        FOLIO_DEBUG_BREAK;
    } // Endelse.

} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
