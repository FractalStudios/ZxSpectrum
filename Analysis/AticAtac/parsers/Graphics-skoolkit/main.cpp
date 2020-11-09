#include "stdafx.h"
#include "BackgroundItemAttrib.h"
#include "BackgroundItemSprite.h"
#include "CharacterSprite.h"
#include "Font.h"
#include "Main.h"
#include "Utils.h"

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


std::wstring    DumpAddressMap (AddressMap &addressMap, AddressMap::iterator &itrAddressMap, bool bUnused = true)
{
    std::wostringstream str;

    if (bUnused)
    {
        str << L"; Unused data at " << DescribeWORD (itrAddressMap->first) << std::endl
            << L"@label=UnusedDataAt" << DescribeWORD (itrAddressMap->first) << std::endl;
    } // Endif.

    DWORD   dwDataIndex = 0;

    while ((itrAddressMap != addressMap.end ())                         &&
           (itrAddressMap->first <= 0xD5FF)                             &&
           (!bUnused || (bUnused && !IsFont (itrAddressMap->first)))    &&
           ((itrAddressMap->second.m_type == AddressDetails::BACKGROUND_ITEM_ATTRIBUTE) ||
            (itrAddressMap->second.m_type == AddressDetails::FONT)                      ||
            (itrAddressMap->second.m_type == AddressDetails::UNKNOWN)))
    {
        if (!(dwDataIndex % 8))
        {
            if (!dwDataIndex)
            {
                if (bUnused)
                {
                    str << L"u";
                } // Endif.

                else
                {
                    str << L"b";
                } // Endelse.

            } // Endif.

            else
            {
                str << L" ";
            } // Endelse.

            str << DescribeWORD (itrAddressMap->first) 
                << L" DEFB ";
        } // Endif.

        else
        {
            str << L",";
        } // Endelse.
                
        str << DescribeBYTE (itrAddressMap->second.m_byByte);

        if (!((dwDataIndex + 1) % 8))
        {
            str << std::endl;
        } // Endelse.

        dwDataIndex++;
        itrAddressMap++;
    } // Endfor.
        
    str << std::endl << std::endl;

    return (str.str ());
} // Endproc.


