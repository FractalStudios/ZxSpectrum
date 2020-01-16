// STL includes.
#include    <algorithm>

// "Home-made" includes.
#include    "Vector3.h"

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
 *
 * @param [in] z
 * The z-component of the vector.
 */
Vector3::Vector3 (float x, 
                  float y,
                  float z)
:   m_x(x),
    m_y(y),
    m_z(z)
{
} // Endproc.


/**
 * The class destructor.
 */
Vector3::~Vector3 ()
{
} // Endproc.


/**
 * The class copy constructor.
 *
 * @param [in] rhs
 * The vector to copy to this one.
 */
Vector3::Vector3 (const Vector3 &rhs)
:   m_x(rhs.m_x),
	m_y(rhs.m_y),
	m_z(rhs.m_z)
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
Vector3&    Vector3::operator= (const Vector3& rhs)
{
    // Check for self-assignment.

	if (this != &(rhs))
    {
	    m_x = rhs.m_x;
    	m_y = rhs.m_y;
    	m_z = rhs.m_z;
    } // Endif.

	return (*this);
} // Endproc.


/**
 * Method that is used to x-component of the vector.
 *
 * @return
 * The x-component of the vector.
 */
float   Vector3::GetX () const
{
    return (m_x);
} // Endproc.


/**
 * Method that is used to y-component of the vector.
 *
 * @return
 * The y-component of the vector.
 */
float   Vector3::GetY () const
{
    return (m_y);
} // Endproc.


/**
 * Method that is used to z-component of the vector.
 *
 * @return
 * The z-component of the vector.
 */
float   Vector3::GetZ () const
{
    return (m_z);
} // Endproc.


/**
 * Method that is used to negate the vector.
 */
void    Vector3::Negate () 
{
	m_x *= -1;
	m_y *= -1;
	m_z *= -1;
} // Endproc.


/**
 * Method that is used to convert the vector to a unit vector and obtain its 
 * previous magnitude.
 *
 * @return
 * The previous magnitude of the vector.
 */
float   Vector3::Normalize ()
{
    float   magnitude = GetMagnitude ();

	if (magnitude != 0.0)
    {
		m_x /= magnitude;
		m_y /= magnitude;
		m_z /= magnitude;
	} // Endif.

	return (magnitude);
} // Endproc.


/**
 * Method that is used to obtain the magnitude of the vector.
 *
 * @return
 * The magnitude of the vector.
 */
float   Vector3::GetMagnitude () const
{
    return (std::sqrt (m_x * m_x + m_y * m_y + m_z * m_z));
} // Endproc.


/**
 * Method that is used to obtain the <i>dot product</i> (or <i>scalar 
 * product</i>) of the vector and a specified vector.
 *
 * @param [in] vector3
 * The vector to calculate the dot product with.
 *
 * @return
 * The dot product of the vectors.
 */
float   Vector3::GetDotProduct (const Vector3& vector3) const
{
	return ((m_x * vector3.m_x) + (m_y * vector3.m_y) + (m_z * vector3.m_z));
} // Endproc.


/**
 * Method that is used to obtain the <i>cross product</i> (or <i>vector 
 * product</i>) of the vector and a specified vector. 
 *
 * @param [in] vector3
 * The vector to calculate the cross product with.
 *
 * @return
 * The cross product of the vectors.
 */
