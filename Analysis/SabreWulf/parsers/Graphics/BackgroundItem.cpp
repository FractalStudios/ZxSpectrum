#include "stdafx.h"
#include "BackgroundItem.h"
#include "Main.h"

void    ParseBackgroundItems (const Utils::DataList &fileData,
                              BackgroundItemList    &backgroundItemList,
                              AddressMap            &addressMap)
{
    BackgroundItem      currentBackgroundItem;

    enum PARSE
    {
        BACKGROUND_ITEM_SPRITE_HEIGHT,
        BACKGROUND_ITEM_SPRITE_WIDTH,
        BACKGROUND_ITEM_SPRITE_DATA,
        BACKGROUND_ITEM_ATTRIB_HEIGHT,
        BACKGROUND_ITEM_ATTRIB_WIDTH,
        BACKGROUND_ITEM_ATTRIB_DATA,
    }; // Endenum.

    PARSE   currentParse = BACKGROUND_ITEM_SPRITE_HEIGHT;

    bool    bFinished   = false;    // Initialise!
    bool    bFoundData  = false;
    BYTE    byByte      = 0;

    WORD    wAddress = 0x70bc;  // Start Address

    UINT    attribScale = 1;

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

            case ',':
            case '\r':
                if (addressMap.find (wAddress) == addressMap.end ())
                {
                    addressMap [wAddress] = AddressDetails(wAddress, byByte);
                }

                switch (currentParse)
                {
                case BACKGROUND_ITEM_SPRITE_HEIGHT:
                    if (wAddress == 0xe3a0)
                        attribScale = 2;

                    addressMap [wAddress].m_type    = AddressDetails::BACKGROUND_ITEM;
                    addressMap [wAddress].m_bKnown  = true;
                                                                
                    currentBackgroundItem.m_wAddress                = wAddress;
                    currentBackgroundItem.m_bySpriteHeightInPixels  = byByte;
                        
                    currentParse = BACKGROUND_ITEM_SPRITE_WIDTH;
                    break;

                case BACKGROUND_ITEM_SPRITE_WIDTH:
                    addressMap [wAddress].m_type    = AddressDetails::BACKGROUND_ITEM;
                    addressMap [wAddress].m_bKnown = true;

                    currentBackgroundItem.m_bySpriteWidth   = byByte;

                    currentParse = BACKGROUND_ITEM_SPRITE_DATA;
                    break;

                case BACKGROUND_ITEM_SPRITE_DATA:
                    addressMap [wAddress].m_type    = AddressDetails::BACKGROUND_ITEM;
                    addressMap [wAddress].m_bKnown = true;
                    
                    currentBackgroundItem.m_spriteData.push_back (byByte);

                    if (currentBackgroundItem.IsSpriteDataFinished ())
                    {
                        currentParse = BACKGROUND_ITEM_ATTRIB_HEIGHT;
                    } // Endif.
                    break;

                case BACKGROUND_ITEM_ATTRIB_HEIGHT:
                    addressMap [wAddress].m_type    = AddressDetails::BACKGROUND_ITEM;
                    addressMap [wAddress].m_bKnown  = true;
                                                                
                    currentBackgroundItem.m_byAttribHeight  = byByte;
                    currentBackgroundItem.m_byAttribHeight  *= attribScale;
                        
                    currentParse = BACKGROUND_ITEM_ATTRIB_WIDTH;
                    break;

                case BACKGROUND_ITEM_ATTRIB_WIDTH:
                    addressMap [wAddress].m_type    = AddressDetails::BACKGROUND_ITEM;
                    addressMap [wAddress].m_bKnown = true;

                    currentBackgroundItem.m_byAttribWidth   = byByte;

                    currentParse = BACKGROUND_ITEM_ATTRIB_DATA;
                    break;

                case BACKGROUND_ITEM_ATTRIB_DATA:
                    addressMap [wAddress].m_type    = AddressDetails::BACKGROUND_ITEM;
                    addressMap [wAddress].m_bKnown = true;
                    
                    currentBackgroundItem.m_attribData.push_back (byByte);

                    if (currentBackgroundItem.IsAttribDataFinished ())
                    {
                        backgroundItemList.push_back (currentBackgroundItem);

                        currentBackgroundItem.Reset ();

                        currentParse = BACKGROUND_ITEM_SPRITE_HEIGHT;

                        if (wAddress == 0x9691)
                            wAddress = 0xe1eb;
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
            case '#':
                ++itr;
                break;

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

    std::sort (backgroundItemList.begin (), backgroundItemList.end ());

    #ifndef _GRAPHICS_ONLY_
    ::wprintf (L"Background Item Sprites\n");
    ::wprintf (L"=======================\n");

    for (BackgroundItemList::const_iterator itr = backgroundItemList.begin ();
         itr != backgroundItemList.end ();
         ++itr)
    {
        ::wprintf (L"%s, Address = 0x%04.04x, Width = %u, HeightInPixels = %u, SpriteData = %s\n",
                    DescribeBackgroundItem (itr->m_wAddress).c_str (),
                    itr->m_wAddress,
                    itr->m_bySpriteWidth, 
                    itr->m_bySpriteHeightInPixels,
                    Utils::DescribeData (itr->m_spriteData).c_str ());
    } // Endfor.
    #else
    for (BackgroundItemList::const_iterator itr = backgroundItemList.begin ();
         itr != backgroundItemList.end ();
         ++itr)
    {           
        itr->SaveSprite ();
    } // Endfor.
    #endif
} // Endproc.

/******************************* End of File *******************************/
