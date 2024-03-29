// "Home-made" includes.
#include    "DrawingElement.h"

namespace Folio
{

namespace Core
{

namespace Game
{

// Drawing element identifiers.
const   DrawingElement::DrawingElementId::value_type*   DrawingElement::DRAWING_ELEMENT_ROOM                        = TXT("Room");                  // Part of a screen's reported drawing elements.
const   DrawingElement::DrawingElementId::value_type*   DrawingElement::DRAWING_ELEMENT_BACKGROUND_ITEM             = TXT("Background Item");       // Part of a screen's reported drawing elements.
const   DrawingElement::DrawingElementId::value_type*   DrawingElement::DRAWING_ELEMENT_INFORMATION_PANEL_ITEM      = TXT("Informaton Panel Item"); // Part of a screen's reported drawing elements.
const   DrawingElement::DrawingElementId::value_type*   DrawingElement::DRAWING_ELEMENT_STATIC_SPRITE               = TXT("Static Sprite");
const   DrawingElement::DrawingElementId::value_type*   DrawingElement::DRAWING_ELEMENT_OBJECT_SPRITE               = TXT("Object Sprite");
const   DrawingElement::DrawingElementId::value_type*   DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE                = TXT("Nasty Sprite");
const   DrawingElement::DrawingElementId::value_type*   DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE                 = TXT("Boss Sprite");
const   DrawingElement::DrawingElementId::value_type*   DrawingElement::DRAWING_ELEMENT_WEAPON_SPRITE               = TXT("Weapon Sprite");
const   DrawingElement::DrawingElementId::value_type*   DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE          = TXT("Main Player Sprite");
const   DrawingElement::DrawingElementId::value_type*   DrawingElement::DRAWING_ELEMENT_LOADING_SCREEN_ITEM         = TXT("Loading Screen Item");
const   DrawingElement::DrawingElementId::value_type*   DrawingElement::DRAWING_ELEMENT_SELECTION_SCREEN_ITEM       = TXT("Selection Screen Item");
const   DrawingElement::DrawingElementId::value_type*   DrawingElement::DRAWING_ELEMENT_GAME_OVER_SCREEN_ITEM       = TXT("Game Over Screen Item");
const   DrawingElement::DrawingElementId::value_type*   DrawingElement::DRAWING_ELEMENT_GAME_COMPLETED_SCREEN_ITEM  = TXT("Game Completed Screen Item");

DrawingElement::DrawingElement (const DrawingElementId&                             drawingElementId,
                                Int32                                               screenXLeft,
                                Int32                                               screenYTop,
                                const Folio::Core::Graphic::GdiGraphicElementPtr&   gdiGraphicElement,
                                UserData                                            userData,
                                UInt32                                              collisionGridCellValue,
                                const Gdiplus::Rect*                                collisionGridDeltaRect)
:   m_drawingElementId(drawingElementId),
    m_screenRect(screenXLeft, screenYTop, gdiGraphicElement->GetScreenWidth (), gdiGraphicElement->GetScreenHeight ()),
    m_userData(userData),
    m_collisionGridCellValue(collisionGridCellValue),
    m_collisionGridDeltaRect(collisionGridDeltaRect ? *collisionGridDeltaRect : Gdiplus::Rect()),
    m_gdiGraphicElement(gdiGraphicElement)
{
} // Endproc.


DrawingElement::~DrawingElement ()
{
} // Endproc.


FolioStatus DrawingElement::SetScreenTopLeft (Int32 screenXLeft,    
                                              Int32 screenYTop)
{
    FolioStatus status = ERR_SUCCESS;

    m_screenRect.X = screenXLeft;
    m_screenRect.Y = screenYTop;

    return (status);
} // Endproc.


FolioStatus DrawingElement::Draw (Gdiplus::Graphics&                                    graphics,
                                  Folio::Core::Graphic::AGdiGraphicElement::RectList*   rects)
{
    return (m_gdiGraphicElement->Draw (m_screenRect.X, m_screenRect.Y, graphics, rects));
} // Endproc.


FolioStatus DrawingElement::Draw (Int32                                                 screenXLeft,    
                                  Int32                                                 screenYTop,
                                  Gdiplus::Graphics&                                    graphics,
                                  Folio::Core::Graphic::AGdiGraphicElement::RectList*   rects)
{
    // Set the screen position.

    FolioStatus status = SetScreenTopLeft (screenXLeft,  screenYTop);

    if (status == ERR_SUCCESS)
    {
        // Draw it.

        status = Draw (graphics, rects);
    } // Endif.

    return (status);
} // Endproc.


DrawingElement::DrawingElementId    DrawingElement::GetDrawingElementId () const
{
    return (m_drawingElementId);
} // Endproc.


Folio::Core::Graphic::GdiGraphicElementPtr  DrawingElement::GetGdiGraphicElement () const
{
    return (m_gdiGraphicElement);
} // Endproc.


Gdiplus::Rect   DrawingElement::GetScreenRect () const
{
    return (m_screenRect);
} // Endproc.


Int32   DrawingElement::GetScreenXLeft () const
{
    return (m_screenRect.X);
} // Endproc.


Int32   DrawingElement::GetScreenYTop () const
{
    return (m_screenRect.Y);
} // Endproc.


Int32   DrawingElement::GetScreenXRight () const
{
    return (m_screenRect.X + m_screenRect.Width - 1);
} // Endproc.


Int32   DrawingElement::GetScreenYBottom () const
{
    return (m_screenRect.Y + m_screenRect.Height - 1);
} // Endproc.


Int32   DrawingElement::GetScreenWidth () const
{
    return (m_screenRect.Width);
} // Endproc.


Int32   DrawingElement::GetScreenHeight () const
{
    return (m_screenRect.Height);
} // Endproc.


void    DrawingElement::SetUserData (const UserData& userData)
{
    m_userData = userData;
} // Endproc.


DrawingElement::UserData    DrawingElement::GetUserData () const
{
    return (m_userData);
} // Endproc.


void    DrawingElement::SetCollisionGridDeltaRect (const Gdiplus::Rect& collisionGridDeltaRect)
{
    m_collisionGridDeltaRect = collisionGridDeltaRect;
} // Endproc.


Gdiplus::Rect   DrawingElement::GetCollisionGridDeltaRect () const
{
    return (m_collisionGridDeltaRect);
} // Endproc.


Gdiplus::Rect   DrawingElement::GetCollisionGridRect () const
{
    return (m_collisionGridDeltaRect.IsEmptyArea () 
            ? GetScreenRect () 
            : Gdiplus::Rect(GetCollisionGridXLeft (), 
                            GetCollisionGridYTop (), 
                            GetCollisionGridWidth (), 
                            GetCollisionGridHeight ()));
} // Endproc.


Int32   DrawingElement::GetCollisionGridXLeft () const
{
    return (m_screenRect.X + m_collisionGridDeltaRect.X);
} // Endproc.


Int32   DrawingElement::GetCollisionGridYTop () const
{
    return (m_screenRect.Y + m_collisionGridDeltaRect.Y);
} // Endproc.


Int32   DrawingElement::GetCollisionGridXRight () const
{
    return (GetCollisionGridXLeft () + GetCollisionGridWidth () - 1);
} // Endproc.


Int32   DrawingElement::GetCollisionGridYBottom () const
{
    return (GetCollisionGridYTop () + GetCollisionGridHeight () - 1);
} // Endproc.


Int32   DrawingElement::GetCollisionGridWidth () const
{
    return (m_screenRect.Width - 2 * m_collisionGridDeltaRect.Width);
} // Endproc.


Int32   DrawingElement::GetCollisionGridHeight () const
{
    return (m_screenRect.Height - 2 * m_collisionGridDeltaRect.Height);
} // Endproc.


void    DrawingElement::SetCollisionGridCellValue (UInt32 collisionGridCellValue)
{
    m_collisionGridCellValue = collisionGridCellValue;
} // Endproc.


UInt32  DrawingElement::GetCollisionGridCellValue () const
{
    return (m_collisionGridCellValue);
} // Endproc.


FolioString DrawingElement::Describe () const
{
    return (m_drawingElementId);
} // Endproc.


DrawingElement::DrawingElementId    DrawingElement::MakeDrawingElementId (UInt32 drawingElementId)
{
    FolioOStringStream  str;

    str << std::dec << drawingElementId;

    return (str.str ());
} // Endproc.


bool   DrawingElement::Sort (const DrawingElement&  lhs, 
                             const DrawingElement&  rhs)
{
    bool    matchDrawingElementId = false; // Initialise!

    bool    returnValue = SortDrawingElementId (DRAWING_ELEMENT_ROOM, lhs, rhs, matchDrawingElementId);

    if (!matchDrawingElementId)
    {
        returnValue = SortDrawingElementId (DRAWING_ELEMENT_BACKGROUND_ITEM, lhs, rhs, matchDrawingElementId);

        if (!matchDrawingElementId)
        {
            returnValue = SortDrawingElementId (DRAWING_ELEMENT_INFORMATION_PANEL_ITEM, lhs, rhs, matchDrawingElementId);

            if (!matchDrawingElementId)
            {
                returnValue = SortDrawingElement (lhs, rhs);
            } // Endif.

        } // Endif.

    } // Endif.

    return (returnValue);
} // Endproc.


bool   DrawingElement::SortDrawingElementId (const DrawingElementId&    drawingElementId,
                                             const DrawingElement&      lhs, 
                                             const DrawingElement&      rhs,
                                             bool&                      matchDrawingElementId)
{
    matchDrawingElementId = false; // Initialise!

    bool    returnValue = false;

    if (lhs.m_drawingElementId == drawingElementId)
    {
        matchDrawingElementId = true;

        if (rhs.m_drawingElementId == drawingElementId)
        {
            returnValue = SortDrawingElement (lhs, rhs);
        } // Endif.

        else
        {
            returnValue = true;
        } // Endelse.

    } // Endif.

    else
    if (rhs.m_drawingElementId == drawingElementId)
    {
        matchDrawingElementId = true;

        if (lhs.m_drawingElementId == drawingElementId)
        {
            returnValue = SortDrawingElement (lhs, rhs);
        } // Endif.

        else
        {
            returnValue = false;
        } // Endelse.

    } // Endelseif.

    return (returnValue);
} // Endproc.


bool   DrawingElement::SortDrawingElement (const DrawingElement&    lhs, 
                                           const DrawingElement&    rhs)
{
    bool    returnValue = false;

    if (lhs.m_screenRect.Y == rhs.m_screenRect.Y)
    {
        if (lhs.m_screenRect.X == rhs.m_screenRect.X)
        {
            returnValue = lhs.m_gdiGraphicElement < rhs.m_gdiGraphicElement;
        } // Endif.

        else
        {
            returnValue = lhs.m_screenRect.X < rhs.m_screenRect.X;
        } // Endelse.

    } // Endif.

    else
    {
        returnValue = lhs.m_screenRect.Y < rhs.m_screenRect.Y;
    } // Endelse.

    return (returnValue);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
