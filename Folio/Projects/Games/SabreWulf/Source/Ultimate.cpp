// "Home-made" includes.
#include    "StdAfx.h"
#include    "Ultimate.h"

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

namespace Ultimate
{

// Frequency table entry.
struct FrequencyTableEntry
{
    FrequencyTableEntry (Folio::Core::Game::ZxSpectrum::BYTE    frequency,
                         Folio::Core::Game::ZxSpectrum::BYTE    duration,
                         Folio::Core::Game::ZxSpectrum::BYTE    numLoopsLoByte,
                         Folio::Core::Game::ZxSpectrum::BYTE    numLoopsHiByte)
    :   m_frequency(frequency),
        m_duration(duration),
        m_numLoops(MAKEWORD(numLoopsLoByte, numLoopsHiByte))
    {
    } // Endproc.

    Folio::Core::Game::ZxSpectrum::WORD   m_frequency;
    Folio::Core::Game::ZxSpectrum::BYTE   m_duration;
    Folio::Core::Game::ZxSpectrum::WORD   m_numLoops;
}; // Endstruct.

// Frequency table.
static  const   FrequencyTableEntry g_frequencyTable [] =
{
    { 0x00, 0x00, 0x00, 0x00, },
    { 0xf4, 0x0a, 0x08, 0x00, },    { 0x65, 0x0a, 0x09, 0x00, },    { 0xde, 0x09, 0x09, 0x00, },    { 0x5e, 0x09, 0x0a, 0x00, },     
    { 0xe7, 0x08, 0x0a, 0x00, },    { 0x75, 0x08, 0x0b, 0x00, },    { 0x0a, 0x08, 0x0c, 0x00, },    { 0xa5, 0x07, 0x0c, 0x00, },    
    { 0x45, 0x07, 0x0d, 0x00, },    { 0xeb, 0x06, 0x0e, 0x00, },    { 0x96, 0x06, 0x0f, 0x00, },    { 0x46, 0x06, 0x0f, 0x00, },    
    { 0xfa, 0x05, 0x10, 0x00, },    { 0xb3, 0x05, 0x11, 0x00, },    { 0x6f, 0x05, 0x12, 0x00, },    { 0x2f, 0x05, 0x13, 0x00, },    
    { 0xf3, 0x04, 0x15, 0x00, },    { 0xf3, 0x04, 0x16, 0x00, },    { 0x85, 0x04, 0x17, 0x00, },    { 0x52, 0x04, 0x19, 0x00, },    
    { 0x23, 0x04, 0x1a, 0x00, },    { 0xf6, 0x03, 0x1c, 0x00, },    { 0xcb, 0x03, 0x1d, 0x00, },    { 0xa3, 0x03, 0x1f, 0x00, },
    { 0x7d, 0x03, 0x21, 0x00, },    { 0x59, 0x03, 0x23, 0x00, },    { 0x38, 0x03, 0x25, 0x00, },    { 0x18, 0x03, 0x27, 0x00, },
    { 0xfa, 0x02, 0x29, 0x00, },    { 0xdd, 0x02, 0x2c, 0x00, },    { 0xc2, 0x02, 0x2e, 0x00, },    { 0xa9, 0x02, 0x31, 0x00, },
    { 0x91, 0x02, 0x34, 0x00, },    { 0x7b, 0x02, 0x37, 0x00, },    { 0x66, 0x02, 0x3a, 0x00, },    { 0x51, 0x02, 0x3e, 0x00, },
    { 0x3f, 0x02, 0x41, 0x00, },    { 0x2d, 0x02, 0x45, 0x00, },    { 0x1c, 0x02, 0x49, 0x00, },    { 0x0c, 0x02, 0x4e, 0x00, },
    { 0xfd, 0x01, 0x52, 0x00, },    { 0xef, 0x01, 0x57, 0x00, },    { 0xe2, 0x01, 0x5d, 0x00, },    { 0xd5, 0x01, 0x62, 0x00, },
    { 0xc9, 0x01, 0x68, 0x00, },    { 0xbd, 0x01, 0x6e, 0x00, },    { 0xb3, 0x01, 0x75, 0x00, },    { 0xa9, 0x01, 0x7b, 0x00, },
    { 0x9f, 0x01, 0x83, 0x00, },    { 0x96, 0x01, 0x8b, 0x00, },    { 0x8e, 0x01, 0x93, 0x00, },    { 0x86, 0x01, 0x9c, 0x00, },
    { 0x7e, 0x01, 0xa5, 0x00, },    { 0x77, 0x01, 0xaf, 0x00, },    { 0x71, 0x01, 0xb9, 0x00, },    { 0x6a, 0x01, 0xc4, 0x00, },
    { 0x64, 0x01, 0xd0, 0x00, },    { 0x5f, 0x01, 0xdc, 0x00, },    { 0x59, 0x01, 0xe9, 0x00, },    { 0x54, 0x01, 0xf7, 0x00, },
};

// Jump condition instruction t-states.
static  const   UInt32  TSTATE_DJNZ_B_ZERO      = 8;   
static  const   UInt32  TSTATE_DJNZ_B_NOT_ZERO  = 13;

static  const   UInt32  TSTATE_JRNZ_CONDITION_NOT_MET     = 7;   
static  const   UInt32  TSTATE_JRNZ_CONDITION_MET         = 12;


// T-state macros.

// (MakeTune).
#define MUSIC_FREQUENCY_TSTATES(frequency, duration)            11 + 4 + 11 +\
                                                                (2 * (TSTATE_DJNZ_B_ZERO + (TSTATE_DJNZ_B_NOT_ZERO * (frequency - 1)))) +\
                                                                ((duration - 1) * 2 * (TSTATE_DJNZ_B_ZERO + (TSTATE_DJNZ_B_NOT_ZERO * 255))) +\
                                                                (2 * (4 + TSTATE_JRNZ_CONDITION_MET + (TSTATE_JRNZ_CONDITION_NOT_MET * (duration - 1)))) +\
                                                                10 + 11 + 7 + 11

// (MakeTune).
#define MUSIC_DURATION_TSTATES(frequency, duration, numLoops)   (numLoops * (10 + 6 + 4 + 4 + MUSIC_FREQUENCY_TSTATES(frequency, duration))) +\
                                                                (2 * (TSTATE_JRNZ_CONDITION_MET + (TSTATE_JRNZ_CONDITION_NOT_MET * (numLoops - 1))))

// (Beeper).
#define SOUND_FREQUENCY_TSTATES(frequency)                      7 + 11 + 2 + 4 + 4 + 4 + 11 + 2 + 4 + 4 + 10 +\
                                                                (2 * (TSTATE_DJNZ_B_ZERO + (TSTATE_DJNZ_B_NOT_ZERO * (frequency - 1))))

// (MakeSound).
#define SOUND_DURATION_TSTATES(frequency, numLoops)             numLoops * (17 + 4 + 12 + SOUND_FREQUENCY_TSTATES(frequency))


static  UInt32  CalculateSoundDuration (Folio::Core::Game::ZxSpectrum::BYTE frequency,
                                        Folio::Core::Game::ZxSpectrum::BYTE numLoops)
{
    return (Folio::Core::Game::ZxSpectrum::CalculateDuration (SOUND_DURATION_TSTATES(frequency, numLoops)));
} // Endproc.


static  float   CalculateSoundFrequency (Folio::Core::Game::ZxSpectrum::BYTE frequency) 
{
    return (Folio::Core::Game::ZxSpectrum::CalculateFrequency (SOUND_FREQUENCY_TSTATES(frequency)));
} // Endproc.


static  UInt32  CalculateMusicDuration (Folio::Core::Game::ZxSpectrum::BYTE frequency,
                                        Folio::Core::Game::ZxSpectrum::BYTE duration,
                                        Folio::Core::Game::ZxSpectrum::WORD numLoops)
{
    return (Folio::Core::Game::ZxSpectrum::CalculateDuration (MUSIC_DURATION_TSTATES(frequency, duration, numLoops)));
} // Endproc.


static  float   CalculateMusicFrequency (Folio::Core::Game::ZxSpectrum::BYTE    frequency,
                                         Folio::Core::Game::ZxSpectrum::BYTE    duration)
{
    return (Folio::Core::Game::ZxSpectrum::CalculateFrequency (MUSIC_FREQUENCY_TSTATES(frequency, duration)));
} // Endproc.


static  Folio::Core::Util::Sound::SoundSample   CreateMusicSample (Folio::Core::Game::ZxSpectrum::BYTE  frequency,
                                                                   Folio::Core::Game::ZxSpectrum::BYTE  duration,
                                                                   Folio::Core::Game::ZxSpectrum::WORD  numLoops)
{
    return (Folio::Core::Util::Sound::SoundSample(CalculateMusicDuration (frequency, duration, numLoops),
                                                  CalculateMusicFrequency (frequency, duration)));
} // Endproc.


Folio::Core::Util::Sound::SoundSample   CreateSoundSample (Folio::Core::Game::ZxSpectrum::BYTE  frequency,
                                                           Folio::Core::Game::ZxSpectrum::WORD  numLoops)
{
    return (Folio::Core::Util::Sound::SoundSample(CalculateSoundDuration (frequency, numLoops),
                                                  CalculateSoundFrequency (frequency)));
} // Endproc.


Folio::Core::Util::Sound::SoundSamplesList  CreateMusicSamples (const ByteList& tune)
{
    Folio::Core::Util::Sound::SoundSamplesList  soundSamplesList;

    for (ByteList::const_iterator itr = tune.begin ();
         itr != tune.end ();
         ++itr)
    {
        // Bits 0 thru 5 holds the frequency table index.

        UInt32  frequencyTableIndex = *itr & 0x3f;

        if (frequencyTableIndex && 
            (frequencyTableIndex < (sizeof (g_frequencyTable) / sizeof (FrequencyTableEntry))))
        {
            // Get the frequency table entry.

            const   FrequencyTableEntry &frequencyTableEntry(g_frequencyTable [frequencyTableIndex]);

            // Calculate the total number of loops.

            Folio::Core::Game::ZxSpectrum::WORD totalNumloops = frequencyTableEntry.m_numLoops;

            // Bits 6 thru 7 holds the loop counter.

            UInt32  loopCounter = (*itr & 0xc0) >> 6;

            while (loopCounter)
            {
                totalNumloops += frequencyTableEntry.m_numLoops; 
                loopCounter--;
            } // Endwhile.

            // Create the sound sample.

            soundSamplesList.push_back (CreateMusicSample (frequencyTableEntry.m_frequency,
                                                           frequencyTableEntry.m_duration,
                                                           totalNumloops));
        } // Endif.

        else
        {
            FOLIO_DEBUG_BREAK;
        } // Endelse.

    } // Endfor.

    return (soundSamplesList);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
