#include "UApplication.h"
#include <string>
#include <cmath>
#include "Core/GLFWIncludes.h"
#include "../Core/Time.h"
#include "../Core/Log.h"
#include "../Input/Input.h"
#include "../Render/Renderer2D_GL.h"
#include "../Render/DrawList.h"
#include "../Core/Math.h"

#ifdef __APPLE__
  #include <OpenGL/gl3.h>
#else
  #error "非 macOS 平台请在 Step1.2 接入 glad 再继续。"
#endif

bool UApplication::Init(int w, int h, const std::string& title){
  if(!glfwInit()){ LOGE("glfwInit failed"); return false; }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  Win = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);
  if(!Win){ LOGE("CreateWindow failed"); glfwTerminate(); return false; }
  glfwMakeContextCurrent(Win);
  glfwSwapInterval(1);

  Input::SetupCallbacks(Win);
  LOGI("GLFW window created.");
  return true;
}

void UApplication::Run(){
  Renderer2D_GL renderer; renderer.Init();
  double lastLog = 0.0;

  while(!glfwWindowShouldClose(Win)){
    Core::Time::Tick();

    // 尺寸：framebuffer 像素与逻辑窗口
    int fbW=0, fbH=0; glfwGetFramebufferSize(Win, &fbW, &fbH);
    int winW=0, winH=0; glfwGetWindowSize(Win, &winW, &winH);

    // 视口用 framebuffer 尺寸
    glViewport(0,0,fbW,fbH);

    // 背景渐变证明时间在走
    double t = std::fmod(Core::Time::Now(), 3.0) / 3.0;
    glClearColor((float)t, 0.12f, 0.22f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    // 渲染 UI：逻辑坐标绘制
    renderer.BeginFrame(fbW, fbH, winW, winH);
    DrawList dl;
    dl.PushClip(Rect{0,0,(float)winW,(float)winH});

    // 顶部 Panel
    dl.AddQuad(Rect{20, 20, (float)winW - 40, 120}, Color{0.12f,0.16f,0.22f,1.f});

    // Button（逻辑坐标）
    Rect btn{40, 60, 200, 48};
    auto& st = Input::Get();
    bool hover = Contains(btn, (float)st.mouseX, (float)st.mouseY);
    Color base = hover ? Color{0.30f,0.55f,0.90f,1.f} : Color{0.25f,0.25f,0.28f,1.f};
    dl.AddQuad(btn, base);

    dl.PopClip();
    renderer.Submit(dl);
    renderer.EndFrame();

    // 交换 & 事件
    glfwSwapBuffers(Win);
    glfwPollEvents();

    // 节流日志
    if(Core::Time::Now() - lastLog > 2.0){
      LOGI("fps=%.1f dt=%.3f ms  mouse(%.0f,%.0f)  dc=%d quads=%d",
           Core::Time::FpsAvg(), Core::Time::Delta()*1000.0,
           Input::Get().mouseX, Input::Get().mouseY,
           renderer.GetStats().drawCalls, renderer.GetStats().quadCount);
      lastLog = Core::Time::Now();
    }
    Input::ClearFrameWheel();
  }
}

void UApplication::Shutdown(){
  if(Win){ glfwDestroyWindow(Win); Win=nullptr; }
  glfwTerminate();
  LOGI("Shutdown complete.");
}
