// �Ƶ���ʽ�ο���
// https://blog.csdn.net/junzia/article/details/85939783
#pragma once
#include <math.h>
#include "Vector3.h"
#include "Matrix.h"
#include "Vector4.h"
constexpr auto M_PI = 3.14159265358979323846;
template <typename myT>
class Model// ģ����
{
private:
	vector3 localPosition;// ��������ϵ������
	vector3 worldPosition;// ��������ϵ������
	vector4 quaternion;// ��ת��Ϣ
	vector3 scale;// ������Ϣ
public:
	Model();
	Model(float locx, float locy, float locz);
	Model(vector3 loc, vector4 q);
	Model(vector3 loc, vector3 world);
	Model(vector3 loc, vector3 world, vector4 q, vector3 scale);
	// ƽ�ƾ���
	Mat<myT> GetTranslate();
	// ���ž���
	Mat<myT> GetScale();
	// ��ת�����һ��д������������ֿ�д
	Mat<myT> GetRotateX();
	Mat<myT> GetRotateY();
	Mat<myT> GetRotateZ();
	// ��ת����ڶ���д�������������һ��д���Ƽ���
	Mat<myT> Rotate();
	// Model����(ʹ��ʱҪ��������������ϵ��
	Mat<myT> ModelMatrix();
};
template <typename myT>
Model<myT>::Model() {
	localPosition = vector3::Zero;
	worldPosition = vector3::Zero;
	quaternion = vector4::Zero;
	scale = vector3::Zero;
}

template <typename myT>
Model<myT>::Model(float x, float y, float z) {
	localPosition = vector3(x, y, z);
	worldPosition = vector3::Zero;
	quaternion = vector4::Zero;
	scale = vector3::Zero;
}

template <typename myT>
Model<myT>::Model(vector3 loc, vector4 q) {
	localPosition = loc;
	worldPosition = vector3::Zero;
	quaternion = q;
	scale = vector3::Zero;
}

template <typename myT>
Model<myT>::Model(vector3 local, vector3 world) {
	localPosition = local;
	worldPosition = world;
	quaternion = vector4::Zero;
	scale = vector3::Zero;
}

template <typename myT>
Model<myT>::Model(vector3 l, vector3 w, vector4 q, vector3 s) {
	localPosition = l;
	worldPosition = w;
	quaternion = q;
	scale = s;
}

/// <summary>
/// ����ƽ�ƾ���
/// </summary>
/// <param name="tx">x���ƽ�ƾ���</param>
/// <param name="ty">y���ƽ�ƾ���</param>
/// <param name="tz">z���ƽ�ƾ���</param>
/// <returns>ƽ�ƾ���</returns>
template <typename myT>
Mat<myT> Model<myT>::GetTranslate() {
	Mat<myT> matrix(4, 4);
	matrix.Identity();
	int tx = worldPosition.x - localPosition.x;
	int ty = worldPosition.y - localPosition.y;
	int tz = worldPosition.z - localPosition.z;
	matrix.num[0][3] = tx;
	matrix.num[1][3] = ty;
	matrix.num[2][3] = tz;
	return matrix;
}

template <typename myT>
Mat<myT> Model<myT>::GetScale()
{
	Mat<myT> matrix(4, 4);
	matrix.num[0][0] = scale.x;
	matrix.num[1][1] = scale.y;
	matrix.num[2][2] = scale.z;
	matrix.num[3][3] = 1;
	return matrix;
}

template <typename myT>
Mat<myT> Model<myT>::Rotate()
{
	int x = quaternion.x;
	int y = quaternion.y;
	int z = quaternion.z;
	Mat<myT> matrix(4, 4);// �ڱ�Mat���У���ʼ��������Ԫ��ȫΪ0
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

	matrix.num[3][3] = 1.0f;
	return matrix;
}

template <typename myT>
Mat<myT> Model<myT>::GetRotateX()
{
	int r = quaternion.x;
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
Mat<myT> Model<myT>::GetRotateY()
{
	int r = quaternion.y;
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
Mat<myT> Model<myT>::GetRotateZ()
{
	int r = quaternion.z;
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

// M = Scale * Rotate * Translate
// Model����˳�����Scale�������Rotate��������Translate 
template <typename myT>
Mat<myT> Model<myT>::ModelMatrix()
{
	Mat<myT> modelMatrix(4, 4);
	modelMatrix = modelMatrix.Premultiply_vec(GetScale(), localPosition);
	modelMatrix = modelMatrix * Rotate();
	modelMatrix = modelMatrix * GetTranslate();
	return modelMatrix;
}
