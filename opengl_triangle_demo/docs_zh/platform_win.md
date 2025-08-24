# Windows 平台部署说明

## 开发环境

* 系统：Windows 10/11 (64-bit)
* 编译器：MSVC (Visual Studio 自带) 或 MinGW
* 包管理：无内置，需要手动下载依赖
* OpenGL 注意事项：Windows 自带 `opengl32.dll`，无需额外安装

## 安装依赖

### 1. GLFW

1. 前往 [GLFW 官网下载页](https://www.glfw.org/download.html)。
2. 下载对应的预编译包，例如：`glfw-3.3.8.bin.WIN64.zip`。
3. 解压后，将内容放置到项目中：

   * `include/GLFW` → 工程 `include/GLFW`
   * `lib-vc2022/*.lib` → 工程 `libs/`
   * `lib-vc2022/*.dll` → 可执行文件所在目录（运行时需要）

### 2. GLAD

1. 前往 [GLAD 在线生成器](https://gen.glad.sh/)。
2. 配置：

   * Generator: C/C++
   * APIs: GL 3.2 + Core
3. 下载 zip 包，解压后：

   * `glad.c` → `src/`
   * `glad.h` → `include/glad/`
   * `khrplatform.h` → `include/KHR/`

## CMake 配置

Windows 下需要显式链接 `opengl32.lib` 和 `glfw3.lib`。在 `CMakeLists.txt` 里添加：

```cmake
target_link_libraries(demo PRIVATE glfw3 opengl32)
```

如果使用的是 **预编译 GLFW 库**，请确保在 CMakeLists.txt 里设置：

```cmake
include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/libs)
```

## Visual Studio 配置方法（可选）

如果不用 CMake，直接在 VS 工程里配置：

* **C/C++ → 附加包含目录**：`include/`
* **链接器 → 附加库目录**：`libs/`
* **链接器 → 输入 → 附加依赖项**：`glfw3.lib; opengl32.lib;`

## 运行注意事项

* 运行程序时，需要确保 `glfw3.dll` 与可执行文件在同一目录。否则会报错“missing glfw3.dll”。
* Windows 不需要设置 `GLFW_OPENGL_FORWARD_COMPAT`，只要 core profile 就能正常运行。
