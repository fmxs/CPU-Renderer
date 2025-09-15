// d00_boot
#include <cmath>
#include <cstdio>
#include <string>

#include "../../Input/Input.h"
#include "../../Core/Time.h"
#include "../../Core/Log.h"
#include "../../Render/DrawList.h"
#include "../../Render/Renderer2D_GL.h"

#include <GLFW/glfw3.h>
#ifdef __APPLE__
  #include <OpenGL/gl3.h>
#else
  #error "This demo currently assumes macOS OpenGL. Add glad for other platforms."
#endif

int main(){
  // 1) Boot GLFW + Window + GL
  if(!glfwInit()){ LOGE("glfwInit failed"); return -1; }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
  glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
#endif
  GLFWwindow* win = glfwCreateWindow(960, 600, "demo-d00-boot", nullptr, nullptr);
  if(!win){ LOGE("CreateWindow failed"); glfwTerminate(); return -1; }
  glfwMakeContextCurrent(win);
  glfwSwapInterval(1);

  // 2) Input callbacks
  Input::SetupCallbacks(win);

  // 3) Renderer
  Renderer2D_GL renderer;
  renderer.Init();

  // 4) Loop
  double lastLog = 0.0;
  while(!glfwWindowShouldClose(win)){
    Core::Time::Tick();

    // Framebuffer viewport（像素，Retina OK）
    int fbW=0, fbH=0; glfwGetFramebufferSize(win, &fbW, &fbH);
    glViewport(0,0,fbW,fbH);

    // 背景渐变（只是证明时间/清屏正常）
    double t = std::fmod(Core::Time::Now(), 3.0)/3.0;
    glClearColor((float)t, 0.12f, 0.22f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    // 逻辑尺寸（window size）
    int winW=0, winH=0; glfwGetWindowSize(win, &winW, &winH);

    // BeginFrame: 传 FB 和 UI（逻辑）尺寸
    renderer.BeginFrame(fbW, fbH, winW, winH);

    // Build DrawList in UI space
    DrawList dl;
    dl.PushClip(Rect{0,0,(float)winW,(float)winH});

    // 小测试方块：左上角(40,60) 大小(120,120)
    Rect test{40, 60, 120, 120};
    auto& st = Input::Get();
    bool hover = Contains(test, (float)st.mouseX, (float)st.mouseY);
    Color c = hover ? Color{0.3f,0.55f,0.9f,1.f} : Color{0.2f,0.22f,0.26f,1.f};
    dl.AddQuad(test, c);

    // 画一个参考边框区域（屏幕中心 200x200）
    Rect mid{(winW-200)/2.f, (winH-200)/2.f, 200, 200};
    Color midc{0.12f,0.35f,0.18f,1.f};
    dl.AddQuad(mid, midc);

    dl.PopClip();

    renderer.Submit(dl);
    renderer.EndFrame();

    glfwSwapBuffers(win);
    glfwPollEvents();

    // 节流日志：验证坐标 & 尺寸
      if(Core::Time::Now() - lastLog > 0.5){   // 原来是 2.0
        LOGI("fb(%d,%d) ui(%d,%d) mouse(%.0f,%.0f) hover=%d",
             fbW, fbH, winW, winH, st.mouseX, st.mouseY, hover?1:0);
        lastLog = Core::Time::Now();
      }
  }

  glfwDestroyWindow(win);
  glfwTerminate();
  return 0;
}
