#pragma once

// "Home-made" includes.
#include    "GraphicConstsAndTypes.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Graphic
{

namespace Gdi
{

// Routines.
FolioStatus RegisterGdi (FolioHandle& gdiHandle);
FolioStatus DeregisterGdi (FolioHandle gdiHandle);
FolioStatus InitializeGraphics (Gdiplus::Graphics&      graphics,
                                bool                    eraseBackground = false,
                                const Gdiplus::Color&   backgroundColour = DEFAULT_BACKGROUND_COLOUR);

FolioStatus DrawText (Gdiplus::Graphics&    graphics,
                      const FolioString&    textString,
                      const Gdiplus::Font&  font,
                      int                   xPos,
                      int                   yPos,
                      const Gdiplus::Brush& brush);
FolioStatus DrawText (Gdiplus::Graphics&            graphics,
                      const FolioString&            textString,
                      const Gdiplus::Font&          font,
                      const Gdiplus::Rect&          area,
                      const Gdiplus::StringFormat&  stringFormat,
                      const Gdiplus::Brush&         brush);
FolioStatus DrawLine (Gdiplus::Graphics&    graphics, 
                      int                   xPosStart,
                      int                   yPosStart,
                      int                   xPosEnd,
                      int                   yPosEnd,
                      const Gdiplus::Pen&   pen);
FolioStatus DrawPath (Gdiplus::Graphics&            graphics, 
                      const Gdiplus::GraphicsPath&  graphicsPath,
                      const Gdiplus::Pen&           pen);
FolioStatus FillPath (Gdiplus::Graphics&            graphics, 
                      const Gdiplus::GraphicsPath&  graphicsPath,
                      const Gdiplus::Brush&         brush);
FolioStatus DrawRectangle (Gdiplus::Graphics&   graphics, 
                           const Gdiplus::Rect& rect,
                           const Gdiplus::Pen&  pen);
FolioStatus FillRectangle (Gdiplus::Graphics&       graphics, 
                           const Gdiplus::Rect&     rect,
                           const Gdiplus::Brush&    brush);
FolioStatus DrawEllipse (Gdiplus::Graphics&     graphics, 
                         const Gdiplus::Rect&   rect,
                         const Gdiplus::Pen&    pen);
FolioStatus FillEllipse (Gdiplus::Graphics&     graphics, 
                         const Gdiplus::Rect&   rect,
                         const Gdiplus::Brush&  brush);
FolioStatus DrawBitmap (Gdiplus::Graphics&              graphics, 
                        Gdiplus::Bitmap&                bitmap,
                        const Gdiplus::Rect&            area, 
                        int                             xPos,
                        int                             yPos,
                        int                             width,
                        int                             height,
                        const Gdiplus::ImageAttributes& imageAttributes);
FolioStatus SaveBitmap (const FolioString&  fileName,
                        Gdiplus::Bitmap&    bitmap);

FolioStatus SetClippingRegion (Gdiplus::Graphics&       graphics,
                               const Gdiplus::Region&   clippingRegion,
                               Gdiplus::CombineMode     combineMode);
FolioStatus ResetClippingRegion (Gdiplus::Graphics& graphics);
FolioStatus QueryClippingRegion (Gdiplus::Graphics& graphics, 
                                 Gdiplus::Region&   clippingRegion);
FolioStatus QueryClippingRegionHandle (Gdiplus::Graphics&   graphics,
                                       FolioHandle&         clippingRegionHandle);
FolioStatus QueryEncoderClsid (const FolioString&   format,
                               CLSID&               clsid);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
