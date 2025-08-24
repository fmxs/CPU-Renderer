# OpenGL 三角形 Demo 实践教程：构建一个会呼吸的渐变三角形

## 一、项目简介

这个 Demo 是我为了实践 OpenGL 渲染流水线而构建的小程序，通过一个给定三角形的顶点位置和颜色，通过 Shader 实现颜色渐变和呼吸效果，完整路途连通 GPU 渲染流程。

### 效果预览

* 显示一个带呼吸效果的三角形
* 顶点颜色不同，通过接管接管渐变
* 数字线性跳动呼吸，通过 fragment shader 实现

## 二、开发环境（通用部分）

| 组件   | 说明                      |
| ---- | ----------------------- |
| 构建工具 | CMake                   |
| 图形库  | OpenGL 3.2 Core Profile |
| 依赖   | GLFW + GLAD             |

> 平台差异请参考 `platform_mac.md`、`platform_win.md`、`platform_linux.md` 等文件。

## 三、项目结构

首先在本地新建一个大文件夹，名字叫 opengl\_triangle\_demo。
再创建几个子文件夹：

* `include`：放头文件（以后 GLAD 的头文件会住在这里）。
* `shaders`：放着色器文件（.vert、.frag），就像给三角形化妆的工具。
* `src`：放源码（.cpp、.c），也就是主程序入口和 GLAD 的实现。
* `build`：空着，等我们用 CMake 构建工程时，它会生成一堆编译结果文件。

最终的目录长这样（此时还没往里塞具体文件）：

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
└── build/      # 构建后生成
```

### 各文件说明

* `main.cpp`：主程序，初始化 GLFW/GLAD，创建窗口，绘制三角形
* `gl.c/.h` + `khrplatform.h`：OpenGL 函数加载器
* `triangle.vert`：vertex shader，做颜色传递
* `triangle.frag`：frag shader，计算呼吸效果并添加渐变
* `CMakeLists.txt`：构建配置

## 四、环境部署（通用部分）

### 下载 GLAD 文件

前往 [https://gen.glad.sh/](https://gen.glad.sh/) 选择配置：

* Generator: C/C++
* APIs: GL 3.2 + Core

下载 zip 后，将内容放到:

* `gl.c` 放到 `src/`
* `gl.h` 放到 `include/glad/`
* `khrplatform.h` 放到 `include/KHR/`

---

平台特定的安装与编译说明请查看：

* macOS: [platform\_mac.md](./platform_mac.md)
* Windows: [platform\_win.md](./platform_win.md)
* Linux: [platform\_linux.md](./platform_linux.md)