Vector3 Vector3::GetCrossProduct (const Vector3& vector3) const
{
	return (Vector3((m_y * vector3.m_z) - (m_z * vector3.m_y),
                    (m_z * vector3.m_x) - (m_x * vector3.m_z),
                    (m_x * vector3.m_y) - (m_y * vector3.m_x)));
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
Vector3&    Vector3::operator+= (const Vector3& rhs)
{
	m_x += rhs.m_x;
	m_y += rhs.m_y;
	m_z += rhs.m_z;

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
Vector3&    Vector3::operator-= (const Vector3& rhs)
{
	m_x -= rhs.m_x;
	m_y -= rhs.m_y;
	m_z -= rhs.m_z;

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
Vector3&    Vector3::operator*= (float scalar)
{
	m_x *= scalar;
	m_y *= scalar;
	m_z *= scalar;

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
Vector3&    Vector3::operator/= (float scalar)
{
    if (scalar != 0.0)
    {
    	m_x /= scalar;
	    m_y /= scalar;
	    m_z /= scalar;
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
const Vector3   Vector3::operator+ (const Vector3& rhs) const 
{
    return (Vector3(m_x + rhs.m_x, m_y + rhs.m_y, m_z + rhs.m_z));
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
const Vector3   Vector3::operator- (const Vector3& rhs) const
{
    return (Vector3(m_x - rhs.m_x, m_y - rhs.m_y, m_z - rhs.m_z));
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
const Vector3   Vector3::operator* (float scalar) const
{
    return (Vector3(m_x * scalar, m_y * scalar, m_z * scalar));
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
const Vector3   Vector3::operator/ (float scalar) const
{
    if (scalar == 0.0)
    {
        return (Vector3(0.0, 0.0, 0.0));
    } // Endif.

    else
    {
        return (Vector3(m_x / scalar, m_y / scalar, m_z / scalar));
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
bool    Vector3::operator== (const Vector3& rhs) const 
{
	return ((m_x == rhs.m_x) && (m_y == rhs.m_y) && (m_z == rhs.m_z));
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
bool    Vector3::operator!= (const Vector3& rhs) const
{
	return (!((m_x == rhs.m_x) && (m_y == rhs.m_y) && (m_z == rhs.m_z)));
} // Endproc.


/**
 * A class operator that will return the value of the component at the 
 * specified index. If the index is greater than 2 then the z-component is returned.
 *
 * @param [in] index
 * The index of the component to return.
 *
 * @return
 * The value of the component at the specified index.
 */
float   Vector3::operator[] (int i)
{
    switch (i)
    {
    case 0:
        return (m_x);
    case 1:
        return (m_y);
    default:
        return (m_z);
    } // Endswitch.

} // Endif.


/**
 * Method that is used to obtain an empty vector.
 *
 * @return
 * An empty vector.
 */
Vector3   Vector3::Zero ()
{
	return (Vector3 (0.0, 0.0, 0.0));
} // Endproc.


/**
 * Method that is used to obtain a vector along the x-axis.
 *
 * @return
 * A vector along the x-axis.
 */
Vector3   Vector3::XAxis ()
{
	return (Vector3 (1.0, 0.0, 0.0));
} // Endproc.


/**
 * Method that is used to obtain a vector along the y-axis.
 *
 * @return
 * A vector along the y-axis.
 */
Vector3   Vector3::YAxis ()
{
	return (Vector3 (0.0, 1.0, 0.0));
} // Endproc.


/**
 * Method that is used to obtain a vector along the z-axis.
 *
 * @return
 * A vector along the z-axis.
 */
Vector3   Vector3::ZAxis ()
{
	return (Vector3 (0.0, 0.0, 1.0));
} // Endproc.


/**
 * Method that is used to obtain the distance between two vectors.
 *
 * @param [in] firstVector3
 * The first vector.
 *
 * @param [in] secondVector3
 * The second vector.
 *
 * @return
 * The distance between the two vectors.
 */
float   Vector3::GetDistance (const Vector3& firstVector3, 
                              const Vector3& secondVector3)
{
    return (std::sqrt (std::pow ((secondVector3.m_x - firstVector3.m_x), 2) +
                       std::pow ((secondVector3.m_y - firstVector3.m_y), 2) + 
                       std::pow ((secondVector3.m_z - firstVector3.m_z), 2)));
} // Endproc.


/**
 * Operator that is used to add two vectors.
 *
 * @param [in] firstVector3
 * The first vector.
 *
 * @param [in] secondVector3
 * The second vector.
 *
 * @return
 * A copy of the resulting vector.
 */
const Vector3   operator+ (const Vector3&   firstVector3, 
                           const Vector3&   secondVector3)
{
    return (Vector3(firstVector3.GetX () + secondVector3.GetX (), 
                    firstVector3.GetY () + secondVector3.GetY (),
                    firstVector3.GetZ () + secondVector3.GetZ ()));
} // Endproc.


/**
 * Operator that is used to subtract two vectors.
 *
 * @param [in] firstVector3
 * The first vector.
 *
 * @param [in] secondVector3
 * The second vector.
 *
 * @return
 * A copy of the resulting vector.
 */
const Vector3   operator- (const Vector3&   firstVector3, 
                           const Vector3&   secondVector3)
{
    return (Vector3(firstVector3.GetX () - secondVector3.GetX (), 
                    firstVector3.GetY () - secondVector3.GetY (),
                    firstVector3.GetZ () - secondVector3.GetZ ()));
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
