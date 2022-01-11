// "Home-made" includes.
#include    "stdafx.h"
#include    "CollisionGrid.h"

namespace Folio
{

namespace Games
{

namespace AticAtac
{

CollisionGrid::CollisionGrid ()
{
} // Endproc.


CollisionGrid::~CollisionGrid ()
{
} // Endproc.


bool    CollisionGrid::IsExitedScreen (DIRECTION        direction,
                                       bool             externalToFloorBound,
                                       Gdiplus::Rect&   spriteScreenRect,
                                       bool&            isAtLockedScreenExit,
                                       bool&            isInScreenExit,
                                       ScreenExit&      screenExit) const
{
    isAtLockedScreenExit    = false; // Initialise!
    isInScreenExit          = false;

    bool    isExitedScreen = false;   // Initialise!

    // Outwith the floor bound?

    Int32   floorBound = 0; // Initialise!

    if (IsOutwithFloorBound (direction, externalToFloorBound, spriteScreenRect, &(floorBound)))
    {
        // Yes. Exited?

        bool    foundExit = false;   // Initialise!

        for (ScreenExitList::const_iterator itr = m_screenExits.begin ();
             !foundExit && (itr != m_screenExits.end ());
             ++itr)
        {
            switch (direction)
            {
            case UP:
                if ((itr->m_orientation == ScreenExit::TOP)                             &&
                   ((floorBound + 1) >= itr->m_screenRect.Y)                            &&
                    (floorBound <= (itr->m_screenRect.Y + itr->m_screenRect.Height))    &&
                    (spriteScreenRect.X >= itr->m_screenRect.X)                         &&
                   ((spriteScreenRect.X + spriteScreenRect.Width) <= (itr->m_screenRect.X + itr->m_screenRect.Width)))
                {
                    foundExit = true;
    
                    // What is the screen exit's state?

                    switch (itr->m_state)
                    {
                    case ScreenExit::OPEN:
                        isInScreenExit  = true;
                        isExitedScreen  = (spriteScreenRect.Y < itr->m_screenRect.Y);
                        screenExit      = *itr;
                        break;

                    case ScreenExit::LOCKED:
                        isAtLockedScreenExit    = true;
                        screenExit              = *itr;
                        break;

                    case ScreenExit::CLOSED:
                    default:
                        break;
                    } // Endswitch.

                } // Endif.
                break; 

            case DOWN:
                if ((itr->m_orientation == ScreenExit::BOTTOM)                          &&
                    ((floorBound + 1) >= itr->m_screenRect.Y)                           &&
                     (floorBound <= (itr->m_screenRect.Y + itr->m_screenRect.Height))   &&
                     (spriteScreenRect.X >= itr->m_screenRect.X)                        &&
                    ((spriteScreenRect.X + spriteScreenRect.Width) <= (itr->m_screenRect.X + itr->m_screenRect.Width)))
                {
                    foundExit = true;
 
                    // What is the screen exit's state?

                    switch (itr->m_state)
                    {
                    case ScreenExit::OPEN:
                        isInScreenExit  = true;
                        isExitedScreen  = ((spriteScreenRect.Y + spriteScreenRect.Height) > (itr->m_screenRect.Y + itr->m_screenRect.Height));
                        screenExit      = *itr;
                        break;

                    case ScreenExit::LOCKED:
                        isAtLockedScreenExit    = true;
                        screenExit              = *itr;
                        break;

                    case ScreenExit::CLOSED:
                    default:
                        break;
                    } // Endswitch.

                } // Endif.
                break; 

            case LEFT:
                if ((itr->m_orientation == ScreenExit::LEFT)                        &&
                   ((floorBound + 1) >= itr->m_screenRect.X)                        &&
                    (floorBound <= (itr->m_screenRect.X + itr->m_screenRect.Width)) &&
                    (spriteScreenRect.Y >= itr->m_screenRect.Y)                     &&
                   ((spriteScreenRect.Y + spriteScreenRect.Height) <= (itr->m_screenRect.Y + itr->m_screenRect.Height)))
                {
                    foundExit = true;

                    // What is the screen exit's state?

                    switch (itr->m_state)
                    {
                    case ScreenExit::OPEN:
                        isInScreenExit  = true;
                        isExitedScreen  = (spriteScreenRect.X < itr->m_screenRect.X);
                        screenExit      = *itr;
                        break;

                    case ScreenExit::LOCKED:
                        isAtLockedScreenExit    = true;
                        screenExit              = *itr;
                        break;

                    case ScreenExit::CLOSED:
                    default:
                        break;
                    } // Endswitch.

                } // Endif.
                break; 

            case RIGHT:
                if ((itr->m_orientation == ScreenExit::RIGHT)                           &&
                    ((floorBound + 1) >= itr->m_screenRect.X)                           &&
                     (floorBound <= (itr->m_screenRect.X + itr->m_screenRect.Width))    &&
                     (spriteScreenRect.Y >= itr->m_screenRect.Y)                        &&
                    ((spriteScreenRect.Y + spriteScreenRect.Height) <= (itr->m_screenRect.Y + itr->m_screenRect.Height)))
                {
                    foundExit = true;

                    // What is the screen exit's state?

                    switch (itr->m_state)
                    {
                    case ScreenExit::OPEN:
                        isInScreenExit  = true;
                        isExitedScreen  = ((spriteScreenRect.X + spriteScreenRect.Width) > (itr->m_screenRect.X + itr->m_screenRect.Width));
                        screenExit      = *itr;
                        break;

                    case ScreenExit::LOCKED:
                        isAtLockedScreenExit    = true;
                        screenExit              = *itr;
                        break;

                    case ScreenExit::CLOSED:
                    default:
                        break;
                    } // Endswitch.

                } // Endif.
                break; 

            default:
                break; 
            } // Endswitch.

            // Check for any exit on the floor.

            if (!foundExit                                                                                          && 
                (itr->m_orientation == ScreenExit::FLOOR)                                                           &&
                (spriteScreenRect.X >= itr->m_screenRect.X)                                                         &&
                ((spriteScreenRect.X + spriteScreenRect.Width) <= (itr->m_screenRect.X + itr->m_screenRect.Width))  &&
                (spriteScreenRect.Y >= itr->m_screenRect.Y)                                                         &&
                ((spriteScreenRect.Y + spriteScreenRect.Height) <= (itr->m_screenRect.Y + itr->m_screenRect.Height)))
            {
                foundExit = true;

                // Is this exit open?

                if (itr->IsOpen ())
                {
                    // Yes. Note the screen exit.

                    isInScreenExit  = true;
                    isExitedScreen  = true;
                    screenExit      = *itr;
                } // Endif.

            } // Endif.

        } // Endfor.

        // In a screen exit or at a locked screen exit?

        if (!isInScreenExit || isAtLockedScreenExit)
        {
            // Bound by the floor.

            ToFloorBound (direction, floorBound, spriteScreenRect);
        } // Endif.

    } // Endif.

    else
    {
        // Check for any exit on the floor.

        isExitedScreen = Folio::Core::Game::ACollisionGrid::IsExitedScreen (spriteScreenRect,
                                                                            isInScreenExit,
                                                                            screenExit);
    } // Endelse.

    return (isExitedScreen);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
