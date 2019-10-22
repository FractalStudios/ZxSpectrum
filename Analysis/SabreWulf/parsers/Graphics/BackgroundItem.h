#pragma once

#include <vector>
#include "Main.h"
#include "Utils.h"
#include "ZxSpectrum.h"

#pragma pack(push, 1)

// Definitions and Types.

struct BackgroundItem
{
    BackgroundItem ()
    :   m_wAddress(0),
        m_bySpriteHeightInPixels(0),
        m_bySpriteWidth(0),
        m_byAttribHeight(0),
        m_byAttribWidth(0)
    {} // Endproc.

    void    Reset ()
    {
        m_wAddress                  = 0;
        m_bySpriteHeightInPixels    = 0;
        m_bySpriteWidth             = 0;
        m_byAttribHeight            = 0;
        m_byAttribWidth             = 0;
        m_spriteData.clear ();
        m_attribData.clear ();
    } // Endproc.

    bool    IsStarted () const
    {
        return (m_wAddress != 0);
    } // Endproc.

    bool    IsSpriteDataFinished () const
    {
        return (m_spriteData.size () == (m_bySpriteWidth * m_bySpriteHeightInPixels));
    } // Endproc.

    bool    IsAttribDataFinished () const
    {
        return (m_attribData.size () == (m_byAttribWidth * m_byAttribHeight));
    } // Endproc.

    bool    operator < (const BackgroundItem &rhs) const
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

        COLORREF    spriteInkColour     = ZxSpectrum::DEFAULT_COLOUR;
        COLORREF    spritePaperColour   = ZxSpectrum::DEFAULT_COLOUR;

        UINT atribOffset = 0;

        if ((m_wAddress == 0xe3a0) ||
            (m_wAddress == 0xE67C) ||
            (m_wAddress == 0xE494) ||
            (m_wAddress == 0xE588))
        {
            atribOffset = 24;
        }


        for (WORD wHeight = 0; wHeight < m_bySpriteHeightInPixels; ++wHeight)
        {
            WORD    wHeightColourIndex = wHeight / 8 * m_byAttribWidth;

            for (WORD wWidth = 0; wWidth < m_bySpriteWidth; ++wWidth)
            {
                if ((wHeightColourIndex + wWidth) < static_cast<WORD> (m_attribData.size ()))
                {
                    spriteInkColour     = ZxSpectrum::MapInkColour (m_attribData [atribOffset  + wHeightColourIndex + wWidth]);
                    spritePaperColour   = ZxSpectrum::MapPaperColour (m_attribData [atribOffset  + wHeightColourIndex + wWidth]);
                } // Endif.

                BYTE    byByte = m_spriteData [wHeight * m_bySpriteWidth + wWidth];

                for (int nBit = 7; nBit >= 0; --nBit)
                {
                    COLORREF    colour = (byByte & static_cast<int> (std::pow (2, nBit))) ? spriteInkColour : spritePaperColour;

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

        HBITMAP hBitmap = CreateCompatibleBitmap (hConsoleDC, 8 * m_bySpriteWidth * SCALE, m_bySpriteHeightInPixels * SCALE);

        // Select new bitmap.

        HBITMAP hOldBitmap = static_cast<HBITMAP> (::SelectObject (hMemoryDC, hBitmap));

        // Copy new bitmap.

        ::BitBlt (hMemoryDC, 
                  0, 
                  0, 
                  8 * m_bySpriteWidth * SCALE, 
                  m_bySpriteHeightInPixels * SCALE, 
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
    BYTE                    m_bySpriteHeightInPixels;
    BYTE                    m_bySpriteWidth;
    BYTE                    m_byAttribHeight;
    BYTE                    m_byAttribWidth;
    Utils::DataList         m_spriteData;
    Utils::DataList         m_attribData;
};

typedef std::vector<BackgroundItem> BackgroundItemList;

// Routines.

extern  void    ParseBackgroundItems (const Utils::DataList &fileData,
                                      BackgroundItemList    &backgroundItemList,
                                      AddressMap            &addressMap);

#pragma pack(pop)

/******************************* End of File *******************************/
