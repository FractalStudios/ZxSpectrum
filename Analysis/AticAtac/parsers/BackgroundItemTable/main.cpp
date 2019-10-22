#include "stdafx.h"
#include "File.h"


static  const   WORD    START_ADDRESS = 0x645d;

struct AddressDetails
{
    AddressDetails ()
    :   m_wAddress(0),
        m_byByte(0),
        m_bKnown(false)
    {} // Endproc.

    AddressDetails (WORD    wAddress,
                    BYTE    byByte)
    :   m_wAddress(wAddress),
        m_byByte(byByte),
        m_bKnown(false)
    {} // Endproc.

    WORD    m_wAddress;
    BYTE    m_byByte;
    bool    m_bKnown;
}; // Endstruct.

typedef std::map<WORD, AddressDetails> AddressMap;

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
        _asm {int 3};
        break;
    } // Endswitch.

    return (str.str ());
} // Endproc.


std::wstring    DescribeFlags (BYTE byFlags)
{
    static  const   BYTE    ROTATE_MASK     = 0xc0;

    static  const   BYTE    ROTATE_TOP      = 0x00;  
    static  const   BYTE    ROTATE_RIGHT    = 0x40;  
    static  const   BYTE    ROTATE_BOTTOM   = 0x80;  
    static  const   BYTE    ROTATE_LEFT     = 0xc0;

    std::wostringstream str;
    str << L"0x" << std::hex << std::setw (2) << std::setfill (L'0') << static_cast<int> (byFlags) << L" (";

    BYTE    byOrientation = byFlags & ROTATE_MASK;

    switch (byOrientation)
    {
    case ROTATE_RIGHT:
        str << L"Right";
        break;
    case ROTATE_BOTTOM:
        str << L"Bottom";
        break;
    case ROTATE_LEFT:
        str << L"Left";
        break;
    default:
        str << L"Top";
        break;
    } // Endswitch.

    str << L')';

    return (str.str ());
} // Endproc.


struct Background
{
    Background ()
    :   m_wAddress(0),
        m_byGraphicType(0),
        m_byScreen(0),
        m_byDoorUnknown1(0),
        m_byXPosition(0),
        m_byYPosition(0),
        m_byFlags(0),
        m_byDoorTiming(0),
        m_byDoorUnknown2(0)
    {} // Endproc.

    void    Reset ()
    {
        m_wAddress          = 0;
        m_byGraphicType     = 0;
        m_byScreen          = 0;
        m_byDoorUnknown1    = 0;
        m_byXPosition       = 0;
        m_byYPosition       = 0;
        m_byFlags           = 0;
        m_byDoorTiming      = 0;
        m_byDoorUnknown2    = 0;
    } // Endproc.

    WORD    m_wAddress;
    BYTE    m_byGraphicType;
    BYTE    m_byScreen;
    BYTE    m_byDoorUnknown1;
    BYTE    m_byXPosition;
    BYTE    m_byYPosition;
    BYTE    m_byFlags;
    BYTE    m_byDoorTiming;
    BYTE    m_byDoorUnknown2;
};

typedef std::vector<Background> BackgroundList;

int wmain (int argc, WCHAR* argv[])
{
    int nReturnCode = 0;

    if (argc == 2)
    {
        DataList    fileData;
        DWORD   dwin32Error = ReadFile (argv [1], fileData);

        if (dwin32Error == ERROR_SUCCESS)
        {
            BackgroundList  backgroundList;
            Background  currentBackground;

            enum PARSE
            {
                GRAPHIC_TYPE = 0,
                SCREEN,
                DOOR_UNKNOWN1,
                X_POSITION,
                Y_POSITION,
                FLAGS,
                DOOR_TIMING,
                DOOR_UNKNOWN2,
            }; // Endenum.

            PARSE   currentParse = GRAPHIC_TYPE;

            bool    bFinished   = false;    // Initialise!
            bool    bFoundData  = false;
            BYTE    byByte      = 0;

            WORD    wAddress = START_ADDRESS;

            AddressMap  addressMap;

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
                        addressMap [wAddress] = AddressDetails(wAddress, byByte);

                        switch (currentParse)
                        {
                        case GRAPHIC_TYPE:
                            addressMap [wAddress].m_bKnown = true;

                            currentBackground.m_wAddress      = wAddress;
                            currentBackground.m_byGraphicType = byByte;
                            currentParse = SCREEN;
                            break;

                        case SCREEN:
                            addressMap [wAddress].m_bKnown = true;
                            
                            currentBackground.m_byScreen = byByte;
                            currentParse = DOOR_UNKNOWN1;

                            if ((currentBackground.m_byGraphicType  == 0) &&
                                (currentBackground.m_byScreen       == 0))
                            {
                                bFinished = true;
                            } // Endif
                            break;

                        case DOOR_UNKNOWN1:
                            addressMap [wAddress].m_bKnown = true;
                            
                            currentBackground.m_byDoorUnknown1 = byByte;
                            currentParse = X_POSITION;
                            break;

                        case X_POSITION:
                            addressMap [wAddress].m_bKnown = true;
                            
                            currentBackground.m_byXPosition = byByte;
                            currentParse = Y_POSITION;
                            break;

                        case Y_POSITION:
                            addressMap [wAddress].m_bKnown = true;
                            
                            currentBackground.m_byYPosition = byByte;
                            currentParse = FLAGS;
                            break;

                        case FLAGS:
                            addressMap [wAddress].m_bKnown = true;
                            
                            currentBackground.m_byFlags = byByte;
                            currentParse = DOOR_TIMING;
                            break;

                        case DOOR_TIMING:
                            addressMap [wAddress].m_bKnown = true;
                            
                            currentBackground.m_byDoorTiming = byByte;
                            currentParse = DOOR_UNKNOWN2;
                            break;

                        case DOOR_UNKNOWN2:
                            addressMap [wAddress].m_bKnown = true;
                            
                            currentBackground.m_byDoorUnknown2 = byByte;
                            currentParse = GRAPHIC_TYPE;

                            backgroundList.push_back (currentBackground);
                            currentBackground.Reset ();
                            break;

                        default:
                            _asm {int 3};
                            break;
                        } // Endswitch.

                        wAddress++;

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

            for (BackgroundList::const_iterator itr = backgroundList.begin ();
                 itr != backgroundList.end ();
                 ++itr)
            {
                ::wprintf (L"Background Item %03.03u, Address = 0x%04.04x, GraphicType = %s, Screen=%03.03u, DoorUnknown1=0x%02.02x, X=%u, Y=%u, Flags=%s, DoorTiming=%u, DoorUnknown2=0x%02.02x, \n", 
                           itr - backgroundList.begin (),
                           itr->m_wAddress,
                           DescribeGraphic (itr->m_byGraphicType).c_str (),
                           itr->m_byScreen,
                           itr->m_byDoorUnknown1,
                           itr->m_byXPosition,
                           itr->m_byYPosition,
                           DescribeFlags (itr->m_byFlags).c_str (),
                           itr->m_byDoorTiming,
                           itr->m_byDoorUnknown2);
            } // Endfor.

            std::ostringstream  str;

            for (AddressMap::const_iterator itr = addressMap.begin ();
                 itr != addressMap.end ();
                 ++itr)
            {
                if (!itr->second.m_bKnown)
                {
                    std::cout << "0x" << std::hex << std::setfill('0') << std::setw(4) << static_cast<int> (itr->first) << ',' 
                              << "0x" << std::hex << std::setfill('0') << std::setw(2) << static_cast<int> (itr->second.m_byByte)
                              << std::endl;
                } // Endif.

            } // Endfor.

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
