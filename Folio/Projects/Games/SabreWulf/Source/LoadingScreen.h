#pragma once

// STL includes.
#include    <memory>

// "Home-made" includes.
#include    <Applet.h>
#include    <Game.h>
#include    <Util.h>
#include    "DrawingElement.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Loading screen item identifier enumeration.
enum LOADING_SCREEN_ITEM_ID
{
    LOADING_SCREEN_ITEM_GRAPHIC = DRAWING_ELEMENT_LOADING_SCREEN_ITEM * MAX_NUM_DRAWING_ELEMENTS_PER_ITEM,
}; // Endenum.


// Loading screen.
class LoadingScreen : public Folio::Core::Applet::AScreen
{
public:
    LoadingScreen ();
    ~LoadingScreen ();

private:
    UInt32  m_currentSoundSampleIndex;  // The current sound sample index.
    Folio::Core::Util::Sound::SoundSamplesList  m_soundSamplesList; // The sound samples list.

    // AScreen method(s).
    virtual FolioStatus BuildScreenItems (FolioHandle dcHandle, 
                                          FolioHandle instanceHandle);
    virtual FolioStatus ProcessScreenInput (); 
    virtual FolioStatus ProcessScreenFrame ();

    void    CreateSoundSampleSequence ();
    FolioStatus PlaySoundSample ();
    bool    IsSoundSampleSequenceFinished () const;

    // Private copy constructor to prevent copying.
    LoadingScreen (const LoadingScreen& rhs);

    // Private assignment operator to prevent copying.
    LoadingScreen& operator= (const LoadingScreen& rhs);
}; // Endclass.

// Loading screen pointer.
typedef std::shared_ptr<LoadingScreen>  LoadingScreenPtr;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
