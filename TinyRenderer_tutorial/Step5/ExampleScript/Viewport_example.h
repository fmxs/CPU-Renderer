// 推导公式参考：
// https://blog.csdn.net/junzia/article/details/85939783
#pragma once
#include <math.h>
#include "Vector3.h"
#include "Matrix.h"
template <typename myT>
class Viewport// 视口矩阵
{
public:
	Mat CreateViewport(int x, int y, int width, int height);
};

template<typename myT>
Mat<myT> Viewport<myT>::CreateViewport(int x, int y, int width, int height)
{
	Mat<myT> mat(4, 4);
	mat.num[0][0] = width / 2;
	mat.num[0][3] = width / 2 + x;
	mat.num[1][1] = height / 2;
	mat.num[1][3] = height / 2 + y;
	mat.num[2][2] = 1;
	mat.num[3][3] = 1;
	return mat;
}