// Windows includes. 
#include    <Windows.h>
#include    <mmsystem.h>
#pragma     comment(lib, "winmm.lib")

// "Home-made" includes.
#include    <Trace.h>
#include    "Thread.h"
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
 * The default class constructor.
 */
WaveOut::WaveOut ()
:   m_waveOutHandle(FOLIO_INVALID_HANDLE),
    m_playing(false)
{
} // Endproc.


/**
 * The class destructor.
 */
WaveOut::~WaveOut ()
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
FolioStatus WaveOut::Open (SOUND_CHANNELS   soundChannels,
                           UInt32           samplesPerSecond)
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
        waveFormat.wFormatTag       = WAVE_FORMAT_PCM;
        waveFormat.nChannels        = soundChannels;
        waveFormat.nSamplesPerSec   = samplesPerSecond;
        waveFormat.wBitsPerSample   = CHAR_BIT * sizeof (SoundSample::SampleBuffer::value_type);
        waveFormat.nBlockAlign      = waveFormat.nChannels * waveFormat.wBitsPerSample / CHAR_BIT;
        waveFormat.nAvgBytesPerSec  = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
        waveFormat.cbSize           = 0;

        // Open the waveform-audio output device for playback.
    
        MMRESULT    mmResult = ::waveOutOpen (reinterpret_cast<HWAVEOUT *> (&(m_waveOutHandle)), 
                                              WAVE_MAPPER,
                                              &(waveFormat), 
                                              0,
                                              0,
                                              CALLBACK_NULL);

        if (mmResult == MMSYSERR_NOERROR)
        {
            // Set periodic timer resolution.

            Thread::SetTimeThreshold (TIME_THRESHOLD_RQD);
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
FolioStatus WaveOut::Close ()
{
    FolioStatus status = ERR_SUCCESS;
    
    // Is the waveform-audio output device open?

    if (IsOpen ())
    {
        // Yes. Reset the waveform-audio output device.

        status = Reset ();

        if (status == ERR_SUCCESS)
        {
            // Clear periodic timer resolution.

            Thread::ResetTimeThreshold (TIME_THRESHOLD_RQD);

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
FolioStatus WaveOut::Play (UInt32                           soundDuration,
                           const SoundSample::SampleBuffer& sampleBuffer)
{
    FolioStatus status = ERR_SUCCESS;

    if (sampleBuffer.empty ())
    {
        status = ERR_INVALID_PARAM2;
    } // Endif.
       
    // Is the waveform-audio output device open?

    else
    if (!m_playing && IsOpen ())
    {
        // Yes. We're playing.
        
        m_playing = true;

        // Build the wave header.

        WAVEHDR waveHeader = {0};   // Initialise!
        waveHeader.lpData           = reinterpret_cast<LPSTR> (const_cast<SoundSample::SampleBuffer::value_type *> (&(sampleBuffer [0])));
        waveHeader.dwBufferLength   = static_cast<DWORD> (sampleBuffer.size () * sizeof (SoundSample::SampleBuffer::value_type));
                    
        // Prepare the waveform-audio data block for playback.

        MMRESULT    mmResult = ::waveOutPrepareHeader (reinterpret_cast<HWAVEOUT> (m_waveOutHandle),
                                                       &(waveHeader), 
                                                       sizeof (waveHeader));

        if (mmResult == MMSYSERR_NOERROR)
        {
            // Send the waveform-audio data block to the waveform-audio output device.

            mmResult = ::waveOutWrite (reinterpret_cast<HWAVEOUT> (m_waveOutHandle), 
                                       &(waveHeader), 
                                       sizeof (waveHeader));

            if (mmResult == MMSYSERR_NOERROR)
            {
                if (soundDuration >= 100)
                {
                    Thread::Sleep (soundDuration);
                } // Endif.

                // Try to unprepare the header; this will fail until the block has
                // played.

                while (::waveOutUnprepareHeader (reinterpret_cast<HWAVEOUT> (m_waveOutHandle), 
                                                 &(waveHeader), 
                                                 sizeof (waveHeader)) == WAVERR_STILLPLAYING)
                {
                    Thread::Sleep ((soundDuration >= 100) ? 0 : soundDuration);
                } // Endwhile.

            } // Endif.

            else
            {
                // Build and log an error.

                status = FOLIO_MAKE_OS_ERROR(mmResult);

                FOLIO_LOG_CALL_ERROR (TXT("waveOutWrite"), status);
            } // Endelse.

        } // Endif.
       
        else
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(mmResult);

            FOLIO_LOG_CALL_ERROR (TXT("waveOutPrepareHeader"), status);
        } // Endelse.

        // Yes. We're no longer playing.
        
        m_playing = false;
    } // Endelseif.

    return (status);
} // Endproc.


/**
 * Method that indicates if the waveform-audio output device is open.
 *
 * @return
 * <b>true</b> if the waveform-audio output device is open, <b>false</b> otherwise.
 */
bool    WaveOut::IsOpen () const
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
FolioStatus WaveOut::Reset ()
{
    FolioStatus status = ERR_SUCCESS;

    // Is the waveform-audio output device open?

    if (IsOpen ())
    {
        // Yes. Reset the waveform-audio output device.

        MMRESULT    mmResult = ::waveOutReset (reinterpret_cast<HWAVEOUT> (m_waveOutHandle));
        
        if (mmResult != MMSYSERR_NOERROR)
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(mmResult);

            FOLIO_LOG_CALL_ERROR (TXT("waveOutReset"), status);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
