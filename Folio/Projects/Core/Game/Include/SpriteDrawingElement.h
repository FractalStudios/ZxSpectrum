#pragma once

// STL includes.
#include    <memory>

// "Home-made" includes.
#include    <Graphic.h>
#include    "ASprite.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Game
{

template <typename T>
class SpriteDrawingElement
{
public:
    SpriteDrawingElement ()
    :   m_createdTickCount(0)
    {} // Endproc.

    SpriteDrawingElement (const DrawingElement::DrawingElementId&   drawingElementId,
                          const T&                                  sprite)
    :   m_sprite(sprite),
        m_drawingElement(new DrawingElement(drawingElementId, 
                                            sprite->GetScreenXLeft (), 
                                            sprite->GetScreenYTop (), 
                                            sprite, 
                                            sprite.get (), 
                                            sprite->GetCollisionGridCellValue (),
                                            &(sprite->GetCollisionGridDeltaRect ()))),
        m_createdTickCount(Folio::Core::Util::DateTime::GetCurrentTickCount ())
    {} // Endproc.

    ~SpriteDrawingElement ()
    {} // Endproc.

    FolioStatus Create (const DrawingElement::DrawingElementId& drawingElementId,
                        const T&                                sprite)
    {
        FolioStatus status = ERR_SUCCESS;

        // Have we created a sprite drawing element already?

        if (IsCreated ())
        {
            // Yes.

            status = ERR_INVALID_SEQUENCE;
        } // Endif.

        else
        {
            // No. Create the sprite drawing element.

            m_sprite = sprite;
            
            m_drawingElement.reset (new DrawingElement(drawingElementId, 
                                                       sprite->GetScreenXLeft (), 
                                                       sprite->GetScreenYTop (), 
                                                       sprite, 
                                                       sprite.get (), 
                                                       sprite->GetCollisionGridCellValue (),
                                                       &(sprite->GetCollisionGridDeltaRect ())));

            m_createdTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount ();
        } // Endelse.

        return (status);
    } // Endproc.

    void    Destroy ()
    {
        m_sprite.reset ();
        m_drawingElement.reset ();

        m_createdTickCount = 0;
    } // Endproc.


    bool    IsCreated () const
    {
        return (m_sprite && m_drawingElement);
    } // Endproc.


    void    SetSprite (const T& sprite) 
    {
        m_sprite = sprite;
    } // Endproc.


    T   GetSprite () const
    {
        return (m_sprite);
    } // Endproc.


    bool    IsSprite () const
    {
        return (m_sprite != 0);
    } // Endproc.


    FolioStatus CreateDrawingElement (const DrawingElement::DrawingElementId&   drawingElementId,
                                      ACollisionGrid::CellValue                 collisionGridCellValue = ACollisionGrid::CELL_VALUE_EMPTY,
                                      const Gdiplus::Rect*                      collisionGridDeltaRect = 0)
    {
        FolioStatus status = ERR_SUCCESS;

        // Have we created a sprite drawing element already?

        if (IsCreated () || !m_sprite)
        {
            // Yes.

            status = ERR_INVALID_SEQUENCE;
        } // Endif.

        else
        {
            // No. Create the sprite drawing element.

            m_drawingElement.reset (new DrawingElement(drawingElementId, 
                                                       m_sprite->GetScreenXLeft (), 
                                                       m_sprite->GetScreenYTop (), 
                                                       m_sprite, 
                                                       m_sprite.get (), 
                                                       collisionGridCellValue, 
                                                       collisionGridDeltaRect));
            
            m_createdTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount ();
        } // Endelse.

        return (status);
    } // Endproc.


    void    DestroyDrawingElement ()
    {
        m_drawingElement.reset ();
    } // Endproc.


    DrawingElementPtr   GetDrawingElement () const
    {
        return (DrawingElementPtr);
    } // Endproc.


    bool    IsDrawingElement () const
    {
        return (m_drawingElement != 0);
    } // Endproc.


    FolioStatus SetScreenTopLeft (Int32 screenXLeft,
                                  Int32 screenY,
                                  bool  screenYTopSpecified = true)
    {
        FolioStatus status = ERR_SUCCESS;

        // Have we created a sprite drawing element?

        if (IsCreated ())
        {
            // Yes.

            status = m_sprite->SetScreenTopLeft (screenXLeft,    
                                                 screenY,
                                                 screenYTopSpecified);

            if (status == ERR_SUCCESS)
            {
                status = m_drawingElement->SetScreenTopLeft (m_sprite->GetScreenXLeft (), 
                                                             m_sprite->GetScreenYTop ()); 
            } // Endif.

        } // Endif.

        else
        {
            // No.

            status = ERR_INVALID_SEQUENCE;
        } // Endelse.

        return (status);
    } // Endproc.


    FolioStatus StoreSpriteBackground (Gdiplus::Graphics& graphics)
    {
        return (IsCreated () ? m_sprite->StoreUnderlyingBackground (graphics) : ERR_SUCCESS);
    } // Endproc.


    FolioStatus RestoreSpriteBackground (Gdiplus::Graphics& graphics)
    {
        return (IsCreated () ? m_sprite->RestoreUnderlyingBackground (graphics) : ERR_SUCCESS);
    } // Endproc.


    FolioStatus DrawSprite (Gdiplus::Graphics&                                  graphics,
                            Folio::Core::Graphic::AGdiGraphicElement::RectList* dirtyRects = 0)
    {
        return (IsCreated () ? m_sprite->Draw (graphics, dirtyRects) : ERR_SUCCESS);
    } // Endproc.


    T                   m_sprite;           // The sprite.
    DrawingElementPtr   m_drawingElement;   // The sprite's drawing element.
    UInt32              m_createdTickCount; // The tick count when the sprite drawing element was created.
}; // Endclass.


template <typename T>
FolioStatus StoreSpriteBackgrounds (Gdiplus::Graphics&  graphics,
                                    T&                  spriteDrawingElementsList)
{
    FolioStatus status = ERR_SUCCESS;

    if (!spriteDrawingElementsList.empty ())
    {
        // Store all the sprites' backgrounds.

        for (T::iterator itr = spriteDrawingElementsList.begin ();
             (status == ERR_SUCCESS) && (itr != spriteDrawingElementsList.end ());
             ++itr)
        {
            // Store the sprite's background.

            status = itr->m_sprite->StoreUnderlyingBackground (graphics);
        } // Endfor.
    
    } // Endif.

    return (status);
} // Endproc.


template <typename T>
FolioStatus RestoreSpriteBackgrounds (Gdiplus::Graphics&    graphics,
                                      T&                    spriteDrawingElementsList)
{
    FolioStatus status = ERR_SUCCESS;

    if (!spriteDrawingElementsList.empty ())
    {
        // Restore all the sprites' backgrounds.

        for (T::iterator itr = spriteDrawingElementsList.begin ();
             (status == ERR_SUCCESS) && (itr != spriteDrawingElementsList.end ());
             ++itr)
        {
            // Restore the sprite's background.

            status = itr->m_sprite->RestoreUnderlyingBackground (graphics);
        } // Endfor.
    
    } // Endif.

    return (status);
} // Endproc.


template <typename T>
FolioStatus DrawSprites (Gdiplus::Graphics&                                     graphics,
                         T&                                                     spriteDrawingElementsList,
                         Folio::Core::Graphic::AGdiGraphicElement::RectList*    dirtyRects = 0)
{
    FolioStatus status = ERR_SUCCESS;

    if (!spriteDrawingElementsList.empty ())
    {
        // Draw all the sprites.

        for (T::iterator itr = spriteDrawingElementsList.begin ();
             (status == ERR_SUCCESS) && (itr != spriteDrawingElementsList.end ());
             ++itr)
        {
            // Draw the sprite.

            status = itr->m_sprite->Draw (graphics, dirtyRects);
        } // Endfor.
    
    } // Endif.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
