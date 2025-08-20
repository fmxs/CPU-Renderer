#include "Vertex.h"
#pragma once
class Scanline {
public:
	Vertex start;	// ɨ����ʼ��
	Vertex step;	// ɨ�貽��
	int x, y;		// ɨ������ʼ��x��y����
	int width;		// ɨ���߿��

	Scanline();
	Scanline(Vertex start, Vertex step, int x, int y, int width);
};

Scanline::Scanline() 
{
	start = Vertex();
	step = Vertex();
	x = y = 0;
	width = 0;
}

Scanline::Scanline(Vertex start, Vertex step, int x, int y, int w) :start(start), step(step), x(x), y(y), width(w) {}