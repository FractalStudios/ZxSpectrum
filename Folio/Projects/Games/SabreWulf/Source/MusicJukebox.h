// "Home-made" includes.
#include    <Util.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Music jukebox.
class MusicJukebox
{
public:
    MusicJukebox ();
    ~MusicJukebox ();

    FolioStatus Create ();

    FolioStatus PlayMainGameMusic (bool &isFinished);
    FolioStatus PlayStartingGameMusic (bool &isFinished);
    FolioStatus PlayGameOverMusic (bool &isFinished);
    FolioStatus PlayFoundAmuletPieceMusic (bool &isFinished);
    FolioStatus StopPlayingMusic ();

private:
    // Music enumeration.
    enum MUSIC
    {
        NO_MUSIC = 0,
        MAIN_GAME_MUSIC,
        STARTING_GAME_MUSIC,
        GAME_OVER_MUSIC,
        FOUND_AMULET_PIECE_MUSIC,
    }; // Endenum.

    MUSIC   m_currentMusic;             // The current music being played.
    UInt32  m_currentSoundSampleIndex;  // The current sound sample index into the current music being played.

    Folio::Core::Util::Sound::SoundSamplesList  m_mainGameMusic;            // Main game music.
    Folio::Core::Util::Sound::SoundSamplesList  m_startingGameMusic;        // Starting game music.
    Folio::Core::Util::Sound::SoundSamplesList  m_gameOverMusic;            // Game over music.
    Folio::Core::Util::Sound::SoundSamplesList  m_foundAmuletPieceMusic;    // Found amulet piece music.
    
    FolioStatus PlayMusic (MUSIC                                            music,
                           const Folio::Core::Util::Sound::SoundSamplesList &soundSamplesList,
                           bool                                             playAsynchronously,
                           bool                                             &isFinished);

    void    StartPlayingMusic (MUSIC music);
    void    StopPlayingMusic (MUSIC music);
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/