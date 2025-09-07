#pragma once
#include "IRenderer2D.h"
#include <vector>
#ifdef __APPLE__
  #include <OpenGL/gl3.h>
#else
  #error "非 macOS 平台请在后续步骤接入 glad。"
#endif

class Renderer2D_GL : public IRenderer2D {
public:
  bool Init() override;
  void BeginFrame(int fbW, int fbH, int uiW, int uiH) override;
  void Submit(const DrawList& list) override;
  void EndFrame() override;
  const DrawStats& GetStats() const override { return stats; }

private:
  struct Vertex { float x,y,r,g,b,a; };
  GLuint vao=0, vbo=0, prog=0;
  int FBW=0, FBH=0;     // framebuffer 像素
  int UIW=0, UIH=0;     // 逻辑 UI 尺寸
  float scaleX=1.f, scaleY=1.f;
  std::vector<Vertex> buffer;
  Rect currentClip{0,0,0,0};
  bool scissorOn=false;
  DrawStats stats;

  void flush();
  void setClip(const Rect& clip);
  static GLuint buildProgram(const char* vs, const char* fs);
};
