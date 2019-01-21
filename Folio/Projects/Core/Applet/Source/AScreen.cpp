// "Home-made" includes.
#include    "AScreen.h"

namespace Folio
{

namespace Core
{

namespace Applet
{

AScreen::AScreen ()
:   m_canvas(0),
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


FolioStatus AScreen::Create (Canvas&                canvas,
                             const Gdiplus::Rect&   clearScreenRect,
                             UInt32                 minTimeToDisplay)
{
    // Note the screen attributes.

    m_canvas            = &(canvas);
    m_clearScreenRect   = clearScreenRect;
    m_minTimeToDisplay  = minTimeToDisplay;

    // Get the first connected controller.

    m_controllerId = canvas.GetCanvasGamepad ()->GetFirstConnectedController ();

    // Build the screen items.

    return (BuildScreenItems (canvas.GetCanvasDcHandle (), canvas.GetAppletInstanceHandle ()));
} // Endproc.


FolioStatus AScreen::HandleProcessFrame (UInt32* frameRateIncrement)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the screen being displayed?

    if (m_isDisplaying)
    {
        // Yes. Check the input.

        status = CheckInput ();

        if (status == ERR_SUCCESS)
        {
            // Let the screen process the frame.

            status = ProcessScreenFrame (frameRateIncrement);
        } // Endif.

    } // Endif.

    else
    {
        // No. Display the screen.
        
        status = Display ();
    } // Endelse.

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
    FolioStatus status = ERR_SUCCESS;

    // Is there a gamepad controller connected?

    if (m_controllerId != Folio::Core::Game::Gamepad::CONTROLLER_ID_UNDEFINED)
    {
        // Yes. Setup the gamepad.

        status = SetupGamepad (*m_canvas->GetCanvasGamepad ());
    } // Endif.

    if (status == ERR_SUCCESS)
    {
        // Start displaying.

        status = StartDisplayingScreen ();

        if (status == ERR_SUCCESS)
        {
            // Draw the screen items in the canvas.

            status = DrawInCanvas ();

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

    return (status);
} // Endproc.


FolioStatus AScreen::StopDisplaying ()
{
    // The screen is not being displayed.

    m_isDisplaying = false;

    return (ERR_SUCCESS);
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
    return (ERR_SUCCESS);
} // Endproc.


FolioStatus AScreen::StartDisplayingScreen ()
{
    return (ERR_SUCCESS);
} // Endproc.


FolioStatus AScreen::ProcessScreenInput ()
{
    return (ERR_SUCCESS);
} // Endproc.


FolioStatus AScreen::ProcessScreenFrame (UInt32* frameRateIncrement)
{
    return (ERR_SUCCESS);
} // Endproc.


FolioStatus AScreen::UpdateScreen ()
{
    return (ERR_SUCCESS);
} // Endproc.


FolioStatus AScreen::DrawInCanvas () const
{
    // Query the drawing elements of the screen.

    Folio::Core::Game::DrawingElementsList  drawingElementsList;

    FolioStatus status = QueryScreenDrawingElements (m_canvas->GetCanvasDcHandle (), 
                                                     drawingElementsList);

    if (status == ERR_SUCCESS)
    {
        // Clear the canvas rect.

        status = m_canvas->ClearCanvasRectangle (m_clearScreenRect);

        if (status == ERR_SUCCESS)
        {
            // Draw the screen item's drawing elements using the canvas.

            status = m_canvas->DrawDrawingElements (drawingElementsList, true); // Draw into the canvas.
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus AScreen::CheckInput ()
{
    FolioStatus status = ERR_SUCCESS;

    // Has the screen been displayed for the minimum time required?

    if ((Folio::Core::Util::DateTime::GetCurrentTickCount () - m_initialFrameTickCount) > m_minTimeToDisplay)
    {
        // Yes. Let the screen process any input.

        status = ProcessScreenInput ();
    } // Endif.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
