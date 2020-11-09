#include"stdafx.h"
#include"CharacterSprite.h"
#include"Main.h"

bool    IsCharacterSprite (WORD wAddress, WORD &wIndex)
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
        0xBBDC, // CursorDirectionsLeftPane.
        0xBC05, // CursorDirectionsRightPane.
        0xBB60, // WizardPotion1.
        0xBB7F, // WizardPotion2.
        0xBB9E, // WizardPotion3.
        0xBBBD, // WizardPotion4.
        0xBA16, // SerfSword1.
        0xB9FB, // SerfSword2.
        0xB9E2, // SerfSword3.
        0xB98B, // SerfSword4.
        0xB9A6, // SerfSword5.
        0xB9C7, // SerfSword6.
        0xB972, // SerfSword7.
        0xBA37, // SerfSword8.
        0xBA58, // KnightAxe1.
        0xBA79, // KnightAxe2.
        0xBA9A, // KnightAxe3.
        0xBABB, // KnightAxe4.
        0xBADC, // KnightAxe5.
        0xBAFD, // KnightAxe6.
        0xBB1E, // KnightAxe7.
        0xBB3F, // KnightAxe8.
        0xBC2E, // KeyboardLeftPane.
        0xBC4F, // KeyboardRightPane.
        0xBC70, // JoystickLeftPane.
        0xBC9F, // JoystickRightPane.
        0xBD30, // Pumpkin1.
        0xBD57, // Pumpkin2.
        0xD2C0, // Ghoul1.
        0xD2D7, // Ghoul2.
        0xC124, // Can.
        0xC1AA, // CandyBar.
        0xC1CB, // Ham.
        0xC1F4, // Lollipop.
        0xC219, // IceCreamCone.
        0xAFF8, // Bowl.
        0xB019, // Apple.
        0xAF6C, // Bottle.
        0xC23A, // CharacterAppear.
        0xC253, // CharacterAppear2.
        0xC26E, // CharacterAppear3.
        0xC28D, // CharacterAppear4.
        0xC310, // Spider1.
        0xC32D, // Spider2.
        0xC34A, // Ghost1.
        0xC36B, // Ghost2.
        0xC38C, // Bouncy1.
        0xC3A3, // Bouncy2.
        0xC3B6, // Smorph1.
        0xC3DF, // Smorph2.
        0xC408, // JellyGhoul1.
        0xC429, // JellyGhoul2.
        0xC44A, // Bat1.
        0xC46F, // Bat2.
        0xC5F8, // CharacterDead1.
        0xC60F, // CharacterDead2.
        0xC62A, // CharacterDead3.
        0xC649, // CharacterDead4.
        0xCB46, // Mummy1.
        0xCB77, // Mummy2.
        0xCBA8, // Mummy3.
        0xCB77, // Mummy2.
        0xCBD9, // Frankenstien1.
        0xCC0A, // Frankenstien2.
        0xCC3B, // Frankenstien3.
        0xCC0A, // Frankenstien2.
        0xCC6C, // Devil1.
        0xCC9D, // Devil2.
        0xCCCE, // Devil3.
        0xCC9D, // Devil2.
        0xCCFF, // Dracula1.
        0xCD30, // Dracula2.
        0xCD61, // Dracula3.
        0xCD30, // Dracula2.
        0xAF0D, // Leaf.
        0xAF2E, // Key.
        0xAF43, // MedicineBottle.
        0xC16E, // Gobstopper.
        0xAF95, // Broken.
        0xAFB6, // Rope.
        0xAFD7, // Arm.
        0xC18F, // Amulet.
        0xC14D, // MoneyBag.
        0xCDE2, // SkeletonHead.
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
        0xD3D3, // Hunchback1.
        0xD404, // Hunchback2.
        0xD435, // Hunchback3.
        0xD404, // Hunchback2.
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


