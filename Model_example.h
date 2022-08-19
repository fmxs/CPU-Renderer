#pragma once
#include <math.h>
#include "Vector3.h"
#include "Matrix.h"
#include "Vector4.h"
template <typename myT>
class Model
{
private:
	vector3 localPosition;// 本地坐标系的坐标
	vector4 quaternion;// 四元数
public:
	Model();
	Model(float x,float y,float z);
	Model(vector3 pos, vector4 q);
	// 平移矩阵
	Mat GetTranslate(float worldx, float worldy, float worldz);
	// 缩放矩阵
	Mat GetScale(float x, float y, float z);
	// 旋转矩阵
	Mat GetRotateX(float r);
	Mat GetRotateY(float r);
	Mat GetRotateZ(float r);
	// 局部转世界的矩阵(使用时要考虑左、右手坐标系）
	Mat ModelMatrix(float worldx, float worldy, float worldz);
};
template <typename myT>
Model<myT>::Model() {
	localPosition = vector3::Zero;
	quaternion = vector4::Zero;
}

template <typename myT>
Model<myT>::Model(float x, float y, float z) {
	localPosition = vector3(x, y, z);
	quaternion = vector4::Zero;
}

template <typename myT>
Model<myT>::Model(vector3 pos, vector4 q) {
	localPosition = pos;
	quaternion = q;
}

template <typename myT>
Mat<myT> Model<myT>::GetTranslate(float x, float y, float z) {
	Mat<myT> matrix(4, 4);
	matrix.Identity();
	matrix[3][0] = x;
	matrix[3][1] = y;
	matrix[3][2] = z;
	return matrix;
}

template <typename myT>
Mat<myT> Model<myT>::GetScale(float x, float y, float z)
{
	Mat<myT> matrix(4, 4);
	matrix.num[0][0] = x;
	matrix.num[1][1] = y;
	matrix.num[2][2] = z;
	matrix.num[3][3] = 1;
	return matrix;
}

template <typename myT>
Mat<myT> Model<myT>::GetRotateX(float r)
{
	Mat<myT> matrix(3, 3);
	matrix = Mat<myT>::Identity();
	float cosR = float(cos(r));
	float sinR = float(sin(r));
	matrix[1][1] = cosR;
	matrix[1][2] = sinR;
	matrix[2][1] = -sinR;
	matrix[2][2] = cosR;
	return matrix;
}

template <typename myT>
Mat<myT> Model<myT>::GetRotateY(float r)
{
	Mat<myT> matrix(3, 3);
	matrix = Mat<myT>::Identity();
	float cosR = float(cos(r));
	float sinR = float(sin(r));
	matrix[0][0] = cosR;
	matrix[0][2] = -sinR;
	matrix[2][0] = sinR;
	matrix[2][2] = cosR;
	return matrix;
}

template <typename myT>
Mat<myT> Model<myT>::GetRotateZ(float r)
{
	Mat<myT> matrix(3, 3);
	matrix = Mat<myT>::Identity();
	float cosR = float(cos(r));
	float sinR = float(sin(r));
	matrix[0][0] = cosR;
	matrix[0][1] = sinR;
	matrix[1][0] = -sinR;
	matrix[1][1] = cosR;
	return matrix;
}

template <typename myT>
Mat<myT> Model<myT>::ModelMatrix(float worldx, float worldy, float worldz)
{
	Mat<myT> modelMatrix(4, 4);
	modelMatrix = GetRotateX(quaternion.x) * GetRotateY(quaternion.y) * GetRotateZ(quaternion.z) * GetTranslate(worldx, worldy, worldz);
	return modelMatrix;
}
