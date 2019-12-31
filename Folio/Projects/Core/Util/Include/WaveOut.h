#pragma once

// Windows includes.
#include    <Windows.h>

// "Home-made" includes.
#include    <Base.h>
#include    "ProcessSingleton.h"
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

/// Wave out class.
class WaveOut : public ProcessSingleton<WaveOut>
{
public:
    ~WaveOut  ();

    FolioStatus Open (SOUND_CHANNELS    numSoundChannels,
                      UInt32            samplesPerSecond);
    FolioStatus Close ();
    FolioStatus Reset ();
    FolioStatus Play (UInt32                            duration,
                      const SoundSample::SampleBuffer&  sampleBuffer);

    bool    IsOpen () const;

protected:
    // As this is a process singleton, don't allow direct construction.
    
    WaveOut ();

private:
    static  const   UInt32    TIME_THRESHOLD_RQD = 1;   // Time threshold.

    HWAVEOUT    m_waveOutHandle; // The wave out handle.

    bool    m_playing;  // Indicates if the waveform-audio output device is playing.

    static  void    CALLBACK    Callback (HWAVEOUT  waveOutHandle,
                                          UINT      message,
                                          DWORD_PTR instance,
                                          DWORD_PTR parameter1,
                                          DWORD_PTR parameter2);

    /// Private copy constructor to prevent copying.
    WaveOut (const WaveOut& rhs);

    /// Private assignment operator to prevent copying.
    WaveOut& operator= (const WaveOut& rhs);

    /// Allow the process singleton to construct.
    friend class ProcessSingleton<WaveOut>;
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
