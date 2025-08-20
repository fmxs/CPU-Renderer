# OpenGL 三角形 Demo 实践教程：构建一个会呼吸的渐变三角形

## 一、项目简介

这个 Demo 是我为了实践 OpenGL 渲染流水线而构建的小程序，通过一个给定三角形的顶点位置和颜色，通过 Shader 实现颜色渐变、自动旋转和呼吸效果，完整路途连通 GPU 渲染流程。

### 效果预览

* 显示一个带呼吸效果的三角形
* 顶点颜色不同，通过接管接管渐变
* 数字线性跳动呼吸，通过 fragment shader 实现

## 二、开发环境

| 组件   | 说明                               |
| ---- | -------------------------------- |
| 系统   | macOS (Apple Silicon / Intel 均可) |
| 编译器  | clang (Xcode 自带)                 |
| 包管理  | Homebrew                         |
| 构建工具 | CMake                            |
| 图形库  | OpenGL 3.2 Core Profile          |
| 依赖   | GLFW + GLAD                      |

> 注：macOS 上 OpenGL 被弃用，但 3.2 Core 版本仍可用，是经典入门选择。

## 三、项目结构

```
opengl_triangle_demo/
├── CMakeLists.txt
├── include/
│   ├── glad/glad.h
│   └── KHR/khrplatform.h
├── shaders/
│   ├── triangle.vert
│   └── triangle.frag
├── src/
│   ├── main.cpp
│   └── glad.c
└── build/      # 构建后生成
```

### 各文件说明

* `main.cpp`：主程序，初始化 GLFW/GLAD，创建窗口，绘制三角形
* `glad.c/.h` + `khrplatform.h`：OpenGL 函数加载器
* `triangle.vert`：vertex shader，做坐标旋转和颜色传递
* `triangle.frag`：frag shader，计算呼吸效果并添加渐变
* `CMakeLists.txt`：构建配置

## 四、环境部署

### 安装 GLFW

```bash
brew install glfw
```

### 生成 GLAD 文件

前往 [https://gen.glad.sh/](https://gen.glad.sh/) 选择配置：

* Language: C/C++
* Specification: OpenGL
* API: OpenGL 3.2 + Core Profile + Forward Compatible

在点击确认生成后，你应该会看到这样的一个网页：
<img width="2128" height="1172" alt="image" src="https://github.com/user-attachments/assets/f1d5443e-c0c7-4bb2-8681-43fe44f34006" />


下载 zip 后，将内容放到:

* `glad.c` 放到 `src/`
* `glad.h` 放到 `include/glad/`
* `khrplatform.h` 放到 `include/KHR/`

