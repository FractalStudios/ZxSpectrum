// "Home-made" includes.
#include    "..\Include\AGdiGraphicElement.h"

namespace Folio
{

namespace Core
{

namespace Graphic
{

using   namespace   Gdiplus;

/**
 * The default class constructor.
 */
AGdiGraphicElement::AGdiGraphicElement ()
:   m_screenScale(1)
{
} // Endproc.


/**
 * The class destructor.
 */
AGdiGraphicElement::~AGdiGraphicElement ()
{
} // Endproc.


#ifdef  FOLIO_DOXYGEN

/**
 * Method that is used to set the top-left hand corner of the graphic element's 
 * screen point.
 *
 * @param [in] screenXLeft
 * The screen X left positoin of the graphic element.
 *
 * @param [in] screenYTop
 * The screen Y top positoin of the graphic element.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_NOT_INITIALISED</b> if the graphic element is not initialised.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus AGdiGraphicElement::SetScreenTopLeft (Int32 screenXLeft,
                                                  Int32 screenYTop) = 0;

/**
 * Method that is used to draw the graphic element.
 *
 * @param [in, out] graphics
 * The graphics object to draw to.
 *
 * @param [out] rects
 * On return, will hold the rects of the graphic element, if successful. If 
 * this method fails then this parameter is undefined. May be zero if not 
 * required.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus AGdiGraphicElement::Draw (Gdiplus::Graphics&    graphics,
                                      RectList*             rects) = 0;

#endif


/**
 * Method that is used to get the screen rect of the graphic element.
 *
 * @return
 * The screen rect of the graphic element.
 */
Gdiplus::Rect   AGdiGraphicElement::GetScreenRect () const
{
    return (m_screenRect);
} // Endproc.


/**
 * Method that is used to get the screen X left position of the graphic element.
 *
 * @return
 * The screen X left position of the graphic element.
 */
Int32   AGdiGraphicElement::GetScreenXLeft () const
{
    return (m_screenRect.X);
} // Endproc.


/**
 * Method that is used to get the screen Y top position of the graphic element.
 *
 * @return
 * The screen Y top position of the graphic element.
 */
Int32   AGdiGraphicElement::GetScreenYTop () const
{
    return (m_screenRect.Y);
} // Endproc.


/**
 * Method that is used to get the screen X right position of the graphic element.
 *
 * @return
 * The screen X right position of the graphic element.
 */
Int32   AGdiGraphicElement::GetScreenXRight () const
{
    return (m_screenRect.X + m_screenRect.Width - 1);
} // Endproc.


/**
 * Method that is used to get the screen Y bottom position of the graphic element.
 *
 * @return
 * The screen Y bottom position of the graphic element.
 */
Int32   AGdiGraphicElement::GetScreenYBottom () const
{
    return (m_screenRect.Y + m_screenRect.Height - 1);
} // Endproc.


/**
 * Method that is used to get the screen width of the graphic element.
 *
 * @return
 * The screen width of the graphic element.
 */
Int32   AGdiGraphicElement::GetScreenWidth () const
{
    return (m_screenRect.Width);
} // Endproc.


/**
 * Method that is used to get the screen height of the graphic element.
 *
 * @return
 * The screen height of the graphic element.
 */
Int32   AGdiGraphicElement::GetScreenHeight () const
{
    return (m_screenRect.Height);
} // Endproc.


/**
 * Method that is used to set the screen scale of the graphic element.
 *
 * @param [in] screenScale
 * The screen scale.
 */
void    AGdiGraphicElement::SetScreenScale (UInt32 screenScale)
{
    m_screenScale = screenScale;

    // Set the scaled rect.

    SetScreenScaledRect ();
} // Endproc.


/**
 * Method that is used to get the screen scale of the graphic element.
 *
 * @return
 * The screen scale of the graphic element.
 */
UInt32  AGdiGraphicElement::GetScreenScale () const
{
    return (m_screenScale);
} // Endproc.


/**
 * Indicates if the specified scaled rect overlaps the scaled rect of the 
 * graphic element.
 *
 * @param [in] screenRect
 * The screen rect.
 *
 * @return
 * <b>true</b> if the specified screen rect overlaps the screen rect of the 
 * graphic element, <b>false</b> otherwise.
 */
bool    AGdiGraphicElement::IsOverlap (const Gdiplus::Rect& screenRect) const
{
    return (!((m_screenRect.X > (  screenRect.X +   screenRect.Width  - 1)) ||
                (screenRect.X > (m_screenRect.X + m_screenRect.Width  - 1)) ||
              (m_screenRect.Y > (  screenRect.Y +   screenRect.Height - 1)) ||
                (screenRect.Y > (m_screenRect.Y + m_screenRect.Height - 1))));
} // Endproc.


/**
 * Method that is used to set the screen rect of the graphic element.
 */
void    AGdiGraphicElement::SetScreenRect (const Gdiplus::Rect& screenRect)
{
    m_screenRect = screenRect;

    // Set the scaled rect.

    SetScreenScaledRect ();
} // Endproc.


/**
 * Method that is used to set the scaled rect of the graphic element.
 */
void    AGdiGraphicElement::SetScreenScaledRect ()
{
    m_scaledRect.X      = m_screenRect.X * m_screenScale;
    m_scaledRect.Y      = m_screenRect.Y * m_screenScale;
    m_scaledRect.Width  = m_screenRect.Width * m_screenScale;
    m_scaledRect.Height = m_screenRect.Height * m_screenScale;
} // Endproc.


/**
 * Method that is used to clone the specified graphic element.
 *
 * @param [in] rhs
 * The graphic element to clone.
 */
void    AGdiGraphicElement::Clone (const AGdiGraphicElement& rhs)
{
    m_screenRect    = rhs.m_screenRect; 
    m_screenScale   = rhs.m_screenScale;
    m_scaledRect    = rhs.m_scaledRect; 
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
