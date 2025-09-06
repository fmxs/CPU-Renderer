#include "UApplication.h"
#include <string>
#include <cmath>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "../Core/Time.h"
#include "../Core/Log.h"
#include "../Input/Input.h"

#ifdef __APPLE__
  #include <OpenGL/gl3.h>   // Apple: 用系统 OpenGL，暂不依赖 glad
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
  glfwSwapInterval(1); // vsync

  Input::SetupCallbacks(Win);
  LOGI("GLFW window created.");
  return true;
}

void UApplication::Run(){
  double lastLog = 0.0;
  while(!glfwWindowShouldClose(Win)){
    Core::Time::Tick();

    // Viewport: 用 framebuffer 尺寸适配 Retina
    int fbW=0, fbH=0;
    glfwGetFramebufferSize(Win, &fbW, &fbH);
    glViewport(0,0,fbW,fbH);

    // 背景渐变（证明 dt/时间可用）
    double t = std::fmod(Core::Time::Now(), 3.0) / 3.0;
    glClearColor((float)t, 0.12f, 0.22f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    // 交换 & 轮询
    glfwSwapBuffers(Win);
    glfwPollEvents();

    // 每 2 秒节流打印一次 fps/dt/鼠标
    if(Core::Time::Now() - lastLog > 2.0){
      auto& s = Input::Get();
      LOGI("fps=%.1f dt=%.3f ms  mouse(%.0f,%.0f)", Core::Time::FpsAvg(), Core::Time::Delta()*1000.0, s.mouseX, s.mouseY);
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
