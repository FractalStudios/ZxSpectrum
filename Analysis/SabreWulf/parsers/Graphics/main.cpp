#include "stdafx.h"
#include "BackgroundItem.h"
#include "Font.h"
#include "CharacterSprite.h"
#include "Main.h"
#include "Utils.h"

std::wstring    DescribeBackgroundItem (WORD wAddress)
{
    std::wostringstream str;
    str << std::setw (4) << std::setfill (L'0') << std::hex << static_cast<int> (wAddress);

    return (str.str ());
} // Endproc.


int wmain (int argc, WCHAR* argv[])
{
    int nReturnCode = 0;

    if (argc == 3)
    {
        Utils::DataList fileData;
        DWORD   dwin32Error = Utils::ReadFile (argv [1], fileData);

        if (dwin32Error == ERROR_SUCCESS)
        {
            ULONG_PTR   lpGdiToken = NULL;

            Utils::GdiStatus    gdiStatus = Utils::RegisterGdi (lpGdiToken);

            if (gdiStatus == Gdiplus::Ok)
            {
                AddressMap  addressMap;

                FontList             fontList;
                ParseFonts (fileData, fontList, addressMap);

                ExitProcess (0);

                if (::_wcsicmp (argv [2], L"b") == 0)
                {
                    BackgroundItemList  backgroundItemList;
                    ParseBackgroundItems (fileData, backgroundItemList, addressMap);
                } // Endif.

                else
                {
                    CharacterSpriteList characterSpriteList;
                    ParseCharacterSprites (fileData, characterSpriteList, addressMap);
                } // Endelse.

                AddressDetails  addressDetails;

                AddressMap::const_iterator itrStart = addressMap.begin ();

                std::ostringstream  str;

                for (AddressMap::const_iterator itr = addressMap.begin ();
                     itr != addressMap.end ();
                     ++itr)
                {
                    if (addressDetails.m_wAddress == 0)
                    {
                        addressDetails = itr->second;
                        itrStart = itr;
                    } // Endif.

                    else
                    if (addressDetails.m_type != itr->second.m_type)
                    {
                        std::cout << AddressDetails::DescribeType (addressDetails.m_type) << ',' 
                                    << std::hex << std::setfill('0') << std::setw(4) << static_cast<int> (addressDetails.m_wAddress) << ',' 
                                    << std::hex << std::setfill('0') << std::setw(4) << static_cast<int> (itr->first - 1) << ',' 
                                    << std::dec << static_cast<int> (itr->first - addressDetails.m_wAddress) << ','; 

                        if (!addressDetails.m_bKnown)
                        {
                            for (;itrStart != itr; ++itrStart)
                            {
                                std::cout << " 0x" << std::hex << std::setfill('0') << std::setw(2) << static_cast<int> (itrStart->second.m_byByte);
                            } // Endfor.

                        } // Endif.

                        std::cout << std::endl;

                        addressDetails = itr->second;
                        itrStart = itr;
                    } // Endif.


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