std::wstring    DescribeCharacterSprite (WORD wAddress, bool bStripWhiteSpace)
{
    std::wostringstream str;

    switch (wAddress)
    {
    case 0xAE0C:
        str << L"Knight Walking Left 1";
        break;
    case 0xAE31:
        str << L"Knight Left";
        break;
    case 0xAE56:
        str << L"Knight Walking Left 2";
        break;
    case 0xAE7B:
        str << L"Knight Walking Right 1";
        break;
    case 0xAEA0:
        str << L"Knight Right";
        break;
    case 0xAEC5:
        str << L"Knight Walking Right 2";
        break;
    case 0xAD9D:
        str << L"Knight Walking Up 1";
        break;
    case 0xADC2:
        str << L"Knight Up";
        break;
    case 0xADE7:
        str << L"Knight Walking Up 2";
        break;
    case 0xAD2E:
        str << L"Knight Walking Down 1";
        break; 
    case 0xAD53:
        str << L"Knight Down";
        break; 
    case 0xAD78:
        str << L"Knight Walking Down 2";
        break; 
    case 0xB87C:
        str << L"Wizard Walking Left 1";
        break;
    case 0xB8A5:
        str << L"Wizard Left";
        break;
    case 0xB8CE:
        str << L"Wizard Walking Left 2";
        break;
    case 0xB8F7:
        str << L"Wizard Walking Right 1";
        break;
    case 0xB920:
        str << L"Wizard Right";
        break;
    case 0xB949:
        str << L"Wizard Walking Right 2";
        break;
    case 0xB801:
        str << L"Wizard Walking Up 1";
        break;
    case 0xB82A:
        str << L"Wizard Up";
        break;
    case 0xB853:
        str << L"Wizard Walking Up 2";
        break;
    case 0xB786:
        str << L"Wizard Walking Down 1";
        break;
    case 0xB7AF:
        str << L"Wizard Down";
        break; 
    case 0xB7D8:
        str << L"Wizard Walking Down 2";
        break;
    case 0xB614:
        str << L"Serf Walking Left 1";
        break;
    case 0xB639:
        str << L"Serf Left";
        break;
    case 0xB65E:
        str << L"Serf Walking Left 2";
        break;
    case 0xB683:
        str << L"Serf Walking Right 1";
        break;
    case 0xB6A8:
        str << L"Serf Right";
        break;
    case 0xB6CD:
        str << L"Serf Walking Right 2";
        break;
    case 0xB5A5:
        str << L"Serf Walking Up 1";
        break;
    case 0xB5CA:
        str << L"Serf Up";
        break;
    case 0xB5EF:
        str << L"Serf Walking Up 2";
        break;
    case 0xB536:
        str << L"Serf Walking Down 1";
        break;
    case 0xB55B:
        str << L"Serf Down";
        break; 
    case 0xB580:
        str << L"Serf Walking Down 2";
        break;
    case 0xBBDC:
        str << L"Cursor Directions Left Pane";
        break;
    case 0xBC05:
        str << L"Cursor Directions Right Pane";
        break;
    case 0xBB60:
        str << L"Wizard Potion 1";
        break;
    case 0xBB7F:
        str << L"Wizard Potion 2";
        break;
    case 0xBB9E:
        str << L"Wizard Potion 3";
        break;
    case 0xBBBD:
        str << L"Wizard Potion 4";
        break;
    case 0xBA16:
        str << L"Serf Sword 1";
        break;
    case 0xB9FB:
        str << L"Serf Sword 2";
        break;
    case 0xB9E2:
        str << L"Serf Sword 3";
        break;
    case 0xB98B:
        str << L"Serf Sword 4";
        break;
    case 0xB9A6:
        str << L"Serf Sword 5";
        break;
    case 0xB9C7:
        str << L"Serf Sword 6";
        break;
    case 0xB972:
        str << L"Serf Sword 7";
        break;
    case 0xBA37:
        str << L"Serf Sword 8";
        break;
    case 0xBA58:
        str << L"Knight Axe 1";
        break;
    case 0xBA79:
        str << L"Knight Axe 2";
        break;
    case 0xBA9A:
        str << L"Knight Axe 3";
        break;
    case 0xBABB:
        str << L"Knight Axe 4";
        break;
    case 0xBADC:
        str << L"Knight Axe 5";
        break;
    case 0xBAFD:
        str << L"Knight Axe 6";
        break;
    case 0xBB1E:
        str << L"Knight Axe 7";
        break;
    case 0xBB3F:
        str << L"Knight Axe 8";
        break;
    case 0xBC2E:
        str << L"Keyboard Left Pane";
        break;
    case 0xBC4F:
        str << L"Keyboard Right Pane";
        break;
    case 0xBC70:
        str << L"Joystick Left Pane";
        break;
    case 0xBC9F:
        str << L"Joystick Right Pane";
        break;
    case 0xBD30:
        str << L"Pumpkin 1";
        break;
    case 0xBD57:
        str << L"Pumpkin 2";
        break;
    case 0xD2C0:
        str << L"Ghoul 1";
        break;
    case 0xD2D7:
        str << L"Ghoul 2";
        break;
    case 0xC124:
        str << L"Can";
        break;
    case 0xC1AA:
        str << L"Candy Bar";
        break;
    case 0xC1CB:
        str << L"Ham";
        break;
    case 0xC1F4:
        str << L"Lollipop";
        break;
    case 0xC219:
        str << L"Ice Cream Cone";
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
        str << L"Character Appear 1";
        break;
    case 0xC253:
        str << L"Character Appear 2";
        break;
    case 0xC26E:
        str << L"Character Appear 3";
        break;
    case 0xC28D:
        str << L"Character Appear 4";
        break;
    case 0xC310:
        str << L"Spider 1";
        break;
    case 0xC32D:
        str << L"Spider 2";
        break;
    case 0xC34A:
        str << L"Ghost 1";
        break;
    case 0xC36B:
        str << L"Ghost 2";
        break;
    case 0xC38C:
        str << L"Bouncy 1";
        break;
    case 0xC3A3:
        str << L"Bouncy 2";
        break;
    case 0xC3B6:
        str << L"Smorph 1";
        break;
    case 0xC3DF:
        str << L"Smorph 2";
        break;
    case 0xC408:
        str << L"Jelly Ghoul 1";
        break;
    case 0xC429:
        str << L"Jelly Ghoul 2";
        break;
    case 0xC44A:
        str << L"Bat 1";
        break;
    case 0xC46F:
        str << L"Bat 2";
        break;
    case 0xC5F8:
        str << L"Character Dead 1";
        break;
    case 0xC60F:
        str << L"Character Dead 2";
        break;
    case 0xC62A:
        str << L"Character Dead 3";
        break;
    case 0xC649:
        str << L"Character Dead 4";
        break;
    case 0xCB46:
        str << L"Mummy 1";
        break;
    case 0xCB77:
        str << L"Mummy 2";
        break;
    case 0xCBA8:
        str << L"Mummy 3";
        break;
    case 0xCBD9:
        str << L"Frankenstien 1";
        break; 
    case 0xCC0A:
        str << L"Frankenstien 2";
        break; 
    case 0xCC3B:
        str << L"Frankenstien 3";
        break; 
    case 0xCC6C:
        str << L"Devil 1";
        break;
    case 0xCC9D:
        str << L"Devil 2";
        break;
    case 0xCCCE:
        str << L"Devil 3";
        break;
    case 0xCCFF:
        str << L"Dracula 1";
        break;
    case 0xCD30:
        str << L"Dracula 2";
        break;
    case 0xCD61:
        str << L"Dracula 3";
        break;
    case 0xAF0D:
        str << L"Leaf";
        break;
    case 0xAF2E:
        str << L"Key";
        break;
    case 0xAF43:
        str << L"Medicine Bottle";
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
        str << L"Money Bag";
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
        str << L"ACG Key Left";
        break;
    case 0xD1EC:
        str << L"ACG KeyMiddle";
        break;
    case 0xD20B:
        str << L"ACG Key Right";
        break;
    case 0xCD92:
        str << L"Gravestone";
        break;
    case 0xCE01:
        str << L"Witch Flying Left 1";
        break;
    case 0xCE2E:
        str << L"Witch Flying Left 2";
        break;
    case 0xCE5B:
        str << L"Witch Flying Right 1";
        break;
    case 0xCE88:
        str << L"Witch Flying Right 2";
        break;
    case 0xCEB5:
        str << L"Ghoul Flying Left 1";
        break;
    case 0xCEDC:
        str << L"Ghoul Flying Left 2";
        break;
    case 0xCF03:
        str << L"Ghoul Flying Right 1";
        break;
    case 0xCF2A:
        str << L"Ghoul Flying Right 2";
        break;
    case 0xCF51:
        str << L"Bat Flying Left 1";
        break;
    case 0xCF78:
        str << L"Bat Flying Left 2";
        break;
    case 0xCF93:
        str << L"Bat Flying Right 1";
        break;
    case 0xCFAE:
        str << L"Bat Flying Right 2";
        break;
    case 0xD3D3:
        str << L"Hunchback 1";
        break;
    case 0xD404:
        str << L"Hunchback 2";
        break;
    case 0xD435:
        str << L"Hunchback 3";
        break;
    case 0xD232:
        str << L"Mushroom";
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
                    break;

                case CHARACTER_SPRITE_SPRITE_DATA:
                    addressMap [wAddress].m_type    = AddressDetails::CHARACTER_SPRITE;
                    addressMap [wAddress].m_bKnown  = true;
                    
                    currentCharacterSprite.m_spriteData.push_back (byByte);

                    if (currentCharacterSprite.IsFinished ())
                    {
                        //currentCharacterSprite.ReorderSpriteData ();

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
} // Endproc.

/******************************* End of File *******************************/
