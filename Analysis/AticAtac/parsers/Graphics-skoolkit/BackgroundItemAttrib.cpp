#include "stdafx.h"
#include "BackgroundItemAttrib.h"
#include "Main.h"

bool    IsBackgroundItemAttrib (WORD wAddress,  WORD &wIndex)
{
    // Background Item Attribute Table 0xA64E.

    static  WORD    BackgroundItemAttribs [] = 
    {
	    0xA7DE, // 01 Cave Door Frame.
        0xA7D0, // 02 Normal Door Frame.
        0xB4AC, // 03 Big Door Frame.
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
        //0xAEEA, // 19 Full Chicken.
        //0xAEEA, // 20 Chicken Carcass.
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
        0xCA74, // 32 Shut Normal Door.
	    0xA7D0, // 33 Open Normal Door.
        0xCA66, // 34 Shut Cave Door.
        0xA7DE, // 35 Open Cave Door.
        0xD1AB, // 36 Acg Exit Door.
	    0xD295, // 37 Picture.
        0xD3B8, // 38 Skeleton.
        0xD4EF, // 39 Barrels.
    };

    for (WORD wAttrib = 0; wAttrib < (sizeof (BackgroundItemAttribs) / sizeof (WORD)); ++wAttrib)
    {
        if (BackgroundItemAttribs [wAttrib] == wAddress)
        {
            wIndex = wAttrib;

            return (true);
        } // Endif.

    } // Endfor.

    return (false);
} // Endfor.


