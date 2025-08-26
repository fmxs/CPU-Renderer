# OpenGL 三角形 Demo 实践教程：构建一个会呼吸的渐变三角形

# OpenGL 教程尾声：功能增强篇（Shader 热重载 + Debug 输出 + 性能采样）

在你已经能顺利跑起那个“呼吸的彩色三角形”之后，我们进入最后一节：**实用功能增强**。

目标很简单：

* 你不想每次改 shader 都重启程序（我们教你如何热重载）
* 你不想再对 OpenGL 报错一脸懵（我们加 debug 回调）
* 你想知道每帧跑了多久（我们教你测 FPS）

---

## 12-1 Shader 热重载机制（跨平台 ✅）

### 🧠 为什么需要热重载？

你总不可能每次修改一行 `.vert` 文件就 `Ctrl + R` 重启整个程序吧？
热重载能让你调 shader 像调 CSS 一样爽：改完文件、按个键，立刻更新到屏幕。

### ⚙️ 实现思路

1. 在主循环中监听某个按键（比如 F5）
2. 按下时重新：

   * 读取文件内容
   * 编译 vertex + fragment shader
   * 链接成新 program
   * 替换 `glUseProgram`
   * 重新获取 uniform location

### 🔢 示例代码片段：

```cpp
if (glfwGetKey(window, GLFW_KEY_F5) == GLFW_PRESS) {
    GLuint newProg = createShaderProgram("../shaders/triangle.vert", "../shaders/triangle.frag");
    glUseProgram(newProg);
    u_time = glGetUniformLocation(newProg, "u_time");
    glDeleteProgram(prog);
    prog = newProg;
}
```

> 🔁 是否能用“文件变化监听”？可以，用 C++17 的 `filesystem::last_write_time()` 或平台 API。教程里我们用按键触发更简单。

✅ **全平台通用**：Windows / macOS / Linux 都能愉快热重载。

---

## 12-2 OpenGL Debug 输出（`KHR_debug` 支持差异）

> 💬 “macOS 用户无法使用本功能。可以跳过此节。原因是Apple 砍了它。

### 🧠 为什么需要 Debug 输出？

OpenGL 报错是静默的，不开调试输出你根本不知道你哪里错了。

> 举个例子：你 shader 少写个 `;`，程序照样运行，但屏幕是黑的。你想哭吗？

### ⚙️ 正确做法：注册 Debug 回调

```cpp
void GLAPIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                               GLsizei length, const GLchar* message, const void* userParam) {
    std::cerr << "[GL DEBUG] " << message << std::endl;
}

void enableDebugOutput() {
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debugCallback, nullptr);
}
```

### ⚠️ 平台差异说明：

| 平台      | 是否支持 `KHR_debug`  | 说明           |
| ------- | ----------------- | ------------ |
| Windows | ✅ 支持（OpenGL 4.3+） | 推荐开启         |
| Linux   | ✅ 支持（Mesa 兼容）     | 需要 4.3+ 驱动   |
| macOS   | ❌ 不支持             | Apple 根本不让你用 |

### 🛡 建议做法：

```cpp
#ifdef GL_KHR_debug
    enableDebugOutput();
#else
    std::cout << "[WARN] 当前平台不支持 OpenGL Debug 输出" << std::endl;
#endif
```


---

## 12-3 性能采样 & FPS 显示（跨平台 ✅）

### 🧠 为什么要测 FPS？

* 帧率能帮你直观看出渲染性能瓶颈
* 后续做 drawcall 优化、对象池优化都要靠它观察效果

### ⚙️ 推荐方案：GLFW 时间函数

```cpp
double lastTime = glfwGetTime();
int frameCount = 0;

while (!glfwWindowShouldClose(window)) {
    double current = glfwGetTime();
    frameCount++;

    if (current - lastTime >= 1.0) {
        std::cout << "FPS: " << frameCount << std::endl;
        frameCount = 0;
        lastTime = current;
    }

    // ... render + swap buffers
}
```

✅ **全平台支持**，GLFW 已经封装了高精度时钟。

---

## 12-4 ✅ 总结：功能 & 平台支持矩阵

| 功能项            | 跨平台支持        | 平台注意事项        |
| -------------- | ------------ | ------------- |
| Shader 热重载     | ✅            | 无             |
| OpenGL Debug输出 | ⚠️ macOS 不支持 | 用 `#ifdef` 包裹 |
| 性能采样 & FPS     | ✅            | 无             |

---
到目前为止的内容，一周时间已经可以做完。
下一节（如果我写了）：我们将进入 Week2，正式开写 UI 系统与 DrawCall 优化！
从“一个三角形”变成“一个游戏 UI 框架”的蜕变，从这一刻开始。
