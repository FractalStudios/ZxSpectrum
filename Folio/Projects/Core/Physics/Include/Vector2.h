#pragma once

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Physics
{

/// The 2D vector class.
/**
 * This class allows a user to control a vector in 2 dimensions.
 */
class Vector2
{
public:
    Vector2 (float x = 0, 
             float y = 0);
    ~Vector2 ();

    Vector2 (const Vector2& rhs);
    Vector2&    operator= (const Vector2& rhs);

    float   GetX () const;
    float   GetY () const;

    void    Negate ();
    void    Rotate (float angle);
    float   Normalize ();

    float   GetMagnitude () const;
    float   GetDotProduct (const Vector2& vector2) const;
    float   GetCrossProduct (const Vector2& vector2) const;

    Vector2&    operator+= (const Vector2& rhs);
    Vector2&    operator-= (const Vector2& rhs);
    Vector2&    operator*= (float scalar);
    Vector2&    operator/= (float scalar);

    const Vector2   operator+ (const Vector2& rhs) const;
    const Vector2   operator- (const Vector2& rhs) const;
    const Vector2   operator* (float scalar) const;
    const Vector2   operator/ (float scalar) const;

    bool    operator== (const Vector2& rhs) const;
    bool    operator!= (const Vector2& rhs) const;

    float   operator[] (int i);

    static Vector2 Zero ();
    static Vector2 XAxis ();
    static Vector2 YAxis ();

    static float GetDistance (const Vector2&    firstVector2, 
                              const Vector2&    secondVector2);

private:
    float   m_x;    ///< The x-component of the vector.
    float   m_y;    ///< The y-component of the vector.
}; // Endclass.

// Operators.
const Vector2 operator+ (const Vector2&  firstVector2, 
                         const Vector2&  secondVector2);
const Vector2 operator- (const Vector2&  firstVector2, 
                         const Vector2&  secondVector2);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
