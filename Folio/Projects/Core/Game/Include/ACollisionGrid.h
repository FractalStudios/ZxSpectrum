#pragma once

// "Home-made" includes.
#include    <Graphic.h>
#include    "DrawingElement.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Game
{

class ACollisionGrid
{
public:
    virtual ~ACollisionGrid ();

    FolioStatus Create (const Gdiplus::Rect& floorRect);
    FolioStatus Create (const Gdiplus::Rect&                            floorRect,
                        const Folio::Core::Game::DrawingElementsList&   drawingElementsList);
    FolioStatus Clear ();

    Gdiplus::Rect   GetFloorRect () const;
    Int32           GetFloorLeftBound () const;
    Int32           GetFloorRightBound () const;
    Int32           GetFloorTopBound () const;
    Int32           GetFloorBottomBound () const;
    Int32           GetFloorWidth () const;
    Int32           GetFloorHeight () const;

    // Cell value.
    typedef UInt32  CellValue;

    // Standard collision grid cell values.
    static  const   CellValue   CELL_VALUE_EMPTY            = 0x00000000;
    static  const   CellValue   CELL_VALUE_ITEM             = 0x00000100;
    static  const   CellValue   CELL_VALUE_SOLID_ITEM       = CELL_VALUE_ITEM | 0x00000001;
    static  const   CellValue   CELL_VALUE_HEALTH_ITEM      = CELL_VALUE_ITEM | 0x00000002;
    static  const   CellValue   CELL_VALUE_HARMFUL_ITEM     = CELL_VALUE_ITEM | 0x00000004;
    static  const   CellValue   CELL_VALUE_COLLECTABLE_ITEM = CELL_VALUE_ITEM | 0x00000008;
    static  const   CellValue   CELL_VALUE_WALL             = 0x00001000;
    static  const   CellValue   CELL_VALUE_EXIT             = 0x00002000;
    static  const   CellValue   CELL_VALUE_NASTY_SPRITE     = 0x00010000;
    static  const   CellValue   CELL_VALUE_BOSS_SPRITE      = 0x00020000;
    static  const   CellValue   CELL_VALUE_WEAPON_SPRITE    = 0x00040000;

    // Cell element.
    struct CellElement
    {
        // Cell element identifier.
        typedef DrawingElement::DrawingElementId    CellElementId;

        // User data.
        typedef DrawingElement::UserData    UserData;

        CellElement (const CellElementId&   cellElementId,
                     const Gdiplus::Rect&   screenRect,
                     CellValue              cellValue = CELL_VALUE_EMPTY,
                     UserData               userData = 0)
        :   m_cellElementId(cellElementId),                   
            m_screenRect(screenRect),           
            m_cellValue(cellValue),
            m_userData(userData)             
        {} // Endproc.

        CellElement (const DrawingElement& drawingElement)
        :   m_cellElementId(drawingElement.GetDrawingElementId ()),                   
            m_screenRect(drawingElement.GetScreenRect ()),           
            m_cellValue(drawingElement.GetCollisionGridCellValue ()),
            m_userData(drawingElement.GetUserData ())             
        {} // Endproc.

        bool    IsOverlap (const Gdiplus::Rect& screenRect) const
        {
            return (!((m_screenRect.X > (  screenRect.X +   screenRect.Width  - 1)) ||
                        (screenRect.X > (m_screenRect.X + m_screenRect.Width  - 1)) ||
                      (m_screenRect.Y > (  screenRect.Y +   screenRect.Height - 1)) ||
                        (screenRect.Y > (m_screenRect.Y + m_screenRect.Height - 1))));
        } // Endproc.

        bool    operator == (const CellElement& rhs) const
        {
            return ((m_cellElementId == rhs.m_cellElementId) && (m_userData == rhs.m_userData));
        } // Endproc.

        CellElementId       m_cellElementId;    // The identifier of the cell element.
        Gdiplus::Rect       m_screenRect;       // The screen rect of the cell element.
        CellValue           m_cellValue;        // The collision grid cell value of the cell element.
        UserData            m_userData;         // User defined data applicable to the cell element.
    }; // Endstruct.

    // Cell elements.
    typedef std::vector<CellElement> CellElements;

    FolioStatus AddCellElement (const CellElement& cellElement);
    FolioStatus RemoveCellElement (const CellElement& cellElement);
    FolioStatus UpdateCellElement (const CellElement& cellElement);

    bool    FindCellElement (CellElement::UserData  userData,
                             CellElement&           cellElement) const;
    bool    FindCellElements (const CellElement::CellElementId& cellElementId,
                              CellElements&                     cellElements) const;

    bool    IsCollision (const Gdiplus::Rect&   spriteScreenRect,
                         CellElements&          cellElements) const;
    bool    IsCollision (const Gdiplus::Rect&   spriteScreenRect,
                         CellValue              cellValue,
                         CellElements&          cellElements) const;

    // Screen exit.
    struct ScreenExit
    {
        // User data.
        typedef void*   UserData;

        // Orientation enumeration.
        enum ORIENTATION
        {
            NONE = 0,
            TOP,
            BOTTOM,
            LEFT,
            RIGHT,
            FLOOR,
        }; // Endenum.

        // State.
        enum STATE
        {
            OPEN = 0,
            CLOSED,
            LOCKED,
        }; // Endenum.

        ScreenExit ()
        :   m_state(OPEN),
            m_userData(0)
        {} // Endproc.

        ScreenExit (ORIENTATION             orientation,
                    const Gdiplus::Rect&    screenRect,
                    STATE                   state = OPEN,
                    const UserData&         userData = 0)
        :   m_orientation(orientation),
            m_screenRect(screenRect),
            m_state(state),
            m_userData(userData)
        {} // Endproc.

        ~ScreenExit ()
        {} // Endproc.

        Int32   GetLeftBound () const
        {
            return (m_screenRect.X);
        } // Endproc.
        
        Int32   GetRightBound () const
        {
            return (m_screenRect.X + m_screenRect.Width - 1);
        } // Endproc.
        
        Int32   GetTopBound () const
        {
            return (m_screenRect.Y);
        } // Endproc.
        
        Int32   GetBottomBound () const
        {
            return (m_screenRect.Y + m_screenRect.Height - 1);
        } // Endproc.

        bool    IsOpen () const
        {
            return (m_state == OPEN);
        } // Endproc.

        bool    IsClosed () const
        {
            return (m_state == CLOSED);
        } // Endproc.
        
        bool    IsLocked () const
        {
            return (m_state == LOCKED);
        } // Endproc.

        ORIENTATION     m_orientation;  // The orientation of the screen exit.
        Gdiplus::Rect   m_screenRect;   // The screen rect of the screen exit.
        STATE           m_state;        // The state of the screen exit.
        UserData        m_userData;     // User defined data applicable to the screen exit.
    }; // Endstruct.

    // Screen exit list.
    typedef std::vector<ScreenExit> ScreenExitList;

    // Screen entrance.
    typedef ScreenExit  ScreenEntrance;

    // Screen entrance list.
    typedef std::vector<ScreenEntrance> ScreenEntranceList;

    FolioStatus AddScreenExit (const ScreenExit& screenExit);
    FolioStatus RemoveScreenExit (const ScreenExit& screenExit);
    bool    IsScreenExit (const ScreenExit& screenExit) const;
    
    FolioStatus OpenScreenExit (ScreenExit::UserData userData);
    FolioStatus CloseScreenExit (ScreenExit::UserData userData);
    bool    IsScreenExit (ScreenExit::UserData userData) const;

    // Direction enumeration.
    enum DIRECTION
    {
        UP = 0,
        DOWN,
        LEFT,
        RIGHT,
    }; // Endenum.

    virtual bool    IsExitedScreen (DIRECTION       direction,
                                    Gdiplus::Rect&  spriteScreenRect,
                                    bool&           isAtLockedScreenExit,
                                    bool&           isInScreenExit,
                                    ScreenExit&     screenExit) const;
    bool    IsExitedScreen (const Gdiplus::Rect&    spriteScreenRect,
                            bool&                   isInScreenExit,
                            ScreenExit&             screenExit) const;
    bool    IsEnteringScreen (DIRECTION             direction,
                              const Gdiplus::Rect&  spriteScreenRect,
                              bool&                 isInScreenExit,
                              ScreenExit&           screenExit) const;
    
    void    CheckScreenExitBound (DIRECTION         direction, 
                                  Gdiplus::Rect&    spriteScreenRect,
                                  bool&             isEnteringScreen,
                                  bool&             isInScreenExit,
                                  ScreenExit&       screenExit) const;

    bool    IsOutwithFloorBound (DIRECTION      direction, 
                                 Gdiplus::Rect& spriteScreenRect,
                                 Int32*         floorBound = 0) const;

    void    ToFloorBound (DIRECTION         direction, 
                          Int32             floorBound,
                          Gdiplus::Rect&    spriteScreenRect) const;

    bool    IsWalls () const;
    bool    IsWallCollision (DIRECTION      direction, 
                             Gdiplus::Rect& spriteScreenRect,
                             bool           screenEntrance = false) const;

    void    ToScreenRectBound (UInt32               spriteDirection, 
                               const Gdiplus::Rect& screenRectBound,
                               Gdiplus::Rect&       spriteScreenRect) const;

    static  bool    IsEmpty (CellValue cellValue);
    static  bool    IsItem (CellValue cellValue);
    static  bool    IsSolidItem (CellValue cellValue);
    static  bool    IsHealthItem (CellValue cellValue);
    static  bool    IsHarmfulItem (CellValue cellValue);
    static  bool    IsCollectableItem (CellValue cellValue);
    static  bool    IsWall (CellValue cellValue);
    static  bool    IsExit (CellValue cellValue);
    static  bool    IsNastySprite (CellValue cellValue);
    static  bool    IsBossSprite (CellValue cellValue);
    static  bool    IsWeaponSprite (CellValue cellValue);

protected:
    ScreenExitList  m_screenExits;  // The screen exits.

    ACollisionGrid ();

private:
    Gdiplus::Rect   m_floorRect;    // The floor rect of the screen.

    // Grid.
    typedef CellElements    Grid;

    Grid    m_grid; // The grid.

    // Walls.
    typedef std::vector<Gdiplus::Rect>  Walls;

    Walls   m_walls;    // The walls.

    void    BuildWall (const CellElement& cellElement);
}; // Endclass.


// Wall bound.
class WallBound
{
public:
    WallBound ()
    :   m_direction(0)
    {} // Endproc.

    WallBound (UInt32               direction,
               const Gdiplus::Rect& screenRect)
    :   m_direction(direction),
        m_screenRect(screenRect)
    {} // Endproc.

    UInt32          m_direction;    // The direction of a sprite at the wall bound
    Gdiplus::Rect   m_screenRect;   // The screen rect of a sprite at the wall bound.
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
