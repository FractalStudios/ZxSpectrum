#pragma once

// "Home-made" includes.
#include    <Graphic.h>
#include    <DrawingElement.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Game
{

class CollisionGrid
{
public:
    CollisionGrid ();
    ~CollisionGrid ();

    FolioStatus Create (const Gdiplus::Rect &floorRect);
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
    static  const   CellValue   CELL_VALUE_EXIT             = 0x00001000;
    static  const   CellValue   CELL_VALUE_NASTY_SPRITE     = 0x00002000;
    static  const   CellValue   CELL_VALUE_BOSS_SPRITE      = 0x00004000;
    static  const   CellValue   CELL_VALUE_WEAPON_SPRITE    = 0x00008000;

    // Cell elements.
    typedef std::vector<DrawingElement> CellElements;

    FolioStatus AddDrawingElement (const DrawingElement& drawingElement);
    FolioStatus RemoveDrawingElement (const DrawingElement& drawingElement);
    FolioStatus UpdateDrawingElement (const DrawingElement& drawingElement);
    bool    FindDrawingElement (DrawingElement::UserData    userData,
                                DrawingElement&             drawingElement) const;
    bool    FindDrawingElements (DrawingElement::Id     drawingElementId,
                                 DrawingElementsList&   drawingElementsList) const;
                                                                                  
    bool    IsCollision (const Gdiplus::Rect&   spriteScreenRect,
                         CellElements&          cellCollisionElements) const;
    bool    IsCollision (const Gdiplus::Rect&   spriteScreenRect,
                         CellValue              cellValue,
                         CellElements&          cellCollisionElements) const;

    // Direction.
    enum DIRECTION
    {
        UP = 0,
        DOWN,
        LEFT,
        RIGHT,
    };

    // Screen exit.
    struct ScreenExit
    {
        // User data.
        typedef void*   UserData;

        // Orientation.
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
                    STATE                   state,
                    const UserData&         userData)
        :   m_orientation(orientation),
            m_screenRect(screenRect),
            m_state(state),
            m_userData(userData)
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

    bool    IsExitedScreen (DIRECTION               direction,
                            Gdiplus::Rect&          spriteScreenRect,
                            bool&                   isAtLockedScreenExit,
                            bool&                   isInScreenExit,
                            ScreenExit&             screenExit) const;
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

    static  bool    IsEmpty (CellValue cellValue);
    static  bool    IsItem (CellValue cellValue);
    static  bool    IsSolidItem (CellValue cellValue);
    static  bool    IsHealthItem (CellValue cellValue);
    static  bool    IsHarmfulItem (CellValue cellValue);
    static  bool    IsCollectableItem (CellValue cellValue);
    static  bool    IsExit (CellValue cellValue);
    static  bool    IsNastySprite (CellValue cellValue);
    static  bool    IsBossSprite (CellValue cellValue);
    static  bool    IsWeaponSprite (CellValue cellValue);

private:
    Gdiplus::Rect   m_floorRect;    // The floor rect of the screen.

    // Grid.
    typedef CellElements    Grid;

    Grid    m_grid; // The grid.

    ScreenExitList  m_screenExits;  // Screen exits.
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
