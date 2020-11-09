#pragma once

#include <vector>
#include <cctype>
#include "Main.h"
#include "Utils.h"
#include "ZxSpectrum.h"

#pragma pack(push, 1)

// Definitions and Types.

struct CharacterSprite
{
    CharacterSprite ()
    :   m_wStartAddress(0),
        m_wEndAddress(0),
        m_wIndex(0),
        m_byZero(0),
        m_byWidthInBytes(0),
        m_byHeightInPixels(0)
    {} // Endproc.

    void    Reset ()
    {
        m_wStartAddress     = 0;
        m_wEndAddress       = 0;
        m_wIndex            = 0;
        m_byZero            = 0;
        m_byWidthInBytes    = 0;
        m_byHeightInPixels  = 0;
        m_spriteData.clear ();
    } // Endproc.

    bool    IsStarted () const
    {
        return (m_wStartAddress != 0);
    } // Endproc.

    bool    IsFinished () const
    {
        return (m_spriteData.size () == (m_byWidthInBytes * m_byHeightInPixels));
    } // Endproc.

    void    ReorderSpriteData ()
    {
        Utils::DataList tempSpriteData;

        for (Utils::DataList::reverse_iterator ritr = m_spriteData.rbegin ();
             ritr != m_spriteData.rend ();
             ritr += m_byWidthInBytes)
        {
            Utils::DataList::iterator   itr = (ritr + m_byWidthInBytes).base ();

            tempSpriteData.insert (tempSpriteData.end (),
                                   itr,
                                   itr + m_byWidthInBytes);
        } // Endfor.

        m_spriteData = tempSpriteData;
    } // Endproc.

    bool    operator < (const CharacterSprite &rhs) const
    {
        return (m_wStartAddress < rhs.m_wStartAddress);
    } // Endproc.

    std::wstring    DescribeCharacterSprite () const
    {
        std::wostringstream str;
        str << std::hex << std::setw (4) << std::setfill (L'0') << static_cast<int> (m_wStartAddress)
            << L'_'
            << std::hex << std::setw (4) << std::setfill (L'0') << static_cast<int> (m_wEndAddress);
        return (str.str ());
    } // Endproc.

    static  std::wstring    DescribeCharacterSprite1 (WORD wStartAddress, WORD wEndAddress)
    {
        switch (wStartAddress)
        {
        case 0x7796:
            return (L"jetmanFlyingRight1");
        case 0x77C9:
            return (L"jetmanFlyingRight2");
        case 0x7814:
            return (L"jetmanFlyingRight3");
        case 0x785F:
            return (L"jetmanFlyingRight4");
        case 0x78AA:
            return (L"jetmanFlyingLeft1");
        case 0x78DD:
            return (L"jetmanFlyingLeft2");
        case 0x7910:
            return (L"jetmanFlyingLeft3");
        case 0x795B:
            return (L"jetmanFlyingLeft4");
        case 0x79A6:
            return (L"jetmanWalkingLeft1");
        case 0x79D9:
            return (L"jetmanWalkingLeft2");
        case 0x7A0C:
            return (L"jetmanWalkingLeft3");
        case 0x7A57:
            return (L"jetmanWalkingLeft4");
        case 0x7AA2:
            return (L"jetmanWalkingRight1");
        case 0x7AD5:
            return (L"jetmanWalkingRight2");
        case 0x7B08:
            return (L"jetmanWalkingRight3");
        case 0x7B53:
            return (L"jetmanWalkingRight4");
        case 0x7B9E:
            return (L"nastyMeteor1");
        case 0x7BB5:
            return (L"nastyMeteor2");
        case 0x7BCC:
            return (L"cloud1");
        case 0x7BFF:
            return (L"cloud2");
        case 0x7C32:
            return (L"cloud3");
        case 0x7C65:
            return (L"rocketU3Bottom");
        case 0x7C88:
            return (L"rocketU3Middle");
        case 0x7CAB:
            return (L"rocketU3Top");
        case 0x7CCE:
            return (L"rocketU1Bottom");
        case 0x7CF1:
            return (L"rocketU1Middle");
        case 0x7D14:
            return (L"rocketU1Top");
        case 0x7D37:
            return (L"rocketU2Bottom");
        case 0x7D5A:
            return (L"rocketU2Middle");
        case 0x7D7D:
            return (L"rocketU2Top");
        case 0x7DA0:
            return (L"rocketU4Bottom");
        case 0x7DC3:
            return (L"rocketU4Middle");
        case 0x7DE6:
            return (L"rocketU4Top");
        case 0x7E09:
            return (L"goldBar");
        case 0x7E1C:
            return (L"fuel");
        case 0x7E35:
            return (L"radiationCanister");
        case 0x7E4E:
            return (L"triangle");
        case 0x7E6B:
            return (L"dome");
        case 0x7E80:
            return (L"crystal");
        case 0x7E9B:
            return (L"nastyFurball1");
        case 0x7EB8:
            return (L"nastyFurball2");
        case 0x7ED5:
            return (L"nastyPlane");
        case 0x7EE4:
            return (L"nastyFlyingSaucer");
        case 0x7EF5:
            return (L"nastyBall1");
        case 0x7F16:
            return (L"nastyBall2");
        case 0x7F33:
            return (L"nastySatellite");
        case 0x7F52:
            return (L"nastyMilleniumFalcon");
        case 0x7F6F:
            return (L"nastyBlob");
        case 0x7F8C:
            return (L"rocketSmokeTrail1");
        case 0x7FAF:
            return (L"rocketSmokeTrail2");
        default:
            {
                std::wostringstream str;
                str << std::hex << std::setw (4) << std::setfill (L'0') << static_cast<int> (wStartAddress)
                    << L'_'
                    << std::hex << std::setw (4) << std::setfill (L'0') << static_cast<int> (wEndAddress);
                return (str.str ());
            } // Endscope.

        } // Endswitch.

    } // Endproc.


