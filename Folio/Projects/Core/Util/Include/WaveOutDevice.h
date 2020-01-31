#pragma once

// Windows includes.
#include    <Windows.h>

// STL includes.
#include    <memory>
#include    <vector>

// "Home-made" includes.
#include    <Base.h>
#include    "Event.h"
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

/// Wave out device.
class WaveOutDevice
{
public:
    // Sound sample id.
    typedef FolioHandle SoundSampleId;

    // Undefined sound sample id.
    static  const   SoundSampleId   UNDFINED_SOUND_SAMPLE_ID;

    WaveOutDevice ();
    ~WaveOutDevice ();
        
    FolioStatus StartPlayingSoundSample (const SoundSample& soundSample,
                                         bool               playAsynchronously,
                                         SoundSampleId&     soundSampleId);
    FolioStatus StopPlayingSoundSample (SoundSampleId soundSampleId);
    FolioStatus WaitUntilStoppedPlayingSoundSample (SoundSampleId   soundSampleId, 
                                                    UInt32          timeout);
    FolioStatus StopPlayingSoundSamples ();

private:
    FolioHandle     m_waveOutHandle;    ///< The wave out handle.
    SOUND_CHANNELS  m_soundChannels;    ///< The sound channels.
    UInt32          m_samplesPerSecond; ///< The sample frequency.

    /// Sound sample container.
    class SoundSampleContainer
    {
    public:
        SoundSampleContainer (bool playAsynchronously);
        ~SoundSampleContainer ();

        FolioStatus StartPlayingSoundSample (FolioHandle        waveOutHandle,
                                             const SoundSample& soundSample);
        FolioStatus StopPlayingSoundSample ();
        FolioStatus WaitUntilStoppedPlayingSoundSample (UInt32 timeout);

    private:
        FolioHandle     m_waveOutHandle;        ///< The wave out handle.
        SoundSample     m_soundSample;          ///< The sound sample.
        WAVEHDR         m_waveHeader;           ///< The wave out header.
        bool            m_playingSoundSample;   ///< <b>true</b> if the sound sample container is playing a sound sample, <b>false</b>otherwise.
        
        mutable std::unique_ptr<Event>  m_stoppedPlayingSoundSampleSignal;  ///< Stopped playing sound sample signal. Set when the sound sample container is NOT playing a sound sample.

        bool    IsPlayingSoundSample () const;

        FolioStatus PrepareWaveHeader ();
        FolioStatus UnprepareWaveHeader ();
        FolioStatus WriteWaveHeader ();

        FolioStatus SetStartedPlayingSoundSample ();
        FolioStatus SetStoppedPlayingSoundSample ();
    }; // Endclass.

    // Sound sample container list.
    typedef std::vector<std::shared_ptr<SoundSampleContainer> >  SoundSampleContainerList;
    SoundSampleContainerList    m_soundSampleContainerList;

    FolioStatus Open (SOUND_CHANNELS    soundChannels,
                      UInt32            samplesPerSecond);
    FolioStatus Close ();
    bool    IsOpen () const;

    SoundSampleContainerList::iterator  FindSoundSample (SoundSampleId soundSampleId);

    static  void    CALLBACK    WaveOutCallback (HWAVEOUT   waveOutHandle,
                                                 UINT       message,
                                                 DWORD_PTR  instance,
                                                 DWORD_PTR  parameter1,
                                                 DWORD_PTR  parameter2);

    /// Private copy constructor to prevent copying.
    WaveOutDevice (const WaveOutDevice& rhs);

    /// Private assignment operator to prevent copying.
    WaveOutDevice& operator= (const WaveOutDevice& rhs);
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
