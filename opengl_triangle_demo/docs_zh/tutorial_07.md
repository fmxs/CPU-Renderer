# OpenGL 三角形 Demo 实践教程：构建一个会呼吸的渐变三角形

# 如何让 GPU 真正跑起来 —— Shader 编译与链接全流程讲透

---

## 🧠 背景问题一：GPU 到底需要什么？

咱写 `.vert` `.frag` 这些 Shader 文件，是人类友好格式，但 GPU 只认**机器指令**。

所以我们要做的事，其实是：

> 把 `.vert` 和 `.frag` 文件：
> → 读成字符串 → 编译成 GPU 能执行的中间代码 → 链接成一个 program → 使用这个 program 去渲染画面。

---

## 🧠 背景问题二：为啥不一口气“直接加载 shader 文件”？

因为 OpenGL 是设计给驱动厂商 + 多平台通用的图形接口，它不允许你随便贴个 `.vert` 进去：

* shader 代码在运行时必须用 `glShaderSource()` 传进去
* 你自己负责读文件、拼字符串、编译检查
* 成功后，才能被链接成可执行程序，被 `glUseProgram()` 使用

也就是说：

> **OpenGL 是不会帮你管理 Shader 文件的，它只认 C 风格字符串。**

---

## 7-1 🎯 本节目标

我们先需要写两个工具函数

```cpp
void checkShader(GLuint shader, const char* tag);
void checkProgram(GLuint prog);
```

之后，我们再来写一个通用函数：

```cpp
GLuint createShaderProgram(const char* vertPath, const char* fragPath);
```

它负责把：

* 一段 GLSL 顶点着色器代码
* 一段 GLSL 片元着色器代码

变成一个 **可执行的、绑定好了 attribute 槽、可以用来绘图的 GPU 程序 ID**。

---

## 7-2 🧪 checkShader / checkProgram —— 你防止黑屏的最后一道防线

### 🧠 为什么需要日志检查？

OpenGL 编译 shader 的过程不会报错、不会抛异常、不会弹窗。

如果你：

* 打错了变量名（比如 `gl_Positionn`）
* 漏了分号
* 用了 shader 不支持的函数
* Attribute 没连上、类型不对

你都不会在编译器那看到报错。你看到的是——一块**沉默的黑屏**。

所以你必须自己写一套“检查系统”，手动去：

* 查询 shader 编译状态
* 查询 program 链接状态
* 如果失败，打印日志
* 然后终止程序，别带 bug 继续执行

---

## 7-3 📄 函数一：checkShader()

```cpp
void checkShader(GLuint shader, const char* tag) {
    GLint ok = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        GLint len = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
        std::vector<char> log(len);
        glGetShaderInfoLog(shader, len, nullptr, log.data());
        std::cerr << "Shader compile failed [" << tag << "]:\n" << log.data() << "\n";
        throw std::runtime_error("shader compile failed");
    }
}
```

---

### 🧠 它在干嘛？

1. `glGetShaderiv(..., GL_COMPILE_STATUS)` → 看编译成功没
2. 如果失败：

   * 获取错误日志长度
   * 分配 char buffer
   * 用 `glGetShaderInfoLog()` 拿到错误详情
   * 打印错误信息
   * 抛出异常，防止继续运行

---

### 🧪 使用方式

```cpp
glCompileShader(vs);
checkShader(vs, "vertex");

glCompileShader(fs);
checkShader(fs, "fragment");
```

这样一旦 shader 写错，你就能看到：

```
Shader compile failed [vertex]:
ERROR: 0:7: 'vColor' : undeclared identifier 
```

而不是黑屏+怀疑人生。

---

## 7-4 📄 函数二：checkProgram()

```cpp
void checkProgram(GLuint prog) {
    GLint ok = 0;
    glGetProgramiv(prog, GL_LINK_STATUS, &ok);
    if (!ok) {
        GLint len = 0;
        glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
        std::vector<char> log(len);
        glGetProgramInfoLog(prog, len, nullptr, log.data());
        std::cerr << "Program link failed:\n" << log.data() << "\n";
        throw std::runtime_error("program link failed");
    }
}
```

---

### 🧠 它在干嘛？

跟 shader 的逻辑一样，但换成了对 `program` 的检查：

* 是否 link 成功？
* 如果失败：

  * 拿日志
  * 打出来
  * 抛异常终止

---

### 使用示例：

```cpp
glLinkProgram(prog);
checkProgram(prog);
```

比如你忘了绑定 `aColor` 变量，就会输出：

```
Program link failed:
error C5041: cannot locate attribute aColor
```

---

## 7-5 ✅ 为什么不把这俩合成一个函数？

