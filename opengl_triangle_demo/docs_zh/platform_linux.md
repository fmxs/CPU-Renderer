# Linux 平台部署说明

## 开发环境

* 系统：常见发行版（Ubuntu/Debian、Fedora/CentOS、Arch 等）
* 编译器：GCC 或 Clang
* 包管理：各发行版自带（apt / dnf / pacman 等）
* OpenGL 栈：Mesa（开源实现）或厂商驱动（NVIDIA/AMD），需要 **dev 头文件**

> 小贴士：Linux 的“能跑起来”= 驱动 + 头文件 + 链接库，缺哪个都不行。

---

## 必备依赖安装

### Ubuntu / Debian（apt）

```bash
sudo apt update
# OpenGL 头文件 + 链接库
sudo apt install -y build-essential cmake pkg-config libgl1-mesa-dev
# X11 头文件（GLFW 默认走 X11，除非你特意编 Wayland 后端）
sudo apt install -y xorg-dev
# GLFW（推荐用系统包；也可源码编译）
sudo apt install -y libglfw3-dev
```

### Fedora / RHEL / CentOS（dnf）

```bash
sudo dnf groupinstall -y "Development Tools"
sudo dnf install -y cmake pkgconf-pkg-config mesa-libGL-devel libX11-devel libXrandr-devel libXinerama-devel libXcursor-devel libXi-devel glfw-devel
```

### Arch / Manjaro（pacman）

```bash
sudo pacman -Syu --noconfirm
sudo pacman -S --noconfirm base-devel cmake pkgconf mesa glfw-x11
```

> 如果你全机都用 Wayland，可选 `glfw-wayland`；否则用 `glfw-x11` 兼容更广。

---

## GLAD 文件

与其它平台相同：

1. 打开 [https://gen.glad.sh/](https://gen.glad.sh/)
2. 选择 **C/C++**，API 选 **OpenGL 3.2 Core**（或更高）
3. 下载 zip，解压后放置：

   * `glad.c` → `src/`
   * `glad.h` → `include/glad/`
   * `khrplatform.h` → `include/KHR/`

---

## CMake 配置（推荐：使用 pkg-config）

Linux 上最稳的是让 CMake 通过 pkg-config 找 GLFW 和依赖：

```cmake
cmake_minimum_required(VERSION 3.15)
project(opengl_triangle_demo)
set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW3 REQUIRED glfw3)

add_executable(demo
    src/main.cpp
    src/gl.c
)

# 头文件目录
target_include_directories(demo PRIVATE
    ${GLFW3_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
)

# 链接库（pkg-config 会把 X11/pthread/dl 等一起带上）
target_link_libraries(demo PRIVATE ${GLFW3_LIBRARIES})

# 一些发行版需要显式加上
if (UNIX)
    find_package(Threads REQUIRED)
    target_link_libraries(demo PRIVATE Threads::Threads)
endif()
```

> 说明：不同发行版对 X11/Wayland 的拆分包不同。`pkg-config` 能自动拼好大多数依赖（`-lX11 -lXrandr -lXi -lXcursor -ldl -lpthread …`）。

---

## 运行注意事项

* **无需** `GLFW_OPENGL_FORWARD_COMPAT`（那是 macOS 的锅）。
* 如果你用 NVIDIA 专有驱动，确保已安装对应的 **-dev/**-devel 包或 DKMS，避免缺头文件/符号。
* Wayland 环境下如果窗口黑屏或创建失败：

  * 尝试安装 `glfw-wayland` 并重新编译；或
  * 在桌面会话切到 Xorg（登录界面选择 X11）。

---

## 常见错误对照

* `fatal error: GL/gl.h: No such file or directory` → 缺 `libgl1-mesa-dev`（或 Mesa-devel）。
* 链接时报 `undefined reference to X11…` → 没走 pkg-config，或缺 X11 相关 dev 包。
* 运行时报 `libglfw.so not found` → 运行时库路径缺失，`sudo ldconfig` 或把库装成系统包，不要手动拷到奇怪位置。

---

## 目录约定回顾

项目目录与其它平台一致：

```
opengl_triangle_demo/
├── CMakeLists.txt
├── include/
│   ├── glad/gl.h
│   └── KHR/khrplatform.h
├── shaders/
│   ├── triangle.vert
│   └── triangle.frag
├── src/
│   ├── main.cpp
│   └── gl.c
└── build/
```

> 编译步骤：
>
> ```bash
> mkdir -p build && cd build
> cmake .. && cmake --build . -j
> ./demo
> ```
