#include <Windows.h>
static COLORREF redColor = RGB(255, 5, 5);
/// <summary>
/// 窗口消息处理
/// </summary>
/// <param name="hwnd">窗口句柄</param>
/// <param name="uMsg">传入的消息</param>
/// <param name="wParam">消息附带参数1</param>
/// <param name="lParam">消息附带参数2</param>
/// <returns></returns>
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("创建成功!"), TEXT("在这里编写事件标题"), MB_OK);
		break;
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
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}
/// <summary>
/// Main
/// </summary>
/// <param name="hIns">当前程序的实例句柄</param>
/// <param name="hPrevIns">当前程序的上一个程序实例句柄，不使用</param>
/// <param name="lpCmdLine">命令行</param>
/// <param name="nCmdShow">窗口显示样式（最大化，最小化）</param>
/// <returns></returns>
int APIENTRY wWinMain(_In_ HINSTANCE hIns, _In_opt_ HINSTANCE hPrevIns, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
	// 1.设计窗口类
	WNDCLASSEX wce = { 0 };
	wce.cbSize = sizeof(wce);
	wce.cbClsExtra = 0;// 类的附加信息
	wce.cbWndExtra = 0;// 窗口附加信息
	wce.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);// 背景色，必须写
	wce.hCursor = LoadCursor(NULL,IDC_HELP);// 加载系统光标
	wce.hIcon = LoadIcon(NULL,IDI_WARNING);// 加载系统默认图标
	wce.hIconSm = NULL;
	wce.hInstance = hIns;// 应用程序实例
	wce.lpfnWndProc = WndProc;// 消息处理函数
	wce.lpszClassName = TEXT("main");// 窗口类名称
	wce.lpszMenuName = NULL;// 菜单名字
	wce.style = CS_HREDRAW | CS_VREDRAW;// 显示风格
	// 2.注册窗口类
	ATOM nAtom = RegisterClassEx(&wce);
	if (!nAtom) {
		MessageBox(NULL, TEXT("failed"), TEXT("Infor"), MB_OK);
		return 0;
	}
	// 3.创建窗口类
	HWND hwnd = CreateWindowEx(0, TEXT("main"), TEXT("在这里编写标题"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL, hIns, NULL);// 窗口大小1024*768
	// 4.显示和更新窗口
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	// 5.开启消息循环
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);// 虚拟按键转为标准字符WM_CHAR
		DispatchMessage(&msg);// 给操作系统分发消息
	}
	return msg.wParam;
}


