#include "Input.h"
#include <GLFW/glfw3.h>
#include "../Core/Log.h"

namespace {
    Input::State g_state;
}

static void cursor_pos(GLFWwindow*, double x, double y){ g_state.mouseX = x; g_state.mouseY = y; }
static void mouse_button(GLFWwindow* win, int button, int action, int){
  (void)win;
  if(button==GLFW_MOUSE_BUTTON_LEFT)  g_state.lmb = (action==GLFW_PRESS);
  if(button==GLFW_MOUSE_BUTTON_RIGHT) g_state.rmb = (action==GLFW_PRESS);
  if(button==GLFW_MOUSE_BUTTON_MIDDLE)g_state.mmb = (action==GLFW_PRESS);
  if(button==GLFW_MOUSE_BUTTON_LEFT && action==GLFW_PRESS){
    LOGI("LMB down at (%.1f, %.1f)", g_state.mouseX, g_state.mouseY);
  }
}
static void scroll_cb(GLFWwindow*, double, double yoff){ g_state.wheel += (int)yoff; }
static void key_cb(GLFWwindow* win, int key, int, int action, int){
  if(key==GLFW_KEY_ESCAPE && action==GLFW_PRESS){
    glfwSetWindowShouldClose(win, GLFW_TRUE);
  }
}

namespace Input {
    void SetupCallbacks(GLFWwindow* win){
      glfwSetCursorPosCallback(win, cursor_pos);
      glfwSetMouseButtonCallback(win, mouse_button);
      glfwSetScrollCallback(win, scroll_cb);
      glfwSetKeyCallback(win, key_cb);
    }
    const State& Get(){ return g_state; }
    void ClearFrameWheel(){ g_state.wheel = 0; }
}
