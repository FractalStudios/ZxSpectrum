// "Home-made" includes.
#include    "StdAfx.h"
#include    "DrawingElement.h"
#include    "LoadingScreen.h"
#include    "ZxSpectrum.h"

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Loading screen item attributes.
struct LoadingScreenItemAttributes
{
    LOADING_SCREEN_ITEM_ID  m_itemId;           // The identifier of the loading screen item.
    UInt16                  m_bitmapResourceId; // The loading screen item's bitmap resource identifier (if it's a graphic item).
    Int32                   m_screenXLeft;      // The screen X left of the loading screen item.
    Int32                   m_screenYTop;       // The screen Y top of the loading screen item.
 }; // Endstruct.

// Loading screen item attributes table.
static  const   LoadingScreenItemAttributes   g_loadingScreenAttributesTable [] =
{
//      m_itemId                        m_bitmapResourceId          m_screenXLeft   m_screenYTop
    {   LOADING_SCREEN_ITEM_GRAPHIC,    IDB_BITMAP_LOADING_SCREEN,  0,              0,  },
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
                                       ZxSpectrum::DEFAULT_SCREEN_SCALE);

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

    UInt32  milliseconds = ZxSpectrum::BeepDurationToMilliseconds (0.1f);

    for (Int32 pitch = 1; pitch <= 5; ++pitch)
    {
        m_soundSamplesList.push_back (Folio::Core::Util::Sound::SoundSample (milliseconds, 
                                                                             ZxSpectrum::BeepPitchToFrequency (pitch)));
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
