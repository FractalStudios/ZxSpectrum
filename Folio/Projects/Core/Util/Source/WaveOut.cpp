// Windows includes. 
#include    <Windows.h>
#include    <mmreg.h>
#pragma     comment(lib, "Winmm.lib")

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
:   m_waveOutHandle(0),
    m_playing(false)
{
} // Endproc.


/**
 * The class destructor.
 */
WaveOut::~WaveOut ()
{
    // Is the waveform-audio output device open?

    if (IsOpen ())
    {
        // Yes.
        
        // Reset the waveform-audio output device.

        Reset ();

        // Close the waveform-audio output device.

        Close ();
    } // Endif.

} // Endproc.


/**
 * Method that will open the waveform-audio output device.
 *
 * @param [in] numSoundChannels
 * The number of channels.
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
FolioStatus WaveOut::Open (SOUND_CHANNELS   numSoundChannels,
                           UInt32           samplesPerSecond)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the waveform-audio output device already open?

    if (IsOpen ())
    { 
        // Yes. Reset the waveform-audio output device.

        status = Reset ();
    } // Endif.

    else
    {
        // No. Build wave format.

        WAVEFORMATEX    waveFormat = {0};   // Initialise!
        waveFormat.cbSize           = 0;
        waveFormat.wFormatTag       = WAVE_FORMAT_PCM;
        waveFormat.nChannels        = numSoundChannels;
        waveFormat.nSamplesPerSec   = samplesPerSecond;
        waveFormat.wBitsPerSample   = CHAR_BIT * sizeof (SoundSample::SampleBuffer::value_type);
        waveFormat.nBlockAlign      = waveFormat.nChannels * waveFormat.wBitsPerSample / CHAR_BIT;
        waveFormat.nAvgBytesPerSec  = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;

        // Open the waveform-audio output device for playback.
    
        MMRESULT    mmResult = ::waveOutOpen (&(m_waveOutHandle), 
                                              WAVE_MAPPER,
                                              &(waveFormat), 
                                              #ifdef _USE_CALLBACK_
                                              reinterpret_cast<DWORD_PTR> (WaveOut::Callback), 
                                              reinterpret_cast<DWORD_PTR> (this), 
                                              CALLBACK_FUNCTION);
                                              #else
                                              0,
                                              0,
                                              CALLBACK_NULL);
                                              #endif

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
        // Yes. Clear periodic timer resolution.

        Thread::ResetTimeThreshold (TIME_THRESHOLD_RQD);

        // Close the waveform-audio output device.

        MMRESULT    mmResult = ::waveOutClose (m_waveOutHandle);
        
        if (mmResult == MMSYSERR_NOERROR)
        {
            // The waveform-audio output device is closed.

            m_waveOutHandle = 0;
        } // Endif.
        
        else
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(mmResult);

            FOLIO_LOG_CALL_ERROR (TXT("waveOutClose"), status);
        } // Endelse.

    } // Endif.

    return (status);
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

        MMRESULT    mmResult = ::waveOutReset (m_waveOutHandle);
        
        if (mmResult != MMSYSERR_NOERROR)
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(mmResult);

            FOLIO_LOG_CALL_ERROR (TXT("waveOutReset"), status);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that will play a sampled sound buffer on the waveform-audio output 
 * device for a specified duration.
 *
 * @param [in] duration
 * The sound's duration (in milliseconds).
 *
 * @param [in] sampleBuffer
 * The sampled sound buffer.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus WaveOut::Play (UInt32                           duration,
                           const SoundSample::SampleBuffer& sampleBuffer)
{
    FolioStatus status = ERR_SUCCESS;
       
    // Is the waveform-audio output device open?

    if (!m_playing && IsOpen ())
    {
        // Yes. We're playing.
        
        m_playing = true;

        // Build the wave header.

        WAVEHDR waveHeader = {0};   // Initialise!
        waveHeader.lpData           = reinterpret_cast<LPSTR> (const_cast<SoundSample::SampleBuffer::value_type *> (&(sampleBuffer [0])));
        waveHeader.dwBufferLength   = static_cast<DWORD> (sampleBuffer.size () * sizeof (SoundSample::SampleBuffer::value_type));
                    
        // Prepare the waveform-audio data block for playback.

        MMRESULT    mmResult = ::waveOutPrepareHeader (m_waveOutHandle,
                                                       &(waveHeader), 
                                                       sizeof (waveHeader));

        if (mmResult == MMSYSERR_NOERROR)
        {
            // Send the waveform-audio data block to the waveform-audio output device.

            mmResult = ::waveOutWrite (m_waveOutHandle, 
                                       &(waveHeader), 
                                       sizeof (waveHeader));

            if (mmResult == MMSYSERR_NOERROR)
            {
                if (duration >= 100)
                {
                    Thread::Sleep (duration);
                } // Endif.

                // Try to unprepare the header; this will fail until the block has
                // played.

                while (::waveOutUnprepareHeader (m_waveOutHandle, 
                                                 &(waveHeader), 
                                                 sizeof (waveHeader)) == WAVERR_STILLPLAYING)
                {
                    Thread::Sleep ((duration >= 100) ? 0 : duration);
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
    } // Endif.

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
    return (m_waveOutHandle != 0);
} // Endproc.


void    CALLBACK    WaveOut::Callback (HWAVEOUT     waveOutHandle,
                                       UINT         message,
                                       DWORD_PTR    instance,
                                       DWORD_PTR    parameter1,
                                       DWORD_PTR    parameter2)
{
    WaveOut*    waveOut = reinterpret_cast<WaveOut*> (instance);

    switch (message)
    {
    case WOM_OPEN:
        // Wave device is opened.
        break;

    case WOM_CLOSE: 
        // Wave device is closed.
        break;

    case WOM_DONE: 
        // A wave buffer is finished playing.
        break;

    default:
        break;
    } // Endswitch.

} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
