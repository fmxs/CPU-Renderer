#pragma once
class Color {
private:
	float r;// ºì
	float g;// ÂÌ
	float b;// À¶
public:
	Color();// ¹¹Ôìº¯Êý
	Color(float r, float g, float b);
	Color(const Color& c);

	Color& operator=(const Color& c);
	Color operator+(const Color& c) const;
	Color operator-(const Color& c) const;
	Color operator*(const Color& c) const;
	Color operator+(float offset)const;
	Color operator-(float offset)const;
	Color operator*(float offset)const;
};
Color::Color() : r(0), g(0), b(0) {}

Color::Color(float red, float green, float blue) :r(red), g(green), b(blue) {}

Color::Color(const Color& c) 
{
	r = c.r;
	g = c.g;
	b = c.b;
}

Color& Color::operator=(const Color& c)
{
	this->r = c.r;
	this->g = c.g;
	this->b = c.b;
}

