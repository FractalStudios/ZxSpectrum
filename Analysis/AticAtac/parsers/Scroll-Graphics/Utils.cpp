#include "stdafx.h"
#include "File.h"
#include "Utils.h"

namespace Utils
{

using namespace Gdiplus;

DWORD   ReadFile (const std::wstring    &filePath,
                  DataList              &fileData)
{
    // Open the file for reading.

    Utils::File    file;

    DWORD   dwWin32Error = file.Create (filePath, 
                                        GENERIC_READ,
                                        FILE_SHARE_READ,
                                        OPEN_EXISTING);

    if (dwWin32Error == ERROR_SUCCESS)
    {
        // Get the file's size.

        UINT    uiLowOrderSize  = 0;    // Initialise!
        UINT    uiHighOrderSize = 0;

        dwWin32Error = file.QuerySize (uiLowOrderSize, uiHighOrderSize);

        if (dwWin32Error == ERROR_SUCCESS)
        {
            // Read from the file.

            fileData.resize (uiLowOrderSize);

            UINT    uiNumOfBytes = uiLowOrderSize;

            dwWin32Error = file.Read (&(fileData [0]), uiNumOfBytes);

            if (dwWin32Error == ERROR_SUCCESS)
            {
                fileData.resize (uiNumOfBytes);
            } // Endif.

            else
            {
                ::wprintf (L"Read file failed, dwWin32Error=%u(0x%08.08x), szFolderPath=%s.",
                           dwWin32Error, dwWin32Error,
                           filePath.c_str ());
            } // Endelse.

        } // Endif.

        else
        {
            ::wprintf (L"Query file size failed, dwWin32Error=%u(0x%08.08x), szFolderPath=%s.",
                       dwWin32Error, dwWin32Error,
                       filePath.c_str ());
        } // Endelse.

    } // Endif.

    else
    {
        ::wprintf (L"Create file failed, dwWin32Error=%u(0x%08.08x), szFolderPath=%s, uiDesiredAccess=0x%08.08x, uiShareMode=0x%08.08x, uiCreationDisposition=0x%08.08x, uiAttributes=0x%08.08x.",
                   dwWin32Error, dwWin32Error,
                   filePath.c_str (),
                   GENERIC_READ,
                   FILE_SHARE_READ,
                   OPEN_EXISTING,
                   FILE_ATTRIBUTE_NORMAL);
    } // Endelse.

    return (dwWin32Error);
} // Endproc.


std::wstring    DescribeData (const DataList &data)
{
    std::wostringstream str;

    for (DataList::const_iterator itr = data.begin ();
         itr != data.end ();
         ++itr)
    {
        str << std::hex << std::setw (2) << std::setfill (L'0') << static_cast<int> (*itr) << L' ';
    } // Endfor.

    return (str.str ());
} // Endproc.


std::wstring    DescribeData (WORD              wMaxWidth,
                              WORD              wMaxHeight,
                              const DataList    &data)
{
    std::wostringstream str;

    str << std::endl;

    for (WORD wHeight = 0; wHeight < wMaxHeight; ++wHeight)
    {
        str << std::dec << std::setw (2) << std::setfill (L'0') << (wHeight + 1) << L": ";

        for (WORD wWidth = 0; wWidth < wMaxWidth; ++wWidth)
        {
            str << std::hex << std::setw (2) << std::setfill (L'0') << static_cast<int> (data [wHeight * wMaxWidth + wWidth]) << L',';
        } // Endfor.

        str << std::endl;
    } // Endfor.

    return (str.str ());
} // Endproc.


void    ShowConsoleCursor (bool bShow)
{
    HANDLE hConsole = ::GetStdHandle (STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo = {0};

    ::GetConsoleCursorInfo (hConsole, &(cursorInfo));
    
    cursorInfo.bVisible = bShow;
    
    ::SetConsoleCursorInfo (hConsole, &(cursorInfo));
} // Endproc.


GdiStatus   RegisterGdi (ULONG_PTR &lpGdiToken)
{
    GdiplusStartupInput GdiStartupInput;

    return (GdiplusStartup (&(lpGdiToken), 
                            &(GdiStartupInput), 
                            NULL));
} // Endproc.


GdiStatus   DeregisterGdi (ULONG_PTR &lpGdiToken)
{
    GdiplusShutdown (lpGdiToken);

    return (Ok);
} // Endproc.


GdiStatus   QueryEncoderClsid (const std::wstring   &format,
                               CLSID                &clsid)
{
    GdiStatus   gdiStatus = Ok;

    UINT  uiNumEncoders = 0;    // Initialise!
    UINT  uiSize        = 0;
   
    gdiStatus = GetImageEncodersSize (&(uiNumEncoders), &(uiSize));

    if (gdiStatus == Ok)
    {
        if (uiSize)
        {
            ImageCodecInfo  *lpImageCodecInfo = 
                reinterpret_cast<ImageCodecInfo *> (new BYTE [uiSize]);
   
            gdiStatus = GetImageEncoders (uiNumEncoders, 
                                          uiSize, 
                                          lpImageCodecInfo);

            if (gdiStatus == Ok)
            {
                bool    bFound = false;

                for (UINT uiEncoder = 0; 
                     !bFound && (uiEncoder < uiNumEncoders);
                     ++uiEncoder)
                {
                    if (wcscmp (lpImageCodecInfo [uiEncoder].MimeType, 
                        format.c_str ()) == 0 )
                    {
                        clsid = lpImageCodecInfo [uiEncoder].Clsid;

                        bFound = true;  
                    } // Endif.

                } // Endfor.

                if (!bFound)
                {
                    gdiStatus = FileNotFound;
                } // Endif.

            } // Endif.

            delete [] lpImageCodecInfo;
        } // Endif.

        else
        {
            gdiStatus = InvalidParameter;
        } // Endelse.

    } // Endif.
   
    return (gdiStatus);
} // Endproc.


bool    SaveBitmap (HBITMAP             hBitmap, 
                    const std::wstring  &fileName)
{
    CLSID   clsid;
    GdiStatus   gdiStatus = QueryEncoderClsid (L"image/bmp", clsid);

    if (gdiStatus == Ok)
    {
        // Note the original bitmap.

        Bitmap  orgBitmap(hBitmap, NULL);
        
        // Convert to 4-bit.

        Bitmap  newBitmap(orgBitmap.GetWidth (), orgBitmap.GetHeight (), PixelFormat4bppIndexed);
        newBitmap.SetResolution (orgBitmap.GetHorizontalResolution (), orgBitmap.GetVerticalResolution ());

        Graphics    *lpGdiGraphics = Graphics::FromImage (&(newBitmap));

        lpGdiGraphics->DrawImage (&(orgBitmap), 0, 0);

        if (gdiStatus == Ok)
        {
            // Save the new 4-bit bitmap.

            gdiStatus = newBitmap.Save (fileName.c_str (), 
                                        &(clsid), 
                                        NULL);
        } // Endif.

        delete lpGdiGraphics;
    } // Endif.

    return (gdiStatus == Ok);
} // Endproc.

}; // Endnamespace.

/******************************* End of File *******************************/
