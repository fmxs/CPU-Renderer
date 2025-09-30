// tiny_probe — 最小数据流探针（GLFW + OpenGL，macOS/Retina 友好）
#include <cstdio>
#include <cmath>
#include <GLFW/glfw3.h>
#ifdef __APPLE__
  #include <OpenGL/gl3.h>
#else
  #include <GL/gl.h>
#endif

static double g_mouseX = 0.0, g_mouseY = 0.0;

static void cursorPosCB(GLFWwindow*, double x, double y){
  // GLFW 鼠标回调给的是“窗口逻辑坐标”，正好就是我们要的 window space
  g_mouseX = x; g_mouseY = y;
}

int main(){
  if(!glfwInit()){ std::fprintf(stderr,"[ERR] glfwInit failed\n"); return -1; }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
  glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  GLFWwindow* win = glfwCreateWindow(960, 600, "tiny-probe", nullptr, nullptr);
  if(!win){ std::fprintf(stderr,"[ERR] create window failed\n"); glfwTerminate(); return -1; }
  glfwMakeContextCurrent(win);
  glfwSwapInterval(1);

  glfwSetCursorPosCallback(win, cursorPosCB);

  double lastLog = 0.0;
  while(!glfwWindowShouldClose(win)){
    // 1) 取窗口逻辑尺寸（UI 坐标）
    int winW=0, winH=0;
    glfwGetWindowSize(win, &winW, &winH);

    // 2) 取 framebuffer 物理像素尺寸（GPU 画布）
    int fbW=0, fbH=0;
    glfwGetFramebufferSize(win, &fbW, &fbH);

    // 3) 守卫：最小化时可能为 0，跳过绘制
    if(fbW>0 && fbH>0){
      glViewport(0,0,fbW,fbH);  // 渲染：必须对齐 framebuffer（像素）
      float t = float(fmod(glfwGetTime(), 3.0) / 3.0);
      glClearColor(t, 0.15f, 0.25f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
    }

    glfwSwapBuffers(win);
    glfwPollEvents();

    // 4) 每 1.5s 打印一次关键变量（数据流探针）
    double now = glfwGetTime();
    if(now - lastLog > 1.5){
      double sx = (winW>0) ? double(fbW)/double(winW) : 0.0;
      double sy = (winH>0) ? double(fbH)/double(winH) : 0.0;
      std::printf("fb(%d,%d) ui(%d,%d) dpi(%.2f,%.2f) mouse(%.0f,%.0f)\n",
                  fbW, fbH, winW, winH, sx, sy, g_mouseX, g_mouseY);
      lastLog = now;
    }
  }

  glfwDestroyWindow(win);
  glfwTerminate();
  return 0;
}
