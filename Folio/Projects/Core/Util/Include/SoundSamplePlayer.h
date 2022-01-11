#pragma once

// "Home-made" includes.
#include    <Base.h>
#include    "ProcessSingleton.h"
#include    "SoundSample.h"
#include    "WaveOutDevice.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Util
{

namespace Sound
{

/// Sound sample player class.
class SoundSamplePlayer : public ProcessSingleton<SoundSamplePlayer>
{
public:
    ~SoundSamplePlayer ();

    FolioStatus Play (const SoundSample&    soundSample,
                      bool                  playAsynchronously = true);
    FolioStatus Stop ();
    bool    IsPlaying () const;

protected:
    // As this is a process singleton, don't allow direct construction.
    
    SoundSamplePlayer ();

private:
    WaveOutDevice   m_waveOutDevice;    ///< The wave out device.

    /// Private copy constructor to prevent copying.
    SoundSamplePlayer (const SoundSamplePlayer& rhs);

    /// Private assignment operator to prevent copying.
    SoundSamplePlayer& operator= (const SoundSamplePlayer& rhs);

    /// Allow the process singleton to construct.
    friend class ProcessSingleton<SoundSamplePlayer>;
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