    static  std::wstring    DescribeCharacterSprite2 (bool bJetman, bool bRocket, WORD wStartAddress, WORD wEndAddress)
    {
        if (bJetman)
        {
            return (L"jetman");
        } // Endif.

        switch (wStartAddress)
        {
        case 0x7796:
            return (L"jetmanFlyingRight");
        case 0x78AA:
            return (L"jetmanFlyingLeft");
        case 0x79A6:
            return (L"jetmanWalkingLeft");
        case 0x7AA2:
            return (L"jetmanWalkingRight");
        case 0x7B9E:
            return (L"nastyMeteor");
        case 0x7BCC:
            return (L"cloud");
        case 0x7C65:
        case 0x7C88:
        case 0x7CAB:
            return (L"rocketU3");
        case 0x7CCE:
        case 0x7CF1:
        case 0x7D14:
            return (L"rocketU1");
        case 0x7D37:
        case 0x7D5A:
        case 0x7D7D:
            return (L"rocketU2");
        case 0x7DA0:
        case 0x7DC3:
        case 0x7DE6:
            return (L"rocketU4");
        case 0x7E09:
            return (L"goldBar");
        case 0x7E1C:
            return (L"fuel");
        case 0x7E35:
            return (L"radiationCanister");
        case 0x7E4E:
            return (L"triangle");
        case 0x7E6B:
            return (L"dome");
        case 0x7E80:
            return (L"crystal");
        case 0x7E9B:
            return (L"nastyFurball");
        case 0x7ED5:
            return (L"nastyPlane");
        case 0x7EE4:
            return (L"nastyFlyingSaucer");
        case 0x7EF5:
            return (L"nastyBall");
        case 0x7F33:
            return (L"nastySatellite");
        case 0x7F52:
            return (L"nastyMilleniumFalcon");
        case 0x7F6F:
            return (L"nastyBlob");
        case 0x7F8C:
            return (L"rocketSmokeTrail");
        default:
            {
                std::wostringstream str;
                str << std::hex << std::setw (4) << std::setfill (L'0') << static_cast<int> (wStartAddress)
                    << L'_'
                    << std::hex << std::setw (4) << std::setfill (L'0') << static_cast<int> (wEndAddress);
                return (str.str ());
            } // Endscope.

        } // Endswitch.

    } // Endproc.

    static  const   int X_START = 16;
    static  const   int Y_START = 16;
    static  const   int SCALE   = 1;

