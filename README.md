# CPU Renderer
从零开始写一个Cpu渲染器，对C++小白友好

语言：C++

编译器：Visual Studio 2022


## 编写流程：
## 0. 导入
请看 importTGA 和 importObject文件夹，看懂了就不用看下面的教程链接了：

https://www.notion.so/Import-TGA-202302131600-b26e67a90401473bab05595763e5f69f

https://www.notion.so/Import-Object-202302131847-f41999a350bd4bf09c55a732e9cafa93

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
