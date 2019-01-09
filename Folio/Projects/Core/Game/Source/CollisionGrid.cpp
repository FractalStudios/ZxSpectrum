// C includes.
#include    <math.h>

// "Home-made" includes.
#include    "CollisionGrid.h"
#include    "DrawingElement.h"

namespace Folio
{

namespace Core
{

namespace Game
{

CollisionGrid::CollisionGrid ()
{
} // Endproc.


CollisionGrid::~CollisionGrid ()
{
} // Endproc.


FolioStatus CollisionGrid::Create (const Gdiplus::Rect &floorRect)
{
    // Note the floor rect of the colllision grid.

    m_floorRect = floorRect;

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus CollisionGrid::Clear ()
{
    // No grid.

    m_grid.clear ();

    // No screen exits.

    m_screenExits.clear ();

    return (ERR_SUCCESS);
} // Endproc.


Gdiplus::Rect   CollisionGrid::GetFloorRect () const
{
    return (Gdiplus::Rect(GetFloorLeftBound (),
                          GetFloorTopBound (),
                          GetFloorRightBound (),
                          GetFloorBottomBound ()));
} // Endproc.


Int32   CollisionGrid::GetFloorLeftBound () const
{
    return (m_floorRect.X);
} // Endproc.


Int32   CollisionGrid::GetFloorRightBound () const
{
    return (m_floorRect.X + m_floorRect.Width - 1);
} // Endproc.


Int32   CollisionGrid::GetFloorTopBound () const
{
    return (m_floorRect.Y);
} // Endproc.


Int32   CollisionGrid::GetFloorBottomBound () const
{
    return (m_floorRect.Y + m_floorRect.Height - 1);
} // Endproc.


Int32   CollisionGrid::GetFloorWidth () const
{
    return (m_floorRect.Width);
} // Endproc.


Int32   CollisionGrid::GetFloorHeight () const
{
    return (m_floorRect.Height);
} // Endproc.


FolioStatus CollisionGrid::AddDrawingElement (const DrawingElement& drawingElement)
{
    // Is the drawing element in the grid?

    Grid::const_iterator    itr = 
        std::find_if (m_grid.begin (), m_grid.end (), 
                      [&drawingElement](const DrawingElement& arg) 
                      {return ((arg.GetUserData () == drawingElement.GetUserData ()) &&
                               (arg.GetScreenRect ().Equals (drawingElement.GetScreenRect ())));});

    if (itr == m_grid.end ())
    {
        // No. Add it to the grid.

        m_grid.push_back (drawingElement);
    } // Endif.

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus CollisionGrid::RemoveDrawingElement (const DrawingElement& drawingElement)
{
    // Is the drawing element in the grid?

    Grid::const_iterator    itr = 
        std::find_if (m_grid.begin (), m_grid.end (), 
                      [&drawingElement](const DrawingElement& arg) 
                      {return ((arg.GetUserData () == drawingElement.GetUserData ()) &&
                               (arg.GetScreenRect ().Equals (drawingElement.GetScreenRect ())));});

    if (itr != m_grid.end ())
    {
        // Remove it from the grid.

        m_grid.erase (itr);
    } // Endif.

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus CollisionGrid::UpdateDrawingElement (const DrawingElement& drawingElement)
{
    // Remove the drawing element from the grid.

    FolioStatus status = RemoveDrawingElement (drawingElement);

    if (status == ERR_SUCCESS)
    {
        // Add it into the grid.

        m_grid.push_back (drawingElement);
    } // Endif.

    return (status);
} // Endproc.


bool    CollisionGrid::FindDrawingElement (DrawingElement::UserData userData,
                                           DrawingElement&          drawingElement) const
{
    // Find the drawing element in the collision grid.

    Grid::const_iterator    itr = 
        std::find_if (m_grid.begin (), m_grid.end (), 
                      [&userData](const DrawingElement& arg) 
                      {return (arg.GetUserData () == userData);});

    bool    found = (itr != m_grid.end ());

    if (found)
    {
        // Note the drawing element.

        drawingElement = *itr;
    } // Endif.

    return (found);
} // Endproc.


bool    CollisionGrid::FindDrawingElements (DrawingElement::Id      drawingElementId,
                                            DrawingElementsList&    drawingElementsList) const
{
    drawingElementsList.clear ();   // Initialise!

    // Find the drawing elements in the collision grid.

    for (Grid::const_iterator itr = m_grid.begin ();
         itr != m_grid.end ();
         ++itr)
    {
        if (itr->GetDrawingElementId () == drawingElementId)
        {
            // Add the drawing element to the list of drawing elements.

            drawingElementsList.push_back (*itr);
        } // Endif.

    } // Endfor.

    return (!drawingElementsList.empty ());
} // Endproc.


bool    CollisionGrid::IsCollision (const Gdiplus::Rect&    spriteScreenRect,
                                    CellElements&           cellCollisionElements) const
{
    cellCollisionElements.clear ();    // Initialise!

    // Check for a collision.

    for (CellElements::const_iterator itr = m_grid.begin ();
         itr != m_grid.end ();
         ++itr)
    {
        if (itr->IsOverlap (spriteScreenRect))
        {
            // Store the grid's drawing element.

            cellCollisionElements.push_back (*itr);
        } // Endif.

    } // Endfor.

    return (!cellCollisionElements.empty ());
} // Endproc.


bool    CollisionGrid::IsCollision (const Gdiplus::Rect&    spriteScreenRect,
                                    CellValue               cellValue,
                                    CellElements&           cellCollisionElements) const
{
    cellCollisionElements.clear ();    // Initialise!

    // Check for a collision.

    for (CellElements::const_iterator itr = m_grid.begin ();
         itr != m_grid.end ();
         ++itr)
    {
        if ((itr->GetCollisionGridCellValue () == cellValue) && 
             itr->IsOverlap (spriteScreenRect))
        {
            // Store the grid's drawing element.

            cellCollisionElements.push_back (*itr);
        } // Endif.

    } // Endfor.

    return (!cellCollisionElements.empty ());
} // Endproc.


FolioStatus CollisionGrid::AddScreenExit (const ScreenExit& screenExit)
{
    // Is the screen exit in the list of screen exits?

    if (!IsScreenExit (screenExit))
    {
        // No. Add it.

        m_screenExits.push_back (screenExit);
    } // Endif.

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus CollisionGrid::RemoveScreenExit (const ScreenExit& screenExit)
{
    // Is the screen exit in the list of screen exits?

    ScreenExitList::const_iterator  itr = 
        std::find_if (m_screenExits.begin (), m_screenExits.end (), 
                      [&screenExit](const ScreenExit& arg) {return (arg.m_screenRect.Equals (screenExit.m_screenRect));});

    if (itr != m_screenExits.end ())
    {
        // Remove it.

        m_screenExits.erase (itr);
    } // Endif.

    return (ERR_SUCCESS);
} // Endproc.


bool    CollisionGrid::IsScreenExit (const ScreenExit& screenExit) const
{
    // Is the screen exit in the list of screen exits?

    return (std::find_if (m_screenExits.begin (), 
                          m_screenExits.end (), 
                          [&screenExit](const ScreenExit& arg) {return (arg.m_screenRect.Equals (screenExit.m_screenRect));}) != m_screenExits.end ());
} // Endproc.


FolioStatus CollisionGrid::OpenScreenExit (ScreenExit::UserData userData)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the screen exit in the list of screen exits?

    ScreenExitList::iterator    itr = 
        std::find_if (m_screenExits.begin (), m_screenExits.end (), 
                      [&userData](const ScreenExit& arg) {return (arg.m_userData == userData);});

    if (itr == m_screenExits.end ())
    {
        // No.

        status = ERR_NOT_FOUND;
    } // Endif.

    else
    {
        // Yes. Open it.

        itr->m_state = ScreenExit::OPEN;
    } // Endelse.

    return (status);
} // Endproc.


FolioStatus CollisionGrid::CloseScreenExit (ScreenExit::UserData userData)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the screen exit in the list of screen exits?

    ScreenExitList::iterator    itr = 
        std::find_if (m_screenExits.begin (), m_screenExits.end (), 
                      [&userData](const ScreenExit& arg) {return (arg.m_userData == userData);});

    if (itr == m_screenExits.end ())
    {
        // No.

        status = ERR_NOT_FOUND;
    } // Endif.

    else
    {
        // Yes. Close it.

        itr->m_state = ScreenExit::CLOSED;
    } // Endelse.

    return (status);
} // Endproc.


bool    CollisionGrid::IsScreenExit (ScreenExit::UserData userData) const
{
    // Is the screen exit in the list of screen exits?

    return (std::find_if (m_screenExits.begin (), m_screenExits.end (), 
                          [&userData](const ScreenExit& arg) {return (arg.m_userData == userData);}) != m_screenExits.end ());
} // Endproc.


bool    CollisionGrid::IsExitedScreen (DIRECTION        direction,
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

    if (IsOutwithFloorBound (direction, spriteScreenRect, &(floorBound)))
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

        isExitedScreen = IsExitedScreen (spriteScreenRect,
                                         isInScreenExit,
                                         screenExit);
    } // Endelse.

    return (isExitedScreen);
} // Endproc.


bool    CollisionGrid::IsExitedScreen (const Gdiplus::Rect& spriteScreenRect,
                                       bool&                isInScreenExit,
                                       ScreenExit&          screenExit) const
{
    bool    isExitedScreen  = false;   // Initialise!
    bool    foundExit       = false;

    // Exited?

    for (ScreenExitList::const_iterator itr = m_screenExits.begin ();
         !foundExit && (itr != m_screenExits.end ());
         ++itr)
    {
        if ((itr->m_orientation == ScreenExit::FLOOR)                                                           &&
            (spriteScreenRect.X >= itr->m_screenRect.X)                                                         &&
            ((spriteScreenRect.X + spriteScreenRect.Width) <= (itr->m_screenRect.X + itr->m_screenRect.Width))  &&
            (spriteScreenRect.Y >= itr->m_screenRect.Y)                                                         &&
            ((spriteScreenRect.Y + spriteScreenRect.Height) <= (itr->m_screenRect.Y + itr->m_screenRect.Height)))
        {
            foundExit = true;
       
            if (itr->IsOpen ())
            {
                // Note the screen exit.
                
                isInScreenExit  = true;
                isExitedScreen  = true;
                screenExit      = *itr;
            } // Endif.

        } // Endif.

    } // Endfor.

    return (isExitedScreen);
} // Endproc.


bool    CollisionGrid::IsEnteringScreen (DIRECTION              direction,
                                         const Gdiplus::Rect&   spriteScreenRect,
                                         bool&                  isInScreenExit,
                                         ScreenExit&            screenExit) const
{
    bool    isEnteringScreen = false;   // Initialise!

    switch (direction)
    {
    case UP:
        isEnteringScreen = ((spriteScreenRect.Y + spriteScreenRect.Height - 1) > GetFloorBottomBound ());
        break;

    case DOWN:
        isEnteringScreen = (spriteScreenRect.Y < GetFloorTopBound ());
        break;

    case LEFT:
        isEnteringScreen = ((spriteScreenRect.X + spriteScreenRect.Width - 1) > GetFloorRightBound ());
        break;

    case RIGHT:
        isEnteringScreen = (spriteScreenRect.X < GetFloorLeftBound ());
        break;

    default:
        break;
    } // Endswitch.

    isInScreenExit              = isEnteringScreen;
    screenExit.m_orientation    = isEnteringScreen ? screenExit.m_orientation : ScreenExit::NONE;

    return (isEnteringScreen);
} // Endproc.


void    CollisionGrid::CheckScreenExitBound (DIRECTION          direction, 
                                             Gdiplus::Rect&     spriteScreenRect,
                                             bool&              isEnteringScreen,
                                             bool&              isInScreenExit,
                                             ScreenExit&        screenExit) const
{
    switch (direction)
    {
    case UP:
        {
            // Get the screen exit's top bound.

            Int32   topScreenExitBound = screenExit.GetTopBound ();

            // Out of bounds?

            switch (screenExit.m_orientation)
            {
            case CollisionGrid::ScreenExit::LEFT:
            case CollisionGrid::ScreenExit::RIGHT:
                if (spriteScreenRect.Y < topScreenExitBound)
                {
                    // Yes. Bound by the screen exit's top bound.

                    spriteScreenRect.Y = topScreenExitBound;
                } // Endif.
                break;

            case CollisionGrid::ScreenExit::BOTTOM:
            case CollisionGrid::ScreenExit::FLOOR:
                if ((spriteScreenRect.Y + spriteScreenRect.Height) <= topScreenExitBound)
                {
                    // Yes. Out of the screen exit.

                    isEnteringScreen            = false;
                    isInScreenExit              = false;
                    screenExit.m_orientation    = ScreenExit::NONE;
                } // Endif.
                break;

            default:
                break;
            } // Endswitch.

        } // Endscope.
        break;

    case DOWN:
        {
            // Get the screen exit's bottom bound.

            Int32   bottomScreenExitBound = screenExit.GetBottomBound ();

            // Out of bounds?

            switch (screenExit.m_orientation)
            {
            case CollisionGrid::ScreenExit::LEFT:
            case CollisionGrid::ScreenExit::RIGHT:
                if ((spriteScreenRect.Y + spriteScreenRect.Height) >= bottomScreenExitBound)
                {
                    // Yes. Bound by the screen exit's bottom bound.

                    spriteScreenRect.Y = bottomScreenExitBound - spriteScreenRect.Height + 1;
                } // Endif.
                break;

            case CollisionGrid::ScreenExit::TOP:
            case CollisionGrid::ScreenExit::FLOOR:
                if (spriteScreenRect.Y > bottomScreenExitBound)
                {
                    // Yes. Out of the screen exit.

                    isEnteringScreen            = false;
                    isInScreenExit              = false;
                    screenExit.m_orientation    = ScreenExit::NONE;
                } // Endif.
                break;

            default:
                break;
            } // Endswitch.

        } // Endscope.
        break;

    case LEFT:
        {
            // Get the screen exit's left bound.

            Int32   leftScreenExitBound = screenExit.GetLeftBound ();

            // Out of bounds?

            switch (screenExit.m_orientation)
            {
            case CollisionGrid::ScreenExit::TOP:
            case CollisionGrid::ScreenExit::BOTTOM:
                if (spriteScreenRect.X < leftScreenExitBound)
                {
                    // Yes. Bound by the screen exit's left bound.

                    spriteScreenRect.X = leftScreenExitBound;
                } // Endif.
                break;

            case CollisionGrid::ScreenExit::RIGHT:
            case CollisionGrid::ScreenExit::FLOOR:
                if ((spriteScreenRect.X + spriteScreenRect.Width) <= leftScreenExitBound)
                {
                    // Yes. Out of the screen exit.

                    isEnteringScreen            = false;
                    isInScreenExit              = false;
                    screenExit.m_orientation    = ScreenExit::NONE;
                } // Endif.
                break;

            default:
                break;
            } // Endswitch.

        } // Endscope.
        break;

    case RIGHT:
        {
            // Get the screen exit's right bound.

            Int32   rightScreenExitBound = screenExit.GetRightBound ();

            // Out of bounds?

            switch (screenExit.m_orientation)
            {
            case CollisionGrid::ScreenExit::TOP:
            case CollisionGrid::ScreenExit::BOTTOM:
                if ((spriteScreenRect.X + spriteScreenRect.Width) >= rightScreenExitBound)
                {
                    // Yes. Bound by the screen exit's right bound.

                    spriteScreenRect.X = rightScreenExitBound - spriteScreenRect.Width + 1;
                } // Endif.
                break;

            case CollisionGrid::ScreenExit::LEFT:
            case CollisionGrid::ScreenExit::FLOOR:
                if (spriteScreenRect.X > rightScreenExitBound)
                {
                    // Yes. Out of the screen exit.

                    isEnteringScreen            = false;
                    isInScreenExit              = false;
                    screenExit.m_orientation    = ScreenExit::NONE;
                } // Endif.
                break;

            default:
                break;
            } // Endswitch.

        } // Endscope.
        break;

    default:
        break;
    } // Endswitch.

} // Endproc.


bool    CollisionGrid::IsOutwithFloorBound (DIRECTION       direction, 
                                            Gdiplus::Rect&  spriteScreenRect,
                                            Int32*          floorBound) const
{
    bool    isOutwithFloorBound = false;    // Initialise!
    Int32   myFloorBound        = 0;

    switch (direction)
    {
    case UP:
        myFloorBound        = GetFloorTopBound ();
        isOutwithFloorBound = spriteScreenRect.Y < myFloorBound;
        break;

    case DOWN:
        myFloorBound        = GetFloorBottomBound ();
        isOutwithFloorBound = (spriteScreenRect.Y + spriteScreenRect.Height - 1) > myFloorBound;
        break;

    case LEFT:
        myFloorBound        = GetFloorLeftBound ();
        isOutwithFloorBound = spriteScreenRect.X < myFloorBound;
        break;

    case RIGHT:
        myFloorBound        = GetFloorRightBound ();
        isOutwithFloorBound = (spriteScreenRect.X + spriteScreenRect.Width - 1) > myFloorBound;
        break;
    } // Endswitch.

    if (floorBound)
    {
        *floorBound = myFloorBound;
    } // Endif.

    else
    if (isOutwithFloorBound)
    {
        ToFloorBound (direction, myFloorBound, spriteScreenRect);
    } // Endelseif.

    return (isOutwithFloorBound);
} // Endproc.


void    CollisionGrid::ToFloorBound (DIRECTION      direction, 
                                     Int32          floorBound,
                                     Gdiplus::Rect& spriteScreenRect) const
{
    // Bound by the floor.

    switch (direction)
    {
    case UP:
        spriteScreenRect.Y = floorBound;
        break;

    case DOWN:
        spriteScreenRect.Y = floorBound - spriteScreenRect.Height + 1;
        break;

    case LEFT:
        spriteScreenRect.X = floorBound;
        break;

    case RIGHT:
        spriteScreenRect.X = floorBound - spriteScreenRect.Width + 1;
        break;
    } // Endswitch.

} // Endproc.


bool    CollisionGrid::IsEmpty (CellValue cellValue)
{
    return (cellValue == CELL_VALUE_EMPTY);
} // Endproc.


bool    CollisionGrid::IsItem (CellValue cellValue)
{
    return ((cellValue & CELL_VALUE_ITEM) == CELL_VALUE_ITEM);
} // Endproc.


bool    CollisionGrid::IsSolidItem (CellValue cellValue)
{
    return ((cellValue & CELL_VALUE_SOLID_ITEM) == CELL_VALUE_SOLID_ITEM);
} // Endproc.


bool    CollisionGrid::IsHealthItem (CellValue cellValue)
{
    return ((cellValue & CELL_VALUE_HEALTH_ITEM) == CELL_VALUE_HEALTH_ITEM);
} // Endproc.


bool    CollisionGrid::IsHarmfulItem (CellValue cellValue)
{
    return ((cellValue & CELL_VALUE_HARMFUL_ITEM) == CELL_VALUE_HARMFUL_ITEM);
} // Endproc.


bool    CollisionGrid::IsCollectableItem (CellValue cellValue)
{
    return ((cellValue & CELL_VALUE_COLLECTABLE_ITEM) == CELL_VALUE_COLLECTABLE_ITEM);
} // Endproc.


bool    CollisionGrid::IsExit (CellValue cellValue)
{
    return ((cellValue & CELL_VALUE_EXIT) == CELL_VALUE_EXIT);
} // Endproc.


bool    CollisionGrid::IsNastySprite (CellValue cellValue)
{
    return ((cellValue & CELL_VALUE_NASTY_SPRITE) == CELL_VALUE_NASTY_SPRITE);
} // Endproc.


bool    CollisionGrid::IsBossSprite (CellValue cellValue)
{
    return ((cellValue & CELL_VALUE_BOSS_SPRITE) == CELL_VALUE_BOSS_SPRITE);
} // Endproc.


bool    CollisionGrid::IsWeaponSprite (CellValue cellValue)
{
    return ((cellValue & CELL_VALUE_WEAPON_SPRITE) == CELL_VALUE_WEAPON_SPRITE);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