可以，但不建议。因为：

* shader 和 program 是两种不同对象（GL\_SHADER vs GL\_PROGRAM）
* 日志函数不同：`glGetShaderInfoLog()` vs `glGetProgramInfoLog()`
* 错误类型不同：compile vs link

所以分开写更清晰，也方便你定位具体是哪一步出错。
---

## 7-6 🔨 createShaderProgram 步骤拆解

---

### ① 从磁盘读取 Shader 文件内容

```cpp
std::string vsrc = readTextFile(vertPath);
std::string fsrc = readTextFile(fragPath);
```

你写的 Shader 文件在硬盘上，是文本文件。

* 我们用 `std::ifstream` 读文件
* 存成 `std::string` 类型，准备传给 OpenGL
* 如果读失败（文件路径错），就直接报错崩溃

> 为什么我们用 `std::string` 而不是 char 数组？因为它更安全、更现代、易于检查和 debug。

---

### ② 编译 Vertex Shader

```cpp
GLuint vs = glCreateShader(GL_VERTEX_SHADER);
const char* vsp = vsrc.c_str();
glShaderSource(vs, 1, &vsp, nullptr);
glCompileShader(vs);
checkShader(vs, "vertex");
```

* `glCreateShader()`：告诉 GPU 我要建一个顶点着色器对象
* `glShaderSource()`：把我们写的代码贴进去
* `glCompileShader()`：请求编译（让 GPU 编译器来处理）
* `checkShader()`：调用封装函数读取编译日志，如果失败就报错退出

🧠 **为什么要封装 checkShader？**
因为你每写一个 shader 都得 compile，如果你拼错了变量名、漏了分号、用错了版本，不加日志你根本不知道哪错了。

---

### ③ 编译 Fragment Shader

逻辑完全一样：

```cpp
GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
const char* fsp = fsrc.c_str();
glShaderSource(fs, 1, &fsp, nullptr);
glCompileShader(fs);
checkShader(fs, "fragment");
```

---

### ④ 创建 Shader Program 并附加 Shader

```cpp
GLuint prog = glCreateProgram();
glAttachShader(prog, vs);
glAttachShader(prog, fs);
```

GPU 里的程序对象是一个“容器”：

* 可以 attach 多个编译好的 Shader
* 然后统一 link 成一个可执行程序

---

### ⑤ 绑定 Attribute 名称到位置（重点）

```cpp
glBindAttribLocation(prog, 0, "aPos");
glBindAttribLocation(prog, 1, "aColor");
```

⚠️ 必须 **在 `glLinkProgram()` 之前做！**

这是你告诉 GPU：

> “shader 里叫 `aPos` 的输入变量，应该绑定到 attribute 位置 0”

为什么你要手动做这一步？

* 如果你不绑定，它会自动分配位置
* 但你 VBO 那边是按 location 0/1 设置好的
* 如果对不上，**shader 就吃不到数据，画面一片黑！**

---

### ⑥ 链接 Shader Program

```cpp
glLinkProgram(prog);
checkProgram(prog);
```

* 这一步把所有 attach 上来的 shader 编译体合并成一个可执行程序
* 同样我们用 `checkProgram()` 来读取日志，如果失败就报错退出

🧠 **为什么可能失败？**

* Shader 间变量名不匹配（比如 `vColor` 没写一致）
* uniform 没被用（被优化掉）
* attribute 没绑定位置
* 某些平台不支持某个功能

---

### ⑦ 清理中间 shader 对象

```cpp
glDeleteShader(vs);
glDeleteShader(fs);
```

> 你创建的 shader 对象已经被拷进 program 里了，原对象没用了，可以释放。

这就像你把 `.cpp` 编译成 `.o` 后 `.cpp` 就可以删一样。



## 7-7 ✅ 最终完整代码：createShaderProgram

现在你已经知道每一步在干嘛，来看完整代码是不是清爽了：

```cpp
GLuint createShaderProgram(const char* vertPath, const char* fragPath) {
    std::string vsrc = readTextFile(vertPath);
    std::string fsrc = readTextFile(fragPath);

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    const char* vsp = vsrc.c_str();
    glShaderSource(vs, 1, &vsp, nullptr);
    glCompileShader(vs);
    checkShader(vs, "vertex");

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fsp = fsrc.c_str();
    glShaderSource(fs, 1, &fsp, nullptr);
    glCompileShader(fs);
    checkShader(fs, "fragment");

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);

    glBindAttribLocation(prog, 0, "aPos");
    glBindAttribLocation(prog, 1, "aColor");

    glLinkProgram(prog);
    checkProgram(prog);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return prog;
}
```

