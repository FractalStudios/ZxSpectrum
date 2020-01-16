// Windows includes. 
#include    <Windows.h>
#include    <mmreg.h>
#pragma     comment(lib, "winmm.lib")

// "Home-made" includes.
#include    <Trace.h>
#include    "AsyncWaveOut.h"
#include    "Thread.h"

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
AsyncWaveOut::AsyncWaveOut ()
:   m_waveOutHandle(FOLIO_INVALID_HANDLE)
{
} // Endproc.


/**
 * The class destructor.
 */
AsyncWaveOut::~AsyncWaveOut ()
{
    // Close the waveform-audio output device.

    Close ();
} // Endproc.


/**
 * Method that will open the waveform-audio output device.
 *
 * @param [in] soundChannels
 * The sound channels.
 *
 * @param [in] samplesPerSecond
 * The sample frequency.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus AsyncWaveOut::Open (SOUND_CHANNELS  soundChannels,
                                UInt32          samplesPerSecond)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the waveform-audio output device already open?

    if (IsOpen ())
    { 
        // Yes. 

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // No. Build wave format.

        WAVEFORMATEX    waveFormat = {0};   // Initialise!
        waveFormat.cbSize           = 0;
        waveFormat.wFormatTag       = WAVE_FORMAT_PCM;
        waveFormat.nChannels        = soundChannels;
        waveFormat.nSamplesPerSec   = samplesPerSecond;
        waveFormat.wBitsPerSample   = CHAR_BIT * sizeof (SoundSample::SampleBuffer::value_type);
        waveFormat.nBlockAlign      = waveFormat.nChannels * waveFormat.wBitsPerSample / CHAR_BIT;
        waveFormat.nAvgBytesPerSec  = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;

        // Open the waveform-audio output device for playback.
    
        MMRESULT    mmResult = ::waveOutOpen (reinterpret_cast<HWAVEOUT *> (&(m_waveOutHandle)), 
                                              WAVE_MAPPER,
                                              &(waveFormat), 
                                              reinterpret_cast<DWORD_PTR> (AsyncWaveOut::Callback), 
                                              reinterpret_cast<DWORD_PTR> (this), 
                                              CALLBACK_FUNCTION);

        if (mmResult == MMSYSERR_NOERROR)
        {
            // Create the sound sample player sema4.

            status = m_soundSamplePlayerSema4.Create (MAX_SOUND_SAMPLE_PLAYERS, 
                                                      MAX_SOUND_SAMPLE_PLAYERS);
        } // Endif.

        else
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(mmResult);

            FOLIO_LOG_CALL_ERROR (TXT("waveOutOpen"), status);
        } // Endelse.

    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will close the waveform-audio output device.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus AsyncWaveOut::Close ()
{
    FolioStatus status = ERR_SUCCESS;
    
    // Is the waveform-audio output device open?

    if (IsOpen ())
    {
        // Yes. Reset the waveform-audio output device.

        status = Reset ();

        if (status == ERR_SUCCESS)
        {
            // Close the waveform-audio output device.

            MMRESULT    mmResult = ::waveOutClose (reinterpret_cast<HWAVEOUT> (m_waveOutHandle));
        
            if (mmResult == MMSYSERR_NOERROR)
            {
                // The waveform-audio output device is closed.

                m_waveOutHandle = FOLIO_INVALID_HANDLE;
            } // Endif.
        
            else
            {
                // Build and log an error.

                status = FOLIO_MAKE_OS_ERROR(mmResult);

                FOLIO_LOG_CALL_ERROR (TXT("waveOutClose"), status);
            } // Endelse.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that will play a sampled sound buffer on the waveform-audio output 
 * device for a specified duration.
 *
 * @param [in] soundDuration
 * The sound's duration (in milliseconds).
 *
 * @param [in] sampleBuffer
 * The sampled sound buffer to play.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus AsyncWaveOut::Play (UInt32                              soundDuration,
                                const SoundSample::SampleBuffer&    sampleBuffer)
{
    FolioStatus status = ERR_SUCCESS;

    if (sampleBuffer.empty ())
    {
        status = ERR_INVALID_PARAM2;
    } // Endif.
       
    // Is the waveform-audio output device open?

    else
    if (IsOpen ())
    {
        // Yes. Wait for a sound sample player to stop playing.

        if ((m_soundSamplePlayerSema4.Lock (FOLIO_FINITE) == ERR_SUCCESS))
        {
            // Get a stopped sound sample player.

            UInt32  stoppedSoundSamplePlayer = GetStoppedSoundSamplePlayer ();

            if (stoppedSoundSamplePlayer == FOLIO_INVALID_INDEX)
            {
                status = ERR_IN_USE;
            } // Endif.

            else
            {
                // Start the sound sample player.
                
                status = StartSoundSamplePlayer (stoppedSoundSamplePlayer, 
                                                 sampleBuffer);
            } // Endelse.

        } // Endif.

        else
        {
            status = ERR_IN_USE;
        } // Endelse.

    } // Endelseif.

    else
    {
        // No.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that indicates if the waveform-audio output device is open.
 *
 * @return
 * <b>true</b> if the waveform-audio output device is open, <b>false</b> otherwise.
 */
