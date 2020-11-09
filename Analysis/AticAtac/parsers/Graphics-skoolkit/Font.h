#pragma once

#include <vector>
#include "Main.h"
#include "Utils.h"
#include "ZxSpectrum.h"

#pragma pack(push, 1)

extern  bool    IsFont (WORD wAddress);

// Definitions and Types.

struct Font
{
    static  const   BYTE    FONT_WIDTH              = 1;
    static  const   BYTE    FONT_HEIGHT_IN_PIXELS   = 8;

    Font ()
    :   m_wAddress(0),
        m_byChar(0)
    {} // Endproc.

    void    Reset ()
    {
        m_wAddress  = 0;
        m_byChar    = 0;
        m_spriteData.clear ();
    } // Endproc.

    bool    IsStarted () const
    {
        return (m_wAddress != 0);
    } // Endproc.

    bool    IsFinished () const
    {
        return (m_spriteData.size () == (FONT_WIDTH * FONT_HEIGHT_IN_PIXELS));
    } // Endproc.

    void    DisplayFont (int scale, int &x, int &y) const
    {
        Utils::ShowConsoleCursor (false);

        // Get window handle to console.

        HWND    hConsoleWnd = ::GetConsoleWindow ();

        // Get device context to console.

        HDC hConsoleDC = ::GetDC (hConsoleWnd);

        int xStart = x;
        int yStart = y;

        for (WORD wHeight = 0; wHeight < FONT_HEIGHT_IN_PIXELS; ++wHeight)
        {
            WORD    wHeightColourIndex = wHeight / 8 * FONT_WIDTH;

            for (WORD wWidth = 0; wWidth < FONT_WIDTH; ++wWidth)
            {
                BYTE    byByte = m_spriteData [wHeight * FONT_WIDTH + wWidth];

                for (int nBit = 7; nBit >= 0; --nBit)
                {
                    COLORREF    colour = (byByte & static_cast<int> (std::pow (2, nBit))) ? ZxSpectrum::DEFAULT_COLOUR : RGB(0x00, 0x00, 0x00);

                    for (int nYScale = 0; nYScale < scale; ++nYScale)
                    {
                        for (int nXScale = 0; nXScale < scale; ++nXScale)
                        {
                            ::SetPixel (hConsoleDC, x + nXScale,  y + nYScale, colour);
                        } // Endfor.

                    } // Endfor.

                    x += scale;
                } // Endfor.

            } // Endfor.

            x = xStart;
            y += scale;
        } // Endfor.

        x = xStart + 8 * scale;
        y = yStart;

        // Release device console DC.

        ::ReleaseDC (hConsoleWnd, hConsoleDC);
    } // Endproc.

    static  void    SaveFonts (int scale, int x, int y, int width, int height)
    {
        // Get window handle to console.

        HWND    hConsoleWnd = ::GetConsoleWindow ();

        // Get device context to console.

        HDC hConsoleDC = ::GetDC (hConsoleWnd);

        // Create a device context to put it in

        HDC hMemoryDC = ::CreateCompatibleDC (hConsoleDC);

        // Create a compatible bitmap to put it in.

        HBITMAP hBitmap = CreateCompatibleBitmap (hConsoleDC, width, height);

        // Select new bitmap.

        HBITMAP hOldBitmap = static_cast<HBITMAP> (::SelectObject (hMemoryDC, hBitmap));

        // Copy new bitmap.

        ::BitBlt (hMemoryDC, 
                  0, 
                  0, 
                  width, 
                  height, 
                  hConsoleDC, 
                  x, 
                  y, 
                  SRCCOPY);

        // Restore old bitmap.
        
        ::SelectObject (hMemoryDC, hOldBitmap);

        // Delete memory DC.

        ::DeleteDC (hMemoryDC);

        // Save the bitmap.

        Utils::SaveBitmap (hBitmap, L"Font.bmp");
       
        // Release device console DC.
        
        ::ReleaseDC (hConsoleWnd, hConsoleDC);
    } // Endproc.



    WORD                    m_wAddress;
    BYTE                    m_byChar;
    Utils::DataList         m_spriteData;
};

typedef std::vector<Font> FontList;

// Routines.

extern  void    ParseFonts (const Utils::DataList   &fileData,
                            FontList                &fontList,
                            AddressMap              &addressMap);

#pragma pack(pop)

/******************************* End of File *******************************/
