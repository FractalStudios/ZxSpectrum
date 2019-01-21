// "Home-made" includes.
#include    "StdAfx.h"
#include    "DrawingElement.h"
#include    "FallingSimulationScreen.h"
#include    "ZxSpectrum.h"

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Falling simulation screen item attributes.
struct FallingSimulationScreenItemAttributes
{
    FALLING_SIMULATION_SCREEN_ITEM_ID   m_itemId;           // The identifier of the falling simulation screen item.
    UInt16                              m_bitmapResourceId; // The falling simulation screen item's bitmap resource identifier.
    Int32                               m_screenXLeft;      // The screen X left of the falling simulation screen item.
    Int32                               m_screenYTop;       // The screen Y top of the falling simulation screen item.
    ZxSpectrum::COLOUR                  m_colour;           // The colour of the falling simulation screen item.
 }; // Endstruct.

// Falling simulation screen item attributes table.
static  const   FallingSimulationScreenItemAttributes   g_fallingSimulationScreenAttributesTable [] =
{
//      m_itemId                            m_bitmapResourceId                  m_screenXLeft   m_screenYTop    m_colour
    {   FALLING_SIMULATION_SCREEN_ITEM_01,  IDB_BITMAP_FALLING_SIMULATION_01,   0,              0,              ZxSpectrum::BRIGHT | ZxSpectrum::WHITE, },
    {   FALLING_SIMULATION_SCREEN_ITEM_02,  IDB_BITMAP_FALLING_SIMULATION_02,   0,              0,              ZxSpectrum::BRIGHT | ZxSpectrum::WHITE, },
    {   FALLING_SIMULATION_SCREEN_ITEM_03,  IDB_BITMAP_FALLING_SIMULATION_03,   0,              0,              ZxSpectrum::BRIGHT | ZxSpectrum::WHITE, },
    {   FALLING_SIMULATION_SCREEN_ITEM_04,  IDB_BITMAP_FALLING_SIMULATION_04,   0,              0,              ZxSpectrum::BRIGHT | ZxSpectrum::WHITE, },
    {   FALLING_SIMULATION_SCREEN_ITEM_05,  IDB_BITMAP_FALLING_SIMULATION_05,   0,              0,              ZxSpectrum::BRIGHT | ZxSpectrum::WHITE, },
    {   FALLING_SIMULATION_SCREEN_ITEM_06,  IDB_BITMAP_FALLING_SIMULATION_06,   0,              0,              ZxSpectrum::BRIGHT | ZxSpectrum::WHITE, },
};


// Falling screen static members.
Folio::Core::Util::Sound::SoundSamplesList  FallingSimulationScreen::m_soundSamplesList;    // The sound samples list.

FallingSimulationScreen::FallingSimulationScreen ()
{
    // Create the screen sequence.

    CreateScreenSequence ();

    // Create the sound samples.

    CreateSoundSamples ();
} // Endproc.


FallingSimulationScreen::~FallingSimulationScreen ()
{
} // Endproc.


