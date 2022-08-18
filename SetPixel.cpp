// 本代码摘自main_exapmle.c，目的在于说明如何使用SetPixel()
case WM_PAINT: {
    PAINTSTRUCT ps;
    HDC dc = BeginPaint(hwnd, &ps);// 开始绘图
    // TODO:在这里添加绘图代码...
    for (int width = 0; width < 200; width++) {
        for (int height = 0; height < 100; height++) {
            SetPixel(dc, width, height, redColor);
        }
    }
    TextOutW(dc, 30, 30, TEXT("在这里写内容"), wcslen(TEXT("在这里写内容")));// 输出
    EndPaint(hwnd, &ps);// 结束绘图
    break;
}
