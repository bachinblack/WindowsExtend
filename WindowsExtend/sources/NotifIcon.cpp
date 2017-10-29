#include <Windows.h>
#include <Strsafe.h>
#include <shellapi.h>


static	HMENU g_menu;
static NOTIFYICONDATA	notif = {};

# define WM_MY_MSG (WM_APP + 100)
# define ID_TRAY_EXIT_CONTEXT_MENU_ITEM  3000

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UINT clicked = 0;
	OutputDebugStringW(L"Message!\n");

	switch (uMsg)
	{
	case WM_MY_MSG:
		switch (lParam)
		{
		case WM_RBUTTONUP:
			OutputDebugStringW(L"Trying to open Context menu\n");
			POINT curPoint;

			GetCursorPos(&curPoint);
			SetForegroundWindow(hwnd);
			clicked = TrackPopupMenu(g_menu, TPM_RETURNCMD | TPM_NONOTIFY, curPoint.x, curPoint.y, 0, hwnd, NULL);
			if (clicked == ID_TRAY_EXIT_CONTEXT_MENU_ITEM)
			{
				Shell_NotifyIcon(NIM_DELETE, &notif);
				PostQuitMessage(0);
			}
			break;
		case WM_MBUTTONUP:
			OutputDebugStringW(L"Trying to open nothing\n");
			break;
		case WM_LBUTTONUP:
			OutputDebugStringW(L"Trying to open Window\n");
			break;
		}
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

bool	CreateNotifyIcon(HINSTANCE& hInstance)
{
	static const wchar_t class_name[] = L"ExtendClass";
	WNDCLASSEX wx = {};
	wx.cbSize = sizeof(WNDCLASSEX);
	wx.lpfnWndProc = WindowProc;
	wx.hInstance = hInstance;
	wx.lpszClassName = class_name;

	g_menu = CreatePopupMenu();
	AppendMenu(g_menu, MF_STRING, ID_TRAY_EXIT_CONTEXT_MENU_ITEM, TEXT("Exit"));


	RegisterClassEx(&wx);
	HWND win = CreateWindowEx(0, class_name, L"Windows Extend", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	if (win == NULL)
		OutputDebugStringW(L"failed to create window\n");
	ZeroMemory(&notif, sizeof(NOTIFYICONDATA));
	notif.cbSize = sizeof(NOTIFYICONDATA);
	notif.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	// Need to find a non-busy uID
	notif.uID = 44421;
	notif.hWnd = win;
	notif.uCallbackMessage = WM_MY_MSG;
	StringCchCopy(notif.szTip, ARRAYSIZE(notif.szTip), L"Access Windows Extend options.");
	StringCchCopy(notif.szInfo, ARRAYSIZE(notif.szInfo), L"Access Windows Extend options.");
	StringCchCopy(notif.szInfoTitle, ARRAYSIZE(notif.szInfoTitle), L"Windows Extend");
	notif.hIcon = (HICON)LoadImage(NULL, L"./Luma.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);

	if (!Shell_NotifyIcon(NIM_ADD, &notif))
	{
		OutputDebugStringW(L"failed to create notifIcon\n");
		return false;
	}
	return true;
}