bool    AsyncWaveOut::IsOpen () const
{
    return (m_waveOutHandle != FOLIO_INVALID_HANDLE);
} // Endproc.


/**
 * Method that will reset the waveform-audio output device.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus AsyncWaveOut::Reset ()
{
    FolioStatus status = ERR_SUCCESS;

    // Is the waveform-audio output device open?

    if (IsOpen ())
    {
        // Yes. Reset the waveform-audio output device.

        MMRESULT    mmResult = ::waveOutReset (reinterpret_cast<HWAVEOUT> (m_waveOutHandle));
        
        if (mmResult == MMSYSERR_NOERROR)
        {
            // Stop all the sound sample players.

            status = StopSoundSamplePlayers ();
        } // Endif.

        else
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(mmResult);

            FOLIO_LOG_CALL_ERROR (TXT("waveOutReset"), status);
        } // Endelse.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that will return the index of a stopped sound sample player
 *
 * @return
 * The the index of a stopped sound sample player, if a there is a sound sample 
 * player that is stopped, FOLIO_INVALD_INDEX otherwise.
 */
UInt32  AsyncWaveOut::GetStoppedSoundSamplePlayer () const
{    
    UInt32  stoppedSoundSamplePlayer = FOLIO_INVALID_INDEX; // Initialise!

    // Get a stopped (non playing) sound sample player.

    for (UInt32 soundSamplePlayer = 0; 
         (stoppedSoundSamplePlayer == FOLIO_INVALID_INDEX) && (soundSamplePlayer < MAX_SOUND_SAMPLE_PLAYERS); 
         ++soundSamplePlayer)
    {
        // Is the sound sample player playing a sound sample?

        if (!m_soundSamplePlayer [soundSamplePlayer].IsPlayingSoundSample ())
        {
            // No.

            stoppedSoundSamplePlayer = soundSamplePlayer;
        } // Endif.

    } // Endfor.

    return (stoppedSoundSamplePlayer);
} // Endproc.


/**
 * Method that will start a specified sound sample player.
 *
 * @param [in] soundSamplePlayer
 * The index of the sound sample player to start.
 *
 * @param [in] sampleBuffer
 * The sampled sound buffer to play.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus AsyncWaveOut::StartSoundSamplePlayer (UInt32                            soundSamplePlayer,
                                                  const SoundSample::SampleBuffer&  sampleBuffer)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the sound sample player playing a sound sample?

    if (m_soundSamplePlayer [soundSamplePlayer].IsPlayingSoundSample ())
    {
        // Yes.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // No. Start playing the sound sample.

        m_soundSamplePlayer [soundSamplePlayer].StartPlayingSoundSample (m_waveOutHandle, 
                                                                         sampleBuffer);
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will stop a specified sound sample player.
 *
 * @param [in] soundSamplePlayer
 * The index of the sound sample player to stop.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus AsyncWaveOut::StopSoundSamplePlayer (UInt32 soundSamplePlayer)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the sound sample player playing a sound sample?

    if (m_soundSamplePlayer [soundSamplePlayer].IsPlayingSoundSample ())
    {
        // Yes. Stop playing the sound sample.

        m_soundSamplePlayer [soundSamplePlayer].StopPlayingSoundSample ();
    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that will stop all sound sample players.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus AsyncWaveOut::StopSoundSamplePlayers ()
{
    FolioStatus status = ERR_SUCCESS;

    // Stop playing all the sound samples.

    for (UInt32 soundSamplePlayer = 0; 
         soundSamplePlayer < MAX_SOUND_SAMPLE_PLAYERS; 
         ++soundSamplePlayer)
    {
        status = StopSoundSamplePlayer (soundSamplePlayer);
    } // Endfor.

    if (status == ERR_SUCCESS)
    {
        // Set the sound sample player sema4.

        status = m_soundSamplePlayerSema4.Set ();
    } // Endif.

    return (status);
} // Endproc.


/**
 * The waveform-audio output device callback.
 */
