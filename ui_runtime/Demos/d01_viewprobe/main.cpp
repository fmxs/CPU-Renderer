// file: d01_viewprobe/main.cpp
#include <GLFW/glfw3.h>
#include <cstdio>

static int g_viewIdx = 0;
static void keyCB(GLFWwindow* w, int key, int sc, int action, int mods){
    if(key == GLFW_KEY_V && action == GLFW_PRESS){
        g_viewIdx = (g_viewIdx + 1) % 3; // 3个预设视口
    }
}

int main() {
    if (!glfwInit()) { std::fprintf(stderr, "glfwInit failed\n"); return -1; }

    GLFWwindow* win = glfwCreateWindow(640, 360, "d01_viewprobe", nullptr, nullptr);
    if (!win) { std::fprintf(stderr, "create window failed\n"); glfwTerminate(); return -2; }
    glfwMakeContextCurrent(win);
    
    glfwSetKeyCallback(win, keyCB);
    
    // 最小循环：处理事件 + 交换前后缓冲
    while (!glfwWindowShouldClose(win)) {
        glfwPollEvents();
        
        int fbW=0, fbH=0;
        glfwGetFramebufferSize(win, &fbW, &fbH);
        
        // 1) 计算三种预设矩形（像素坐标，和 framebuffer 尺寸对齐）
        GLint x=0,y=0,w=fbW,h=fbH;
        if (g_viewIdx == 0) { x = 0;        y = 0;        w = fbW;   h = fbH;   }
        if (g_viewIdx == 1) { x = 0;        y = fbH/2;        w = fbW/2; h = fbH/2; }
        if (g_viewIdx == 2) { x = fbW/2;    y = 0;    w = fbW/2; h = fbH/2; }

        // 2) 先把整屏清成“底色A”（一定要先关裁剪）
        glDisable(GL_SCISSOR_TEST);
        glViewport(0, 0, fbW, fbH);
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 3) 再只清一个小矩形成“高亮色”（能一眼看出差异）
        glEnable(GL_SCISSOR_TEST);
        glViewport(x, y, w, h);// 视口变换
        glScissor (x, y, w, h);// 裁剪 确定绘制区域

        // 每个 viewIdx 给不同颜色，这样即使位置看花了，颜色也能证明在变
        float r=0,g=0,b=0;
        if (g_viewIdx == 0) { r=0.10f; g=0.20f; b=0.90f; } // 蓝
        if (g_viewIdx == 1) { r=0.90f; g=0.20f; b=0.10f; } // 红
        if (g_viewIdx == 2) { r=0.10f; g=0.90f; b=0.20f; } // 绿
        glClearColor(r,g,b,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 4) 交换
        glfwSwapBuffers(win);
    }

    glfwDestroyWindow(win);
    glfwTerminate();
    return 0;
}
