#include "Vector4_example.h"
#include "Color.h"
#pragma once
/// <summary>
/// ����ı任һ������ɫ�����ٿأ�
/// ���Vertex���ﲻ��Ҫд���˹��캯��������κη�����
/// </summary>
class Vertex {
public:
	vector4 position;	// ��������
	float u, v;			// ��������
	Color color;		// ��ɫ
	float deepZ;		// �����Ϣ

	Vertex();
	Vertex(vector4 p, float u, float v, Color c, float z);
	Vertex(const Vertex& v);
	Vertex& operator =(const Vertex& v);
	Vertex operator-(const Vertex& v) const;
	Vertex operator+(const Vertex& v) const;
	Vertex operator* (float scale) const;

	// �������������1/z��ֵʱ���Զ������ݽ��д���
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