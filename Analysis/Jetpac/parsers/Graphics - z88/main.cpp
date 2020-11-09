#include "stdafx.h"
#include "CharacterSprite.h"
#include "Main.h"
#include "Utils.h"


unsigned char mirror(unsigned char b) 
{
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}

int wmain (int argc, WCHAR* argv[])
{
    int nReturnCode = 0;

#define _FROM_BMP_ 1
#ifdef _FROM_BMP_
    if (argc >= 2)
    {
        bool    bMirror = (argv [1][0] == L'm');
        bool    bJetman = (argv [1][0] == L'j');
        bool    bRocket = (argv [1][0] == L'r');

        UINT    uiNumFiles = bMirror || bJetman || bRocket ? argc - 2 : argc - 1;
        UINT    firstFile  = bMirror || bJetman || bRocket ? 2 : 1;

        ULONG_PTR   lpGdiToken = NULL;

        Utils::GdiStatus    gdiStatus = Utils::RegisterGdi (lpGdiToken);

        if (gdiStatus == Gdiplus::Ok)
        {
            bool    bError = false;

            BYTE    bySpriteWidthInPixels   = 0;
            BYTE    bySpriteHeightInPixels  = 0;

            std::wstring    spriteName;
            Utils::DataList pixelData;

            for (UINT uiFile = 0; !bError && (uiFile < uiNumFiles); ++uiFile)
            {
                BYTE    byWidthInPixels  = 0;
                BYTE    byHeightInPixels = 0;
                if (Utils::LoadBitmap (argv [uiFile + firstFile], byWidthInPixels, byHeightInPixels, pixelData))
                {
                    std::wstring    fileName(Utils::SplitPath (argv [uiFile + firstFile], false, false, true, false));

                    if (uiFile == 0)
                    {
                        bySpriteWidthInPixels   = byWidthInPixels;
                        bySpriteHeightInPixels  = byHeightInPixels;

                        std::wistringstream fileNameStr(fileName);
                        WORD    wStartAddress   = 0;
                        WORD    wEndAddress     = 0;
                        fileNameStr >> std::setw(4) >> std::hex >> wStartAddress;
                        fileNameStr.ignore (1);
                        fileNameStr >> std::setw(4) >> std::hex >> wEndAddress;

                        spriteName = CharacterSprite::DescribeCharacterSprite2 (bJetman, bRocket, wStartAddress, wEndAddress);
                    } // Endif.

                    else
                    if ((bySpriteWidthInPixels != byWidthInPixels) ||
                        (bySpriteHeightInPixels != byHeightInPixels))
                    {
                        printf ("Bitmap %ws dimensions don't match expected. ExpectedWidth=%u vs %u. ExpectedHeight=%u vs %u\n",
                                 fileName.c_str (),
                                 bySpriteWidthInPixels, byWidthInPixels,
                                 bySpriteHeightInPixels, byHeightInPixels);

                        bError = true;
                    } // Endelse.

                } // Endif.

                else
                {
                    printf ("Failed to load bitmap %ws.\n", argv [uiFile + firstFile]);

                    bError = true;
                } // Endelse.

            } // Endfor.

            if (!bError)
            {
                if (bMirror)
                {
                    Utils::DataList mirrorPixelData;

                    BYTE    bySpriteWidthInBytes = bySpriteWidthInPixels / 8;

                    for (WORD wFrame = 0; wFrame < argc - 2; ++wFrame)
                    {
                        for (WORD wHeight = 0; wHeight < bySpriteHeightInPixels; ++wHeight)
                        {
                            for (int wWidth = bySpriteWidthInBytes - 1; wWidth >=0; --wWidth)
                            {
                                BYTE    byByte = pixelData [wFrame * bySpriteWidthInBytes * bySpriteHeightInPixels + wHeight * bySpriteWidthInBytes + wWidth];
                                mirrorPixelData.push_back (mirror(byByte)); 
                            } // Endfor.

                        } // Endfor.

                    } // Endfor.

                    pixelData.insert (pixelData.end (), mirrorPixelData.begin (), mirrorPixelData.end ());
                } // Endif.

                CharacterSprite::SaveSprite3 (bySpriteWidthInPixels / 8,
                                              bySpriteHeightInPixels,
                                              pixelData,
                                              spriteName,
                                              bMirror,
                                              bJetman,
                                              bRocket);
            } // Endif.

            Utils::DeregisterGdi (lpGdiToken);
        } // Endif.

    } // Endif.

    else
    {
        printf ("Feed me a bitmap to decode.\n");

        nReturnCode = 1;
    } // Endelse.
#else
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
        printf ("Feed me a uiFile name to parse.\n");

        nReturnCode = 1;
    } // Endelse.
#endif

    return (nReturnCode);
} // Endproc.

/******************************* End of File *******************************/
