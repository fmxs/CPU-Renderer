#include "Vertex.h"
#pragma once
class Line {
public:
	Vertex v0, v1;	// 线段的两个端点
	Vertex v2;		// 线段上的某一点，该点是生成扫描线时的起点或终点

	Line();
	Line(Vertex v0, Vertex v1, Vertex v2);
};

Line::Line() 
{
	v0 = Vertex();
	v1 = Vertex();
	v2 = Vertex();
}

Line::Line(Vertex v0, Vertex v1, Vertex v2) :v0(v0), v1(v1), v2(v2) {}