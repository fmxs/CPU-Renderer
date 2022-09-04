#include "Vector4_example.h"
#include "Color.h"
#pragma once
/// <summary>
/// 顶点的变换一般由着色器来操控，
/// 因此Vertex类里不需要写除了构造函数以外的任何方法。
/// </summary>
class Vertex {
public:
	vector4 position;	// 顶点坐标
	float u, v;			// 纹理坐标
	Color color;		// 颜色
	float deepZ;		// 深度信息

	Vertex();
	Vertex(vector4 p, float u, float v, Color c, float z);
	Vertex(const Vertex& v);
	Vertex& operator =(const Vertex& v);
	Vertex operator-(const Vertex& v) const;
	Vertex operator+(const Vertex& v) const;
	Vertex operator* (float scale) const;

	// 当纹理坐标进行1/z插值时，对顶点数据进行处理
	void Init();
};

Vertex::Vertex() 
{
	position = vector4(0, 0, 0, 0);
	u = v = 0;
	color = Color(0, 0, 0);
	deepZ = 0;
}

Vertex::Vertex(vector4 p, float u, float v, Color c, float z) : position(p), u(u), v(v), color(c), deepZ(z) {}

Vertex::Vertex(const Vertex& v) 
{
	this->position = v.position;
	this->u = v.u;
	this->v = v.v;
	this->color = v.color;
	this->deepZ = v.deepZ;
}