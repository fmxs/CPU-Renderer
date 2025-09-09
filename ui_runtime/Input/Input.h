#pragma once
#include <cstdint>
struct GLFWwindow;

namespace Input {
    enum class Type { MouseMove, MouseDown, MouseUp, MouseScroll, KeyDown, KeyUp };
    struct State {
      double mouseX=0, mouseY=0;
      bool   lmb=false, rmb=false, mmb=false;
      int    wheel=0;
    };
    void SetupCallbacks(GLFWwindow* win);
    const State& Get();
    void ClearFrameWheel();
}
