#include "stdafx.h"
#include "CharacterSprite.h"
#include "Main.h"

static  bool    IsCharacterSprite (WORD wAddress, WORD &wIndex)
{
    // Character Sprite Table 0xA4BE.

    static  WORD    CharacterSprites [] = 
    {
        0xAE0C, // KnightWalkingLeft1.
        0xAE31, // KnightLeft.
        0xAE56, // KnightWalkingLeft2.
        0xAE31, // KnightLeft.
        0xAE7B, // KnightWalkingRight1.
        0xAEA0, // KnightRight.
        0xAEC5, // KnightWalkingRight2.
        0xAEA0, // KnightRight.
        0xAD9D, // KnightWalkingUp1.
        0xADC2, // KnightUp.
        0xADE7, // KnightWalkingUp2.
        0xADC2, // KnightUp.
        0xAD2E, // KnightWalkingDown1. 
        0xAD53, // KnightDown. 
        0xAD78, // KnightWalkingDown2. 
        0xAD53, // KnightDown. 
        0xB87C, // WizardWalkingLeft1.
        0xB8A5, // WizardLeft.
        0xB8CE, // WizardWalkingLeft2.
        0xB8A5, // WizardLeft.
        0xB8F7, // WizardWalkingRight1
        0xB920, // WizardRight.
        0xB949, // WizardWalkingRight2
        0xB920, // WizardRight.
        0xB801, // WizardWalkingUp1.
        0xB82A, // WizardUp.
        0xB853, // WizardWalkingUp2.
        0xB82A, // WizardUp.
        0xB786, // WizardWalkingDown1.
        0xB7AF, // WizardDown. 
        0xB7D8, // WizardWalkingDown2.
        0xB7AF, // WizardDown. 
        0xB614, // SerfWalkingLeft1.
        0xB639, // SerfLeft.
        0xB65E, // SerfWalkingLeft2.
        0xB639, // SerfLeft.
        0xB683, // SerfWalkingRight1
        0xB6A8, // SerfRight.
        0xB6CD, // SerfWalkingRight2
        0xB6A8, // SerfRight.
        0xB5A5, // SerfWalkingUp1.
        0xB5CA, // SerfUp.
        0xB5EF, // SerfWalkingUp2.
        0xB5CA, // SerfUp.
        0xB536, // SerfWalkingDown1.
        0xB55B, // SerfDown. 
        0xB580, // SerfWalkingDown2.
        0xB55B, // SerfDown. 
        0xAEEC, 
        0xBBDC, // Cursor DirectionsLeftPane.
        0xBC05, // Cursor DirectionsRightPane.
        0xBB60, // WizardPotion1.
        0xBB7F, // WizardPotion2.
        0xBB7F, // WizardPotion2.
        0xBBBD, // WizardPotion3.
        0xBA16, // KnightSword1.
        0xB9FB, // KnightSword2.
        0xB9E2, // KnightSword3.
        0xB98B, // KnightSword4.
        0xB9A6, // KnightSword5.
        0xB9C7, // KnightSword6.
        0xB972, // KnightSword7.
        0xBA37, // KnightSword8.
        0xBA58, // SerfAxe1.
        0xBA79, // SerfAxe2.
        0xBA9A, // SerfAxe3.
        0xBABB, // SerfAxe4.
        0xBADC, // SerfAxe5.
        0xBAFD, // SerfAxe6.
        0xBB1E, // SerfAxe7.
        0xBB3F, // SerfAxe8.
        0xBC2E, //KeyboardLeftPane.
        0xBC4F, //KeyboardRightPane.
        0xBC70, // JoystickLeftPane.
        0xBC9F, // JoystickRightPane.
        0xBD30, // Pumpkin 1.
        0xBD57, // Pumpkin 2.
        0xD2C0, // Ghoul 1.
        0xD2D7, // Ghoul 2.
        0xC124, // Can.
        0xC1AA, // Candy Bar.
        0xC1CB, // Ham.
        0xC1F4, // Lollipop.
        0xC219, // Ice Cream Cone.
        0xAFF8, // Bowl.
        0xB019, // Apple.
        0xAF6C, // Bottle.
        0xC23A, // Character Appear.
        0xC253, // Character Appear 2.
        0xC26E, // Character Appear 3.
        0xC28D, // Character Appear 4.
        0xC310, // Spider 1.
        0xC32D, // Spider 2.
        0xC34A, // Ghost 1.
        0xC36B, // Ghost 2.
        0xC38C, // Bouncy 1.
        0xC3A3, // Bouncy 2.
        0xC3B6, // Smorph 1.
        0xC3DF, // Smorph 2.
        0xAEEA, 
        0xAEEA, 
        0xAEEA, 
        0xAEEA, 
        0xC408, // Jelly Ghoul 1.
        0xC429, // Jelly Ghoul 2.
        0xC44A, // Bat 1.
        0xC46F, // Bat 2.
        0xC5F8, // Character Dead 1.
        0xC60F, // Character Dead 2.
        0xC62A, // Character Dead 3.
        0xC649, // Character Dead 4.
        0xCB46, // Mummy 1.
        0xCB77, // Mummy 2.
        0xCBA8, // Mummy 3.
        0xCB77, // Mummy 2.
        0xCBD9, // Frankenstien 1. 
        0xCC0A, // Frankenstien 2. 
        0xCC3B, // Frankenstien 3. 
        0xCC0A, // Frankenstien 2. 
        0xCC6C, // Devil 1.
        0xCC9D, // Devil 2.
        0xCCCE, // Devil 3.
        0xCC9D, // Devil 2.
        0xCCFF, // Dracula 1.
        0xCD30, // Dracula 2.
        0xCD61, // Dracula 3.
        0xCD30, // Dracula 2.
        0xAF0D, // Leaf.
        0xAF2E, //Key.
        0xAF43, // Medicine Bottle.
        0xC16E, // Gobstopper.
        0xAF95, // Broken.
        0xAFB6, // Rope.
        0xAFD7, // Arm.
        0xC18F, // Amulet.
        0xC14D, // Money Bag.
        0xCDE2, // Skeleton Head.
        0xCDBD, // Cross.
        0xD29F, // Spanner.
        0xD1D5, // ACGKeyLeft.
        0xD1EC, // ACGKeyMiddle.
        0xD20B, // ACGKeyRight.
        0xCD92, // Gravestone.
        0xCE01, // WitchFlyingLeft1.
        0xCE2E, // WitchFlyingLeft2.
        0xCE5B, // WitchFlyingRight1.
        0xCE88, // WitchFlyingRight2.
        0xCEB5, // GhoulFlyingLeft1.
        0xCEDC, // GhoulFlyingLeft2.
        0xCF03, // GhoulFlyingRight1.
        0xCF2A, // GhoulFlyingRight2.
        0xCF51, // BatFlyingLeft1.
        0xCF78, // BatFlyingLeft2.
        0xCF93, // BatFlyingRight1.
        0xCFAE, // BatFlyingRight2.
        0xD3D3, // Hunchback 1.
        0xD404, // Hunchback 2.
        0xD435, // Hunchback 3.
        0xD404, // Hunchback 2.
        0xAEEA,
        0xD232, // Mushroom.
    };

    for (WORD wSprite = 0; wSprite < (sizeof (CharacterSprites) / sizeof (WORD)); ++wSprite)
    {
        if (CharacterSprites [wSprite] == wAddress)
        {
            wIndex = wSprite;

            return (true);
        } // Endif.

    } // Endfor.

    return (false);
} // Endfor.


