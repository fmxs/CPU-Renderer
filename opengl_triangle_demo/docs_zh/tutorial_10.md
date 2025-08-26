# OpenGL 三角形 Demo 实践教程：构建一个会呼吸的渐变三角形

# 主函数结构梳理 & 代码回顾总结

---

## 10-1 🧠 main.cpp 是整套系统的“大总管”

前面我们一共写了 7 个步骤：

| 阶段                         | 负责内容            | 函数                                        |
| -------------------------- | --------------- | ----------------------------------------- |
| 1️⃣ 初始化 GLFW & 创建窗口        | 搭建画布            | `initWindow()`                            |
| 2️⃣ 加载 OpenGL 函数           | 拿到画笔            | `initGLAD()`                              |
| 3️⃣ 加载 Shader 文件 + 编译 + 链接 | 创建画图方案          | `createShaderProgram()`                   |
| 4️⃣ 设置 VAO / VBO           | 告诉 GPU 哪块内存是三角形 | `setupTriangleVAO()`                      |
| 5️⃣ 启动主循环                  | 每帧绘制            | `renderLoop()`                            |
| 6️⃣ 退出时释放资源                | 收工扫地            | `cleanup()`                               |
| 7️⃣ 销毁窗口 + 退出系统            | 锁门回家            | `glfwDestroyWindow()` + `glfwTerminate()` |

`main()` 就是把这些步骤，按照逻辑顺序**串起来执行一遍**的地方。

它的核心目标只有一个：

> “用最少的主函数代码，清晰地表达出程序的执行流程。”

---

## 10-2 📚 回顾我们每一节教程写了什么？

---

### ✅ 创建窗口 + 初始化 OpenGL

你通过 `initWindow()` 和 `initGLAD()` 做到了：

* 告诉系统我要用 OpenGL 3.2 Core
* 成功创建出窗口和上下文
* 加载所有 OpenGL 函数，拿到画图权限

---

### ✅ 配置三角形的顶点数据

你写了 `setupTriangleVAO()`，创建了：

* 顶点数组对象 VAO → 存储“怎么读数据”
* 顶点缓冲对象 VBO → 真正的 float 数据

通过 `glVertexAttribPointer()`，你告诉 GPU：

* 每 5 个 float 是一个顶点
* 前 2 个是位置（vec2）→ aPos
* 后 3 个是颜色（vec3）→ aColor

---

### ✅ 创建 Shader Program

你写了 `createShaderProgram()`，完成了：

* 从磁盘读取 `.vert` 和 `.frag` 源码
* 编译 shader
* 绑定变量名到位置（aPos/aColor）
* 链接成 GPU 可执行程序
* 报错时输出编译日志，避免黑屏找不到原因

---

### ✅ 启动渲染主循环

你写了 `renderLoop()`，每一帧做了这些事：

* 清除上一帧图像，填上背景色
* 绑定 shader program
* 更新时间（uniform float u\_time）
* 绑定 VAO，画出三角形
* 显示当前帧画面
* 监听用户输入（ESC / resize / 关闭窗口）

> 你在 Shader 里写的动画逻辑就是靠 `glfwGetTime()` 每一帧更新出来的！

---

### ✅ 收尾 + 清理资源

你写了 `cleanup()` 函数，把用过的都收了：

* 删除 Shader Program（`glDeleteProgram`）
* 删除 VAO、VBO（`glDelete*`）
* 销毁窗口（`glfwDestroyWindow`）
* 释放 GLFW 状态（`glfwTerminate`）

程序就能优雅退出，像个“有素养的开发者”。

---

## 10-3 🪜 如何把所有模块串成一条清晰的执行路径？

你这个三角形 Demo 的**核心执行脉络**其实就是这 7 步：

```
1. 初始化图形系统
2. 加载图形函数表（GLAD）
3. 准备 Shader 程序（告诉 GPU 怎么画）
4. 准备顶点数据（告诉 GPU 画什么）
5. 每帧绘制图像（时间驱动）
6. 响应窗口/用户事件（交互驱动）
7. 程序退出，清理资源
```

每一步都通过一个独立函数实现，你在 `main()` 里只要关心“顺序”，不用去纠结“细节”。

---

## 10-4 ✅ 最终 main 函数代码（包含所有环节）

```cpp
int main() {
    // 1. 创建窗口和 OpenGL 上下文
    GLFWwindow* window = initWindow(800, 600);
    if (!window) return -1;

    // 2. 加载 OpenGL 函数地址
    if (!initGLAD()) return -1;

    // 3. 创建 Shader Program
    GLuint prog = createShaderProgram("../shaders/triangle.vert", "../shaders/triangle.frag");

    // 4. 获取 uniform 变量位置（用于传递时间）
    GLint u_time = glGetUniformLocation(prog, "u_time");

    // 5. 创建并配置三角形数据
    GLuint vbo;
    GLuint vao = setupTriangleVAO(vbo);

    // 6. 启动主循环
    renderLoop(window, prog, vao, u_time);

    // 7. 清理资源
    cleanup(prog, vao, vbo);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
```

> 注意：`setupTriangleVAO()` 返回 `vao`，同时通过引用参数输出 `vbo`。

---


你不是在“写一堆图形代码”，你是在**搭建一个完整的图形生命周期**：

> 初始化 → 数据准备 → 指令编译 → 渲染驱动 → 资源释放

现在你已经完成了从 0 到 1 的第一步。你写出来的程序，**不只是能跑，而是结构清晰、逻辑完整、便于扩展。**
