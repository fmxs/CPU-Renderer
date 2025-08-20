// 推导公式参考：
// https://blog.csdn.net/junzia/article/details/85939783
#pragma once
#include <math.h>
#include "Vector3.h"
#include "Matrix.h"
template <typename myT>
class Projection// Projection 矩阵
{
public:
	// 正交矩阵
	Mat CreateOrthogonal(float left, float right, float top, float bottom, float near, float far);
	// 透视矩阵
	Mat CreatePerspective(float fov, float aspect, float near, float far);
};


/// <summary>
/// 创建正交投影矩阵
/// </summary>
/// <typeparam name="myT"></typeparam>
/// <param name="left">需要变换的长方体的左侧</param>
/// <param name="right">需要变换的长方体的右侧</param>
/// <param name="top">需要变换的长方体的顶部</param>
/// <param name="bottom">需要变换的长方体的底部</param>
/// <param name="near">近平面</param>
/// <param name="far">远平面</param>
/// <returns>正交投影矩阵</returns>
template<typename myT>
Mat<myT> Projection<myT>::CreateOrthogonal(float left, float right, float top, float bottom, float near, float far)
{
	Mat<myT> mat(4, 4);// 在本Mat类中，初始化后矩阵的元素全为0
	mat.num[0][0] = 2 / (right - left);
	mat.num[1][1] = 2 / (top - bottom);
	mat.num[2][2] = 2 / (near - far);
	mat.num[3][3] = 1.0f;

	mat.num[0][3] = -(right + left) / (right - left);
	mat.num[1][3] = -(top + bottom) / (top - bottom);
	mat.num[2][3] = -(near + far) / (far - near);
	return mat;
}


template<typename myT>
Mat<myT> Projection<myT>::CreatePerspective(float fov, float aspect, float near, float far)// 透视矩阵
{
	Mat<myT> mat(4, 4);// 在本Mat类中，初始化后矩阵的元素全为0
	mat.num[0][0] = 1 / tanf(fov / 2);
	mat.num[1][1] = 1 / aspect * tanf(fov / 2);
	mat.num[2][2] = -(far + near) / (far - near);
	mat.num[3][2] = -1.0f;
	mat.num[2][3] = 2 * near * far / (near - far);
	return mat;
}