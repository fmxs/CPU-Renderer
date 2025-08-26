# 🎮 CPU/GPU 渲染实践合集 | CPU Renderer + OpenGL Triangle Demo

欢迎来到这个既手搓 CPU 光栅化、又玩转 GPU Shader 的综合性图形实践仓库。  
这里包含两个子项目，各自独立又互相关联，适合拿来当面试作品集/技术笔记/手工图形引擎参考。

---

## 📦 项目结构一览

| 目录名 | 项目说明 | 技术栈 | 适用平台 |
|--------|----------|--------|----------|
| [`TinyRenderer_tutorial/`](./TinyRenderer_tutorial) | 基于 C++/WinAPI 实现的 CPU 级光栅化渲染器 | C++、WinAPI、数学库 | Windows |
| [`opengl_triangle_demo/`](./opengl_triangle_demo) | 彩色三角形 + 动态 Shader 实现的 OpenGL demo | C++、GLFW、GLAD、OpenGL 3.2 | macOS / Windows |

---

## 🔧 快速开始（构建方法）

```bash
# OpenGL 彩色三角形 Demo（macOS / Windows）
cd opengl_triangle_demo
cmake -S . -B build
cmake --build build -j
./build/bin/tri
````

确保你已经安装以下依赖：
- CMake ≥ 3.15
- C++17 编译器（推荐 clang / MSVC / g++）
- 对于 OpenGL demo：
  - macOS：自带 OpenGL 3.2 Core Profile
  - Windows：需下载并配置 GLFW/GLAD（见子项目教程）


---

## 📚 子项目详情

### 🔸 [CPU 渲染器](./cpu-renderer/README.md)

基于 TinyRenderer 教程，从零实现光栅化渲染流程，包括：

* 手写数学库（Vector、Matrix）
* DDA/Bresenham 线段算法
* 屏幕坐标变换
* 扫描线三角形填充 + 背面剔除 + Z-buffer 消隐
* WinAPI 绘制窗口、键盘控制、FPS 显示

> 本项目更适合作为“图形学入门 + C++ 实战练手”的双拼套餐。
> 👉 阅读子项目文档：[TinyRenderer_tutorial/README.md](./TinyRenderer_tutorial/README.md)

---

### 🔸 [OpenGL Triangle Demo](./opengl_triangle_demo/README.md)

完整实现一个 GPU 渲染路径的小 Demo，包含：

* Vertex Shader + Fragment Shader 的编写与加载
* 时间驱动的颜色脉冲动画
* 使用 GLFW + GLAD 初始化上下文
* OpenGL Core Profile 下 glDrawArrays 调用路径分析

> 这是你面试时最容易讲清楚、又最容易 impress 面试官的小 demo。
> 👉 阅读子项目文档：[opengl\_triangle\_demo/README.md](./opengl_triangle_demo/README.md)

---

## 🗺️ 路线图（开发进度）

当前的学习和开发进度安排如下：

* [x] Week1: C++ 内存模型、对象池、自定义分配器
* [x] Week2: OpenGL Triangle + UI 批渲染系统构建中
* [ ] Week3: 网络同步 / FPS 专题（子弹、地图、穿透）
* [ ] Week4: 项目整合、面试话术准备

---

## 🧠 License & 联系方式

代码与文档基于 MIT 协议开放。
如有任何合作或内推交流，欢迎通过 GitHub Issues 联系我 @fmxs。

---
