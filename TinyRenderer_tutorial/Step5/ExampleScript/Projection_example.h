// �Ƶ���ʽ�ο���
// https://blog.csdn.net/junzia/article/details/85939783
#pragma once
#include <math.h>
#include "Vector3.h"
#include "Matrix.h"
template <typename myT>
class Projection// Projection ����
{
public:
	// ��������
	Mat CreateOrthogonal(float left, float right, float top, float bottom, float near, float far);
	// ͸�Ӿ���
	Mat CreatePerspective(float fov, float aspect, float near, float far);
};


/// <summary>
/// ��������ͶӰ����
/// </summary>
/// <typeparam name="myT"></typeparam>
/// <param name="left">��Ҫ�任�ĳ���������</param>
/// <param name="right">��Ҫ�任�ĳ�������Ҳ�</param>
/// <param name="top">��Ҫ�任�ĳ�����Ķ���</param>
/// <param name="bottom">��Ҫ�任�ĳ�����ĵײ�</param>
/// <param name="near">��ƽ��</param>
/// <param name="far">Զƽ��</param>
/// <returns>����ͶӰ����</returns>
template<typename myT>
Mat<myT> Projection<myT>::CreateOrthogonal(float left, float right, float top, float bottom, float near, float far)
{
	Mat<myT> mat(4, 4);// �ڱ�Mat���У���ʼ��������Ԫ��ȫΪ0
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
Mat<myT> Projection<myT>::CreatePerspective(float fov, float aspect, float near, float far)// ͸�Ӿ���
{
	Mat<myT> mat(4, 4);// �ڱ�Mat���У���ʼ��������Ԫ��ȫΪ0
	mat.num[0][0] = 1 / tanf(fov / 2);
	mat.num[1][1] = 1 / aspect * tanf(fov / 2);
	mat.num[2][2] = -(far + near) / (far - near);
	mat.num[3][2] = -1.0f;
	mat.num[2][3] = 2 * near * far / (near - far);
	return mat;
}