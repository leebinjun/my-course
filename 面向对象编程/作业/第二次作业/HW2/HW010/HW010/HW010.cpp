#include <windows.h>
#include <tchar.h>
#include "resource.h"

long WINAPI WndProc(HWND hwnd, UINT uMsgID, WPARAM wParam, LPARAM lParam);

class Cxwnd { // 将消息处理函数封装成类
public:
	void OnCommand(HWND hwnd, UINT uMsgID, WPARAM wParam, LPARAM lParam);
	void OnDestroy(HWND hwnd, UINT uMsgID, WPARAM wParam, LPARAM lParam);
	void OnPaint(HWND hwnd, UINT uMsgID, WPARAM wParam, LPARAM lParam);
	void OnLButtonDblClick(HWND hwnd, UINT uMsgID, WPARAM wParam, LPARAM lParam);
};

struct msgMap {
	UINT msgID;
	void(Cxwnd::*pfn)(HWND, UINT, WPARAM, LPARAM);
};

class CApplication {
public:
	BOOL InitApplication(HINSTANCE hInst);
	BOOL ProcessShellCommand(LPSTR lpCmdLine, int nShow);
	long Run(void);
private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	MSG m_msg;
};

BOOL CApplication::InitApplication(HINSTANCE hInst)
{
	WNDCLASSEX ex;
	ex.cbSize = sizeof(WNDCLASSEX);
	ex.cbClsExtra = 0;
	ex.cbWndExtra = 0;
	ex.hbrBackground = (HBRUSH)(RGB(0, 255, 0));
	ex.hCursor = LoadCursor(NULL, IDC_ARROW);
	ex.hIcon = NULL;
	ex.hIconSm = NULL;
	ex.hInstance = hInst;
	ex.lpfnWndProc = (WNDPROC)WndProc;
	ex.lpszClassName = _T("First");
	ex.lpszMenuName = (LPCWSTR)IDR_MENU1;
	ex.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&ex))
	{
		return  FALSE;
	}
	m_hInstance = hInst;
	return TRUE;
}

BOOL CApplication::ProcessShellCommand(LPSTR lpCmdLine, int nShow)
{
	HWND hwnd = CreateWindow(_T("First"), _T("FirstWindow"), WS_OVERLAPPEDWINDOW,
		0, 0, 400, 400, NULL, NULL, m_hInstance, NULL);
	if (!hwnd)
		return FALSE;
	m_hWnd = hwnd;
	ShowWindow(m_hWnd, SW_NORMAL);
	UpdateWindow(m_hWnd);
	return TRUE;
}

long CApplication::Run(void)
{
	while (GetMessage(&m_msg, 0, 0, 0))
	{
		TranslateMessage(&m_msg);
		DispatchMessage(&m_msg);
	}
	return m_msg.wParam;
}

msgMap Maps[] = {
	{ WM_DESTROY,&Cxwnd::OnDestroy },
	{ WM_COMMAND,&Cxwnd::OnCommand },
	{ WM_LBUTTONDOWN,&Cxwnd::OnLButtonDblClick },
	{ WM_PAINT,&Cxwnd::OnPaint } };

CApplication theApp;
Cxwnd myWin;

void Cxwnd::OnDestroy(HWND hwnd, UINT uMsgID, WPARAM wParam, LPARAM lParam)
{
	PostQuitMessage(0);
}

void Cxwnd::OnPaint(HWND hwnd, UINT uMsgID, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	TextOut(hdc, 100, 80, _T("This is 010th homework!"), 23);
	EndPaint(hwnd, &ps);
}

void Cxwnd::OnLButtonDblClick(HWND hwnd, UINT uMsgID, WPARAM wParam, LPARAM lParam)
{
	MessageBox(hwnd, _T("Clicked"), _T("Info"), MB_OK);
}

void Cxwnd::OnCommand(HWND hwnd, UINT uMsgID, WPARAM wParam, LPARAM lParam)
{
	UINT uMenuID = LOWORD(wParam);
	switch (uMenuID) {
	case ID_FILE_EXIT:
		DestroyWindow(hwnd);
	}
}

int WINAPI WinMain(HINSTANCE hInst,
	HINSTANCE hPrev,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	if (!theApp.InitApplication(hInst))
		return -1;
	if (!theApp.ProcessShellCommand(lpCmdLine, nShowCmd))
		return -2;
	return theApp.Run();
}

long WINAPI WndProc(HWND hwnd, UINT uMsgID, WPARAM wParam, LPARAM lParam)
{
	int i = 0;
	for (; i<(sizeof(Maps)/sizeof(Maps[0])); ++i)
		if (Maps[i].msgID == uMsgID)
		{
			( myWin.*(Maps[i].pfn))(hwnd, uMsgID, wParam, lParam);
			//Maps[i].pfn(hwnd, uMsgID, wParam, lParam);
			//MessageBox(hwnd, _T("Message"), _T("Message"), MB_OK);
			return 0L;
		}
	return DefWindowProc(hwnd, uMsgID, wParam, lParam);
}