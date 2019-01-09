// "Home-made" includes.
#include    "IGraphicElement.h"

namespace Folio
{

namespace Core
{

namespace Physics
{

/**
 * The class destructor.
 */
IGraphicElement::~IGraphicElement ()
{
} // Endproc.


#ifdef  FOLIO_DOXYGEN

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
FolioStatus IGraphicElement::Draw (Gdiplus::Graphics&   graphics,
                                   RectList*            rects) = 0;

#endif

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
