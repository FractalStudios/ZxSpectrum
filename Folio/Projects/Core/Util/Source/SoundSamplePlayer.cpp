// "Home-made" includes.
#include    "SoundSamplePlayer.h"

namespace Folio
{

namespace Core
{

namespace Util
{

namespace Sound
{

/**
 * The default class constructor.
 */
SoundSamplePlayer::SoundSamplePlayer ()
{
} // Endproc.


/**
 * The class destructor.
 */
SoundSamplePlayer::~SoundSamplePlayer ()
{
} // Endproc.


/**
 * Method that will play a sound sample.
 *
 * @param [in] soundSample
 * The sound sample to play.
 *
 * @param [in] playAsynchronously
 * <b>true</b> if a the sound sample should be played asynchronously, 
 * <b>false</b> otherwise.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus SoundSamplePlayer::Play (const SoundSample& soundSample,
                                     bool               playAsynchronously)
{
    FolioStatus status = ERR_SUCCESS;

    // Has the sound sample been generated?

    if (soundSample.IsSoundSampleGenerated ())
    {
        // Yes. Start playing a sound sample using the wave out device.
                
        WaveOutDevice::SoundSampleId    soundSampleId = WaveOutDevice::UNDFINED_SOUND_SAMPLE_ID;    // Initialise!

        status = m_waveOutDevice.StartPlayingSoundSample (soundSample, 
                                                          playAsynchronously, 
                                                          soundSampleId);

        if (!playAsynchronously && (status == ERR_SUCCESS))
        {
            // Wait for the wave out device to stop playing the sound sample.

            status = m_waveOutDevice.WaitUntilStoppedPlayingSoundSample (soundSampleId, 
                                                                         FOLIO_FINITE);
        } // Endif.

    } // Endif.

    else
    {
        // No.

        status = ERR_INVALID_PARAM1;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will stop all currently playing sound samples.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus SoundSamplePlayer::Stop ()
{
    // Stop the wave out device playing all currently playing sound samples.

    return (m_waveOutDevice.StopPlayingSoundSamples ());
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
