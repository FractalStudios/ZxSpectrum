// "Home-made" includes.
#include    "AScreen.h"

namespace Folio
{

namespace Core
{

namespace Applet
{

AScreen::AScreen ()
:   m_canvasBag(0),
    m_controllerId(Folio::Core::Game::Gamepad::CONTROLLER_ID_UNDEFINED),
    m_minTimeToDisplay(0),
    m_isDisplaying(false),
    m_initialFrameTickCount(0),
    m_previousFrameTickCount(0)
{
} // Endproc.


AScreen::~AScreen ()
{
} // Endproc.


FolioStatus AScreen::Create (CanvasBag&             canvasBag,
                             const Gdiplus::Rect&   clearScreenRect,
                             UInt32                 minTimeToDisplay)
{
    // Note the screen attributes.

    m_canvasBag         = &(canvasBag);
    m_clearScreenRect   = clearScreenRect;
    m_minTimeToDisplay  = minTimeToDisplay;

    // Get the first connected controller.

    m_controllerId = canvasBag.GetCanvasGamepad ()->GetFirstConnectedController ();

    // Build the screen items.

    return (BuildScreenItems (canvasBag.GetCanvasDcHandle (), canvasBag.GetAppletInstanceHandle ()));
} // Endproc.


FolioStatus AScreen::HandleProcessFrame (UInt32* frameRateIncrement)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the screen being displayed?

    if (m_isDisplaying)
    {
        // Yes. Let the screen process the frame.

        status = ProcessScreenFrame (frameRateIncrement);
    } // Endif.

    else
    {
        // No. Display the screen.
        
        status = Display ();
    } // Endelse.

