# 🌈 OpenGL 彩色三角形 Demo（macOS 版）

> 🚀 这个 Demo 是我为了实践 OpenGL 渲染流水线，结合 Shader 动态效果而写的小项目，**从顶点坐标 → 插值颜色 → 动态 uniform 控制动画**，完整打通了现代 GPU 管线流程。  
> 它可作为本仓库 CPU 渲染器部分的「GPU 对照组」，有助于理解两种渲染方式的本质异同。

### 📁 项目路径：
`opengl_triangle_demo/`

### 💻 技术栈：
- C++
- OpenGL 3.2 Core Profile（macOS 兼容）
- GLAD + GLFW
- CMake 构建系统

### 🎯 实现效果：
- 屏幕显示一个彩色渐变三角形
- 三角形旋转（顶点着色器中通过时间控制）
- 颜色呼吸（片元着色器中通过 sin(time) 控制）

### 📷 效果图（带呼吸效果）：
<img width="1600" height="1260" alt="image" src="https://github.com/user-attachments/assets/4d03da7a-0596-4dff-aecb-9d7368341beb" />



### 📝 使用方法：

```bash
cd opengl_triangle_demo
cmake -S . -B build
cmake --build build -j
./build/bin/tri