    void    SaveAnimatedSprite ()
    {
        std::wostringstream str;

        for (UINT uiFrame = 0; uiFrame <= 6; uiFrame += 2)
        {
            Utils::DataList animatedSpriteData;;

            for (Utils::DataList::iterator itr = m_spriteData.begin ();
                 itr != m_spriteData.end ();
                 itr += m_byWidthInBytes)
            {
                BYTE    byNibble = 0;

                for (UINT uiByte = 0; uiByte < m_byWidthInBytes; ++uiByte)
                {
                    BYTE    byData = (*(itr + uiByte)) >> uiFrame;
                    byData |= byNibble;
                    animatedSpriteData.push_back (byData);

                    byNibble = (*(itr + uiByte)) << (8 - uiFrame);
                } // Endfor.

                animatedSpriteData.push_back (byNibble);
            } // Endfor.

            str.str (L"");
            str << DescribeCharacterSprite () << L"_Animation_" << uiFrame/2 << L".bmp";

            SaveSprite (m_byWidthInBytes + 1, 
                        m_byHeightInPixels, 
                        animatedSpriteData,
                        str.str ());
        } // Endfor.

    } // Endproc.

    void    SaveAnimatedSprite2 ()
    {
        std::wostringstream str;

        for (UINT uiFrame = 0; uiFrame <= 4; uiFrame += 4)
        {
            Utils::DataList animatedSpriteData;;

            for (Utils::DataList::iterator itr = m_spriteData.begin ();
                 itr != m_spriteData.end ();
                 itr += m_byWidthInBytes)
            {
                BYTE    byNibble = 0;

                for (UINT uiByte = 0; uiByte < m_byWidthInBytes; ++uiByte)
                {
                    BYTE    byData = (*(itr + uiByte)) >> uiFrame;
                    byData |= byNibble;
                    animatedSpriteData.push_back (byData);

                    byNibble = (*(itr + uiByte)) << (8 - uiFrame);
                } // Endfor.

                animatedSpriteData.push_back (byNibble);
            } // Endfor.

            str.str (L"");
            str << DescribeCharacterSprite () << L"_Animation_" << uiFrame/2 << L".bmp";

            SaveSprite (m_byWidthInBytes + 1, 
                        m_byHeightInPixels, 
                        animatedSpriteData,
                        str.str ());
        } // Endfor.

    } // Endproc.

    void    SaveSprite () const
    {
        SaveSprite (m_byWidthInBytes, 
                    m_byHeightInPixels, 
                    m_spriteData, 
                    DescribeCharacterSprite () + L".bmp");
    } // Endproc.

    void    SaveSprite2 () const
    {
        SaveSprite2 (m_byWidthInBytes, 
                     m_byHeightInPixels, 
                     m_spriteData, 
                     DescribeCharacterSprite1 (m_wStartAddress, m_wEndAddress));
    } // Endproc.

    static  void    SaveSprite2 (BYTE                   byWidthInBytes,
                                 BYTE                   byHeightInPixels,
                                 const Utils::DataList  &spriteData,
                                 const std::wstring     &sprite)
    {
        BYTE    byHeightInBytes = byHeightInPixels / 8;

        if (byHeightInPixels % 8)
        {       
            byHeightInBytes++;
        } // Endif.

        std::ostringstream str;
        str << "// " << Utils::WideStringToNarrowString (sprite) << "." << std::endl
            << "static  MaskedSprite" << static_cast<int> (byWidthInBytes) << "   g_" << Utils::WideStringToNarrowString (sprite) << " =" << std::endl
            << "{" << std::endl
            << "    0x" << std::hex << std::uppercase << std::setw (2) << std::setfill ('0') << static_cast<int> (byWidthInBytes) << ",   // Width." << std::endl
            << "    0x" << std::hex << std::uppercase << std::setw (2) << std::setfill ('0') << static_cast<int> (byHeightInBytes) << ",   // Height." << std::endl
            << "    // Guard." << std::endl
            << "    {" << std::endl
            << "        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00," << std::endl
            << "    }," << std::endl
            << "    // Glyph data." << std::endl
            << "    {" << std::endl;

        BYTE    byCount = 0;    // Initialise!
            
        for (WORD wWidth = 0; wWidth < byWidthInBytes; ++wWidth)
        {
            str << "        // Column " << std::dec << (wWidth + 1) << ".";

            for (WORD wHeight = 0; wHeight < byHeightInPixels; ++wHeight)
            {
                if ((byCount % 8) == 0)
                {
                    str << std::endl << "       ";
                } // Endif.

                byCount++;

                BYTE    byByte = spriteData [wHeight * byWidthInBytes + wWidth];
                str << " 0x" << std::hex << std::uppercase << std::setw (2) << std::setfill ('0') << static_cast<int> (~byByte & 0xff) << ","
                    << " 0x" << std::hex << std::uppercase << std::setw (2) << std::setfill ('0') << static_cast<int> (byByte) << ",";
            } // Endfor.
            
            if (byHeightInPixels % 8)
            {
                for (WORD wHeight = 0; wHeight < (8 - (byHeightInPixels % 8)); ++wHeight)
                {
                    if ((byCount % 8) == 0)
                    {
                        str << std::endl << "       ";
                    } // Endif.

                    byCount++;

                    BYTE    byByte = 0;
                    str << " 0x" << std::hex << std::uppercase << std::setw (2) << std::setfill ('0') << static_cast<int> (~byByte & 0xff) << ","
                        << " 0x" << std::hex << std::uppercase << std::setw (2) << std::setfill ('0') << static_cast<int> (byByte) << ",";
                } // Endfor.
            
            } // Endif.

            str << std::endl << "        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00," << std::endl;
        } // Endfor.

        str << "    }," << std::endl
            << "};" << std::endl
            << std::endl;

        std::string text(str.str ());

        Utils::WriteFile (L"SpriteData.h", Utils::DataList(text.begin (), text.end ()));
    } // Endproc.

