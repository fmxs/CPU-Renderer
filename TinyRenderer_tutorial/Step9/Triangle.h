#include "Vertex.h"
#pragma once
class Triangle {
public:
	Vertex v0, v1, v2;// �����ε���������

	Triangle();
	Triangle(Vertex v0, Vertex v1, Vertex v2);
	~Triangle();

	// �ж����������Ƿ����������
	bool IsTriangle() const;
};

Triangle::Triangle(){}

Triangle::Triangle(Vertex a, Vertex b, Vertex c) :v0(a), v1(b), v2(c) {}

Triangle::~Triangle(){}