#pragma once

// STL includes.
#include    <vector>

// "Home-made" includes.
#include    <Game.h>
#include    <Graphic.h>
#include    "Canvas.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Applet
{

class AScreen
{
public:
    virtual ~AScreen ();

    FolioStatus Create (Canvas&                 canvas,
                        const Gdiplus::Rect&    clearRect,
                        UInt32                  minTimeToDisplay = 0);
    FolioStatus HandleProcessFrame (UInt32* frameRateIncrement = 0);

    bool    IsDisplaying () const;
    bool    IsComplete () const;

protected:
    Canvas*         m_canvas;           // The canvas.
    Gdiplus::Rect   m_clearScreenRect;  // The screen rect to clear when displaying the screen.

    Folio::Core::Game::Gamepad::CONTROLLER_ID   m_controllerId; // The controller identifier of the first connected controller.

    UInt32  m_minTimeToDisplay;         // The minimal time (in milliseconds) to display the screen.
    bool    m_isDisplaying;             // Indicates if the screen is being displayed.
    UInt32  m_initialFrameTickCount;    // The initial frame tick count.
    UInt32  m_previousFrameTickCount;   // The previous frame tick count.

    Folio::Core::Game::ItemsList    m_itemsList; // The screen items.

    AScreen ();

    FolioStatus Display ();
    FolioStatus StopDisplaying ();

    virtual FolioStatus BuildScreenItems (FolioHandle   dcHandle, 
                                          FolioHandle   instanceHandle) = 0;
    virtual FolioStatus QueryScreenDrawingElements (FolioHandle                             dcHandle,
                                                    Folio::Core::Game::DrawingElementsList& drawingElementsList) const;
    virtual FolioStatus SetupGamepad (Folio::Core::Game::Gamepad& gamepad);
    virtual FolioStatus StartDisplayingScreen ();
    virtual FolioStatus ProcessScreenInput ();
    virtual FolioStatus ProcessScreenFrame (UInt32* frameRateIncrement);
    virtual FolioStatus UpdateScreen ();

private:
    FolioStatus DrawInCanvas () const;
    FolioStatus CheckInput ();
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
