// "Home-made" includes.
#include    "StdAfx.h"
#include    "DrawingElement.h"
#include    "LoadingScreen.h"

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Loading screen item attributes.
typedef Folio::Core::Game::ItemAttributes<LOADING_SCREEN_ITEM_ID>   LoadingScreenItemAttributes;

// Loading screen item attributes table.
static  const   LoadingScreenItemAttributes g_loadingScreenAttributesTable [] =
{
//      m_itemId                        m_bitmapResourceId          m_screenXLeft   m_screenYTop    m_colour
    {   LOADING_SCREEN_ITEM_GRAPHIC,    IDB_BITMAP_LOADING_SCREEN,  0,              0,              Folio::Core::Game::ZxSpectrum::UNDEFINED},
};


// Loading screen static members.
UInt32  LoadingScreen::m_currentSoundSampleIndex = 0;   // The current sound sample index.
Folio::Core::Util::Sound::SoundSamplesList  LoadingScreen::m_soundSamplesList;  // The sound samples list.

LoadingScreen::LoadingScreen ()
{
    // Create the sound samples.

    CreateSoundSamples ();
} // Endproc.


LoadingScreen::~LoadingScreen ()
{
} // Endproc.


FolioStatus LoadingScreen::BuildScreenItems (FolioHandle    dcHandle, 
                                             FolioHandle    instanceHandle)
{                               
    FolioStatus status = ERR_SUCCESS;

    // Build the loading screen items. 

    for (UInt32 index = 0; 
         (status == ERR_SUCCESS) && (index < (sizeof (g_loadingScreenAttributesTable) / sizeof (LoadingScreenItemAttributes)));
         ++index)
    {              
        // Build the loading screen item.

        switch (g_loadingScreenAttributesTable [index].m_itemId)
        {
        case LOADING_SCREEN_ITEM_GRAPHIC:
            {
                // Create a loading screen graphic item.
            
                Folio::Core::Game::GraphicItemPtr   item(new Folio::Core::Game::GraphicItemPtr::element_type);
            
                status = item->Create (dcHandle,
                                       instanceHandle,
                                       DRAWING_ELEMENT_LOADING_SCREEN_ITEM,
                                       g_loadingScreenAttributesTable [index].m_bitmapResourceId,
                                       g_loadingScreenAttributesTable [index].m_itemId,
                                       g_loadingScreenAttributesTable [index].m_screenXLeft, 
                                       g_loadingScreenAttributesTable [index].m_screenYTop,
                                       Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE);

                if (status == ERR_SUCCESS)
                {
                    // Store the loading screen item in the loading screen items list.

                    m_itemsList.push_back (item);
                } // Endif.
            
            } // Endscope.
            break;

        default:
            status = ERR_INVALID;
            break;
        } // Endswitch.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus LoadingScreen::StartDisplayingScreen ()
{
    // Start from the beginning of the sound sample sequence.
            
    m_currentSoundSampleIndex = 0;

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus LoadingScreen::ProcessScreenInput ()
{
    if (Folio::Core::Util::KeyInput::IsAnyKeyDown ())
    {
        // Stop displaying the loading screen.

        StopDisplaying ();
    } // Endif.

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus LoadingScreen::ProcessScreenFrame (UInt32 *frameRateIncrement)
{
    // Play the loading screen's sound sample.

    PlaySoundSample ();

    return (ERR_SUCCESS);
} // Endproc.


void    LoadingScreen::CreateSoundSamples ()
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

  
void    LoadingScreen::PlaySoundSample ()
{
    // Have we completed the sound sample sequence?

    if (m_currentSoundSampleIndex < m_soundSamplesList.size ())
    {
        // No. Play the current sound sample.

        Folio::Core::Util::Sound::PlaySoundSample (m_soundSamplesList [m_currentSoundSampleIndex++]);
    } // Endif.

} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
