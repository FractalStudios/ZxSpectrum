#include "stdafx.h"
#include "BackgroundItemAttrib.h"
#include "BackgroundItemSprite.h"
#include "CharacterSprite.h"
#include "Font.h"
#include "Main.h"
#include "Utils.h"

std::wstring    DescribeBackgroundItem (BYTE byGraphicType)
{
    std::wostringstream str;
    str << std::setw (2) << std::setfill (L'0') << static_cast<int> (byGraphicType);

    switch (byGraphicType)
    {
    case 1:
        str << L"CaveDoorFrame";
        break;
    case 2:
        str << L"NormalDoorFrame";
        break;
    case 3:
        str << L"BigDoorFrame";
        break;
    case 8:
        str << L"RedLockedNormalDoor";
        break;
    case 9:
        str << L"GreenLockedNormalDoor";
        break;
    case 10:
        str << L"CyanLockedNormalDoor";
        break;
    case 11:
        str << L"YellowLockedNormalDoor";
        break;
    case 12:
        str << L"RedLockedCaveDoor";
        break;
    case 13:
        str << L"GreenLockedCaveDoor";
        break;
    case 14:
        str << L"CyanLockedCaveDoor";
        break;
    case 15:
        str << L"YellowLockedCaveDoor";
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
        str << L"FullChicken";
        break;
    case 20:
        str << L"ChickenCarcass";
        break;
    case 21:
        str << L"AntlerTrophy";
        break;
    case 22:
        str << L"Trophy";
        break;
    case 23:
        str << L"Bookcase";
        break;
    case 24:
        str << L"ShutTrapDoor";
        break;
    case 25:
        str << L"OpenTrapDoor";
        break;
    case 26:
        str << L"Barrel";
        break;
    case 27:
        str << L"Rug";
        break;
    case 28:
        str << L"AcgShield";
        break;
    case 29:
        str << L"Shield";
        break;
    case 30:
        str << L"Knight";
        break;
    case 32:
        str << L"ShutNormalDoor";
        break;
    case 33:
        str << L"OpenNormalDoor";
        break;
    case 34:
        str << L"ShutCaveDoor";
        break;
    case 35:
        str << L"OpenCaveDoor";
        break;
    case 36:
        str << L"AcgExitDoor";
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
        str << L"Unknown";
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


int wmain (int argc, WCHAR* argv[])
{
    int nReturnCode = 0;

    if (argc == 2)
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

                BackgroundItemAttribList  backgroundItemAttribList;
                ParseBackgroundItemAttribs (fileData, backgroundItemAttribList, addressMap);

                BackgroundItemSpriteList  backgroundItemSpriteList;
                ParseBackgroundItemSprites (fileData, backgroundItemAttribList, backgroundItemSpriteList, addressMap);
                
                FontList  fontList;
                ParseFonts (fileData, fontList, addressMap);

                CharacterSpriteList characterSpriteList;
                ParseCharacterSprites (fileData, characterSpriteList, addressMap);

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
