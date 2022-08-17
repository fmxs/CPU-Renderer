/*
 * @Author: 方墨小生
 * @Date: 2022-08-01 16:37:36
 * @LastEditors: 方墨小生
 * @LastEditTime: 2022-08-03 16:12:36
 * @FilePath: \Shader\vector.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 * 代码来源：https://noobtuts.com/cpp/fast-vector3-class
 */
#include <math.h>
using namespace std;
class Vector3
{
public:
    float x;
    float y;
    float z;
    Vector3() : x(0), y(0), z(0) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    ~Vector3() {}

    static Vector3 Add(
        Vector3 left,
        Vector3 right);

    // Gets a vector whose 3 elements are equal to one.
    inline Vector3 One() { return Vector3(1, 1, 1); }

    // Gets the vector (1,0,0).
    inline Vector3 UnitX() { return Vector3(1, 0, 0); }

    // Gets the vector (0,1,0).
    inline Vector3 UnitY() { return Vector3(0, 1, 0); }

    // Gets the vector (0,0,1).
    inline Vector3 UnitZ() { return Vector3(0, 0, 1); }

    // Gets a vector whose 3 elements are equal to zero.
    inline Vector3 Zero() { return Vector3(0, 0, 0); }

    // Returns a vector whose elements are the absolute values of each of the specified vector's elements.
    inline Vector3 Abs() { return Vector3(abs(x), abs(y), abs(z)); }

    // Adds two vectors together.
    static Vector3 Add(const Vector3 v0, const Vector3 v1) { return Vector3(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z); }

    // Subtracts the second vector from the first.
    inline Vector3 Subtract(const Vector3 v0, const Vector3 v1) { return Vector3(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z); }

    // Determines the cross product of two 3-D vectors.
    inline static Vector3 Cross(const Vector3 v0, const Vector3 v1)
    {
        float x = v0.y * v1.z - v0.z * v1.y;
        float y = v0.x * v1.z - v0.z * v1.x;
        float z = v0.x * v1.y - v0.y * v1.x;
        return Vector3(x, y, z);
    }

    // Determines the dot product of two 3-D vectors.
    inline static float Dot(const Vector3 left, const Vector3 right) { return left.x * right.x + left.y * right.y + left.z * right.z; }
};