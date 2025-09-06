#include "Time.h"
#include <GLFW/glfw3.h>
#include <algorithm>

namespace {
    double g_now = 0.0, g_last = 0.0, g_dt = 0.0, g_fps = 60.0;
    inline double clampd(double v, double lo, double hi){ return std::max(lo, std::min(v, hi)); }
}
namespace Core {
    void Time::Tick(){
      g_now = glfwGetTime();
      double raw = g_now - g_last;
      g_dt = clampd(raw, 1.0/200.0, 1.0/15.0); // 0.005 ~ 0.066s
      g_last = g_now;
      double inst = (g_dt > 1e-9) ? 1.0/g_dt : 1000.0;
      g_fps = 0.9 * g_fps + 0.1 * inst;       // EMA 平滑
    }
    double Time::Now(){ return g_now; }
    double Time::Delta(){ return g_dt; }
    double Time::FpsAvg(){ return g_fps; }
}
