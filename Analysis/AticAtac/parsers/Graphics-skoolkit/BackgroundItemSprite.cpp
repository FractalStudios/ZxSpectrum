#include "stdafx.h"
#include "BackgroundItemSprite.h"
#include "Main.h"

bool    IsBackgroundItemSprite (WORD wAddress, WORD &wIndex)
{
    // Background Item Sprite Table 0xA600.

    static  WORD    BackgroundItemSprites [] = 
    {
        0xBCCE, // 01 Cave Door Frame.  
        0xA76E, // 02 Normal Door Frame.
        0xB3EA, // 03 Big Door Frame.
        0xA69C, // 08 Red Locked Normal Door.
	    0xA69C, // 09 Green Locked Normal Door.
        0xA69C, // 10 Cyan Locked Normal Door.
        0xA69C, // 11 Yellow Locked Normal Door.
        0xC2AE, // 12 Red Locked Cave Door.
	    0xC2AE, // 13 Green Locked Cave Door.
        0xC2AE, // 14 Cyan Locked Cave Door.
        0xC2AE, // 15 Yellow Locked Cave Door.
        0xB6F2, // 16 Clock.
	    0xB4C6, // 17 Picture.
        0xA7EC, // 18 Table.
        0xC542, // 19 Full Chicken.
        0xC48C, // 20 Chicken Carcass.
	    0xC66A, // 21 Antler Trophy.
        0xC6AC, // 22 Trophy.
        0xC6CE, // 23 Bookcase.
        0xC7F2, // 24 Shut Trap Door.
	    0xC770, // 25 Open Trap Door.
        0xCFD5, // 26 Barrel.
        0xC874, // 27 Rug.
        0xC9CA, // 28 Acg Shield.
	    0xC9EC, // 29 Shield.
        0xCA0E, // 30 Knight.
        0xCA82, // 32 Shut Normal Door.
	    0xA76E, // 33 Open Normal Door.
        0xCAE4, // 34 Shut Cave Door.
        0xBCCE, // 35 Open Cave Door.
        0xD069, // 36 Acg Exit Door.
	    0xD253, // 37 Picture.
        0xD2EE, // 38 Skeleton.
        0xD466, // 39 Barrels.
    };

    for (WORD wSprite = 0; wSprite < (sizeof (BackgroundItemSprites) / sizeof (WORD)); ++wSprite)
    {
        if (BackgroundItemSprites [wSprite] == wAddress)
        {
            wIndex = wSprite;

            return (true);
        } // Endif.

    } // Endfor.

    return (false);
} // Endfor.


std::wstring    DescribeBackgroundItemSprite (WORD wAddress, bool bStripWhiteSpace, WORD wAttribAddress)
{
    std::wostringstream str;

    switch (wAddress)
    {
    case 0xBCCE:
        str << L"Cave Door Frame";
        break;
    case 0xA76E:
        str << L"Normal Door Frame";
        break;
    case 0xB3EA:
        str << L"Big Door Frame";
        break;
    case 0xA69C:
        switch (wAttribAddress)
        {
        case 0xA6FE:
            str << L"Red Locked Normal Door";
            break;
        case 0xA70C:
            str << L"Green Locked Normal Door";
            break;
        case 0xA71A:
            str << L"Cyan Locked Normal Door";
            break;
        case 0xA728:
            str << L"Yellow Locked Normal Door";
            break;
        default:
            str << L"Locked Normal Door";
            break;
        } // Endswitch.
        break;
    case 0xC2AE:
        switch (wAttribAddress)
        {
        case 0xA736:
            str << L"Red Locked Cave Door";
            break;
        case 0xA744:
            str << L"Green Locked Cave Door";
            break;
        case 0xA752:
            str << L"Cyan Locked Cave Door";
            break;
        case 0xA760:
            str << L"Yellow Locked Cave Door";
            break;
        default:
            str << L"Locked Cave Door";
            break;
        } // Endswitch.
        break;
    case 0xB6F2:
        str << L"Clock";
        break;
    case 0xB4C6:
        str << L"Picture";
        break;
    case 0xA7EC:
        str << L"Table";
        break;
    case 0xC542:
        str << L"Full Chicken";
        break;
    case 0xC48C:
        str << L"Chicken Carcass";
        break;
    case 0xC66A:
        str << L"Antler Trophy";
        break;
    case 0xC6AC:
        str << L"Trophy";
        break;
    case 0xC6CE:
        str << L"Bookcase";
        break;
    case 0xC7F2:
        str << L"Shut Trap Door";
        break;
    case 0xC770:
        str << L"Open Trap Door";
        break;
    case 0xCFD5:
        str << L"Barrel";
        break;
    case 0xC874:
        str << L"Rug";
        break;
    case 0xC9CA:
        str << L"Acg Shield";
        break;
    case 0xC9EC:
        str << L"Shield";
        break;
    case 0xCA0E:
        str << L"Knight";
        break;
    case 0xCA82:
        str << L"Shut Normal Door";
        break;
    case 0xCAE4:
        str << L"Shut Cave Door";
        break;
    case 0xD069:
        str << L"Acg Exit Door";
        break;
    case 0xD253:
        str << L"Picture 2";
        break;
    case 0xD2EE:
        str << L"Skeleton";
        break;
    case 0xD466:
        str << L"Barrels";
        break;
    default:
        str << L"Unknown";
        break;
    } // Endswitch.

    std::wstring    description(str.str ());

    if (bStripWhiteSpace)
    {
        description.erase (std::remove(description.begin (), description.end(), L' '), description.end());
    } // Endif.

    return (description);
} // Endproc.


