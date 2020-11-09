#include "stdafx.h"
#include "Main.h"
#include "File.h"
#include "Utils.h"
#include "ZxSpectrum.h"

enum CONTROL
{
    C_UNDEFINED = 0,
    C_DATA_ADDRESS,
    C_DATA_BYTE,
    C_SCREEN_ADDRESS,
    C_SCREEN_WIDTH,
    C_SCREEN_HEIGHT,
    C_SCREEN_POINTS,
    C_SCREEN_LINETO,
}; // Endenum.

DWORD   ReadFile (const std::wstring    &filePath,
                  Utils::DataList       &fileData)
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


std::wstring    DescribeBYTE (BYTE byte)
{
    std::wostringstream str;

    str << L"$" << std::setw(2) << std::setfill(L'0') << std::uppercase << std::hex << byte;

    return (str.str ());
} // Endproc.


std::wstring    DescribeWORD (WORD word)
{
    std::wostringstream str;

    str << L"$" << std::setw(4) << std::setfill(L'0') << std::uppercase << std::hex << word;

    return (str.str ());
} // Endproc.


//std::wstring    BuildSklText (const AddressMap &addressMap)
//{
//    std::wostringstream str;


    //str << L"; Background Item Table" << std::endl
    //    << L";" << std::endl;

    //str << L"; #TABLE(default)" << std::endl
    //    << L"; { =h Offset   | =h Field              | =h Description }" << std::endl
    //    << L"; { $00         | Graphic Type          | Graphic type. }" << std::endl
    //    << L"; { $01         | Screen Number         | Screen number. }" << std::endl
    //    << L"; { $02         | Door Flags            | ??? }" << std::endl
    //    << L"; { $03         | X                     | X coordinate (left). }" << std::endl
    //    << L"; { $04         | Y                     | Y coordinate (bottom). }" << std::endl
    //    << L"; { $05         | Flags                 | ??? }" << std::endl
    //    << L"; { $06         | Door Timing           | ??? }" << std::endl
    //    << L"; { $07         | Door Flags            | ??? }" << std::endl
    //    << L"; TABLE#" << std::endl;

    //str << L"@label=BackgroundItemTable" << std::endl
    //    << L"b";

    //for (BackgroundList::const_iterator itr = backgroundItemList.begin ();
    //     itr != backgroundItemList.end ();
    //     ++itr)
    //{
    //    if (itr != backgroundItemList.begin ())
    //    {
    //        str << L" ";
    //    } // Endif.

    //    str << DescribeWORD (itr->m_wAddress)
    //        << L" DEFB " 
    //        << DescribeBYTE (itr->m_byGraphicType) << L","
    //        << DescribeBYTE (itr-> m_byScreen) << L","
    //        << DescribeBYTE (itr-> m_byDoorUnknown1) << L","
    //        << DescribeBYTE (itr-> m_byXPosition) << L","
    //        << DescribeBYTE (itr-> m_byYPosition) << L","
    //        << DescribeBYTE (itr-> m_byFlags) << L","
    //        << DescribeBYTE (itr-> m_byDoorTiming) << L","
    //        << DescribeBYTE (itr-> m_byDoorUnknown2)
    //        << L" ; " << DescribeGraphic (itr->m_byGraphicType) 
    //        << L", Screen " << DescribeBYTE (itr-> m_byScreen) 
    //        << L" (" << DescribeBYTE (itr->m_byYPosition) << "," << DescribeBYTE (itr->m_byXPosition) << L")."
    //        << std::endl;
    //} // Endfor.

//    return (str.str ());
//} // Endproc.


enum PARSE
{
    P_BYTE,
    P_WORD,
    P_BYTE_TO_WORD,
}; // Endenum.


typedef std::vector<std::pair<WORD, BYTE>> AddressMap;

AddressMap::const_iterator Find (WORD wAddress, const AddressMap &addressMap)
{
    AddressMap::const_iterator  itr = addressMap.begin ();

    for (;
         itr != addressMap.end ();
         ++itr)
    {
        if (itr->first == wAddress)
        {
            break;
        } // Endif.

    } // Endfor.

    return (itr);
} // Endproc.


