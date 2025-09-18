// file: d00_min_loop/main.cpp
#include <GLFW/glfw3.h>
#include <cstdio>

int main() {
    if (!glfwInit()) { std::fprintf(stderr, "glfwInit failed\n"); return -1; }

    GLFWwindow* win = glfwCreateWindow(640, 360, "d00_min_loop", nullptr, nullptr);
    if (!win) { std::fprintf(stderr, "create window failed\n"); glfwTerminate(); return -2; }
    glfwMakeContextCurrent(win);

    // 最小循环：处理事件 + 交换前后缓冲
    while (!glfwWindowShouldClose(win)) {
        glfwPollEvents();
        glfwSwapBuffers(win);
    }

    glfwDestroyWindow(win);
    glfwTerminate();
    return 0;
}
