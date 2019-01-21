// "Home-made" includes.
#include    <Trace.h>
#include    "AsyncSound.h"
#include    "Sound.h"
#include    "WaveOut.h"

namespace Folio
{

namespace Core
{

namespace Util
{

namespace Sound
{

/**
 * Function that will play a sound sample.
 *
 * @param [in] soundSample
 * The sound sample to play.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus PlaySoundSample (const SoundSample& soundSample)
{
    FolioStatus status = ERR_SUCCESS;

    // Get the waveform-audio output device instance.
        
    WaveOut *waveOut = WaveOut::GetInstance ();

    if (waveOut)
    {
        // Is the waveform-audio output device open?

        if (waveOut->IsOpen ())
        {
            // Yes. Reset the waveform-audio output device.
        
            status = waveOut->Reset ();
        } // Endif.

        else
        {
            // No. Open the waveform-audio output device.
        
            status = waveOut->Open (soundSample.GetNumSoundChannels (), 
                                    soundSample.GetSamplesPerSecond ());
        } // Endelse.

        if (status == ERR_SUCCESS)
        {
            // Use the waveform-audio output device to play the sound.
            
            status = waveOut->Play (soundSample.GetDuration (), 
                                    soundSample.GetSampleBuffer ());
        } // Endif.

    } // Endif.
 
    else
    {
        status = ERR_INTERNAL_ERROR;
    } // Endelse.
    
    return (status);
} // Endproc.


/**
 * Function that will play a sound sample asynchronously.
 *
 * @param [in] soundSample
 * The sound sample to play.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus PlayAsyncSoundSample (const SoundSample& soundSample)
{
    FolioStatus status = ERR_SUCCESS;

    // Get the asynchronous sound.
        
    AsyncSound  *asyncSound = AsyncSound::GetInstance ();

    if (asyncSound)
    {
        // Use the asynchronous sound to play the sound sample.

        status = asyncSound->PlaySoundSample (soundSample);
    } // Endif.
 
    else
    {
        status = ERR_INTERNAL_ERROR;
    } // Endelse.
    
    return (status);
} // Endproc.


/**
 * Function that will play a list of sound samples asynchronously.
 *
 * @param [in] soundSamplesList
 * The list of sound samples to play.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus PlayAsyncSoundSamples (const SoundSamplesList& soundSamplesList)
{
    FolioStatus status = ERR_SUCCESS;

    if (soundSamplesList.empty ())
    {
        status = ERR_INVALID_PARAM1;
    } // Endif.

    else
    {
        // Get the asynchronous sound.
        
        AsyncSound  *asyncSound = AsyncSound::GetInstance ();

        if (asyncSound)
        {
            // Use the asynchronous sound to play the list of sound samples.

            status = asyncSound->PlaySoundSamples (soundSamplesList);
        } // Endif.
 
        else
        {
            status = ERR_INTERNAL_ERROR;
        } // Endelse.
    
    } // Endelse.
    
    return (status);
} // Endproc.


/**
 * Function that makes a sound for a specified duration and frequency.
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
FolioStatus Beep (UInt32                    duration,
                  const float&              frequency, 
                  SOUND_CHANNELS            numSoundChannels,
                  UInt32                    samplesPerSecond,
                  SoundSample::SIGNAL_PROC  signalProc)
{
    return (PlaySoundSample (SoundSample(duration,
                                         frequency, 
                                         numSoundChannels,
                                         samplesPerSecond,
                                         signalProc))); 
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
