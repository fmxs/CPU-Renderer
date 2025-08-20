本仓库包括 CPU 渲染器实现（使用 WinAPI）以及 GPU 渲染器对照 demo（使用 OpenGL）。
# 关于 Tiny Renderer
Tiny Renderer是ssloy制作的CPU渲染器教程，不过是全英文，本人根据他的教程写了中文教程。

由于github记笔记比较麻烦，请转移至Notion上查阅：

https://www.notion.so/TinyRenderer-202302131552-b99e56b11f714a269960e88fe5fcd371

# CPU Renderer编写流程
从零开始写一个Cpu渲染器，对C++小白友好

语言：C++

编译器：Visual Studio 2022

## 编写流程：
## 1. 数学库的编写
1. 实现VECTOR3
2. 实现VECTOR4，
3. 实现MATRIX4，包括转置矩阵，矩阵与向量的乘法问题（左乘，右乘）
## 2. Win窗口的创建
1. 主要使用win api去创建一个1024*768的窗口
## 3. Win窗口清除算法
有两种方法，
1. 直接使用win api 的setpixel 
2. 使用位图Bitblt绘制（涉及Framebuffer的概念，使用hdc）
## 4. 绘制一条线段
1. 使用DDA(digital differential analyzer) 算法，在一个坐标轴上对线段以单位间隔取样，计算另一坐标轴上最靠近线段的对应整数值。
2. 使用Bresenham算法。Bresenham 算法是一个只用整数增量进行计算，精确并且有效的光栅线生成算法。
## 5. 三角形坐标系转化（注意左右手系的选择）（1,1,1）（100,200） (200,300)
World（model）、View（Camera）、Projection、NDC、视口变换
## 6. 三角形矩阵变换
模型变换矩阵 平移、缩放、旋转
## 7. 键盘控制
控制物体的平移旋转缩放
## 8. FPS显示
用window画笔
## 9. 扫描线算法(左上规则)
## 10. 背面剔除
## 11. 消隐算法(zbuffer)

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
