#pragma once
#include <vector>
#include "../Core/Math.h"

struct DrawStats {
  int drawCalls=0;
  int quadCount=0;
  int vertexCount=0;
};

class DrawList;

class IRenderer2D {
public:
  virtual ~IRenderer2D() = default;
  // fbW/fbH: framebuffer 像素尺寸；uiW/uiH: 逻辑窗口尺寸
  virtual bool Init() = 0;
  virtual void BeginFrame(int fbW, int fbH, int uiW, int uiH) = 0;
  virtual void Submit(const DrawList& list) = 0;
  virtual void EndFrame() = 0;
  virtual const DrawStats& GetStats() const = 0;
};
