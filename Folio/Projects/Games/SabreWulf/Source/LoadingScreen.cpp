// "Home-made" includes.
#include    "StdAfx.h"
#include    "LoadingScreen.h"

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Loading screen item attributes.
static  const   Folio::Core::Game::ItemAttributesList<LOADING_SCREEN_ITEM_ID> g_loadingScreenAttributes =
{
//      m_itemId                        m_bitmapResourceId          m_screenXLeft   m_screenYTop    m_colour
    {   LOADING_SCREEN_ITEM_GRAPHIC,    IDB_BITMAP_LOADING_SCREEN,  0,              0,              Folio::Core::Game::ZxSpectrum::UNDEFINED},
};


LoadingScreen::LoadingScreen ()
:   m_currentSoundSampleIndex(0)
{
    // Create the sound sample sequence.

    CreateSoundSampleSequence ();
} // Endproc.


LoadingScreen::~LoadingScreen ()
{
} // Endproc.


FolioStatus LoadingScreen::BuildScreenItems (FolioHandle    dcHandle, 
                                             FolioHandle    instanceHandle)
{                               
    FolioStatus status = ERR_SUCCESS;

    // Build the loading screen items. 

    for (Folio::Core::Game::ItemAttributesList<LOADING_SCREEN_ITEM_ID>::const_iterator itr = g_loadingScreenAttributes.begin (); 
         (status == ERR_SUCCESS) && (itr != g_loadingScreenAttributes.end ());
         ++itr)
    {              
        // Build the loading screen item.

        switch (itr->m_itemId)
        {
        case LOADING_SCREEN_ITEM_GRAPHIC:
            // Add loading screen graphic item.

            status = AddGraphicItem (dcHandle, 
                                     instanceHandle ,
                                     Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_LOADING_SCREEN_ITEM,
                                     *itr);
            break;

        default:
            status = ERR_INVALID;
            break;
        } // Endswitch.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus LoadingScreen::ProcessScreenInput ()
{
    // Only process screen input once the loading screen's sound sample sequence 
    // has finished.

    if (IsSoundSampleSequenceFinished () &&
        Folio::Core::Util::KeyInput::IsAnyKeyDown ())
    {
        // Stop displaying the loading screen.

        StopDisplaying ();
    } // Endif.

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus LoadingScreen::ProcessScreenFrame ()
{
    // Play the loading screen's sound sample.

    return (PlaySoundSample ());
} // Endproc.


void    LoadingScreen::CreateSoundSampleSequence ()
{
    // Create each sound sample representing the required sound.

    UInt32  milliseconds = Folio::Core::Game::ZxSpectrum::BeepDurationToMilliseconds (0.1f);

    for (Int32 pitch = 1; pitch <= 5; ++pitch)
    {
        m_soundSamplesList.push_back (Folio::Core::Util::Sound::SoundSample (milliseconds, 
                                                                             Folio::Core::Game::ZxSpectrum::BeepPitchToFrequency (pitch)));
    } // Endfor.

    m_currentSoundSampleIndex = 0;  // Initialise!
} // Endproc.

  
FolioStatus LoadingScreen::PlaySoundSample ()
{
    FolioStatus status = ERR_SUCCESS;

    // Have we finished the sound sample sequence?

    if (!IsSoundSampleSequenceFinished ())
    {
        // No. Play the current sound sample.

        status = Folio::Core::Util::Sound::PlaySoundSample (m_soundSamplesList [m_currentSoundSampleIndex++],
                                                            false); // Play synchronously.
    } // Endif.

    return (status);
} // Endproc.


bool    LoadingScreen::IsSoundSampleSequenceFinished () const
{
    return (m_currentSoundSampleIndex >= m_soundSamplesList.size ());
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
