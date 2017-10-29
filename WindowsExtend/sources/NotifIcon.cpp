#include <Windows.h>
#include <Strsafe.h>
#include <shellapi.h>


static	HMENU g_menu;
static	NOTIFYICONDATA	notif = {};
static  HWND g_hwnd;

# define WM_MY_MSG (WM_APP + 100)

enum Context {
	EXIT = 3000,
	OPEN = 3001
};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UINT clicked = 0;
	
	switch (uMsg)
	{
	case WM_MY_MSG:
		switch (lParam)
		{
		case WM_RBUTTONUP:
			POINT curPoint;

			GetCursorPos(&curPoint);
			SetForegroundWindow(hwnd);
			clicked = TrackPopupMenu(g_menu, TPM_RETURNCMD | TPM_NONOTIFY, curPoint.x, curPoint.y, 0, hwnd, NULL);
			switch (clicked)
			{
			case EXIT:
				Shell_NotifyIcon(NIM_DELETE, &notif);
				PostQuitMessage(0);
				break;
			case OPEN:
				ShowWindow(g_hwnd, SW_SHOW);
				break;
			}
			break;
		case WM_LBUTTONUP:
			OutputDebugStringW(L"Trying to open Window\n");
			break;
		}
		break;
	case WM_CLOSE:
		OutputDebugString(L"Got an actual WM_CLOSE Message!  Woo hoo!\n");
		ShowWindow(g_hwnd, SW_HIDE);
		return 0;
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

bool	CreateNotifyIcon(HINSTANCE& hInstance)
{
	static const wchar_t class_name[] = L"ExtendClass";
	WNDCLASSEX wx = {};
	HICON ico = (HICON)LoadImage(NULL, L"./Luma.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
	// Window class initialization
	wx.cbSize = sizeof(WNDCLASSEX);
	wx.lpfnWndProc = WindowProc;
	wx.hInstance = hInstance;
	wx.lpszClassName = class_name;
	RegisterClassEx(&wx);

	// Popup menu initialization
	g_menu = CreatePopupMenu();
	AppendMenu(g_menu, MF_STRING, Context::OPEN, TEXT("Open settings"));
	AppendMenu(g_menu, MF_STRING, Context::EXIT, TEXT("Exit"));

	// Window creation
	g_hwnd = CreateWindowEx(0, class_name, L"Windows Extend", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	if (g_hwnd == NULL)
		OutputDebugStringW(L"failed to create window\n");
	SendMessage(g_hwnd, (UINT)WM_SETICON, ICON_BIG, (LPARAM)ico);

	// NotifyIconData initialization
	ZeroMemory(&notif, sizeof(NOTIFYICONDATA));
	notif.cbSize = sizeof(NOTIFYICONDATA);
	notif.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	notif.uID = 1;
	notif.hWnd = g_hwnd;
	notif.uCallbackMessage = WM_MY_MSG;
	StringCchCopy(notif.szTip, ARRAYSIZE(notif.szTip), L"Access Windows Extend options.");
	StringCchCopy(notif.szInfo, ARRAYSIZE(notif.szInfo), L"Access Windows Extend options.");
	StringCchCopy(notif.szInfoTitle, ARRAYSIZE(notif.szInfoTitle), L"Windows Extend");
	notif.hIcon = ico;

	// Creating NotifyIcon
	if (!notif.hIcon || !Shell_NotifyIcon(NIM_ADD, &notif))
	{
		OutputDebugStringW(L"failed to create notifIcon\n");
		return false;
	}
	return true;
}