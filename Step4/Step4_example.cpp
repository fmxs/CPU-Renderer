// Step4_example.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "Step4_example.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
COLORREF redColor = RGB(255, 5, 5);
COLORREF whiteColor = RGB(255, 255, 255);
COLORREF blackColor = RGB(0, 0, 0);
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_STEP4EXAMPLE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_STEP4EXAMPLE));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

// DDA 算法
void DDA(int x0, int y0, int xn, int yn, HDC hdc) {
    int dx = xn - x0;
    int dy = yn - y0;
    int steps, direction;
    float xmid = x0, ymid = y0;
    float xInc, yInc;

    int absdx = abs(dx), absdy = abs(dy);
    if (absdx > absdy) {
        steps = absdx;
        direction = 0;
    }
    else {
        steps = absdy;
        direction = 1;
    }
    xInc = float(dx) / float(steps);
    yInc = float(dy) / float(steps);
    for (int k = 0; k <= steps; ++k) {
        if (direction == 0) {
            SetPixel(hdc, int(xmid), int(ymid + 0.5), redColor);
        }
        else {
            SetPixel(hdc, int(xmid + 0.5), int(ymid), redColor);
        }
        xmid += xInc;
        ymid += yInc;
    }
}

// Bresenham算法
void Bresenham(int x0, int y0, int xn, int yn, HDC hdc) {
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
            SetPixel(hdc, x, y, blackColor);
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
            SetPixel(hdc, x, y, blackColor);
            y += uy;
        }
    }
}

//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_STEP4EXAMPLE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_STEP4EXAMPLE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            // 使用DDC算法绘制红色的线条
            DDA(100, 400, 100, 100, hdc);
            DDA(200, 200, 300, 300, hdc);
            DDA(200, 300, 300, 200, hdc);
            // 使用Bresenham算法绘制黑色的线条
            Bresenham(100, 400, 100, 100, hdc);
            Bresenham(200, 200, 300, 300, hdc);
            Bresenham(200, 300, 300, 200, hdc);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
