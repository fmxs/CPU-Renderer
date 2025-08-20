#include <Windows.h>
/// <summary>
/// 窗口消息处理
/// </summary>
/// <param name="hwnd">窗口句柄</param>
/// <param name="uMsg">传入的消息</param>
/// <param name="wParam">消息附带参数1</param>
/// <param name="lParam">消息附带参数2</param>
/// <returns></returns>
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	HPEN hpen1, oldhpen, hpen2, hpen3, hpen4, hpen5, hpen;
	HBRUSH hbrush1, oldhbrush, hbrush2, hbrush3, hbrush4, hbrush5, hbrush6;
	static int xClient, yClient;
	static POINT apt[5] = { 90,50,110,10,130,50,150,10,180,50 };//5个点
	static POINT capt[] = { 200, 50, 230, 10, 260, 50, 290, 10, 310, 50,
					200, 100, 230, 60, 260, 100, 290, 60, 310, 100,
					200, 150, 230, 110, 260, 150, 290, 110, 310, 150 };
	static DWORD asz[] = { 5,5,5 };
	static POINT bapt[4] = { 350,50,350,80,370,50,450,10 };//4个点
	switch (Message)
	{
	case WM_SIZE:
	{
		xClient = LOWORD(lParam);
		yClient = HIWORD(lParam);
		break;
	}
	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);
		// 画笔写字核心代码
		RECT rcText;
		rcText.left = 10;
		rcText.top = 50;
		rcText.right = 300;
		rcText.bottom = 80;
		DrawText(hdc, TEXT("使用画笔写字示例"), -1, &rcText, DT_LEFT | DT_SINGLELINE | DT_END_ELLIPSIS);

		//还可以使用CreatePenIndirect创建画笔
		//画一个红色点
		SetPixel(hdc, 20, 50, RGB(255, 0, 0));

		//画一条直线
		hpen1 = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));//实线
		oldhpen = (HPEN)SelectObject(hdc, hpen1);//选入画笔
		MoveToEx(hdc, 30, 50, NULL);
		LineTo(hdc, 70, 50);
		SelectObject(hdc, oldhpen);//恢复先前画笔
		DeleteObject(hpen1);//记得自创画笔一定删除

		//画一条5个点折线
		hpen2 = CreatePen(PS_DASH, 1, RGB(255, 255, 0));//段线
		oldhpen = (HPEN)SelectObject(hdc, hpen2);//选入画笔
		Polyline(hdc, apt, 5); //其后缀不带To，表示该函数不使用也不改变设备当前位置
		SelectObject(hdc, oldhpen);//恢复先前画笔
		DeleteObject(hpen2);//记得自创画笔一定删除

		//画3条折线
		hpen3 = CreatePen(PS_DASHDOT, 1, RGB(255, 0, 255));//线点
		SetBkColor(hdc, RGB(0, 0, 222));// 设置当前背景颜色
		oldhpen = (HPEN)SelectObject(hdc, hpen3);//选入画笔
		PolyPolyline(hdc, capt, asz, 3);
		SelectObject(hdc, oldhpen);//恢复先前画笔
		DeleteObject(hpen3);//记得自创画笔一定删除

		//画贝塞尔曲线(最少需要4个点)
		hpen4 = (HPEN)GetStockObject(BLACK_PEN);//获得Windows预设的画笔画刷
		oldhpen = (HPEN)SelectObject(hdc, hpen4);//选入画笔
		PolyBezier(hdc, bapt, 4);// 4个点: 1和4是端点, 2.3点是控制点
								 // 7个点 : 1.4.7是端点, 其余是控制点
		SelectObject(hdc, oldhpen);//恢复先前画笔
		DeleteObject(hpen4);//记得自创画笔一定删除

		//画无边框矩形
		hbrush1 = CreateSolidBrush(RGB(0, 255, 0)); //绿色实心画刷
		hpen = CreatePen(PS_NULL, 1, 0);  //创建空画笔
		oldhpen = (HPEN)SelectObject(hdc, hpen);  //重点：填充图形的边框由当前画笔绘制
		oldhbrush = (HBRUSH)SelectObject(hdc, hbrush1);//选入环境句柄
		Rectangle(hdc, 10, 80, 70, 140);
		SelectObject(hdc, oldhpen);
		SelectObject(hdc, oldhbrush);
		DeleteObject(hbrush1);//删除画刷

		//圆角矩形
		SetBkColor(hdc, RGB(0, 0, 0));// 设置当前背景颜色
		hbrush2 = CreateHatchBrush(HS_FDIAGONAL, RGB(255, 255, 0));//创建画刷
		oldhbrush = (HBRUSH)SelectObject(hdc, hbrush2);//选入设备环境
		RoundRect(hdc, 90, 80, 150, 140, 20, 20);//画图
		SelectObject(hdc, oldhbrush);//恢复先前画刷
		DeleteObject(hbrush2);//删除画刷

		//椭圆
		SetBkColor(hdc, RGB(222, 0, 0));// 设置当前背景颜色
		hbrush3 = CreateHatchBrush(HS_CROSS, RGB(255, 255, 0));
		oldhbrush = (HBRUSH)SelectObject(hdc, hbrush3);
		Ellipse(hdc, 10, 160, 70, 200);
		SelectObject(hdc, oldhbrush);
		DeleteObject(hbrush3);

		//普通弧
		SetDCPenColor(hdc, RGB(255, 0, 255));  //设置句柄颜色
		hpen5 = (HPEN)GetStockObject(DC_PEN);
		oldhpen = (HPEN)SelectObject(hdc, hpen5);
		Arc(hdc, 90, 160, 150, 200, 90, 180, 150, 170);
		SelectObject(hdc, oldhpen);
		DeleteObject(hpen5);
		//圆弧
		MoveToEx(hdc, 190, 200, NULL);
		AngleArc(hdc, 190, 200, 30, 10, 90);  //终点会与当前位置连接起来

		//弓形、弦
		hbrush4 = CreateSolidBrush(RGB(155, 155, 155));
		oldhbrush = (HBRUSH)SelectObject(hdc, hbrush4);
		Chord(hdc, 240, 160, 300, 240, 270, 180, 290, 230);
		SelectObject(hdc, oldhbrush);
		DeleteObject(hbrush4);

		//扇形
		SetBkColor(hdc, RGB(35, 55, 111));// 设置当前背景颜色
		hbrush5 = CreateHatchBrush(HS_HORIZONTAL, RGB(0, 255, 0));
		oldhbrush = (HBRUSH)SelectObject(hdc, hbrush5);
		Pie(hdc, 330, 160, 370, 220, 333, 26, 370, 220);
		SelectObject(hdc, oldhbrush);
		DeleteObject(hbrush5);

		EndPaint(hwnd, &ps);
		break;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
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
	wce.hCursor = LoadCursor(NULL, IDC_HELP);// 加载系统光标
	wce.hIcon = LoadIcon(NULL, IDI_WARNING);// 加载系统默认图标
	wce.hIconSm = NULL;
	wce.hInstance = hIns;// 应用程序实例
	wce.lpfnWndProc = WndProc;// 消息处理函数
	wce.lpszClassName = "main";// 窗口类名称
	wce.lpszMenuName = NULL;// 菜单名字
	wce.style = CS_HREDRAW | CS_VREDRAW;// 显示风格
	// 2.注册窗口类
	ATOM nAtom = RegisterClassEx(&wce);
	if (!nAtom) {
		MessageBox(NULL, "failed", "Infor", MB_OK);
		return 0;
	}
	// 3.创建窗口类
	HWND hwnd = CreateWindowEx(0, "main", "title", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL, hIns, NULL);// 窗口大小1024*768
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
