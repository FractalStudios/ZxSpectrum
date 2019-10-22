#pragma once

#include <vector>
#include <string>

namespace Gdiplus
{
    using   std::min;
    using   std::max;
}; // Endnamespace.
#include <gdiplus.h>

#pragma pack(push, 1)

namespace Utils
{

// Definitions and Types.

// Data list.
typedef std::vector<BYTE>   DataList;

// GDI+ status.
typedef Gdiplus::Status GdiStatus;


// Routines.

extern  DWORD   ReadFile (const std::wstring    &filePath,
                          DataList              &fileData);

extern  std::wstring    DescribeData (const DataList &data);
extern  std::wstring    DescribeData (WORD              wMaxWidth,
                                      WORD              wMaxHeight,
                                      const DataList    &data);

extern  void    ShowConsoleCursor (bool bShow);

extern  GdiStatus   RegisterGdi (ULONG_PTR &lpGdiToken);
extern  GdiStatus   DeregisterGdi (ULONG_PTR &lpGdiToken);
extern  GdiStatus   QueryEncoderClsid (const std::wstring   &format,
                                       CLSID                &clsid);
extern  bool    SaveBitmap (HBITMAP             hBitmap, 
                            const std::wstring  &fileName);

}; // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