std::wstring    DescribeBackgroundItemAttrib (WORD wAddress, bool bStripWhiteSpace)
{
    std::wostringstream str;

    switch (wAddress)
    {
	case 0xA7DE: str << "Cave Door Frame"; break;
    case 0xA7D0: str << "Normal Door Frame"; break;
    case 0xB4AC: str << "Big Door Frame"; break;
    case 0xA6FE: str << "Red Locked Normal Door"; break;
	case 0xA70C: str << "Green Locked Normal Door"; break;
    case 0xA71A: str << "Cyan Locked Normal Door"; break;
    case 0xA728: str << "Yellow Locked Normal Door"; break;
    case 0xA736: str << "Red Locked Cave Door"; break;
	case 0xA744: str << "Green Locked Cave Door"; break;
    case 0xA752: str << "Cyan Locked Cave Door"; break;
    case 0xA760: str << "Yellow Locked Cave Door"; break;
    case 0xB774: str << "Clock"; break;
	case 0xB528: str << "Picture"; break;
    case 0xA846: str << "Table"; break;
    //case 0xAEEA: str << "Full Chicken"; break;
    //case 0xAEEA: str << "Chicken Carcass"; break;
	case 0xC960: str << "Antler Trophy"; break;
    case 0xC96A: str << "Trophy"; break;
    case 0xC970: str << "Bookcase"; break;
    case 0xC998: str << "Shut Trap Door"; break;
	case 0xC986: str << "Open Trap Door"; break;
    case 0xD057: str << "Barrel"; break;
    case 0xC9AA: str << "Rug"; break;
    case 0xCA50: str << "Acg Shield"; break;
	case 0xCA56: str << "Shield"; break;
    case 0xCA5C: str << "Knight"; break;
    case 0xCA74: str << "Shut Normal Door"; break;
	//case 0xA7D0: str << "Open Normal Door"; break;
    case 0xCA66: str << "Shut Cave Door"; break;
    //case 0xA7DE: str << "Open Cave Door"; break;
    case 0xD1AB: str << "Acg Exit Door"; break;
	case 0xD295: str << "Picture 2"; break;
    case 0xD3B8: str << "Skeleton"; break;
    case 0xD4EF: str << "Barrels"; break;
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


BackgroundItemAttribList    FindBackgroundItemAttrib (WORD                              wAddress, 
                                                      const BackgroundItemAttribList    &backgroundItemAttribList)
{
    std::vector<WORD>   attribAddressList;

    switch (wAddress)
    {
    case 0xBCCE:
        break;
    case 0xA76E:
        attribAddressList.push_back (0xA7D0);
        break;
    case 0xB3EA:
        attribAddressList.push_back (0xB4AC);
        break;
    case 0xA69C:
        attribAddressList.push_back (0xA6FE);
        attribAddressList.push_back (0xA70C);
        attribAddressList.push_back (0xA71A);
        attribAddressList.push_back (0xA728);
        break;
    case 0xC2AE:
        //attribAddressList.push_back (0xA736);
        //attribAddressList.push_back (0xA744);
        //attribAddressList.push_back (0xA752);
        //attribAddressList.push_back (0xA760);
        break;
    case 0xB6F2:
        attribAddressList.push_back (0xB774);
        break;
    case 0xB4C6:
        break;
    case 0xA7EC:
        attribAddressList.push_back (0xA846);
        break;
    case 0xC542:
        break;
    case 0xC48C:
        break;
    case 0xC66A:
        attribAddressList.push_back (0xC960);
        break;
    case 0xC6AC:
        attribAddressList.push_back (0xC96A);
        break;
    case 0xC6CE:
        attribAddressList.push_back (0xC970);
        break;
    case 0xC7F2:
        attribAddressList.push_back (0xC998);
        break;
    case 0xC770:
        attribAddressList.push_back (0xC986);
        break;
    case 0xCFD5:
        attribAddressList.push_back (0xD057);
        break;
    case 0xC874:
        break;
    case 0xC9CA:
        attribAddressList.push_back (0xCA50);
        break;
    case 0xC9EC:
        break;
    case 0xCA0E:
        break;
    case 0xCA82:
        attribAddressList.push_back (0xCA74); 
        break;
    case 0xCAE4:
        //attribAddressList.push_back (0xCA66);
        break;
    case 0xD069:
        attribAddressList.push_back (0xD1AB);
        break;
    case 0xD253:
        attribAddressList.push_back (0xD295);
        break;
    case 0xD2EE:
        //attribAddressList.push_back (0xD3B8);
        break;
    case 0xD466:
        attribAddressList.push_back (0xD4EF);
        break;
    default:
        break;
    } // Endswitch.

    BackgroundItemAttribList    newBackgroundItemAttribList;

    for (std::vector<WORD>::const_iterator itrAddressList = attribAddressList.begin ();
         itrAddressList != attribAddressList.end ();
         ++itrAddressList)
    {
        BackgroundItemAttribList::const_iterator    itr = backgroundItemAttribList.begin ();
    
        for (;
             itr != backgroundItemAttribList.end (); 
             ++itr)
        {
            if (itr->m_wAddress == *itrAddressList)
            {
                newBackgroundItemAttribList.push_back (*itr);
            } // Endif.

        } // Endfor.

    } // Endfor.

    return (newBackgroundItemAttribList);
} // Endproc.


void    ParseBackgroundItemAttribs (const Utils::DataList       &fileData,
                                    BackgroundItemAttribList    &backgroundItemAttribList,
                                    AddressMap                  &addressMap)
{
    BackgroundItemAttrib      currentBackgroundItemAttrib;
    BackgroundItemAttribList  currentBackgroundItemAttribs;

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
                case BACKGROUND_ITEM_ATTRIB_WIDTH:
                    if (IsBackgroundItemAttrib (wAddress, wIndex))
                    {
                        addressMap [wAddress].m_type   = AddressDetails::BACKGROUND_ITEM_ATTRIBUTE;
                        addressMap [wAddress].m_bKnown = true;

                        currentBackgroundItemAttrib.m_wAddress  = wAddress;
                        currentBackgroundItemAttrib.m_wIndex    = wIndex;
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
                        currentBackgroundItemAttrib.m_wIndex = wIndex;
                        backgroundItemAttribList.push_back (currentBackgroundItemAttrib);

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
                        currentBackgroundItemAttrib.m_wIndex = wIndex;
                        backgroundItemAttribList.push_back (currentBackgroundItemAttrib);

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
} // Endproc.

/******************************* End of File *******************************/
