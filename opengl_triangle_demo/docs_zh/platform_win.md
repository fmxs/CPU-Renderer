# Windows 平台部署说明

## 开发环境

* 系统：Windows 10/11 (64-bit)
* 编译器：MSVC（Visual Studio 自带）或 MinGW（GCC 工具链）
* 包管理：无内置，需要手动下载依赖
* OpenGL 注意事项：Windows 自带 `opengl32.dll`，无需额外安装

> 如果你还没有 Visual Studio 或 MinGW 环境，请先阅读 [windows\_setup.md](./windows_setup.md)，选择一条路线完成环境准备。

---

## 项目目录结构

以 `C:\dev\opengl_triangle_demo\` 为例，你需要手动创建以下文件夹结构：

```
C:\dev\opengl_triangle_demo\
├── CMakeLists.txt        # 构建配置文件（见下文）
├── include\              # 头文件目录（GLAD/KHR/GLFW 放这里）
│   ├── glad\
│   ├── KHR\
│   └── GLFW\
├── libs\                 # 库文件目录（.lib 或 .a 放这里）
├── shaders\              # 着色器文件目录
│   ├── triangle.vert
│   └── triangle.frag
├── src\                  # 源码目录
│   ├── main.cpp          # ⬅️ 必须包含 main 函数，否则链接失败
│   └── gl.c              # glad 加载器
└── build\                # 构建输出目录（CMake 生成）
```

---

## 编写 main.cpp（最小可运行）

```cpp
int main() {
    return 0;
}
```

> 没有 `main()` 函数将导致链接失败：LNK2019（VS）或 undefined reference（GCC）

---

## 安装依赖：GLFW + GLAD

### 1) GLFW

1\. 前往 [GLFW 官网下载页](https://www.glfw.org/download.html$。)

2\. 下载预编译包，例如：\`glfw-3.3.8.bin.WIN64.zip\`。

接下来请根据你的构建工具，使用压缩包中的目录：

#### 👉 Visual Studio 用户：

使用 `glfw-3.x.x.bin.WIN64.zip` 中的 `lib-vc2022` 目录：

```
include/GLFW/glfw3.h       → 复制到 include/GLFW
lib-vc2022/glfw3dll.lib    → 复制到 libs/
lib-vc2022/glfw3.dll       → 复制到 build/（exe 同目录）
```

#### 👉 MinGW 用户：

使用 `glfw-3.x.x.bin.MINGW.zip` 中的 `lib-mingw-w64` 目录：

```
include/GLFW/glfw3.h        → 复制到 include/GLFW
lib-mingw-w64/libglfw3dll.a → 复制到 libs/
lib-mingw-w64/glfw3.dll     → 复制到 build/（exe 同目录）
```

> ⚠️ 注意：`.lib` 文件是给 Visual Studio 用的，`.a` 是给 MinGW 用的，不能混用！

### 2) GLAD

1. 打开 [GLAD 在线生成器](https://gen.glad.sh/)
2. 选择语言：C/C++，API：OpenGL 3.2 Core，Profile：Core
3. 下载 zip 后放置：

```
glad.c（如果你下载到的文件叫gl.c，是一样的）            → src/
glad.h（如果你下载到的文件叫gl.h，是一样的）            → include/glad/
khrplatform.h     → include/KHR/
```

---

## 创建 CMakeLists.txt（通用于 VS / MinGW）

在项目根目录 \`C:\dev\opengl\_triangle\_demo\\\` 新建 \`CMakeLists.txt\`，填入 \*\*可直接使用\*\* 的最小模板（适配 GLFW 预编译动态库）：

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

---

## 构建与运行

### ✅ Visual Studio 用户：

```bash
# 打开 VS → 打开本地文件夹 → C:\dev\opengl_triangle_demo
# 自动识别 CMakeLists.txt → 点击绿色 ▶ 运行
```

确保 `glfw3.dll` 放在 `build/x64-Debug/` 下，否则运行时报错。

---

### ✅ MinGW 用户（命令行）：

```bash
cd C:\dev\opengl_triangle_demo\
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
```

生成成功后将 `glfw3.dll` 放入 `build/` 目录，然后运行：

```bash
./demo.exe
```

---

## ❗常见坑排查

| 错误提示                          | 原因说明              | 解决方法                              |
| ----------------------------- | ----------------- | --------------------------------- |
| `cannot find -lglfw3dll`      | MinGW 找不到 `.a` 文件 | 确保使用 `libglfw3dll.a` 而不是 `.lib`   |
| `LNK1104 无法打开 glfw3dll.lib`   | VS 没找到 `.lib`     | `.lib` 放入 libs/，并刷新 VS CMake 项目   |
| `找不到 glfw3.dll`               | 运行时 DLL 缺失        | 把 glfw3.dll 复制到 exe 同目录           |
| `undefined reference to main` | main 函数缺失         | 请确保 main.cpp 至少写了 `int main() {}` |

---

## ✅ 完整构建就绪！

你现在拥有：

* Visual Studio 或 MinGW 环境
* 正确的头文件、库文件路径
* 匹配的链接方式（lib/a）
* 能运行的 demo.exe

