#pragma once
#include <algorithm>
struct Vec2 { float x=0, y=0; };
struct Color { float r=1,g=1,b=1,a=1; };
struct Rect  { float x=0,y=0,w=0,h=0; };
inline bool Contains(const Rect& r, float px, float py){
  return px>=r.x && px<=r.x+r.w && py>=r.y && py<=r.y+r.h;
}
inline Rect Intersect(const Rect& a, const Rect& b){
  float nx = std::max(a.x,b.x), ny = std::max(a.y,b.y);
  float rx = std::min(a.x+a.w, b.x+b.w), ry = std::min(a.y+a.h, b.y+b.h);
  if (rx<=nx || ry<=ny) return {0,0,0,0};
  return {nx,ny,rx-nx,ry-ny};
}
