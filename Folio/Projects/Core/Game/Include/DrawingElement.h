#pragma once

// STL includes.
#include    <set>
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
    typedef UInt32  Id;

    static  const   Id  DRAWING_ELEMENT_ID_UNDEFINED = -1;  // Undefined drawing element identifier.

    // User data.
    typedef void*   UserData;

    DrawingElement (Id                                                  id,
                    const Folio::Core::Graphic::GdiGraphicElementPtr&   gdiGraphicElement,
                    UserData                                            userData = 0,
                    UInt32                                              collisionGridCellValue = 0);
    ~DrawingElement ();

    FolioStatus SetScreenTopLeft (Int32 screenXLeft,    
                                  Int32 screenYTop);
    FolioStatus Draw (Gdiplus::Graphics&                                    graphics,
                      Folio::Core::Graphic::AGdiGraphicElement::RectList*   rects = 0);

    Id                                          GetDrawingElementId () const;
    Folio::Core::Graphic::GdiGraphicElementPtr  GetGdiGraphicElement () const;

    void    SetCollisionGridCellValue (UInt32 collisionGridCellValue);
    UInt32  GetCollisionGridCellValue () const;

    void        SetUserData (const UserData& userData);
    UserData    GetUserData () const;

    Gdiplus::Rect   GetScreenRect () const;
    Int32           GetScreenXLeft () const;
    Int32           GetScreenYTop () const;
    Int32           GetScreenXRight () const;
    Int32           GetScreenYBottom () const;
    Int32           GetScreenWidth () const;
    Int32           GetScreenHeight () const;

    bool    IsOverlap (const Gdiplus::Rect& screenRect) const;

    bool    operator < (const DrawingElement &rhs) const;

private:
    Id                          m_id;                       // The identifier of the drawing element.
    UserData                    m_userData;                 // User defined data applicable to the drawing element.
    UInt32    m_collisionGridCellValue;   // The collision grid cell value of the drawing element.

    Folio::Core::Graphic::GdiGraphicElementPtr  m_gdiGraphicElement;    // The GDI graphic element.
}; // Endclass.

// Drawing elements list.
typedef std::vector<DrawingElement> DrawingElementsList;

// Drawing elements multi-set.
typedef std::multiset<DrawingElement>   DrawingElementsSet;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