void    ParseCharacterSprites (const Utils::DataList    &fileData,
                               CharacterSpriteList      &characterSpriteList,
                               AddressMap               &addressMap)
{
    CharacterSprite     currentCharacterSprite;
    CharacterSpriteList currentCharacterSprites;

    enum PARSE
    {
        CHARACTER_SPRITE_HEIGHT = 0,
        CHARACTER_SPRITE_SPRITE_DATA,
    }; // Endenum.

    PARSE   currentParse = CHARACTER_SPRITE_HEIGHT;

    bool    bFinished   = false;    // Initialise!
    bool    bFoundData  = false;
    BYTE    byByte      = 0;
    WORD    wIndex      = 0;

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

            case 'h':
            case 'H':
                if (addressMap.find (wAddress) == addressMap.end ())
                {
                    addressMap [wAddress] = AddressDetails(wAddress, byByte);
                }

                switch (currentParse)
                {
                case CHARACTER_SPRITE_HEIGHT:
                    if (IsCharacterSprite (wAddress, wIndex))
                    {
                        addressMap [wAddress].m_type    = AddressDetails::CHARACTER_SPRITE;
                        addressMap [wAddress].m_bKnown  = true;

                        currentCharacterSprite.m_wAddress           = wAddress;
                        currentCharacterSprite.m_wIndex             = wIndex;
                        currentCharacterSprite.m_byWidth            = 2;
                        currentCharacterSprite.m_byHeightInPixels   = byByte;
                        
                        if (currentCharacterSprite.m_byHeightInPixels == 0)
                        {
                            characterSpriteList.push_back (currentCharacterSprite);

                            currentCharacterSprite.Reset ();

                            currentParse = CHARACTER_SPRITE_HEIGHT;
                        } // Endif.

                        else
                        {
                            currentParse = CHARACTER_SPRITE_SPRITE_DATA;
                        } // Endelse.

                    } // Endif.
                    //else
                    //if (!addressMap [wAddress].m_bKnown && byByte == 0x0d)
                    //{
                    //    ccount++;

                    //    if (ccount == 5)
                    //    {
                    //        addressMap [wAddress].m_type    = AddressDetails::CHARACTER_SPRITE;
                    //        addressMap [wAddress].m_bKnown  = true;

                    //        currentCharacterSprite.m_wAddress           = wAddress;
                    //        currentCharacterSprite.m_wIndex             = wIndex;
                    //        currentCharacterSprite.m_byWidth            = 2;
                    //        currentCharacterSprite.m_byHeightInPixels   = byByte;
                    //    
                    //        if (currentCharacterSprite.m_byHeightInPixels == 0)
                    //        {
                    //            characterSpriteList.push_back (currentCharacterSprite);

                    //            currentCharacterSprite.Reset ();

                    //            currentParse = CHARACTER_SPRITE_HEIGHT;
                    //        } // Endif.

                    //        else
                    //        {
                    //            currentParse = CHARACTER_SPRITE_SPRITE_DATA;
                    //        } // Endelse.
                    //        ccount = 0;
                    //    }
                    //}
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

                        currentParse = CHARACTER_SPRITE_HEIGHT;
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

    std::sort (characterSpriteList.begin (), characterSpriteList.end ());

    #ifndef _GRAPHICS_ONLY_
    ::wprintf (L"Character Sprites\n");
    ::wprintf (L"=================\n");

    for (CharacterSpriteList::const_iterator itr = characterSpriteList.begin ();
         itr != characterSpriteList.end ();
         ++itr)
    {
        ::wprintf (L"%u, %s, Address = 0x%04.04x, Width = %u, HeightInPixels = %u, SpriteData = %s\n",
                    itr->m_wIndex,
                    DescribeCharacterSprite (itr->m_wAddress, false).c_str (),
                    itr->m_wAddress,
                    itr->m_byWidth, 
                    itr->m_byHeightInPixels,
                    Utils::DescribeData (itr->m_spriteData).c_str ());
    } // Endfor.
    #else
    for (CharacterSpriteList::iterator itr = characterSpriteList.begin ();
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
    case 0xAE0C:
        str << L"KnightWalkingLeft1";
        break;
    case 0xAE31:
        str << L"KnightLeft";
        break;
    case 0xAE56:
        str << L"KnightWalkingLeft2";
        break;
    case 0xAE7B:
        str << L"KnightWalkingRight1";
        break;
    case 0xAEA0:
        str << L"KnightRight";
        break;
    case 0xAEC5:
        str << L"KnightWalkingRight2";
        break;
    case 0xAD9D:
        str << L"KnightWalkingUp1";
        break;
    case 0xADC2:
        str << L"KnightUp";
        break;
    case 0xADE7:
        str << L"KnightWalkingUp2";
        break;
    case 0xAD2E:
        str << L"KnightWalkingDown1";
        break; 
    case 0xAD53:
        str << L"KnightDown";
        break; 
    case 0xAD78:
        str << L"KnightWalkingDown2";
        break; 
    case 0xB87C:
        str << L"WizardWalkingLeft1";
        break;
    case 0xB8A5:
        str << L"WizardLeft";
        break;
    case 0xB8CE:
        str << L"WizardWalkingLeft2";
        break;
    case 0xB8F7:
        str << L"WizardWalkingRight1";
        break;
    case 0xB920:
        str << L"WizardRight";
        break;
    case 0xB949:
        str << L"WizardWalkingRight2";
        break;
    case 0xB801:
        str << L"WizardWalkingUp1";
        break;
    case 0xB82A:
        str << L"WizardUp";
        break;
    case 0xB853:
        str << L"WizardWalkingUp2";
        break;
    case 0xB786:
        str << L"WizardWalkingDown1";
        break;
    case 0xB7AF:
        str << L"WizardDown";
        break; 
    case 0xB7D8:
        str << L"WizardWalkingDown2";
        break;
    case 0xB614:
        str << L"SerfWalkingLeft1";
        break;
    case 0xB639:
        str << L"SerfLeft";
        break;
    case 0xB65E:
        str << L"SerfWalkingLeft2";
        break;
    case 0xB683:
        str << L"SerfWalkingRight1";
        break;
    case 0xB6A8:
        str << L"SerfRight";
        break;
    case 0xB6CD:
        str << L"SerfWalkingRight2";
        break;
    case 0xB5A5:
        str << L"SerfWalkingUp1";
        break;
    case 0xB5CA:
        str << L"SerfUp";
        break;
    case 0xB5EF:
        str << L"SerfWalkingUp2";
        break;
    case 0xB536:
        str << L"SerfWalkingDown1";
        break;
    case 0xB55B:
        str << L"SerfDown";
        break; 
    case 0xB580:
        str << L"SerfWalkingDown2";
        break;
    case 0xBBDC:
        str << L"CursorDirectionsLeftPane";
        break;
    case 0xBC05:
        str << L"CursorDirectionsRightPane";
        break;
    case 0xBB60:
        str << L"WizardPotion1";
        break;
    case 0xBB7F:
        str << L"WizardPotion2";
        break;
    case 0xBBBD:
        str << L"WizardPotion3";
        break;
    case 0xBA16:
        str << L"KnightSword1";
        break;
    case 0xB9FB:
        str << L"KnightSword2";
        break;
    case 0xB9E2:
        str << L"KnightSword3";
        break;
    case 0xB98B:
        str << L"KnightSword4";
        break;
    case 0xB9A6:
        str << L"KnightSword5";
        break;
    case 0xB9C7:
        str << L"KnightSword6";
        break;
    case 0xB972:
        str << L"KnightSword7";
        break;
    case 0xBA37:
        str << L"KnightSword8";
        break;
    case 0xBA58:
        str << L"SerfAxe1";
        break;
    case 0xBA79:
        str << L"SerfAxe2";
        break;
    case 0xBA9A:
        str << L"SerfAxe3";
        break;
    case 0xBABB:
        str << L"SerfAxe4";
        break;
    case 0xBADC:
        str << L"SerfAxe5";
        break;
    case 0xBAFD:
        str << L"SerfAxe6";
        break;
    case 0xBB1E:
        str << L"SerfAxe7";
        break;
    case 0xBB3F:
        str << L"SerfAxe8";
        break;
    case 0xBC2E:
        str << L"KeyboardLeftPane";
        break;
    case 0xBC4F:
        str << L"KeyboardRightPane";
        break;
    case 0xBC70:
        str << L"JoystickLeftPane";
        break;
    case 0xBC9F:
        str << L"JoystickRightPane";
        break;
    case 0xBD30:
        str << L"Pumpkin1";
        break;
    case 0xBD57:
        str << L"Pumpkin2";
        break;
    case 0xD2C0:
        str << L"Ghoul1";
        break;
    case 0xD2D7:
        str << L"Ghoul2";
        break;
    case 0xC124:
        str << L"Can";
        break;
    case 0xC1AA:
        str << L"CandyBar";
        break;
    case 0xC1CB:
        str << L"Ham";
        break;
    case 0xC1F4:
        str << L"Lollipop";
        break;
    case 0xC219:
        str << L"IceCreamCone";
        break;
    case 0xAFF8:
        str << L"Bowl";
        break;
    case 0xB019:
        str << L"Apple";
        break;
    case 0xAF6C:
        str << L"Bottle";
        break;
    case 0xC23A:
        str << L"CharacterAppear";
        break;
    case 0xC253:
        str << L"CharacterAppear2";
        break;
    case 0xC26E:
        str << L"CharacterAppear3";
        break;
    case 0xC28D:
        str << L"CharacterAppear4";
        break;
    case 0xC310:
        str << L"Spider1";
        break;
    case 0xC32D:
        str << L"Spider2";
        break;
    case 0xC34A:
        str << L"Ghost1";
        break;
    case 0xC36B:
        str << L"Ghost2";
        break;
    case 0xC38C:
        str << L"Bouncy1";
        break;
    case 0xC3A3:
        str << L"Bouncy2";
        break;
    case 0xC3B6:
        str << L"Smorph1";
        break;
    case 0xC3DF:
        str << L"Smorph2";
        break;
    case 0xC408:
        str << L"JellyGhoul1";
        break;
    case 0xC429:
        str << L"JellyGhoul2";
        break;
    case 0xC44A:
        str << L"Bat1";
        break;
    case 0xC46F:
        str << L"Bat2";
        break;
    case 0xC5F8:
        str << L"CharacterDead1";
        break;
    case 0xC60F:
        str << L"CharacterDead2";
        break;
    case 0xC62A:
        str << L"CharacterDead3";
        break;
    case 0xC649:
        str << L"CharacterDead4";
        break;
    case 0xCB46:
        str << L"Mummy1";
        break;
    case 0xCB77:
        str << L"Mummy2";
        break;
    case 0xCBA8:
        str << L"Mummy3";
        break;
    case 0xCBD9:
        str << L"Frankenstien1";
        break; 
    case 0xCC0A:
        str << L"Frankenstien2";
        break; 
    case 0xCC3B:
        str << L"Frankenstien3";
        break; 
    case 0xCC6C:
        str << L"Devil1";
        break;
    case 0xCC9D:
        str << L"Devil2";
        break;
    case 0xCCCE:
        str << L"Devil3";
        break;
    case 0xCCFF:
        str << L"Dracula1";
        break;
    case 0xCD30:
        str << L"Dracula2";
        break;
    case 0xCD61:
        str << L"Dracula3";
        break;
    case 0xAF0D:
        str << L"Leaf";
        break;
    case 0xAF2E:
        str << L"Key";
        break;
    case 0xAF43:
        str << L"MedicineBottle";
        break;
    case 0xC16E:
        str << L"Gobstopper";
        break;
    case 0xAF95:
        str << L"Broken";
        break;
    case 0xAFB6:
        str << L"Rope";
        break;
    case 0xAFD7:
        str << L"Arm";
        break;
    case 0xC18F:
        str << L"Amulet";
        break;
    case 0xC14D:
        str << L"MoneyBag";
        break;
    case 0xCDE2:
        str << L"Skull";
        break;
    case 0xCDBD:
        str << L"Crucifix";
        break;
    case 0xD29F:
        str << L"Spanner";
        break;
    case 0xD1D5:
        str << L"ACGKeyLeft";
        break;
    case 0xD1EC:
        str << L"ACGKeyMiddle";
        break;
    case 0xD20B:
        str << L"ACGKeyRight";
        break;
    case 0xCD92:
        str << L"Gravestone";
        break;
    case 0xCE01:
        str << L"WitchFlyingLeft1";
        break;
    case 0xCE2E:
        str << L"WitchFlyingLeft2";
        break;
    case 0xCE5B:
        str << L"WitchFlyingRight1";
        break;
    case 0xCE88:
        str << L"WitchFlyingRight2";
        break;
    case 0xCEB5:
        str << L"GhoulFlyingLeft1";
        break;
    case 0xCEDC:
        str << L"GhoulFlyingLeft2";
        break;
    case 0xCF03:
        str << L"GhoulFlyingRight1";
        break;
    case 0xCF2A:
        str << L"GhoulFlyingRight2";
        break;
    case 0xCF51:
        str << L"BatFlyingLeft1";
        break;
    case 0xCF78:
        str << L"BatFlyingLeft2";
        break;
    case 0xCF93:
        str << L"BatFlyingRight1";
        break;
    case 0xCFAE:
        str << L"BatFlyingRight2";
        break;
    case 0xD3D3:
        str << L"Hunchback1";
        break;
    case 0xD404:
        str << L"Hunchback2";
        break;
    case 0xD435:
        str << L"Hunchback3";
        break;
    case 0xD232:
        str << L"Mushroom";
        break;
    default:
        str << L"Unknown";
        break;
    } // Endswitch.

    return (str.str ());
} // Endproc.

/******************************* End of File *******************************/
