# 重复绘制，这是怎么回事？
遇到了一个问题，
使用了本节提供的bresenham代码进行了绘制，以下是结果图：
![image](https://user-images.githubusercontent.com/65701532/195054017-8fcf977c-d7fb-4eb2-b4ea-653f447d8562.png)

代码如下：
```
void Bresenham(int x0, int y0, int xn, int yn, TGAImage& image, TGAColor color) {
    int dx = xn - x0;
    int dy = yn - y0;
    int ux = dx > 0 ? 1 : -1;
    int uy = dy > 0 ? 1 : -1;
    int dxTwice = abs(dx << 1);
    int dyTwice = abs(dy << 1);
    if (abs(dx) > abs(dy)) {
        int e = -dx;
        int x = x0;
        int y = y0;
        while (x != xn + ux) {
            e += dyTwice;
            if (e > 0) {
                if (y != yn) {
                    y += uy;
                }
                e -= dxTwice;
            }
            image.set(x, y, color);
            x += ux;
        }
    }
    else {
        int e = -dy;
        int x = x0;
        int y = y0;
        while (y != yn + uy) {
            e += dxTwice;
            if (e > 0) {
                if (x != xn); {
                    x += ux;
                }
                e -= dyTwice;
            }
            image.set(x, y, color);
            y += uy;
        }
    }
}
```


接着又使用了tinyRenderer作者提供的bresenham代码进行绘制，以下是结果图：
![image](https://user-images.githubusercontent.com/65701532/195054158-a0c0f891-9ffb-46be-b4ab-44958ee6d0e6.png)

代码如下：
```
void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
    bool steep = false;
    // 斜率大于45度时，每个点把自身的 x 和 y 分量交换
    if (std::abs(x0-x1)<std::abs(y0-y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0>x1) {// A 比 B 更靠 x 轴的右侧时，交换两点
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int dx = x1 - x0;
    int dy = y1 - y0;
    int derror2 = std::abs(dy) * 2;
    int error2 = 0;
    int y = y0;
    for (int x = x0; x <= x1; x++) {
        if (steep) {
            image.set(y, x, color);
        }
        else {
            image.set(x, y, color);
        }
        error2 += derror2;
        if (error2 > dx) {
            y += (y1 > y0 ? 1 : -1);
            error2 -= dx * 2;
        }
    }
}
```
