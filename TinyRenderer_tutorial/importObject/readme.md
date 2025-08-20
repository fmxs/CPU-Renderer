这个示例工程旨在告诉你如何读取obj文件。

我们需要导入几个头文件，分别为model.h，model.cpp，以及geometry.h

接着在main函数中，使用类似如下所示的代码：
```
// 导入头文件
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"
int main()
{
  // 声明一个model
  Model *model = NULL;
  // 读取工程目录下的obj文件
  model = new Model("ObjectFile.obj");
}
```
将模型数据读取进来后，使用一些算法对模型进行处理（如bresenham算法），最后输出到一张tga图片上。
输出tga图片的代码如下：
```
const int width  = 800;
const int height = 800;
int main()
{
  // 声明一个图片
  TGAImage image(width, height, TGAImage::RGB);
  // 这里写一个算法来对image进行处理
  line(image);
  // 输出图片
  image.write_tga_file("FileName.tga"); 
}
```
