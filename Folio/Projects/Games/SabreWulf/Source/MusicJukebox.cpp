// "Home-made" includes.
#include    "StdAfx.h"
#include    "MusicJukebox.h"
#include    "Ultimate.h"

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Main game tune.
static  Ultimate::ByteList g_mainGameTune = 
{
    0x19, 0x1d, 0x20, 0x25, 0x29, 0x20, 0x25, 0x29, 0x19, 0x1d, 0x20, 0x25, 0x29, 0x25, 0x20, 0x1d,
    0x1b, 0x1e, 0x22, 0x27, 0x2a, 0x22, 0x27, 0x2a, 0x1b, 0x1e, 0x22, 0x27, 0x2a, 0x27, 0x22, 0x1e,
    0x18, 0x1b, 0x20, 0x24, 0x27, 0x20, 0x24, 0x27, 0x18, 0x1b, 0x20, 0x24, 0x27, 0x24, 0x20, 0x1b,
    0x19, 0x1d, 0x20, 0x25, 0x29, 0x20, 0x25, 0x29, 0x19, 0x1d, 0x20, 0x25, 0x29, 0x25, 0x20, 0x1d,
    0x19, 0x1d, 0x22, 0x29, 0x2e, 0x22, 0x29, 0x2e, 0x19, 0x1d, 0x22, 0x29, 0x2e, 0x29, 0x22, 0x1d,
    0x19, 0x1b, 0x1f, 0x22, 0x27, 0x1f, 0x22, 0x27, 0x19, 0x1b, 0x1f, 0x22, 0x27, 0x22, 0x1f, 0x1b,
    0x1b, 0x20, 0x24, 0x27, 0x2c, 0x24, 0x27, 0x2c, 0x1b, 0x20, 0x24, 0x27, 0x2c, 0x27, 0x24, 0x20,
    0x18, 0x19, 0x1d, 0x20, 0x25, 0x1d, 0x20, 0x25, 0x18, 0x19, 0x1d, 0x20, 0x25, 0x20, 0x1d, 0x19,
    0x16, 0x19, 0x1d, 0x20, 0x25, 0x1d, 0x20, 0x25, 0x16, 0x19, 0x1d, 0x20, 0x25, 0x20, 0x1d, 0x19,
    0x13, 0x16, 0x1b, 0x1f, 0x25, 0x1b, 0x1f, 0x25, 0x13, 0x16, 0x1b, 0x1f, 0x25, 0x1f, 0x1b, 0x16,
    0x14, 0x18, 0x1b, 0x20, 0x24, 0x1b, 0x20, 0x24, 0x14, 0x18, 0x1b, 0x20, 0x24, 0x20, 0x1b, 0x18,
    0x19, 0x1d, 0x20, 0x25, 0x29, 0x20, 0x25, 0x29, 0x19, 0x1d, 0x20, 0x25, 0x29, 0x25, 0x20, 0x1d,
};


// Starting game tune.
static  Ultimate::ByteList g_startingGameTune = 
{
    0x59, 0x14, 0x17, 0x59, 0x14, 0x17, 0x19, 0x1C, 0x14, 0x1C, 0x99,
};


// Game over tune.
static  Ultimate::ByteList g_gameOverTune = 
{
    0x18, 0x21, 0x1d, 0x17, 0x20, 0x1d, 0x16, 0x1f, 0x1c, 0x1d,
};


// Found amulet piece tune.
static  Ultimate::ByteList g_foundAmuletPieceTune = 
{
    0x67, 0x69, 0x6a, 0x6c, 0x6a, 0x69, 0x67, 0x65, 0x27, 0x29, 
    0x27, 0x29, 0x27, 0x29, 0x27, 0x29, 0xa7, 
};


MusicJukebox::MusicJukebox ()
:   m_currentMusic(NO_MUSIC),
    m_currentSoundSampleIndex(0)
{
} // Endproc.


MusicJukebox::~MusicJukebox ()
{
} // Endproc.


FolioStatus MusicJukebox::Create ()
{
    FolioStatus status = ERR_SUCCESS;

    // Create the main game music.

    m_mainGameMusic = Ultimate::CreateMusicSamples (g_mainGameTune);

    // Create the starting game music.

    m_startingGameMusic = Ultimate::CreateMusicSamples (g_startingGameTune);

    // Create the game over music.

    m_gameOverMusic = Ultimate::CreateMusicSamples (g_gameOverTune);

    // Create the found amulet piece music.

    m_foundAmuletPieceMusic = Ultimate::CreateMusicSamples (g_foundAmuletPieceTune);

    return (status);
} // Endproc.


FolioStatus MusicJukebox::PlayMainGameMusic (bool &isFinished)
{
    // Play the main game music.

    return (PlayMusic (MAIN_GAME_MUSIC, m_mainGameMusic, true, isFinished));
} // Endproc.


FolioStatus MusicJukebox::PlayStartingGameMusic (bool &isFinished)
{
    // Play the starting game music.

    return (PlayMusic (STARTING_GAME_MUSIC, m_startingGameMusic, false, isFinished));
} // Endproc.


FolioStatus MusicJukebox::PlayGameOverMusic (bool &isFinished)
{
    // Play the game over music.

    return (PlayMusic (GAME_OVER_MUSIC, m_gameOverMusic, false, isFinished));
} // Endproc.


FolioStatus MusicJukebox::PlayFoundAmuletPieceMusic (bool &isFinished)
{
    // Play the found amulet piece music.

    return (PlayMusic (FOUND_AMULET_PIECE_MUSIC, m_foundAmuletPieceMusic, false, isFinished));
} // Endproc.


FolioStatus MusicJukebox::StopPlayingMusic ()
{
    // Stop playing music.

    StopPlayingMusic (m_currentMusic);

    return (Folio::Core::Util::Sound::StopPlayingSoundSamples ());
} // Endproc.


FolioStatus MusicJukebox::PlayMusic (MUSIC                                              music,
                                     const Folio::Core::Util::Sound::SoundSamplesList   &soundSamplesList,
                                     bool                                               playAsynchronously,
                                     bool                                               &isFinished)
{
    FolioStatus status = ERR_SUCCESS;

    // Start playing the music.

    StartPlayingMusic (music);

    // Have we completed the sound sample sequence?

    isFinished = m_currentSoundSampleIndex >= soundSamplesList.size ();

    if (isFinished)
    {
        // Yes.

        StopPlayingMusic (music);
    } // Endif.

    else
    {
        // No. Play the current sound sample.

        status = Folio::Core::Util::Sound::PlaySoundSample (soundSamplesList [m_currentSoundSampleIndex++],
                                                            playAsynchronously);
    } // Endelse.

    return (status);
} // Endproc.


void    MusicJukebox::StartPlayingMusic (MUSIC music)
{
    // Are we already playing the music?

    if (m_currentMusic != music)
    {
        // No.

        m_currentMusic              = music;    // Initialise!
        m_currentSoundSampleIndex   = 0;
    } // Endif.

} // Endproc.
 

void    MusicJukebox::StopPlayingMusic (MUSIC music)
{
    m_currentMusic              = NO_MUSIC; // Reset.
    m_currentSoundSampleIndex   = 0;
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
