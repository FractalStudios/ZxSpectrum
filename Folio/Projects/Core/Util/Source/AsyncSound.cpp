// "Home-made" includes.
#include    <Trace.h>
#include    "AsyncSound.h"
#include    "ProcessInfo.h"
#include    "WaitAny.h"

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
AsyncSound::AsyncSound ()
:   m_waveOut(0),
    m_soundChannels(DEFAULT_SOUND_CHANNELS),
    m_samplesPerSecond(SoundSample::DEFAULT_SAMPLES_PER_SECOND)
{
} // Endproc.


/**
 * The class destructor.
 */
AsyncSound::~AsyncSound ()
{
    // Is the sound thread started?

    if (IsThreadStarted ())
    {
        // Yes. Stop the sound thread.

        StopThread ();
    } // Endif.

} // Endproc.


/**
 * Method that will play a sound sample.
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
FolioStatus AsyncSound::PlaySoundSample (const SoundSample& soundSample)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the sound thread started?

    if (!IsThreadStarted ())
    {
        // No. Start the sound thread.

        status = StartThread ();
    } // Endif.
      
    if (status == ERR_SUCCESS)
    {
        // Support multi-threaded synchronization.

        SingleThreadAccess  singleThreadAccess(m_lock);

        // Add the sound sample to our list.

        m_soundSamplesList.push_back (soundSample);

        // Let the sound thread play the added sound sample.

        status = m_soundSampleAvailableSema4.Unlock (1);
    } // Endif.
    
    return (status);
} // Endproc.


/**
 * Method that will play a list of sound samples.
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
FolioStatus AsyncSound::PlaySoundSamples (const SoundSamplesList& soundSamplesList)
{
    FolioStatus status = ERR_SUCCESS;

    if (soundSamplesList.empty ())
    {
        status = ERR_INVALID_PARAM1;
    } // Endif.

    else
    {
        // Is the sound thread started?

        if (!IsThreadStarted ())
        {
            // No. Start the sound thread.

            status = StartThread ();
        } // Endif.
      
        if (status == ERR_SUCCESS)
        {
            // Support multi-threaded synchronization.

            SingleThreadAccess  singleThreadAccess(m_lock);

            // Add the list of sound samples to the end of our list.

            m_soundSamplesList.insert (m_soundSamplesList.end (),
                                       soundSamplesList.begin (), 
                                       soundSamplesList.end ());

            // Let the sound thread play all the added sound samples.

            status = m_soundSampleAvailableSema4.Unlock (soundSamplesList.size ());
        } // Endif.
    
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to determine if the sound thread has been started.
 *
 * @return
 * <b>true</b> if the sound thread has been started, <b>false</b> otherwise.
 */
bool    AsyncSound::IsThreadStarted () const
{
    return (m_thread.IsRunning ());
} // Endproc.


