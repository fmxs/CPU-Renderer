#include "Vertex.h"
#pragma once
class Line {
public:
	Vertex v0, v1;	// �߶ε������˵�
	Vertex v2;		// �߶��ϵ�ĳһ�㣬�õ�������ɨ����ʱ�������յ�

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