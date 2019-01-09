#pragma once

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Physics
{

/// The 3D vector class.
/**
 * This class allows a user to control a vector in 3 dimensions.
 */
class Vector3
{
public:
    Vector3 (float x = 0, 
             float y = 0,
             float z = 0);
    ~Vector3 ();

    Vector3 (const Vector3& rhs);
    Vector3&    operator= (const Vector3& rhs);

    float   GetX () const;
    float   GetY () const;
    float   GetZ () const;

    void    Negate ();
    float   Normalize ();

    float   GetMagnitude () const;
    float   GetDotProduct (const Vector3& vector3) const;
    Vector3 GetCrossProduct (const Vector3& vector3) const;

    Vector3&    operator+= (const Vector3& rhs);
    Vector3&    operator-= (const Vector3& rhs);
    Vector3&    operator*= (float scalar);
    Vector3&    operator/= (float scalar);

    const Vector3   operator+ (const Vector3& rhs) const;
    const Vector3   operator- (const Vector3& rhs) const;
    const Vector3   operator* (float scalar) const;
    const Vector3   operator/ (float scalar) const;

    bool    operator== (const Vector3& rhs) const;
    bool    operator!= (const Vector3& rhs) const;

    float   operator[] (int i);

    static Vector3 Zero ();
    static Vector3 XAxis ();
    static Vector3 YAxis ();
    static Vector3 ZAxis ();

    static float GetDistance (const Vector3&    firstVector3, 
                              const Vector3&    secondVector3);

private:
    float   m_x;    ///< The x-component of the vector.
    float   m_y;    ///< The y-component of the vector.
    float   m_z;    ///< The z-component of the vector.
}; // Endclass.

// Operators.
const Vector3 operator+ (const Vector3&  firstVector3, 
                         const Vector3&  secondVector3);
const Vector3 operator- (const Vector3&  firstVector3, 
                         const Vector3&  secondVector3);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
