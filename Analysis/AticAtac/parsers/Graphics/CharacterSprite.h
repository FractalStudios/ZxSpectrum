#pragma once

#include <vector>
#include "Main.h"
#include "Utils.h"
#include "ZxSpectrum.h"

#pragma pack(push, 1)

extern  std::wstring    DescribeCharacterSprite (WORD wAddress, bool bToSave);

// Definitions and Types.

struct CharacterSprite
{
    CharacterSprite ()
    :   m_wAddress(0),
        m_wIndex(0),
        m_byWidth(0),
        m_byHeightInPixels(0)
    {} // Endproc.

    void    Reset ()
    {
        m_wAddress          = 0;
        m_wIndex            = 0;
        m_byWidth           = 0;
        m_byHeightInPixels  = 0;
        m_spriteData.clear ();
    } // Endproc.

    bool    IsStarted () const
    {
        return (m_wAddress != 0);
    } // Endproc.

    bool    IsFinished () const
    {
        return (m_spriteData.size () == (m_byWidth * m_byHeightInPixels));
    } // Endproc.

    void    ReorderSpriteData ()
    {
        Utils::DataList tempSpriteData;

        for (Utils::DataList::reverse_iterator ritr = m_spriteData.rbegin ();
             ritr != m_spriteData.rend ();
             ritr += m_byWidth)
        {
            Utils::DataList::iterator   itr = (ritr + m_byWidth).base ();

            tempSpriteData.insert (tempSpriteData.end (),
                                   itr,
                                   itr + m_byWidth);
        } // Endfor.

        m_spriteData = tempSpriteData;
    } // Endproc.

    bool    operator < (const CharacterSprite &rhs) const
    {
        return (m_wAddress < rhs.m_wAddress);
    } // Endproc.

    static  const   int X_START = 16;
    static  const   int Y_START = 16;
    static  const   int SCALE   = 4;

    void    DisplaySprite () const
    {
        Utils::ShowConsoleCursor (false);

        // Get window handle to console.

        HWND    hConsoleWnd = ::GetConsoleWindow ();

        // Get device context to console.

        HDC hConsoleDC = ::GetDC (hConsoleWnd);

        int x = X_START;
        int y = Y_START;

        COLORREF    spriteColour = ZxSpectrum::DEFAULT_COLOUR;

        for (WORD wHeight = 0; wHeight < m_byHeightInPixels; ++wHeight)
        {
            WORD    wHeightColourIndex = wHeight / 8 * m_byWidth;

            for (WORD wWidth = 0; wWidth < m_byWidth; ++wWidth)
            {
                BYTE    byByte = m_spriteData [wHeight * m_byWidth + wWidth];

                for (int nBit = 7; nBit >= 0; --nBit)
                {
                    COLORREF    colour = (byByte & static_cast<int> (std::pow (2, nBit))) ? RGB(0xff, 0xff, 0xff): RGB(0x30, 0x30, 0x30);

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

    void    SaveSprite ()
    {
        DisplaySprite ();

        //if (m_wAddress == 0xAE0C)
        //{
        //    system ("cls");

        //    Utils::DataList data(m_spriteData);

        //    for (int n = 0; n < 8; n++)
        //    {
        //        for (Utils::DataList::iterator itr = m_spriteData.begin (); itr != m_spriteData.end (); itr += 2)
        //        {
        //            WORD    hl=MAKEWORD(*(itr+1), *itr);
        //            for (int i = 0; i < n; i++)
        //            {
        //                hl += hl;
        //            }
        //            *itr        = HIBYTE(hl);
        //            *(itr + 1)  = LOBYTE(hl);
        //        }

        //        DisplaySprite ();

        //        m_spriteData = data;
        //    }
        //} // Endif.

        // Get window handle to console.

        HWND    hConsoleWnd = ::GetConsoleWindow ();

        // Get device context to console.

        HDC hConsoleDC = ::GetDC (hConsoleWnd);

        // Create a device context to put it in

        HDC hMemoryDC = ::CreateCompatibleDC (hConsoleDC);

        // Create a compatible bitmap to put it in.

        HBITMAP hBitmap = CreateCompatibleBitmap (hConsoleDC, 8 * m_byWidth * SCALE, m_byHeightInPixels * SCALE);

        // Select new bitmap.

        HBITMAP hOldBitmap = static_cast<HBITMAP> (::SelectObject (hMemoryDC, hBitmap));

        // Copy new bitmap.

        ::BitBlt (hMemoryDC, 
                  0, 
                  0, 
                  8 * m_byWidth * SCALE, 
                  m_byHeightInPixels * SCALE, 
                  hConsoleDC, 
                  X_START, 
                  Y_START, 
                  SRCCOPY);

        // Restore old bitmap.
        
        ::SelectObject (hMemoryDC, hOldBitmap);

        // Delete memory DC.

        ::DeleteDC (hMemoryDC);

        // Save the bitmap.

        Utils::SaveBitmap (hBitmap, DescribeCharacterSprite(m_wAddress, true) + L".bmp");
       
        // Release device console DC.
        
        ::ReleaseDC (hConsoleWnd, hConsoleDC);
    } // Endproc.

    WORD            m_wAddress;
    WORD            m_wIndex;
    BYTE            m_byWidth;
    BYTE            m_byHeightInPixels;
    Utils::DataList m_spriteData;
};

typedef std::vector<CharacterSprite> CharacterSpriteList;

// Routines.

extern  void    ParseCharacterSprites (const Utils::DataList    &fileData,
                                       CharacterSpriteList      &CharacterSpriteList,
                                       AddressMap               &addressMap);

#pragma pack(pop)

/******************************* End of File *******************************/