struct ScreenType
{
    ScreenType ()
    :   m_byScreen(-1),
        m_wAddress(0),
        m_byWidth(0),
        m_byHeight(0),
        m_wPoints(0),
        m_wLineTo(0)
    {} // Endproc.

    void    Reset ()
    {
        m_byScreen  = -1;
        m_wAddress  = 0;
        m_byWidth   = 0;
        m_byHeight  = 0;
        m_wPoints   = 0;
        m_wLineTo    = 0;
    } // Endproc.

    static  const   int X_START = 100;
    static  const   int Y_START = 100;
    static  const   int WIDTH   = 192;
    static  const   int HEIGHT  = WIDTH;
    static  const   int SCALE   = 1;

    void    Display (const AddressMap &addressMap) const
    {
        Utils::ShowConsoleCursor (false);

        // Get window handle to console.

        HWND    hConsoleWnd = ::GetConsoleWindow ();

        // Get device context to console.

        HDC hConsoleDC = ::GetDC (hConsoleWnd);

        int x = X_START;
        int y = Y_START;

        ::SelectObject (hConsoleDC, ::GetStockObject (WHITE_PEN));

        AddressMap::const_iterator itrPoints = Find (m_wPoints, addressMap);
        AddressMap::const_iterator itrLineTo = Find (m_wLineTo, addressMap);

        bool    bFinishedOuter = false;

        do
        {
            if (itrLineTo == addressMap.end ())
            {
                _asm {int 3};
            } // Endif.

            else
            if (itrLineTo->second == 0xFF)
            {
                bFinishedOuter = true;
            } // Endelseif.

            else
            {                                
                BYTE    byStartX = itrPoints [2 * itrLineTo->second    ].second;
                BYTE    byStartY = itrPoints [2 * itrLineTo->second + 1].second;

                bool    bFinishedInner = false;

                do
                {
                    itrLineTo++;

                    if (itrLineTo == addressMap.end ())
                    {
                        _asm {int 3};
                    } // Endif.

                    else
                    if (itrLineTo->second == 0xFF)
                    {
                        bFinishedInner = true;
                    } // Endelseif.

                    else
                    {
                        BYTE    byEndX = itrPoints [2 * itrLineTo->second    ].second;
                        BYTE    byEndY = itrPoints [2 * itrLineTo->second + 1].second;

                        //printf ("(%u, %u) to (%u, %u)\n", byStartX, byStartY, byEndX, byEndY);

                        // Draw from start point to end.

                        ::MoveToEx (hConsoleDC, X_START + byStartX,  Y_START + byStartY, NULL);
                        ::LineTo (hConsoleDC, X_START + byEndX,  Y_START + byEndY);
                    } // Endelse.
                
                } // Enddo.
                while (!bFinishedInner);

                itrLineTo++;
            } // Endelse.
        
        } // Enddo.
        while (!bFinishedOuter);
        // Release device console DC.

        ::ReleaseDC (hConsoleWnd, hConsoleDC);
    } // Endproc.

    void    Save (const AddressMap &addressMap) const
    {
        Display (addressMap);

        // Get window handle to console.

        HWND    hConsoleWnd = ::GetConsoleWindow ();

        // Get device context to console.

        HDC hConsoleDC = ::GetDC (hConsoleWnd);

        // Create a device context to put it in

        HDC hMemoryDC = ::CreateCompatibleDC (hConsoleDC);

        // Create a compatible bitmap to put it in.

        HBITMAP hBitmap = CreateCompatibleBitmap (hConsoleDC, WIDTH * SCALE, HEIGHT * SCALE);

        // Select new bitmap.

        HBITMAP hOldBitmap = static_cast<HBITMAP> (::SelectObject (hMemoryDC, hBitmap));

        // Copy new bitmap.

        ::BitBlt (hMemoryDC, 
                  0, 
                  0, 
                  WIDTH * SCALE, 
                  HEIGHT * SCALE, 
                  hConsoleDC, 
                  X_START, 
                  Y_START, 
                  SRCCOPY);

        // Restore old bitmap.
        
        ::SelectObject (hMemoryDC, hOldBitmap);

        // Delete memory DC.

        ::DeleteDC (hMemoryDC);

        // Save the bitmap.

        std::wostringstream str;
        str << L"ScreenType" << DescribeBYTE(m_byScreen) << L".bmp";

        Utils::SaveBitmap (hBitmap, str.str ());
       
        // Release device console DC.
        
        ::ReleaseDC (hConsoleWnd, hConsoleDC);
    } // Endproc.

