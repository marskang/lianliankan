#include "Main.h"
#include "GameControl.h"
#include "GameEntity.h"

HINSTANCE g_hInstace = 0;
BOOL RegisterWnd(LPCSTR lpszClassName, WNDPROC wndProc);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HWND CreateWnd(LPCSTR lpszClassName, LPCSTR lpszWindowsName);
int Message();
void DisplayWnd(HWND hWnd);
DWORD tPre = GetTickCount();
GameControl gameControl;
D2DResources d2dResources;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	if (!RegisterWnd(TEXT("WinMain"), WndProc)) {
		MessageBox(NULL, TEXT("创建窗口失败"), TEXT("Warning"), MB_YESNOCANCEL);
		return 0;
	}
	d2dResources.CreateDeviceResources();
	HWND hWnd = CreateWnd(TEXT("WinMain"), TEXT("主窗口"));
	d2dResources.m_hwnd = hWnd;
	d2dResources.CreateDeviceIndependentResources();
	initData();
	DisplayWnd(hWnd);
	Message();
	return 0;
}

//注册窗口
BOOL RegisterWnd(LPCSTR lpszClassName, WNDPROC wndProc) {
	WNDCLASSEX wcx = { 0 };
	wcx.cbSize = sizeof(WNDCLASSEX);
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcx.hIcon = NULL;
	wcx.hIconSm = NULL;
	wcx.hInstance = g_hInstace;
	wcx.lpfnWndProc = WndProc;
	wcx.lpszClassName = lpszClassName;
	wcx.lpszMenuName = NULL;
	wcx.style = CS_HREDRAW | CS_VREDRAW;
	ATOM nAtom = RegisterClassEx(&wcx);
	if (0 == nAtom) {
		return FALSE;
	}
	return TRUE;
}

HWND CreateWnd(LPCSTR lpszClassName, LPCSTR lpszWindowsName) {
	HWND hWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		lpszClassName,
		lpszWindowsName,
		WS_OVERLAPPEDWINDOW,
		WND_X, WND_Y,
		WND_WIDTH, WND_HEIGHT,
		NULL, NULL, g_hInstace, NULL);
	return hWnd;
}

void DisplayWnd(HWND hWnd) {
	ShowWindow(hWnd, SW_NORMAL);
	UpdateWindow(hWnd);
}

int Message() {
	MSG nMsg = { 0 };
	/*while (GetMessage(&nMsg, NULL, 0, 0)) {
	TranslateMessage(&nMsg);
	DispatchMessage(&nMsg);
	}*/
	while (true) {
		if (PeekMessage(&nMsg, NULL, 0, 0, PM_REMOVE)) {
			if (nMsg.message == WM_QUIT)
				break;
			TranslateMessage(&nMsg);
			DispatchMessage(&nMsg);
		} else {
			DWORD tNow = GetTickCount();
			if ((tNow - tPre) >= 30) {
				d2dResources.nextFrame();
				tPre = tNow;
			}
			d2dResources.OnRender();
		}
	}
	return (int)nMsg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam) {
	POINT p;
	switch (nMsg) {
	case WM_CREATE:
		//{HWND hButton = CreateWindow("Button", "有种就来点击我！", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		//	767, 387, 160, 65, hWnd, NULL, g_hInstace, NULL); }
		//	return 0;
		break;
	case WM_QUIT:
		PostQuitMessage(0);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break; 
	case WM_PAINT:
		d2dResources.OnRender();
		break;
	case WM_SIZE:
		d2dResources.SizeUpdate(hWnd);
		break;
	case WM_LBUTTONUP:
		GetCursorPos(&p);
		//ClientToScreen(hWnd, &p);
		ScreenToClient(hWnd, &p);
		char x[256];
		char y[256];
		sprintf_s(x, "%ld", p.x);
		sprintf_s(y, "%ld", p.y);
		/*OutputDebugString(y);
		OutputDebugString(" ");
		OutputDebugString(x);
		OutputDebugString("\n");*/
		gameControl.MouseLClickEvent(p);
		break;
	case WM_RBUTTONUP:
		GetCursorPos(&p);
		ScreenToClient(hWnd, &p);
		//MouseLClickEvent(p, 1);
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, nMsg, wParam, lParam);
}

