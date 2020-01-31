#pragma once

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

// Loading screen item identifier enumeration.
enum LOADING_SCREEN_ITEM_ID
{
    LOADING_SCREEN_ITEM_UNDEFINED = Folio::Core::Game::AItem::ITEM_ID_UNDEFINED,
    LOADING_SCREEN_ITEM_GRAPHIC,
}; // Endenum.


// Loading screen.
class LoadingScreen : public Folio::Core::Applet::AScreen
{
public:
    LoadingScreen ();
    ~LoadingScreen ();

private:
    static  UInt32  m_currentSoundSampleIndex;  // The current sound sample index.
    static  Folio::Core::Util::Sound::SoundSamplesList  m_soundSamplesList; // The sound samples list.

    // AScreen method(s).
    virtual FolioStatus BuildScreenItems (FolioHandle dcHandle, 
                                          FolioHandle instanceHandle);
    virtual FolioStatus StartDisplayingScreen ();
    virtual FolioStatus ProcessScreenInput (); 
    virtual FolioStatus ProcessScreenFrame ();

    static  void    CreateSoundSamples ();
    static  FolioStatus PlaySoundSample ();

    // Private copy constructor to prevent copying.
    LoadingScreen (const LoadingScreen& rhs);

    // Private assignment operator to prevent copying.
    LoadingScreen& operator= (const LoadingScreen& rhs);
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
