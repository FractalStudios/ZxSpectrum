#pragma once

#include <vector>
#include "BackgroundItemAttrib.h"
#include "Main.h"
#include "Utils.h"
#include "ZxSpectrum.h"

#pragma pack(push, 1)


extern  bool    IsBackgroundItemSprite (WORD wAddress, WORD &wIndex);
extern  std::wstring    DescribeBackgroundItemSprite (WORD wAddress, bool bStripWhiteSpace = false, WORD wAttribAddress = 0);


// Definitions and Types.

struct BackgroundItemSprite
{
    BackgroundItemSprite ()
    :   m_wIndex(0),
        m_wAddress(0),
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
        m_backgroundItemAttrib.Reset ();
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

    bool    operator == (WORD wAddress) const
    {
        return (m_wAddress == wAddress);
    } // Endproc.

    bool    operator < (const BackgroundItemSprite &rhs) const
    {
        return (m_wAddress < rhs.m_wAddress);
    } // Endproc.

    static  const   int X_START = 16;
    static  const   int Y_START = 16;
    static  const   int SCALE   = 1;

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
                if ((wHeightColourIndex + wWidth) < static_cast<WORD> (m_backgroundItemAttrib.m_colourData.size ()))
                {
                    spriteColour = ZxSpectrum::MapInkColour (m_backgroundItemAttrib.m_colourData [wHeightColourIndex + wWidth]);
                } // Endif.

                BYTE    byByte = m_spriteData [wHeight * m_byWidth + wWidth];

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

    void    SaveSprite () const
    {
        DisplaySprite ();

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

        Utils::SaveBitmap (hBitmap, DescribeBackgroundItem (m_wAddress) + L".bmp");
       
        // Release device console DC.
        
        ::ReleaseDC (hConsoleWnd, hConsoleDC);
    } // Endproc.

    WORD                    m_wAddress;
    WORD                    m_wIndex;
    BYTE                    m_byWidth;
    BYTE                    m_byHeightInPixels;
    Utils::DataList         m_spriteData;
    BackgroundItemAttrib    m_backgroundItemAttrib;
};

typedef std::vector<BackgroundItemSprite> BackgroundItemSpriteList;

// Routines.

extern  void    ParseBackgroundItemSprites (const Utils::DataList           &fileData,
                                            const BackgroundItemAttribList  &backgroundItemAttribList,
                                            BackgroundItemSpriteList        &backgroundItemSpriteList,
                                            AddressMap                      &addressMap);

#pragma pack(pop)

/******************************* End of File *******************************/