void    CALLBACK    AsyncWaveOut::Callback (HWAVEOUT     waveOutHandle,
                                            UINT         message,
                                            DWORD_PTR    instance,
                                            DWORD_PTR    parameter1,
                                            DWORD_PTR    parameter2)
{
    AsyncWaveOut*   asyncWaveOut = reinterpret_cast<AsyncWaveOut*> (instance);

    if (asyncWaveOut)
    {
        switch (message)
        {
        case WOM_OPEN:
            // Waveform-audio output device is opened.
            break;

        case WOM_CLOSE: 
            // Waveform-audio output device is closed.
            break;

        case WOM_DONE: 
            // A wave buffer has finished playing.

            asyncWaveOut->m_soundSamplePlayerSema4.Unlock (1);
            break;

        default:
            break;
        } // Endswitch.
    
    } // Endif.

} // Endproc.


/**
 * The default class constructor.
 */
AsyncWaveOut::SoundSamplePlayer::SoundSamplePlayer ()
:   m_waveOutHandle(FOLIO_INVALID_HANDLE)
{
    ::ZeroMemory (&(m_waveHeader), sizeof (m_waveHeader));
} // Endproc.
        

/**
 * The class destructor.
 */
AsyncWaveOut::SoundSamplePlayer::~SoundSamplePlayer ()
{
    // Stop playing any sound sample.

    StopPlayingSoundSample ();
} // Endproc.
        

/**
 * Method that will start playing a specified sound sample on the sound sample 
 * player.
 *
 * @param [in] waveOutHandle
 * The handle to the waveform-audio output device to play the sound sample.
 *
 * @param [in] sampleBuffer
 * The sampled sound buffer to play.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus AsyncWaveOut::SoundSamplePlayer::StartPlayingSoundSample (FolioHandle                       waveOutHandle, 
                                                                      const SoundSample::SampleBuffer&  sampleBuffer)
{
    // Stop playing any currently playing sound sample.

    FolioStatus status = StopPlayingSoundSample ();

    if (status == ERR_SUCCESS)
    {
        // Note the waveform-audio output device and sample buffer.

        m_waveOutHandle = waveOutHandle;
        m_sampleBuffer  = sampleBuffer;

        // Build the wave header.

        ::ZeroMemory (&(m_waveHeader), sizeof (m_waveHeader));
        m_waveHeader.lpData         = reinterpret_cast<LPSTR> (const_cast<SoundSample::SampleBuffer::value_type *> (&(m_sampleBuffer [0])));
        m_waveHeader.dwBufferLength = static_cast<DWORD> (m_sampleBuffer.size () * sizeof (SoundSample::SampleBuffer::value_type));
                    
        // Prepare the waveform-audio data block for playback.

        MMRESULT    mmResult = ::waveOutPrepareHeader (reinterpret_cast<HWAVEOUT> (m_waveOutHandle),
                                                       &(m_waveHeader), 
                                                       sizeof (m_waveHeader));

        if (mmResult == MMSYSERR_NOERROR)
        {
            // Send the waveform-audio data block to the waveform-audio output device.

            mmResult = ::waveOutWrite (reinterpret_cast<HWAVEOUT> (m_waveOutHandle), 
                                       &(m_waveHeader), 
                                       sizeof (m_waveHeader));

            if (mmResult != MMSYSERR_NOERROR)
            {
                // Build and log an error.

                status = FOLIO_MAKE_OS_ERROR(mmResult);

                FOLIO_LOG_CALL_ERROR (TXT("waveOutWrite"), status);
            } // Endif.

        } // Endif.
       
        else
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(mmResult);

            FOLIO_LOG_CALL_ERROR (TXT("waveOutPrepareHeader"), status);
        } // Endelse.
    
    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that will stop playing a sound sample on the sound sample player.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus AsyncWaveOut::SoundSamplePlayer::StopPlayingSoundSample ()
{
    FolioStatus status = ERR_SUCCESS;

    // Has the wave header been prepared?

    if (m_waveHeader.dwFlags & WHDR_PREPARED)
    {
        // Yes. Try to unprepare the header; this will fail until the block has
        // played.
        
        while (::waveOutUnprepareHeader (reinterpret_cast<HWAVEOUT> (m_waveOutHandle), 
                                         &(m_waveHeader), 
                                         sizeof (m_waveHeader)) == WAVERR_STILLPLAYING)
        {
            Thread::Sleep (0);
        } // Endwhile.

        m_waveOutHandle = FOLIO_INVALID_HANDLE;
    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that indicates if the sound sample player is playing a sound sample.
 *
 * @return
 * <b>true</b> if the the sound sample player is playing a sound sample, 
 * <b>false</b> otherwise.
 */
bool    AsyncWaveOut::SoundSamplePlayer::IsPlayingSoundSample () const
{
    return ((m_waveOutHandle != FOLIO_INVALID_HANDLE) && 
            !(m_waveHeader.dwFlags & WHDR_DONE));
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
