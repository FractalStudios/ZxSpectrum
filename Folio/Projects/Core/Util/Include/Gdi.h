#pragma once

// Windows includes.
#include    <Windows.h>

// "Home-made" includes.
#include    <Base.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Util
{

namespace Gdi
{

// Routines.
FolioStatus CreateCompatibleMemoryDC (FolioHandle   dcHandle,
                                      FolioHandle&  memoryDcHandle);
FolioStatus DestroyMemoryDC (FolioHandle memoryDcHandle);
FolioStatus SelectObjectIntoDC (FolioHandle     dcHandle,
                                FolioHandle     newObjectHandle,
                                FolioHandle*    oldObjectHandle = 0);
FolioStatus DestroyObject (FolioHandle objectHandle);
FolioStatus SelectClippingRegion (FolioHandle   dcHandle,
                                  FolioHandle   clippingRegionHandle);
FolioStatus DestroyClippingRegion (FolioHandle clippingRegionHandle);

FolioStatus ClearRectangle (FolioHandle  dcHandle,
                            Int32        x,
                            Int32        y,
                            Int32        width,
                            Int32        height,
                            COLORREF     colour);
FolioStatus DrawLine (FolioHandle dcHandle,
                      Int32       startX,
                      Int32       startY,
                      Int32       endX,
                      Int32       endY,
                      Int32       width,
                      COLORREF    colour);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
