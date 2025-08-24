# macOS 平台部署说明

## 开发环境

* 系统：macOS 12+（Intel 或 Apple Silicon 均可）
* 编译器：clang（Xcode Command Line Tools 自带）
* 包管理：Homebrew（/usr/local… for Intel，/opt/homebrew… for Apple Silicon）
* OpenGL 注意事项：macOS 将 OpenGL 标记为 **Deprecated**，但 **Core Profile 3.2** 仍可用；需要 **Forward Compatibility**。

> TL;DR：在 mac 上跑 Core Profile，一定要加 `GLFW_OPENGL_FORWARD_COMPAT`，不然可能黑屏或创建上下文失败。

---

## 项目目录结构

以 `~/dev/opengl_triangle_demo/` 为例，你需要手动创建以下文件夹结构：

```
~/dev/opengl_triangle_demo/
├── CMakeLists.txt        # 构建配置文件
├── include/              # 头文件目录（GLAD/KHR 放这里）
│   ├── glad/
│   └── KHR/
├── shaders/              # 着色器文件目录
│   ├── triangle.vert
│   └── triangle.frag
├── src/                  # 源码目录
│   ├── main.cpp
│   └── gl.c
└── build/                # 空目录，CMake 会在这里生成构建结果
```

这样 CMake 才能正确识别工程。

---

## 准备环境

### 1) 安装 Xcode 命令行工具

```bash
xcode-select --install
```

### 2) 安装 Homebrew（如未安装）

参考 [https://brew.sh](https://brew.sh) 的官方脚本安装（Intel 安装到 `/usr/local`，Apple Silicon 安装到 `/opt/homebrew`）。

### 3) 安装 GLFW

```bash
brew update
brew install glfw
```

> 验证头文件与库位置：
>
> * Apple Silicon：`/opt/homebrew/include`, `/opt/homebrew/lib`
> * Intel：`/usr/local/include`, `/usr/local/lib`

---

## GLAD 文件

与其它平台相同，在线生成并放置到项目目录：

* `glad.c` → `src/`
* `glad.h` → `include/glad/`
* `khrplatform.h` → `include/KHR/`

GLAD 生成参数建议：

* Generator: **C/C++**
* API: **OpenGL 3.2** + **Core**

---

## main.cpp 中的 macOS 专属 Hint

在创建 OpenGL 上下文前添加 **Forward Compatibility**：

```cpp
// 必须在 glfwCreateWindow 之前设置
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
```

以及明确指定 Core Profile 版本（与 GLAD 选择一致）：

```cpp
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
```

---

## 创建 CMakeLists.txt（必须）

在项目根目录 `~/dev/opengl_triangle_demo/` 创建 `CMakeLists.txt` 文件，推荐最小可用模板：

```cmake
cmake_minimum_required(VERSION 3.15)
project(opengl_triangle_demo CXX)
set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 REQUIRED)

add_executable(demo
  src/main.cpp
  src/gl.c
)

# 本项目的头文件（放了 GLAD 头）
target_include_directories(demo PRIVATE ${CMAKE_SOURCE_DIR}/include)

# 链接 GLFW
target_link_libraries(demo PRIVATE glfw)
```

> 如果找不到 glfw，可以在命令行加上 `-DCMAKE_PREFIX_PATH=/opt/homebrew`（Apple Silicon）或者 `-DCMAKE_PREFIX_PATH=/usr/local`（Intel）。

---

## 构建与运行

```bash
mkdir -p build && cd build
# Apple Silicon 若需，显式告诉 CMake 去 Homebrew 前缀找包：
# cmake -DCMAKE_PREFIX_PATH=/opt/homebrew ..
cmake ..
cmake --build . -j
./demo
```

> 常见小坑：
>
> * **黑屏/创建失败**：忘了加 `GLFW_OPENGL_FORWARD_COMPAT`。
> * **链接不到 GLFW**：CMake 没找到 Homebrew 前缀，传 `-DCMAKE_PREFIX_PATH`。
> * **GLSL 版本不匹配**：你选择了 GL 3.2 Core，对应 GLSL `#version 150`；若改 3.3，对应 `#version 330`，保持一致。

---

## FAQ

**Q: macOS 的 OpenGL 都 Deprecated 了，还能学吗？**
A: 能。3.2 Core 足够入门渲染管线与 API 使用；等你把三角形、VAO/VBO、着色器、UBO、FBO 走一遍，再学 Vulkan/Metal 也更快。

**Q: 一定要装 Xcode 完整版吗？**
A: 不需要，装 Command Line Tools 即可（自带 clang、ld、headers）。

**Q: 我用的是 CLion / VSCode 可以吗？**
A: 可以，IDE 只要调用 CMake 构建即可。记得把 Homebrew 包含与库路径告诉 CMake。
