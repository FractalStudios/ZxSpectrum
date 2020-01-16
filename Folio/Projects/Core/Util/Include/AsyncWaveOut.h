#pragma once

// Windows includes.
#include    <Windows.h>

// "Home-made" includes.
#include    <Base.h>
#include    "ProcessSingleton.h"
#include    "Semaphore.h"
#include    "SoundSample.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Util
{

namespace Sound
{

/// Aynchronous wave out class.
class AsyncWaveOut : public ProcessSingleton<AsyncWaveOut>
{
public:
    ~AsyncWaveOut ();

    FolioStatus Open (SOUND_CHANNELS    soundChannels,
                      UInt32            samplesPerSecond);
    FolioStatus Close ();
    FolioStatus Play (UInt32                            soundDuration,
                      const SoundSample::SampleBuffer&  sampleBuffer);

    bool    IsOpen () const;

protected:
    // As this is a process singleton, don't allow direct construction.
    
    AsyncWaveOut ();

private:
    /// Maximum number of sound sample players.
    static  const   UInt32  MAX_SOUND_SAMPLE_PLAYERS = 2;

    FolioHandle m_waveOutHandle; ///< The wave out handle.

    /// Sound sample player.
    class SoundSamplePlayer
    {
    public:
        SoundSamplePlayer ();
        ~SoundSamplePlayer ();
        
        FolioStatus StartPlayingSoundSample (FolioHandle                        waveOutHandle,
                                             const SoundSample::SampleBuffer&   sampleBuffer);
        FolioStatus StopPlayingSoundSample ();
        bool    IsPlayingSoundSample () const;
   
    private:
        FolioHandle                 m_waveOutHandle;    ///< The wave out handle.
        SoundSample::SampleBuffer   m_sampleBuffer;     ///< The sound sample buffer.
        WAVEHDR                     m_waveHeader;       ///< The wave out header.
    }; // Endclass.

    SoundSamplePlayer   m_soundSamplePlayer [MAX_SOUND_SAMPLE_PLAYERS];   ///< The sound sample players.

    Semaphore   m_soundSamplePlayerSema4;  ///< Counting semaphore indicating a sound sample player is playing.

    FolioStatus Reset ();

    UInt32  GetStoppedSoundSamplePlayer () const;
    FolioStatus StartSoundSamplePlayer (UInt32                              soundSamplePlayer,
                                        const SoundSample::SampleBuffer&    sampleBuffer);
    FolioStatus StopSoundSamplePlayer (UInt32 soundSamplePlayer);
    FolioStatus StopSoundSamplePlayers ();

    static  void    CALLBACK    Callback (HWAVEOUT  waveOutHandle,
                                          UINT      message,
                                          DWORD_PTR instance,
                                          DWORD_PTR parameter1,
                                          DWORD_PTR parameter2);

    /// Private copy constructor to prevent copying.
    AsyncWaveOut (const AsyncWaveOut& rhs);

    /// Private assignment operator to prevent copying.
    AsyncWaveOut& operator= (const AsyncWaveOut& rhs);

    /// Allow the process singleton to construct.
    friend class ProcessSingleton<AsyncWaveOut>;
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
