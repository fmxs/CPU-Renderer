# OpenGL 三角形 Demo 实践教程：构建一个会呼吸的渐变三角形

# 🚀 构建三角形 Demo 的工程 & 跨平台部署

---

## 11-1 🎯 教程目标

你已经完成了所有内容，包括：

* `main.cpp`（主函数）
* `gl.c`（glad 入口）
* `triangle.vert` / `triangle.frag`（Shader 文件）
* `CMakeLists.txt`（构建配置）

接下来要做的事情是：

1. 确认工程目录结构是否正确
2. 分平台部署工程，**构建 + 编译 + 运行**

---

## 11-2 ✅ 检查文件目录结构（四个核心文件夹）

确保你的工程目录长这样（路径、大小写都要小心）：

```
opengl_triangle_demo/
├── CMakeLists.txt
├── include/
│   ├── glad/ gl.h
│   └── KHR/ khrplatform.h
├── shaders/
│   ├── triangle.vert
│   └── triangle.frag
├── src/
│   ├── main.cpp
│   └── gl.c
```

> 注意：glad 是你从官网生成的代码，别直接用系统的 GLEW。

---

## 11-3 🪟 Windows - Visual Studio 部署方式（推荐 IDE 用户）

#### ✅ 1. 下载并安装以下工具：

* Visual Studio（2022 或以上）
* 安装时勾选 “Desktop development with C++”
* CMake（可选，VS 内置也支持）

#### ✅ 2. 打开命令行，构建工程：

```bash
mkdir build && cd build
cmake .. -G "Visual Studio 17 2022"
```

会生成一个 `.sln` 工程文件，双击它，在 Visual Studio 里打开。

#### ✅ 3. 设置运行目录（运行时找不到 shader 会崩）

* 点中 `demo` 项目 → 属性（Properties）
* 修改工作目录：`$(ProjectDir)/../`（确保能读到 `shaders/`）

#### ✅ 4. 编译 & 运行

直接按下 F5，Visual Studio 会构建并运行项目。

---

## 11-4 🪟 Windows - MinGW 构建方式（命令行玩家）

#### ✅ 1. 安装依赖工具

* 安装 MinGW-w64（64位）
* 安装 CMake
* 下载 GLFW 预编译包（glfw-3.3.8.bin.WIN64.zip）

#### ✅ 2. 项目目录结构需额外包含：

```
libs/
├── glfw3.dll
├── glfw3dll.lib
```

> `glfw3.dll` 需要复制到最终生成的 `.exe` 所在目录！

#### ✅ 3. 构建步骤

```bash
mkdir build && cd build
cmake -G "MinGW Makefiles" .. 
mingw32-make
```

生成 `demo.exe`，别忘了把 `glfw3.dll` 放到它旁边，然后运行。

---

## 11-5 🍎 macOS 构建方式（M系列芯片 / Intel 通吃）

#### ✅ 1. 安装依赖工具（用 Homebrew）

```bash
brew install glfw cmake
```

#### ✅ 2. 构建步骤

```bash
mkdir build && cd build
cmake ..
make -j8
./bin/demo
```

macOS 自带 OpenGL.framework，Shader 需使用 `#version 150 core`，不能用老语法。

#### ✅ 3. macOS 特别注意：

* Shader 使用 Core Profile
* `CMakeLists.txt` 中需要加上：

```cmake
if(APPLE)
  target_link_libraries(demo
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
  )
endif()
```

---

## 11-6 🐧 Linux（Ubuntu / Arch / WSL 都通吃）

#### ✅ 1. 安装依赖

```bash
sudo apt update
sudo apt install cmake g++ libglfw3-dev libgl1-mesa-dev
```

#### ✅ 2. 构建步骤

```bash
mkdir build && cd build
cmake ..
make -j8
./bin/demo
```

#### ✅ WSL（Windows Subsystem for Linux）

你可以编译，但默认没有 GUI。要显示图形界面，请先装一个 WSL GUI 桥接器（如 X410）。

---

## 11-7 🧱 常见问题排查（跨平台共通）

| 问题                                  | 可能原因         | 解决方式                                  |
| ----------------------------------- | ------------ | ------------------------------------- |
| `glad.h: No such file or directory` | include 路径不对 | 放进 `include/glad/` 目录                 |
| 黑屏但窗口能打开                            | Shader 加载失败  | 检查 `shaderPath` 是否正确                  |
| 报找不到 glfw3.dll                      | 没放到可执行文件目录   | 复制到 `.exe` 所在文件夹                      |
| `GL version not supported`          | Shader 写法不兼容 | macOS 用 `#version 150 core`，不要用 `120` |

---

## 11-8 ✅ 跨平台构建命令速查表

| 平台            | 构建命令                                            |
| ------------- | ----------------------------------------------- |
| macOS         | `cmake .. && make -j8`                          |
| Linux         | `cmake .. && make -j8`                          |
| Windows-MinGW | `cmake -G "MinGW Makefiles" .. && mingw32-make` |
| Windows-VS    | `cmake .. -G "Visual Studio 17 2022"` → F5      |

---

下一节，胖爷可以给你写一份跨平台 `README.md` 或者教你怎么打包 zip / 版本管理，
也可以进入 Week2 正题：**UI drawcall 优化、背包/排行榜 Demo 架构**。

选吧，天真，这节是铺地板，下一节开始造家具了。往哪走？
