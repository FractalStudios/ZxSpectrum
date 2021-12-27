// STL includes.
#include    <algorithm>

// "Home-made" includes.
#include    "Vector2.h"

namespace Folio
{

namespace Core
{

namespace Physics
{

/**
 * A class constructor.
 *
 * @param [in] x
 * The x-component of the vector.
 *
 * @param [in] y
 * The y-component of the vector.
 */
Vector2::Vector2 (float x, 
                  float y)
:   m_x(x),
    m_y(y)
{
} // Endproc.


/**
 * The class destructor.
 */
Vector2::~Vector2 ()
{
} // Endproc.


/**
 * The class copy constructor.
 *
 * @param [in] rhs
 * The vector to copy to this one.
 */
Vector2::Vector2 (const Vector2& rhs)
:   m_x(rhs.m_x),
	m_y(rhs.m_y)
{
} // Endproc.


/**
 * The class assignment operator.
 *
 * @param [in] rhs
 * The vector to assign to this one.
 *
 * @return
 * The assigned vector.
 */
Vector2&    Vector2::operator= (const Vector2& rhs)
{
    // Check for self-assignment.

	if (this != &(rhs))
    {
	    m_x = rhs.m_x;
    	m_y = rhs.m_y;
    } // Endif.

	return (*this);
} // Endproc.


/**
 * Method that is used to x-component of the vector.
 *
 * @return
 * The x-component of the vector.
 */
float   Vector2::GetX () const
{
    return (m_x);
} // Endproc.


/**
 * Method that is used to y-component of the vector.
 *
 * @return
 * The y-component of the vector.
 */
float   Vector2::GetY () const
{
    return (m_y);
} // Endproc.


/**
 * Method that is used to negate the vector.
 */
void    Vector2::Negate () 
{
	m_x *= -1;
	m_y *= -1;
} // Endproc.


/**
 * Method that is used to rotate the vector by the specified angle.
 *
 * @param [in] angle
 * The angle (in radians).
 */
void    Vector2::Rotate (float angle) 
{
	float   x = (m_x * std::cos (angle)) - (m_y * std::sin (angle));
	float   y = (m_y * std::cos (angle)) + (m_x * std::sin (angle));

	m_x = x;
	m_y = y;
} // Endproc.


/**
 * Method that is used to convert the vector to a unit vector and obtain its 
 * previous magnitude.
 *
 * @return
 * The previous magnitude of the vector.
 */
float   Vector2::Normalize ()
{
    float   magnitude = GetMagnitude ();

	if (magnitude != 0.0)
    {
		m_x /= magnitude;
		m_y /= magnitude;
	} // Endif.

	return (magnitude);
} // Endproc.


/**
 * Method that is used to obtain the magnitude of the vector.
 *
 * @return
 * The magnitude of the vector.
 */
float   Vector2::GetMagnitude () const
{
    return (std::sqrt (m_x * m_x + m_y * m_y));
} // Endproc.


/**
 * Method that is used to obtain the <i>dot product</i> (or <i>scalar 
 * product</i>) of the vector and a specified vector.
 *
 * @param [in] vector2
 * The vector to calculate the dot product with.
 *
 * @return
 * The dot product of the vectors.
 */
float   Vector2::GetDotProduct (const Vector2& vector2) const
{
	return ((m_x * vector2.m_x) + (m_y * vector2.m_y));
} // Endproc.


/**
 * Method that is used to obtain the <i>cross product</i> (or <i>vector 
 * product</i>) of the vector and a specified vector. 
 *
 * In this case of a 2D vector this is the magnitide of the Z-component.
 *
 * @param [in] vector2
 * The vector to calculate the cross product with.
 *
 * @return
 * The cross product of the vectors.
 */
float   Vector2::GetCrossProduct (const Vector2& vector2) const
{
	return ((m_x * vector2.m_y) - (m_y * vector2.m_x));
} // Endproc.


/**
 * A class operator that will add the specified vector to the vector and return
 * the resulting vector.
 *
 * @param [in] rhs
 * The vector to add to this one.
 *
 * @return
 * The resulting vector.
 */
Vector2&    Vector2::operator+= (const Vector2& rhs)
{
	m_x += rhs.m_x;
	m_y += rhs.m_y;

	return (*this);
} // Endproc.


/**
 * A class operator that will subtract the specified vector from the vector and 
 * return the resulting vector.
 *
 * @param [in] rhs
 * The vector to subtract from this one.
 *
 * @return
 * The resulting vector.
 */
Vector2&    Vector2::operator-= (const Vector2& rhs)
{
	m_x -= rhs.m_x;
	m_y -= rhs.m_y;

	return (*this);
} // Endproc.


/**
 * A class operator that will multiply the specified scalar with the vector and 
 * return the resulting vector.
 *
 * @param [in] scalar
 * The scalar to multiply.
 *
 * @return
 * The resulting vector.
 */
Vector2&    Vector2::operator*= (float scalar)
{
	m_x *= scalar;
	m_y *= scalar;

	return (*this);
} // Endproc.


/**
 * A class operator that will divide the specified scalar from the vector and return
 * the resulting vector.
 *
 * @param [in] scalar
 * The scalar to divide.
 *
 * @return
 * The resulting vector.
 */
Vector2&    Vector2::operator/= (float scalar)
{
    if (scalar != 0.0)
    {
    	m_x /= scalar;
	    m_y /= scalar;
    } // Endif.

	return (*this);
} // Endproc.


/**
 * A class operator that will add the specified vector to the vector and return 
 * a copy of the resulting vector.
 *
 * @param [in] rhs
 * The vector to add.
 *
 * @return
 * A copy of the resulting vector.
 */
const Vector2   Vector2::operator+ (const Vector2& rhs) const 
{
    return (Vector2(m_x + rhs.m_x, m_y + rhs.m_y));
} // Endproc.


/**
 * A class operator that will subtract the specified vector to the vector and 
 * return a copy of the resulting vector.
 *
 * @param [in] rhs
 * The vector to subtract.
 *
 * @return
 * A copy of the resulting vector.
 */
const Vector2   Vector2::operator- (const Vector2& rhs) const
{
    return (Vector2(m_x - rhs.m_x, m_y - rhs.m_y));
} // Endproc.


/**
 * A class operator that will multiply the specified scalar with the vector and 
 * return a copy of the resulting vector.
 *
 * @param [in] scalar
 * The scalar to multiply.
 *
 * @return
 * A copy of the resulting vector.
 */
const Vector2   Vector2::operator* (float scalar) const
{
    return (Vector2(m_x * scalar, m_y * scalar));
} // Endproc.


/**
 * A class operator that will divide the specified scalar from the vector and 
 * return a copy of the resulting vector.
 *
 * @param [in] scalar
 * The scalar to divide.
 *
 * @return
 * A copy of the resulting vector.
 */
const Vector2   Vector2::operator/ (float scalar) const
{
    if (scalar == 0.0)
    {
        return (Vector2(0.0, 0.0));
    } // Endif.

    else
    {
        return (Vector2(m_x / scalar, m_y / scalar));
    } // Endelse.

} // Endproc.


/**
 * A class operator that will compare the specified vector with the vector for 
 * equality.
 *
 * @param [in] rhs
 * The vector to compare to this one.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>true</b> if the vector are the same.
 * <li><b>false</b> otherwise.
 * </ul>
 */
bool    Vector2::operator== (const Vector2& rhs) const 
{
	return ((m_x == rhs.m_x) && (m_y == rhs.m_y));
} // Endproc.


/**
 * A class operator that will compare the specified vector with the vector for 
 * inequality.
 *
 * @param [in] rhs
 * The vector to compare to this one.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>true</b> if the vector are not the same.
 * <li><b>false</b> otherwise.
 * </ul>
 */
bool    Vector2::operator!= (const Vector2& rhs) const
{
	return (!((m_x == rhs.m_x) && (m_y == rhs.m_y)));
} // Endproc.


/**
 * A class operator that will return the value of the component at the 
 * specified index. If the index is greater than 1 then the y-component is returned.
 *
 * @param [in] index
 * The index of the component to return.
 *
 * @return
 * The value of the component at the specified index.
 */
float   Vector2::operator[] (int i)
{
    switch (i)
    {
    case 0:
        return (m_x);
    default:
        return (m_y);
    } // Endswitch.

} // Endproc.


/**
 * Method that is used to obtain an empty vector.
 *
 * @return
 * An empty vector.
 */
Vector2   Vector2::Zero ()
{
	return (Vector2 (0.0, 0.0));
} // Endproc.


/**
 * Method that is used to obtain a vector along the x-axis.
 *
 * @return
 * A vector along the x-axis.
 */
Vector2   Vector2::XAxis ()
{
	return (Vector2 (1.0, 0.0));
} // Endproc.


/**
 * Method that is used to obtain a vector along the y-axis.
 *
 * @return
 * A vector along the y-axis.
 */
Vector2   Vector2::YAxis ()
{
	return (Vector2 (0.0, 1.0));
} // Endproc.


/**
 * Method that is used to obtain the distance between two vectors.
 *
 * @param [in] firstVector2
 * The first vector.
 *
 * @param [in] secondVector2
 * The second vector.
 *
 * @return
 * The distance between the two vectors.
 */
float   Vector2::GetDistance (const Vector2& firstVector2, 
                              const Vector2& secondVector2)
{
    return (std::sqrt (std::pow ((secondVector2.m_x - firstVector2.m_x), 2) +
                       std::pow ((secondVector2.m_y - firstVector2.m_y), 2)));
} // Endproc.


/**
 * Operator that is used to add two vectors.
 *
 * @param [in] firstVector2
 * The first vector.
 *
 * @param [in] secondVector2
 * The second vector.
 *
 * @return
 * A copy of the resulting vector.
 */
const Vector2   operator+ (const Vector2&   firstVector2, 
                           const Vector2&   secondVector2)
{
    return (Vector2(firstVector2.GetX () + secondVector2.GetX (), 
                    firstVector2.GetY () + secondVector2.GetY ()));
} // Endproc.


/**
 * Operator that is used to subtract two vectors.
 *
 * @param [in] firstVector2
 * The first vector.
 *
 * @param [in] secondVector2
 * The second vector.
 *
 * @return
 * A copy of the resulting vector.
 */
const Vector2   operator- (const Vector2&   firstVector2, 
                           const Vector2&   secondVector2)
{
    return (Vector2(firstVector2.GetX () - secondVector2.GetX (), 
                    firstVector2.GetY () - secondVector2.GetY ()));
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