    static  WORD    GetNumFrames (const std::wstring    &sprite, 
                                  bool                  bMirror,
                                  bool                  bJetman,
                                  bool                  bRocket)
    {
        if (bJetman)
        {
            return (4);
        } // Endif.

        if (bRocket)
        {
            return (1);
        } // Endif.

        if ((sprite == L"nastyMeteor")  ||
            (sprite == L"nastyFurball") ||
            (sprite == L"nastyBall")    ||
            (sprite == L"rocketSmokeTrail"))
        {
            return (2);
        } // Endif.

        if (sprite == L"cloud")
        {
            return (3);
        } // Endif.

        return (1);
    } // Endproc.

    static  WORD    GetNumMovements (const std::wstring &sprite, 
                                     bool               bMirror,
                                     bool               bJetman,
                                     bool               bRocket)
    {
        if (bJetman)
        {
            return (4);
        } // Endif.

        if (bRocket)
        {
            return (3);
        } // Endif.

        return (bMirror ? 2 : 1);
    } // Endproc.

    static  std::wstring    DescribeSpriteStruct (const std::wstring    &sprite, 
                                                  WORD                  wNumMovements,
                                                  WORD                  wNumFrames,
                                                  WORD                  wNumFrameBytes,
                                                  bool                  bJetman,
                                                  bool                  bRocket)
    {
        if (bJetman)
        {
            return (L"JetmanSprite");
        } // Endif.

        if (bRocket)
        {
            return (L"RocketSprite");
        } // Endif.

        if (sprite == L"cloud")
        {
            return (L"CloudSprite");
        } // Endif.

        std::wostringstream str;
        str << L"MaskedSpriteM" << wNumMovements << L"F" << wNumFrames << L"_" << wNumFrameBytes;

        return (str.str ());
    } // Endproc.

    static  std::wstring    DescribeMovement (const std::wstring    &sprite,
                                              bool                  bMirror,
                                              bool                  bJetman,
                                              bool                  bRocket,
                                              WORD                  wMovement) 
    {
        if (bJetman)
        {
            switch (wMovement)
            {
            case 0:
                return (L"Walking right");
            case 1:
                return (L"Walking left");
            case 2:
                return (L"Flying right");
            case 3:
                return (L"Flying left");
            default:
                return (L"?");
            } // Endswitch.

        } // Endif.

        if (bRocket)
        {
            switch (wMovement)
            {
            case 0:
                return (L"Bottom");
            case 1:
                return (L"Middle");
            case 2:
                return (L"Top");
            default:
                return (L"?");
            } // Endswitch.

        } // Endif.

        if (bMirror)
        {
            switch (wMovement)
            {
            case 0:
                return (L"Right");
            case 1:
                return (L"Left");
            default:
                return (L"?");
            } // Endswitch.

        } // Endif.

        return (L"Static");
    } // Endproc.