    return (status);
} // Endproc.


FolioStatus AScreen::HandleProcessKeyboardMsg (UInt32   wParam,
                                               UInt32   lParam,
                                               bool     keyDown)
{
    FolioStatus status = ERR_SUCCESS;

    // Has the screen been displayed for the minimum time required?

    if ((Folio::Core::Util::DateTime::GetCurrentTickCount () - m_initialFrameTickCount) > m_minTimeToDisplay)
    {
        // Yes. Let the screen process the keyboard message.

        status = ProcessScreenKeyboardMsg (wParam, lParam, keyDown);
    } // Endif.

    return (status);
} // Endproc.


bool    AScreen::IsDisplaying () const
{
    return (m_isDisplaying);
} // Endproc.


bool    AScreen::IsComplete () const
{
    return (!m_isDisplaying);
} // Endproc.


FolioStatus AScreen::Display ()
{
    // Clear the canvas bag.

    FolioStatus status = m_canvasBag->ClearCanvas ();

    if (status == ERR_SUCCESS)
    {
        // Is there a gamepad controller connected?

        if (m_controllerId != Folio::Core::Game::Gamepad::CONTROLLER_ID_UNDEFINED)
        {
            // Yes. Setup the gamepad.

            status = SetupGamepad (*m_canvasBag->GetCanvasGamepad ());
        } // Endif.

        if (status == ERR_SUCCESS)
        {
            // Start displaying.

            status = StartDisplayingScreen ();

            if (status == ERR_SUCCESS)
            {
                // Add the screen items to the canvas bag.

                status = AddToCanvasBag ();

                if (status == ERR_SUCCESS)
                {
                    // The screen is being displayed.

                    m_isDisplaying = true;
                
                    // Set the initial and previous frame tick counts.

                    m_initialFrameTickCount     = Folio::Core::Util::DateTime::GetCurrentTickCount (); 
                    m_previousFrameTickCount    = m_initialFrameTickCount;
                } // Endif.
    
            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus AScreen::StopDisplaying ()
{
    // Clear the canvas bag.

    FolioStatus status = m_canvasBag->ClearCanvas ();

    if (status == ERR_SUCCESS)
    {
        // The screen is not being displayed.

        m_isDisplaying = false;
    } // Endif.

    return (status);
} // Endproc.


FolioStatus AScreen::QueryScreenDrawingElements (FolioHandle                            dcHandle,
                                                 Folio::Core::Game::DrawingElementsList &drawingElementsList) const
{
    FolioStatus status = ERR_SUCCESS;

    drawingElementsList.clear ();   // Initialise!

    // Query the drawing elements of the screen items.

    for (ItemsList::const_iterator itr = m_itemsList.begin ();
         (status == ERR_SUCCESS) && (itr != m_itemsList.end ());
         ++itr)
    {
        // Get the screen item's drawing elements.

        Folio::Core::Game::DrawingElementsList  itemDrawingElementsList((*itr)->GetDrawingElementsList ());

        // Add the game over screen item's drawing elements to the drawing elements list.

        drawingElementsList.insert (drawingElementsList.end (), 
                                    itemDrawingElementsList.begin (),
                                    itemDrawingElementsList.end ()); 
    } // Endfor.

    if (status != ERR_SUCCESS)
    {
        drawingElementsList.clear ();
    } // Endif.

    return (status);
} // Endproc.


FolioStatus AScreen::SetupGamepad (Folio::Core::Game::Gamepad& gamepad)
{
    // Clear the gamepad controller's key mappings.

    gamepad.ClearKeyMappings (m_controllerId);

    // Set the gamepad controller's key mappings.

    gamepad.AddKeyMapping (m_controllerId, Folio::Core::Game::Gamepad::BUTTON_START,          VK_RETURN);
    gamepad.AddKeyMapping (m_controllerId, Folio::Core::Game::Gamepad::BUTTON_BACK,           VK_BACK);            
    gamepad.AddKeyMapping (m_controllerId, Folio::Core::Game::Gamepad::BUTTON_LEFT_THUMB,     VK_LBUTTON);      
    gamepad.AddKeyMapping (m_controllerId, Folio::Core::Game::Gamepad::BUTTON_RIGHT_THUMB,    VK_RBUTTON);     
    gamepad.AddKeyMapping (m_controllerId, Folio::Core::Game::Gamepad::BUTTON_LEFT_SHOULDER,  VK_XBUTTON1);   
    gamepad.AddKeyMapping (m_controllerId, Folio::Core::Game::Gamepad::BUTTON_RIGHT_SHOULDER, VK_XBUTTON2);  
    gamepad.AddKeyMapping (m_controllerId, Folio::Core::Game::Gamepad::BUTTON_A,              'A');
    gamepad.AddKeyMapping (m_controllerId, Folio::Core::Game::Gamepad::BUTTON_B,              'B');
    gamepad.AddKeyMapping (m_controllerId, Folio::Core::Game::Gamepad::BUTTON_X,              'X');
    gamepad.AddKeyMapping (m_controllerId, Folio::Core::Game::Gamepad::BUTTON_Y,              'Y');

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus AScreen::StartDisplayingScreen ()
{
    return (ERR_SUCCESS);
} // Endproc.


FolioStatus AScreen::ProcessScreenFrame (UInt32* frameRateIncrement)
{
    return (ERR_SUCCESS);
} // Endproc.


FolioStatus AScreen::ProcessScreenKeyboardMsg (UInt32   wParam,
                                               UInt32   lParam,
                                               bool     keyDown)
{
    return (ERR_SUCCESS);
} // Endproc.


FolioStatus AScreen::UpdateScreen ()
{
    return (ERR_SUCCESS);
} // Endproc.


FolioStatus AScreen::AddToCanvasBag () const
{
    // Query the drawing elements of the screen.

    Folio::Core::Game::DrawingElementsList  drawingElementsList;

    FolioStatus status = QueryScreenDrawingElements (m_canvasBag->GetCanvasDcHandle (), 
                                                     drawingElementsList);

    if (status == ERR_SUCCESS)
    {
        // Clear the canvas rect.

        status = m_canvasBag->ClearCanvasRectangle (m_clearScreenRect);

        if (status == ERR_SUCCESS)
        {
            // Add the screen item's drawing elements to the canvas bag.

            status = m_canvasBag->AddDrawingElements (drawingElementsList,
                                                      true);    // Draw into the canvas bag.
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
