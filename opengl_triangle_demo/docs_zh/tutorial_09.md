# OpenGL 三角形 Demo 实践教程：构建一个会呼吸的渐变三角形

# 清理资源，让程序优雅退出

---

## 9-1 🧠 我们之前创建了什么？

前面几节你写了好多初始化代码，但我们没管善后，现在就来清点一下家底：

| 类别             | 变量       | 作用                    |
| -------------- | -------- | --------------------- |
| Shader Program | `prog`   | GPU 执行用的程序（负责处理顶点/颜色） |
| VAO            | `vao`    | 顶点数组对象，记住数据怎么解释       |
| VBO            | `vbo`    | 顶点缓冲对象，保存三角形的坐标+颜色    |
| GLFW 窗口        | `window` | 你在屏幕上看到的那个窗口          |
| GLFW 全局状态      | (内部结构)   | GLFW 自己分配的一堆底层资源      |

---

## 9-2 🤔 哪些需要我们手动清理，哪些系统会自动帮你清？

| 资源               | 谁来管？  | 如果不手动清理会怎样？        |
| ---------------- | ----- | ------------------ |
| `prog`           | 你自己   | GPU 程序可能残留，调试困难    |
| `vao`, `vbo`     | 你自己   | 显存泄漏，长期运行会崩        |
| `window`         | 你自己   | 系统窗口资源可能僵尸化        |
| `glfwInit` 创建的状态 | 你自己   | 不能再次初始化，导致报错       |
| 所有 CPU 内存        | 操作系统  | 程序退出时会自动清，但别依赖它    |
| OpenGL context   | 系统+驱动 | 不总是立即释放，可能影响后续程序运行 |

🧠 所以总结一句：

> 系统可能**迟早会帮你收场**，但你**不主动清理就是等着背锅**，而且还容易养成坏习惯。

---

## 9-3 🔄 和创建一一对应的销毁逻辑怎么写？

| 创建方式                          | 销毁方式                             | 代码 |
| ----------------------------- | -------------------------------- | -- |
| `glCreateProgram()`           | `glDeleteProgram(prog);`         | ✔️ |
| `glGenVertexArrays(1, &vao);` | `glDeleteVertexArrays(1, &vao);` | ✔️ |
| `glGenBuffers(1, &vbo);`      | `glDeleteBuffers(1, &vbo);`      | ✔️ |
| `glfwCreateWindow(...)`       | `glfwDestroyWindow(window);`     | ✔️ |
| `glfwInit()`                  | `glfwTerminate();`               | ✔️ |

---

## 9-4 📦 销毁流程要按什么顺序做？

正确的顺序就像打扫战场，必须有条理：

1. **先清 GPU 对象**（Program、VAO、VBO）

   * 因为这些都是依赖于 OpenGL 上下文的，如果你先销毁窗口，它们就“找不到家”了
2. **再销毁窗口**（GLFW window）
3. **最后 Terminate GLFW**

### ❌ 如果你顺序搞反，比如：

* 先 `glfwTerminate()` → OpenGL context 直接失效
* 然后你再 `glDeleteProgram()` → GPU 直接报错或崩溃

所以一定要守顺序！

---

## 9-5 ✅ 最终清理代码：`cleanup(...)`

我们封装一个函数：

```cpp
void cleanup(GLuint program, GLuint vao, GLuint vbo) {
    glDeleteProgram(program);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}
```

> 它把你构建的三角形相关内容都收掉了。

---

## 9-6 🧱 在 main() 里完整清理流程长这样：

```cpp
renderLoop(window, prog, vao, u_time);

cleanup(prog, vao, vbo);          // 1. 清理 GPU 资源
glfwDestroyWindow(window);        // 2. 销毁窗口
glfwTerminate();                  // 3. 清理 GLFW 系统资源
return 0;
```

---

## 9-7 📄 全部完整代码：Day7-5 收尾代码段

```cpp
void cleanup(GLuint program, GLuint vao, GLuint vbo) {
    glDeleteProgram(program);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

// main() 结尾部分
renderLoop(window, prog, vao, u_time);
cleanup(prog, vao, vbo);
glfwDestroyWindow(window);
glfwTerminate();
return 0;
```

---

## 9-8 🧠 记忆口诀：GPU → 窗口 → 系统

> “把画笔收好，桌子擦干净，最后把房门锁了。”

---

## 🎉 你已经完整完成了一个 OpenGL 三角形项目的全生命周期！

| 阶段  | 动作                 | 你已经实现 |
| --- | ------------------ | ----- |
| 初始化 | 窗口 + GLAD          | ✅     |
| 准备  | Shader + VAO + VBO | ✅     |
| 渲染  | 主循环 + uniform 动画   | ✅     |
| 清理  | 程序 + 数据 + 上下文      | ✅     |