    static  void    SaveSprite3 (BYTE                   byWidthInBytes,
                                 BYTE                   byHeightInPixels,
                                 const Utils::DataList  &spriteData,
                                 const std::wstring     &sprite,
                                 bool                   bMirror,
                                 bool                   bJetman,
                                 bool                   bRocket)
    {
        BYTE    byHeightInBytes = byHeightInPixels / 8;

        if (byHeightInPixels % 8)
        {       
            byHeightInBytes++;
        } // Endif.

        //if (spriteData.size () % (byWidthInBytes * byHeightInBytes))
        //{
        //    _asm {int 3};
        //} // Endif.

        std::wstring    spriteName(sprite);
        spriteName [0] = std::toupper (spriteName [0]);

        WORD    wNumMovements = GetNumMovements (sprite, bMirror, bJetman, bRocket);
        WORD    wNumFrames    = GetNumFrames (sprite, bMirror, bJetman, bRocket);

        WORD    uiNumFrameBytes             = 2 * byWidthInBytes * 8 * (byHeightInBytes + 1);
        WORD    uiNumMovementBytes          = wNumFrames * uiNumFrameBytes;
        WORD    uiNumActualMovementBytes    = wNumFrames * byWidthInBytes * byHeightInPixels;

        std::ostringstream str;
        str << "// " << Utils::WideStringToNarrowString (spriteName) << "." << std::endl
            << "static  " << Utils::WideStringToNarrowString (DescribeSpriteStruct (sprite, wNumMovements, wNumFrames, uiNumFrameBytes, bJetman, bRocket)) << " g_" << Utils::WideStringToNarrowString (sprite) << " =" << std::endl
            << "{" << std::endl
            << "    0x" << std::hex << std::uppercase << std::setw (2) << std::setfill ('0') << static_cast<int> (byWidthInBytes) << ",   // Width (in bytes)." << std::endl
            << "    0x" << std::hex << std::uppercase << std::setw (2) << std::setfill ('0') << static_cast<int> (byHeightInPixels) << ",   // Height (in pixels)." << std::endl
            << "    {" << std::endl
            << "        // Top Guard." << std::endl
            << "        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00," << std::endl
            << "    }," << std::endl;

        for (WORD wMovement = 0; wMovement < wNumMovements ; ++wMovement)
        {
            str << "    // " << Utils::WideStringToNarrowString (DescribeMovement (sprite, bMirror, bJetman, bRocket, wMovement)) << " (" << std::dec << uiNumMovementBytes << " bytes)." << std::endl
                << "    {" << std::endl;

            for (WORD wFrame = 0; wFrame < wNumFrames; ++wFrame)
            {
                BYTE    byCount = 0;    // Initialise!

                if (wFrame)
                {
                    str << std::endl;
                } // Endif.
                str << "        // Frame " << std::dec << (wFrame + 1) << " glyph data (" << std::dec << uiNumFrameBytes << " bytes)." << std::endl;

                for (WORD wWidth = 0; wWidth < byWidthInBytes; ++wWidth)
                {
                    str << "        // Column " << std::dec << (wWidth + 1) << ".";

                    for (WORD wHeight = 0; wHeight < byHeightInPixels; ++wHeight)
                    {
                        if ((byCount % 8) == 0)
                        {
                            str << std::endl << "       ";
                        } // Endif.

                        byCount++;

                        BYTE    byByte = spriteData [wMovement * uiNumActualMovementBytes + wFrame * byWidthInBytes * byHeightInPixels + wHeight * byWidthInBytes + wWidth];
                        str << " 0x" << std::hex << std::uppercase << std::setw (2) << std::setfill ('0') << static_cast<int> (~byByte & 0xff) << ","
                            << " 0x" << std::hex << std::uppercase << std::setw (2) << std::setfill ('0') << static_cast<int> (byByte) << ",";
                    } // Endfor.
            
                    if (byHeightInPixels % 8)
                    {
                        for (WORD wHeight = 0; wHeight < (8 - (byHeightInPixels % 8)); ++wHeight)
                        {
                            if ((byCount % 8) == 0)
                            {
                                str << std::endl << "       ";
                            } // Endif.

                            byCount++;

                            BYTE    byByte = 0;
                            str << " 0x" << std::hex << std::uppercase << std::setw (2) << std::setfill ('0') << static_cast<int> (~byByte & 0xff) << ","
                                << " 0x" << std::hex << std::uppercase << std::setw (2) << std::setfill ('0') << static_cast<int> (byByte) << ",";
                        } // Endfor.
            
                    } // Endif.

                    str << std::endl 
                        << "        // Guard." << std::endl
                        << "        0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00," << std::endl;
                } // Endfor.

            } // Endfor.

            str << "    }," << std::endl;
        } // Endfor.

        str << "};" << std::endl
            << std::endl;

        std::string text(str.str ());

        Utils::WriteFile (L"SpriteData.h", Utils::DataList(text.begin (), text.end ()));
    } // Endproc.

