// Windows includes. 
#include    <Windows.h>
#include    <mmreg.h>
#pragma     comment(lib, "winmm.lib")

// STL includes.
#include    <algorithm>

// "Home-made" includes.
#include    <Trace.h>
#include    "WaveOutDevice.h"
#include    "Thread.h"

namespace Folio
{

namespace Core
{

namespace Util
{

namespace Sound
{

// Wave out device static members.
const   WaveOutDevice::SoundSampleId    WaveOutDevice::UNDFINED_SOUND_SAMPLE_ID = FOLIO_INVALID_HANDLE;

/**
 * The default class constructor.
 */
WaveOutDevice::WaveOutDevice ()
:   m_waveOutHandle(FOLIO_INVALID_HANDLE),
    m_soundChannels(DEFAULT_SOUND_CHANNELS),
    m_samplesPerSecond(SoundSample::DEFAULT_SAMPLES_PER_SECOND)
{
} // Endproc.
        

/**
 * The class destructor.
 */
WaveOutDevice::~WaveOutDevice ()
{
    // Close the waveform-audio output device.

    Close ();
} // Endproc.
 

/**
 * Method that will start playing a specified sound sample.
 *
 * @param [in] soundSample
 * The sound sample to play.
 *
 * @param [in] playAsynchronously
 * <b>true</b> if a the sound sample should be played asynchronously, 
 * <b>false</b> otherwise.
 *
 * @param [out] soundSampleId
 * The sound sample identifier associated with the sound sample. 
 * <b>UNDFINED_SOUND_SAMPLE_ID</b> if no sound sample identifier is associated with 
 * the sound sample.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus WaveOutDevice::StartPlayingSoundSample (const SoundSample&  soundSample,
                                                    bool                playAsynchronously,
                                                    SoundSampleId&      soundSampleId)
{
    FolioStatus status = ERR_SUCCESS;

    soundSampleId = UNDFINED_SOUND_SAMPLE_ID;   // Initialise!

    // Has the sound sample been generated?

    if (soundSample.IsSoundSampleGenerated ())
    {
        // Yes.

        SOUND_CHANNELS  soundChannels       = soundSample.GetSoundChannels ();
        UInt32          samplesPerSecond    = soundSample.GetSamplesPerSecond ();

        bool    openRqd = true; // Initialise!

        // Has the waveform-audio output device been opened?

        if (IsOpen ())
        {
            // Yes. Has the waveform-audio output device been opened with matching 
            // sound sample attributes?

            openRqd = ((m_soundChannels     != soundChannels) ||
                       (m_samplesPerSecond  != samplesPerSecond));

            if (openRqd)
            {
                // No. Close the waveform-audio output device.

                status = Close ();
            } // Endif.

        } // Endif.

        if (openRqd && (status == ERR_SUCCESS))
        {
            // Open the waveform-audio output device.

            status = Open (soundChannels, samplesPerSecond);
        } // Endif.

        if (status == ERR_SUCCESS)
        {
            // Create the sound sample container.

            SoundSampleContainerList::value_type    soundSampleContainer(new SoundSampleContainer(playAsynchronously));

            // Start playing the sound sample.

            status = soundSampleContainer->StartPlayingSoundSample (m_waveOutHandle, soundSample);

            if (status == ERR_SUCCESS)
            {
                // Add the sound sample container to the sound sample container list.

                m_soundSampleContainerList.push_back (soundSampleContainer);

                // Set the sound sample identifier.

                soundSampleId = soundSampleContainer.get ();
            } // Endif.

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
 * Method that will stop playing a sound sample.
 *
 * @param [in] soundSampleId
 * The sound sample identifier associated with the sound sample to stop. 
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus WaveOutDevice::StopPlayingSoundSample (SoundSampleId soundSampleId)
{
    FolioStatus status = ERR_SUCCESS;

    // Find the sound sample in the sound sample container list.

    SoundSampleContainerList::iterator  itr = FindSoundSample (soundSampleId);

    // Did we find the sound sample in the sound sample container list?

    if (itr == m_soundSampleContainerList.end ())
    {
        // No. The sound sample may have already stopped.
    } // Endif.

    else
    {
        // Yes. Stop playing the sound sample.

        status = (*itr)->StopPlayingSoundSample ();

        if (status == ERR_SUCCESS)
        {
            // Remove the sound sample container from the sound sample 
            // container list.

            m_soundSampleContainerList.erase (itr);
        } // Endif.

    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will wait until a sound sample has stopped playing.
 *
 * @param [in] soundSampleId
 * The sound sample identifier associated with the sound sample to wait for. 
 *
 * @param [in] timeout
 * Time to wait in milliseconds.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus WaveOutDevice::WaitUntilStoppedPlayingSoundSample (SoundSampleId    soundSampleId, 
                                                               UInt32           timeout)
{
    FolioStatus status = ERR_SUCCESS;
    
    // Find the sound sample in the sound sample container list.

    SoundSampleContainerList::iterator  itr = FindSoundSample (soundSampleId);

    // Did we find the sound sample in the sound sample container list?

    if (itr == m_soundSampleContainerList.end ())
    {
        // No. The sound sample may have already stopped.
    } // Endif.

    else
    {
        // Yes. Wait for the sound sample to stop playing.

        status = (*itr)->WaitUntilStoppedPlayingSoundSample (timeout);
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
FolioStatus WaveOutDevice::StopPlayingSoundSamples ()
{
    // Close the waveform-audio output device.

    return (Close ());
} // Endproc.


/**
 * Method that will indicate if we're playing any samples.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>true</b> if playing any sound samples.
 * <li><b>false</b> otherwise.
 * </ul>
 */
bool    WaveOutDevice::IsPlayingSoundSamples () const
{
    return (!m_soundSampleContainerList.empty ());
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
FolioStatus WaveOutDevice::Open (SOUND_CHANNELS soundChannels,
                                 UInt32         samplesPerSecond)
{
    FolioStatus status = ERR_SUCCESS;

    // Has the waveform-audio output device been opened already?

    if (!IsOpen ())
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
                                              reinterpret_cast<DWORD_PTR> (WaveOutDevice::WaveOutCallback), 
                                              reinterpret_cast<DWORD_PTR> (this), 
                                              CALLBACK_FUNCTION);

        if (mmResult == MMSYSERR_NOERROR)
        {
            // Note the sound sample attributes.

            m_soundChannels     = soundChannels;
            m_samplesPerSecond  = samplesPerSecond;
        } // Endif.

        else
        {
            // Build and log an error.

            status = FOLIO_MAKE_OS_ERROR(mmResult);

            FOLIO_LOG_CALL_ERROR (TXT("waveOutOpen"), status);
        } // Endelse.
    
    } // Endif.
    
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
FolioStatus WaveOutDevice::Close ()
{
    FolioStatus status = ERR_SUCCESS;
    
    // Has the waveform-audio output device been opened?

    if (IsOpen ())
    { 
        // Yes. Reset the waveform-audio output device.

        MMRESULT    mmResult = ::waveOutReset (reinterpret_cast<HWAVEOUT> (m_waveOutHandle));
        
        if (mmResult == MMSYSERR_NOERROR)
        {
            // Close the waveform-audio output device.

            mmResult = ::waveOutClose (reinterpret_cast<HWAVEOUT> (m_waveOutHandle));
        
            if (mmResult == MMSYSERR_NOERROR)
            {
                // The waveform-audio output device is closed.

                m_waveOutHandle = FOLIO_INVALID_HANDLE;

                // Clear the sound sample container list.

                m_soundSampleContainerList.clear ();
            } // Endif.
        
            else
            {
                // Build and log an error.

                status = FOLIO_MAKE_OS_ERROR(mmResult);

                FOLIO_LOG_CALL_ERROR (TXT("waveOutClose"), status);
            } // Endelse.
            
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
 * Method that indicates if the waveform-audio output device has been opened.
 *
 * @return
 * <b>true</b> if the waveform-audio output device has been opened, <b>false</b> otherwise.
 */
bool    WaveOutDevice::IsOpen () const
{
    return (m_waveOutHandle != FOLIO_INVALID_HANDLE);
} // Endproc.


/**
 * Method that will find the specified sound sample identifier in the sound 
 * sample container list.
 *
 * @param [in] soundSampleId
 * The sound sample identifier associated with the sound sample to find. 
 *
 * @return
 * The iterator to the found sound sample identifier in the sound sample 
 * container list.
 */
WaveOutDevice::SoundSampleContainerList::iterator   WaveOutDevice::FindSoundSample (SoundSampleId soundSampleId)
{
    // Find the sound sample in the sound sample container list.

    return (std::find_if (m_soundSampleContainerList.begin (),
                          m_soundSampleContainerList.end (),
                          [soundSampleId](const SoundSampleContainerList::value_type& arg) 
                          {return (arg.get () == soundSampleId);}));
} // Endproc.


/**
 * The waveform-audio output device callback.
 */
void    CALLBACK    WaveOutDevice::WaveOutCallback (HWAVEOUT    waveOutHandle,
                                                    UINT        message,
                                                    DWORD_PTR   instance,
                                                    DWORD_PTR   parameter1,
                                                    DWORD_PTR   parameter2)
{
    WaveOutDevice*  waveOut = reinterpret_cast<WaveOutDevice*> (instance);

    if (waveOut)
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
            // Waveform-audio output device has finished playing a sound buffer.

            if (parameter1)
            {
                // The sound sample container has stopped playing a sound sample.

                waveOut->StopPlayingSoundSample (reinterpret_cast<SoundSampleId> ((reinterpret_cast<WAVEHDR *> (parameter1)->dwUser)));
            } // Endif.
            break;

        default:
            break;
        } // Endswitch.
    
    } // Endif.

} // Endproc.


/**
 * The class constructor.
 *
 * @param [in] playAsynchronously
 * <b>true</b> if a the sound sample should be played asynchronously, 
 * <b>false</b> otherwise.
 */
WaveOutDevice::SoundSampleContainer::SoundSampleContainer (bool playAsynchronously)
:   m_waveOutHandle(FOLIO_INVALID_HANDLE),
    m_waveHeader{0},
    m_playingSoundSample(false)
{
    if (!playAsynchronously)
    {
        // Create the stopped playing sound sample signal.

        m_stoppedPlayingSoundSampleSignal.reset (new Event);

        m_stoppedPlayingSoundSampleSignal->Create (true);
    } // Endif.

} // Endproc.


/**
 * The class constructor.
 */
WaveOutDevice::SoundSampleContainer::~SoundSampleContainer ()
{
    // Stop playing the sound sample.

    StopPlayingSoundSample ();
} // Endproc.


/**
 * Method that will start playing a sound sample.
 *
 * @param [in] waveOutHandle
 * Handle to the open waveform-audio output device.
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
FolioStatus WaveOutDevice::SoundSampleContainer::StartPlayingSoundSample (FolioHandle           waveOutHandle,
                                                                          const SoundSample&    soundSample)
{
    FolioStatus status = ERR_SUCCESS;

    // Are we playing a sound sample already?

    if (IsPlayingSoundSample ())
    {
        // Yes.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // No. Note the sound sample attributes.

        m_waveOutHandle = waveOutHandle;
        m_soundSample   = soundSample;

        // Prepare the wave header.

        status = PrepareWaveHeader ();

        if (status == ERR_SUCCESS)
        {
            // Write the wave header.

            status = WriteWaveHeader ();

            if (status == ERR_SUCCESS)
            {
                // Started playing sound sample.

                status = SetStartedPlayingSoundSample ();
            } // Endif.

        } // Endif.
    
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will stop playing a sound sample.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus WaveOutDevice::SoundSampleContainer::StopPlayingSoundSample ()
{
    FolioStatus status = ERR_SUCCESS;

    // Are we playing a sound sample?

    if (IsPlayingSoundSample ())
    {
        // Yes. We have stopped playing a sound sample.

        status = SetStoppedPlayingSoundSample ();
    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that will wait until a sound sample has stopped playing.
 *
 * @param [in] timeout
 * Time to wait in milliseconds.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus WaveOutDevice::SoundSampleContainer::WaitUntilStoppedPlayingSoundSample (UInt32 timeout)
{
    FolioStatus status = ERR_SUCCESS;

    if (m_stoppedPlayingSoundSampleSignal)
    {
        // Are we playing a sound sample?

        if (IsPlayingSoundSample ())
        {
            // Yes. Wait until we have stopped playing the sound sample.

            status = m_stoppedPlayingSoundSampleSignal->Wait (timeout);
        } // Endif.

    } // Endif.

    else
    {
        status = ERR_NOT_SUPPORTED;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that indicates if the sound sample container is playing a sound sample.
 *
 * @return
 * <b>true</b> if the sound sample container is playing a sound sample, <b>false</b> 
 * otherwise.
 */
bool    WaveOutDevice::SoundSampleContainer::IsPlayingSoundSample () const
{
    return (m_playingSoundSample);
} // Endproc.


/**
 * Method that will prepare the wave header.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus WaveOutDevice::SoundSampleContainer::PrepareWaveHeader ()
{
    FolioStatus status = ERR_SUCCESS;

    // Build the wave header.

    const SoundSample::SampleBuffer &sampleBuffer(m_soundSample.GetSampleBuffer ());

    ::ZeroMemory (&(m_waveHeader), sizeof (m_waveHeader));
    m_waveHeader.lpData         = reinterpret_cast<LPSTR> (const_cast<SoundSample::SampleBuffer::value_type *> (&(sampleBuffer [0])));
    m_waveHeader.dwBufferLength = static_cast<DWORD> (sampleBuffer.size () * sizeof (SoundSample::SampleBuffer::value_type));
    m_waveHeader.dwUser         = reinterpret_cast<DWORD_PTR> (this);
                    
    // Prepare the waveform-audio data block for playback.

    MMRESULT    mmResult = ::waveOutPrepareHeader (reinterpret_cast<HWAVEOUT> (m_waveOutHandle),
                                                   &(m_waveHeader), 
                                                   sizeof (m_waveHeader));

    if (mmResult != MMSYSERR_NOERROR)
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(mmResult);

        FOLIO_LOG_CALL_ERROR (TXT("waveOutPrepareHeader"), status);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that will unprepare the wave header.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus WaveOutDevice::SoundSampleContainer::UnprepareWaveHeader ()
{
    FolioStatus status = ERR_SUCCESS;

    // Has the wave header been prepared?

    if (m_waveHeader.dwFlags & WHDR_PREPARED)
    {
        // Yes. Unprepare the waveform-audio data block for playback.

        MMRESULT    mmResult = ::waveOutUnprepareHeader (reinterpret_cast<HWAVEOUT> (m_waveOutHandle),
                                                         &(m_waveHeader), 
                                                         sizeof (m_waveHeader));

        switch (mmResult)
        {
        case MMSYSERR_NOERROR:
            break;

        case WAVERR_STILLPLAYING:
            Thread::Sleep (1);

            // Recurse.

            status = UnprepareWaveHeader ();
            break;

        default:
            {
                // Build and log an error.

                status = FOLIO_MAKE_OS_ERROR(mmResult);

                FOLIO_LOG_CALL_ERROR (TXT("waveOutUnprepareHeader"), status);
            } // Endscope.
            break;
        } // Endswitch.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that will write the wave header.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus WaveOutDevice::SoundSampleContainer::WriteWaveHeader ()
{
    FolioStatus status = ERR_SUCCESS;

    // Send the waveform-audio data block to the waveform-audio output device.

    MMRESULT    mmResult = ::waveOutWrite (reinterpret_cast<HWAVEOUT> (m_waveOutHandle), 
                                           &(m_waveHeader), 
                                           sizeof (m_waveHeader));

    if (mmResult != MMSYSERR_NOERROR)
    {
        // Build and log an error.

        status = FOLIO_MAKE_OS_ERROR(mmResult);

        FOLIO_LOG_CALL_ERROR (TXT("waveOutWrite"), status);
    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that sets that the sound sample container is playing a sound sample.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
*/
FolioStatus WaveOutDevice::SoundSampleContainer::SetStartedPlayingSoundSample ()
{
    FolioStatus status = ERR_SUCCESS;

    m_playingSoundSample = true;

    if (m_stoppedPlayingSoundSampleSignal)
    {
        // Reset the stopped playing sound sample signal.
        
        status = m_stoppedPlayingSoundSampleSignal->Reset ();
    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that sets that the sound sample container has stopped playing a sound sample.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
*/
FolioStatus WaveOutDevice::SoundSampleContainer::SetStoppedPlayingSoundSample ()
{
    FolioStatus status = ERR_SUCCESS;

    m_playingSoundSample = false;

    if (m_stoppedPlayingSoundSampleSignal)
    {
        // Set the stopped playing sound sample signal.
        
        status = m_stoppedPlayingSoundSampleSignal->Set ();
    } // Endif.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
