# Windows 平台部署说明

## 开发环境

* 系统：Windows 10/11 (64-bit)
* 编译器：MSVC (Visual Studio 自带) 或 MinGW
* 包管理：无内置，需要手动下载依赖
* OpenGL 注意事项：Windows 自带 `opengl32.dll`，无需额外安装

> 如果你还没有 Visual Studio 或 MinGW 环境，请先阅读 [windows\_setup.md](./windows_setup.md)，选择一条路线完成环境准备。

---

## 项目目录结构

以 `C:\dev\opengl_triangle_demo\` 为例，你需要手动创建以下文件夹结构：

```
C:\dev\opengl_triangle_demo\
├── CMakeLists.txt        # 构建配置文件（见下文「创建 CMakeLists.txt」）
├── include\              # 头文件目录（GLAD/KHR/GLFW 放这里）
│   ├── glad\
│   ├── KHR\
│   └── GLFW\
├── libs\                 # 库文件目录（.lib 放这里，编译时使用）
├── shaders\              # 着色器文件目录
│   ├── triangle.vert
│   └── triangle.frag
├── src\                  # 源码目录
│   ├── main.cpp
│   └── gl.c
└── build\                # 空目录，CMake 会在这里生成构建结果
```

---

## 安装依赖

### 1) GLFW

1. 前往 [GLFW 官网下载页](https://www.glfw.org/download.html)。
2. 下载预编译包，例如：`glfw-3.3.8.bin.WIN64.zip`。
3. 解压后会看到：

   * `include/GLFW/glfw3.h`
   * `lib-vc2022/glfw3.lib`（静态库）
   * `lib-vc2022/glfw3dll.lib`（**动态库的导入库**，编译时用）
   * `lib-vc2022/glfw3.dll`（**动态库本体**，运行时用）
4. 放置方式：

   * `include/GLFW` → 复制到 **工程** `include/GLFW`
   * `lib-vc2022/*.lib` → 复制到 **工程** `libs/`
   * `lib-vc2022/*.dll` → 复制到 **exe 同目录**（通常在 `build/Debug/` 或 `build/Release/`）

> 建议新手使用 **动态库**：编译时链接 `glfw3dll.lib`，运行时确保 `glfw3.dll` 在 exe 同目录。

### 2) GLAD

1. 打开 [GLAD 在线生成器](https://gen.glad.sh/)。
2. 选择 **C/C++**，API 选 **OpenGL 3.2 Core**（与教程一致）。
3. 下载 zip 后放置：

   * `glad.c` → `src/`
   * `glad.h` → `include/glad/`
   * `khrplatform.h` → `include/KHR/`

---

## 创建 CMakeLists.txt（必须）

在项目根目录 `C:\dev\opengl_triangle_demo\` 新建 `CMakeLists.txt`，填入 **可直接使用** 的最小模板（适配 GLFW 预编译动态库）：

```cmake
cmake_minimum_required(VERSION 3.15)
project(opengl_triangle_demo CXX)
set(CMAKE_CXX_STANDARD 17)

# 1) 先声明可执行程序的源文件
add_executable(demo
  src/main.cpp
  src/gl.c
)

# 2) 让编译器找到头文件（GLAD/KHR/GLFW 都在 include/ 下）
target_include_directories(demo PRIVATE
  ${CMAKE_SOURCE_DIR}/include
)

# 3) 告诉链接器 .lib 在哪（我们把 .lib 放在项目根的 libs/ 下）
link_directories(${CMAKE_SOURCE_DIR}/libs)

# 4) 链接库（动态库导入库 + 系统 OpenGL）
#    若你使用静态库，则把 glfw3dll 替换为 glfw3
#    MSVC 和 MinGW 都使用 opengl32 这个系统库名

if (WIN32)
  target_link_libraries(demo PRIVATE glfw3dll opengl32)
else()
  message(FATAL_ERROR "This CMakeLists is for Windows only")
endif()
```

> 常见坑：
>
> * **目标名对不上**：你若把 `add_executable(demo ...)` 改成了别的名字，`target_link_libraries` 也要同步改名。
> * **缺少 .dll**：运行时报错找不到 `glfw3.dll`，请把它放到 exe 同目录（`build/Debug/` 或 `build/Release/`）。
> * **包含目录不全**：确保 `include/GLFW/glfw3.h`、`include/glad/gl.h`、`include/KHR/khrplatform.h` 都在位。

---

## 构建与运行

### Visual Studio（推荐新手）

1. 打开 VS → **打开本地文件夹** → 选择 `C:\dev\opengl_triangle_demo\`
2. 首次会自动“配置 CMake”；顶部出现绿色运行按钮
3. 确保 `glfw3.dll` 已放到 `build/Debug/`（或 `build/Release/`）旁 → 运行

### MinGW（命令行）

```powershell
cd C:\dev\opengl_triangle_demo\
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
```

* 将 `glfw3.dll` 复制到 `build/` 里生成的 exe 同目录后再运行：

```powershell
./demo.exe
```

---

## 运行注意事项

* 动态库方案务必把 `glfw3.dll` 放在 exe 同目录；否则会提示缺少 DLL。
* Windows 不需要 `GLFW_OPENGL_FORWARD_COMPAT`（那是 macOS 的要求）。
* 若你切换到静态库 `glfw3.lib`，请留意其依赖（可能需要额外链接 `gdi32`、`user32`、`shell32` 等，具体以 GLFW 包说明为准）。