    BYTE    m_byScreen;
    WORD    m_wAddress;
    BYTE    m_byWidth;
    BYTE    m_byHeight;
    WORD    m_wPoints;
    WORD    m_wLineTo;
};

typedef std::vector<ScreenType> ScreenTypeList;


int wmain (int argc, WCHAR* argv[])
{
    int nReturnCode = 0;

    if (argc == 2)
    {
        Utils::DataList    fileData;
        DWORD   dwin32Error = ReadFile (argv [1], fileData);

        if (dwin32Error == ERROR_SUCCESS)
        {
            AddressMap      screenDataMap;

            ScreenTypeList  screenTypeList;
            ScreenType      screenType;
            BYTE            byScreen = 0;
            
            CONTROL control = C_UNDEFINED;
            PARSE   parse   = P_WORD;

            bool    bFinished   = false;    // Initialise!
            UINT    uiNumDigits = 0;
            BYTE    byByte      = 0;
            WORD    wWord       = 0;
            WORD    wAddress    = 0;

            Utils::DataList::const_iterator itr = fileData.begin ();

            while (!bFinished && (itr != fileData.end ()))
            {
                switch (*itr)
                {
                case '0': 
                case '1': 
                case '2': 
                case '3': 
                case '4': 
                case '5': 
                case '6': 
                case '7': 
                case '8': 
                case '9': 
                    switch (parse)
                    {
                    case P_BYTE:
                        byByte <<= 4;
                        byByte += *itr - '0';
                        break;
                    
                    case P_WORD:
                        wWord <<= 4;
                        wWord += *itr - '0';
                        break;

                    case P_BYTE_TO_WORD:
                        if (uiNumDigits < sizeof (WORD))
                        {
                            wWord <<= 4;
                            wWord += *itr - '0';
                        } // Endif.

                        else
                        {
                            WORD    wNibble = *itr - '0';
                            wNibble <<= 4 * (5 - uiNumDigits);
                            wWord |= wNibble;
                        } // Endelse.
                        break;
                    } // Endswitch.

                    ++uiNumDigits;
                    ++itr;
                    break;

                case 'a':
                case 'b':
                case 'c':
                case 'd':
                case 'e':
                case 'f':
                    switch (parse)
                    {
                    case P_BYTE:
                        byByte <<= 4;
                        byByte += *itr - 'a' + 10;
                        break;

                    case P_WORD:
                        wWord <<= 4;
                        wWord += *itr - 'a' + 10;
                        break;

                    case P_BYTE_TO_WORD:
                        if (uiNumDigits < sizeof (WORD))
                        {
                            wWord <<= 4;
                            wWord += *itr - 'a' + 10;
                        } // Endif.

                        else
                        {
                            WORD    wNibble = *itr - 'a' + 10;
                            wNibble <<= 4 * (5 - uiNumDigits);
                            wWord |= wNibble;
                        } // Endelse.
                        break;
                    } // Endswitch.

                    ++uiNumDigits;
                    ++itr;
                    break;

                case 'A':
                case 'B':
                case 'C':
                case 'D':
                case 'E':
                case 'F':
                    switch (parse)
                    {
                    case P_BYTE:
                        byByte <<= 4;
                        byByte += *itr - 'A' + 10;
                        break;

                    case P_WORD:
                        wWord <<= 4;
                        wWord += *itr - 'A' + 10;
                        break;

                    case P_BYTE_TO_WORD:
                        if (uiNumDigits < sizeof (WORD))
                        {
                            wWord <<= 4;
                            wWord += *itr - 'A' + 10;
                        } // Endif.

                        else
                        {
                            WORD    wNibble = *itr - 'A' + 10;
                            wNibble <<= 4 * (5 - uiNumDigits);
                            wWord |= wNibble;
                        } // Endelse.
                        break;
                    } // Endswitch.

                    ++uiNumDigits;
                    ++itr;
                    break;

                case ' ':
                case ',':
                case '\r':
                    switch (parse)
                    {
                    case P_BYTE:
                        switch (control)
                        {
                        case C_DATA_BYTE:
                            if (uiNumDigits)
                            {
                                screenDataMap.push_back (AddressMap::value_type(wAddress, byByte));

                                control = C_DATA_BYTE;
                                parse   = P_BYTE;
                            } // Endif.
                            break;

                        case C_SCREEN_WIDTH:
                            if (uiNumDigits)
                            {
                                screenType.m_wAddress = wAddress;
                                screenType.m_byScreen = byScreen;

                                screenType.m_byWidth  = byByte;

                                control = C_SCREEN_HEIGHT;
                                parse   = P_BYTE;
                            } // Endif.
                            break;

                        case C_SCREEN_HEIGHT:
                            if (uiNumDigits)
                            {
                                screenType.m_byHeight  = byByte;

                                control = C_SCREEN_POINTS;
                                parse   = P_WORD;
                            } // Endif.
                            break;

                        case C_UNDEFINED:
                            break;

                        default:
                            _asm {int 3};
                            break;
                        } // Endswitch.

                        byByte = 0;

                        uiNumDigits = 0;
                        wAddress++;
                        break;

                    case P_WORD:
                        switch (control)
                        {
                        case C_DATA_ADDRESS:
                            if (uiNumDigits)
                            {
                                wAddress = wWord;

                                control = C_DATA_BYTE;
                                parse   = P_BYTE;
                            } // Endif.
                            break;

                        case C_SCREEN_ADDRESS:
                            if (uiNumDigits)
                            {
                                wAddress = wWord;

                                control = C_SCREEN_WIDTH;
                                parse   = P_BYTE;
                            } // Endif.
                            break;

                        case C_SCREEN_POINTS:
                            if (uiNumDigits)
                            {
                                screenType.m_wPoints = wWord;

                                control = C_SCREEN_LINETO;
                                parse   = P_WORD;
                            } // Endif.
                            break;

                        case C_SCREEN_LINETO:
                            if (uiNumDigits)
                            {
                                screenType.m_wLineTo = wWord;

                                screenTypeList.push_back (screenType);
                                screenType.Reset ();

                                byScreen++;

                                control = C_UNDEFINED;
                                parse   = P_BYTE;
                            } // Endif.
                            break;

                        default:
                            _asm {int 3};
                            break;
                        } // Endswitch.
                        
                        wWord = 0;
                        
                        uiNumDigits = 0;
                        break;

                    case P_BYTE_TO_WORD:
                        if (uiNumDigits == (2 * sizeof (WORD)))
                        {
                            _asm {int 3};
                        
                            wWord = 0;
                        
                            uiNumDigits = 0;
                            wAddress += 2;
                        } // Endif.
                        break;

                    default:
                        _asm {int 3};
                        break;
                    } // Endswitch.

                    ++itr;
                    break;

                case 'i':
                    control = C_DATA_ADDRESS;
                    parse   = P_WORD;

                    ++itr;
                    break;

                case 's':
                    control = C_SCREEN_ADDRESS;
                    parse   = P_WORD;

                    ++itr;
                    break;

                default:
                    ++itr;
                    break;                                
                } // Endswitch.

            } // Endwhile.

            ULONG_PTR   lpGdiToken = NULL;

            Utils::GdiStatus    gdiStatus = Utils::RegisterGdi (lpGdiToken);

            if (gdiStatus == Gdiplus::Ok)
            {
                for (ScreenTypeList::const_iterator itr = screenTypeList.begin ();
                     itr != screenTypeList.end ();
                     ++itr)
                {
                    itr->Save (screenDataMap);

                    system("cls");
                } // Endfor.

                Utils::DeregisterGdi (lpGdiToken);
            } // Endif.

        } // Endif.
    
    } // Endif.

    else
    {
        printf ("Feed me a file name to parse.\n");

        nReturnCode = 1;
    } // Endelse.

    return (nReturnCode);
} // Endproc.

/******************************* End of File *******************************/
