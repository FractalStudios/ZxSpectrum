// "Home-made" includes.
#include    "ACollisionGrid.h"
#include    "ASprite.h"

namespace Folio
{

namespace Core
{

namespace Game
{

ACollisionGrid::ACollisionGrid ()
{
} // Endproc.


ACollisionGrid::~ACollisionGrid ()
{
} // Endproc.


FolioStatus ACollisionGrid::Create (const Gdiplus::Rect& floorRect)
{
    // Note the floor rect of the colllision grid.

    m_floorRect = floorRect;

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus ACollisionGrid::Create (const Gdiplus::Rect&                            floorRect,
                                    const Folio::Core::Game::DrawingElementsList&   drawingElementsList)
{
    FolioStatus status = ERR_SUCCESS;

    // Note the floor rect of the colllision grid.

    m_floorRect = floorRect;

    // Add the drawing elements to the collision grid.

    for (Folio::Core::Game::DrawingElementsList::const_iterator itr = drawingElementsList.begin ();
         (status == ERR_SUCCESS) && (itr != drawingElementsList.end ());
         ++itr)
    {
        // Add the drawing element to the collision grid.

        status = AddCellElement (*itr);
    } // Endfor.
    
    return (status);
} // Endproc.


FolioStatus ACollisionGrid::Clear ()
{
    // No grid.

    m_grid.clear ();

    // No screen exits.

    m_screenExits.clear ();

    return (ERR_SUCCESS);
} // Endproc.


Gdiplus::Rect   ACollisionGrid::GetFloorRect () const
{
    return (Gdiplus::Rect(GetFloorLeftBound (),
                          GetFloorTopBound (),
                          GetFloorRightBound (),
                          GetFloorBottomBound ()));
} // Endproc.


Int32   ACollisionGrid::GetFloorLeftBound () const
{
    return (m_floorRect.X);
} // Endproc.


Int32   ACollisionGrid::GetFloorRightBound () const
{
    return (m_floorRect.X + m_floorRect.Width - 1);
} // Endproc.


Int32   ACollisionGrid::GetFloorTopBound () const
{
    return (m_floorRect.Y);
} // Endproc.


Int32   ACollisionGrid::GetFloorBottomBound () const
{
    return (m_floorRect.Y + m_floorRect.Height - 1);
} // Endproc.


Int32   ACollisionGrid::GetFloorWidth () const
{
    return (m_floorRect.Width);
} // Endproc.


Int32   ACollisionGrid::GetFloorHeight () const
{
    return (m_floorRect.Height);
} // Endproc.


FolioStatus ACollisionGrid::AddCellElement (const CellElement& cellElement)
{
    // Is this a wall?

    if (cellElement.m_cellValue == CELL_VALUE_WALL)
    {
        // Yes. Build the wall.

        BuildWall (cellElement);
    } // Endif.

    // Does the cell element support a collision grid cell value?
    
    else
    if (!IsEmpty (cellElement.m_cellValue))
    {
        // Yes. Is the cell element in the grid?

        Grid::const_iterator    itr = std::find (m_grid.begin (), 
                                                 m_grid.end (), 
                                                 cellElement);

        if (itr == m_grid.end ())
        {
            // No. Add it to the grid.

            m_grid.push_back (cellElement);
        } // Endif.
    
    } // Endif.

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus ACollisionGrid::RemoveCellElement (const CellElement& cellElement)
{
    // Does the cell element support a collision grid cell value?

    if (!IsEmpty (cellElement.m_cellValue))
    {
        // Is the cell element in the grid?

        Grid::const_iterator    itr = std::find (m_grid.begin (), 
                                                 m_grid.end (), 
                                                 cellElement);

        if (itr != m_grid.end ())
        {
            // Remove it from the grid.

            m_grid.erase (itr);
        } // Endif.
    
    } // Endif.

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus ACollisionGrid::UpdateCellElement (const CellElement& cellElement)
{
    FolioStatus status = ERR_SUCCESS;

    // Does the cell element support a collision grid cell value?

    if (!IsEmpty (cellElement.m_cellValue))
    {
        // Remove the cell element from the grid.

        status = RemoveCellElement (cellElement);

        if (status == ERR_SUCCESS)
        {
            // Add it into the grid.

            m_grid.push_back (cellElement);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


bool    ACollisionGrid::FindCellElement (CellElement::UserData  userData,
                                         CellElement&           cellElement) const
{
    // Find the cell element in the collision grid.

    Grid::const_iterator    itr = std::find (m_grid.begin (), 
                                             m_grid.end (), 
                                             cellElement);

    bool    found = (itr != m_grid.end ());

    if (found)
    {
        // Note the cell element.

        cellElement = *itr;
    } // Endif.

    return (found);
} // Endproc.


bool    ACollisionGrid::FindCellElements (CellElement::Id   cellElementId,
                                          CellElements&     cellElements) const
{
    cellElements.clear ();  // Initialise!

    // Find the cell elements in the collision grid.

    for (Grid::const_iterator itr = m_grid.begin ();
         itr != m_grid.end ();
         ++itr)
    {
        if (itr->m_id == cellElementId)
        {
            // Add the cell element to the list of cell elements.

            cellElements.push_back (*itr);
        } // Endif.

    } // Endfor.

    return (!cellElements.empty ());
} // Endproc.


bool    ACollisionGrid::IsCollision (const Gdiplus::Rect&   spriteScreenRect,
                                     CellElements&          cellElements) const
{
    cellElements.clear ();    // Initialise!

    // Check for a collision.

    for (CellElements::const_iterator itr = m_grid.begin ();
         itr != m_grid.end ();
         ++itr)
    {
        if (itr->IsOverlap (spriteScreenRect))
        {
            // Store the grid's cell element.

            cellElements.push_back (*itr);
        } // Endif.

    } // Endfor.

    return (!cellElements.empty ());
} // Endproc.


bool    ACollisionGrid::IsCollision (const Gdiplus::Rect&   spriteScreenRect,
                                     CellValue              cellValue,
                                     CellElements&          cellElements) const
{
    cellElements.clear ();    // Initialise!

    // Check for a collision.

    for (CellElements::const_iterator itr = m_grid.begin ();
         itr != m_grid.end ();
         ++itr)
    {
        if ((itr->m_cellValue == cellValue) && 
             itr->IsOverlap (spriteScreenRect))
        {
            // Store the grid's cell element.

            cellElements.push_back (*itr);
        } // Endif.

    } // Endfor.

    return (!cellElements.empty ());
} // Endproc.


FolioStatus ACollisionGrid::AddScreenExit (const ScreenExit& screenExit)
{
    // Is the screen exit in the list of screen exits?

    if (!IsScreenExit (screenExit))
    {
        // No. Add it.

        m_screenExits.push_back (screenExit);
    } // Endif.

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus ACollisionGrid::RemoveScreenExit (const ScreenExit& screenExit)
{
    // Is the screen exit in the list of screen exits?

    ScreenExitList::const_iterator  itr = 
        std::find_if (m_screenExits.begin (), m_screenExits.end (), 
                      [&screenExit](const ScreenExit& arg) 
                      {return (arg.m_screenRect.Equals (screenExit.m_screenRect));});

    if (itr != m_screenExits.end ())
    {
        // Remove it.

        m_screenExits.erase (itr);
    } // Endif.

    return (ERR_SUCCESS);
} // Endproc.


bool    ACollisionGrid::IsScreenExit (const ScreenExit& screenExit) const
{
    // Is the screen exit in the list of screen exits?

    return (std::find_if (m_screenExits.begin (), m_screenExits.end (), 
                          [&screenExit](const ScreenExit& arg) 
                          {return (arg.m_screenRect.Equals (screenExit.m_screenRect));}) != m_screenExits.end ());
} // Endproc.


FolioStatus ACollisionGrid::OpenScreenExit (ScreenExit::UserData userData)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the screen exit in the list of screen exits?

    ScreenExitList::iterator    itr = 
        std::find_if (m_screenExits.begin (), m_screenExits.end (), 
                      [&userData](const ScreenExit& arg) 
                      {return (arg.m_userData == userData);});

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


FolioStatus ACollisionGrid::CloseScreenExit (ScreenExit::UserData userData)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the screen exit in the list of screen exits?

    ScreenExitList::iterator    itr = 
        std::find_if (m_screenExits.begin (), m_screenExits.end (), 
                      [&userData](const ScreenExit& arg) 
                      {return (arg.m_userData == userData);});

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


bool    ACollisionGrid::IsScreenExit (ScreenExit::UserData userData) const
{
    // Is the screen exit in the list of screen exits?

    return (std::find_if (m_screenExits.begin (), m_screenExits.end (), 
                          [&userData](const ScreenExit& arg) 
                          {return (arg.m_userData == userData);}) != m_screenExits.end ());
} // Endproc.


bool    ACollisionGrid::IsExitedScreen (DIRECTION       direction,
                                        Gdiplus::Rect&  spriteScreenRect,
                                        bool&           isAtLockedScreenExit,
                                        bool&           isInScreenExit,
                                        ScreenExit&     screenExit) const
{
    isAtLockedScreenExit    = false; // Initialise!
    isInScreenExit          = false;

    bool    isExitedScreen = false;   // Initialise!

    // Outwith the floor bound?

    Int32   floorBound = 0; // Initialise!

    if (IsOutwithFloorBound (direction, spriteScreenRect, &(floorBound)))
    {
        // Yes. Exited.

        isExitedScreen = true;

        // Set the screen exit.

        switch (direction)
        {
        case UP:
            screenExit.m_orientation = ScreenExit::TOP;

            // Psuedo screen exit.

            screenExit.m_screenRect.X       = spriteScreenRect.X; 
            screenExit.m_screenRect.Y       = floorBound;
            screenExit.m_screenRect.Width   = spriteScreenRect.Width;
            screenExit.m_screenRect.Height  = spriteScreenRect.Height;
            break; 

        case DOWN:
            screenExit.m_orientation = ScreenExit::BOTTOM;

            // Psuedo screen exit.

            screenExit.m_screenRect.X       = spriteScreenRect.X; 
            screenExit.m_screenRect.Y       = floorBound;
            screenExit.m_screenRect.Width   = spriteScreenRect.Width;
            screenExit.m_screenRect.Height  = spriteScreenRect.Height;
            break; 

        case LEFT:
            screenExit.m_orientation = ScreenExit::LEFT;

            // Psuedo screen exit.

            screenExit.m_screenRect.X       = floorBound; 
            screenExit.m_screenRect.Y       = spriteScreenRect.X;
            screenExit.m_screenRect.Width   = spriteScreenRect.Width;
            screenExit.m_screenRect.Height  = spriteScreenRect.Height;
            break; 

        case RIGHT:
            screenExit.m_orientation = ScreenExit::RIGHT;

            // Psuedo screen exit.

            screenExit.m_screenRect.X       = floorBound; 
            screenExit.m_screenRect.Y       = spriteScreenRect.X;
            screenExit.m_screenRect.Width   = spriteScreenRect.Width;
            screenExit.m_screenRect.Height  = spriteScreenRect.Height;
            break; 

        default:
            break; 
        } // Endswitch.

        screenExit.m_state      = ScreenExit::OPEN;
        screenExit.m_userData   = 0;
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


bool    ACollisionGrid::IsExitedScreen (const Gdiplus::Rect&    spriteScreenRect,
                                        bool&                   isInScreenExit,
                                        ScreenExit&             screenExit) const
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


bool    ACollisionGrid::IsEnteringScreen (DIRECTION             direction,
                                          const Gdiplus::Rect&  spriteScreenRect,
                                          bool&                 isInScreenExit,
                                          ScreenExit&           screenExit) const
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


void    ACollisionGrid::CheckScreenExitBound (DIRECTION         direction, 
                                              Gdiplus::Rect&    spriteScreenRect,
                                              bool&             isEnteringScreen,
                                              bool&             isInScreenExit,
                                              ScreenExit&       screenExit) const
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
            case ScreenExit::LEFT:
            case ScreenExit::RIGHT:
                if (spriteScreenRect.Y < topScreenExitBound)
                {
                    // Yes. Bound by the screen exit's top bound.

                    spriteScreenRect.Y = topScreenExitBound;
                } // Endif.
                break;

            case ScreenExit::BOTTOM:
            case ScreenExit::FLOOR:
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
            case ScreenExit::LEFT:
            case ScreenExit::RIGHT:
                if ((spriteScreenRect.Y + spriteScreenRect.Height) >= bottomScreenExitBound)
                {
                    // Yes. Bound by the screen exit's bottom bound.

                    spriteScreenRect.Y = bottomScreenExitBound - spriteScreenRect.Height + 1;
                } // Endif.
                break;

            case ScreenExit::TOP:
            case ScreenExit::FLOOR:
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
            case ScreenExit::TOP:
            case ScreenExit::BOTTOM:
                if (spriteScreenRect.X < leftScreenExitBound)
                {
                    // Yes. Bound by the screen exit's left bound.

                    spriteScreenRect.X = leftScreenExitBound;
                } // Endif.
                break;

            case ScreenExit::RIGHT:
            case ScreenExit::FLOOR:
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
            case ScreenExit::TOP:
            case ScreenExit::BOTTOM:
                if ((spriteScreenRect.X + spriteScreenRect.Width) >= rightScreenExitBound)
                {
                    // Yes. Bound by the screen exit's right bound.

                    spriteScreenRect.X = rightScreenExitBound - spriteScreenRect.Width + 1;
                } // Endif.
                break;

            case ScreenExit::LEFT:
            case ScreenExit::FLOOR:
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


bool    ACollisionGrid::IsOutwithFloorBound (DIRECTION      direction, 
                                             Gdiplus::Rect& spriteScreenRect,
                                             Int32*         floorBound) const
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


void    ACollisionGrid::ToFloorBound (DIRECTION         direction, 
                                      Int32             floorBound,
                                      Gdiplus::Rect&    spriteScreenRect) const
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


bool    ACollisionGrid::IsWalls () const
{
    return (!m_walls.empty ());
} // Endproc.


bool    ACollisionGrid::IsWallCollision (DIRECTION      direction,
                                         Gdiplus::Rect& spriteScreenRect,
                                         bool           screenEntrance) const
{
    bool    isWallCollision = false;    // Initialise!

    if (!m_walls.empty ())
    {
        for (Walls::const_iterator itr = m_walls.begin (); 
             !isWallCollision && (itr != m_walls.end ()); 
             ++itr)
        {
            if (!((itr->X > (spriteScreenRect.X + spriteScreenRect.Width - 1))  ||
                  (spriteScreenRect.X > (itr->X + itr->Width - 1))              ||
                  (itr->Y > (spriteScreenRect.Y + spriteScreenRect.Height - 1)) ||
                  (spriteScreenRect.Y > (itr->Y + itr->Height - 1))))
            {
                isWallCollision = true;

                if (screenEntrance)
                {
                    switch (direction)
                    {
                    case UP:
                    case DOWN:
                        spriteScreenRect.X = (spriteScreenRect.X >= itr->X) 
                                              ? itr->X + itr->Width
                                              : itr->X - spriteScreenRect.Width; 
                        break;

                    case RIGHT:
                    case LEFT:
                        spriteScreenRect.Y = (spriteScreenRect.Y >= itr->Y) 
                                              ? itr->Y + itr->Height
                                              : itr->Y - spriteScreenRect.Height; 
                        break;

                    default:
                        break;
                    } // Endswitch.

                } // Endif.

                else
                {
                    switch (direction)
                    {
                    case UP:
                        spriteScreenRect.Y = itr->Y + itr->Height; 
                        break;

                    case DOWN:
                        spriteScreenRect.Y = itr->Y - spriteScreenRect.Height; 
                        break;

                    case RIGHT:
                        spriteScreenRect.X = itr->X - spriteScreenRect.Width; 
                        break;
 
                    case LEFT:
                        spriteScreenRect.X = itr->X + itr->Width; 
                        break;

                    default:
                        break;
                    } // Endswitch.

                } // Endelse.

            } // Endif.

        } // Endfor.
    
    } // Endif.

    return (isWallCollision);
} // Endproc.


void    ACollisionGrid::ToScreenRectBound (UInt32               spriteDirection, 
                                           const Gdiplus::Rect& screenRectBound,
                                           Gdiplus::Rect&       spriteScreenRect) const
{
    switch (spriteDirection)
    {
    case N:
        spriteScreenRect.Y = screenRectBound.Y + screenRectBound.Height; 
        break;

    case S:
        spriteScreenRect.Y = screenRectBound.Y - spriteScreenRect.Height; 
        break;

    case E:
        spriteScreenRect.X = screenRectBound.X - spriteScreenRect.Width; 
        break;
 
    case W:
        spriteScreenRect.X = screenRectBound.X + screenRectBound.Width; 
        break;
            
    case NE:
    case NW:
    case SE:
    case SW:
        {
            // Get the sprite's position.

            Int32   spriteXRight    = spriteScreenRect.X + spriteScreenRect.Width - 1;
            Int32   spriteYBottom   = spriteScreenRect.Y + spriteScreenRect.Height - 1;

            // Get the solid item's position.

            Int32   solidItemXRight     = screenRectBound.X + screenRectBound.Width - 1;
            Int32   solidItemYBottom    = screenRectBound.Y + screenRectBound.Height - 1;

            if ((spriteDirection == NE) ||
                (spriteDirection == NW))
            {
                if ((spriteScreenRect.Y < solidItemYBottom) &&
                    (spriteYBottom > solidItemYBottom))
                {
                    // Check floor bound.

                    Int32   floorBottomBound = GetFloorBottomBound ();

                    if ((solidItemYBottom + 1 + spriteScreenRect.Height) < floorBottomBound)
                    {
                        spriteScreenRect.Y = solidItemYBottom + 1;
                    } // Endif.

                    else
                    {
                        spriteScreenRect.Y = floorBottomBound - spriteScreenRect.Height + 1;
                    } // Endelse.

                } // Endif.
                 
            } // Endif.
                
            else
            if ((spriteScreenRect.Y < screenRectBound.Y) &&
                (spriteYBottom > screenRectBound.Y))
            {
                // Check floor bound.

                Int32   floorTopBound = GetFloorTopBound ();

                if ((screenRectBound.Y - spriteScreenRect.Height) > floorTopBound)
                {
                    spriteScreenRect.Y = screenRectBound.Y - spriteScreenRect.Height; 
                } // Endif.

                else
                {
                    spriteScreenRect.Y = floorTopBound; 
                } // Endelse.

            } // Endelseif.

            if ((spriteDirection == NE) ||
                (spriteDirection == SE))
            {
                if ((spriteScreenRect.X < screenRectBound.X)  &&
                    (spriteXRight > screenRectBound.X))
                {
                    // Check floor bound.

                    Int32   floorLeftBound = GetFloorLeftBound ();

                    if ((screenRectBound.X - spriteScreenRect.Width) > floorLeftBound)
                    {
                        spriteScreenRect.X = screenRectBound.X - spriteScreenRect.Width; 
                    } // Endif.

                    else
                    {
                        spriteScreenRect.X = floorLeftBound; 
                    } // Endelse.

                } // Endif.

            } // Endif.

            else
            if ((spriteScreenRect.X < solidItemXRight) &&
                (spriteXRight > solidItemXRight))
            {
                // Check floor bound.

                Int32   floorRightBound = GetFloorRightBound ();

                if ((solidItemXRight + 1 + spriteScreenRect.Width) < floorRightBound)
                {
                    spriteScreenRect.X = solidItemXRight + 1;
                } // Endif.

                else
                {
                    spriteScreenRect.X = floorRightBound - spriteScreenRect.Width + 1;
                } // Endelse.
                
            } // Endelseif.

        } // Endscope.
        break;

    default:
        break;
    } // Endswitch.

} // Endproc.


bool    ACollisionGrid::IsEmpty (CellValue cellValue)
{
    return (cellValue == CELL_VALUE_EMPTY);
} // Endproc.


bool    ACollisionGrid::IsItem (CellValue cellValue)
{
    return ((cellValue & CELL_VALUE_ITEM) == CELL_VALUE_ITEM);
} // Endproc.


bool    ACollisionGrid::IsSolidItem (CellValue cellValue)
{
    return ((cellValue & CELL_VALUE_SOLID_ITEM) == CELL_VALUE_SOLID_ITEM);
} // Endproc.


bool    ACollisionGrid::IsHealthItem (CellValue cellValue)
{
    return ((cellValue & CELL_VALUE_HEALTH_ITEM) == CELL_VALUE_HEALTH_ITEM);
} // Endproc.


bool    ACollisionGrid::IsHarmfulItem (CellValue cellValue)
{
    return ((cellValue & CELL_VALUE_HARMFUL_ITEM) == CELL_VALUE_HARMFUL_ITEM);
} // Endproc.


bool    ACollisionGrid::IsCollectableItem (CellValue cellValue)
{
    return ((cellValue & CELL_VALUE_COLLECTABLE_ITEM) == CELL_VALUE_COLLECTABLE_ITEM);
} // Endproc.


bool    ACollisionGrid::IsWall (CellValue cellValue)
{
    return ((cellValue & CELL_VALUE_WALL) == CELL_VALUE_WALL);
} // Endproc.


bool    ACollisionGrid::IsExit (CellValue cellValue)
{
    return ((cellValue & CELL_VALUE_EXIT) == CELL_VALUE_EXIT);
} // Endproc.


bool    ACollisionGrid::IsNastySprite (CellValue cellValue)
{
    return ((cellValue & CELL_VALUE_NASTY_SPRITE) == CELL_VALUE_NASTY_SPRITE);
} // Endproc.


bool    ACollisionGrid::IsBossSprite (CellValue cellValue)
{
    return ((cellValue & CELL_VALUE_BOSS_SPRITE) == CELL_VALUE_BOSS_SPRITE);
} // Endproc.


bool    ACollisionGrid::IsWeaponSprite (CellValue cellValue)
{
    return ((cellValue & CELL_VALUE_WEAPON_SPRITE) == CELL_VALUE_WEAPON_SPRITE);
} // Endproc.


void    ACollisionGrid::BuildWall (const CellElement& cellElement)
{
    bool    addedToWall = false;    // Initialse!

    // Get the cell element's screen rect;

    Gdiplus::Rect   screenRect(cellElement.m_screenRect);

    for (Walls::iterator itr = m_walls.begin ();
         !addedToWall && (itr != m_walls.end ());
         ++itr)
    {
        if ((itr->Y         == screenRect.Y) &&
            (itr->Height    == screenRect.Height))
        {
            if ((itr->X <= screenRect.X) &&
                ((itr->X + itr->Width) >= screenRect.X))
            {
                itr->Width += screenRect.Width;
                addedToWall = true;
            } // Endif.
        
        } // Endif.

        else
        if ((itr->X         == screenRect.X) &&
            (itr->Width     == screenRect.Width))
        {
            if ((itr->Y <= screenRect.Y) &&
                ((itr->Y + itr->Height) >= screenRect.Y))
            {
                itr->Height += screenRect.Height;
                addedToWall = true;
            } // Endif.
        
        } // Endelseif.

    } // Endif.

    if (!addedToWall)
    {
        // New wall.

        m_walls.push_back (screenRect);
    } // Endif.

} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
