#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>

using namespace std;

class Vector2D
{
public:
    float x;
    float y;

    Vector2D() = default;
    Vector2D(float x, float y);

    // return the reference to the vector
    Vector2D& add(const Vector2D& vec);
    Vector2D& subtract(const Vector2D& vec);
    Vector2D& multiply(const Vector2D& vec);
    Vector2D& divide(const Vector2D& vec);

    // operator overloading
    friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);

    Vector2D& operator+=(const Vector2D& vec);
    Vector2D& operator-=(const Vector2D& vec);
    Vector2D& operator*=(const Vector2D& vec);
    Vector2D& operator/=(const Vector2D& vec);

    friend ostream& operator<<(ostream& stream, const Vector2D& vec);

};

#endif /* VECTOR_H */