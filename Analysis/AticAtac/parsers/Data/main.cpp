#include "stdafx.h"
#include "File.h"


typedef std::vector<BYTE>   DataList;

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


std::wstring    DescribeAttribute (BYTE byAttribute)
{
    static  const   BYTE    ATTRIBUTE_MASK = 0xf0;

    static  const   BYTE    FLASH   = 0x80;
    static  const   BYTE    BRIGHT  = 0x40;

    std::wostringstream str;

    if (byAttribute & FLASH)
    {
        str << L"Flash ";
    } // Endif.

    if (byAttribute & BRIGHT)
    {
        str << L"Bright ";
    } // Endif.

    return (str.str ());
} // Endproc.


std::wstring    DescribeColour (BYTE byColour)
{
    static  const   BYTE    COLOUR_MASK = 0x0f;

    static  const   BYTE    BLACK   = 0;  
    static  const   BYTE    BLUE    = 1;  
    static  const   BYTE    RED     = 2;  
    static  const   BYTE    MAGENTA = 3;  
    static  const   BYTE    GREEN   = 4;  
    static  const   BYTE    CYAN    = 5;  
    static  const   BYTE    YELLOW  = 6;  
    static  const   BYTE    WHITE   = 7;

    switch (byColour & COLOUR_MASK)
    {
    case BLACK:
        return (L"Black");
        break;
    case BLUE:
        return (L"Blue");
        break;
    case RED:
        return (L"Red");
        break;
    case MAGENTA:
        return (L"Magenta");
        break;
    case GREEN:
        return (L"Green");
        break;
    case CYAN:
        return (L"Cyan");
        break;
    case YELLOW:
        return (L"Yellow");
        break;
    case WHITE:
        return (L"White");
        break;
    default:
        {
            std::wostringstream str;
            str << static_cast<int> (byColour);
            return (str.str ());
        } // Endscope.
        break;
    } // Endswitch.

} // Endproc.


std::wstring    DescribeGraphic (BYTE byGraphicType)
{
    std::wostringstream str;
    str << static_cast<int> (byGraphicType) << L' ';

    switch (byGraphicType)
    {
    case 01:
        str << L"Cave Dooor Frame";
        break;
    case 2:
        str << L"Normal Door Frame";
        break;
    case 3:
        str << L"BigDooor Frame";
        break;
    case 8:
        str << L"Red Locked Normal Door";
        break;
    case 9:
        str << L"Green Locked Normal Door";
        break;
    case 10:
        str << L"Cyan Locked Normal Door";
        break;
    case 11:
        str << L"Yellow Locked Normal Door";
        break;
    case 12:
        str << L"Red Locked Cave Door";
        break;
    case 13:
        str << L"Green Locked Cave Door";
        break;
    case 14:
        str << L"Cyan Locked Cave Door";
        break;
    case 15:
        str << L"Yellow Locked Cave Door";
        break;
    case 16:
        str << L"Clock";
        break;
    case 17:
        str << L"Picture";
        break;
    case 18:
        str << L"Table";
        break;
    case 19:
        str << L"Full Chicken";
        break;
    case 20:
        str << L"Chicken Carcass";
        break;
    case 21:
        str << L"Antler Trophy";
        break;
    case 22:
        str << L"Trophy";
        break;
    case 23:
        str << L"Bookcase";
        break;
    case 24:
        str << L"Shut Trap Door";
        break;
    case 25:
        str << L"Open Trap Door";
        break;
    case 26:
        str << L"Barrel";
        break;
    case 27:
        str << L"Rug";
        break;
    case 28:
        str << L"Acg Shield";
        break;
    case 29:
        str << L"Shield";
        break;
    case 30:
        str << L"Knight";
        break;
    case 32:
        str << L"Shut Normal Door";
        break;
    case 33:
        str << L"Open Normal Door";
        break;
    case 34:
        str << L"Shut Cave Door";
        break;
    case 35:
        str << L"Open Cave Door";
        break;
    case 36:
        str << L"Acg Exit Door";
        break;
    case 37:
        str << L"Picture";
        break;
    case 38:
        str << L"Skeleton";
        break;
    case 39:
        str << L"Barrels";
        break;
    default:
        str << L"?";
        break;
    } // Endswitch.

    return (str.str ());
} // Endproc.


std::wstring    DescribeFlags (BYTE byFlags)
{

    // Table always 0x?4.
    // Skelton alway 0x?1.
    // Picure may be 0x?1.
    // Trophy may be 0x?1.

    static  const   BYTE    ROTATE_MASK     = 0xc0;

    static  const   BYTE    ROTATE_TOP      = 0x00;  
    static  const   BYTE    ROTATE_RIGHT    = 0x40;  
    static  const   BYTE    ROTATE_BOTTOM   = 0x80;  
    static  const   BYTE    ROTATE_LEFT     = 0xc0;

    std::wostringstream str;
    str << L"0x" << std::hex << std::setw (2) << std::setfill (L'0') << static_cast<int> (byFlags) << L" (";

    if ((byFlags & ROTATE_RIGHT) == ROTATE_RIGHT)
    {
        str << L"Right";
    } // Endif.

    else
    if ((byFlags & ROTATE_BOTTOM) == ROTATE_BOTTOM)
    {
        str << L"Bottom";
    } // Endelseif.

    else
    if ((byFlags & ROTATE_LEFT) == ROTATE_LEFT)
    {
        str << L"Left";
    } // Endelseif.

    else
    {
        str << L"Top";
    } // Endelse.

    str << L')';

    return (str.str ());
} // Endproc.