std::wstring    BuildSklText (const CharacterSpriteList         &characterSpriteList, 
                              const BackgroundItemAttribList    &backgroundItemAttribList,
                              const BackgroundItemSpriteList    &backgroundItemSpriteList,
                              const FontList                    &fontList,
                              AddressMap                        &addressMap)
{
    std::wostringstream str;

    Utils::DataList graphicTypes;
    WORD    wIndex = 0;

    AddressMap::iterator itrAddressMap = addressMap.begin ();

    while (itrAddressMap != addressMap.end () && (itrAddressMap->first <= 0xD5FF)) 
    {
        if (IsCharacterSprite (itrAddressMap->first, wIndex))
        {
            CharacterSpriteList::const_iterator itr(std::find (characterSpriteList.begin (), 
                                                               characterSpriteList.end (), 
                                                               itrAddressMap->first));

            str << L"; Sprite: " << DescribeCharacterSprite (itr->m_wAddress, false) << std::endl
                << L";" << std::endl
                << L"; This sprite is 2 bytes wide." << std::endl
                << L"; ." << std::endl;

            str << L"; #UDGTABLE" << std::endl
                << L"; {" << std::endl
                << L"; #UDGARRAY" << itr->m_byWidth << L",$07,4," << itr->m_byWidth << L",,2";

            for (WORD wDataAddress = (itr->m_wAddress + 1); 
                    wDataAddress < (itr->m_wAddress + 1 + itr->m_byWidth * itr->m_byHeightInPixels); 
                    wDataAddress += (itr->m_byWidth * 8))
            {
                str << L";" << DescribeWORD (wDataAddress) << L"-" << DescribeWORD (wDataAddress + itr->m_byWidth - 1); 
            } // Endfor.

            if (itr->m_byHeightInPixels % 8)
            {
                str << L"{," << 8 - (itr->m_byHeightInPixels % 8) << L"*4}";
            } // Endif.

            str << L"(" << DescribeCharacterSprite (itr->m_wAddress, true) << L")" << std::endl
                << L"; }" << std::endl
                << L"; TABLE#" << std::endl;
        
            str << L"@label=Sprite" << DescribeCharacterSprite (itr->m_wAddress, true) << std::endl
                << L"b" << DescribeWORD (itr->m_wAddress) 
                << L" DEFB " << DescribeBYTE (itr->m_byHeightInPixels) << L"                             ;  Height (in pixels).";

            itrAddressMap++;

            bool    bOpenedComment = false;

            for (DWORD dwDataIndex = 0; dwDataIndex < static_cast<DWORD> (itr->m_byWidth * itr->m_byHeightInPixels); ++dwDataIndex)
            {
                if (!(dwDataIndex % 8))
                {
                    str << std::endl << L" " << DescribeWORD (itr->m_wAddress + 1 + static_cast<WORD> (dwDataIndex)) << L" DEFB ";
                } // Endif
                
                str << DescribeBYTE (itr->m_spriteData [dwDataIndex]);

                if (((dwDataIndex + 1) % 8) && 
                    ((dwDataIndex + 1) != (itr->m_byWidth * itr->m_byHeightInPixels)))
                {
                    str << L",";
                } // Endif

                else
                if (!bOpenedComment)
                {
                    str << L" ; { Graphic data.";

                    bOpenedComment = true;
                } // Endelseif.

                else
                if ((dwDataIndex + 1) == (itr->m_byWidth * itr->m_byHeightInPixels))
                {
                    if ((itr->m_byWidth * itr->m_byHeightInPixels) % 8)
                    {
                        for (int i = 0; i < 8 - (itr->m_byWidth * itr->m_byHeightInPixels) % 8; ++i)
                        {
                            str << L"    ";
                        } // Endfor.

                    } // Endif.

                    str << L" ; }";
                } // Endelseif.

                else
                {
                    str << L" ;";
                } // Endelse.

                itrAddressMap++;
            } // Endfor.

            str << std::endl << std::endl;
        } // Endif.

        else
        if (IsBackgroundItemSprite (itrAddressMap->first, wIndex))
        {
            BackgroundItemSpriteList::const_iterator itr(std::find (backgroundItemSpriteList.begin (), 
                                                                    backgroundItemSpriteList.end (), 
                                                                    itrAddressMap->first));

            str << L"; Sprite: " << DescribeBackgroundItemSprite (itr->m_wAddress, false) << std::endl
                << L";" << std::endl
                << L"; #UDGTABLE" << std::endl
                << L"; {" << std::endl;

            BackgroundItemAttribList    newbackgroundItemAttribList(FindBackgroundItemAttrib (itr->m_wAddress, backgroundItemAttribList));

            if (newbackgroundItemAttribList.empty ())
            {
                str << L"; #UDGARRAY" << itr->m_byWidth << L",$07,4," << itr->m_byWidth << L",,2";

                for (WORD wDataAddress = (itr->m_wAddress + 2); 
                     wDataAddress < (itr->m_wAddress + 2 + itr->m_byWidth * itr->m_byHeightInPixels); 
                     wDataAddress += (itr->m_byWidth * 8))
                {
                    str << L";" << DescribeWORD (wDataAddress) << L"-" << DescribeWORD (wDataAddress + itr->m_byWidth - 1); 
                } // Endfor.

                if (itr->m_byHeightInPixels % 8)
                {
                    str << L"{," << 8 - (itr->m_byHeightInPixels % 8) << L"*4}";
                } // Endif.

                str << L"(" << DescribeBackgroundItemSprite (itr->m_wAddress, true) << L")" << std::endl;
            } // Endif.

            else
            {
                for (BackgroundItemAttribList::const_iterator itrNewbackgroundItemAttribList = newbackgroundItemAttribList.begin ();
                     itrNewbackgroundItemAttribList != newbackgroundItemAttribList.end (); 
                     ++itrNewbackgroundItemAttribList )
                {
                    str << L"; #UDGARRAY" << itr->m_byWidth << L",,4," << itr->m_byWidth << L",,2";

                    for (WORD wDataAddress = (itr->m_wAddress + 2); 
                         wDataAddress < (itr->m_wAddress + 2 + itr->m_byWidth * itr->m_byHeightInPixels); 
                         wDataAddress += (itr->m_byWidth * 8))
                    {
                        str << L";" << DescribeWORD (wDataAddress) << L"-" << DescribeWORD (wDataAddress + itr->m_byWidth - 1); 
                    } // Endfor.

                    str << L"@" << DescribeWORD (itrNewbackgroundItemAttribList->m_wAddress + 2) << L"-" << DescribeWORD (itrNewbackgroundItemAttribList->m_wAddress + 2 + itrNewbackgroundItemAttribList->m_byWidth * itrNewbackgroundItemAttribList->m_byHeight - 1); 

                    if (itr->m_byHeightInPixels % 8)
                    {
                        str << L"{," << 8 - (itr->m_byHeightInPixels % 8) << L"*4}";
                    } // Endif.

                    str << L"(" << DescribeBackgroundItemSprite (itr->m_wAddress, true, itrNewbackgroundItemAttribList->m_wAddress) << L")" << std::endl;
                } // Endfor.

            } // Endelse.

            str << L"; }" << std::endl
                << L"; TABLE#" << std::endl
                << L"@label=Sprite" << DescribeBackgroundItemSprite (itr->m_wAddress, true) << std::endl
                << L"b" << DescribeWORD (itr->m_wAddress) 
                << L" DEFB " << DescribeBYTE (itr->m_byWidth) << L"                             ;  Width (in bytes)." << std::endl
                << L" " << DescribeWORD (itr->m_wAddress + 1) 
                << L" DEFB " << DescribeBYTE (itr->m_byHeightInPixels) << L"                             ;  Height (in pixels).";

            itrAddressMap++;
            itrAddressMap++;

            bool    bOpenedComment = false;

            for (DWORD dwDataIndex = 0; dwDataIndex < static_cast<DWORD> (itr->m_byWidth * itr->m_byHeightInPixels); ++dwDataIndex)
            {
                if (!(dwDataIndex % 8))
                {
                    str << std::endl << L" " << DescribeWORD (itr->m_wAddress + 2 + static_cast<WORD> (dwDataIndex)) << L" DEFB ";
                } // Endif
                
                str << DescribeBYTE (itr->m_spriteData [dwDataIndex]);

                if (((dwDataIndex + 1) % 8) && 
                    ((dwDataIndex + 1) != (itr->m_byWidth * itr->m_byHeightInPixels)))
                {
                    str << L",";
                } // Endif

                else
                if (!bOpenedComment)
                {
                    str << L" ; { Graphic data.";

                    bOpenedComment = true;
                } // Endelseif.

                else
                if ((dwDataIndex + 1) == (itr->m_byWidth * itr->m_byHeightInPixels))
                {
                    if ((itr->m_byWidth * itr->m_byHeightInPixels) % 8)
                    {
                        for (int i = 0; i < 8 - (itr->m_byWidth * itr->m_byHeightInPixels) % 8; ++i)
                        {
                            str << L"    ";
                        } // Endfor.

                    } // Endif.

                    str << L" ; }";
                } // Endelseif.

                else
                {
                    str << L" ;";
                } // Endelse.

                itrAddressMap++;
            } // Endfor.

            str << std::endl << std::endl;
        } // Endelseif.

        else
        if (IsBackgroundItemAttrib (itrAddressMap->first, wIndex))
        {
            BackgroundItemAttribList::const_iterator    itr(std::find (backgroundItemAttribList.begin (), 
                                                                       backgroundItemAttribList.end (), 
                                                                       itrAddressMap->first));

            str << L"; Attributes: " << DescribeBackgroundItemAttrib (itr->m_wAddress, false) << std::endl;
        
            str << L"@label=Attrib" << DescribeBackgroundItemAttrib (itr->m_wAddress, true) << std::endl
                << L"b" << DescribeWORD (itr->m_wAddress) 
                << L" DEFB " << DescribeBYTE (itr->m_byWidth) << L"                             ;  Width (in bytes)." << std::endl
                << L" " << DescribeWORD (itr->m_wAddress + 1) 
                << L" DEFB " << DescribeBYTE (itr->m_byHeight) << L"                             ;  Height (in bytes).";

            itrAddressMap++;
            itrAddressMap++;

            bool    bOpenedComment = false;

            for (DWORD dwDataIndex = 0; dwDataIndex < static_cast<DWORD> (itr->m_byWidth * itr->m_byHeight); ++dwDataIndex)
            {
                if (!(dwDataIndex % 8))
                {
                    str << std::endl << L" " << DescribeWORD (itr->m_wAddress + 2 + static_cast<WORD> (dwDataIndex)) << L" DEFB ";
                } // Endif
                
                str << DescribeBYTE (itr->m_colourData [dwDataIndex]);

                if (((dwDataIndex + 1) % 8) && 
                    ((dwDataIndex + 1) != (itr->m_byWidth * itr->m_byHeight)))
                {
                    str << L",";
                } // Endif

                else
                if (!bOpenedComment)
                {
                    str << L" ; { Colour attribute data.";

                    bOpenedComment = true;
                } // Endelseif.

                else
                if ((dwDataIndex + 1) == (itr->m_byWidth * itr->m_byHeight))
                {
                    if ((itr->m_byWidth * itr->m_byHeight) % 8)
                    {
                        for (int i = 0; i < 8 - (itr->m_byWidth * itr->m_byHeight) % 8; ++i)
                        {
                            str << L"    ";
                        } // Endfor.

                    } // Endif.

                    str << L" ; }";
                } // Endelseif.

                else
                {
                    str << L" ;";
                } // Endelse.

                itrAddressMap++;
            } // Endfor.

            str << std::endl << std::endl;
        } // Endelseif.

        else
        if (IsFont (itrAddressMap->first))
        {
            str << L"; Font" << std::endl
                << L";" << std::endl;

            str << L"; #UDGTABLE" << std::endl
                << L"; {" << std::endl;

            for (FontList::const_iterator itrFontList = fontList.begin ();
                 itrFontList != fontList.end ();
                 ++itrFontList)
            {
                str << L"; #UDG" << DescribeWORD (itrFontList->m_wAddress) << L",$47" << L"(" << L"Font" << DescribeWORD (itrFontList->m_wAddress) << L")" << std::endl;
            } // Endif.

            str << L"; }" << std::endl
                << L"; TABLE#" << std::endl;
        
            str << L"@label=Font" << std::endl;

            str << DumpAddressMap (addressMap, itrAddressMap, false);
        } // Endelseif.

        else
        if (itrAddressMap->first == 0xA854)
        {
            str << L"; Screen Table" << std::endl
                << L";" << std::endl;

            str << L"; #TABLE(default)" << std::endl
                << L"; { =h Offset   | =h Field              | =h Description }" << std::endl
                << L"; { $00         | Colour Attribute      | Colour attribute. }" << std::endl
                << L"; { $01         | Screen Type           | Screen type. }" << std::endl
                << L"; TABLE#" << std::endl;

            str << L"@label=ScreenTable" << std::endl
                << L"b";

            for (int i = 0; i < 149; ++i)
            {
                if (i)
                {
                    str << L" ";
                } // Endif.

                str << DescribeWORD (itrAddressMap->first)
                    << L" DEFB " << DescribeBYTE (itrAddressMap->second.m_byByte);
                itrAddressMap++;
                
                str << L"," << DescribeBYTE (itrAddressMap->second.m_byByte) << L" ; Screen " << DescribeBYTE (i) << L"." << std::endl;
                itrAddressMap++;
            } // Endfor.

            str << std::endl;
        } // Endelseif.

        else
        if (itrAddressMap->first == 0xAEEA)
        {
            str << L"; Sprite: " << L"Unused" << std::endl
                << L";" << std::endl
                << L"; Unused sprite." << std::endl;

            str << L"@label=Sprite" << L"Unused" << std::endl
                << L"b" << DescribeWORD (itrAddressMap->first) 
                << L" DEFB " << DescribeBYTE (itrAddressMap->second.m_byByte) << L"                             ;  Width (in bytes)." << std::endl;
            itrAddressMap++;

            str << L" " << DescribeWORD (itrAddressMap->first) 
                << L" DEFB " << DescribeBYTE (itrAddressMap->second.m_byByte) << L"                             ;  Height (in pixels)."
                << std::endl << std::endl;

            itrAddressMap++;
        } // Endelseif.

        else
        if (itrAddressMap->first == 0xB03A)
        {
            BYTE    byWidth             = 8;
            BYTE    byHeightInPixels    = 118;

            str << L"; Status Panel Graphic" << std::endl;
            str << L"@label=" << "StatusPanel" << std::endl;

            bool    bOpenedComment = false;

            for (DWORD dwDataIndex = 0; dwDataIndex < static_cast<DWORD> (byWidth * byHeightInPixels); ++dwDataIndex)
            {
                if (dwDataIndex == 0)
                {
                    str << L"b" << DescribeWORD (itrAddressMap->first) << L" DEFB ";
                } // Endif.

                else
                if (!(dwDataIndex % 8))
                {

                    str << std::endl << L" " << DescribeWORD (itrAddressMap->first) << L" DEFB ";
                } // Endif
                
                str << DescribeBYTE (itrAddressMap->second.m_byByte);

                if (((dwDataIndex + 1) % 8) && 
                    ((dwDataIndex + 1) != (byWidth * byHeightInPixels)))
                {
                    str << L",";
                } // Endif

                else
                if (!bOpenedComment)
                {
                    str << L" ; { Graphic data.";

                    bOpenedComment = true;
                } // Endelseif.

                else
                if ((dwDataIndex + 1) == (byWidth * byHeightInPixels))
                {
                    if ((byWidth * byHeightInPixels) % 8)
                    {
                        for (int i = 0; i < 8 - (byWidth * byHeightInPixels) % 8; ++i)
                        {
                            str << L"    ";
                        } // Endfor.

                    } // Endif.

                    str << L" ; }";
                } // Endelseif.

                else
                {
                    str << L" ;";
                } // Endelse.

                itrAddressMap++;
            } // Endfor.

            str << std::endl << std::endl;
        } // Endelseif.

        //else
        //if (itrAddressMap->first == 0xB3BA)
        //{
        //    BYTE    byWidth             = 3;
        //    BYTE    byHeightInPixels    = 6;

        //    WORD    wNumBytes = 48;

        //    str << L"; Rosette Graphic" << std::endl
        //        << L";" << std::endl;

        //    str << L"; #UDGTABLE" << std::endl
        //        << L"; {" << std::endl
        //        << L"; #UDGARRAY" << byWidth << L",$07,4,8,,";

        //    str << L";" << DescribeWORD (itrAddressMap->first) << L"-" << DescribeWORD (itrAddressMap->first + wNumBytes - 1); 

        //    str << L"(" << L"Rosette" << L")" << std::endl
        //        << L"; }" << std::endl
        //        << L"; TABLE#" << std::endl;
        //
        //    str << L"@label=" << "Rosette" << std::endl;

        //    bool    bOpenedComment = false;

        //    for (DWORD dwDataIndex = 0; dwDataIndex < static_cast<DWORD> (wNumBytes); ++dwDataIndex)
        //    {
        //        if (dwDataIndex == 0)
        //        {
        //            str << L"b" << DescribeWORD (itrAddressMap->first) << L" DEFB ";
        //        } // Endif.

        //        else
        //        if (!(dwDataIndex % 8))
        //        {

        //            str << std::endl << L" " << DescribeWORD (itrAddressMap->first) << L" DEFB ";
        //        } // Endif
        //        
        //        str << DescribeBYTE (itrAddressMap->second.m_byByte);

        //        if (((dwDataIndex + 1) % 8) && 
        //            ((dwDataIndex + 1) != (byWidth * byHeightInPixels)))
        //        {
        //            str << L",";
        //        } // Endif

        //        else
        //        if (!bOpenedComment)
        //        {
        //            str << L" ; { Graphic data.";

        //            bOpenedComment = true;
        //        } // Endelseif.

        //        else
        //        if ((dwDataIndex + 1) == (byWidth * byHeightInPixels))
        //        {
        //            if ((byWidth * byHeightInPixels) % 8)
        //            {
        //                for (int i = 0; i < 8 - (byWidth * byHeightInPixels) % 8; ++i)
        //                {
        //                    str << L"    ";
        //                } // Endfor.

        //            } // Endif.

        //            str << L" ; }";
        //        } // Endelseif.

        //        else
        //        {
        //            str << L" ;";
        //        } // Endelse.

        //        itrAddressMap++;
        //    } // Endfor.

        //    str << std::endl << std::endl;
        //} // Endelseif.

        else
        {
            str << DumpAddressMap (addressMap, itrAddressMap);
        } // Endelse.

    } // Endfor.

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
                AddressMap  addressMap;

                BackgroundItemAttribList  backgroundItemAttribList;
                ParseBackgroundItemAttribs (fileData, backgroundItemAttribList, addressMap);

                BackgroundItemSpriteList  backgroundItemSpriteList;
                ParseBackgroundItemSprites (fileData, backgroundItemAttribList, backgroundItemSpriteList, addressMap);
                
                FontList  fontList;
                ParseFonts (fileData, fontList, addressMap);

                CharacterSpriteList characterSpriteList;
                ParseCharacterSprites (fileData, characterSpriteList, addressMap);

                std::string text(Utils::WideStringToNarrowString (BuildSklText (characterSpriteList, 
                                                                                backgroundItemAttribList ,
                                                                                backgroundItemSpriteList,
                                                                                fontList,
                                                                                addressMap)));

                Utils::WriteFile (L"aticatic.skl", Utils::DataList(text.begin (), text.end ()));
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
