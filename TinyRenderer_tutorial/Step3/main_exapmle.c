#include <Windows.h>
static COLORREF redColor = RGB(255, 5, 5);
/// <summary>
/// ������Ϣ����
/// </summary>
/// <param name="hwnd">���ھ��</param>
/// <param name="uMsg">�������Ϣ</param>
/// <param name="wParam">��Ϣ��������1</param>
/// <param name="lParam">��Ϣ��������2</param>
/// <returns></returns>
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("�����ɹ�!"), TEXT("�������д�¼�����"), MB_OK);
		break;
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC dc = BeginPaint(hwnd, &ps);// ��ʼ��ͼ
		// TODO:��������ӻ�ͼ����...
		for (int width = 0; width < 200; width++) {
			for (int height = 0; height < 100; height++) {
				SetPixel(dc, width, height, redColor);
			}
		}
		TextOutW(dc, 30, 30, TEXT("������д����"), wcslen(TEXT("������д����")));// ���
		EndPaint(hwnd, &ps);// ������ͼ
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
/// <param name="hIns">��ǰ�����ʵ�����</param>
/// <param name="hPrevIns">��ǰ�������һ������ʵ���������ʹ��</param>
/// <param name="lpCmdLine">������</param>
/// <param name="nCmdShow">������ʾ��ʽ����󻯣���С����</param>
/// <returns></returns>
int APIENTRY wWinMain(_In_ HINSTANCE hIns, _In_opt_ HINSTANCE hPrevIns, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
	// 1.��ƴ�����
	WNDCLASSEX wce = { 0 };
	wce.cbSize = sizeof(wce);
	wce.cbClsExtra = 0;// ��ĸ�����Ϣ
	wce.cbWndExtra = 0;// ���ڸ�����Ϣ
	wce.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);// ����ɫ������д
	wce.hCursor = LoadCursor(NULL,IDC_HELP);// ����ϵͳ���
	wce.hIcon = LoadIcon(NULL,IDI_WARNING);// ����ϵͳĬ��ͼ��
	wce.hIconSm = NULL;
	wce.hInstance = hIns;// Ӧ�ó���ʵ��
	wce.lpfnWndProc = WndProc;// ��Ϣ������
	wce.lpszClassName = TEXT("main");// ����������
	wce.lpszMenuName = NULL;// �˵�����
	wce.style = CS_HREDRAW | CS_VREDRAW;// ��ʾ���
	// 2.ע�ᴰ����
	ATOM nAtom = RegisterClassEx(&wce);
	if (!nAtom) {
		MessageBox(NULL, TEXT("failed"), TEXT("Infor"), MB_OK);
		return 0;
	}
	// 3.����������
	HWND hwnd = CreateWindowEx(0, TEXT("main"), TEXT("�������д����"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, NULL, NULL, hIns, NULL);// ���ڴ�С1024*768
	// 4.��ʾ�͸��´���
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	// 5.������Ϣѭ��
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);// ���ⰴ��תΪ��׼�ַ�WM_CHAR
		DispatchMessage(&msg);// ������ϵͳ�ַ���Ϣ
	}
	return msg.wParam;
}


