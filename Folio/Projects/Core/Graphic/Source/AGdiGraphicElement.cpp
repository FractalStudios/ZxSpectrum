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
:   m_screenWidth(0),
    m_screenHeight(0), 
    m_screenScale(1)
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
 * Method that is used to draw the graphic element.
 *
 * @param [in] screenXLeft
 * The screen X left position of the graphic element.
 *
 * @param [in] screenYTop
 * The screen Y top position of the graphic element.
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
FolioStatus AGdiGraphicElement::Draw (Int32                 screenXLeft,
                                      Int32                 screenYTop,
                                      Gdiplus::Graphics&    graphics,
                                      RectList*             rects) = 0;

#endif


/**
 * Method that is used to get the screen width of the graphic element.
 *
 * @return
 * The screen width of the graphic element.
 */
Int32   AGdiGraphicElement::GetScreenWidth () const
{
    return (m_screenWidth);
} // Endproc.


/**
 * Method that is used to get the screen height of the graphic element.
 *
 * @return
 * The screen height of the graphic element.
 */
Int32   AGdiGraphicElement::GetScreenHeight () const
{
    return (m_screenHeight);
} // Endproc.


/**
 * Method that is used to set the screen scale of the graphic element.
 *
 * @param [in] screenScale
 * The screen scale.
 */
void    AGdiGraphicElement::SetScreenScale (UInt32 screenScale)
{
    m_screenScale   = screenScale;
    m_scaledWidth   = m_screenWidth * m_screenScale;
    m_scaledHeight  = m_screenHeight * m_screenScale;
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
 * Method that is used to get the scaled rect of the graphic element.
 *
 * @param [in] screenXLeft
 * The screen X left position of the graphic element.
 *
 * @param [in] screenYTop
 * The screen Y top position of the graphic element.
 *
 * @return
 * The scaled rect.
 */
Gdiplus::Rect   AGdiGraphicElement::GetScaledRect  (Int32   screenXLeft,
                                                    Int32   screenYTop) const
{
    return (Gdiplus::Rect(screenXLeft * m_screenScale, 
                          screenYTop * m_screenScale, 
                          m_scaledWidth, 
                          m_scaledHeight));
} // Endproc.


/**
 * Method that is used to get the scaled width of the graphic element.
 *
 * @return
 * The scaled width of the graphic element.
 */
Int32   AGdiGraphicElement::GetScaledWidth () const
{
    return (m_scaledWidth);
} // Endproc.


/**
 * Method that is used to get the scaled height of the graphic element.
 *
 * @return
 * The scaled height of the graphic element.
 */
Int32   AGdiGraphicElement::GetScaledHeight() const
{
    return (m_scaledHeight);
} // Endproc.


/**
 * Method that is used to set the screen width of the graphic element.
 *
 * @param [in] UInt32 screenWidth
 * The screen width of the graphic element.
 */
void    AGdiGraphicElement::SetScreenWidth (Int32 screenWidth)
{
    m_screenWidth   = screenWidth;
    m_scaledWidth   = m_screenWidth * m_screenScale;
} // Endproc.


/**
 * Method that is used to set the screen height of the graphic element.
 *
 * @param [in] UInt32 screenHeight
 * The screen height of the graphic element.
 */
void    AGdiGraphicElement::SetScreenHeight (Int32 screenHeight)
{
    m_screenHeight  = screenHeight;
    m_scaledHeight  = m_screenHeight * m_screenScale;
} // Endproc.


/**
 * Method that is used to clone the specified graphic element.
 *
 * @param [in] rhs
 * The graphic element to clone.
 */
void    AGdiGraphicElement::Clone (const AGdiGraphicElement& rhs)
{
    m_screenWidth   = rhs.m_screenWidth;
    m_screenHeight  = rhs.m_screenHeight; 
    m_screenScale   = rhs.m_screenScale;
    m_scaledWidth   = rhs.m_scaledWidth;
    m_scaledHeight  = rhs.m_scaledHeight; 
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
