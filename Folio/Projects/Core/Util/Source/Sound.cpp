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
 * Function that will load a sound resource.
 *
 * @param [in] instanceHandle
 * The application instance handle.
 *
 * @param [in] resourceId
 * The resource identifier of the sound resource to load.
 *
 * @param [out] soundHandle
 * On return, will hold the sound resource handle, if successful. If this method fails 
 * then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the sound resource was successfully loaded.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus LoadSound (FolioHandle  instanceHandle,
                       UInt16       resourceId,
                       FolioHandle& soundHandle)
{
    FolioStatus status = ERR_SUCCESS;

    // Find the WAVE resource. 
 
    FolioHandle resourceHandle = ::FindResource (static_cast<HINSTANCE> (instanceHandle), 
                                                 MAKEINTRESOURCE(resourceId), 
                                                 TXT("WAVE"));

    if (resourceHandle != NULL)
    {
        // Load the sound resource.

        soundHandle = ::LoadResource (static_cast<HINSTANCE> (instanceHandle), 
                                      static_cast<HRSRC> (resourceHandle));

        if (soundHandle == FOLIO_INVALID_HANDLE)
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

            FOLIO_LOG_CALL_ERROR_2 (TXT("LoadResource"),
                                    status,
                                    instanceHandle,
                                    resourceId);
        } // Endif.

    } // Endif.

    else
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());

        FOLIO_LOG_CALL_ERROR_2 (TXT("FindResource"),
                                status,
                                instanceHandle,
                                resourceId);
    } // Endelse.

    return (status);
} // Endproc.


 /**
 * Function that will play a sound resource.
 *
 * @param [in] soundHandle
 * The sound resource handle.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the sound resource was successfully loaded.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus PlayAsyncSound (FolioHandle soundHandle)
{
    FolioStatus status = ERR_SUCCESS;

    // Lock the sound resource and play it. 
 
    LPVOID  lpvResource = ::LockResource (soundHandle);

    if (lpvResource != NULL) 
    { 
        if (!::sndPlaySound (reinterpret_cast<LPCWSTR> (lpvResource), 
                             SND_MEMORY | SND_SYNC | SND_NODEFAULT))
        {
            status = FOLIO_MAKE_OS_ERROR(::GetLastError ());
        } // Endif.

        UnlockResource (soundHandle); 
    } // Endif.

    else
    {
        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());
    } // Endelse.

    return (status);
} // Endproc.


 /**
 * Function that will stop a sound resource.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the sound resource was successfully loaded.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus StopSound ()
{
    FolioStatus status = ERR_SUCCESS;

    if (!::sndPlaySound (NULL,
                        SND_SYNC | SND_NODEFAULT))
    {
        status = FOLIO_MAKE_OS_ERROR(::GetLastError ());
    } // Endif.

    return (status);
} // Endproc.


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

        if (!waveOut->IsOpen ())
        {
            // No. Open the waveform-audio output device.
        
            status = waveOut->Open (soundSample.GetSoundChannels (), 
                                    soundSample.GetSamplesPerSecond ());
        } // Endif.

        if (status == ERR_SUCCESS)
        {
            // Use the waveform-audio output device to play the sound.
            
            status = waveOut->Play (soundSample.GetSoundDuration (), 
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
 * Function that will play a list of sound samples.
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
FolioStatus PlaySoundSamples (const SoundSamplesList& soundSamplesList)
{
    FolioStatus status = ERR_SUCCESS;

    if (soundSamplesList.empty ())
    {
        status = ERR_INVALID_PARAM1;
    } // Endif.

    else
    {
        // Play the sound samples.

        for (SoundSamplesList::const_iterator itr = soundSamplesList.begin ();
             itr != soundSamplesList.end ();
             ++itr)
        {
            status = PlaySoundSample (*itr);
        } // Endfor.

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
FolioStatus Beep (UInt32                            soundDuration,
                  const float&                      soundFrequency, 
                  SOUND_CHANNELS                    soundChannels,
                  UInt32                            samplesPerSecond,
                  SoundSample::SOUND_SAMPLE_WAVE    soundSampleWave)
{
    return (PlaySoundSample (SoundSample(soundDuration,
                                         soundFrequency, 
                                         soundChannels,
                                         samplesPerSecond,
                                         soundSampleWave))); 
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
