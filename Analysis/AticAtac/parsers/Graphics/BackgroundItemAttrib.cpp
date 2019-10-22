#include "stdafx.h"
#include "BackgroundItemAttrib.h"
#include "Main.h"

static  bool    IsBackgroundItemAttrib (WORD            wAddress, 
                                        Utils::DataList &graphicTypes)
{
    // Background Item Attribute Table 0xA64E.

    static  WORD    BackgroundItemAttribs [] = 
    {
	    0xA7DE, // 01 Cave Door Frame.
        0xA7D0, // 02 Normal Door Frame.
        0xB4AC, // 03 Big Door Frame.
        0xAEEA, 
	    0xAEEA, 
        0xAEEA, 
        0xAEEA, 
        0xA6FE, // 08 Red Locked Normal Door.
	    0xA70C, // 09 Green Locked Normal Door.
        0xA71A, // 10 Cyan Locked Normal Door.
        0xA728, // 11 Yellow Locked Normal Door.
        0xA736, // 12 Red Locked Cave Door.
	    0xA744, // 13 Green Locked Cave Door.
        0xA752, // 14 Cyan Locked Cave Door.
        0xA760, // 15 Yellow Locked Cave Door.
        0xB774, // 16 Clock.
	    0xB528, // 17 Picture.
        0xA846, // 18 Table.
        0xAEEA, // 19 Full Chicken.
        0xAEEA, // 20 Chicken Carcass.
	    0xC960, // 21 Antler Trophy.
        0xC96A, // 22 Trophy.
        0xC970, // 23 Bookcase.
        0xC998, // 24 Shut Trap Door.
	    0xC986, // 25 Open Trap Door.
        0xD057, // 26 Barrel.
        0xC9AA, // 27 Rug.
        0xCA50, // 28 Acg Shield.
	    0xCA56, // 29 Shield.
        0xCA5C, // 30 Knight.
        0xAEEA, 
        0xCA74, // 32 Shut Normal Door.
	    0xA7D0, // 33 Open Normal Door.
        0xCA66, // 34 Shut Cave Door.
        0xA7DE, // 35 Open Cave Door.
        0xD1AB, // 36 Acg Exit Door.
	    0xD295, // 37 Picture.
        0xD3B8, // 38 Skeleton.
        0xD4EF, // 39 Barrels.
    };

    graphicTypes.clear ();

    for (BYTE byGraphicType = 0; byGraphicType < (sizeof (BackgroundItemAttribs) / sizeof (WORD)); ++byGraphicType)
    {
        if (BackgroundItemAttribs [byGraphicType] == wAddress)
        {
            // Start from 1. 

            graphicTypes.push_back (byGraphicType + 1);
        } // Endif.

    } // Endfor.

    return (!graphicTypes.empty ());
} // Endfor.


