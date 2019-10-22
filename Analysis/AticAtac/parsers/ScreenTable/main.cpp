#include "stdafx.h"
#include "File.h"

static  const   WORD    START_ADDRESS = 0xa854;

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

struct Screen
{
    Screen ()
    :   m_wAddress(0),
        m_byScreenColour(0),
        m_byScreenType(0)
    {} // Endproc.

    void    Reset ()
    {
        m_wAddress          = 0;
        m_byScreenColour    = 0;
        m_byScreenType      = 0;
    } // Endproc.

    WORD    m_wAddress;
    BYTE    m_byScreenColour;
    BYTE    m_byScreenType;
};

typedef std::vector<Screen> ScreenList;

int wmain (int argc, WCHAR* argv[])
{
    int nReturnCode = 0;

    if (argc == 2)
    {
        DataList    fileData;
        DWORD   dwin32Error = ReadFile (argv [1], fileData);

        if (dwin32Error == ERROR_SUCCESS)
        {
            ScreenList  screenList;
            Screen  currentScreen;

            enum PARSE
            {
                SCREEN_COLOUR = 0,
                SCREEN_TYPE,
            }; // Endenum.

            PARSE   currentParse = SCREEN_COLOUR;

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
                        case SCREEN_COLOUR:
                            addressMap [wAddress].m_bKnown = true;
                            
                            currentScreen.m_wAddress        = wAddress;
                            currentScreen.m_byScreenColour  = byByte;
                            currentParse = SCREEN_TYPE;
                            break;

                        case SCREEN_TYPE:
                            addressMap [wAddress].m_bKnown = true;
                            
                            currentScreen.m_byScreenType = byByte;
                            currentParse = SCREEN_COLOUR;

                            if ((currentScreen.m_byScreenColour == 0) &&
                                (currentScreen.m_byScreenType   == 0))
                            {
                                bFinished = true;
                            } // Endif

                            else
                            {
                                screenList.push_back (currentScreen);

                                currentScreen.Reset ();
                            } // Endelse.
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

            for (ScreenList::const_iterator itr = screenList.begin ();
                 itr != screenList.end ();
                 ++itr)
            {
                ::wprintf (L"Screen %03.03u, Address = 0x%04.04x, Colour = %s%s, Type = %u\n", 
                           itr - screenList.begin (),
                           itr->m_wAddress,
                           DescribeAttribute (itr->m_byScreenColour).c_str (), 
                           DescribeColour (itr->m_byScreenColour).c_str (), 
                           itr->m_byScreenType);
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
