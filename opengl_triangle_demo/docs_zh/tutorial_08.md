# OpenGL 三角形 Demo 实践教程：构建一个会呼吸的渐变三角形
## 渲染主循环 renderLoop()——让三角形“活”起来！

---

## 8-1 🧠 本节要解决的问题是什么？

你已经做了：

* 初始化窗口（GLFW）
* 配置 OpenGL（GLAD）
* 加载并编译 Shader 程序（createShaderProgram）
* 配置顶点数据（VAO + VBO）

但如果你现在运行程序，它会一闪而过。或者就一个空窗口啥也没有。

为啥？

因为你没有写“每一帧”要干什么！

---

## 8-2 🌀 什么是“渲染主循环”？

OpenGL 是个老实人，**它不会自动重绘**。你不告诉它“下一帧要干嘛”，它就静止在那里，哪怕你已经设置了所有东西。

所以我们需要写一个 `while` 循环，在里面告诉它：

* 当前帧要清什么颜色？
* 要不要更新时间？
* 要不要画东西？
* 要不要响应键盘鼠标？

这个循环就是所谓的 “**主循环（main loop）**”。

---

## 8-3 🧠 为什么必须“每一帧”都重新设置？

因为 GPU 不保留你前一帧的状态，**每一帧都是从头画起**。你不：

* 清屏，它就叠画在上面
* 用 program，它就不知道该用哪个
* 绑定 VAO，它就不知道画哪个东西
* 设置 uniform，它就不知道时间是多少

你以为 GPU 会记得？不，它连你是谁都不记得。

---

## 8-4 📦 本节目标：在main.CPP中写一个叫 `renderLoop()` 的函数

```cpp
void renderLoop(GLFWwindow* window, GLuint prog, GLuint vao, GLint u_time);
```

它的工作流程大致是：

1. 检查窗口是否关闭（如果用户点了叉叉，就退出循环）
2. 清空屏幕背景
3. 告诉 GPU 用哪个 shader 程序
4. 更新 `u_time` 这个全局变量，让三角形“呼吸”
5. 告诉 GPU：绑定哪个 VAO（里面有三角形的坐标数据）
6. 画出这个三角形
7. 把这一帧画的内容显示出来
8. 处理一下键盘鼠标事件，准备下一帧

这一整套流程会 **每一帧重复一次**，一直到你关闭窗口为止。

---

## 8-5 🪜 每一步具体干什么？为什么这样写？

---

### ① `while (!glfwWindowShouldClose(window)) {`

这是一个死循环，只有在用户关闭窗口时才会跳出。

也就是说：**只要窗口开着，GPU 就一直按照你的代码画画、画画、再画画。**

---

### ② `glClearColor(...) + glClear(...)`

```cpp
glClearColor(0.12f, 0.18f, 0.15f, 1.0f);
glClear(GL_COLOR_BUFFER_BIT);
```

这两行意思是：

> “我想要一个深绿色的背景，请你清掉上一帧的内容，然后重新来过。”

如果你不写这两行，你的三角形会堆在上一帧的残影上，就像在画布上不停地用蜡笔重复画一样，最终花成一坨。

---

### ③ `glUseProgram(prog);`

这句告诉 GPU：

> “我要使用这个已经编译好的 Shader 程序。”

你前面用了 `createShaderProgram(...)` 拿到的那个程序 ID，现在就是用它来“指导”这一帧该怎么画。

---

### ④ `glUniform1f(u_time, glfwGetTime());`

这句是你三角形能“呼吸”的关键。

你之前的 fragment shader 写了：

```glsl
float pulse = abs(sin(u_time));
```

那 `u_time` 是哪来的？**你得每一帧动态传进去当前时间。**

```cpp
glfwGetTime(); // 返回从程序启动到现在经过的秒数
```

就这样，你三角形的颜色每秒钟会变一次——像在跳动一样。

---

### ⑤ `glBindVertexArray(vao);`

你之前用 `setupTriangleVAO()` 配置好的 VAO，里面已经记录了你三角形的坐标 + 颜色数据。

现在你告诉 GPU：

> “我要画的几何体是这个 VAO 绑定的内容。”

---

### ⑥ `glDrawArrays(GL_TRIANGLES, 0, 3);`

终于，开始画图了！

这个函数的意思是：

* `GL_TRIANGLES` → 我要画的是三角形（每 3 个点为一组）
* `0` → 从第 0 个顶点开始
* `3` → 总共要画 3 个顶点

你那段数据是：

```cpp
// x, y,  r, g, b
-0.6, -0.4, 1, 0.2, 0.2,  // 顶点1
 0.6, -0.4, 0.2, 1, 0.2,  // 顶点2
 0.0,  0.6, 0.2, 0.2, 1   // 顶点3
```

所以正好一组三角形，画出来！

---

### ⑦ `glfwSwapBuffers(window);`

OpenGL 使用 **双缓冲**，你这一帧画好了，要用 `swap` 把它显示到屏幕上。

否则你会看到“正在绘制”的画面抖动，像老电视机。

---

### ⑧ `glfwPollEvents();`

这一帧结束了，我们要看一下有没有：

* 用户按了 ESC
* 用户移动了鼠标
* 用户拉伸了窗口

**没有这行代码，你的窗口会“假死”**，看起来像崩了一样。

---

## 8-6 ✅ 本节知识点汇总

| 步骤                          | 做什么          | 为什么要这样做      |
| --------------------------- | ------------ | ------------ |
| `glClearColor + glClear`    | 清屏           | 避免上一帧残留      |
| `glUseProgram`              | 使用 Shader 程序 | 指定怎么画        |
| `glUniform1f(u_time, time)` | 更新时间         | 让三角形动起来      |
| `glBindVertexArray(vao)`    | 加载三角形数据      | GPU 要知道画哪    |
| `glDrawArrays(...)`         | 开始画图         | 画出三角形        |
| `glfwSwapBuffers`           | 显示这一帧画面      | GPU 画的内容推上屏幕 |
| `glfwPollEvents()`          | 处理交互         | 保证窗口响应       |

---

## 8-7 📄 最终完整代码：renderLoop()

```cpp
void renderLoop(GLFWwindow* window, GLuint prog, GLuint vao, GLint u_time) {
    while (!glfwWindowShouldClose(window)) {
        // 1. 设置背景色 & 清屏
        glClearColor(0.12f, 0.18f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 2. 使用 Shader 程序
        glUseProgram(prog);

        // 3. 更新 uniform: u_time
        if (u_time >= 0)
            glUniform1f(u_time, static_cast<float>(glfwGetTime()));

        // 4. 绑定 VAO 并绘制三角形
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // 5. 显示 & 处理输入事件
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
```
