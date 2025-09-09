#pragma once
#include <cstdint>
struct GLFWwindow;

namespace Input {
    enum class Type { MouseMove, MouseDown, MouseUp, MouseScroll, KeyDown, KeyUp };
    struct State {
      double mouseX=0, mouseY=0;
      bool   lmb=false, rmb=false, mmb=false;
      int    wheel=0;// 鼠标滚轮滚动量 往上为正，往下为负
    };
    void SetupCallbacks(GLFWwindow* win);
    const State& Get();
    // 鼠标滚动是某一帧的输入，不清理的话下一帧就会残留，导致误以为还在滚动。通常渲染循环结束后手动重置为0
    void ClearFrameWheel();
}
