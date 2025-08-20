#include "Vector3_example.h"
#include <math.h>
using namespace std;
// 实现vector类的构造函数
vector3::vector3() : x(0), y(0), z(0) {}
vector3::vector3(float x, float y, float z) : x(x), y(y), z(z) {}
vector3::~vector3() {}
// 实现vector类的参数
vector3 vector3::One = vector3(1, 1, 1);
vector3 vector3::UnitX = vector3(1, 0, 0);
vector3 vector3::UnitY = vector3(0, 1, 0);
vector3 vector3::UnitZ = vector3(0, 0, 1);
vector3 vector3::Zero = vector3(0, 0, 0);
// 实现vector类的函数
vector3 vector3::Abs(vector3 value)
{
    return vector3(fabsf(value.x), fabsf(value.y), fabsf(value.z));
}
vector3 vector3::Add(vector3 left, vector3 right)
{
    return vector3(left.x + right.x, left.y + right.y, left.z + right.z);
}
vector3 vector3::Cross(vector3 v0, vector3 v1)
{
    return vector3(v0.y * v1.z - v0.z * v1.y, v0.x * v1.z - v0.z * v1.x, v0.x * v1.y - v0.y * v1.x);
}
float vector3::Distance(vector3 value1, vector3 value2)
{
    float x = value1.x - value2.x;
    float y = value1.y - value2.y;
    float z = value1.z - value2.z;
    return sqrt(x * x + y * y + z * z);
}
float vector3::DistanceSquared(vector3 value1, vector3 value2)
{
    float x = value1.x - value2.x;
    float y = value1.y - value2.y;
    float z = value1.z - value2.z;
    return x * x + y * y + z * z;
}
vector3 vector3::Divide(vector3 left, float divisor)
{
    return vector3(left.x / divisor, left.y / divisor, left.z / divisor);
}
vector3 vector3 ::Divide(vector3 left, vector3 right)
{
    return vector3(left.x / right.x, left.y / right.y, left.z / right.z);
}
float vector3::Dot(vector3 vector1, vector3 vector2)
{
    return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
}
const float vector3::Length(vector3 left)
{
    return sqrt(left.x * left.x + left.y * left.y + left.z * left.z);
}
const float vector3::LengthSquared(vector3 left)
{
    return left.x * left.x + left.y * left.y + left.z * left.z;
}
vector3 vector3::Multiply(float left, vector3 right)
{
    return vector3(right.x * left, right.y * left, right.z * left);
}
vector3 vector3::Multiply(vector3 left, float right)
{
    return vector3(right * left.x, right * left.y, right * left.z);
}
vector3 vector3::Negate(vector3 value)
{
    return vector3(-value.x, -value.y, -value.z);
}
vector3 vector3::Normalize(vector3 value)
{
    float len = value.Length(value);
    return vector3(value.x / len, value.y / len, value.z / len);
}
vector3 vector3::Subtract(vector3 left, vector3 right)
{
    return vector3(left.x - right.x, left.y - right.y, left.z - right.z);
}
// 实现运算符
vector3 operator+(vector3 left, vector3 right)
{
    return vector3(left.x + right.x, left.y + right.y, left.z + right.z);
}
vector3 operator/(vector3 left, float divisor)
{
    return vector3(left.x / divisor, left.y / divisor, left.z / divisor);
}
vector3 operator/(vector3 left, vector3 right)
{
    return vector3(left.x / right.x, left.y / right.y, left.z / right.z);
}
bool operator==(vector3 left, vector3 right)
{
    return (left.x == right.x && left.y == right.y && left.z == right.z);
}
bool operator!=(vector3 left, vector3 right)
{
    return (left.x != right.x || left.y != right.y || left.z != right.z);
}
vector3 operator*(float left, vector3 right)
{
    return vector3(right.x * left, right.y * left, right.z * left);
}
vector3 operator*(vector3 left, float right)
{
    return vector3(right * left.x, right * left.y, right * left.z);
}
vector3 operator*(vector3 left, vector3 right)
{
    return vector3(left.x * right.x, left.y * right.y, left.z * right.z);
}
vector3 operator-(vector3 left, vector3 right)
{
    return vector3(left.x - right.x, left.y - right.y, left.z - right.z);
}
vector3 operator-(vector3 value)
{
    return vector3(-value.x, -value.y, -value.z);
}