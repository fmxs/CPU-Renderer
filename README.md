# CpuShader
从零开始写一个Cpu渲染器，对C++小白友好

编程语言：C++
编译器：Visual Studio 2022、Visual Studio Code

## 编写流程：
## 1. 数学库的编写
实现VECTOR3，VECTOR4，MATRIX4，转置矩阵，矩阵与向量的乘法问题（左乘，右乘）
## 2. Win窗口的创建
主要使用win api去创建一个1024*768的窗口
## 3. Win窗口清除算法
两种方法，一种直接使用win api 的setpixel 
或者是 使用位图Bitblt绘制（涉及Framebuffer的概念，使用hdc）
## 4. 绘制一条线段
DDA、B
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
