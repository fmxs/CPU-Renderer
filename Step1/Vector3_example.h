#ifndef _VECTOR3_H_
#define _VECTOR3_H_
#include <math.h>
using namespace std;

class vector3
{
public:
    float x; // The X component of the vector.
    float y; // The Y component of the vector.
    float z; // The Z component of the vector.

    vector3();
    vector3(float x, float y, float z); // Creates a vector whose elements have the specified values.
    ~vector3();

    static vector3 One;   // Gets a vector whose 3 elements are equal to one.
    static vector3 UnitX; // Gets the vector (1,0,0).
    static vector3 UnitY; // Gets the vector (0,1,0).
    static vector3 UnitZ; // Gets the vector (0,0,1).
    static vector3 Zero;  // Gets a vector whose 3 elements are equal to zero.

    static vector3 Abs(vector3 value);                            // Returns a vector whose elements are the absolute values of each of the specified vector's elements.
    static vector3 Add(vector3 left, vector3 right);              // Adds two vectors together.
    static vector3 Cross(vector3 vector1, vector3 vector2);       // Computes the cross product of two vectors.
    static float Distance(vector3 value1, vector3 value2);        // Computes the Euclidean distance between the two given points.
    static float DistanceSquared(vector3 value1, vector3 value2); // Returns the Euclidean distance squared between two specified points.
    static vector3 Divide(vector3 left, float divisor);           // Divides the specified vector by a specified scalar value.
    static vector3 Divide(vector3 left, vector3 right);           // Divides the first vector by the second.
    static float Dot(vector3 vector1, vector3 vector2);           // Returns the dot product of two vectors.
    const float Length(vector3 left);                             // Returns the length of this vector object.
    const float LengthSquared(vector3 left);                      // Returns the length of the vector squared.
    static vector3 Multiply(float left, vector3 right);           // Multiplies a scalar value by a specified vector.
    static vector3 Multiply(vector3 left, float right);           // Multiplies a vector by a specified scalar.
    static vector3 Negate(vector3 value);                         // Negates a specified vector.
    static vector3 Normalize(vector3 value);                      // Returns a vector with the same direction as the specified vector, but with a length of one.
    static vector3 Subtract(vector3 left, vector3 right);         // Subtracts the second vector from the first.
};

static vector3 operator+(vector3 left, vector3 right);  // Adds two vectors together.
static vector3 operator/(vector3 value1, float value2); // Divides the specified vector by a specified scalar value.
static vector3 operator/(vector3 left, vector3 right);  // Divides the first vector by the second.
static bool operator==(vector3 left, vector3 right);    // Returns a value that indicates whether each pair of elements in two specified vectors is equal.
static bool operator!=(vector3 left, vector3 right);    // Returns a value that indicates whether two specified vectors are not equal.
static vector3 operator*(float left, vector3 right);    // Multiples the scalar value by the specified vector.
static vector3 operator*(vector3 left, float right);    // Multiples the specified vector by the specified scalar value.
static vector3 operator*(vector3 left, vector3 right);  // Returns a new vector whose values are the product of each pair of elements in two specified vectors.
static vector3 operator-(vector3 left, vector3 right);  // Subtracts the second vector from the first.
static vector3 operator-(vector3 value);                // Negates the specified vector.
#endif