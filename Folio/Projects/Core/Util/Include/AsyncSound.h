#pragma once

// STL includes.
#include    <list>

// "Home-made" includes.
#include    <Base.h>
#include    "CriticalSection.h"
#include    "ProcessSingleton.h"
#include    "Pulse.h"
#include    "Semaphore.h"
#include    "SoundSample.h"
#include    "Thread.h"
#include    "Waveout.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Util
{

namespace Sound
{

/// Asynchronous sound class.
class AsyncSound : public ProcessSingleton<AsyncSound>
{
public:
    ~AsyncSound  ();

    FolioStatus PlaySoundSample (const SoundSample& soundSamples);
    FolioStatus PlaySoundSamples (const SoundSamplesList& soundSamplesList);

protected:
    // As this is a process singleton, don't allow direct construction.
    
    AsyncSound ();

private:
    mutable WaveOut*    m_waveOut;  ///< The wave out.

    SOUND_CHANNELS  m_numSoundChannels; ///< The number of sound channels to use.
    UInt32          m_samplesPerSecond; ///< The sample frequency to use.

    /// Scope lock for single thread access.
    typedef ScopedCriticalSection    SingleThreadAccess;
    mutable CriticalSection  m_lock; ///< The (instance) single thread access lock.

    typedef std::list<SoundSample>  SoundSampleList;
    SoundSampleList m_soundSamplesList; ///< The list of sound samples to play.
    Semaphore   m_soundSampleAvailableSema4;    ///< Counting semaphore for the available number of sound samples.

    Thread   m_thread;          ///< The sound thread.
    Pulse    m_exitThreadPulse; ///< The (instance) pulse that the sound thread should exit.

    bool    IsThreadStarted () const;

    FolioStatus StartThread ();
    FolioStatus StopThread ();

    static  FolioStatus FOLIO_CALL  ThreadEntry (void* args);

    FolioStatus ThreadInitialize ();
    void        ThreadTerminate ();
    FolioStatus Thread ();

    FolioStatus PlayFirstSoundSample ();

    /// Private copy constructor to prevent copying.
    AsyncSound (const AsyncSound& rhs);

    /// Private assignment operator to prevent copying.
    AsyncSound& operator= (const AsyncSound& rhs);

    /// Allow the process singleton to construct.
    friend class ProcessSingleton<AsyncSound>;
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
