代码参考来源：TinyRenderer

# 如何在VS中导入并使用TGA
## 步骤
打开如下github链接：
https://github.com/ssloy/tinyrenderer/tree/909fe20934ba5334144d2c748805690a1fa4c89f

找到该仓库中的tgaimage.h和tgaimage.cpp文件。
![image](https://user-images.githubusercontent.com/65701532/194848889-7e69fdd4-f50c-4fef-ae01-975b180a892d.png)

将这两个文件复制到自己的VS工程中，作为头文件。

接着在主cpp脚本中引入头文件：
#include "tgaimage.h"
![image](https://user-images.githubusercontent.com/65701532/194849833-f4cd2602-dfa7-4d11-93fc-7f9dad708ea4.png)

至此就可以使用tag中的函数了。