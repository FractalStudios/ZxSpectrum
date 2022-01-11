// "Home-made" includes.
#include    "StdAfx.h"
#include    "SoundResources.h"

namespace Folio
{

namespace Games
{

namespace SabreWulf
{


SoundResources::SoundResources ()
:   m_startGame(0),
    m_playerMoving1(0),
    m_playerMoving2(0),
    m_playerCollectedItem(0),
    m_playerInfectionFinishing(0),
    m_playerStrikingBoss(0),
    m_playerTerminating(0),
    m_nastyInitialising(0),
    m_nastyTerminating(0)
{
} // Endproc.


SoundResources::~SoundResources ()
{
} // Endproc.


FolioStatus SoundResources::Create ()
{
    // Load the start game resource.

    FolioStatus status = Folio::Core::Util::Sound::LoadSoundResource (NULL, IDB_WAVE_START_GAME , m_startGame);

    if (status != ERR_SUCCESS)
    {
        return (status);
    } // Endif.

    // Load the player moving 1 sound resource.

    status = Folio::Core::Util::Sound::LoadSoundResource (NULL, IDB_WAVE_PLAYER_MOVING_1, m_playerMoving1);

    if (status != ERR_SUCCESS)
    {
        return (status);
    } // Endif.

    // Load the player moving 2 sound resource.

    status = Folio::Core::Util::Sound::LoadSoundResource (NULL, IDB_WAVE_PLAYER_MOVING_2, m_playerMoving2);

    if (status != ERR_SUCCESS)
    {
        return (status);
    } // Endif.

    // Load the player collected item sound resource.

    status = Folio::Core::Util::Sound::LoadSoundResource (NULL, IDB_WAVE_PLAYER_COLLECTED_ITEM, m_playerCollectedItem);

    if (status != ERR_SUCCESS)
    {
        return (status);
    } // Endif.

    // Load the player infection finishing sound resource.

    status = Folio::Core::Util::Sound::LoadSoundResource (NULL, IDB_WAVE_PLAYER_INFECTION_FINISHING, m_playerInfectionFinishing);

    if (status != ERR_SUCCESS)
    {
        return (status);
    } // Endif.

    // Load the player striking boss sound resource.

    status = Folio::Core::Util::Sound::LoadSoundResource (NULL, IDB_WAVE_PLAYER_STRIKING_BOSS, m_playerStrikingBoss);

    if (status != ERR_SUCCESS)
    {
        return (status);
    } // Endif.

    // Load the player terminating sound resource.

    status = Folio::Core::Util::Sound::LoadSoundResource (NULL, IDB_WAVE_PLAYER_TERMINATING, m_playerTerminating);

    if (status != ERR_SUCCESS)
    {
        return (status);
    } // Endif.

    // Load the nasty initialising sound resource.

    status = Folio::Core::Util::Sound::LoadSoundResource (NULL, IDB_WAVE_NASTY_INITIALISING, m_nastyInitialising);

    if (status != ERR_SUCCESS)
    {
        return (status);
    } // Endif.

    // Load the nasty terminating sound resource.

    status = Folio::Core::Util::Sound::LoadSoundResource (NULL, IDB_WAVE_NASTY_TERMINATING, m_nastyTerminating);

    if (status != ERR_SUCCESS)
    {
        return (status);
    } // Endif.

    return (status);
} // Endproc.


FolioHandle SoundResources::GetStartGameSound () const
{
    return (m_startGame);
} // Endproc.


FolioHandle SoundResources::GetPlayerMoving1Sound () const
{
    return (m_playerMoving1);
} // Endproc.


FolioHandle SoundResources::GetPlayerMoving2Sound () const
{
    return (m_playerMoving2);
} // Endproc.


FolioHandle SoundResources::GetPlayerCollectedItemSound () const
{
    return (m_playerCollectedItem);
} // Endproc.


FolioHandle SoundResources::GetPlayerInfectionFinishingSound () const
{
    return (m_playerInfectionFinishing);
} // Endproc.


FolioHandle SoundResources::GetPlayerStrikingBossSound () const
{
    return (m_playerStrikingBoss);
} // Endproc.


FolioHandle SoundResources::GetPlayerTerminatingSound () const
{
    return (m_playerTerminating);
} // Endproc.


FolioHandle SoundResources::GetNastyInitialisingSound () const
{
    return (m_nastyInitialising);
} // Endproc.


FolioHandle SoundResources::GetNastyTerminatingSound () const
{
    return (m_nastyTerminating);
} // Endproc.


FolioStatus SoundResources::PlayStartGameSound () const
{
    return (Folio::Core::Util::Sound::PlaySoundResource (m_startGame, false));  // Play synchronously.
} // Endif.


FolioStatus SoundResources::PlayPlayerCollectedItemSound () const
{
    return (Folio::Core::Util::Sound::PlaySoundResource (m_playerCollectedItem));
} // Endif.


FolioStatus SoundResources::PlayPlayerInfectionFinishingSound () const
{
    return (Folio::Core::Util::Sound::PlaySoundResource (m_playerInfectionFinishing));
} // Endif.


FolioStatus SoundResources::PlayPlayerStrikingBossSound () const
{
    return (Folio::Core::Util::Sound::PlaySoundResource (m_playerStrikingBoss));
} // Endif.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
