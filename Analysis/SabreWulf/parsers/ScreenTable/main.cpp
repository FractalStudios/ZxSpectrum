#include "stdafx.h"
#include "File.h"

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

struct BackgroundItem
{
    BackgroundItem ()
    :   m_wAddress(0),
        m_byXPos(0),
        m_byYPos(0)
    {} // Endproc.

    void    Reset ()
    {
        m_wAddress  = 0;
        m_byXPos    = 0;
        m_byYPos    = 0;
    } // Endproc.

    WORD    m_wAddress;
    BYTE    m_byXPos;
    BYTE    m_byYPos;
};

typedef std::vector<BackgroundItem> BackgroundItemList;

struct Screen
{
    Screen ()
    :   m_wAddress(0),
        m_byScreenNumber(-1)
    {} // Endproc.

    void    Reset ()
    {
        m_wAddress          = 0;
        m_byScreenNumber    = -1;
        m_backgroundItemList.clear ();
    } // Endproc.

    WORD                m_wAddress;
    BYTE                m_byScreenNumber;
    BackgroundItemList  m_backgroundItemList;
};

typedef std::vector<Screen> ScreenList;


UINT    GetScreenNumber (WORD wAddress)
{
    typedef std::vector<WORD>   ScreenAddress;
    
    // Screen table at 0x6166
    ScreenAddress   s_screenAddress = 
    {
        0x6200, 0x624A, 0x6294, 0x62DE, 0x6330, 0x6376, 0x63D0, 0x6422,
        0x647C, 0x64CA, 0x6520, 0x6586, 0x65C0, 0x6616, 0x666C, 0x66B2,
        0x671C, 0x6786, 0x67E8, 0x681E, 0x6864, 0x68B2, 0x68FC, 0x693A,
        0x6988, 0x69DE, 0x6A38, 0x6A7E, 0x6AC4, 0x6B1A, 0x6B70, 0x6BBA,
        0x6C08, 0x6C66, 0x6CBC, 0x6D0E, 0x6D58, 0x6DB2, 0x6E10, 0x6E5E,
        0x6EA0, 0x6EEE, 0x6F34, 0x6F6E, 0x6FB0, 0x6FF2, 0x7030, 0x7076,
    };

    ScreenAddress::iterator itr = std::find (s_screenAddress.begin (), s_screenAddress.end (), wAddress);

    if (itr != s_screenAddress.end ())
    {
        return (std::distance (s_screenAddress.begin (), itr));
    }

    return (-1);
}


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
                SCREEN_BACKGROUND_ITEM_ADDRESS = 0,
                SCREEN_BACKGROUND_ITEM_POS,
            }; // Endenum.

            PARSE   currentParse = SCREEN_BACKGROUND_ITEM_ADDRESS;

            bool    bFinished   = false;    // Initialise!
            bool    bFoundData  = false;
            WORD    wWord      = 0;

            WORD    wAddress = 0x6200;

            BackgroundItem  currentBackgroundItem;

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
                        wWord *= 16;
                        wWord += *itr - '0';
                        ++itr;
                        break;

                    case 'a':
                    case 'b':
                    case 'c':
                    case 'd':
                    case 'e':
                    case 'f':
                        wWord *= 16;
                        wWord += *itr - 'a' + 10;
                        ++itr;
                        break;

                    case 'A':
                    case 'B':
                    case 'C':
                    case 'D':
                    case 'E':
                    case 'F':
                        wWord *= 16;
                        wWord += *itr - 'A' + 10;
                        ++itr;
                       break;

                    case ',':
                    case '\r':
                        addressMap [wAddress    ] = AddressDetails(wAddress, HIBYTE(wWord));
                        addressMap [wAddress + 1] = AddressDetails(wAddress, LOBYTE(wWord));

                        switch (currentParse)
                        {
                        case SCREEN_BACKGROUND_ITEM_ADDRESS:
                            addressMap [wAddress    ].m_bKnown = true;
                            addressMap [wAddress + 1].m_bKnown = true;
                                 
                            if (wWord == 0)
                            {
                                screenList.push_back (currentScreen);

                                currentScreen.Reset ();
                            }

                            else
                            {
                                if (currentScreen.m_wAddress == 0)
                                {
                                    currentScreen.m_wAddress = wAddress;
                                    currentScreen.m_byScreenNumber = GetScreenNumber (wAddress);
                                } 

                                currentBackgroundItem.m_wAddress = wWord;

                                currentParse = SCREEN_BACKGROUND_ITEM_POS;
                            }
                            break;

                        case SCREEN_BACKGROUND_ITEM_POS:
                            addressMap [wAddress    ].m_bKnown = true;
                            addressMap [wAddress + 1].m_bKnown = true;
                            
                            currentBackgroundItem.m_byXPos = LOBYTE(wWord);
                            currentBackgroundItem.m_byYPos = HIBYTE(wWord);

                            currentScreen.m_backgroundItemList.push_back (currentBackgroundItem);

                            currentBackgroundItem.Reset ();

                            currentParse = SCREEN_BACKGROUND_ITEM_ADDRESS;
                            break;

                        default:
                            _asm {int 3};
                            break;
                        } // Endswitch.

                        wAddress += 2;

                        wWord = 0;
                        ++itr;
                        break;

                    case ' ':
                    case '#':
                        ++itr;
                        break;

                    case '\n':
                    case '\t':
                    default:
                        bFoundData  = false;
                        wWord      = 0;
                        break;                                
                    } // Endswitch.

                } // Endif.

                else
                if (((*itr == 'D') || (*itr == 'd')) &&
                   (((itr + 1) != fileData.end ()) && ((*(itr + 1) == 'W') || (*(itr + 1) == 'w'))) &&
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
                ::wprintf (L"Screen %02.02u, Address = 0x%04.04x, BackgroundItems = ", 
                           itr->m_byScreenNumber,
                           itr->m_wAddress);

                for (BackgroundItemList::const_iterator backgroundItemItr = itr->m_backgroundItemList.begin ();
                     backgroundItemItr != itr->m_backgroundItemList.end ();
                     ++backgroundItemItr)
                {
                    ::wprintf (L"{0x%04.04x (%03.03u %03.03u)} ", 
                               backgroundItemItr->m_wAddress,
                               backgroundItemItr->m_byXPos,
                               backgroundItemItr->m_byYPos);
                } // Endfor.

                ::wprintf (L"\n");
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