    WORD            m_wStartAddress;
    WORD            m_wEndAddress;
    WORD            m_wIndex;
    BYTE            m_byZero;
    BYTE            m_byWidthInBytes;
    BYTE            m_byHeightInPixels;
    Utils::DataList m_spriteData;

private:
    static  void    DisplaySprite (BYTE     byWidthInBytes,
                                   BYTE     byHeightInPixels,
                                   const    Utils::DataList &spriteData)
    {
        Utils::ShowConsoleCursor (false);

        // Get window handle to console.

        HWND    hConsoleWnd = ::GetConsoleWindow ();

        // Get device context to console.

        HDC hConsoleDC = ::GetDC (hConsoleWnd);

        int x = X_START;
        int y = Y_START;

        COLORREF    spriteColour = ZxSpectrum::DEFAULT_COLOUR;

        for (WORD wHeight = 0; wHeight < byHeightInPixels; ++wHeight)
        {
            WORD    wHeightColourIndex = wHeight / 8 * byWidthInBytes;

            for (WORD wWidth = 0; wWidth < byWidthInBytes; ++wWidth)
            {
                BYTE    byByte = spriteData [wHeight * byWidthInBytes + wWidth];

                for (int nBit = 7; nBit >= 0; --nBit)
                {
                    COLORREF    colour = (byByte & static_cast<int> (std::pow (2, nBit))) ? spriteColour : RGB(0x00, 0x00, 0x00);

                    for (int nYScale = 0; nYScale < SCALE; ++nYScale)
                    {
                        for (int nXScale = 0; nXScale < SCALE; ++nXScale)
                        {
                            ::SetPixel (hConsoleDC, x + nXScale,  y + nYScale, colour);
                        } // Endfor.

                    } // Endfor.

                    x += SCALE;
                } // Endfor.

            } // Endfor.

            x = X_START;
            y += SCALE;
        } // Endfor.

        // Release device console DC.

        ::ReleaseDC (hConsoleWnd, hConsoleDC);
    } // Endproc.

    static  void    SaveSprite (BYTE                    byWidthInBytes,
                                BYTE                    byHeightInPixels,
                                const Utils::DataList   &spriteData,
                                const std::wstring      &fileName)
    {
        DisplaySprite (byWidthInBytes, byHeightInPixels, spriteData);

        // Get window handle to console.

        HWND    hConsoleWnd = ::GetConsoleWindow ();

        // Get device context to console.

        HDC hConsoleDC = ::GetDC (hConsoleWnd);

        // Create a device context to put it in

        HDC hMemoryDC = ::CreateCompatibleDC (hConsoleDC);

        // Create a compatible bitmap to put it in.

        HBITMAP hBitmap = CreateCompatibleBitmap (hConsoleDC, 8 * byWidthInBytes * SCALE, byHeightInPixels * SCALE);

        // Select new bitmap.

        HBITMAP hOldBitmap = static_cast<HBITMAP> (::SelectObject (hMemoryDC, hBitmap));

        // Copy new bitmap.

        ::BitBlt (hMemoryDC, 
                  0, 
                  0, 
                  8 *byWidthInBytes * SCALE, 
                  byHeightInPixels * SCALE, 
                  hConsoleDC, 
                  X_START, 
                  Y_START, 
                  SRCCOPY);

        // Restore old bitmap.
        
        ::SelectObject (hMemoryDC, hOldBitmap);

        // Delete memory DC.

        ::DeleteDC (hMemoryDC);

        // Save the bitmap.

        Utils::SaveBitmap (hBitmap, fileName);
       
        // Release device console DC.
        
        ::ReleaseDC (hConsoleWnd, hConsoleDC);
    } // Endproc.

};

typedef std::vector<CharacterSprite> CharacterSpriteList;

// Routines.

extern  void    ParseCharacterSprites (const Utils::DataList    &fileData,
                                       CharacterSpriteList      &CharacterSpriteList,
                                       AddressMap               &addressMap);

#pragma pack(pop)

/******************************* End of File *******************************/
