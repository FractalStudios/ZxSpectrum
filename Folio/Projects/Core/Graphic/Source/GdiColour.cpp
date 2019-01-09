// "Home-made" includes.
#include    <Trace.h>
#include    "..\Include\Gdi.h"

namespace Folio
{

namespace Core
{

namespace Graphic
{

namespace Colour
{

using   namespace   Gdiplus;

/*
 * Function that is used to change the intensity of the specified colour 
 * component. The colour component may be alpha, red, green or blue.
 *
 * @param [in] intensity
 * The intensity to increase/decrease by.
 *
 * @param [in, out] colourComponent
 * The colour component to change.
 */
inline  void    ChangeColourComponentIntensity (Int32   intensity, 
                                                UInt8&  colourComponent)
{
    // Change the colour component's intensity.

    Int32   newColourComponent = colourComponent + intensity;

    if (newColourComponent < 0)
    {
        colourComponent = 0;
    } // Endif.

    else
    if (newColourComponent > 255)
    {
        colourComponent = 255;
    } // Endelseif.

    else
    {
        colourComponent = static_cast<UInt8> (newColourComponent);
    } // Endelse.

} // Endproc.


/*
 * Function that is used to change the intensity of the specified colour.
 *
 * @param [in] intensity
 * The intensity to increase/decrease by.
 *
 * @param [in, out] colour
 * The colour to change.
 */
void    ChangeColourIntensity (Int32            intensity, 
                               Gdiplus::Color&  colour)
{
    // Change the red colour component.

    UInt8   red = colour.GetR ();
    ChangeColourComponentIntensity (intensity, red);

    // Change the green colour component.

    UInt8   green = colour.GetG ();
    ChangeColourComponentIntensity (intensity, green);

    // Change the blue colour component.

    UInt8   blue = colour.GetB ();
    ChangeColourComponentIntensity (intensity, blue);

    // Change the colour.

    colour.SetValue (Color::MakeARGB (colour.GetA (),
                                      red,
                                      green,
                                      blue));
} // Endproc.


/*
 * Function that is used to change the intensity of the alpha component of the 
 * specified colour.
 *
 * @param [in] intensity
 * The intensity to increase/decrease by.
 *
 * @param [in, out] color
 * The colour to change.
 */
void    ChangeAlphaIntensity (Int32             intensity, 
                              Gdiplus::Color&   colour)
{
    // Change the alpha colour component.

    UInt8   alpha = colour.GetA ();
    ChangeColourComponentIntensity (intensity, alpha);

    // Change the colour.

    colour.SetValue (Color::MakeARGB (alpha,
                                      colour.GetR (),
                                      colour.GetG (),
                                      colour.GetB ()));
} // Endproc.


/*
 * Function that is used to change the intensity of the red component of the 
 * specified colour.
 *
 * @param [in] intensity
 * The intensity to increase/decrease by.
 *
 * @param [in, out] color
 * The colour to change.
 */
void    ChangeRedIntensity (Int32           intensity, 
                            Gdiplus::Color& colour)
{
    // Change the red colour component.

    UInt8   red = colour.GetR ();
    ChangeColourComponentIntensity (intensity, red);

    // Change the colour.

    colour.SetValue (Color::MakeARGB (colour.GetA (),
                                      red,
                                      colour.GetG (),
                                      colour.GetB ()));
} // Endproc.


/*
 * Function that is used to change the intensity of the green component of the 
 * specified colour.
 *
 * @param [in] intensity
 * The intensity to increase/decrease by.
 *
 * @param [in, out] color
 * The colour to change.
 */
void    ChangeGreenIntensity (Int32             intensity, 
                              Gdiplus::Color&   colour)
{
    // Change the green colour component.

    UInt8   green = colour.GetG ();
    ChangeColourComponentIntensity (intensity, green);

    // Change the colour.

    colour.SetValue (Color::MakeARGB (colour.GetA (),
                                      colour.GetR (),
                                      green,
                                      colour.GetB ()));
} // Endproc.


/*
 * Function that is used to change the intensity of the blue component of the 
 * specified colour.
 *
 * @param [in] intensity
 * The intensity to increase/decrease by.
 *
 * @param [in, out] color
 * The colour to change.
 */
void    ChangeBlueIntensity (Int32              intensity, 
                             Gdiplus::Color&    colour)
{
    // Change the blue colour component.

    UInt8   blue = colour.GetB ();
    ChangeColourComponentIntensity (intensity, blue);

    // Change the colour.

    colour.SetValue (Color::MakeARGB (colour.GetA (),
                                      colour.GetR (),
                                      colour.GetG (),
                                      blue));
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
