// 推导公式参考：
// https://blog.csdn.net/junzia/article/details/85939783
#pragma once
#include <math.h>
#include "Vector3.h"
#include "Matrix.h"
template <typename myT>
class View// View 矩阵
{
public:
	Mat CreateView(float posx, float posy, float posz, float tarx, float tary, float tarz, float upx, float upy, float z);
};

template<typename myT>
Mat<myT> View<myT>::CreateView(float posx, float posy, float posz, float tarx, float tary, float tarz, float upx, float upy, float upz)
{
	vector3 position(posx, posy, posz);
	vector3 target(tarx, tary, tarz);
	vector3 up(upx, upy, upz);
	vector3 N = (target - position).Normalize();
	vector3 U = U.Cross(N, up).Normalize();
	vector3 V = V.Cross(U, N).Normalize();
	N = -N;

	Mat<myT> mat(4, 4);// 在本Mat类中，初始化后矩阵的元素全为0

	mat.num[0][0] = U.x;
	mat.num[0][1] = U.y;
	mat.num[0][2] = U.z;

	mat.num[1][0] = V.x;
	mat.num[1][1] = V.y;
	mat.num[1][2] = V.z;

	mat.num[2][0] = N.x;
	mat.num[2][1] = N.y;
	mat.num[2][2] = N.z;

	mat.num[0][3] = -U.Dot(U, position);
	mat.num[1][3] = -V.Dot(V, position);
	mat.num[2][3] = -N.Dot(N, position);
	mat.num[3][3] = 1.0f;
	return mat;
}