void    ParseBackgroundItemAttribs (const Utils::DataList       &fileData,
                                    BackgroundItemAttribList    &backgroundItemAttribList,
                                    AddressMap                  &addressMap)
{
    BackgroundItemAttrib      currentBackgroundItemAttrib;
    BackgroundItemAttribList  currentBackgroundItemAttribs;

    Utils::DataList graphicTypes;
 
    enum PARSE
    {
        BACKGROUND_ITEM_ATTRIB_WIDTH = 0,
        BACKGROUND_ITEM_ATTRIB_HEIGHT,
        BACKGROUND_ITEM_ATTRIB_COLOUR_DATA,
    }; // Endenum.

    PARSE   currentParse = BACKGROUND_ITEM_ATTRIB_WIDTH;

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
                case BACKGROUND_ITEM_ATTRIB_WIDTH:
                    if (IsBackgroundItemAttrib (wAddress, 
                                                graphicTypes))
                    {
                        addressMap [wAddress].m_type   = AddressDetails::BACKGROUND_ITEM_ATTRIBUTE;
                        addressMap [wAddress].m_bKnown = true;

                        currentBackgroundItemAttrib.m_wAddress  = wAddress;
                        currentBackgroundItemAttrib.m_byWidth   = byByte;
                        currentParse = BACKGROUND_ITEM_ATTRIB_HEIGHT;
                    } // Endif.
                    break;

                case BACKGROUND_ITEM_ATTRIB_HEIGHT:
                    addressMap [wAddress].m_type   = AddressDetails::BACKGROUND_ITEM_ATTRIBUTE;
                    addressMap [wAddress].m_bKnown = true;
                    
                    currentBackgroundItemAttrib.m_byHeight = byByte;

                    if ((currentBackgroundItemAttrib.m_byWidth == 0) ||
                        (currentBackgroundItemAttrib.m_byHeight == 0))
                    {
                        for (Utils::DataList::const_iterator graphicTypeItr = graphicTypes.begin ();
                             graphicTypeItr != graphicTypes.end ();
                             ++graphicTypeItr)
                        {
                            currentBackgroundItemAttrib.m_byGraphicType = *graphicTypeItr;
                            backgroundItemAttribList.push_back (currentBackgroundItemAttrib);
                        } // Endfor.

                        graphicTypes.clear ();
                        currentBackgroundItemAttrib.Reset ();

                        currentParse = BACKGROUND_ITEM_ATTRIB_WIDTH;
                    } // Endif.

                    else
                    {
                        currentParse = BACKGROUND_ITEM_ATTRIB_COLOUR_DATA;
                    } // Endelse.
                    break;

                case BACKGROUND_ITEM_ATTRIB_COLOUR_DATA:
                    addressMap [wAddress].m_type   = AddressDetails::BACKGROUND_ITEM_ATTRIBUTE;
                    addressMap [wAddress].m_bKnown = true;
                    
                    currentBackgroundItemAttrib.m_colourData.push_back (byByte);

                    if (currentBackgroundItemAttrib.IsFinished ())
                    {
                        currentBackgroundItemAttrib.ReorderColourData();

                        for (Utils::DataList::const_iterator graphicTypeItr = graphicTypes.begin ();
                             graphicTypeItr != graphicTypes.end ();
                             ++graphicTypeItr)
                        {
                            currentBackgroundItemAttrib.m_byGraphicType = *graphicTypeItr;
                            backgroundItemAttribList.push_back (currentBackgroundItemAttrib);
                        } // Endfor.

                        graphicTypes.clear ();
                        currentBackgroundItemAttrib.Reset ();

                        currentParse = BACKGROUND_ITEM_ATTRIB_WIDTH;
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

    std::sort (backgroundItemAttribList.begin (), backgroundItemAttribList.end ());

    #ifndef _GRAPHICS_ONLY_
    ::wprintf (L"Background Item Attributes\n");
    ::wprintf (L"==========================\n");

    for (BackgroundItemAttribList::const_iterator itr = backgroundItemAttribList.begin ();
         itr != backgroundItemAttribList.end ();
         ++itr)
    {
        ::wprintf (L"%s, Address = 0x%04.04x, Width = %u, Height = %u, ColourData = %s\n",
                    DescribeBackgroundItem (itr->m_byGraphicType).c_str (),
                    itr->m_wAddress,
                    itr->m_byWidth, 
                    itr->m_byHeight,
                    Utils::DescribeData (itr->m_colourData).c_str ()); 
    } // Endfor.
    #endif
} // Endproc.


BackgroundItemAttrib    GetBackgroundItemAttrib (BYTE                           byGraphicType,
                                                 const BackgroundItemAttribList &backgroundItemAttribList)
{
    for (BackgroundItemAttribList::const_iterator itr = backgroundItemAttribList.begin ();
         itr != backgroundItemAttribList.end ();
         ++itr)
    {
        if (itr->m_byGraphicType == byGraphicType)
        {
            return (*itr);
        } // Endif.

    } // Endfor.

    _asm {int 3};
    return (BackgroundItemAttrib ());
} // Endproc.

/******************************* End of File *******************************/
