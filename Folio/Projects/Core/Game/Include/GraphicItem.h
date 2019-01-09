#pragma once

// STL includes.
#include    <memory>

// "Home-made" includes.
#include    <Graphic.h>
#include    "AItem.h"
#include    "ResourceGraphic.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Game
{

class GraphicItem : public AItem
{
public:
    GraphicItem ();
    ~GraphicItem ();

    FolioStatus Create (FolioHandle         dcHandle,
                        FolioHandle         instanceHandle,
                        DrawingElement::Id  drawingElementId,
                        UInt16              bitmapResourceId,
                        Id                  itemId,
                        Int32               screenXLeft,
                        Int32               screenYTop,
                        UInt32              screenScale,
                        bool                maskedBitmapDrawingElementRqd = false,
                        Gdiplus::ARGB       maskColour = Folio::Core::Graphic::DEFAULT_BACKGROUND_COLOUR);
    FolioStatus Create (FolioHandle         dcHandle,
                        FolioHandle         instanceHandle,
                        DrawingElement::Id  drawingElementId,
                        UInt16              bitmapResourceId,
                        Id                  itemId,
                        Int32               screenXLeft,
                        Int32               screenYTop,
                        UInt32              screenScale,
                        Gdiplus::ARGB       changeColour, 
                        Gdiplus::ARGB       foregroundColour = Folio::Core::Graphic::DEFAULT_FOREGROUND_COLOUR,
                        Gdiplus::ARGB       backgroundColour = Folio::Core::Graphic::DEFAULT_BACKGROUND_COLOUR,
                        bool                maskedBitmapDrawingElementRqd = false,
                        Gdiplus::ARGB       maskColour = Folio::Core::Graphic::DEFAULT_BACKGROUND_COLOUR);
    FolioStatus QueryDrawingElements (FolioHandle           dcHandle,
                                      Gdiplus::ARGB         foregroundColour,
                                      DrawingElementsList&  drawingElementsList);

    Folio::Core::Graphic::GdiBitmapPtr  GetGdiBitmap () const;

private:
    ResourceGraphicPtr  m_resourceGraphic;  // The resource graphic of the graphic item.

    FolioStatus CreateDrawingElements (FolioHandle          dcHandle,
                                       DrawingElement::Id   drawingElementId,
                                       Int32                screenXLeft,
                                       Int32                screenYTop,
                                       UInt32               screenScale,
                                       Gdiplus::ARGB        foregroundColour = Folio::Core::Graphic::DEFAULT_FOREGROUND_COLOUR);

    bool    IsCreated () const;
}; // Endclass.

// Graphic item pointer.
typedef std::shared_ptr<GraphicItem>    GraphicItemPtr;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
