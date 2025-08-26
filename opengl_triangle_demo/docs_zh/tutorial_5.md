# OpenGL 三角形 Demo 实践教程：构建一个会呼吸的渐变三角形

## 创建窗口 & 初始化 OpenGL 上下文

---

## 5-1 🧠 本节目标

这一节我们只做两件事：

1. **用 GLFW 创建一个窗口，指定使用 OpenGL 3.2 Core Profile**
2. **用 GLAD 加载 OpenGL 的所有函数指针**

这听着简单，但它们是整套 OpenGL 项目的**底座**。
你写 shader、VBO、绘图之前，全靠这一步打基础。

---

## 5-2 📐 本节函数设计思路

我们要写两个函数：

| 函数名                                             | 职责                                  | 返回                    |
| ----------------------------------------------- | ----------------------------------- | --------------------- |
| `GLFWwindow* initWindow(int width, int height)` | 创建窗口 + 上下文 + 设置 VSync + 处理窗口 resize | 成功返回窗口指针，失败返回 nullptr |
| `bool initGLAD()`                               | 使用 `gladLoadGL()` 加载所有 OpenGL 函数指针  | 加载成功返回 true，否则 false  |

---

## 5-3 🔧 为什么要这样封装？

你可能会问：**我干嘛不直接在 `main()` 里调用 glfwXxx 一堆初始化？**

答：**为了让每一步都像搭积木**。模块化之后：

* 教学时可以逐个讲函数，不怕新手晕
* 错误调试时能明确是哪步出错（是 GLFW，还是 GLAD？）
* 以后要换成 SDL / EGL / WebGL 的时候，更容易替换

代码不写成屎山，就是对未来版本的仁慈。

---

## 5-4 🧩 函数一：initWindow()

```cpp
GLFWwindow* initWindow(int width, int height) {
    if (!glfwInit()) return nullptr;
```

### 🧠 为什么不能省 glfwInit？

GLFW 是一个库，它不是魔法，它不常驻内存。你用前一定要先初始化。

---

```cpp
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
```

### 🧠 为什么指定 3.2 Core？

* 我们写的是现代 OpenGL（使用 shader 的），Core Profile 会禁用掉所有古董函数（glBegin 什么的）
* macOS 默认支持 OpenGL 到 3.2，不要瞎选 4.6，一选就 crash

---

```cpp
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
```

### 🧠 为什么只有 mac 需要 forward\_compat？

mac 是个“洁癖型”平台。你不告诉它“我不用老 API”，它直接不给你 context。

这句话的意思是：

> “请给我一个干净的、支持 Core Profile 的上下文，我发誓不用祖传函数。”

---

```cpp
    GLFWwindow* window = glfwCreateWindow(width, height, "Triangle", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return nullptr;
    }
```

* 如果成功，它会返回一个 `GLFWwindow*`
* 如果失败，你就老老实实清理资源退出，别跟 GLFW 玩硬刚

---

```cpp
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
```

### 🧠 为什么需要这两句？

* `makeContextCurrent`：你得告诉 OpenGL 当前在哪个窗口里绘图
* `swapInterval(1)`：开启 VSync，否则你的 GPU 可能会跑到屏幕都接不住

---

```cpp
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int w, int h) {
        glViewport(0, 0, w, h);
    });
```

### 🧠 为什么需要自动调整 viewport？

你窗口变了，绘图区域也要变。不然你窗口拉大了，画面还卡在小块中间。

这个 callback 相当于监听了窗口大小变化事件，每次窗口 resize，就重设 glViewport。

---

```cpp
    return window;
}
```

---

## 5-5 🧩 函数二：initGLAD()

```cpp
bool initGLAD() {
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return false;
    }
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";
    return true;
}
```

### 🧠 为什么我们需要 GLAD？

因为 OpenGL 是个“标准接口”，它的函数实现藏在显卡驱动里，而这些函数地址是“运行时加载”的。

GLAD 的职责就是帮你**查表，找这些函数的地址并存起来**，否则你连 `glDrawArrays` 都不能用。

---

## 5-6 ✅ 总结：我们在做什么 & 为什么这样做？

| 我们在做的事    | 背后的意义                       |
| -------- | --------------------------- |
| 初始化 GLFW | 告诉系统我要一个可用的 OpenGL 上下文      |
| 设置窗口参数   | 保证跨平台一致，强制使用现代 Core Profile |
| 创建窗口     | OpenGL 所有图像最终要画在这块窗口上       |
| 设置回调     | 保证窗口 resize 时图像不变形          |
| 初始化 GLAD | 加载所有 OpenGL 函数，启动 GPU 干活的能力 |

如果你连窗口都开不了，你谈什么 draw triangle？没这个基础，OpenGL 根本不会理你。

---

## 5-7 📄 最终完整代码（贴在教程结尾）

```cpp
GLFWwindow* initWindow(int width, int height) {
    if (!glfwInit()) return nullptr;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(width, height, "Triangle", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int w, int h) {
        glViewport(0, 0, w, h);
    });

    return window;
}

bool initGLAD() {
    if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return false;
    }
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";
    return true;
}
```
