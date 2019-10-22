#include "stdafx.h"
#include "BackgroundItemSprite.h"
#include "Main.h"

static  bool    IsBackgroundItemSprite (WORD            wAddress, 
                                        Utils::DataList &graphicTypes)
{
    // Background Item Sprite Table 0xA600.

    static  WORD    BackgroundItemSprites [] = 
    {
        0xBCCE, // 01 Cave Door Frame.  
        0xA76E, // 02 Normal Door Frame.
        0xB3EA, // 03 Big Door Frame.
        0xAEEA,
	    0xAEEA, 
        0xAEEA, 
        0xAEEA, 
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
        0xAEEA,
        0xCA82, // 32 Shut Normal Door.
	    0xA76E, // 33 Open Normal Door.
        0xCAE4, // 34 Shut Cave Door.
        0xBCCE, // 35 Open Cave Door.
        0xD069, // 36 Acg Exit Door.
	    0xD253, // 37 Picture.
        0xD2EE, // 38 Skeleton.
        0xD466, // 39 Barrels.
    };

    graphicTypes.clear ();

    for (BYTE byGraphicType = 0; byGraphicType < (sizeof (BackgroundItemSprites) / sizeof (WORD)); ++byGraphicType)
    {
        if (BackgroundItemSprites [byGraphicType] == wAddress)
        {
            // Start from 1. 

            graphicTypes.push_back (byGraphicType + 1);
        } // Endif.

    } // Endfor.

    return (!graphicTypes.empty ());
} // Endfor.


void    ParseBackgroundItemSprites (const Utils::DataList           &fileData,
                                    const BackgroundItemAttribList  &backgroundItemAttribList,
                                    BackgroundItemSpriteList        &backgroundItemSpriteList,
                                    AddressMap                      &addressMap)
{
    BackgroundItemSprite      currentBackgroundItemSprite;
    BackgroundItemSpriteList  currentBackgroundItemSprites;

    Utils::DataList graphicTypes;
 
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
                    if (IsBackgroundItemSprite (wAddress, 
                                                graphicTypes))
                    {                   
                        addressMap [wAddress].m_type    = AddressDetails::BACKGROUND_ITEM_SPRITE;
                        addressMap [wAddress].m_bKnown  = true;

                        currentBackgroundItemSprite.m_wAddress  = wAddress;
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
                        for (Utils::DataList::const_iterator graphicTypeItr = graphicTypes.begin ();
                             graphicTypeItr != graphicTypes.end ();
                             ++graphicTypeItr)
                        {
                            currentBackgroundItemSprite.m_byGraphicType         = *graphicTypeItr;
                            currentBackgroundItemSprite.m_backgroundItemAttrib  = GetBackgroundItemAttrib (*graphicTypeItr, backgroundItemAttribList);

                            backgroundItemSpriteList.push_back (currentBackgroundItemSprite);
                        } // Endfor.

                        graphicTypes.clear ();
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
                        currentBackgroundItemSprite.ReorderSpriteData ();

                        for (Utils::DataList::const_iterator graphicTypeItr = graphicTypes.begin ();
                             graphicTypeItr != graphicTypes.end ();
                             ++graphicTypeItr)
                        {
                            currentBackgroundItemSprite.m_byGraphicType         = *graphicTypeItr;
                            currentBackgroundItemSprite.m_backgroundItemAttrib  = GetBackgroundItemAttrib (*graphicTypeItr, backgroundItemAttribList);
                            
                            backgroundItemSpriteList.push_back (currentBackgroundItemSprite);
                        } // Endfor.

                        graphicTypes.clear ();
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

    #ifndef _GRAPHICS_ONLY_
    ::wprintf (L"Background Item Sprites\n");
    ::wprintf (L"=======================\n");

    for (BackgroundItemSpriteList::const_iterator itr = backgroundItemSpriteList.begin ();
         itr != backgroundItemSpriteList.end ();
         ++itr)
    {
        ::wprintf (L"%s, Address = 0x%04.04x, Width = %u, HeightInPixels = %u, SpriteData = %s\n",
                    DescribeBackgroundItem (itr->m_byGraphicType).c_str (),
                    itr->m_wAddress,
                    itr->m_byWidth, 
                    itr->m_byHeightInPixels,
                    Utils::DescribeData (itr->m_spriteData).c_str ());
    } // Endfor.
    #else
    for (BackgroundItemSpriteList::const_iterator itr = backgroundItemSpriteList.begin ();
         itr != backgroundItemSpriteList.end ();
         ++itr)
    {           
        itr->SaveSprite ();
    } // Endfor.
    #endif
} // Endproc.

/******************************* End of File *******************************/
