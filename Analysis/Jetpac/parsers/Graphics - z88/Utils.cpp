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


DWORD   WriteFile (const std::wstring   &filePath,
                   const DataList       &fileData)
{
    // Open the file for writing.

    Utils::File    file;

    DWORD   dwWin32Error = file.Create (filePath, 
                                        GENERIC_WRITE,
                                        FILE_SHARE_READ | FILE_SHARE_WRITE,
                                        OPEN_ALWAYS);

    if ((dwWin32Error == ERROR_SUCCESS) ||
        (dwWin32Error == ERROR_ALREADY_EXISTS))
    {
        dwWin32Error = file.MoveToEndOfFile ();

        if (dwWin32Error == ERROR_SUCCESS)
        {
            // Write to the file.

            UINT    uiNumOfBytes = fileData.size ();

            dwWin32Error = file.Write (const_cast<DataList::value_type *> (&(fileData [0])), uiNumOfBytes);

            if (dwWin32Error != ERROR_SUCCESS)
            {
                ::wprintf (L"Write file failed, dwWin32Error=%u(0x%08.08x), szFolderPath=%s.",
                            dwWin32Error, dwWin32Error,
                            filePath.c_str ());
            } // Endif.

        } // Endif.

        else
        {
            ::wprintf (L"Move to end of file failed, dwWin32Error=%u(0x%08.08x), szFolderPath=%s.",
                        dwWin32Error, dwWin32Error,
                        filePath.c_str ());
        } // Endelse.

    } // Endif.

    else
    {
        ::wprintf (L"Create file failed, dwWin32Error=%u(0x%08.08x), szFolderPath=%s, uiDesiredAccess=0x%08.08x, uiShareMode=0x%08.08x, uiCreationDisposition=0x%08.08x, uiAttributes=0x%08.08x.",
                   dwWin32Error, dwWin32Error,
                   filePath.c_str (),
                   GENERIC_WRITE,
                   FILE_SHARE_WRITE,
                   CREATE_ALWAYS,
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


bool    LoadBitmap (const std::wstring  &fileName,
                    BYTE                &byWidthInPixels,
                    BYTE                &byHeightInPixels,
                    DataList            &pixelData)
{
    GdiStatus   gdiStatus = Ok;

    // Load the bitmap.

    Bitmap*  orgBitmap(new Bitmap(fileName.c_str ()));

    if (orgBitmap)
    {
        byWidthInPixels     = orgBitmap->GetWidth ();
        byHeightInPixels    = orgBitmap->GetHeight ();

        for (BYTE byY = 0; (gdiStatus == Ok) && (byY < byHeightInPixels); ++byY)
        {
            BYTE    byGlyphLine = 0;

            for (BYTE byX = 0; (gdiStatus == Ok) && (byX < byWidthInPixels); ++byX)
            {
                Color   colour;
                gdiStatus = orgBitmap->GetPixel (byX, byY, &(colour));

                if (gdiStatus == Ok)
                {
                    byGlyphLine <<= 1;

                    if (colour.ToCOLORREF () != RGB(0, 0, 0))
                    {
                        byGlyphLine |= 0x01;
                    } // Endif.

                    if (byX && !((byX + 1) % 8))
                    {
                        pixelData.push_back (byGlyphLine);
                        byGlyphLine = 0;
                    } // Endif.

                } // Endif.

            } // Endfor.

        } // Endfor.

        delete orgBitmap;
    } // Endif.

    return ((gdiStatus == Ok) && !pixelData.empty ());
} // Endproc.


std::string     WideStringToNarrowString (const std::wstring &string)
{
    std::string narrowString;

    int nLength = ::WideCharToMultiByte (CP_ACP,
                                         0,
                                         string.c_str (),
                                         -1,    // Whole string.
                                         NULL,
                                         0,
                                         NULL,
                                         NULL);

    if (nLength > 0)
    {
        std::vector<char>   narrowBuffer(nLength);

        if (::WideCharToMultiByte (CP_ACP,
                                   0,
                                   string.c_str (),
                                   -1,  // Whole string.
                                   &(narrowBuffer [0]),
                                   nLength,
                                   NULL,
                                   NULL) > 0)
        {
            narrowString = &(narrowBuffer [0]);
        } // Endif.

    } // Endif.

    return (narrowString);
} // Endproc.


std::wstring    NarrowStringToWideString (const std::string &string)
{
    std::wstring    wideString;

    int nLength = ::MultiByteToWideChar (CP_ACP,
                                         0,
                                         string.c_str (),
                                         -1,    // Whole string.
                                         NULL,
                                         NULL);

    if (nLength > 0)
    {
        std::vector<wchar_t> wideBuffer(nLength);

        if (::MultiByteToWideChar (CP_ACP,
                                   0,
                                   string.c_str (),
                                   -1,  // Whole string.
                                   &(wideBuffer [0]),
                                   nLength) > 0)
        {
            wideString = &(wideBuffer [0]);
        } // Endif.

    } // Endif.

    return (wideString);
} // Endproc.

std::wstring    SplitPath (const std::wstring   &path,
                           bool                 bDrive,
                           bool                 bDirectory,
                           bool                 bFileName,
                           bool                 bFileNameExt)
{
    // Split the path.

    TCHAR   szDrive [_MAX_DRIVE] = {0};
    TCHAR   szDirectory [_MAX_DIR] = {0};
    TCHAR   szFileName [_MAX_FNAME] = {0};
    TCHAR   szFileNameExt [_MAX_EXT] = {0};
    ::_tsplitpath_s (path.c_str (), 
                     bDrive ? szDrive : NULL,
                     bDrive ? ARRAYSIZE(szDrive) : 0,
                     bDirectory ? szDirectory : NULL,
                     bDirectory ? ARRAYSIZE(szDirectory) : 0,
                     bFileName ? szFileName : NULL,
                     bFileName ? ARRAYSIZE(szFileName) : 0,
                     bFileNameExt ? szFileNameExt : NULL,
                     bFileNameExt ? ARRAYSIZE(szFileNameExt) : 0);

    std::wstring  splitPath;

    if (bDrive)
    {
        splitPath += szDrive;
    } // Endif.

    if (bDirectory)
    {
        splitPath += szDirectory;
    } // Endif.

    if (bFileName)
    {
        splitPath += szFileName;
    } // Endif.

    if (bFileNameExt)
    {
        splitPath += szFileNameExt;
    } // Endif.

    return (splitPath);
} // Endproc.

}; // Endnamespace.

/******************************* End of File *******************************/
