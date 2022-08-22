// �Ƶ���ʽ�ο���
// https://blog.csdn.net/junzia/article/details/85939783
#pragma once
#include <math.h>
#include "Vector4.h"
#include "Vector3.h"
#include "Projection_example.h"
template <typename myT>
class NDC// NDC�ռ�
{
public:
	int x;
	int y;
	int z;
	int w;
	vector4 NDCPoint(int x, int y, int z, int w);// ����ͶӰ�ռ�������NDC����
};

// NDCPoint(x, y, z, w) = ProjectionPoint(x / w, y / w, z / w, 1)
template<typename myT>
vector4 NDC<myT>::NDCPoint(int proj_x, int proj_y, int proj_z, int proj_w)
{
	this->x = proj_x / proj_w;
	this->y = proj_y / proj_w;
	this->z = proj_z / proj_w;
	this->w = 1;
}

