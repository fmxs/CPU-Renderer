#include "Vector4.h"
#include <math.h>
using namespace std;
// 实现vector类的构造函数
vector4::vector4() : x(0), y(0), z(0), w(0) {}
vector4::vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
vector4::~vector4() {}
// 实现vector类的参数
vector4 vector4::One = vector4(1, 1, 1, 1);
vector4 vector4::UnitX = vector4(1, 0, 0, 0);
vector4 vector4::UnitY = vector4(0, 1, 0, 0);
vector4 vector4::UnitZ = vector4(0, 0, 1, 0);
vector4 vector4::UnitW = vector4(0, 0, 0, 1);
vector4 vector4::Zero = vector4(0, 0, 0, 0);
// 实现vector类的函数
vector4 vector4::Abs(vector4 value)
{
    return vector4(fabsf(value.x), fabsf(value.y), fabsf(value.z), fabsf(value.w));
}
vector4 vector4::Add(vector4 left, vector4 right)
{
    return vector4(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
}
float vector4::Distance(vector4 value1, vector4 value2)
{
    float x = value1.x - value2.x;
    float y = value1.y - value2.y;
    float z = value1.z - value2.z;
    float w = value1.w - value2.w;
    return sqrt(x * x + y * y + z * z + w * w);
}
float vector4::DistanceSquared(vector4 value1, vector4 value2)
{
    float x = value1.x - value2.x;
    float y = value1.y - value2.y;
    float z = value1.z - value2.z;
    float w = value1.w - value2.w;
    return x * x + y * y + z * z + w * w;
}
vector4 vector4::Divide(vector4 left, float divisor)
{
    return vector4(left.x / divisor, left.y / divisor, left.z / divisor, left.w / divisor);
}
vector4 vector4::Divide(vector4 left, vector4 right)
{
    return vector4(left.x / right.x, left.y / right.y, left.z / right.z, left.w / right.w);
}
float vector4::Dot(vector4 vector1, vector4 vector2)
{
    return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z + vector1.w * vector2.w;
}
const float vector4::Length(vector4 left)
{
    return sqrt(left.x * left.x + left.y * left.y + left.z * left.z + left.w * left.w);
}
const float vector4::LengthSquared(vector4 left)
{
    return left.x * left.x + left.y * left.y + left.z * left.z + left.w * left.w;
}
vector4 vector4::Multiply(float left, vector4 right)
{
    return vector4(right.x * left, right.y * left, right.z * left, right.w * left);
}
vector4 vector4::Multiply(vector4 left, float right)
{
    return vector4(right * left.x, right * left.y, right * left.z, right * left.w);
}
vector4 vector4::Negate(vector4 value)
{
    return vector4(-value.x, -value.y, -value.z, -value.w);
}
vector4 vector4::Normalize(vector4 value)
{
    float len = value.Length(value);
    return vector4(value.x / len, value.y / len, value.z / len, value.w / len);
}
vector4 vector4::Subtract(vector4 left, vector4 right)
{
    return vector4(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
}
// 实现运算符
vector4 operator+(vector4 left, vector4 right)
{
    return vector4(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
}
vector4 operator/(vector4 left, float divisor)
{
    return vector4(left.x / divisor, left.y / divisor, left.z / divisor, left.w / divisor);
}
vector4 operator/(vector4 left, vector4 right)
{
    return vector4(left.x / right.x, left.y / right.y, left.z / right.z, left.w / right.w);
}
bool operator==(vector4 left, vector4 right)
{
    return (left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w);
}
bool operator!=(vector4 left, vector4 right)
{
    return (left.x != right.x || left.y != right.y || left.z != right.z || left.w != right.w);
}
vector4 operator*(float left, vector4 right)
{
    return vector4(right.x * left, right.y * left, right.z * left, right.w * left);
}
vector4 operator*(vector4 left, float right)
{
    return vector4(right * left.x, right * left.y, right * left.z, right * left.w);
}
vector4 operator*(vector4 left, vector4 right)
{
    return vector4(left.x * right.x, left.y * right.y, left.z * right.z, left.w * right.w);
}
vector4 operator-(vector4 left, vector4 right)
{
    return vector4(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
}
vector4 operator-(vector4 value)
{
    return vector4(-value.x, -value.y, -value.z, -value.w);
}