void    ParseBackgroundItemSprites (const Utils::DataList           &fileData,
                                    const BackgroundItemAttribList  &backgroundItemAttribList,
                                    BackgroundItemSpriteList        &backgroundItemSpriteList,
                                    AddressMap                      &addressMap)
{
    BackgroundItemSprite      currentBackgroundItemSprite;
    BackgroundItemSpriteList  currentBackgroundItemSprites;

    enum PARSE
    {
        BACKGROUND_ITEM_SPRITE_WIDTH = 0,
        BACKGROUND_ITEM_SPRITE_HEIGHT,
        BACKGROUND_ITEM_SPRITE_SPRITE_DATA,
    }; // Endenum.

    PARSE   currentParse = BACKGROUND_ITEM_SPRITE_WIDTH;

    bool    bFinished   = false;    // Initialise!
    bool    bFoundData  = false;
    BYTE    byByte      = 0;
    WORD    wIndex      = 0;

    WORD    wAddress = START_ADDRESS;

    Utils::DataList::const_iterator itr = fileData.begin ();

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
                if (addressMap.find (wAddress) == addressMap.end ())
                {
                    addressMap [wAddress] = AddressDetails(wAddress, byByte);
                }

                switch (currentParse)
                {
                case BACKGROUND_ITEM_SPRITE_WIDTH:
                    if (IsBackgroundItemSprite (wAddress, wIndex))
                    {                   
                        addressMap [wAddress].m_type    = AddressDetails::BACKGROUND_ITEM_SPRITE;
                        addressMap [wAddress].m_bKnown  = true;

                        currentBackgroundItemSprite.m_wAddress  = wAddress;
                        currentBackgroundItemSprite.m_wIndex    = wIndex;
                        currentBackgroundItemSprite.m_byWidth   = byByte;
                        currentParse = BACKGROUND_ITEM_SPRITE_HEIGHT;
                    } // Endif.
                    break;

                case BACKGROUND_ITEM_SPRITE_HEIGHT:
                    addressMap [wAddress].m_type    = AddressDetails::BACKGROUND_ITEM_SPRITE;
                    addressMap [wAddress].m_bKnown = true;
                    
                    currentBackgroundItemSprite.m_byHeightInPixels = byByte;

                    if ((currentBackgroundItemSprite.m_byWidth          == 0) ||
                        (currentBackgroundItemSprite.m_byHeightInPixels == 0))
                    {
                        backgroundItemSpriteList.push_back (currentBackgroundItemSprite);

                        currentBackgroundItemSprite.Reset ();

                        currentParse = BACKGROUND_ITEM_SPRITE_WIDTH;
                    } // Endif.

                    else
                    {
                        currentParse = BACKGROUND_ITEM_SPRITE_SPRITE_DATA;
                    } // Endelse.
                    break;

                case BACKGROUND_ITEM_SPRITE_SPRITE_DATA:
                    addressMap [wAddress].m_type    = AddressDetails::BACKGROUND_ITEM_SPRITE;
                    addressMap [wAddress].m_bKnown = true;
                    
                    currentBackgroundItemSprite.m_spriteData.push_back (byByte);

                    if (currentBackgroundItemSprite.IsFinished ())
                    {
                        backgroundItemSpriteList.push_back (currentBackgroundItemSprite);

                        currentBackgroundItemSprite.Reset ();

                        currentParse = BACKGROUND_ITEM_SPRITE_WIDTH;
                    } // Endif.
                    break;

                default:
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
                ++itr;
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

    std::sort (backgroundItemSpriteList.begin (), backgroundItemSpriteList.end ());
} // Endproc.

/******************************* End of File *******************************/
