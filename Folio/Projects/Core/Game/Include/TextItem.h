#pragma once

// STL includes.
#include    <memory>

// "Home-made" includes.
#include    <Graphic.h>
#include    "AItem.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Game
{

class TextItem : public AItem
{
public:
    TextItem ();
    ~TextItem ();

    FolioStatus Create (FolioHandle                             dcHandle,
                        DrawingElement::Id                      drawingElementId,
                        Folio::Core::Graphic::GdiRasterFont&    gdiRasterFont,
                        Id                                      itemId,
                        Int32                                   screenXLeft,
                        Int32                                   screenYTop,
                        UInt32                                  screenScale,
                        Gdiplus::ARGB                           textColour = Folio::Core::Graphic::DEFAULT_TEXT_COLOUR,
                        Gdiplus::ARGB                           backgroundColour = Folio::Core::Graphic::DEFAULT_BACKGROUND_COLOUR,
                        bool                                    gdiBitmapCacheRqd = false);
   FolioStatus SetInvert (bool              invert,
                          Gdiplus::Graphics &graphics, 
                          bool              &redrawCanvas);

    Folio::Core::Graphic::GdiRasterTextPtr  GetGdiRasterText () const;

private:
    Folio::Core::Graphic::GdiRasterTextPtr  m_gdiRasterText;    // The GDI raster text of the text item.

    bool    IsCreated () const;
}; // Endclass.

// Text item pointer.
typedef std::shared_ptr<TextItem>   TextItemPtr;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
