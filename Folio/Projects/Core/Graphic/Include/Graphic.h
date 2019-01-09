#pragma once

// "Home-made" includes.
#include    "AGdiGraphicElement.h"
#include    "Gdi.h"
#include    "GdiBitmap.h"
#include    "GdiBufferedBitmap.h"
#include    "GdiColour.h"
#include    "GdiFont.h"
#include    "GdiRasterFont.h"
#include    "GdiRasterText.h"
#include    "GraphicConstsAndTypes.h"
#include    "GraphicMacros.h"

#ifdef _DEBUG
#pragma comment(lib, "GraphicD.lib")
#else
#pragma comment(lib, "Graphic.lib")
#endif
#pragma comment(lib, "Gdiplus.lib")

/******************************* End of File *******************************/
