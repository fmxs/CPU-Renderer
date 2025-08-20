#include "Vertex.h"
#pragma once
class Scanline {
public:
	Vertex start;	// 扫描起始点
	Vertex step;	// 扫描步长
	int x, y;		// 扫面线起始点x、y坐标
	int width;		// 扫描线宽度

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