FolioStatus FallingSimulationScreen::BuildScreenItems (FolioHandle  dcHandle, 
                                                       FolioHandle  instanceHandle)
{                               
    FolioStatus status = ERR_SUCCESS;

    // Build the falling simulation screen items. 

    for (UInt32 index = 0; 
         (status == ERR_SUCCESS) && (index < (sizeof (g_fallingSimulationScreenAttributesTable) / sizeof (FallingSimulationScreenItemAttributes)));
         ++index)
    {              
        // Build the falling simulation screen item.

        switch (g_fallingSimulationScreenAttributesTable [index].m_itemId)
        {
        case FALLING_SIMULATION_SCREEN_ITEM_01:
        case FALLING_SIMULATION_SCREEN_ITEM_02:
        case FALLING_SIMULATION_SCREEN_ITEM_03:
        case FALLING_SIMULATION_SCREEN_ITEM_04:
        case FALLING_SIMULATION_SCREEN_ITEM_05:
        case FALLING_SIMULATION_SCREEN_ITEM_06:
            {
                // Create a falling simulation screen graphic item.
            
                Folio::Core::Game::GraphicItemPtr   item(new Folio::Core::Game::GraphicItemPtr::element_type);
            
                status = item->Create (dcHandle,
                                       instanceHandle,
                                       DRAWING_ELEMENT_FALLING_SIMULATION_SCREEN_ITEM,
                                       g_fallingSimulationScreenAttributesTable [index].m_bitmapResourceId,
                                       g_fallingSimulationScreenAttributesTable [index].m_itemId,
                                       g_fallingSimulationScreenAttributesTable [index].m_screenXLeft, 
                                       g_fallingSimulationScreenAttributesTable [index].m_screenYTop,
                                       ZxSpectrum::DEFAULT_SCREEN_SCALE, 
                                       ZxSpectrum::GetBitmapChangeColour (),
                                       ZxSpectrum::MapInkColour (g_fallingSimulationScreenAttributesTable [index].m_colour));

                if (status == ERR_SUCCESS)
                {
                    // Store the falling simulation screen item in the falling simulation screen items list.

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


FolioStatus FallingSimulationScreen::QueryScreenDrawingElements (FolioHandle                            dcHandle,
                                                                 Folio::Core::Game::DrawingElementsList &drawingElementsList) const
{
    FolioStatus status = ERR_SUCCESS;

    drawingElementsList.clear ();   // Initialise!

    // Query the drawing elements of the falling simulation screen items.

    bool    finished = false;   // Initialise!

    for (ItemsList::const_iterator itr = m_itemsList.begin ();
         !finished && (status == ERR_SUCCESS) && (itr != m_itemsList.end ());
         ++itr)
    {
        // Get the falling simulation screen graphic item.

        Folio::Core::Game::GraphicItemPtr   item(std::dynamic_pointer_cast<Folio::Core::Game::GraphicItem> (*itr));

        // Only display one falling simulation screen item at a time, so is this 
        // falling simulation screen item the current one in the screen sequence?

        if (item->GetItemId () == *m_currentScreenSequenceListItr)
        {
            // Yes. Get the falling simulation screen item's drawing elements.

            Folio::Core::Game::DrawingElementsList  itemDrawingElementsList(item->GetDrawingElementsList ());

            // Add the falling simulation screen item's drawing elements
            // to the drawing elements list.

            drawingElementsList.insert (drawingElementsList.end (), 
                                        itemDrawingElementsList.begin (),
                                        itemDrawingElementsList.end ()); 

            finished = true;
        } // Endif.

    } // Endfor.

    if (status != ERR_SUCCESS)
    {
        drawingElementsList.clear ();
    } // Endif.

    return (status);
} // Endproc.


FolioStatus FallingSimulationScreen::StartDisplayingScreen ()
{
    // Start from the beginning of the screen sequence.
            
    m_currentScreenSequenceListItr = m_screenSequenceList.begin ();

    // Play the sound samples.

    Folio::Core::Util::Sound::PlayAsyncSoundSamples (m_soundSamplesList);

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus FallingSimulationScreen::ProcessScreenFrame (UInt32 *frameRateIncrement)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we completed the screen sequence?

    if (++m_currentScreenSequenceListItr == m_screenSequenceList.end ())
    {
        // Yes. The falling simulation is complete.

        // Stop displaying the falling simulation screen.

        StopDisplaying ();
    } // Endif.

    else
    {
        // No. Update the falling simulation screen.

        status = UpdateScreen ();
    } // Endelse.

    return (status);
} // Endproc.


FolioStatus FallingSimulationScreen::UpdateScreen ()
{
    FolioStatus status = ERR_SUCCESS;

    // Get the canvas graphics.

    Gdiplus::Graphics   *graphics = m_canvas->GetCanvasGraphics ();

    // Update the falling simulation screen items.

    bool    finished        = false;   // Initialise!
    bool    redrawCanvas    = false;

    for (ItemsList::iterator itr = m_itemsList.begin ();
         !finished && (status == ERR_SUCCESS) && (itr != m_itemsList.end ());
         ++itr)
    {
        // Get the falling simulation screen graphic item.

        Folio::Core::Game::GraphicItemPtr   item(std::dynamic_pointer_cast<Folio::Core::Game::GraphicItem> (*itr));

        // Only display one falling simulation screen item at a time, so is this 
        // falling simulation screen item the current one in the screen sequence?

        if (item->GetItemId () == *m_currentScreenSequenceListItr)
        {
            // Yes. Draw it.

            status = item->Draw (*graphics);
            
            redrawCanvas    = true;
            finished        = true;
        } // Endif.

    } // Endfor.

    if (redrawCanvas && (status == ERR_SUCCESS))
    {
        // The canvas should be redrawn on the next draw.

        m_canvas->SetRedrawRqd ();
    } // Endif.

    return (status);
} // Endproc.


void    FallingSimulationScreen::CreateScreenSequence ()
{
    // Create the screen sequence of falling simulation screens.

    m_screenSequenceList.push_back (FALLING_SIMULATION_SCREEN_ITEM_01);  
    m_screenSequenceList.push_back (FALLING_SIMULATION_SCREEN_ITEM_02);  

    for (UInt32 index = 0; index < 42; ++index)
    {
        m_screenSequenceList.push_back (FALLING_SIMULATION_SCREEN_ITEM_03);
        m_screenSequenceList.push_back (FALLING_SIMULATION_SCREEN_ITEM_04);
        m_screenSequenceList.push_back (FALLING_SIMULATION_SCREEN_ITEM_05);
        m_screenSequenceList.push_back (FALLING_SIMULATION_SCREEN_ITEM_06);
    } // Endfor.

    // Start from the beginning of the screen sequence.

    m_currentScreenSequenceListItr = m_screenSequenceList.begin ();
} // Endproc.


void    FallingSimulationScreen::CreateSoundSamples ()
{
    if (m_soundSamplesList.empty ())
    {
        // Create each sound sample representing the required sound.

        for (ZxSpectrum::BYTE frequency = 0x80; frequency <= 0xff; ++frequency)
        {
            m_soundSamplesList.push_back (ZxSpectrum::MapUltimateMakeSound (frequency, 0x08));
        } // Endfor.
        
    } // Endif.

} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
