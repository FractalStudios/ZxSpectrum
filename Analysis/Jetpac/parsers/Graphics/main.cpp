#include "stdafx.h"
#include "CharacterSprite.h"
#include "Main.h"
#include "Utils.h"

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

                //BackgroundItemAttribList  backgroundItemAttribList;
                //ParseBackgroundItemAttribs (fileData, backgroundItemAttribList, addressMap);

                //BackgroundItemSpriteList  backgroundItemSpriteList;
                //ParseBackgroundItemSprites (fileData, backgroundItemAttribList, backgroundItemSpriteList, addressMap);
                
                CharacterSpriteList characterSpriteList;
                ParseCharacterSprites (fileData, characterSpriteList, addressMap);

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
