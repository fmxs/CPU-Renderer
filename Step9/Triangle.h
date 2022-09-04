#include "Vertex.h"
#pragma once
class Triangle {
public:
	Vertex v0, v1, v2;// 三角形的三个顶点

	Triangle();
	Triangle(Vertex v0, Vertex v1, Vertex v2);
	~Triangle();

	// 判断三个顶点是否组成三角形
	bool IsTriangle() const;
};

Triangle::Triangle(){}

Triangle::Triangle(Vertex a, Vertex b, Vertex c) :v0(a), v1(b), v2(c) {}

Triangle::~Triangle(){}