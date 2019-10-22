#include "stdafx.h"
#include "Font.h"
#include "Main.h"

static  bool    IsFont (WORD            wAddress, 
                        Utils::DataList &graphicTypes)
{
    static  const   WORD    FONT_START_ADDRESS  = 0xbf4c;
    static  const   WORD    FONT_END_ADDRESS    = 0xc123;

    return ((wAddress >= FONT_START_ADDRESS) && (wAddress <= FONT_END_ADDRESS));
} // Endfor.


std::wstring    DescribeChar (BYTE byChar)
{
    std::wostringstream str;

    if ((byChar >= 32) && (byChar <= 126))
    {
        str << static_cast<char> (byChar);
    } // Endif.

    else
    {
        str << std::hex << std::setfill(L'0') << std::setw (2) << static_cast<int> (byChar);
    } // Endelse.

    return (str.str ());
}

void    ParseFonts (const Utils::DataList   &fileData,
                    FontList                &fontList,
                    AddressMap              &addressMap)
{
    Font      currentFont;
    FontList  currentFonts;

    Utils::DataList graphicTypes;
 
    enum PARSE
    {
        FONT_WIDTH = 0,
        FONT_HEIGHT,
        FONT_SPRITE_DATA,
    }; // Endenum.

    PARSE   currentParse = FONT_WIDTH;

    bool    bFinished   = false;    // Initialise!
    bool    bFoundData  = false;
    BYTE    byByte      = 0;
    BYTE    byChar      = 32;

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
                case FONT_WIDTH:
                    if (IsFont (wAddress, graphicTypes))
                    {                   
                        addressMap [wAddress].m_type    = AddressDetails::FONT;
                        addressMap [wAddress].m_bKnown  = true;

                        currentFont.m_wAddress          = wAddress;
                        currentFont.m_byChar            = byChar++;
                        currentFont.m_spriteData.push_back (byByte);

                        currentParse = FONT_SPRITE_DATA;
                    } // Endelse.
                    break;

                case FONT_SPRITE_DATA:
                    addressMap [wAddress].m_type    = AddressDetails::FONT;
                    addressMap [wAddress].m_bKnown = true;
                    
                    currentFont.m_spriteData.push_back (byByte);

                    if (currentFont.IsFinished ())
                    {
                        fontList.push_back (currentFont);

                        graphicTypes.clear ();
                        currentFont.Reset ();

                        currentParse = FONT_WIDTH;
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

    //std::sort (fontList.begin (), fontList.end ());

    #ifndef _GRAPHICS_ONLY_
    ::wprintf (L"Font\n");
    ::wprintf (L"====\n");

    for (FontList::const_iterator itr = fontList.begin ();
         itr != fontList.end ();
         ++itr)
    {
        ::wprintf (L"'%s', Address = 0x%04.04x, SpriteData = %s\n",
                    DescribeChar (itr->m_byChar).c_str (),
                    itr->m_wAddress,
                    Utils::DescribeData (itr->m_spriteData).c_str ());
    } // Endfor.
    #else

    int x = 0;
    int y = 16;

    for (FontList::const_iterator itr = fontList.begin ();
         itr != fontList.end ();
         ++itr)
    {           
        itr->DisplayFont (1, x, y);
    } // Endfor.

    Font::SaveFonts (1, 0, 16, x, 8);
    #endif
} // Endproc.

/******************************* End of File *******************************/
