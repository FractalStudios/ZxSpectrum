#pragma once

// STL includes.
#include    <vector>

// "Home-made" includes.
#include    <Applet.h>
#include    <Game.h>
#include    <Util.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Falling simulation screen item identifier enumeration.
enum FALLING_SIMULATION_SCREEN_ITEM_ID
{
    FALLING_SIMULATION_SCREEN_ITEM_UNDEFINED = Folio::Core::Game::AItem::ITEM_ID_UNDEFINED,
    FALLING_SIMULATION_SCREEN_ITEM_01,
    FALLING_SIMULATION_SCREEN_ITEM_02,
    FALLING_SIMULATION_SCREEN_ITEM_03,
    FALLING_SIMULATION_SCREEN_ITEM_04,
    FALLING_SIMULATION_SCREEN_ITEM_05,
    FALLING_SIMULATION_SCREEN_ITEM_06,
}; // Endenum.


// Falling simulation screen.
class FallingSimulationScreen : public Folio::Core::Applet::AScreen
{
public:
    FallingSimulationScreen ();
    ~FallingSimulationScreen ();

private:
    // Screen sequence list.
    typedef std::vector<FALLING_SIMULATION_SCREEN_ITEM_ID>  ScreenSequenceList;

    ScreenSequenceList              m_screenSequenceList;           // The screen sequence list.
    ScreenSequenceList::iterator    m_currentScreenSequenceListItr; // The current screen sequence.

    static  UInt32  m_currentSoundSampleIndex;  // The current sound sample index.
    static  Folio::Core::Util::Sound::SoundSamplesList  m_soundSamplesList; // The sound samples list.

    // AScreen method(s).
    virtual FolioStatus BuildScreenItems (FolioHandle dcHandle, 
                                          FolioHandle instanceHandle);
    virtual FolioStatus QueryScreenDrawingElements (FolioHandle                             dcHandle,
                                                    Folio::Core::Game::DrawingElementsList  &drawingElementsList) const;
    virtual FolioStatus StartDisplayingScreen ();
    virtual FolioStatus ProcessScreenFrame ();

    FolioStatus UpdateScreen ();
    void    CreateScreenSequence ();
   
    static  void    CreateSoundSamples ();
    static  FolioStatus PlaySoundSample ();

    // Private copy constructor to prevent copying.
    FallingSimulationScreen (const FallingSimulationScreen& rhs);

    // Private assignment operator to prevent copying.
    FallingSimulationScreen& operator= (const FallingSimulationScreen& rhs);
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
