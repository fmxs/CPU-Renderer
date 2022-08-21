#pragma once
#include <math.h>
#include "Vector3.h"
#include "Matrix.h"
#include "Vector4.h"
constexpr auto M_PI = 3.14159265358979323846;
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
	Mat<myT> GetTranslate(float worldx, float worldy, float worldz);
	// 缩放矩阵
	Mat<myT> GetScale(float x, float y, float z);
	Mat<myT> GetScale(float scale);
	// 旋转矩阵第一种写法
	Mat<myT> GetRotateX(float r);
	Mat<myT> GetRotateY(float r);
	Mat<myT> GetRotateZ(float r);
	// 旋转矩阵第二种写法
	Mat<myT> Rotate(float x, float y, float z);
	// 局部转世界的矩阵(使用时要考虑左、右手坐标系）
	Mat<myT> ModelMatrix(float worldx, float worldy, float worldz);
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
	matrix.num[0][3] = x;
	matrix.num[1][3] = y;
	matrix.num[2][3] = z;
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
Mat<myT> Model<myT>::GetScale(float scale)
{
	return this->GetScale(scale, scale, scale);
}

template <typename myT>
Mat<myT> Model<myT>::Rotate(float x, float y, float  z)
{
	Mat<myT> matrix(4, 4);
	auto M_PI_180 = (float)(M_PI / 180.0f);
	x *= M_PI_180;
	y *= M_PI_180;
	z *= M_PI_180;
	float cosx = cosf(x);
	float sinx = sinf(x);
	float cosy = cosf(y);
	float siny = sinf(y);
	float cosz = cosf(z);
	float sinz = sinf(z);
	float cx_sy = cosx * siny;
	float sx_sy = sinx * siny;

	matrix.num[0][0] = cosy * cosz;
	matrix.num[1][0] = -cosy * sinz;
	matrix.num[2][0] = siny;

	matrix.num[0][1] = sx_sy * cosz + cosx * sinz;
	matrix.num[1][1] = -sx_sy * sinz + cosx * cosz;
	matrix.num[2][1] = -sinx * cosy;

	matrix.num[0][2] = -cx_sy * cosz + sinx * sinz;
	matrix.num[1][2] = cx_sy * sinz + sinx * cosz;
	matrix.num[2][2] = cosx * cosy;
	
	matrix.num[3][3] = 1;
	return matrix;
}

template <typename myT>
Mat<myT> Model<myT>::GetRotateX(float r)
{
	Mat<myT> matrix(4, 4);
	matrix = matrix.Identity();
	float cosR = float(cos(r));
	float sinR = float(sin(r));
	matrix.num[1][1] = cosR;
	matrix.num[1][2] = sinR;
	matrix.num[2][1] = -sinR;
	matrix.num[2][2] = cosR;
	return matrix;
}

template <typename myT>
Mat<myT> Model<myT>::GetRotateY(float r)
{
	Mat<myT> matrix(4, 4);
	matrix = matrix.Identity();
	float cosR = float(cos(r));
	float sinR = float(sin(r));
	matrix.num[0][0] = cosR;
	matrix.num[0][2] = -sinR;
	matrix.num[2][0] = sinR;
	matrix.num[2][2] = cosR;
	return matrix;
}

template <typename myT>
Mat<myT> Model<myT>::GetRotateZ(float r)
{
	Mat<myT> matrix(4, 4);
	matrix = matrix.Identity();
	float cosR = float(cos(r));
	float sinR = float(sin(r));
	matrix.num[0][0] = cosR;
	matrix.num[0][1] = sinR;
	matrix.num[1][0] = -sinR;
	matrix.num[1][1] = cosR;
	return matrix;
}

template <typename myT>
Mat<myT> Model<myT>::ModelMatrix(float worldx, float worldy, float worldz)
{
	Mat<myT> modelMatrix(4, 4);
	//modelMatrix = GetRotateX(quaternion.x) * GetRotateY(quaternion.y) * GetRotateZ(quaternion.z) * GetTranslate(worldx, worldy, worldz);
	modelMatrix = Rotate(quaternion.x, quaternion.y, quaternion.z) * GetTranslate(worldx, worldy, worldz);
	return modelMatrix;
}
