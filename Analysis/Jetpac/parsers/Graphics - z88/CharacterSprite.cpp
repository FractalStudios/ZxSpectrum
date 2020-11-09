#include "stdafx.h"
#include "CharacterSprite.h"
#include "Main.h"

void    ParseCharacterSprites (const Utils::DataList    &fileData,
                               CharacterSpriteList      &characterSpriteList,
                               AddressMap               &addressMap)
{
    CharacterSprite     currentCharacterSprite;
    CharacterSpriteList currentCharacterSprites;

    enum PARSE
    {
        CHARACTER_SPRITE_ZERO = 0,
        CHARACTER_SPRITE_WIDTH_IN_BYTES,
        CHARACTER_SPRITE_HEIGHT_IN_PIXELS,
        CHARACTER_SPRITE_SPRITE_DATA,
    }; // Endenum.

    PARSE   currentParse = CHARACTER_SPRITE_ZERO;

    bool    bFinished       = false;    // Initialise!
    bool    bFoundData      = false;
    bool    bNastySprite    = false;
    BYTE    byByte          = 0;
    WORD    wIndex          = 0;

    WORD    wAddress = START_ADDRESS;

    Utils::DataList::const_iterator itr = fileData.begin ();

    int ccount = 0;

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

            case '\r':
            case '\n':
            case ',':
                switch (currentParse)
                {
                case CHARACTER_SPRITE_ZERO:
                    if ((wAddress < 0x7fac) || 
                        (wAddress > 0x7fae))
                    {
                        addressMap [wAddress].m_type    = AddressDetails::CHARACTER_SPRITE;
                        addressMap [wAddress].m_bKnown  = true;

                        currentCharacterSprite.m_wStartAddress  = wAddress;
                        currentCharacterSprite.m_wIndex         = wIndex;
                        currentCharacterSprite.m_byZero         = byByte;

                        currentParse = CHARACTER_SPRITE_WIDTH_IN_BYTES;
                    } // Endif.
                    break;

                case CHARACTER_SPRITE_WIDTH_IN_BYTES:
                    currentCharacterSprite.m_byWidthInBytes = byByte;

                    currentParse = CHARACTER_SPRITE_HEIGHT_IN_PIXELS;
                    break;

                case CHARACTER_SPRITE_HEIGHT_IN_PIXELS:
                    currentCharacterSprite.m_byHeightInPixels = byByte;
                        
                    currentParse = CHARACTER_SPRITE_SPRITE_DATA;
                    break;

                case CHARACTER_SPRITE_SPRITE_DATA:
                    currentCharacterSprite.m_spriteData.push_back (byByte);

                    if (currentCharacterSprite.IsFinished ())
                    {
                        currentCharacterSprite.m_wEndAddress = wAddress;

                        currentCharacterSprite.ReorderSpriteData ();

                        characterSpriteList.push_back (currentCharacterSprite);

                        currentCharacterSprite.Reset ();

                        if ((wAddress == 0x7f8b) ||
                            (wAddress == 0x7bcb))
                        {
                            bNastySprite = false;

                            currentParse = CHARACTER_SPRITE_ZERO;
                        } // Endif

                        else
                        if (bNastySprite || (wAddress == 0x7e9a) || (wAddress == 0x7b9d))
                        {
                            addressMap [wAddress].m_type    = AddressDetails::CHARACTER_SPRITE;
                            addressMap [wAddress].m_bKnown  = true;

                            currentCharacterSprite.m_wStartAddress  = wAddress + 1;
                            currentCharacterSprite.m_wIndex         = wIndex;
                            currentCharacterSprite.m_byZero         = 0;
                            currentCharacterSprite.m_byWidthInBytes = 2;

                            bNastySprite = true;

                            currentParse = CHARACTER_SPRITE_HEIGHT_IN_PIXELS;
                        } // Endif.

                        else
                        {
                            bNastySprite = false;

                            currentParse = CHARACTER_SPRITE_ZERO;
                        } // Endelse.

                    } // Endif.
                    break;

                default:
                    break;
                } // Endswitch.

                wAddress++;

                if ((*itr == '\r') ||
                    (*itr == '\n'))
                {
                    bFoundData  = false;
                } // Endif.

                byByte = 0;
                ++itr;
                break;

            case ' ':
            case '$':
                ++itr;
                break;

            case '\t':
            default:
                bFoundData  = false;
                byByte      = 0;
                ++itr;
                break;                                
            } // Endswitch.

        } // Endif.

        else
        if (((*itr == 'F') || (*itr == 'f')) &&
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

    std::sort (characterSpriteList.begin (), characterSpriteList.end ());

    for (CharacterSpriteList::iterator itr = characterSpriteList.begin ();
         itr != characterSpriteList.end ();
         ++itr)
    {   
        itr->SaveSprite2 ();
        ////if (itr->m_wStartAddress == 0x7cf1)
        ////{
        ////    itr->SaveAnimatedSprite ();
        ////} // Endif.

        //if ((itr->m_wStartAddress == 0x7b9e) ||
        //    (itr->m_wStartAddress == 0x7bb5))
        //{
        //    itr->SaveAnimatedSprite2 ();
        //} // Endif.

    } // Endfor.

} // Endproc.

/******************************* End of File *******************************/
