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


// Definitions and Types.

struct DIBITMAPINFO
{
    BITMAPINFOHEADER    bmiHeader;
    RGBQUAD             bmiColors [256];
};


// Routines.
FolioStatus CreateCompatibleBitmap (FolioHandle     dcHandle,
                                    Int32           bitmapWidth,
                                    Int32           bitmapHeight,
                                    FolioHandle&    bitmapHandle);
FolioStatus CreateMonochromeBitmap  (FolioHandle        dcHandle,
                                     FolioHandle        sourceBitmapHandle,
                                     const COLORREF&    transparentColourRef,
                                     FolioHandle&       monochromeBitmapHandle);
FolioStatus CreateCompatibleBitmap (FolioHandle     dcHandle,
                                    FolioHandle     diBitmapHandle,
                                    FolioHandle&    bitmapHandle);
FolioStatus CreateCopiedDiBitmap (FolioHandle       dcHandle, 
                                  FolioHandle       diBitmapHandle, 
                                  FolioHandle&      copiedDiBitmapHandle);
FolioStatus CreateRotatedDiBitmap (FolioHandle      dcHandle, 
                                   FolioHandle      diBitmapHandle, 
                                   const double&    radians, 
                                   const COLORREF&  backgroundColourRef,
                                   FolioHandle& rotatedDiBitmapHandle);
FolioStatus LoadBitmap (FolioHandle     instanceHandle,
                        UInt16          resourceId,
                        bool            loadDiBitmap,
                        FolioHandle&    bitmapHandle);
FolioStatus LoadBitmap (const FolioString&  fileName,
                        bool                loadDiBitmap,
                        FolioHandle&        bitmapHandle);
FolioStatus QueryBitmapDetails (FolioHandle bitmapHandle,
                                BITMAP&     bitmap);
FolioStatus QueryBitmapDimensions (FolioHandle  bitmapHandle,
                                   Int32&       bitmapWidth,
                                   Int32&       bitmapHeight);
FolioStatus QueryDiBitmapDetails (FolioHandle   dcHandle,
                                  FolioHandle   diBitmapHandle,
                                  DIBITMAPINFO& diBitmapInfo,
                                  Byte*&        diBitmapPixels);
FolioStatus QueryColourTableIndexInDiBitmap (FolioHandle        dcHandle,
                                             FolioHandle        bitmapHandle,
                                             const COLORREF&    colourRef,
                                             UInt32&            colourTableIndex);
FolioStatus ChangeColourInDiBitmap (FolioHandle     dcHandle,
                                    FolioHandle     bitmapHandle,
                                    UInt32          colourTableIndex,
                                    const COLORREF& newColourRef);
FolioStatus ChangeColourInDiBitmap (FolioHandle     dcHandle,
                                    FolioHandle     bitmapHandle,
                                    const COLORREF& colourRef,
                                    const COLORREF& newColourRef,
                                    UInt32&         colourTableIndex);
FolioStatus ChangeColourInBitmap (FolioHandle       dcHandle,
                                  FolioHandle       bitmapHandle,
                                  const COLORREF&   colourRef,
                                  const COLORREF&   newColourRef);
FolioStatus CopyBitmap (FolioHandle destinationDcHandle,
                        Int32       destinationX,
                        Int32       destinationY,
                        Int32       destinationWidth,
                        Int32       destinationHeight,
                        FolioHandle sourceDcHandle,
                        Int32       sourceX,
                        Int32       sourceY,
                        UInt32      rasterOperation);
FolioStatus ScaleBitmap (FolioHandle destinationDcHandle,
                         Int32       destinationX,
                         Int32       destinationY,
                         Int32       destinationWidth,
                         Int32       destinationHeight,
                         FolioHandle sourceDcHandle,
                         Int32       sourceX,
                         Int32       sourceY,
                         Int32       sourceWidth,
                         Int32       sourceHeight,
                         UInt32      rasterOperation);
FolioStatus DestroyBitmap (FolioHandle bitmapHandle);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
