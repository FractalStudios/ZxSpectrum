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
        CHARACTER_SPRITE_WIDTH = 0,
        CHARACTER_SPRITE_HEIGHT,
        CHARACTER_SPRITE_SPRITE_DATA,
    }; // Endenum.

    PARSE   currentParse = CHARACTER_SPRITE_WIDTH;

    bool    bFinished   = false;    // Initialise!
    bool    bFoundData  = false;
    BYTE    byByte      = 0;
    WORD    wIndex      = 0;

    WORD    wAddress = 0xc10e;

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

            case ',':
            case '\r':
                if (addressMap.find (wAddress) == addressMap.end ())
                {
                    addressMap [wAddress] = AddressDetails(wAddress, byByte);
                }

                switch (currentParse)
                {
                case CHARACTER_SPRITE_WIDTH:
                    addressMap [wAddress].m_type    = AddressDetails::CHARACTER_SPRITE;
                    addressMap [wAddress].m_bKnown  = true;

                    currentCharacterSprite.m_wAddress           = wAddress;
                    currentCharacterSprite.m_byWidth            = byByte;

                    currentParse = CHARACTER_SPRITE_HEIGHT;
                    break;

                case CHARACTER_SPRITE_HEIGHT:
                    addressMap [wAddress].m_type    = AddressDetails::CHARACTER_SPRITE;
                    addressMap [wAddress].m_bKnown  = true;

                    currentCharacterSprite.m_byHeightInPixels = byByte;

                    currentParse = CHARACTER_SPRITE_SPRITE_DATA;
                    break;

                case CHARACTER_SPRITE_SPRITE_DATA:
                    addressMap [wAddress].m_type    = AddressDetails::CHARACTER_SPRITE;
                    addressMap [wAddress].m_bKnown  = true;
                    
                    currentCharacterSprite.m_spriteData.push_back (byByte);

                    if (currentCharacterSprite.IsFinished ())
                    {
                        currentCharacterSprite.ReorderSpriteData ();

                        characterSpriteList.push_back (currentCharacterSprite);

                        currentCharacterSprite.Reset ();

                        if (wAddress == 0xc373)
                            wAddress = 0xc38b;
                        else
                        if (wAddress == 0xd6a5)
                            wAddress = 0xd705;
                        else
                        if (wAddress == 0xdc6b)
                            wAddress = 0xe76f;

                        currentParse = CHARACTER_SPRITE_WIDTH;
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

    std::sort (characterSpriteList.begin (), characterSpriteList.end ());

    #ifndef _GRAPHICS_ONLY_
    ::wprintf (L"Character Sprites\n");
    ::wprintf (L"=================\n");

    for (CharacterSpriteList::const_iterator itr = characterSpriteList.begin ();
         itr != characterSpriteList.end ();
         ++itr)
    {
        ::wprintf (L"%s, Address = 0x%04.04x, Width = %u, HeightInPixels = %u, SpriteData = %s\n",
                    DescribeCharacterSprite (itr->m_wAddress, false).c_str (),
                    itr->m_wAddress,
                    itr->m_byWidth, 
                    itr->m_byHeightInPixels,
                    Utils::DescribeData (itr->m_spriteData).c_str ());
    } // Endfor.
    #else
    for (CharacterSpriteList::const_iterator itr = characterSpriteList.begin ();
         itr != characterSpriteList.end ();
         ++itr)
    {           
        itr->SaveSprite ();
    } // Endfor.
    #endif
} // Endproc.


std::wstring    DescribeCharacterSprite (WORD wAddress, bool bToSave)
{
    std::wostringstream str;
    str << std::hex << std::setw (4) << std::setfill (L'0') << static_cast<int> (wAddress);

    if (!bToSave)
    {
        str << L" ";
    } // Endif.

    switch (wAddress)
    {
    case 0xD822:
        str << L"NastyAlive1";
        break;

    case 0xD84E:
        str << L"NastyAlive2";
        break;

    case 0xD889:
        str << L"NastyAlive3";
        break;

    case 0xD8D0:
        str << L"NastyAlive4";
        break;

    case 0xD917:
        str << L"NastyAlive5";
        break;

    case 0xD95E:
        str << L"NastyAlive6";
        break;

    case 0xD747:
        str << L"NastyDead1";
        break;

    case 0xD78E:
        str << L"NastyDead2";
        break;

    case 0xD7D8:
        str << L"NastyDead3";
        break;

    case 0xD706:
        str << L"NastyDead4";
        break;

    case 0xC514:
        str << L"SabreManWalkingLeft1";
        break;

    case 0xC540:
        str << L"SabreManLeft";
        break;

    case 0xC56E:
        str << L"SabreManWalkingLeft2";
        break;

    case 0xC720:
        str << L"SabreManWalkingRight1";
        break;

    case 0xC74C:
        str << L"SabreManRight";
        break;

    case 0xC77A:
        str << L"SabreManWalkingRight2";
        break;

    case 0xC40C:
        str << L"SabreManWalkingUp1";
        break;

    case 0xC438:
        str << L"SabreManUp";
        break;

    case 0xC464:
        str << L"SabreManWalkingUp2";
        break;

    case 0xC490:
        str << L"SabreManWalkingDown1";
        break;

    case 0xC4BC:
        str << L"SabreManDown";
        break;

    case 0xC4E8:
        str << L"SabreManWalkingDown2";
        break;

    case 0xC59A:
        str << L"SabreManSwordLeft1";
        break;

    case 0xC5DB:
        str << L"SabreManSwordLeft2";
        break;

    case 0xC61C:
        str << L"SabreManSwordLeft3";
        break;

    case 0xC65D:
        str << L"SabreManSwordLeft4";
        break;

    case 0xC69E:
        str << L"SabreManSwordLeft5";
        break;

    case 0xC6DF:
        str << L"SabreManSwordLeft6";
        break;

    case 0xC7A6:
        str << L"SabreManSwordRight1";
        break;

    case 0xC7E7:
        str << L"SabreManSwordRight2";
        break;

    case 0xC828:
        str << L"SabreManSwordRight3";
        break;

    case 0xC869:
        str << L"SabreManSwordRight4";
        break;

    case 0xC8AA:
        str << L"SabreManSwordRight5";
        break;

    case 0xC8EB:
        str << L"SabreManSwordRight6";
        break;

    case 0xC97A:
        str << L"RhinocerosRunningLeft1";
        break;

    case 0xC92C:
        str << L"RhinocerosRunningLeft2";
        break;

    case 0xCA16:
        str << L"RhinocerosRunningRight1";
        break;

    case 0xC9C8:
        str << L"RhinocerosRunningRight2";
        break;

    case 0xE8FC:
        str << L"Fire1";
        break;

    case 0xE92A:
        str << L"Fire2";
        break;

    case 0xE958:
        str << L"Fire3";
        break;

    case 0xE988:
        str << L"Fire4";
        break;

    case 0xCBDE:
        str << L"IndianLeft1";
        break;

    case 0xCC0E:
        str << L"IndianLeft2";
        break;

    case 0xCC3E:
        str << L"IndianLeft3";
        break;

    case 0xCC6E:
        str << L"IndianRight1";
        break;

    case 0xCC9E:
        str << L"IndianRight2";
        break;

    case 0xCCCE:
        str << L"IndianRight3";
        break;

    case 0xD282:
        str << L"SabreManFallingRight1";
        break;

    case 0xD2B0:
        str << L"SabreManFallingRight2";
        break;

    case 0xD2D6:
        str << L"SabreManFallingRight3";
        break;

    case 0xD2FC:
        str << L"SabreManFallingLeft1";
        break;

    case 0xD32A:
        str << L"SabreManFallingLeft2";
        break;

    case 0xD350:
        str << L"SabreManFallingLeft3";
        break;

    case 0xD376:
        str << L"OrchidGrowing1";
        break;

    case 0xD37E:
        str << L"OrchidGrowing2";
        break;

    case 0xD386:
        str << L"OrchidGrowing3";
        break;

    case 0xD392:
        str << L"OrchidGrowing4";
        break;

    case 0xD3A0:
        str << L"OrchidGrowing5";
        break;

    case 0xD3B2:
        str << L"OrchidGrowing6";
        break;

    case 0xD3CA:
        str << L"OrchidGrowing7";
        break;

    case 0xD3E6:
        str << L"OrchidGrowing8";
        break;

    case 0xCF06:
        str << L"WolfWalkingLeft1";
        break;

    case 0xCF64:
        str << L"WolfWalkingLeft2";
        break;

    case 0xCFC2:
        str << L"WolfWalkingLeft3";
        break;

    case 0xD020:
        str << L"WolfWalkingRight1";
        break;

    case 0xD07E:
        str << L"WolfWalkingRight2";
        break;

    case 0xD0DC:
        str << L"WolfWalkingRight3";
        break;

    case 0xD13A:
        str << L"WolfJumpingLeft1";
        break;

    case 0xD1BE:
        str << L"WolfJumpingLeft2";
        break;

    case 0xD17C:
        str << L"WolfJumpingRight1";
        break;

    case 0xD220:
        str << L"WolfJumpingRight2";
        break;

    case 0xCCFE:
        str << L"SpiderLeft1";
        break;

    case 0xCD3F:
        str << L"SpiderLeft2";
        break;

    case 0xCD83:
        str << L"SpiderRight1";
        break;

    case 0xCDC4:
        str << L"SpiderRight2";
        break;

    case 0xCE08:
        str << L"ScorpionLeft1";
        break;

    case 0xCE49:
        str << L"ScorpionLeft2";
        break;

    case 0xCE87:
        str << L"ScorpionRight1";
        break;

    case 0xCEC8:
        str << L"ScorpionRight2";
        break;

    case 0xC38C:
        str << L"BatLeft1";
        break;

    case 0xC3B0:
        str << L"BatLeft2";
        break;

    case 0xC3CC:
        str << L"BatRight1";
        break;

    case 0xC3F0:
        str << L"BatRight2";
        break;

    case 0xD418:
        str << L"ParrotLeft1";
        break;

    case 0xD440:
        str << L"ParrotLeft2";
        break;

    case 0xD468:
        str << L"ParrotRight1";
        break;

    case 0xD490:
        str << L"ParrotRight2";
        break;

    case 0xD4B8:
        str << L"MonkeyLeft1";
        break;

    case 0xD4E4:
        str << L"MonkeyLeft2";
        break;

    case 0xD50E:
        str << L"MonkeyRight1";
        break;

    case 0xD53A:
        str << L"MonkeyRight2";
        break;

    case 0xD564:
        str << L"LizardLeft1";
        break;

    case 0xD58D:
        str << L"LizardLeft2";
        break;

    case 0xD5B9:
        str << L"LizardRight1";
        break;

    case 0xD5E5:
        str << L"LizardRight2";
        break;

    case 0xD60E:
        str << L"SnakeLeft1";
        break;

    case 0xD637:
        str << L"SnakeLeft2";
        break;

    case 0xD65A:
        str << L"SnakeRight1";
        break;

    case 0xD67D:
        str << L"SnakeRight2";
        break;

    case 0xD999:
        str << L"Box";
        break;

    case 0xD9BB:
        str << L"Ring";
        break;

    case 0xD9DD:
        str << L"Apple";
        break;

    case 0xD9FF:
        str << L"Charm";
        break;

    case 0xDA21:
        str << L"Amulet";
        break;

    case 0xDA43:
        str << L"ExtraLife";
        break;

    case 0xDA65:
        str << L"MoneyBag";
        break;

    case 0xDA87:
        str << L"Spear";
        break;

    case 0xDAA9:
        str << L"Chalice";
        break;

    case 0xE7D6:
        str << L"AmuletBottomRight";
        break;

    case 0xE7B4:
        str << L"AmuletBottomLeft";
        break;

    case 0xE792:
        str << L"AmuletTopRight";
        break;

    case 0xE770:
        str << L"AmuletTopLeft";
        break;

    case 0xE7F8:
        str << L"Guardian1";
        break;                                                     

    case 0xE87A:
        str << L"Guardian2";
        break;

    case 0xE9B8:
        str << L"RatLeft1";
        break;

    case 0xE9D5:
        str << L"RatLeft2";
        break;

    case 0xE9F2:
        str << L"RatRight1";
        break;

    case 0xEA0F:
        str << L"RatRight2";
        break;

    case 0xEA2C:
        str << L"BirdLeft1";
        break;

    case 0xEA64:
        str << L"BirdLeft2";
        break;

    case 0xEAA8:
        str << L"BirdRight1";
        break;

    case 0xEAE0:
        str << L"BirdRight2";
        break;

    case 0xCAAE:
        str << L"HippopotamusRunningLeft1";
        break;

    case 0xCAF8:
        str << L"HippopotamusRunningLeft2";
        break;

    case 0xCB46:
        str << L"HippopotamusRunningRight1";
        break;

    case 0xCB90:
        str << L"HippopotamusRunningRight2";
        break;

    case 0xCA64:
        str << L"HippopotamusSleeping";
        break;

    case 0xDB4C:
        str << L"BoarRunningLeft1";
        break;

    case 0xDC22:
        str << L"BoarRunningLeft2";
        break;

    case 0xDB92:
        str << L"BoarRunningRight1";
        break;

    case 0xDBDC:
        str << L"BoarRunningRight2";
        break;

    case 0xDB0B:
        str << L"BoarSleeping";
        break;

    case 0xEBA4:
        str << L"FrogLeft1";
        break;

    case 0xEBCA:
        str << L"FrogLeft2";
        break;

    case 0xEBEA:
        str << L"FrogRight1";
        break;

    case 0xEC10:
        str << L"FrogRight2";
        break;

    case 0xEB24:
        str << L"FlyLeft1";
        break;

    case 0xEB46:
        str << L"FlyLeft2";
        break;

    case 0xEB64:
        str << L"FlyRight1";
        break;

    case 0xEB86:
        str << L"FlyRight2";
        break;

    case 0xC270:
        str << L"SquirrelLeft1";
        break;

    case 0xC2B1:
        str << L"SquirrelLeft2";
        break;

    case 0xC2F2:
        str << L"SquirrelRight1";
        break;

    case 0xC333:
        str << L"SquirrelRight2";
        break;

    case 0xC1E8:
        str << L"BugLeft1";
        break;

    case 0xC206:
        str << L"BugLeft2";
        break;

    case 0xC22C:
        str << L"BugRight1";
        break;

    case 0xC24A:
        str << L"BugRight2";
        break;

    case 0xC10E:
        str << L"InsectLeft1";
        break;

    case 0xC146:
        str << L"InsectLeft2";
        break;

    case 0xC17B:
        str << L"InsectRight1";
        break;

    case 0xC1B3:
        str << L"InsectRight2";
        break;

    case 0xC10C:
    default:
        str << L"Unknown";
        break;
    } // Endswitch.

    return (str.str ());
} // Endproc.

/******************************* End of File *******************************/
