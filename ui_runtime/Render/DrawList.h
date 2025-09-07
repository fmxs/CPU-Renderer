#pragma once
#include <vector>
#include "../Core/Math.h"

struct DrawCmd {
  enum class Type { Quad, PushClip, PopClip } type;
  Rect rect;
  Color color;
};

class DrawList {
public:
  void PushClip(const Rect& r){ DrawCmd c; c.type=DrawCmd::Type::PushClip; c.rect=r; cmds.push_back(c); }
  void PopClip(){ DrawCmd c; c.type=DrawCmd::Type::PopClip; cmds.push_back(c); }
  void AddQuad(const Rect& r, const Color& col){
    DrawCmd c; c.type=DrawCmd::Type::Quad; c.rect=r; c.color=col; cmds.push_back(c);
  }
  const std::vector<DrawCmd>& Commands() const { return cmds; }
private:
  std::vector<DrawCmd> cmds;
};
