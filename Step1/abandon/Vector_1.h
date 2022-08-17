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

inline void inverse(float v[3])
{
    v[0] = -v[0];
    v[1] = -v[1];
    v[2] = -v[2];
}

inline bool cmp(const float v0[3], const float v1[3])
{
    return (v0[0] > v1[0]) && (v0[1] > v1[1]) && (v0[2] > v1[2]);
}

inline void copy(const float v[3], float out[3])
{
    out[0] = v[0];
    out[1] = v[1];
    out[2] = v[2];
}

inline void add(const float v0[3], const float v1[3], float out[3])
{
    out[0] = v0[0] + v1[0];
    out[1] = v0[1] + v1[1];
    out[2] = v0[2] + v1[2];
}

inline void scale(const float v0[3], const float v1[3], float out[3])
{
    out[0] = v0[0] * v1[0];
    out[1] = v0[1] * v1[1];
    out[2] = v0[2] * v1[2];
}

inline float dist(const float p1[3], const float p2[3])
{
    float x = p1[0] - p2[0];
    float y = p1[1] - p2[1];
    float z = p1[2] - p2[2];
    return sqrt(x * x + y * y + z * z);
}

inline float length(const float v[3])
{
    float x = v[0] * v[0];
    float y = v[1] * v[1];
    float z = v[2] * v[2];
    return sqrt(x + y + z);
}

inline float dot(const float v0[3], const float v1[3])
{
    float x = v0[0] * v1[0];
    float y = v0[1] * v1[1];
    float z = v0[2] * v1[2];
    return x + y + z;
}

inline void Cross(const float v0[3], const float v1[3], float out[3])
{
    out[0] = v0[1] * v1[2] - v0[2] * v1[1];
    out[1] = v0[0] * v1[2] - v0[2] * v1[0];
    out[2] = v0[0] * v1[1] - v0[1] * v1[0];
}

inline bool Equals(const float v0[3], const float v1[3])
{
    return (v0[0] == v1[0]) && (v0[1] == v1[1]) && (v0[2] == v1[2]);
}

inline void Subtract(const float v0[3], const float v1[3], float out[3])
{
    out[0] = v0[0] - v1[0];
    out[1] = v0[1] - v1[1];
    out[2] = v0[2] - v1[2];
}
// Ctrl + Alt + N