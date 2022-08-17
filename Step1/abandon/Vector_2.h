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
protected:
public:
    float v[3];
    Vector3(float x, float y, float z)
    {
        v[0] = x;
        v[1] = y;
        v[2] = z;
    }

    float x()
    {
        return v[0];
    }

    float y()
    {
        return v[1];
    }

    float z()
    {
        return v[2];
    }

    inline void inverse()
    {
        v[0] = -v[0];
        v[1] = -v[1];
        v[2] = -v[2];
    }

    inline bool cmp(const Vector3 v0, const Vector3 v1)
    {
        return (v0.v[0] > v1.v[0]) && (v0.v[1] > v1.v[1]) && (v0.v[2] > v1.v[2]);
    }

    inline void copy(const Vector3 v, Vector3 out)
    {
        out.v[0] = v.v[0];
        out.v[1] = v.v[1];
        out.v[2] = v.v[2];
    }

private:
};