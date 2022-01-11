// "Home-made" includes.
#include    <Util.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Sound Resources.
class SoundResources
{
public:
    SoundResources ();
    ~SoundResources ();

    FolioStatus Create ();

    FolioHandle GetStartGameSound () const;
    FolioHandle GetPlayerMoving1Sound () const;
    FolioHandle GetPlayerMoving2Sound () const;
    FolioHandle GetPlayerCollectedItemSound () const;
    FolioHandle GetPlayerInfectionFinishingSound () const;
    FolioHandle GetPlayerStrikingBossSound () const;
    FolioHandle GetPlayerTerminatingSound () const;
    FolioHandle GetNastyInitialisingSound () const;
    FolioHandle GetNastyTerminatingSound () const;

    FolioStatus PlayStartGameSound () const;
    FolioStatus PlayPlayerCollectedItemSound () const;
    FolioStatus PlayPlayerInfectionFinishingSound () const;
    FolioStatus PlayPlayerStrikingBossSound () const;

private:
    FolioHandle m_startGame;                // The start game sound resource.
    FolioHandle m_playerMoving1;            // The player moving 1 sound resource.
    FolioHandle m_playerMoving2;            // The player moving 2 sound resource.
    FolioHandle m_playerCollectedItem;      // The player collected item sound resource.
    FolioHandle m_playerInfectionFinishing; // The player infection finishing sound resource.
    FolioHandle m_playerStrikingBoss;       // The player striking boss sound resource.
    FolioHandle m_playerTerminating;        // The player terminating sound resource.
    FolioHandle m_nastyInitialising;        // The nasty intialising sound resource.
    FolioHandle m_nastyTerminating;         // The nasty terminating sound resource.
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/