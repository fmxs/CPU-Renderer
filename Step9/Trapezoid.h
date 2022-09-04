#include "Triangle.h"
#include "Scanline.h"
#include "Line.h"
#include <algorithm>
#pragma once
class Trapezoid {
public:
	float top, bottom;
	Line left, right;
	Trapezoid();
	Trapezoid(float t, float b, Line l, Line r);

	// ��������������λ���Ϊ��������������
	// ���������Σ�������ĳһ�������ڵ�ֱ��ƽ����x��
	static int GetTrapezoids(const Triangle& tri, Trapezoid* tra);

	// ��ȡɨ���ߵ������յ�
	void GetEndPoint(float y);

	// ��ȡɨ���߶���
	Scanline InitScanline(int y);
};

Trapezoid::Trapezoid() 
{
	top = bottom = 0;
	left = Line();
	right = Line();
}

Trapezoid::Trapezoid(float t, float b, Line l, Line r) :top(t), bottom(b), left(l), right(r) {}

int Trapezoid::GetTrapezoids(const Triangle& tri, Trapezoid* tra) 
{
	if (tra == NULL || tri.IsTriangle() == false) {
		return 0;
	}
	Vertex v1 = tri.v0;
	Vertex v2 = tri.v1;
	Vertex v3 = tri.v2;

	// �������ε������������y�����С��������
	if (v1.position.y > v2.position.y) {
		swap(v1, v2);
	}
	if (v1.position.y > v3.position.y) {
		swap(v1, v3);
	}
	if (v2.position.y > v3.position.y) {
		swap(v2, v3);
	}

	// �������1��v1v2���ڵ�ֱ��ƽ����x��
	if (v1.position.y == v2.position.y) {
		if (v1.position.x > v2.position.x) {
			swap(v1, v2);
		}
		if(v1.position.y >= v3.position.y){
			return 0;
		}
		tra[0].top = v1.position.y;
		tra[0].bottom = v3.position.y;
		tra[0].left.v1 = v1;
		tra[0].left.v2 = v3;
		tra[0].right.v1 = v2;
		tra[0].right.v2 = v3;
		return 1;
	}

	// �������2��v2v3���ڵ�ֱ��ƽ����x��
	if (v2.position.y == v3.position.y) {
		if (v2.position.x > v3.position.x) {
			swap(v2, v3);
		}
		if (v1.position.y >= v3.position.y) {
			return 0;
		}
		tra[0].top = v1.position.y;
		tra[0].bottom = v3.position.y;
		tra[0].left.v1 = v1;
		tra[0].left.v2 = v2;
		tra[0].right.v1 = v1;
		tra[0].right.v2 = v3;
		return 1;
	}

	// �������������Ҫ�����λ��ֳ�����������
	tra[0].top = v1.position.y;
	tra[0].bottom = v2.position.y;
	tra[1].top = v2.position.y;
	tra[1].bottom = v3.position.y;

	// ����P������ֱ�ߵ�б��
	// P���ǣ���v1,v2����ֱ�� �� ����v3��ƽ��x���ֱ�� �Ľ���
	float k = (v3.position.y - v1.position.y) / (v2.position.y - v1.position.y);
	// ����б����P���x����
	float x = (v2.position.x - v1.position.x) * k + v1.position.x;

	// ��v2��v1v3���ʱ
	if (x < v3.position.x) {
		tra[0].left.v2 = v2;
		tra[0].right.v2 = v3;
		tra[1].left.v1 = v2;
		tra[1].right.v1 = v1;
	}
	else {// ��v2��v1v3�Ҳ�ʱ
		tra[0].left.v2 = v3;
		tra[0].right.v2 = v2;
		tra[1].left.v1 = v1;
		tra[1].right.v1 = v2;
	}
	tra[0].left.v1 = v1;
	tra[0].right.v1 = v1;
	tra[1].left.v2 = v3;
	tra[1].right.v2 = v3;

	return 2;
}