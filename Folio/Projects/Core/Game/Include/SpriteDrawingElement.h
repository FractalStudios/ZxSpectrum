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
    // Drawing element pointer.
    typedef std::shared_ptr<DrawingElement> DrawingElementPtr;

    SpriteDrawingElement ()
    :   m_reset(false)
    {} // Endproc.

    SpriteDrawingElement (const T&              sprite,
                          DrawingElement::Id    id,
                          UInt32                collisionGridCellValue = CollisionGrid::CELL_VALUE_EMPTY)
    :   m_sprite(sprite),
        m_drawingElement(new DrawingElement(id, sprite, sprite.get (), collisionGridCellValue)),
        m_reset(false)
    {} // Endproc.

    ~SpriteDrawingElement ()
    {} // Endproc.

    FolioStatus Create  (const T&              sprite,
                         DrawingElement::Id    id,
                         UInt32                collisionGridCellValue = CollisionGrid::CELL_VALUE_EMPTY)
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

            m_reset     = false;
            m_sprite    = sprite;
            
            m_drawingElement.reset (new DrawingElement(id, sprite, sprite.get (), collisionGridCellValue));
        } // Endelse.

        return (status);
    } // Endproc.


    bool    IsCreated () const
    {
        return (m_sprite && m_drawingElement);
    } // Endproc.

    void    Kill ()
    {
        Reset ();
    } // Endproc.
        
    bool    IsKilled () const
    {
        return (m_reset);
    } // Endproc.

    void    Reset ()
    {
        m_reset = true;

        m_sprite.reset ();
        m_drawingElement.reset ();
    } // Endproc.
        
    FolioStatus StoreSpriteBackground (Gdiplus::Graphics &graphics)
    {
        return (m_sprite ? m_sprite->StoreUnderlyingBackground (graphics) : ERR_SUCCESS);
    } // Endproc.

    FolioStatus RestoreSpriteBackground (Gdiplus::Graphics &graphics)
    {
        return (m_sprite ? m_sprite->RestoreUnderlyingBackground (graphics) : ERR_SUCCESS);
    } // Endproc.

    FolioStatus DrawSprite (Gdiplus::Graphics                                   &graphics,
                            Folio::Core::Graphic::AGdiGraphicElement::RectList  *dirtyRects = 0)
    {
        return (m_sprite ? m_sprite->Draw (graphics, dirtyRects) : ERR_SUCCESS);
    } // Endproc.

    T                   m_sprite;           // The sprite.
    DrawingElementPtr   m_drawingElement;   // The sprite's drawing element.
    bool                m_reset;            // Indicates if the sprite has been reset.
}; // Endclass.


template <typename T>
FolioStatus StoreSpriteBackgrounds (Gdiplus::Graphics   &graphics,
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
FolioStatus RestoreSpriteBackgrounds (Gdiplus::Graphics &graphics,
                                      T&                spriteDrawingElementsList)
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
FolioStatus DrawSprites (Gdiplus::Graphics                                  &graphics,
                         T&                                                 spriteDrawingElementsList,
                         Folio::Core::Graphic::AGdiGraphicElement::RectList *dirtyRects = 0)
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
