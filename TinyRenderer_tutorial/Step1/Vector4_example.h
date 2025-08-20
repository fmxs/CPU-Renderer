#ifndef _VECTOR4_H_
#define _VECTOR4_H_

#include <math.h>
using namespace std;

class vector4
{
private:
    /* data */

public:
    float w; //	The W component of the vector.
    float x; // The X component of the vector.
    float y; // The Y component of the vector.
    float z; // The Z component of the vector.

    vector4();
    vector4(float x, float y, float z, float w); // Creates a vector whose elements have the specified values.
    ~vector4();

    static vector4 One;   // Gets a vector whose 3 elements are equal to one.
    static vector4 UnitX; // Gets the vector (1,0,0,0).
    static vector4 UnitY; // Gets the vector (0,1,0,0).
    static vector4 UnitZ; // Gets the vector (0,0,1,0).
    static vector4 UnitW; // Gets the vector (0,0,0,1).
    static vector4 Zero;  // Gets a vector whose 4 elements are equal to zero.
    static vector4 Abs(vector4 value);                            // Returns a vector whose elements are the absolute values of each of the specified vector's elements.
    static vector4 Add(vector4 left, vector4 right);              // Adds two vectors together.
    static float Distance(vector4 value1, vector4 value2);        // Computes the Euclidean distance between the two given points.
    static float DistanceSquared(vector4 value1, vector4 value2); // Returns the Euclidean distance squared between two specified points.
    static vector4 Divide(vector4 left, float divisor);           // Divides the specified vector by a specified scalar value.
    static vector4 Divide(vector4 left, vector4 right);           // Divides the first vector by the second.
    static float Dot(vector4 vector1, vector4 vector2);           // Returns the dot product of two vectors.
    const float Length(vector4 left);                             // Returns the length of this vector object.
    const float LengthSquared(vector4 left);                      // Returns the length of the vector squared.
    static vector4 Multiply(float left, vector4 right);           // Multiplies a scalar value by a specified vector.
    static vector4 Multiply(vector4 left, float right);           // Multiplies a vector by a specified scalar.
    static vector4 Negate(vector4 value);                         // Negates a specified vector.
    static vector4 Normalize(vector4 value);                      // Returns a vector with the same direction as the specified vector, but with a length of one.
    static vector4 Subtract(vector4 left, vector4 right);         // Subtracts the second vector from the first.
};

static vector4 operator+(vector4 left, vector4 right);  // Adds two vectors together.
static vector4 operator/(vector4 value1, float value2); // Divides the specified vector by a specified scalar value.
static vector4 operator/(vector4 left, vector4 right);  // Divides the first vector by the second.
static bool operator==(vector4 left, vector4 right);    // Returns a value that indicates whether each pair of elements in two specified vectors is equal.
static bool operator!=(vector4 left, vector4 right);    // Returns a value that indicates whether two specified vectors are not equal.
static vector4 operator*(float left, vector4 right);    // Multiples the scalar value by the specified vector.
static vector4 operator*(vector4 left, float right);    // Multiples the specified vector by the specified scalar value.
static vector4 operator*(vector4 left, vector4 right);  // Returns a new vector whose values are the product of each pair of elements in two specified vectors.
static vector4 operator-(vector4 left, vector4 right);  // Subtracts the second vector from the first.
static vector4 operator-(vector4 value);                // Negates the specified vector.
#endif