bool    IsBackgroundItemAttrib (WORD    wAddress, 
                                BYTE    &byGraphicType)
{
    static  WORD    BackgroundItemAttribs [] = 
    {
	    0xA7DE,     // 01 CaveDooor Frame 
        0xA7D0,     // 02 Normal Door Frame
        0xB4AC,     // 03 Big Door Frame
        0xAEEA,     
	    0xAEEA,     
        0xAEEA,     
        0xAEEA,     
        0xA6FE,     // 08 Red Locked Normal Door
	    0xA70C,     // 09 Green Locked Normal Door
        0xA71A,     // 10 Cyan Locked Normal Door
        0xA728,     // 11 Yellow Locked Normal Door
        0xA736,     // 12 Red Locked Cave Door
	    0xA744,     // 13 Green Locked Cave Door
        0xA752,     // 14 Cyan Locked Cave Door
        0xA760,     // 15 Yellow Locked Cave Door
        0xB774,     // 16 Clock
	    0xB528,     // 17 Picture
        0xA846,     // 18 Table
        0xAEEA,     // 19 Full Chicken
        0xAEEA,     // 20 Chicken Carcass
	    0xC960,     // 21 Antler Trophy
        0xC96A,     // 22 Trophy
        0xC970,     // 23 Bookcase
        0xC998,     // 24 Shut Trap Door
	    0xC986,     // 25 Open Trap Door
        0xD057,     // 26 Barrel
        0xC9AA,     // 27 Rug
        0xCA50,     // 28 Acg Shield
	    0xCA56,     // 29 Shield
        0xCA5C,     // 30 Knight
        0xAEEA,     
        0xCA74,     // 32 Shut Normal Door
	    0xA7D0,     // 33 Open Normal Door
        0xCA66,     // 34 Shut Cave Door
        0xA7DE,     // 35 Open Cave Door
        0xD1AB,     // 36 Acg Exit Door
	    0xD295,     // 37 Picture
        0xD3B8,     // 38 Skeleton
        0xD4EF,     // 39 Barrels
    };

    for (byGraphicType = 0; byGraphicType < (sizeof (BackgroundItemAttribs) / sizeof (WORD)); ++byGraphicType)
    {
        if (BackgroundItemAttribs [byGraphicType] == wAddress)
        {
            byGraphicType++; // Start from 1. 

            return (true);
        } // Endif.

    } // Endfor.

    return (false);
} // Endfor.


int wmain (int argc, WCHAR* argv[])
{
    int nReturnCode = 0;

    if (argc == 2)
    {
        DataList    fileData;
        DWORD   dwin32Error = ReadFile (argv [1], fileData);

        if (dwin32Error == ERROR_SUCCESS)
        {
            bool    bFinished   = false;    // Initialise!
            bool    bFoundData  = false;
            BYTE    byByte      = 0;

            WORD    dwStartAddress  = 0xa69c;
            UINT    uiByteCount     = 0;

            DataList::const_iterator itr = fileData.begin ();

            while (!bFinished && (itr != fileData.end ()))
            {
                if (bFoundData)
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
                        byByte *= 16;
                        byByte += *itr - '0';
                        ++itr;
                        break;

                    case 'a':
                    case 'b':
                    case 'c':
                    case 'd':
                    case 'e':
                    case 'f':
                        byByte *= 16;
                        byByte += *itr - 'a' + 10;
                        ++itr;
                        break;

                    case 'A':
                    case 'B':
                    case 'C':
                    case 'D':
                    case 'E':
                    case 'F':
                        byByte *= 16;
                        byByte += *itr - 'A' + 10;
                        ++itr;
                       break;

                    case 'h':
                    case 'H':
                        if ((uiByteCount % 16) == 0)
                        {
                            ::wprintf (L"\n%04.04X   ", dwStartAddress + uiByteCount);
                        } // Endif.

                        ::wprintf (L"%02.02X ", byByte);

                        uiByteCount++;

                        byByte = 0;
                        ++itr;
                        break;

                    case ' ':
                    case ',':
                        ++itr;
                        break;

                    case '\r':
                    case '\n':
                    case '\t':
                    default:
                        bFoundData  = false;
                        byByte      = 0;
                        break;                                
                    } // Endswitch.

                } // Endif.

                else
                if (((*itr == 'D') || (*itr == 'd')) &&
                   (((itr + 1) != fileData.end ()) && ((*(itr + 1) == 'B') || (*(itr + 1) == 'b'))) &&
                   (((itr + 2) != fileData.end ()) && ((*(itr + 2) == ' '))))
                {
                    bFoundData = true;

                    itr += 3;
                } // Endelseif.

                else
                {
                    ++itr;
                } // Endelse.

            } // Endwhile.

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
