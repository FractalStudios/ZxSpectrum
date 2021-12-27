#pragma once

// STL includes.
#include    <memory>
#include    <vector>

// "Home-made" includes.
#include    <Graphic.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Game
{

class DrawingElement
{
public:
    // Drawing element identifier.
    typedef FolioString DrawingElementId;

    // Drawing element identifiers.
    static  const   DrawingElementId::value_type*   DRAWING_ELEMENT_ROOM;                      // Part of a screen's reported drawing elements.
    static  const   DrawingElementId::value_type*   DRAWING_ELEMENT_BACKGROUND_ITEM;           // Part of a screen's reported drawing elements.
    static  const   DrawingElementId::value_type*   DRAWING_ELEMENT_INFORMATION_PANEL_ITEM;    // Part of a screen's reported drawing elements.
    static  const   DrawingElementId::value_type*   DRAWING_ELEMENT_STATIC_SPRITE;
    static  const   DrawingElementId::value_type*   DRAWING_ELEMENT_MAIN_PLAYER_SPRITE;
    static  const   DrawingElementId::value_type*   DRAWING_ELEMENT_NASTY_SPRITE;
    static  const   DrawingElementId::value_type*   DRAWING_ELEMENT_BOSS_SPRITE;
    static  const   DrawingElementId::value_type*   DRAWING_ELEMENT_WEAPON_SPRITE;
    static  const   DrawingElementId::value_type*   DRAWING_ELEMENT_LOADING_SCREEN_ITEM;
    static  const   DrawingElementId::value_type*   DRAWING_ELEMENT_SELECTION_SCREEN_ITEM;
    static  const   DrawingElementId::value_type*   DRAWING_ELEMENT_GAME_OVER_SCREEN_ITEM;

    // User data.
    typedef void*   UserData;

    DrawingElement (const DrawingElementId&                             drawingElementId,
                    Int32                                               screenXLeft,
                    Int32                                               screenYTop,
                    const Folio::Core::Graphic::GdiGraphicElementPtr&   gdiGraphicElement,
                    UserData                                            userData = 0,
                    UInt32                                              collisionGridCellValue = 0);
    ~DrawingElement ();

    FolioStatus SetScreenTopLeft (Int32 screenXLeft,    
                                  Int32 screenYTop);
    FolioStatus Draw (Gdiplus::Graphics&                                    graphics,
                      Folio::Core::Graphic::AGdiGraphicElement::RectList*   rects = 0);
    FolioStatus Draw (Int32                                                 screenXLeft,    
                      Int32                                                 screenYTop,
                      Gdiplus::Graphics&                                    graphics,
                      Folio::Core::Graphic::AGdiGraphicElement::RectList*   rects = 0);

    DrawingElementId                            GetDrawingElementId () const;
    Folio::Core::Graphic::GdiGraphicElementPtr  GetGdiGraphicElement () const;

    Gdiplus::Rect   GetScreenRect () const;
    Int32           GetScreenXLeft () const;
    Int32           GetScreenYTop () const;
    Int32           GetScreenXRight () const;
    Int32           GetScreenYBottom () const;
    Int32           GetScreenWidth () const;
    Int32           GetScreenHeight () const;

    void        SetUserData (const UserData& userData);
    UserData    GetUserData () const;

    void    SetCollisionGridCellValue (UInt32 collisionGridCellValue);
    UInt32  GetCollisionGridCellValue () const;

    bool    IsOverlap (const Gdiplus::Rect& screenRect) const;

    FolioString Describe () const;

    static  DrawingElementId    MakeDrawingElementId (UInt32 drawingElementId);

    static  bool    Sort (const DrawingElement& lhs, 
                          const DrawingElement& rhs);

private:
    DrawingElementId    m_drawingElementId;         // The identifier of the drawing element.
    Gdiplus::Rect       m_screenRect;               // The screen rect of the drawing element.
    UserData            m_userData;                 // User defined data applicable to the drawing element.
    UInt32              m_collisionGridCellValue;   // The collision grid cell value of the drawing element.

    Folio::Core::Graphic::GdiGraphicElementPtr  m_gdiGraphicElement;    // The GDI graphic element.

    static  bool   SortDrawingElementId (const DrawingElementId&    drawingElementId,
                                         const DrawingElement&      lhs, 
                                         const DrawingElement&      rhs,
                                         bool&                      matchDrawingElementId);
    static  bool   SortDrawingElement (const DrawingElement&    lhs, 
                                       const DrawingElement&    rhs);
}; // Endclass.

// Drawing element pointer.
typedef std::shared_ptr<DrawingElement> DrawingElementPtr;

// Drawing elements list.
typedef std::vector<DrawingElement> DrawingElementsList;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