/**
 * Method that will start the sound thread.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus AsyncSound::StartThread ()
{
    // Create the sound samples available semaphore.

    FolioStatus status = m_soundSampleAvailableSema4.Create (0xffff);
        
    if (status == ERR_SUCCESS)
    {
        // Create the sound thread exit pulse (unset).

        status = m_exitThreadPulse.Create ();

        if (status == ERR_SUCCESS)
        {
            // Start the sound thread.

            status = m_thread.Start (reinterpret_cast<Thread::ThreadCallback> (ThreadEntry),
                                     this); // Pass in this object.
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that will stop the sound thread.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus AsyncSound::StopThread ()
{
    // Signal the sound thread to exit.

    FolioStatus status = m_exitThreadPulse.Set ();

    if (status == ERR_SUCCESS)
    {
        // Wait a finite time for the sound thread to exit.

        m_thread.Wait (FOLIO_FINITE);
    } // Endif.

    return (status);
} // Endproc.


/**
 * The entry point of the sound thread.
 *
 * @param [in] args
 * Pointer to the <i>AsyncSound</i> object that created the thread.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INTERNAL_ERROR</b> if there is no <b>AsyncSound</b> object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus FOLIO_CALL  AsyncSound::ThreadEntry (void* args)
{
    FolioStatus status = ERR_SUCCESS;

    // Set our thread name.
                                            
    ProcessInfo::SetThreadName (ProcessInfo::GetCurrentThreadId (), "AsyncSound Thread");

    // Pick up the sound object.

    AsyncSound*   asyncSoundObject = reinterpret_cast<AsyncSound*> (args);

    // Do we have a valid object?

    if (asyncSoundObject)
    {
        // Yes. Initialise the sound thread.

        status = asyncSoundObject->ThreadInitialize ();

        if (status == ERR_SUCCESS)
        {
            // Let's go.

            status = asyncSoundObject->Thread ();
        } // Endif.

        // Terminate the sound thread.

        asyncSoundObject->ThreadTerminate ();
    } // Endif.

    else
    {
        // No. Something bad has happened.

        status = ERR_INTERNAL_ERROR;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will initialize the sound thread.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus AsyncSound::ThreadInitialize ()
{
    FolioStatus status = ERR_SUCCESS;

    // Get the waveform-audio output device instance.
        
    m_waveOut = WaveOut::GetInstance ();

    if (m_waveOut)
    {
        // Is the waveform-audio output device open?

        if (!m_waveOut->IsOpen ())
        {
            // No. Open the waveform-audio output device.
        
            status = m_waveOut->Open (m_soundChannels, m_samplesPerSecond);
        } // Endif.
   
    } // Endif.

    else
    {
        status = ERR_INTERNAL_ERROR;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will terminate the sound thread.
 */
void    AsyncSound::ThreadTerminate ()
{
} // Endproc.


/**
 * This method is THE sound thread.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus AsyncSound::Thread ()
{
    FolioStatus status = ERR_SUCCESS;

    // Loop until we are told to exit.

    bool    exit = false;   // Initialise!

    // Build wait any.

    WaitAny     waitAny;
    waitAny.Add (m_exitThreadPulse);
    waitAny.Add (m_soundSampleAvailableSema4);
    
    do
    {
        // Wait an infinite time.

        status = waitAny.Wait (FOLIO_INFINITE, false);

        switch (status)
        {
        case ERR_SUCCESS:
            // Get the synchronization signal.

            switch (waitAny.GetSyncIndex ())
            {
            case 1:
                // Play the first sound sample in the list of sound samples.

                PlayFirstSoundSample (GetFirstSoundSample ());
                break;
        
            case 0:
            default:
                // Get-outta-here.

                exit = true;
                break;
            } // Endswitch.
            break;

        default:
            // Get-outta-here.

            exit = true;
            break;
        } // Endswitch.

    } // Enddo.
    while (!exit);

    return (status);
} // Endproc.


/**
 * Method that will return the first sound sample in the list of sound samples.
 *
 * @return
 * The first sound sample in the list of sound samples
 */
SoundSample AsyncSound::GetFirstSoundSample ()
{
    SoundSample soundSample;

    // Support multi-threaded synchronization.

    SingleThreadAccess  singleThreadAccess(m_lock);

    if (!m_soundSamplesList.empty ())
    {
        // Get the first sound sample to play from the list of sound samples.

        soundSample = m_soundSamplesList.front ();

        // Remove the first sound sample from the list of sound samples.

        m_soundSamplesList.pop_front ();
    } // Endif.

    return (soundSample);
} // Endproc.


/**
 * Method that plays the first sound sample in the list of sound samples.
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
FolioStatus AsyncSound::PlayFirstSoundSample (const SoundSample& soundSample) const
{
    FolioStatus status = ERR_SUCCESS;

    if (soundSample.IsSoundSampleGenerated ())
    {
        if (m_waveOut)
        {
            // Use the waveform-audio output device to play the sound.
            
            status = m_waveOut->Play (soundSample.GetSoundDuration (), 
                                      soundSample.GetSampleBuffer ());
        } // Endif.

        else
        {
            status = ERR_INTERNAL_ERROR;
        } // Endelse.

    } // Endif.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
