#include "stdafx.h"
#include "File.h"


static  const   WORD    START_ADDRESS = 0x76a9;


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


DWORD   WriteFile (const std::wstring   &filePath,
                   const DataList       &fileData)
{
    // Open the file for writing.

    Utils::File    file;

    DWORD   dwWin32Error = file.Create (filePath, 
                                        GENERIC_WRITE,
                                        FILE_SHARE_READ | FILE_SHARE_WRITE,
                                        CREATE_ALWAYS);

    if ((dwWin32Error == ERROR_SUCCESS) ||
        (dwWin32Error == ERROR_ALREADY_EXISTS))
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


bool    IsStartScreenBackgroundItems (WORD  wAddress, 
                                      BYTE  &byScreen)
{
    // Screen Background Item Table 0x757D

    static  WORD    ScreenBackgroundItems [] = 
    {
	    0x76A9, 0x76C3, 0x76CD, 0x76D7,
	    0x76E5, 0x76F1, 0x76FB, 0x770D,
	    0x7717, 0x7721, 0x7733, 0x773D,
	    0x7747, 0x7751, 0x775F, 0x776B,
	    0x7775, 0x777D, 0x7787, 0x778F,
	    0x779D, 0x77A7, 0x77B5, 0x77BF,
	    0x77CB, 0x77D9, 0x77E3, 0x77E9,
	    0x77F3, 0x77F9, 0x77FF, 0x7805,
	    0x780D, 0x7815, 0x7821, 0x7829,
	    0x7833, 0x783F, 0x7847, 0x784D,
	    0x785D, 0x7863, 0x7871, 0x787B,
	    0x7885, 0x788B, 0x7899, 0x78A3,
	    0x78A9, 0x78B1, 0x78B7, 0x78BD,
	    0x78C7, 0x78CD, 0x78D5, 0x78DB,
	    0x78E1, 0x78EB, 0x78F1, 0x78F9,
	    0x7903, 0x7909, 0x7915, 0x791D,
	    0x7923, 0x792D, 0x7933, 0x7939,
	    0x7943, 0x7949, 0x794F, 0x7957,
	    0x795D, 0x7967, 0x796D, 0x7973,
	    0x797D, 0x7985, 0x798B, 0x7993,
	    0x7999, 0x79A1, 0x79A7, 0x79AD,
	    0x79B5, 0x79BD, 0x79C5, 0x79D3,
	    0x79DB, 0x79E3, 0x79EB, 0x79F7,
	    0x7A05, 0x7A13, 0x7A1F, 0x7A27,
	    0x7A33, 0x7A3F, 0x7A4B, 0x7A55,
	    0x7A61, 0x7A6B, 0x7A77, 0x7A8B,
	    0x7A91, 0x7A97, 0x7A9D, 0x7AA5,
	    0x7AAD, 0x7AB7, 0x7AC3, 0x7ACF,
	    0x7AD7, 0x7AE1, 0x7AE7, 0x7AED,
	    0x7AF7, 0x7AFD, 0x7B05, 0x7B11,
	    0x7B17, 0x7B1F, 0x7B25, 0x7B33,
	    0x7B39, 0x7B43, 0x7B4D, 0x7B57,
	    0x7B61, 0x7B67, 0x7B6F, 0x7B7B,
	    0x7B81, 0x7B8B, 0x7B91, 0x7B97,
	    0x7BA3, 0x7BAF, 0x7BBB, 0x7BC9,
	    0x7BD3, 0x7BDD, 0x7BEB, 0x7BEF,
	    0x7BF7, 0x7BFD, 0x7C05, 0x7C0B,
	    0x7C11, 0x7C17,
    };

    for (byScreen = 0; byScreen < (sizeof (ScreenBackgroundItems) / sizeof (WORD)); ++byScreen)
    {
        if (ScreenBackgroundItems [byScreen] == wAddress)
        {
            return (true);
        } // Endif

    } // Endfor.

    _asm {int 3};

    return (false);
} // Endfor.


typedef std::vector<WORD>   BackgroundItemAddressList;

struct ScreenBackgroundItems
{
    ScreenBackgroundItems ()
    :   m_wAddress(0)
    {} // Endproc.

    void    Reset ()
    {
        m_wAddress = 0;
        m_backgroundItemAddressList.clear ();
    } // Endproc.

    WORD                        m_wAddress;
    BackgroundItemAddressList   m_backgroundItemAddressList;
};


typedef std::map<BYTE, ScreenBackgroundItems>   ScreenBackgroundItemMap;

std::wstring    DescribeBackgroundItemAddressList (const BackgroundItemAddressList &backgroundItemAddressList)
{
    std::wostringstream str;

    for (BackgroundItemAddressList::const_iterator itr = backgroundItemAddressList.begin ();
         itr != backgroundItemAddressList.end ();
         ++itr)
    {
        str << std::hex << std::setw (4) << std::setfill (L'0') << static_cast<int> (*itr) << L' ';
    } // Endfor.

    return (str.str ());
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


std::wstring    BuildSklText (const ScreenBackgroundItemMap &screenBackgroundItemMap,
                              const AddressMap              &addressMap)
{
    std::wostringstream str;


    str << L"; Screen Background Item Table" << std::endl;
    str << L"@label=ScreenBackgroundItemTable" << std::endl
        << L"b";

    bool bf = true;

    for (ScreenBackgroundItemMap::const_iterator itr = screenBackgroundItemMap.begin ();
         itr != screenBackgroundItemMap.end ();
         ++itr)
    {
        DWORD   dwCount = 0;

        for (BackgroundItemAddressList::const_iterator itrBackgroundItemAddressList = itr->second.m_backgroundItemAddressList.begin ();
             itrBackgroundItemAddressList != itr->second.m_backgroundItemAddressList.end ();
             ++itrBackgroundItemAddressList)
        {
            if (!bf)
            {
                str << L" ";
            } // Endif.

            bf = false;

            str << DescribeWORD (itr->second.m_wAddress + dwCount * 2)
                << L" DEFW "
                << DescribeWORD (*itrBackgroundItemAddressList);

            if (dwCount == 0)
                str << L" ; { Screen " << DescribeBYTE (itr->first) << L"." << std::endl;
            else
                str << L" ;" << std::endl;

            dwCount++;
        } // Endfor.
        
        str << L" " << DescribeWORD (itr->second.m_wAddress + dwCount * 2)
            << L" DEFW $0000"
            << L" ; }" << std::endl;
    } // Endfor.

    return (str.str ());
} // Endproc.


//std::wstring    BuildSklText (const ScreenBackgroundItemMap &screenBackgroundItemMap,
//                              const AddressMap              &addressMap)
//{
//    std::wostringstream str;
//
//
//    str << L"; Screen Background Item Table" << std::endl;
//    str << L"@label=ScreenBackgroundItemTable" << std::endl
//        << L"b";
//
//    for (ScreenBackgroundItemMap::const_iterator itr = screenBackgroundItemMap.begin ();
//         itr != screenBackgroundItemMap.end ();
//         ++itr)
//    {
//        if (itr != screenBackgroundItemMap.begin ())
//        {
//            str << L" ";
//        } // Endif.
//
//        str << DescribeWORD (itr->second.m_wAddress)
//            << L" DEFW ";
//
//        DWORD   dwCount = 0;
//
//        for (BackgroundItemAddressList::const_iterator itrBackgroundItemAddressList = itr->second.m_backgroundItemAddressList.begin ();
//             itrBackgroundItemAddressList != itr->second.m_backgroundItemAddressList.end ();
//             ++itrBackgroundItemAddressList)
//        {
//            if (dwCount % 4)
//            {
//                str << L",";
//            } // Endif.
//
//            str << DescribeWORD (*itrBackgroundItemAddressList);
//
//            dwCount++;
//
//            if (!(dwCount % 4))
//            {
//                if (dwCount == 4)
//                {
//                    str << L" ; { Screen " << DescribeBYTE (itr->first) << L"." << std::endl;
//                } // Endif.
//
//                else
//                {
//                    str << L" ;" << std::endl;
//                } // Endif.
//
//                str << L" " << DescribeWORD (itr->second.m_wAddress + dwCount * 2)
//                    << L" DEFW ";
//            } // Endif.
//
//        } // Endfor.
//        
//        if (dwCount % 4)
//        {
//            str << L",";
//        } // Endif.
//
//        str << L"$0000";
//
//        if (!(dwCount % 4))
//        {
//            for (int i = 0; i < 3; ++i)
//            {
//                str << L"      ";
//            } // Endfor.
//
//        } // Endif.
//
//        else
//        if (dwCount % 4)
//        {
//            for (int i = 0; i < 3 - dwCount % 4; ++i)
//            {
//                str << L"      ";
//            } // Endfor.
//
//        } // Endif.
//
//        if (dwCount <= 3)
//        {
//            str << L" ;   Screen " << DescribeBYTE (itr->first) << L"." << std::endl;
//        }
//        else
//        {
//            str << L" ; }" << std::endl;
//        } // Endelse.
//    } // Endfor.
//
//    return (str.str ());
//} // Endproc.
//
int wmain (int argc, WCHAR* argv[])
{
    int nReturnCode = 0;

    if (argc == 2)
    {
        DataList    fileData;
        DWORD   dwin32Error = ReadFile (argv [1], fileData);

        if (dwin32Error == ERROR_SUCCESS)
        {
            ScreenBackgroundItemMap     screenBackgroundItemMap;
            BackgroundItemAddressList   backgroundItemAddressList;

            BYTE    byScreen = -1;

            bool    bFinished   = false;    // Initialise!
            bool    bFoundData  = false;
            WORD    wWord       = 0;

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

                    case 'h':
                    case 'H':
                        addressMap [wAddress     ] = AddressDetails(wAddress, wWord & 0x00ff);
                        addressMap [wAddress + 1 ] = AddressDetails(wAddress, (wWord & 0xff00) >> 8);

                        if (wWord == 0)
                        {
                            addressMap [wAddress     ].m_bKnown = true;
                            addressMap [wAddress + 1 ].m_bKnown = true;

                            if ((byScreen != 255) && !backgroundItemAddressList.empty ())
                            {
                                screenBackgroundItemMap [byScreen].m_backgroundItemAddressList = backgroundItemAddressList;
                                backgroundItemAddressList.clear ();

                                byScreen = -1;
                            } // Endif.

                        } // Endif.

                        else
                        if (!backgroundItemAddressList.empty ())
                        {
                            addressMap [wAddress     ].m_bKnown = true;
                            addressMap [wAddress + 1 ].m_bKnown = true;

                            backgroundItemAddressList.push_back (wWord);
                        } // Endif.

                        else
                        if (IsStartScreenBackgroundItems (wAddress, 
                                                          byScreen))
                        {
                            addressMap [wAddress     ].m_bKnown = true;
                            addressMap [wAddress + 1 ].m_bKnown = true;

                            screenBackgroundItemMap [byScreen].m_wAddress = wAddress;

                            backgroundItemAddressList.push_back (wWord);
                        } // Endif.

                        wAddress += 2;

                        wWord = 0;
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

            std::string text(WideStringToNarrowString (BuildSklText (screenBackgroundItemMap, addressMap)));

            
            WriteFile (L"aticatic2.skl", DataList(text.begin (), text.end ()));
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
