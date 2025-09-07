#include "Renderer2D_GL.h"
#include "DrawList.h"
#include <cmath>
#include "../Core/Log.h"

static const char* VS_SRC = R"(#version 330 core
layout(location=0) in vec2 aPos;
layout(location=1) in vec4 aCol;
out vec4 vCol;
uniform vec2 uViewport; // 逻辑 UI 尺寸
void main(){
  vec2 ndc;
  ndc.x = aPos.x / uViewport.x * 2.0 - 1.0;
  ndc.y = aPos.y / uViewport.y * -2.0 + 1.0; // 上正下负 → NDC
  gl_Position = vec4(ndc, 0.0, 1.0);
  vCol = aCol;
}
)";

static const char* FS_SRC = R"(#version 330 core
in vec4 vCol;
out vec4 FragColor;
void main(){ FragColor = vCol; }
)";

static GLuint compile(GLenum type, const char* src){
  GLuint s = glCreateShader(type);
  glShaderSource(s, 1, &src, nullptr);
  glCompileShader(s);
  GLint ok=0; glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
  if(!ok){
    char log[1024]; glGetShaderInfoLog(s, 1024, nullptr, log);
    LOGE("shader compile error: %s", log);
  }
  return s;
}
GLuint Renderer2D_GL::buildProgram(const char* vs, const char* fs){
  GLuint v = compile(GL_VERTEX_SHADER, vs);
  GLuint f = compile(GL_FRAGMENT_SHADER, fs);
  GLuint p = glCreateProgram();
  glAttachShader(p, v); glAttachShader(p, f);
  glLinkProgram(p);
  GLint ok=0; glGetProgramiv(p, GL_LINK_STATUS, &ok);
  if(!ok){
    char log[1024]; glGetProgramInfoLog(p, 1024, nullptr, log);
    LOGE("program link error: %s", log);
  }
  glDeleteShader(v); glDeleteShader(f);
  return p;
}

bool Renderer2D_GL::Init(){
  glGenVertexArrays(1,&vao);
  glGenBuffers(1,&vbo);
  prog = buildProgram(VS_SRC, FS_SRC);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)*2));
  glBindVertexArray(0);
  LOGI("Renderer2D_GL initialized.");
  return true;
}

void Renderer2D_GL::BeginFrame(int fbW, int fbH, int uiW, int uiH){
  FBW=fbW; FBH=fbH; UIW=uiW; UIH=uiH;
  scaleX = (UIW>0)? (float)FBW/(float)UIW : 1.f;
  scaleY = (UIH>0)? (float)FBH/(float)UIH : 1.f;
  stats = {};
  buffer.clear();
  scissorOn=false;
  currentClip = {0,0,(float)UIW,(float)UIH};
}

void Renderer2D_GL::setClip(const Rect& clip){
  Rect c = clip;
  if(c.w<=0 || c.h<=0){
    glDisable(GL_SCISSOR_TEST);
    scissorOn=false;
    currentClip = {0,0,0,0};
    return;
  }
  // 逻辑(UI) → framebuffer 像素，并翻转 Y
  GLint sx = (GLint)std::lround(c.x * scaleX);
  GLint sy = (GLint)std::lround(FBH - (c.y + c.h) * scaleY);
  GLsizei sw = (GLsizei)std::lround(c.w * scaleX);
  GLsizei sh = (GLsizei)std::lround(c.h * scaleY);

  // Clamp
  if (sx < 0) { sw += sx; sx = 0; }
  if (sy < 0) { sh += sy; sy = 0; }
  if (sx + sw > FBW) sw = FBW - sx;
  if (sy + sh > FBH) sh = FBH - sy;
  if (sw <= 0 || sh <= 0){
    glDisable(GL_SCISSOR_TEST);
    scissorOn=false;
    currentClip = {0,0,0,0};
    return;
  }

  glEnable(GL_SCISSOR_TEST);
  glScissor(sx, sy, sw, sh);
  scissorOn=true;
  currentClip = c;
}

void Renderer2D_GL::flush(){
  if(buffer.empty()) return;
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(buffer.size()*sizeof(Vertex)), buffer.data(), GL_DYNAMIC_DRAW);
  glUseProgram(prog);
  GLint loc = glGetUniformLocation(prog, "uViewport");
  glUniform2f(loc, (float)UIW, (float)UIH);
  glDrawArrays(GL_TRIANGLES, 0, (GLsizei)buffer.size());
  stats.drawCalls += 1;
  stats.vertexCount += (int)buffer.size();
  stats.quadCount += (int)(buffer.size()/6);
  buffer.clear();
}

void Renderer2D_GL::Submit(const DrawList& list){
  for(const auto& c : list.Commands()){
    if(c.type == DrawCmd::Type::PushClip){
      flush();
      setClip(c.rect);
    } else if(c.type == DrawCmd::Type::PopClip){
      flush();
      setClip(Rect{0,0,(float)UIW,(float)UIH});
    } else if(c.type == DrawCmd::Type::Quad){
      const Rect& r = c.rect;
      const Color& col = c.color;
      Vertex v[6] = {
        {r.x,       r.y,        col.r,col.g,col.b,col.a},
        {r.x+r.w,   r.y,        col.r,col.g,col.b,col.a},
        {r.x+r.w,   r.y+r.h,    col.r,col.g,col.b,col.a},
        {r.x,       r.y,        col.r,col.g,col.b,col.a},
        {r.x+r.w,   r.y+r.h,    col.r,col.g,col.b,col.a},
        {r.x,       r.y+r.h,    col.r,col.g,col.b,col.a},
      };
      buffer.insert(buffer.end(), std::begin(v), std::end(v));
    }
  }
  flush();
}

void Renderer2D_GL::EndFrame(){
  if(scissorOn) glDisable(GL_SCISSOR_TEST);
  glBindVertexArray(0);
  glUseProgram(0);
}
