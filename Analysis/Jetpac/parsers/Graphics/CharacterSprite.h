#pragma once

#include <vector>
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
