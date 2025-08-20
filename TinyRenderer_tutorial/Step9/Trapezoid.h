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

	// 将不规则的三角形划分为两个理想三角形
	// 理想三角形：三角形某一条边所在的直线平行于x轴
	static int GetTrapezoids(const Triangle& tri, Trapezoid* tra);

	// 获取扫描线的起点和终点
	void GetEndPoint(float y);

	// 获取扫描线对象
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

	// 对三角形的三个顶点根据y坐标从小到大排序
	if (v1.position.y > v2.position.y) {
		swap(v1, v2);
	}
	if (v1.position.y > v3.position.y) {
		swap(v1, v3);
	}
	if (v2.position.y > v3.position.y) {
		swap(v2, v3);
	}

	// 理想情况1：v1v2所在的直线平行于x轴
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

	// 理想情况2：v2v3所在的直线平行于x轴
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

	// 非理想情况，需要将梯形划分成两个三角形
	tra[0].top = v1.position.y;
	tra[0].bottom = v2.position.y;
	tra[1].top = v2.position.y;
	tra[1].bottom = v3.position.y;

	// 计算P点所在直线的斜率
	// P点是：点v1,v2所在直线 与 过点v3且平行x轴的直线 的交点
	float k = (v3.position.y - v1.position.y) / (v2.position.y - v1.position.y);
	// 根据斜率求P点的x坐标
	float x = (v2.position.x - v1.position.x) * k + v1.position.x;

	// 当v2在v1v3左侧时
	if (x < v3.position.x) {
		tra[0].left.v2 = v2;
		tra[0].right.v2 = v3;
		tra[1].left.v1 = v2;
		tra[1].right.v1 = v1;
	}
	else {// 当v2在v1v3右侧时
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