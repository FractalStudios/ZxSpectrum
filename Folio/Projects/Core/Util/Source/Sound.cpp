// "Home-made" includes.
#include    <Trace.h>
#include    "Sound.h"
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
FolioStatus LoadSoundResource (FolioHandle      instanceHandle,
                               UInt16           resourceId,
                               FolioHandle&     soundHandle)
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
 * <li><b>ERR_SUCCESS</b> if the sound resource was successfully played.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus PlaySoundResource (FolioHandle soundHandle)
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
 * Function that will stop playing a sound resource.
 *
 * @param [in] soundHandle
 * The sound resource handle.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the sound resource was successfully stopped.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus StopPlayingSoundResource (FolioHandle soundHandle)
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
FolioStatus PlaySoundSample (const SoundSample& soundSample,
                             bool               playAsynchronously)
{
    FolioStatus status = ERR_SUCCESS;

    // Has the sound sample been generated?

    if (soundSample.IsSoundSampleGenerated ())
    {
        // Yes. Get the sound sample player instance.
        
        SoundSamplePlayer*  soundSamplePlayer = SoundSamplePlayer::GetInstance ();

        if (soundSamplePlayer)
        {
            // Play the sound sample.
            
            status = soundSamplePlayer->Play (soundSample, playAsynchronously);
        } // Endif.
 
        else
        {
            status = ERR_INTERNAL_ERROR;
        } // Endelse.

    } // Endif.

    else
    {
        // No.

        status = ERR_INVALID_PARAM1;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Function that will play a list of sound samples.
 *
 * @param [in] soundSamplesList
 * The list of sound samples to play.
 *
 * @param [in] playAsynchronously
 * <b>true</b> if a the sound samples should be played asynchronously, 
 * <b>false</b> otherwise.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus PlaySoundSamples (const SoundSamplesList&   soundSamplesList,
                              bool                      playAsynchronously)
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
             (status == ERR_SUCCESS) && (itr != soundSamplesList.end ());
             ++itr)
        {
            status = PlaySoundSample (*itr, playAsynchronously);
        } // Endfor.

    } // Endelse.
    
    return (status);
} // Endproc.


/**
 * Function that will stop playing any sound samples.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus StopPlayingSoundSamples ()
{
    FolioStatus status = ERR_SUCCESS;

    // Get the sound sample player instance.
        
    SoundSamplePlayer*  soundSamplePlayer = SoundSamplePlayer::GetInstance ();

    if (soundSamplePlayer)
    {
        // Stop playing sound samples.
            
        status = soundSamplePlayer->Stop ();
    } // Endif.
 
    else
    {
        status = ERR_INTERNAL_ERROR;
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
                                         soundSampleWave), 
                             false));   // Don't play asynchronously. 
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
