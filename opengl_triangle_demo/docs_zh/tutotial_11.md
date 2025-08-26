# OpenGL 三角形 Demo 实践教程：构建一个会呼吸的渐变三角形
# 🚀OpenGL 三角形 Demo 多平台部署教程 

---

你已经完成了所有内容，包括：

- `main.cpp`（主函数）
- `gl.c`（glad 入口）
- `triangle.vert` / `triangle.frag`（Shader 文件）
- `CMakeLists.txt`（构建配置）
  
接下来要做的事情是：

1. 确认工程目录结构是否正确
2. 分平台部署工程，**构建 + 编译 + 运行**

## 11-1 📁 工程目录要求（统一结构）

确保你的工程目录长这样（路径、大小写都要小心）：

```
C:\dev\opengl_triangle_demo\
├── CMakeLists.txt
├── include\
│   ├── glad\
│   └── KHR\
├── shaders\
│   ├── triangle.vert
│   └── triangle.frag
├── src\
│   ├── main.cpp
│   └── gl.c
```

> 注意：Windows 的盘符是 `C:\`，macOS/Linux 是 `~/` 或绝对路径，下面会分开说。

---

## 11-2 🪟 Windows - Visual Studio 构建（VS2019 与 VS2022 差异）

### ✅ 安装要求：

| 工具           | VS2019   | VS2022 |
| ------------ | -------- | ------ |
| C++ 工具链（必装）  | ✅        | ✅      |
| CMake ≥ 3.15 | ⚠️（需手动装） | ✅ 内置   |
| Shader 文件兼容性 | ✅        | ✅      |

### ✅ 路径 & 构建命令：

```bat
cd C:\dev\opengl_triangle_demo
mkdir build
cd build
```

* 如果你用 **VS2019**：

  ```bat
  cmake .. -G "Visual Studio 16 2019"
  ```
* 如果你用 **VS2022**：

  ```bat
  cmake .. -G "Visual Studio 17 2022"
  ```

> 生成 `.sln` 文件后双击打开，在 Visual Studio 中编译运行。

### ✅ 项目配置建议：

* 工程属性 → 工作目录设置为 `$(ProjectDir)\..\`
* 编译后 `.exe` 会出现在 `Debug` 或 `Release` 文件夹
* **链接使用 `glfw3dll.lib`，运行时需要 `glfw3.dll` 放到可执行文件目录**

---

## 11-3 🪟 Windows - MinGW 构建（命令行玩家）

### ✅ 安装要求：

* MinGW-w64
* GLFW 预编译包（使用 `lib-mingw-w64/` 中的库文件）
* glad 自己生成

### ✅ 正确的链接方式：

| 文件类型            | 作用   | MinGW 要求                 |
| --------------- | ---- | ------------------------ |
| `libglfw3dll.a` | 链接时用 | ✅ 必须（来自 `lib-mingw-w64`） |
| `glfw3.dll`     | 运行时用 | ✅ 必须放在 `.exe` 所在目录       |

⚠️ 注意：不要拿 Visual Studio 的 `glfw3dll.lib` 喂 MinGW，会链接失败！

### ✅ 构建命令：

```bat
cd C:\dev\opengl_triangle_demo
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
```

---

## 11-4 🍎 macOS 构建（M系列 / Intel）

### ✅ 安装依赖：

```bash
brew install glfw cmake
```

### ✅ 构建命令：

```bash
cd ~/dev/opengl_triangle_demo
mkdir build
cd build
cmake ..
make -j8
./bin/demo
```

> Shader 使用 `#version 150 core`，不要写老语法。

### ✅ mac 专属CMake内容

确保在你的文件`CMakeLists.txt`中存在下面的语句，如果没有就加到最后面：

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

## 11-5 🐧 Linux 构建（Ubuntu / Arch / WSL）

### ✅ 安装依赖：

```bash
sudo apt update
sudo apt install cmake g++ libglfw3-dev libgl1-mesa-dev
```

### ✅ 构建命令：

```bash
cd ~/dev/opengl_triangle_demo
mkdir build
cd build
cmake ..
make -j8
./bin/demo
```

---

## 11-6 📄 跨平台路径命令速查表

| 平台             | 进入路径命令                           | 构建命令                                            |
| -------------- | -------------------------------- | ----------------------------------------------- |
| Windows-VS2019 | `cd C:\dev\opengl_triangle_demo` | `cmake .. -G "Visual Studio 16 2019"`           |
| Windows-VS2022 | `cd C:\dev\opengl_triangle_demo` | `cmake .. -G "Visual Studio 17 2022"`           |
| Windows-MinGW  | `cd C:\dev\opengl_triangle_demo` | `cmake -G "MinGW Makefiles" .. && mingw32-make` |
| macOS          | `cd ~/dev/opengl_triangle_demo`  | `cmake .. && make -j8`                          |
| Linux          | `cd ~/dev/opengl_triangle_demo`  | `cmake .. && make -j8`                          |

---

## 11-7 ✅ 运行目录建议

> 保持在 `opengl_triangle_demo/` 根目录或 build 目录外层，确保 `shaders/` 能被找到。

运行 `.exe` 或 `./demo` 时一定要能读到 `shaders/triangle.vert` 和 `triangle.frag`。

